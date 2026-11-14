# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 556.173 | 0.0668298 | 864.13ms | 905 | 4890 | 5259.28 | 1551.81 | 0.0100994 | 9.49675 | 49.3702 | 6.37017 | 0.00123242 | 0.000135353 | 2.73419e-05 | 1(Win) | true |
| simdjson (ondemand) | 287.339 | 0.0582536 | 1015.17ms | 905 | 160 | 489.864 | 3003.69 | 0.149592 | 18.1754 | 88.9459 | 9.47735 | 0.0239572 | 0.000379834 | 0.000172652 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 566.251 | 0.0637111 | 861.32ms | 905 | 4890 | 4611.25 | 1524.19 | 0.00433189 | 9.34577 | 48.7514 | 6.25194 | 0.00297281 | 9.8973e-05 | 6.77897e-06 | 1(Win) | true |
| simdjson (ondemand) | 290.043 | 0.0878003 | 1009.29ms | 905 | 320 | 2184.31 | 2975.68 | 0.0854527 | 18.0018 | 88.3271 | 9.35912 | 0.0244199 | 0.000172652 | 0 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 687.783 | 0.0678129 | 966.241ms | 1811 | 2560 | 7423.33 | 2511.12 | 0.172512 | 7.60376 | 38.9752 | 6.36555 | 0.00074566 | 9.46904e-05 | 9.70631e-06 | 1(Win) | true |
| simdjson (ondemand) | 367.904 | 0.0772899 | 1193.94ms | 1811 | 640 | 8425.45 | 4694.44 | 0.0300465 | 14.1091 | 71.1706 | 9.25014 | 0.000588418 | 6.98854e-05 | 3.45113e-06 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 716.704 | 0.102013 | 955.081ms | 1811 | 80 | 483.461 | 2409.79 | 0.108295 | 7.31668 | 37.9094 | 6.13087 | 0.00106295 | 4.14136e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 371.65 | 0.046752 | 1184.42ms | 1811 | 2560 | 12083.9 | 4647.12 | 0.05736 | 13.8262 | 70.2253 | 9.04362 | 0.000599634 | 0.000236187 | 5.43553e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1557.77 | 0.0330724 | 951.414ms | 3862 | 4890 | 2989.91 | 2364.34 | 0.0480162 | 3.36069 | 16.9444 | 2.10177 | 0.00117685 | 3.56894e-05 | 2.22397e-06 | 1(Win) | true |
| simdjson (ondemand) | 795.483 | 0.0247546 | 1177.35ms | 3862 | 2560 | 3362.9 | 4630 | 0.0126368 | 6.52939 | 28.2372 | 3.48887 | 0.0138927 | 4.17732e-05 | 1.41604e-06 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1637.3 | 0.0479444 | 939.292ms | 3862 | 2560 | 2977.71 | 2249.49 | 0.0773362 | 3.20839 | 16.4606 | 1.99171 | 0.00062589 | 4.88534e-05 | 1.43627e-05 | 1(Win) | true |
| simdjson (ondemand) | 806.508 | 0.0239865 | 1168.63ms | 3862 | 4890 | 5867.45 | 4566.71 | 0.00173734 | 6.43958 | 27.7962 | 3.39203 | 0.0164342 | 3.53187e-05 | 3.70661e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1440.62 | 0.0936643 | 1362.26ms | 9578 | 1280 | 45144.8 | 6340.52 | 0.00347456 | 3.54214 | 17.6752 | 3.00209 | 0.00303552 | 4.09467e-05 | 2.15337e-05 | 1(Win) | true |
| Jsonifier (generic) | 1329.34 | 0.188552 | 1414.47ms | 9578 | 80 | 13428.6 | 6871.31 | 0.289536 | 3.89335 | 19.1543 | 3.34673 | 0.00353936 | 1.95761e-05 | 7.83044e-06 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2042.76 | 0.0682468 | 1312.64ms | 9578 | 2560 | 23840.8 | 4471.55 | 0.02902 | 2.51521 | 13.3639 | 2.0283 | 0.00157449 | 4.49843e-05 | 2.22678e-05 | 1(Win) | true |
| Jsonifier (generic) | 1733.45 | 0.0584618 | 1383.46ms | 9578 | 2560 | 24294.6 | 5269.42 | 0.208734 | 2.95614 | 14.9192 | 2.39079 | 0.00307374 | 4.44541e-05 | 2.21047e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1542.87 | 0.0613078 | 954.134ms | 3873 | 2560 | 5514.52 | 2393.97 | 0.041526 | 3.39222 | 17.0648 | 2.1149 | 0.0006579 | 4.04443e-05 | 4.94207e-06 | 1(Win) | true |
| simdjson (ondemand) | 729.053 | 0.0660507 | 1221.05ms | 3873 | 320 | 3583.29 | 5066.27 | 0.0398628 | 7.12014 | 27.912 | 3.56649 | 0.0163149 | 5.4867e-05 | 5.64808e-06 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1594.69 | 0.052718 | 941.96ms | 3873 | 160 | 238.552 | 2316.18 | 0.0644504 | 3.29747 | 16.5882 | 2.00697 | 0.00201394 | 4.51846e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 733.403 | 0.020832 | 1216.41ms | 3873 | 4890 | 5382.47 | 5036.22 | 0.058846 | 7.07549 | 27.4216 | 3.45624 | 0.0183404 | 4.84715e-05 | 6.33614e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1493.54 | 0.182077 | 6706.87ms | 94653 | 40 | 484405 | 60439.1 | 0.0905725 | 3.43606 | 15.0311 | 2.96587 | 0.0100052 | 7.39543e-06 | 3.16947e-06 | 1(Win) | true |
| simdjson (ondemand) | 1264.35 | 0.114406 | 7842.38ms | 94653 | 40 | 266865 | 71394.6 | 0.0201036 | 4.07346 | 16.5912 | 3.09837 | 0.0118058 | 3.69772e-06 | 0 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2238.13 | 0.0864825 | 6053.77ms | 94653 | 80 | 97329.2 | 40331.9 | 0.0903638 | 2.30237 | 11.1446 | 2.08843 | 0.00621428 | 4.62215e-06 | 1.45267e-06 | 1(Win) | true |
| simdjson (ondemand) | 1712 | 0.0178572 | 7237.99ms | 94653 | 4890 | 433512 | 52726.8 | 0.10129 | 2.98838 | 12.7232 | 2.22457 | 0.00855281 | 5.55252e-06 | 1.1602e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1899.28 | 0.0603998 | 7033.39ms | 124597 | 160 | 228469 | 62563.2 | 0.227819 | 2.71171 | 11.8484 | 2.26045 | 0.00713385 | 6.35549e-05 | 5.93413e-05 | 1(Win) | true |
| simdjson (ondemand) | 1630.8 | 0.0324445 | 8020.39ms | 124597 | 1280 | 715324 | 72862.8 | 0.0842048 | 3.13007 | 12.9142 | 2.3706 | 0.00879225 | 4.82807e-06 | 1.19761e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2688.77 | 0.0438813 | 6392.29ms | 124597 | 640 | 240683 | 44193 | 0.0338262 | 1.9037 | 8.88611 | 1.5922 | 0.00459208 | 2.59587e-06 | 4.38915e-07 | 1(Win) | true |
| simdjson (ondemand) | 2185 | 0.0509283 | 7406.38ms | 124597 | 640 | 490921 | 54382.2 | 0.105338 | 2.33692 | 9.97882 | 1.70865 | 0.00645432 | 5.06633e-06 | 6.14481e-07 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1129.28 | 0.016533 | 8713.95ms | 94653 | 4890 | 854040 | 79934.3 | 0.0100171 | 4.52716 | 20.9698 | 4.22029 | 0.0100701 | 6.87259e-06 | 2.73737e-06 | 1(Win) | true |
| simdjson (ondemand) | 717.515 | 0.121976 | 6732ms | 94653 | 40 | 941930 | 125807 | 0.00688936 | 7.04766 | 35.1168 | 7.03381 | 0.0116829 | 5.91635e-05 | 4.27879e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1456.24 | 0.0967431 | 8180.2ms | 94653 | 160 | 575391 | 61987.1 | 0.00937607 | 3.51891 | 17.1026 | 3.36093 | 0.00747322 | 8.31986e-06 | 3.76375e-06 | 1(Win) | true |
| simdjson (ondemand) | 849.251 | 0.051091 | 6433.52ms | 94653 | 640 | 1.88741e+06 | 106291 | 0.051214 | 6.02828 | 31.2898 | 6.18435 | 0.00871436 | 1.02182e-05 | 4.25898e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.46 | 0.023084 | 9009.06ms | 124597 | 2560 | 939981 | 83009.8 | 0.0410175 | 3.56412 | 16.5479 | 3.28321 | 0.00845738 | 9.41786e-06 | 4.31391e-06 | 1(Win) | true |
| simdjson (ondemand) | 939.936 | 0.0252969 | 6807.61ms | 124597 | 2560 | 2.61813e+06 | 126418 | 0.111507 | 5.42273 | 26.6555 | 5.30039 | 0.00941692 | 1.67948e-05 | 8.01647e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1846.55 | 0.0220077 | 8393.46ms | 124597 | 2560 | 513427 | 64349.6 | 0.223483 | 2.74939 | 13.6237 | 2.63462 | 0.00597345 | 2.95014e-06 | 4.89077e-07 | 1(Win) | true |
| simdjson (ondemand) | 1099.95 | 0.0241752 | 6507.1ms | 124597 | 2560 | 1.74603e+06 | 108028 | 0.0897984 | 4.62346 | 23.7486 | 4.65715 | 0.00697834 | 7.53053e-06 | 2.80592e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2489.68 | 0.0491128 | 4349.01ms | 94653 | 640 | 202933 | 36257 | 0.0858106 | 2.04361 | 9.39126 | 1.80364 | 0.00477232 | 4.80373e-06 | 7.92368e-07 | 1(Win) | true |
| simdjson (ondemand) | 1893.09 | 0.0238883 | 5491.7ms | 94653 | 2560 | 332152 | 47682.9 | 0.0358589 | 2.70365 | 10.9659 | 1.93883 | 0.00750467 | 5.88498e-06 | 2.1625e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3367.67 | 0.0198692 | 3926.33ms | 94653 | 4890 | 138701 | 26804.3 | 0.221745 | 1.51388 | 7.48562 | 1.35676 | 0.00343324 | 6.82074e-06 | 3.17163e-06 | 1(Win) | true |
| simdjson (ondemand) | 2349.68 | 0.0568688 | 5048.04ms | 94653 | 1280 | 610956 | 38417.2 | 0.0470901 | 2.18651 | 9.07985 | 1.49728 | 0.00601155 | 6.51227e-06 | 3.16947e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2995.84 | 0.0735146 | 4712.04ms | 124597 | 160 | 136033 | 39663.3 | 0.0172359 | 1.7178 | 7.57047 | 1.38295 | 0.00465115 | 4.91585e-06 | 1.60518e-06 | 1(Win) | true |
| simdjson (ondemand) | 2494.65 | 0.0189607 | 5506.73ms | 124597 | 4890 | 398853 | 47631.9 | 0.174533 | 2.04637 | 8.31683 | 1.43036 | 0.00582442 | 6.23031e-06 | 2.10905e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3926.73 | 0.0183252 | 4246.21ms | 124597 | 4890 | 150370 | 30260.6 | 0.197073 | 1.30172 | 6.12549 | 1.04417 | 0.00292355 | 7.24134e-06 | 3.90133e-06 | 1(Win) | true |
| simdjson (ondemand) | 3125.06 | 0.0934808 | 4992.62ms | 124597 | 160 | 202146 | 38023.3 | 0.077068 | 1.64104 | 6.891 | 1.09639 | 0.00436537 | 2.40776e-06 | 1.50485e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1853.44 | 0.023042 | 5636.15ms | 94653 | 1280 | 161200 | 48703.1 | 0.0442537 | 2.77496 | 12.9834 | 2.53903 | 0.0075906 | 5.35674e-06 | 1.51045e-06 | 1(Win) | true |
| simdjson (ondemand) | 1572.39 | 0.0263098 | 6469.31ms | 94653 | 2560 | 584014 | 57408.3 | 0.0660672 | 3.24804 | 13.6144 | 2.44476 | 0.00820142 | 2.8616e-05 | 1.78613e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2233.03 | 0.0657659 | 5223.24ms | 94653 | 320 | 226168 | 40424.1 | 0.218381 | 2.27722 | 11.1128 | 2.11506 | 0.0063194 | 3.16947e-06 | 1.65077e-07 | 1(Win) | true |
| simdjson (ondemand) | 1856.57 | 0.0190532 | 6079.28ms | 94653 | 4890 | 419655 | 48620.9 | 0.0284297 | 2.75974 | 11.7615 | 2.0258 | 0.00725374 | 4.40096e-06 | 1.06513e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2327.18 | 0.0178954 | 5825.46ms | 124597 | 4890 | 408272 | 51059.7 | 0.0771568 | 2.19461 | 10.4017 | 1.96503 | 0.00551074 | 4.67602e-06 | 1.25066e-06 | 1(Win) | true |
| simdjson (ondemand) | 2079.16 | 0.0585805 | 6418.15ms | 124597 | 640 | 717343 | 57150.5 | 0.0666256 | 2.45406 | 10.3194 | 1.81535 | 0.00649755 | 4.70266e-06 | 1.65534e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2839.38 | 0.0913944 | 5439.43ms | 124597 | 40 | 58515.1 | 41848.9 | 0.000577471 | 1.81517 | 8.97755 | 1.64264 | 0.00502721 | 4.61488e-06 | 1.60518e-06 | 1(Win) | true |
| simdjson (ondemand) | 2467.4 | 0.0741283 | 6006.87ms | 124597 | 320 | 407807 | 48158 | 0.0522096 | 2.07945 | 8.90509 | 1.49596 | 0.00540194 | 2.93446e-06 | 7.77507e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 779.443 | 0.145301 | 7975.91ms | 2090234 | 30 | 4.14269e+08 | 2.55747e+06 | 0.162116 | 6.52433 | 32.6606 | 6.35605 | 0.0229047 | 0.104268 | 2.38251e-05 | 1(Win) | true |
| simdjson (ondemand) | 765.031 | 0.0707108 | 8082.47ms | 2090234 | 160 | 5.43155e+08 | 2.60565e+06 | 0.0757604 | 6.60949 | 31.7559 | 5.64958 | 0.0228756 | 0.10564 | 0.000262692 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 910.352 | 0.106914 | 7976.15ms | 2090234 | 80 | 4.3846e+08 | 2.1897e+06 | 0.0873196 | 5.57607 | 27.3243 | 5.06579 | 0.0218243 | 0.0790229 | 0.00012797 | 1(Win) | true |
| simdjson (ondemand) | 896.92 | 0.055193 | 8110.02ms | 2090234 | 160 | 2.40752e+08 | 2.2225e+06 | 0.0433242 | 5.63891 | 26.4284 | 4.36085 | 0.0218202 | 0.0804596 | 0.000155796 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1772.4 | 0.0662957 | 8769.94ms | 5212421 | 80 | 2.76579e+08 | 2.80465e+06 | 0.0277371 | 2.8456 | 13.4652 | 2.30074 | 0.0102668 | 0.0613649 | 0.00102222 | 1(Win) | true |
| Jsonifier (generic) | 1762.52 | 0.0872393 | 8798.03ms | 5212421 | 160 | 9.6862e+08 | 2.82036e+06 | 0.0358851 | 2.86793 | 13.8883 | 2.59592 | 0.0100582 | 0.0605944 | 0.00085497 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2056.29 | 0.107632 | 8741.32ms | 5212421 | 30 | 2.03103e+08 | 2.41744e+06 | 0.0601493 | 2.45347 | 11.3279 | 1.78366 | 0.00989242 | 0.0511361 | 0.00120588 | 1(Win) | true |
| Jsonifier (generic) | 2037.17 | 0.0673113 | 8792.06ms | 5212421 | 80 | 2.15819e+08 | 2.44012e+06 | 0.119872 | 2.47877 | 11.7381 | 2.07614 | 0.00974707 | 0.0512011 | 0.000861039 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 735.011 | 0.100327 | 8482.33ms | 2090234 | 80 | 5.92276e+08 | 2.71207e+06 | 0.645353 | 6.94995 | 35.6643 | 6.98898 | 0.0228326 | 0.157185 | 0.000112918 | 1(Win) | true |
| simdjson (ondemand) | 701.917 | 0.11149 | 8844.54ms | 2090234 | 30 | 3.00756e+08 | 2.83994e+06 | 0.237099 | 7.23081 | 36.0797 | 6.61044 | 0.022877 | 0.181413 | 0.000125648 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 848.783 | 0.107143 | 8497.86ms | 2090234 | 30 | 1.89952e+08 | 2.34854e+06 | 0.0771911 | 5.98715 | 30.3634 | 5.70543 | 0.0219187 | 0.131556 | 8.26542e-05 | 1(Win) | true |
| simdjson (ondemand) | 806.754 | 0.12315 | 8850.35ms | 2090234 | 30 | 2.77777e+08 | 2.47089e+06 | 0.0411775 | 6.27755 | 30.7467 | 5.3204 | 0.0218448 | 0.155711 | 0.000158882 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1614.24 | 0.12461 | 9583.6ms | 5212421 | 40 | 5.88988e+08 | 3.07943e+06 | 0.170357 | 3.1521 | 15.0934 | 2.84958 | 0.0102782 | 0.100863 | 0.000733781 | 1(Win) | true |
| simdjson (ondemand) | 1569.62 | 0.129081 | 9842.6ms | 5212421 | 40 | 6.68465e+08 | 3.16698e+06 | 0.163808 | 3.2265 | 15.1882 | 2.6837 | 0.0103242 | 0.121404 | 0.000739877 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1850.4 | 0.100402 | 9554.85ms | 5212421 | 160 | 1.16401e+09 | 2.68643e+06 | 0.0698385 | 2.73932 | 12.957 | 2.33274 | 0.00980118 | 0.0905794 | 0.000492238 | 1(Win) | true |
| simdjson (ondemand) | 1794.27 | 0.18449 | 9849.98ms | 5212421 | 40 | 1.04498e+09 | 2.77045e+06 | 0.116057 | 2.85404 | 13.0598 | 2.16844 | 0.00995783 | 0.111151 | 0.000711402 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7826.81 | 0.172449 | 6619.88ms | 2090234 | 30 | 5.7871e+06 | 254689 | 0.0561415 | 0.651958 | 3.25154 | 0.398873 | 0.0031207 | 0.0508947 | 3.42864e-06 | 1(Win) | true |
| simdjson (ondemand) | 7193.17 | 0.0935186 | 7282.55ms | 2090234 | 640 | 4.29858e+07 | 277124 | 0.00684495 | 0.710283 | 3.65784 | 0.418404 | 0.00242698 | 0.0497175 | 3.61802e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7952.47 | 0.131647 | 6580.14ms | 2090234 | 40 | 4.3558e+06 | 250665 | 0.0831682 | 0.636896 | 3.25146 | 0.398855 | 0.00262987 | 0.0508313 | 3.40871e-06 | 1(Win) | true |
| simdjson (ondemand) | 7254.74 | 0.0574914 | 7254.44ms | 2090234 | 30 | 748639 | 274772 | 0.0922216 | 0.709285 | 3.65775 | 0.418386 | 0.00240045 | 0.0496593 | 2.07313e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10851.5 | 0.0349425 | 5933.98ms | 5212421 | 640 | 1.63978e+07 | 458088 | 0.031344 | 0.468048 | 1.95585 | 0.18325 | 0.00198073 | 0.0394006 | 5.33042e-06 | 1(Win) | true |
| simdjson (ondemand) | 9893.29 | 0.0769887 | 6499.05ms | 5212421 | 30 | 4.48924e+06 | 502457 | 0.287343 | 0.520055 | 2.19705 | 0.202784 | 0.00230684 | 0.039483 | 2.34056e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10874.9 | 0.0698041 | 5905.39ms | 5212421 | 160 | 1.62898e+07 | 457105 | 0.170278 | 0.467391 | 1.95582 | 0.183243 | 0.0019681 | 0.0394045 | 5.80464e-06 | 1(Win) | true |
| simdjson (ondemand) | 9946.79 | 0.0361625 | 6459.67ms | 5212421 | 640 | 2.09031e+07 | 499754 | 0.0225878 | 0.514869 | 2.19702 | 0.202777 | 0.00216785 | 0.0393847 | 1.84775e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5991.04 | 0.048496 | 8713.21ms | 2090234 | 1280 | 3.33278e+07 | 332731 | 0.151124 | 0.850025 | 4.69133 | 0.718822 | 0.0026089 | 0.076328 | 1.91889e-06 | 1(Win) | true |
| simdjson (ondemand) | 5538.54 | 0.0821172 | 9404.22ms | 2090234 | 640 | 5.59047e+07 | 359915 | 0.0502704 | 0.921028 | 5.09755 | 0.738335 | 0.00243247 | 0.075888 | 8.41712e-07 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5977.38 | 0.0464295 | 8695.75ms | 2090234 | 640 | 1.53439e+07 | 333491 | 0.066141 | 0.847917 | 4.69125 | 0.718804 | 0.00261203 | 0.0762828 | 1.72902e-06 | 1(Win) | true |
| simdjson (ondemand) | 5529.75 | 0.101379 | 9364.9ms | 2090234 | 80 | 1.06848e+07 | 360487 | 0.0986924 | 0.919848 | 5.09747 | 0.738317 | 0.0024026 | 0.0758405 | 1.18408e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8777.55 | 0.0726018 | 7350.46ms | 5212421 | 80 | 1.35244e+07 | 566326 | 0.0179743 | 0.586427 | 2.53322 | 0.311554 | 0.00200281 | 0.059099 | 2.15591e-06 | 1(Win) | true |
| simdjson (ondemand) | 8031.96 | 0.0783487 | 7996.39ms | 5212421 | 160 | 3.762e+07 | 618896 | 0.0712162 | 0.638645 | 2.77439 | 0.331079 | 0.00218097 | 0.0590791 | 6.95694e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8656.81 | 0.0362155 | 7413.01ms | 5212421 | 640 | 2.76778e+07 | 574224 | 0.072266 | 0.591945 | 2.53319 | 0.311547 | 0.00196048 | 0.0590592 | 8.48334e-06 | 1(Win) | true |
| simdjson (ondemand) | 8025.21 | 0.118615 | 7978.33ms | 5212421 | 320 | 1.72741e+08 | 619417 | 0.132956 | 0.637391 | 2.77436 | 0.331072 | 0.00214824 | 0.0590751 | 8.12482e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1264.59 | 0.0430264 | 9810.24ms | 500299 | 1280 | 3.37318e+07 | 377294 | 0.0143903 | 4.01954 | 17.9917 | 3.40013 | 0.0168521 | 0.0079828 | 2.32908e-05 | 1(Win) | true |
| simdjson (ondemand) | 1145.26 | 0.0898979 | 5395.32ms | 500299 | 160 | 2.24426e+07 | 416608 | 0.173909 | 4.43031 | 18.6464 | 3.00038 | 0.0211184 | 0.0115708 | 1.54907e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1417.22 | 0.0620774 | 9596.12ms | 500299 | 160 | 6.98827e+06 | 336660 | 0.129165 | 3.56853 | 16.8416 | 3.12307 | 0.0118254 | 0.00646688 | 1.53033e-05 | 1(Win) | true |
| simdjson (ondemand) | 1273.17 | 0.17178 | 5255.9ms | 500299 | 30 | 1.24324e+07 | 374752 | 0.148358 | 3.97057 | 17.5034 | 2.72464 | 0.0157612 | 0.00938472 | 1.51909e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2600.26 | 0.0613283 | 5498.01ms | 1151920 | 320 | 2.14824e+07 | 422480 | 0.00309399 | 1.95808 | 8.58584 | 1.51221 | 0.00718792 | 0.0342628 | 1.49235e-05 | 1(Win) | true |
| simdjson (ondemand) | 2422.08 | 0.0474797 | 5866.13ms | 1151920 | 320 | 1.484e+07 | 453558 | 0.0379479 | 2.08809 | 8.78375 | 1.33636 | 0.00953626 | 0.0350642 | 1.43158e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2867.99 | 0.0286084 | 5386.58ms | 1151920 | 640 | 7.68525e+06 | 383041 | 0.0289421 | 1.76218 | 8.08584 | 1.39173 | 0.00521427 | 0.0308611 | 8.06263e-06 | 1(Win) | true |
| simdjson (ondemand) | 2699.65 | 0.0633082 | 5697.69ms | 1151920 | 320 | 2.12373e+07 | 406925 | 0.441231 | 1.88573 | 8.28641 | 1.21638 | 0.00729602 | 0.0315005 | 3.39922e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 686.707 | 0.0519391 | 8880.45ms | 500299 | 160 | 2.08365e+07 | 694798 | 0.0779223 | 7.37501 | 36.6865 | 7.57417 | 0.0223259 | 0.00858233 | 2.85329e-05 | 1(Win) | true |
| simdjson (ondemand) | 422.668 | 0.178939 | 7178.68ms | 500299 | 30 | 1.22403e+08 | 1.12884e+06 | 0.317391 | 12.0986 | 65.5821 | 13.0764 | 0.0328618 | 0.0125226 | 5.45007e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 739.364 | 0.0512107 | 8701.29ms | 500299 | 320 | 3.49474e+07 | 645314 | 0.131593 | 6.90428 | 35.5245 | 7.29491 | 0.0162225 | 0.00592767 | 1.5016e-05 | 1(Win) | true |
| simdjson (ondemand) | 440.988 | 0.123538 | 7076.75ms | 500299 | 80 | 1.42921e+08 | 1.08194e+06 | 0.00212008 | 11.6248 | 64.4342 | 12.8004 | 0.0270165 | 0.00650284 | 5.57167e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1428.68 | 0.0357678 | 9878.75ms | 1151920 | 640 | 4.84107e+07 | 768934 | 0.0506839 | 3.58176 | 17.0623 | 3.3874 | 0.00973766 | 0.0398615 | 3.25774e-05 | 1(Win) | true |
| simdjson (ondemand) | 928.351 | 0.146611 | 7483.14ms | 1151920 | 40 | 1.20396e+08 | 1.18334e+06 | 0.189807 | 5.47753 | 29.1282 | 5.70489 | 0.0140457 | 0.0918568 | 1.30434e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1512.69 | 0.073519 | 9728.25ms | 1151920 | 160 | 4.56106e+07 | 726229 | 0.0597104 | 3.37882 | 16.5608 | 3.26693 | 0.00741917 | 0.0351472 | 8.33391e-06 | 1(Win) | true |
| simdjson (ondemand) | 968.527 | 0.106479 | 7410.93ms | 1151920 | 80 | 1.16691e+08 | 1.13426e+06 | 0.0311616 | 5.25983 | 28.6298 | 5.58497 | 0.0116193 | 0.0828316 | 9.26714e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5232.54 | 0.0389294 | 5019.88ms | 500299 | 640 | 806437 | 91183.7 | 0.177113 | 0.981076 | 5.40903 | 0.739194 | 0.000951197 | 2.01442e-06 | 1.81142e-07 | 1(Win) | true |
| simdjson (ondemand) | 4927.64 | 0.0217488 | 5327.21ms | 500299 | 1280 | 567622 | 96825.6 | 0.0580273 | 1.04498 | 5.5135 | 0.724737 | 0.00121607 | 2.64685e-06 | 6.04326e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5371.42 | 0.023312 | 9685.45ms | 500299 | 640 | 274424 | 88826.2 | 0.0113868 | 0.958592 | 5.37987 | 0.732364 | 0.00089612 | 3.31364e-06 | 1.4991e-07 | 1(Win) | true |
| simdjson (ondemand) | 4981.01 | 0.0790807 | 5279.08ms | 500299 | 160 | 918093 | 95788.3 | 0.00187911 | 1.03372 | 5.48437 | 0.717925 | 0.0011865 | 7.82032e-06 | 8.61985e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8627.6 | 0.0410913 | 6877.48ms | 1151920 | 640 | 1.75204e+06 | 127330 | 0.014886 | 0.591532 | 3.03778 | 0.353951 | 0.000949827 | 0.00812867 | 3.89024e-06 | 1(Win) | true |
| simdjson (ondemand) | 8343.52 | 0.0254865 | 7139ms | 1151920 | 1280 | 1.44137e+06 | 131666 | 0.031546 | 0.614989 | 3.07951 | 0.347817 | 0.00116849 | 0.0121733 | 4.53726e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8794.37 | 0.0339599 | 6829.41ms | 1151920 | 40 | 71982.7 | 124916 | 0.0116492 | 0.585769 | 3.02512 | 0.350985 | 0.000905901 | 0.00736564 | 1.08949e-05 | 1(Win) | true |
| simdjson (ondemand) | 8388.46 | 0.0249379 | 7066.66ms | 1151920 | 2560 | 2.73048e+06 | 130960 | 0.0819224 | 0.610672 | 3.06686 | 0.344858 | 0.00115899 | 0.0116464 | 2.07297e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2965.33 | 0.0619026 | 8609.89ms | 500299 | 640 | 6.34906e+06 | 160900 | 0.0171069 | 1.73284 | 9.81426 | 1.76937 | 0.00220518 | 8.20135e-06 | 4.71593e-07 | 1(Win) | true |
| simdjson (ondemand) | 2911.28 | 0.12006 | 8744.85ms | 500299 | 80 | 3.09727e+06 | 163887 | 0.0940919 | 1.75306 | 10.122 | 1.72963 | 0.00239514 | 1.99381e-05 | 2.72337e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2977.53 | 0.134958 | 8585.64ms | 500299 | 160 | 7.48285e+06 | 160241 | 0.162144 | 1.72616 | 9.78511 | 1.76254 | 0.00215867 | 1.05062e-05 | 1.41166e-06 | 1(Win) | true |
| simdjson (ondemand) | 2937.41 | 0.0407378 | 8726.88ms | 500299 | 2560 | 1.1209e+07 | 162430 | 0.0294793 | 1.74196 | 10.0929 | 1.72282 | 0.0023549 | 1.06881e-05 | 3.20824e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5453.79 | 0.0643732 | 5341.92ms | 1151920 | 160 | 2.69017e+06 | 201430 | 0.00938689 | 0.92745 | 5.08125 | 0.784306 | 0.00174341 | 0.00904946 | 1.72267e-05 | 1(Win) | true |
| Jsonifier (generic) | 5305.4 | 0.11577 | 5467.09ms | 1151920 | 320 | 1.83887e+07 | 207064 | 0.0785142 | 0.953455 | 4.97646 | 0.804974 | 0.00145868 | 0.00510395 | 4.70899e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5476.82 | 0.0702831 | 5322.55ms | 1151920 | 40 | 794966 | 200583 | 0.198516 | 0.921927 | 5.0685 | 0.781332 | 0.00171462 | 0.00812635 | 1.77964e-05 | 1(Win) | true |
| Jsonifier (generic) | 5379.54 | 0.088705 | 5407.22ms | 1151920 | 640 | 2.10005e+07 | 204210 | 0.169094 | 0.940782 | 4.96371 | 0.801993 | 0.00142015 | 0.0041493 | 2.71503e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1435.33 | 0.117398 | 4487.76ms | 56369 | 40 | 77331.3 | 37453.2 | 0.0142643 | 3.59088 | 15.578 | 3.10793 | 0.00688543 | 9.44668e-05 | 7.89441e-05 | 1(Win) | true |
| simdjson (ondemand) | 1238.45 | 0.0381695 | 5095.98ms | 56369 | 640 | 175685 | 43407.1 | 0.0694248 | 4.15196 | 16.9805 | 2.84656 | 0.0101714 | 1.56613e-05 | 7.31785e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1801.59 | 0.139991 | 4070.35ms | 56369 | 30 | 52346.5 | 29838.9 | 0.0120633 | 2.86175 | 13.2873 | 2.60734 | 0.00533922 | 1.36009e-05 | 8.27878e-06 | 1(Win) | true |
| simdjson (ondemand) | 1435.75 | 0.0289285 | 4832.59ms | 56369 | 2560 | 300342 | 37442.3 | 0.113488 | 3.56979 | 14.7335 | 2.35618 | 0.0120577 | 1.09352e-05 | 4.26182e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1980.1 | 0.0734637 | 4775.96ms | 83958 | 40 | 35298.3 | 40436.6 | 0.0167781 | 2.60468 | 11.0484 | 2.09804 | 0.00552181 | 3.7221e-05 | 2.9479e-05 | 1(Win) | true |
| simdjson (ondemand) | 1755.13 | 0.0462032 | 5313.17ms | 83958 | 640 | 284334 | 45619.7 | 0.0210186 | 2.92441 | 11.8163 | 1.93134 | 0.00876 | 2.42495e-05 | 1.48512e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2450.05 | 0.122228 | 4343.15ms | 83958 | 30 | 47867.4 | 32680.4 | 0.0832996 | 2.10414 | 9.51012 | 1.76283 | 0.00406394 | 5.55833e-06 | 3.17619e-06 | 1(Win) | true |
| simdjson (ondemand) | 2095.4 | 0.017463 | 4911.12ms | 83958 | 4890 | 217738 | 38211.6 | 0.168929 | 2.44847 | 10.285 | 1.59742 | 0.00756737 | 8.80273e-06 | 3.43925e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 706.748 | 0.0281327 | 8350.54ms | 56369 | 4890 | 2.23916e+06 | 76063.4 | 0.176208 | 7.24386 | 35.3631 | 7.26097 | 0.0116265 | 6.3727e-05 | 3.9707e-05 | 1(Win) | true |
| simdjson (ondemand) | 209.465 | 0.0611225 | 6755.2ms | 56369 | 640 | 1.57485e+07 | 256643 | 0.0185628 | 24.4592 | 139.872 | 28.1085 | 0.0380251 | 8.50146e-05 | 4.84531e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.162 | 0.0440369 | 7852.22ms | 56369 | 640 | 575920 | 68119.9 | 0.179194 | 6.5108 | 33.074 | 6.7659 | 0.00944097 | 9.84029e-06 | 1.74631e-06 | 1(Win) | true |
| simdjson (ondemand) | 215.774 | 0.125346 | 6651.28ms | 56369 | 80 | 7.80173e+06 | 249138 | 0.0743812 | 23.7649 | 137.612 | 27.6215 | 0.0326857 | 4.05808e-05 | 2.04013e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 923.345 | 0.0404554 | 9499.03ms | 83958 | 640 | 787645 | 86715.8 | 0.0944635 | 5.55791 | 25.0738 | 5.23875 | 0.00835178 | 1.60236e-05 | 7.0906e-06 | 1(Win) | true |
| simdjson (ondemand) | 306.145 | 0.0949978 | 6848.75ms | 83958 | 640 | 3.95072e+07 | 261538 | 0.0672132 | 16.6201 | 93.9425 | 18.8216 | 0.0237212 | 7.96715e-05 | 3.56205e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1014.41 | 0.055359 | 9013.33ms | 83958 | 30 | 57279.1 | 78931.3 | 0.0277801 | 5.07918 | 23.5346 | 4.90563 | 0.00692092 | 1.86601e-05 | 9.13155e-06 | 1(Win) | true |
| simdjson (ondemand) | 318.467 | 0.229561 | 6715.21ms | 83958 | 40 | 1.33245e+07 | 251419 | 0.215288 | 16.0237 | 92.4364 | 18.4974 | 0.0217478 | 2.02482e-05 | 5.95536e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2393.72 | 0.0200617 | 2990.8ms | 56369 | 2560 | 51964.7 | 22457.8 | 0.3049 | 2.15189 | 9.92209 | 1.77376 | 0.00350093 | 2.52937e-05 | 1.61325e-05 | 1(Win) | true |
| simdjson (ondemand) | 1910.86 | 0.0442264 | 3536.16ms | 56369 | 1280 | 198152 | 28132.8 | 0.0761647 | 2.67458 | 10.4523 | 1.7053 | 0.010659 | 8.9117e-06 | 3.58963e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2985.04 | 0.0201411 | 2822.43ms | 56369 | 4890 | 64336.2 | 18009 | 0.0439876 | 1.71467 | 8.30045 | 1.42202 | 0.00273841 | 5.84811e-06 | 1.16454e-06 | 1(Win) | true |
| simdjson (ondemand) | 2422.54 | 0.0508196 | 3238.49ms | 56369 | 1280 | 162784 | 22190.6 | 0.0310792 | 2.12285 | 8.82655 | 1.35461 | 0.0065577 | 4.89243e-06 | 1.42754e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3266.09 | 0.0171668 | 3179.75ms | 83958 | 4890 | 86607.6 | 24515.1 | 0.133675 | 1.56892 | 7.19921 | 1.21805 | 0.00261522 | 4.05062e-06 | 1.20081e-06 | 1(Win) | true |
| simdjson (ondemand) | 2810.03 | 0.0288397 | 3578.07ms | 83958 | 2560 | 172871 | 28493.8 | 0.0537604 | 1.8325 | 7.42931 | 1.16355 | 0.00614419 | 8.90977e-06 | 3.88494e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4036.92 | 0.0527629 | 2990.25ms | 83958 | 640 | 70090.8 | 19834.1 | 0.0493698 | 1.26935 | 6.10439 | 0.980324 | 0.00197264 | 3.51738e-06 | 9.30525e-07 | 1(Win) | true |
| simdjson (ondemand) | 3421.66 | 0.0255299 | 3363.08ms | 83958 | 4890 | 174525 | 23400.5 | 0.142883 | 1.50032 | 6.34556 | 0.93007 | 0.00442575 | 3.97998e-06 | 8.91477e-07 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1776.76 | 0.0162513 | 3758.56ms | 56369 | 4890 | 118226 | 30256.1 | 0.00287917 | 2.88616 | 13.3852 | 2.5076 | 0.00652264 | 2.02507e-05 | 1.18377e-05 | 1(Win) | true |
| simdjson (ondemand) | 1297.16 | 0.0890276 | 4800.8ms | 56369 | 640 | 871214 | 41442.7 | 0.105025 | 3.93463 | 17.4915 | 2.9041 | 0.00936871 | 5.7933e-06 | 1.41368e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2092.93 | 0.0185667 | 3587.52ms | 56369 | 4890 | 111212 | 25685.4 | 0.0355788 | 2.44278 | 11.819 | 2.17036 | 0.00572602 | 6.22541e-06 | 1.09924e-06 | 1(Win) | true |
| simdjson (ondemand) | 1485.95 | 0.0531106 | 4625.14ms | 56369 | 2560 | 945087 | 36177.2 | 0.0735768 | 3.45266 | 15.9152 | 2.56765 | 0.00923643 | 6.7011e-06 | 2.21753e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2491.75 | 0.0888382 | 3955.32ms | 83958 | 80 | 65193.5 | 32133.5 | 0.0176965 | 2.06846 | 9.71114 | 1.73789 | 0.00444448 | 6.99755e-06 | 2.38214e-06 | 1(Win) | true |
| simdjson (ondemand) | 1898.49 | 0.03005 | 4947.57ms | 83958 | 4890 | 785432 | 42175 | 0.0379746 | 2.70094 | 12.0205 | 1.94246 | 0.00610813 | 8.32045e-06 | 3.37105e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2865.63 | 0.038388 | 3809.18ms | 83958 | 2560 | 294521 | 27941 | 0.0125136 | 1.79343 | 8.65541 | 1.51091 | 0.00417672 | 4.31298e-06 | 1.05149e-06 | 1(Win) | true |
| simdjson (ondemand) | 2115.42 | 0.0317791 | 4799.01ms | 83958 | 4890 | 707497 | 37850 | 0.0771397 | 2.42057 | 10.9582 | 1.71597 | 0.00572301 | 1.17183e-05 | 5.74589e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1290.08 | 0.0327359 | 4680.31ms | 53331 | 2560 | 426397 | 39424.2 | 0.0301649 | 3.96976 | 13.984 | 2.75474 | 0.0129809 | 2.99647e-05 | 9.08243e-06 | 1(Win) | true |
| simdjson (ondemand) | 1012.33 | 0.0313156 | 5752.91ms | 53331 | 2560 | 633690 | 50240.8 | 0.105525 | 5.07477 | 18.8423 | 3.49368 | 0.0193669 | 4.56246e-05 | 2.44127e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1606.49 | 0.0362152 | 4443.34ms | 53331 | 2560 | 336530 | 31659.3 | 0.0205871 | 3.1895 | 11.7525 | 2.24271 | 0.0103168 | 1.73079e-05 | 6.50419e-06 | 1(Win) | true |
| simdjson (ondemand) | 1195.8 | 0.0329738 | 5560.82ms | 53331 | 2560 | 503521 | 42532.4 | 0.0465147 | 4.286 | 16.6623 | 2.99522 | 0.0156893 | 1.98349e-05 | 8.73818e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1472.99 | 0.0831576 | 4964.21ms | 65103 | 320 | 393151 | 42150.5 | 0.015631 | 3.49324 | 12.0117 | 2.32166 | 0.0111118 | 3.52806e-05 | 2.39524e-05 | 1(Win) | true |
| simdjson (ondemand) | 1222.33 | 0.0434016 | 5835.02ms | 65103 | 1280 | 622086 | 50794.2 | 0.0298773 | 4.20907 | 15.6129 | 2.86082 | 0.0157889 | 8.68216e-05 | 5.96411e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1809.04 | 0.0220942 | 4704.54ms | 65103 | 4890 | 281173 | 34320.5 | 0.0237038 | 2.84123 | 10.182 | 1.90286 | 0.00864337 | 1.13616e-05 | 4.00184e-06 | 1(Win) | true |
| simdjson (ondemand) | 1441.45 | 0.0481165 | 5589.07ms | 65103 | 1280 | 549795 | 43072.6 | 0.105068 | 3.55684 | 13.8299 | 2.45393 | 0.0129471 | 2.07364e-05 | 7.68014e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 981.889 | 0.085257 | 5948.93ms | 53331 | 320 | 624087 | 51798.6 | 0.0457812 | 5.22394 | 19.492 | 3.91626 | 0.0159465 | 7.19563e-05 | 4.73458e-05 | 1(Win) | true |
| simdjson (ondemand) | 444.895 | 0.102143 | 6239.59ms | 53331 | 640 | 8.72656e+06 | 114320 | 0.0356424 | 11.5457 | 40.8025 | 7.36421 | 0.064802 | 8.2152e-05 | 4.35957e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1152.24 | 0.0279083 | 5705.34ms | 53331 | 2560 | 388489 | 44140.4 | 0.0234221 | 4.46017 | 17.1984 | 3.39203 | 0.0134824 | 3.1957e-05 | 1.78792e-05 | 1(Win) | true |
| simdjson (ondemand) | 481.43 | 0.145701 | 6069.36ms | 53331 | 320 | 7.58171e+06 | 105644 | 0.123036 | 10.6544 | 38.544 | 6.84824 | 0.0600383 | 8.32654e-05 | 2.85364e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1079.03 | 0.0559074 | 6502.11ms | 65103 | 640 | 662301 | 57539.8 | 0.0845836 | 4.77021 | 16.9316 | 3.39064 | 0.014793 | 2.97605e-05 | 1.02242e-05 | 1(Win) | true |
| simdjson (ondemand) | 562.85 | 0.0655918 | 6003.5ms | 65103 | 1280 | 6.70077e+06 | 110308 | 0.00641213 | 9.08616 | 33.2686 | 5.9672 | 0.046913 | 6.04091e-05 | 3.13086e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1255.86 | 0.0737712 | 6239.29ms | 65103 | 320 | 425640 | 49437.8 | 0.0172848 | 4.1013 | 15.0459 | 2.96008 | 0.0119704 | 1.86723e-05 | 1.10402e-05 | 1(Win) | true |
| simdjson (ondemand) | 619.29 | 0.088312 | 5824.58ms | 65103 | 640 | 5.01688e+06 | 100255 | 0.164895 | 8.31355 | 31.4199 | 5.54554 | 0.042053 | 2.81765e-05 | 8.92816e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7879.05 | 0.0296356 | 1368.16ms | 53331 | 2560 | 9368.67 | 6455.14 | 0.0141824 | 0.657563 | 2.99372 | 0.41985 | 0.000853551 | 3.03236e-06 | 5.05393e-07 | 1(Win) | true |
| simdjson (ondemand) | 6753.23 | 0.0525516 | 1478.94ms | 53331 | 1280 | 20050.1 | 7531.27 | 0.0828173 | 0.765025 | 3.34413 | 0.415462 | 0.000919728 | 3.76481e-06 | 5.42016e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8715.56 | 0.0288387 | 1320.07ms | 53331 | 2560 | 7250.35 | 5835.59 | 0.0330584 | 0.594898 | 2.82537 | 0.382536 | 0.000736497 | 3.5231e-06 | 6.59209e-07 | 1(Win) | true |
| simdjson (ondemand) | 7206.49 | 0.0946413 | 1439.19ms | 53331 | 320 | 14276.6 | 7057.59 | 0.0437281 | 0.71838 | 3.18515 | 0.380042 | 0.000838806 | 4.8049e-06 | 1.05473e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8220.37 | 0.0190934 | 1478.17ms | 65103 | 4890 | 10169.4 | 7552.83 | 0.0845422 | 0.629594 | 2.82454 | 0.358279 | 0.000793507 | 2.82704e-06 | 1.91611e-07 | 1(Win) | true |
| simdjson (ondemand) | 7616.71 | 0.0240321 | 1536.04ms | 65103 | 2560 | 9824.1 | 8151.43 | 0.0160606 | 0.679316 | 2.98593 | 0.352703 | 0.000758636 | 3.24006e-06 | 7.50013e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8962.3 | 0.027351 | 1430.64ms | 65103 | 2560 | 9190.74 | 6927.58 | 0.00489463 | 0.577843 | 2.68664 | 0.327712 | 0.000631811 | 2.46004e-06 | 1.14002e-07 | 1(Win) | true |
| simdjson (ondemand) | 8104.32 | 0.0270427 | 1500.63ms | 65103 | 2560 | 10987.8 | 7660.98 | 0.0391187 | 0.638689 | 2.852 | 0.322981 | 0.000723127 | 2.46604e-06 | 3.72007e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5692.12 | 0.0437461 | 1616.51ms | 53331 | 1280 | 19557 | 8935.24 | 0.0158544 | 0.908797 | 4.36592 | 0.711481 | 0.0017715 | 2.98841e-06 | 3.51578e-07 | 1(Win) | true |
| simdjson (ondemand) | 4077.51 | 0.034156 | 1974.57ms | 53331 | 1280 | 23233.5 | 12473.4 | 0.0280769 | 1.26703 | 5.90441 | 0.948079 | 0.00226859 | 4.27753e-06 | 8.20348e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6150.74 | 0.0261078 | 1588.02ms | 53331 | 2560 | 11931.2 | 8268.98 | 0.00717049 | 0.841185 | 4.19786 | 0.674261 | 0.00154283 | 3.32534e-06 | 6.59209e-07 | 1(Win) | true |
| simdjson (ondemand) | 4254.65 | 0.022595 | 1958.04ms | 53331 | 2560 | 18676.5 | 11954.1 | 0.00189204 | 1.21387 | 5.73871 | 0.911403 | 0.00219147 | 4.18964e-06 | 7.98375e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5972.24 | 0.0274317 | 1761.86ms | 65103 | 2560 | 20819.7 | 10395.9 | 0.0759298 | 0.865559 | 3.95613 | 0.606393 | 0.00155171 | 6.83412e-06 | 3.40806e-06 | 1(Win) | true |
| simdjson (ondemand) | 4738.99 | 0.0331745 | 2036.3ms | 65103 | 1280 | 24179.6 | 13101.3 | 0.0709229 | 1.0896 | 5.07872 | 0.788105 | 0.00195291 | 3.50406e-06 | 1.10402e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6313.22 | 0.0345641 | 1724.39ms | 65103 | 2560 | 29579.5 | 9834.46 | 0.0375376 | 0.816936 | 3.81883 | 0.57598 | 0.00128611 | 4.51208e-06 | 1.32002e-06 | 1(Win) | true |
| simdjson (ondemand) | 4929.89 | 0.0372419 | 1998.15ms | 65103 | 320 | 7039.5 | 12594 | 0.00424327 | 1.04816 | 4.94298 | 0.75806 | 0.00188264 | 2.44804e-06 | 2.88005e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1319.57 | 0.0609612 | 1578.15ms | 11812 | 1280 | 34665.6 | 8536.72 | 0.0430404 | 3.91556 | 18.1246 | 3.5414 | 0.00497025 | 6.40239e-05 | 3.49221e-05 | 1(Win) | true |
| simdjson (ondemand) | 1035.24 | 0.107957 | 1802.56ms | 11812 | 30 | 4139.87 | 10881.3 | 0.0238999 | 4.99474 | 20.7117 | 3.5963 | 0.0095863 | 2.25759e-05 | 5.64398e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.03 | 0.0245224 | 1560.08ms | 11812 | 4890 | 18221.5 | 7871.8 | 0.122031 | 3.61544 | 17.0348 | 3.29631 | 0.00486816 | 3.19941e-05 | 1.37464e-05 | 1(Win) | true |
| simdjson (ondemand) | 1113.41 | 0.127013 | 1785.53ms | 11812 | 160 | 26421.2 | 10117.4 | 0.0101939 | 4.64178 | 19.6626 | 3.36074 | 0.00761355 | 1.85193e-05 | 3.17474e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2440.18 | 0.0563746 | 1716.42ms | 25388 | 640 | 20024.4 | 9922.17 | 0.0123918 | 2.11793 | 9.32047 | 1.6961 | 0.00333782 | 3.68653e-05 | 2.32639e-05 | 1(Win) | true |
| simdjson (ondemand) | 2136.27 | 0.0428422 | 1855.05ms | 25388 | 1280 | 30178.6 | 11333.7 | 0.00574921 | 2.41842 | 10.2585 | 1.70147 | 0.00391056 | 2.71413e-05 | 1.4063e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2638.53 | 0.0224569 | 1693.34ms | 25388 | 4890 | 20765.5 | 9176.29 | 0.00285419 | 1.96 | 8.84891 | 1.58969 | 0.0028677 | 8.8685e-06 | 2.02985e-06 | 1(Win) | true |
| simdjson (ondemand) | 2269.09 | 0.0734132 | 1840.69ms | 25388 | 640 | 39271.8 | 10670.3 | 0.0598852 | 2.27883 | 9.73901 | 1.58547 | 0.00358388 | 7.01611e-06 | 1.41553e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 779.551 | 0.0194486 | 2166.1ms | 11812 | 4890 | 38622.7 | 14450.4 | 0.0175701 | 6.61965 | 30.0065 | 6.03061 | 0.0161588 | 2.67483e-05 | 7.15019e-06 | 1(Win) | true |
| simdjson (ondemand) | 689.698 | 0.0355725 | 2355.63ms | 11812 | 1280 | 43208.3 | 16332.9 | 0.0554929 | 7.4761 | 33.5294 | 6.17449 | 0.013618 | 2.32814e-05 | 7.34158e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 818.34 | 0.0215996 | 2149.58ms | 11812 | 4890 | 43229.5 | 13765.4 | 0.0357491 | 6.30912 | 28.9064 | 5.78412 | 0.015123 | 2.25932e-05 | 2.99512e-06 | 1(Win) | true |
| simdjson (ondemand) | 720.138 | 0.0624712 | 2339.84ms | 11812 | 160 | 15279 | 15642.5 | 0.00391576 | 7.17078 | 32.4524 | 5.93371 | 0.013609 | 2.32814e-05 | 1.05825e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1537.46 | 0.0950598 | 2306.94ms | 25388 | 320 | 71712.4 | 15748 | 0.0964146 | 3.35704 | 14.9887 | 2.93773 | 0.00730894 | 7.75465e-06 | 1.60017e-06 | 1(Win) | true |
| simdjson (ondemand) | 1442.09 | 0.050267 | 2397.59ms | 25388 | 1280 | 91168.9 | 16789.4 | 0.120773 | 3.56422 | 16.0589 | 2.87307 | 0.00695918 | 1.13858e-05 | 1.90789e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1614.25 | 0.0390403 | 2281.35ms | 25388 | 2560 | 87777.1 | 14998.8 | 0.0717029 | 3.1917 | 14.4737 | 2.82228 | 0.0071646 | 8.87784e-06 | 1.63094e-06 | 1(Win) | true |
| simdjson (ondemand) | 1539.4 | 0.0935171 | 2356.84ms | 25388 | 80 | 17307.3 | 15728.2 | 0.0268698 | 3.35344 | 15.5453 | 2.75835 | 0.00673005 | 1.03395e-05 | 2.46179e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2361.3 | 0.0908612 | 1197.67ms | 11812 | 640 | 12024.9 | 4770.58 | 0.155917 | 2.19907 | 10.5319 | 1.9415 | 0.0031713 | 1.15084e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1998.71 | 0.0148347 | 1284.41ms | 11812 | 1280 | 894.781 | 5636.04 | 0.0224194 | 2.59624 | 11.6999 | 1.87343 | 0.00375108 | 1.0384e-05 | 3.30702e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2418.51 | 0.0267244 | 1194.87ms | 11812 | 4890 | 7576.6 | 4657.74 | 0.116446 | 2.1448 | 10.3452 | 1.89604 | 0.00281534 | 1.34521e-05 | 1.09071e-06 | 1(Win) | true |
| simdjson (ondemand) | 2033.37 | 0.0233663 | 1281.92ms | 11812 | 4890 | 8194.09 | 5539.96 | 0.0717774 | 2.54943 | 11.5132 | 1.82797 | 0.00364047 | 1.22575e-05 | 1.41965e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4165.3 | 0.0407278 | 1302.04ms | 25388 | 1280 | 7173.94 | 5812.76 | 0.0544358 | 1.24486 | 5.71057 | 0.959627 | 0.00205363 | 1.03088e-05 | 2.80029e-06 | 1(Win) | true |
| simdjson (ondemand) | 3827.38 | 0.0417091 | 1349.29ms | 25388 | 160 | 1113.87 | 6325.98 | 0.0294334 | 1.35478 | 6.08165 | 0.903695 | 0.00226165 | 7.87774e-06 | 4.92359e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4243.2 | 0.0503064 | 1300.38ms | 25388 | 160 | 1318.36 | 5706.04 | 0.0459827 | 1.22292 | 5.62372 | 0.938475 | 0.00190814 | 7.63156e-06 | 2.46179e-07 | 1(Win) | true |
| simdjson (ondemand) | 3902.55 | 0.0226765 | 1347.94ms | 25388 | 2560 | 5067.03 | 6204.12 | 0.0654504 | 1.32811 | 5.9948 | 0.882543 | 0.00212562 | 7.64694e-06 | 1.53862e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1802.05 | 0.112475 | 1343.85ms | 11812 | 320 | 15818.7 | 6251.09 | 0.0313347 | 2.87349 | 14.0227 | 2.64265 | 0.00845115 | 3.17474e-05 | 1.00533e-05 | 1(Win) | true |
| simdjson (ondemand) | 1596.28 | 0.017493 | 1427.61ms | 11812 | 4890 | 7451.93 | 7056.93 | 0.00428723 | 3.24406 | 14.6073 | 2.41238 | 0.00731712 | 2.26105e-05 | 5.03803e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1840.6 | 0.0721219 | 1339.01ms | 11812 | 640 | 12469.4 | 6120.2 | 0.0552424 | 2.81566 | 13.836 | 2.59719 | 0.00737042 | 2.14295e-05 | 4.62983e-06 | 1(Win) | true |
| simdjson (ondemand) | 1615.14 | 0.0270027 | 1425.13ms | 11812 | 2560 | 9079.88 | 6974.49 | 0.0426849 | 3.20633 | 14.4206 | 2.36692 | 0.00725719 | 1.51792e-05 | 1.02518e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3183.59 | 0.0558444 | 1484.91ms | 25388 | 40 | 721.512 | 7605.23 | 0.187785 | 1.62713 | 7.30054 | 1.30365 | 0.00313337 | 7.87774e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3165.02 | 0.0226278 | 1484.74ms | 25388 | 2560 | 7670.57 | 7649.84 | 0.00503458 | 1.63555 | 7.43434 | 1.15444 | 0.00355611 | 5.63135e-06 | 7.6931e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3242.98 | 0.0219109 | 1475.23ms | 25388 | 2560 | 6850.57 | 7465.93 | 0.000507511 | 1.59642 | 7.20372 | 1.28053 | 0.00293389 | 6.693e-06 | 1.24628e-06 | 1(Win) | true |
| simdjson (ondemand) | 3200.44 | 0.0186255 | 1483.43ms | 25388 | 4890 | 9708.72 | 7565.18 | 0.0759568 | 1.61747 | 7.34749 | 1.13329 | 0.00352359 | 7.69247e-06 | 1.61099e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1519.74 | 0.01545 | 7524.57ms | 108313 | 4890 | 539250 | 67969 | 0.0816415 | 3.37926 | 14.863 | 3.01435 | 0.00431072 | 7.94675e-06 | 3.66279e-06 | 1(Win) | true |
| simdjson (ondemand) | 1439.23 | 0.0253859 | 7916.31ms | 108313 | 2560 | 849818 | 71771.1 | 0.161921 | 3.53711 | 16.6368 | 2.50869 | 0.00605099 | 9.5102e-06 | 4.89395e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1640.03 | 0.0190918 | 7211.37ms | 108313 | 4890 | 707064 | 62983.8 | 0.032037 | 3.12085 | 14.1407 | 2.84712 | 0.00383928 | 8.19597e-06 | 3.84216e-06 | 1(Win) | true |
| simdjson (ondemand) | 1549.97 | 0.0799187 | 7579.63ms | 108313 | 320 | 907745 | 66643.6 | 0.141568 | 3.29023 | 15.9077 | 2.34016 | 0.00563823 | 1.09059e-05 | 5.33754e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2386.72 | 0.0209871 | 8074.08ms | 183677 | 4890 | 1.16017e+06 | 73392.9 | 0.0276464 | 2.14199 | 9.5816 | 1.82734 | 0.00243788 | 9.97906e-06 | 4.67278e-06 | 1(Win) | true |
| simdjson (ondemand) | 2312.77 | 0.0460388 | 8296.96ms | 183677 | 4890 | 5.94567e+06 | 75739.5 | 0.0673633 | 2.19518 | 10.3195 | 1.50024 | 0.00403934 | 7.85588e-06 | 3.03168e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2585.07 | 0.0345502 | 7691.49ms | 183677 | 1280 | 701577 | 67761.4 | 0.152275 | 1.98671 | 9.16416 | 1.73058 | 0.00205054 | 1.96507e-06 | 1.99909e-07 | 1(Win) | true |
| simdjson (ondemand) | 2473.99 | 0.0264546 | 7987.69ms | 183677 | 2560 | 898169 | 70804 | 0.0580883 | 2.05754 | 9.89507 | 1.40204 | 0.00385528 | 5.89945e-06 | 1.71624e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 620.573 | 0.0660491 | 8829.87ms | 108313 | 320 | 3.86776e+06 | 166452 | 0.0624746 | 8.20566 | 38.0687 | 7.59222 | 0.0130083 | 1.17137e-05 | 4.5297e-06 | 1(Win) | true |
| simdjson (ondemand) | 247.729 | 0.0883777 | 5399.22ms | 108313 | 320 | 4.34552e+07 | 416968 | 0.0310262 | 20.6373 | 100.108 | 18.134 | 0.0682448 | 3.74205e-05 | 2.11771e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.921 | 0.0292511 | 8649.49ms | 108313 | 640 | 1.39613e+06 | 159672 | 0.0698783 | 7.96098 | 37.3482 | 7.42665 | 0.0122304 | 6.23194e-06 | 9.95379e-07 | 1(Win) | true |
| simdjson (ondemand) | 251.902 | 0.0536547 | 5336.32ms | 108313 | 640 | 3.09809e+07 | 410062 | 0.0816209 | 20.3111 | 99.3922 | 17.9694 | 0.0662405 | 2.5952e-05 | 1.21177e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.533 | 0.0177697 | 9566.94ms | 183677 | 2560 | 2.60632e+06 | 179561 | 0.0224397 | 5.267 | 24.1524 | 4.78826 | 0.00564106 | 1.71284e-05 | 1.02209e-05 | 1(Win) | true |
| simdjson (ondemand) | 423.222 | 0.0786757 | 5344.44ms | 183677 | 640 | 6.78631e+07 | 413891 | 0.126817 | 12.0624 | 58.7412 | 10.5637 | 0.0377536 | 5.49198e-05 | 3.04202e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1002.5 | 0.023503 | 9380.27ms | 183677 | 2560 | 4.31742e+06 | 174731 | 0.0946097 | 5.10718 | 23.7295 | 4.69105 | 0.00524691 | 1.91615e-05 | 7.8709e-06 | 1(Win) | true |
| simdjson (ondemand) | 432.395 | 0.0932883 | 5267.68ms | 183677 | 640 | 9.14077e+07 | 405111 | 0.000547692 | 11.8099 | 58.3182 | 10.4665 | 0.0367652 | 3.4512e-05 | 1.46061e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4713.76 | 0.022571 | 2920.55ms | 108313 | 1280 | 31314 | 21913.6 | 0.0482309 | 1.09422 | 5.5397 | 0.85313 | 0.000895747 | 3.45498e-06 | 9.2325e-07 | 1(Win) | true |
| simdjson (ondemand) | 4211.19 | 0.0245377 | 3171.04ms | 108313 | 4890 | 177145 | 24528.8 | 0.0706895 | 1.21987 | 6.09758 | 0.770028 | 0.0017308 | 4.99008e-06 | 2.40914e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4961.5 | 0.0347776 | 2812.31ms | 108313 | 1280 | 67103.4 | 20819.4 | 0.0254056 | 1.03555 | 5.35389 | 0.803671 | 0.000664877 | 2.20715e-06 | 1.87535e-07 | 1(Win) | true |
| simdjson (ondemand) | 4418.5 | 0.0243455 | 3074.99ms | 108313 | 4890 | 158401 | 23377.9 | 0.104966 | 1.16557 | 5.91343 | 0.721012 | 0.00146751 | 2.13726e-06 | 4.45577e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6484.52 | 0.0706135 | 3427.86ms | 183677 | 160 | 58217 | 27013.3 | 0.0217207 | 0.795165 | 3.87686 | 0.535059 | 0.000573153 | 2.79703e-05 | 2.62009e-05 | 1(Win) | true |
| simdjson (ondemand) | 6251.75 | 0.0545777 | 3534.81ms | 183677 | 640 | 149664 | 28019 | 0.0529828 | 0.822578 | 4.11054 | 0.47638 | 0.0011807 | 2.28832e-06 | 1.05484e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6775.08 | 0.0301817 | 3326.31ms | 183677 | 640 | 38971.7 | 25854.8 | 0.000290083 | 0.761094 | 3.768 | 0.506046 | 0.000400295 | 1.11439e-06 | 7.6561e-08 | 1(Win) | true |
| simdjson (ondemand) | 6529.14 | 0.168942 | 3435.02ms | 183677 | 40 | 82173.9 | 26828.7 | 0.0388417 | 0.789868 | 4.00195 | 0.447476 | 0.00104912 | 1.08887e-06 | 0 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3303.2 | 0.154703 | 3841.42ms | 108313 | 640 | 1.49786e+06 | 31271.3 | 0.335901 | 1.5559 | 8.1892 | 1.44348 | 0.00150575 | 5.25099e-06 | 2.06289e-06 | 1(Win) | true |
| simdjson (ondemand) | 2625.36 | 0.0308991 | 4667.2ms | 108313 | 2560 | 378371 | 39345.2 | 0.286061 | 1.95646 | 10.3411 | 1.59589 | 0.00282828 | 7.4978e-06 | 3.25662e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3407.01 | 0.207754 | 3790.78ms | 108313 | 320 | 1.26959e+06 | 30318.5 | 0.0553913 | 1.51315 | 8.00572 | 1.39499 | 0.00127302 | 1.8465e-06 | 1.73109e-07 | 1(Win) | true |
| simdjson (ondemand) | 2719.69 | 0.113232 | 4557.3ms | 108313 | 160 | 295927 | 37980.6 | 0.0399706 | 1.89502 | 10.1578 | 1.5475 | 0.00262261 | 3.17367e-06 | 5.19328e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5012.14 | 0.0213931 | 4214.51ms | 183677 | 2560 | 143103 | 34948.7 | 0.0445678 | 1.02481 | 5.5993 | 0.900124 | 0.000901304 | 2.58606e-06 | 6.76289e-07 | 1(Win) | true |
| simdjson (ondemand) | 4046.58 | 0.0416988 | 5048.84ms | 183677 | 1280 | 417054 | 43287.9 | 0.0306736 | 1.26686 | 6.5987 | 0.960719 | 0.00183773 | 2.48823e-06 | 3.78552e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5206.46 | 0.0210593 | 4105.95ms | 183677 | 2560 | 128515 | 33644.4 | 0.05501 | 0.987566 | 5.4911 | 0.87153 | 0.000745277 | 1.85235e-06 | 1.48869e-07 | 1(Win) | true |
| simdjson (ondemand) | 4163.7 | 0.0879907 | 4945.12ms | 183677 | 320 | 438504 | 42070.3 | 0.00210218 | 1.23287 | 6.49051 | 0.932126 | 0.00177256 | 3.02841e-06 | 6.97556e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 595.808 | 0.0667951 | 9148.39ms | 1834197 | 160 | 6.15302e+08 | 2.93589e+06 | 0.0374846 | 8.48355 | 36.8087 | 7.30777 | 0.0387074 | 0.139031 | 0.00216662 | 1(Win) | true |
| simdjson (ondemand) | 579.56 | 0.0904577 | 9405.72ms | 1834197 | 80 | 5.96316e+08 | 3.0182e+06 | 0.0797332 | 8.76124 | 37.2147 | 6.35849 | 0.0452937 | 0.139466 | 0.00153412 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 647.816 | 0.0802714 | 9130.64ms | 1834197 | 160 | 7.51676e+08 | 2.70019e+06 | 0.00378413 | 7.83718 | 33.8187 | 6.60873 | 0.0374876 | 0.118291 | 0.00130065 | 1(Win) | true |
| simdjson (ondemand) | 623.509 | 0.096303 | 9413.75ms | 1834197 | 40 | 2.91975e+08 | 2.80545e+06 | 0.146193 | 8.11485 | 34.2262 | 5.65997 | 0.0443827 | 0.118706 | 0.0010315 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2185.61 | 0.0477547 | 10004.7ms | 7351818 | 160 | 3.75489e+08 | 3.20791e+06 | 0.205234 | 2.31534 | 10.0418 | 1.86246 | 0.0103707 | 0.0588626 | 0.00285209 | 1(Win) | true |
| simdjson (ondemand) | 2060.41 | 0.173241 | 5098.74ms | 7351818 | 30 | 1.04257e+09 | 3.40284e+06 | 0.674996 | 2.4488 | 10.1996 | 1.62643 | 0.0111239 | 0.0587552 | 0.00948023 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2353.8 | 0.112919 | 10062.2ms | 7351818 | 40 | 4.52529e+08 | 2.97869e+06 | 0.162462 | 2.15271 | 9.29634 | 1.68823 | 0.0100872 | 0.0536666 | 0.00301817 | 1(Win) | true |
| simdjson (ondemand) | 2251.38 | 0.0986035 | 5108.75ms | 7351818 | 30 | 2.82877e+08 | 3.1142e+06 | 0.834218 | 2.24744 | 9.45416 | 1.45213 | 0.0108794 | 0.0535217 | 0.0031925 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 384.474 | 0.218971 | 6777.57ms | 1834197 | 80 | 7.93999e+09 | 4.54966e+06 | 0.251996 | 13.1227 | 64.1942 | 13.4199 | 0.0385662 | 0.343896 | 0.020975 | 1(Win) | true |
| simdjson (ondemand) | 266.716 | 0.0994834 | 9884.98ms | 1834197 | 40 | 1.70277e+09 | 6.55839e+06 | 0.22056 | 18.975 | 105.333 | 21.2119 | 0.0494483 | 0.788908 | 0.00124125 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 407.861 | 0.229549 | 6776.36ms | 1834197 | 30 | 2.90763e+09 | 4.28878e+06 | 0.0334948 | 12.395 | 61.2039 | 12.7205 | 0.0376136 | 0.322776 | 0.0155594 | 1(Win) | true |
| simdjson (ondemand) | 277.478 | 0.140962 | 9828.98ms | 1834197 | 40 | 3.15865e+09 | 6.30402e+06 | 0.257337 | 18.3464 | 102.346 | 20.5133 | 0.0482184 | 0.767718 | 0.00550464 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1373.77 | 0.121926 | 7703.04ms | 7351818 | 80 | 3.09776e+09 | 5.10367e+06 | 0.309632 | 3.68324 | 17.0514 | 3.3956 | 0.0103912 | 0.186412 | 0.00172323 | 1(Win) | true |
| simdjson (ondemand) | 896.034 | 0.213482 | 5538.2ms | 7351818 | 40 | 1.11616e+10 | 7.82475e+06 | 1.39708 | 5.69212 | 27.194 | 5.33205 | 0.0120835 | 0.43583 | 0.00708829 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1416.08 | 0.245476 | 7818.35ms | 7351818 | 30 | 4.43154e+09 | 4.95117e+06 | 0.118635 | 3.59021 | 16.3057 | 3.22128 | 0.0100694 | 0.181159 | 0.00347038 | 1(Win) | true |
| simdjson (ondemand) | 921.077 | 0.281808 | 5550.21ms | 7351818 | 40 | 1.84062e+10 | 7.612e+06 | 2.05119 | 5.55472 | 26.4489 | 5.15787 | 0.0117924 | 0.430494 | 0.00561963 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4744.56 | 0.0826638 | 9613.94ms | 1834197 | 640 | 5.94443e+07 | 368680 | 0.0350252 | 1.07203 | 6.28014 | 0.838105 | 0.0021911 | 0.0755262 | 5.57465e-06 | 1(Win) | true |
| simdjson (ondemand) | 4394.17 | 0.0804067 | 5182.74ms | 1834197 | 80 | 8.19622e+06 | 398079 | 0.0350776 | 1.16933 | 6.33083 | 0.867833 | 0.00330446 | 0.0754515 | 8.85946e-07 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4784.78 | 0.0600894 | 9590.45ms | 1834197 | 160 | 7.72118e+06 | 365581 | 0.024532 | 1.07219 | 6.27992 | 0.838056 | 0.00220732 | 0.075505 | 1.92182e-06 | 1(Win) | true |
| simdjson (ondemand) | 4352.38 | 0.0428445 | 5209.37ms | 1834197 | 640 | 1.89762e+07 | 401901 | 0.175677 | 1.17061 | 6.33061 | 0.867784 | 0.00335713 | 0.0754283 | 2.39461e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10367.3 | 0.200584 | 8667.38ms | 7351818 | 160 | 2.94422e+08 | 676284 | 0.283373 | 0.489518 | 2.37653 | 0.241967 | 0.00110275 | 0.0423859 | 1.36148e-05 | 1(Win) | true |
| simdjson (ondemand) | 9522.8 | 0.137365 | 9455.15ms | 7351818 | 40 | 4.09142e+07 | 736258 | 0.270602 | 0.535494 | 2.4948 | 0.256653 | 0.000955274 | 0.042426 | 0.000309641 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10211.3 | 0.123244 | 8861.3ms | 7351818 | 80 | 5.72856e+07 | 686615 | 0.0371106 | 0.497501 | 2.37647 | 0.241955 | 0.00107651 | 0.0423764 | 0.00025096 | 1(Win) | true |
| simdjson (ondemand) | 9581.8 | 0.158774 | 9424.47ms | 7351818 | 40 | 5.39901e+07 | 731724 | 0.0684549 | 0.533179 | 2.49474 | 0.25664 | 0.000979577 | 0.0424141 | 0.000230392 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3363.51 | 0.167794 | 6710.12ms | 1834197 | 640 | 4.87346e+08 | 520060 | 0.0988655 | 1.51523 | 8.73485 | 1.53934 | 0.00225533 | 0.113182 | 6.19907e-06 | 1(Win) | true |
| simdjson (ondemand) | 2477.26 | 0.128817 | 9277.71ms | 1834197 | 30 | 2.48209e+07 | 706113 | 0.110761 | 2.07004 | 12.6414 | 2.27011 | 0.00381346 | 0.150276 | 1.25395e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3399.85 | 0.199842 | 6654.39ms | 1834197 | 320 | 3.38295e+08 | 514501 | 0.0606531 | 1.51383 | 8.73463 | 1.53929 | 0.00218296 | 0.113154 | 1.08358e-06 | 1(Win) | true |
| simdjson (ondemand) | 2399.63 | 0.293955 | 9246.66ms | 1834197 | 320 | 1.46932e+09 | 728957 | 0.140738 | 2.12772 | 12.6412 | 2.27006 | 0.00331183 | 0.150211 | 2.96622e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7877.93 | 0.0729367 | 5666.87ms | 7351818 | 160 | 6.74183e+07 | 889986 | 0.383099 | 0.652742 | 3.0764 | 0.416921 | 0.00108517 | 0.0635544 | 0.000188254 | 1(Win) | true |
| simdjson (ondemand) | 6083.59 | 0.314945 | 7318.05ms | 7351818 | 30 | 3.95241e+08 | 1.15248e+06 | 0.101772 | 0.84024 | 4.06923 | 0.606505 | 0.000983566 | 0.0848139 | 0.000373032 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7847.81 | 0.105841 | 5718.18ms | 7351818 | 160 | 1.4306e+08 | 893401 | 0.175055 | 0.655049 | 3.07634 | 0.416909 | 0.00109182 | 0.0635435 | 0.000221472 | 1(Win) | true |
| simdjson (ondemand) | 6135.47 | 0.123685 | 7321.87ms | 7351818 | 160 | 3.19632e+08 | 1.14274e+06 | 0.176708 | 0.836344 | 4.06917 | 0.606493 | 0.000986344 | 0.0847926 | 0.000369267 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1235.37 | 0.183092 | 8303.43ms | 409725 | 30 | 1.00612e+07 | 316296 | 0.00993893 | 4.14443 | 18.6315 | 3.68698 | 0.0104689 | 0.0157703 | 3.16472e-05 | 1(Win) | true |
| simdjson (ondemand) | 969.839 | 0.0935724 | 5219.25ms | 409725 | 160 | 2.27406e+07 | 402896 | 0.10786 | 5.24375 | 21.0938 | 3.77434 | 0.0168974 | 0.0281846 | 9.84654e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1558.34 | 0.0329243 | 7719.55ms | 409725 | 1280 | 8.72377e+06 | 250744 | 0.0588885 | 3.25898 | 15.6445 | 3.01481 | 0.00653146 | 0.00227621 | 1.02222e-05 | 1(Win) | true |
| simdjson (ondemand) | 1160.74 | 0.0337728 | 9912.11ms | 409725 | 1280 | 1.65446e+07 | 336633 | 0.0711067 | 4.37514 | 18.118 | 3.1048 | 0.0126507 | 0.0104854 | 1.42836e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1891.87 | 0.0211221 | 8921.43ms | 676745 | 1280 | 6.64584e+06 | 341140 | 0.114948 | 2.67454 | 11.9099 | 2.2509 | 0.00702893 | 0.0285989 | 3.39146e-05 | 1(Win) | true |
| simdjson (ondemand) | 1525.51 | 0.0442693 | 5458.41ms | 676745 | 640 | 2.24495e+07 | 423069 | 0.0919055 | 3.32731 | 13.2933 | 2.31081 | 0.0114967 | 0.0424679 | 6.35533e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2334.51 | 0.0377552 | 8465.86ms | 676745 | 160 | 1.74314e+06 | 276458 | 0.049847 | 2.16468 | 10.1038 | 1.84459 | 0.00467508 | 0.016229 | 6.36318e-06 | 1(Win) | true |
| simdjson (ondemand) | 1813.34 | 0.104889 | 5206.99ms | 676745 | 160 | 2.22986e+07 | 355915 | 0.1179 | 2.79919 | 11.4927 | 1.90578 | 0.00887907 | 0.0238034 | 2.89252e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.255 | 0.0964881 | 6145.02ms | 409725 | 160 | 3.38855e+07 | 476951 | 0.0164966 | 6.21561 | 28.815 | 5.82606 | 0.0133943 | 0.0152858 | 2.78235e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.869 | 0.1307 | 5503.77ms | 409725 | 80 | 1.02188e+08 | 864729 | 0.165304 | 11.3222 | 50.5956 | 9.29805 | 0.0365147 | 0.0334486 | 5.18946e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 955.765 | 0.103793 | 5872.35ms | 409725 | 80 | 1.44049e+07 | 408829 | 0.0578575 | 5.32808 | 25.8413 | 5.15292 | 0.00975679 | 0.00226942 | 2.31863e-06 | 1(Win) | true |
| simdjson (ondemand) | 491.477 | 0.134264 | 5365.24ms | 409725 | 80 | 9.11567e+07 | 795040 | 0.105338 | 10.3774 | 47.6272 | 8.62647 | 0.0318493 | 0.0128476 | 5.64098e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1184.69 | 0.0544988 | 7015.69ms | 676745 | 320 | 2.82076e+07 | 544780 | 0.134748 | 4.28922 | 18.5598 | 3.71871 | 0.0101989 | 0.0296153 | 2.51156e-05 | 1(Win) | true |
| simdjson (ondemand) | 726.511 | 0.117876 | 5629.3ms | 676745 | 160 | 1.75444e+08 | 888347 | 0.179269 | 6.9889 | 30.9278 | 5.61325 | 0.0229497 | 0.0466802 | 4.11344e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1346 | 0.0362595 | 6738.95ms | 676745 | 160 | 4.83638e+06 | 479489 | 0.243904 | 3.75825 | 16.7587 | 3.31104 | 0.00781141 | 0.0168861 | 9.01373e-06 | 1(Win) | true |
| simdjson (ondemand) | 791.482 | 0.178827 | 5472.9ms | 676745 | 80 | 1.70108e+08 | 815425 | 0.0627714 | 6.42857 | 29.1334 | 5.20714 | 0.0203264 | 0.0263743 | 4.02847e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2425.62 | 0.0788222 | 8618.17ms | 409725 | 160 | 2.57963e+06 | 161091 | 0.0380093 | 2.09838 | 9.75952 | 1.84217 | 0.00594303 | 2.70456e-05 | 5.522e-06 | 1(Win) | true |
| simdjson (ondemand) | 1879.86 | 0.056914 | 5488.62ms | 409725 | 320 | 4.47838e+06 | 207858 | 0.226224 | 2.7065 | 11.0852 | 1.8133 | 0.00971669 | 6.7164e-05 | 5.83471e-06 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2821.26 | 0.0440257 | 8446.77ms | 409725 | 2560 | 9.51812e+06 | 138500 | 0.0185586 | 1.81003 | 8.73548 | 1.60724 | 0.0044196 | 1.16618e-05 | 4.15294e-06 | 1(Win) | true |
| simdjson (ondemand) | 2134.69 | 0.0902919 | 5410.04ms | 409725 | 160 | 4.3705e+06 | 183045 | 0.00600228 | 2.38545 | 10.0685 | 1.57735 | 0.00775148 | 3.88675e-05 | 4.02709e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3459.74 | 0.0382419 | 9907.11ms | 676745 | 320 | 1.62851e+06 | 186544 | 0.187949 | 1.46296 | 6.54911 | 1.15094 | 0.00421664 | 0.00645237 | 6.46015e-06 | 1(Win) | true |
| simdjson (ondemand) | 2978.91 | 0.04224 | 5719.33ms | 676745 | 640 | 5.35998e+06 | 216654 | 0.24642 | 1.71387 | 7.0958 | 1.09716 | 0.00579269 | 0.00631021 | 4.64771e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3936.5 | 0.0237948 | 9839.32ms | 676745 | 1280 | 1.94808e+06 | 163951 | 0.0863073 | 1.28749 | 5.93055 | 1.00905 | 0.00341042 | 0.00488033 | 6.07573e-06 | 1(Win) | true |
| simdjson (ondemand) | 3369.95 | 0.101704 | 5624.41ms | 676745 | 30 | 1.13815e+06 | 191514 | 0.207664 | 1.52817 | 6.48114 | 0.954434 | 0.00469842 | 0.00474856 | 3.15234e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1843.06 | 0.0551153 | 5593.97ms | 409725 | 320 | 4.36917e+06 | 212008 | 0.296108 | 2.76936 | 12.8282 | 2.46445 | 0.00881192 | 3.37116e-05 | 4.10336e-06 | 1(Win) | true |
| simdjson (ondemand) | 1477.27 | 0.0583821 | 6955.98ms | 409725 | 160 | 3.81544e+06 | 264504 | 0.0959933 | 3.47948 | 15.3611 | 2.62544 | 0.0122444 | 0.000391635 | 6.8186e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2074.3 | 0.0584949 | 5538.82ms | 409725 | 30 | 364249 | 188374 | 0.0759882 | 2.48249 | 11.8053 | 2.22781 | 0.00742238 | 3.57964e-06 | 5.69488e-07 | 1(Win) | true |
| simdjson (ondemand) | 1620.27 | 0.0764482 | 6887.38ms | 409725 | 160 | 5.43832e+06 | 241160 | 0.0449991 | 3.15811 | 14.3423 | 2.38762 | 0.0104375 | 2.54897e-05 | 6.71182e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2639.36 | 0.110394 | 6361.71ms | 676745 | 40 | 2.91474e+06 | 244527 | 0.130249 | 1.91728 | 8.49114 | 1.55262 | 0.00648376 | 0.000494943 | 8.23796e-06 | 1(Win) | true |
| simdjson (ondemand) | 2320.34 | 0.0262188 | 7308.23ms | 676745 | 1280 | 6.80742e+06 | 278147 | 0.0418755 | 2.20784 | 9.7427 | 1.60045 | 0.00782886 | 0.00255256 | 4.99057e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2976.27 | 0.0466265 | 6266.15ms | 676745 | 320 | 3.27131e+06 | 216847 | 0.0261594 | 1.70382 | 7.871 | 1.40914 | 0.00523433 | 0.000308633 | 6.7603e-06 | 1(Win) | true |
| simdjson (ondemand) | 2538.89 | 0.040966 | 7218.8ms | 676745 | 640 | 6.94047e+06 | 254203 | 0.0340795 | 2.00996 | 9.12554 | 1.45642 | 0.0066555 | 0.001884 | 4.00123e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1858.61 | 0.0255471 | 7296.79ms | 264040 | 2560 | 3.06682e+06 | 135482 | 0.0110865 | 2.73317 | 10.3744 | 1.96003 | 0.00706331 | 0.000116483 | 9.77006e-06 | 1(Win) | true |
| simdjson (ondemand) | 1616.67 | 0.119046 | 8342.7ms | 264040 | 320 | 1.10022e+07 | 155758 | 0.12885 | 3.13895 | 11.2689 | 1.84299 | 0.0108214 | 0.00024208 | 1.29597e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2236.89 | 0.0714403 | 6825.19ms | 264040 | 320 | 2.06961e+06 | 112571 | 0.082455 | 2.27038 | 8.95182 | 1.63284 | 0.00578468 | 1.92442e-05 | 1.49125e-06 | 1(Win) | true |
| simdjson (ondemand) | 1818.99 | 0.0888541 | 8235.77ms | 264040 | 640 | 9.68313e+06 | 138433 | 0.00419331 | 2.7751 | 9.84533 | 1.51625 | 0.0122121 | 1.42497e-05 | 4.88207e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2364.53 | 0.0274019 | 7878.47ms | 360584 | 2560 | 4.06561e+06 | 145433 | 0.194173 | 2.15139 | 8.09409 | 1.44906 | 0.00517451 | 0.000172125 | 1.75074e-05 | 1(Win) | true |
| simdjson (ondemand) | 2129.78 | 0.0614295 | 8635.54ms | 360584 | 2560 | 2.51848e+07 | 161463 | 0.0327255 | 2.36997 | 8.60115 | 1.36611 | 0.00800169 | 0.000644486 | 1.60428e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2834.91 | 0.0266276 | 7350.87ms | 360584 | 2560 | 2.67079e+06 | 121302 | 0.339309 | 1.79657 | 7.04821 | 1.20876 | 0.00368194 | 1.26737e-05 | 3.04627e-06 | 1(Win) | true |
| simdjson (ondemand) | 2385.71 | 0.0513427 | 8557.19ms | 360584 | 2560 | 1.40208e+07 | 144141 | 0.182624 | 2.12988 | 7.56047 | 1.12743 | 0.00970522 | 5.06329e-05 | 6.40454e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 694.51 | 0.0400772 | 9445.27ms | 264040 | 1280 | 2.70264e+07 | 362570 | 0.133142 | 7.3778 | 28.4659 | 5.3042 | 0.0245361 | 0.00786881 | 5.78274e-05 | 1(Win) | true |
| simdjson (ondemand) | 280.461 | 0.143521 | 5706.31ms | 264040 | 160 | 2.6567e+08 | 897836 | 0.0444182 | 17.9673 | 72.701 | 12.7247 | 0.0883643 | 0.00156446 | 7.51307e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 752.891 | 0.0829156 | 9184.05ms | 264040 | 320 | 2.46092e+07 | 334455 | 0.0314098 | 6.80607 | 27.0427 | 4.97483 | 0.0205102 | 0.0015017 | 2.81207e-05 | 1(Win) | true |
| simdjson (ondemand) | 290.324 | 0.149989 | 5634.1ms | 264040 | 160 | 2.70776e+08 | 867334 | 0.323481 | 17.3758 | 71.272 | 12.3951 | 0.0834951 | 0.00012446 | 2.7458e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.969 | 0.152677 | 5023.23ms | 360584 | 80 | 2.77796e+07 | 385961 | 0.0758115 | 5.74143 | 21.7011 | 4.0771 | 0.0164052 | 0.00634894 | 1.5045e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.53 | 0.14956 | 5504.46ms | 360584 | 160 | 2.65132e+08 | 860710 | 0.0639078 | 12.6936 | 52.8829 | 9.1997 | 0.0529287 | 0.00281436 | 7.85878e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 956.494 | 0.051551 | 9776.9ms | 360584 | 640 | 2.19838e+07 | 359521 | 0.00874394 | 5.32378 | 20.6554 | 3.83491 | 0.0138616 | 0.00130421 | 1.7034e-05 | 1(Win) | true |
| simdjson (ondemand) | 411.173 | 0.364119 | 5431.71ms | 360584 | 30 | 2.78209e+08 | 836338 | 0.0960013 | 12.3076 | 51.8408 | 8.95972 | 0.0502329 | 7.4971e-05 | 1.06309e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7010.45 | 0.130175 | 4341.19ms | 264040 | 320 | 699605 | 35919 | 0.034006 | 0.722546 | 3.47659 | 0.478159 | 0.000943453 | 1.18353e-06 | 3.31389e-07 | 1(Win) | true |
| simdjson (ondemand) | 5921.03 | 0.054075 | 4984.27ms | 264040 | 640 | 338468 | 42527.8 | 0.0359784 | 0.853965 | 3.88683 | 0.43569 | 0.00115563 | 2.29605e-06 | 9.34991e-07 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7220.96 | 0.115361 | 4278.37ms | 264040 | 320 | 517864 | 34871.8 | 0.0215744 | 0.699111 | 3.39322 | 0.459385 | 0.000943619 | 2.87598e-06 | 8.28473e-07 | 1(Win) | true |
| simdjson (ondemand) | 6098.95 | 0.199604 | 4905.52ms | 264040 | 160 | 1.08665e+06 | 41287.1 | 0.105835 | 0.828942 | 3.80332 | 0.416939 | 0.00112537 | 1.96466e-06 | 6.86449e-07 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7948.44 | 0.0385646 | 5059.97ms | 360584 | 4890 | 1.36125e+06 | 43263.8 | 0.0428151 | 0.637748 | 3.00187 | 0.372818 | 0.000750559 | 1.45583e-06 | 5.66566e-07 | 1(Win) | true |
| simdjson (ondemand) | 7267.6 | 0.0320834 | 5467.98ms | 360584 | 2560 | 589972 | 47316.8 | 0.105969 | 0.695118 | 3.19736 | 0.335857 | 0.000805887 | 2.43095e-06 | 5.95822e-07 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8188.66 | 0.199948 | 4997.97ms | 360584 | 40 | 282020 | 41994.6 | 0.130405 | 0.62003 | 2.94082 | 0.35907 | 0.000713703 | 5.54656e-06 | 3.32793e-06 | 1(Win) | true |
| simdjson (ondemand) | 7492.1 | 0.0389456 | 5395.47ms | 360584 | 2560 | 818019 | 45899 | 0.0323466 | 0.677308 | 3.13621 | 0.322126 | 0.000791206 | 1.7918e-06 | 7.84318e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4833.51 | 0.0313738 | 5933.49ms | 264040 | 1280 | 341947 | 52096.4 | 0.0459079 | 1.05721 | 5.31884 | 0.86493 | 0.00169293 | 4.73413e-06 | 2.21617e-06 | 1(Win) | true |
| simdjson (ondemand) | 3941.6 | 0.0321897 | 7144.03ms | 264040 | 2560 | 1.0826e+06 | 63884.7 | 0.0390657 | 1.283 | 6.37915 | 0.936322 | 0.00254018 | 4.52405e-06 | 1.32704e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4966.03 | 0.0171677 | 5848.96ms | 264040 | 4890 | 370556 | 50706.1 | 0.062061 | 1.02695 | 5.23966 | 0.847497 | 0.00163716 | 3.0918e-06 | 9.65801e-07 | 1(Win) | true |
| simdjson (ondemand) | 4001.93 | 0.0733453 | 7095.15ms | 264040 | 640 | 1.3631e+06 | 62921.7 | 0.31556 | 1.26165 | 6.29984 | 0.918912 | 0.00248464 | 3.21329e-06 | 1.65103e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5816.37 | 0.0213155 | 6674.74ms | 360584 | 2560 | 406574 | 59122.7 | 0.0233527 | 0.881792 | 4.38275 | 0.665185 | 0.00142728 | 2.07346e-06 | 8.22234e-07 | 1(Win) | true |
| simdjson (ondemand) | 4966 | 0.0326285 | 7688.79ms | 360584 | 2560 | 1.30687e+06 | 69246.8 | 0.11557 | 1.01805 | 5.0342 | 0.704453 | 0.00188925 | 2.13196e-06 | 8.23317e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5923.74 | 0.0250025 | 6587.17ms | 360584 | 2560 | 539296 | 58051.1 | 0.165738 | 0.864932 | 4.32478 | 0.65242 | 0.00144112 | 3.17085e-06 | 1.32922e-06 | 1(Win) | true |
| simdjson (ondemand) | 5073.8 | 0.0985633 | 7615.75ms | 360584 | 80 | 356999 | 67775.6 | 0.112451 | 0.999326 | 4.9762 | 0.691724 | 0.00182579 | 1.14398e-06 | 2.77328e-07 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1878.46 | 0.0589881 | 851.348ms | 2632 | 2560 | 1590.51 | 1336.24 | 0.0845586 | 2.82742 | 11.1459 | 2.10372 | 0.000947177 | 0.000129714 | 5.47647e-05 | 1(Win) | true |
| simdjson (ondemand) | 1588.71 | 0.0508305 | 895.526ms | 2632 | 2560 | 1651.1 | 1579.95 | 0.0774706 | 3.33371 | 12.2511 | 2.13868 | 0.00404324 | 6.18885e-05 | 1.38025e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2416.69 | 0.0459026 | 829.005ms | 2632 | 4890 | 1111.51 | 1038.64 | 0.0879358 | 2.21332 | 9.13298 | 1.64058 | 0.000765473 | 4.56859e-05 | 7.53663e-06 | 1(Win) | true |
| simdjson (ondemand) | 1955.86 | 0.136668 | 867.206ms | 2632 | 320 | 984.412 | 1283.36 | 0.0316453 | 2.71792 | 10.3788 | 1.71163 | 0.0024423 | 5.69909e-05 | 3.56193e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.91 | 0.0758174 | 863.873ms | 3370 | 320 | 355.779 | 1390.74 | 0.050981 | 2.29443 | 9.01632 | 1.63056 | 0.000822515 | 3.52374e-05 | 9.273e-07 | 1(Win) | true |
| simdjson (ondemand) | 1997.78 | 0.0675251 | 895.774ms | 3370 | 320 | 377.611 | 1608.72 | 0.0976103 | 2.64318 | 9.77626 | 1.66884 | 0.00354043 | 6.30564e-05 | 1.02003e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2942.05 | 0.0351085 | 834.811ms | 3370 | 4890 | 719.269 | 1092.39 | 0.0111003 | 1.81553 | 7.52048 | 1.28427 | 0.00059602 | 3.29504e-05 | 3.70161e-06 | 1(Win) | true |
| simdjson (ondemand) | 2434.91 | 0.0587998 | 858.203ms | 3370 | 4890 | 2945.47 | 1319.92 | 0.0208947 | 2.17624 | 8.3905 | 1.35074 | 0.00195099 | 5.12764e-05 | 2.17849e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1271.12 | 0.114739 | 916.558ms | 2632 | 160 | 821.373 | 1974.69 | 0.0398638 | 4.13558 | 16.5657 | 3.24924 | 0.00457827 | 0.000113982 | 1.8997e-05 | 1(Win) | true |
| simdjson (ondemand) | 717.56 | 0.0713339 | 1071.6ms | 2632 | 160 | 996.248 | 3498.06 | 0.117345 | 7.26108 | 30.9586 | 5.91717 | 0.0127826 | 7.83625e-05 | 2.37462e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.57 | 0.099509 | 901.233ms | 2632 | 80 | 225.848 | 1688.5 | 0.0340655 | 3.55242 | 14.6489 | 2.80471 | 0.00457827 | 3.32447e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 781.929 | 0.0316503 | 1048.41ms | 2632 | 2560 | 2642.61 | 3210.1 | 0.00194702 | 6.66801 | 29.0847 | 5.48898 | 0.0116626 | 0.000136541 | 7.62847e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1490.22 | 0.0369021 | 935.489ms | 3370 | 4890 | 3097.18 | 2156.64 | 0.0294311 | 3.51854 | 13.657 | 2.65341 | 0.00449716 | 3.7623e-05 | 7.28186e-06 | 1(Win) | true |
| simdjson (ondemand) | 930.223 | 0.0338281 | 1063.56ms | 3370 | 640 | 874.219 | 3454.96 | 0.0466051 | 5.60307 | 24.0893 | 4.56706 | 0.00845095 | 4.59013e-05 | 9.273e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1752.65 | 0.0581916 | 912.037ms | 3370 | 1280 | 1457.46 | 1833.72 | 0.0583342 | 3.00365 | 12.1599 | 2.30623 | 0.00351748 | 4.47422e-05 | 1.11276e-05 | 1(Win) | true |
| simdjson (ondemand) | 1006.13 | 0.031314 | 1048.05ms | 3370 | 2560 | 2561.32 | 3194.29 | 0.00508695 | 5.18238 | 22.7018 | 4.24807 | 0.00869923 | 8.12546e-05 | 3.82511e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3188.58 | 0.167086 | 790.606ms | 2632 | 160 | 276.806 | 787.206 | 0.0627612 | 1.69835 | 6.87462 | 1.23708 | 0.000660144 | 2.37462e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2401.52 | 0.0536208 | 817.061ms | 2632 | 4890 | 1535.94 | 1045.2 | 0.216269 | 2.22937 | 8.21999 | 1.34385 | 0.00319203 | 5.01924e-05 | 5.28341e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3985.48 | 0.106201 | 778.989ms | 2632 | 1280 | 572.629 | 629.803 | 0.123703 | 1.37538 | 5.80775 | 0.984043 | 0.000773532 | 3.2651e-05 | 5.93655e-07 | 1(Win) | true |
| simdjson (ondemand) | 2991.61 | 0.0582327 | 796.906ms | 2632 | 640 | 152.783 | 839.036 | 0.0336955 | 1.80386 | 7.15312 | 1.09081 | 0.000760472 | 3.02764e-05 | 1.18731e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3743.88 | 0.135805 | 797.923ms | 3370 | 1280 | 1739.62 | 858.435 | 0.0244753 | 1.43718 | 5.77745 | 0.982197 | 0.00104228 | 3.77875e-05 | 1.62277e-06 | 1(Win) | true |
| simdjson (ondemand) | 3111.92 | 0.0690902 | 816.705ms | 3370 | 1280 | 651.697 | 1032.76 | 0.0610094 | 1.72031 | 6.49703 | 1.02641 | 0.00230295 | 1.62277e-05 | 9.273e-07 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4619.6 | 0.102288 | 784.859ms | 3370 | 320 | 162.051 | 695.706 | 0.016168 | 1.18049 | 4.94421 | 0.78457 | 0.00060089 | 6.30564e-05 | 1.29822e-05 | 1(Win) | true |
| simdjson (ondemand) | 3742.25 | 0.0626596 | 802.21ms | 3370 | 4890 | 1416.05 | 858.81 | 0.0814221 | 1.44008 | 5.6638 | 0.828784 | 0.0012094 | 3.11906e-05 | 4.06571e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2377.36 | 0.0480136 | 821.721ms | 2632 | 4890 | 1256.67 | 1055.82 | 0.191932 | 2.24744 | 9.46391 | 1.7747 | 0.00144975 | 6.92282e-05 | 1.82588e-05 | 1(Win) | true |
| simdjson (ondemand) | 2023.15 | 0.0721984 | 837.799ms | 2632 | 1280 | 1027.02 | 1240.67 | 0.00566697 | 2.62727 | 10.1246 | 1.70973 | 0.0047344 | 3.2651e-05 | 6.82703e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2843.9 | 0.0576186 | 808.122ms | 2632 | 1280 | 331.039 | 882.616 | 0.0361896 | 1.89392 | 8.40008 | 1.52432 | 0.0011413 | 4.83829e-05 | 5.93655e-07 | 1(Win) | true |
| simdjson (ondemand) | 2438.89 | 0.0427152 | 819.476ms | 2632 | 4890 | 945.064 | 1029.19 | 0.0125057 | 2.194 | 9.06079 | 1.45935 | 0.00114495 | 4.63852e-05 | 1.99682e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2830.69 | 0.0404774 | 826.873ms | 3370 | 4890 | 1032.78 | 1135.37 | 0.0406324 | 1.8831 | 7.87389 | 1.42018 | 0.001014 | 3.08872e-05 | 2.60933e-06 | 1(Win) | true |
| simdjson (ondemand) | 2598.7 | 0.0366962 | 836.153ms | 3370 | 2560 | 527.266 | 1236.73 | 0.0431011 | 2.04587 | 7.97507 | 1.31217 | 0.00288738 | 2.96736e-05 | 1.04321e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3322.05 | 0.0423687 | 813.37ms | 3370 | 640 | 107.527 | 967.439 | 0.0803344 | 1.61533 | 7.04303 | 1.22463 | 0.000890208 | 1.48368e-05 | 4.6365e-07 | 1(Win) | true |
| simdjson (ondemand) | 3088.04 | 0.0948415 | 820.364ms | 3370 | 160 | 155.887 | 1040.75 | 0.104601 | 1.73383 | 7.14421 | 1.11662 | 0.00104043 | 4.45104e-05 | 9.273e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 762 | 0.12393 | 1316.24ms | 4630 | 1280 | 66010.5 | 5794.64 | 0.16373 | 6.67317 | 32.2382 | 5.70446 | 0.00328817 | 9.61798e-05 | 5.41644e-05 | 1(Win) | true |
| Jsonifier (generic) | 723.512 | 0.0733727 | 1344.47ms | 4630 | 1280 | 25665.5 | 6102.89 | 0.0108439 | 7.02574 | 33.0283 | 6.3946 | 0.00335296 | 0.000103604 | 6.10826e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 907.613 | 0.049153 | 1312.07ms | 4630 | 4890 | 27962 | 4864.97 | 0.134908 | 5.60591 | 27.6091 | 4.62916 | 0.00160914 | 7.34076e-05 | 3.03878e-05 | 1(Win) | true |
| Jsonifier (generic) | 865.142 | 0.066854 | 1333.95ms | 4630 | 4890 | 56931.2 | 5103.8 | 0.0632118 | 5.90364 | 28.3559 | 5.30367 | 0.00207675 | 8.3213e-05 | 3.78964e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1776.9 | 0.166617 | 1352.07ms | 11579 | 320 | 34308.9 | 6214.52 | 0.107021 | 2.83242 | 13.6667 | 2.32568 | 0.00148329 | 5.07384e-05 | 3.10368e-05 | 1(Win) | true |
| Jsonifier (generic) | 1738.83 | 0.0945105 | 1373.03ms | 11579 | 320 | 11527.6 | 6350.61 | 0.066878 | 2.93123 | 13.9775 | 2.60014 | 0.00132541 | 1.18749e-05 | 1.61931e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2148.51 | 0.064062 | 1342.21ms | 11579 | 2560 | 27753 | 5139.65 | 0.254081 | 2.36792 | 11.7488 | 1.87944 | 0.000746232 | 5.72494e-05 | 2.97886e-05 | 1(Win) | true |
| Jsonifier (generic) | 1995.64 | 0.116459 | 1376.84ms | 11579 | 40 | 1661.05 | 5533.35 | 0.154757 | 2.55383 | 12.1181 | 2.16487 | 0.000995336 | 1.51136e-05 | 0 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 714.34 | 0.082946 | 1352.81ms | 4630 | 160 | 4205.93 | 6181.24 | 0.0583078 | 7.26173 | 36.4246 | 6.66436 | 0.00604887 | 2.42981e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 680.584 | 0.0545424 | 1371.83ms | 4630 | 2560 | 32055.8 | 6487.82 | 0.0239087 | 7.49918 | 36.322 | 7.10238 | 0.00393063 | 5.32364e-05 | 1.88985e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 797.593 | 0.101343 | 1369.77ms | 4630 | 40 | 1259.07 | 5536.05 | 0.133191 | 6.38644 | 31.6432 | 5.98877 | 0.00230562 | 1.61987e-05 | 5.39957e-06 | 1(Win) | true |
| simdjson (ondemand) | 789.979 | 0.236095 | 1384.75ms | 4630 | 160 | 27862.8 | 5589.41 | 0.0432926 | 6.42984 | 32.1689 | 5.62916 | 0.00218143 | 3.64471e-05 | 1.34989e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1626.4 | 0.0302538 | 1420.17ms | 11579 | 4890 | 20632.7 | 6789.59 | 0.159852 | 3.11828 | 15.4168 | 2.71267 | 0.00156893 | 4.80385e-05 | 2.39133e-05 | 1(Win) | true |
| Jsonifier (generic) | 1612.74 | 0.0688166 | 1422.37ms | 11579 | 640 | 14209.4 | 6847.08 | 0.0476481 | 3.14614 | 15.2958 | 2.87546 | 0.00163793 | 2.88777e-05 | 1.4169e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1909.81 | 0.0479472 | 1411.31ms | 11579 | 2560 | 19675.6 | 5782.04 | 0.0400326 | 2.66335 | 13.5323 | 2.2742 | 0.000666346 | 2.62463e-05 | 1.02556e-05 | 1(Win) | true |
| Jsonifier (generic) | 1871.44 | 0.0446296 | 1422.33ms | 11579 | 2560 | 17753.1 | 5900.58 | 0.0541033 | 2.71818 | 13.3974 | 2.43199 | 0.000979987 | 4.89504e-05 | 2.72247e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7510.91 | 0.118665 | 770.323ms | 4630 | 2560 | 1245.83 | 587.88 | 0.566616 | 0.731142 | 3.63391 | 0.469979 | 0.000435171 | 1.82235e-05 | 3.20599e-06 | 1(Win) | true |
| simdjson (ondemand) | 6600.23 | 0.0306619 | 776.367ms | 4630 | 4890 | 205.755 | 668.993 | 0.381041 | 0.827528 | 4.09914 | 0.490497 | 0.000432142 | 1.44872e-05 | 1.45755e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7778.43 | 0.109094 | 767.264ms | 4630 | 640 | 245.448 | 567.661 | 0.0129385 | 0.716695 | 3.59698 | 0.461987 | 0.000431965 | 2.83477e-05 | 1.51863e-05 | 1(Win) | true |
| simdjson (ondemand) | 6854.22 | 0.106517 | 773.782ms | 4630 | 1280 | 602.691 | 644.203 | 0.0138271 | 0.80881 | 4.0622 | 0.482506 | 0.000432472 | 2.59854e-05 | 9.28051e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12609.3 | 0.0685112 | 799.573ms | 11579 | 160 | 57.5975 | 875.75 | 0.139685 | 0.427326 | 2.10459 | 0.210899 | 0.000172726 | 1.07954e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11083.5 | 0.0982576 | 810.07ms | 11579 | 160 | 153.336 | 996.312 | 0.0238322 | 0.483755 | 2.36696 | 0.231108 | 0.000179204 | 1.72726e-05 | 3.23862e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12889.9 | 0.0290108 | 799.051ms | 11579 | 1280 | 79.0624 | 856.684 | 0.0166914 | 0.420178 | 2.08982 | 0.207704 | 0.000172726 | 9.10862e-06 | 1.21448e-06 | 1(Win) | true |
| simdjson (ondemand) | 11243.6 | 0.0714508 | 809.272ms | 11579 | 160 | 78.7893 | 982.125 | 0.129989 | 0.477215 | 2.35219 | 0.227913 | 0.000172726 | 4.31816e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5386.73 | 0.0786317 | 795.67ms | 4630 | 4890 | 2031.5 | 819.702 | 0.358844 | 1.00203 | 5.15276 | 0.805195 | 0.000649052 | 1.49289e-05 | 1.01587e-06 | 1(Win) | true |
| simdjson (ondemand) | 5121.66 | 0.085585 | 797.443ms | 4630 | 80 | 43.5538 | 862.125 | 0 | 1.07105 | 5.58445 | 0.817495 | 0.000647948 | 5.39957e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5435.82 | 0.0801743 | 791.628ms | 4630 | 4890 | 2074.01 | 812.3 | 0.288588 | 0.993907 | 5.11577 | 0.797192 | 0.000648169 | 1.77998e-05 | 7.24359e-06 | 1(Win) | true |
| simdjson (ondemand) | 5096.07 | 0.0325026 | 797.578ms | 4630 | 640 | 50.7585 | 866.455 | 0.0405584 | 1.05682 | 5.54752 | 0.809503 | 0.000647948 | 5.39957e-06 | 1.68737e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10327.7 | 0.0898519 | 816.653ms | 11579 | 1280 | 1181.41 | 1069.22 | 0.0280656 | 0.517265 | 2.71137 | 0.345367 | 0.000259562 | 8.7038e-06 | 1.34943e-07 | 1(Win) | true |
| simdjson (ondemand) | 9163.67 | 0.0364372 | 831.372ms | 11579 | 640 | 123.388 | 1205.04 | 0.00648276 | 0.581034 | 2.96088 | 0.361862 | 0.000264892 | 2.83379e-06 | 1.34943e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10486.4 | 0.0544292 | 817.795ms | 11579 | 4890 | 1606.43 | 1053.04 | 0.0633396 | 0.510157 | 2.69661 | 0.342171 | 0.00025962 | 1.35815e-05 | 2.43724e-06 | 1(Win) | true |
| simdjson (ondemand) | 9272.66 | 0.0819859 | 831.966ms | 11579 | 640 | 610.086 | 1190.88 | 0.0749747 | 0.574312 | 2.94611 | 0.358667 | 0.000259899 | 2.96874e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.59 | 0.0303811 | 1147.23ms | 5092 | 4890 | 7942.99 | 4195.02 | 0.19604 | 4.42712 | 18.4292 | 3.50823 | 0.00333793 | 6.81931e-05 | 2.68274e-05 | 1(Win) | true |
| simdjson (ondemand) | 1133.26 | 0.0418142 | 1158.86ms | 5092 | 1280 | 4109.35 | 4285.07 | 0.0904207 | 4.51789 | 18.3979 | 3.07994 | 0.00275325 | 3.57485e-05 | 8.59191e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1306.94 | 0.0530932 | 1137.38ms | 5092 | 1280 | 4981.41 | 3715.62 | 0.0334637 | 3.98422 | 16.7756 | 3.10207 | 0.00318944 | 3.37539e-05 | 5.83022e-06 | 1(Win) | true |
| simdjson (ondemand) | 1284.03 | 0.0589156 | 1135.46ms | 5092 | 640 | 3177.38 | 3781.94 | 0.135738 | 4.0556 | 17.0927 | 2.74764 | 0.00220352 | 2.36277e-05 | 9.20562e-07 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2046 | 0.0790437 | 1194.63ms | 9739 | 160 | 2060.03 | 4539.51 | 0.0316764 | 2.4938 | 10.2014 | 1.63833 | 0.00182706 | 8.34275e-06 | 2.567e-06 | 1(Win) | true |
| Jsonifier (generic) | 2024.33 | 0.117065 | 1197.4ms | 9739 | 320 | 9231.45 | 4588.11 | 0.0876499 | 2.51747 | 10.3433 | 1.86332 | 0.00185305 | 1.50811e-05 | 1.60437e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2275.12 | 0.088668 | 1186.17ms | 9739 | 640 | 8385.56 | 4082.34 | 0.012629 | 2.24407 | 9.56347 | 1.66958 | 0.00131527 | 3.04831e-05 | 1.12306e-05 | 1(Win) | true |
| simdjson (ondemand) | 2264.53 | 0.0408569 | 1178.7ms | 9739 | 4890 | 13731.3 | 4101.44 | 0.0949151 | 2.24784 | 9.50539 | 1.46274 | 0.00193122 | 4.34447e-05 | 2.34127e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.706 | 0.0419321 | 1430.36ms | 5092 | 2560 | 22314.2 | 7040.84 | 0.0424463 | 7.51466 | 32.5171 | 6.61361 | 0.00700893 | 0.000123739 | 6.49763e-05 | 1(Win) | true |
| simdjson (ondemand) | 449.415 | 0.0629382 | 1804.05ms | 5092 | 160 | 7399.96 | 10805.4 | 0.0251095 | 11.5046 | 56.1387 | 10.9487 | 0.0138133 | 3.06854e-05 | 2.45483e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.273 | 0.0902962 | 1418.98ms | 5092 | 80 | 2754.53 | 6498.44 | 0.0221158 | 6.93922 | 30.648 | 6.1764 | 0.00698399 | 7.36449e-05 | 3.43676e-05 | 1(Win) | true |
| simdjson (ondemand) | 472.009 | 0.016391 | 1791.73ms | 5092 | 4890 | 13905.8 | 10288.2 | 0.0595042 | 10.9487 | 54.4812 | 10.5491 | 0.013418 | 4.87151e-05 | 9.4378e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1189.78 | 0.0259996 | 1505.14ms | 9739 | 2560 | 10545.5 | 7806.34 | 0.0248384 | 4.35461 | 18.2056 | 3.58475 | 0.00331235 | 3.66599e-05 | 1.42789e-05 | 1(Win) | true |
| simdjson (ondemand) | 846.194 | 0.0316818 | 1818.14ms | 9739 | 1280 | 15478.2 | 10976 | 0.00467661 | 6.11153 | 29.7888 | 5.72379 | 0.0070436 | 2.18997e-05 | 3.77028e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1274.31 | 0.0178234 | 1492.91ms | 9739 | 4890 | 8252.1 | 7288.5 | 0.0049833 | 4.06446 | 17.1969 | 3.34764 | 0.00370765 | 2.30767e-05 | 4.36757e-06 | 1(Win) | true |
| simdjson (ondemand) | 891.323 | 0.0322948 | 1805.13ms | 9739 | 1280 | 14495.5 | 10420.3 | 0.0618602 | 5.79981 | 28.9591 | 5.52192 | 0.00643346 | 3.03227e-05 | 1.05889e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4755.91 | 0.0782931 | 816.444ms | 5092 | 160 | 102.253 | 1021.07 | 0.0483796 | 1.12646 | 4.97604 | 0.690888 | 0.00106785 | 2.70031e-05 | 1.22742e-06 | 1(Win) | true |
| simdjson (ondemand) | 4415.62 | 0.0395264 | 822.216ms | 5092 | 2560 | 483.736 | 1099.76 | 0.030236 | 1.20806 | 5.29271 | 0.663216 | 0.000799048 | 1.68003e-05 | 2.07126e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4936.61 | 0.0378802 | 813.186ms | 5092 | 640 | 88.8638 | 983.694 | 0.0136621 | 1.08608 | 4.8533 | 0.664768 | 0.000794445 | 1.56495e-05 | 6.13708e-07 | 1(Win) | true |
| simdjson (ondemand) | 4561.82 | 0.055769 | 819.93ms | 5092 | 2560 | 902.25 | 1064.51 | 0.0458166 | 1.17151 | 5.17046 | 0.637667 | 0.00083027 | 2.61593e-05 | 7.74806e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7831.72 | 0.058654 | 833.219ms | 9739 | 160 | 77.4157 | 1185.92 | 0.0410903 | 0.681198 | 3.2068 | 0.390492 | 0.000576933 | 2.567e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7071.26 | 0.0388231 | 843.167ms | 9739 | 2560 | 665.665 | 1313.46 | 0.0682367 | 0.751251 | 3.34665 | 0.373344 | 0.000612309 | 9.0246e-06 | 1.52416e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8000.47 | 0.0454088 | 828.975ms | 9739 | 4890 | 1358.9 | 1160.91 | 0.276668 | 0.667262 | 3.14262 | 0.376836 | 0.000660784 | 1.54125e-05 | 4.49356e-06 | 1(Win) | true |
| simdjson (ondemand) | 7270.3 | 0.0274844 | 841.67ms | 9739 | 2560 | 315.6 | 1277.5 | 0.0899689 | 0.730853 | 3.28278 | 0.359996 | 0.000833873 | 1.28751e-05 | 2.04558e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3096.13 | 0.0582598 | 872.676ms | 5092 | 320 | 267.195 | 1568.45 | 0.0209248 | 1.70722 | 7.92812 | 1.37667 | 0.00224924 | 2.14798e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3010.82 | 0.0597315 | 876.195ms | 5092 | 160 | 148.503 | 1612.89 | 0.0589353 | 1.75343 | 8.32934 | 1.30597 | 0.00241433 | 7.36449e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3138.59 | 0.0166905 | 869.764ms | 5092 | 2560 | 170.721 | 1547.23 | 0.0691284 | 1.68396 | 7.80538 | 1.35055 | 0.00224932 | 1.90249e-05 | 2.3014e-07 | 1(Win) | true |
| simdjson (ondemand) | 3131.82 | 0.0297592 | 870.619ms | 5092 | 1280 | 272.542 | 1550.57 | 0.0119901 | 1.68814 | 8.20719 | 1.28044 | 0.00213202 | 1.59564e-05 | 1.6877e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5118.5 | 0.05474 | 910.226ms | 9739 | 4890 | 4824.61 | 1814.56 | 0.0783191 | 1.00977 | 4.93675 | 0.710237 | 0.000943081 | 2.27618e-05 | 8.79814e-06 | 1(Win) | true |
| Jsonifier (generic) | 4864.91 | 0.051164 | 919.418ms | 9739 | 2560 | 2442.57 | 1909.15 | 0.0294343 | 1.05987 | 4.80594 | 0.756135 | 0.00125498 | 1.21932e-05 | 2.92798e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5178.63 | 0.0717338 | 908.09ms | 9739 | 160 | 264.83 | 1793.49 | 0.0896401 | 0.999593 | 4.87288 | 0.696889 | 0.00111087 | 3.20875e-06 | 1.92525e-06 | 1(Win) | true |
| Jsonifier (generic) | 5003.77 | 0.0972723 | 910.732ms | 9739 | 30 | 97.7989 | 1856.17 | 0.102466 | 1.03292 | 4.74176 | 0.742479 | 0.00128008 | 1.0268e-05 | 0 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1422.84 | 0.0304393 | 1045.56ms | 4857 | 2560 | 2513.8 | 3255.45 | 0.0166695 | 3.66533 | 14.6448 | 2.87729 | 0.000736614 | 5.38849e-05 | 1.46374e-05 | 1(Win) | true |
| simdjson (ondemand) | 1343.24 | 0.0379068 | 1065.83ms | 4857 | 640 | 1093.57 | 3448.38 | 0.0276321 | 3.88095 | 15.4894 | 2.61519 | 0.000481586 | 2.67012e-05 | 9.65102e-07 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1826.51 | 0.0360992 | 998.524ms | 4857 | 2560 | 2145.5 | 2535.98 | 0.000292662 | 2.86665 | 11.624 | 2.21701 | 0.00216303 | 4.44751e-05 | 6.19274e-06 | 1(Win) | true |
| simdjson (ondemand) | 1650.89 | 0.0509949 | 1022.46ms | 4857 | 320 | 655.097 | 2805.76 | 0.0202667 | 3.16596 | 13.1493 | 2.1085 | 0.0010333 | 6.36967e-05 | 1.2868e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1856.99 | 0.225805 | 1064.47ms | 6701 | 30 | 1811.55 | 3441.37 | 0.017438 | 2.81681 | 11.1388 | 2.09327 | 0.00096503 | 6.96413e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1795.57 | 0.128849 | 1076.09ms | 6701 | 320 | 6729.61 | 3559.08 | 0.0793496 | 2.89893 | 11.5998 | 1.91076 | 0.000741494 | 4.10387e-05 | 1.95866e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2385.4 | 0.060507 | 1015.79ms | 6701 | 320 | 840.851 | 2679.04 | 0.0505989 | 2.19722 | 8.92941 | 1.61066 | 0.00185047 | 4.10387e-05 | 6.99522e-06 | 1(Win) | true |
| simdjson (ondemand) | 2184.84 | 0.0331178 | 1033.72ms | 6701 | 2560 | 2402.16 | 2924.96 | 0.0472185 | 2.38944 | 9.90524 | 1.5438 | 0.00137223 | 2.79226e-05 | 6.23741e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 722.201 | 0.0442261 | 1363.43ms | 4857 | 640 | 5149.4 | 6413.72 | 0.0466312 | 7.17608 | 31.1437 | 6.15483 | 0.00629407 | 4.37513e-05 | 8.04252e-06 | 1(Win) | true |
| simdjson (ondemand) | 229.152 | 0.0136427 | 2745.91ms | 4857 | 4890 | 37187.4 | 20213.6 | 0.0192868 | 22.5127 | 115.762 | 22.3167 | 0.0437075 | 0.00011267 | 3.67147e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 832.778 | 0.0548117 | 1302.37ms | 4857 | 640 | 5948.46 | 5562.1 | 0.046345 | 6.22951 | 28.0752 | 5.48672 | 0.00585495 | 2.41275e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 236.137 | 0.0410038 | 2711.38ms | 4857 | 640 | 41403.6 | 19615.7 | 0.0230151 | 21.8444 | 113.469 | 21.8231 | 0.0449647 | 4.95419e-05 | 3.21701e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 903.988 | 0.0535394 | 1432ms | 6701 | 640 | 9168.12 | 7069.31 | 0.032414 | 5.73259 | 23.6257 | 4.73347 | 0.00554348 | 2.37838e-05 | 2.56492e-06 | 1(Win) | true |
| simdjson (ondemand) | 314.846 | 0.0313846 | 2750.64ms | 6701 | 1280 | 51943 | 20297.5 | 0.00864561 | 16.3583 | 83.9096 | 16.1249 | 0.0329071 | 5.26974e-05 | 1.4107e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1027.83 | 0.0415425 | 1369.91ms | 6701 | 1280 | 8539.42 | 6217.51 | 0.0296579 | 5.04158 | 21.4205 | 4.25444 | 0.00507002 | 2.59989e-05 | 6.06253e-06 | 1(Win) | true |
| simdjson (ondemand) | 326.925 | 0.0451011 | 2708.82ms | 6701 | 160 | 12435.9 | 19547.5 | 0.00671395 | 15.7924 | 82.2855 | 15.7747 | 0.0320325 | 3.54425e-05 | 3.73079e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4000.57 | 0.0321886 | 830.697ms | 4857 | 1280 | 177.79 | 1157.83 | 0.11112 | 1.33283 | 5.5456 | 0.890056 | 0.000307707 | 2.20365e-05 | 2.09105e-06 | 1(Win) | true |
| simdjson (ondemand) | 3603.96 | 0.0557733 | 842.828ms | 4857 | 640 | 328.858 | 1285.25 | 0.0538272 | 1.47384 | 6.01462 | 0.829319 | 0.00035194 | 1.80152e-05 | 4.82551e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4704.81 | 0.096698 | 817.642ms | 4857 | 640 | 580.053 | 984.523 | 0.12063 | 1.13933 | 4.95882 | 0.756434 | 0.000621526 | 1.57633e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4070.63 | 0.0872462 | 833.52ms | 4857 | 320 | 315.396 | 1137.91 | 0.0379129 | 1.3107 | 5.4441 | 0.700432 | 0.00062796 | 1.15812e-05 | 1.2868e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4973.66 | 0.103309 | 843.656ms | 6701 | 640 | 1127.68 | 1284.88 | 0.0923845 | 1.06782 | 4.51157 | 0.672885 | 0.000160191 | 1.6089e-05 | 2.33174e-07 | 1(Win) | true |
| simdjson (ondemand) | 4635.8 | 0.0799603 | 853.983ms | 6701 | 320 | 388.802 | 1378.53 | 0.00272022 | 1.14388 | 4.73616 | 0.618117 | 0.000283073 | 1.81876e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5609.18 | 0.0782096 | 835.396ms | 6701 | 320 | 254.069 | 1139.31 | 0.236426 | 0.951321 | 4.08626 | 0.576033 | 0.000760614 | 2.09857e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5218.03 | 0.0350959 | 842.589ms | 6701 | 4890 | 903.414 | 1224.71 | 0.0899751 | 1.02123 | 4.32264 | 0.524698 | 0.000529604 | 1.65406e-05 | 1.80054e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2993.75 | 0.046705 | 871.528ms | 4857 | 2560 | 1336.82 | 1547.22 | 0.0474668 | 1.76625 | 7.53675 | 1.3218 | 0.000657476 | 4.22232e-05 | 1.2305e-05 | 1(Win) | true |
| simdjson (ondemand) | 2116.14 | 0.0396425 | 934.922ms | 4857 | 4890 | 3681.96 | 2188.89 | 0.163568 | 2.48187 | 10.6601 | 1.64896 | 0.00206065 | 4.32829e-05 | 1.73047e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3312.16 | 0.100108 | 861.043ms | 4857 | 160 | 313.597 | 1398.48 | 0.0576186 | 1.60118 | 6.96644 | 1.19518 | 0.00138717 | 1.2868e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2255.64 | 0.0519449 | 925.675ms | 4857 | 1280 | 1456.44 | 2053.52 | 0.086893 | 2.32808 | 10.1069 | 1.5279 | 0.00318033 | 1.44765e-05 | 3.37786e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3793.3 | 0.0252094 | 886.546ms | 6701 | 4890 | 882.024 | 1684.7 | 0.024606 | 1.39176 | 6.08685 | 1.01224 | 0.000405397 | 1.92872e-05 | 1.06812e-06 | 1(Win) | true |
| simdjson (ondemand) | 2849.47 | 0.0773607 | 938.782ms | 6701 | 1280 | 3853.02 | 2242.72 | 0.0136882 | 1.83945 | 8.02015 | 1.19713 | 0.0012687 | 2.89136e-05 | 7.69475e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4151.7 | 0.0343498 | 876.99ms | 6701 | 640 | 178.918 | 1539.27 | 0.02579 | 1.27361 | 5.67348 | 0.92046 | 0.000875569 | 1.44568e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3014.37 | 0.0641748 | 931.532ms | 6701 | 1280 | 2369.33 | 2120.03 | 0.00641245 | 1.73973 | 7.61916 | 1.10939 | 0.00234573 | 1.09592e-05 | 9.32697e-07 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1308.64 | 0.0466254 | 841.467ms | 1691 | 1280 | 422.572 | 1232.32 | 0.0157833 | 4.06547 | 14.7363 | 2.89769 | 0.000593676 | 0.000103027 | 1.15501e-05 | 1(Win) | true |
| simdjson (ondemand) | 1191.53 | 0.0396911 | 853.252ms | 1691 | 4890 | 1411.16 | 1353.44 | 0.0879412 | 4.45055 | 16.8102 | 2.90893 | 0.000633088 | 9.56586e-05 | 5.68389e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.54 | 0.063288 | 835.487ms | 1691 | 320 | 150.843 | 1084.84 | 0.133194 | 3.59703 | 13.1638 | 2.50917 | 0.00118273 | 0.000109033 | 3.69604e-06 | 1(Win) | true |
| simdjson (ondemand) | 1352.55 | 0.047101 | 845.77ms | 1691 | 4890 | 1542.23 | 1192.31 | 0.111045 | 3.93667 | 15.1892 | 2.51035 | 0.000597534 | 0.000132543 | 3.54336e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1536.8 | 0.0381747 | 852.61ms | 2158 | 2560 | 669.048 | 1339.16 | 0.0713408 | 3.45288 | 12.2275 | 2.3633 | 0.000467374 | 7.36721e-05 | 7.60253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1490.65 | 0.0346303 | 856.315ms | 2158 | 4890 | 1117.82 | 1380.62 | 0.0443022 | 3.5577 | 13.4194 | 2.29611 | 0.000479597 | 9.31522e-05 | 1.89526e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1726.53 | 0.0911587 | 846.015ms | 2158 | 640 | 755.668 | 1192 | 0.196747 | 3.08448 | 11.0765 | 2.07507 | 0.000469184 | 5.21316e-05 | 2.17215e-06 | 1(Win) | true |
| simdjson (ondemand) | 1692.55 | 0.0295785 | 848.433ms | 2158 | 4890 | 632.529 | 1215.93 | 0.0288312 | 3.14859 | 12.1492 | 1.98378 | 0.000593502 | 6.43442e-05 | 6.91771e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 932.843 | 0.0410763 | 891.81ms | 1691 | 640 | 322.726 | 1728.76 | 0.0773077 | 5.65331 | 20.4944 | 4.12951 | 0.00184432 | 7.85408e-05 | 1.84802e-06 | 1(Win) | true |
| simdjson (ondemand) | 673.213 | 0.0672586 | 955.516ms | 1691 | 640 | 1661.34 | 2395.47 | 0.146977 | 7.77984 | 30.181 | 5.40154 | 0.00565863 | 6.65287e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1063.79 | 0.0894879 | 878.483ms | 1691 | 1280 | 2355.65 | 1515.95 | 0.0567081 | 4.98116 | 18.9468 | 3.74453 | 0.00177918 | 6.00606e-05 | 4.62005e-07 | 1(Win) | true |
| simdjson (ondemand) | 734.251 | 0.134907 | 947.434ms | 1691 | 80 | 702.353 | 2196.34 | 0.0608598 | 7.14511 | 28.56 | 5.00177 | 0.00441307 | 0.000103489 | 4.43525e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1068.58 | 0.0262091 | 910.627ms | 2158 | 4890 | 1245.94 | 1925.94 | 0.000833323 | 4.92059 | 17.2706 | 3.49537 | 0.00289473 | 9.30575e-05 | 1.6394e-05 | 1(Win) | true |
| simdjson (ondemand) | 865.697 | 0.0534758 | 956.337ms | 2158 | 1280 | 2068.7 | 2377.31 | 0.0397153 | 6.0504 | 23.766 | 4.22475 | 0.00275392 | 7.2043e-05 | 1.4843e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1169.61 | 0.0460701 | 902.226ms | 2158 | 320 | 210.286 | 1759.59 | 0.0122528 | 4.50665 | 16.1196 | 3.20621 | 0.00296426 | 8.6886e-05 | 1.15848e-05 | 1(Win) | true |
| simdjson (ondemand) | 932.391 | 0.110541 | 951.065ms | 2158 | 640 | 3810.06 | 2207.26 | 0.0297403 | 5.62186 | 22.4958 | 3.91149 | 0.00332991 | 5.28557e-05 | 3.62025e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4473.48 | 0.176233 | 748.186ms | 1691 | 160 | 64.5786 | 360.494 | 0.0364217 | 1.27646 | 4.57363 | 0.735068 | 0.000798344 | 2.58723e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4100.47 | 0.147985 | 751.142ms | 1691 | 320 | 108.394 | 393.288 | 0.272592 | 1.4047 | 5.1029 | 0.71437 | 0.00118273 | 7.02247e-05 | 9.24009e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4985.28 | 0.146327 | 745.648ms | 1691 | 2560 | 573.586 | 323.485 | 0.11314 | 1.16129 | 4.22413 | 0.656417 | 0.000806891 | 3.74224e-05 | 6.00606e-06 | 1(Win) | true |
| simdjson (ondemand) | 4493.63 | 0.210053 | 743.803ms | 1691 | 1280 | 727.374 | 358.877 | 0.0612091 | 1.28819 | 4.75458 | 0.636902 | 0.0011795 | 7.29967e-05 | 2.31002e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5249.07 | 0.141635 | 747.844ms | 2158 | 160 | 49.3403 | 392.075 | 0.0669067 | 1.10124 | 3.98424 | 0.592678 | 0.000706673 | 5.7924e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4931.3 | 0.0689836 | 749.993ms | 2158 | 1280 | 106.092 | 417.34 | 0.263706 | 1.15824 | 4.23726 | 0.568582 | 0.000922802 | 4.01848e-05 | 1.15848e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5717.46 | 0.110365 | 745.736ms | 2158 | 4890 | 771.741 | 359.955 | 0.147134 | 1.00648 | 3.71038 | 0.531048 | 0.000840739 | 3.23142e-05 | 1.42145e-06 | 1(Win) | true |
| simdjson (ondemand) | 5474.48 | 0.162853 | 745.644ms | 2158 | 320 | 119.939 | 375.931 | 0.0349011 | 1.05647 | 3.96437 | 0.507888 | 0.00092244 | 2.8962e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3162.64 | 0.0488806 | 761.52ms | 1691 | 4890 | 303.788 | 509.911 | 0.2441 | 1.76479 | 6.86339 | 1.21644 | 0.00156295 | 5.49039e-05 | 2.41868e-06 | 1(Win) | true |
| simdjson (ondemand) | 2557.4 | 0.0603618 | 772.334ms | 1691 | 4890 | 708.471 | 630.587 | 0.390071 | 2.14209 | 8.66292 | 1.43111 | 0.00107812 | 9.75935e-05 | 3.53127e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3440.28 | 0.054549 | 759.805ms | 1691 | 2560 | 167.384 | 468.76 | 0.203 | 1.62659 | 6.51391 | 1.13779 | 0.00127305 | 3.04923e-05 | 1.84802e-06 | 1(Win) | true |
| simdjson (ondemand) | 2633.5 | 0.0548655 | 772.96ms | 1691 | 4890 | 551.985 | 612.364 | 0.278055 | 2.08247 | 8.31461 | 1.35364 | 0.00258387 | 3.51917e-05 | 2.90241e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3656.63 | 0.0601088 | 766.738ms | 2158 | 2560 | 292.993 | 562.821 | 0.153703 | 1.50552 | 5.79564 | 0.988415 | 0.000656894 | 2.8238e-05 | 5.43038e-06 | 1(Win) | true |
| simdjson (ondemand) | 3189.47 | 0.117362 | 776.074ms | 2158 | 2560 | 1468.11 | 645.258 | 0.110968 | 1.72896 | 7.02688 | 1.13021 | 0.000935835 | 5.01405e-05 | 1.97304e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3879.23 | 0.0754105 | 765.022ms | 2158 | 1280 | 204.873 | 530.525 | 0.0800452 | 1.44076 | 5.52178 | 0.926784 | 0.000888047 | 3.22202e-05 | 1.30329e-05 | 1(Win) | true |
| simdjson (ondemand) | 3254.25 | 0.187308 | 774.441ms | 2158 | 160 | 224.508 | 632.413 | 0.0197617 | 1.68394 | 6.75394 | 1.06951 | 0.00168269 | 1.73772e-05 | 1.15848e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1302.84 | 0.0453781 | 1040.64ms | 4390 | 1280 | 2721.78 | 3213.47 | 0.0318828 | 4.00204 | 18.0189 | 3.50228 | 0.00251904 | 5.44562e-05 | 1.61945e-05 | 1(Win) | true |
| simdjson (ondemand) | 1044.97 | 0.0221148 | 1117.89ms | 4390 | 4890 | 3838.8 | 4006.45 | 0.0196257 | 4.97757 | 20.6995 | 3.58132 | 0.00438219 | 5.47349e-05 | 1.23911e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.72 | 0.0232355 | 1043.48ms | 4390 | 4890 | 2223.2 | 2901.9 | 0.0294609 | 3.61941 | 16.5267 | 3.17084 | 0.00215614 | 4.48593e-05 | 8.05884e-06 | 1(Win) | true |
| simdjson (ondemand) | 1146.24 | 0.0532558 | 1104ms | 4390 | 640 | 2421.53 | 3652.48 | 0.00149729 | 4.54317 | 19.1497 | 3.2385 | 0.00419704 | 2.88297e-05 | 2.13554e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2426.43 | 0.0222514 | 1088.19ms | 9378 | 4890 | 3289.32 | 3685.89 | 0.0188035 | 2.1454 | 9.36255 | 1.69727 | 0.00127394 | 2.41831e-05 | 5.95311e-06 | 1(Win) | true |
| simdjson (ondemand) | 2137.57 | 0.0246728 | 1136.89ms | 9378 | 4890 | 5211.06 | 4183.98 | 0.0206983 | 2.43455 | 10.3172 | 1.70687 | 0.00167289 | 2.42267e-05 | 5.49517e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2684.78 | 0.0240936 | 1072.66ms | 9378 | 4890 | 3150.03 | 3331.21 | 0.0853889 | 1.9412 | 8.63702 | 1.53679 | 0.00149667 | 2.17626e-05 | 5.38614e-06 | 1(Win) | true |
| simdjson (ondemand) | 2333.07 | 0.0720918 | 1135.02ms | 9378 | 160 | 1221.96 | 3833.39 | 0.0485627 | 2.2321 | 9.5917 | 1.54639 | 0.00159949 | 2.46588e-05 | 2.66581e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 768.565 | 0.0914145 | 1263.43ms | 4390 | 160 | 3967.51 | 5447.33 | 0.0393696 | 6.75036 | 29.8093 | 5.97062 | 0.01124 | 5.69476e-05 | 1.42369e-06 | 1(Win) | true |
| simdjson (ondemand) | 693.127 | 0.0377835 | 1326.27ms | 4390 | 1280 | 6666.8 | 6040.21 | 0.0467093 | 7.47785 | 33.349 | 6.12506 | 0.00877794 | 0.000100014 | 3.34567e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 828.204 | 0.0551147 | 1249.15ms | 4390 | 1280 | 9935.73 | 5055.07 | 0.0736962 | 6.26349 | 28.2592 | 5.62756 | 0.0101915 | 3.57702e-05 | 1.60165e-06 | 1(Win) | true |
| simdjson (ondemand) | 730.99 | 0.0354759 | 1313.52ms | 4390 | 1280 | 5284.24 | 5727.34 | 0.0863793 | 7.09408 | 31.7989 | 5.78201 | 0.00954816 | 3.87956e-05 | 4.09311e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1507.68 | 0.0496365 | 1314.86ms | 9378 | 320 | 2774.32 | 5932.01 | 0.0428474 | 3.44017 | 14.9562 | 2.92163 | 0.00621468 | 1.033e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1441.86 | 0.0708021 | 1340.86ms | 9378 | 80 | 1542.97 | 6202.8 | 0.0181337 | 3.59663 | 16.0671 | 2.86788 | 0.0044799 | 3.33227e-05 | 3.99872e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1611.71 | 0.0751951 | 1299.71ms | 9378 | 320 | 5571.55 | 5549.12 | 0.00106998 | 3.21854 | 14.2305 | 2.76104 | 0.00596976 | 2.39923e-05 | 5.99808e-06 | 1(Win) | true |
| simdjson (ondemand) | 1523.3 | 0.0251084 | 1342.57ms | 9378 | 2560 | 5563.26 | 5871.18 | 0.0550055 | 3.40347 | 15.3414 | 2.70729 | 0.00468142 | 1.89939e-05 | 2.45755e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2133.2 | 0.062017 | 934.526ms | 4390 | 640 | 948.127 | 1962.6 | 0.13389 | 2.46464 | 10.7417 | 1.97585 | 0.00254413 | 3.09653e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1908.57 | 0.026784 | 935.437ms | 4390 | 2560 | 883.699 | 2193.6 | 0.0599581 | 2.74762 | 11.8572 | 1.89818 | 0.00266239 | 2.82069e-05 | 4.36005e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2252.76 | 0.0604504 | 907.877ms | 4390 | 1280 | 1615.51 | 1858.45 | 0.0385758 | 2.33557 | 10.4009 | 1.8959 | 0.00205634 | 2.50925e-05 | 1.24573e-06 | 1(Win) | true |
| simdjson (ondemand) | 1955.54 | 0.0251742 | 932.722ms | 4390 | 4890 | 1420.42 | 2140.91 | 0.00930684 | 2.68246 | 11.574 | 1.82961 | 0.00263529 | 1.97046e-05 | 5.91603e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3900.55 | 0.0378365 | 970.435ms | 9378 | 4890 | 3680.44 | 2292.9 | 0.0030059 | 1.34314 | 5.80657 | 0.975155 | 0.00135635 | 1.3171e-05 | 1.30837e-07 | 1(Win) | true |
| simdjson (ondemand) | 3657.78 | 0.0303544 | 987.536ms | 9378 | 4890 | 2693.63 | 2445.08 | 0.0886559 | 1.43108 | 6.17797 | 0.91896 | 0.0015571 | 1.66818e-05 | 2.22424e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4031.08 | 0.0252331 | 945.244ms | 9378 | 4890 | 1532.6 | 2218.65 | 0.0203231 | 1.3011 | 5.67402 | 0.943058 | 0.00118404 | 1.26258e-05 | 8.94056e-07 | 1(Win) | true |
| simdjson (ondemand) | 3744.19 | 0.0423363 | 970.341ms | 9378 | 4890 | 5000.79 | 2388.65 | 0.0255323 | 1.39808 | 6.04543 | 0.886863 | 0.00160439 | 1.45666e-05 | 2.81301e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1758.39 | 0.0522507 | 967.435ms | 4390 | 320 | 495.26 | 2380.95 | 0.078033 | 2.97946 | 14.0765 | 2.64374 | 0.00447893 | 1.99317e-05 | 4.27107e-06 | 1(Win) | true |
| simdjson (ondemand) | 1596.07 | 0.0440254 | 978.452ms | 4390 | 1280 | 1707.03 | 2623.09 | 0.0437032 | 3.27507 | 14.738 | 2.43212 | 0.00324868 | 2.01096e-05 | 3.38126e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.11 | 0.0449095 | 950.931ms | 4390 | 4890 | 5275.99 | 2312.91 | 0.0994556 | 2.892 | 13.7934 | 2.57517 | 0.00365965 | 3.97352e-05 | 8.19859e-06 | 1(Win) | true |
| simdjson (ondemand) | 1651.21 | 0.025639 | 972.835ms | 4390 | 4890 | 2066.51 | 2535.5 | 0.015554 | 3.16684 | 14.3973 | 2.35216 | 0.00330427 | 3.72663e-05 | 7.6396e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3100.55 | 0.0518557 | 1017.68ms | 9378 | 2560 | 5727.65 | 2884.51 | 0.00426561 | 1.66223 | 7.49744 | 1.16293 | 0.0018215 | 2.55335e-05 | 1.45787e-05 | 1(Win) | true |
| Jsonifier (generic) | 3011.41 | 0.0682454 | 1031.37ms | 9378 | 2560 | 10516.4 | 2969.89 | 0.0778305 | 1.70452 | 7.35114 | 1.3087 | 0.00185057 | 2.43255e-05 | 8.78885e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3187.1 | 0.06003 | 1016.34ms | 9378 | 160 | 454.032 | 2806.18 | 0.131234 | 1.60987 | 7.3649 | 1.13084 | 0.00181142 | 1.33291e-05 | 4.66517e-06 | 1(Win) | true |
| Jsonifier (generic) | 3070.34 | 0.123908 | 1024.61ms | 9378 | 640 | 8337.39 | 2912.89 | 0.0486822 | 1.67409 | 7.2186 | 1.27661 | 0.00172845 | 3.38225e-05 | 2.18263e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1438.88 | 0.039891 | 1027.42ms | 4669 | 2560 | 3901.14 | 3094.57 | 0.0107031 | 3.62487 | 14.7356 | 2.98802 | 0.00297725 | 5.25407e-05 | 1.42228e-05 | 1(Win) | true |
| simdjson (ondemand) | 1433.44 | 0.0339252 | 1029.64ms | 4669 | 4890 | 5430.5 | 3106.3 | 0.0446069 | 3.63728 | 16.4716 | 2.48554 | 0.00160564 | 3.07909e-05 | 2.80316e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1575.58 | 0.193181 | 1017.4ms | 4669 | 40 | 1192.23 | 2826.07 | 0.0598234 | 3.33009 | 13.9163 | 2.8006 | 0.00194903 | 3.74813e-05 | 1.60634e-05 | 1(Win) | true |
| simdjson (ondemand) | 1559.25 | 0.0463256 | 1008.93ms | 4669 | 640 | 1120.05 | 2855.67 | 0.0016415 | 3.35226 | 15.6483 | 2.29792 | 0.00164349 | 4.04931e-05 | 1.33862e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2269.26 | 0.0426793 | 1068.06ms | 7932 | 4890 | 9897.84 | 3333.48 | 0.10207 | 2.24887 | 10.1771 | 1.47819 | 0.000699917 | 6.42218e-05 | 3.69707e-05 | 1(Win) | true |
| Jsonifier (generic) | 2210.46 | 0.126138 | 1078.92ms | 7932 | 320 | 5962.71 | 3422.15 | 0.229135 | 2.33298 | 9.49143 | 1.81026 | 0.00162632 | 3.58516e-05 | 1.33951e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2453.58 | 0.0606873 | 1047.49ms | 7932 | 2560 | 8961.89 | 3083.06 | 0.00278749 | 2.08951 | 9.72832 | 1.37658 | 0.00056225 | 4.37311e-05 | 2.15208e-05 | 1(Win) | true |
| Jsonifier (generic) | 2424.9 | 0.136774 | 1053.56ms | 7932 | 80 | 1456.38 | 3119.53 | 0.0160255 | 2.15252 | 9.01488 | 1.70222 | 0.00118507 | 2.04866e-05 | 1.5759e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 592.753 | 0.0377559 | 1472.18ms | 4669 | 1280 | 10296.3 | 7511.91 | 0.030484 | 8.73387 | 38.7169 | 7.68537 | 0.00894698 | 3.09555e-05 | 5.01981e-06 | 1(Win) | true |
| simdjson (ondemand) | 246.512 | 0.02629 | 2530.3ms | 4669 | 4890 | 110271 | 18062.9 | 0.0150035 | 20.9297 | 104.739 | 18.9589 | 0.0367356 | 5.16832e-05 | 6.70129e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 608.778 | 0.0258048 | 1455.89ms | 4669 | 2560 | 9119.48 | 7314.17 | 0.0393227 | 8.50558 | 37.8929 | 7.49754 | 0.0107663 | 4.25847e-05 | 1.15456e-05 | 1(Win) | true |
| simdjson (ondemand) | 249.453 | 0.0522768 | 2512.61ms | 4669 | 1280 | 111454 | 17849.9 | 0.0332965 | 20.6587 | 103.922 | 18.7734 | 0.0359313 | 3.86525e-05 | 5.18714e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 894.024 | 0.0203871 | 1567.66ms | 7932 | 4890 | 14550.8 | 8461.23 | 0.0097874 | 5.78974 | 24.5102 | 4.84569 | 0.00502647 | 7.4818e-05 | 3.74863e-05 | 1(Win) | true |
| simdjson (ondemand) | 418.741 | 0.0705307 | 2531.75ms | 7932 | 320 | 51949.5 | 18065 | 0.00733517 | 12.3239 | 61.3188 | 11.0212 | 0.0228209 | 5.08226e-05 | 1.89107e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 941.762 | 0.0755207 | 1531.52ms | 7932 | 320 | 11775.1 | 8032.33 | 0.0251265 | 5.4973 | 24.0252 | 4.73512 | 0.00479663 | 2.04866e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 423.653 | 0.0629815 | 2514.83ms | 7932 | 640 | 80937.7 | 17855.5 | 0.0416361 | 12.1764 | 60.8362 | 10.9115 | 0.0239436 | 2.56083e-05 | 1.37891e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4357.92 | 0.322586 | 816.501ms | 4669 | 40 | 434.551 | 1021.75 | 0.125759 | 1.2292 | 5.1722 | 0.76269 | 0.00114586 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4179.39 | 0.0814367 | 817.986ms | 4669 | 1280 | 963.545 | 1065.4 | 0.0990434 | 1.28208 | 5.63868 | 0.702292 | 0.00154627 | 2.30911e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4746.17 | 0.0952641 | 807.771ms | 4669 | 640 | 511.211 | 938.169 | 0.0479888 | 1.13207 | 4.89848 | 0.701007 | 0.00107156 | 2.17525e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4480.39 | 0.0318305 | 810.764ms | 4669 | 2560 | 256.18 | 993.822 | 0.0718771 | 1.19579 | 5.36496 | 0.640609 | 0.00143508 | 2.03302e-05 | 1.92426e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6073.73 | 0.0912125 | 854.175ms | 7932 | 1280 | 1651.86 | 1245.45 | 0.192018 | 0.861618 | 3.81531 | 0.432048 | 0.00100109 | 3.0533e-05 | 1.52665e-05 | 1(Win) | true |
| Jsonifier (generic) | 6028.81 | 0.101959 | 853.927ms | 7932 | 30 | 49.0989 | 1254.73 | 0.0824227 | 0.866293 | 3.65721 | 0.483737 | 0.000760632 | 1.68095e-05 | 1.68095e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6498.49 | 0.0884509 | 845.756ms | 7932 | 4890 | 5183.87 | 1164.05 | 0.0684989 | 0.805156 | 3.65419 | 0.395739 | 0.000808199 | 2.82308e-05 | 1.66291e-05 | 1(Win) | true |
| Jsonifier (generic) | 6419.17 | 0.0474292 | 847.265ms | 7932 | 160 | 49.9827 | 1178.43 | 0.024921 | 0.814602 | 3.49609 | 0.447428 | 0.000636662 | 6.30358e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3130.65 | 0.0717477 | 854.12ms | 4669 | 4890 | 5092.18 | 1422.29 | 0.626987 | 1.69058 | 7.65175 | 1.31292 | 0.00149763 | 2.19435e-05 | 1.48918e-06 | 1(Win) | true |
| simdjson (ondemand) | 2572.96 | 0.0310858 | 903.385ms | 4669 | 1280 | 370.437 | 1730.57 | 0.179756 | 2.04917 | 9.79225 | 1.53116 | 0.0023215 | 2.87803e-05 | 3.84852e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3376.85 | 0.0680032 | 847.132ms | 4669 | 4890 | 3931.8 | 1318.6 | 0.142214 | 1.57312 | 7.37803 | 1.25123 | 0.00137644 | 1.77387e-05 | 1.79577e-06 | 1(Win) | true |
| simdjson (ondemand) | 2699.3 | 0.0911455 | 879.646ms | 4669 | 1280 | 2893.52 | 1649.58 | 0.013168 | 1.95305 | 9.51853 | 1.46948 | 0.00235161 | 1.58961e-05 | 2.17525e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4725.11 | 0.0677983 | 875.958ms | 7932 | 80 | 94.2475 | 1600.92 | 0.040585 | 1.11757 | 5.27408 | 0.820348 | 0.000918747 | 1.5759e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3993.99 | 0.0431253 | 904.08ms | 7932 | 2560 | 1707.88 | 1893.98 | 0.0415757 | 1.31691 | 6.23664 | 0.915154 | 0.00139654 | 1.50203e-05 | 1.77288e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5063.71 | 0.0610733 | 867.97ms | 7932 | 80 | 66.5918 | 1493.88 | 0 | 1.0638 | 5.11296 | 0.784039 | 0.000806858 | 7.87948e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4157.79 | 0.0299712 | 896.252ms | 7932 | 4890 | 1453.98 | 1819.37 | 0.0168545 | 1.26612 | 6.07552 | 0.878845 | 0.00147326 | 1.08798e-05 | 1.36642e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 557.195 | 0.0338123 | 1507.44ms | 4604 | 1280 | 9086.89 | 7880.03 | 0.156703 | 9.28967 | 36.7168 | 7.45026 | 0.0103314 | 6.07488e-05 | 1.9684e-05 | 1(Win) | true |
| simdjson (ondemand) | 552.465 | 0.0240932 | 1534.51ms | 4604 | 2560 | 9386.17 | 7947.5 | 0.0933357 | 9.36797 | 38.0517 | 6.88003 | 0.012852 | 9.33292e-05 | 4.10648e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 638.815 | 0.0290883 | 1502.92ms | 4604 | 2560 | 10232.8 | 6873.22 | 0.0317285 | 8.10926 | 32.5699 | 6.50912 | 0.00923501 | 4.55616e-05 | 9.24807e-06 | 1(Win) | true |
| simdjson (ondemand) | 620.523 | 0.018579 | 1516.94ms | 4604 | 4890 | 8451.05 | 7075.83 | 0.050132 | 8.34904 | 34.0367 | 5.96655 | 0.0104493 | 6.07634e-05 | 1.80336e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2097.61 | 0.0224212 | 1554.06ms | 18245 | 2560 | 8855.13 | 8295.05 | 0.00722905 | 2.46675 | 10.19 | 1.92706 | 0.00271232 | 1.43019e-05 | 3.57547e-06 | 1(Win) | true |
| simdjson (ondemand) | 1993.98 | 0.123651 | 1588.61ms | 18245 | 160 | 18627.8 | 8726.16 | 0.0491813 | 2.59344 | 10.5249 | 1.77632 | 0.0031101 | 2.98027e-05 | 1.50726e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2347.93 | 0.0515346 | 1552.65ms | 18245 | 640 | 9334.61 | 7410.71 | 0.083235 | 2.20511 | 9.15314 | 1.69164 | 0.00240811 | 1.19039e-05 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 2251.19 | 0.0254098 | 1579.27ms | 18245 | 2560 | 9874.35 | 7729.16 | 0.0592366 | 2.29943 | 9.50441 | 1.54409 | 0.00243705 | 1.24178e-05 | 9.63449e-07 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 326.707 | 0.0938783 | 2067.63ms | 4604 | 160 | 25468.5 | 13439.3 | 0.00186025 | 15.8091 | 68.9156 | 14.5793 | 0.0201863 | 0.000126249 | 7.73784e-05 | 1(Win) | true |
| simdjson (ondemand) | 224.099 | 0.0497638 | 2685.39ms | 4604 | 640 | 60841.2 | 19592.7 | 0.0678681 | 23.0175 | 109.233 | 21.907 | 0.0240423 | 8.00934e-05 | 2.5114e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 349.729 | 0.0173331 | 2075.52ms | 4604 | 4890 | 23156.4 | 12554.6 | 0.0534213 | 14.7757 | 64.6384 | 13.6095 | 0.0180891 | 0.000135252 | 7.29338e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.184 | 0.0303466 | 2678.86ms | 4604 | 1280 | 41084.9 | 18669.2 | 0.0253779 | 21.9424 | 104.945 | 20.9355 | 0.0235108 | 0.000150345 | 6.77061e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1221.22 | 0.0224021 | 2152.78ms | 18245 | 2560 | 26080.6 | 14247.8 | 0.0397326 | 4.22844 | 18.5961 | 3.76876 | 0.00507633 | 2.51353e-05 | 9.29193e-06 | 1(Win) | true |
| simdjson (ondemand) | 860.06 | 0.0220669 | 2745.69ms | 18245 | 2560 | 51021.7 | 20230.9 | 0.00777872 | 5.99751 | 28.4352 | 5.55837 | 0.00625283 | 2.84753e-05 | 7.36503e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1300.75 | 0.0298058 | 2153.31ms | 18245 | 4890 | 77734.3 | 13376.8 | 0.0295308 | 3.96448 | 17.5237 | 3.52568 | 0.00477077 | 2.60149e-05 | 9.43755e-06 | 1(Win) | true |
| simdjson (ondemand) | 900.6 | 0.0182659 | 2748.58ms | 18245 | 4890 | 60899.8 | 19320.2 | 0.0809911 | 5.72524 | 27.3584 | 5.31444 | 0.00619424 | 2.9512e-05 | 1.14327e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4143.18 | 0.0310621 | 821.624ms | 4604 | 4890 | 529.874 | 1059.75 | 0.0435961 | 1.29061 | 6.73501 | 0.943093 | 0.000434583 | 2.18979e-05 | 7.10683e-07 | 1(Win) | true |
| simdjson (ondemand) | 3918.72 | 0.0279577 | 826.152ms | 4604 | 1280 | 125.602 | 1120.45 | 0.019876 | 1.36264 | 6.86208 | 0.959818 | 0.000438138 | 2.2399e-05 | 5.93913e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4247.02 | 0.0237812 | 820.573ms | 4604 | 4890 | 295.581 | 1033.83 | 0.0539123 | 1.25979 | 6.6477 | 0.923545 | 0.00043476 | 2.44297e-05 | 9.77189e-07 | 1(Win) | true |
| simdjson (ondemand) | 4024.67 | 0.0545372 | 825.275ms | 4604 | 160 | 56.639 | 1090.95 | 0.0721327 | 1.32757 | 6.77476 | 0.940269 | 0.000435762 | 4.07255e-05 | 1.35752e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9740.3 | 0.0738362 | 909.725ms | 18245 | 4890 | 8507.27 | 1786.37 | 0.0634689 | 0.531726 | 2.66002 | 0.283091 | 0.00015721 | 1.2901e-05 | 6.01896e-06 | 1(Win) | true |
| Jsonifier (generic) | 9503.73 | 0.233173 | 908.366ms | 18245 | 160 | 2915.92 | 1830.84 | 0.186053 | 0.544156 | 2.54185 | 0.274431 | 0.000190121 | 5.48095e-06 | 2.39792e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9957.32 | 0.0624411 | 905.207ms | 18245 | 160 | 190.487 | 1747.44 | 0.100046 | 0.520018 | 2.63798 | 0.278158 | 0.000114072 | 7.19375e-06 | 6.85119e-07 | 1(Win) | true |
| Jsonifier (generic) | 9688.18 | 0.219485 | 909.234ms | 18245 | 160 | 2486.19 | 1795.98 | 0.00939686 | 0.538221 | 2.51981 | 0.269498 | 0.000193204 | 1.09619e-05 | 4.79583e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2899.58 | 0.0440526 | 867.14ms | 4604 | 4890 | 2175.97 | 1514.26 | 0.0417492 | 1.82537 | 9.43571 | 1.67572 | 0.00108215 | 2.24309e-05 | 4.04201e-06 | 1(Win) | true |
| simdjson (ondemand) | 2050.07 | 0.0896826 | 929.515ms | 4604 | 320 | 1180.59 | 2141.74 | 0.0530829 | 2.56258 | 13.2628 | 2.351 | 0.00112063 | 9.50261e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2968.28 | 0.0730924 | 864.236ms | 4604 | 160 | 187.036 | 1479.21 | 0.0312764 | 1.78357 | 9.34839 | 1.65617 | 0.000897318 | 2.17202e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2069.06 | 0.0404905 | 928.345ms | 4604 | 2560 | 1890.04 | 2122.08 | 0.0560827 | 2.53596 | 13.1755 | 2.33145 | 0.00114676 | 5.41309e-05 | 2.40111e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7452.97 | 0.0362742 | 951.994ms | 18245 | 2560 | 1835.97 | 2334.61 | 0.0574913 | 0.703022 | 3.30863 | 0.461113 | 0.000274776 | 6.53004e-06 | 3.4256e-07 | 1(Win) | true |
| simdjson (ondemand) | 6275.69 | 0.0279998 | 995.882ms | 18245 | 1280 | 771.407 | 2772.57 | 0.000394488 | 0.833096 | 4.27569 | 0.634037 | 0.000330913 | 5.65223e-06 | 8.56399e-08 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7530 | 0.0302402 | 948.547ms | 18245 | 320 | 156.249 | 2310.73 | 0.0514994 | 0.6963 | 3.2866 | 0.45618 | 0.000274048 | 8.05015e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6335.89 | 0.0288453 | 993.47ms | 18245 | 160 | 100.402 | 2746.22 | 0.0514078 | 0.82557 | 4.25366 | 0.629104 | 0.000361743 | 2.05536e-05 | 6.85119e-07 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1238.75 | 0.0495591 | 1099.16ms | 4926 | 2560 | 9042.88 | 3792.36 | 0.174676 | 4.19804 | 17.1961 | 3.36785 | 0.00424026 | 4.34556e-05 | 1.20534e-05 | 1(Win) | true |
| simdjson (ondemand) | 1039.4 | 0.0298164 | 1175.26ms | 4926 | 4890 | 8880.64 | 4519.73 | 0.112225 | 4.99802 | 19.6762 | 3.44478 | 0.00541769 | 8.00394e-05 | 3.00148e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1535.87 | 0.0727786 | 1067.95ms | 4926 | 1280 | 6343.03 | 3058.72 | 0.200101 | 3.39804 | 14.4533 | 2.75822 | 0.00411703 | 4.29799e-05 | 1.04674e-05 | 1(Win) | true |
| simdjson (ondemand) | 1234.63 | 0.0498565 | 1138.17ms | 4926 | 1280 | 4606.47 | 3805.03 | 0.000615966 | 4.21742 | 16.9503 | 2.84024 | 0.00517535 | 3.74289e-05 | 3.96493e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1942.44 | 0.0376111 | 1119.76ms | 8150 | 4890 | 11075.5 | 4001.39 | 0.0153293 | 2.67686 | 11.0044 | 2.05153 | 0.00276884 | 2.80026e-05 | 7.1261e-06 | 1(Win) | true |
| simdjson (ondemand) | 1657.65 | 0.0500094 | 1187.62ms | 8150 | 640 | 3518.96 | 4688.85 | 0.127766 | 3.13421 | 12.3863 | 2.1065 | 0.00282458 | 1.97469e-05 | 2.68405e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2372.74 | 0.0321299 | 1088.03ms | 8150 | 4890 | 5416.82 | 3275.73 | 0.0359092 | 2.2017 | 9.35387 | 1.68479 | 0.00250513 | 2.07761e-05 | 3.96452e-06 | 1(Win) | true |
| simdjson (ondemand) | 1952.44 | 0.0849226 | 1154.03ms | 8150 | 160 | 1828.64 | 3980.89 | 0.0554517 | 2.6667 | 10.7357 | 1.73975 | 0.00330752 | 2.76074e-05 | 8.43558e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 821.031 | 0.0289411 | 1293.84ms | 4926 | 4890 | 13409.4 | 5721.83 | 0.0824525 | 6.31479 | 27.4139 | 5.50853 | 0.00898882 | 6.06523e-05 | 1.94286e-05 | 1(Win) | true |
| simdjson (ondemand) | 458.956 | 0.0221387 | 1744.84ms | 4926 | 4890 | 25110.7 | 10235.8 | 0.03566 | 11.2622 | 49.3512 | 9.00163 | 0.0247796 | 6.09844e-05 | 1.70623e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 945.841 | 0.0314117 | 1254.11ms | 4926 | 4890 | 11902.7 | 4966.8 | 0.0409655 | 5.49252 | 24.701 | 4.90723 | 0.00832468 | 3.15093e-05 | 3.69476e-06 | 1(Win) | true |
| simdjson (ondemand) | 497.398 | 0.0241287 | 1707.24ms | 4926 | 4890 | 25395.5 | 9444.74 | 0.0425097 | 10.4011 | 46.6251 | 8.39505 | 0.0227436 | 3.66155e-05 | 5.60442e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1204.2 | 0.0457414 | 1370.75ms | 8150 | 160 | 1394.63 | 6454.46 | 0.0157812 | 4.3054 | 17.6831 | 3.52528 | 0.00627607 | 6.21166e-05 | 3.60429e-05 | 1(Win) | true |
| simdjson (ondemand) | 756.729 | 0.0634686 | 1750.49ms | 8150 | 320 | 13598.9 | 10271.1 | 0.0326051 | 6.83219 | 30.0207 | 5.40552 | 0.0150947 | 2.45399e-05 | 2.30061e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.35 | 0.0780182 | 1337.88ms | 8150 | 320 | 6501.05 | 5777.25 | 0.00129818 | 3.85474 | 16.0353 | 3.15865 | 0.00625422 | 2.76074e-05 | 2.68405e-06 | 1(Win) | true |
| simdjson (ondemand) | 820.222 | 0.0580916 | 1715.01ms | 8150 | 640 | 19393.6 | 9476.02 | 0.151403 | 6.30379 | 28.373 | 5.0389 | 0.0141493 | 2.31979e-05 | 2.87577e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2521.9 | 0.0553226 | 903.839ms | 4926 | 2560 | 2718.79 | 1862.8 | 0.01294 | 2.08625 | 8.92814 | 1.66565 | 0.00220133 | 3.67946e-05 | 5.07511e-06 | 1(Win) | true |
| simdjson (ondemand) | 2150.55 | 0.0612818 | 933.078ms | 4926 | 640 | 1146.92 | 2184.46 | 0.0227511 | 2.43878 | 10.2745 | 1.62525 | 0.00134015 | 2.09348e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2754.59 | 0.112183 | 896.893ms | 4926 | 640 | 2342.68 | 1705.45 | 0.00531357 | 1.91353 | 8.32318 | 1.51786 | 0.00286236 | 2.69615e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2331.29 | 0.0385093 | 928.071ms | 4926 | 4890 | 2944.68 | 2015.11 | 0.0318467 | 2.25725 | 9.67053 | 1.47848 | 0.00138923 | 2.60294e-05 | 2.40782e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3667.29 | 0.0403829 | 927.241ms | 8150 | 1280 | 937.63 | 2119.4 | 0.00328081 | 1.43142 | 6.02994 | 1.04245 | 0.00168549 | 1.66794e-05 | 4.79294e-07 | 1(Win) | true |
| simdjson (ondemand) | 3375.32 | 0.0372441 | 945.99ms | 8150 | 4890 | 3596.75 | 2302.73 | 0.0262292 | 1.55172 | 6.56638 | 0.97951 | 0.00090652 | 2.06255e-05 | 3.03612e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3994.57 | 0.0649862 | 919.852ms | 8150 | 1280 | 2046.57 | 1945.75 | 0.00349307 | 1.31628 | 5.66429 | 0.953129 | 0.00167868 | 1.67753e-05 | 9.58589e-07 | 1(Win) | true |
| simdjson (ondemand) | 3633.32 | 0.0357742 | 939.925ms | 8150 | 4890 | 2863.9 | 2139.21 | 0.00202046 | 1.4442 | 6.20135 | 0.890798 | 0.0010158 | 1.53312e-05 | 1.38005e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1901.7 | 0.111452 | 963.606ms | 4926 | 1280 | 9702.61 | 2470.32 | 0.00449102 | 2.7516 | 12.0481 | 2.29781 | 0.00321524 | 0.000112128 | 3.91735e-05 | 1(Win) | true |
| simdjson (ondemand) | 1575.58 | 0.0389518 | 1014.1ms | 4926 | 4890 | 6595.86 | 2981.63 | 0.00985609 | 3.31083 | 14.6072 | 2.446 | 0.00449138 | 2.38707e-05 | 1.20391e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2017.97 | 0.0347268 | 961.705ms | 4926 | 4890 | 3195.95 | 2327.99 | 0.0642496 | 2.59715 | 11.4367 | 2.14819 | 0.00459869 | 3.25056e-05 | 2.57388e-06 | 1(Win) | true |
| simdjson (ondemand) | 1660.59 | 0.0493476 | 1008.9ms | 4926 | 2560 | 4989.3 | 2829 | 0.106946 | 3.14573 | 13.9968 | 2.2974 | 0.00537684 | 2.41861e-05 | 2.14106e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2780.7 | 0.0515777 | 998.084ms | 8150 | 2560 | 5320.73 | 2795.14 | 0.0246181 | 1.87793 | 7.99718 | 1.45031 | 0.00222522 | 2.19517e-05 | 4.16986e-06 | 1(Win) | true |
| simdjson (ondemand) | 2526.73 | 0.0777212 | 1023.48ms | 8150 | 1280 | 7316.21 | 3076.09 | 0.0333358 | 2.06407 | 9.22699 | 1.48454 | 0.00249406 | 9.39417e-06 | 2.87577e-07 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2965.61 | 0.0751052 | 990.331ms | 8150 | 1280 | 4959.49 | 2620.86 | 0.0357238 | 1.76227 | 7.62761 | 1.35988 | 0.00296281 | 2.05138e-05 | 2.68405e-06 | 1(Win) | true |
| simdjson (ondemand) | 2663.71 | 0.0574574 | 1019.3ms | 8150 | 160 | 449.733 | 2917.91 | 0.026339 | 1.96153 | 8.85804 | 1.39472 | 0.00295322 | 3.60429e-05 | 3.83436e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2150.82 | 0.0534815 | 842.583ms | 2821 | 1280 | 572.815 | 1250.83 | 0.0890489 | 2.4719 | 9.18433 | 1.69763 | 0.000357254 | 4.37566e-05 | 9.96987e-06 | 1(Win) | true |
| simdjson (ondemand) | 1992.23 | 0.0501241 | 853.647ms | 2821 | 2560 | 1172.9 | 1350.41 | 0.0547878 | 2.66078 | 10.0383 | 1.55902 | 0.000359885 | 8.64055e-05 | 2.38169e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2357.4 | 0.0332528 | 838.802ms | 2821 | 640 | 92.1675 | 1141.22 | 0.158705 | 2.26339 | 8.57639 | 1.54591 | 0.0003567 | 4.32028e-05 | 1.10776e-05 | 1(Win) | true |
| simdjson (ondemand) | 2137.02 | 0.047666 | 849.93ms | 2821 | 4890 | 1760.82 | 1258.91 | 0.0367325 | 2.48681 | 9.55335 | 1.43602 | 0.000378406 | 7.48839e-05 | 1.88478e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2716.47 | 0.0523806 | 849.624ms | 3770 | 2560 | 1230.42 | 1323.54 | 0.0498735 | 1.95348 | 7.31379 | 1.26976 | 0.000268878 | 4.71444e-05 | 1.23301e-05 | 1(Win) | true |
| simdjson (ondemand) | 2589.38 | 0.0638509 | 857.345ms | 3770 | 160 | 125.761 | 1388.5 | 0.0332982 | 2.04735 | 7.83289 | 1.17958 | 0.000265252 | 3.64721e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2963.13 | 0.0838878 | 844.736ms | 3770 | 160 | 165.767 | 1213.36 | 0.00824224 | 1.79772 | 6.90743 | 1.16764 | 0.000268568 | 3.97878e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2763.17 | 0.0488455 | 853.738ms | 3770 | 2560 | 1034.09 | 1301.17 | 0.0666023 | 1.92268 | 7.47427 | 1.08912 | 0.000266599 | 5.15998e-05 | 1.32626e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 859.974 | 0.0348665 | 1052.31ms | 2821 | 4890 | 5817.82 | 3128.37 | 0.0294763 | 6.06373 | 26.1372 | 4.83233 | 0.00119408 | 0.000117944 | 5.24115e-05 | 1(Win) | true |
| simdjson (ondemand) | 357.982 | 0.0354828 | 1472.8ms | 2821 | 2560 | 18203.7 | 7515.22 | 0.0401627 | 14.4611 | 67.0245 | 11.5509 | 0.0129219 | 9.05596e-05 | 2.49247e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 893.126 | 0.0352345 | 1027.25ms | 2821 | 2560 | 2883.74 | 3012.25 | 0.0560936 | 5.84278 | 25.5108 | 4.6721 | 0.00174293 | 7.69895e-05 | 1.86935e-05 | 1(Win) | true |
| simdjson (ondemand) | 362.244 | 0.055919 | 1467.5ms | 2821 | 1280 | 22076.7 | 7426.81 | 0.0689696 | 14.2933 | 66.5409 | 11.4272 | 0.0132012 | 0.000147609 | 7.58818e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1046.46 | 0.0537267 | 1063.15ms | 3770 | 160 | 545.179 | 3435.73 | 0.0263703 | 4.98274 | 20.3992 | 3.79841 | 0.00161804 | 4.64191e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 477.946 | 0.0927506 | 1496.6ms | 3770 | 640 | 31155.7 | 7522.5 | 0.0566313 | 10.823 | 49.7037 | 8.5069 | 0.0105297 | 2.27951e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1080.12 | 0.0307312 | 1060.06ms | 3770 | 2560 | 2678.78 | 3328.66 | 0.0484312 | 4.82608 | 19.9939 | 3.69576 | 0.00160716 | 3.9477e-05 | 2.90119e-06 | 1(Win) | true |
| simdjson (ondemand) | 481.714 | 0.0425069 | 1474.22ms | 3770 | 2560 | 25767 | 7463.67 | 0.0577137 | 10.7293 | 49.3501 | 8.41751 | 0.01093 | 4.75589e-05 | 8.80719e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5732.11 | 0.0540991 | 759.748ms | 2821 | 4890 | 315.258 | 469.341 | 0.0442327 | 0.973819 | 3.72847 | 0.511521 | 0.000397037 | 2.92866e-05 | 5.65435e-06 | 1(Win) | true |
| simdjson (ondemand) | 5464.57 | 0.0842791 | 760.635ms | 2821 | 2560 | 440.732 | 492.32 | 0.214529 | 1.02178 | 3.99646 | 0.449132 | 0.000521203 | 1.93859e-05 | 2.90788e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5659.65 | 0.0999646 | 765.816ms | 2821 | 2560 | 578.043 | 475.35 | 0.144592 | 0.984674 | 3.64977 | 0.493442 | 0.000814898 | 3.35098e-05 | 7.06199e-06 | 1(Win) | true |
| simdjson (ondemand) | 5634.13 | 0.0900074 | 764.2ms | 2821 | 320 | 59.1097 | 477.503 | 0.0869656 | 0.988345 | 3.92095 | 0.432471 | 0.000538373 | 2.99096e-05 | 1.10776e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6850.34 | 0.0968448 | 763.469ms | 3770 | 4890 | 1263.34 | 524.843 | 0.0224056 | 0.809048 | 3.25013 | 0.405305 | 0.000306423 | 2.15348e-05 | 2.16975e-06 | 1(Win) | true |
| simdjson (ondemand) | 6618.31 | 0.0552651 | 765.343ms | 3770 | 4890 | 440.756 | 543.243 | 0.0988579 | 0.836828 | 3.31883 | 0.35199 | 0.000358497 | 2.97798e-05 | 5.74984e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6999.23 | 0.122885 | 763.007ms | 3770 | 640 | 255.014 | 513.678 | 0.130968 | 0.794047 | 3.19125 | 0.391777 | 0.000292192 | 1.03614e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6803.42 | 0.130918 | 765.95ms | 3770 | 1280 | 612.68 | 528.462 | 0.0745642 | 0.813985 | 3.26021 | 0.338727 | 0.00035664 | 3.12914e-05 | 1.07759e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4088.8 | 0.0437061 | 778.493ms | 2821 | 4890 | 404.397 | 657.972 | 0.135502 | 1.33332 | 5.43283 | 0.868132 | 0.00125237 | 2.73294e-05 | 1.81229e-06 | 1(Win) | true |
| simdjson (ondemand) | 3807.09 | 0.0438745 | 784.565ms | 2821 | 2560 | 246.084 | 706.659 | 0.194916 | 1.43098 | 6.24991 | 0.899681 | 0.000850624 | 1.53702e-05 | 2.49247e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4137.61 | 0.0454137 | 780.23ms | 2821 | 2560 | 223.214 | 650.209 | 0.0563203 | 1.32077 | 5.35449 | 0.85041 | 0.000710907 | 2.38169e-05 | 7.06199e-06 | 1(Win) | true |
| simdjson (ondemand) | 3895.73 | 0.0799099 | 783.761ms | 2821 | 4890 | 1489.15 | 690.581 | 0.0437173 | 1.39907 | 6.17193 | 0.882312 | 0.000825028 | 3.11714e-05 | 1.44983e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5161.66 | 0.129137 | 782.843ms | 3770 | 160 | 129.457 | 696.55 | 0.0754283 | 1.05896 | 4.55438 | 0.680902 | 0.000734416 | 2.15517e-05 | 6.6313e-06 | 1(Win) | true |
| simdjson (ondemand) | 4730.72 | 0.0353832 | 788.634ms | 3770 | 4890 | 353.615 | 760.002 | 0.136503 | 1.14468 | 5.01698 | 0.691777 | 0.000721442 | 2.99968e-05 | 6.34652e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5334.1 | 0.144007 | 781.513ms | 3770 | 160 | 150.747 | 674.031 | 0.0342967 | 1.02402 | 4.49576 | 0.667639 | 0.000570292 | 2.15517e-05 | 1.65782e-06 | 1(Win) | true |
| simdjson (ondemand) | 4857.97 | 0.0410689 | 788.018ms | 3770 | 4890 | 451.761 | 740.094 | 0.118733 | 1.11902 | 4.95862 | 0.67878 | 0.000642789 | 2.39757e-05 | 2.87492e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5201.26 | 0.0352347 | 5838.24ms | 277673 | 320 | 102977 | 50912.6 | 0.000945257 | 0.990583 | 4.30864 | 0.678261 | 0.00311565 | 1.71065e-06 | 3.37627e-08 | 1(Win) | true |
| simdjson (ondemand) | 4111.55 | 0.244642 | 7221.68ms | 277673 | 80 | 1.98614e+06 | 64406.3 | 0.159224 | 1.25263 | 4.69362 | 0.771527 | 0.00496231 | 2.79105e-06 | 9.0034e-08 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4133.42 | 0.114978 | 7618.24ms | 10548466 | 30 | 2.34915e+08 | 2.43377e+06 | 0.357883 | 1.23815 | 4.3063 | 0.678223 | 0.00981906 | 0.0175674 | 1.10822e-05 | 1(Win) | true |
| simdjson (ondemand) | 3694.86 | 0.210208 | 8466.46ms | 10548466 | 40 | 1.31021e+09 | 2.72265e+06 | 0.0957329 | 1.37864 | 4.69 | 0.771548 | 0.00985439 | 0.0177114 | 0.000263316 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3409.1 | 0.0730037 | 6758.25ms | 16002592 | 80 | 8.54442e+08 | 4.47663e+06 | 0.0423845 | 1.49223 | 7.61292 | 1.20636 | 0.000934763 | 0.0334716 | 0.00451621 | 1(Win) | true |
| simdjson (ondemand) | 3036.44 | 0.0879737 | 7567.25ms | 16002592 | 80 | 1.56404e+09 | 5.02604e+06 | 0.0428374 | 1.67073 | 8.59454 | 1.25499 | 0.00260717 | 0.0364287 | 0.00453047 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3610.66 | 0.109148 | 6350.31ms | 16002591 | 40 | 8.51326e+08 | 4.22672e+06 | 0.332195 | 1.40953 | 7.89616 | 1.29591 | 0.000916127 | 0.0364814 | 0.00600501 | 1(Win) | true |
| simdjson (ondemand) | 1720.57 | 0.109428 | 6248.69ms | 16002591 | 30 | 2.8263e+09 | 8.8699e+06 | 0.301728 | 2.98413 | 13.0901 | 2.14357 | 0.00257269 | 0.0523997 | 0.0057663 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 17616.7 | 0.197112 | 5596.22ms | 16197086 | 30 | 8.96132e+07 | 876822 | 0.11198 | 0.28984 | 1.33568 | 0.070273 | 7.88599e-05 | 0.0157217 | 0.00215358 | 1(Win) | true |
| simdjson (ondemand) | 16712 | 0.368807 | 6051.2ms | 16197086 | 30 | 3.48608e+08 | 924290 | 0.349107 | 0.303765 | 1.26202 | 0.0749453 | 0.000116634 | 0.0157316 | 0.00139189 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 17593.8 | 0.135243 | 5613.91ms | 16197085 | 30 | 4.22964e+07 | 877964 | 0.534969 | 0.287604 | 1.33981 | 0.0717036 | 9.21874e-05 | 0.015738 | 0.00157375 | 1(Win) | true |
| simdjson (ondemand) | 15448.9 | 0.563737 | 6282.85ms | 16197085 | 30 | 9.53131e+08 | 999860 | 0.340345 | 0.329793 | 1.33649 | 0.0897511 | 0.000127356 | 0.0157531 | 0.0016175 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1944.57 | 0.0593981 | 8248.07ms | 4212000 | 80 | 1.20438e+08 | 2.06569e+06 | 0.0438661 | 2.59825 | 11.4437 | 2.08965 | 0.0111175 | 0.0663689 | 0.00209831 | 1(Win) | true |
| simdjson (ondemand) | 1575.62 | 0.0952003 | 9743.07ms | 4212000 | 80 | 4.71239e+08 | 2.5494e+06 | 0.365258 | 3.234 | 13.512 | 2.36363 | 0.0100315 | 0.0662347 | 0.00196254 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1563.79 | 0.0978468 | 9776.17ms | 4212000 | 40 | 2.5268e+08 | 2.56867e+06 | 0.071905 | 3.23642 | 15.2579 | 2.94039 | 0.0120455 | 0.0663078 | 0.00142923 | 1(Win) | true |
| simdjson (ondemand) | 1311.59 | 0.0945861 | 5461.94ms | 4212000 | 80 | 6.7131e+08 | 3.06259e+06 | 0.198649 | 3.87128 | 16.6363 | 2.89734 | 0.0102263 | 0.0662761 | 0.0031137 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1786.52 | 0.126139 | 8789.29ms | 4211999 | 30 | 2.41311e+08 | 2.24843e+06 | 0.106374 | 2.83223 | 12.3737 | 2.30527 | 0.0121033 | 0.0677295 | 0.00219192 | 1(Win) | true |
| simdjson (ondemand) | 1295.28 | 0.100855 | 5545.17ms | 4211999 | 80 | 7.8259e+08 | 3.10117e+06 | 0.990851 | 3.90839 | 15.7514 | 2.81311 | 0.0102146 | 0.0676224 | 0.00427819 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1536.11 | 0.130731 | 9955.15ms | 4211999 | 30 | 3.50595e+08 | 2.61496e+06 | 0.0912336 | 3.29933 | 15.4776 | 2.99713 | 0.0126099 | 0.0678179 | 0.00178362 | 1(Win) | true |
| simdjson (ondemand) | 1111.31 | 0.0747329 | 6308.79ms | 4211999 | 80 | 5.83736e+08 | 3.61453e+06 | 0.106394 | 4.55555 | 18.8759 | 3.34688 | 0.0104273 | 0.06731 | 0.00187006 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1489.14 | 0.11084 | 9663.64ms | 4525120 | 30 | 3.09534e+08 | 2.89798e+06 | 0.209729 | 3.40428 | 16.6405 | 3.0144 | 0.00957328 | 0.0777589 | 0.000684777 | 1(Win) | true |
| simdjson (ondemand) | 1332.22 | 0.0577866 | 5170.15ms | 4525120 | 80 | 2.8032e+08 | 3.23933e+06 | 0.131783 | 3.79387 | 17.1962 | 2.62393 | 0.0135537 | 0.0774928 | 0.00179199 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 791.879 | 0.0738288 | 8564.97ms | 4525120 | 80 | 1.29505e+09 | 5.44969e+06 | 0.277329 | 6.46139 | 32.019 | 6.41872 | 0.0155268 | 0.078526 | 0.00383561 | 1(Win) | true |
| simdjson (ondemand) | 612.422 | 0.176385 | 5125.32ms | 4525120 | 40 | 6.17937e+09 | 7.0466e+06 | 0.660624 | 8.30927 | 42.9269 | 8.08853 | 0.0238809 | 0.07834 | 0.00654536 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1317.27 | 0.108028 | 5230.52ms | 4525119 | 80 | 1.00201e+09 | 3.27609e+06 | 0.391645 | 3.86742 | 18.8618 | 3.5689 | 0.0104733 | 0.078078 | 0.00507569 | 1(Win) | true |
| simdjson (ondemand) | 976.021 | 0.0763324 | 7043.84ms | 4525119 | 80 | 9.11276e+08 | 4.42151e+06 | 0.798603 | 5.23603 | 22.1113 | 3.6087 | 0.0164491 | 0.0942075 | 0.00186638 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 786.172 | 0.115928 | 8620.15ms | 4525119 | 40 | 1.61981e+09 | 5.48924e+06 | 0.104583 | 6.49996 | 31.75 | 6.41969 | 0.0155753 | 0.0787093 | 0.00361472 | 1(Win) | true |
| simdjson (ondemand) | 526.876 | 0.0771136 | 5949.91ms | 4525119 | 30 | 1.19682e+09 | 8.19072e+06 | 0.383178 | 9.75272 | 47.8417 | 9.07322 | 0.0268003 | 0.0947277 | 0.00482519 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1266.02 | 0.0972621 | 5034.53ms | 4203059 | 30 | 2.84487e+08 | 3.16611e+06 | 0.141629 | 4.04272 | 17.8425 | 3.41847 | 0.0147793 | 0.0893615 | 0.000597549 | 1(Win) | true |
| simdjson (ondemand) | 976.094 | 0.143803 | 6452.98ms | 4203059 | 30 | 1.04618e+09 | 4.10652e+06 | 0.174645 | 5.20691 | 20.3934 | 3.53675 | 0.0261833 | 0.0883497 | 0.00261513 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 815.472 | 0.0962321 | 7772.09ms | 4203059 | 30 | 6.71235e+08 | 4.91538e+06 | 0.32044 | 6.20293 | 28.0165 | 5.62808 | 0.0225069 | 0.0889751 | 0.0114896 | 1(Win) | true |
| simdjson (ondemand) | 740.544 | 0.164161 | 8478.89ms | 4203059 | 80 | 6.31621e+09 | 5.41271e+06 | 0.116056 | 6.90791 | 28.8013 | 5.12675 | 0.0282289 | 0.0872549 | 0.00774577 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1150.59 | 0.100367 | 5523.29ms | 4203058 | 40 | 4.89026e+08 | 3.48374e+06 | 0.131551 | 4.44492 | 19.9837 | 3.95304 | 0.0162264 | 0.0889822 | 0.00178356 | 1(Win) | true |
| simdjson (ondemand) | 779.009 | 0.105273 | 8044.57ms | 4203058 | 40 | 1.17364e+09 | 5.14545e+06 | 0.439712 | 6.53325 | 25.0228 | 4.44937 | 0.0278738 | 0.10438 | 0.00949836 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.867 | 0.0977877 | 8175.5ms | 4203058 | 40 | 1.04774e+09 | 5.23374e+06 | 0.36152 | 6.67667 | 30.1571 | 6.16232 | 0.0245503 | 0.0883762 | 0.00621529 | 1(Win) | true |
| simdjson (ondemand) | 616.316 | 0.107952 | 10156.9ms | 4203058 | 40 | 1.97171e+09 | 6.50372e+06 | 0.374316 | 8.25858 | 33.4332 | 6.04004 | 0.0297118 | 0.103446 | 0.00759376 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1711.8 | 0.0754671 | 7564.09ms | 4197496 | 160 | 4.98321e+08 | 2.3385e+06 | 0.244649 | 2.96739 | 15.7559 | 3.07136 | 0.000545551 | 0.0815531 | 0.000298955 | 1(Win) | true |
| simdjson (ondemand) | 1464.42 | 0.0479718 | 8799.42ms | 4197496 | 160 | 2.75132e+08 | 2.73353e+06 | 0.0801344 | 3.46579 | 18.5331 | 2.75321 | 0.00468651 | 0.0806472 | 0.00164808 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1014.14 | 0.0729459 | 6102.84ms | 4197496 | 80 | 6.63244e+08 | 3.94721e+06 | 0.30344 | 4.99727 | 27.5614 | 5.67729 | 0.000924313 | 0.0817773 | 0.00210129 | 1(Win) | true |
| simdjson (ondemand) | 777.311 | 0.114152 | 7888.75ms | 4197496 | 40 | 1.38236e+09 | 5.14986e+06 | 0.0396799 | 6.51618 | 34.4591 | 5.37466 | 0.00789279 | 0.0811621 | 0.00603087 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1518.83 | 0.0784242 | 8495.47ms | 4197495 | 30 | 1.28169e+08 | 2.63561e+06 | 0.0111334 | 3.35543 | 18.0178 | 3.60609 | 0.000658647 | 0.0841686 | 0.000458766 | 1(Win) | true |
| simdjson (ondemand) | 1041.73 | 0.104638 | 5925.09ms | 4197495 | 40 | 6.46712e+08 | 3.84269e+06 | 0.42965 | 4.8616 | 23.6499 | 3.76542 | 0.0049365 | 0.10208 | 0.00121556 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 988.719 | 0.0717451 | 6232.98ms | 4197495 | 40 | 3.37504e+08 | 4.04872e+06 | 0.00645657 | 5.11685 | 27.8261 | 5.76671 | 0.00113836 | 0.0842991 | 0.00150408 | 1(Win) | true |
| simdjson (ondemand) | 646.571 | 0.102051 | 9497.75ms | 4197495 | 30 | 1.19758e+09 | 6.19119e+06 | 0.350465 | 7.83671 | 39.5762 | 6.38691 | 0.00969878 | 0.102361 | 0.00085713 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1468.93 | 0.109724 | 5119.85ms | 4506447 | 40 | 4.12219e+08 | 2.92573e+06 | 0.0138582 | 3.45867 | 15.8899 | 3.00045 | 0.00842295 | 0.0812673 | 0.00141024 | 1(Win) | true |
| simdjson (ondemand) | 1141.88 | 0.0760923 | 6381.57ms | 4506447 | 80 | 6.56139e+08 | 3.76368e+06 | 0.0177952 | 4.44767 | 18.2754 | 3.12968 | 0.014082 | 0.0790395 | 0.00132092 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.385 | 0.038842 | 8378.52ms | 4506447 | 80 | 3.08997e+08 | 5.05976e+06 | 0.210605 | 5.96715 | 26.8775 | 5.42152 | 0.0131544 | 0.0814058 | 0.00639333 | 1(Win) | true |
| simdjson (ondemand) | 508.134 | 0.101152 | 6290.44ms | 4506447 | 30 | 2.19574e+09 | 8.45777e+06 | 0.203295 | 9.99718 | 43.6994 | 7.78398 | 0.0323102 | 0.0791902 | 0.00530606 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1315.87 | 0.131448 | 5643.12ms | 4506446 | 40 | 7.37247e+08 | 3.26605e+06 | 0.130945 | 3.87153 | 17.5592 | 3.41545 | 0.0111467 | 0.0816765 | 0.003959 | 1(Win) | true |
| simdjson (ondemand) | 932.299 | 0.16982 | 7631.21ms | 4506446 | 40 | 2.4513e+09 | 4.60977e+06 | 0.225324 | 5.46727 | 21.9317 | 3.84809 | 0.0142171 | 0.0864623 | 0.00385869 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 857.622 | 0.0787108 | 8301.64ms | 4506446 | 80 | 1.24462e+09 | 5.01116e+06 | 0.385352 | 5.91736 | 26.7357 | 5.4338 | 0.0129768 | 0.0817192 | 0.0128213 | 1(Win) | true |
| simdjson (ondemand) | 461.31 | 0.190872 | 6863.85ms | 4506446 | 30 | 9.48605e+09 | 9.31625e+06 | 0.0370731 | 11.0516 | 47.3555 | 8.50232 | 0.0325121 | 0.0865437 | 0.0135259 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2010.8 | 0.0769873 | 6920.62ms | 4219120 | 160 | 3.79722e+08 | 2.00103e+06 | 0.911409 | 2.53597 | 9.28423 | 1.64402 | 0.011724 | 0.0570426 | 0.000339797 | 1(Win) | true |
| simdjson (ondemand) | 1755.79 | 0.0950217 | 7802.87ms | 4219120 | 80 | 3.79347e+08 | 2.29166e+06 | 0.0787248 | 2.86971 | 9.94023 | 1.53195 | 0.0156902 | 0.0546356 | 8.5074e-05 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 764.585 | 0.0738981 | 8273.84ms | 4219120 | 80 | 1.2099e+09 | 5.26255e+06 | 0.00157454 | 6.66123 | 26.4406 | 4.97297 | 0.0173897 | 0.0577318 | 0.00214198 | 1(Win) | true |
| simdjson (ondemand) | 296.564 | 0.0830157 | 9732.46ms | 4219120 | 40 | 5.07444e+09 | 1.35676e+07 | 0.571388 | 17.1072 | 70.1423 | 12.163 | 0.0794076 | 0.0552 | 0.00415004 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1856.66 | 0.0984599 | 7464ms | 4219119 | 80 | 3.6424e+08 | 2.16715e+06 | 0.0629814 | 2.75765 | 10.3099 | 1.89894 | 0.0122746 | 0.0567478 | 0.000278459 | 1(Win) | true |
| simdjson (ondemand) | 1440.36 | 0.0914134 | 9375.3ms | 4219119 | 80 | 5.21686e+08 | 2.79351e+06 | 0.12472 | 3.50089 | 12.1414 | 1.96019 | 0.0173462 | 0.0557095 | 3.27705e-05 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 761.358 | 0.0758742 | 8314.39ms | 4219119 | 40 | 6.43154e+08 | 5.28486e+06 | 0.347998 | 6.6857 | 26.339 | 4.97693 | 0.0172933 | 0.0575623 | 0.000503192 | 1(Win) | true |
| simdjson (ondemand) | 284.299 | 0.118155 | 10065.1ms | 4219119 | 30 | 8.38914e+09 | 1.41529e+07 | 0.271178 | 17.7527 | 72.3434 | 12.5913 | 0.081114 | 0.0542475 | 0.0051299 | 2(Loss) | true |
