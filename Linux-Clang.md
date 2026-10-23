# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| Simdjson (On Demand): [70f83c9](https://github.com/simdjson/simdjson/commit/70f83c9)  

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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 294.629 | 0.221406 | 1091.99ms | 905 | 30 | 1261.96 | 2929.37 | 0.0159332 | 17.4165 | 52.8387 | 7.89945 | 0.0179374 | 3.68324e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 217.267 | 0.0644125 | 1185.89ms | 905 | 2560 | 16760.6 | 3972.42 | 0.360761 | 23.4677 | 90.9293 | 10.8055 | 0.0235044 | 0.000221858 | 7.12189e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 296.745 | 0.0840336 | 1090.12ms | 905 | 640 | 3823.12 | 2908.48 | 0.0190141 | 17.2764 | 52.2243 | 7.77901 | 0.0206544 | 0.000146754 | 2.58978e-05 | 1(Win) | true |
| simdjson (ondemand) | 218.557 | 0.037792 | 1191.23ms | 905 | 4890 | 10891.2 | 3948.97 | 0.299279 | 23.3661 | 90.3149 | 10.6851 | 0.0230112 | 0.000267091 | 0.000108012 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 415.253 | 0.0603073 | 1209.73ms | 1811 | 2560 | 16106.1 | 4159.16 | 0.0262103 | 12.2811 | 40.1938 | 6.93485 | 0.00117597 | 0.000126613 | 2.43736e-05 | 1(Win) | true |
| simdjson (ondemand) | 269.524 | 0.0260568 | 1377.03ms | 1811 | 4890 | 13633.1 | 6407.98 | 0.152877 | 18.8585 | 69.5097 | 9.53065 | 0.000635742 | 0.000124664 | 3.45537e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 418.036 | 0.0779549 | 1165.03ms | 1811 | 640 | 6638.6 | 4131.47 | 0.253841 | 12.0731 | 39.159 | 6.709 | 0.00170831 | 9.1455e-05 | 1.2079e-05 | 1(Win) | true |
| simdjson (ondemand) | 271.141 | 0.0625618 | 1371.24ms | 1811 | 640 | 10163.5 | 6369.76 | 0.000932131 | 18.7563 | 68.5748 | 9.32413 | 0.00066348 | 5.34925e-05 | 1.46673e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 930.887 | 0.0655544 | 1136.13ms | 3862 | 80 | 538.176 | 3956.54 | 0.0300226 | 5.48626 | 17.9433 | 2.36976 | 0.000812403 | 5.50233e-05 | 6.47333e-06 | 1(Win) | true |
| simdjson (ondemand) | 554.856 | 0.0441222 | 1401.62ms | 3862 | 2560 | 21959.4 | 6637.93 | 0.0109527 | 9.15415 | 27.5593 | 3.59244 | 0.0128138 | 9.31553e-05 | 3.98514e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 937.362 | 0.0397712 | 1130.13ms | 3862 | 4890 | 11941.4 | 3929.21 | 0.0435421 | 5.39648 | 17.4689 | 2.26334 | 0.00105855 | 6.80428e-05 | 2.39341e-05 | 1(Win) | true |
| simdjson (ondemand) | 555.974 | 0.0271611 | 1398.62ms | 3862 | 4890 | 15831.4 | 6624.57 | 0.090117 | 9.13107 | 27.123 | 3.4956 | 0.0158666 | 7.38145e-05 | 1.79506e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1181.93 | 0.0673345 | 1513.71ms | 9578 | 2560 | 69323.5 | 7728.27 | 0.0117958 | 4.29129 | 18.3522 | 3.45625 | 0.00192503 | 4.372e-05 | 1.47229e-05 | 1(Win) | true |
| simdjson (ondemand) | 1134.49 | 0.053015 | 1555.7ms | 9578 | 4890 | 89094.9 | 8051.44 | 0.0201907 | 4.43502 | 17.718 | 3.04625 | 0.003375 | 3.9243e-05 | 1.18925e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1538.25 | 0.0572719 | 1467.94ms | 9578 | 4890 | 56557.6 | 5938.12 | 0.0337733 | 3.28676 | 14.1094 | 2.49896 | 0.0012951 | 4.52426e-05 | 1.75291e-05 | 1(Win) | true |
| simdjson (ondemand) | 1455.68 | 0.310483 | 1514.1ms | 9578 | 30 | 11387.2 | 6274.93 | 0.229479 | 3.49759 | 13.4468 | 2.08854 | 0.00243962 | 8.35247e-05 | 4.17624e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 933.353 | 0.0822588 | 1133.44ms | 3873 | 40 | 423.866 | 3957.32 | 0.0439918 | 5.47066 | 17.9029 | 2.3953 | 0.00546088 | 3.87297e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 577.588 | 0.0518567 | 1383.32ms | 3873 | 1280 | 14076 | 6394.83 | 0.1299 | 8.79571 | 27.182 | 3.67209 | 0.0150806 | 7.84679e-05 | 2.40043e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 930.552 | 0.0597955 | 1133.54ms | 3873 | 2560 | 14420.8 | 3969.24 | 0.106636 | 5.43705 | 17.4265 | 2.28738 | 0.00713856 | 9.20838e-05 | 3.31824e-05 | 1(Win) | true |
| simdjson (ondemand) | 586.063 | 0.0706884 | 1377.87ms | 3873 | 320 | 6351.15 | 6302.36 | 0.207576 | 8.68 | 26.6987 | 3.55952 | 0.0174542 | 3.38885e-05 | 0 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 700.145 | 0.114758 | 4306.87ms | 2090234 | 80 | 8.54018e+08 | 2.84713e+06 | 0.152111 | 7.1685 | 32.1195 | 6.20156 | 0.0228204 | 0.103604 | 0.00157335 | 1(Win) | true |
| simdjson (ondemand) | 662.794 | 0.131812 | 4524.64ms | 2090234 | 80 | 1.25729e+09 | 3.00758e+06 | 0.00299045 | 7.54764 | 30.8046 | 5.60156 | 0.0225674 | 0.103893 | 0.00155434 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 802.336 | 0.135925 | 4318.29ms | 2090234 | 80 | 9.12357e+08 | 2.4845e+06 | 0.0322558 | 6.23261 | 26.7592 | 4.90594 | 0.0218127 | 0.0785448 | 0.00137671 | 1(Win) | true |
| simdjson (ondemand) | 756.942 | 0.232424 | 4543.88ms | 2090234 | 30 | 1.12395e+09 | 2.6335e+06 | 0.219099 | 6.60324 | 25.4505 | 4.30739 | 0.021657 | 0.0785563 | 0.0010008 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2078.44 | 0.193816 | 4636.54ms | 6661897 | 80 | 2.80795e+09 | 3.05675e+06 | 0.397814 | 2.4007 | 10.9881 | 1.98849 | 0.00633758 | 0.0545511 | 0.00227023 | 1(Win) | true |
| simdjson (ondemand) | 1978.91 | 0.367759 | 4861ms | 6661897 | 30 | 4.18205e+09 | 3.21049e+06 | 0.203021 | 2.54825 | 10.515 | 1.7979 | 0.0063367 | 0.0545049 | 0.00258338 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2362.06 | 0.207338 | 4640.26ms | 6661897 | 40 | 1.24403e+09 | 2.68972e+06 | 0.0407782 | 2.11078 | 9.30839 | 1.58237 | 0.00605446 | 0.0465722 | 0.00267731 | 1(Win) | true |
| simdjson (ondemand) | 2240.7 | 0.157606 | 4840.84ms | 6661897 | 80 | 1.59758e+09 | 2.8354e+06 | 0.270399 | 2.24014 | 8.83259 | 1.39131 | 0.00605946 | 0.0465259 | 0.00196288 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 608.102 | 0.110262 | 4953.5ms | 2090234 | 80 | 1.04515e+09 | 3.27807e+06 | 0.0985161 | 8.25849 | 39.0428 | 7.34634 | 0.0231501 | 0.179825 | 0.00236788 | 1(Win) | true |
| simdjson (ondemand) | 571.813 | 0.348108 | 5210.39ms | 2090234 | 40 | 5.89075e+09 | 3.48611e+06 | 0.254671 | 8.74162 | 37.5716 | 6.80038 | 0.0233828 | 0.179548 | 0.00596651 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 687.674 | 0.129961 | 4946.62ms | 2090234 | 80 | 1.13538e+09 | 2.89876e+06 | 0.0168799 | 7.2757 | 33.6915 | 6.05252 | 0.0222315 | 0.154156 | 0.000825344 | 1(Win) | true |
| simdjson (ondemand) | 646.642 | 0.22265 | 5200.1ms | 2090234 | 30 | 1.41328e+09 | 3.0827e+06 | 0.143648 | 7.72069 | 32.2281 | 5.50845 | 0.0223191 | 0.153899 | 0.00318958 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1746.24 | 0.414908 | 5442.27ms | 6661897 | 40 | 9.11489e+09 | 3.63826e+06 | 0.681111 | 2.85081 | 13.1653 | 2.34861 | 0.00641647 | 0.11119 | 0.00328852 | 1(Win) | true |
| simdjson (ondemand) | 1696.15 | 0.596726 | 5630.97ms | 6661897 | 40 | 1.99837e+10 | 3.7457e+06 | 0.181573 | 2.96359 | 12.6262 | 2.17161 | 0.0066231 | 0.112025 | 0.0017217 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2013.3 | 0.330041 | 5391.54ms | 6661897 | 30 | 3.25413e+09 | 3.15565e+06 | 0.0698966 | 2.48884 | 11.4833 | 1.94207 | 0.00613851 | 0.103192 | 0.0012362 | 1(Win) | true |
| simdjson (ondemand) | 1916.17 | 0.308949 | 5601.24ms | 6661897 | 40 | 4.19721e+09 | 3.31562e+06 | 0.588018 | 2.62186 | 10.9585 | 1.76791 | 0.0063047 | 0.103933 | 0.00140255 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6291.62 | 0.249729 | 4125.43ms | 2090234 | 320 | 2.00334e+08 | 316834 | 0.128129 | 0.793198 | 4.33222 | 0.398854 | 0.00263046 | 0.0507698 | 3.41469e-06 | 1(Win) | true |
| simdjson (ondemand) | 6032.47 | 0.0579339 | 4305.1ms | 2090234 | 640 | 2.34556e+07 | 330446 | 0.196986 | 0.826422 | 4.32274 | 0.49882 | 0.00235845 | 0.0498802 | 3.64941e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6293.09 | 0.155424 | 4113.69ms | 2090234 | 320 | 7.7562e+07 | 316761 | 0.557464 | 0.791047 | 4.33214 | 0.398836 | 0.00264082 | 0.0507333 | 3.28761e-06 | 1(Win) | true |
| simdjson (ondemand) | 6016.54 | 0.0798187 | 4297.21ms | 2090234 | 160 | 1.11899e+07 | 331320 | 0.105037 | 0.826992 | 4.32267 | 0.498802 | 0.00236629 | 0.0498183 | 3.42366e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 13052.7 | 0.0627521 | 6293.73ms | 6661897 | 320 | 2.9854e+07 | 486741 | 0.0622343 | 0.380821 | 2.16283 | 0.151579 | 0.000315948 | 0.0376488 | 9.89161e-06 | 1(Win) | true |
| simdjson (ondemand) | 11358.1 | 0.0490055 | 7228.59ms | 6661897 | 640 | 4.80904e+07 | 559363 | 0.171095 | 0.440961 | 2.20354 | 0.196347 | 0.000422221 | 0.0377329 | 6.6582e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12979.5 | 0.0934946 | 6311.79ms | 6661897 | 320 | 6.70201e+07 | 489487 | 0.05399 | 0.3808 | 2.16281 | 0.151574 | 0.000315351 | 0.0376836 | 5.10506e-06 | 1(Win) | true |
| simdjson (ondemand) | 11404.3 | 0.178587 | 7244.38ms | 6661897 | 30 | 2.96945e+07 | 557093 | 0.268264 | 0.440765 | 2.20351 | 0.196341 | 0.000423973 | 0.0377242 | 6.68979e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4184.6 | 0.0799436 | 6181.62ms | 2090234 | 160 | 2.32044e+07 | 476367 | 0.142609 | 1.19423 | 6.67133 | 0.899192 | 0.00264774 | 0.0727723 | 8.34536e-06 | 1(Win) | true |
| jsonifier (generic) | 4109.24 | 0.160376 | 6234.91ms | 2090234 | 40 | 2.42106e+07 | 485103 | 0.132959 | 1.21149 | 6.89163 | 0.718794 | 0.00276422 | 0.0743465 | 6.20744e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4162.71 | 0.36278 | 6197.41ms | 2090234 | 160 | 4.82887e+08 | 478872 | 0.449932 | 1.20414 | 6.67125 | 0.899174 | 0.00260024 | 0.0727441 | 5.59148e-06 | 1(Win) | true |
| jsonifier (generic) | 4124.21 | 0.0293104 | 6225.55ms | 2090234 | 640 | 1.28449e+07 | 483342 | 0.22193 | 1.20614 | 6.89155 | 0.718776 | 0.00262846 | 0.0743034 | 7.05438e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9629.6 | 0.122961 | 4204.53ms | 6661897 | 160 | 1.05301e+08 | 659766 | 0.212841 | 0.515572 | 2.96587 | 0.251964 | 0.000316083 | 0.056425 | 1.8421e-05 | 1(Win) | true |
| simdjson (ondemand) | 8854.47 | 0.157089 | 4592.19ms | 6661897 | 40 | 5.08188e+07 | 717523 | 0.0334013 | 0.566013 | 2.94043 | 0.321967 | 0.000504102 | 0.0565615 | 1.22975e-05 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9667.22 | 0.127989 | 4206.19ms | 6661897 | 160 | 1.13202e+08 | 657198 | 0.188577 | 0.515566 | 2.96585 | 0.251958 | 0.000315774 | 0.0564218 | 1.42377e-05 | 1(Win) | true |
| simdjson (ondemand) | 8853 | 0.164971 | 4590.97ms | 6661897 | 30 | 4.20487e+07 | 717641 | 0.0781302 | 0.565525 | 2.9404 | 0.321962 | 0.000494489 | 0.0565658 | 1.09929e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1129.66 | 0.152052 | 5478.18ms | 500299 | 320 | 1.31976e+08 | 422358 | 0.370926 | 4.41874 | 17.6787 | 3.0394 | 0.0154789 | 0.0103536 | 0.000198313 | 1(Win) | true |
| simdjson (ondemand) | 1069.17 | 0.183589 | 5818.25ms | 500299 | 30 | 2.01362e+07 | 446253 | 0.31966 | 4.66677 | 17.1222 | 2.93717 | 0.0237988 | 0.0109265 | 0.000125658 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1270.5 | 0.0760664 | 5302.53ms | 500299 | 640 | 5.22249e+07 | 375540 | 0.0092945 | 3.94068 | 16.5308 | 2.76094 | 0.00950615 | 0.0086945 | 8.4259e-05 | 1(Win) | true |
| simdjson (ondemand) | 1190.81 | 0.0543867 | 5630.95ms | 500299 | 640 | 3.03907e+07 | 400671 | 0.278168 | 4.20308 | 15.9761 | 2.66098 | 0.0180859 | 0.00810786 | 0.000136721 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2892.45 | 0.103185 | 6154.33ms | 1439562 | 160 | 3.83784e+07 | 474640 | 0.056965 | 1.7186 | 7.1007 | 1.10192 | 0.00516967 | 0.0437285 | 4.87735e-05 | 1(Win) | true |
| simdjson (ondemand) | 2752.87 | 0.0650688 | 6479.48ms | 1439562 | 640 | 6.73932e+07 | 498707 | 0.0735205 | 1.81941 | 6.8139 | 1.06193 | 0.00864155 | 0.0431508 | 2.56306e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3172.55 | 0.449134 | 6048.79ms | 1439562 | 80 | 3.02194e+08 | 432735 | 0.0282672 | 1.57168 | 6.70366 | 1.00564 | 0.00346145 | 0.0404036 | 5.03712e-05 | 1(Win) | true |
| simdjson (ondemand) | 3007.65 | 0.104428 | 6372.26ms | 1439562 | 160 | 3.63549e+07 | 456460 | 0.148263 | 1.66385 | 6.41665 | 0.966247 | 0.00691894 | 0.0399665 | 4.60644e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 409.662 | 0.0731053 | 7413.94ms | 500299 | 160 | 1.15991e+08 | 1.16467e+06 | 0.295578 | 12.2416 | 52.6529 | 12.338 | 0.0461984 | 0.0276186 | 0.000157893 | 1(Win) | true |
| simdjson (ondemand) | 246.891 | 0.0991464 | 6033.66ms | 500299 | 80 | 2.93691e+08 | 1.93252e+06 | 0.24783 | 20.3058 | 87.6637 | 15.657 | 0.0896693 | 0.0207126 | 0.000322207 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 431.17 | 0.111752 | 7279.56ms | 500299 | 80 | 1.22339e+08 | 1.10658e+06 | 0.0564718 | 11.6606 | 51.5162 | 12.0616 | 0.0397151 | 0.0228579 | 0.00016705 | 1(Win) | true |
| simdjson (ondemand) | 251.367 | 0.15728 | 5984.7ms | 500299 | 40 | 3.56494e+08 | 1.89811e+06 | 0.281912 | 19.7858 | 86.5159 | 15.3811 | 0.0824605 | 0.0135913 | 0.00025085 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1125.69 | 0.0632599 | 7734.54ms | 1439562 | 320 | 1.90471e+08 | 1.21958e+06 | 0.0972896 | 4.44859 | 19.248 | 4.33056 | 0.0154287 | 0.0739392 | 0.000116928 | 1(Win) | true |
| simdjson (ondemand) | 686.998 | 0.164968 | 6202.4ms | 1439562 | 40 | 4.34721e+08 | 1.99836e+06 | 0.199805 | 7.24131 | 31.3102 | 5.47843 | 0.0301605 | 0.118057 | 6.47419e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1179.77 | 0.116132 | 7584.13ms | 1439562 | 320 | 5.84416e+08 | 1.16368e+06 | 0.031342 | 4.24611 | 18.8493 | 4.23372 | 0.0128692 | 0.0689889 | 2.46711e-05 | 1(Win) | true |
| simdjson (ondemand) | 709.654 | 0.13111 | 6159.89ms | 1439562 | 80 | 5.14669e+08 | 1.93457e+06 | 0.018046 | 7.06215 | 30.9103 | 5.38236 | 0.0278165 | 0.109332 | 5.06057e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4110.83 | 0.174257 | 6313.03ms | 500299 | 640 | 2.61796e+07 | 116065 | 0.0896195 | 1.22387 | 5.68777 | 1.04017 | 0.00251298 | 3.88892e-05 | 2.6887e-05 | 1(Win) | true |
| simdjson (ondemand) | 3193.28 | 0.119626 | 4004.38ms | 500299 | 80 | 2.55579e+06 | 149415 | 0.00684291 | 1.57779 | 6.73784 | 0.860534 | 0.00237391 | 0.000284455 | 7.89278e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4145.37 | 0.036471 | 6287.4ms | 500299 | 1280 | 2.25547e+06 | 115098 | 0.107023 | 1.21141 | 5.65893 | 1.03339 | 0.00246155 | 1.84796e-05 | 9.51618e-06 | 1(Win) | true |
| simdjson (ondemand) | 3225.44 | 0.02558 | 7978.06ms | 500299 | 1280 | 1.8327e+06 | 147925 | 0.0481221 | 1.56355 | 6.70905 | 0.853752 | 0.00232457 | 0.000232042 | 2.20056e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8432.69 | 0.154716 | 4378.57ms | 1439562 | 320 | 2.03024e+07 | 162804 | 0.0351527 | 0.596385 | 2.87776 | 0.399226 | 0.00133865 | 0.016133 | 1.80068e-05 | 1(Win) | true |
| simdjson (ondemand) | 6816.9 | 0.281117 | 5363.2ms | 1439562 | 80 | 2.5642e+07 | 201393 | 0.146434 | 0.735798 | 3.20358 | 0.339818 | 0.00124441 | 0.0174968 | 4.14188e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8590.92 | 0.108704 | 4345.25ms | 1439562 | 40 | 1.20707e+06 | 159805 | 0.108187 | 0.588359 | 2.86774 | 0.396869 | 0.00132974 | 0.0145816 | 4.93206e-06 | 1(Win) | true |
| simdjson (ondemand) | 6880.32 | 0.169976 | 5275.56ms | 1439562 | 30 | 3.45098e+06 | 199536 | 0.0716815 | 0.730089 | 3.19357 | 0.337461 | 0.00123431 | 0.0166284 | 6.59923e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2146.28 | 0.0970508 | 5854.53ms | 500299 | 640 | 2.97897e+07 | 222302 | 0.0536452 | 2.35476 | 12.3616 | 2.36146 | 0.0055258 | 2.46634e-05 | 7.09576e-06 | 1(Win) | true |
| simdjson (ondemand) | 1772.35 | 0.0859837 | 7101.44ms | 500299 | 160 | 8.57262e+06 | 269204 | 0.0395071 | 2.85078 | 13.8241 | 2.13988 | 0.00705409 | 0.000412503 | 0.000109122 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2159.54 | 0.054177 | 5851.84ms | 500299 | 1280 | 1.8339e+07 | 220937 | 0.351159 | 2.34862 | 12.3327 | 2.35468 | 0.00544646 | 3.7526e-05 | 1.93369e-05 | 1(Win) | true |
| simdjson (ondemand) | 1781.42 | 0.0322768 | 7061.6ms | 500299 | 640 | 4.78286e+06 | 267833 | 0.174669 | 2.83852 | 13.7953 | 2.1331 | 0.00695109 | 0.000358776 | 8.81036e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5072.31 | 0.201917 | 7203.88ms | 1439562 | 160 | 4.77878e+07 | 270660 | 0.0282722 | 0.99268 | 5.19714 | 0.85842 | 0.00253499 | 0.0166359 | 8.86989e-06 | 1(Win) | true |
| simdjson (ondemand) | 4283.13 | 0.05519 | 4185.08ms | 1439562 | 320 | 1.0014e+07 | 320531 | 0.129806 | 1.17961 | 5.66631 | 0.784438 | 0.00295383 | 0.0177513 | 4.51309e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5051.87 | 0.163805 | 7195.86ms | 1439562 | 1280 | 2.53641e+08 | 271756 | 0.0612047 | 0.99926 | 5.18712 | 0.856063 | 0.00251744 | 0.0150586 | 5.87907e-06 | 1(Win) | true |
| simdjson (ondemand) | 4288.82 | 0.0466942 | 4174.49ms | 1439562 | 640 | 1.42985e+07 | 320105 | 0.017176 | 1.17934 | 5.65631 | 0.782081 | 0.00296522 | 0.0169473 | 2.42695e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1440.05 | 0.0373663 | 4481.54ms | 56369 | 2560 | 498114 | 37330.5 | 0.0575681 | 3.49976 | 14.9525 | 2.84175 | 0.00544624 | 4.15995e-05 | 1.79204e-05 | 1(Win) | true |
| simdjson (ondemand) | 1254.16 | 0.0251884 | 5040.92ms | 56369 | 4890 | 570010 | 42863.3 | 0.0289815 | 4.03238 | 15.3726 | 2.80782 | 0.0128938 | 8.02773e-05 | 4.88963e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1816.67 | 0.0846279 | 4041.86ms | 56369 | 640 | 401360 | 29591.3 | 0.0734369 | 2.7777 | 12.7181 | 2.35527 | 0.00407712 | 1.74353e-05 | 9.31363e-06 | 1(Win) | true |
| simdjson (ondemand) | 1470.09 | 0.215231 | 4792.5ms | 56369 | 40 | 247778 | 36567.6 | 0.0886587 | 3.44039 | 13.1692 | 2.32835 | 0.015108 | 2.21753e-05 | 1.24182e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2283.48 | 0.100385 | 4697.79ms | 94370 | 4890 | 7.65452e+06 | 39412.7 | 0.135087 | 2.21301 | 9.57489 | 1.72614 | 0.00339851 | 2.4292e-05 | 1.18448e-05 | 1(Win) | true |
| simdjson (ondemand) | 1981.64 | 0.0554769 | 5304.24ms | 94370 | 1280 | 812558 | 45416.1 | 0.00639268 | 2.55637 | 9.71463 | 1.70193 | 0.00893253 | 7.91929e-05 | 5.9937e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2834.6 | 0.0327611 | 4258.59ms | 94370 | 4890 | 529069 | 31749.9 | 0.0118283 | 1.78396 | 8.24224 | 1.43564 | 0.00252936 | 1.73793e-05 | 1.10733e-05 | 1(Win) | true |
| simdjson (ondemand) | 2426.27 | 0.0606963 | 4846.5ms | 94370 | 2560 | 1.29764e+06 | 37093.3 | 0.0373707 | 2.08463 | 8.40187 | 1.41635 | 0.00628624 | 3.20878e-05 | 2.62845e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 477.65 | 0.0473928 | 6174.31ms | 56369 | 1280 | 3.64164e+06 | 112546 | 0.0512003 | 10.5879 | 46.1727 | 9.63073 | 0.0291435 | 0.000275417 | 0.000222779 | 1(Win) | true |
| simdjson (ondemand) | 139.826 | 0.0615171 | 4990.49ms | 56369 | 320 | 1.78998e+07 | 384462 | 0.00385589 | 36.0955 | 178.866 | 33.0546 | 0.0709875 | 0.000281238 | 0.000185496 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 520.258 | 0.0265448 | 5856.01ms | 56369 | 2560 | 1.92594e+06 | 103329 | 0.0359555 | 9.69894 | 44.0042 | 9.16364 | 0.0240452 | 5.86468e-05 | 4.35606e-05 | 1(Win) | true |
| simdjson (ondemand) | 142.86 | 0.0477362 | 4932.37ms | 56369 | 640 | 2.06508e+07 | 376297 | 0.0147995 | 35.3332 | 176.723 | 32.5951 | 0.0657621 | 0.000150875 | 9.05307e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 784.043 | 0.120482 | 6250.04ms | 94370 | 320 | 6.12041e+06 | 114787 | 0.0604471 | 6.44772 | 28.1477 | 5.75682 | 0.0178208 | 0.00020415 | 0.000150968 | 1(Win) | true |
| simdjson (ondemand) | 234.303 | 0.0282844 | 4983.38ms | 94370 | 640 | 7.55413e+06 | 384110 | 0.0460566 | 21.5649 | 107.191 | 19.7207 | 0.0409485 | 0.000118334 | 9.7737e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 850.986 | 0.0702602 | 5978.49ms | 94370 | 640 | 3.53363e+06 | 105758 | 0.063437 | 5.9134 | 26.8534 | 5.47844 | 0.014473 | 7.09971e-05 | 5.19895e-05 | 1(Win) | true |
| simdjson (ondemand) | 239.126 | 0.044379 | 4921.09ms | 94370 | 640 | 1.78546e+07 | 376363 | 0.0722326 | 21.0334 | 105.911 | 19.4464 | 0.0377977 | 3.54986e-05 | 2.17727e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2107.16 | 0.0312158 | 3320.88ms | 56369 | 2560 | 162358 | 25511.9 | 0.0422342 | 2.40225 | 10.5936 | 1.77585 | 0.00363779 | 1.0762e-05 | 3.80445e-06 | 1(Win) | true |
| jsonifier (generic) | 1981.2 | 0.0454349 | 3490.11ms | 56369 | 2560 | 389084 | 27133.9 | 0.0606877 | 2.56001 | 11.02 | 1.76705 | 0.00727371 | 6.97275e-05 | 5.27911e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2577.36 | 0.041953 | 3154.39ms | 56369 | 2560 | 196019 | 20857.7 | 0.030714 | 1.97245 | 8.97201 | 1.42452 | 0.00287394 | 2.59243e-05 | 1.6971e-05 | 1(Win) | true |
| jsonifier (generic) | 2426.04 | 0.0473554 | 3294.64ms | 56369 | 2560 | 281879 | 22158.6 | 0.0176502 | 2.08835 | 9.40356 | 1.41679 | 0.00550124 | 1.09491e-05 | 5.0033e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3238.34 | 0.0586222 | 3548.48ms | 94370 | 4890 | 1.29795e+06 | 27791.5 | 0.113294 | 1.56237 | 6.86723 | 1.08749 | 0.00274773 | 1.96741e-05 | 1.26032e-05 | 1(Win) | true |
| jsonifier (generic) | 3047.33 | 0.0614453 | 3729.48ms | 94370 | 1280 | 421519 | 29533.5 | 0.125188 | 1.6595 | 7.21385 | 1.08071 | 0.00493318 | 1.55306e-05 | 9.4707e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3973.84 | 0.0516396 | 3351.51ms | 94370 | 1280 | 175075 | 22647.7 | 0.0392339 | 1.27549 | 5.89452 | 0.877005 | 0.00168037 | 1.96451e-05 | 1.49263e-05 | 1(Win) | true |
| jsonifier (generic) | 3734.45 | 0.0358163 | 3468.85ms | 94370 | 4890 | 364320 | 24099.4 | 0.0171939 | 1.35178 | 6.2459 | 0.871146 | 0.00324171 | 4.80639e-06 | 1.7856e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1309.57 | 0.0939501 | 4934.35ms | 56369 | 640 | 951916 | 41049.9 | 0.132014 | 3.85653 | 18.7115 | 3.81053 | 0.00799719 | 1.30834e-05 | 8.03855e-06 | 1(Win) | true |
| simdjson (ondemand) | 1252.26 | 0.0772912 | 5071.3ms | 56369 | 4890 | 5.38346e+06 | 42928.5 | 0.0408021 | 4.04243 | 18.4105 | 3.32592 | 0.00841818 | 5.2136e-05 | 3.65725e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1463.13 | 0.177452 | 4738.86ms | 56369 | 2560 | 1.08822e+07 | 36741.5 | 0.197652 | 3.43342 | 17.1423 | 3.47294 | 0.00733754 | 2.53006e-05 | 1.23212e-05 | 1(Win) | true |
| simdjson (ondemand) | 1392.75 | 0.0206607 | 4930.59ms | 56369 | 4890 | 310980 | 38598.2 | 0.080318 | 3.62714 | 16.8384 | 2.99003 | 0.00809368 | 1.21461e-05 | 6.35601e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2112.49 | 0.0422574 | 5037.33ms | 94370 | 2560 | 829708 | 42603 | 0.0947603 | 2.3951 | 11.7512 | 2.28103 | 0.00475973 | 9.78115e-06 | 4.84711e-06 | 1(Win) | true |
| simdjson (ondemand) | 2031.13 | 0.0249622 | 5208.64ms | 94370 | 4890 | 598225 | 44309.4 | 0.0400608 | 2.48966 | 11.4143 | 1.98407 | 0.00494844 | 4.76478e-05 | 3.62798e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2374.26 | 0.0372135 | 4847.42ms | 94370 | 4890 | 973014 | 37905.7 | 0.0958955 | 2.11779 | 10.8133 | 2.07959 | 0.00404588 | 6.88236e-06 | 3.71639e-06 | 1(Win) | true |
| simdjson (ondemand) | 2260.2 | 0.0202373 | 5052.63ms | 94370 | 4890 | 317532 | 39818.6 | 0.0238358 | 2.23866 | 10.4779 | 1.78424 | 0.00481171 | 7.38727e-06 | 4.03494e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1257.84 | 0.0494201 | 1656.6ms | 11812 | 4890 | 95788.6 | 8955.68 | 0.0713403 | 4.03722 | 17.9681 | 3.27481 | 0.00542246 | 4.21221e-05 | 1.85593e-05 | 1(Win) | true |
| simdjson (ondemand) | 1051.47 | 0.0470348 | 1839.7ms | 11812 | 2560 | 65003.1 | 10713.4 | 0.257311 | 4.83366 | 18.9211 | 3.57205 | 0.00758742 | 3.22434e-05 | 9.85491e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1366.17 | 0.0666393 | 1636.46ms | 11812 | 2560 | 77292.5 | 8245.52 | 0.0459461 | 3.72531 | 16.944 | 3.0436 | 0.004554 | 5.86996e-05 | 2.89364e-05 | 1(Win) | true |
| simdjson (ondemand) | 1135.35 | 0.11128 | 1810.27ms | 11812 | 320 | 39010 | 9921.92 | 0.105117 | 4.4699 | 17.7348 | 3.30706 | 0.00583993 | 1.74611e-05 | 3.70386e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2948.81 | 0.0729431 | 1780.74ms | 31235 | 2560 | 138994 | 10101.7 | 0.208028 | 1.71896 | 7.78495 | 1.29373 | 0.00257898 | 1.17807e-05 | 3.88937e-06 | 1(Win) | true |
| simdjson (ondemand) | 2522.24 | 0.121844 | 1971.74ms | 31235 | 30 | 6212.12 | 11810.1 | 0.176935 | 2.0122 | 7.96104 | 1.38899 | 0.00375327 | 6.50979e-05 | 4.69559e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3190.67 | 0.0521204 | 1764.69ms | 31235 | 4890 | 115783 | 9335.97 | 0.216412 | 1.59234 | 7.39808 | 1.20653 | 0.00206344 | 1.1811e-05 | 3.83661e-06 | 1(Win) | true |
| simdjson (ondemand) | 2690.16 | 0.0333443 | 1932.94ms | 31235 | 4890 | 66662 | 11073 | 0.0461181 | 1.88428 | 7.58531 | 1.30443 | 0.00288073 | 1.21187e-05 | 4.47822e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 654.931 | 0.0719082 | 2483.76ms | 11812 | 1280 | 195805 | 17200 | 0.251921 | 7.7433 | 34.5082 | 7.59795 | 0.0185126 | 3.393e-05 | 1.18391e-05 | 1(Win) | true |
| simdjson (ondemand) | 621.215 | 0.0738329 | 2569.15ms | 11812 | 640 | 114721 | 18133.5 | 0.0405664 | 8.14931 | 35.9485 | 6.4244 | 0.0152852 | 3.65095e-05 | 1.42863e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 681.488 | 0.0803127 | 2462.88ms | 11812 | 1280 | 225585 | 16529.7 | 0.0342211 | 7.43344 | 33.4924 | 7.36878 | 0.0174822 | 2.04374e-05 | 3.24088e-06 | 1(Win) | true |
| simdjson (ondemand) | 642.663 | 0.0721168 | 2553.45ms | 11812 | 640 | 102266 | 17528.3 | 0.0876673 | 7.88051 | 34.8695 | 6.1827 | 0.0149653 | 2.87049e-05 | 1.00533e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1647.35 | 0.224323 | 2554.69ms | 31235 | 160 | 263256 | 18082.4 | 0.157708 | 3.06123 | 13.9915 | 2.90917 | 0.00701677 | 9.00432e-06 | 3.60173e-06 | 1(Win) | true |
| simdjson (ondemand) | 1591.5 | 0.0344306 | 2650.56ms | 31235 | 4890 | 203080 | 18716.9 | 0.297349 | 3.2151 | 14.279 | 2.43925 | 0.00577164 | 7.46371e-05 | 5.0655e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1718.88 | 0.0361918 | 2543.97ms | 31235 | 4890 | 192364 | 17329.9 | 0.136925 | 2.94832 | 13.5968 | 2.82011 | 0.00673691 | 1.67933e-05 | 7.11016e-06 | 1(Win) | true |
| simdjson (ondemand) | 1647.48 | 0.0405803 | 2648.66ms | 31235 | 2560 | 137821 | 18081 | 0.139877 | 3.08772 | 13.871 | 2.34785 | 0.0059819 | 2.93641e-05 | 1.71958e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2257.29 | 0.133542 | 1287.79ms | 11812 | 30 | 1332.39 | 4990.4 | 0.0728595 | 2.30132 | 11.0112 | 1.98705 | 0.00370809 | 1.69319e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2187.95 | 0.155491 | 1312.7ms | 11812 | 640 | 41017.1 | 5148.56 | 0.00555404 | 2.3679 | 10.4677 | 1.77853 | 0.00370915 | 3.28056e-05 | 1.82547e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2257.2 | 0.104245 | 1286.66ms | 11812 | 640 | 17321.8 | 4990.6 | 0.393119 | 2.27015 | 10.8195 | 1.94099 | 0.00400202 | 2.48688e-05 | 1.01856e-05 | 1(Win) | true |
| simdjson (ondemand) | 2221.6 | 0.0501016 | 1288.96ms | 11812 | 2560 | 16521.9 | 5070.59 | 0.0469609 | 2.30322 | 10.2759 | 1.73248 | 0.00373286 | 1.73618e-05 | 2.74483e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4971.42 | 0.0766552 | 1366.69ms | 31235 | 2560 | 54006.5 | 5991.85 | 0.132785 | 1.02637 | 5.08318 | 0.796639 | 0.00173743 | 6.36556e-06 | 1.20058e-06 | 1(Win) | true |
| simdjson (ondemand) | 4812.34 | 0.0355404 | 1400.01ms | 31235 | 4890 | 23665.9 | 6189.92 | 0.0506963 | 1.05984 | 4.75998 | 0.710421 | 0.00165687 | 1.09337e-05 | 3.65329e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5071.24 | 0.0991027 | 1366.77ms | 31235 | 1280 | 43374.6 | 5873.91 | 0.0271667 | 1.00956 | 5.01069 | 0.779222 | 0.00172073 | 9.15439e-06 | 2.97643e-06 | 1(Win) | true |
| simdjson (ondemand) | 4878.59 | 0.0844186 | 1405.48ms | 31235 | 1280 | 34008 | 6105.87 | 0.0299878 | 1.04529 | 4.68743 | 0.693005 | 0.00165074 | 4.00192e-06 | 4.25204e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1738.52 | 0.0764033 | 1436.07ms | 11812 | 2560 | 62740.8 | 6479.52 | 0.0549688 | 2.93332 | 14.7591 | 2.70665 | 0.00678795 | 2.65884e-05 | 1.23352e-05 | 1(Win) | true |
| simdjson (ondemand) | 1667.04 | 0.0466913 | 1459.81ms | 11812 | 2560 | 25483.9 | 6757.35 | 0.48919 | 3.08434 | 13.942 | 2.36683 | 0.00675379 | 1.63367e-05 | 4.89439e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1771.27 | 0.0813975 | 1451.84ms | 11812 | 2560 | 68602.4 | 6359.72 | 0.428702 | 2.88881 | 14.5674 | 2.6606 | 0.00677995 | 4.26605e-05 | 2.1694e-05 | 1(Win) | true |
| simdjson (ondemand) | 1690.84 | 0.168035 | 1473.77ms | 11812 | 80 | 10026.1 | 6662.26 | 0.0997277 | 3.006 | 13.7518 | 2.32078 | 0.00645001 | 3.80969e-05 | 1.37572e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3999.99 | 0.295775 | 1513.7ms | 31235 | 320 | 155253 | 7447.03 | 0.224793 | 1.27541 | 6.5005 | 1.06877 | 0.00289449 | 2.65127e-05 | 1.69081e-05 | 1(Win) | true |
| simdjson (ondemand) | 3912.31 | 0.135995 | 1547.46ms | 31235 | 320 | 34309.3 | 7613.91 | 0.17548 | 1.32186 | 6.07383 | 0.932896 | 0.00272841 | 9.80471e-06 | 4.60221e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4110.28 | 0.0841575 | 1511.91ms | 31235 | 2560 | 95228.2 | 7247.2 | 0.0136709 | 1.24793 | 6.42802 | 1.05135 | 0.00272986 | 1.49947e-05 | 7.291e-06 | 1(Win) | true |
| simdjson (ondemand) | 3894.69 | 0.037713 | 1551.33ms | 31235 | 4890 | 40684.5 | 7648.36 | 0.0235125 | 1.3078 | 6.00189 | 0.91548 | 0.00275208 | 9.04811e-06 | 2.74979e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1581.06 | 0.0256416 | 7333.71ms | 108313 | 2560 | 718445 | 65332.9 | 0.00435409 | 3.19788 | 14.4913 | 2.66637 | 0.00377302 | 6.17712e-05 | 5.20627e-05 | 1(Win) | true |
| simdjson (ondemand) | 1473.2 | 0.0514644 | 7820.26ms | 108313 | 1280 | 1.66672e+06 | 70116.4 | 0.0852375 | 3.42992 | 15.0292 | 2.5307 | 0.00749836 | 1.72172e-05 | 1.05741e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1727.83 | 0.0459074 | 6980.36ms | 108313 | 1280 | 964123 | 59783.1 | 0.123333 | 2.9339 | 13.7598 | 2.50079 | 0.00347268 | 1.76355e-05 | 1.19085e-05 | 1(Win) | true |
| simdjson (ondemand) | 1591.63 | 0.0297832 | 7469.47ms | 108313 | 2560 | 956447 | 64899.3 | 0.0256774 | 3.17002 | 14.3009 | 2.36518 | 0.00690997 | 7.76107e-06 | 4.21954e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2837.85 | 0.062947 | 4073.47ms | 213963 | 1280 | 2.62216e+06 | 71903.4 | 0.0107674 | 1.77575 | 8.19209 | 1.40487 | 0.00198188 | 7.65319e-06 | 4.96216e-06 | 1(Win) | true |
| simdjson (ondemand) | 2714.4 | 0.0365969 | 4240.12ms | 213963 | 1280 | 968785 | 75173.5 | 0.0186198 | 1.86158 | 8.23363 | 1.30878 | 0.00372892 | 1.7468e-05 | 1.25679e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3066.23 | 0.0282583 | 7640.96ms | 213963 | 4890 | 1.72928e+06 | 66547.7 | 0.192476 | 1.64781 | 7.82395 | 1.3216 | 0.00178188 | 1.86891e-05 | 1.49473e-05 | 1(Win) | true |
| simdjson (ondemand) | 2925.67 | 0.0352335 | 4068.34ms | 213963 | 2560 | 1.54589e+06 | 69745 | 0.0491456 | 1.72615 | 7.86839 | 1.22586 | 0.00355231 | 7.05803e-06 | 4.78142e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 441.496 | 0.0335258 | 6163.26ms | 108313 | 1280 | 7.87545e+06 | 233967 | 0.0110224 | 11.4026 | 52.3172 | 10.9975 | 0.0197121 | 0.000120693 | 9.1748e-05 | 1(Win) | true |
| simdjson (ondemand) | 196.311 | 0.0401944 | 6794ms | 108313 | 640 | 2.86273e+07 | 526181 | 0.19809 | 25.6839 | 117.472 | 23.1976 | 0.075753 | 0.000101875 | 7.61104e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 456.567 | 0.121124 | 6029.04ms | 108313 | 40 | 3.00381e+06 | 226244 | 0.171603 | 11.0699 | 51.5935 | 10.8342 | 0.0187953 | 0.00014495 | 0.000129717 | 1(Win) | true |
| simdjson (ondemand) | 199.042 | 0.0830909 | 6752.35ms | 108313 | 160 | 2.97508e+07 | 518963 | 0.206005 | 25.4862 | 116.754 | 23.035 | 0.0748527 | 0.000249451 | 0.000213329 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 838.588 | 0.0616253 | 6404.88ms | 213963 | 320 | 7.19528e+06 | 243327 | 0.106277 | 6.01489 | 27.292 | 5.60613 | 0.0108402 | 0.000143103 | 3.69807e-05 | 1(Win) | true |
| simdjson (ondemand) | 392.59 | 0.132794 | 6711.94ms | 213963 | 80 | 3.81106e+07 | 519756 | 0.0116823 | 12.8437 | 59.4164 | 11.6176 | 0.034291 | 0.000200268 | 7.5714e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 866.684 | 0.0567415 | 6259ms | 213963 | 320 | 5.71093e+06 | 235439 | 0.00477323 | 5.82306 | 26.9205 | 5.52236 | 0.0103749 | 7.17852e-05 | 3.07588e-05 | 1(Win) | true |
| simdjson (ondemand) | 396.522 | 0.121264 | 6660.97ms | 213963 | 320 | 1.24612e+08 | 514602 | 0.0354232 | 12.7219 | 59.0458 | 11.5338 | 0.0343833 | 0.000212887 | 0.00013748 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4108.9 | 0.0318751 | 3273.69ms | 108313 | 4890 | 313996 | 25139.4 | 0.0274988 | 1.23107 | 6.76363 | 0.886034 | 0.000883365 | 4.98064e-06 | 2.36005e-06 | 1(Win) | true |
| simdjson (ondemand) | 3992.45 | 0.0316084 | 3356.18ms | 108313 | 4890 | 327038 | 25872.7 | 0.0256519 | 1.26638 | 6.30197 | 0.849307 | 0.00174672 | 6.20031e-06 | 3.22099e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4314.9 | 0.13228 | 3171.96ms | 108313 | 160 | 160446 | 23939.2 | 0.0122983 | 1.17299 | 6.58229 | 0.837573 | 0.000681763 | 3.17367e-06 | 1.61569e-06 | 1(Win) | true |
| simdjson (ondemand) | 4182.26 | 0.0232012 | 3240.51ms | 108313 | 4890 | 160572 | 24698.4 | 0.0291102 | 1.20991 | 6.1214 | 0.80092 | 0.00167037 | 6.661e-06 | 3.98753e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6855.16 | 0.0273051 | 3739.94ms | 213963 | 4890 | 323027 | 29766 | 0.0230035 | 0.736753 | 4.12479 | 0.475363 | 0.000472804 | 7.0182e-06 | 4.95661e-06 | 1(Win) | true |
| simdjson (ondemand) | 6598.33 | 0.0484339 | 3862.6ms | 213963 | 1280 | 287157 | 30924.7 | 0.0258601 | 0.766307 | 3.81 | 0.456439 | 0.00107367 | 1.09796e-05 | 8.31043e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7118.59 | 0.0304417 | 3638.29ms | 213963 | 4890 | 372338 | 28664.5 | 0.0269145 | 0.707124 | 4.033 | 0.45083 | 0.000366277 | 7.72547e-06 | 5.91716e-06 | 1(Win) | true |
| simdjson (ondemand) | 6840.23 | 0.0341825 | 3764.1ms | 213963 | 4890 | 508456 | 29831 | 0.0579637 | 0.737193 | 3.71844 | 0.431907 | 0.00104917 | 6.10736e-06 | 4.51887e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2400.48 | 0.031122 | 5079.39ms | 108313 | 4890 | 877020 | 43031.2 | 0.0621056 | 2.09879 | 11.3759 | 2.17583 | 0.00274653 | 1.63164e-05 | 1.24271e-05 | 1(Win) | true |
| simdjson (ondemand) | 2096.34 | 0.0476681 | 5695.07ms | 108313 | 4890 | 2.69776e+06 | 49274.2 | 0.164343 | 2.39761 | 11.6295 | 1.82429 | 0.00446166 | 1.98999e-05 | 1.27084e-05 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2442.12 | 0.287522 | 4991.66ms | 108313 | 320 | 4.73281e+06 | 42297.5 | 0.0838667 | 2.05634 | 11.1932 | 2.12739 | 0.00259468 | 2.57356e-05 | 2.23888e-05 | 1(Win) | true |
| simdjson (ondemand) | 2144.61 | 0.0351909 | 5604.73ms | 108313 | 2560 | 735466 | 48165 | 0.250116 | 2.34437 | 11.4472 | 1.77584 | 0.00431288 | 9.41282e-06 | 5.99752e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4280.64 | 0.0546137 | 5552.58ms | 213963 | 1280 | 867506 | 47668.3 | 0.119102 | 1.17843 | 6.45608 | 1.12708 | 0.00150575 | 6.49937e-06 | 4.36699e-06 | 1(Win) | true |
| simdjson (ondemand) | 3773.32 | 0.15924 | 6232.51ms | 213963 | 80 | 593234 | 54077.3 | 0.0479176 | 1.33989 | 6.49626 | 0.947524 | 0.00231284 | 5.02423e-06 | 2.68738e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4368.59 | 0.0564832 | 5466.72ms | 213963 | 1280 | 890928 | 46708.6 | 0.0779093 | 1.15068 | 6.36361 | 1.10259 | 0.00141257 | 7.11645e-06 | 4.922e-06 | 1(Win) | true |
| simdjson (ondemand) | 3812.47 | 0.0328938 | 6155.86ms | 213963 | 2560 | 793474 | 53522 | 0.0327583 | 1.31307 | 6.40402 | 0.923029 | 0.00218821 | 2.38688e-05 | 2.09404e-05 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 593.169 | 0.0834833 | 4494.29ms | 1834197 | 80 | 4.84869e+08 | 2.94895e+06 | 1.41104 | 8.35822 | 36.5783 | 7.20697 | 0.0386024 | 0.141028 | 0.0129786 | 1(Win) | true |
| simdjson (ondemand) | 568.056 | 0.140107 | 4653.74ms | 1834197 | 40 | 7.44544e+08 | 3.07932e+06 | 0.56674 | 8.74446 | 35.9144 | 6.36338 | 0.0443901 | 0.139995 | 0.0222504 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 642.168 | 0.194188 | 4448.03ms | 1834197 | 30 | 8.39385e+08 | 2.72394e+06 | 0.628522 | 7.77919 | 33.5868 | 6.50781 | 0.0375485 | 0.120317 | 0.0240711 | 1(Win) | true |
| simdjson (ondemand) | 621.997 | 0.13027 | 4597.32ms | 1834197 | 40 | 5.36867e+08 | 2.81227e+06 | 0.0768896 | 7.99938 | 32.9233 | 5.66414 | 0.0432681 | 0.119044 | 0.00777855 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2750.13 | 0.11468 | 5177.56ms | 9930848 | 80 | 1.24777e+09 | 3.44376e+06 | 0.154154 | 1.80046 | 7.77456 | 1.37355 | 0.00750811 | 0.0521963 | 0.0107626 | 1(Win) | true |
| simdjson (ondemand) | 2705.89 | 0.161893 | 5304.75ms | 9930848 | 80 | 2.56862e+09 | 3.50007e+06 | 0.1862 | 1.8533 | 7.67465 | 1.2213 | 0.00773716 | 0.0518927 | 0.00625317 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3031.55 | 0.124516 | 5113.1ms | 9930848 | 40 | 6.05278e+08 | 3.12408e+06 | 0.289241 | 1.64801 | 7.22223 | 1.24447 | 0.00727338 | 0.0483239 | 0.00367001 | 1(Win) | true |
| simdjson (ondemand) | 2910.79 | 0.193235 | 5284.7ms | 9930848 | 30 | 1.18589e+09 | 3.25368e+06 | 0.069475 | 1.71958 | 7.12225 | 1.09218 | 0.00755695 | 0.0480035 | 0.00469133 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 260.733 | 0.153813 | 4712.21ms | 1834197 | 30 | 3.19453e+09 | 6.70889e+06 | 0.0994004 | 19.2328 | 95.2556 | 22.0531 | 0.0434971 | 0.53776 | 0.00973327 | 1(Win) | true |
| simdjson (ondemand) | 190.226 | 0.119141 | 6429.22ms | 1834197 | 40 | 4.801e+09 | 9.19551e+06 | 0.345489 | 26.2033 | 131.404 | 22.762 | 0.0523523 | 0.791579 | 0.036951 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 270.274 | 0.187267 | 4735.04ms | 1834197 | 30 | 4.40682e+09 | 6.47204e+06 | 0.309808 | 18.6391 | 92.2661 | 21.3547 | 0.0423734 | 0.516502 | 0.00545176 | 1(Win) | true |
| simdjson (ondemand) | 195.888 | 0.174798 | 6432.83ms | 1834197 | 30 | 7.30916e+09 | 8.92972e+06 | 0.245095 | 25.4135 | 128.414 | 22.0633 | 0.0511033 | 0.769494 | 0.025127 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1201.55 | 0.388753 | 5582.61ms | 9930848 | 40 | 3.75577e+10 | 7.88218e+06 | 0.627036 | 4.16921 | 18.6123 | 4.11565 | 0.00829939 | 0.280785 | 0.0123903 | 1(Win) | true |
| simdjson (ondemand) | 923.653 | 0.302107 | 7199.43ms | 9930848 | 30 | 2.87871e+10 | 1.02536e+07 | 0.870742 | 5.4187 | 25.3112 | 4.25006 | 0.00923616 | 0.409101 | 0.0133929 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1237.69 | 0.398887 | 5541.88ms | 9930848 | 30 | 2.79491e+10 | 7.65198e+06 | 0.454605 | 4.02897 | 18.0597 | 3.98644 | 0.00808137 | 0.276827 | 0.0105261 | 1(Win) | true |
| simdjson (ondemand) | 928.905 | 0.272161 | 7320.65ms | 9930848 | 30 | 2.30995e+10 | 1.01957e+07 | 0.241791 | 5.40204 | 24.7588 | 4.121 | 0.00902909 | 0.405216 | 0.0138246 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3924.41 | 0.262798 | 5810.67ms | 1834197 | 160 | 2.19537e+08 | 445730 | 0.0364633 | 1.28105 | 6.4428 | 1.20929 | 0.00158743 | 0.0754798 | 8.13367e-06 | 1(Win) | true |
| simdjson (ondemand) | 3105.31 | 0.33669 | 7242.68ms | 1834197 | 320 | 1.15104e+09 | 563301 | 0.749197 | 1.61715 | 7.63588 | 0.930037 | 0.00345306 | 0.0754433 | 8.16263e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3919.72 | 0.117395 | 5807.81ms | 1834197 | 640 | 1.75654e+08 | 446263 | 0.206966 | 1.28249 | 6.44259 | 1.20924 | 0.00161729 | 0.0754412 | 5.31397e-06 | 1(Win) | true |
| simdjson (ondemand) | 3139.36 | 0.0871617 | 7199.14ms | 1834197 | 320 | 7.54762e+07 | 557192 | 0.14727 | 1.59792 | 7.63568 | 0.92999 | 0.0034299 | 0.0754298 | 1.22346e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11144.3 | 0.241546 | 5421.66ms | 9930848 | 320 | 1.3484e+09 | 849835 | 0.106384 | 0.44531 | 2.1723 | 0.259132 | 0.000664053 | 0.0395135 | 8.6321e-05 | 1(Win) | true |
| simdjson (ondemand) | 9558.79 | 0.240876 | 6376ms | 9930848 | 40 | 2.27831e+08 | 990794 | 0.178365 | 0.527626 | 2.45184 | 0.217843 | 0.000714048 | 0.0395446 | 0.000159203 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11244.1 | 0.308044 | 5384.35ms | 9930848 | 80 | 5.38565e+08 | 842289 | 1.12246 | 0.440668 | 2.17226 | 0.259124 | 0.000656113 | 0.0395058 | 8.54232e-05 | 1(Win) | true |
| simdjson (ondemand) | 9302.32 | 0.423117 | 6506.27ms | 9930848 | 40 | 7.42287e+08 | 1.01811e+06 | 0.0933277 | 0.535061 | 2.4518 | 0.217834 | 0.00072126 | 0.0395356 | 0.000260534 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1844.12 | 0.480782 | 6039.5ms | 1834197 | 80 | 1.6638e+09 | 948544 | 0.238228 | 2.71845 | 13.5377 | 3.35419 | 0.00229676 | 0.150716 | 2.54607e-05 | 1(Win) | true |
| simdjson (ondemand) | 1565.16 | 0.141534 | 7113.7ms | 1834197 | 320 | 8.00654e+08 | 1.1176e+06 | 0.271386 | 3.20359 | 16.6097 | 2.47757 | 0.00421949 | 0.150626 | 6.13058e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1857.34 | 0.136039 | 5961.31ms | 1834197 | 320 | 5.2528e+08 | 941794 | 0.0357219 | 2.68769 | 13.5375 | 3.35414 | 0.00222608 | 0.150635 | 1.93562e-05 | 1(Win) | true |
| simdjson (ondemand) | 1571.12 | 0.21216 | 7085.59ms | 1834197 | 80 | 4.46364e+08 | 1.11336e+06 | 0.105897 | 3.1794 | 16.6095 | 2.47753 | 0.00421918 | 0.150535 | 3.69576e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6932.95 | 0.637481 | 4278.31ms | 9930848 | 30 | 2.27506e+09 | 1.36606e+06 | 0.0231099 | 0.722576 | 3.4827 | 0.655288 | 0.000740209 | 0.0789752 | 0.000187527 | 1(Win) | true |
| simdjson (ondemand) | 5691.81 | 0.388392 | 5222.23ms | 9930848 | 160 | 6.6824e+09 | 1.66393e+06 | 0.220322 | 0.878249 | 4.10927 | 0.503668 | 0.000793153 | 0.0790441 | 0.000812517 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6669.64 | 0.733019 | 4436.09ms | 9930848 | 30 | 3.25028e+09 | 1.41999e+06 | 0.145772 | 0.745677 | 3.48266 | 0.655279 | 0.000737517 | 0.0789662 | 0.000706009 | 1(Win) | true |
| simdjson (ondemand) | 5774.56 | 0.283192 | 5180.27ms | 9930848 | 160 | 3.45157e+09 | 1.64009e+06 | 0.43322 | 0.868222 | 4.10923 | 0.503659 | 0.000788746 | 0.0790211 | 0.000589863 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1159.41 | 0.133555 | 6852.66ms | 642697 | 640 | 3.19034e+08 | 528649 | 0.442527 | 4.28784 | 22.4296 | 3.99121 | 0.0115998 | 0.0590539 | 0.000145101 | 1(Win) | true |
| simdjson (ondemand) | 1144.04 | 0.219974 | 6948.48ms | 642697 | 40 | 5.55566e+07 | 535756 | 0.196006 | 4.35569 | 21.7403 | 3.44063 | 0.0111097 | 0.0582664 | 0.000138868 | 2(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1284.45 | 0.134471 | 6526.19ms | 642697 | 640 | 2.63522e+08 | 477187 | 0.0456233 | 3.86435 | 21.2104 | 3.71211 | 0.0106279 | 0.0206499 | 0.000192018 | 1(Win) | true |
| simdjson (ondemand) | 1268.52 | 0.128347 | 6575.43ms | 642697 | 80 | 3.07667e+07 | 483181 | 0.0307709 | 3.93006 | 20.5212 | 3.16182 | 0.00995557 | 0.0203292 | 0.000225495 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2132.39 | 0.115686 | 7142.36ms | 1225964 | 640 | 2.57491e+08 | 548292 | 0.60211 | 2.35148 | 12.5432 | 2.13473 | 0.00477691 | 0.0577493 | 9.3517e-05 | 1(Win) | true |
| simdjson (ondemand) | 2102.37 | 0.122049 | 7186.52ms | 1225964 | 640 | 2.94841e+08 | 556121 | 0.263468 | 2.3626 | 12.034 | 1.82659 | 0.00440542 | 0.0575908 | 9.22386e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2359.47 | 0.290858 | 6787.69ms | 1225964 | 160 | 3.3236e+08 | 495522 | 0.434814 | 2.13444 | 11.9039 | 1.98856 | 0.00454134 | 0.0376104 | 5.26473e-05 | 1(Win) | true |
| simdjson (ondemand) | 2323.5 | 0.0483161 | 6838.06ms | 1225964 | 320 | 1.89148e+07 | 503193 | 0.770294 | 2.14056 | 11.3945 | 1.68052 | 0.00388915 | 0.0400814 | 4.07868e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 940.123 | 0.270288 | 4144.68ms | 642697 | 320 | 9.93683e+08 | 651961 | 0.672157 | 5.31736 | 28.9194 | 5.94408 | 0.0117257 | 0.0537741 | 0.000189781 | 1(Win) | true |
| simdjson (ondemand) | 712.957 | 0.101281 | 5506.45ms | 642697 | 160 | 1.21299e+08 | 859692 | 0.0327456 | 6.99939 | 39.3199 | 6.40438 | 0.011237 | 0.0519274 | 0.000353637 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1037.02 | 0.364426 | 7942.53ms | 642697 | 30 | 1.3918e+08 | 591041 | 0.0230889 | 4.82809 | 27.7022 | 5.66586 | 0.0103614 | 0.0180776 | 0.000198953 | 1(Win) | true |
| simdjson (ondemand) | 754.674 | 0.157771 | 5318.06ms | 642697 | 30 | 4.92573e+07 | 812170 | 0.18482 | 6.58832 | 38.1011 | 6.12598 | 0.00988491 | 0.0160039 | 0.000231836 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1743.91 | 0.111523 | 4285.9ms | 1225964 | 320 | 1.78892e+08 | 670431 | 0.0368919 | 2.86414 | 15.9455 | 3.15859 | 0.00488316 | 0.0743738 | 0.000110135 | 1(Win) | true |
| simdjson (ondemand) | 1327.2 | 0.169142 | 5602.17ms | 1225964 | 40 | 8.88068e+07 | 880928 | 0.364533 | 3.75696 | 21.249 | 3.38021 | 0.00444287 | 0.113384 | 6.13599e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1908.66 | 0.168625 | 4151.99ms | 1225964 | 40 | 4.26777e+07 | 612560 | 0.148052 | 2.63002 | 15.3065 | 3.01265 | 0.00445804 | 0.0454974 | 4.49442e-05 | 1(Win) | true |
| simdjson (ondemand) | 1422.48 | 0.0689501 | 5401.58ms | 1225964 | 160 | 5.13872e+07 | 821926 | 0.00924268 | 3.54536 | 20.6097 | 3.23423 | 0.00407552 | 0.0822708 | 9.59245e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3032.32 | 0.122873 | 5397.22ms | 642697 | 640 | 3.94778e+07 | 202130 | 0.0789213 | 1.64801 | 9.69961 | 1.61497 | 0.000110688 | 0.01861 | 1.87345e-05 | 1(Win) | true |
| simdjson (ondemand) | 2787.4 | 0.115012 | 5828.87ms | 642697 | 640 | 4.09333e+07 | 219891 | 0.0168621 | 1.79477 | 10.2379 | 1.38547 | 0.000143069 | 0.0153772 | 1.74752e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3217.12 | 0.102056 | 5062.36ms | 642697 | 320 | 1.20979e+07 | 190519 | 0.135465 | 1.55779 | 9.68869 | 1.61257 | 9.147e-05 | 0.00309505 | 1.37069e-05 | 1(Win) | true |
| simdjson (ondemand) | 2913.2 | 0.0341006 | 5601.62ms | 642697 | 1280 | 6.58879e+06 | 210395 | 0.0132971 | 1.72068 | 10.227 | 1.38306 | 0.000219778 | 0.000576015 | 3.4232e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5072.31 | 0.17047 | 6105.13ms | 1225964 | 160 | 2.47037e+07 | 230501 | 0.00794945 | 0.985883 | 5.76606 | 0.868384 | 4.45823e-05 | 0.0294611 | 1.83988e-05 | 1(Win) | true |
| simdjson (ondemand) | 4710.65 | 0.137118 | 6561.07ms | 1225964 | 160 | 1.85311e+07 | 248197 | 0.224923 | 1.06581 | 6.00278 | 0.749044 | 4.19925e-05 | 0.0312029 | 7.71842e-06 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5367.7 | 0.0816557 | 5780.99ms | 1225964 | 1280 | 4.04913e+07 | 217816 | 0.0824905 | 0.940205 | 5.76021 | 0.867092 | 3.82951e-05 | 0.0161069 | 1.41681e-05 | 1(Win) | true |
| simdjson (ondemand) | 4938.65 | 0.0860411 | 6314.73ms | 1225964 | 160 | 6.63852e+06 | 236739 | 0.126891 | 1.02063 | 5.99694 | 0.747747 | 3.50082e-05 | 0.0201369 | 6.67332e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2996.9 | 0.286605 | 5378.42ms | 642697 | 30 | 1.03076e+07 | 204519 | 0.0660685 | 1.64999 | 9.7008 | 1.61529 | 0.000321821 | 0.0187908 | 9.95804e-06 | 1(Win) | true |
| simdjson (ondemand) | 2843 | 0.0662559 | 5727.43ms | 642697 | 1280 | 2.61166e+07 | 215590 | 0.498694 | 1.76496 | 10.2392 | 1.38569 | 0.000144913 | 0.0156429 | 1.42612e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3228.27 | 0.0987659 | 5081.92ms | 642697 | 160 | 5.62608e+06 | 189861 | 0.0565192 | 1.55729 | 9.68988 | 1.61289 | 9.6449e-05 | 0.00335749 | 2.08399e-05 | 1(Win) | true |
| simdjson (ondemand) | 2974.97 | 0.033113 | 5450.47ms | 642697 | 1280 | 5.95736e+06 | 206027 | 0.0985863 | 1.69055 | 10.2283 | 1.38329 | 0.000100281 | 0.000792467 | 3.42952e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5067.93 | 0.073251 | 6091.02ms | 1225964 | 1280 | 3.65537e+07 | 230700 | 0.00893387 | 0.98824 | 5.76669 | 0.868555 | 4.51278e-05 | 0.0294697 | 1.32345e-05 | 1(Win) | true |
| simdjson (ondemand) | 4776.1 | 0.16653 | 6476.78ms | 1225964 | 640 | 1.06359e+08 | 244796 | 0.0138515 | 1.0562 | 6.00345 | 0.749158 | 4.13616e-05 | 0.031114 | 2.82813e-06 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5308.07 | 0.399489 | 5802.64ms | 1225964 | 640 | 4.95531e+08 | 220263 | 0.317339 | 0.951726 | 5.76083 | 0.867263 | 3.84646e-05 | 0.0159271 | 1.38501e-05 | 1(Win) | true |
| simdjson (ondemand) | 4997.69 | 0.0883128 | 6181.86ms | 1225964 | 640 | 2.73178e+07 | 233942 | 0.112246 | 1.00941 | 5.99761 | 0.747861 | 3.60354e-05 | 0.0199282 | 4.09499e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1232 | 0.0760014 | 4144.47ms | 409725 | 640 | 3.71865e+07 | 317162 | 0.0149645 | 4.09559 | 18.1814 | 3.45168 | 0.010076 | 0.0314503 | 2.54363e-05 | 1(Win) | true |
| simdjson (ondemand) | 983.237 | 0.0757109 | 5164.27ms | 409725 | 320 | 2.89692e+07 | 397406 | 0.0889505 | 5.12562 | 19.5238 | 3.73918 | 0.0188927 | 0.0398022 | 3.20947e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1549.84 | 0.147139 | 7819.84ms | 409725 | 80 | 1.10093e+07 | 252120 | 0.0880069 | 3.25423 | 15.1983 | 2.78422 | 0.00666831 | 0.0113227 | 5.64403e-05 | 1(Win) | true |
| simdjson (ondemand) | 1169.71 | 0.243575 | 4901.14ms | 409725 | 80 | 5.29645e+07 | 334053 | 0.178153 | 4.27604 | 16.5466 | 3.07289 | 0.0146577 | 0.0198073 | 4.45116e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2207.42 | 0.0961976 | 4460.65ms | 785750 | 30 | 3.19925e+06 | 339468 | 0.0891286 | 2.28808 | 10.1683 | 1.82774 | 0.00648629 | 0.0299377 | 2.65139e-05 | 1(Win) | true |
| simdjson (ondemand) | 1747.4 | 0.159359 | 5576.08ms | 785750 | 640 | 2.98894e+08 | 428837 | 0.0967533 | 2.8692 | 10.7897 | 1.97905 | 0.0111262 | 0.0398121 | 2.75752e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2706.84 | 0.221241 | 4201.83ms | 785750 | 320 | 1.20039e+08 | 276835 | 0.168745 | 1.84977 | 8.60838 | 1.47877 | 0.00423683 | 0.0163736 | 1.17642e-05 | 1(Win) | true |
| simdjson (ondemand) | 2085.45 | 0.0894095 | 5263.79ms | 785750 | 640 | 6.60568e+07 | 359323 | 0.106407 | 2.3983 | 9.23608 | 1.63145 | 0.00888774 | 0.0253139 | 1.62285e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 437.906 | 0.101196 | 5662.79ms | 409725 | 320 | 2.60918e+08 | 892301 | 0.347009 | 11.4218 | 41.0868 | 8.54199 | 0.071003 | 0.0809567 | 0.000250633 | 1(Win) | true |
| simdjson (ondemand) | 409.947 | 0.129427 | 6137.64ms | 409725 | 40 | 6.08746e+07 | 953157 | 0.129805 | 12.244 | 56.1655 | 10.7158 | 0.0240697 | 0.0463746 | 0.000124962 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 471.643 | 0.164067 | 5553.39ms | 409725 | 320 | 5.9122e+08 | 828474 | 0.168748 | 10.6027 | 38.1185 | 7.87804 | 0.0662047 | 0.0385304 | 0.000111111 | 1(Win) | true |
| simdjson (ondemand) | 440.113 | 0.0458733 | 5968.7ms | 409725 | 320 | 5.30796e+07 | 887827 | 0.472402 | 11.4342 | 53.2002 | 10.0526 | 0.020143 | 0.0210729 | 0.000118959 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 835.658 | 0.110272 | 5773.08ms | 785750 | 30 | 2.93336e+07 | 896718 | 0.157382 | 6.04457 | 22.0926 | 4.47437 | 0.0357769 | 0.0670528 | 4.07254e-05 | 1(Win) | true |
| simdjson (ondemand) | 764.72 | 0.326501 | 6191.74ms | 785750 | 80 | 8.18883e+08 | 979900 | 0.0926053 | 6.58199 | 29.7927 | 5.59448 | 0.0136342 | 0.0471297 | 0.000184298 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 895.383 | 0.155953 | 5652.6ms | 785750 | 320 | 5.45117e+08 | 836904 | 0.0942898 | 5.61689 | 20.5438 | 4.12795 | 0.0334383 | 0.0415359 | 7.39898e-05 | 1(Win) | true |
| simdjson (ondemand) | 827.63 | 0.180006 | 6072.04ms | 785750 | 160 | 4.25e+08 | 905416 | 0.100109 | 6.10269 | 28.2471 | 5.24885 | 0.0109875 | 0.0262025 | 0.000140185 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2208.2 | 0.161157 | 4721.09ms | 409725 | 320 | 2.6023e+07 | 176952 | 0.132748 | 2.28555 | 10.6208 | 1.90442 | 0.00672642 | 0.00168907 | 6.48758e-05 | 1(Win) | true |
| simdjson (ondemand) | 1953.45 | 0.0481227 | 5302.95ms | 409725 | 320 | 2.96504e+06 | 200028 | 0.0315669 | 2.5797 | 10.2318 | 1.79911 | 0.010024 | 0.00275824 | 4.57166e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2543.56 | 0.0681832 | 4597.28ms | 409725 | 640 | 7.02158e+06 | 153621 | 0.0204238 | 1.96989 | 9.59641 | 1.67102 | 0.0048538 | 0.000488853 | 3.85853e-05 | 1(Win) | true |
| simdjson (ondemand) | 2261.1 | 0.0559886 | 5075ms | 409725 | 320 | 2.99567e+06 | 172811 | 0.0297635 | 2.23506 | 9.21648 | 1.56465 | 0.00749127 | 0.00130849 | 6.27936e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3820.22 | 0.0385885 | 5215.51ms | 785750 | 640 | 3.66679e+06 | 196153 | 0.188598 | 1.3206 | 6.2146 | 1.01717 | 0.0042842 | 0.00466425 | 5.06801e-05 | 1(Win) | true |
| simdjson (ondemand) | 3372.2 | 0.21057 | 5880.7ms | 785750 | 80 | 1.75155e+07 | 222214 | 0.200905 | 1.49473 | 5.92245 | 0.964514 | 0.00582178 | 0.00652879 | 4.16322e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4368.89 | 0.117193 | 5112ms | 785750 | 80 | 3.23234e+06 | 171520 | 0.0720317 | 1.15754 | 5.68214 | 0.895772 | 0.00327534 | 0.00352526 | 1.37289e-05 | 1(Win) | true |
| simdjson (ondemand) | 3824.73 | 0.322215 | 5718.19ms | 785750 | 40 | 1.59411e+07 | 195922 | 0.0995688 | 1.32149 | 5.39322 | 0.842308 | 0.00463201 | 0.00551079 | 2.18581e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1530.96 | 0.0406792 | 6699.05ms | 409725 | 640 | 6.89889e+06 | 255228 | 0.012797 | 3.29587 | 16.2786 | 3.04207 | 0.00981309 | 0.000747765 | 5.26344e-05 | 1(Win) | true |
| simdjson (ondemand) | 1375.29 | 0.160364 | 7426.89ms | 409725 | 320 | 6.64294e+07 | 284117 | 0.216809 | 3.64024 | 15.5906 | 2.77202 | 0.01023 | 0.000924942 | 2.79303e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1679.8 | 0.0383034 | 6627ms | 409725 | 1280 | 1.01615e+07 | 232614 | 0.0885943 | 2.99512 | 15.2553 | 2.80605 | 0.00843828 | 0.000234242 | 5.19613e-05 | 1(Win) | true |
| simdjson (ondemand) | 1490.84 | 0.226487 | 7373.16ms | 409725 | 30 | 1.05714e+07 | 262098 | 0.115142 | 3.35639 | 14.5723 | 2.53653 | 0.00948051 | 0.000472756 | 4.02709e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2653.98 | 0.0895116 | 7391.85ms | 785750 | 1280 | 8.17604e+07 | 282350 | 0.183871 | 1.87093 | 9.16937 | 1.61186 | 0.00611355 | 0.00753625 | 2.41927e-05 | 1(Win) | true |
| simdjson (ondemand) | 2423.94 | 0.0988569 | 4022.41ms | 785750 | 40 | 3.73593e+06 | 309145 | 0.188726 | 2.04747 | 8.72629 | 1.4731 | 0.006009 | 0.00814098 | 2.05536e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2914.66 | 0.06696 | 7266.33ms | 785750 | 1280 | 3.79345e+07 | 257097 | 0.0599767 | 1.69618 | 8.63577 | 1.4888 | 0.00502678 | 0.00598617 | 7.00266e-06 | 1(Win) | true |
| simdjson (ondemand) | 2644.46 | 0.105309 | 7988.33ms | 785750 | 640 | 5.69913e+07 | 283366 | 0.256371 | 1.88794 | 8.19478 | 1.35016 | 0.00490875 | 0.00690342 | 9.68223e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1817.82 | 0.0867309 | 7537.7ms | 264040 | 640 | 9.23772e+06 | 138522 | 0.0534636 | 2.77143 | 10.0001 | 1.78661 | 0.0104031 | 0.000222546 | 5.37738e-05 | 1(Win) | true |
| simdjson (ondemand) | 1638.59 | 0.14425 | 4121.14ms | 264040 | 320 | 1.57247e+07 | 153674 | 0.489013 | 3.04335 | 10.2136 | 1.76974 | 0.0141126 | 0.000859967 | 8.44569e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2384.68 | 0.0735051 | 6453.42ms | 264040 | 640 | 3.85562e+06 | 105594 | 0.0417663 | 2.10857 | 8.58757 | 1.46299 | 0.0032958 | 2.77243e-05 | 1.509e-05 | 1(Win) | true |
| simdjson (ondemand) | 1940.29 | 0.0870379 | 7783.9ms | 264040 | 2560 | 3.26634e+07 | 129778 | 0.236957 | 2.56465 | 8.80621 | 1.44873 | 0.0117907 | 0.000180536 | 7.67728e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2576.97 | 0.245442 | 7739.42ms | 399947 | 80 | 1.05578e+07 | 148010 | 0.00716114 | 1.95002 | 7.15832 | 1.20103 | 0.00675718 | 0.0010608 | 0.000112327 | 1(Win) | true |
| simdjson (ondemand) | 2471.27 | 0.209214 | 4216.67ms | 399947 | 1280 | 1.33462e+08 | 154342 | 0.431167 | 2.03451 | 7.19287 | 1.19007 | 0.0066781 | 0.00418073 | 2.70895e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3326.69 | 0.0421059 | 6914.09ms | 399947 | 2560 | 5.96632e+06 | 114654 | 0.115724 | 1.52003 | 6.22244 | 0.986959 | 0.00235693 | 5.71384e-05 | 1.94889e-05 | 1(Win) | true |
| simdjson (ondemand) | 2804.43 | 0.190013 | 4071.38ms | 399947 | 1280 | 8.54856e+07 | 136006 | 0.337794 | 1.79206 | 6.25819 | 0.976633 | 0.00780249 | 0.000435739 | 1.3158e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 630.986 | 0.121924 | 5185.71ms | 264040 | 640 | 1.51516e+08 | 399071 | 0.113704 | 7.98129 | 30.3078 | 5.88072 | 0.0231158 | 0.0153328 | 6.58814e-05 | 1(Win) | true |
| simdjson (ondemand) | 213.632 | 0.206995 | 7474.65ms | 264040 | 160 | 9.52466e+08 | 1.1787e+06 | 0.124155 | 23.3516 | 84.3403 | 17.0278 | 0.151397 | 0.00609846 | 0.000245086 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 678.226 | 0.120831 | 5024.54ms | 264040 | 640 | 1.28804e+08 | 371275 | 0.0100963 | 7.43339 | 28.8888 | 5.55563 | 0.019281 | 0.00529886 | 0.00016879 | 1(Win) | true |
| simdjson (ondemand) | 218.526 | 0.0983225 | 7373.44ms | 264040 | 320 | 4.10762e+08 | 1.15231e+06 | 0.376565 | 22.619 | 82.9262 | 16.7051 | 0.14311 | 0.000922138 | 5.40756e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 933.687 | 0.140341 | 5300.25ms | 399947 | 640 | 2.10353e+08 | 408509 | 0.0865077 | 5.32233 | 20.5468 | 3.89774 | 0.0132461 | 0.0125571 | 4.63811e-05 | 1(Win) | true |
| simdjson (ondemand) | 335.006 | 0.127203 | 7224.37ms | 399947 | 320 | 6.71194e+08 | 1.13855e+06 | 0.187411 | 14.8112 | 55.6269 | 11.1516 | 0.0827277 | 0.0069524 | 9.89037e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 996.536 | 0.157835 | 5160.09ms | 399947 | 320 | 1.16782e+08 | 382745 | 0.886947 | 4.98022 | 19.6114 | 3.68366 | 0.0116331 | 0.00403087 | 4.16149e-05 | 1(Win) | true |
| simdjson (ondemand) | 345.01 | 0.289805 | 7113.21ms | 399947 | 30 | 3.07946e+08 | 1.10553e+06 | 0.0118751 | 14.3316 | 54.6949 | 10.9392 | 0.077473 | 0.00225297 | 6.40085e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5830.31 | 0.0832042 | 5077.66ms | 264040 | 1280 | 1.65294e+06 | 43189.5 | 0.0377096 | 0.848687 | 4.29606 | 0.49207 | 0.00126077 | 3.3997e-06 | 1.48533e-06 | 1(Win) | true |
| simdjson (ondemand) | 5508.41 | 0.0308759 | 5343.61ms | 264040 | 4890 | 974168 | 45713.4 | 0.0744889 | 0.906117 | 4.16239 | 0.474101 | 0.000836789 | 2.18936e-05 | 1.73635e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5986.22 | 0.0489859 | 5028.43ms | 264040 | 4890 | 2.07628e+06 | 42064.6 | 0.00395215 | 0.82682 | 4.21192 | 0.473387 | 0.00124967 | 1.48472e-05 | 1.12868e-05 | 1(Win) | true |
| simdjson (ondemand) | 5633.63 | 0.0612543 | 5288.24ms | 264040 | 1280 | 959505 | 44697.4 | 0.139359 | 0.884141 | 4.07957 | 0.45541 | 0.000826656 | 2.04722e-05 | 1.58682e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7464.71 | 0.0702439 | 5860.21ms | 399947 | 1280 | 1.64895e+06 | 51096.3 | 0.473526 | 0.664511 | 3.38112 | 0.344241 | 0.000861913 | 7.90144e-06 | 4.35409e-06 | 1(Win) | true |
| simdjson (ondemand) | 7170.7 | 0.0579211 | 6056.96ms | 399947 | 1280 | 1.21497e+06 | 53191.4 | 0.00334718 | 0.692473 | 3.19497 | 0.334036 | 0.000558277 | 6.69425e-06 | 3.95756e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7670.99 | 0.0567101 | 5791.83ms | 399947 | 2560 | 2.03547e+06 | 49722.3 | 0.053245 | 0.649939 | 3.32557 | 0.331907 | 0.000845158 | 1.3157e-05 | 8.90743e-06 | 1(Win) | true |
| simdjson (ondemand) | 7400.96 | 0.0927772 | 5958.77ms | 399947 | 320 | 731579 | 51536.4 | 0.00551764 | 0.676043 | 3.14029 | 0.321697 | 0.000547705 | 4.28182e-06 | 2.1956e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3548.98 | 0.0778073 | 4012.51ms | 264040 | 2560 | 7.80214e+06 | 70952.3 | 0.200699 | 1.41566 | 7.4811 | 1.19224 | 0.00152394 | 2.14989e-05 | 1.59688e-05 | 1(Win) | true |
| simdjson (ondemand) | 3138.55 | 0.0823536 | 4497.54ms | 264040 | 2560 | 1.1176e+07 | 80230.8 | 0.100479 | 1.6005 | 7.37311 | 1.07091 | 0.00223842 | 1.21933e-05 | 8.53327e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3612.89 | 0.0637064 | 7791.33ms | 264040 | 4890 | 9.64063e+06 | 69697.2 | 0.0670669 | 1.39459 | 7.40158 | 1.17489 | 0.00145432 | 8.87887e-06 | 5.67166e-06 | 1(Win) | true |
| simdjson (ondemand) | 3189.87 | 0.117663 | 4455.81ms | 264040 | 2560 | 2.20858e+07 | 78939.9 | 0.0335836 | 1.57545 | 7.29456 | 1.05356 | 0.00219141 | 1.84557e-05 | 1.20424e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4849.59 | 0.172922 | 4425.73ms | 399947 | 640 | 1.18379e+07 | 78649.8 | 0.0141808 | 1.03399 | 5.4866 | 0.807482 | 0.000997945 | 1.11343e-05 | 7.23533e-06 | 1(Win) | true |
| simdjson (ondemand) | 4323.72 | 0.150864 | 4914.37ms | 399947 | 640 | 1.13355e+07 | 88215.4 | 0.151722 | 1.15197 | 5.32367 | 0.730123 | 0.00141555 | 2.47103e-05 | 1.83266e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4900.74 | 0.0603497 | 4407.1ms | 399947 | 2560 | 5.64771e+06 | 77828.9 | 0.141171 | 1.01675 | 5.43329 | 0.795843 | 0.000974316 | 2.08074e-05 | 1.65383e-05 | 1(Win) | true |
| simdjson (ondemand) | 4386.71 | 0.196369 | 4873.86ms | 399947 | 320 | 9.32872e+06 | 86948.8 | 0.0190234 | 1.13322 | 5.27182 | 0.718669 | 0.00136271 | 9.82943e-06 | 7.21971e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 717.683 | 0.102607 | 1372.51ms | 4630 | 4890 | 194877 | 6152.45 | 0.235611 | 7.04269 | 32.5406 | 6.173 | 0.00348479 | 0.000154147 | 7.52627e-05 | 1(Win) | true |
| simdjson (ondemand) | 666.505 | 0.319768 | 1416.15ms | 4630 | 80 | 35901.7 | 6624.88 | 0.115607 | 7.49629 | 31.4665 | 5.63845 | 0.0037041 | 0.00012149 | 7.5594e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 852.477 | 0.0737144 | 1367.91ms | 4630 | 4890 | 71287 | 5179.63 | 0.0411678 | 5.93068 | 28.0365 | 5.12808 | 0.00158944 | 0.000104944 | 4.18715e-05 | 1(Win) | true |
| simdjson (ondemand) | 787.273 | 0.0949365 | 1414.61ms | 4630 | 2560 | 72580.2 | 5608.62 | 0.0414364 | 6.37977 | 26.9102 | 4.58467 | 0.0020391 | 7.63533e-05 | 3.15537e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2158.97 | 0.0799131 | 1415.76ms | 14795 | 2560 | 69825.6 | 6535.36 | 0.0745242 | 2.34494 | 11.0422 | 1.96648 | 0.00087482 | 5.20921e-05 | 2.70098e-05 | 1(Win) | true |
| simdjson (ondemand) | 2023.32 | 0.127694 | 1461.94ms | 14795 | 640 | 50748.5 | 6973.49 | 0.118791 | 2.48681 | 10.5759 | 1.78155 | 0.0010448 | 1.6792e-05 | 5.17489e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2482.34 | 0.0777568 | 1417.92ms | 14795 | 4890 | 95519.8 | 5684 | 0.567847 | 2.02576 | 9.62555 | 1.63839 | 0.000470617 | 2.7437e-05 | 1.03252e-05 | 1(Win) | true |
| simdjson (ondemand) | 2337.87 | 0.23979 | 1460.45ms | 14795 | 160 | 33510 | 6035.25 | 0.108439 | 2.13785 | 9.18872 | 1.45955 | 0.000659006 | 2.87259e-05 | 9.71612e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 609.796 | 0.124651 | 1485.88ms | 4630 | 30 | 2444.03 | 7240.97 | 0.517952 | 8.18375 | 39.384 | 7.30972 | 0.00433405 | 5.75954e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 563.111 | 0.115788 | 1540.09ms | 4630 | 1280 | 105514 | 7841.28 | 0.205596 | 8.99061 | 38.2024 | 6.82635 | 0.00815267 | 0.000156587 | 7.32316e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 700.04 | 0.112371 | 1488.19ms | 4630 | 4890 | 245660 | 6307.51 | 0.192803 | 7.24892 | 35.0134 | 6.29352 | 0.00274912 | 8.2948e-05 | 2.85327e-05 | 1(Win) | true |
| simdjson (ondemand) | 637.324 | 0.132114 | 1549.25ms | 4630 | 640 | 53619.3 | 6928.21 | 0.142126 | 7.94222 | 33.7648 | 5.79849 | 0.00748954 | 5.29833e-05 | 2.09233e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1828.78 | 0.102096 | 1536.56ms | 14795 | 4890 | 303414 | 7715.32 | 0.0895861 | 2.76288 | 13.2366 | 2.33342 | 0.00140003 | 4.70645e-05 | 2.32351e-05 | 1(Win) | true |
| simdjson (ondemand) | 1704.7 | 0.14433 | 1595.89ms | 14795 | 1280 | 182668 | 8276.9 | 0.0654545 | 2.95582 | 12.7133 | 2.15999 | 0.00263655 | 3.56962e-05 | 1.53663e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2071.21 | 0.0564875 | 1536.62ms | 14795 | 4890 | 72409.6 | 6812.26 | 0.233328 | 2.43994 | 11.8362 | 2.00906 | 0.00109224 | 3.1321e-05 | 1.36839e-05 | 1(Win) | true |
| simdjson (ondemand) | 1903.53 | 0.258501 | 1599.27ms | 14795 | 1280 | 469943 | 7412.35 | 0.0360804 | 2.6572 | 11.3611 | 1.84549 | 0.00235885 | 3.43233e-05 | 1.57887e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5661.7 | 0.309692 | 826.459ms | 4630 | 1280 | 7466.88 | 779.891 | 0.194214 | 0.938109 | 4.71577 | 0.465011 | 0.000432978 | 2.02484e-05 | 5.73704e-06 | 1(Win) | true |
| simdjson (ondemand) | 4669.57 | 0.0959268 | 840.831ms | 4630 | 4890 | 4023.43 | 945.592 | 0.129989 | 1.12077 | 4.69482 | 0.565443 | 0.0024361 | 1.84182e-05 | 5.16768e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5711.66 | 0.200831 | 825.182ms | 4630 | 2560 | 6170.79 | 773.07 | 0.307833 | 0.918306 | 4.68035 | 0.45702 | 0.000433906 | 1.67049e-05 | 3.03726e-06 | 1(Win) | true |
| simdjson (ondemand) | 4731.97 | 0.181466 | 840.451ms | 4630 | 640 | 1835.05 | 933.123 | 0.0045209 | 1.09713 | 4.65961 | 0.557451 | 0.00200256 | 1.38364e-05 | 2.36231e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11651.1 | 0.121414 | 867.802ms | 14795 | 4890 | 10571.6 | 1211.01 | 0.375733 | 0.444572 | 2.26063 | 0.170936 | 0.000135913 | 8.33477e-06 | 1.07813e-06 | 1(Win) | true |
| simdjson (ondemand) | 9739.28 | 0.181581 | 888.704ms | 14795 | 2560 | 17715.6 | 1448.73 | 0.1929 | 0.532597 | 2.30896 | 0.216627 | 0.000611482 | 1.29108e-05 | 5.62373e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11794.9 | 0.128882 | 862.942ms | 14795 | 4890 | 11623.5 | 1196.25 | 0.173928 | 0.43896 | 2.24954 | 0.168436 | 0.000135955 | 1.33384e-05 | 4.81011e-06 | 1(Win) | true |
| simdjson (ondemand) | 9790.68 | 0.160054 | 892.669ms | 14795 | 1280 | 6810.02 | 1441.13 | 0.113443 | 0.531928 | 2.29794 | 0.214126 | 0.000681237 | 2.3023e-05 | 1.50494e-05 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3723.76 | 0.111887 | 871.668ms | 4630 | 30 | 52.8057 | 1185.77 | 0.199192 | 1.3787 | 7.31555 | 0.796328 | 0.000647948 | 2.15983e-05 | 2.15983e-05 | 1(Win) | true |
| simdjson (ondemand) | 3019.31 | 0.306443 | 906.097ms | 4630 | 80 | 1606.7 | 1462.42 | 0.0239271 | 1.68917 | 7.10821 | 0.978618 | 0.00279698 | 1.61987e-05 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3827.87 | 0.205409 | 867.802ms | 4630 | 640 | 3593.09 | 1153.52 | 0.0629471 | 1.37044 | 7.28035 | 0.788337 | 0.000649636 | 2.22732e-05 | 6.41199e-06 | 1(Win) | true |
| simdjson (ondemand) | 3059.87 | 0.150791 | 898.287ms | 4630 | 2560 | 12121.2 | 1443.04 | 0.0709185 | 1.67706 | 7.07322 | 0.970627 | 0.00393215 | 2.56479e-05 | 8.52119e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8845.18 | 0.215871 | 910.387ms | 14795 | 640 | 7588.99 | 1595.17 | 0.352554 | 0.585904 | 3.07421 | 0.27462 | 0.000203933 | 1.17227e-05 | 4.11879e-06 | 1(Win) | true |
| simdjson (ondemand) | 7080.92 | 0.116066 | 946.951ms | 14795 | 640 | 3423.29 | 1992.62 | 0.0191294 | 0.715035 | 3.06421 | 0.345928 | 0.00086389 | 1.08778e-05 | 4.64684e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8785.58 | 0.135665 | 912.881ms | 14795 | 4890 | 23213.1 | 1606 | 0.191042 | 0.581579 | 3.0632 | 0.272119 | 0.000205093 | 1.21082e-05 | 4.16047e-06 | 1(Win) | true |
| simdjson (ondemand) | 7226.49 | 0.136157 | 932.249ms | 14795 | 1280 | 9046.16 | 1952.49 | 0.093518 | 0.708622 | 3.05326 | 0.343427 | 0.00118362 | 6.81185e-06 | 2.21781e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1140.42 | 0.13868 | 1163.9ms | 5092 | 30 | 1046.14 | 4258.17 | 0.0775582 | 4.39876 | 17.2145 | 3.0542 | 0.00305708 | 0.000170202 | 0.000157109 | 1(Win) | true |
| jsonifier (generic) | 1057.06 | 0.0752144 | 1206.42ms | 5092 | 4890 | 58383 | 4593.97 | 0.136919 | 4.82161 | 18.5231 | 3.32613 | 0.00372978 | 0.000144338 | 6.93979e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1323.55 | 0.0813043 | 1147.01ms | 5092 | 4890 | 43514.3 | 3669 | 0.185879 | 3.86771 | 15.4417 | 2.63271 | 0.00264809 | 0.000129358 | 6.95586e-05 | 1(Win) | true |
| jsonifier (generic) | 1253.5 | 0.310217 | 1185.87ms | 5092 | 160 | 23108.7 | 3874.03 | 0.119886 | 4.07386 | 16.2129 | 2.79001 | 0.00219707 | 4.90966e-05 | 1.84112e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2457.89 | 0.102965 | 1206.08ms | 11724 | 4890 | 107279 | 4548.98 | 0.581822 | 2.0515 | 8.19695 | 1.35901 | 0.000875313 | 4.13394e-05 | 2.04778e-05 | 1(Win) | true |
| jsonifier (generic) | 2228.18 | 0.0739744 | 1258.95ms | 11724 | 4890 | 67378.6 | 5017.93 | 0.0364226 | 2.26244 | 8.85766 | 1.47516 | 0.00167949 | 5.65146e-05 | 2.6984e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2791.28 | 0.0621053 | 1183.83ms | 11724 | 4890 | 30263.1 | 4005.65 | 0.0871262 | 1.81276 | 7.43707 | 1.17748 | 0.000830119 | 2.75596e-05 | 9.90749e-06 | 1(Win) | true |
| jsonifier (generic) | 2578.38 | 0.246482 | 1240.48ms | 11724 | 640 | 73115.4 | 4336.4 | 0.06442 | 1.97597 | 7.92436 | 1.25638 | 0.00103447 | 3.85161e-05 | 1.67925e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 451.207 | 0.13181 | 1836.33ms | 5092 | 640 | 128796 | 10762.5 | 0.0996539 | 11.1377 | 45.2673 | 10.1908 | 0.00695423 | 0.000128265 | 7.18038e-05 | 1(Win) | true |
| simdjson (ondemand) | 312.245 | 0.187605 | 2322.8ms | 5092 | 160 | 136206 | 15552.2 | 0.153106 | 16.2252 | 70.436 | 12.7875 | 0.0109449 | 8.83739e-05 | 3.06854e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 479.42 | 0.0728216 | 1817.32ms | 5092 | 2560 | 139285 | 10129.1 | 0.0416901 | 10.4628 | 43.2553 | 9.70965 | 0.00645766 | 7.80943e-05 | 3.09922e-05 | 1(Win) | true |
| simdjson (ondemand) | 320.541 | 0.038852 | 2302.14ms | 5092 | 4890 | 169412 | 15149.7 | 0.219205 | 15.6673 | 68.6889 | 12.3698 | 0.00987965 | 0.000155181 | 7.49e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 998.379 | 0.185058 | 1869.86ms | 11724 | 640 | 274887 | 11199 | 0.0605469 | 5.01441 | 20.5192 | 4.46375 | 0.00242371 | 2.6788e-05 | 7.19678e-06 | 1(Win) | true |
| simdjson (ondemand) | 698.771 | 0.0983845 | 2354.1ms | 11724 | 4890 | 1.21184e+06 | 16000.8 | 0.0776655 | 7.23236 | 31.1915 | 5.56235 | 0.00607941 | 5.7003e-05 | 2.47513e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1067.52 | 0.0926774 | 1846.9ms | 11724 | 4890 | 460740 | 10473.7 | 0.446217 | 4.72064 | 19.6504 | 4.25561 | 0.00256379 | 6.74861e-05 | 3.80078e-05 | 1(Win) | true |
| simdjson (ondemand) | 726.879 | 0.130843 | 2346.15ms | 11724 | 1280 | 518489 | 15382 | 0.22911 | 6.96991 | 30.5172 | 5.39671 | 0.00526517 | 7.5233e-05 | 4.00487e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3994.75 | 0.142155 | 863.607ms | 5092 | 2560 | 7644.74 | 1215.62 | 0.0333338 | 1.31324 | 5.22722 | 0.899843 | 0.000859191 | 1.97154e-05 | 6.98093e-06 | 1(Win) | true |
| simdjson (ondemand) | 3571.18 | 0.0667421 | 879.813ms | 5092 | 4890 | 4027.75 | 1359.81 | 0.0972393 | 1.4471 | 6.00648 | 0.753142 | 0.000977635 | 2.34539e-05 | 4.21689e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4155.03 | 0.109974 | 860.638ms | 5092 | 4890 | 8078.25 | 1168.73 | 0.151465 | 1.25649 | 5.11351 | 0.874902 | 0.000475705 | 1.91969e-05 | 2.81126e-06 | 1(Win) | true |
| simdjson (ondemand) | 3678 | 0.0757962 | 873.079ms | 5092 | 4890 | 4897.32 | 1320.31 | 0.128866 | 1.41773 | 5.89395 | 0.728201 | 0.00108743 | 2.38555e-05 | 7.46992e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7239.46 | 0.0954647 | 895.976ms | 11724 | 2560 | 5565 | 1544.43 | 0.0517468 | 0.715458 | 3.05843 | 0.422211 | 0.000349177 | 1.12949e-05 | 1.79919e-06 | 1(Win) | true |
| simdjson (ondemand) | 6681.78 | 0.266262 | 912.733ms | 11724 | 320 | 6352.36 | 1673.34 | 0.0597251 | 0.774673 | 3.33947 | 0.361396 | 0.000433672 | 5.33095e-06 | 7.99642e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7458.98 | 0.154416 | 893.45ms | 11724 | 640 | 3428.93 | 1498.98 | 0.0122985 | 0.69618 | 3.00904 | 0.411379 | 0.000171523 | 5.0644e-06 | 5.33095e-07 | 1(Win) | true |
| simdjson (ondemand) | 6859.32 | 0.0901858 | 910.562ms | 11724 | 320 | 691.538 | 1630.03 | 0.217505 | 0.756239 | 3.2906 | 0.350563 | 0.000381429 | 6.66368e-06 | 1.06619e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2576.41 | 0.112305 | 943.19ms | 5092 | 4890 | 21910.5 | 1884.84 | 0.122741 | 2.00678 | 9.54694 | 1.76512 | 0.00109221 | 2.20483e-05 | 4.29721e-06 | 1(Win) | true |
| simdjson (ondemand) | 2127.38 | 0.0694024 | 989.428ms | 5092 | 4890 | 12272.8 | 2282.67 | 0.0120691 | 2.39897 | 10.5799 | 1.58916 | 0.00194868 | 2.83536e-05 | 6.82734e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2596.17 | 0.102155 | 954.314ms | 5092 | 2560 | 9347.05 | 1870.49 | 0.184197 | 1.973 | 9.43323 | 1.74018 | 0.000826204 | 1.97921e-05 | 2.07126e-06 | 1(Win) | true |
| simdjson (ondemand) | 2216.18 | 0.0654472 | 970.252ms | 5092 | 4890 | 10056.7 | 2191.2 | 0.246761 | 2.31099 | 10.4177 | 1.5544 | 0.00124989 | 2.61045e-05 | 7.67072e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4935.67 | 0.111398 | 988.005ms | 11724 | 2560 | 16302.5 | 2265.32 | 0.492897 | 1.03547 | 4.93458 | 0.798021 | 0.000576375 | 1.42603e-05 | 1.36605e-06 | 1(Win) | true |
| simdjson (ondemand) | 4351.34 | 0.194676 | 1010.99ms | 11724 | 640 | 16014.4 | 2569.53 | 0.181125 | 1.18291 | 5.32583 | 0.724497 | 0.000529629 | 1.75921e-05 | 6.79695e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5119.55 | 0.287636 | 984.62ms | 11724 | 160 | 6313.85 | 2183.96 | 0.430252 | 1.00609 | 4.88519 | 0.787189 | 0.000344912 | 2.02576e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4485.84 | 0.165733 | 1005.47ms | 11724 | 640 | 10921 | 2492.48 | 0.0326714 | 1.14437 | 5.25537 | 0.7094 | 0.000338648 | 5.33095e-06 | 3.99821e-07 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1409.14 | 0.189487 | 1103.46ms | 4857 | 320 | 12414.6 | 3287.1 | 0.0269116 | 3.62552 | 14.182 | 2.67902 | 0.000824197 | 6.11231e-05 | 2.05888e-05 | 1(Win) | true |
| simdjson (ondemand) | 1361.22 | 0.0941417 | 1118.21ms | 4857 | 4890 | 50182.9 | 3402.84 | 0.0103447 | 3.72782 | 14.3084 | 2.62075 | 0.000918835 | 9.63339e-05 | 3.33042e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1850.15 | 0.116359 | 1040.28ms | 4857 | 4890 | 41497.8 | 2503.57 | 0.192629 | 2.75186 | 11.1491 | 2.02018 | 0.00122182 | 4.40408e-05 | 8.75763e-06 | 1(Win) | true |
| simdjson (ondemand) | 1719.02 | 0.156135 | 1072.01ms | 4857 | 40 | 707.997 | 2694.55 | 0.254803 | 2.98719 | 11.9862 | 2.12147 | 0.000669137 | 3.08833e-05 | 0 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2071.21 | 0.102714 | 1097.44ms | 7376 | 2560 | 31152.5 | 3396.23 | 0.153588 | 2.46444 | 9.90944 | 1.78539 | 0.000535944 | 6.65164e-05 | 3.14046e-05 | 1(Win) | true |
| simdjson (ondemand) | 2002.59 | 0.303101 | 1092.25ms | 7376 | 160 | 18136.5 | 3512.61 | 0.160414 | 2.55247 | 9.85941 | 1.73902 | 0.000861748 | 3.64357e-05 | 7.62608e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2692.86 | 0.204132 | 1031.26ms | 7376 | 640 | 18197.8 | 2612.21 | 0.119667 | 1.90803 | 7.91228 | 1.35155 | 0.00070965 | 4.19435e-05 | 1.60995e-05 | 1(Win) | true |
| simdjson (ondemand) | 2478.39 | 0.0571336 | 1046.37ms | 7376 | 4890 | 12858.6 | 2838.26 | 0.139823 | 2.06875 | 8.33026 | 1.41025 | 0.000761021 | 5.0293e-05 | 2.00451e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 555.98 | 0.0574007 | 1578.71ms | 4857 | 4890 | 111831 | 8331.22 | 0.129132 | 9.13168 | 37.908 | 7.73338 | 0.00662413 | 6.12613e-05 | 1.69679e-05 | 1(Win) | true |
| simdjson (ondemand) | 160.995 | 0.102911 | 3613.08ms | 4857 | 320 | 280532 | 28771.1 | 0.119947 | 31.1833 | 143.139 | 27.1952 | 0.0566888 | 9.65102e-05 | 2.38058e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 622.875 | 0.137902 | 1523.43ms | 4857 | 640 | 67306.1 | 7436.48 | 0.475129 | 8.15687 | 34.8882 | 7.07886 | 0.00630565 | 5.59759e-05 | 1.12595e-05 | 1(Win) | true |
| simdjson (ondemand) | 165.867 | 0.0582428 | 3580.72ms | 4857 | 4890 | 1.29363e+06 | 27926 | 0.117662 | 30.4503 | 140.848 | 26.7056 | 0.0575372 | 9.79759e-05 | 3.17464e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 828.289 | 0.139104 | 1603.52ms | 7376 | 2560 | 357272 | 8492.57 | 0.145149 | 6.11443 | 25.5645 | 5.11958 | 0.00403589 | 6.52454e-05 | 2.42552e-05 | 1(Win) | true |
| simdjson (ondemand) | 247.461 | 0.0585233 | 3604.78ms | 7376 | 1280 | 354239 | 28425.9 | 0.142855 | 20.3384 | 94.388 | 17.8468 | 0.0324722 | 6.54572e-05 | 2.48907e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 924.191 | 0.106154 | 1546.41ms | 7376 | 2560 | 167121 | 7611.31 | 0.21243 | 5.50734 | 23.5409 | 4.6814 | 0.00408403 | 4.77689e-05 | 1.68409e-05 | 1(Win) | true |
| simdjson (ondemand) | 254.092 | 0.141543 | 3562.39ms | 7376 | 1280 | 1.9654e+06 | 27684.1 | 0.0578 | 19.9187 | 92.88 | 17.5244 | 0.033683 | 3.96133e-05 | 9.74444e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3514.48 | 0.214716 | 870.131ms | 4857 | 40 | 320.333 | 1317.97 | 0.0297085 | 1.45937 | 5.98992 | 0.874001 | 0.000252213 | 1.54416e-05 | 5.14721e-06 | 1(Win) | true |
| jsonifier (generic) | 3492.31 | 0.147916 | 879.443ms | 4857 | 2560 | 9853.21 | 1326.34 | 0.257066 | 1.49075 | 6.15966 | 0.888427 | 0.000889985 | 2.18756e-05 | 6.91656e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 4002.46 | 0.16993 | 872.443ms | 4857 | 2560 | 9900.66 | 1157.29 | 0.0560623 | 1.30768 | 5.59769 | 0.758082 | 0.00101593 | 1.4557e-05 | 1.04553e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3987.47 | 0.100996 | 866.22ms | 4857 | 4890 | 6730.63 | 1161.64 | 0.15301 | 1.3044 | 5.45151 | 0.747581 | 0.000547183 | 1.77258e-05 | 2.73676e-06 | 1(Tie) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4965.48 | 0.0737812 | 882.523ms | 7376 | 4890 | 5342.19 | 1416.64 | 0.0438775 | 1.04669 | 4.40496 | 0.59653 | 0.000178909 | 1.46942e-05 | 2.21799e-06 | 1(Win) | true |
| jsonifier (generic) | 4912.99 | 0.279557 | 890.242ms | 7376 | 640 | 10253.5 | 1431.78 | 0.358729 | 1.05787 | 4.61891 | 0.603988 | 0.00027009 | 1.60995e-05 | 5.08406e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5581.18 | 0.0724212 | 869.268ms | 7376 | 4890 | 4074.08 | 1260.36 | 0.0618252 | 0.93605 | 4.05043 | 0.513286 | 0.000137599 | 1.76885e-05 | 5.07366e-06 | 1(Win) | true |
| jsonifier (generic) | 5366.02 | 0.180586 | 880.981ms | 7376 | 2560 | 14346.5 | 1310.9 | 0.700091 | 0.961566 | 4.24892 | 0.518168 | 0.000777914 | 1.2869e-05 | 1.74764e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2060.85 | 0.112823 | 967.388ms | 4857 | 1280 | 8230.97 | 2247.61 | 0.0621454 | 2.49843 | 11.1388 | 2.25777 | 0.00133184 | 1.89803e-05 | 2.2519e-06 | 1(Win) | true |
| simdjson (ondemand) | 2027.58 | 0.134645 | 974.416ms | 4857 | 30 | 283.845 | 2284.5 | 0.00437713 | 2.53644 | 11.2469 | 1.89314 | 0.000823554 | 5.49036e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2184.63 | 0.0959146 | 961.676ms | 4857 | 4890 | 20223.7 | 2120.27 | 0.037358 | 2.35734 | 10.5959 | 2.13445 | 0.0024827 | 2.29888e-05 | 5.68404e-06 | 1(Win) | true |
| simdjson (ondemand) | 2112.81 | 0.0742778 | 963.997ms | 4857 | 4890 | 12967.1 | 2192.34 | 0.0729506 | 2.43887 | 10.7237 | 1.77455 | 0.00211118 | 2.91359e-05 | 5.93666e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2969.83 | 0.0933543 | 981.547ms | 7376 | 4890 | 23908.8 | 2368.59 | 0.135407 | 1.72554 | 7.86646 | 1.49404 | 0.00078151 | 2.49524e-05 | 1.00641e-05 | 1(Win) | true |
| simdjson (ondemand) | 2931.39 | 0.14299 | 980.853ms | 7376 | 160 | 1883.76 | 2399.65 | 0.104291 | 1.75772 | 7.80586 | 1.25393 | 0.000699905 | 7.62608e-06 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3126.45 | 0.12612 | 979.149ms | 7376 | 320 | 2576.65 | 2249.93 | 0.11113 | 1.64022 | 7.50895 | 1.41283 | 0.00156716 | 1.99126e-05 | 8.47343e-06 | 1(Win) | true |
| simdjson (ondemand) | 3093.9 | 0.109175 | 969.27ms | 7376 | 40 | 246.451 | 2273.6 | 0.0748272 | 1.66448 | 7.46136 | 1.17584 | 0.00117611 | 6.77874e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1223.31 | 0.113466 | 1079.56ms | 4390 | 2560 | 38603.2 | 3422.37 | 0.0522001 | 4.18188 | 17.846 | 3.23759 | 0.00334977 | 5.0541e-05 | 1.73512e-05 | 1(Win) | true |
| simdjson (ondemand) | 1081.91 | 0.0527796 | 1125.79ms | 4390 | 4890 | 20398.1 | 3869.67 | 0.0504031 | 4.72243 | 18.6312 | 3.49909 | 0.00239706 | 6.24211e-05 | 2.58069e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1354.72 | 0.165077 | 1069.46ms | 4390 | 2560 | 66625.6 | 3090.4 | 0.00939237 | 3.78001 | 16.4171 | 2.918 | 0.00307882 | 3.87956e-05 | 1.10336e-05 | 1(Win) | true |
| simdjson (ondemand) | 1180.33 | 0.0663828 | 1115.39ms | 4390 | 2560 | 14192.9 | 3546.99 | 0.120654 | 4.33326 | 17.2727 | 3.19294 | 0.00217567 | 2.72281e-05 | 7.11845e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2910.62 | 0.155444 | 1117.96ms | 11521 | 640 | 22036.3 | 3774.9 | 0.137356 | 1.76497 | 7.81564 | 1.29451 | 0.00121463 | 5.68256e-05 | 2.91587e-05 | 1(Win) | true |
| simdjson (ondemand) | 2581.55 | 0.0841443 | 1168.12ms | 11521 | 1280 | 16416.5 | 4256.09 | 0.0171967 | 1.98374 | 7.91693 | 1.37479 | 0.00135018 | 2.21064e-05 | 9.9004e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3161.11 | 0.0933252 | 1111.79ms | 11521 | 1280 | 13468.1 | 3475.76 | 0.217443 | 1.62114 | 7.2492 | 1.16839 | 0.00139474 | 1.8309e-05 | 4.54333e-06 | 1(Win) | true |
| simdjson (ondemand) | 2775.4 | 0.0856746 | 1156.26ms | 11521 | 1280 | 14724.6 | 3958.81 | 0.231883 | 1.84126 | 7.37731 | 1.2538 | 0.00132862 | 3.00403e-05 | 1.56643e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 652.528 | 0.0543187 | 1379.85ms | 4390 | 4890 | 59393.4 | 6416.02 | 0.109299 | 7.78163 | 34.2417 | 7.52301 | 0.0115821 | 8.81814e-05 | 3.71266e-05 | 1(Win) | true |
| simdjson (ondemand) | 620.924 | 0.0983325 | 1428.25ms | 4390 | 640 | 28133.7 | 6742.58 | 0.0410574 | 8.1839 | 35.444 | 6.32005 | 0.0088283 | 1.92198e-05 | 5.69476e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 692.052 | 0.0825075 | 1371.31ms | 4390 | 2560 | 63779.2 | 6049.59 | 0.125243 | 7.33859 | 32.7549 | 7.1918 | 0.0112195 | 4.48462e-05 | 1.41479e-05 | 1(Win) | true |
| simdjson (ondemand) | 653.667 | 0.0694078 | 1410.39ms | 4390 | 2560 | 50590.9 | 6404.83 | 0.0945534 | 7.76173 | 34.0852 | 6.01367 | 0.00895697 | 3.30118e-05 | 9.07603e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1624.7 | 0.211919 | 1438.45ms | 11521 | 160 | 32861.9 | 6762.64 | 0.0482197 | 3.13263 | 13.9644 | 2.89758 | 0.00467245 | 1.79021e-05 | 1.62746e-06 | 1(Win) | true |
| simdjson (ondemand) | 1566.43 | 0.147494 | 1452.16ms | 11521 | 320 | 34250 | 7014.23 | 0.00628227 | 3.24594 | 14.1891 | 2.41932 | 0.00376324 | 9.22229e-06 | 2.71244e-07 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1709.74 | 0.301915 | 1413.89ms | 11521 | 320 | 120460 | 6426.29 | 0.0760152 | 2.97501 | 13.3979 | 2.77137 | 0.00441856 | 1.41047e-05 | 1.08498e-06 | 1(Win) | true |
| simdjson (ondemand) | 1644.76 | 0.158024 | 1432.24ms | 11521 | 160 | 17829.5 | 6680.17 | 0.0231148 | 3.09426 | 13.6714 | 2.30258 | 0.00369326 | 2.82094e-05 | 2.27845e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2039.54 | 0.158694 | 971.809ms | 4390 | 1280 | 13583 | 2052.73 | 0.0155305 | 2.52879 | 11.1203 | 1.99704 | 0.00274665 | 3.2389e-05 | 6.58457e-06 | 1(Win) | true |
| simdjson (ondemand) | 2031.29 | 0.0982782 | 947.925ms | 4390 | 4890 | 20063.5 | 2061.07 | 0.366682 | 2.52826 | 10.603 | 1.79544 | 0.00219974 | 3.95023e-05 | 9.45633e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2137.67 | 0.112287 | 947.485ms | 4390 | 30 | 145.086 | 1958.5 | 0.0664214 | 2.41543 | 10.2503 | 1.71412 | 0.00211845 | 6.83371e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 2117.9 | 0.0816423 | 943.345ms | 4390 | 4890 | 12736.7 | 1976.78 | 0.139366 | 2.436 | 10.8257 | 1.92711 | 0.00201057 | 3.30739e-05 | 4.19246e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4505.61 | 0.129721 | 988.511ms | 11521 | 1280 | 12808.8 | 2438.58 | 0.0551055 | 1.12899 | 4.83743 | 0.722247 | 0.000903378 | 2.3666e-05 | 9.42572e-06 | 1(Win) | true |
| jsonifier (generic) | 4467.88 | 0.0930497 | 1001.43ms | 11521 | 4890 | 25604.4 | 2459.17 | 0.2663 | 1.14197 | 5.17386 | 0.810173 | 0.0011277 | 2.12114e-05 | 4.43753e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4753.83 | 0.0638405 | 986.412ms | 11521 | 4890 | 10646.2 | 2311.25 | 0.388731 | 1.0819 | 4.70306 | 0.69126 | 0.000917681 | 1.24961e-05 | 2.16551e-06 | 1(Win) | true |
| jsonifier (generic) | 4666.5 | 0.0985289 | 992.783ms | 11521 | 4890 | 26316.9 | 2354.5 | 0.089415 | 1.09397 | 5.03967 | 0.779186 | 0.00106032 | 1.58331e-05 | 2.59152e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1632.55 | 0.0735372 | 1024.95ms | 4390 | 4890 | 17390.8 | 2564.47 | 0.232534 | 3.11973 | 14.7998 | 2.70547 | 0.00404587 | 6.7685e-05 | 2.56672e-05 | 1(Win) | true |
| simdjson (ondemand) | 1623.48 | 0.0956402 | 1010.34ms | 4390 | 160 | 973.272 | 2578.79 | 0.0113897 | 3.16501 | 13.9638 | 2.36788 | 0.00340689 | 1.70843e-05 | 5.69476e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1699.74 | 0.153178 | 1016.23ms | 4390 | 1280 | 18220.9 | 2463.1 | 0.103579 | 2.99721 | 14.4476 | 2.62415 | 0.00328588 | 2.42027e-05 | 6.22864e-06 | 1(Win) | true |
| simdjson (ondemand) | 1669.57 | 0.061753 | 998.551ms | 4390 | 4890 | 11725.9 | 2507.61 | 0.487364 | 3.05008 | 13.6146 | 2.28656 | 0.00311565 | 2.16611e-05 | 4.37879e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3734.95 | 0.0794513 | 1036.77ms | 11521 | 4890 | 26712.9 | 2941.75 | 0.331649 | 1.36906 | 6.55395 | 1.07577 | 0.00188084 | 1.69869e-05 | 4.02927e-06 | 1(Win) | true |
| simdjson (ondemand) | 3692.04 | 0.0882772 | 1045.51ms | 11521 | 2560 | 17667.8 | 2975.94 | 0.150178 | 1.3841 | 6.11805 | 0.94037 | 0.00149367 | 3.7296e-05 | 1.96652e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3916.13 | 0.14922 | 1032.57ms | 11521 | 40 | 701.105 | 2805.65 | 0.060034 | 1.31144 | 6.41976 | 1.04479 | 0.00164482 | 4.3399e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3839.53 | 0.106655 | 1033.74ms | 11521 | 1280 | 11923.3 | 2861.62 | 0.0367332 | 1.33042 | 5.98498 | 0.909383 | 0.00135947 | 2.10892e-05 | 9.42572e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1474.78 | 0.174258 | 1061.65ms | 4669 | 640 | 17715.7 | 3019.23 | 0.0507941 | 3.47136 | 14.9156 | 2.5196 | 0.000287133 | 4.18318e-05 | 8.70101e-06 | 1(Win) | true |
| jsonifier (generic) | 1435.46 | 0.0792743 | 1060.91ms | 4669 | 4890 | 29569.3 | 3101.94 | 0.0524642 | 3.54492 | 14.3074 | 2.63912 | 0.00185494 | 6.39908e-05 | 2.57102e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1606.72 | 0.0668379 | 1040.04ms | 4669 | 4890 | 16777.3 | 2771.3 | 0.643216 | 3.19038 | 14.1259 | 2.34054 | 0.00046401 | 4.13027e-05 | 1.34464e-05 | 1(Win) | true |
| jsonifier (generic) | 1576.94 | 0.0677507 | 1029.68ms | 4669 | 4890 | 17895.8 | 2823.63 | 0.0843835 | 3.24884 | 13.5348 | 2.46391 | 0.00163862 | 6.83707e-05 | 2.84258e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2717.23 | 0.0807877 | 1083.02ms | 9249 | 4890 | 33630.7 | 3246.15 | 0.0557221 | 1.88472 | 8.15701 | 1.2996 | 0.000156741 | 3.29887e-05 | 1.40843e-05 | 1(Win) | true |
| jsonifier (generic) | 2673.79 | 0.112938 | 1088.13ms | 9249 | 2560 | 35534.7 | 3298.89 | 0.064552 | 1.91236 | 8.08358 | 1.38793 | 0.0010412 | 2.45381e-05 | 5.57493e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2962.59 | 0.0544765 | 1059.42ms | 9249 | 4890 | 12863.9 | 2977.3 | 0.294281 | 1.72979 | 7.75835 | 1.20921 | 0.000142501 | 1.97446e-05 | 3.71455e-06 | 1(Win) | true |
| jsonifier (generic) | 2864.36 | 0.0885913 | 1065.59ms | 9249 | 2560 | 19052.7 | 3079.41 | 0.185813 | 1.78358 | 7.68613 | 1.29798 | 0.00104374 | 6.04373e-05 | 3.48855e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 427.889 | 0.239479 | 1796.45ms | 4669 | 320 | 198733 | 10406.2 | 0.139474 | 11.8601 | 52.2123 | 10.9809 | 0.0113086 | 0.00014524 | 6.15764e-05 | 1(Win) | true |
| simdjson (ondemand) | 186.307 | 0.0596255 | 3149.46ms | 4669 | 2560 | 519869 | 23899.8 | 0.124732 | 27.1079 | 123.046 | 24.4181 | 0.0377035 | 7.51298e-05 | 2.45971e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 439.334 | 0.0633372 | 1761.83ms | 4669 | 2560 | 105491 | 10135.1 | 0.142673 | 11.518 | 51.4316 | 10.8034 | 0.0103479 | 6.47556e-05 | 1.78203e-05 | 1(Win) | true |
| simdjson (ondemand) | 187.37 | 0.0314529 | 3128.19ms | 4669 | 4890 | 273196 | 23764.2 | 0.000689464 | 26.8417 | 122.256 | 24.2397 | 0.0386381 | 6.31586e-05 | 1.82643e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 824.236 | 0.219772 | 1822.87ms | 9249 | 320 | 177003 | 10701.5 | 0.109568 | 6.14916 | 27.1736 | 5.58558 | 0.00582293 | 4.52752e-05 | 1.72316e-05 | 1(Win) | true |
| simdjson (ondemand) | 368.259 | 0.0695218 | 3142.25ms | 9249 | 4890 | 1.35592e+06 | 23952 | 0.0189276 | 13.7395 | 62.0324 | 12.1948 | 0.0225114 | 5.35292e-05 | 1.61185e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 844.926 | 0.0738865 | 1793.94ms | 9249 | 2560 | 152308 | 10439.4 | 0.0727293 | 5.9905 | 26.7807 | 5.49616 | 0.00587589 | 3.28583e-05 | 7.47547e-06 | 1(Win) | true |
| simdjson (ondemand) | 373.388 | 0.0421171 | 3125.36ms | 9249 | 2560 | 253411 | 23622.9 | 0.0460023 | 13.4913 | 61.6341 | 12.1049 | 0.0230348 | 5.23705e-05 | 2.33556e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3921.71 | 0.28456 | 857.105ms | 4669 | 320 | 3340.37 | 1135.4 | 0.0137636 | 1.32797 | 5.86185 | 0.758835 | 0.000886164 | 1.20475e-05 | 2.00792e-06 | 1(Win) | true |
| jsonifier (generic) | 3693.47 | 0.145658 | 866.464ms | 4669 | 2560 | 7893.85 | 1205.56 | 0.292926 | 1.41125 | 6.31313 | 0.789677 | 0.00107834 | 2.34258e-05 | 4.76882e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4148.2 | 0.175899 | 852.386ms | 4669 | 160 | 570.394 | 1073.41 | 0.0145586 | 1.24551 | 5.61041 | 0.699722 | 0.000844667 | 8.0317e-06 | 0 | 1(Win) | true |
| jsonifier (generic) | 3997.36 | 0.129704 | 858.381ms | 4669 | 80 | 166.992 | 1113.91 | 0.202701 | 1.3109 | 6.05847 | 0.730563 | 0.000859392 | 8.0317e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6493.29 | 0.171098 | 878.352ms | 9249 | 1280 | 6914.47 | 1358.41 | 0.140191 | 0.801161 | 3.5819 | 0.410315 | 0.00043155 | 1.19101e-05 | 1.3515e-06 | 1(Win) | true |
| jsonifier (generic) | 6216.93 | 0.103864 | 885.568ms | 9249 | 4890 | 10618.9 | 1418.79 | 0.171613 | 0.835319 | 3.88553 | 0.424916 | 0.000560122 | 1.4615e-05 | 1.79094e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6876.78 | 0.0767673 | 873.503ms | 9249 | 4890 | 4741.12 | 1282.66 | 0.107905 | 0.758442 | 3.45497 | 0.380474 | 0.000444131 | 8.33562e-06 | 7.07532e-07 | 1(Win) | true |
| jsonifier (generic) | 6612.4 | 0.124362 | 883.309ms | 9249 | 80 | 220.161 | 1333.94 | 0.106002 | 0.788104 | 3.75695 | 0.39507 | 0.000481133 | 1.21635e-05 | 1.3515e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2237.58 | 0.0861953 | 941.355ms | 4669 | 2560 | 7531.78 | 1989.97 | 0.367242 | 2.3012 | 10.8501 | 2.07475 | 0.00197153 | 1.23822e-05 | 2.50991e-07 | 1(Win) | true |
| simdjson (ondemand) | 2060.06 | 0.0550571 | 970.652ms | 4669 | 4890 | 6925.09 | 2161.45 | 0.124411 | 2.50024 | 11.1626 | 1.72864 | 0.0023974 | 1.73007e-05 | 1.62057e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2324.86 | 0.0846593 | 947.699ms | 4669 | 4890 | 12856.2 | 1915.25 | 0.0654107 | 2.21869 | 10.5952 | 2.01564 | 0.00226622 | 1.61181e-05 | 2.36516e-06 | 1(Win) | true |
| simdjson (ondemand) | 2119.23 | 0.0649548 | 963.15ms | 4669 | 4890 | 9108.03 | 2101.1 | 0.0181096 | 2.42233 | 10.9111 | 1.66952 | 0.00230209 | 1.37092e-05 | 6.1319e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3980.42 | 0.159509 | 972.584ms | 9249 | 1280 | 15992.3 | 2215.98 | 0.330971 | 1.29115 | 6.1718 | 1.07233 | 0.0011595 | 1.43597e-05 | 2.02725e-06 | 1(Win) | true |
| simdjson (ondemand) | 3661.36 | 0.0662125 | 1000.5ms | 9249 | 4890 | 12442.1 | 2409.09 | 0.207854 | 1.39442 | 6.24695 | 0.897611 | 0.00125032 | 8.7336e-06 | 2.43214e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4169.05 | 0.0827738 | 975.969ms | 9249 | 160 | 490.707 | 2115.72 | 0.225905 | 1.23698 | 6.04314 | 1.04249 | 0.00108728 | 9.46048e-06 | 1.3515e-06 | 1(Win) | true |
| simdjson (ondemand) | 3808.57 | 0.160216 | 993.415ms | 9249 | 640 | 8811.64 | 2315.97 | 0.0179428 | 1.35107 | 6.12001 | 0.86777 | 0.00123561 | 1.75695e-05 | 5.06812e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 579.702 | 0.0788504 | 1522.49ms | 4604 | 2560 | 91308.1 | 7574.09 | 0.152452 | 8.73967 | 36.706 | 7.34978 | 0.0102598 | 7.24574e-05 | 1.91749e-05 | 1(Win) | true |
| simdjson (ondemand) | 569.971 | 0.0883435 | 1539.03ms | 4604 | 1280 | 59282.3 | 7703.41 | 0.216066 | 8.87653 | 36.3223 | 6.82081 | 0.0103003 | 5.2434e-05 | 1.37448e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 662.292 | 0.116651 | 1518.69ms | 4604 | 1280 | 76552.4 | 6629.58 | 0.0382019 | 7.64592 | 32.1451 | 6.30995 | 0.00964956 | 4.41192e-05 | 6.4482e-06 | 1(Win) | true |
| simdjson (ondemand) | 649.327 | 0.166502 | 1540.51ms | 4604 | 2560 | 324507 | 6761.95 | 0.0181945 | 7.8053 | 31.9234 | 5.81614 | 0.00979574 | 7.69541e-05 | 1.72235e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2688.09 | 0.0949216 | 1635.12ms | 24579 | 30 | 2055.37 | 8720.07 | 0.0389753 | 1.88996 | 7.84055 | 1.32422 | 0.00181184 | 9.4932e-06 | 0 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2686.86 | 0.0764741 | 1640.06ms | 24579 | 2560 | 113948 | 8724.07 | 0.063684 | 1.8816 | 7.92217 | 1.42461 | 0.00217982 | 2.32986e-05 | 8.32774e-06 | 1(Tie) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3033.66 | 0.0916826 | 1631.04ms | 24579 | 2560 | 128472 | 7726.75 | 0.0214399 | 1.66779 | 7.06823 | 1.23003 | 0.00196644 | 1.23009e-05 | 3.17853e-06 | 1(Win) | true |
| simdjson (ondemand) | 2999.58 | 0.161086 | 1624.95ms | 24579 | 640 | 101415 | 7814.55 | 0.108449 | 1.68712 | 7.00259 | 1.13293 | 0.00177088 | 7.00547e-05 | 4.18294e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 214.107 | 0.117444 | 2819.55ms | 4604 | 640 | 371237 | 20507.1 | 0.0440285 | 23.5432 | 101.917 | 23.6551 | 0.0341761 | 0.00030612 | 0.000192767 | 1(Win) | true |
| simdjson (ondemand) | 162.735 | 0.0858705 | 3493.85ms | 4604 | 320 | 171770 | 26980.8 | 0.0800514 | 31.0923 | 137.11 | 24.7533 | 0.043826 | 0.000111316 | 4.4798e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 226.729 | 0.13613 | 2807.27ms | 4604 | 320 | 222388 | 19365.5 | 0.0931687 | 22.3404 | 97.5804 | 22.6596 | 0.0327799 | 5.09068e-05 | 6.10882e-06 | 1(Win) | true |
| simdjson (ondemand) | 168.056 | 0.0860093 | 3481.3ms | 4604 | 2560 | 1.29269e+06 | 26126.5 | 0.0194748 | 30.1192 | 132.654 | 23.733 | 0.0428094 | 0.000217372 | 0.000111571 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1091.99 | 0.04404 | 2929.17ms | 24579 | 4890 | 437011 | 21465.7 | 0.0452818 | 4.62895 | 20.1333 | 4.47699 | 0.00636908 | 1.57749e-05 | 5.1418e-06 | 1(Win) | true |
| simdjson (ondemand) | 836.245 | 0.0384612 | 3579.15ms | 24579 | 4890 | 568350 | 28030.5 | 0.00819981 | 6.04423 | 26.6805 | 4.67448 | 0.00775656 | 4.96708e-05 | 2.77807e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1146.54 | 0.124424 | 2930.99ms | 24579 | 320 | 207065 | 20444.4 | 0.113684 | 4.41571 | 19.2992 | 4.28618 | 0.00628407 | 3.90323e-05 | 2.31397e-05 | 1(Win) | true |
| simdjson (ondemand) | 865.464 | 0.0750419 | 3574.34ms | 24579 | 640 | 264374 | 27084.1 | 0.0931878 | 5.82226 | 25.8447 | 4.48316 | 0.00774683 | 3.45824e-05 | 1.50662e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3082.81 | 0.183207 | 892.776ms | 4604 | 1280 | 8715.12 | 1424.26 | 0.149753 | 1.68688 | 6.95982 | 1.28171 | 0.0018564 | 1.71386e-05 | 1.86658e-06 | 1(Win) | true |
| simdjson (ondemand) | 2707.96 | 0.261972 | 911.108ms | 4604 | 320 | 5773.59 | 1621.41 | 0.0242903 | 1.9119 | 8.10882 | 1.05647 | 0.00188423 | 1.83265e-05 | 4.07255e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3146.59 | 0.194791 | 892.67ms | 4604 | 320 | 2364.17 | 1395.39 | 0.0903949 | 1.65384 | 6.87967 | 1.26303 | 0.001834 | 2.98653e-05 | 2.03627e-06 | 1(Win) | true |
| simdjson (ondemand) | 2749.71 | 0.0846201 | 910.902ms | 4604 | 2560 | 4673.94 | 1596.79 | 0.00296013 | 1.88016 | 8.02932 | 1.03779 | 0.00170572 | 1.75629e-05 | 1.5272e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10086.7 | 0.148466 | 983.307ms | 24579 | 640 | 7618.42 | 2323.89 | 0.0907539 | 0.510012 | 2.30388 | 0.278653 | 0.000341247 | 5.14921e-06 | 1.27141e-07 | 1(Win) | true |
| simdjson (ondemand) | 8982.36 | 0.142549 | 1011.91ms | 24579 | 30 | 415.145 | 2609.6 | 0.0191637 | 0.561506 | 2.551 | 0.243582 | 0.000381084 | 3.52605e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10275.2 | 0.160262 | 985.195ms | 24579 | 2560 | 34217.6 | 2281.25 | 0.0635895 | 0.501886 | 2.28886 | 0.275154 | 0.000336892 | 6.30937e-06 | 1.0807e-06 | 1(Win) | true |
| simdjson (ondemand) | 9192.48 | 0.174305 | 1012.83ms | 24579 | 320 | 6321.7 | 2549.95 | 0.00367668 | 0.559382 | 2.53611 | 0.240083 | 0.000324845 | 9.917e-06 | 1.27141e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1467.63 | 0.106471 | 1045.96ms | 4604 | 320 | 3246.74 | 2991.71 | 0.229171 | 3.47324 | 14.2053 | 3.45004 | 0.00497122 | 1.42539e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1287.11 | 0.0812756 | 1082.49ms | 4604 | 1280 | 9839.45 | 3411.3 | 0.0101236 | 3.9751 | 17.449 | 2.7209 | 0.00460842 | 2.0193e-05 | 2.88472e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1482.1 | 0.0614554 | 1040.06ms | 4604 | 4890 | 16208.6 | 2962.5 | 0.21754 | 3.45772 | 14.1251 | 3.43137 | 0.00464582 | 1.76782e-05 | 1.02161e-06 | 1(Win) | true |
| simdjson (ondemand) | 1286.66 | 0.0848253 | 1086.29ms | 4604 | 1280 | 10725.1 | 3412.48 | 0.05972 | 3.97445 | 17.3695 | 2.70222 | 0.0045078 | 1.91749e-05 | 7.29664e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6052.68 | 0.19287 | 1133.26ms | 24579 | 40 | 2231.64 | 3872.72 | 0.00193658 | 0.844637 | 3.66052 | 0.684609 | 0.000945929 | 2.03426e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5346.51 | 0.112289 | 1191.42ms | 24579 | 30 | 727.082 | 4384.23 | 0.0228142 | 0.954955 | 4.30013 | 0.55523 | 0.000922196 | 5.42469e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6091.8 | 0.0533699 | 1127.97ms | 24579 | 4890 | 20622.4 | 3847.86 | 0.117178 | 0.836654 | 3.64551 | 0.68111 | 0.00088518 | 8.69447e-06 | 1.48929e-06 | 1(Win) | true |
| simdjson (ondemand) | 5380.63 | 0.0497655 | 1181.48ms | 24579 | 2560 | 12032.6 | 4356.44 | 0.0754302 | 0.948015 | 4.28524 | 0.551731 | 0.000824669 | 5.181e-06 | 7.94632e-08 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 752.57 | 0.260185 | 891.959ms | 1181 | 640 | 9703.96 | 1496.59 | 0.202326 | 6.90742 | 29.1219 | 5.10669 | 0.00342401 | 0.000171994 | 8.07049e-05 | 1(Win) | true |
| jsonifier (generic) | 715.606 | 0.160984 | 898.264ms | 1181 | 1280 | 8217.25 | 1573.9 | 0.0171222 | 7.2449 | 30.149 | 5.68163 | 0.00447449 | 0.000171333 | 4.03525e-05 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 971.857 | 0.0982765 | 879.64ms | 1181 | 4890 | 6343.12 | 1158.9 | 0.117096 | 5.37142 | 22.8188 | 3.69517 | 0.00172205 | 9.0215e-05 | 1.316e-05 | 1(Win) | true |
| jsonifier (generic) | 919.897 | 0.135258 | 882.165ms | 1181 | 2560 | 7020.84 | 1224.36 | 0.181111 | 5.67804 | 23.547 | 4.20661 | 0.00249094 | 0.00023153 | 6.08594e-05 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1509.87 | 0.100438 | 905.505ms | 2496 | 4890 | 12260.6 | 1576.54 | 0.16545 | 3.41087 | 14.4507 | 2.44191 | 0.0016668 | 0.000100857 | 3.82616e-05 | 1(Win) | true |
| jsonifier (generic) | 1438.37 | 0.150656 | 918.201ms | 2496 | 80 | 497.296 | 1654.91 | 0.41446 | 3.59972 | 15.1843 | 2.7516 | 0.00204828 | 6.00962e-05 | 2.50401e-05 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1955.24 | 0.135657 | 882.12ms | 2496 | 2560 | 6982.56 | 1217.43 | 0.00574372 | 2.67486 | 11.4685 | 1.77407 | 0.000813802 | 2.89526e-05 | 3.13001e-06 | 1(Win) | true |
| jsonifier (generic) | 1796.24 | 0.128237 | 898.495ms | 2496 | 2560 | 7393.09 | 1325.2 | 0.0924125 | 2.90418 | 12.1619 | 2.07372 | 0.000885949 | 4.19421e-05 | 2.97351e-06 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 544.675 | 0.108522 | 961.484ms | 1181 | 2560 | 12891.5 | 2067.82 | 0.157319 | 9.46057 | 40.558 | 8.58595 | 0.004795 | 0.0002355 | 7.04514e-05 | 1(Win) | true |
| simdjson (ondemand) | 437.261 | 0.117414 | 1009.31ms | 1181 | 1280 | 11707.6 | 2575.78 | 0.148172 | 11.7399 | 50.8086 | 8.93904 | 0.00837347 | 9.79043e-05 | 1.78609e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 647.996 | 0.141729 | 942.253ms | 1181 | 2560 | 15535 | 1738.11 | 0.0548068 | 7.94375 | 34.1719 | 7.15326 | 0.00205434 | 0.000348288 | 0.000159425 | 1(Win) | true |
| simdjson (ondemand) | 503.767 | 0.101271 | 988.331ms | 1181 | 2560 | 13123.5 | 2235.73 | 0.0635922 | 10.228 | 44.5064 | 7.52752 | 0.00688638 | 8.3351e-05 | 8.5997e-06 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1088.33 | 0.140007 | 967.029ms | 2496 | 1280 | 12002.6 | 2187.18 | 0.0833713 | 4.73523 | 20.2107 | 4.14583 | 0.00245236 | 0.000115497 | 4.63241e-05 | 1(Win) | true |
| simdjson (ondemand) | 891.658 | 0.115331 | 1016.84ms | 2496 | 30 | 284.386 | 2669.6 | 0.0287267 | 5.64945 | 24.7119 | 4.25521 | 0.00380609 | 6.67735e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1289.18 | 0.202976 | 949.118ms | 2496 | 40 | 561.84 | 1846.42 | 0.128462 | 4.01007 | 17.1891 | 3.46795 | 0.000971554 | 2.00321e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1033.92 | 0.318352 | 1001.47ms | 2496 | 320 | 17190.1 | 2302.27 | 0.139459 | 4.96649 | 21.73 | 3.58734 | 0.00340294 | 5.25841e-05 | 1.252e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2336.22 | 0.1899 | 797.999ms | 1181 | 4890 | 4098.55 | 482.099 | 0.304319 | 2.33234 | 8.65284 | 1.59695 | 0.00168603 | 8.70982e-05 | 1.74889e-05 | 1(Win) | true |
| simdjson (ondemand) | 2198.03 | 0.323904 | 795.057ms | 1181 | 1280 | 3525.95 | 512.409 | 0.076444 | 2.44528 | 9.56562 | 1.4039 | 0.000867909 | 6.81361e-05 | 6.61516e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2697.3 | 0.202751 | 791.65ms | 1181 | 4890 | 3504.88 | 417.561 | 0.376972 | 2.03884 | 7.8171 | 1.4022 | 0.00091912 | 8.10377e-05 | 2.44152e-05 | 1(Win) | true |
| simdjson (ondemand) | 2534.97 | 0.273077 | 793.48ms | 1181 | 40 | 58.8821 | 444.3 | 0.565867 | 2.17902 | 8.75783 | 1.21338 | 0.00084674 | 4.2337e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4287.05 | 0.390129 | 810.406ms | 2496 | 640 | 3003.09 | 555.247 | 0.0691781 | 1.25789 | 4.84135 | 0.785657 | 0.000415665 | 2.37881e-05 | 2.50401e-06 | 1(Win) | true |
| simdjson (ondemand) | 4107.52 | 0.194333 | 802.251ms | 2496 | 2560 | 3246.85 | 579.515 | 0.176157 | 1.31834 | 5.19752 | 0.689904 | 0.000413787 | 2.66051e-05 | 3.59951e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4867.82 | 0.153641 | 794.876ms | 2496 | 4890 | 2760.23 | 489.001 | 0.0809593 | 1.12411 | 4.44591 | 0.69351 | 0.000454633 | 2.9577e-05 | 5.24356e-06 | 1(Win) | true |
| simdjson (ondemand) | 4602.24 | 0.225885 | 797.325ms | 2496 | 1280 | 1747.18 | 517.22 | 0.102213 | 1.18359 | 4.8153 | 0.59976 | 0.000412222 | 2.03451e-05 | 3.13001e-07 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2171.64 | 0.214179 | 793.734ms | 1181 | 2560 | 3158.77 | 518.636 | 0.0198878 | 2.50182 | 9.30229 | 1.77477 | 0.00159359 | 5.22597e-05 | 1.98455e-06 | 1(Win) | true |
| simdjson (ondemand) | 2015.58 | 0.158722 | 798.476ms | 1181 | 4890 | 3846.64 | 558.793 | 0.0473958 | 2.68239 | 10.2718 | 1.52413 | 0.00182629 | 7.09946e-05 | 1.36794e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2439.31 | 0.195822 | 789.222ms | 1181 | 2560 | 2092.81 | 461.725 | 0.74561 | 2.25226 | 8.46655 | 1.58002 | 0.000913884 | 6.21825e-05 | 4.29985e-06 | 1(Win) | true |
| simdjson (ondemand) | 2256.7 | 0.179615 | 794.508ms | 1181 | 640 | 514.301 | 499.086 | 0.127883 | 2.40083 | 9.46401 | 1.33362 | 0.00188135 | 4.76291e-05 | 1.32303e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3953.53 | 0.16526 | 806.778ms | 2496 | 320 | 316.814 | 602.087 | 0.0560864 | 1.34246 | 5.14864 | 0.869792 | 0.000565905 | 1.878e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3837.75 | 0.149716 | 806.328ms | 2496 | 4890 | 4216.8 | 620.252 | 0.121307 | 1.39991 | 5.53165 | 0.746795 | 0.000602272 | 2.23671e-05 | 1.96634e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4399.44 | 0.165856 | 803.298ms | 2496 | 4890 | 3937.9 | 541.062 | 0.0284985 | 1.23302 | 4.75321 | 0.777644 | 0.000554835 | 2.55624e-05 | 1.55668e-06 | 1(Win) | true |
| simdjson (ondemand) | 4250.85 | 0.223684 | 795.118ms | 2496 | 2560 | 4016.49 | 559.976 | 0.176658 | 1.27512 | 5.14944 | 0.656651 | 0.000611917 | 1.98756e-05 | 1.565e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1214.68 | 0.0833759 | 1139.4ms | 4926 | 2560 | 26618.9 | 3867.53 | 0.0677873 | 4.20457 | 16.6831 | 3.10942 | 0.00443454 | 5.91568e-05 | 1.83973e-05 | 1(Win) | true |
| simdjson (ondemand) | 1091.01 | 0.0449264 | 1178.8ms | 4926 | 4890 | 18299.7 | 4305.92 | 0.114229 | 4.67575 | 17.8839 | 3.3648 | 0.00293505 | 5.04813e-05 | 1.18315e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1503.48 | 0.0644355 | 1098.5ms | 4926 | 4890 | 19822.3 | 3124.62 | 0.165734 | 3.40687 | 14.0045 | 2.52132 | 0.0041809 | 4.56656e-05 | 8.96707e-06 | 1(Win) | true |
| simdjson (ondemand) | 1305.44 | 0.0724292 | 1142.09ms | 4926 | 2560 | 17391.7 | 3598.63 | 0.0552856 | 3.89897 | 15.3291 | 2.80106 | 0.00294277 | 4.3297e-05 | 1.11018e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2214.07 | 0.0982028 | 1155.92ms | 9463 | 1280 | 20508.4 | 4076.03 | 0.0438539 | 2.30646 | 9.34439 | 1.64419 | 0.00218293 | 2.59233e-05 | 5.61397e-06 | 1(Win) | true |
| simdjson (ondemand) | 1990.16 | 0.0413557 | 1197.41ms | 9463 | 4890 | 17197.3 | 4534.61 | 0.183437 | 2.56004 | 9.90289 | 1.77787 | 0.00114118 | 2.16104e-05 | 4.55979e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2699.01 | 0.0595132 | 1120.28ms | 9463 | 4890 | 19363.5 | 3343.67 | 0.00978357 | 1.89586 | 7.95002 | 1.33805 | 0.0022112 | 1.87362e-05 | 2.0746e-06 | 1(Win) | true |
| simdjson (ondemand) | 2358.7 | 0.0448571 | 1163.84ms | 9463 | 4890 | 14404 | 3826.1 | 0.0705667 | 2.16732 | 8.57297 | 1.48441 | 0.00138456 | 2.11782e-05 | 2.87418e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 502.328 | 0.0467815 | 1687.8ms | 4926 | 4890 | 93599.1 | 9352.06 | 0.0120703 | 10.1008 | 38.9842 | 8.10841 | 0.0317551 | 5.61272e-05 | 1.03786e-05 | 1(Win) | true |
| simdjson (ondemand) | 406.089 | 0.112826 | 1908.85ms | 4926 | 640 | 109030 | 11568.4 | 0.0957725 | 12.4901 | 54.6458 | 10.3678 | 0.0156545 | 6.0267e-05 | 1.77629e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 543.941 | 0.046277 | 1659.71ms | 4926 | 4890 | 78113.5 | 8636.6 | 0.0247527 | 9.33267 | 36.3167 | 7.52599 | 0.0316215 | 4.78659e-05 | 6.22713e-06 | 1(Win) | true |
| simdjson (ondemand) | 436.535 | 0.142111 | 1866.32ms | 4926 | 320 | 74844.1 | 10761.6 | 0.0443325 | 11.6261 | 52.1021 | 9.80979 | 0.0145104 | 3.04507e-05 | 0 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 939.247 | 0.0639785 | 1714.83ms | 9463 | 2560 | 96740.1 | 9608.35 | 0.0981514 | 5.39239 | 20.9332 | 4.2383 | 0.0169152 | 0.000102414 | 6.1217e-05 | 1(Win) | true |
| simdjson (ondemand) | 770.88 | 0.0632912 | 1931ms | 9463 | 1280 | 70271.9 | 11706.9 | 0.145375 | 6.56365 | 28.9011 | 5.39153 | 0.00824643 | 3.49222e-05 | 9.90701e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1004.65 | 0.217242 | 1693.37ms | 9463 | 160 | 60931.3 | 8982.88 | 0.156095 | 4.95772 | 19.5446 | 3.93512 | 0.0165817 | 3.03815e-05 | 1.12279e-05 | 1(Win) | true |
| simdjson (ondemand) | 814.922 | 0.156876 | 1898.92ms | 9463 | 640 | 193161 | 11074.2 | 0.00294894 | 6.16317 | 27.5644 | 5.09861 | 0.00768041 | 2.49326e-05 | 5.11862e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2247.21 | 0.160878 | 962.041ms | 4926 | 80 | 904.861 | 2090.5 | 0.0263164 | 2.29353 | 9.78969 | 1.72574 | 0.00265175 | 1.77629e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2220.11 | 0.152794 | 954.395ms | 4926 | 1280 | 13380.1 | 2116.02 | 0.0922023 | 2.31716 | 9.38002 | 1.6078 | 0.00209253 | 1.58597e-05 | 7.92986e-07 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2441.86 | 0.0781566 | 943.102ms | 4926 | 4890 | 11055.8 | 1923.86 | 0.00785075 | 2.11322 | 8.7905 | 1.46204 | 0.00189612 | 2.69012e-05 | 5.2723e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2440.63 | 0.100887 | 952.473ms | 4926 | 4890 | 18440.2 | 1924.83 | 0.189905 | 2.10306 | 9.19549 | 1.57998 | 0.00267248 | 3.05129e-05 | 8.30284e-06 | 1(Tie) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 3917.81 | 0.0987882 | 972.863ms | 9463 | 2560 | 13256.3 | 2303.49 | 0.156597 | 1.30674 | 5.75092 | 0.921378 | 0.00138025 | 2.27448e-05 | 6.39827e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3910.46 | 0.156232 | 972.722ms | 9463 | 640 | 8320 | 2307.82 | 0.00128641 | 1.31486 | 5.46201 | 0.862306 | 0.000623646 | 1.60163e-05 | 2.9721e-06 | 1(Tie) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4256.71 | 0.15788 | 966.126ms | 9463 | 1280 | 14340.8 | 2120.09 | 0.0984121 | 1.21058 | 5.44161 | 0.845504 | 0.00139383 | 1.95663e-05 | 4.21048e-06 | 1(Win) | true |
| simdjson (ondemand) | 4221.28 | 0.0817429 | 963.72ms | 9463 | 2560 | 7818.25 | 2137.89 | 0.05838 | 1.21938 | 5.15513 | 0.786432 | 0.000755781 | 9.94829e-06 | 1.77501e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1495.55 | 0.0792881 | 1055.23ms | 4926 | 4890 | 30333 | 3141.19 | 0.145935 | 3.42075 | 15.4811 | 2.87353 | 0.00401401 | 2.95996e-05 | 6.97439e-06 | 1(Win) | true |
| simdjson (ondemand) | 1440.88 | 0.0598109 | 1067.32ms | 4926 | 4890 | 18595.2 | 3260.36 | 0.0211021 | 3.53687 | 14.7659 | 2.58648 | 0.00422515 | 2.48255e-05 | 4.27596e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1572.2 | 0.241657 | 1055.46ms | 4926 | 160 | 8342.45 | 2988.05 | 0.0560252 | 3.24801 | 14.8839 | 2.72594 | 0.0048683 | 3.80633e-05 | 2.53756e-06 | 1(Win) | true |
| simdjson (ondemand) | 1526.94 | 0.111947 | 1059.46ms | 4926 | 1280 | 15183.8 | 3076.62 | 0.0581673 | 3.35342 | 14.1705 | 2.43991 | 0.00426706 | 1.79215e-05 | 2.69615e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2713.47 | 0.122425 | 1074.19ms | 9463 | 1280 | 21220.7 | 3325.86 | 0.0105482 | 1.88496 | 8.71447 | 1.51929 | 0.00215989 | 1.89884e-05 | 4.70583e-06 | 1(Win) | true |
| simdjson (ondemand) | 2561.82 | 0.113963 | 1092.53ms | 9463 | 30 | 483.513 | 3522.73 | 0.0899732 | 1.95871 | 8.27264 | 1.37261 | 0.00227553 | 3.52249e-06 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2841.37 | 0.13422 | 1080.25ms | 9463 | 80 | 1453.88 | 3176.15 | 0.0212476 | 1.8027 | 8.40357 | 1.44246 | 0.0027449 | 7.9256e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2738.91 | 0.0517544 | 1083.93ms | 9463 | 4890 | 14220.2 | 3294.97 | 0.0702181 | 1.86464 | 7.9627 | 1.29631 | 0.00201746 | 2.65159e-05 | 8.9467e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2128.09 | 0.142843 | 871.045ms | 2821 | 4890 | 15946 | 1264.19 | 0.179504 | 2.44434 | 8.82879 | 1.51967 | 0.000549197 | 6.69098e-05 | 2.02252e-05 | 1(Win) | true |
| simdjson (ondemand) | 2022.75 | 0.114989 | 881.633ms | 2821 | 4890 | 11437.8 | 1330.03 | 0.269034 | 2.55269 | 8.94045 | 1.48281 | 0.000455683 | 4.27701e-05 | 5.58186e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2348.55 | 0.118796 | 861.116ms | 2821 | 4890 | 9055.63 | 1145.52 | 0.0576118 | 2.23104 | 8.22155 | 1.36831 | 0.000754203 | 4.34225e-05 | 4.13202e-06 | 1(Win) | true |
| simdjson (ondemand) | 2192.83 | 0.223223 | 880.079ms | 2821 | 640 | 4800.13 | 1226.87 | 0.452227 | 2.39053 | 8.4782 | 1.36973 | 0.00075051 | 3.82178e-05 | 4.98493e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2915.86 | 0.211371 | 884.064ms | 4147 | 2560 | 21041.1 | 1356.34 | 0.180279 | 1.76056 | 6.53533 | 1.05281 | 0.000367642 | 4.1634e-05 | 9.04268e-06 | 1(Win) | true |
| simdjson (ondemand) | 2855.26 | 0.180543 | 883.487ms | 4147 | 2560 | 16009.5 | 1385.12 | 0.180363 | 1.81285 | 6.48059 | 1.02653 | 0.000314704 | 3.94675e-05 | 1.04556e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3200.19 | 0.138161 | 877.864ms | 4147 | 4890 | 14256 | 1235.83 | 0.177599 | 1.62591 | 6.12226 | 0.949844 | 0.000479811 | 2.99327e-05 | 1.47938e-06 | 1(Win) | true |
| simdjson (ondemand) | 3089.11 | 0.268131 | 880.103ms | 4147 | 160 | 1885.46 | 1280.27 | 0.0882823 | 1.70078 | 6.16494 | 0.94912 | 0.000327044 | 2.41138e-05 | 3.01423e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 747.621 | 0.225218 | 1108.29ms | 2821 | 1280 | 84073.7 | 3598.5 | 0.0221061 | 6.86957 | 28.2478 | 5.38603 | 0.00133984 | 0.000181119 | 0.000109115 | 1(Win) | true |
| simdjson (ondemand) | 288.292 | 0.0776151 | 1683.01ms | 2821 | 1280 | 67149.5 | 9331.9 | 0.0849018 | 17.588 | 77.0695 | 15.6196 | 0.00662886 | 0.00015841 | 8.11437e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 766.548 | 0.205552 | 1105.05ms | 2821 | 1280 | 66616.3 | 3509.65 | 0.0498376 | 6.68395 | 27.6345 | 5.23254 | 0.00194717 | 0.000119915 | 6.17578e-05 | 1(Win) | true |
| simdjson (ondemand) | 289.975 | 0.0517664 | 1683.34ms | 2821 | 2560 | 59050.3 | 9277.76 | 0.088529 | 17.3783 | 76.5998 | 15.5037 | 0.00732218 | 6.75736e-05 | 1.02468e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1070.23 | 0.100994 | 1118.42ms | 4147 | 4890 | 68109.9 | 3695.35 | 0.264025 | 4.77999 | 19.7159 | 3.67398 | 0.00121333 | 4.67483e-05 | 1.63224e-05 | 1(Win) | true |
| simdjson (ondemand) | 427.768 | 0.110072 | 1681.63ms | 4147 | 640 | 66280.6 | 9245.41 | 0.0333216 | 11.8661 | 52.2479 | 10.511 | 0.00650809 | 3.9185e-05 | 3.01423e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1100.07 | 0.132642 | 1122.3ms | 4147 | 2560 | 58214.9 | 3595.14 | 0.0743073 | 4.6539 | 19.3014 | 3.57005 | 0.00145926 | 4.46482e-05 | 9.23107e-06 | 1(Win) | true |
| simdjson (ondemand) | 432.39 | 0.140262 | 1674.58ms | 4147 | 320 | 52668.3 | 9146.58 | 0.147232 | 11.7504 | 51.931 | 10.4326 | 0.00602544 | 4.37063e-05 | 3.76778e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5210 | 0.121281 | 801.254ms | 2821 | 80 | 31.3766 | 516.375 | 0.0725689 | 1.04637 | 4.20596 | 0.479263 | 0.000354484 | 8.86211e-06 | 0 | 1(Win) | true |
| jsonifier (generic) | 4585.67 | 0.143554 | 806.274ms | 2821 | 4890 | 3468.51 | 586.679 | 0.112459 | 1.18023 | 4.50514 | 0.524991 | 0.00105243 | 5.43687e-05 | 2.51546e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5330.26 | 0.242808 | 806.252ms | 2821 | 320 | 480.601 | 504.725 | 0.11033 | 1.02782 | 4.12974 | 0.461184 | 0.000357808 | 3.32329e-05 | 2.21553e-06 | 1(Win) | true |
| jsonifier (generic) | 4722.27 | 0.147408 | 806.261ms | 2821 | 4890 | 3448.71 | 569.708 | 0.0768782 | 1.14776 | 4.42964 | 0.506913 | 0.00101858 | 2.64595e-05 | 2.68219e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6715.23 | 0.165167 | 819.949ms | 4147 | 4890 | 4627.03 | 588.943 | 0.0543937 | 0.804739 | 3.26573 | 0.34531 | 0.000244541 | 1.82456e-05 | 5.07919e-06 | 1(Win) | true |
| jsonifier (generic) | 5833.59 | 0.142527 | 832.67ms | 4147 | 4890 | 4565.62 | 677.95 | 0.446227 | 0.916466 | 3.58524 | 0.374488 | 0.000711826 | 2.02674e-05 | 4.09294e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6891.7 | 0.147534 | 804.529ms | 4147 | 4890 | 3505.16 | 573.862 | 0.124538 | 0.78567 | 3.21389 | 0.333012 | 0.000244048 | 1.51883e-05 | 1.43006e-06 | 1(Win) | true |
| jsonifier (generic) | 5985.3 | 0.173355 | 818.715ms | 4147 | 2560 | 3358.99 | 660.767 | 0.0611051 | 0.895874 | 3.53399 | 0.362212 | 0.00071456 | 1.79912e-05 | 4.23876e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3092.27 | 0.197232 | 842.24ms | 2821 | 80 | 235.557 | 870.013 | 0.110753 | 1.70967 | 7.38674 | 1.15349 | 0.00117866 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3069.31 | 0.165477 | 840.691ms | 2821 | 2560 | 5385.63 | 876.52 | 0.438862 | 1.72238 | 7.09004 | 1.01772 | 0.000364177 | 1.42625e-05 | 3.04635e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3173.55 | 0.131258 | 840.597ms | 2821 | 4890 | 6054.51 | 847.732 | 0.194792 | 1.66553 | 7.31124 | 1.13577 | 0.000816691 | 3.07365e-05 | 6.66923e-06 | 1(Win) | true |
| simdjson (ondemand) | 3123.17 | 0.0950454 | 841.769ms | 2821 | 4890 | 3277.83 | 861.406 | 0.158272 | 1.69148 | 7.0156 | 1 | 0.000362313 | 2.43572e-05 | 5.43687e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4168.4 | 0.118718 | 833.193ms | 4147 | 4890 | 6203.96 | 948.778 | 0.264527 | 1.26419 | 5.23607 | 0.713528 | 0.000257954 | 2.92916e-05 | 6.85444e-06 | 1(Win) | true |
| jsonifier (generic) | 4148.34 | 0.183787 | 844.807ms | 4147 | 30 | 92.1023 | 953.367 | 0.0663871 | 1.26874 | 5.54811 | 0.80299 | 0.000707339 | 1.60759e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4242.82 | 0.217414 | 830.924ms | 4147 | 1280 | 5257.1 | 932.138 | 0.0501452 | 1.24288 | 5.18544 | 0.701471 | 0.000256021 | 1.58247e-05 | 5.46329e-06 | 1(Win) | true |
| jsonifier (generic) | 4205.07 | 0.125236 | 832.345ms | 4147 | 4890 | 6784.08 | 940.505 | 0.283063 | 1.25574 | 5.49674 | 0.790934 | 0.000720012 | 1.70621e-05 | 4.19156e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4459.8 | 0.0364912 | 6713.07ms | 277673 | 4890 | 2.29574e+06 | 59377.1 | 0.105666 | 1.12857 | 4.33378 | 0.689538 | 0.0031302 | 4.20821e-06 | 2.97683e-06 | 1(Win) | true |
| simdjson (ondemand) | 3642.25 | 0.11987 | 4110.9ms | 277673 | 320 | 2.4305e+06 | 72705 | 0.018221 | 1.38382 | 4.72182 | 0.764614 | 0.00444934 | 1.8682e-06 | 7.99051e-07 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3648.17 | 0.119191 | 4145.05ms | 10548466 | 40 | 4.32095e+08 | 2.75749e+06 | 0.545354 | 1.38288 | 4.3345 | 0.689686 | 0.0100334 | 0.017133 | 0.00159123 | 1(Win) | true |
| simdjson (ondemand) | 3223.64 | 0.178362 | 4690.27ms | 10548466 | 80 | 2.47843e+09 | 3.12063e+06 | 0.0724465 | 1.56437 | 4.72151 | 0.76497 | 0.00974287 | 0.0181495 | 9.91625e-05 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3659.42 | 0.153133 | 6275.75ms | 16002592 | 40 | 1.63136e+09 | 4.1704e+06 | 0.0694231 | 1.37867 | 7.85124 | 1.05049 | 0.000674163 | 0.0383582 | 0.000262264 | 1(Win) | true |
| jsonifier (generic) | 3462.38 | 0.14776 | 6660.79ms | 16002592 | 80 | 3.39338e+09 | 4.40773e+06 | 0.0999851 | 1.45892 | 8.35675 | 0.986212 | 0.000835961 | 0.0336845 | 0.000166457 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3678.03 | 0.17218 | 6246.68ms | 16002591 | 80 | 4.08326e+09 | 4.14931e+06 | 0.423035 | 1.36593 | 7.78798 | 1.35176 | 0.000841674 | 0.0370693 | 0.000669478 | 1(Win) | true |
| simdjson (ondemand) | 2169.61 | 0.136034 | 4947.43ms | 16002591 | 30 | 2.74687e+09 | 7.03411e+06 | 0.0580352 | 2.3278 | 12.0137 | 1.91026 | 0.000635812 | 0.0530853 | 0.00470471 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 18618.1 | 0.0923806 | 5288.78ms | 16197086 | 320 | 1.87981e+08 | 829661 | 0.0198731 | 0.268301 | 1.45194 | 0.0666257 | 8.03078e-05 | 0.0157366 | 8.24666e-05 | 1(Win) | true |
| simdjson (ondemand) | 18296 | 0.0503273 | 5392.96ms | 16197086 | 320 | 5.77721e+07 | 844269 | 0.0826814 | 0.27601 | 1.27274 | 0.0715446 | 8.07281e-05 | 0.0157419 | 6.27281e-05 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 18678.1 | 0.144193 | 5337.72ms | 16197085 | 40 | 5.68797e+07 | 826997 | 0.057898 | 0.270119 | 1.46122 | 0.072645 | 9.20459e-05 | 0.0157071 | 3.74188e-05 | 1(Win) | true |
| simdjson (ondemand) | 17191.3 | 0.100245 | 5749.2ms | 16197085 | 320 | 2.59615e+08 | 898522 | 0.171183 | 0.293571 | 1.34168 | 0.0858754 | 9.06191e-05 | 0.0157319 | 0.000126893 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1310.24 | 0.123314 | 5202.67ms | 4525120 | 80 | 1.31969e+09 | 3.29366e+06 | 0.763325 | 3.82768 | 16.3186 | 2.65575 | 0.00877123 | 0.0781736 | 0.000697189 | 1(Win) | true |
| simdjson (ondemand) | 1233.96 | 0.143126 | 5557.75ms | 4525120 | 40 | 1.00221e+09 | 3.49727e+06 | 0.285527 | 4.08164 | 15.6507 | 2.56521 | 0.0163186 | 0.0773843 | 0.000117362 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 565.228 | 0.0708246 | 5508.5ms | 4525120 | 40 | 1.16961e+09 | 7.63496e+06 | 0.206678 | 8.91972 | 41.1109 | 8.85391 | 0.0239485 | 0.0787928 | 0.000657193 | 1(Win) | true |
| simdjson (ondemand) | 407.485 | 0.0341931 | 7589.45ms | 4525120 | 30 | 3.93401e+08 | 1.05906e+07 | 0.137993 | 12.3945 | 54.1604 | 9.54748 | 0.0448833 | 0.0781267 | 0.00094561 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1111.85 | 0.643222 | 6139.83ms | 4525119 | 80 | 4.98635e+10 | 3.88138e+06 | 0.136223 | 4.54395 | 19.2032 | 3.53613 | 0.0114299 | 0.0781176 | 0.000866577 | 1(Win) | true |
| simdjson (ondemand) | 941.969 | 0.807831 | 7201.4ms | 4525119 | 40 | 5.47884e+10 | 4.58135e+06 | 0.773811 | 5.36116 | 20.1916 | 3.50588 | 0.0188198 | 0.0934166 | 0.000631928 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 570.885 | 0.30183 | 5433.43ms | 4525119 | 30 | 1.56174e+10 | 7.55929e+06 | 0.303327 | 8.84344 | 39.5724 | 9.18145 | 0.0260461 | 0.0789599 | 0.00101779 | 1(Win) | true |
| simdjson (ondemand) | 370.775 | 0.0534368 | 8337.01ms | 4525119 | 30 | 1.16049e+09 | 1.16391e+07 | 0.0342701 | 13.6071 | 58.7057 | 10.4889 | 0.0474622 | 0.0945033 | 0.00194628 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1262.56 | 0.110618 | 5010.03ms | 4203059 | 80 | 9.86657e+08 | 3.17478e+06 | 0.0989471 | 4.00026 | 17.7024 | 3.20723 | 0.0136289 | 0.0896659 | 0.000466613 | 1(Win) | true |
| simdjson (ondemand) | 995.798 | 0.0916321 | 6296.75ms | 4203059 | 80 | 1.08836e+09 | 4.02526e+06 | 0.145257 | 5.0693 | 18.5179 | 3.50478 | 0.023647 | 0.0886598 | 0.000122336 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 778.6 | 0.0691973 | 8002.25ms | 4203059 | 80 | 1.01525e+09 | 5.14815e+06 | 0.283442 | 6.48034 | 29.3778 | 6.01331 | 0.0216614 | 0.0888691 | 0.00306902 | 1(Win) | true |
| simdjson (ondemand) | 725.09 | 0.0728713 | 4005.36ms | 4203059 | 40 | 6.49113e+08 | 5.52807e+06 | 0.0322389 | 6.96494 | 29.0052 | 5.21275 | 0.0271567 | 0.0883969 | 0.00810155 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1061.03 | 0.12261 | 5920.81ms | 4203058 | 80 | 1.7164e+09 | 3.77779e+06 | 0.137223 | 4.76003 | 20.4465 | 4.0388 | 0.0153487 | 0.0891048 | 0.00200845 | 1(Win) | true |
| simdjson (ondemand) | 822.956 | 0.119455 | 7544.14ms | 4203058 | 80 | 2.70818e+09 | 4.87067e+06 | 0.0428123 | 6.11874 | 22.8067 | 4.38887 | 0.0250252 | 0.104806 | 0.00028001 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 696.558 | 0.0964002 | 4153.96ms | 4203058 | 40 | 1.23093e+09 | 5.75451e+06 | 0.0276505 | 7.25025 | 32.125 | 6.84598 | 0.0235222 | 0.0889809 | 0.00465155 | 1(Win) | true |
| simdjson (ondemand) | 637.519 | 0.0928536 | 4533.61ms | 4203058 | 40 | 1.36333e+09 | 6.28742e+06 | 0.238249 | 7.93797 | 33.2928 | 6.09642 | 0.0285922 | 0.104468 | 0.000421074 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1824.52 | 0.127229 | 7136.56ms | 4197496 | 80 | 6.23376e+08 | 2.19403e+06 | 0.0512562 | 2.7711 | 14.9223 | 2.63365 | 0.000508687 | 0.0819708 | 5.72484e-05 | 1(Win) | true |
| simdjson (ondemand) | 1547.18 | 0.21031 | 4046.58ms | 4197496 | 30 | 8.88263e+08 | 2.58732e+06 | 0.0280289 | 3.26424 | 15.8296 | 2.56673 | 0.00649193 | 0.0821697 | 5.1769e-05 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 751.477 | 0.0872167 | 8161.73ms | 4197496 | 80 | 1.72679e+09 | 5.3269e+06 | 0.201788 | 6.70606 | 32.5851 | 6.0965 | 0.0155776 | 0.0826279 | 0.00207434 | 1(Win) | true |
| jsonifier (generic) | 667.1 | 0.0960313 | 4283.6ms | 4197496 | 40 | 1.32826e+09 | 6.00066e+06 | 0.00880953 | 7.56687 | 39.3953 | 7.33175 | 0.00106665 | 0.08249 | 0.00525899 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1580.5 | 0.09695 | 8199.57ms | 4197495 | 160 | 9.64735e+08 | 2.53277e+06 | 0.170016 | 3.18652 | 17.6302 | 3.4828 | 0.000646729 | 0.0841985 | 0.000384725 | 1(Win) | true |
| simdjson (ondemand) | 1161.41 | 0.101571 | 5348.27ms | 4197495 | 30 | 3.67682e+08 | 3.44671e+06 | 0.0395074 | 4.34909 | 20.564 | 3.55178 | 0.00675566 | 0.102457 | 4.28827e-05 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 667.304 | 0.465322 | 4278.68ms | 4197495 | 30 | 2.33755e+10 | 5.99883e+06 | 0.0179997 | 7.55437 | 38.6353 | 7.74912 | 0.0012731 | 0.0846542 | 0.0086696 | 1(Win) | true |
| simdjson (ondemand) | 648.477 | 0.0596196 | 4431.39ms | 4197495 | 40 | 5.41789e+08 | 6.17299e+06 | 0.541993 | 7.77821 | 37.3196 | 7.08159 | 0.0158074 | 0.102792 | 0.00147604 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1517.73 | 0.116469 | 5070.81ms | 4506447 | 30 | 3.26301e+08 | 2.83165e+06 | 0.131806 | 3.31748 | 15.3675 | 2.78104 | 0.00827319 | 0.081167 | 0.00155846 | 1(Win) | true |
| simdjson (ondemand) | 1148.72 | 0.601233 | 6390.65ms | 4506447 | 80 | 4.04776e+10 | 3.74127e+06 | 0.0430881 | 4.40344 | 16.6536 | 3.08358 | 0.0156189 | 0.0792103 | 0.00735674 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 612.588 | 0.224408 | 5286.96ms | 4506447 | 30 | 7.43585e+09 | 7.01562e+06 | 0.274776 | 8.2382 | 33.2953 | 6.45701 | 0.0311977 | 0.0814895 | 0.0139985 | 1(Win) | true |
| simdjson (ondemand) | 477.405 | 0.463549 | 6634.15ms | 4506447 | 30 | 5.22404e+10 | 9.00217e+06 | 1.30796 | 10.5717 | 47.8474 | 9.12034 | 0.0195208 | 0.0796181 | 0.0157661 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1292.14 | 0.0632306 | 5782.56ms | 4506446 | 30 | 1.32686e+08 | 3.32602e+06 | 0.0107577 | 3.90592 | 17.4744 | 3.42323 | 0.0107976 | 0.0818326 | 0.00112054 | 1(Win) | true |
| simdjson (ondemand) | 979.908 | 0.514728 | 7413.57ms | 4506446 | 80 | 4.07702e+10 | 4.3858e+06 | 0.438804 | 5.15879 | 20.0403 | 3.78823 | 0.0158103 | 0.0869335 | 0.000277927 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 613.144 | 0.473038 | 5312.45ms | 4506446 | 40 | 4.39739e+10 | 7.00925e+06 | 0.165201 | 8.2518 | 32.1963 | 6.6987 | 0.0316353 | 0.0821893 | 0.000541497 | 1(Win) | true |
| simdjson (ondemand) | 446.737 | 0.508531 | 7150.22ms | 4506446 | 30 | 7.17992e+10 | 9.62015e+06 | 0.0768503 | 11.3215 | 51.2341 | 9.82499 | 0.0196813 | 0.0874978 | 0.000825721 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2095.05 | 0.845607 | 6743.14ms | 4219120 | 30 | 7.91248e+09 | 1.92056e+06 | 0.0203597 | 2.41073 | 8.83772 | 1.47936 | 0.0116476 | 0.0569984 | 0.000499678 | 1(Win) | true |
| simdjson (ondemand) | 1849.59 | 0.706495 | 7471.43ms | 4219120 | 160 | 3.77948e+10 | 2.17544e+06 | 0.157353 | 2.72298 | 8.88813 | 1.46044 | 0.0153402 | 0.0546861 | 0.000450867 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 715.578 | 0.771981 | 4116.55ms | 4219120 | 30 | 5.6528e+10 | 5.62296e+06 | 0.00991332 | 7.06508 | 27.881 | 5.19 | 0.0193775 | 0.0577272 | 0.000137928 | 1(Win) | true |
| simdjson (ondemand) | 228.49 | 0.240621 | 5375.47ms | 4219120 | 30 | 5.38638e+10 | 1.76098e+07 | 0.0482016 | 22.0053 | 81.4439 | 16.4482 | 0.12549 | 0.0565353 | 0.000625707 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1821.22 | 0.702418 | 7573.35ms | 4219119 | 160 | 3.85328e+10 | 2.20933e+06 | 0.153254 | 2.77678 | 10.1434 | 1.86844 | 0.0133297 | 0.0555045 | 0.000106311 | 1(Win) | true |
| simdjson (ondemand) | 1557.93 | 0.721409 | 4251ms | 4219119 | 80 | 2.77715e+10 | 2.58269e+06 | 0.278749 | 3.22591 | 10.9255 | 1.88276 | 0.0164113 | 0.0547414 | 6.29989e-05 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 722.227 | 0.585874 | 4070.41ms | 4219119 | 40 | 4.26153e+10 | 5.57119e+06 | 0.0846017 | 7.02744 | 27.1791 | 5.32824 | 0.0199934 | 0.0572961 | 0.00736686 | 1(Win) | true |
| simdjson (ondemand) | 222.648 | 0.202195 | 5502.38ms | 4219119 | 30 | 4.00561e+10 | 1.80718e+07 | 0.198037 | 22.5518 | 83.4811 | 16.8704 | 0.128439 | 0.0573037 | 0.0013484 | 2(Loss) | true |
