# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-42-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 542.946 | 0.133701 | 886.656ms | 905 | 2560 | 11563.5 | 1589.61 | 0.209517 | 9.53945 | 52.5415 | 5.48619 | 0.00277624 | 0.000178695 | 4.22997e-05 | 1(Win) | true |
| simdjson (ondemand) | 226.93 | 0.112917 | 1110.02ms | 905 | 1280 | 23606.9 | 3803.27 | 0.0770079 | 22.6553 | 104.421 | 9.82431 | 0.0751045 | 0.000182148 | 3.88467e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 550.821 | 0.150653 | 885.357ms | 905 | 2560 | 14265 | 1566.89 | 0.11441 | 9.3803 | 51.8889 | 5.25977 | 0.00162897 | 0.000153229 | 1.5107e-05 | 1(Win) | true |
| simdjson (ondemand) | 223.887 | 0.116026 | 1114.8ms | 905 | 30 | 600.171 | 3854.97 | 0.244109 | 22.8503 | 103.737 | 9.68508 | 0.0893186 | 0.000220994 | 7.36648e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 617.858 | 0.0768993 | 1015.23ms | 1811 | 4890 | 22595.1 | 2795.31 | 0.261579 | 8.25664 | 39.8763 | 5.94644 | 0.000633258 | 9.64341e-05 | 6.32355e-06 | 1(Win) | true |
| simdjson (ondemand) | 319.957 | 0.151146 | 1283.27ms | 1811 | 1280 | 85203.2 | 5397.92 | 0.118719 | 15.7804 | 77.2584 | 9.77195 | 0.000641479 | 0.000176871 | 5.04728e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 642.881 | 0.0672245 | 1001.04ms | 1811 | 4890 | 15949.2 | 2686.51 | 0.383161 | 7.9459 | 38.8117 | 5.70624 | 0.00117562 | 0.000105694 | 1.02758e-05 | 1(Win) | true |
| simdjson (ondemand) | 331.976 | 0.13247 | 1262.09ms | 1811 | 40 | 1899.85 | 5202.5 | 0.0570564 | 15.3825 | 76.1773 | 9.5323 | 0.000565986 | 0.000110436 | 0 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1374.06 | 0.0891607 | 1003.16ms | 3862 | 2560 | 14621.8 | 2680.44 | 0.0558026 | 3.73594 | 17.5686 | 2.03314 | 0.000286344 | 0.000112373 | 3.91434e-05 | 1(Win) | true |
| simdjson (ondemand) | 728.755 | 0.0726352 | 1237.4ms | 3862 | 2560 | 34498.2 | 5053.95 | 0.021096 | 6.99973 | 32.0559 | 3.55956 | 0.000770529 | 8.40521e-05 | 1.8712e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1440.85 | 0.0534776 | 989.933ms | 3862 | 4890 | 9137.72 | 2556.19 | 0.221195 | 3.57155 | 17.029 | 1.9073 | 0.000291287 | 5.89351e-05 | 3.75956e-06 | 1(Win) | true |
| simdjson (ondemand) | 741.218 | 0.142659 | 1228.81ms | 3862 | 160 | 8039.92 | 4968.97 | 0.0260298 | 6.88038 | 31.5601 | 3.45236 | 0.00189183 | 5.98783e-05 | 6.47333e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1374.2 | 0.0841919 | 1402.06ms | 9578 | 1280 | 40086.5 | 6646.97 | 0.0512361 | 3.69963 | 17.5453 | 3.36866 | 0.00180206 | 1.77001e-05 | 2.44701e-06 | 1(Win) | true |
| simdjson (ondemand) | 1322.53 | 0.0828839 | 1438.93ms | 9578 | 2560 | 83891 | 6906.66 | 0.0306901 | 3.83569 | 19.2611 | 2.98632 | 0.00340265 | 6.28883e-05 | 2.35729e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1806.75 | 0.207853 | 1376.03ms | 9578 | 320 | 35335.9 | 5055.65 | 0.00197795 | 2.82022 | 13.4313 | 2.42974 | 0.00105124 | 4.73089e-05 | 1.10931e-05 | 1(Win) | true |
| simdjson (ondemand) | 1723.79 | 0.153434 | 1411.19ms | 9578 | 640 | 42306.1 | 5298.95 | 0.221604 | 2.90001 | 15.1391 | 2.04187 | 0.00219448 | 3.01798e-05 | 5.7097e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1386.48 | 0.185904 | 1004.04ms | 3873 | 1280 | 31394.4 | 2664 | 0.078568 | 3.65674 | 17.4284 | 2.01085 | 0.000279782 | 9.70259e-05 | 3.71159e-05 | 1(Win) | true |
| simdjson (ondemand) | 721.221 | 0.073896 | 1255.72ms | 3873 | 2560 | 36664 | 5121.29 | 0.0355033 | 7.03723 | 31.8105 | 3.67674 | 0.00573996 | 6.02125e-05 | 8.2704e-06 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1449.21 | 0.109956 | 995.084ms | 3873 | 2560 | 20105.5 | 2548.68 | 0.104176 | 3.49807 | 16.9336 | 1.90137 | 0.000283816 | 4.01417e-05 | 1.91631e-06 | 1(Win) | true |
| simdjson (ondemand) | 736.27 | 0.0693868 | 1237.19ms | 3873 | 2560 | 31018 | 5016.61 | 0.0927625 | 6.91699 | 31.3016 | 3.56468 | 0.00751083 | 5.14378e-05 | 5.64808e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1514.05 | 0.051358 | 6713.93ms | 94653 | 640 | 600047 | 59620.4 | 0.0392748 | 3.32271 | 14.9755 | 2.94806 | 0.00888604 | 8.4024e-06 | 1.89838e-06 | 1(Win) | true |
| simdjson (ondemand) | 1249.9 | 0.0635673 | 4105.16ms | 94653 | 160 | 337212 | 72220.1 | 0.0586317 | 4.04458 | 15.8351 | 3.13704 | 0.0117959 | 2.76008e-05 | 2.06676e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2224.7 | 0.0349111 | 6088.34ms | 94653 | 2560 | 513678 | 40575.4 | 0.0485637 | 2.26502 | 11.1932 | 2.08062 | 0.00562596 | 5.46816e-06 | 1.47331e-06 | 1(Win) | true |
| simdjson (ondemand) | 1648.81 | 0.0310052 | 7496.55ms | 94653 | 4890 | 1.40898e+06 | 54747.4 | 0.033558 | 3.05112 | 12.0837 | 2.27856 | 0.00891819 | 1.46915e-05 | 7.02167e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1914.4 | 0.0469351 | 6972.21ms | 124597 | 1280 | 1.08632e+06 | 62069.2 | 0.0911558 | 2.61807 | 11.7287 | 2.24488 | 0.0074243 | 5.00363e-06 | 1.07848e-06 | 1(Win) | true |
| simdjson (ondemand) | 1569.46 | 0.0476675 | 4261.51ms | 124597 | 1280 | 1.66712e+06 | 75710.5 | 0.155687 | 3.20563 | 12.3626 | 2.39684 | 0.0100648 | 2.81783e-05 | 1.91492e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2766.93 | 0.109067 | 6350.72ms | 124597 | 320 | 702030 | 42944.7 | 0.0368415 | 1.79325 | 8.84761 | 1.58543 | 0.00455697 | 4.26375e-06 | 1.63026e-06 | 1(Win) | true |
| simdjson (ondemand) | 2081.01 | 0.138498 | 7722.42ms | 124597 | 80 | 500321 | 57099.8 | 0.174451 | 2.38633 | 9.50969 | 1.74541 | 0.00670171 | 3.51132e-06 | 6.01941e-07 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1093.12 | 0.0305754 | 4608.47ms | 94653 | 2560 | 1.63199e+06 | 82578.6 | 0.0637057 | 4.61064 | 20.7604 | 4.30951 | 0.0109476 | 2.05603e-05 | 1.28966e-05 | 1(Win) | true |
| simdjson (ondemand) | 679.057 | 0.13184 | 7160.4ms | 94653 | 80 | 2.45719e+06 | 132932 | 0.0607731 | 7.29754 | 34.634 | 7.19813 | 0.0127404 | 4.70138e-05 | 1.74321e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1385.53 | 0.0644037 | 4348.53ms | 94653 | 1280 | 2.25358e+06 | 65150.8 | 0.103635 | 3.63752 | 16.9724 | 3.44473 | 0.00795498 | 1.81749e-05 | 9.2608e-06 | 1(Win) | true |
| simdjson (ondemand) | 792.671 | 0.188912 | 7001.63ms | 94653 | 80 | 3.70246e+06 | 113878 | 0.285529 | 6.2564 | 30.8917 | 6.3452 | 0.0101325 | 1.70359e-05 | 4.62215e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1408.19 | 0.0574984 | 4830.97ms | 124597 | 640 | 1.50654e+06 | 84381.1 | 0.0236835 | 3.5346 | 16.225 | 3.32517 | 0.0080024 | 8.64036e-06 | 2.2322e-06 | 1(Win) | true |
| simdjson (ondemand) | 895.964 | 0.075722 | 7154.36ms | 124597 | 320 | 3.22722e+06 | 132622 | 0.105125 | 5.5341 | 26.3714 | 5.4258 | 0.0102921 | 1.97386e-05 | 9.00403e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1788.68 | 0.0398014 | 4442.78ms | 124597 | 2560 | 1.78973e+06 | 66431.8 | 0.0593653 | 2.78283 | 13.3495 | 2.66793 | 0.00601112 | 1.79924e-05 | 1.05747e-05 | 1(Win) | true |
| simdjson (ondemand) | 1028.25 | 0.0852413 | 7033.01ms | 124597 | 320 | 3.10506e+06 | 115561 | 0.0533013 | 4.84349 | 23.5244 | 4.77577 | 0.00805091 | 6.99756e-06 | 2.43284e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2443.4 | 0.0243724 | 4456.78ms | 94653 | 4890 | 396446 | 36943.7 | 0.0464643 | 2.03193 | 9.71666 | 1.80391 | 0.00549808 | 6.58956e-06 | 2.03088e-06 | 1(Win) | true |
| simdjson (ondemand) | 1785.72 | 0.0241841 | 5923.67ms | 94653 | 2560 | 382595 | 50549.9 | 0.0964272 | 2.77833 | 10.7881 | 2.0203 | 0.00797034 | 6.35545e-06 | 1.96441e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3289.49 | 0.0864918 | 4025.93ms | 94653 | 640 | 360530 | 27441.4 | 0.0531529 | 1.51056 | 7.86955 | 1.37294 | 0.0029766 | 5.87673e-06 | 1.88187e-06 | 1(Win) | true |
| simdjson (ondemand) | 2180.74 | 0.0621138 | 5385.07ms | 94653 | 1280 | 846151 | 41393.4 | 0.0579119 | 2.27542 | 8.9629 | 1.59505 | 0.00648571 | 5.82721e-06 | 1.17204e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3059.07 | 0.0505402 | 4623.92ms | 124597 | 1280 | 493310 | 38843.5 | 0.00774885 | 1.62526 | 7.72989 | 1.38597 | 0.00456485 | 1.36064e-05 | 4.27002e-06 | 1(Win) | true |
| simdjson (ondemand) | 2412.64 | 0.0372972 | 5691.45ms | 124597 | 1280 | 431909 | 49251 | 0.200708 | 2.06086 | 8.24847 | 1.49154 | 0.00581905 | 4.20104e-06 | 1.14118e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4087.6 | 0.0909183 | 4174.06ms | 124597 | 1280 | 894110 | 29069.6 | 0.00249126 | 1.22052 | 6.322 | 1.05704 | 0.00252349 | 5.67454e-06 | 2.02528e-06 | 1(Win) | true |
| simdjson (ondemand) | 2920.98 | 0.0544027 | 5311.97ms | 124597 | 640 | 313458 | 40679.8 | 0.0911782 | 1.69968 | 6.86412 | 1.16912 | 0.00487842 | 6.52102e-06 | 1.99393e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1775.25 | 0.0362751 | 5841.24ms | 94653 | 4890 | 1.6637e+06 | 50848 | 0.112731 | 2.80601 | 12.8149 | 2.60478 | 0.00739477 | 6.43833e-06 | 1.6744e-06 | 1(Win) | true |
| simdjson (ondemand) | 1495.41 | 0.0781184 | 6776.91ms | 94653 | 1280 | 2.84621e+06 | 60363.6 | 0.147908 | 3.31739 | 13.4374 | 2.55795 | 0.00869668 | 6.42974e-06 | 1.22982e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2109.57 | 0.0448546 | 5548.71ms | 94653 | 2560 | 943052 | 42789.8 | 0.0223673 | 2.35729 | 10.9676 | 2.17296 | 0.0063703 | 9.29382e-06 | 3.63581e-06 | 1(Win) | true |
| simdjson (ondemand) | 1724.38 | 0.0260171 | 6510.15ms | 94653 | 4890 | 907047 | 52348.1 | 0.0495817 | 2.87855 | 11.618 | 2.13353 | 0.00865052 | 1.00269e-05 | 3.50219e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2291.35 | 0.0673958 | 5945.98ms | 124597 | 1280 | 1.56354e+06 | 51858.1 | 0.0403884 | 2.16473 | 10.1287 | 2.00124 | 0.00564417 | 9.7251e-06 | 4.16969e-06 | 1(Win) | true |
| simdjson (ondemand) | 1998.21 | 0.0967204 | 6687.79ms | 124597 | 160 | 529287 | 59465.8 | 0.0260586 | 2.4862 | 10.2724 | 1.90024 | 0.00654284 | 3.26051e-06 | 4.01294e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2743.77 | 0.0309831 | 5590.3ms | 124597 | 4890 | 880398 | 43307.2 | 0.0144702 | 1.81146 | 8.72567 | 1.67389 | 0.00493417 | 3.5025e-06 | 6.89339e-07 | 1(Win) | true |
| simdjson (ondemand) | 2329.69 | 0.0972401 | 6397.75ms | 124597 | 320 | 787157 | 51004.7 | 0.0118541 | 2.14105 | 8.89001 | 1.57874 | 0.00630518 | 3.18527e-06 | 3.0097e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 773.925 | 0.0617907 | 8043.96ms | 2090234 | 30 | 7.59905e+07 | 2.57571e+06 | 0.134129 | 6.40284 | 30.1036 | 5.62558 | 0.0235512 | 0.104312 | 0.000259668 | 1(Win) | true |
| Jsonifier (generic) | 684.579 | 0.393005 | 4369.16ms | 2090234 | 80 | 1.04768e+10 | 2.91187e+06 | 0.0580132 | 7.24058 | 31.3351 | 6.47344 | 0.0272532 | 0.104814 | 0.000478385 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 911.188 | 0.307891 | 8052.82ms | 2090234 | 160 | 7.25919e+09 | 2.1877e+06 | 0.213699 | 5.5066 | 24.7775 | 4.35844 | 0.0225894 | 0.078938 | 0.000903042 | 1(Win) | true |
| Jsonifier (generic) | 793.282 | 0.314259 | 4377.88ms | 2090234 | 80 | 4.98884e+09 | 2.51285e+06 | 0.214687 | 6.24482 | 26.0209 | 5.20889 | 0.0261663 | 0.0789238 | 0.000220543 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1811.75 | 0.125102 | 4185.04ms | 5212421 | 30 | 3.53453e+08 | 2.74373e+06 | 0.0499727 | 2.77671 | 12.8776 | 2.29052 | 0.0104701 | 0.0607789 | 0.00161821 | 1(Win) | true |
| Jsonifier (generic) | 1701.63 | 0.437362 | 4380.97ms | 5212421 | 80 | 1.30594e+10 | 2.92129e+06 | 0.0875493 | 2.92112 | 13.3598 | 2.63556 | 0.0102081 | 0.0621278 | 0.00188325 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2070.6 | 0.310643 | 4216.37ms | 5212421 | 80 | 4.44936e+09 | 2.40073e+06 | 0.285591 | 2.39319 | 10.7435 | 1.78281 | 0.0101044 | 0.0505892 | 0.00077494 | 1(Win) | true |
| Jsonifier (generic) | 1985.07 | 0.795286 | 4377.04ms | 5212421 | 30 | 1.18986e+10 | 2.50417e+06 | 0.187643 | 2.53169 | 11.2426 | 2.13116 | 0.00983219 | 0.0519221 | 0.00169159 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 699.404 | 0.048734 | 4312.02ms | 2090234 | 40 | 7.71717e+07 | 2.85014e+06 | 0.907688 | 7.08336 | 34.4212 | 6.58507 | 0.0235938 | 0.179178 | 0.00136692 | 1(Win) | true |
| Jsonifier (generic) | 647.851 | 0.104986 | 4650.54ms | 2090234 | 30 | 3.13058e+08 | 3.07694e+06 | 0.537938 | 7.611 | 34.2339 | 7.11821 | 0.0270102 | 0.155356 | 0.000910345 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 802.498 | 0.428442 | 4403.49ms | 2090234 | 80 | 9.061e+09 | 2.484e+06 | 0.366841 | 6.17667 | 29.0971 | 5.3184 | 0.0225543 | 0.153565 | 0.00175639 | 1(Win) | true |
| Jsonifier (generic) | 735.427 | 0.487722 | 4656.29ms | 2090234 | 80 | 1.39812e+10 | 2.71054e+06 | 0.0590904 | 6.70458 | 28.9026 | 5.85014 | 0.0260806 | 0.129791 | 0.00111028 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1545.7 | 0.106199 | 4877.55ms | 5212421 | 30 | 3.49936e+08 | 3.21599e+06 | 0.0618368 | 3.19641 | 14.5332 | 2.89595 | 0.0101384 | 0.100257 | 0.00248952 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1531.32 | 0.48362 | 4895.83ms | 5212421 | 40 | 9.85863e+09 | 3.24619e+06 | 0.353343 | 3.23445 | 14.6086 | 2.67522 | 0.0105504 | 0.120034 | 0.00352974 | 1(Tie) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1766.03 | 0.17844 | 4947.09ms | 5212421 | 80 | 2.01818e+09 | 2.81477e+06 | 0.367073 | 2.80566 | 12.4755 | 2.16767 | 0.0101147 | 0.109773 | 0.00123657 | 1(Win) | true |
| Jsonifier (generic) | 1743.98 | 0.323025 | 4934.92ms | 5212421 | 80 | 6.78202e+09 | 2.85035e+06 | 0.182608 | 2.82831 | 12.3972 | 2.38772 | 0.00978701 | 0.0912149 | 0.00277781 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6993.92 | 0.0852998 | 7585.36ms | 2090234 | 160 | 9.45725e+06 | 285019 | 0.0340804 | 0.709077 | 3.66626 | 0.418408 | 0.00243804 | 0.0489405 | 1.16016e-06 | 1(Win) | true |
| Jsonifier (generic) | 6775.35 | 0.575569 | 7699.91ms | 2090234 | 640 | 1.83528e+09 | 294214 | 0.426941 | 0.731396 | 3.34731 | 0.513237 | 0.00613334 | 0.0504764 | 4.42684e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7198.21 | 0.144741 | 7467ms | 2090234 | 80 | 1.28532e+07 | 276930 | 0.0418466 | 0.705095 | 3.66618 | 0.418391 | 0.00237271 | 0.0488814 | 5.54364e-06 | 1(Win) | true |
| Jsonifier (generic) | 6825.98 | 0.155657 | 7773ms | 2090234 | 80 | 1.65305e+07 | 292032 | 0.157363 | 0.725938 | 3.34723 | 0.513221 | 0.0061442 | 0.0504274 | 2.88843e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10917.7 | 0.240602 | 5927.64ms | 5212421 | 40 | 4.80039e+07 | 455311 | 0.00355239 | 0.452143 | 1.96418 | 0.225702 | 0.00210915 | 0.0394398 | 9.96658e-06 | 1(Win) | true |
| simdjson (ondemand) | 9331.33 | 0.48548 | 6867.4ms | 5212421 | 320 | 2.14034e+09 | 532716 | 0.136344 | 0.53643 | 2.27765 | 0.202787 | 0.00216378 | 0.039493 | 1.79361e-05 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10914.9 | 0.116968 | 5935.03ms | 5212421 | 80 | 2.27019e+07 | 455426 | 0.156433 | 0.453417 | 1.96415 | 0.225696 | 0.00211994 | 0.0394093 | 9.94499e-06 | 1(Win) | true |
| simdjson (ondemand) | 9422.04 | 0.390081 | 6815.63ms | 5212421 | 640 | 2.71068e+09 | 527588 | 0.0193595 | 0.533712 | 2.27762 | 0.20278 | 0.00209686 | 0.0394696 | 5.7399e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5544.79 | 0.14131 | 4688.04ms | 2090234 | 30 | 7.74259e+06 | 359509 | 0.0254449 | 0.910944 | 5.10596 | 0.73834 | 0.0025531 | 0.0738796 | 4.05058e-06 | 1(Win) | true |
| Jsonifier (generic) | 5401.8 | 0.0914547 | 4836.38ms | 2090234 | 160 | 1.82241e+07 | 369026 | 0.239356 | 0.934667 | 4.78712 | 0.833192 | 0.00612436 | 0.075491 | 2.61633e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5588.48 | 0.0843153 | 4681.39ms | 2090234 | 40 | 3.61806e+06 | 356699 | 0.358774 | 0.903929 | 5.10588 | 0.738323 | 0.0023812 | 0.073895 | 6.78154e-06 | 1(Win) | true |
| Jsonifier (generic) | 5396.21 | 0.0700325 | 4832.9ms | 2090234 | 320 | 2.14172e+07 | 369408 | 0.0968712 | 0.935571 | 4.78705 | 0.833174 | 0.00614336 | 0.0754462 | 3.01701e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8649.63 | 0.634452 | 7431.98ms | 5212421 | 320 | 4.25433e+09 | 574701 | 0.0506193 | 0.58175 | 2.54156 | 0.354008 | 0.00211209 | 0.0591009 | 7.19915e-06 | 1(Win) | true |
| simdjson (ondemand) | 7566.2 | 0.0900223 | 4225.24ms | 5212421 | 160 | 5.59685e+07 | 656994 | 0.0177002 | 0.654972 | 2.85498 | 0.331083 | 0.00211153 | 0.0591816 | 1.43875e-05 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8534.47 | 0.127734 | 7560.79ms | 5212421 | 40 | 2.2141e+07 | 582456 | 0.0854069 | 0.580345 | 2.54153 | 0.354001 | 0.00210578 | 0.0590741 | 1.65662e-05 | 1(Win) | true |
| simdjson (ondemand) | 7533.35 | 0.0491085 | 4234.38ms | 5212421 | 80 | 8.40051e+06 | 659859 | 0.0907173 | 0.657645 | 2.85495 | 0.331076 | 0.00212876 | 0.0591825 | 4.10318e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1281.4 | 0.301109 | 4894ms | 500299 | 640 | 8.04484e+08 | 372344 | 0.216588 | 3.87788 | 17.0039 | 3.32681 | 0.0165225 | 0.0212149 | 2.73524e-05 | 1(Win) | true |
| simdjson (ondemand) | 1156.72 | 0.351962 | 5353.55ms | 500299 | 320 | 6.74441e+08 | 412478 | 0.0347344 | 4.29971 | 17.4674 | 2.95223 | 0.0251944 | 0.0227085 | 2.52162e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1456.31 | 0.285278 | 4751ms | 500299 | 640 | 5.59069e+08 | 327624 | 0.0214234 | 3.41104 | 15.8764 | 3.05297 | 0.0110175 | 0.0171133 | 1.94228e-05 | 1(Win) | true |
| simdjson (ondemand) | 1292.5 | 0.20894 | 5243.27ms | 500299 | 640 | 3.80736e+08 | 369147 | 0.21346 | 3.82784 | 16.3489 | 2.68077 | 0.0199771 | 0.01812 | 8.65732e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2644.76 | 0.19386 | 5473.07ms | 1151920 | 30 | 1.94522e+07 | 415371 | 0.263781 | 1.87813 | 8.07613 | 1.4772 | 0.00957326 | 0.0365726 | 2.3497e-05 | 1(Win) | true |
| simdjson (ondemand) | 2408.33 | 0.291896 | 5920.53ms | 1151920 | 640 | 1.13462e+09 | 456149 | 0.226152 | 2.05906 | 8.35258 | 1.316 | 0.0115787 | 0.0389386 | 2.05486e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2936.68 | 0.230623 | 5337.52ms | 1151920 | 40 | 2.97711e+07 | 374081 | 0.0827745 | 1.68071 | 7.58747 | 1.35862 | 0.00711458 | 0.033228 | 2.93423e-05 | 1(Win) | true |
| simdjson (ondemand) | 2681.92 | 0.231702 | 5765.87ms | 1151920 | 640 | 5.76489e+08 | 409615 | 0.231801 | 1.849 | 7.86568 | 1.19789 | 0.00935082 | 0.0349549 | 2.25303e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 640.93 | 0.0952514 | 4754.05ms | 500299 | 80 | 4.02227e+07 | 744422 | 0.220205 | 7.72587 | 36.2472 | 7.67008 | 0.0227138 | 0.0240073 | 3.50291e-05 | 1(Win) | true |
| simdjson (ondemand) | 398.88 | 0.11269 | 7587.26ms | 500299 | 40 | 7.2679e+07 | 1.19616e+06 | 0.346995 | 12.419 | 63.7134 | 13.1227 | 0.038439 | 0.0359493 | 4.40237e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 687.322 | 0.222523 | 4655.77ms | 500299 | 30 | 7.15831e+07 | 694175 | 0.261797 | 7.23932 | 35.1186 | 7.39725 | 0.0168438 | 0.0184748 | 2.61177e-05 | 1(Win) | true |
| simdjson (ondemand) | 416.248 | 0.223082 | 7485.21ms | 500299 | 160 | 1.04618e+09 | 1.14625e+06 | 0.429049 | 11.9222 | 62.5988 | 12.8535 | 0.033393 | 0.0260236 | 1.87638e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1391.45 | 0.19417 | 5062.56ms | 1151920 | 40 | 9.40004e+07 | 789503 | 0.294288 | 3.62249 | 16.4692 | 3.39266 | 0.0126793 | 0.0415435 | 4.26245e-05 | 1(Win) | true |
| simdjson (ondemand) | 898.935 | 0.0929306 | 7777.62ms | 1151920 | 30 | 3.86925e+07 | 1.22206e+06 | 0.0144476 | 5.6155 | 28.4002 | 5.72485 | 0.0170595 | 0.0810935 | 1.69572e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1488.64 | 0.181479 | 4954.76ms | 1151920 | 40 | 7.17425e+07 | 737958 | 0.00215351 | 3.37783 | 15.9779 | 3.27398 | 0.00957975 | 0.0366726 | 1.30651e-05 | 1(Win) | true |
| simdjson (ondemand) | 935.818 | 0.0554949 | 7742.98ms | 1151920 | 80 | 3.39514e+07 | 1.1739e+06 | 0.0682615 | 5.39695 | 27.9121 | 5.60705 | 0.0147543 | 0.0708639 | 2.09216e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5302.84 | 0.0431097 | 5003.13ms | 500299 | 640 | 962879 | 89974.9 | 0.00573912 | 0.953096 | 5.27646 | 0.919542 | 0.000972166 | 6.44583e-05 | 6.42116e-06 | 1(Win) | true |
| simdjson (ondemand) | 4981.04 | 0.040379 | 5283.03ms | 500299 | 1280 | 1.91488e+06 | 95787.7 | 0.0707876 | 1.01263 | 5.65296 | 0.729412 | 0.00130472 | 3.89236e-05 | 1.03469e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5343.93 | 0.0533269 | 4965.74ms | 500299 | 1280 | 2.90162e+06 | 89283.1 | 0.126003 | 0.945423 | 5.2509 | 0.913252 | 0.000935858 | 4.24012e-05 | 5.39209e-06 | 1(Win) | true |
| simdjson (ondemand) | 5019.49 | 0.0550071 | 5277.25ms | 500299 | 640 | 1.74967e+06 | 95053.9 | 0.0995607 | 1.00495 | 5.6274 | 0.723102 | 0.00128484 | 1.93041e-05 | 7.63606e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8676.09 | 0.184494 | 6950.83ms | 1151920 | 160 | 8.73133e+06 | 126619 | 0.100442 | 0.570782 | 2.9447 | 0.420283 | 0.000722191 | 0.0090843 | 4.99167e-06 | 1(Win) | true |
| simdjson (ondemand) | 8163.57 | 0.104849 | 7340.48ms | 1151920 | 160 | 3.18516e+06 | 134568 | 0.144769 | 0.611936 | 3.21865 | 0.349885 | 0.000924093 | 0.00794564 | 1.99124e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8644.52 | 0.106964 | 6892.18ms | 1151920 | 640 | 1.18255e+07 | 127081 | 0.0331135 | 0.574377 | 2.93358 | 0.417552 | 0.000967702 | 0.00804711 | 2.30593e-06 | 1(Win) | true |
| simdjson (ondemand) | 8131.45 | 0.434898 | 7284.2ms | 1151920 | 1280 | 4.41869e+08 | 135100 | 0.030678 | 0.611605 | 3.20755 | 0.347144 | 0.000921405 | 0.00742136 | 1.56329e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2956.49 | 0.213281 | 4363.25ms | 500299 | 80 | 9.47768e+06 | 161382 | 0.227657 | 1.7084 | 9.72841 | 1.96237 | 0.00198489 | 6.94085e-05 | 2.04877e-06 | 1(Win) | true |
| simdjson (ondemand) | 2783.12 | 0.0528666 | 4537.1ms | 500299 | 640 | 5.25702e+06 | 171435 | 0.0416932 | 1.78401 | 10.2303 | 1.74662 | 0.00254441 | 3.15686e-05 | 1.54907e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2930.71 | 0.16367 | 4361.72ms | 500299 | 160 | 1.13598e+07 | 162801 | 0.0164131 | 1.70219 | 9.70284 | 1.95606 | 0.00195311 | 5.90272e-05 | 2.74836e-06 | 1(Win) | true |
| simdjson (ondemand) | 2837.9 | 0.0545611 | 4517.83ms | 500299 | 320 | 2.69266e+06 | 168125 | 0.0272026 | 1.77908 | 10.2048 | 1.74031 | 0.00253193 | 3.1275e-05 | 1.74708e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5475.02 | 0.18371 | 5362.66ms | 1151920 | 80 | 1.08699e+07 | 200649 | 0.153043 | 0.904116 | 4.88393 | 0.876366 | 0.00133754 | 0.00924819 | 2.49583e-06 | 1(Win) | true |
| simdjson (ondemand) | 5290.16 | 0.0701566 | 5526.56ms | 1151920 | 320 | 6.79195e+06 | 207660 | 0.234797 | 0.943378 | 5.20668 | 0.791675 | 0.00149309 | 0.00808187 | 7.09956e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5437.19 | 0.324301 | 5343.39ms | 1151920 | 1280 | 5.49543e+08 | 202045 | 0.0760566 | 0.911195 | 4.87282 | 0.873626 | 0.00147008 | 0.0083145 | 1.32618e-05 | 1(Win) | true |
| simdjson (ondemand) | 5288.86 | 0.0994951 | 5533.1ms | 1151920 | 80 | 3.41676e+06 | 207711 | 0.168735 | 0.938576 | 5.19558 | 0.788934 | 0.00149199 | 0.00770093 | 9.11522e-07 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.07 | 0.0419538 | 4625.96ms | 56369 | 4890 | 1.28355e+06 | 38617.1 | 0.145254 | 3.57828 | 15.3132 | 3.13666 | 0.00660975 | 5.55172e-05 | 2.83118e-05 | 1(Win) | true |
| simdjson (ondemand) | 1252 | 0.0322313 | 5060.3ms | 56369 | 4890 | 936571 | 42937.6 | 0.0350085 | 3.96223 | 15.8048 | 2.84618 | 0.00898774 | 1.6144e-05 | 3.6061e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1703.18 | 0.0487001 | 4257.39ms | 56369 | 2560 | 604863 | 31563 | 0.0491483 | 2.91536 | 13.1693 | 2.66886 | 0.00533659 | 7.0961e-06 | 9.42451e-07 | 1(Win) | true |
| simdjson (ondemand) | 1506.64 | 0.04893 | 4664.63ms | 56369 | 1280 | 390139 | 35680.4 | 0.00879914 | 3.29215 | 13.6914 | 2.38531 | 0.00687885 | 1.53287e-05 | 4.92015e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2025.91 | 0.038306 | 4730.03ms | 83958 | 4890 | 1.1208e+06 | 39522.3 | 0.261506 | 2.46268 | 10.7025 | 2.11975 | 0.00507993 | 1.23565e-05 | 2.64764e-06 | 1(Win) | true |
| simdjson (ondemand) | 1781.48 | 0.118158 | 5273ms | 83958 | 320 | 902487 | 44945 | 0.00874604 | 2.79987 | 11.0893 | 1.93303 | 0.00715789 | 1.01613e-05 | 4.57818e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2494.17 | 0.119509 | 4317.07ms | 83958 | 320 | 470999 | 32102.3 | 0.0922221 | 1.99955 | 9.26316 | 1.8055 | 0.00387065 | 7.55586e-06 | 2.1216e-06 | 1(Win) | true |
| simdjson (ondemand) | 2070.16 | 0.0419484 | 4982.43ms | 83958 | 1280 | 336943 | 38677.4 | 0.131947 | 2.39948 | 9.65127 | 1.61991 | 0.00740055 | 8.3282e-06 | 1.74939e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 640.761 | 0.0439468 | 4663.62ms | 56369 | 2560 | 3.48004e+06 | 83896.6 | 0.082413 | 7.78764 | 35.2932 | 7.51441 | 0.0119505 | 2.97357e-05 | 8.90477e-06 | 1(Win) | true |
| simdjson (ondemand) | 190.841 | 0.142213 | 7360.38ms | 56369 | 80 | 1.28383e+07 | 281689 | 0.0777169 | 26.0289 | 136.221 | 29.3906 | 0.0354441 | 7.78353e-05 | 2.63886e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 703.877 | 0.0619779 | 4454.32ms | 56369 | 1280 | 2.86795e+06 | 76373.7 | 0.00528167 | 7.07344 | 33.1375 | 7.04029 | 0.0105898 | 2.00132e-05 | 6.80505e-06 | 1(Win) | true |
| simdjson (ondemand) | 195.022 | 0.0512487 | 7299.12ms | 56369 | 640 | 1.2772e+07 | 275649 | 0.11948 | 25.4613 | 134.1 | 28.9259 | 0.0320939 | 2.37553e-05 | 8.37118e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 887.426 | 0.0463936 | 4993.51ms | 83958 | 2560 | 4.48556e+06 | 90225.7 | 0.282179 | 5.63907 | 24.8217 | 5.35797 | 0.00775079 | 2.1416e-05 | 5.18768e-06 | 1(Win) | true |
| simdjson (ondemand) | 284.291 | 0.0588822 | 7388.92ms | 83958 | 640 | 1.76013e+07 | 281643 | 0.0891902 | 17.5629 | 91.6087 | 19.6869 | 0.0237953 | 2.87346e-05 | 1.16688e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 973.098 | 0.304855 | 4834.2ms | 83958 | 40 | 2.51686e+06 | 82282.1 | 0.0906826 | 5.15833 | 23.3892 | 5.04334 | 0.00716787 | 2.8288e-05 | 1.25063e-05 | 1(Win) | true |
| simdjson (ondemand) | 292.644 | 0.0623746 | 7296.68ms | 83958 | 640 | 1.86398e+07 | 273604 | 0.0292319 | 17.1717 | 90.1753 | 19.3733 | 0.0219733 | 4.02173e-05 | 2.10112e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2408.24 | 0.0575603 | 2986.08ms | 56369 | 2560 | 422639 | 22322.4 | 0.0572307 | 2.07939 | 9.97743 | 1.87466 | 0.00309881 | 6.61101e-06 | 7.69206e-07 | 1(Win) | true |
| simdjson (ondemand) | 1938.69 | 0.0694987 | 3530.08ms | 56369 | 1280 | 475363 | 27728.8 | 0.0208987 | 2.57849 | 10.2346 | 1.72571 | 0.00808951 | 7.23469e-06 | 1.55227e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2983.15 | 0.0454503 | 2849.73ms | 56369 | 4890 | 328029 | 18020.4 | 0.104967 | 1.67427 | 8.4092 | 1.53235 | 0.00252032 | 6.48299e-06 | 1.71235e-06 | 1(Win) | true |
| simdjson (ondemand) | 2327.43 | 0.132034 | 3336.9ms | 56369 | 40 | 37201.3 | 23097.5 | 0.0514222 | 2.1348 | 8.67892 | 1.38805 | 0.00649027 | 3.54805e-06 | 4.43506e-07 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3317.66 | 0.06851 | 3153.6ms | 83958 | 1280 | 349928 | 24134.1 | 0.0147915 | 1.50239 | 7.14226 | 1.27765 | 0.00257276 | 7.86293e-06 | 2.78227e-06 | 1(Win) | true |
| simdjson (ondemand) | 2755.85 | 0.159605 | 3729.54ms | 83958 | 80 | 172028 | 29054.1 | 0.0107977 | 1.83662 | 7.34227 | 1.17963 | 0.00577982 | 5.65759e-06 | 2.08438e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4089.85 | 0.17317 | 2991.08ms | 83958 | 1280 | 1.47118e+06 | 19577.4 | 0.444382 | 1.22767 | 6.09769 | 1.04999 | 0.00196764 | 3.8989e-06 | 9.30525e-07 | 1(Win) | true |
| simdjson (ondemand) | 3288.57 | 0.038996 | 3482.41ms | 83958 | 4890 | 440819 | 24347.6 | 0.00316995 | 1.51885 | 6.29661 | 0.952596 | 0.00412828 | 4.34291e-06 | 1.30555e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1795.45 | 0.0554142 | 3737.22ms | 56369 | 2560 | 704721 | 29941.1 | 0.0925115 | 2.78074 | 13.3621 | 2.66663 | 0.0042815 | 9.29284e-06 | 1.94034e-06 | 1(Win) | true |
| simdjson (ondemand) | 1237.33 | 0.102302 | 5099.48ms | 56369 | 640 | 1.26433e+06 | 43446.4 | 0.317582 | 4.05247 | 17.094 | 3.14214 | 0.00930321 | 1.39704e-05 | 3.93612e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2112.09 | 0.160599 | 3599.91ms | 56369 | 320 | 534677 | 25452.3 | 0.0264904 | 2.38564 | 11.7821 | 2.32183 | 0.00413071 | 1.09213e-05 | 2.10665e-06 | 1(Win) | true |
| simdjson (ondemand) | 1356.9 | 0.0447791 | 5012ms | 56369 | 2560 | 805706 | 39618.1 | 0.0562629 | 3.67352 | 15.5095 | 2.79939 | 0.00837376 | 1.13371e-05 | 2.98674e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2469.2 | 0.0627725 | 4005.68ms | 83958 | 1280 | 530350 | 32427 | 0.0795602 | 2.04811 | 9.46479 | 1.8272 | 0.00356599 | 9.76121e-06 | 3.38711e-06 | 1(Win) | true |
| simdjson (ondemand) | 1807.8 | 0.0681433 | 5175.65ms | 83958 | 1280 | 1.16595e+06 | 44290.7 | 0.0390978 | 2.79647 | 11.8098 | 2.1019 | 0.00622194 | 9.24011e-06 | 2.46589e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2878.5 | 0.0602688 | 3825.79ms | 83958 | 2560 | 719479 | 27816.1 | 0.0202054 | 1.75746 | 8.40533 | 1.59601 | 0.00272439 | 5.73669e-06 | 5.76925e-07 | 1(Win) | true |
| simdjson (ondemand) | 2011.55 | 0.0736637 | 5045.85ms | 83958 | 640 | 550239 | 39804.5 | 0.00410584 | 2.51467 | 10.7597 | 1.87426 | 0.00575463 | 4.6154e-06 | 4.28041e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.19 | 0.245457 | 4829.55ms | 53331 | 320 | 3.22172e+06 | 40878.4 | 0.115606 | 4.01993 | 13.8907 | 2.77821 | 0.0124767 | 6.61552e-05 | 1.89266e-05 | 1(Win) | true |
| simdjson (ondemand) | 967.111 | 0.0561884 | 6016.69ms | 53331 | 2560 | 2.23532e+06 | 52590 | 0.0109347 | 5.21244 | 18.3133 | 3.66513 | 0.0203353 | 6.33573e-05 | 1.82528e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1529.16 | 0.0768078 | 4626.75ms | 53331 | 4890 | 3.19134e+06 | 33260.4 | 0.197769 | 3.26683 | 11.712 | 2.28274 | 0.00973284 | 2.26927e-05 | 6.84462e-06 | 1(Win) | true |
| simdjson (ondemand) | 1141.48 | 0.060353 | 5750.86ms | 53331 | 2560 | 1.85125e+06 | 44556.7 | 0.161395 | 4.39101 | 16.1771 | 3.18038 | 0.0170435 | 1.73299e-05 | 4.17499e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1462.69 | 0.0585234 | 4984.66ms | 65103 | 4890 | 3.01763e+06 | 42447.2 | 0.224399 | 3.44564 | 11.8128 | 2.33192 | 0.0113881 | 0.000102066 | 5.71e-05 | 1(Win) | true |
| simdjson (ondemand) | 1175.01 | 0.0420521 | 6064.21ms | 65103 | 4890 | 2.41436e+06 | 52839.6 | 0.173183 | 4.27728 | 15.1963 | 2.99771 | 0.0166097 | 6.08034e-05 | 3.13299e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1790.44 | 0.246412 | 4797.58ms | 65103 | 320 | 2.33646e+06 | 34677 | 0.0819036 | 2.8175 | 10.0317 | 1.92734 | 0.00906002 | 1.79523e-05 | 6.14411e-06 | 1(Win) | true |
| simdjson (ondemand) | 1391.32 | 0.0561214 | 5795.98ms | 65103 | 2560 | 1.60563e+06 | 44624.6 | 0.134669 | 3.6191 | 13.4539 | 2.60343 | 0.013636 | 1.78203e-05 | 5.26209e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 886.26 | 0.0502268 | 6510.01ms | 53331 | 4890 | 4.06273e+06 | 57387.7 | 0.174934 | 5.63355 | 19.7982 | 4.01737 | 0.0175733 | 6.975e-05 | 1.6105e-05 | 1(Win) | true |
| simdjson (ondemand) | 406.576 | 0.0693783 | 6773.15ms | 53331 | 2560 | 1.92824e+07 | 125094 | 0.0475624 | 12.3487 | 40.6694 | 8.54604 | 0.0958473 | 7.98082e-05 | 2.8075e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1048.83 | 0.115626 | 6170.36ms | 53331 | 4890 | 1.53735e+07 | 48492.6 | 0.00505168 | 4.79434 | 17.538 | 3.50452 | 0.0137381 | 3.39815e-05 | 1.07252e-05 | 1(Win) | true |
| simdjson (ondemand) | 443.252 | 0.25531 | 6615.36ms | 53331 | 160 | 1.37314e+07 | 114744 | 0.0778521 | 11.3399 | 38.463 | 8.04715 | 0.0874381 | 1.96884e-05 | 4.57051e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1026.83 | 0.0498136 | 6781.53ms | 65103 | 4890 | 4.43621e+06 | 60464.9 | 0.115027 | 4.9036 | 16.8687 | 3.44076 | 0.0144544 | 5.57462e-05 | 1.50116e-05 | 1(Win) | true |
| simdjson (ondemand) | 516.844 | 0.238691 | 6484.28ms | 65103 | 160 | 1.31545e+07 | 120127 | 0.380174 | 9.63152 | 33.2384 | 6.93743 | 0.0661035 | 5.94251e-05 | 2.19844e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1197.76 | 0.228887 | 6540.77ms | 65103 | 320 | 4.50456e+06 | 51835.8 | 0.249163 | 4.21858 | 15.03 | 3.0244 | 0.011807 | 1.76163e-05 | 6.96012e-06 | 1(Win) | true |
| simdjson (ondemand) | 561.363 | 0.230342 | 6351.44ms | 65103 | 160 | 1.03844e+07 | 110600 | 0.23958 | 8.83459 | 31.4321 | 6.52914 | 0.0593952 | 5.3377e-05 | 3.84007e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8043.42 | 0.182007 | 1380.79ms | 53331 | 1280 | 169538 | 6323.24 | 0.0993484 | 0.627578 | 3.04168 | 0.463914 | 0.000684361 | 7.57357e-06 | 8.49647e-07 | 1(Win) | true |
| simdjson (ondemand) | 6571.09 | 0.0535175 | 1524.86ms | 53331 | 2560 | 43925.3 | 7740.02 | 0.174576 | 0.759141 | 3.41301 | 0.428325 | 0.000957566 | 1.54475e-05 | 5.74244e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8489.73 | 0.094238 | 1376.57ms | 53331 | 1280 | 40797.5 | 5990.81 | 0.0960725 | 0.589989 | 2.88946 | 0.428606 | 0.000749242 | 3.20815e-06 | 5.27367e-07 | 1(Win) | true |
| simdjson (ondemand) | 7000.38 | 0.0992893 | 1491.47ms | 53331 | 40 | 2081.52 | 7265.38 | 0.119545 | 0.726787 | 3.27556 | 0.395549 | 0.00108145 | 1.17193e-05 | 9.84418e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8667.22 | 0.0786801 | 1467.7ms | 65103 | 1280 | 40661.3 | 7163.43 | 0.0903185 | 0.58103 | 2.81879 | 0.390566 | 0.000639731 | 3.54006e-06 | 4.44008e-07 | 1(Win) | true |
| simdjson (ondemand) | 7631.67 | 0.0568979 | 1554.57ms | 65103 | 4890 | 104777 | 8135.45 | 0.00449178 | 0.665131 | 3.06232 | 0.362364 | 0.000778857 | 3.48041e-06 | 2.79563e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9226.81 | 0.0686195 | 1442.6ms | 65103 | 1280 | 27290.1 | 6728.99 | 0.036582 | 0.548269 | 2.6941 | 0.361642 | 0.000706573 | 2.91605e-06 | 2.40004e-07 | 1(Win) | true |
| simdjson (ondemand) | 7990.75 | 0.107144 | 1529.47ms | 65103 | 640 | 44354.7 | 7769.87 | 0.0903341 | 0.635805 | 2.94989 | 0.335545 | 0.00077723 | 3.07206e-06 | 0 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5459.33 | 0.0948695 | 1685.64ms | 53331 | 1280 | 99987 | 9316.24 | 0.175994 | 0.914045 | 4.35887 | 0.768428 | 0.0017274 | 5.36156e-06 | 1.15728e-06 | 1(Win) | true |
| simdjson (ondemand) | 3783.77 | 0.125704 | 2096.36ms | 53331 | 320 | 91360.7 | 13441.7 | 0.0305346 | 1.31367 | 5.94157 | 0.98275 | 0.00230254 | 5.39086e-06 | 4.68771e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5732.01 | 0.11942 | 1663.16ms | 53331 | 640 | 71859.3 | 8873.05 | 0.0753021 | 0.874189 | 4.20665 | 0.73312 | 0.00176205 | 3.98455e-06 | 6.73858e-07 | 1(Win) | true |
| simdjson (ondemand) | 3910.38 | 0.0737398 | 2065.72ms | 53331 | 1280 | 117743 | 13006.5 | 0.040078 | 1.27497 | 5.80413 | 0.949973 | 0.00233883 | 6.15261e-06 | 1.06938e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6208.61 | 0.0503253 | 1751.28ms | 65103 | 4890 | 123850 | 10000.1 | 0.0224125 | 0.80493 | 3.90497 | 0.647175 | 0.00138854 | 3.98613e-06 | 5.43421e-07 | 1(Win) | true |
| simdjson (ondemand) | 4443.77 | 0.0374245 | 2151.73ms | 65103 | 4890 | 133697 | 13971.7 | 0.105032 | 1.12174 | 5.13618 | 0.81709 | 0.00199309 | 4.25941e-06 | 5.90538e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6447.44 | 0.0593463 | 1735.16ms | 65103 | 2560 | 83609.4 | 9629.72 | 0.0211995 | 0.773901 | 3.78027 | 0.618251 | 0.00138186 | 2.82005e-06 | 3.54006e-07 | 1(Win) | true |
| simdjson (ondemand) | 4566.54 | 0.101979 | 2123.52ms | 65103 | 640 | 123035 | 13596.1 | 0.0828022 | 1.09013 | 5.02376 | 0.790271 | 0.0020583 | 4.99209e-06 | 1.24802e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1324.39 | 0.067329 | 1596.64ms | 11812 | 2560 | 83957.7 | 8505.66 | 0.0189085 | 3.77276 | 17.9512 | 3.51579 | 0.0049639 | 2.85396e-05 | 4.06763e-06 | 1(Win) | true |
| simdjson (ondemand) | 1048.33 | 0.0351328 | 1823.34ms | 11812 | 4890 | 69692 | 10745.4 | 0.00830316 | 4.8403 | 19.3346 | 3.64824 | 0.00899231 | 5.66995e-05 | 2.66444e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1457.97 | 0.0570631 | 1574.76ms | 11812 | 4890 | 95053.3 | 7726.34 | 0.231021 | 3.48515 | 16.9817 | 3.29258 | 0.00426243 | 5.82403e-05 | 2.41168e-05 | 1(Win) | true |
| simdjson (ondemand) | 1124.17 | 0.0494938 | 1808.45ms | 11812 | 2560 | 62968.9 | 10020.6 | 0.0847687 | 4.50373 | 18.3226 | 3.41822 | 0.00809492 | 1.86185e-05 | 1.15746e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2608.01 | 0.0793316 | 1677.37ms | 25388 | 2560 | 138858 | 9283.65 | 0.0245788 | 1.9422 | 9.15671 | 1.68682 | 0.00256054 | 1.52477e-05 | 1.95405e-06 | 1(Win) | true |
| simdjson (ondemand) | 2141.59 | 0.053763 | 1873.89ms | 25388 | 2560 | 94578.3 | 11305.6 | 0.10987 | 2.36822 | 9.74183 | 1.73667 | 0.00386225 | 1.79095e-05 | 4.18505e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2828.95 | 0.106491 | 1654.19ms | 25388 | 1280 | 106327 | 8558.63 | 0.0473257 | 1.79486 | 8.64869 | 1.57118 | 0.00222986 | 1.0955e-05 | 1.41553e-06 | 1(Win) | true |
| simdjson (ondemand) | 2300.75 | 0.0307412 | 1853.46ms | 25388 | 4890 | 51176.3 | 10523.5 | 0.065126 | 2.20529 | 9.25453 | 1.62597 | 0.00341419 | 8.53824e-06 | 1.25657e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 761.396 | 0.044257 | 2225.86ms | 11812 | 4890 | 209652 | 14794.9 | 0.0238186 | 6.65537 | 29.9117 | 6.25584 | 0.0147482 | 3.35349e-05 | 6.05949e-06 | 1(Win) | true |
| simdjson (ondemand) | 639.603 | 0.0959009 | 2505.78ms | 11812 | 640 | 182579 | 17612.2 | 0.0256281 | 7.9195 | 31.9371 | 6.27701 | 0.0135522 | 2.46042e-05 | 4.76211e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 800.93 | 0.066131 | 2208.97ms | 11812 | 2560 | 221466 | 14064.6 | 0.0789894 | 6.32899 | 28.8842 | 6.021 | 0.014339 | 7.51685e-05 | 3.59804e-05 | 1(Win) | true |
| simdjson (ondemand) | 664.885 | 0.0583 | 2497.21ms | 11812 | 1280 | 124882 | 16942.5 | 0.0206624 | 7.61427 | 30.8867 | 6.03962 | 0.0137108 | 3.25411e-05 | 4.4314e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.52 | 0.131043 | 2337.74ms | 25388 | 640 | 277569 | 15892.1 | 0.0234547 | 3.32519 | 14.7974 | 2.9964 | 0.00689468 | 1.04011e-05 | 9.23172e-07 | 1(Win) | true |
| simdjson (ondemand) | 1335.89 | 0.0993507 | 2558.89ms | 25388 | 4890 | 1.5855e+06 | 18124.1 | 0.00935428 | 3.78773 | 15.4212 | 2.9187 | 0.00712512 | 1.65449e-05 | 3.665e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1589.97 | 0.167582 | 2322.33ms | 25388 | 1280 | 833567 | 15227.8 | 0.0308191 | 3.18676 | 14.2924 | 2.88156 | 0.00666998 | 1.06473e-05 | 2.03098e-06 | 1(Win) | true |
| simdjson (ondemand) | 1383.7 | 0.0326961 | 2541.77ms | 25388 | 4890 | 160057 | 17497.9 | 0.187045 | 3.66012 | 14.9325 | 2.80826 | 0.00733492 | 1.11722e-05 | 1.11964e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2388.93 | 0.107635 | 1215.5ms | 11812 | 640 | 16486.4 | 4715.41 | 0.0928933 | 2.13559 | 10.7854 | 2.03598 | 0.00288769 | 1.69319e-05 | 2.51333e-06 | 1(Win) | true |
| simdjson (ondemand) | 2005.56 | 0.0351408 | 1304.94ms | 11812 | 4890 | 19050.6 | 5616.79 | 0.0819063 | 2.53913 | 11.3138 | 1.93295 | 0.00399189 | 1.49063e-05 | 1.61009e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2485.15 | 0.0558397 | 1204.42ms | 11812 | 4890 | 31328.4 | 4532.85 | 0.126393 | 2.05227 | 10.6023 | 1.99094 | 0.00243586 | 2.51382e-05 | 1.59278e-06 | 1(Win) | true |
| simdjson (ondemand) | 2056.82 | 0.0387952 | 1297.57ms | 11812 | 4890 | 22075.8 | 5476.79 | 0.129397 | 2.47634 | 11.1271 | 1.8869 | 0.00373706 | 1.46986e-05 | 1.69666e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4331.31 | 0.0713726 | 1301.34ms | 25388 | 2560 | 40749.4 | 5589.97 | 0.0186474 | 1.176 | 5.80833 | 0.996888 | 0.00161592 | 8.43164e-06 | 7.6931e-07 | 1(Win) | true |
| simdjson (ondemand) | 3808.85 | 0.0378391 | 1373.24ms | 25388 | 4890 | 28291.7 | 6356.74 | 0.0518996 | 1.33499 | 5.97562 | 0.930913 | 0.00162695 | 8.56241e-06 | 1.11158e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4457.52 | 0.0721404 | 1290.84ms | 25388 | 2560 | 39306.9 | 5431.7 | 0.0147018 | 1.14196 | 5.72337 | 0.975934 | 0.00139308 | 8.70859e-06 | 9.53945e-07 | 1(Win) | true |
| simdjson (ondemand) | 3886.43 | 0.0747094 | 1368.88ms | 25388 | 1280 | 27727.8 | 6229.85 | 0.0743196 | 1.31055 | 5.88873 | 0.909485 | 0.00160875 | 5.50826e-06 | 3.07724e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1687.68 | 0.138977 | 1408.94ms | 11812 | 640 | 55071.8 | 6674.71 | 0.0240121 | 3.00986 | 13.9611 | 2.78539 | 0.00702133 | 1.44186e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (ondemand) | 1587.79 | 0.0344673 | 1473.37ms | 11812 | 4890 | 29240.4 | 7094.63 | 0.0395227 | 3.20216 | 13.789 | 2.4415 | 0.00624896 | 2.15718e-05 | 3.34137e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1724.13 | 0.0781417 | 1401.71ms | 11812 | 2560 | 66728.5 | 6533.61 | 0.107709 | 2.95037 | 13.7779 | 2.74035 | 0.00676047 | 2.87049e-05 | 3.93535e-06 | 1(Win) | true |
| simdjson (ondemand) | 1626.03 | 0.0355421 | 1440.44ms | 11812 | 4890 | 29647.1 | 6927.79 | 0.0493828 | 3.12777 | 13.6024 | 2.39545 | 0.00592355 | 2.22816e-05 | 3.93001e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3339.68 | 0.174925 | 1461.9ms | 25388 | 320 | 51463.8 | 7249.77 | 0.0191853 | 1.5228 | 7.26635 | 1.36179 | 0.00360296 | 1.0955e-05 | 3.69269e-07 | 1(Win) | true |
| simdjson (ondemand) | 3091.46 | 0.0362519 | 1525.87ms | 25388 | 4890 | 39418.6 | 7831.85 | 0.113702 | 1.64342 | 7.12723 | 1.16752 | 0.00297518 | 1.58521e-05 | 5.74318e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3394.14 | 0.0569491 | 1464.21ms | 25388 | 2560 | 42248.6 | 7133.44 | 0.0871328 | 1.49877 | 7.18131 | 1.34083 | 0.00346673 | 1.19551e-05 | 1.24628e-06 | 1(Win) | true |
| simdjson (ondemand) | 3136.44 | 0.0384554 | 1519.4ms | 25388 | 4890 | 43092.9 | 7719.54 | 0.176141 | 1.62187 | 7.04037 | 1.14609 | 0.00290175 | 1.76645e-05 | 6.24258e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1575.88 | 0.0312094 | 7307.4ms | 108313 | 2560 | 1.07134e+06 | 65547.7 | 0.0086517 | 3.20829 | 14.1723 | 2.97973 | 0.00384481 | 1.78627e-05 | 9.47413e-06 | 1(Win) | true |
| simdjson (ondemand) | 1489.66 | 0.0379198 | 7686.94ms | 108313 | 2560 | 1.76993e+06 | 69341.3 | 0.0968022 | 3.39095 | 15.2358 | 2.55134 | 0.00617151 | 4.10666e-05 | 2.84837e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1688.34 | 0.0345665 | 7057.22ms | 108313 | 2560 | 1.14497e+06 | 61181.6 | 0.0542684 | 2.99333 | 13.4832 | 2.81819 | 0.0032514 | 3.08099e-05 | 2.14944e-05 | 1(Win) | true |
| simdjson (ondemand) | 1594.2 | 0.0280093 | 7397.77ms | 108313 | 4890 | 1.6106e+06 | 64794.4 | 0.0301947 | 3.16365 | 14.5525 | 2.39062 | 0.00594967 | 6.79316e-06 | 1.31407e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2437.03 | 0.0741497 | 4052.42ms | 183677 | 2560 | 7.27191e+06 | 71877.8 | 0.0955978 | 2.06939 | 8.90855 | 1.80241 | 0.0021937 | 1.4402e-05 | 5.21466e-06 | 1(Win) | true |
| simdjson (ondemand) | 2357.79 | 0.0353869 | 4183.8ms | 183677 | 2560 | 1.7694e+06 | 74293.4 | 0.196767 | 2.11636 | 9.57028 | 1.52683 | 0.0037712 | 6.42475e-06 | 1.98208e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2581.91 | 0.0517246 | 7712.72ms | 183677 | 1280 | 1.57628e+06 | 67844.4 | 0.00503079 | 1.95583 | 8.50173 | 1.70696 | 0.00196371 | 4.60642e-06 | 1.02932e-06 | 1(Win) | true |
| simdjson (ondemand) | 2533.24 | 0.0424731 | 4007.59ms | 183677 | 2560 | 2.20813e+06 | 69147.7 | 0.0199076 | 1.97547 | 9.16416 | 1.43147 | 0.00362106 | 4.03221e-06 | 1.08461e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 579.458 | 0.122401 | 4722.7ms | 108313 | 160 | 7.61747e+06 | 178262 | 0.000543439 | 8.61224 | 38.8859 | 7.96487 | 0.0130023 | 2.44661e-05 | 5.25099e-06 | 1(Win) | true |
| simdjson (ondemand) | 228.398 | 0.0535163 | 5856.63ms | 108313 | 320 | 1.87455e+07 | 452260 | 0.0140377 | 22.1157 | 94.4562 | 20.0596 | 0.0752578 | 2.49855e-05 | 8.62662e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 604.903 | 0.0843578 | 4607.97ms | 108313 | 320 | 6.64034e+06 | 170763 | 0.135108 | 8.34612 | 38.2013 | 7.80569 | 0.0124374 | 2.663e-05 | 1.23196e-05 | 1(Win) | true |
| simdjson (ondemand) | 230.959 | 0.108384 | 5789.2ms | 108313 | 160 | 3.75959e+07 | 447246 | 0.0901947 | 21.8237 | 93.7718 | 19.9012 | 0.0738054 | 2.65434e-05 | 7.09749e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 931.585 | 0.10485 | 4998.44ms | 183677 | 160 | 6.21903e+06 | 188032 | 0.019126 | 5.43266 | 23.8723 | 4.91396 | 0.0060523 | 4.3929e-05 | 2.70516e-05 | 1(Win) | true |
| simdjson (ondemand) | 393.51 | 0.0337876 | 5746.06ms | 183677 | 640 | 1.44775e+07 | 445143 | 0.124857 | 12.8392 | 55.5516 | 11.693 | 0.0421027 | 5.32184e-05 | 2.77151e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 949.286 | 0.0518003 | 4923.93ms | 183677 | 1280 | 1.16947e+07 | 184526 | 0.0870116 | 5.28991 | 23.4668 | 4.8198 | 0.00590566 | 9.82108e-06 | 2.81574e-06 | 1(Win) | true |
| simdjson (ondemand) | 398.438 | 0.0808681 | 5803.66ms | 183677 | 160 | 2.02238e+07 | 439637 | 0.203173 | 12.6705 | 55.1475 | 11.5996 | 0.0410353 | 2.84467e-05 | 6.66932e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4791.3 | 0.0710386 | 2914.73ms | 108313 | 1280 | 300229 | 21558.9 | 0.218065 | 1.04491 | 5.84705 | 0.999594 | 0.00107125 | 9.43446e-06 | 5.40967e-06 | 1(Win) | true |
| simdjson (ondemand) | 4391.83 | 0.0891814 | 3155.22ms | 108313 | 320 | 140789 | 23519.9 | 0.0675284 | 1.15287 | 5.97745 | 0.795907 | 0.00118133 | 1.01846e-05 | 5.39524e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5037.1 | 0.0824139 | 2824.83ms | 108313 | 640 | 182802 | 20506.9 | 0.0636014 | 1.00517 | 5.68321 | 0.95621 | 0.000866615 | 4.12577e-06 | 2.7409e-07 | 1(Win) | true |
| simdjson (ondemand) | 4493.54 | 0.0568615 | 3081.85ms | 108313 | 1280 | 218691 | 22987.5 | 0.132714 | 1.11404 | 5.81482 | 0.752615 | 0.00104717 | 2.87073e-06 | 1.73109e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6838.69 | 0.294681 | 3388.95ms | 183677 | 30 | 170919 | 25614.3 | 0.00767742 | 0.740602 | 3.98108 | 0.612695 | 0.000685987 | 2.8855e-05 | 2.52254e-05 | 1(Win) | true |
| simdjson (ondemand) | 6338.96 | 0.0262962 | 3529.68ms | 183677 | 4890 | 258208 | 27633.6 | 0.111356 | 0.790397 | 4.10306 | 0.491074 | 0.000737935 | 2.10759e-06 | 3.79656e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6933.76 | 0.366753 | 3303.36ms | 183677 | 40 | 343382 | 25263 | 0.0432307 | 0.721315 | 3.8844 | 0.587129 | 0.000565803 | 2.44995e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6486.04 | 0.056246 | 3473.18ms | 183677 | 1280 | 295355 | 27007 | 0.128476 | 0.768487 | 4.00653 | 0.465404 | 0.000651713 | 2.64986e-06 | 5.40181e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3087.35 | 0.0967895 | 4088.87ms | 108313 | 1280 | 1.34232e+06 | 33457.6 | 0.0297046 | 1.61273 | 8.33159 | 1.63928 | 0.00152574 | 3.8589e-06 | 3.7507e-07 | 1(Win) | true |
| simdjson (ondemand) | 2516.2 | 0.0890104 | 4844.03ms | 108313 | 1280 | 1.70908e+06 | 41052.2 | 0.024087 | 1.99377 | 10.0778 | 1.69037 | 0.00203081 | 4.21233e-06 | 8.87186e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3164.72 | 0.0993435 | 4030.03ms | 108313 | 1280 | 1.3458e+06 | 32639.7 | 0.249979 | 1.58377 | 8.16741 | 1.59569 | 0.00131593 | 4.89034e-06 | 1.08915e-06 | 1(Win) | true |
| simdjson (ondemand) | 2574.1 | 0.0459208 | 4778.9ms | 108313 | 2560 | 869302 | 40128.7 | 0.283288 | 1.9589 | 9.91406 | 1.64684 | 0.00196132 | 4.60183e-06 | 1.05308e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4715.92 | 0.10025 | 4472.43ms | 183677 | 1280 | 1.77482e+06 | 37144 | 0.088542 | 1.05517 | 5.45732 | 0.999037 | 0.000894212 | 1.86724e-06 | 3.36018e-07 | 1(Win) | true |
| simdjson (ondemand) | 3861.2 | 0.030767 | 5281ms | 183677 | 4890 | 952674 | 45366.2 | 0.0980471 | 1.29562 | 6.50698 | 1.01547 | 0.00125703 | 4.66165e-06 | 1.75132e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4837.27 | 0.144152 | 4401.15ms | 183677 | 640 | 1.74392e+06 | 36212.2 | 0.0572563 | 1.03503 | 5.36099 | 0.973448 | 0.000791199 | 3.06244e-06 | 1.02081e-07 | 1(Win) | true |
| simdjson (ondemand) | 3934.13 | 0.0725822 | 5227.23ms | 183677 | 640 | 668424 | 44525.2 | 0.142503 | 1.26838 | 6.41092 | 0.989912 | 0.00112859 | 3.24959e-06 | 5.52941e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 561.991 | 0.0976924 | 4672.46ms | 1834197 | 30 | 2.77381e+08 | 3.11255e+06 | 0.199652 | 8.79435 | 34.9351 | 6.31593 | 0.0477325 | 0.139235 | 0.0016891 | 1(Win) | true |
| Jsonifier (generic) | 532.338 | 0.337046 | 4938.24ms | 1834197 | 80 | 9.8126e+09 | 3.28593e+06 | 0.00555482 | 9.2683 | 34.6273 | 7.4284 | 0.0451519 | 0.139577 | 0.0103776 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 617.916 | 0.346787 | 4643.4ms | 1834197 | 80 | 7.70989e+09 | 2.83085e+06 | 0.232314 | 8.16111 | 31.9423 | 5.62034 | 0.0467034 | 0.118619 | 0.00600695 | 1(Win) | true |
| Jsonifier (generic) | 575.352 | 0.516585 | 4917.88ms | 1834197 | 30 | 7.39999e+09 | 3.04027e+06 | 0.0749349 | 8.61209 | 31.6339 | 6.73286 | 0.0441688 | 0.118932 | 0.00973587 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2057.05 | 0.464217 | 5151.53ms | 7351818 | 40 | 1.00138e+10 | 3.40839e+06 | 0.264139 | 2.43431 | 9.48456 | 1.89223 | 0.0136963 | 0.0589892 | 0.00670379 | 1(Win) | true |
| simdjson (ondemand) | 2007.24 | 0.732934 | 5229.55ms | 7351818 | 30 | 1.96627e+10 | 3.49298e+06 | 0.0788611 | 2.46054 | 9.73308 | 1.61403 | 0.0119736 | 0.0589353 | 0.00616361 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2182.89 | 0.275357 | 5200.85ms | 7351818 | 80 | 6.25761e+09 | 3.21191e+06 | 0.633804 | 2.2715 | 8.98671 | 1.44054 | 0.0117466 | 0.0537101 | 0.00391361 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 2176.22 | 0.404425 | 5190ms | 7351818 | 80 | 1.35815e+10 | 3.22175e+06 | 0.782483 | 2.26789 | 8.73844 | 1.71884 | 0.0134152 | 0.0538173 | 0.0060595 | 1(Tie) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 359.197 | 0.314754 | 7341.9ms | 1834197 | 40 | 9.39788e+09 | 4.86983e+06 | 0.123387 | 13.7465 | 60.9527 | 13.6303 | 0.0469546 | 0.345482 | 0.00373271 | 1(Win) | true |
| simdjson (ondemand) | 255.703 | 0.404437 | 4843.15ms | 1834197 | 30 | 2.29639e+10 | 6.84086e+06 | 0.542197 | 19.6729 | 102.32 | 21.208 | 0.0515794 | 0.791515 | 0.0168004 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 374.522 | 0.40024 | 7349.28ms | 1834197 | 30 | 1.04833e+10 | 4.67056e+06 | 0.453326 | 13.158 | 57.9622 | 12.9351 | 0.045905 | 0.324152 | 0.00284731 | 1(Win) | true |
| simdjson (ondemand) | 260.161 | 0.528741 | 4857.56ms | 1834197 | 30 | 3.79153e+10 | 6.72363e+06 | 0.16186 | 19.048 | 99.3323 | 20.5137 | 0.0506244 | 0.769883 | 0.018288 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1221.18 | 0.353474 | 4049.12ms | 7351818 | 40 | 1.64742e+10 | 5.74137e+06 | 0.39216 | 4.03923 | 16.0415 | 3.44344 | 0.0140763 | 0.186381 | 0.0090144 | 1(Win) | true |
| simdjson (ondemand) | 840.394 | 0.487454 | 5874.12ms | 7351818 | 30 | 4.96148e+10 | 8.3428e+06 | 0.467988 | 5.89969 | 26.5447 | 5.32941 | 0.0132955 | 0.435962 | 0.00831699 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1267.85 | 0.580671 | 4044.9ms | 7351818 | 30 | 3.09337e+10 | 5.53e+06 | 0.106608 | 3.88411 | 15.2966 | 3.2703 | 0.0138434 | 0.181072 | 0.00765393 | 1(Win) | true |
| simdjson (ondemand) | 871.522 | 0.524236 | 5817.55ms | 7351818 | 40 | 7.11455e+10 | 8.04483e+06 | 0.0352618 | 5.71773 | 25.7996 | 5.15628 | 0.0130601 | 0.43061 | 0.00603306 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4260.72 | 0.160852 | 5425.07ms | 1834197 | 30 | 1.30828e+07 | 410547 | 0.0591949 | 1.18601 | 6.52918 | 0.874489 | 0.00489362 | 0.0755033 | 1.17581e-05 | 1(Win) | true |
| Jsonifier (generic) | 3947.02 | 0.0940731 | 5820.46ms | 1834197 | 160 | 2.78103e+07 | 443177 | 0.365993 | 1.26717 | 6.09588 | 1.08514 | 0.00799454 | 0.0756914 | 2.16716e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4269.43 | 0.0668005 | 5415.1ms | 1834197 | 40 | 2.9962e+06 | 409710 | 0.0653776 | 1.18413 | 6.52898 | 0.874442 | 0.00482879 | 0.075469 | 1.64922e-06 | 1(Win) | true |
| Jsonifier (generic) | 3881.82 | 0.403389 | 5829.66ms | 1834197 | 640 | 2.1147e+09 | 450621 | 0.490469 | 1.28074 | 6.09568 | 1.08509 | 0.00824551 | 0.0756526 | 8.34834e-07 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9127.48 | 0.537685 | 4954.89ms | 7351818 | 320 | 5.45877e+09 | 768147 | 0.0126494 | 0.54743 | 2.64676 | 0.256658 | 0.000975643 | 0.0424393 | 0.000302767 | 1(Win) | true |
| Jsonifier (generic) | 8365.2 | 0.360403 | 5335.69ms | 7351818 | 320 | 2.91986e+09 | 838143 | 0.0168536 | 0.590783 | 2.27881 | 0.29565 | 0.00430994 | 0.0424274 | 0.000260603 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9216.12 | 0.221292 | 4835.9ms | 7351818 | 30 | 8.50247e+07 | 760758 | 0.247956 | 0.546078 | 2.64671 | 0.256646 | 0.00101946 | 0.0424242 | 0.000325466 | 1(Win) | true |
| Jsonifier (generic) | 8446.88 | 0.233411 | 5387.23ms | 7351818 | 80 | 3.00283e+08 | 830039 | 0.184065 | 0.584483 | 2.27876 | 0.295639 | 0.00421838 | 0.0424189 | 0.000236377 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2875.57 | 0.16523 | 7871.62ms | 1834197 | 40 | 4.04091e+07 | 608306 | 0.122052 | 1.74309 | 8.90098 | 1.7864 | 0.00835259 | 0.113384 | 5.7791e-06 | 1(Win) | true |
| simdjson (ondemand) | 2347.19 | 0.174366 | 4794ms | 1834197 | 30 | 5.06574e+07 | 745244 | 0.0925193 | 2.13315 | 12.8397 | 2.27681 | 0.00489996 | 0.150798 | 2.26984e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2847.28 | 0.576342 | 7900.2ms | 1834197 | 320 | 4.01184e+09 | 614351 | 0.00987022 | 1.75797 | 8.90078 | 1.78635 | 0.00833684 | 0.113326 | 1.88553e-05 | 1(Win) | true |
| simdjson (ondemand) | 2338.11 | 0.18803 | 4794.97ms | 1834197 | 30 | 5.93659e+07 | 748138 | 0.0247264 | 2.13727 | 12.8395 | 2.27676 | 0.00510505 | 0.150716 | 5.38474e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6270.66 | 0.724625 | 7016.23ms | 7351818 | 160 | 1.05029e+10 | 1.1181e+06 | 0.392879 | 0.784603 | 2.97865 | 0.470609 | 0.00430675 | 0.0636241 | 0.00107939 | 1(Win) | true |
| simdjson (ondemand) | 5643.56 | 0.309899 | 7940.34ms | 7351818 | 30 | 4.44678e+08 | 1.24234e+06 | 0.931814 | 0.881911 | 4.22117 | 0.606521 | 0.00103315 | 0.0848202 | 0.00100948 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 5952.83 | 0.391956 | 7517.73ms | 7351818 | 320 | 6.81971e+09 | 1.1778e+06 | 0.100002 | 0.832074 | 4.22112 | 0.60651 | 0.000981684 | 0.0848 | 4.19267e-05 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 5900.6 | 0.461545 | 7407.08ms | 7351818 | 320 | 9.62446e+09 | 1.18822e+06 | 0.0290547 | 0.837747 | 2.9786 | 0.470597 | 0.00430461 | 0.0636088 | 0.00242924 | 1(Tie) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1269.56 | 0.219696 | 4039.64ms | 409725 | 40 | 1.82885e+07 | 307779 | 0.0127808 | 3.90249 | 18.2553 | 3.65745 | 0.0087898 | 0.0292813 | 3.45354e-05 | 1(Win) | true |
| simdjson (ondemand) | 957.426 | 0.147709 | 5236.61ms | 409725 | 40 | 1.45361e+07 | 408120 | 0.0188063 | 5.19697 | 19.918 | 3.84553 | 0.0201392 | 0.0375086 | 7.32198e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1594.63 | 0.222915 | 7617.48ms | 409725 | 640 | 1.90952e+08 | 245037 | 0.0787671 | 3.12208 | 15.398 | 3.01103 | 0.00590447 | 0.00992821 | 3.56184e-06 | 1(Win) | true |
| simdjson (ondemand) | 1150.35 | 0.231594 | 4989.43ms | 409725 | 640 | 3.96058e+08 | 339673 | 0.00785882 | 4.38938 | 17.0642 | 3.20019 | 0.0161184 | 0.014997 | 6.08259e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2005.45 | 0.366111 | 4205.63ms | 676745 | 30 | 4.1646e+07 | 321821 | 0.164768 | 2.51724 | 11.5351 | 2.22867 | 0.00765266 | 0.0312218 | 1.8717e-05 | 1(Win) | true |
| simdjson (ondemand) | 1540.14 | 0.164547 | 5465.33ms | 676745 | 30 | 1.42637e+07 | 419048 | 0.0425191 | 3.28025 | 12.6412 | 2.35424 | 0.0133399 | 0.0403039 | 3.72863e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2526.72 | 0.148844 | 7888.31ms | 676745 | 80 | 1.15635e+07 | 255428 | 0.0929452 | 1.99917 | 9.80551 | 1.83733 | 0.004462 | 0.0174733 | 3.76988e-05 | 1(Win) | true |
| simdjson (ondemand) | 1809.85 | 0.206709 | 5240.31ms | 676745 | 30 | 1.63007e+07 | 356602 | 0.0500775 | 2.79169 | 10.9135 | 1.96354 | 0.0108861 | 0.0228715 | 1.6205e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.753 | 0.111613 | 6441.07ms | 409725 | 80 | 2.43962e+07 | 494768 | 0.115859 | 6.3976 | 29.0343 | 5.98526 | 0.0143972 | 0.0302135 | 4.53048e-05 | 1(Win) | true |
| simdjson (ondemand) | 408.787 | 0.145125 | 6089.51ms | 409725 | 30 | 5.77295e+07 | 955863 | 0.00966921 | 12.1745 | 49.556 | 10.2522 | 0.0459496 | 0.0485592 | 3.95387e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 900.695 | 0.20532 | 6268.49ms | 409725 | 30 | 2.38019e+07 | 433825 | 0.071924 | 5.61024 | 26.1788 | 5.33726 | 0.0113837 | 0.00944634 | 2.11524e-05 | 1(Win) | true |
| simdjson (ondemand) | 438.412 | 0.137527 | 5966.83ms | 409725 | 40 | 6.0098e+07 | 891273 | 0.0247189 | 11.3528 | 46.7104 | 9.60665 | 0.0421416 | 0.0201193 | 1.50101e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1185.53 | 0.299419 | 7034.06ms | 676745 | 640 | 1.70046e+09 | 544395 | 0.0119493 | 4.19804 | 18.3464 | 3.76682 | 0.0105097 | 0.0334002 | 9.23815e-05 | 1(Win) | true |
| simdjson (ondemand) | 667.207 | 0.0549822 | 6155.08ms | 676745 | 40 | 1.13145e+07 | 967308 | 0.0650782 | 7.42919 | 30.4079 | 6.19308 | 0.0283684 | 0.0484529 | 2.9073e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1350.9 | 0.121476 | 6759.54ms | 676745 | 80 | 2.6945e+07 | 477752 | 0.42459 | 3.66914 | 16.6183 | 3.3749 | 0.00744172 | 0.0172244 | 1.33174e-05 | 1(Win) | true |
| simdjson (ondemand) | 717.48 | 0.205053 | 6012.59ms | 676745 | 320 | 1.08871e+09 | 899530 | 0.236511 | 6.94031 | 28.6831 | 5.80187 | 0.0258371 | 0.024916 | 2.43906e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2346.42 | 0.0989517 | 4448.32ms | 409725 | 160 | 4.34449e+06 | 166528 | 0.0640924 | 2.11192 | 10.3998 | 1.93924 | 0.00515959 | 0.000805022 | 1.01135e-05 | 1(Win) | true |
| simdjson (ondemand) | 1899.66 | 0.119974 | 5446.51ms | 409725 | 40 | 2.43592e+06 | 205691 | 0.160416 | 2.6097 | 10.9587 | 1.90022 | 0.00785448 | 0.00243712 | 1.56202e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2675.35 | 0.0557305 | 4434.15ms | 409725 | 640 | 4.24024e+06 | 146053 | 0.13147 | 1.85718 | 9.40765 | 1.7115 | 0.00476144 | 0.000420804 | 4.51904e-06 | 1(Win) | true |
| simdjson (ondemand) | 2138.86 | 0.112209 | 5342.83ms | 409725 | 80 | 3.36176e+06 | 182688 | 0.116968 | 2.31821 | 9.97093 | 1.67122 | 0.00645024 | 0.000971963 | 5.61352e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3284.5 | 0.294202 | 5231.93ms | 676745 | 40 | 1.33679e+07 | 196497 | 0.0779514 | 1.50958 | 6.85104 | 1.20485 | 0.00641397 | 0.00324927 | 7.09277e-06 | 1(Win) | true |
| simdjson (ondemand) | 2951.05 | 0.15829 | 5766.94ms | 676745 | 30 | 3.5952e+06 | 218700 | 0.00650859 | 1.6796 | 7.09826 | 1.15175 | 0.00539213 | 0.0065752 | 1.32497e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3826.16 | 0.155348 | 5060.72ms | 676745 | 1280 | 8.78911e+07 | 168679 | 0.0372563 | 1.29585 | 6.25077 | 1.06719 | 0.00437283 | 0.00163615 | 1.95097e-06 | 1(Win) | true |
| simdjson (ondemand) | 3332.29 | 0.13589 | 5682.04ms | 676745 | 80 | 5.54148e+06 | 193679 | 0.0533448 | 1.48482 | 6.4993 | 1.01279 | 0.00428684 | 0.00419418 | 8.69973e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.14 | 0.0893586 | 5718.16ms | 409725 | 320 | 1.19065e+07 | 215865 | 0.0241933 | 2.77558 | 13.3564 | 2.61429 | 0.00866554 | 0.000656141 | 1.45067e-05 | 1(Win) | true |
| simdjson (ondemand) | 1424 | 0.0870485 | 7226.17ms | 409725 | 1280 | 7.30299e+07 | 274400 | 0.0364404 | 3.54645 | 15.2454 | 2.82951 | 0.0126155 | 0.00185381 | 1.21099e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1986.26 | 0.0838313 | 5688.92ms | 409725 | 1280 | 3.48124e+07 | 196723 | 0.0413962 | 2.52902 | 12.339 | 2.38064 | 0.00805637 | 0.000480799 | 9.0171e-06 | 1(Win) | true |
| simdjson (ondemand) | 1545.58 | 0.0514241 | 7138.08ms | 409725 | 1280 | 2.16343e+07 | 252813 | 0.0586399 | 3.26781 | 14.2356 | 2.59612 | 0.0113283 | 0.000723624 | 4.41416e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2632.17 | 0.142411 | 6458.27ms | 676745 | 1280 | 1.56069e+08 | 245194 | 0.0427052 | 1.91184 | 8.67072 | 1.62929 | 0.00847494 | 0.00332878 | 7.61227e-06 | 1(Win) | true |
| simdjson (ondemand) | 2228.26 | 0.140711 | 7617.57ms | 676745 | 640 | 1.06305e+08 | 289641 | 0.163555 | 2.2653 | 9.74925 | 1.72553 | 0.00853809 | 0.00617527 | 5.79636e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2967.64 | 0.171184 | 6255.83ms | 676745 | 1280 | 1.77404e+08 | 217477 | 0.0277294 | 1.69912 | 8.05666 | 1.48836 | 0.00631006 | 0.00172219 | 2.48374e-05 | 1(Win) | true |
| simdjson (ondemand) | 2406.92 | 0.164896 | 7553.23ms | 676745 | 80 | 1.56399e+07 | 268141 | 0.0603546 | 2.08702 | 9.1362 | 1.58384 | 0.00743127 | 0.00405858 | 1.80829e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1699.19 | 0.0756387 | 7988.27ms | 264040 | 2560 | 3.21649e+07 | 148193 | 0.295102 | 2.91395 | 10.3647 | 1.98653 | 0.0121933 | 0.00110683 | 3.58847e-05 | 1(Win) | true |
| simdjson (ondemand) | 1560.96 | 0.141948 | 4333.85ms | 264040 | 320 | 1.67789e+07 | 161316 | 0.0496729 | 3.17484 | 10.6752 | 1.85701 | 0.0142245 | 0.00137277 | 3.44171e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2261.44 | 0.100652 | 6813.54ms | 264040 | 1280 | 1.60776e+07 | 111348 | 0.154626 | 2.18743 | 8.99187 | 1.67339 | 0.00372696 | 5.48952e-05 | 3.78435e-06 | 1(Win) | true |
| simdjson (ondemand) | 1843.05 | 0.126788 | 4082.1ms | 264040 | 640 | 1.92045e+07 | 136626 | 0.151112 | 2.68382 | 9.30728 | 1.54536 | 0.0118907 | 0.000169358 | 3.19554e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2139.82 | 0.331329 | 4299.63ms | 360584 | 160 | 4.53625e+07 | 160705 | 0.0758229 | 2.30677 | 7.98031 | 1.46455 | 0.0120648 | 0.000617037 | 1.38664e-05 | 1(Win) | true |
| simdjson (ondemand) | 2042.12 | 0.261268 | 4483.24ms | 360584 | 320 | 6.19401e+07 | 168393 | 0.12209 | 2.42177 | 8.20983 | 1.37702 | 0.0107287 | 0.00102081 | 1.39791e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2601.73 | 0.15902 | 7793.45ms | 360584 | 640 | 2.82728e+07 | 132173 | 0.0679565 | 1.89833 | 6.9771 | 1.23556 | 0.00907335 | 2.63505e-05 | 2.85994e-06 | 1(Win) | true |
| simdjson (ondemand) | 2414.75 | 0.0947049 | 4229.14ms | 360584 | 1280 | 2.32821e+07 | 142408 | 0.242164 | 2.04347 | 7.20663 | 1.14871 | 0.00883902 | 8.40758e-05 | 2.61512e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 619.797 | 0.112335 | 5286.97ms | 264040 | 320 | 6.66534e+07 | 406275 | 0.128527 | 8.01206 | 28.9406 | 5.60502 | 0.0306388 | 0.00378671 | 3.42514e-05 | 1(Win) | true |
| simdjson (ondemand) | 265.398 | 0.149396 | 6036.6ms | 264040 | 160 | 3.21469e+08 | 948794 | 0.206607 | 18.5742 | 69.4948 | 14.8252 | 0.0894605 | 0.00574813 | 8.64689e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 664.911 | 0.159336 | 5125.92ms | 264040 | 160 | 5.82585e+07 | 378709 | 0.0311715 | 7.46053 | 27.5701 | 5.29246 | 0.0265363 | 0.000402188 | 1.81791e-05 | 1(Win) | true |
| simdjson (ondemand) | 273.65 | 0.099466 | 5950.23ms | 264040 | 320 | 2.68069e+08 | 920182 | 0.0247729 | 17.9887 | 68.1284 | 14.515 | 0.0832181 | 0.000723943 | 2.25108e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 778.717 | 0.280739 | 5693.56ms | 360584 | 160 | 2.45912e+08 | 441598 | 0.0602509 | 6.37033 | 21.8379 | 4.24315 | 0.0294865 | 0.0032031 | 2.26889e-05 | 1(Win) | true |
| simdjson (ondemand) | 384.023 | 0.210117 | 5688.85ms | 360584 | 160 | 5.66425e+08 | 895467 | 0.0332969 | 13.0225 | 50.6412 | 10.7384 | 0.0492904 | 0.00590847 | 5.81522e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 836.357 | 0.237787 | 5540.97ms | 360584 | 80 | 7.64709e+07 | 411164 | 0.0518158 | 5.94936 | 20.8339 | 4.01436 | 0.0261533 | 0.000353801 | 1.91703e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.712 | 0.244664 | 5584.61ms | 360584 | 80 | 3.54445e+08 | 860320 | 0.0564036 | 12.5416 | 49.6395 | 10.5109 | 0.0450214 | 0.00145358 | 4.13912e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6982.98 | 0.0831535 | 4369.14ms | 264040 | 1280 | 1.15088e+06 | 36060.3 | 0.0457625 | 0.722892 | 3.67989 | 0.560843 | 0.00127763 | 2.55643e-06 | 8.31432e-07 | 1(Win) | true |
| simdjson (ondemand) | 6015.82 | 0.11891 | 4960.37ms | 264040 | 160 | 396372 | 41857.6 | 0.100776 | 0.840726 | 4.02549 | 0.451873 | 0.00106411 | 5.04185e-06 | 1.94099e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7178.06 | 0.109251 | 4405.43ms | 264040 | 320 | 470029 | 35080.3 | 0.0422869 | 0.702941 | 3.60186 | 0.543274 | 0.00128871 | 3.68079e-06 | 1.66878e-06 | 1(Win) | true |
| simdjson (ondemand) | 6165.21 | 0.0926407 | 4915.7ms | 264040 | 320 | 458139 | 40843.4 | 0.0841035 | 0.820272 | 3.94716 | 0.434145 | 0.00106004 | 2.5801e-06 | 1.05334e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8211.5 | 0.136683 | 4955.12ms | 360584 | 320 | 1.04845e+06 | 41877.8 | 0.133574 | 0.612795 | 3.10164 | 0.427005 | 0.000868114 | 1.07118e-05 | 6.46521e-06 | 1(Win) | true |
| simdjson (ondemand) | 7099.14 | 0.0261688 | 5565.95ms | 360584 | 4890 | 785738 | 48439.6 | 0.0562676 | 0.698577 | 3.33735 | 0.347679 | 0.000826333 | 6.60823e-06 | 3.54855e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8474.07 | 0.0734437 | 4979.04ms | 360584 | 640 | 568484 | 40580.2 | 0.0355056 | 0.596502 | 3.04451 | 0.414139 | 0.000869544 | 2.79061e-06 | 6.36987e-07 | 1(Win) | true |
| simdjson (ondemand) | 7264.68 | 0.0365294 | 5553.28ms | 360584 | 4890 | 1.46209e+06 | 47335.9 | 0.0394661 | 0.682532 | 3.27999 | 0.334697 | 0.000813187 | 3.71472e-06 | 9.24993e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4641.81 | 0.066929 | 6192.12ms | 264040 | 1280 | 1.68734e+06 | 54247.9 | 0.141178 | 1.06731 | 5.38635 | 0.967172 | 0.0023444 | 4.13053e-06 | 1.38473e-06 | 1(Win) | true |
| simdjson (ondemand) | 3712.9 | 0.0504465 | 7547.04ms | 264040 | 4890 | 5.72378e+06 | 67819.8 | 0.00944191 | 1.33433 | 6.44399 | 0.987868 | 0.00273096 | 4.92195e-06 | 2.01912e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4742.53 | 0.0967243 | 6236.44ms | 264040 | 320 | 843997 | 53095.8 | 0.0816586 | 1.0465 | 5.30857 | 0.949572 | 0.00232821 | 4.7223e-06 | 2.44991e-06 | 1(Win) | true |
| simdjson (ondemand) | 3793.35 | 0.0636081 | 7469.25ms | 264040 | 640 | 1.14103e+06 | 66381.5 | 0.000666126 | 1.30819 | 6.36544 | 0.970139 | 0.00272105 | 3.79914e-06 | 8.81732e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5803.59 | 0.0652926 | 6697.73ms | 360584 | 2560 | 3.83167e+06 | 59253 | 0.0174916 | 0.853011 | 4.36421 | 0.732096 | 0.00134896 | 5.83689e-06 | 2.26846e-06 | 1(Win) | true |
| simdjson (ondemand) | 4675.98 | 0.054295 | 4160.65ms | 360584 | 640 | 1.02039e+06 | 73541.7 | 0.0145581 | 1.06063 | 5.11917 | 0.742478 | 0.0020001 | 8.11184e-06 | 4.61924e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5932.23 | 0.0723016 | 6752.28ms | 360584 | 1280 | 2.24845e+06 | 57968.1 | 0.0235554 | 0.83437 | 4.30733 | 0.719228 | 0.00127328 | 7.93418e-06 | 4.34841e-06 | 1(Win) | true |
| simdjson (ondemand) | 4746.07 | 0.0363499 | 4164.1ms | 360584 | 2560 | 1.77578e+06 | 72455.6 | 0.0826218 | 1.04507 | 5.06164 | 0.729496 | 0.00203228 | 1.05504e-05 | 6.58437e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1879.91 | 0.170779 | 909.572ms | 2632 | 1280 | 6655.47 | 1335.21 | 0.0049152 | 2.72958 | 10.9829 | 2.07105 | 0.000847739 | 0.000102999 | 2.5824e-05 | 1(Win) | true |
| simdjson (ondemand) | 1509.79 | 0.0741619 | 936.652ms | 2632 | 4890 | 7433.73 | 1662.53 | 0.253102 | 3.40133 | 11.5376 | 2.15958 | 0.00299802 | 6.20023e-05 | 2.65724e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2315.77 | 0.105292 | 866.072ms | 2632 | 4890 | 6369.13 | 1083.9 | 0.0483339 | 2.23886 | 9.15654 | 1.6421 | 0.00113181 | 4.42097e-05 | 1.00229e-05 | 1(Win) | true |
| simdjson (ondemand) | 1760.09 | 0.0641398 | 896.364ms | 2632 | 4890 | 4091.36 | 1426.11 | 0.277268 | 2.91811 | 9.84575 | 1.76178 | 0.0024968 | 3.08458e-05 | 4.11795e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2321.46 | 0.10507 | 892.641ms | 3370 | 4890 | 10346.7 | 1384.42 | 0.246627 | 2.21599 | 9.03769 | 1.64896 | 0.000600754 | 0.000133076 | 6.86922e-05 | 1(Win) | true |
| simdjson (ondemand) | 1886.63 | 0.0809199 | 918.931ms | 3370 | 2560 | 4864.48 | 1703.5 | 0.0468713 | 2.69816 | 9.31991 | 1.69882 | 0.00181183 | 4.77559e-05 | 1.39095e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2926.65 | 0.252003 | 923.434ms | 3370 | 640 | 4901.25 | 1098.14 | 0.123494 | 1.76387 | 7.51009 | 1.29139 | 0.000609236 | 3.75556e-05 | 1.02003e-05 | 1(Win) | true |
| simdjson (ondemand) | 2195.42 | 0.0740049 | 901.347ms | 3370 | 4890 | 5739.23 | 1463.9 | 0.237159 | 2.34371 | 7.99852 | 1.38813 | 0.00168976 | 8.48944e-05 | 4.58151e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1200.02 | 0.0851263 | 956.886ms | 2632 | 160 | 507.273 | 2091.69 | 0.070567 | 4.21906 | 16.497 | 3.32941 | 0.00368778 | 5.22416e-05 | 9.49848e-06 | 1(Win) | true |
| simdjson (ondemand) | 660.497 | 0.0546655 | 1129.81ms | 2632 | 4890 | 21104 | 3800.27 | 0.379247 | 7.59514 | 30.0612 | 6.16565 | 0.0118909 | 7.94842e-05 | 2.98357e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1373.35 | 0.0995707 | 933.47ms | 2632 | 4890 | 16195.1 | 1827.7 | 0.523041 | 3.7044 | 14.6717 | 2.90046 | 0.00499624 | 5.67189e-05 | 1.20431e-05 | 1(Win) | true |
| simdjson (ondemand) | 707.819 | 0.111206 | 1114.68ms | 2632 | 640 | 9953.29 | 3546.21 | 0.087847 | 7.09596 | 28.3742 | 5.76786 | 0.011749 | 8.19244e-05 | 2.01843e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1479.36 | 0.126063 | 968.875ms | 3370 | 2560 | 19201.1 | 2172.48 | 0.00383001 | 3.42117 | 13.4309 | 2.69318 | 0.00272638 | 5.38993e-05 | 7.53431e-06 | 1(Win) | true |
| simdjson (ondemand) | 855.98 | 0.0979596 | 1128.76ms | 3370 | 40 | 541.112 | 3754.62 | 0.0774001 | 5.86398 | 23.5377 | 4.77537 | 0.00931751 | 2.22552e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1673.07 | 0.173881 | 951.706ms | 3370 | 1280 | 14280.6 | 1920.95 | 0.0104126 | 3.03073 | 12.0042 | 2.35786 | 0.00359375 | 4.84514e-05 | 9.96847e-06 | 1(Win) | true |
| simdjson (ondemand) | 927.458 | 0.171942 | 1106.94ms | 3370 | 640 | 22720.3 | 3465.26 | 0.647294 | 5.46188 | 22.2199 | 4.46469 | 0.00908707 | 2.92099e-05 | 4.6365e-07 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3062.68 | 0.30408 | 824.756ms | 2632 | 30 | 186.323 | 819.567 | 0.0162714 | 1.71881 | 7.16679 | 1.25798 | 0.000848531 | 2.53293e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2311.48 | 0.141588 | 844.566ms | 2632 | 2560 | 6051.83 | 1085.92 | 0.0362729 | 2.27601 | 8.18048 | 1.42781 | 0.00180976 | 7.3168e-05 | 4.03685e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3800.08 | 0.161001 | 806.802ms | 2632 | 2560 | 2895.25 | 660.531 | 0.0885103 | 1.42122 | 6.12424 | 1.01406 | 0.00122174 | 5.43194e-05 | 2.52303e-05 | 1(Win) | true |
| simdjson (ondemand) | 2708.24 | 0.170863 | 835.049ms | 2632 | 320 | 802.5 | 926.828 | 0.0982133 | 1.95529 | 7.15426 | 1.18161 | 0.00133454 | 1.5435e-05 | 1.18731e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3777.34 | 0.106418 | 825.607ms | 3370 | 4890 | 4008.93 | 850.833 | 0.151517 | 1.39931 | 5.96024 | 1.00415 | 0.00036379 | 3.98075e-05 | 1.68696e-05 | 1(Win) | true |
| simdjson (ondemand) | 2927.42 | 0.235895 | 851.344ms | 3370 | 160 | 1073.12 | 1097.86 | 0.040436 | 1.77278 | 6.51424 | 1.08991 | 0.000650964 | 3.52374e-05 | 1.66914e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4529.4 | 0.166613 | 811.311ms | 3370 | 2560 | 3577.99 | 709.561 | 0.121481 | 1.1786 | 5.15935 | 0.81365 | 0.000802346 | 2.93259e-05 | 1.02003e-05 | 1(Win) | true |
| simdjson (ondemand) | 3449.08 | 0.175083 | 833.199ms | 3370 | 1280 | 3406.84 | 931.809 | 0.00159303 | 1.53374 | 5.71276 | 0.897626 | 0.000727003 | 5.10015e-05 | 1.80823e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2316.42 | 0.11881 | 847.522ms | 2632 | 4890 | 8104.99 | 1083.6 | 0.137536 | 2.26034 | 9.40426 | 1.83473 | 0.00077837 | 6.31678e-05 | 2.36199e-05 | 1(Win) | true |
| simdjson (ondemand) | 1951.14 | 0.150919 | 865.756ms | 2632 | 30 | 113.085 | 1286.47 | 0 | 2.67411 | 10.0695 | 1.80927 | 0.00192503 | 0 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2681.51 | 0.181892 | 833.965ms | 2632 | 2560 | 7421.33 | 936.068 | 0.0657686 | 1.95667 | 8.38488 | 1.58891 | 0.00116342 | 3.6213e-05 | 1.5435e-05 | 1(Win) | true |
| simdjson (ondemand) | 2198.25 | 0.126366 | 857.552ms | 2632 | 80 | 166.559 | 1141.85 | 0.248019 | 2.38372 | 9.03116 | 1.56307 | 0.00213241 | 1.8997e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2833.61 | 0.14336 | 857.356ms | 3370 | 40 | 105.754 | 1134.2 | 0.0352547 | 1.84822 | 7.7549 | 1.46291 | 0.000897626 | 5.93472e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2476.82 | 0.0711084 | 873.853ms | 3370 | 4890 | 4163.16 | 1297.59 | 0.531677 | 2.09261 | 7.99443 | 1.38785 | 0.00107043 | 2.8642e-05 | 4.24775e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3214.08 | 0.215792 | 845.398ms | 3370 | 1280 | 5959.73 | 999.938 | 0.327926 | 1.62134 | 6.95875 | 1.27092 | 0.000925213 | 2.2487e-05 | 8.11387e-06 | 1(Win) | true |
| simdjson (ondemand) | 2814.17 | 0.115385 | 858.888ms | 3370 | 2560 | 4445.26 | 1142.04 | 0.128431 | 1.85123 | 7.18339 | 1.19555 | 0.00089809 | 1.94733e-05 | 3.82511e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 731.134 | 0.298512 | 1349.62ms | 4630 | 80 | 26000.5 | 6039.26 | 0.00972896 | 6.83619 | 31.5069 | 5.77019 | 0.00241091 | 4.31965e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 667.17 | 0.122649 | 1404.09ms | 4630 | 640 | 42169.7 | 6618.27 | 0.0637033 | 7.58672 | 31.7853 | 6.41901 | 0.0106115 | 5.09584e-05 | 1.07991e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 882.761 | 0.104672 | 1340.85ms | 4630 | 2560 | 70174.6 | 5001.93 | 0.052694 | 5.75806 | 27.0741 | 4.7648 | 0.00181189 | 0.000225432 | 0.000125371 | 1(Win) | true |
| Jsonifier (generic) | 773.232 | 0.122219 | 1414.31ms | 4630 | 640 | 31174.7 | 5710.46 | 0.169466 | 6.58829 | 27.4687 | 5.43499 | 0.00978604 | 6.64822e-05 | 1.34989e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1778.22 | 0.06481 | 1366.73ms | 11579 | 2560 | 41466.5 | 6209.93 | 0.224538 | 2.86231 | 13.5005 | 2.36126 | 0.00101858 | 8.75103e-05 | 5.30324e-05 | 1(Win) | true |
| Jsonifier (generic) | 1600.6 | 0.0643997 | 1433.84ms | 11579 | 4890 | 96528.5 | 6899.05 | 0.104241 | 3.17139 | 13.7837 | 2.66085 | 0.00404274 | 6.73068e-05 | 3.01477e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2058.73 | 0.0718137 | 1378.35ms | 11579 | 2560 | 37983.9 | 5363.79 | 0.0585939 | 2.4701 | 11.732 | 1.96001 | 0.000591048 | 4.25069e-05 | 1.86221e-05 | 1(Win) | true |
| Jsonifier (generic) | 1833.1 | 0.139933 | 1444.97ms | 11579 | 320 | 22738.4 | 6024.01 | 0.328278 | 2.78033 | 12.1049 | 2.27679 | 0.00372819 | 1.51136e-05 | 1.07954e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 651.771 | 0.0998298 | 1419.49ms | 4630 | 2560 | 117094 | 6774.64 | 0.0290517 | 7.80446 | 36.0158 | 6.7648 | 0.00300849 | 0.000444283 | 0.000323299 | 1(Win) | true |
| Jsonifier (generic) | 608.095 | 0.0515976 | 1474.87ms | 4630 | 4890 | 68641.6 | 7261.23 | 0.15856 | 8.29622 | 35.6683 | 7.25875 | 0.00934967 | 0.000237228 | 0.000135508 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 769.618 | 0.106153 | 1413.05ms | 4630 | 1280 | 47477.1 | 5737.27 | 0.110393 | 6.60443 | 31.6441 | 5.77171 | 0.00215038 | 7.13755e-05 | 2.85165e-05 | 1(Win) | true |
| Jsonifier (generic) | 693.009 | 0.0802822 | 1479.68ms | 4630 | 1280 | 33491.3 | 6371.5 | 0.163518 | 7.32178 | 31.2255 | 6.24989 | 0.00847884 | 0.000181054 | 8.28496e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1586.7 | 0.0868132 | 1450.1ms | 11579 | 640 | 23361.8 | 6959.49 | 0.131603 | 3.18481 | 15.1982 | 2.73772 | 0.00125578 | 8.58235e-05 | 4.87143e-05 | 1(Win) | true |
| Jsonifier (generic) | 1507.39 | 0.093017 | 1485.45ms | 11579 | 640 | 29716.2 | 7325.62 | 0.339514 | 3.37343 | 15.077 | 2.94568 | 0.00320043 | 7.7592e-05 | 3.85936e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1814.05 | 0.0709991 | 1454.59ms | 11579 | 4890 | 91339.1 | 6087.24 | 0.0162999 | 2.79485 | 13.4726 | 2.34537 | 0.000925323 | 6.67063e-05 | 3.53401e-05 | 1(Win) | true |
| Jsonifier (generic) | 1699.03 | 0.102684 | 1490.37ms | 11579 | 1280 | 57010.6 | 6499.34 | 0.00525322 | 2.98034 | 13.3117 | 2.54478 | 0.00265054 | 5.01986e-05 | 2.348e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7151.5 | 0.175792 | 794.234ms | 4630 | 40 | 47.1224 | 617.425 | 0.253031 | 0.752964 | 3.72354 | 0.583585 | 0.000431965 | 5.39957e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5822.26 | 0.12307 | 809.314ms | 4630 | 4890 | 4259.84 | 758.385 | 0.606019 | 0.918359 | 4.10518 | 0.492657 | 0.000434439 | 2.12891e-05 | 8.78948e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7203.23 | 0.199264 | 798.748ms | 4630 | 2560 | 3819.5 | 612.99 | 0.256215 | 0.750325 | 3.6892 | 0.576026 | 0.000433231 | 2.59854e-05 | 1.23178e-05 | 1(Win) | true |
| simdjson (ondemand) | 5869.14 | 0.196487 | 814.265ms | 4630 | 640 | 1398.5 | 752.327 | 0.291367 | 0.910645 | 4.07019 | 0.484881 | 0.000434665 | 1.65362e-05 | 1.01242e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12391 | 0.154455 | 826.203ms | 11579 | 2560 | 4850.39 | 891.18 | 0.141515 | 0.42861 | 2.12195 | 0.254426 | 0.000174245 | 2.3986e-05 | 1.16051e-05 | 1(Win) | true |
| simdjson (ondemand) | 10384.5 | 0.132416 | 841.944ms | 11579 | 2560 | 5075.66 | 1063.38 | 0.335103 | 0.507245 | 2.44641 | 0.231626 | 0.000174211 | 1.30557e-05 | 5.36397e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12541.9 | 0.126685 | 825.814ms | 11579 | 2560 | 3185.01 | 880.459 | 0.0815225 | 0.422547 | 2.10865 | 0.251403 | 0.000187638 | 1.98366e-05 | 9.17609e-06 | 1(Win) | true |
| simdjson (ondemand) | 10388.2 | 0.177502 | 842.951ms | 11579 | 1280 | 4556.96 | 1062.99 | 0.176591 | 0.499759 | 2.43242 | 0.228517 | 0.000173266 | 1.36292e-05 | 4.11575e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5035.51 | 0.321681 | 822.104ms | 4630 | 160 | 1273.05 | 876.875 | 0.707714 | 1.05034 | 5.25097 | 0.921166 | 0.000650648 | 3.7797e-05 | 8.09935e-06 | 1(Win) | true |
| simdjson (ondemand) | 3919.87 | 0.123967 | 851.404ms | 4630 | 2560 | 4992.01 | 1126.44 | 0.222412 | 1.33202 | 5.58164 | 0.820303 | 0.000649973 | 1.2824e-05 | 3.20599e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5124.29 | 0.251791 | 821.476ms | 4630 | 1280 | 6025.41 | 861.683 | 0.268734 | 1.01777 | 5.21771 | 0.913391 | 0.000648961 | 1.43426e-05 | 1.18116e-06 | 1(Win) | true |
| simdjson (ondemand) | 4225.33 | 0.179736 | 845.894ms | 4630 | 4890 | 17251.2 | 1045.01 | 0.695899 | 1.22162 | 5.54665 | 0.812527 | 0.000658814 | 1.45755e-05 | 3.57763e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9652.6 | 0.105497 | 887.735ms | 11579 | 4890 | 7122.62 | 1144 | 0.0123702 | 0.532431 | 2.73383 | 0.38993 | 0.000261863 | 8.68931e-06 | 6.53464e-07 | 1(Win) | true |
| simdjson (ondemand) | 7469.76 | 0.183889 | 893.868ms | 11579 | 1280 | 9459.08 | 1478.31 | 0.545827 | 0.682712 | 3.03679 | 0.362639 | 0.000260034 | 7.08448e-06 | 9.44598e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9787.7 | 0.210036 | 852.357ms | 11579 | 1280 | 7187.5 | 1128.21 | 0.108392 | 0.5263 | 2.72053 | 0.386821 | 0.000259562 | 8.63632e-06 | 6.07242e-07 | 1(Win) | true |
| simdjson (ondemand) | 7620.14 | 0.123551 | 889.081ms | 11579 | 2560 | 8206.39 | 1449.13 | 0.391209 | 0.674084 | 3.0228 | 0.35953 | 0.000260878 | 1.36629e-05 | 6.30857e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1136.57 | 0.0785766 | 1182.22ms | 5092 | 4890 | 55115.9 | 4272.58 | 0.148081 | 4.41906 | 17.6345 | 3.07541 | 0.00196752 | 5.65866e-05 | 1.24097e-05 | 1(Win) | true |
| Jsonifier (generic) | 1114.92 | 0.133256 | 1195.65ms | 5092 | 40 | 1347.48 | 4355.57 | 0.0177965 | 4.49496 | 18.2498 | 3.58602 | 0.00240082 | 2.9458e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1293.15 | 0.130506 | 1246.13ms | 5092 | 2560 | 61486.6 | 3755.26 | 0.0298108 | 3.89091 | 16.0555 | 3.07812 | 0.00252464 | 7.42586e-05 | 1.76441e-05 | 1(Win) | true |
| simdjson (ondemand) | 1286.83 | 0.100891 | 1165.82ms | 5092 | 2560 | 37109.1 | 3773.71 | 0.0566015 | 3.91553 | 16.0327 | 2.68338 | 0.00173787 | 0.000126347 | 6.67407e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2045.14 | 0.0668871 | 1206.8ms | 9739 | 4890 | 45120.9 | 4541.42 | 0.287935 | 2.44809 | 9.87535 | 1.63682 | 0.00123292 | 4.72454e-05 | 1.65044e-05 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 2041.33 | 0.0761336 | 1209.29ms | 9739 | 4890 | 58676.5 | 4549.89 | 0.456469 | 2.45643 | 10.0846 | 1.89095 | 0.00137419 | 7.1876e-05 | 3.35757e-05 | 1(Tie) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 2312.97 | 0.0811795 | 1203.42ms | 9739 | 4890 | 51962.5 | 4015.54 | 0.289696 | 2.17497 | 9.00023 | 1.6369 | 0.00154809 | 0.000117798 | 6.71724e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2307.65 | 0.108091 | 1224.28ms | 9739 | 1280 | 24225.8 | 4024.81 | 0.321147 | 2.18912 | 9.03781 | 1.43185 | 0.00148822 | 2.50282e-05 | 3.60984e-06 | 1(Tie) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 645.883 | 0.161655 | 1530.66ms | 5092 | 640 | 94542.6 | 7518.56 | 0.119889 | 7.73361 | 32.4385 | 6.75216 | 0.00636906 | 9.8807e-05 | 5.00172e-05 | 1(Win) | true |
| simdjson (ondemand) | 404.569 | 0.0982217 | 1963.14ms | 5092 | 1280 | 177916 | 12003.2 | 0.00766784 | 12.354 | 54.0281 | 11.0573 | 0.0153381 | 0.000296574 | 0.000171531 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 695.448 | 0.0731148 | 1501.22ms | 5092 | 4890 | 127458 | 6982.7 | 0.128504 | 7.17649 | 30.4386 | 6.2814 | 0.00635208 | 5.0201e-05 | 8.99603e-06 | 1(Win) | true |
| simdjson (ondemand) | 416.574 | 0.0648535 | 1956.3ms | 5092 | 2560 | 146319 | 11657.3 | 0.197749 | 11.9472 | 52.523 | 10.6848 | 0.0165246 | 8.07793e-05 | 2.3014e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1175.83 | 0.092654 | 1550.3ms | 9739 | 4890 | 261926 | 7898.98 | 0.304699 | 4.25609 | 17.6747 | 3.61567 | 0.00325938 | 8.09261e-05 | 3.65574e-05 | 1(Win) | true |
| simdjson (ondemand) | 760.301 | 0.0710731 | 1979.92ms | 9739 | 2560 | 192978 | 12216 | 0.0106343 | 6.59547 | 28.8148 | 5.79033 | 0.00858701 | 7.86946e-05 | 3.36517e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1261.88 | 0.11847 | 1537.64ms | 9739 | 2560 | 194649 | 7360.33 | 0.10499 | 3.96389 | 16.6822 | 3.38025 | 0.00331307 | 3.99489e-05 | 1.43993e-05 | 1(Win) | true |
| simdjson (ondemand) | 784.492 | 0.0495032 | 1965.21ms | 9739 | 4890 | 167968 | 11839.3 | 0.171092 | 6.36081 | 28.0279 | 5.59552 | 0.00846079 | 4.81693e-05 | 1.59794e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4773.64 | 0.126955 | 845.725ms | 5092 | 40 | 66.7173 | 1017.27 | 0.0810333 | 1.07979 | 4.95699 | 0.845444 | 0.00119796 | 4.90966e-06 | 4.90966e-06 | 1(Win) | true |
| simdjson (ondemand) | 4438.47 | 0.0880852 | 853.845ms | 5092 | 4890 | 4541.76 | 1094.09 | 0.133943 | 1.16179 | 5.39965 | 0.670857 | 0.00124334 | 1.53013e-05 | 3.8956e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4943.15 | 0.117656 | 843.793ms | 5092 | 4890 | 6532.92 | 982.392 | 0.0889848 | 1.04439 | 4.84191 | 0.821092 | 0.00106093 | 1.48997e-05 | 2.32933e-06 | 1(Win) | true |
| simdjson (ondemand) | 4543.92 | 0.139838 | 850.387ms | 5092 | 2560 | 5717.46 | 1068.7 | 0.0530078 | 1.13319 | 5.28437 | 0.645719 | 0.00130329 | 1.72605e-05 | 4.37267e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7645.15 | 0.202771 | 864.843ms | 9739 | 30 | 182.051 | 1214.87 | 0.101417 | 0.671058 | 3.14673 | 0.459287 | 0.000722182 | 3.42266e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7020.66 | 0.0982782 | 875.941ms | 9739 | 2560 | 4327.4 | 1322.93 | 0.2458 | 0.731459 | 3.47274 | 0.377862 | 0.000680576 | 1.59635e-05 | 5.89608e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7828.15 | 0.154242 | 860.397ms | 9739 | 2560 | 8573.45 | 1186.47 | 0.00385218 | 0.661104 | 3.08553 | 0.446658 | 0.000801064 | 1.27949e-05 | 1.16317e-06 | 1(Win) | true |
| simdjson (ondemand) | 7269.4 | 0.105229 | 874.671ms | 9739 | 2560 | 4627.44 | 1277.66 | 0.237662 | 0.706742 | 3.41247 | 0.36472 | 0.000563456 | 8.30264e-06 | 1.2835e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3005.95 | 0.107079 | 905.763ms | 5092 | 4890 | 14633 | 1615.5 | 0.311943 | 1.7023 | 8.00295 | 1.55283 | 0.00212953 | 2.02411e-05 | 3.65464e-06 | 1(Win) | true |
| simdjson (ondemand) | 2850.52 | 0.0734545 | 918.115ms | 5092 | 4890 | 7657.3 | 1703.59 | 0.00988784 | 1.7884 | 8.38276 | 1.33386 | 0.0025676 | 3.1968e-05 | 1.23294e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3069.71 | 0.161453 | 904.665ms | 5092 | 1280 | 8349.92 | 1581.94 | 0.00464245 | 1.66893 | 7.88727 | 1.52789 | 0.00244915 | 1.61098e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2864.15 | 0.272828 | 913.513ms | 5092 | 160 | 3423.61 | 1695.48 | 0.0387208 | 1.7764 | 8.26748 | 1.30872 | 0.00333734 | 1.71838e-05 | 2.45483e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4997.76 | 0.110402 | 930.373ms | 9739 | 2560 | 10776.3 | 1858.4 | 0.0491193 | 1.0156 | 4.7492 | 0.835516 | 0.00134334 | 1.55624e-05 | 3.08842e-06 | 1(Win) | true |
| simdjson (ondemand) | 4775.32 | 0.0945342 | 941.963ms | 9739 | 2560 | 8654.51 | 1944.97 | 0.00202843 | 1.06253 | 5.05853 | 0.729644 | 0.00105223 | 1.09499e-05 | 2.24612e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5150.65 | 0.117415 | 930.8ms | 9739 | 320 | 1434.51 | 1803.23 | 0.302874 | 0.988173 | 4.68867 | 0.822467 | 0.00125398 | 1.18724e-05 | 1.92525e-06 | 1(Win) | true |
| simdjson (ondemand) | 5035.04 | 0.199892 | 930.074ms | 9739 | 640 | 8701.5 | 1844.64 | 0.0527142 | 1.0079 | 4.97228 | 0.711367 | 0.000623941 | 8.9845e-06 | 0 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1379.27 | 0.0936156 | 1091.79ms | 4857 | 4890 | 48333.2 | 3358.3 | 0.195778 | 3.63966 | 14.5512 | 2.9092 | 0.00116081 | 0.000177763 | 9.74286e-05 | 1(Win) | true |
| simdjson (ondemand) | 1308.52 | 0.0659269 | 1107.9ms | 4857 | 4890 | 26632.4 | 3539.88 | 0.109428 | 3.84172 | 14.5571 | 2.64299 | 0.00201741 | 0.000111576 | 4.86722e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1833.37 | 0.123799 | 1036.9ms | 4857 | 80 | 782.633 | 2526.49 | 0.0153399 | 2.7538 | 11.559 | 2.25221 | 0.00154416 | 5.40457e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1582.57 | 0.0689726 | 1068.39ms | 4857 | 4890 | 19928.4 | 2926.88 | 0.0836632 | 3.20336 | 12.2712 | 2.14845 | 0.00230123 | 0.000124207 | 5.41036e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1881.04 | 0.156903 | 1088.22ms | 6701 | 30 | 852.447 | 3397.37 | 0.180858 | 2.67127 | 10.8154 | 2.10088 | 0.00117395 | 9.94876e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1770.54 | 0.063318 | 1116.98ms | 6701 | 4890 | 25540.7 | 3609.4 | 0.0381278 | 2.83566 | 10.9812 | 1.9324 | 0.000538546 | 5.16359e-05 | 1.97755e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2427.14 | 0.0794807 | 1040.2ms | 6701 | 4890 | 21415.2 | 2632.96 | 0.279979 | 2.08004 | 8.7284 | 1.6399 | 0.00161298 | 0.000103119 | 6.10964e-05 | 1(Win) | true |
| simdjson (ondemand) | 2138.45 | 0.0782072 | 1075.47ms | 6701 | 2560 | 13983.5 | 2988.41 | 0.0175125 | 2.35504 | 9.32428 | 1.57395 | 0.000647874 | 4.11552e-05 | 1.12507e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 643.385 | 0.121113 | 1473.46ms | 4857 | 1280 | 97317 | 7199.41 | 0.142957 | 7.77925 | 31.4604 | 6.41322 | 0.00802997 | 8.02643e-05 | 3.45828e-05 | 1(Win) | true |
| simdjson (ondemand) | 206.761 | 0.177187 | 3010.55ms | 4857 | 160 | 252107 | 22402.7 | 0.0699065 | 24.1797 | 112.623 | 24.2841 | 0.0345082 | 0.000234198 | 0.000131254 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 720.446 | 0.0650375 | 1425.36ms | 4857 | 4890 | 85500.8 | 6429.35 | 0.258801 | 6.93645 | 28.5503 | 5.7692 | 0.00775791 | 0.00013187 | 6.964e-05 | 1(Win) | true |
| simdjson (ondemand) | 212.388 | 0.0760162 | 2962.28ms | 4857 | 640 | 175901 | 21809.1 | 0.102111 | 23.3986 | 110.346 | 23.7906 | 0.0353208 | 6.85222e-05 | 1.25463e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 836.302 | 0.134227 | 1519.21ms | 6701 | 1280 | 134662 | 7641.47 | 0.147476 | 5.99001 | 23.6854 | 4.87972 | 0.00602405 | 0.000232708 | 0.000153545 | 1(Win) | true |
| simdjson (ondemand) | 283.364 | 0.0780224 | 3003.95ms | 6701 | 640 | 198157 | 22552.5 | 0.217598 | 17.5415 | 81.7065 | 17.5406 | 0.0271529 | 0.000183042 | 9.70004e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 945.658 | 0.0571411 | 1462.45ms | 6701 | 4890 | 72915 | 6757.8 | 0.0250878 | 5.30136 | 21.5375 | 4.40502 | 0.00570144 | 7.52566e-05 | 3.32948e-05 | 1(Win) | true |
| simdjson (ondemand) | 293.546 | 0.10182 | 2963.44ms | 6701 | 640 | 314469 | 21770.3 | 0.0563668 | 17.0031 | 80.1064 | 17.1933 | 0.0271247 | 0.000185373 | 0.000110525 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3866.96 | 0.111897 | 869.767ms | 4857 | 4890 | 8784.98 | 1197.84 | 0.112835 | 1.33489 | 5.74861 | 0.992177 | 0.000398346 | 4.56407e-05 | 1.42311e-05 | 1(Win) | true |
| simdjson (ondemand) | 3419.7 | 0.153784 | 884.654ms | 4857 | 1280 | 5553.82 | 1354.5 | 0.0843964 | 1.5023 | 5.98579 | 0.853614 | 0.000389901 | 5.79061e-05 | 2.63795e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4399.55 | 0.122937 | 860.585ms | 4857 | 2560 | 4288.73 | 1052.83 | 0.0552518 | 1.17511 | 5.17912 | 0.867202 | 0.000428103 | 2.77467e-05 | 5.38849e-06 | 1(Win) | true |
| simdjson (ondemand) | 3769.05 | 0.161028 | 874.764ms | 4857 | 640 | 2506.42 | 1228.96 | 0.0857661 | 1.36897 | 5.43834 | 0.73111 | 0.00140165 | 3.28135e-05 | 9.97272e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4894.95 | 0.151259 | 879.172ms | 6701 | 2560 | 9983.1 | 1305.54 | 0.266131 | 1.05077 | 4.5632 | 0.740337 | 0.000209565 | 3.59671e-05 | 8.51086e-06 | 1(Win) | true |
| simdjson (ondemand) | 4367.27 | 0.136066 | 894.586ms | 6701 | 1280 | 5074.22 | 1463.29 | 0.0349827 | 1.16848 | 4.76601 | 0.637368 | 0.000449443 | 1.8071e-05 | 1.98198e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5485.45 | 0.1119 | 866.161ms | 6701 | 4890 | 8310.45 | 1165 | 0.3996 | 0.941857 | 4.15565 | 0.649754 | 0.000594545 | 2.11488e-05 | 5.40163e-06 | 1(Win) | true |
| simdjson (ondemand) | 4835.79 | 0.074916 | 885.312ms | 6701 | 4890 | 4792.95 | 1321.52 | 0.0985765 | 1.0593 | 4.3692 | 0.548575 | 0.000534578 | 1.78223e-05 | 4.45558e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2786.98 | 0.385384 | 911.683ms | 4857 | 80 | 3282.06 | 1662.01 | 0.0653899 | 1.82754 | 7.7064 | 1.46922 | 0.000512147 | 2.83097e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1943.23 | 0.103763 | 986.327ms | 4857 | 2560 | 15660.7 | 2383.66 | 0.0890857 | 2.60222 | 10.5073 | 1.80152 | 0.00105309 | 4.4073e-05 | 1.42353e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3100.84 | 0.131014 | 905.056ms | 4857 | 2560 | 9805.17 | 1493.79 | 0.065306 | 1.65435 | 7.15359 | 1.3426 | 0.00103837 | 1.78544e-05 | 3.21701e-06 | 1(Win) | true |
| simdjson (ondemand) | 2064.01 | 0.143425 | 969.506ms | 4857 | 40 | 414.404 | 2244.18 | 0.0575233 | 2.45029 | 9.95038 | 1.67902 | 0.00171402 | 2.05888e-05 | 1.02944e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3555.83 | 0.0901379 | 929.198ms | 6701 | 4890 | 12832.8 | 1797.21 | 0.0639769 | 1.43022 | 6.03641 | 1.10461 | 0.000379579 | 2.67945e-05 | 7.99563e-06 | 1(Win) | true |
| simdjson (ondemand) | 2602.38 | 0.122883 | 992.736ms | 6701 | 1280 | 11655.4 | 2455.66 | 0.0173417 | 1.95066 | 7.96777 | 1.30891 | 0.000784281 | 5.46793e-05 | 2.77477e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3838.59 | 0.0995374 | 922.414ms | 6701 | 4890 | 13428.2 | 1664.82 | 0.0983878 | 1.3246 | 5.63573 | 1.01283 | 0.000778262 | 2.31019e-05 | 5.79836e-06 | 1(Win) | true |
| simdjson (ondemand) | 2727.03 | 0.0638132 | 982.154ms | 6701 | 4890 | 10935.3 | 2343.42 | 0.0662746 | 1.85204 | 7.5641 | 1.22012 | 0.00149173 | 1.79139e-05 | 4.54713e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1225.33 | 0.191299 | 887.072ms | 1691 | 30 | 190.162 | 1316.1 | 0.0709669 | 4.18315 | 14.6688 | 2.8971 | 0.000611078 | 7.88488e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1107.72 | 0.125692 | 896.816ms | 1691 | 4890 | 16373.8 | 1455.84 | 0.175957 | 4.64135 | 15.88 | 3.08989 | 0.000908092 | 0.000239933 | 0.000125287 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1373.27 | 0.373823 | 877.61ms | 1691 | 1280 | 24667 | 1174.32 | 0.104605 | 3.75581 | 13.3418 | 2.5618 | 0.0006177 | 0.000171404 | 5.68266e-05 | 1(Win) | true |
| simdjson (ondemand) | 1255.26 | 0.20372 | 879.278ms | 1691 | 40 | 273.999 | 1284.72 | 0.0395518 | 4.0864 | 14.4021 | 2.72501 | 0.000975754 | 5.91366e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1512.55 | 0.0851453 | 886.576ms | 2158 | 80 | 107.373 | 1360.64 | 0.33055 | 3.4449 | 12.0876 | 2.37905 | 0.000915199 | 4.05468e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1389.12 | 0.187025 | 897.147ms | 2158 | 30 | 230.326 | 1481.53 | 0.233446 | 3.67411 | 12.7813 | 2.44995 | 0.000463392 | 0 | 0 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1676.09 | 0.250116 | 877.564ms | 2158 | 2560 | 24145.3 | 1227.87 | 0.200687 | 3.1093 | 10.9481 | 2.09361 | 0.000889858 | 0.000143724 | 5.43038e-05 | 1(Win) | true |
| simdjson (ondemand) | 1583.86 | 0.12279 | 888.535ms | 2158 | 2560 | 6516.83 | 1299.38 | 0.0553756 | 3.27351 | 11.5236 | 2.14133 | 0.00113893 | 0.00013757 | 5.08645e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 850.747 | 0.223286 | 934.482ms | 1691 | 2560 | 45861.6 | 1895.58 | 0.0051309 | 6.00105 | 20.838 | 4.20343 | 0.00232458 | 9.4249e-05 | 1.22431e-05 | 1(Win) | true |
| simdjson (ondemand) | 637.66 | 0.264513 | 997.511ms | 1691 | 640 | 28640.7 | 2529.03 | 0.0258936 | 7.96127 | 29.6357 | 5.94974 | 0.00339573 | 0.000229154 | 0.000111805 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.559 | 0.20701 | 926.486ms | 1691 | 30 | 351.306 | 1653.07 | 0.034268 | 5.41382 | 19.5103 | 3.86813 | 0.00240489 | 3.94244e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 702.617 | 0.180511 | 988.62ms | 1691 | 80 | 1373.24 | 2295.22 | 0.117774 | 7.33535 | 28.1573 | 5.58486 | 0.00119752 | 0.000273507 | 5.17445e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1006.75 | 0.158496 | 949.942ms | 2158 | 4890 | 51334.4 | 2044.24 | 0.0438278 | 5.09615 | 17.2294 | 3.54124 | 0.00182059 | 0.000222314 | 0.000108409 | 1(Win) | true |
| simdjson (ondemand) | 823.43 | 0.16839 | 990.375ms | 2158 | 80 | 1417.01 | 2499.34 | 0.435709 | 6.1944 | 23.4629 | 4.66728 | 0.00141335 | 5.7924e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1124.22 | 0.114763 | 939.96ms | 2158 | 40 | 176.548 | 1830.62 | 0.0586886 | 4.51628 | 16.0278 | 3.24328 | 0.000961538 | 0.000115848 | 0 | 1(Win) | true |
| simdjson (ondemand) | 862.833 | 0.586025 | 990.064ms | 2158 | 320 | 62521.8 | 2385.2 | 0.364464 | 5.87167 | 22.2048 | 4.35867 | 0.00113821 | 0.000141914 | 5.7924e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4384.27 | 0.197062 | 771.555ms | 1691 | 4890 | 2569.25 | 367.829 | 0.280601 | 1.27302 | 4.77824 | 0.795387 | 0.000603701 | 3.68848e-05 | 4.71642e-06 | 1(Win) | true |
| simdjson (ondemand) | 3818.25 | 0.186366 | 781.666ms | 1691 | 2560 | 1586.1 | 422.356 | 0.641323 | 1.43515 | 5.16381 | 0.742757 | 0.00059922 | 5.28995e-05 | 1.84802e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4809.25 | 0.759738 | 769.989ms | 1691 | 160 | 1038.43 | 335.325 | 0.0596081 | 1.19975 | 4.44766 | 0.720875 | 0.000609846 | 4.43525e-05 | 2.21762e-05 | 1(Win) | true |
| simdjson (ondemand) | 4125.91 | 0.195319 | 772.255ms | 1691 | 160 | 93.2514 | 390.863 | 0.146894 | 1.33666 | 4.84211 | 0.667652 | 0.00104598 | 4.06564e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5148.69 | 0.35737 | 782.641ms | 2158 | 2560 | 5223.79 | 399.719 | 0.106894 | 1.06966 | 4.07739 | 0.634384 | 0.000466107 | 3.45734e-05 | 8.32658e-06 | 1(Win) | true |
| simdjson (ondemand) | 4617.97 | 0.298792 | 787.064ms | 2158 | 320 | 567.399 | 445.656 | 0.329248 | 1.17722 | 4.30677 | 0.590825 | 0.000463392 | 1.4481e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5695.04 | 0.155645 | 776.168ms | 2158 | 4890 | 1547 | 361.372 | 0.325153 | 0.986126 | 3.81835 | 0.575996 | 0.000467277 | 3.94215e-05 | 1.0424e-05 | 1(Win) | true |
| simdjson (ondemand) | 5045.17 | 0.330707 | 785.343ms | 2158 | 640 | 1164.71 | 407.92 | 0.109812 | 1.08561 | 4.05471 | 0.53198 | 0.000473529 | 4.12709e-05 | 5.06835e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3091.15 | 0.308662 | 794.425ms | 1691 | 320 | 829.783 | 521.703 | 0.102324 | 1.77034 | 6.95446 | 1.30278 | 0.000611694 | 3.69604e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2320.92 | 0.133233 | 812.985ms | 1691 | 4890 | 4190.79 | 694.837 | 0.0946886 | 2.2876 | 8.69013 | 1.51094 | 0.00163176 | 5.17596e-05 | 1.34236e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3159.09 | 0.147685 | 792.657ms | 1691 | 4890 | 2779.35 | 510.483 | 0.225403 | 1.70773 | 6.62389 | 1.22827 | 0.00101875 | 5.06712e-05 | 1.2698e-05 | 1(Win) | true |
| simdjson (ondemand) | 2451.68 | 0.129003 | 808.553ms | 1691 | 4890 | 3520.98 | 657.778 | 0.352081 | 2.15706 | 8.36842 | 1.43584 | 0.000962875 | 2.85404e-05 | 4.83735e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3650.63 | 0.316755 | 802.811ms | 2158 | 640 | 2040.78 | 563.747 | 0.0632332 | 1.46487 | 5.80399 | 1.04773 | 0.000531453 | 3.11342e-05 | 7.2405e-06 | 1(Win) | true |
| simdjson (ondemand) | 2917.17 | 0.195481 | 807.946ms | 2158 | 80 | 152.152 | 705.487 | 0.453866 | 1.81431 | 7.06302 | 1.18999 | 0.00055607 | 6.37164e-05 | 1.73772e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3885.92 | 0.154694 | 795.991ms | 2158 | 4890 | 3282.26 | 529.612 | 0.527352 | 1.38392 | 5.54495 | 0.989342 | 0.000480828 | 7.67582e-05 | 3.66734e-05 | 1(Win) | true |
| simdjson (ondemand) | 3043.63 | 0.140125 | 812.854ms | 2158 | 4890 | 4389.98 | 676.176 | 0.111203 | 1.73575 | 6.81094 | 1.13114 | 0.00060421 | 1.86683e-05 | 1.0424e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1302.44 | 0.0872586 | 1074.38ms | 4390 | 80 | 629.39 | 3214.45 | 0.166159 | 3.86107 | 17.8941 | 3.48109 | 0.000865604 | 3.41686e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1042.51 | 0.0922872 | 1147.83ms | 4390 | 640 | 8790.89 | 4015.92 | 0.00863675 | 4.8094 | 19.3984 | 3.63303 | 0.00279897 | 2.45587e-05 | 3.91515e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1436.44 | 0.145467 | 1066.97ms | 4390 | 640 | 11504.4 | 2914.58 | 0.0583615 | 3.51469 | 16.4884 | 3.16287 | 0.00168245 | 2.7406e-05 | 3.2033e-06 | 1(Win) | true |
| simdjson (ondemand) | 1134.63 | 0.0754371 | 1145.26ms | 4390 | 2560 | 19835.1 | 3689.88 | 0.0702972 | 4.42567 | 17.9112 | 3.30137 | 0.00310507 | 2.65162e-05 | 2.22452e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2480.19 | 0.0603811 | 1114.42ms | 9378 | 4890 | 23182.6 | 3606 | 0.0429124 | 2.02382 | 9.19279 | 1.68501 | 0.000891243 | 5.20515e-05 | 1.86007e-05 | 1(Win) | true |
| simdjson (ondemand) | 2083.92 | 0.104963 | 1182.03ms | 9378 | 640 | 12987.1 | 4291.69 | 0.0246055 | 2.40363 | 9.77959 | 1.72979 | 0.00184091 | 2.29926e-05 | 6.83115e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2741.04 | 0.110445 | 1104.71ms | 9378 | 1280 | 16622.3 | 3262.83 | 0.102041 | 1.83437 | 8.53508 | 1.53604 | 0.0011074 | 2.4992e-05 | 1.66613e-07 | 1(Win) | true |
| simdjson (ondemand) | 2250.51 | 0.050606 | 1175.64ms | 9378 | 4890 | 19777.4 | 3974.01 | 0.0428712 | 2.22765 | 9.08339 | 1.57454 | 0.00186729 | 1.62893e-05 | 2.85662e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 727.543 | 0.192929 | 1333.97ms | 4390 | 320 | 39441.9 | 5754.48 | 0.0074936 | 6.8983 | 29.7196 | 6.18383 | 0.012989 | 3.63041e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 627.605 | 0.058151 | 1415.67ms | 4390 | 40 | 601.908 | 6670.8 | 0.0419916 | 7.95681 | 31.8285 | 6.22825 | 0.00871868 | 3.98633e-05 | 5.69476e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 772.194 | 0.130367 | 1321.62ms | 4390 | 2560 | 127895 | 5421.73 | 0.000144096 | 6.46367 | 28.3144 | 5.8656 | 0.0120473 | 4.87614e-05 | 9.25399e-06 | 1(Win) | true |
| simdjson (ondemand) | 668.723 | 0.183674 | 1425.73ms | 4390 | 30 | 3966.93 | 6260.63 | 0.0399161 | 7.47517 | 30.3408 | 5.89658 | 0.00911162 | 3.03721e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1449.26 | 0.0815791 | 1371.07ms | 9378 | 2560 | 64882.4 | 6171.13 | 0.00312073 | 3.44687 | 14.7721 | 2.97835 | 0.00600479 | 3.66133e-05 | 1.1413e-05 | 1(Win) | true |
| simdjson (ondemand) | 1306.63 | 0.11729 | 1438.05ms | 9378 | 320 | 20624.9 | 6844.77 | 0.0263362 | 3.82096 | 15.4573 | 2.91309 | 0.0046815 | 1.7661e-05 | 1.33291e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1546.52 | 0.0590207 | 1346.13ms | 9378 | 4890 | 56967.1 | 5783 | 0.164612 | 3.23659 | 14.1145 | 2.82939 | 0.00559219 | 3.5566e-05 | 1.58095e-05 | 1(Win) | true |
| simdjson (ondemand) | 1383.3 | 0.0688435 | 1426.99ms | 9378 | 1280 | 25358.4 | 6465.36 | 0.0741881 | 3.61115 | 14.7609 | 2.75784 | 0.00465801 | 4.57354e-05 | 1.9827e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2120.61 | 0.0723513 | 960.775ms | 4390 | 4890 | 9977.24 | 1974.26 | 0.0618778 | 2.39286 | 10.9692 | 2.06105 | 0.00206483 | 4.1552e-05 | 1.08538e-05 | 1(Win) | true |
| simdjson (ondemand) | 1810.92 | 0.0650628 | 976.469ms | 4390 | 4890 | 11063.9 | 2311.88 | 0.14627 | 2.78893 | 11.5383 | 1.96333 | 0.00264251 | 3.18627e-05 | 8.38492e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2299.98 | 0.239635 | 933.28ms | 4390 | 160 | 3044.42 | 1820.29 | 0.098639 | 2.29161 | 10.6763 | 1.9918 | 0.00205438 | 5.41002e-05 | 1.13895e-05 | 1(Win) | true |
| simdjson (ondemand) | 1880.32 | 0.0552078 | 973.414ms | 4390 | 4890 | 7388.83 | 2226.55 | 0.0974474 | 2.68911 | 11.1802 | 1.88064 | 0.00310922 | 3.23751e-05 | 7.3601e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3872.67 | 0.0717091 | 999.341ms | 9378 | 4890 | 13410.9 | 2309.41 | 0.00600003 | 1.30447 | 5.90744 | 1.01173 | 0.00132 | 2.28529e-05 | 4.57931e-06 | 1(Win) | true |
| simdjson (ondemand) | 3541.3 | 0.0625556 | 1001.28ms | 9378 | 2560 | 6389.53 | 2525.5 | 0.174946 | 1.42511 | 6.10269 | 0.949136 | 0.000766755 | 1.02051e-05 | 1.2496e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4030.95 | 0.103849 | 998.845ms | 9378 | 2560 | 13590.9 | 2218.72 | 0.149251 | 1.25661 | 5.77063 | 0.979314 | 0.00117791 | 3.50721e-05 | 1.06216e-05 | 1(Win) | true |
| simdjson (ondemand) | 3698.43 | 0.0764077 | 992.68ms | 9378 | 2560 | 8739.76 | 2418.2 | 0.0247048 | 1.37593 | 5.93506 | 0.910429 | 0.00121228 | 1.10381e-05 | 6.66453e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1589.98 | 0.0768699 | 1007.52ms | 4390 | 4890 | 20033.9 | 2633.13 | 0.106039 | 3.16785 | 14.0838 | 2.78952 | 0.00370553 | 5.79957e-05 | 2.3897e-05 | 1(Win) | true |
| simdjson (ondemand) | 1496.99 | 0.0582034 | 1035.15ms | 4390 | 4890 | 12956.8 | 2796.7 | 0.0811575 | 3.36699 | 13.939 | 2.45604 | 0.00392121 | 3.41453e-05 | 2.23598e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1649.41 | 0.103892 | 1007.57ms | 4390 | 2560 | 17802.4 | 2538.26 | 0.0260169 | 3.05502 | 13.7909 | 2.72027 | 0.00332645 | 6.09517e-05 | 1.89529e-05 | 1(Win) | true |
| simdjson (ondemand) | 1551.57 | 0.07526 | 1024.11ms | 4390 | 2560 | 10557.3 | 2698.31 | 0.0285995 | 3.25407 | 13.5806 | 2.37335 | 0.00400813 | 4.53801e-05 | 1.59275e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3069.38 | 0.100506 | 1052.31ms | 9378 | 2560 | 21955.7 | 2913.8 | 0.00203768 | 1.64583 | 7.37108 | 1.37428 | 0.0021309 | 3.19065e-05 | 8.62224e-06 | 1(Win) | true |
| simdjson (ondemand) | 3047.63 | 0.0478234 | 1029.72ms | 9378 | 4890 | 9631.33 | 2934.59 | 0.103237 | 1.68785 | 7.19951 | 1.17445 | 0.00142879 | 2.09122e-05 | 5.2335e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3213.22 | 0.203117 | 1032.36ms | 9378 | 30 | 958.861 | 2783.37 | 0.188376 | 1.56787 | 7.20719 | 1.33653 | 0.00185896 | 7.10884e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3121.55 | 0.04541 | 1028.65ms | 9378 | 4890 | 8277.36 | 2865.1 | 0.186333 | 1.64432 | 7.05876 | 1.14108 | 0.00144364 | 1.1928e-05 | 1.41741e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1463.25 | 0.104611 | 1044ms | 4669 | 2560 | 25942 | 3043.01 | 0.0222896 | 3.50539 | 14.0105 | 2.94474 | 0.00193112 | 5.11184e-05 | 1.12109e-05 | 1(Win) | true |
| simdjson (ondemand) | 1427.73 | 0.066252 | 1051.01ms | 4669 | 4890 | 20876.8 | 3118.73 | 0.177308 | 3.57783 | 15.0979 | 2.52495 | 0.0022296 | 5.21212e-05 | 1.75197e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1575.08 | 0.061765 | 1024.56ms | 4669 | 4890 | 14908.7 | 2826.98 | 0.0116758 | 3.25816 | 13.2165 | 2.76912 | 0.00213346 | 2.85134e-05 | 3.46015e-06 | 1(Win) | true |
| simdjson (ondemand) | 1554.35 | 0.125637 | 1037.6ms | 4669 | 160 | 2072.57 | 2864.68 | 0.0644029 | 3.30173 | 14.3011 | 2.34676 | 0.00192091 | 3.74813e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2311.38 | 0.237408 | 1077.02ms | 7932 | 640 | 38636 | 3272.74 | 0.0551256 | 2.1904 | 9.45588 | 1.50441 | 0.000633707 | 1.06373e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 2281 | 0.0716077 | 1081.82ms | 7932 | 2560 | 14436.9 | 3316.33 | 0.299121 | 2.24527 | 8.81757 | 1.78013 | 0.00119315 | 2.02896e-05 | 3.20104e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2464.33 | 0.140325 | 1060.46ms | 7932 | 640 | 11874.5 | 3069.61 | 0.112114 | 2.04396 | 8.98626 | 1.39927 | 0.000728655 | 1.4577e-05 | 1.37891e-06 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 2451.33 | 0.323949 | 1056.71ms | 7932 | 320 | 31979.1 | 3085.9 | 0.107531 | 2.08786 | 8.35212 | 1.67625 | 0.00116695 | 1.73348e-05 | 0 | 1(Tie) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 530.851 | 0.152278 | 1588.56ms | 4669 | 640 | 104413 | 8387.87 | 0.0595709 | 9.40053 | 39.5008 | 8.05997 | 0.0109787 | 4.11625e-05 | 3.01189e-06 | 1(Win) | true |
| simdjson (ondemand) | 213.483 | 0.0643375 | 2838.38ms | 4669 | 1280 | 230493 | 20857.4 | 0.0375476 | 23.3608 | 98.777 | 21.0401 | 0.0521935 | 5.85645e-05 | 1.28842e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 550.727 | 0.216904 | 1563.16ms | 4669 | 1280 | 393661 | 8085.14 | 0.0345132 | 9.08225 | 38.7306 | 7.88456 | 0.0117504 | 3.86525e-05 | 3.6812e-06 | 1(Win) | true |
| simdjson (ondemand) | 216.115 | 0.0348078 | 2809.63ms | 4669 | 4890 | 251503 | 20603.4 | 0.131808 | 23.0506 | 97.9846 | 20.8619 | 0.0513717 | 5.01064e-05 | 6.5699e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 852.429 | 0.140674 | 1641.37ms | 7932 | 2560 | 398947 | 8874.11 | 0.0919888 | 5.87004 | 24.2249 | 4.97327 | 0.00570774 | 3.71813e-05 | 1.07358e-05 | 1(Win) | true |
| simdjson (ondemand) | 364.726 | 0.0329131 | 2809.46ms | 7932 | 4890 | 227866 | 20740.3 | 0.0190134 | 13.7397 | 57.9385 | 12.2321 | 0.0344476 | 5.92717e-05 | 2.37706e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 878.245 | 0.0632407 | 1618.94ms | 7932 | 4890 | 145090 | 8613.25 | 0.0587654 | 5.68267 | 23.7685 | 4.86926 | 0.00570004 | 4.64583e-05 | 1.41798e-05 | 1(Win) | true |
| simdjson (ondemand) | 372.94 | 0.0788506 | 2780.48ms | 7932 | 1280 | 327422 | 20283.5 | 0.596248 | 13.534 | 57.4842 | 12.1299 | 0.0339724 | 4.75723e-05 | 1.4774e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 4218.75 | 0.269016 | 845.651ms | 4669 | 320 | 2579.81 | 1055.46 | 0.0859371 | 1.22171 | 5.47355 | 0.920326 | 0.00109566 | 2.14179e-05 | 3.34654e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4193.94 | 0.180625 | 845.07ms | 4669 | 640 | 2353.65 | 1061.7 | 0.30079 | 1.24774 | 5.59028 | 0.722211 | 0.000919964 | 2.67723e-05 | 8.0317e-06 | 1(Tie) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4630.46 | 0.115213 | 836.629ms | 4669 | 4890 | 6002.25 | 961.613 | 0.310867 | 1.13529 | 5.21375 | 0.863783 | 0.0011881 | 3.69666e-05 | 1.56802e-05 | 1(Win) | true |
| simdjson (ondemand) | 4450.58 | 0.16838 | 839.461ms | 4669 | 1280 | 3632.5 | 1000.48 | 0.0199865 | 1.16858 | 5.33091 | 0.663954 | 0.00114937 | 2.20872e-05 | 3.17921e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 6209.89 | 0.193536 | 862.002ms | 7932 | 160 | 889.281 | 1218.14 | 0.0569839 | 0.842436 | 3.85401 | 0.444655 | 0.000599628 | 2.20625e-05 | 7.87948e-06 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 6191.34 | 0.275041 | 863.151ms | 7932 | 160 | 1806.81 | 1221.79 | 0.106798 | 0.848433 | 3.77395 | 0.567322 | 0.00119374 | 3.073e-05 | 1.41831e-05 | 1(Tie) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6649.95 | 0.15496 | 855.201ms | 7932 | 2560 | 7954.41 | 1137.53 | 0.00886041 | 0.785148 | 3.61977 | 0.534166 | 0.000768052 | 1.92062e-05 | 4.92467e-06 | 1(Win) | true |
| simdjson (ondemand) | 6594.78 | 0.114776 | 853.487ms | 7932 | 40 | 69.3308 | 1147.05 | 0.146969 | 0.79421 | 3.70134 | 0.410363 | 0.000630358 | 1.26072e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2985.39 | 0.151597 | 889.641ms | 4669 | 2560 | 13087.8 | 1491.5 | 0.164902 | 1.74426 | 7.75991 | 1.50375 | 0.00162541 | 2.21708e-05 | 2.25892e-06 | 1(Win) | true |
| simdjson (ondemand) | 2384.79 | 0.109137 | 924.609ms | 4669 | 2560 | 10630 | 1867.12 | 0.0244091 | 2.16184 | 9.60313 | 1.60805 | 0.00270518 | 5.31263e-05 | 2.51827e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3069.39 | 0.116157 | 889.338ms | 4669 | 4890 | 13884.9 | 1450.68 | 0.00381558 | 1.67186 | 7.49882 | 1.44592 | 0.00178224 | 1.4629e-05 | 2.05857e-06 | 1(Win) | true |
| simdjson (ondemand) | 2532.66 | 0.263233 | 918.049ms | 4669 | 640 | 13707.4 | 1758.11 | 0.641262 | 2.06153 | 9.34376 | 1.5498 | 0.00231848 | 2.37604e-05 | 6.02377e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4567.94 | 0.169933 | 909.928ms | 7932 | 1280 | 10136.6 | 1656.01 | 0.740647 | 1.11627 | 5.13174 | 0.920575 | 0.000940711 | 3.59501e-05 | 1.95017e-05 | 1(Win) | true |
| simdjson (ondemand) | 3723.66 | 0.136209 | 950.14ms | 7932 | 640 | 4900.25 | 2031.48 | 0.0713256 | 1.38455 | 6.19743 | 0.962053 | 0.00155817 | 1.14252e-05 | 2.56083e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4811.54 | 0.169569 | 908.78ms | 7932 | 2560 | 18194 | 1572.17 | 0.201112 | 1.07472 | 4.97806 | 0.886536 | 0.00124382 | 2.89571e-05 | 1.29026e-05 | 1(Win) | true |
| simdjson (ondemand) | 3800.56 | 0.214231 | 942.275ms | 7932 | 40 | 727.266 | 1990.38 | 0.232068 | 1.33418 | 6.04476 | 0.927761 | 0.00122605 | 3.78215e-05 | 2.52143e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 542.307 | 0.107598 | 1562.92ms | 4604 | 1280 | 97140.7 | 8096.37 | 0.00663922 | 9.3009 | 36.4712 | 6.97309 | 0.0106572 | 0.000295429 | 0.000163241 | 1(Win) | true |
| Jsonifier (generic) | 529.924 | 0.0983972 | 1580.23ms | 4604 | 1280 | 85078.3 | 8285.56 | 0.161654 | 9.43394 | 35.8851 | 7.5921 | 0.00950651 | 8.2469e-05 | 2.74897e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 599.25 | 0.177697 | 1570.02ms | 4604 | 160 | 27122.9 | 7327.02 | 0.815416 | 8.34488 | 32.4567 | 6.06346 | 0.00925961 | 8.6881e-05 | 2.98653e-05 | 1(Win) | true |
| Jsonifier (generic) | 593.75 | 0.0616354 | 1588.85ms | 4604 | 4890 | 101586 | 7394.89 | 0.11477 | 8.48769 | 31.6348 | 6.63065 | 0.00942872 | 0.000306704 | 0.00018309 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2022.38 | 0.22526 | 1627.12ms | 18245 | 320 | 120194 | 8603.62 | 0.0266532 | 2.51624 | 9.95884 | 1.96432 | 0.00256697 | 5.70362e-05 | 2.98027e-05 | 1(Win) | true |
| simdjson (ondemand) | 1947.82 | 0.150919 | 1632.65ms | 18245 | 640 | 116321 | 8932.94 | 0.337126 | 2.55721 | 10.2193 | 1.79452 | 0.00251199 | 4.26487e-05 | 1.83269e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2220.79 | 0.0515766 | 1633.07ms | 18245 | 4890 | 79852.2 | 7834.94 | 0.0467512 | 2.25042 | 8.8863 | 1.72171 | 0.00240721 | 2.1935e-05 | 4.25923e-06 | 1(Win) | true |
| simdjson (ondemand) | 2198.39 | 0.0993638 | 1649.04ms | 18245 | 1280 | 79167.1 | 7914.79 | 0.188462 | 2.27215 | 9.22746 | 1.56997 | 0.0022397 | 1.70852e-05 | 2.74048e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 299.562 | 0.194563 | 2210.57ms | 4604 | 320 | 260235 | 14657.1 | 0.108491 | 16.6765 | 68.0954 | 15.035 | 0.0246918 | 0.000132358 | 5.56581e-05 | 1(Win) | true |
| simdjson (ondemand) | 218.26 | 0.0345706 | 2769.23ms | 4604 | 4890 | 236509 | 20116.9 | 0.0224491 | 22.7588 | 106.913 | 22.4303 | 0.0236573 | 0.000303639 | 0.000149998 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 322.632 | 0.0458914 | 2211.07ms | 4604 | 4890 | 190734 | 13609.1 | 0.0274843 | 15.4876 | 63.813 | 14.0626 | 0.0233684 | 0.00012055 | 3.42016e-05 | 1(Win) | true |
| simdjson (ondemand) | 228.129 | 0.0279061 | 2778.31ms | 4604 | 4890 | 141065 | 19246.7 | 0.393366 | 21.7875 | 102.594 | 21.4516 | 0.0227696 | 0.000100517 | 2.8605e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1134.88 | 0.176721 | 2288.25ms | 18245 | 320 | 234918 | 15331.8 | 0.257849 | 4.38137 | 18.1262 | 3.87186 | 0.00593073 | 1.67854e-05 | 4.79583e-06 | 1(Win) | true |
| simdjson (ondemand) | 836.127 | 0.113723 | 2832.56ms | 18245 | 320 | 179222 | 20810 | 0.127716 | 5.9453 | 27.9426 | 5.68446 | 0.00565155 | 2.41505e-05 | 7.53631e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1212.63 | 0.228847 | 2307.84ms | 18245 | 320 | 345044 | 14348.9 | 0.0251608 | 4.12255 | 17.0431 | 3.62604 | 0.00580553 | 5.92628e-05 | 2.68909e-05 | 1(Win) | true |
| simdjson (ondemand) | 869.894 | 0.0899943 | 2841.75ms | 18245 | 640 | 207379 | 20002.2 | 0.0229559 | 5.72488 | 26.8564 | 5.43864 | 0.00531918 | 7.69903e-05 | 4.18779e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3704.69 | 0.284264 | 866.444ms | 4604 | 320 | 3632.12 | 1185.18 | 0.498743 | 1.38657 | 6.67333 | 1.18245 | 0.000657716 | 4.4798e-05 | 1.56114e-05 | 1(Win) | true |
| simdjson (ondemand) | 3638.68 | 0.192812 | 864.689ms | 4604 | 1280 | 6928.87 | 1206.68 | 0.227767 | 1.41957 | 7.04648 | 0.979366 | 0.000556921 | 1.51024e-05 | 2.37565e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3862.78 | 0.198828 | 860.271ms | 4604 | 640 | 3268.94 | 1136.67 | 0.1083 | 1.33977 | 6.59231 | 1.16421 | 0.000451034 | 1.56114e-05 | 6.78758e-07 | 1(Win) | true |
| simdjson (ondemand) | 3711.74 | 0.232445 | 864.406ms | 4604 | 1280 | 9677.56 | 1182.93 | 0.187851 | 1.38273 | 6.96525 | 0.960687 | 0.000442041 | 1.20479e-05 | 2.71503e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10215.2 | 0.136535 | 919.378ms | 18245 | 1280 | 6922.96 | 1703.32 | 0.307912 | 0.498911 | 2.4575 | 0.323541 | 0.000150469 | 8.82091e-06 | 1.4987e-06 | 1(Win) | true |
| simdjson (ondemand) | 9421.61 | 0.0655832 | 934.031ms | 18245 | 4890 | 7173.51 | 1846.8 | 0.0343297 | 0.539541 | 2.80285 | 0.285119 | 0.000146417 | 7.70024e-06 | 7.50969e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10395.2 | 0.231799 | 919.424ms | 18245 | 40 | 602.148 | 1673.83 | 0.0333679 | 0.489352 | 2.4376 | 0.318937 | 0.000143875 | 1.50726e-05 | 1.09619e-05 | 1(Win) | true |
| simdjson (ondemand) | 9582.11 | 0.0661733 | 930.019ms | 18245 | 4890 | 7060.57 | 1815.86 | 0.0274691 | 0.531929 | 2.78235 | 0.280406 | 0.000150362 | 8.10374e-06 | 1.07602e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2649 | 0.173772 | 910.459ms | 4604 | 30 | 248.879 | 1657.5 | 0.122825 | 1.92039 | 9.66051 | 1.92637 | 0.000731248 | 3.62004e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1753.8 | 0.332008 | 992.428ms | 4604 | 160 | 11054.1 | 2503.54 | 0.273861 | 2.87693 | 13.4196 | 2.38749 | 0.00139553 | 5.29431e-05 | 1.22176e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2711.63 | 0.137633 | 930.146ms | 4604 | 640 | 3178.59 | 1619.22 | 0.00135094 | 1.88581 | 9.5821 | 1.90769 | 0.000658055 | 1.69689e-05 | 1.35752e-06 | 1(Win) | true |
| simdjson (ondemand) | 1837.42 | 0.101883 | 986.508ms | 4604 | 2560 | 15173.9 | 2389.62 | 0.451915 | 2.7862 | 13.3386 | 2.36881 | 0.00134352 | 1.17934e-05 | 7.63602e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7774.15 | 0.188581 | 972.134ms | 18245 | 1280 | 22802.7 | 2238.16 | 0.511143 | 0.653268 | 3.21392 | 0.51225 | 0.000287279 | 1.15186e-05 | 2.44074e-06 | 1(Win) | true |
| simdjson (ondemand) | 5635.06 | 0.189457 | 1057.76ms | 18245 | 2560 | 87609.5 | 3087.77 | 0.0730479 | 0.902309 | 4.41113 | 0.64045 | 0.000369558 | 9.29193e-06 | 1.39165e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8036.99 | 0.328387 | 965.108ms | 18245 | 80 | 4043.56 | 2164.96 | 0.0109714 | 0.629639 | 3.19414 | 0.507536 | 0.000279529 | 1.84982e-05 | 4.11072e-06 | 1(Win) | true |
| simdjson (ondemand) | 5706.32 | 0.186222 | 1059.96ms | 18245 | 640 | 20635.5 | 3049.21 | 0.0966016 | 0.882753 | 4.39068 | 0.635736 | 0.000377158 | 9.24911e-06 | 1.19896e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1256.16 | 0.0846874 | 1131.7ms | 4926 | 2560 | 25679 | 3739.81 | 0.157697 | 4.02171 | 16.8061 | 3.33212 | 0.00446007 | 5.4161e-05 | 6.66108e-06 | 1(Win) | true |
| simdjson (ondemand) | 1020.29 | 0.0619491 | 1210.22ms | 4926 | 2560 | 20828.3 | 4604.39 | 0.241034 | 4.91628 | 18.4919 | 3.50426 | 0.00492468 | 6.19322e-05 | 1.42738e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1580.4 | 0.187451 | 1092.7ms | 4926 | 640 | 19870.4 | 2972.53 | 0.133598 | 3.27624 | 14.2138 | 2.75639 | 0.00419458 | 0.000100868 | 4.69448e-05 | 1(Win) | true |
| simdjson (ondemand) | 1206.29 | 0.0910284 | 1182.21ms | 4926 | 1280 | 16086 | 3894.41 | 0.108311 | 4.1762 | 15.8829 | 2.93037 | 0.00502817 | 4.96409e-05 | 4.44072e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1974.47 | 0.0581244 | 1146.37ms | 8150 | 4890 | 25600.1 | 3936.48 | 0.254626 | 2.54164 | 10.6524 | 2.02847 | 0.00259837 | 3.04616e-05 | 7.90395e-06 | 1(Win) | true |
| simdjson (ondemand) | 1644.55 | 0.0734716 | 1221.84ms | 8150 | 2560 | 30867.4 | 4726.18 | 0.0367437 | 3.07002 | 11.7091 | 2.1373 | 0.00289863 | 2.88056e-05 | 6.23083e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2403.16 | 0.170161 | 1117.12ms | 8150 | 640 | 19384.3 | 3234.27 | 0.0911488 | 2.09687 | 9.08479 | 1.68025 | 0.00235583 | 4.6204e-05 | 2.14724e-05 | 1(Win) | true |
| simdjson (ondemand) | 1916.66 | 0.0566528 | 1198.23ms | 8150 | 4890 | 25809.2 | 4055.19 | 0.299359 | 2.64097 | 10.1395 | 1.79178 | 0.00288876 | 4.24053e-05 | 8.53125e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 782.494 | 0.112781 | 1358.29ms | 4926 | 40 | 1833.83 | 6003.62 | 0.00874548 | 6.5173 | 27.6711 | 5.6689 | 0.010003 | 7.10516e-05 | 5.07511e-06 | 1(Win) | true |
| simdjson (ondemand) | 421.813 | 0.0885568 | 1867.81ms | 4926 | 1280 | 124509 | 11137.2 | 0.160717 | 11.9023 | 48.2732 | 9.94113 | 0.0311249 | 0.000158439 | 7.26375e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 869.733 | 0.0603356 | 1324.75ms | 4926 | 4890 | 51936.7 | 5401.43 | 0.26383 | 5.83111 | 25.0775 | 5.09704 | 0.0103159 | 0.000125373 | 5.89917e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.115 | 0.0445258 | 1834.1ms | 4926 | 4890 | 105135 | 10413.8 | 0.104132 | 11.1361 | 45.6797 | 9.36988 | 0.0288995 | 8.55193e-05 | 3.84422e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1188.29 | 0.0879504 | 1413.96ms | 8150 | 2560 | 84720.5 | 6540.89 | 0.109737 | 4.22946 | 17.508 | 3.5708 | 0.00621276 | 0.000100412 | 5.26265e-05 | 1(Win) | true |
| simdjson (ondemand) | 691.347 | 0.0658139 | 1880.03ms | 8150 | 1280 | 70075.7 | 11242.5 | 0.0147273 | 7.2513 | 29.4594 | 5.96859 | 0.0183191 | 4.18903e-05 | 1.30368e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1325.69 | 0.0793665 | 1376.26ms | 8150 | 2560 | 55429.9 | 5862.93 | 0.135713 | 3.77506 | 15.9428 | 3.22601 | 0.00615452 | 4.68271e-05 | 9.34624e-06 | 1(Win) | true |
| simdjson (ondemand) | 740.566 | 0.0411266 | 1840.61ms | 8150 | 4890 | 91105.1 | 10495.3 | 0.40596 | 6.78446 | 27.8945 | 5.62393 | 0.0175907 | 6.62426e-05 | 2.75258e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2402.87 | 0.0937998 | 940.037ms | 4926 | 4890 | 16445.4 | 1955.08 | 0.14869 | 2.12637 | 9.56618 | 1.76147 | 0.00158709 | 5.9988e-05 | 2.61124e-05 | 1(Win) | true |
| simdjson (ondemand) | 1995.37 | 0.144859 | 984.51ms | 4926 | 40 | 465.259 | 2354.35 | 0.144911 | 2.5319 | 10.1411 | 1.70686 | 0.00204019 | 6.59765e-05 | 3.55258e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2594.37 | 0.195756 | 939.892ms | 4926 | 30 | 376.944 | 1810.77 | 0.268042 | 1.96596 | 8.9998 | 1.62363 | 0.00213831 | 6.76682e-06 | 6.76682e-06 | 1(Win) | true |
| simdjson (ondemand) | 2164.15 | 0.0718768 | 973.122ms | 4926 | 4890 | 11904.2 | 2170.74 | 0.118508 | 2.36136 | 9.56841 | 1.5678 | 0.00264686 | 4.12651e-05 | 1.39903e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3538.42 | 0.17424 | 964.618ms | 8150 | 1280 | 18750.1 | 2196.59 | 0.114584 | 1.43995 | 6.35742 | 1.09693 | 0.00139254 | 5.77071e-05 | 3.50844e-05 | 1(Win) | true |
| simdjson (ondemand) | 3084.72 | 0.0939212 | 995.95ms | 8150 | 2560 | 14336.8 | 2519.66 | 0.087576 | 1.65059 | 6.56049 | 1.02994 | 0.00169694 | 5.04697e-05 | 2.75115e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3788.04 | 0.0977803 | 961.647ms | 8150 | 2560 | 10304.6 | 2051.84 | 0.0739212 | 1.34482 | 6.01141 | 1.01362 | 0.00177842 | 2.50671e-05 | 7.8125e-06 | 1(Win) | true |
| simdjson (ondemand) | 3333.98 | 0.0631386 | 989.019ms | 8150 | 4890 | 10594.7 | 2331.28 | 0.204185 | 1.52483 | 6.21436 | 0.94589 | 0.00180627 | 2.26831e-05 | 7.67812e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1795.25 | 0.0993153 | 1006.83ms | 4926 | 2560 | 17290.6 | 2616.79 | 0.0886214 | 2.83065 | 12.5978 | 2.44986 | 0.00318035 | 3.63188e-05 | 1.1419e-05 | 1(Win) | true |
| simdjson (ondemand) | 1442.86 | 0.0493558 | 1068.34ms | 4926 | 4890 | 12627.8 | 3255.9 | 0.257913 | 3.53581 | 14.4844 | 2.64657 | 0.00686637 | 7.896e-05 | 3.32114e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1909.59 | 0.0688071 | 998.592ms | 4926 | 4890 | 14011.5 | 2460.11 | 0.0786549 | 2.67545 | 11.9931 | 2.30512 | 0.00438789 | 2.1795e-05 | 3.36265e-06 | 1(Win) | true |
| simdjson (ondemand) | 1522.82 | 0.132719 | 1060.42ms | 4926 | 4890 | 81972.4 | 3084.93 | 0.00396304 | 3.35005 | 13.8715 | 2.50081 | 0.00731194 | 5.42176e-05 | 2.10892e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2773.93 | 0.213381 | 1019.76ms | 8150 | 160 | 5719.47 | 2801.96 | 0.142514 | 1.84841 | 8.21963 | 1.52982 | 0.00190951 | 1.91718e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2252.42 | 0.0573568 | 1095.02ms | 8150 | 4890 | 19155.5 | 3450.7 | 0.0570776 | 2.23099 | 9.22577 | 1.60577 | 0.00421163 | 2.16543e-05 | 5.14384e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2893.33 | 0.273392 | 1028.31ms | 8150 | 320 | 17260 | 2686.33 | 0.0358424 | 1.7762 | 7.85411 | 1.44233 | 0.00288842 | 1.18865e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2387.87 | 0.0819016 | 1088.28ms | 8150 | 30 | 213.206 | 3254.97 | 0.00716802 | 2.10727 | 8.85534 | 1.51767 | 0.00423313 | 0.000163599 | 3.68098e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2090.17 | 0.153989 | 878.717ms | 2821 | 40 | 157.138 | 1287.12 | 0.341326 | 2.4507 | 9.18929 | 1.72669 | 0.000708968 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1916.79 | 0.127337 | 887.621ms | 2821 | 4890 | 15619.8 | 1403.56 | 0.120979 | 2.66624 | 9.46189 | 1.58171 | 0.000735428 | 4.96568e-05 | 9.27893e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2299.3 | 0.446844 | 867.916ms | 2821 | 160 | 4373.66 | 1170.06 | 0.0709932 | 2.23711 | 8.61928 | 1.581 | 0.000374424 | 5.98192e-05 | 6.64658e-06 | 1(Win) | true |
| simdjson (ondemand) | 2084.23 | 0.127915 | 878.982ms | 2821 | 4890 | 13331.1 | 1290.8 | 0.112824 | 2.47797 | 9.02552 | 1.47111 | 0.000715783 | 3.73332e-05 | 4.92943e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2709.52 | 0.174899 | 894.713ms | 3770 | 30 | 161.582 | 1326.93 | 0.320513 | 1.89004 | 7.17374 | 1.28806 | 0.000548187 | 2.65252e-05 | 8.84173e-06 | 1(Win) | true |
| simdjson (ondemand) | 2454.84 | 0.227694 | 896.044ms | 3770 | 30 | 333.628 | 1464.6 | 0.326664 | 2.07866 | 7.46074 | 1.20504 | 0.000875332 | 2.65252e-05 | 8.84173e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2963.68 | 0.0879353 | 902.856ms | 3770 | 160 | 182.082 | 1213.14 | 0.0298901 | 1.7343 | 6.78912 | 1.1878 | 0.00026691 | 1.82361e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2662.69 | 0.165061 | 887.151ms | 3770 | 2560 | 12716.5 | 1350.27 | 0.167115 | 1.93378 | 7.13157 | 1.12122 | 0.000270225 | 3.24312e-05 | 3.21204e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 757.211 | 0.396052 | 1104.12ms | 2821 | 320 | 63361.6 | 3552.93 | 0.0492795 | 6.66455 | 26.6221 | 5.11415 | 0.00225097 | 0.000140686 | 6.64658e-05 | 1(Win) | true |
| simdjson (ondemand) | 325.729 | 0.047377 | 1568.04ms | 2821 | 4890 | 74875.1 | 8259.36 | 0.0425434 | 15.358 | 63.9724 | 13.5888 | 0.0114006 | 0.000185651 | 9.38767e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.114 | 0.136102 | 1094.64ms | 2821 | 2560 | 55118.1 | 3409.28 | 0.730065 | 6.45535 | 26.1056 | 4.97944 | 0.00251919 | 7.40817e-05 | 1.08007e-05 | 1(Win) | true |
| simdjson (ondemand) | 326.923 | 0.0766846 | 1577.16ms | 2821 | 1280 | 50973.2 | 8229.21 | 0.133047 | 15.2755 | 63.5945 | 13.4913 | 0.0109129 | 8.03128e-05 | 1.8832e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 977.29 | 0.145829 | 1121.33ms | 3770 | 2560 | 73682.6 | 3678.9 | 0.0641127 | 5.13423 | 20.5369 | 3.9687 | 0.0013273 | 5.98889e-05 | 1.08795e-05 | 1(Win) | true |
| simdjson (ondemand) | 443.007 | 0.0424201 | 1562.6ms | 3770 | 4890 | 57958.2 | 8115.8 | 0.069177 | 11.289 | 47.5536 | 10.0409 | 0.0078155 | 0.000118197 | 6.22176e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1000.09 | 0.152802 | 1117.04ms | 3770 | 2560 | 77250 | 3595.02 | 0.282512 | 5.00952 | 20.1504 | 3.86791 | 0.0018147 | 5.61588e-05 | 1.23301e-05 | 1(Win) | true |
| simdjson (ondemand) | 456.876 | 0.394595 | 1570.12ms | 3770 | 40 | 38569.9 | 7869.43 | 0.402574 | 11.1013 | 47.2708 | 9.96791 | 0.00753316 | 0.000112732 | 3.97878e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5314.96 | 0.213169 | 793.731ms | 2821 | 320 | 372.567 | 506.178 | 0.265381 | 1.01085 | 3.98121 | 0.597306 | 0.000707861 | 5.42804e-05 | 2.21553e-05 | 1(Win) | true |
| simdjson (ondemand) | 4928.85 | 0.128206 | 796.478ms | 2821 | 4890 | 2394.64 | 545.83 | 0.234927 | 1.08714 | 4.17122 | 0.464729 | 0.00052513 | 1.85579e-05 | 2.82717e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5422.22 | 0.136521 | 793.392ms | 2821 | 4890 | 2243.68 | 496.165 | 0.146843 | 0.99115 | 3.90819 | 0.580291 | 0.000708389 | 3.87105e-05 | 1.15987e-05 | 1(Win) | true |
| simdjson (ondemand) | 5118.01 | 0.924752 | 791.322ms | 2821 | 160 | 3780.72 | 525.656 | 0.0392521 | 1.06647 | 4.09642 | 0.447359 | 0.000445321 | 1.32932e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6610.57 | 0.197399 | 796.108ms | 3770 | 4890 | 5636.41 | 543.88 | 0.228242 | 0.812438 | 3.34377 | 0.459151 | 0.000266879 | 2.98341e-05 | 8.2993e-06 | 1(Win) | true |
| simdjson (ondemand) | 6045.39 | 0.136706 | 797.052ms | 3770 | 4890 | 3232.34 | 594.726 | 0.173899 | 0.891431 | 3.48621 | 0.364191 | 0.000369725 | 3.0051e-05 | 7.37715e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6745.34 | 0.375093 | 793.335ms | 3770 | 160 | 639.547 | 533.013 | 0.0257901 | 0.793297 | 3.28913 | 0.446421 | 0.000271883 | 2.98408e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6222.89 | 0.228674 | 797.808ms | 3770 | 2560 | 4468.6 | 577.763 | 0.454361 | 0.867414 | 3.43024 | 0.351194 | 0.000383061 | 1.59566e-05 | 1.96867e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3916.89 | 0.244433 | 813.867ms | 2821 | 40 | 112.746 | 686.85 | 0.602968 | 1.36767 | 5.57285 | 0.97235 | 0.0008419 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3392.02 | 0.136035 | 817.03ms | 2821 | 2560 | 2980.09 | 793.131 | 0.0467666 | 1.56312 | 6.35697 | 0.949309 | 0.00107647 | 2.45093e-05 | 1.66164e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3844.92 | 0.616375 | 807.221ms | 2821 | 640 | 11904.2 | 699.706 | 0.308106 | 1.37298 | 5.5016 | 0.954981 | 0.00111939 | 1.60626e-05 | 5.53882e-07 | 1(Win) | true |
| simdjson (ondemand) | 3450.97 | 0.119503 | 817.251ms | 2821 | 4890 | 4244.18 | 779.583 | 0.11306 | 1.53322 | 6.28218 | 0.931941 | 0.00107679 | 4.47998e-05 | 1.7253e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4729.93 | 0.257586 | 817.384ms | 3770 | 2560 | 9814.27 | 760.129 | 0.00652602 | 1.10834 | 4.54722 | 0.747215 | 0.0007024 | 2.39348e-05 | 2.27951e-06 | 1(Win) | true |
| simdjson (ondemand) | 4118.49 | 0.104833 | 831.998ms | 3770 | 4890 | 4095.51 | 872.978 | 0.228457 | 1.26377 | 5.13422 | 0.729708 | 0.000910048 | 3.63433e-05 | 1.28015e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4828.25 | 0.124913 | 820.269ms | 3770 | 4890 | 4230.85 | 744.649 | 0.474333 | 1.08595 | 4.4939 | 0.734218 | 0.000796027 | 3.58551e-05 | 9.32993e-06 | 1(Win) | true |
| simdjson (ondemand) | 4196.57 | 0.141553 | 828.634ms | 3770 | 4890 | 7191.9 | 856.736 | 0.148456 | 1.24082 | 5.07825 | 0.716711 | 0.000922795 | 3.14614e-05 | 8.89598e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4956.55 | 0.0721313 | 6111.89ms | 277673 | 640 | 950464 | 53426.2 | 0.012121 | 1.00259 | 3.95287 | 0.682914 | 0.00485968 | 2.66726e-06 | 1.39553e-06 | 1(Win) | true |
| simdjson (ondemand) | 4336.58 | 0.0246427 | 6858.82ms | 277673 | 4890 | 1.10728e+06 | 61064.1 | 0.0900016 | 1.14724 | 4.74393 | 0.785786 | 0.00384965 | 1.48179e-05 | 1.18801e-05 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3790.71 | 0.142806 | 8265ms | 10548466 | 80 | 1.149e+09 | 2.6538e+06 | 0.196751 | 1.30839 | 3.95209 | 0.6835 | 0.0151361 | 0.0175303 | 0.000639689 | 1(Win) | true |
| simdjson (ondemand) | 3664.23 | 0.160098 | 4122.82ms | 10548466 | 30 | 5.79568e+08 | 2.74541e+06 | 0.0161544 | 1.35156 | 4.74227 | 0.786833 | 0.0101504 | 0.0180755 | 0.000979798 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3761.36 | 0.139727 | 6091.42ms | 16002592 | 30 | 9.64208e+08 | 4.05738e+06 | 0.162826 | 1.31773 | 7.65365 | 1.32406 | 0.000687476 | 0.0339957 | 0.00211914 | 1(Win) | true |
| simdjson (ondemand) | 2918.32 | 0.116073 | 7872.01ms | 16002592 | 40 | 1.47381e+09 | 5.22947e+06 | 0.316707 | 1.72422 | 7.97951 | 1.15922 | 0.00248157 | 0.0377685 | 0.00905028 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3416.79 | 0.157266 | 6786.74ms | 16002591 | 40 | 1.97366e+09 | 4.46655e+06 | 0.375883 | 1.46576 | 7.69712 | 1.41118 | 0.0007723 | 0.0366533 | 0.0090208 | 1(Win) | true |
| simdjson (ondemand) | 1744.48 | 0.0692541 | 6133.92ms | 16002591 | 30 | 1.10119e+09 | 8.74832e+06 | 0.00942721 | 2.83744 | 12.9567 | 2.70124 | 0.00257328 | 0.0548748 | 0.00883879 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 21448.6 | 0.10036 | 4607.51ms | 16197086 | 160 | 8.35833e+07 | 720176 | 0.184652 | 0.23045 | 1.15825 | 0.0700875 | 7.25223e-05 | 0.0157294 | 0.000626909 | 1(Win) | true |
| simdjson (ondemand) | 17166.7 | 0.275383 | 5829.59ms | 16197086 | 80 | 4.91204e+08 | 899807 | 0.391104 | 0.288315 | 1.3372 | 0.0733714 | 0.000114955 | 0.0157467 | 0.000309188 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 21239.5 | 0.122686 | 4666.92ms | 16197085 | 80 | 6.36887e+07 | 727264 | 0.0397692 | 0.232733 | 1.15882 | 0.0714888 | 7.4853e-05 | 0.0157557 | 0.000428882 | 1(Win) | true |
| simdjson (ondemand) | 15379.1 | 0.875259 | 6449.66ms | 16197085 | 30 | 2.3185e+09 | 1.0044e+06 | 1.02919 | 0.321617 | 1.41971 | 0.0990586 | 0.000125004 | 0.0157746 | 0.000945121 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1901.33 | 0.125011 | 4102.76ms | 4212000 | 30 | 2.09258e+08 | 2.11267e+06 | 0.359658 | 2.60538 | 11.3529 | 2.10439 | 0.0162755 | 0.067515 | 0.00524271 | 1(Win) | true |
| simdjson (ondemand) | 1504.23 | 0.102333 | 4917.45ms | 4212000 | 30 | 2.24028e+08 | 2.67038e+06 | 0.00859376 | 3.29379 | 12.656 | 2.39684 | 0.0120526 | 0.0668986 | 0.00744949 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.89 | 0.121947 | 5130.2ms | 4212000 | 40 | 4.6747e+08 | 2.80334e+06 | 0.0347016 | 3.46296 | 15.1848 | 3.00408 | 0.0170393 | 0.0677465 | 0.00409411 | 1(Win) | true |
| simdjson (ondemand) | 1269.96 | 0.162008 | 5672.41ms | 4212000 | 40 | 1.05035e+09 | 3.16301e+06 | 0.107432 | 3.92748 | 16.192 | 3.06152 | 0.0125243 | 0.0670023 | 0.00436742 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1795.21 | 0.0851991 | 4278.19ms | 4211999 | 80 | 2.9074e+08 | 2.23755e+06 | 0.195845 | 2.76751 | 12.2137 | 2.30087 | 0.0172223 | 0.0689261 | 0.00631482 | 1(Win) | true |
| simdjson (ondemand) | 1262.03 | 0.105456 | 5709.89ms | 4211999 | 40 | 4.50649e+08 | 3.18286e+06 | 0.0351216 | 3.93561 | 15.1297 | 3.16422 | 0.0124518 | 0.0688763 | 0.0074091 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.58 | 0.226526 | 5156.25ms | 4211999 | 30 | 1.21031e+09 | 2.80395e+06 | 0.401671 | 3.48618 | 15.3256 | 3.04161 | 0.0173539 | 0.068952 | 0.00836332 | 1(Win) | true |
| simdjson (ondemand) | 1078.32 | 0.115596 | 6519.9ms | 4211999 | 80 | 1.4834e+09 | 3.72514e+06 | 0.0750041 | 4.63363 | 18.6656 | 3.82887 | 0.0129498 | 0.0691562 | 0.00304673 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1543.96 | 0.0715034 | 4523.1ms | 4525120 | 80 | 3.19546e+08 | 2.79509e+06 | 0.628933 | 3.22144 | 15.5647 | 2.95669 | 0.0121675 | 0.0782875 | 0.00177007 | 1(Win) | true |
| simdjson (ondemand) | 1376.52 | 0.115166 | 5075.79ms | 4525120 | 80 | 1.04289e+09 | 3.13508e+06 | 0.264859 | 3.60032 | 16.0064 | 2.58889 | 0.0166511 | 0.0771439 | 0.00309645 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 771.807 | 0.086616 | 4113.07ms | 4525120 | 30 | 7.03656e+08 | 5.59141e+06 | 0.146868 | 6.42957 | 31.2891 | 6.45694 | 0.0180019 | 0.0791396 | 0.0061834 | 1(Win) | true |
| simdjson (ondemand) | 588.104 | 0.16454 | 5317.7ms | 4525120 | 30 | 4.37336e+09 | 7.33797e+06 | 0.0803654 | 8.45331 | 41.3453 | 8.11954 | 0.027711 | 0.0777864 | 0.00542801 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1360.76 | 0.236018 | 5058.48ms | 4525119 | 30 | 1.68078e+09 | 3.17139e+06 | 0.0340313 | 3.64984 | 17.7803 | 3.5102 | 0.0128471 | 0.0781422 | 0.000813061 | 1(Win) | true |
| simdjson (ondemand) | 1000.7 | 0.124339 | 6795.86ms | 4525119 | 80 | 2.30013e+09 | 4.31245e+06 | 0.114812 | 4.97071 | 21.2186 | 4.13374 | 0.0194087 | 0.0926441 | 0.0031582 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.63 | 0.114767 | 4126.81ms | 4525119 | 40 | 1.67384e+09 | 5.63652e+06 | 0.201974 | 6.48723 | 31.0203 | 6.45725 | 0.0180474 | 0.0786129 | 0.00437045 | 1(Win) | true |
| simdjson (ondemand) | 507.859 | 0.104734 | 6152.43ms | 4525119 | 40 | 3.16815e+09 | 8.49741e+06 | 0.00328307 | 9.78096 | 46.5574 | 9.66433 | 0.0305785 | 0.0935777 | 0.013405 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1253.26 | 0.0735386 | 5117.09ms | 4203059 | 40 | 2.21277e+08 | 3.19833e+06 | 0.0292759 | 3.95767 | 17.6318 | 3.4352 | 0.021598 | 0.0894772 | 0.00371803 | 1(Win) | true |
| simdjson (ondemand) | 980.82 | 0.139526 | 6489.38ms | 4203059 | 80 | 2.60108e+09 | 4.08673e+06 | 0.0583857 | 5.1076 | 19.0264 | 3.60681 | 0.0271274 | 0.0874699 | 0.00515124 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.191 | 0.0405134 | 8322.88ms | 4203059 | 80 | 3.68939e+08 | 5.30071e+06 | 0.775077 | 6.55778 | 28.0223 | 5.8231 | 0.0296747 | 0.089099 | 0.00719851 | 1(Win) | true |
| simdjson (ondemand) | 694.775 | 0.121241 | 4182.12ms | 4203059 | 30 | 1.46779e+09 | 5.76928e+06 | 0.123169 | 7.1515 | 27.2129 | 5.24707 | 0.0306279 | 0.0879935 | 0.00712661 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1138.22 | 0.0813427 | 5590.88ms | 4203058 | 80 | 6.56451e+08 | 3.52158e+06 | 0.116345 | 4.3812 | 19.7647 | 3.96772 | 0.023211 | 0.0887323 | 0.00580994 | 1(Win) | true |
| simdjson (ondemand) | 778.926 | 0.0608943 | 8072.1ms | 4203058 | 80 | 7.85565e+08 | 5.14599e+06 | 0.543033 | 6.38823 | 24.1313 | 5.16988 | 0.0289136 | 0.104267 | 0.00968201 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 709.093 | 0.0710631 | 4149.8ms | 4203058 | 40 | 6.45465e+08 | 5.65279e+06 | 0.16587 | 7.01874 | 30.1531 | 6.35484 | 0.0316403 | 0.0887351 | 0.0130127 | 1(Win) | true |
| simdjson (ondemand) | 584.772 | 0.128543 | 4952.4ms | 4203058 | 30 | 2.32905e+09 | 6.85455e+06 | 0.122692 | 8.51378 | 32.3191 | 6.8106 | 0.0324098 | 0.104634 | 0.0160533 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1718.36 | 0.0931305 | 7556.53ms | 4197496 | 30 | 1.41207e+08 | 2.32957e+06 | 0.102563 | 2.93648 | 14.864 | 3.09446 | 0.000508652 | 0.0825837 | 0.0030125 | 1(Win) | true |
| simdjson (ondemand) | 1474.47 | 0.0402958 | 4246.22ms | 4197496 | 80 | 9.57451e+07 | 2.71489e+06 | 0.111989 | 3.42945 | 16.7346 | 2.79798 | 0.00544373 | 0.0819475 | 0.000520289 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 909.179 | 0.168623 | 6789.71ms | 4197496 | 80 | 4.40965e+09 | 4.40292e+06 | 0.293283 | 5.55067 | 28.0486 | 5.89321 | 0.00109673 | 0.0829549 | 0.00925283 | 1(Win) | true |
| simdjson (ondemand) | 771.36 | 0.121018 | 7934.09ms | 4197496 | 40 | 1.57772e+09 | 5.18959e+06 | 0.310188 | 6.49109 | 31.5718 | 5.88152 | 0.0104024 | 0.0822207 | 0.00486059 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1544.43 | 0.0541888 | 4047.52ms | 4197495 | 80 | 1.57818e+08 | 2.59193e+06 | 0.159074 | 3.26442 | 16.9453 | 3.6013 | 0.000819367 | 0.0844788 | 0.000395268 | 1(Win) | true |
| simdjson (ondemand) | 1041.83 | 0.0780041 | 5948.5ms | 4197495 | 40 | 3.59317e+08 | 3.8423e+06 | 0.224218 | 4.83357 | 22.4264 | 4.57547 | 0.00579648 | 0.102811 | 0.000283586 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 891.322 | 0.188179 | 6911.34ms | 4197495 | 30 | 2.14277e+09 | 4.49113e+06 | 0.00661347 | 5.60876 | 28.0926 | 5.9548 | 0.000969316 | 0.0848332 | 0.00333886 | 1(Win) | true |
| simdjson (ondemand) | 628.478 | 0.137746 | 4597.07ms | 4197495 | 30 | 2.3093e+09 | 6.36942e+06 | 0.623166 | 8.02096 | 37.2637 | 7.65901 | 0.0117623 | 0.103282 | 0.00405734 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1478.01 | 0.198399 | 5097.9ms | 4506447 | 80 | 2.66246e+09 | 2.90775e+06 | 0.28568 | 3.41184 | 15.472 | 3.00294 | 0.0160285 | 0.0812499 | 0.001907 | 1(Win) | true |
| simdjson (ondemand) | 1141.81 | 0.141119 | 6432.17ms | 4506447 | 30 | 8.46393e+08 | 3.76391e+06 | 0.0940837 | 4.40471 | 17.1461 | 3.21392 | 0.0165494 | 0.0792366 | 0.00303621 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 827.194 | 0.109162 | 4019.96ms | 4506447 | 40 | 1.28664e+09 | 5.19549e+06 | 0.478672 | 6.08285 | 26.757 | 5.54151 | 0.0199163 | 0.0815045 | 0.00834212 | 1(Win) | true |
| simdjson (ondemand) | 460.616 | 0.0979234 | 6897.45ms | 4506447 | 30 | 2.50429e+09 | 9.33029e+06 | 0.279058 | 10.8864 | 42.9215 | 8.76065 | 0.0466663 | 0.0797963 | 0.0129368 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.36 | 0.128651 | 5568.22ms | 4506446 | 40 | 6.7558e+08 | 3.19444e+06 | 0.860167 | 3.73333 | 17.109 | 3.41521 | 0.01821 | 0.0815656 | 0.00884058 | 1(Win) | true |
| simdjson (ondemand) | 914.989 | 0.151257 | 7811.76ms | 4506446 | 30 | 1.51421e+09 | 4.69698e+06 | 0.338807 | 5.45598 | 21.2099 | 4.47412 | 0.0167815 | 0.0883511 | 0.00512255 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 822.528 | 0.201298 | 4019.44ms | 4506446 | 30 | 3.31868e+09 | 5.22497e+06 | 0.381246 | 6.1199 | 26.5732 | 5.55105 | 0.0198509 | 0.0819436 | 0.00531121 | 1(Win) | true |
| simdjson (ondemand) | 429.373 | 0.116963 | 7449.24ms | 4506446 | 30 | 4.11167e+09 | 1.00092e+07 | 0.623326 | 11.8617 | 46.9859 | 10.021 | 0.0417009 | 0.0887839 | 0.0169395 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1859.57 | 0.215313 | 7624.38ms | 4219120 | 30 | 6.51152e+08 | 2.16377e+06 | 0.152757 | 2.69444 | 9.2346 | 1.68888 | 0.0209516 | 0.0567586 | 0.0018954 | 1(Win) | true |
| simdjson (ondemand) | 1817.77 | 0.115213 | 7667.68ms | 4219120 | 80 | 5.20306e+08 | 2.21351e+06 | 0.00797255 | 2.74806 | 9.38318 | 1.55793 | 0.0153367 | 0.0539115 | 0.000529711 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 700.118 | 0.15308 | 4212.88ms | 4219120 | 30 | 2.322e+09 | 5.74713e+06 | 0.284856 | 7.17711 | 27.1076 | 5.22648 | 0.026766 | 0.0581656 | 0.0010061 | 1(Win) | true |
| simdjson (ondemand) | 284.19 | 0.125292 | 4324.23ms | 4219120 | 30 | 9.44044e+09 | 1.41584e+07 | 0.932338 | 17.4924 | 67.0976 | 14.2811 | 0.0790163 | 0.0553247 | 0.00531913 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1721.49 | 0.0767202 | 8150.27ms | 4219119 | 160 | 5.14486e+08 | 2.33732e+06 | 0.232966 | 2.91333 | 10.2545 | 1.94368 | 0.0212701 | 0.0572396 | 0.000474194 | 1(Win) | true |
| simdjson (ondemand) | 1440.28 | 0.159255 | 4591.72ms | 4219119 | 80 | 1.58353e+09 | 2.79366e+06 | 0.0842912 | 3.47459 | 11.8252 | 2.31683 | 0.0180411 | 0.0550757 | 0.000333512 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 701.481 | 0.141872 | 4225.78ms | 4219119 | 40 | 2.64892e+09 | 5.73596e+06 | 0.33409 | 7.1892 | 26.994 | 5.22952 | 0.026964 | 0.0589894 | 0.00179856 | 1(Win) | true |
| simdjson (ondemand) | 272.996 | 0.0895996 | 4500.04ms | 4219119 | 30 | 5.23194e+09 | 1.47389e+07 | 0.539017 | 18.4067 | 69.5391 | 15.0398 | 0.0815876 | 0.0563246 | 0.00986337 | 2(Loss) | true |
