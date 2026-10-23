# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 249.32 | 0.057434 | 1099.22ms | 905 | 640 | 2529.88 | 3461.72 | 0.226919 | 20.1367 | 60.6895 | 7.90387 | 0.0530456 | 0.000143301 | 1.72652e-06 | 1(Win) | true |
| simdjson (ondemand) | 184.884 | 0.0351622 | 1203.26ms | 905 | 4890 | 13175.2 | 4668.19 | 0.150333 | 27.4858 | 102.641 | 10.2663 | 0.0689026 | 0.000201561 | 5.21981e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 235.24 | 0.0620011 | 1105.37ms | 905 | 160 | 827.929 | 3668.91 | 0.0112444 | 21.3339 | 60.032 | 7.67293 | 0.063605 | 4.83425e-05 | 1.38122e-05 | 1(Win) | true |
| simdjson (ondemand) | 182.252 | 0.0966287 | 1205.41ms | 905 | 80 | 1675.15 | 4735.61 | 0.0705263 | 27.4606 | 101.966 | 10.1271 | 0.0714779 | 6.90608e-05 | 4.14365e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 350.897 | 0.0410166 | 1236.5ms | 1811 | 2560 | 10433.7 | 4921.97 | 0.136398 | 14.4275 | 44.0569 | 7.037 | 0.000600497 | 0.000190459 | 8.56312e-05 | 1(Win) | true |
| simdjson (ondemand) | 233.528 | 0.0783372 | 1476.33ms | 1811 | 40 | 1342.63 | 7395.7 | 0.0297559 | 21.366 | 75.7802 | 9.62231 | 0.0064053 | 2.76091e-05 | 2.76091e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 356.451 | 0.0285659 | 1228.43ms | 1811 | 4890 | 9367.88 | 4845.28 | 0.0231944 | 14.0976 | 42.9757 | 6.79735 | 0.00111554 | 0.000137763 | 5.07013e-05 | 1(Win) | true |
| simdjson (ondemand) | 242.955 | 0.0604919 | 1447.5ms | 1811 | 30 | 554.754 | 7108.73 | 0.0807171 | 20.9384 | 74.6897 | 9.38266 | 0.00079146 | 7.36241e-05 | 0 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 701.559 | 0.0590292 | 1262.72ms | 3862 | 1280 | 12292.5 | 5249.87 | 0.0915742 | 7.23306 | 19.6559 | 2.39487 | 0.000269857 | 0.000134928 | 6.14966e-05 | 1(Win) | true |
| simdjson (ondemand) | 530.935 | 0.0303082 | 1437ms | 3862 | 4890 | 21615.8 | 6936.99 | 0.169532 | 9.50396 | 31.5111 | 3.40394 | 0.00643293 | 0.000119141 | 6.70896e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 706.754 | 0.0590371 | 1251.71ms | 3862 | 40 | 378.615 | 5211.27 | 0.0904307 | 7.08138 | 19.1163 | 2.26903 | 0.000258933 | 7.768e-05 | 1.942e-05 | 1(Win) | true |
| simdjson (ondemand) | 535.157 | 0.027366 | 1431.39ms | 3862 | 4890 | 17345.8 | 6882.26 | 0.0787379 | 9.43748 | 31.0137 | 3.297 | 0.00806934 | 5.94117e-05 | 3.33595e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1114.86 | 0.0276443 | 1568.27ms | 9578 | 4890 | 25085.8 | 8193.21 | 0.32385 | 4.52576 | 17.677 | 3.22385 | 0.00113252 | 6.09141e-05 | 3.49941e-05 | 1(Win) | true |
| simdjson (ondemand) | 1058.39 | 0.14611 | 1603.11ms | 9578 | 640 | 101764 | 8630.33 | 0.0266069 | 4.69803 | 18.8332 | 2.96074 | 0.00311407 | 5.79127e-05 | 3.81734e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1395.72 | 0.103984 | 1535.24ms | 9578 | 320 | 14819.4 | 6544.49 | 0.230974 | 3.64331 | 13.6207 | 2.30476 | 0.000332794 | 2.38176e-05 | 1.23982e-05 | 1(Win) | true |
| simdjson (ondemand) | 1327.11 | 0.0978139 | 1570.61ms | 9578 | 1280 | 58016 | 6882.86 | 0.348861 | 3.77087 | 14.7393 | 2.03466 | 0.00174032 | 3.09139e-05 | 1.28876e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 795.796 | 0.0407903 | 1203.83ms | 3873 | 4890 | 17527.3 | 4641.37 | 0.0120923 | 6.37828 | 19.1312 | 2.36819 | 0.0021281 | 0.000112678 | 5.96125e-05 | 1(Win) | true |
| simdjson (ondemand) | 534.685 | 0.0489587 | 1427.88ms | 3873 | 2560 | 29281.8 | 6907.95 | 0.0830915 | 9.44527 | 31.2523 | 3.5164 | 0.0104711 | 9.87405e-05 | 4.77061e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 817.281 | 0.0535495 | 1189.02ms | 3873 | 2560 | 14993.5 | 4519.35 | 0.0644294 | 6.21568 | 18.6352 | 2.2582 | 0.00239236 | 9.80345e-05 | 6.29357e-05 | 1(Win) | true |
| simdjson (ondemand) | 540.452 | 0.0318607 | 1418.03ms | 3873 | 4890 | 23184.7 | 6834.25 | 0.0176258 | 9.37804 | 30.7563 | 3.40976 | 0.0135115 | 9.76822e-05 | 5.99293e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 775.41 | 0.193005 | 7992.08ms | 2090234 | 160 | 3.93898e+09 | 2.57077e+06 | 0.190129 | 6.46857 | 30.5702 | 5.61885 | 0.0231334 | 0.104212 | 0.00128007 | 1(Win) | true |
| jsonifier (generic) | 725.467 | 0.132249 | 4153.29ms | 2090234 | 40 | 5.28198e+08 | 2.74775e+06 | 0.911479 | 6.92069 | 31.7631 | 6.33343 | 0.0223846 | 0.104053 | 0.00213905 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 911.713 | 0.208012 | 8033.2ms | 2090234 | 160 | 3.30955e+09 | 2.18644e+06 | 0.148838 | 5.49576 | 25.2505 | 4.35288 | 0.0220676 | 0.078706 | 0.00172367 | 1(Win) | true |
| jsonifier (generic) | 835.855 | 0.222912 | 4177.18ms | 2090234 | 80 | 2.26092e+09 | 2.38487e+06 | 0.0245462 | 5.99378 | 26.443 | 5.06735 | 0.021485 | 0.0786712 | 0.00168977 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2262.17 | 0.421727 | 4231.32ms | 6661897 | 80 | 1.12228e+10 | 2.80849e+06 | 0.0429993 | 2.21881 | 10.5069 | 1.80195 | 0.00650024 | 0.0551433 | 0.00616737 | 1(Win) | true |
| jsonifier (generic) | 2113.73 | 0.118207 | 4552.29ms | 6661897 | 80 | 1.00988e+09 | 3.00572e+06 | 0.203075 | 2.37803 | 10.8523 | 2.02964 | 0.00641504 | 0.054573 | 0.00314559 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2494.88 | 2.86502 | 4336.12ms | 6661897 | 40 | 2.12919e+11 | 2.54653e+06 | 1.47799 | 2.00102 | 8.84154 | 1.40544 | 0.00619175 | 0.0471754 | 0.00616881 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2448.69 | 0.132789 | 4521.2ms | 6661897 | 40 | 4.74802e+08 | 2.59457e+06 | 0.201012 | 2.06657 | 9.18204 | 1.63217 | 0.0060954 | 0.0463919 | 0.00208041 | 1(Tie) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 662.86 | 0.0728544 | 4529.05ms | 2090234 | 80 | 3.84015e+08 | 3.00728e+06 | 0.0332945 | 7.6018 | 37.6421 | 7.97685 | 0.0239595 | 0.181589 | 0.000932025 | 1(Win) | true |
| jsonifier (generic) | 636.493 | 0.264449 | 4717.71ms | 2090234 | 80 | 5.48751e+09 | 3.13185e+06 | 0.0752542 | 7.89451 | 37.13 | 7.47398 | 0.0233618 | 0.180818 | 0.000576915 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 757.855 | 0.0614294 | 4554.04ms | 2090234 | 80 | 2.08862e+08 | 2.63032e+06 | 0.668722 | 6.65499 | 32.3306 | 6.71247 | 0.0229459 | 0.155686 | 0.00212576 | 1(Win) | true |
| jsonifier (generic) | 722.3 | 0.144331 | 4700ms | 2090234 | 40 | 6.34648e+08 | 2.7598e+06 | 0.243495 | 6.94524 | 31.8075 | 6.2072 | 0.0228912 | 0.156144 | 0.00054214 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1908.94 | 1.16556 | 5076.79ms | 6661897 | 30 | 4.51444e+10 | 3.32817e+06 | 0.213003 | 2.64302 | 12.7334 | 2.54338 | 0.00667085 | 0.111076 | 0.000892433 | 1(Win) | true |
| jsonifier (generic) | 1831.16 | 0.61693 | 5306.2ms | 6661897 | 30 | 1.37447e+10 | 3.46953e+06 | 0.20549 | 2.75735 | 12.5254 | 2.38526 | 0.00677058 | 0.111786 | 0.00110274 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2150.34 | 0.765352 | 5003.9ms | 6661897 | 40 | 2.04534e+10 | 2.95455e+06 | 1.51324 | 2.32037 | 11.0636 | 2.14604 | 0.0063887 | 0.102935 | 0.000643822 | 1(Win) | true |
| jsonifier (generic) | 2045.57 | 0.680701 | 5335.48ms | 6661897 | 80 | 3.57576e+10 | 3.10587e+06 | 1.91019 | 2.46792 | 10.8653 | 1.98986 | 0.00643694 | 0.103667 | 0.000492309 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6831.28 | 0.247068 | 7732.56ms | 2090234 | 80 | 4.15825e+07 | 291805 | 0.135173 | 0.728412 | 3.67025 | 0.46371 | 0.00297619 | 0.0509014 | 2.75687e-06 | 1(Win) | true |
| simdjson (ondemand) | 5895.45 | 0.108799 | 4450.37ms | 2090234 | 320 | 4.33064e+07 | 338125 | 0.0298968 | 0.851891 | 4.24003 | 0.805091 | 0.00277018 | 0.0484561 | 3.96038e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6879.85 | 0.507171 | 7752.75ms | 2090234 | 80 | 1.72755e+08 | 289745 | 0.312006 | 0.730206 | 3.67017 | 0.463693 | 0.00299983 | 0.0508194 | 2.79275e-06 | 1(Win) | true |
| simdjson (ondemand) | 5884.57 | 0.33656 | 4407.19ms | 2090234 | 160 | 2.07972e+08 | 338750 | 0.160856 | 0.85817 | 4.23996 | 0.805073 | 0.00286588 | 0.048333 | 2.02728e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12386.3 | 0.255974 | 6611.14ms | 6661897 | 160 | 2.75821e+08 | 512930 | 0.0564248 | 0.406577 | 1.92237 | 0.170588 | 0.000448664 | 0.0376975 | 2.25818e-06 | 1(Win) | true |
| simdjson (ondemand) | 11285.5 | 0.0607432 | 7312.23ms | 6661897 | 640 | 7.4839e+07 | 562959 | 0.20293 | 0.447593 | 2.24967 | 0.292442 | 0.000415425 | 0.0376992 | 9.42018e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12485.8 | 0.0753799 | 6644.21ms | 6661897 | 320 | 4.70784e+07 | 508839 | 0.189054 | 0.405143 | 1.92234 | 0.170582 | 0.000447704 | 0.0376818 | 3.49797e-06 | 1(Win) | true |
| simdjson (ondemand) | 11350.5 | 0.0906118 | 7271.08ms | 6661897 | 40 | 1.02895e+07 | 559735 | 0.245304 | 0.44421 | 2.24964 | 0.292437 | 0.000418953 | 0.037693 | 4.36437e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4892.19 | 0.209226 | 5288.74ms | 2090234 | 320 | 2.32575e+08 | 407467 | 0.0543154 | 1.02907 | 5.65619 | 0.850459 | 0.00344707 | 0.076908 | 4.12783e-06 | 1(Win) | true |
| simdjson (ondemand) | 3935.71 | 0.243396 | 6507.46ms | 2090234 | 30 | 4.55925e+07 | 506491 | 0.266918 | 1.2832 | 6.77352 | 1.63171 | 0.00366664 | 0.0766839 | 2.37613e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4872.76 | 0.231532 | 5324.05ms | 2090234 | 640 | 5.74171e+08 | 409091 | 0.512088 | 1.03261 | 5.65611 | 0.850441 | 0.0034026 | 0.0768664 | 2.91086e-06 | 1(Win) | true |
| simdjson (ondemand) | 3947.05 | 0.341109 | 6537.61ms | 2090234 | 320 | 9.49688e+08 | 505036 | 0.359352 | 1.27541 | 6.77344 | 1.63169 | 0.00290135 | 0.0766952 | 2.94524e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9415.88 | 0.263371 | 4315.23ms | 6661897 | 320 | 1.01056e+09 | 674741 | 0.0308806 | 0.533303 | 2.54548 | 0.291934 | 0.00056191 | 0.0564781 | 2.07195e-06 | 1(Win) | true |
| simdjson (ondemand) | 8674.89 | 0.399213 | 4681.14ms | 6661897 | 160 | 1.36772e+09 | 732376 | 0.113086 | 0.582206 | 3.04457 | 0.5518 | 0.000464567 | 0.0565352 | 3.56224e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9416.48 | 0.398266 | 4327.31ms | 6661897 | 160 | 1.15528e+09 | 674698 | 0.041241 | 0.533096 | 2.54545 | 0.291928 | 0.000587 | 0.056477 | 1.32657e-06 | 1(Win) | true |
| simdjson (ondemand) | 8623.19 | 0.323188 | 4702.77ms | 6661897 | 320 | 1.81435e+09 | 736767 | 0.100182 | 0.584563 | 3.04455 | 0.551795 | 0.000454761 | 0.0565183 | 4.31137e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1255.9 | 0.445915 | 4990.07ms | 500299 | 30 | 8.60946e+07 | 379905 | 0.0610569 | 4.01895 | 16.636 | 3.08948 | 0.0168219 | 0.0122977 | 6.5161e-05 | 1(Win) | true |
| simdjson (ondemand) | 1167.34 | 0.161931 | 5322.09ms | 500299 | 320 | 1.40176e+08 | 408727 | 0.261482 | 4.30517 | 16.671 | 2.81827 | 0.0247539 | 0.013903 | 9.21449e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1413.2 | 0.145347 | 4829.62ms | 500299 | 320 | 7.70576e+07 | 337618 | 0.394593 | 3.56668 | 15.5029 | 2.81767 | 0.0112314 | 0.00970457 | 4.33616e-05 | 1(Win) | true |
| simdjson (ondemand) | 1308.44 | 0.17018 | 5190.86ms | 500299 | 320 | 1.2323e+08 | 364649 | 0.0194163 | 3.8245 | 15.5463 | 2.54956 | 0.0190324 | 0.0105281 | 4.7659e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3103.33 | 0.305057 | 5720.62ms | 1439562 | 320 | 5.82798e+08 | 442388 | 0.0600709 | 1.61983 | 6.68832 | 1.1078 | 0.00607725 | 0.0432333 | 4.71367e-05 | 1(Win) | true |
| simdjson (ondemand) | 2950.72 | 0.224759 | 6031.12ms | 1439562 | 320 | 3.49938e+08 | 465267 | 0.0194917 | 1.70956 | 6.73341 | 1.02065 | 0.00896549 | 0.0426782 | 1.74467e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3469.59 | 0.200792 | 5579.24ms | 1439562 | 640 | 4.03997e+08 | 395687 | 0.180364 | 1.44627 | 6.29269 | 1.01292 | 0.00425748 | 0.0390807 | 1.25678e-05 | 1(Win) | true |
| simdjson (ondemand) | 3269.92 | 0.191676 | 5893.82ms | 1439562 | 320 | 2.0724e+08 | 419850 | 0.288322 | 1.53993 | 6.34232 | 0.927241 | 0.00715797 | 0.0392374 | 1.65024e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 406.969 | 0.138419 | 7456.38ms | 500299 | 80 | 2.10679e+08 | 1.17238e+06 | 0.000131143 | 12.404 | 47.0041 | 10.6625 | 0.0600936 | 0.0270064 | 0.000203953 | 1(Win) | true |
| simdjson (ondemand) | 228.577 | 0.154087 | 9202.64ms | 500299 | 40 | 4.13793e+08 | 2.08736e+06 | 0.26281 | 22.0145 | 91.4683 | 26.0297 | 0.0957524 | 0.0191853 | 0.001424 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 422.833 | 0.128852 | 7394.54ms | 500299 | 160 | 3.38242e+08 | 1.12839e+06 | 0.0170451 | 11.8844 | 45.8675 | 10.3927 | 0.0532814 | 0.0215314 | 0.000205215 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 213.191 | 1.03658 | 4536.54ms | 500299 | 40 | 2.15271e+10 | 2.238e+06 | 5.93704 | 23.2363 | 90.3423 | 25.7619 | 0.0925539 | 0.0428656 | 0.0181111 | -(Loss) | false |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) DID NOT CONVERGE | 618.272 | 0.114454 | 6375.89ms | 1439562 | 30 | 1.9377e+08 | 2.2205e+06 | 21.227 | 8.14101 | 17.2293 | 3.73504 | 0.0213713 | 0.100667 | 0.00888569 | -(Win) | false |
| simdjson (ondemand) DID NOT CONVERGE | 398.632 | 1.94805 | 5278.32ms | 1439562 | 80 | 3.60087e+11 | 3.44396e+06 | 3.11875 | 12.6345 | 32.708 | 9.08206 | 0.0301384 | 0.173184 | 0.0182713 | -(Loss) | false |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 790.369 | 2.80195 | 7063.92ms | 1439562 | 30 | 7.1063e+10 | 1.737e+06 | 2.49681 | 5.16952 | 16.8349 | 3.64155 | 0.0195953 | 0.0839521 | 0.010072 | 1(Win) | true |
| simdjson (ondemand) | 448.987 | 1.92534 | 5170.67ms | 1439562 | 80 | 2.77267e+11 | 3.05771e+06 | 1.59545 | 11.2302 | 32.315 | 8.98866 | 0.0279149 | 0.176729 | 0.012352 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2851.65 | 0.523403 | 4615.52ms | 500299 | 1280 | 9.81635e+08 | 167315 | 0.330123 | 1.75847 | 5.04125 | 0.812415 | 0.00142338 | 0.00383847 | 0.00112859 | 1(Win) | true |
| simdjson (ondemand) | 2088.46 | 1.35387 | 6078.82ms | 500299 | 30 | 2.87e+08 | 228457 | 0.876281 | 2.3735 | 7.17648 | 1.44723 | 0.00348265 | 0.0090923 | 0.00145806 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2795.94 | 0.218527 | 4572.75ms | 500299 | 160 | 2.22502e+07 | 170648 | 1.63524 | 1.80508 | 5.01676 | 0.808577 | 0.0018467 | 0.00255222 | 0.00159116 | 1(Win) | true |
| simdjson (ondemand) | 2039.4 | 0.435149 | 5969.48ms | 500299 | 640 | 6.63299e+08 | 233952 | 0.525469 | 2.48394 | 7.1523 | 1.44338 | 0.0028024 | 0.0183826 | 0.000404233 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5471 | 0.314331 | 6620.86ms | 1439562 | 1280 | 7.96364e+08 | 250936 | 0.0615974 | 0.915507 | 2.60809 | 0.309099 | 0.00103069 | 0.0274054 | 0.000202713 | 1(Win) | true |
| simdjson (ondemand) | 4718.83 | 0.585577 | 7416.08ms | 1439562 | 640 | 1.85755e+09 | 290935 | 0.268016 | 1.0611 | 3.43189 | 0.543714 | 0.00161137 | 0.0293191 | 0.000172382 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5492.06 | 0.686755 | 6598.56ms | 1439562 | 160 | 4.71535e+08 | 249974 | 0.329806 | 0.90731 | 2.59958 | 0.307765 | 0.00145096 | 0.0297015 | 0.000169214 | 1(Win) | true |
| simdjson (ondemand) | 5014.46 | 0.690337 | 7698.75ms | 1439562 | 80 | 2.85775e+08 | 273783 | 1.38535 | 0.990436 | 3.42348 | 0.542374 | 0.00149643 | 0.0261935 | 0.000203604 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1583.01 | 0.260724 | 4059.43ms | 500299 | 320 | 1.97607e+08 | 301402 | 0.219304 | 3.14581 | 10.4686 | 2.04342 | 0.00554723 | 0.00949785 | 0.00135247 | 1(Win) | true |
| simdjson (ondemand) | 1135.15 | 0.542411 | 5692.89ms | 500299 | 640 | 3.32653e+09 | 420317 | 0.358899 | 4.38616 | 14.0585 | 3.67679 | 0.0102098 | 0.0176981 | 0.00173755 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2072.97 | 0.487768 | 4436.43ms | 500299 | 40 | 5.04152e+07 | 230164 | 0.443697 | 2.39591 | 10.4442 | 2.03958 | 0.00311439 | 0.00155132 | 0.001512 | 1(Win) | true |
| simdjson (ondemand) | 1039.64 | 1.14175 | 5509.16ms | 500299 | 40 | 1.09825e+09 | 458932 | 0.288079 | 4.81951 | 14.0343 | 3.67293 | 0.0113538 | 0.0147414 | 0.00239932 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3258.19 | 1.57743 | 5572.47ms | 1439562 | 80 | 3.53426e+09 | 421361 | 0.968978 | 1.53712 | 4.4943 | 0.736917 | 0.00224837 | 0.0325483 | 0.000226857 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2403.81 | 0.327881 | 7095.25ms | 1439562 | 640 | 2.24426e+09 | 571124 | 4.69451 | 2.06744 | 5.82365 | 1.31857 | 0.00411335 | 0.0372858 | 0.000294024 | -(Loss) | false |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3415.25 | 0.626191 | 5472.32ms | 1439562 | 320 | 2.02759e+09 | 401984 | 2.05347 | 1.45573 | 4.4858 | 0.735584 | 0.00201913 | 0.034889 | 0.000131064 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2400.82 | 0.669148 | 7049.1ms | 1439562 | 160 | 2.34265e+09 | 571836 | 3.18037 | 2.06646 | 5.81524 | 1.31723 | 0.00393758 | 0.0353547 | 0.0002696 | -(Loss) | false |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 859.588 | 0.147863 | 7577.08ms | 56369 | 4890 | 4.18144e+07 | 62538.9 | 1.05915 | 5.81571 | 14.7143 | 2.63155 | 0.013346 | 0.00392579 | 0.00268542 | 1(Win) | true |
| jsonifier (generic) | 839.395 | 0.16146 | 7547.44ms | 56369 | 4890 | 5.22864e+07 | 64043.3 | 0.138131 | 5.94508 | 14.3243 | 2.76296 | 0.0126829 | 0.00444476 | 0.00260706 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 970.354 | 0.40277 | 6705.13ms | 56369 | 320 | 1.59326e+07 | 55400.1 | 2.14098 | 5.13866 | 12.2185 | 2.33315 | 0.00824894 | 0.00191423 | 0.00146496 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 966.353 | 0.364266 | 6970.63ms | 56369 | 160 | 6.57004e+06 | 55629.5 | 0.598716 | 5.1529 | 12.64 | 2.20912 | 0.0144056 | 0.00170883 | 0.00138307 | 1(Tie) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1335.37 | 0.286415 | 4493.7ms | 94370 | 2560 | 9.5388e+07 | 67395.5 | 0.673726 | 3.6652 | 9.37859 | 1.59691 | 0.00894305 | 0.00190171 | 0.00148841 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 1331.83 | 0.151549 | 7997.01ms | 94370 | 4890 | 5.12847e+07 | 67574.9 | 0.941098 | 3.74321 | 9.16498 | 1.6694 | 0.00706141 | 0.00296191 | 0.00181158 | 1(Tie) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2143.53 | 1.00467 | 7430.08ms | 94370 | 320 | 5.69379e+07 | 41985.9 | 0.503374 | 2.31031 | 7.89974 | 1.41043 | 0.00436377 | 0.000776299 | 0.000694739 | 1(Win) | true |
| simdjson (ondemand) | 1521.45 | 0.246375 | 7900.89ms | 94370 | 1280 | 2.71866e+07 | 59152.9 | 1.8159 | 3.23633 | 8.14358 | 1.34535 | 0.00870763 | 0.00119687 | 0.000895817 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 270.143 | 1.07475 | 6060.81ms | 56369 | 80 | 3.65931e+08 | 198997 | 0.63987 | 18.3413 | 44.5452 | 9.31846 | 0.043078 | 0.017303 | 0.00866412 | 1(Win) | true |
| simdjson (ondemand) | 67.5541 | 0.953046 | 4686.29ms | 56369 | 40 | 2.30073e+09 | 795772 | 0.664101 | 73.9126 | 196.925 | 60.0423 | 0.263704 | 0.0448141 | 0.0201405 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 294.856 | 0.538836 | 4735.28ms | 56369 | 320 | 3.08832e+08 | 182318 | 1.79101 | 16.7806 | 42.4261 | 8.88072 | 0.0383693 | 0.0080681 | 0.00476708 | 1(Win) | true |
| simdjson (ondemand) | 67.746 | 1.673 | 5083.31ms | 56369 | 40 | 7.04965e+09 | 793518 | 0.254932 | 73.5502 | 194.84 | 59.6161 | 0.231728 | 0.0259513 | 0.0122869 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 762.065 | 0.221998 | 5521.37ms | 94370 | 80 | 5.49887e+06 | 118098 | 0.194217 | 6.49652 | 27.1534 | 5.56298 | 0.0143147 | 0.00255908 | 0.00249868 | 1(Win) | true |
| simdjson (ondemand) | 178.228 | 1.74211 | 4260.59ms | 94370 | 40 | 3.09545e+09 | 504960 | 1.4015 | 28.2544 | 117.999 | 35.8358 | 0.0937295 | 0.0101693 | 0.00943706 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 495.033 | 0.6559 | 5231.11ms | 94370 | 30 | 4.26575e+07 | 181803 | 1.5122 | 10.0707 | 25.8982 | 5.30415 | 0.0224075 | 0.00358518 | 0.0029681 | 1(Win) | true |
| simdjson (ondemand) | 123.337 | 1.34098 | 4577.39ms | 94370 | 320 | 3.0639e+10 | 729695 | 2.43565 | 40.3091 | 116.752 | 35.5801 | 0.105147 | 0.0141408 | 0.00754941 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2015.35 | 0.0340793 | 3422.96ms | 56369 | 2560 | 211544 | 26674.1 | 0.0284224 | 2.48545 | 10.4067 | 2.00744 | 0.00503799 | 4.15718e-05 | 2.99089e-05 | 1(Win) | true |
| jsonifier (generic) | 1325.93 | 0.535849 | 4702.73ms | 56369 | 40 | 1.88794e+06 | 40543.5 | 1.24352 | 3.73016 | 10.1954 | 1.77387 | 0.00420311 | 0.00192836 | 0.00136644 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2684.29 | 0.0397312 | 3063.53ms | 56369 | 1280 | 81039.3 | 20026.8 | 0.0544014 | 1.85068 | 8.62896 | 1.44949 | 0.00192899 | 1.47189e-05 | 9.54924e-06 | 1(Win) | true |
| simdjson (ondemand) | 2465.59 | 0.0324119 | 3222.95ms | 56369 | 4890 | 244206 | 21803.2 | 0.0323404 | 2.02189 | 8.85577 | 1.68745 | 0.00271898 | 2.66213e-05 | 1.91769e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3357.32 | 0.194507 | 3435.12ms | 94370 | 1280 | 3.47988e+06 | 26806.6 | 0.17629 | 1.49495 | 6.67592 | 1.07237 | 0.00173636 | 3.49936e-05 | 2.39831e-05 | 1(Win) | true |
| simdjson (ondemand) | 3116.35 | 0.022962 | 3645.77ms | 94370 | 2560 | 112573 | 28879.4 | 0.115324 | 1.59438 | 6.79923 | 1.2237 | 0.00282243 | 3.29984e-05 | 2.51917e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4063.06 | 0.0362406 | 3274.93ms | 94370 | 2560 | 164965 | 22150.3 | 0.0817004 | 1.23781 | 5.74971 | 0.880863 | 0.00125762 | 2.06013e-05 | 1.57252e-05 | 1(Win) | true |
| simdjson (ondemand) | 3769.28 | 0.0951213 | 3405.24ms | 94370 | 320 | 165066 | 23876.8 | 0.0740756 | 1.32096 | 5.87612 | 1.03308 | 0.00152697 | 2.14581e-05 | 1.63916e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1288.45 | 0.0232075 | 4922.97ms | 56369 | 4890 | 458472 | 41722.8 | 0.10266 | 3.90537 | 17.3384 | 3.76396 | 0.00943923 | 9.01052e-05 | 7.01411e-05 | 1(Win) | true |
| simdjson (ondemand) | 1187.89 | 0.209786 | 5270.36ms | 56369 | 30 | 270397 | 45254.7 | 0.024018 | 4.25385 | 18.1574 | 4.06347 | 0.0130828 | 8.57445e-05 | 4.73073e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1449.71 | 0.0219176 | 4750.33ms | 56369 | 4890 | 323009 | 37081.7 | 0.00985548 | 3.48206 | 15.7789 | 3.44219 | 0.00812817 | 6.74311e-05 | 5.55281e-05 | 1(Win) | true |
| simdjson (ondemand) | 1320.7 | 0.0316125 | 5119.7ms | 56369 | 1280 | 211934 | 40703.8 | 0.10289 | 3.82169 | 16.6218 | 3.74804 | 0.0121205 | 2.00687e-05 | 9.47994e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2063.18 | 0.0186128 | 5111.88ms | 94370 | 4890 | 322350 | 43621.1 | 0.179691 | 2.43515 | 10.8924 | 2.24191 | 0.00556373 | 1.98496e-05 | 1.15717e-05 | 1(Win) | true |
| simdjson (ondemand) | 1945.85 | 0.0350893 | 5378.24ms | 94370 | 2560 | 674278 | 46251.4 | 0.107494 | 2.59505 | 11.3147 | 2.42536 | 0.00733062 | 2.3536e-05 | 1.37383e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2315.44 | 0.0407562 | 4911.4ms | 94370 | 1280 | 321217 | 38868.8 | 0.0122754 | 2.16768 | 9.95987 | 2.04923 | 0.00480799 | 1.70125e-05 | 1.2393e-05 | 1(Win) | true |
| simdjson (ondemand) | 2140.72 | 0.0304567 | 5236.65ms | 94370 | 640 | 104928 | 42041.1 | 0.0748039 | 2.36206 | 10.3975 | 2.23691 | 0.00731562 | 1.75009e-05 | 1.24344e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1256.11 | 0.0663512 | 1636.73ms | 11812 | 2560 | 90642.3 | 8968.02 | 0.0121497 | 4.03412 | 17.0251 | 3.10477 | 0.00491019 | 0.000129073 | 7.11009e-05 | 1(Win) | true |
| simdjson (ondemand) | 1107.03 | 0.0273807 | 1759.12ms | 11812 | 4890 | 37960.1 | 10175.7 | 0.0246085 | 4.57331 | 18.3738 | 3.36649 | 0.00695882 | 8.11452e-05 | 4.5602e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1362.13 | 0.0798059 | 1620.59ms | 11812 | 640 | 27877.8 | 8269.98 | 0.026142 | 3.72562 | 16.1071 | 2.89578 | 0.00429965 | 2.10326e-05 | 6.74632e-06 | 1(Win) | true |
| simdjson (ondemand) | 1195.63 | 0.0342189 | 1735.52ms | 11812 | 2560 | 26608.8 | 9421.65 | 0.0517075 | 4.24277 | 17.3339 | 3.13342 | 0.00627143 | 2.95647e-05 | 1.2732e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2987.39 | 0.102764 | 1735.68ms | 31235 | 40 | 4199.94 | 9971.25 | 0.0228939 | 1.69974 | 7.37151 | 1.21146 | 0.00172803 | 2.48119e-05 | 4.00192e-06 | 1(Win) | true |
| simdjson (ondemand) | 2643.32 | 0.0326744 | 1877.78ms | 31235 | 4890 | 66299.1 | 11269.2 | 0.244102 | 1.91314 | 7.84605 | 1.31598 | 0.00276729 | 1.83515e-05 | 8.23626e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3208.52 | 0.185478 | 1716.01ms | 31235 | 40 | 11860.9 | 9284.05 | 0.153005 | 1.57939 | 6.97484 | 1.12214 | 0.00184328 | 3.52169e-05 | 2.48119e-05 | 1(Win) | true |
| simdjson (ondemand) | 2831.97 | 0.0448722 | 1845.39ms | 31235 | 1280 | 28514.8 | 10518.5 | 0.0637902 | 1.78734 | 7.44425 | 1.22564 | 0.00240796 | 8.92929e-06 | 2.75132e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 695.101 | 0.0861978 | 2368.32ms | 11812 | 1280 | 249777 | 16206 | 0.0366656 | 7.28522 | 32.0014 | 7.02172 | 0.0116711 | 6.46191e-05 | 2.47365e-05 | 1(Win) | true |
| simdjson (ondemand) | 578.166 | 0.0970911 | 2680.03ms | 11812 | 320 | 114512 | 19483.7 | 0.185273 | 8.65545 | 37.0329 | 8.67694 | 0.0173155 | 0.000118788 | 7.22253e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 728.446 | 0.061176 | 2358.38ms | 11812 | 40 | 3579.93 | 15464.1 | 0.0311376 | 6.96075 | 30.9804 | 6.79131 | 0.0113698 | 5.50288e-05 | 2.53979e-05 | 1(Win) | true |
| simdjson (ondemand) | 605.38 | 0.0744796 | 2659.98ms | 11812 | 40 | 7682.92 | 18607.8 | 0.055725 | 8.37228 | 36.0235 | 8.44988 | 0.0174568 | 7.40772e-05 | 5.29123e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1739.66 | 0.0298309 | 2456.43ms | 31235 | 2560 | 66792.2 | 17122.9 | 0.120428 | 2.89431 | 12.985 | 2.67061 | 0.00450047 | 2.46493e-05 | 1.23059e-05 | 1(Win) | true |
| simdjson (ondemand) | 1477.77 | 0.0422111 | 2758.78ms | 31235 | 2560 | 185336 | 20157.4 | 0.0722555 | 3.41509 | 14.7416 | 3.28791 | 0.00683642 | 2.12102e-05 | 9.35449e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1823.66 | 0.137828 | 2431.05ms | 31235 | 80 | 40547.3 | 16334.2 | 0.000918309 | 2.77675 | 12.5879 | 2.58108 | 0.0043657 | 1.08052e-05 | 4.40211e-06 | 1(Win) | true |
| simdjson (ondemand) | 1533.51 | 0.042955 | 2727.33ms | 31235 | 2560 | 178229 | 19424.8 | 0.0533927 | 3.29836 | 14.3582 | 3.20195 | 0.00691441 | 1.62953e-05 | 7.54112e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2224.46 | 0.0406726 | 1243.49ms | 11812 | 2560 | 10860.3 | 5064.07 | 0.00455127 | 2.29092 | 10.4167 | 1.89274 | 0.00210115 | 2.84073e-05 | 1.09462e-05 | 1(Win) | true |
| jsonifier (generic) | 2132.83 | 0.059001 | 1268ms | 11812 | 1280 | 12429.8 | 5281.62 | 0.169491 | 2.38673 | 10.6187 | 1.98535 | 0.00236114 | 1.885e-05 | 6.34948e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2274.04 | 0.0581294 | 1240.94ms | 11812 | 1280 | 10613.3 | 4953.65 | 0.17752 | 2.24029 | 10.2388 | 1.85058 | 0.00217939 | 1.70642e-05 | 2.51333e-06 | 1(Win) | true |
| jsonifier (generic) | 2186.72 | 0.0538124 | 1258.49ms | 11812 | 4890 | 37578.2 | 5151.47 | 0.00436097 | 2.32847 | 10.4411 | 1.94311 | 0.00238758 | 2.00829e-05 | 5.4016e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4798.92 | 0.0327239 | 1376.93ms | 31235 | 2560 | 10562.5 | 6207.24 | 0.0364942 | 1.05818 | 4.81284 | 0.753322 | 0.00107435 | 8.329e-06 | 2.48869e-06 | 1(Win) | true |
| jsonifier (generic) | 4762.03 | 0.0295814 | 1364.02ms | 31235 | 4890 | 16743.5 | 6255.32 | 0.0179879 | 1.06964 | 4.89172 | 0.782424 | 0.00100402 | 1.02397e-05 | 3.43069e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4910.27 | 0.0398905 | 1354.11ms | 31235 | 2560 | 14991.8 | 6066.48 | 0.222534 | 1.0372 | 4.74557 | 0.737378 | 0.00112858 | 6.71572e-06 | 2.75132e-06 | 1(Win) | true |
| jsonifier (generic) | 4849.45 | 0.0465489 | 1364.3ms | 31235 | 1280 | 10464.7 | 6142.55 | 0.0534788 | 1.0503 | 4.82456 | 0.766448 | 0.00102819 | 7.57864e-06 | 2.75132e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1787.6 | 0.102219 | 1372.86ms | 11812 | 640 | 26555.3 | 6301.65 | 0.202735 | 2.8544 | 13.884 | 2.71935 | 0.00252815 | 1.0847e-05 | 1.98421e-06 | 1(Win) | true |
| simdjson (ondemand) | 1607.73 | 0.0487358 | 1459.42ms | 11812 | 80 | 932.838 | 7006.65 | 0.0171237 | 3.16429 | 14.0654 | 2.99357 | 0.00618016 | 2.11649e-05 | 1.05825e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1809.36 | 0.0834792 | 1373.65ms | 11812 | 80 | 2160.96 | 6225.86 | 0.0620781 | 2.81349 | 13.7064 | 2.67711 | 0.00275673 | 2.11649e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (ondemand) | 1643.9 | 0.0645314 | 1431.89ms | 11812 | 320 | 6257.37 | 6852.51 | 0.0976789 | 3.09321 | 13.8873 | 2.95098 | 0.00571294 | 1.9313e-05 | 2.38105e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4021.56 | 0.063598 | 1480.75ms | 31235 | 640 | 14202.4 | 7407.08 | 0.0648449 | 1.26288 | 6.12656 | 1.06 | 0.00121158 | 1.02549e-05 | 2.95142e-06 | 1(Win) | true |
| simdjson (ondemand) | 3697.2 | 0.085754 | 1546.52ms | 31235 | 640 | 30551.1 | 8056.92 | 0.0845874 | 1.36967 | 6.19264 | 1.16962 | 0.00220316 | 1.18557e-05 | 2.35113e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4111.73 | 0.0579936 | 1480.6ms | 31235 | 160 | 2824.32 | 7244.64 | 0.304382 | 1.23703 | 6.05939 | 1.04402 | 0.00121478 | 5.80279e-06 | 1.20058e-06 | 1(Win) | true |
| simdjson (ondemand) | 3768.11 | 0.0435903 | 1539.54ms | 31235 | 4890 | 58066.3 | 7905.3 | 0.0759609 | 1.34807 | 6.12531 | 1.15351 | 0.00220873 | 8.24281e-06 | 2.22602e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1506.28 | 0.0752346 | 7619.42ms | 108313 | 4890 | 1.30165e+07 | 68576.3 | 0.0134576 | 3.34772 | 14.1807 | 2.35239 | 0.00692206 | 4.40422e-05 | 3.34522e-05 | 1(Win) | true |
| jsonifier (generic) | 1475.39 | 0.0755738 | 7761.2ms | 108313 | 4890 | 1.36899e+07 | 70012.4 | 0.0445904 | 3.41366 | 13.2614 | 2.6175 | 0.00418242 | 4.60341e-05 | 3.13792e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1617.07 | 0.0676575 | 7316.24ms | 108313 | 320 | 597706 | 63878.2 | 0.0576527 | 3.12145 | 13.5376 | 2.2163 | 0.00659706 | 4.84706e-06 | 1.93306e-06 | 1(Win) | true |
| jsonifier (generic) | 1581.31 | 0.0296507 | 7448.45ms | 108313 | 4890 | 1.83446e+06 | 65322.7 | 0.0821093 | 3.19105 | 12.6154 | 2.48146 | 0.00384789 | 2.0168e-05 | 1.47173e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2733.42 | 0.0235997 | 4208.37ms | 213963 | 2560 | 794544 | 74650.5 | 0.209759 | 1.84412 | 7.86991 | 1.21973 | 0.00414329 | 1.50234e-05 | 1.09631e-05 | 1(Win) | true |
| jsonifier (generic) | 2663.22 | 0.0283825 | 4294.31ms | 213963 | 2560 | 1.21061e+06 | 76618.2 | 0.050501 | 1.89634 | 7.52719 | 1.36935 | 0.00212278 | 1.74461e-05 | 1.19362e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2942.76 | 0.0558812 | 4009.3ms | 213963 | 640 | 960905 | 69340.1 | 0.038446 | 1.7107 | 7.5443 | 1.15085 | 0.00344212 | 1.1582e-05 | 8.4857e-06 | 1(Win) | true |
| jsonifier (generic) | 2824.56 | 0.0292437 | 4159.96ms | 213963 | 2560 | 1.14256e+06 | 72241.7 | 0.139258 | 1.78339 | 7.19915 | 1.30014 | 0.00186339 | 1.37126e-05 | 9.74906e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 446.133 | 0.0919725 | 6089.14ms | 108313 | 1280 | 5.8044e+07 | 231535 | 0.222256 | 11.2676 | 49.2249 | 10.2949 | 0.0177081 | 0.000236208 | 0.00017668 | 1(Win) | true |
| simdjson (ondemand) | 188.785 | 0.0470878 | 7043.98ms | 108313 | 640 | 4.2484e+07 | 547160 | 0.0951384 | 26.7109 | 119.788 | 33.368 | 0.0818005 | 6.7931e-05 | 4.77926e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 460.421 | 0.0347459 | 5978.13ms | 108313 | 640 | 3.889e+06 | 224350 | 0.056958 | 10.9519 | 48.5864 | 10.1624 | 0.0168885 | 6.38341e-05 | 5.06922e-05 | 1(Win) | true |
| simdjson (ondemand) | 191.846 | 0.0693164 | 6970.81ms | 108313 | 320 | 4.45737e+07 | 538429 | 0.0348132 | 26.2987 | 119.148 | 33.235 | 0.0791707 | 7.94572e-05 | 6.61566e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 852.049 | 0.0452897 | 6287.83ms | 213963 | 640 | 7.52883e+06 | 239483 | 0.0995974 | 5.9057 | 25.6767 | 5.23647 | 0.00987625 | 8.79825e-05 | 6.53661e-05 | 1(Win) | true |
| simdjson (ondemand) | 378.472 | 0.161392 | 6934.9ms | 213963 | 320 | 2.42283e+08 | 539144 | 0.0444639 | 13.2867 | 60.5871 | 16.745 | 0.0371143 | 0.000166399 | 0.000115426 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 876.29 | 0.0293629 | 6183.85ms | 213963 | 1280 | 5.98398e+06 | 232858 | 0.0128481 | 5.76254 | 25.3534 | 5.16933 | 0.00930622 | 5.32547e-05 | 3.89159e-05 | 1(Win) | true |
| simdjson (ondemand) | 383.701 | 0.120697 | 6871.85ms | 213963 | 160 | 6.59181e+07 | 531797 | 0.0951841 | 13.1277 | 60.2643 | 16.6781 | 0.0366765 | 5.5325e-05 | 4.51013e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4081.76 | 0.0275051 | 3270.84ms | 108313 | 2560 | 124032 | 25306.6 | 0.0100214 | 1.23668 | 5.9224 | 0.911488 | 0.00065127 | 1.0639e-05 | 7.03978e-06 | 1(Win) | true |
| simdjson (ondemand) | 3921.09 | 0.0149769 | 3377.26ms | 108313 | 4890 | 76120.1 | 26343.5 | 0.123974 | 1.28802 | 6.25066 | 1.09726 | 0.00177737 | 8.14877e-06 | 5.61691e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4226.51 | 0.0606942 | 3200.27ms | 108313 | 320 | 70411.3 | 24439.9 | 0.120594 | 1.19696 | 5.78436 | 0.881344 | 0.00050623 | 4.76051e-06 | 2.82745e-06 | 1(Win) | true |
| simdjson (ondemand) | 4028.75 | 0.0243935 | 3316.01ms | 108313 | 2560 | 100140 | 25639.6 | 0.203511 | 1.25353 | 6.11459 | 1.06696 | 0.00173395 | 6.23915e-06 | 4.23397e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6664.21 | 0.0241492 | 3817.04ms | 213963 | 2560 | 139967 | 30618.9 | 0.136432 | 0.757524 | 3.66982 | 0.479602 | 0.000344688 | 2.73667e-06 | 1.72708e-06 | 1(Win) | true |
| simdjson (ondemand) | 6535.76 | 0.0255351 | 3872.11ms | 213963 | 4890 | 310793 | 31220.7 | 0.247563 | 0.770889 | 3.84211 | 0.581633 | 0.000920575 | 4.04481e-06 | 2.59682e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6854.63 | 0.0184555 | 3733.23ms | 213963 | 4890 | 147594 | 29768.3 | 0.0217726 | 0.736404 | 3.60013 | 0.464379 | 0.000259742 | 3.522e-06 | 2.49551e-06 | 1(Win) | true |
| simdjson (ondemand) | 6721.85 | 0.0164872 | 3800.56ms | 213963 | 4890 | 122491 | 30356.4 | 0.0257681 | 0.751255 | 3.77343 | 0.566336 | 0.0008664 | 3.51149e-06 | 2.48691e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2580.34 | 0.0392098 | 4742.01ms | 108313 | 1280 | 315358 | 40031.6 | 0.014264 | 1.95685 | 10.0353 | 2.00574 | 0.00134303 | 1.37117e-05 | 1.03433e-05 | 1(Win) | true |
| simdjson (ondemand) | 2149.43 | 0.015097 | 5557.76ms | 108313 | 4890 | 257396 | 48057 | 0.0479109 | 2.34993 | 11.6353 | 2.70636 | 0.0033189 | 1.00123e-05 | 7.27083e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2640.25 | 0.0320682 | 4678.1ms | 108313 | 1280 | 201479 | 39123.3 | 0.0267153 | 1.91722 | 9.89849 | 1.97589 | 0.00115928 | 7.19847e-06 | 4.62346e-06 | 1(Win) | true |
| simdjson (ondemand) | 2176.02 | 0.162297 | 5477.83ms | 108313 | 80 | 474839 | 47469.8 | 0.312646 | 2.31296 | 11.5004 | 2.67641 | 0.00327108 | 2.88516e-06 | 8.07844e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4510.77 | 0.0277802 | 5274.89ms | 213963 | 2560 | 404286 | 45236.4 | 0.00491491 | 1.12216 | 5.74874 | 1.03237 | 0.000851817 | 4.2538e-06 | 2.1981e-06 | 1(Win) | true |
| simdjson (ondemand) | 3842.31 | 0.0383018 | 6036.05ms | 213963 | 1280 | 529591 | 53106.3 | 0.0457871 | 1.31248 | 6.55714 | 1.39356 | 0.00178033 | 5.12282e-06 | 2.83343e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4569.6 | 0.0234373 | 5228.59ms | 213963 | 2560 | 280398 | 44654 | 0.00863947 | 1.10547 | 5.67956 | 1.01728 | 0.000746603 | 3.20404e-06 | 1.59563e-06 | 1(Win) | true |
| simdjson (ondemand) | 3929.36 | 0.0937154 | 5946.8ms | 213963 | 320 | 757891 | 51929.9 | 0.134418 | 1.29234 | 6.48859 | 1.37832 | 0.00177166 | 8.63175e-06 | 7.08358e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 592.094 | 0.348054 | 4445.36ms | 1834197 | 30 | 3.17195e+09 | 2.95431e+06 | 0.248107 | 8.51679 | 34.832 | 6.27643 | 0.0468965 | 0.138722 | 0.000706394 | 1(Win) | true |
| jsonifier (generic) | 565.352 | 0.192155 | 4659.4ms | 1834197 | 30 | 1.06042e+09 | 3.09405e+06 | 0.0768828 | 8.86929 | 34.5201 | 7.22273 | 0.0424933 | 0.140069 | 0.00112474 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 644.532 | 0.245232 | 4427.71ms | 1834197 | 80 | 3.54361e+09 | 2.71395e+06 | 0.120072 | 7.88789 | 31.8369 | 5.5807 | 0.0456613 | 0.117976 | 0.00540263 | 1(Win) | true |
| jsonifier (generic) | 613.423 | 0.121962 | 4658.83ms | 1834197 | 80 | 9.67637e+08 | 2.85158e+06 | 0.0885459 | 8.2192 | 31.5253 | 6.52731 | 0.0413288 | 0.119199 | 0.000945223 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2767.53 | 0.494911 | 5155.54ms | 9930848 | 30 | 8.60526e+09 | 3.42211e+06 | 0.0801775 | 1.8283 | 7.5621 | 1.20385 | 0.00840347 | 0.0518132 | 0.00216184 | 1(Win) | true |
| jsonifier (generic) | 2687.16 | 0.129484 | 5307.55ms | 9930848 | 80 | 1.66613e+09 | 3.52446e+06 | 0.209948 | 1.87447 | 7.36879 | 1.37311 | 0.00852935 | 0.0521079 | 0.00402868 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2992.09 | 0.163827 | 5153.67ms | 9930848 | 40 | 1.07561e+09 | 3.16528e+06 | 0.127841 | 1.69027 | 7.00905 | 1.07536 | 0.00820839 | 0.0480135 | 0.00245992 | 1(Win) | true |
| jsonifier (generic) | 2893.37 | 0.160894 | 5307.42ms | 9930848 | 40 | 1.10945e+09 | 3.27328e+06 | 0.307622 | 1.74153 | 6.816 | 1.24466 | 0.00830197 | 0.0482564 | 0.00277925 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 282.07 | 0.249913 | 4345.44ms | 1834197 | 30 | 7.20571e+09 | 6.20138e+06 | 0.0176381 | 18.0117 | 84.437 | 19.3788 | 0.0520644 | 0.537329 | 0.0107086 | 1(Win) | true |
| simdjson (ondemand) | 168.586 | 0.115003 | 7259.42ms | 1834197 | 40 | 5.6955e+09 | 1.03759e+07 | 0.0376355 | 29.9832 | 143.549 | 41.8457 | 0.0566558 | 0.7876 | 0.021328 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 294.534 | 0.32593 | 4344.17ms | 1834197 | 30 | 1.12406e+10 | 5.93896e+06 | 0.472524 | 17.2303 | 81.4428 | 18.6833 | 0.0508675 | 0.515928 | 0.00976756 | 1(Win) | true |
| simdjson (ondemand) | 170.958 | 0.244632 | 7290.53ms | 1834197 | 30 | 1.87958e+10 | 1.02319e+07 | 1.07823 | 29.5645 | 140.559 | 41.1513 | 0.0562796 | 0.766603 | 0.0165696 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1276.49 | 0.500289 | 5230.61ms | 9930848 | 40 | 5.51109e+10 | 7.41938e+06 | 1.49042 | 3.98889 | 16.589 | 3.61849 | 0.0103068 | 0.28031 | 0.00751269 | 1(Win) | true |
| simdjson (ondemand) | 856.262 | 0.371773 | 7807.14ms | 9930848 | 30 | 5.07266e+10 | 1.10606e+07 | 0.377146 | 5.91688 | 27.642 | 7.77348 | 0.010462 | 0.407715 | 0.00876003 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1322.69 | 0.617212 | 5192.42ms | 9930848 | 30 | 5.85929e+10 | 7.16023e+06 | 0.25496 | 3.84781 | 16.0366 | 3.49018 | 0.0100859 | 0.27637 | 0.00584589 | 1(Win) | true |
| simdjson (ondemand) | 870.167 | 0.292233 | 7796.45ms | 9930848 | 30 | 3.03492e+10 | 1.08839e+07 | 0.334726 | 5.79746 | 27.0901 | 7.64533 | 0.0102598 | 0.40376 | 0.00852785 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4203.16 | 0.101908 | 5441.13ms | 1834197 | 640 | 1.15115e+08 | 416169 | 0.747539 | 1.20813 | 5.61706 | 0.892569 | 0.00114726 | 0.0755643 | 4.46721e-06 | 1(Win) | true |
| simdjson (ondemand) | 3240.42 | 0.288314 | 6957.86ms | 1834197 | 30 | 7.26681e+07 | 539815 | 0.0871984 | 1.56389 | 7.57014 | 1.66799 | 0.00411517 | 0.0753977 | 1.27031e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4180.1 | 0.243146 | 5433.51ms | 1834197 | 320 | 3.31286e+08 | 418466 | 0.070689 | 1.21216 | 5.61685 | 0.892521 | 0.00105279 | 0.0755335 | 5.2799e-06 | 1(Win) | true |
| simdjson (ondemand) | 3249.72 | 0.122535 | 6967.75ms | 1834197 | 640 | 2.78419e+08 | 538270 | 0.28775 | 1.56111 | 7.56994 | 1.66794 | 0.00393953 | 0.0753455 | 7.4658e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11355.5 | 0.519147 | 5417.85ms | 9930848 | 30 | 5.62418e+08 | 834025 | 1.8168 | 0.447103 | 1.97632 | 0.1968 | 0.000758629 | 0.0395068 | 4.28832e-05 | 1(Win) | true |
| simdjson (ondemand) | 9738.26 | 0.685522 | 6234.37ms | 9930848 | 40 | 1.77792e+09 | 972535 | 0.0981287 | 0.52474 | 2.52766 | 0.352914 | 0.000682631 | 0.0395162 | 0.000239833 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11129.7 | 0.297526 | 5374.65ms | 9930848 | 160 | 1.02559e+09 | 850944 | 1.5139 | 0.456145 | 1.97628 | 0.196791 | 0.000753837 | 0.0395017 | 0.000181217 | 1(Win) | true |
| simdjson (ondemand) | 9677.45 | 0.653425 | 6234.8ms | 9930848 | 30 | 1.22677e+09 | 978646 | 0.504116 | 0.52094 | 2.52763 | 0.352905 | 0.000670027 | 0.0395065 | 0.000247495 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2339.81 | 0.279099 | 4776.61ms | 1834197 | 40 | 1.74144e+08 | 747592 | 0.193769 | 2.14459 | 11.5728 | 2.42417 | 0.00150635 | 0.150852 | 6.26977e-06 | 1(Win) | true |
| simdjson (ondemand) | 1453.23 | 0.239308 | 7629.69ms | 1834197 | 160 | 1.32758e+09 | 1.20368e+06 | 0.0850375 | 3.4849 | 16.3138 | 4.65754 | 0.00451386 | 0.150618 | 1.44682e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2341.72 | 0.15338 | 4779.97ms | 1834197 | 160 | 2.1003e+08 | 746984 | 0.0252931 | 2.14603 | 11.5726 | 2.42413 | 0.00149625 | 0.150796 | 1.13742e-05 | 1(Win) | true |
| simdjson (ondemand) | 1450.02 | 0.462025 | 7645.43ms | 1834197 | 40 | 1.24261e+09 | 1.20635e+06 | 0.188552 | 3.5034 | 16.3136 | 4.65749 | 0.00442222 | 0.150537 | 1.91092e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7446.51 | 0.358887 | 4056.75ms | 9930848 | 40 | 8.3338e+08 | 1.27184e+06 | 0.314784 | 0.681444 | 3.07632 | 0.479682 | 0.000799365 | 0.0789577 | 8.6692e-05 | 1(Win) | true |
| simdjson (ondemand) | 5740.84 | 0.383704 | 5218.79ms | 9930848 | 30 | 1.20209e+09 | 1.64972e+06 | 0.823817 | 0.88088 | 4.14259 | 0.905076 | 0.000740138 | 0.0789847 | 0.000218837 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7371.18 | 0.423435 | 4072.2ms | 9930848 | 80 | 2.3679e+09 | 1.28484e+06 | 1.13302 | 0.691134 | 3.07628 | 0.479673 | 0.000868583 | 0.078952 | 0.000113656 | 1(Win) | true |
| simdjson (ondemand) | 5637.47 | 0.512044 | 5263.95ms | 9930848 | 80 | 5.91981e+09 | 1.67997e+06 | 1.15755 | 0.896994 | 4.14255 | 0.905066 | 0.000742333 | 0.0789713 | 0.000448313 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1170.83 | 0.221714 | 6745.01ms | 642697 | 30 | 4.0414e+07 | 523494 | 0.0107749 | 4.31215 | 20.9094 | 3.18836 | 0.0120042 | 0.0612137 | 0.000116385 | 1(Win) | true |
| jsonifier (generic) | 1140.86 | 0.117064 | 6940.5ms | 642697 | 30 | 1.18663e+07 | 537248 | 0.147785 | 4.42211 | 20.9347 | 4.03863 | 0.0136323 | 0.0600677 | 0.000107412 | 2(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1290.36 | 0.108097 | 6482.22ms | 642697 | 640 | 1.68733e+08 | 475002 | 0.00134307 | 3.91075 | 19.7438 | 2.92078 | 0.0113838 | 0.0256662 | 8.72009e-05 | 1(Win) | true |
| jsonifier (generic) | 1260.48 | 0.115123 | 6683.54ms | 642697 | 80 | 2.50701e+07 | 486264 | 0.11986 | 4.00463 | 19.7707 | 3.77101 | 0.0128388 | 0.0225781 | 7.34016e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2165.13 | 0.0297767 | 7005.13ms | 1225964 | 640 | 1.65471e+07 | 540000 | 0.967317 | 2.33146 | 11.6345 | 1.68802 | 0.00516917 | 0.0583389 | 0.00010973 | 1(Win) | true |
| jsonifier (generic) | 2055.6 | 0.184904 | 7410.15ms | 1225964 | 160 | 1.76967e+08 | 568774 | 0.0985997 | 2.44911 | 11.7137 | 2.15263 | 0.0058161 | 0.0588735 | 9.01332e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2384.38 | 0.0889358 | 6717.27ms | 1225964 | 30 | 5.70532e+06 | 490346 | 0.0648101 | 2.11829 | 11.0233 | 1.54794 | 0.00469405 | 0.0369109 | 4.51345e-05 | 1(Win) | true |
| jsonifier (generic) | 2238.51 | 0.193285 | 7119.71ms | 1225964 | 320 | 3.26125e+08 | 522300 | 0.162597 | 2.24537 | 11.1026 | 2.01249 | 0.00545751 | 0.0383019 | 3.73558e-05 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 962.611 | 0.0562022 | 4072.61ms | 642697 | 160 | 2.04898e+07 | 636730 | 0.0158117 | 5.24056 | 26.3971 | 5.42762 | 0.0139214 | 0.058029 | 0.000198412 | 1(Win) | true |
| simdjson (ondemand) | 645.379 | 0.203033 | 6060.72ms | 642697 | 40 | 1.48722e+08 | 949711 | 0.059339 | 7.80497 | 41.7607 | 10.0692 | 0.0118191 | 0.0760731 | 0.000238682 | 2(Loss) | true |

----
### Mesh Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1032.47 | 0.0702483 | 7990.33ms | 642697 | 640 | 1.11305e+08 | 593651 | 0.188943 | 4.87669 | 25.231 | 5.1604 | 0.0130973 | 0.0243528 | 0.000209559 | 1(Win) | true |
| simdjson (ondemand) | 680.472 | 0.0811238 | 5924.02ms | 642697 | 320 | 1.7086e+08 | 900733 | 0.144049 | 7.40992 | 40.5941 | 9.80189 | 0.011586 | 0.0396782 | 0.000229472 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1714.2 | 0.252568 | 4366.65ms | 1225964 | 80 | 2.37399e+08 | 682049 | 0.521199 | 2.9222 | 14.5753 | 2.8808 | 0.00597603 | 0.0728816 | 8.46477e-05 | 1(Win) | true |
| simdjson (ondemand) | 1203.8 | 0.270193 | 6201.48ms | 1225964 | 80 | 5.50909e+08 | 971229 | 0.072221 | 4.18312 | 22.5641 | 5.29508 | 0.00513421 | 0.111927 | 0.000160374 | 2(Loss) | true |

----
### Mesh Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1852.34 | 0.17184 | 4202.56ms | 1225964 | 320 | 3.76456e+08 | 631187 | 0.0221512 | 2.70758 | 13.9647 | 2.74076 | 0.00562262 | 0.043977 | 4.52246e-05 | 1(Win) | true |
| simdjson (ondemand) | 1274.88 | 0.0835345 | 6028.02ms | 1225964 | 30 | 1.76064e+07 | 917084 | 0.00739972 | 3.9583 | 21.9528 | 5.15505 | 0.00481545 | 0.0793594 | 0.000137334 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3294.32 | 0.092019 | 4961.59ms | 642697 | 1280 | 3.75186e+07 | 186055 | 0.367262 | 1.53018 | 8.15603 | 1.49562 | 9.77886e-05 | 0.0179335 | 5.80744e-05 | 1(Win) | true |
| simdjson (ondemand) | 2745.83 | 0.28412 | 5889.4ms | 642697 | 640 | 2.57424e+08 | 223220 | 0.0329051 | 1.84013 | 10.0956 | 1.61923 | 0.000137509 | 0.0197794 | 5.58097e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3458.82 | 0.144362 | 4722.53ms | 642697 | 160 | 1.04709e+07 | 177206 | 0.0208224 | 1.45778 | 8.14441 | 1.49307 | 0.00015717 | 0.00674301 | 9.1684e-05 | 1(Win) | true |
| simdjson (ondemand) | 2905.58 | 0.0484208 | 5594.68ms | 642697 | 160 | 1.66928e+06 | 210947 | 0.00224884 | 1.74003 | 10.0838 | 1.61665 | 0.000101914 | 0.00724611 | 2.7793e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5291.12 | 0.126165 | 5879.35ms | 1225964 | 640 | 4.9741e+07 | 220968 | 0.538307 | 0.95327 | 4.92832 | 0.804887 | 4.39399e-05 | 0.0291022 | 1.99116e-05 | 1(Win) | true |
| simdjson (ondemand) | 4725.94 | 0.0744383 | 6562.85ms | 1225964 | 30 | 1.0174e+06 | 247394 | 0.11863 | 1.0682 | 5.96449 | 0.865408 | 4.32585e-05 | 0.0300025 | 1.08758e-05 | 2(Loss) | true |

----
### Mesh Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5556.01 | 0.120728 | 5599.73ms | 1225964 | 1280 | 8.26146e+07 | 210433 | 0.190328 | 0.904516 | 4.92209 | 0.803515 | 3.31493e-05 | 0.0153601 | 1.51278e-05 | 1(Win) | true |
| simdjson (ondemand) | 4924.59 | 0.0616862 | 6271.28ms | 1225964 | 1280 | 2.74537e+07 | 237415 | 0.254489 | 1.02522 | 5.95818 | 0.86402 | 3.585e-05 | 0.0178558 | 3.35591e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3307.26 | 0.100382 | 4970.13ms | 642697 | 160 | 5.53747e+06 | 185327 | 0.281886 | 1.52634 | 8.15719 | 1.49593 | 0.000158434 | 0.017964 | 2.92323e-05 | 1(Win) | true |
| simdjson (ondemand) | 2757.35 | 0.118716 | 5893.84ms | 642697 | 320 | 2.22844e+07 | 222287 | 0.219551 | 1.82972 | 10.0969 | 1.61959 | 0.000154233 | 0.0198755 | 7.16171e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3482.21 | 0.0472992 | 4706.29ms | 642697 | 30 | 207937 | 176016 | 0.0580398 | 1.45084 | 8.14556 | 1.49338 | 8.72365e-05 | 0.00647692 | 1.75303e-05 | 1(Win) | true |
| simdjson (ondemand) | 2902.66 | 0.0296804 | 5597.21ms | 642697 | 160 | 628462 | 211159 | 0.0137703 | 1.74027 | 10.0851 | 1.61702 | 9.9133e-05 | 0.00725881 | 5.07237e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5247.95 | 0.0589322 | 5911.53ms | 1225964 | 1280 | 2.20644e+07 | 222786 | 0.193288 | 0.949721 | 4.92893 | 0.805052 | 4.30356e-05 | 0.0288388 | 2.06725e-05 | 1(Win) | true |
| simdjson (ondemand) | 4671.1 | 0.187408 | 6596.91ms | 1225964 | 1280 | 2.81646e+08 | 250299 | 0.281274 | 1.08051 | 5.96518 | 0.865599 | 4.30548e-05 | 0.0298868 | 9.68148e-05 | 2(Loss) | true |

----
### Mesh Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5529.69 | 0.13836 | 5618.36ms | 1225964 | 640 | 5.47714e+07 | 211435 | 0.0104838 | 0.904755 | 4.9227 | 0.80368 | 3.34303e-05 | 0.0152084 | 3.22336e-05 | 1(Win) | true |
| simdjson (ondemand) | 4928.49 | 0.149025 | 6262.23ms | 1225964 | 320 | 3.9994e+07 | 237227 | 0.0070349 | 1.02314 | 5.95888 | 0.864211 | 3.4269e-05 | 0.0177283 | 1.13686e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1264.02 | 0.0433391 | 4030.82ms | 409725 | 640 | 1.14873e+07 | 309128 | 0.072366 | 3.98956 | 17.53 | 3.29175 | 0.00913222 | 0.0234297 | 0.000262684 | 1(Win) | true |
| simdjson (ondemand) | 1007.13 | 0.12922 | 5046.22ms | 409725 | 160 | 4.02154e+07 | 387977 | 0.111568 | 4.99722 | 19.1425 | 3.61351 | 0.0165649 | 0.0352425 | 0.000135792 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1602.84 | 0.211936 | 7614.27ms | 409725 | 30 | 8.00829e+06 | 243783 | 0.428267 | 3.17754 | 14.6453 | 2.67826 | 0.00621116 | 0.00772453 | 5.38573e-05 | 1(Win) | true |
| simdjson (ondemand) | 1202.39 | 0.247756 | 4776.88ms | 409725 | 160 | 1.0372e+08 | 324972 | 0.420735 | 4.19983 | 16.262 | 3.00114 | 0.0129923 | 0.0121829 | 8.88401e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2270.18 | 0.0416994 | 4335.46ms | 785750 | 640 | 1.21252e+07 | 330084 | 0.191062 | 2.2336 | 9.79946 | 1.73581 | 0.00557982 | 0.0348556 | 0.000101106 | 1(Win) | true |
| simdjson (ondemand) | 1822.51 | 0.0727427 | 5341.76ms | 785750 | 160 | 1.43129e+07 | 411163 | 0.263855 | 2.76324 | 10.6463 | 1.91296 | 0.00963106 | 0.0423227 | 9.03357e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2782.25 | 0.241283 | 4095.42ms | 785750 | 80 | 3.37848e+07 | 269332 | 0.0627314 | 1.817 | 8.29365 | 1.41565 | 0.00381662 | 0.0199857 | 5.40407e-05 | 1(Win) | true |
| simdjson (ondemand) | 2168.73 | 0.106944 | 5091.41ms | 785750 | 320 | 4.36937e+07 | 345524 | 0.198913 | 2.32738 | 9.14412 | 1.59376 | 0.00753764 | 0.026855 | 7.29041e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 515.608 | 0.112168 | 4850.56ms | 409725 | 160 | 1.15613e+08 | 757833 | 0.308108 | 9.80905 | 39.0325 | 8.16425 | 0.0424591 | 0.0723286 | 0.000419275 | 1(Win) | true |
| simdjson (ondemand) | 417.929 | 0.08144 | 5977.95ms | 409725 | 160 | 9.27632e+07 | 934954 | 0.342395 | 12.1314 | 57.566 | 14.4329 | 0.0213094 | 0.040509 | 0.000462688 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 562.326 | 0.158188 | 4740.86ms | 409725 | 160 | 1.93319e+08 | 694872 | 0.0499082 | 9.00668 | 36.1624 | 7.55356 | 0.0373122 | 0.0343124 | 0.000289951 | 1(Win) | true |
| simdjson (ondemand) | 442.646 | 0.0952681 | 5929.47ms | 409725 | 80 | 5.65793e+07 | 882748 | 0.096105 | 11.3946 | 54.6937 | 13.8198 | 0.0197649 | 0.0101596 | 0.000171792 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 958.106 | 0.185438 | 5024.36ms | 785750 | 40 | 8.41392e+07 | 782115 | 0.0873748 | 5.2649 | 20.9935 | 4.26903 | 0.0223789 | 0.0729744 | 0.000344321 | 1(Win) | true |
| simdjson (ondemand) | 776.55 | 0.105935 | 6140.87ms | 785750 | 320 | 3.34393e+08 | 964973 | 0.166539 | 6.50194 | 30.573 | 7.52741 | 0.0130614 | 0.0507382 | 0.000125052 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1038.15 | 0.157872 | 4910.53ms | 785750 | 160 | 2.07767e+08 | 721812 | 0.07127 | 4.85079 | 19.4936 | 3.94975 | 0.0200099 | 0.0440521 | 9.2364e-05 | 1(Win) | true |
| simdjson (ondemand) | 836.696 | 0.0752526 | 6037.45ms | 785750 | 320 | 1.45354e+08 | 895605 | 0.0451491 | 6.05871 | 29.0773 | 7.20813 | 0.0105765 | 0.0273552 | 0.000221015 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2133.64 | 0.0929981 | 4885.39ms | 409725 | 80 | 2.3205e+06 | 183135 | 0.0826505 | 2.37467 | 10.2757 | 1.92151 | 0.00599521 | 0.00100427 | 5.32674e-05 | 1(Win) | true |
| simdjson (ondemand) | 2066.66 | 0.025791 | 5072.59ms | 409725 | 1280 | 3.04364e+06 | 189070 | 0.147313 | 2.43913 | 10.4458 | 1.88511 | 0.00700748 | 0.0015375 | 7.64194e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2382.89 | 0.0892171 | 4830.77ms | 409725 | 30 | 642089 | 163979 | 0.0485053 | 2.11906 | 9.25985 | 1.69921 | 0.00535994 | 0.000160026 | 3.85625e-05 | 1(Win) | true |
| simdjson (ondemand) | 2316.31 | 0.103276 | 4983.19ms | 409725 | 40 | 1.21408e+06 | 168692 | 0.0279376 | 2.1811 | 9.43457 | 1.6619 | 0.00598432 | 0.000792239 | 5.63183e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3609.74 | 0.148651 | 5494.86ms | 785750 | 640 | 6.09444e+07 | 207591 | 0.139281 | 1.39726 | 6.00835 | 1.01808 | 0.00376335 | 0.00250812 | 0.000139037 | 1(Win) | true |
| simdjson (ondemand) | 3514.09 | 0.0704557 | 5668.1ms | 785750 | 320 | 7.22312e+06 | 213241 | 0.0602094 | 1.43338 | 6.10693 | 1.00966 | 0.00452271 | 0.00245925 | 8.19281e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4028.54 | 0.160178 | 5472.6ms | 785750 | 80 | 7.10178e+06 | 186010 | 0.0802672 | 1.24263 | 5.47827 | 0.90207 | 0.00294796 | 0.00189575 | 3.56188e-05 | 1(Win) | true |
| simdjson (ondemand) | 3921.82 | 0.0852013 | 5597.98ms | 785750 | 160 | 4.2404e+06 | 191072 | 0.260306 | 1.28314 | 5.57811 | 0.892803 | 0.00369493 | 0.00146819 | 3.95005e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1491.56 | 0.0724763 | 6893.31ms | 409725 | 1280 | 4.61429e+07 | 261970 | 0.267669 | 3.36397 | 15.2274 | 3.08243 | 0.00693549 | 0.00103757 | 0.000164066 | 1(Win) | true |
| simdjson (ondemand) | 1464.29 | 0.087804 | 7031.04ms | 409725 | 160 | 8.78369e+06 | 266848 | 0.0461449 | 3.43804 | 15.8008 | 3.48981 | 0.00733381 | 0.000847032 | 0.000102584 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1610.28 | 0.0786582 | 6852.17ms | 409725 | 320 | 1.16579e+07 | 242656 | 0.233128 | 3.1069 | 14.1961 | 2.85519 | 0.0058189 | 0.000236927 | 0.000103743 | 1(Win) | true |
| simdjson (ondemand) | 1583.57 | 0.0998105 | 6930.51ms | 409725 | 640 | 3.8819e+07 | 246749 | 0.0461047 | 3.1731 | 14.7688 | 3.26096 | 0.00586191 | 0.000280989 | 5.60742e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2615.18 | 0.15402 | 7538.45ms | 785750 | 1280 | 2.49303e+08 | 286538 | 0.433262 | 1.91572 | 8.59265 | 1.62443 | 0.00410715 | 0.00172658 | 0.000117392 | 1(Win) | true |
| simdjson (ondemand) | 2575.74 | 0.0651371 | 7665.07ms | 785750 | 1280 | 4.59656e+07 | 290926 | 0.0534855 | 1.94874 | 8.89929 | 1.84687 | 0.00441518 | 0.00308112 | 8.10521e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2839.07 | 0.119264 | 7388.28ms | 785750 | 1280 | 1.26838e+08 | 263942 | 0.002175 | 1.7621 | 8.0535 | 1.50573 | 0.00332059 | 0.00128525 | 4.18977e-05 | 1(Win) | true |
| simdjson (ondemand) | 2771.09 | 0.151102 | 7556.77ms | 785750 | 640 | 1.06853e+08 | 270417 | 0.111376 | 1.81444 | 8.36173 | 1.72773 | 0.00358488 | 0.00227469 | 0.000129395 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1711.62 | 0.0787775 | 7681.63ms | 264040 | 1280 | 1.71925e+07 | 147117 | 0.0910989 | 2.92428 | 9.70831 | 1.74277 | 0.0121497 | 0.000232265 | 0.000114746 | 1(Win) | true |
| simdjson (ondemand) | 1650.39 | 0.064972 | 4116.02ms | 264040 | 1280 | 1.25785e+07 | 152575 | 0.0653439 | 3.03831 | 9.93017 | 1.6987 | 0.0145179 | 0.000207654 | 0.000111799 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2083.74 | 0.280756 | 7375.28ms | 264040 | 80 | 9.20881e+06 | 120845 | 0.0687201 | 2.40958 | 8.3813 | 1.45555 | 0.00913091 | 3.08665e-05 | 2.37653e-05 | 1(Win) | true |
| simdjson (ondemand) | 1972.36 | 0.114788 | 7747ms | 264040 | 1280 | 2.74896e+07 | 127668 | 0.0316058 | 2.53266 | 8.60273 | 1.41286 | 0.0118642 | 9.64816e-05 | 6.2097e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2409.19 | 0.105444 | 4258.46ms | 399947 | 640 | 1.78354e+07 | 158318 | 0.159901 | 2.05933 | 6.9498 | 1.16754 | 0.00822532 | 0.000899443 | 0.00011182 | 1(Win) | true |
| simdjson (ondemand) | 2340.31 | 0.0730823 | 4361.36ms | 399947 | 1280 | 1.81591e+07 | 162978 | 0.0522146 | 2.1328 | 7.04505 | 1.14329 | 0.0101115 | 0.000909056 | 9.62295e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3058.22 | 0.133976 | 7402.18ms | 399947 | 320 | 8.93447e+06 | 124719 | 0.0465963 | 1.61525 | 6.0738 | 0.977897 | 0.00301298 | 0.000185462 | 0.000126923 | 1(Win) | true |
| simdjson (ondemand) | 2813.33 | 0.317013 | 4080.13ms | 399947 | 80 | 1.47777e+07 | 135576 | 0.134377 | 1.78541 | 6.16786 | 0.954531 | 0.00826309 | 4.50997e-05 | 2.47845e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 513.564 | 0.123274 | 6341.18ms | 264040 | 640 | 2.33818e+08 | 490315 | 0.11911 | 9.69689 | 29.7616 | 5.68292 | 0.0678172 | 0.0130984 | 0.000356095 | 1(Win) | true |
| simdjson (ondemand) | 221.729 | 0.134971 | 7193.92ms | 264040 | 160 | 3.75923e+08 | 1.13566e+06 | 0.00726064 | 22.3476 | 82.6181 | 22.1015 | 0.132621 | 0.00127066 | 0.000800944 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 551.561 | 0.111366 | 6149.89ms | 264040 | 640 | 1.65438e+08 | 456538 | 0.183588 | 9.10496 | 28.433 | 5.39666 | 0.0619562 | 0.00467518 | 0.000351799 | 1(Win) | true |
| simdjson (ondemand) | 230.054 | 0.158395 | 7078.83ms | 264040 | 160 | 4.80932e+08 | 1.09456e+06 | 0.129005 | 21.6419 | 81.2963 | 21.8184 | 0.124443 | 0.00027858 | 0.000178216 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 785.168 | 0.0921561 | 6267.05ms | 399947 | 640 | 1.28265e+08 | 485780 | 0.341681 | 6.36316 | 20.1522 | 3.75916 | 0.0382113 | 0.0171562 | 0.00064564 | 1(Win) | true |
| simdjson (ondemand) | 355.455 | 0.134423 | 6808.89ms | 399947 | 160 | 3.32892e+08 | 1.07304e+06 | 0.255757 | 13.9895 | 54.482 | 14.4813 | 0.066254 | 0.00140209 | 0.000607034 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 844.448 | 0.304331 | 6095.89ms | 399947 | 80 | 1.51161e+08 | 451679 | 0.372142 | 5.91575 | 19.2756 | 3.57036 | 0.0336932 | 0.00719974 | 0.000226593 | 1(Win) | true |
| simdjson (ondemand) | 370.026 | 0.236641 | 6728.35ms | 399947 | 30 | 1.78501e+08 | 1.03079e+06 | 0.0849681 | 13.5974 | 53.6088 | 14.2944 | 0.0634193 | 0.000150687 | 0.000116765 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5999.38 | 0.0534183 | 4964.65ms | 264040 | 2560 | 1.28691e+06 | 41972.4 | 0.0646677 | 0.834973 | 3.88196 | 0.517395 | 0.000833678 | 1.08737e-05 | 7.35122e-06 | 1(Win) | true |
| simdjson (ondemand) | 5550.24 | 0.025523 | 5282.98ms | 264040 | 4890 | 655675 | 45368.9 | 0.209917 | 0.901824 | 4.41334 | 0.705342 | 0.00109433 | 2.47213e-05 | 2.10881e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6124.01 | 0.0460589 | 4949.1ms | 264040 | 4890 | 1.75389e+06 | 41118.2 | 0.0850743 | 0.817131 | 3.80543 | 0.502083 | 0.000812689 | 4.71399e-05 | 4.24519e-05 | 1(Win) | true |
| simdjson (ondemand) | 5657.88 | 0.0351261 | 5241.39ms | 264040 | 4890 | 1.19509e+06 | 44505.8 | 0.0764841 | 0.880283 | 4.3361 | 0.689712 | 0.00110689 | 2.83312e-05 | 2.52007e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7549.02 | 0.0298305 | 5814.97ms | 399947 | 4890 | 1.11084e+06 | 50525.6 | 0.0225897 | 0.66116 | 3.08515 | 0.355217 | 0.000561432 | 1.82841e-05 | 1.56641e-05 | 1(Win) | true |
| simdjson (ondemand) | 7234.58 | 0.0615937 | 6050.3ms | 399947 | 640 | 674888 | 52721.7 | 0.0656438 | 0.692796 | 3.40041 | 0.486763 | 0.000739442 | 1.3369e-05 | 1.12945e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7719.11 | 0.0637635 | 5748.05ms | 399947 | 1280 | 1.27065e+06 | 49412.3 | 0.113518 | 0.646506 | 3.03462 | 0.345108 | 0.000548737 | 1.93444e-05 | 1.72894e-05 | 1(Win) | true |
| simdjson (ondemand) | 7358.28 | 0.0461395 | 5987ms | 399947 | 640 | 366082 | 51835.4 | 0.12401 | 0.678205 | 3.34942 | 0.476445 | 0.000758112 | 5.0827e-06 | 4.03569e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3699.63 | 0.027188 | 7566.09ms | 264040 | 4890 | 1.67451e+06 | 68063.1 | 0.117176 | 1.35389 | 6.61747 | 1.17498 | 0.00110854 | 2.05901e-05 | 1.68407e-05 | 1(Win) | true |
| simdjson (ondemand) | 3222.58 | 0.0499489 | 4384.47ms | 264040 | 1280 | 1.94982e+06 | 78138.8 | 0.064363 | 1.55111 | 7.70525 | 1.75135 | 0.00161708 | 1.34035e-05 | 1.00423e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3761.79 | 0.0374355 | 7518.78ms | 264040 | 4890 | 3.07063e+06 | 66938.4 | 0.0117977 | 1.3305 | 6.54049 | 1.15967 | 0.00112112 | 1.51128e-05 | 1.2179e-05 | 1(Win) | true |
| simdjson (ondemand) | 3279.06 | 0.0394223 | 4337ms | 264040 | 2560 | 2.3462e+06 | 76792.9 | 0.00505749 | 1.52793 | 7.62753 | 1.73572 | 0.00161493 | 1.37349e-05 | 1.11518e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5020.64 | 0.0578941 | 4283.92ms | 399947 | 1280 | 2.47609e+06 | 75970.2 | 0.0484892 | 1.00261 | 4.89385 | 0.790345 | 0.000739801 | 1.40019e-05 | 1.1105e-05 | 1(Win) | true |
| simdjson (ondemand) | 4438.51 | 0.100323 | 4776.86ms | 399947 | 320 | 2.37839e+06 | 85934.1 | 0.0452695 | 1.12898 | 5.58314 | 1.17959 | 0.00126889 | 1.27986e-05 | 1.04858e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5057.61 | 0.0408423 | 4266.24ms | 399947 | 2560 | 2.42871e+06 | 75414.9 | 0.018836 | 0.986807 | 4.84177 | 0.779889 | 0.00074347 | 2.14687e-05 | 1.81284e-05 | 1(Win) | true |
| simdjson (ondemand) | 4501.95 | 0.0913946 | 4755.5ms | 399947 | 640 | 3.83728e+06 | 84723 | 0.103593 | 1.112 | 5.53126 | 1.16909 | 0.00126156 | 8.39174e-06 | 6.88372e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 751.367 | 0.0436838 | 1328.77ms | 4630 | 2560 | 16870.9 | 5876.64 | 0.0695598 | 6.74071 | 31.6426 | 5.71296 | 0.0030937 | 0.000126974 | 5.92265e-05 | 1(Win) | true |
| jsonifier (generic) | 656.729 | 0.0297282 | 1413.62ms | 4630 | 4890 | 19536.1 | 6723.49 | 0.175588 | 7.67124 | 32.5324 | 6.36544 | 0.0064036 | 8.97057e-05 | 4.15182e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 896.512 | 0.0680362 | 1330.78ms | 4630 | 80 | 898.296 | 4925.21 | 0.125278 | 5.69194 | 27.1618 | 4.69676 | 0.00330724 | 5.39957e-05 | 2.15983e-05 | 1(Win) | true |
| jsonifier (generic) | 761.451 | 0.117341 | 1413.22ms | 4630 | 80 | 3704 | 5798.81 | 0.021336 | 6.66501 | 28.0274 | 5.34255 | 0.00642009 | 9.44924e-05 | 4.04968e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2241.94 | 0.0520958 | 1374.86ms | 14795 | 1280 | 13759.3 | 6293.48 | 0.271615 | 2.25972 | 10.8072 | 1.82541 | 0.00111049 | 3.55378e-05 | 1.80065e-05 | 1(Win) | true |
| jsonifier (generic) | 1955.65 | 0.110029 | 1469.42ms | 14795 | 320 | 20165.8 | 7214.81 | 0.0558625 | 2.58793 | 11.0403 | 2.02866 | 0.00236968 | 2.26005e-05 | 8.66002e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2623.94 | 0.0680424 | 1372.69ms | 14795 | 640 | 8567.63 | 5377.25 | 0.0849503 | 1.94152 | 9.40575 | 1.50801 | 0.00068995 | 1.02442e-05 | 3.1683e-06 | 1(Win) | true |
| jsonifier (generic) | 2216.55 | 0.0437603 | 1472.8ms | 14795 | 4890 | 37944.2 | 6365.59 | 0.264211 | 2.2654 | 9.64164 | 1.71125 | 0.00212425 | 3.01323e-05 | 1.3988e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 587.725 | 0.0644366 | 1479.57ms | 4630 | 80 | 1874.86 | 7512.89 | 0.00449248 | 8.49195 | 38.7076 | 8.06479 | 0.0105373 | 3.7797e-05 | 1.88985e-05 | 1(Win) | true |
| jsonifier (generic) | 562.969 | 0.0936648 | 1527.22ms | 4630 | 4890 | 263909 | 7843.25 | 0.0495118 | 8.97932 | 37.9374 | 7.52765 | 0.00836648 | 0.000265407 | 0.000165057 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 684.703 | 0.0290824 | 1482.49ms | 4630 | 4890 | 17199.9 | 6448.8 | 0.130486 | 7.38586 | 34.3071 | 7.06674 | 0.00787705 | 9.78768e-05 | 4.16948e-05 | 1(Win) | true |
| jsonifier (generic) | 635.632 | 0.0514725 | 1523.61ms | 4630 | 320 | 4091.21 | 6946.65 | 0.0332783 | 7.8563 | 33.5056 | 6.52138 | 0.00758437 | 5.19708e-05 | 1.68737e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1815.94 | 0.0432645 | 1522.68ms | 14795 | 1280 | 14464.3 | 7769.85 | 0.0755693 | 2.79652 | 13.0208 | 2.56249 | 0.00308693 | 3.82836e-05 | 1.81649e-05 | 1(Win) | true |
| jsonifier (generic) | 1696.78 | 0.0699454 | 1574.7ms | 14795 | 640 | 21650.9 | 8315.51 | 0.0548599 | 2.98483 | 12.7533 | 2.3973 | 0.00319206 | 2.52408e-05 | 1.32013e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2039.97 | 0.0410359 | 1529.72ms | 14795 | 2560 | 20622.8 | 6916.56 | 0.052823 | 2.48385 | 11.6471 | 2.2509 | 0.0026003 | 4.31681e-05 | 2.48976e-05 | 1(Win) | true |
| jsonifier (generic) | 1911.83 | 0.0583986 | 1573.71ms | 14795 | 1280 | 23776.4 | 7380.15 | 0.0321282 | 2.6533 | 11.3657 | 2.08239 | 0.00228308 | 3.11021e-05 | 1.64224e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5711.02 | 0.0843221 | 809.529ms | 4630 | 4890 | 2078.38 | 773.156 | 0.351088 | 0.929189 | 4.02916 | 0.530886 | 0.000222122 | 1.85948e-05 | 6.80191e-06 | 1(Win) | true |
| simdjson (ondemand) | 4968.15 | 0.0561856 | 821.434ms | 4630 | 640 | 159.589 | 888.764 | 0.212296 | 1.06348 | 4.61015 | 0.865875 | 0.00143089 | 1.58612e-05 | 2.02484e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5753.83 | 0.113741 | 810.687ms | 4630 | 2560 | 1950.38 | 767.404 | 0.20888 | 0.923075 | 3.9933 | 0.522894 | 0.000216911 | 1.68737e-05 | 5.5683e-06 | 1(Win) | true |
| simdjson (ondemand) | 5017.43 | 0.0613261 | 818.745ms | 4630 | 4890 | 1424.29 | 880.035 | 0.193793 | 1.05213 | 4.57581 | 0.857668 | 0.00147862 | 1.67839e-05 | 5.65354e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11725.9 | 0.0767304 | 852.544ms | 14795 | 4890 | 4168.54 | 1203.29 | 0.0975095 | 0.443436 | 2.03521 | 0.19243 | 6.81018e-05 | 1.25505e-05 | 5.69473e-06 | 1(Win) | true |
| simdjson (ondemand) | 10225.5 | 0.0312391 | 871.906ms | 14795 | 1280 | 237.832 | 1379.85 | 0.0299602 | 0.508983 | 2.35471 | 0.310645 | 0.000523826 | 6.23099e-06 | 2.1122e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 11865.8 | 0.140945 | 852.669ms | 14795 | 160 | 449.424 | 1189.1 | 0.064083 | 0.440532 | 2.02399 | 0.189929 | 6.75904e-05 | 4.64684e-06 | 8.4488e-07 | 1(Win) | true |
| simdjson (ondemand) | 10424.2 | 0.102022 | 869.498ms | 14795 | 80 | 152.554 | 1353.55 | 0.0572896 | 0.502056 | 2.34397 | 0.308077 | 0.000415681 | 2.53464e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3736.96 | 0.113247 | 854.312ms | 4630 | 2560 | 4583.69 | 1181.58 | 0.018153 | 1.39858 | 6.06285 | 0.933046 | 0.00021902 | 2.12608e-05 | 8.26809e-06 | 1(Win) | true |
| simdjson (ondemand) | 3148.98 | 0.0722552 | 873.538ms | 4630 | 4890 | 5019.6 | 1402.2 | 0.0513564 | 1.64924 | 7.17797 | 1.70022 | 0.00277695 | 2.34975e-05 | 6.09522e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3837.66 | 0.105916 | 850.857ms | 4630 | 4890 | 7262.02 | 1150.57 | 0.294634 | 1.3614 | 6.027 | 0.925054 | 0.000288065 | 1.53705e-05 | 4.28432e-06 | 1(Win) | true |
| simdjson (ondemand) | 3176.18 | 0.173491 | 874.105ms | 4630 | 1280 | 7445.88 | 1390.2 | 0.132857 | 1.63261 | 7.14298 | 1.69201 | 0.00276272 | 1.46801e-05 | 3.37473e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8743.74 | 0.206001 | 899.89ms | 14795 | 1280 | 14144.5 | 1613.68 | 0.134748 | 0.592554 | 2.67165 | 0.318283 | 7.24485e-05 | 6.2838e-06 | 1.74257e-06 | 1(Win) | true |
| simdjson (ondemand) | 7471.8 | 0.0567166 | 920.258ms | 14795 | 4890 | 5609.3 | 1888.38 | 0.313806 | 0.688379 | 3.1583 | 0.571747 | 0.000848336 | 8.07215e-06 | 2.77826e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8976.94 | 0.250804 | 895.198ms | 14795 | 160 | 2486.36 | 1571.76 | 0.000795292 | 0.577991 | 2.66043 | 0.315782 | 8.19534e-05 | 7.60392e-06 | 1.26732e-06 | 1(Win) | true |
| simdjson (ondemand) | 7626.74 | 0.0511452 | 919.867ms | 14795 | 1280 | 1145.97 | 1850.02 | 0.241768 | 0.677313 | 3.14735 | 0.569179 | 0.000900906 | 5.96697e-06 | 1.32013e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1159.25 | 0.0630064 | 1164.15ms | 5092 | 160 | 1114.59 | 4189.02 | 0.161471 | 4.40574 | 16.926 | 2.95463 | 0.00291879 | 3.19128e-05 | 1.10467e-05 | 1(Win) | true |
| jsonifier (generic) | 1098.62 | 0.150421 | 1186.75ms | 5092 | 40 | 1768.32 | 4420.2 | 0.03317 | 4.64621 | 17.8154 | 3.34623 | 0.00267086 | 0.000343676 | 8.83739e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1321.69 | 0.0686177 | 1137.73ms | 5092 | 320 | 2033.96 | 3674.18 | 0.0612857 | 3.87232 | 15.2084 | 2.5409 | 0.00309616 | 9.69658e-05 | 5.27789e-05 | 1(Win) | true |
| jsonifier (generic) | 1259.97 | 0.0786529 | 1171.91ms | 5092 | 1280 | 11762.4 | 3854.15 | 0.0494639 | 4.00559 | 15.5133 | 2.82323 | 0.00339227 | 7.62532e-05 | 2.9458e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2483.31 | 0.0284518 | 1185.39ms | 11724 | 4890 | 8024.53 | 4502.41 | 0.173972 | 2.05273 | 8.16181 | 1.31952 | 0.0011619 | 2.31117e-05 | 7.20386e-06 | 1(Win) | true |
| jsonifier (generic) | 2297.63 | 0.0264433 | 1226.78ms | 11724 | 4890 | 8097.13 | 4866.26 | 0.0585608 | 2.21733 | 8.63025 | 1.49804 | 0.00111154 | 3.58972e-05 | 1.46345e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2777.8 | 0.0418443 | 1170.74ms | 11724 | 2560 | 7262.08 | 4025.08 | 0.0327429 | 1.8389 | 7.40611 | 1.13991 | 0.00130152 | 1.47267e-05 | 3.33184e-06 | 1(Win) | true |
| jsonifier (generic) | 2647.53 | 0.0496564 | 1207.4ms | 11724 | 2560 | 11258 | 4223.13 | 0.0439644 | 1.92506 | 7.5995 | 1.26451 | 0.0014893 | 2.91869e-05 | 6.63036e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 478.318 | 0.0428085 | 1755.43ms | 5092 | 160 | 3022.21 | 10152.5 | 0.0645361 | 10.6161 | 42.1059 | 9.25373 | 0.00299735 | 5.27789e-05 | 3.68225e-06 | 1(Win) | true |
| simdjson (ondemand) | 283.89 | 0.0208086 | 2449.31ms | 5092 | 2560 | 32434.2 | 17105.6 | 0.0607162 | 17.8411 | 73.1901 | 20.2143 | 0.021407 | 6.559e-05 | 1.65701e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 507.74 | 0.0591649 | 1736.63ms | 5092 | 640 | 20492.9 | 9564.17 | 0.0414805 | 9.9934 | 39.8493 | 8.7412 | 0.0034831 | 5.21652e-05 | 1.41153e-05 | 1(Win) | true |
| simdjson (ondemand) | 293.032 | 0.0146039 | 2432.69ms | 5092 | 4890 | 28641.3 | 16571.9 | 0.000660821 | 17.2941 | 71.4462 | 19.8001 | 0.0217543 | 7.27714e-05 | 2.48596e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1059.66 | 0.0580146 | 1795.7ms | 11724 | 640 | 23981.3 | 10551.4 | 0.0204843 | 4.7929 | 19.1418 | 4.05519 | 0.00142669 | 2.99866e-05 | 1.23944e-05 | 1(Win) | true |
| simdjson (ondemand) | 640.785 | 0.0766571 | 2501.03ms | 11724 | 160 | 28625.5 | 17448.7 | 0.0832819 | 7.90199 | 32.5391 | 8.8028 | 0.00971511 | 1.27943e-05 | 5.33095e-07 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1121.18 | 0.0565843 | 1786.49ms | 11724 | 320 | 10189.2 | 9972.38 | 0.0418168 | 4.52698 | 18.1414 | 3.82866 | 0.00159235 | 2.13238e-05 | 3.99821e-06 | 1(Win) | true |
| simdjson (ondemand) | 660.645 | 0.0937916 | 2494ms | 11724 | 320 | 80629.4 | 16924.2 | 0.0832434 | 7.66195 | 31.7702 | 8.6217 | 0.00984892 | 7.33005e-05 | 4.39803e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4122.46 | 0.118791 | 850.15ms | 5092 | 2560 | 5012.7 | 1177.96 | 0.100311 | 1.26571 | 4.77494 | 0.759231 | 0.000199685 | 2.26305e-05 | 9.20562e-06 | 1(Win) | true |
| simdjson (ondemand) | 3647.48 | 0.0305287 | 864.086ms | 5092 | 4890 | 807.822 | 1331.36 | 0.0427772 | 1.42715 | 6.28535 | 1.14336 | 0.00127362 | 2.02812e-05 | 6.6667e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4277 | 0.0796816 | 845.277ms | 5092 | 160 | 130.958 | 1135.4 | 0.077006 | 1.22325 | 4.65691 | 0.737431 | 0.000197614 | 1.71838e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3690.02 | 0.0694664 | 862.127ms | 5092 | 4890 | 4086.76 | 1316.01 | 0.0427166 | 1.40988 | 6.17557 | 1.12097 | 0.00128772 | 2.23696e-05 | 7.14863e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7250.33 | 0.0834976 | 889.721ms | 11724 | 4890 | 8107.62 | 1542.12 | 0.0383543 | 0.71373 | 2.84664 | 0.355937 | 9.29002e-05 | 3.14842e-05 | 1.80533e-05 | 1(Win) | true |
| simdjson (ondemand) | 6539.98 | 0.130582 | 905.102ms | 11724 | 1280 | 6379.31 | 1709.62 | 0.0303338 | 0.790199 | 3.54981 | 0.535653 | 0.000617257 | 1.11283e-05 | 3.2652e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7639.45 | 0.0996527 | 882.209ms | 11724 | 2560 | 5445.61 | 1463.57 | 0.0683593 | 0.678607 | 2.7738 | 0.342204 | 8.97598e-05 | 1.31941e-05 | 4.59794e-06 | 1(Win) | true |
| simdjson (ondemand) | 6763.17 | 0.110709 | 899.306ms | 11724 | 80 | 267.985 | 1653.2 | 0.0951791 | 0.765573 | 3.48055 | 0.521665 | 0.000604529 | 3.19857e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2529.52 | 0.0747056 | 930.397ms | 5092 | 2560 | 5265.6 | 1919.78 | 0.0810594 | 2.03955 | 8.41241 | 1.59859 | 0.000322964 | 2.86141e-05 | 8.5152e-06 | 1(Win) | true |
| simdjson (ondemand) | 2043.16 | 0.113387 | 973.113ms | 5092 | 80 | 581.019 | 2376.76 | 0.091068 | 2.51786 | 10.6915 | 2.53103 | 0.0026954 | 7.36449e-06 | 2.45483e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2629.47 | 0.12283 | 923.557ms | 5092 | 30 | 154.372 | 1846.8 | 0 | 1.96568 | 8.24509 | 1.56697 | 0.000196386 | 1.30924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2082.21 | 0.0684748 | 968.21ms | 5092 | 320 | 816.09 | 2332.19 | 0.0557727 | 2.46342 | 10.5314 | 2.49882 | 0.0030937 | 2.08661e-05 | 1.22742e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5041.28 | 0.0526983 | 961.132ms | 11724 | 2560 | 3497.07 | 2217.87 | 0.236278 | 1.0182 | 4.38332 | 0.711959 | 8.95599e-05 | 1.1928e-05 | 3.73166e-06 | 1(Win) | true |
| simdjson (ondemand) | 4108.48 | 0.0523661 | 1007.05ms | 11724 | 2560 | 5199.13 | 2721.42 | 0.120555 | 1.24785 | 5.44191 | 1.13408 | 0.00130535 | 1.7159e-05 | 7.26341e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5147.91 | 0.10004 | 955.593ms | 11724 | 40 | 188.84 | 2171.93 | 0.0887097 | 1.00042 | 4.33222 | 0.702491 | 8.52951e-05 | 1.27943e-05 | 4.26476e-06 | 1(Win) | true |
| simdjson (ondemand) | 4172.04 | 0.043541 | 1001.66ms | 11724 | 4890 | 6658.26 | 2679.96 | 0.292924 | 1.22377 | 5.3724 | 1.1201 | 0.00139652 | 1.37972e-05 | 4.98863e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 1392.84 | 0.0433382 | 1071.6ms | 4857 | 4890 | 10157.5 | 3325.59 | 0.0201941 | 3.6699 | 13.7953 | 2.63414 | 0.00137095 | 0.000124291 | 6.77874e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1391.7 | 0.0952812 | 1067.76ms | 4857 | 640 | 6436.34 | 3328.3 | 0.0383401 | 3.67308 | 13.67 | 2.46325 | 0.000704524 | 2.89531e-05 | 7.72082e-06 | 1(Tie) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1742.54 | 0.0362351 | 1025.61ms | 4857 | 4890 | 4536.68 | 2658.18 | 0.0192312 | 2.94497 | 10.8563 | 2.00968 | 0.00261356 | 4.43355e-05 | 1.0105e-05 | 1(Win) | true |
| simdjson (ondemand) | 1683.07 | 0.0800529 | 1033.17ms | 4857 | 160 | 776.616 | 2752.11 | 0.0877368 | 3.05241 | 11.5304 | 2.02368 | 0.00117228 | 4.24645e-05 | 2.44492e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2051.22 | 0.0439407 | 1080.8ms | 7376 | 2560 | 5812.88 | 3429.33 | 0.108272 | 2.4944 | 9.52874 | 1.64778 | 0.000817209 | 9.47435e-05 | 5.6772e-05 | 1(Win) | true |
| jsonifier (generic) | 2034.06 | 0.0423125 | 1083.89ms | 7376 | 2560 | 5481.43 | 3458.26 | 0.096771 | 2.51381 | 9.52807 | 1.72845 | 0.000918784 | 3.61709e-05 | 1.20217e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2508.52 | 0.0426142 | 1042.61ms | 7376 | 4890 | 6982.74 | 2804.17 | 0.0331912 | 2.04412 | 7.71367 | 1.34124 | 0.00173042 | 3.4767e-05 | 8.92742e-06 | 1(Win) | true |
| simdjson (ondemand) | 2432.25 | 0.0394631 | 1045.99ms | 7376 | 2560 | 3334.63 | 2892.09 | 0.09036 | 2.10673 | 8.08555 | 1.35155 | 0.00122113 | 3.08221e-05 | 7.36129e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 570.621 | 0.0559598 | 1555.53ms | 4857 | 1280 | 26412.2 | 8117.47 | 0.0654986 | 8.90308 | 37.1923 | 7.57217 | 0.00371082 | 0.000247388 | 0.00015699 | 1(Win) | true |
| simdjson (ondemand) | 150.91 | 0.075699 | 3820.38ms | 4857 | 320 | 172754 | 30693.7 | 0.0838517 | 33.5203 | 153.778 | 45.0838 | 0.0731181 | 4.24645e-05 | 2.57361e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 631.839 | 0.0520733 | 1504.92ms | 4857 | 1280 | 18653.6 | 7330.97 | 0.00172644 | 8.04109 | 34.2215 | 6.93844 | 0.00422699 | 7.47954e-05 | 1.62459e-05 | 1(Win) | true |
| simdjson (ondemand) | 153.989 | 0.0268413 | 3766.92ms | 4857 | 2560 | 166880 | 30080 | 0.0118942 | 32.8513 | 151.538 | 44.6241 | 0.0729391 | 4.95419e-05 | 6.43401e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 842.234 | 0.0316182 | 1579.58ms | 7376 | 2560 | 17852.2 | 8351.96 | 0.0321303 | 6.02566 | 25.0762 | 5.00651 | 0.00386409 | 4.96225e-05 | 1.82708e-05 | 1(Win) | true |
| simdjson (ondemand) | 229.666 | 0.059275 | 3801.47ms | 7376 | 640 | 210946 | 30628.4 | 0.0145974 | 22.0208 | 101.369 | 29.6155 | 0.0464092 | 6.07968e-05 | 2.22427e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 935.091 | 0.0265494 | 1526.05ms | 7376 | 4890 | 19505.3 | 7522.59 | 0.0403995 | 5.43071 | 23.0849 | 4.58203 | 0.00365392 | 0.000106325 | 5.90263e-05 | 1(Win) | true |
| simdjson (ondemand) | 234.39 | 0.0250779 | 3765.61ms | 7376 | 4890 | 276985 | 30011.1 | 0.0459606 | 21.6455 | 99.9233 | 29.3187 | 0.0470765 | 0.00014392 | 9.46529e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3512.49 | 0.0480553 | 863.218ms | 4857 | 4890 | 1963.81 | 1318.72 | 0.0107213 | 1.48169 | 6.00268 | 0.997324 | 0.000207909 | 2.42098e-05 | 6.86295e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 3507.24 | 0.12125 | 865.505ms | 4857 | 1280 | 3282.29 | 1320.69 | 0.0315785 | 1.4902 | 5.73049 | 0.89335 | 0.000376068 | 4.64857e-05 | 2.26799e-05 | 1(Tie) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4012.25 | 0.0947725 | 854.173ms | 4857 | 160 | 191.533 | 1154.46 | 0.0346362 | 1.30527 | 5.16409 | 0.777846 | 0.000243206 | 1.80152e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3930.74 | 0.0611465 | 854.1ms | 4857 | 4890 | 2538.87 | 1178.4 | 0.118493 | 1.33119 | 5.46901 | 0.885115 | 0.000335274 | 3.31358e-05 | 1.53679e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4826.91 | 0.345999 | 878.142ms | 7376 | 2560 | 65086.9 | 1457.31 | 0.154041 | 1.07244 | 4.45635 | 0.677197 | 0.000202621 | 2.43611e-05 | 8.42047e-06 | 1(Win) | true |
| jsonifier (generic) | 4725.54 | 0.0491052 | 882.798ms | 7376 | 4890 | 2612.79 | 1488.57 | 0.0808439 | 1.09811 | 4.3144 | 0.600326 | 0.00014087 | 3.46561e-05 | 1.45279e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5343.37 | 0.0422534 | 869.492ms | 7376 | 640 | 198.023 | 1316.45 | 0.0526073 | 0.976538 | 4.10494 | 0.603308 | 0.000460531 | 1.44048e-05 | 2.33019e-06 | 1(Win) | true |
| jsonifier (generic) | 5299.34 | 0.068255 | 868.478ms | 7376 | 2560 | 2101.39 | 1327.39 | 0.0040609 | 0.983539 | 3.94143 | 0.524268 | 0.000261935 | 1.933e-05 | 6.24915e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2033.82 | 0.0785817 | 962.937ms | 4857 | 320 | 1024.96 | 2277.49 | 0.179383 | 2.53079 | 10.357 | 2.18695 | 0.000937436 | 4.24645e-05 | 1.86586e-05 | 1(Win) | true |
| simdjson (ondemand) | 1940.51 | 0.0392026 | 972.564ms | 4857 | 4890 | 4281.96 | 2386.99 | 0.202872 | 2.64893 | 11.3515 | 2.48384 | 0.00153633 | 1.87784e-05 | 5.01037e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2193.05 | 0.0502239 | 951.776ms | 4857 | 4890 | 5502.59 | 2112.12 | 0.0318861 | 2.34848 | 9.78958 | 2.07144 | 0.0013267 | 3.77252e-05 | 1.60416e-05 | 1(Win) | true |
| simdjson (ondemand) | 2069.58 | 0.106256 | 963.765ms | 4857 | 160 | 904.895 | 2238.13 | 0.105948 | 2.48887 | 10.8205 | 2.37163 | 0.00151843 | 1.80152e-05 | 1.02944e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2894.13 | 0.0533518 | 980.441ms | 7376 | 640 | 1076.18 | 2430.54 | 0.0744343 | 1.77644 | 7.33134 | 1.44048 | 0.000729774 | 1.56758e-05 | 3.38937e-06 | 1(Win) | true |
| simdjson (ondemand) | 2835.31 | 0.0499418 | 981.775ms | 7376 | 2560 | 3930.14 | 2480.96 | 0.107338 | 1.81101 | 7.91283 | 1.64046 | 0.000867732 | 1.933e-05 | 5.29589e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3120.82 | 0.067039 | 967.427ms | 7376 | 2560 | 5845.21 | 2253.99 | 0.059754 | 1.64871 | 6.9577 | 1.36443 | 0.00078644 | 1.98596e-05 | 8.6323e-06 | 1(Win) | true |
| simdjson (ondemand) | 2971.92 | 0.207459 | 973.544ms | 7376 | 320 | 7715.79 | 2366.92 | 0.0254879 | 1.72692 | 7.56318 | 1.56657 | 0.00155699 | 6.77874e-06 | 1.27101e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1231.49 | 0.13295 | 1074.25ms | 4390 | 30 | 612.861 | 3399.63 | 0.0303862 | 4.1562 | 17.0002 | 3.11367 | 0.00157175 | 3.79651e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1095.03 | 0.0643461 | 1118.25ms | 4390 | 1280 | 7746.98 | 3823.31 | 0.0529313 | 4.66169 | 18.2435 | 3.34465 | 0.00392173 | 3.86176e-05 | 1.31691e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1371.22 | 0.0354758 | 1065.3ms | 4390 | 4890 | 5737.04 | 3053.22 | 0.14962 | 3.73469 | 15.59 | 2.79772 | 0.00146121 | 4.91916e-05 | 1.88661e-05 | 1(Win) | true |
| simdjson (ondemand) | 1198.81 | 0.0377622 | 1103.98ms | 4390 | 4890 | 8504.61 | 3492.33 | 0.0614867 | 4.26079 | 16.8734 | 3.03759 | 0.00451351 | 3.95489e-05 | 1.70493e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2889.99 | 0.0448113 | 1117.89ms | 11521 | 2560 | 7430.25 | 3801.84 | 0.0186142 | 1.76598 | 7.43573 | 1.2301 | 0.000692011 | 2.05128e-05 | 3.52617e-06 | 1(Win) | true |
| simdjson (ondemand) | 2615.62 | 0.0332661 | 1156.79ms | 11521 | 4890 | 9548.73 | 4200.64 | 0.20934 | 1.943 | 7.82554 | 1.3149 | 0.00106712 | 2.67672e-05 | 1.14666e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3189.26 | 0.0886422 | 1107.12ms | 11521 | 80 | 746.056 | 3445.09 | 0.00108849 | 1.60488 | 6.8764 | 1.10537 | 0.000736698 | 2.38695e-05 | 9.76478e-06 | 1(Win) | true |
| simdjson (ondemand) | 2856.62 | 0.0589221 | 1141.23ms | 11521 | 1280 | 6574.19 | 3846.25 | 0.0783226 | 1.78777 | 7.30345 | 1.1979 | 0.000906836 | 3.24814e-05 | 1.80377e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 681.306 | 0.0551935 | 1352.76ms | 4390 | 1280 | 14724.2 | 6145.01 | 0.0891507 | 7.45125 | 31.8153 | 6.98679 | 0.00777815 | 9.44974e-05 | 4.18209e-05 | 1(Win) | true |
| simdjson (ondemand) | 584.118 | 0.0525223 | 1457.8ms | 4390 | 4890 | 69298.5 | 7167.44 | 0.127478 | 8.69232 | 36.6321 | 8.57176 | 0.0139457 | 7.68152e-05 | 3.81514e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 717.442 | 0.0658883 | 1336.92ms | 4390 | 30 | 443.5 | 5835.5 | 0.0947321 | 6.9666 | 30.3465 | 6.65945 | 0.00766894 | 1.5186e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 614.448 | 0.063875 | 1438.83ms | 4390 | 1280 | 24245.4 | 6813.64 | 0.0522088 | 8.2727 | 35.2335 | 8.259 | 0.0140821 | 2.79399e-05 | 7.11845e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1713.93 | 0.0647391 | 1380.51ms | 11521 | 4890 | 84224 | 6410.58 | 0.0241921 | 2.96485 | 12.9695 | 2.67173 | 0.00298853 | 3.64587e-05 | 1.42711e-05 | 1(Win) | true |
| simdjson (ondemand) | 1466.53 | 0.0617332 | 1488.59ms | 11521 | 1280 | 27380.7 | 7492.01 | 0.0150033 | 3.46519 | 14.7414 | 3.28487 | 0.00529631 | 8.97817e-05 | 5.2011e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1815.39 | 0.0695836 | 1366.14ms | 11521 | 30 | 532.079 | 6052.3 | 0.0898537 | 2.80513 | 12.4318 | 2.55134 | 0.00321442 | 2.89327e-05 | 1.44663e-05 | 1(Win) | true |
| simdjson (ondemand) | 1541.42 | 0.0483169 | 1477.26ms | 11521 | 160 | 1897.82 | 7128.02 | 0.0131506 | 3.3 | 14.1772 | 3.15971 | 0.00533211 | 1.57321e-05 | 8.6798e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2048.95 | 0.124781 | 963.998ms | 4390 | 160 | 1040.11 | 2043.31 | 0.0156022 | 2.51846 | 10.6098 | 1.92688 | 0.00183514 | 1.70843e-05 | 5.69476e-06 | 1(Win) | true |
| jsonifier (generic) | 1980.23 | 0.0916855 | 949.772ms | 4390 | 80 | 300.6 | 2114.21 | 0.000591233 | 2.60306 | 10.7961 | 2.01868 | 0.00163724 | 6.54897e-05 | 2.84738e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2123.65 | 0.0420403 | 933.208ms | 4390 | 4890 | 3358.95 | 1971.43 | 0.189711 | 2.42648 | 10.2558 | 1.8467 | 0.00217095 | 2.30585e-05 | 5.68312e-06 | 1(Win) | true |
| jsonifier (generic) | 2050.66 | 0.101461 | 945.799ms | 4390 | 640 | 2746.12 | 2041.6 | 0.109094 | 2.51595 | 10.5007 | 1.94989 | 0.00102079 | 2.06435e-05 | 6.76253e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4492.77 | 0.0598895 | 988.082ms | 11521 | 2560 | 5491.53 | 2445.55 | 0.0115817 | 1.14063 | 4.91329 | 0.77259 | 0.000599551 | 1.13244e-05 | 3.18711e-06 | 1(Win) | true |
| jsonifier (generic) | 4405.06 | 0.0581143 | 992.393ms | 11521 | 2560 | 5378.77 | 2494.24 | 0.151091 | 1.15853 | 4.98169 | 0.800104 | 0.000418936 | 2.24454e-05 | 7.73045e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4671.53 | 0.0611689 | 969.279ms | 11521 | 1280 | 2649.32 | 2351.97 | 0.0341586 | 1.10243 | 4.7784 | 0.742036 | 0.000719813 | 1.24094e-05 | 3.7296e-06 | 1(Win) | true |
| jsonifier (generic) | 4576.7 | 0.0353595 | 978.08ms | 11521 | 4890 | 3523.7 | 2400.7 | 0.164743 | 1.11908 | 4.86911 | 0.773891 | 0.00032646 | 1.36853e-05 | 5.20078e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1672.45 | 0.0482658 | 995.404ms | 4390 | 4890 | 7138.6 | 2503.3 | 0.0127832 | 3.0717 | 13.9647 | 2.72893 | 0.00122774 | 5.00766e-05 | 2.75305e-05 | 1(Win) | true |
| simdjson (ondemand) | 1563.79 | 0.0639801 | 1003.72ms | 4390 | 2560 | 7511.04 | 2677.23 | 0.0772562 | 3.27752 | 14.1465 | 2.9934 | 0.0028464 | 2.96306e-05 | 8.98704e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1713.91 | 0.0271002 | 981.561ms | 4390 | 1280 | 560.927 | 2442.73 | 0.0189621 | 3.00034 | 13.6692 | 2.66014 | 0.00130908 | 3.84396e-05 | 1.15675e-05 | 1(Win) | true |
| simdjson (ondemand) | 1621.53 | 0.0619308 | 990.529ms | 4390 | 160 | 409.084 | 2581.9 | 0.0397152 | 3.1707 | 13.792 | 2.9123 | 0.00264806 | 1.28132e-05 | 2.84738e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3819.5 | 0.134358 | 1036.45ms | 11521 | 40 | 597.522 | 2876.62 | 0.201742 | 1.34278 | 6.18905 | 1.07074 | 0.000305963 | 1.30197e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3591.79 | 0.110571 | 1044.88ms | 11521 | 320 | 3660.93 | 3059 | 0.0106233 | 1.42586 | 6.26092 | 1.17898 | 0.00156969 | 1.32909e-05 | 4.61114e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3841.57 | 0.190012 | 1019.13ms | 11521 | 30 | 886.024 | 2860.1 | 0.123692 | 1.31106 | 6.07647 | 1.04453 | 0.000315366 | 4.3399e-05 | 5.78653e-06 | 1(Win) | true |
| simdjson (ondemand) | 3711.91 | 0.0352372 | 1030.45ms | 11521 | 2560 | 2785.03 | 2960.01 | 0.0334782 | 1.38209 | 6.12586 | 1.14808 | 0.00149669 | 1.50879e-05 | 6.40814e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1480.17 | 0.0519304 | 1035.75ms | 4669 | 2560 | 6247.52 | 3008.24 | 0.0350088 | 3.45847 | 14.1007 | 2.3444 | 0.00137944 | 6.29986e-05 | 2.08322e-05 | 1(Win) | true |
| jsonifier (generic) | 1407.64 | 0.0515721 | 1053.67ms | 4669 | 2560 | 6812.92 | 3163.24 | 0.126342 | 3.63987 | 13.1893 | 2.61876 | 0.00215852 | 9.01893e-05 | 4.56803e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1589.18 | 0.0372668 | 1018.4ms | 4669 | 4890 | 5331.57 | 2801.89 | 0.0620346 | 3.23701 | 13.3267 | 2.17521 | 0.00176533 | 2.39582e-05 | 7.92768e-06 | 1(Win) | true |
| jsonifier (generic) | 1509.7 | 0.037688 | 1033.79ms | 4669 | 4890 | 6041.99 | 2949.39 | 0.065218 | 3.39225 | 12.4112 | 2.45149 | 0.00248263 | 5.0413e-05 | 1.94907e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2744.78 | 0.0339491 | 1057.67ms | 9249 | 4890 | 5820.25 | 3213.57 | 0.0734867 | 1.86498 | 7.80225 | 1.21137 | 0.000539427 | 3.3254e-05 | 1.22713e-05 | 1(Win) | true |
| jsonifier (generic) | 2525.67 | 0.0628349 | 1084.93ms | 9249 | 1280 | 6163.81 | 3492.36 | 0.0170938 | 2.02401 | 7.43464 | 1.35874 | 0.00112225 | 4.79782e-05 | 2.09482e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2923.26 | 0.0336803 | 1041.1ms | 9249 | 4890 | 5050.29 | 3017.36 | 0.0606381 | 1.75072 | 7.42405 | 1.12931 | 0.000615951 | 1.83074e-05 | 7.42909e-06 | 1(Win) | true |
| jsonifier (generic) | 2697.73 | 0.0732732 | 1068.87ms | 9249 | 1280 | 7346.71 | 3269.61 | 0.0286574 | 1.89617 | 7.05438 | 1.27765 | 0.00113332 | 2.44959e-05 | 9.37601e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 438.577 | 0.024582 | 1755.63ms | 4669 | 4890 | 30457.8 | 10152.6 | 0.050051 | 11.5405 | 49.2913 | 10.3121 | 0.00446411 | 0.000123164 | 6.2852e-05 | 1(Win) | true |
| simdjson (ondemand) | 186.095 | 0.0605699 | 3137.85ms | 4669 | 640 | 134422 | 23927 | 0.0144167 | 27.203 | 125.378 | 34.9668 | 0.0413201 | 0.000144571 | 9.06913e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 451.291 | 0.0585116 | 1732.53ms | 4669 | 640 | 21330.4 | 9866.6 | 0.0937751 | 11.2388 | 48.5434 | 10.1514 | 0.00503922 | 6.02377e-05 | 2.54337e-05 | 1(Win) | true |
| simdjson (ondemand) | 188.825 | 0.0376123 | 3104.41ms | 4669 | 2560 | 201385 | 23581.1 | 0.166386 | 26.8383 | 124.637 | 34.8042 | 0.0412804 | 4.91105e-05 | 1.93263e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 843.67 | 0.038365 | 1785.63ms | 9249 | 320 | 5148.32 | 10455 | 0.128094 | 6.01729 | 25.6559 | 5.2343 | 0.00279828 | 2.97329e-05 | 9.79836e-06 | 1(Win) | true |
| simdjson (ondemand) | 369.254 | 0.0554078 | 3126.6ms | 9249 | 640 | 112114 | 23887.4 | 0.224555 | 13.7019 | 63.2228 | 17.5017 | 0.0238451 | 4.15585e-05 | 1.95967e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 868.077 | 0.0242326 | 1766.74ms | 9249 | 4890 | 29647.2 | 10161 | 0.0354796 | 5.82894 | 25.279 | 5.15332 | 0.00204932 | 3.0645e-05 | 9.22003e-06 | 1(Win) | true |
| simdjson (ondemand) | 375.725 | 0.0315115 | 3095.26ms | 9249 | 2560 | 140097 | 23476 | 0.00112148 | 13.4545 | 62.849 | 17.4197 | 0.0225414 | 1.83297e-05 | 4.60354e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3811.22 | 0.0690283 | 845.937ms | 4669 | 2560 | 1665 | 1168.31 | 0.18356 | 1.37059 | 5.89227 | 1.03812 | 0.000661778 | 1.40555e-05 | 3.51387e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 3802.45 | 0.105772 | 850.724ms | 4669 | 1280 | 1963.69 | 1171.01 | 0.0110069 | 1.37353 | 5.55365 | 0.823731 | 0.000214848 | 1.35535e-05 | 1.33862e-06 | 1(Tie) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 4088.06 | 0.0584969 | 843.001ms | 4669 | 4890 | 1985.12 | 1089.2 | 0.142559 | 1.2818 | 5.29064 | 0.770615 | 0.000215974 | 1.30084e-05 | 1.53298e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4081.31 | 0.0689944 | 842.076ms | 4669 | 4890 | 2770.66 | 1091 | 0.0382982 | 1.28001 | 5.64425 | 0.983723 | 0.000689357 | 1.42786e-05 | 6.4823e-06 | 1(Tie) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6375.89 | 0.0368419 | 871.353ms | 9249 | 4890 | 1270.28 | 1383.42 | 0.0393828 | 0.815764 | 3.65391 | 0.550222 | 0.000345298 | 1.15637e-05 | 3.67032e-06 | 1(Win) | true |
| jsonifier (generic) | 6349.28 | 0.144727 | 875.153ms | 9249 | 160 | 646.788 | 1389.22 | 0.0319322 | 0.819439 | 3.46567 | 0.432587 | 0.000165558 | 9.46048e-06 | 6.75749e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6750.62 | 0.0445768 | 869.695ms | 9249 | 1280 | 434.239 | 1306.62 | 0.418456 | 0.772299 | 3.3329 | 0.405774 | 0.000126618 | 7.43324e-06 | 7.60217e-07 | 1(Win) | true |
| simdjson (ondemand) | 6734.62 | 0.0466165 | 862.661ms | 9249 | 4890 | 1822.86 | 1309.73 | 0.0123458 | 0.773717 | 3.52871 | 0.522759 | 0.000371786 | 1.63838e-05 | 8.31351e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2384.39 | 0.0586001 | 918.201ms | 4669 | 320 | 383.213 | 1867.44 | 0.0366612 | 2.16594 | 9.57357 | 1.89184 | 0.000759665 | 2.00792e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2008.82 | 0.0376126 | 953.863ms | 4669 | 4890 | 3398.92 | 2216.58 | 0.0589209 | 2.55791 | 11.3076 | 2.70058 | 0.00211813 | 1.93593e-05 | 6.92029e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2519.66 | 0.0627887 | 910.2ms | 4669 | 2560 | 3151.86 | 1767.19 | 0.0177687 | 2.0506 | 9.31099 | 1.83872 | 0.000588322 | 2.04976e-05 | 7.19506e-06 | 1(Win) | true |
| simdjson (ondemand) | 2095.82 | 0.0556401 | 944.727ms | 4669 | 160 | 223.581 | 2124.56 | 0.101889 | 2.45911 | 11.0595 | 2.64618 | 0.00211903 | 1.87406e-05 | 6.69308e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4213.79 | 0.0442479 | 943.807ms | 9249 | 4890 | 4195.07 | 2093.26 | 0.0293451 | 1.22108 | 5.4913 | 0.970484 | 0.00028204 | 1.16301e-05 | 3.13968e-06 | 1(Win) | true |
| simdjson (ondemand) | 3630.37 | 0.049571 | 973.94ms | 9249 | 4890 | 7093.35 | 2429.65 | 0.0470736 | 1.41494 | 6.37431 | 1.38588 | 0.00128351 | 1.93245e-05 | 9.30847e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4402.42 | 0.0677273 | 935.804ms | 9249 | 2560 | 4713.85 | 2003.57 | 0.08412 | 1.17046 | 5.35874 | 0.94367 | 0.000404647 | 1.35994e-05 | 5.11035e-06 | 1(Win) | true |
| simdjson (ondemand) | 3760.18 | 0.0588679 | 967.874ms | 9249 | 320 | 610.208 | 2345.77 | 0.0427448 | 1.36873 | 6.24911 | 1.35842 | 0.00122108 | 1.52043e-05 | 5.06812e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 558.721 | 0.0350147 | 1530.27ms | 4604 | 2560 | 19383 | 7858.52 | 0.0594951 | 9.08874 | 36.4221 | 6.97774 | 0.0108539 | 0.000147375 | 6.09185e-05 | 1(Win) | true |
| jsonifier (generic) | 540.142 | 0.0445802 | 1553.22ms | 4604 | 1280 | 16809.3 | 8128.82 | 0.0611261 | 9.39866 | 35.7183 | 7.37707 | 0.0104194 | 0.000112165 | 4.78524e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 641.578 | 0.0822097 | 1518.49ms | 4604 | 640 | 20258 | 6843.62 | 0.0889408 | 7.91985 | 31.954 | 5.96568 | 0.00881536 | 6.85545e-05 | 2.40959e-05 | 1(Win) | true |
| jsonifier (generic) | 609.76 | 0.0247735 | 1552.1ms | 4604 | 4890 | 15561 | 7200.73 | 0.0522081 | 8.32053 | 31.127 | 6.3396 | 0.00928947 | 8.2528e-05 | 3.42016e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2646.74 | 0.095653 | 1623.18ms | 24579 | 640 | 45928.6 | 8856.31 | 0.0765639 | 1.91807 | 7.90579 | 1.34383 | 0.00182314 | 7.09447e-05 | 5.07293e-05 | 1(Win) | true |
| jsonifier (generic) | 2523.89 | 0.096805 | 1667.79ms | 24579 | 640 | 51732.6 | 9287.4 | 0.098466 | 2.00437 | 7.72603 | 1.42795 | 0.00217487 | 3.71888e-05 | 1.69733e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2982.3 | 0.0260745 | 1618.14ms | 24579 | 4890 | 20538.4 | 7859.83 | 0.00361967 | 1.69732 | 7.08857 | 1.15847 | 0.00149839 | 1.31124e-05 | 3.28643e-06 | 1(Win) | true |
| jsonifier (generic) | 2835.03 | 0.0703207 | 1665.54ms | 24579 | 320 | 10817.6 | 8268.12 | 0.0622109 | 1.79197 | 6.86185 | 1.2329 | 0.00184838 | 2.19954e-05 | 1.29684e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 225.843 | 0.0275709 | 2686.16ms | 4604 | 1280 | 36776.2 | 19441.4 | 0.0356486 | 22.4149 | 93.126 | 21.4881 | 0.0172888 | 0.000223142 | 0.00010928 | 1(Win) | true |
| simdjson (ondemand) | 148.03 | 0.0192533 | 3708.13ms | 4604 | 2560 | 83487.1 | 29660.9 | 0.064065 | 34.1666 | 145.906 | 41.573 | 0.0522905 | 0.000229505 | 0.000133461 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 237.208 | 0.0601303 | 2686.69ms | 4604 | 30 | 3716.38 | 18510 | 0.0527365 | 21.3665 | 88.8091 | 20.5026 | 0.0162395 | 7.96409e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 153.264 | 0.0252616 | 3693.96ms | 4604 | 1280 | 67038.5 | 28648.1 | 0.0193522 | 33.006 | 141.545 | 40.5778 | 0.0498951 | 0.000199555 | 0.000102832 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1152.34 | 0.0314927 | 2773.49ms | 24579 | 2560 | 105057 | 20341.5 | 0.146143 | 4.42868 | 18.4563 | 4.06483 | 0.00353201 | 0.000123295 | 8.34681e-05 | 1(Win) | true |
| simdjson (ondemand) | 765.137 | 0.0645069 | 3802.24ms | 24579 | 160 | 62486.1 | 30635.5 | 0.0264877 | 6.61245 | 28.4014 | 7.82056 | 0.00910177 | 9.12873e-05 | 6.10277e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1200.55 | 0.0146659 | 2790.51ms | 24579 | 4890 | 40095.6 | 19524.7 | 0.24329 | 4.21493 | 17.6419 | 3.87929 | 0.00313758 | 3.27644e-05 | 1.81211e-05 | 1(Win) | true |
| simdjson (ondemand) | 792.979 | 0.035037 | 3800.91ms | 24579 | 640 | 68649.7 | 29559.9 | 0.0527333 | 6.37966 | 27.585 | 7.63435 | 0.00892835 | 3.58538e-05 | 2.11054e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3246.9 | 0.0878101 | 865.987ms | 4604 | 1280 | 1804.82 | 1352.28 | 0.00889779 | 1.60307 | 6.20547 | 1.0152 | 0.000587465 | 2.17202e-05 | 5.76944e-06 | 1(Win) | true |
| simdjson (ondemand) | 2732.63 | 0.377884 | 893.69ms | 4604 | 40 | 1474.64 | 1606.78 | 0.0554634 | 1.90075 | 7.94852 | 1.6957 | 0.000841659 | 0.000114031 | 5.43006e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3325.13 | 0.0427753 | 865.724ms | 4604 | 2560 | 816.733 | 1320.46 | 0.0674024 | 1.56888 | 6.12163 | 0.996091 | 0.000589501 | 1.89204e-05 | 4.7513e-06 | 1(Win) | true |
| simdjson (ondemand) | 2791.22 | 0.0612797 | 890.947ms | 4604 | 640 | 594.699 | 1573.05 | 0.0679876 | 1.86122 | 7.86664 | 1.67615 | 0.000936685 | 8.82385e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10612.6 | 0.0360151 | 960.377ms | 24579 | 4890 | 3094.31 | 2208.73 | 0.144108 | 0.484423 | 2.10415 | 0.220839 | 0.000137123 | 8.23687e-06 | 2.30466e-06 | 1(Win) | true |
| simdjson (ondemand) | 9049.33 | 0.0476683 | 997.166ms | 24579 | 2560 | 3902.97 | 2590.29 | 0.123434 | 0.566316 | 2.60344 | 0.36104 | 0.000173214 | 7.00865e-06 | 1.31909e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10764.2 | 0.0166227 | 954.701ms | 24579 | 1280 | 167.716 | 2177.62 | 0.0609553 | 0.478425 | 2.08845 | 0.217259 | 0.000143161 | 6.67491e-06 | 8.58202e-07 | 1(Win) | true |
| simdjson (ondemand) | 9117.6 | 0.0756473 | 992.967ms | 24579 | 640 | 2420.67 | 2570.89 | 0.0146493 | 0.563188 | 2.5881 | 0.357378 | 0.000180159 | 4.57708e-06 | 6.35705e-08 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1786.29 | 0.0463271 | 976.016ms | 4604 | 2560 | 3319.53 | 2458.01 | 0.0205282 | 2.88688 | 12.4089 | 2.64294 | 0.00132646 | 2.13809e-05 | 2.63019e-06 | 1(Win) | true |
| simdjson (ondemand) | 1334.59 | 0.0440026 | 1061.7ms | 4604 | 4890 | 10248 | 3289.93 | 0.0822041 | 3.89208 | 16.7333 | 4.61164 | 0.00156968 | 5.82316e-05 | 3.87766e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1804.5 | 0.0707024 | 973.745ms | 4604 | 30 | 88.7862 | 2433.2 | 0.0082203 | 2.85063 | 12.3254 | 2.62381 | 0.00150594 | 7.24008e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1333.96 | 0.0415691 | 1058.13ms | 4604 | 2560 | 4792.59 | 3291.5 | 0.0297672 | 3.85371 | 16.6527 | 4.59209 | 0.00172786 | 1.87507e-05 | 6.95727e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7110.83 | 0.0385161 | 1060.29ms | 24579 | 4890 | 7882.82 | 3296.43 | 0.145251 | 0.724409 | 3.26563 | 0.52553 | 0.000291901 | 8.71943e-06 | 1.77217e-06 | 1(Win) | true |
| simdjson (ondemand) | 5422.27 | 0.110548 | 1163.18ms | 24579 | 320 | 7308.34 | 4322.98 | 0.0783494 | 0.940145 | 4.24936 | 0.90736 | 0.000338322 | 7.7556e-06 | 1.77997e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7235.54 | 0.147638 | 1060.46ms | 24579 | 640 | 14640.7 | 3239.61 | 0.0610979 | 0.719126 | 3.25001 | 0.52195 | 0.000292361 | 1.32227e-05 | 5.33992e-06 | 1(Win) | true |
| simdjson (ondemand) | 5485.48 | 0.0446175 | 1163.32ms | 24579 | 1280 | 4652.85 | 4273.16 | 0.0803975 | 0.930135 | 4.23427 | 0.903698 | 0.000300403 | 6.67491e-06 | 1.17605e-06 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 741.02 | 0.0386104 | 880.106ms | 1181 | 4890 | 1684.06 | 1519.92 | 0.191088 | 7.01839 | 29.2396 | 5.04234 | 0.00321294 | 0.000165712 | 6.78777e-05 | 1(Win) | true |
| jsonifier (generic) | 673.002 | 0.079793 | 895.188ms | 1181 | 320 | 570.62 | 1673.53 | 0.219486 | 7.71219 | 28.8544 | 5.7663 | 0.00484229 | 0.000230207 | 8.20279e-05 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 999.843 | 0.19638 | 857.603ms | 1181 | 30 | 146.809 | 1126.47 | 0.144786 | 5.35507 | 22.5038 | 3.54784 | 0.00189105 | 2.82247e-05 | 2.82247e-05 | 1(Win) | true |
| jsonifier (generic) | 897.156 | 0.0884234 | 867.392ms | 1181 | 160 | 197.16 | 1255.4 | 0.157073 | 5.82413 | 22.3065 | 4.29805 | 0.00387384 | 2.11685e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1521.24 | 0.0578503 | 887.269ms | 2496 | 2560 | 2097.7 | 1564.76 | 0.169766 | 3.42026 | 14.5156 | 2.39503 | 0.0015348 | 0.000133964 | 6.21307e-05 | 1(Win) | true |
| jsonifier (generic) | 1341.89 | 0.0694173 | 908.409ms | 2496 | 160 | 242.611 | 1773.89 | 0.0144435 | 3.85538 | 14.6234 | 2.80409 | 0.00241637 | 1.7528e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1988.64 | 0.0455942 | 860.815ms | 2496 | 640 | 190.624 | 1196.99 | 0.0813902 | 2.62982 | 11.3285 | 1.6879 | 0.000805038 | 4.19421e-05 | 1.252e-05 | 1(Win) | true |
| jsonifier (generic) | 1723.62 | 0.144789 | 881.04ms | 2496 | 1280 | 5117.86 | 1381.03 | 0.347753 | 3.01582 | 11.5252 | 2.10938 | 0.00252341 | 6.82342e-05 | 2.44141e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 516.36 | 0.0924241 | 946.736ms | 1181 | 1280 | 5202.05 | 2181.21 | 0.0637238 | 10.0581 | 38.7587 | 8.24302 | 0.00424627 | 0.000246745 | 0.000109812 | 1(Win) | true |
| simdjson (ondemand) | 407.425 | 0.213521 | 1005.89ms | 1181 | 320 | 11149 | 2764.41 | 0.00859209 | 12.6731 | 53.5182 | 12.7257 | 0.00879551 | 5.02752e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 624.428 | 0.0932598 | 924.665ms | 1181 | 160 | 452.734 | 1803.71 | 0.0401787 | 8.28366 | 32.21 | 6.77477 | 0.00328641 | 0.000121719 | 4.2337e-05 | 1(Win) | true |
| simdjson (ondemand) | 469.91 | 0.0467244 | 988.716ms | 1181 | 2560 | 3210.69 | 2396.82 | 0.0332361 | 10.9454 | 46.7807 | 11.2312 | 0.0065748 | 0.000121057 | 4.96137e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1042.68 | 0.0507098 | 958.527ms | 2496 | 2560 | 3430.95 | 2282.94 | 0.116762 | 4.93836 | 19.2853 | 3.97556 | 0.00243421 | 4.38201e-05 | 1.20505e-05 | 1(Win) | true |
| simdjson (ondemand) | 854.55 | 0.0902481 | 1014.93ms | 2496 | 80 | 505.569 | 2785.53 | 0.107584 | 6.11518 | 26.0032 | 6.03045 | 0.00529347 | 0.0001252 | 8.51362e-05 | 2(Loss) | true |

----
### Mesh Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1264.61 | 0.0682131 | 930.796ms | 2496 | 640 | 1055.09 | 1882.3 | 0.0320522 | 4.16331 | 16.1867 | 3.28085 | 0.00227489 | 0.000130834 | 6.94862e-05 | 1(Win) | true |
| simdjson (ondemand) | 980.502 | 0.101693 | 990.319ms | 2496 | 2560 | 15603.4 | 2427.71 | 0.104526 | 5.26162 | 22.8153 | 5.32332 | 0.00318009 | 7.41812e-05 | 2.25361e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2383.14 | 0.0325274 | 780.208ms | 1181 | 640 | 15.1245 | 472.608 | 0.120819 | 2.29818 | 7.91956 | 1.48264 | 0.000849386 | 3.83679e-05 | 1.32303e-06 | 1(Win) | true |
| simdjson (ondemand) | 2065.19 | 0.233745 | 785.474ms | 1181 | 160 | 260.008 | 545.369 | 0.471074 | 2.65669 | 10.1931 | 1.93311 | 0.000889077 | 7.40898e-05 | 2.64606e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2720.88 | 0.092404 | 773.969ms | 1181 | 320 | 46.8181 | 413.944 | 0.040783 | 2.04669 | 7.0398 | 1.28112 | 0.000965813 | 7.67358e-05 | 1.85224e-05 | 1(Win) | true |
| simdjson (ondemand) | 2303.63 | 0.172598 | 782.017ms | 1181 | 160 | 113.937 | 488.919 | 0.0140597 | 2.38081 | 9.29467 | 1.7265 | 0.000957875 | 4.2337e-05 | 0 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4440.34 | 0.200246 | 785.922ms | 2496 | 640 | 737.506 | 536.078 | 0 | 1.22421 | 4.48558 | 0.736779 | 0.000410031 | 3.13001e-05 | 7.51202e-06 | 1(Win) | true |
| simdjson (ondemand) | 4005.38 | 0.082311 | 789.035ms | 2496 | 320 | 76.5717 | 594.294 | 0.0294554 | 1.34871 | 5.50681 | 0.92508 | 0.000436949 | 2.00321e-05 | 1.252e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5027.22 | 0.0373111 | 781.68ms | 2496 | 2560 | 79.9007 | 473.497 | 0.0939592 | 1.09586 | 4.06931 | 0.641426 | 0.000464493 | 3.05176e-05 | 6.72952e-06 | 1(Win) | true |
| simdjson (ondemand) | 4444 | 0.233573 | 785.337ms | 2496 | 80 | 125.221 | 535.638 | 0.0816117 | 1.22353 | 5.08173 | 0.827324 | 0.000405649 | 5.00801e-05 | 5.00801e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2174.62 | 0.189882 | 784.58ms | 1181 | 40 | 38.6865 | 517.925 | 0.443711 | 2.50191 | 8.55207 | 1.65453 | 0.000867909 | 4.2337e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1881.74 | 0.0928044 | 790.056ms | 1181 | 4890 | 1508.78 | 598.536 | 0.109448 | 2.8641 | 10.9119 | 2.13125 | 0.00102475 | 5.22936e-05 | 9.69682e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2429.02 | 0.0457443 | 780.54ms | 1181 | 640 | 28.7934 | 463.681 | 0.0518676 | 2.26594 | 7.67062 | 1.45301 | 0.00103461 | 2.38146e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2134 | 0.0919431 | 786.255ms | 1181 | 640 | 150.705 | 527.783 | 0.0500074 | 2.55455 | 10.0169 | 1.92464 | 0.000943321 | 7.14437e-05 | 1.05843e-05 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4081.71 | 0.0655234 | 789.544ms | 2496 | 640 | 93.4497 | 583.18 | 0.0955588 | 1.32466 | 4.78486 | 0.818109 | 0.000403771 | 2.31621e-05 | 4.38201e-06 | 1(Win) | true |
| simdjson (ondemand) | 3740.38 | 0.0359832 | 792.801ms | 2496 | 2560 | 134.245 | 636.399 | 0.145745 | 1.44227 | 5.84696 | 1.01883 | 0.000418952 | 1.86235e-05 | 1.878e-06 | 2(Loss) | true |

----
### Mesh Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4562.66 | 0.0644872 | 785.338ms | 2496 | 4890 | 553.49 | 521.707 | 0.026576 | 1.19404 | 4.36779 | 0.722756 | 0.000491502 | 4.47342e-05 | 1.97453e-05 | 1(Win) | true |
| simdjson (ondemand) | 4157.01 | 0.146518 | 788.109ms | 2496 | 2560 | 1801.97 | 572.617 | 0.316367 | 1.29392 | 5.42348 | 0.921074 | 0.000415196 | 2.09711e-05 | 4.38201e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1281.84 | 0.0335712 | 1104.12ms | 4926 | 4890 | 7402.27 | 3664.89 | 0.0190587 | 3.99488 | 16.037 | 2.94459 | 0.00425637 | 7.32311e-05 | 2.0591e-05 | 1(Win) | true |
| simdjson (ondemand) | 1077.37 | 0.0399482 | 1175.11ms | 4926 | 4890 | 14837.7 | 4360.44 | 0.169602 | 4.72618 | 17.622 | 3.24442 | 0.00432391 | 5.68329e-05 | 1.3243e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1570.13 | 0.134881 | 1080.92ms | 4926 | 80 | 1302.89 | 2991.97 | 0.0509957 | 3.26714 | 13.418 | 2.41332 | 0.00436967 | 2.2838e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1258.3 | 0.130165 | 1148.58ms | 4926 | 320 | 7557.14 | 3733.44 | 0.0157337 | 4.07039 | 15.0278 | 2.71681 | 0.00552997 | 7.23203e-05 | 2.72787e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2288.41 | 0.0448712 | 1136.99ms | 9463 | 2560 | 8016.11 | 3943.61 | 0.160366 | 2.22645 | 8.99271 | 1.54845 | 0.00235448 | 3.82658e-05 | 1.49018e-05 | 1(Win) | true |
| simdjson (ondemand) | 1959.38 | 0.0330769 | 1199.75ms | 9463 | 4890 | 11349.6 | 4605.86 | 0.0361839 | 2.59168 | 9.82838 | 1.71658 | 0.00192062 | 4.2097e-05 | 1.7418e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2761.26 | 0.107745 | 1107.67ms | 9463 | 80 | 992.035 | 3268.3 | 0.240764 | 1.85521 | 7.6332 | 1.27264 | 0.00249524 | 6.60467e-06 | 1.32093e-06 | 1(Win) | true |
| simdjson (ondemand) | 2280.84 | 0.0512156 | 1175.51ms | 9463 | 2560 | 10512.6 | 3956.7 | 0.0227114 | 2.22926 | 8.47797 | 1.44193 | 0.00227733 | 1.75849e-05 | 4.25176e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 591.977 | 0.028164 | 1542.73ms | 4926 | 4890 | 24427.4 | 7935.78 | 0.0715429 | 8.54878 | 36.8183 | 7.72574 | 0.00739858 | 8.72629e-05 | 2.98487e-05 | 1(Win) | true |
| simdjson (ondemand) | 411.687 | 0.0434265 | 1880.07ms | 4926 | 2560 | 62864.3 | 11411.1 | 0.160467 | 12.2533 | 56.1401 | 14.0743 | 0.0146392 | 6.43112e-05 | 2.11727e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 656.566 | 0.130936 | 1502.6ms | 4926 | 320 | 28086.7 | 7155.11 | 0.0216145 | 7.73506 | 34.205 | 7.19854 | 0.00726629 | 7.9933e-05 | 4.37728e-05 | 1(Win) | true |
| simdjson (ondemand) | 446.742 | 0.050642 | 1838.06ms | 4926 | 1280 | 36300.1 | 10515.7 | 0.137722 | 11.3671 | 53.543 | 13.5471 | 0.0132064 | 8.3105e-05 | 4.55174e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1102.25 | 0.0333161 | 1567.96ms | 9463 | 4890 | 36384 | 8187.42 | 0.27678 | 4.58167 | 19.8217 | 4.03096 | 0.0035776 | 5.59277e-05 | 2.22803e-05 | 1(Win) | true |
| simdjson (ondemand) | 789.82 | 0.169263 | 1888.51ms | 9463 | 40 | 14961.8 | 11426.2 | 0.12143 | 6.42513 | 29.7297 | 7.31755 | 0.00756895 | 5.28374e-05 | 2.90606e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1214.55 | 0.040428 | 1529.34ms | 9463 | 2560 | 23101.2 | 7430.44 | 0.0875809 | 4.16049 | 18.4601 | 3.75589 | 0.00349375 | 1.93187e-05 | 4.74711e-06 | 1(Win) | true |
| simdjson (ondemand) | 843.205 | 0.0264837 | 1845.31ms | 9463 | 4890 | 39287.7 | 10702.8 | 0.0524593 | 6.01323 | 28.3778 | 7.04312 | 0.00701784 | 3.1724e-05 | 1.04162e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2204.47 | 0.0686064 | 946.318ms | 4926 | 1280 | 2736.03 | 2131.04 | 0.0357935 | 2.33626 | 9.42509 | 1.73853 | 0.00303856 | 3.67946e-05 | 1.23706e-05 | 1(Win) | true |
| simdjson (ondemand) | 2119.58 | 0.0619448 | 953.086ms | 4926 | 2560 | 4825.44 | 2216.38 | 0.0627918 | 2.42783 | 9.58567 | 1.68473 | 0.00225692 | 2.5217e-05 | 1.13397e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2377.98 | 0.0363873 | 940.984ms | 4926 | 4890 | 2526.86 | 1975.54 | 0.0174286 | 2.17041 | 8.82136 | 1.60495 | 0.00277809 | 2.56143e-05 | 3.90234e-06 | 1(Win) | true |
| simdjson (ondemand) | 2285.82 | 0.0359348 | 948.831ms | 4926 | 640 | 349.071 | 2055.19 | 0.00463787 | 2.25704 | 8.99371 | 1.54974 | 0.00252328 | 1.1419e-05 | 2.22036e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3770.44 | 0.102977 | 975.407ms | 9463 | 1280 | 7776.19 | 2393.52 | 0.00424305 | 1.35988 | 5.55004 | 0.919053 | 0.00167932 | 2.40245e-05 | 6.357e-06 | 1(Win) | true |
| simdjson (ondemand) | 3633.22 | 0.0458851 | 978.02ms | 9463 | 2560 | 3325.51 | 2483.92 | 0.112395 | 1.41296 | 5.64007 | 0.90204 | 0.00159635 | 2.21256e-05 | 6.23316e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4061.07 | 0.0503903 | 967.715ms | 9463 | 4890 | 6131.68 | 2222.23 | 0.0493075 | 1.26844 | 5.23576 | 0.849519 | 0.00151491 | 3.52897e-05 | 1.59701e-05 | 1(Win) | true |
| simdjson (ondemand) | 3915.35 | 0.0382327 | 971.322ms | 9463 | 4890 | 3797.48 | 2304.94 | 0.110957 | 1.31344 | 5.33192 | 0.831766 | 0.00150421 | 1.37442e-05 | 1.94493e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1553.06 | 0.0541549 | 1035.11ms | 4926 | 320 | 858.693 | 3024.87 | 0.0678289 | 3.30093 | 14.43 | 2.91291 | 0.00263208 | 1.52253e-05 | 1.26878e-06 | 1(Win) | true |
| simdjson (ondemand) | 1421.11 | 0.0584501 | 1063.81ms | 4926 | 1280 | 4778.78 | 3305.74 | 0.0238402 | 3.60184 | 14.9685 | 3.29233 | 0.0059428 | 4.71034e-05 | 1.95075e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1642.88 | 0.0499321 | 1026.61ms | 4926 | 2560 | 5218.89 | 2859.5 | 0.0217566 | 3.12117 | 13.7952 | 2.77243 | 0.00252923 | 4.96409e-05 | 2.22036e-05 | 1(Win) | true |
| simdjson (ondemand) | 1511.12 | 0.0345762 | 1051.96ms | 4926 | 4890 | 5650.1 | 3108.83 | 0.0136747 | 3.38066 | 14.3419 | 3.15063 | 0.00445506 | 1.94702e-05 | 5.68745e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2756.18 | 0.0868039 | 1062.19ms | 9463 | 160 | 1292.54 | 3274.32 | 0.106016 | 1.85856 | 8.15619 | 1.5308 | 0.00162277 | 9.24654e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2545.35 | 0.0373231 | 1086.48ms | 9463 | 2560 | 4482.91 | 3545.54 | 0.0109194 | 2.00667 | 8.44383 | 1.73972 | 0.00263857 | 1.81216e-05 | 5.86165e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2906.56 | 0.087648 | 1055.22ms | 9463 | 640 | 4739.82 | 3104.91 | 0.0299515 | 1.74831 | 7.82574 | 1.45768 | 0.00161715 | 3.02164e-05 | 1.22186e-05 | 1(Win) | true |
| simdjson (ondemand) | 2716.04 | 0.139687 | 1072.62ms | 9463 | 320 | 6893.66 | 3322.71 | 0.00188103 | 1.88236 | 8.11762 | 1.66596 | 0.00210821 | 9.24654e-06 | 2.9721e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2137.79 | 0.0731477 | 861.337ms | 2821 | 4890 | 4143.68 | 1258.46 | 0.000139965 | 2.43345 | 8.53811 | 1.51259 | 0.000358471 | 5.05267e-05 | 1.38459e-05 | 1(Win) | true |
| simdjson (ondemand) | 2080.26 | 0.0672075 | 863.72ms | 2821 | 1280 | 966.977 | 1293.26 | 0.0487137 | 2.50378 | 8.65402 | 1.42928 | 0.000747463 | 3.76639e-05 | 5.53882e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2357.93 | 0.0958515 | 857.058ms | 2821 | 80 | 95.6821 | 1140.96 | 0.00109558 | 2.22157 | 7.95711 | 1.36335 | 0.000354484 | 8.86211e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2224.41 | 0.285905 | 861.03ms | 2821 | 320 | 3826.22 | 1209.45 | 0.0892211 | 2.34762 | 8.27189 | 1.33073 | 0.000732231 | 5.42804e-05 | 1.44009e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2972.95 | 0.0494696 | 868.359ms | 4147 | 2560 | 1108.69 | 1330.29 | 0.0255237 | 1.75041 | 6.24259 | 1.02508 | 0.000423122 | 4.03153e-05 | 1.4035e-05 | 1(Win) | true |
| simdjson (ondemand) | 2897.09 | 0.101605 | 870.869ms | 4147 | 80 | 153.908 | 1365.12 | 0.0146528 | 1.79935 | 6.32747 | 0.990354 | 0.000533518 | 2.10996e-05 | 3.01423e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3215.35 | 0.0443924 | 866.473ms | 4147 | 4890 | 1457.94 | 1230 | 0.0419365 | 1.62061 | 5.89173 | 0.933446 | 0.000254551 | 6.08516e-05 | 2.02674e-05 | 1(Win) | true |
| simdjson (ondemand) | 3123.41 | 0.0398059 | 869.268ms | 4147 | 640 | 162.587 | 1266.21 | 0.0845809 | 1.67193 | 6.06752 | 0.923318 | 0.000244906 | 2.07228e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 732.739 | 0.0654114 | 1104.15ms | 2821 | 320 | 1845.72 | 3671.59 | 0.0541026 | 6.97724 | 27.7051 | 5.26551 | 0.00137584 | 2.10475e-05 | 6.64658e-06 | 1(Win) | true |
| simdjson (ondemand) | 297.389 | 0.0398269 | 1642.74ms | 2821 | 1280 | 16615.8 | 9046.46 | 0.0468548 | 17.0496 | 74.9724 | 19.8483 | 0.0103825 | 6.03731e-05 | 1.82781e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 753.002 | 0.042885 | 1099.89ms | 2821 | 2560 | 6009.88 | 3572.79 | 0.0788437 | 6.77926 | 27.1879 | 5.13116 | 0.00115512 | 4.08488e-05 | 6.92352e-06 | 1(Win) | true |
| simdjson (ondemand) | 299.5 | 0.0295278 | 1641.86ms | 2821 | 2560 | 18010.1 | 8982.7 | 0.0533384 | 16.9105 | 74.5899 | 19.7512 | 0.010231 | 7.54664e-05 | 2.88018e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1046.59 | 0.087211 | 1112.74ms | 4147 | 1280 | 13901.6 | 3778.82 | 0.0134986 | 4.87422 | 19.3685 | 3.58066 | 0.000780685 | 4.37063e-05 | 1.1115e-05 | 1(Win) | true |
| simdjson (ondemand) | 442.656 | 0.0775633 | 1648.4ms | 4147 | 320 | 15367.3 | 8934.44 | 0.0351745 | 11.4682 | 50.8107 | 13.368 | 0.00806909 | 0.00019065 | 0.000138654 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1068.97 | 0.0842358 | 1111.09ms | 4147 | 4890 | 47493.9 | 3699.71 | 0.150068 | 4.76316 | 19.0166 | 3.48927 | 0.000638745 | 9.75895e-05 | 5.49341e-05 | 1(Win) | true |
| simdjson (ondemand) | 447.861 | 0.0652169 | 1625.75ms | 4147 | 320 | 10613.4 | 8830.62 | 0.0426246 | 11.3363 | 50.5505 | 13.3019 | 0.00743007 | 4.06921e-05 | 7.53557e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4832.27 | 0.0754209 | 787.419ms | 2821 | 640 | 112.841 | 556.739 | 0.0911288 | 1.12219 | 4.08756 | 0.550868 | 0.000354484 | 1.82781e-05 | 2.21553e-06 | 1(Win) | true |
| simdjson (ondemand) | 4760.78 | 0.114582 | 785.704ms | 2821 | 2560 | 1073.31 | 565.1 | 0.192676 | 1.13795 | 4.47253 | 0.685218 | 0.000709661 | 2.34015e-05 | 6.36964e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4976.48 | 0.157264 | 787.084ms | 2821 | 160 | 115.649 | 540.606 | 0.170237 | 1.09491 | 4.01134 | 0.53279 | 0.000354484 | 6.64658e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4910.63 | 0.136808 | 782.883ms | 2821 | 4890 | 2747.02 | 547.856 | 0.0476085 | 1.11147 | 4.39773 | 0.666785 | 0.000709186 | 5.82108e-05 | 3.42886e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6299.66 | 0.117709 | 795.435ms | 4147 | 160 | 87.3723 | 627.794 | 0.120317 | 0.856491 | 3.483 | 0.484688 | 0.000421992 | 7.53557e-06 | 0 | 1(Win) | true |
| jsonifier (generic) | 6174.4 | 0.0534937 | 796.332ms | 4147 | 1280 | 150.277 | 640.53 | 0.372565 | 0.869642 | 3.25609 | 0.381481 | 0.000241138 | 8.47751e-06 | 2.07228e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6460.91 | 0.237762 | 795.684ms | 4147 | 40 | 84.7276 | 612.125 | 0.0503456 | 0.833633 | 3.43212 | 0.472149 | 0.000415963 | 1.20569e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 6276.24 | 0.180794 | 797.218ms | 4147 | 1280 | 1661.3 | 630.137 | 0.122022 | 0.855915 | 3.20424 | 0.369183 | 0.000241703 | 2.82584e-05 | 1.3564e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3258.53 | 0.0838746 | 818.167ms | 2821 | 2560 | 1227.62 | 825.622 | 0.231754 | 1.61543 | 6.55654 | 1.14215 | 0.000355592 | 2.49247e-05 | 9.8314e-06 | 1(Win) | true |
| simdjson (ondemand) | 3016.19 | 0.0323503 | 819.54ms | 2821 | 4890 | 407.15 | 891.959 | 0.00110272 | 1.75219 | 7.42184 | 1.6207 | 0.00106273 | 1.55132e-05 | 4.20452e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3344.9 | 0.23757 | 813.147ms | 2821 | 1280 | 4673.4 | 804.305 | 0.00835279 | 1.58375 | 6.48033 | 1.12407 | 0.000360023 | 5.73267e-05 | 2.99096e-05 | 1(Win) | true |
| simdjson (ondemand) | 3081.63 | 0.0599981 | 820.321ms | 2821 | 2560 | 702.358 | 873.016 | 0.122717 | 1.71549 | 7.34669 | 1.60227 | 0.000728354 | 2.46477e-05 | 3.87717e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4324.87 | 0.112492 | 826.405ms | 4147 | 320 | 338.625 | 914.453 | 0.183856 | 1.2103 | 4.93827 | 0.784664 | 0.000241138 | 1.50711e-05 | 5.2749e-06 | 1(Win) | true |
| simdjson (ondemand) | 4118.39 | 0.111877 | 829.231ms | 4147 | 80 | 92.3392 | 960.3 | 0.083238 | 1.27914 | 5.49891 | 1.12322 | 0.000566675 | 6.02845e-06 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4454.5 | 0.0576877 | 824.766ms | 4147 | 640 | 167.887 | 887.841 | 0.0186513 | 1.18653 | 4.88642 | 0.772366 | 0.000242645 | 1.09266e-05 | 1.50711e-06 | 1(Win) | true |
| simdjson (ondemand) | 4197.45 | 0.0993738 | 828.613ms | 4147 | 160 | 140.269 | 942.212 | 0.0132684 | 1.25659 | 5.44779 | 1.11068 | 0.000575717 | 1.20569e-05 | 0 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4821.49 | 0.0546807 | 6268.94ms | 277673 | 1280 | 1.15447e+06 | 54922.8 | 0.128988 | 1.04835 | 3.97788 | 0.647333 | 0.00488581 | 3.22153e-06 | 1.94136e-06 | 1(Win) | true |
| simdjson (ondemand) | 4609.14 | 0.0609265 | 6488.19ms | 277673 | 1280 | 1.56838e+06 | 57453.2 | 0.0191647 | 1.09399 | 4.54075 | 0.756877 | 0.00534808 | 3.79549e-06 | 2.23959e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4194.9 | 0.138108 | 7508.76ms | 10548466 | 40 | 4.38764e+08 | 2.3981e+06 | 0.0394457 | 1.20156 | 3.97753 | 0.647977 | 0.0116493 | 0.0182739 | 0.000223732 | 1(Win) | true |
| simdjson (ondemand) | 4028.72 | 0.139888 | 7776.38ms | 10548466 | 160 | 1.95221e+09 | 2.49702e+06 | 0.00852688 | 1.24626 | 4.5413 | 0.758176 | 0.0103537 | 0.0184957 | 0.000390466 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3538.96 | 0.171417 | 6488.91ms | 16002592 | 80 | 4.37146e+09 | 4.31236e+06 | 0.156697 | 1.41737 | 6.9247 | 1.13434 | 0.000555087 | 0.034563 | 0.00265388 | 1(Win) | true |
| simdjson (ondemand) | 3439.4 | 0.142861 | 6686.23ms | 16002592 | 80 | 3.21463e+09 | 4.43719e+06 | 0.110738 | 1.45937 | 7.91775 | 1.44247 | 0.000798048 | 0.0378538 | 0.00365417 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3524.31 | 0.171931 | 6518.81ms | 16002591 | 30 | 1.66288e+09 | 4.33029e+06 | 0.152698 | 1.42366 | 7.21433 | 1.21325 | 0.000482322 | 0.0363021 | 0.00371694 | 1(Win) | true |
| simdjson (ondemand) | 1773.14 | 0.205051 | 6036.17ms | 16002591 | 30 | 9.34413e+09 | 8.60689e+06 | 0.143079 | 2.84116 | 12.8949 | 2.98449 | 0.000821992 | 0.0561025 | 0.00661265 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 17626.2 | 0.186606 | 5608.19ms | 16197086 | 320 | 8.5578e+08 | 876354 | 0.0582694 | 0.283932 | 1.33614 | 0.0780642 | 8.03003e-05 | 0.0157214 | 0.000282626 | 1(Win) | true |
| jsonifier (generic) | 16842.6 | 0.217337 | 5861.37ms | 16197086 | 80 | 3.17843e+08 | 917124 | 0.0465968 | 0.296799 | 1.37646 | 0.0670091 | 7.60893e-05 | 0.0157237 | 0.000294152 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 16763.8 | 0.193642 | 5868.87ms | 16197085 | 160 | 5.09388e+08 | 921434 | 0.176543 | 0.297158 | 1.38069 | 0.0682619 | 8.85175e-05 | 0.0157235 | 0.000268914 | 1(Win) | true |
| simdjson (ondemand) | 15503.4 | 0.402988 | 6453.42ms | 16197085 | 30 | 4.83643e+08 | 996346 | 0.380791 | 0.32011 | 1.41865 | 0.103752 | 8.98763e-05 | 0.0157389 | 0.000940575 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1479.07 | 0.0645676 | 4781.43ms | 4525120 | 80 | 2.83924e+08 | 2.9177e+06 | 0.0300948 | 3.35554 | 15.2767 | 2.71802 | 0.0108638 | 0.0773969 | 0.0079313 | 1(Win) | true |
| simdjson (ondemand) | 1394.18 | 0.064 | 5081.06ms | 4525120 | 80 | 3.13959e+08 | 3.09537e+06 | 0.285536 | 3.56498 | 15.1619 | 2.45026 | 0.015979 | 0.0765362 | 0.00761228 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 547.442 | 0.0893527 | 5748.42ms | 4525120 | 30 | 1.48841e+09 | 7.88301e+06 | 0.197825 | 9.10083 | 36.5097 | 8.12011 | 0.0274664 | 0.0782553 | 0.017542 | 1(Win) | true |
| simdjson (ondemand) | 384.831 | 0.0734519 | 8070.56ms | 4525120 | 30 | 2.03539e+09 | 1.1214e+07 | 0.00803347 | 12.9082 | 56.3061 | 15.0509 | 0.0500248 | 0.0773607 | 0.0252569 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1255.01 | 0.101139 | 5606.17ms | 4525119 | 30 | 3.62849e+08 | 3.4386e+06 | 0.334573 | 3.97624 | 17.6911 | 3.35007 | 0.0118127 | 0.0780326 | 0.0111741 | 1(Win) | true |
| simdjson (ondemand) | 1008.53 | 0.130942 | 6891.58ms | 4525119 | 30 | 9.41805e+08 | 4.27898e+06 | 0.0931861 | 4.97994 | 20.3739 | 3.99498 | 0.0187528 | 0.0934506 | 0.0117781 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 576.251 | 0.171053 | 5414.33ms | 4525119 | 30 | 4.92289e+09 | 7.4889e+06 | 0.414133 | 8.7098 | 35.8625 | 7.98668 | 0.0182416 | 0.0788673 | 0.00782295 | 1(Win) | true |
| simdjson (ondemand) | 352.922 | 0.11685 | 8825.76ms | 4525119 | 30 | 6.12461e+09 | 1.22279e+07 | 0.250705 | 14.241 | 61.5178 | 16.5955 | 0.0528425 | 0.0942341 | 0.0129324 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1228.71 | 0.344292 | 5210.54ms | 4203059 | 30 | 3.78446e+09 | 3.26223e+06 | 0.203694 | 4.0704 | 16.8613 | 3.05474 | 0.0162042 | 0.0889501 | 0.00561095 | 1(Win) | true |
| simdjson (ondemand) | 994.337 | 0.0680102 | 6420.87ms | 4203059 | 80 | 6.01315e+08 | 4.03118e+06 | 0.19208 | 5.05924 | 18.0833 | 3.32658 | 0.0282653 | 0.088727 | 0.0174764 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 745.46 | 0.0990177 | 8483.65ms | 4203059 | 30 | 8.50412e+08 | 5.37701e+06 | 0.0873465 | 6.73359 | 27.7425 | 5.90312 | 0.026739 | 0.0889562 | 0.0219334 | 1(Win) | true |
| simdjson (ondemand) | 670.878 | 0.124226 | 4363.23ms | 4203059 | 30 | 1.65268e+09 | 5.97479e+06 | 0.246679 | 7.48961 | 29.0034 | 6.2237 | 0.0316416 | 0.0876285 | 0.0219488 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1125.96 | 0.168756 | 5758.54ms | 4203058 | 30 | 1.08273e+09 | 3.55992e+06 | 0.829771 | 4.46288 | 19.1506 | 3.65436 | 0.0149491 | 0.0884899 | 0.0181413 | 1(Win) | true |
| simdjson (ondemand) | 782.368 | 0.0996359 | 8064.78ms | 4203058 | 80 | 2.08464e+09 | 5.12336e+06 | 0.235172 | 6.40861 | 23.1883 | 4.88981 | 0.0294079 | 0.10543 | 0.00605369 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 735.809 | 0.124009 | 8482.81ms | 4203058 | 80 | 3.65091e+09 | 5.44754e+06 | 0.438626 | 6.82056 | 30.0147 | 6.49871 | 0.0178586 | 0.0884089 | 0.00451384 | 1(Win) | true |
| simdjson (ondemand) | 570.428 | 0.138635 | 5071.24ms | 4203058 | 40 | 3.79606e+09 | 7.02691e+06 | 0.853646 | 8.82523 | 34.1088 | 7.787 | 0.0332863 | 0.104578 | 0.00419039 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1636.3 | 0.146561 | 7932.57ms | 4197496 | 30 | 3.85669e+08 | 2.4464e+06 | 0.0204887 | 3.08107 | 13.8513 | 2.62989 | 0.00543269 | 0.0821255 | 0.00143875 | 1(Win) | true |
| simdjson (ondemand) | 1540.88 | 0.0990961 | 4087.1ms | 4197496 | 80 | 5.30207e+08 | 2.59789e+06 | 0.256028 | 3.23093 | 15.1336 | 2.48306 | 0.00947606 | 0.0805382 | 0.00765594 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 782.406 | 0.138114 | 7879.76ms | 4197496 | 30 | 1.49801e+09 | 5.11632e+06 | 0.234705 | 6.3828 | 30.6679 | 6.22029 | 0.0154281 | 0.0806847 | 0.011901 | 1(Win) | true |
| jsonifier (generic) | 587.045 | 0.182417 | 4861.99ms | 4197496 | 30 | 4.64181e+09 | 6.81897e+06 | 0.319773 | 8.51027 | 37.6405 | 7.925 | 0.0128733 | 0.082764 | 0.0124813 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1482.85 | 0.333466 | 4270.88ms | 4197495 | 40 | 3.24152e+09 | 2.69956e+06 | 0.0534832 | 3.38606 | 16.2347 | 3.24968 | 0.000558678 | 0.0846453 | 0.00945681 | 1(Win) | true |
| simdjson (ondemand) | 1042.42 | 0.133638 | 6020.85ms | 4197495 | 80 | 2.10691e+09 | 3.84015e+06 | 0.409354 | 4.8186 | 20.8254 | 4.26052 | 0.0110136 | 0.102641 | 0.00765789 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 630.158 | 0.0858263 | 4581.44ms | 4197495 | 30 | 8.9175e+08 | 6.35244e+06 | 0.967749 | 8.00395 | 36.3597 | 7.99777 | 0.0160591 | 0.102703 | 0.0118212 | 1(Win) | true |
| jsonifier (generic) | 605.1 | 0.108814 | 4808.43ms | 4197495 | 30 | 1.5546e+09 | 6.6155e+06 | 0.42374 | 8.31387 | 37.8604 | 7.94721 | 0.012312 | 0.0849125 | 0.0206861 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1485.13 | 0.128609 | 5095.72ms | 4506447 | 40 | 5.54047e+08 | 2.89382e+06 | 0.157453 | 3.35644 | 14.8216 | 2.6775 | 0.00903751 | 0.0808906 | 0.0073549 | 1(Win) | true |
| simdjson (ondemand) | 1205.15 | 0.312323 | 6104.76ms | 4506447 | 30 | 3.72146e+09 | 3.56609e+06 | 0.036668 | 4.15145 | 16.3602 | 3.01281 | 0.0129793 | 0.0786437 | 0.0130821 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 692.865 | 0.127244 | 4721.13ms | 4506447 | 40 | 2.49176e+09 | 6.20277e+06 | 0.0756891 | 7.2291 | 31.4772 | 6.58621 | 0.0166782 | 0.0814168 | 0.0198727 | 1(Win) | true |
| simdjson (ondemand) | 486.031 | 0.0910482 | 6607.15ms | 4506447 | 40 | 2.59265e+09 | 8.84241e+06 | 0.649976 | 10.3125 | 48.9231 | 11.8499 | 0.0170155 | 0.0786759 | 0.0231617 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1391.7 | 0.255644 | 5418.64ms | 4506446 | 30 | 1.86969e+09 | 3.08808e+06 | 0.0374203 | 3.6051 | 16.5916 | 3.13738 | 0.00859126 | 0.0810076 | 0.024233 | 1(Win) | true |
| simdjson (ondemand) | 939.648 | 0.0962183 | 7680.23ms | 4506446 | 30 | 5.80998e+08 | 4.57371e+06 | 0.0167091 | 5.32311 | 20.4239 | 4.27296 | 0.0152764 | 0.0872026 | 0.0232774 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 712.085 | 0.158877 | 4622.7ms | 4506446 | 30 | 2.75833e+09 | 6.03535e+06 | 0.480457 | 6.97411 | 31.2644 | 6.53752 | 0.00973985 | 0.081747 | 0.0198658 | 1(Win) | true |
| simdjson (ondemand) | 434.272 | 0.197459 | 7285.85ms | 4506446 | 30 | 1.14556e+10 | 9.89628e+06 | 0.484163 | 11.4172 | 52.9873 | 13.1102 | 0.0187691 | 0.0870006 | 0.0212963 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1914.77 | 0.0932693 | 7636.09ms | 4219120 | 160 | 6.14624e+08 | 2.10139e+06 | 0.671789 | 2.58656 | 8.65928 | 1.47344 | 0.0168155 | 0.0565627 | 0.00421626 | 1(Win) | true |
| simdjson (ondemand) | 1867.62 | 0.174258 | 7700.43ms | 4219120 | 80 | 1.12757e+09 | 2.15444e+06 | 0.036277 | 2.66537 | 8.68523 | 1.42603 | 0.0158372 | 0.0535219 | 0.00394767 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 586.422 | 0.162867 | 5150.28ms | 4219120 | 40 | 4.99517e+09 | 6.86139e+06 | 0.286979 | 8.54894 | 27.2722 | 5.16804 | 0.0545223 | 0.0583149 | 0.0145746 | 1(Win) | true |
| simdjson (ondemand) | 240.779 | 0.145655 | 5150.81ms | 4219120 | 30 | 1.77736e+10 | 1.6711e+07 | 0.443836 | 20.6523 | 80.1996 | 21.4005 | 0.0989966 | 0.0546249 | 0.0169429 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1738.45 | 0.207939 | 8201.85ms | 4219119 | 80 | 1.85303e+09 | 2.31451e+06 | 0.239717 | 2.85887 | 9.74063 | 1.75194 | 0.0181169 | 0.0567987 | 0.00339477 | 1(Win) | true |
| simdjson (ondemand) | 1462.85 | 0.165725 | 4624.9ms | 4219119 | 40 | 8.31151e+08 | 2.75057e+06 | 0.0359251 | 3.38548 | 11.1279 | 2.18506 | 0.0172545 | 0.0556915 | 0.00448278 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 633.433 | 0.269709 | 4740.47ms | 4219119 | 30 | 8.80551e+09 | 6.35216e+06 | 0.0956216 | 7.88388 | 27.1096 | 5.11959 | 0.0380785 | 0.0590932 | 0.0112451 | 1(Win) | true |
| simdjson (ondemand) | 231.194 | 0.123768 | 5332.86ms | 4219119 | 30 | 1.39197e+10 | 1.74039e+07 | 0.837966 | 21.4626 | 82.6421 | 22.1595 | 0.102124 | 0.0579033 | 0.0181483 | 2(Loss) | true |
