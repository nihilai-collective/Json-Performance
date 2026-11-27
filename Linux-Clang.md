# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier (Generic): [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |

> SIMD paths above are whatever each library picked at build/run time on this box.

> **Sampling (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations: 100 → 200 → 400 ... (max 100000), doubling per epoch.  
> Window: last `max(iterations/10, 30)` samples (max 100000). Runs for 5s or until the cap.  
> Epoch used: lowest RSE + mean shift (1st epoch is just a fallback).  
> Converged = RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged ones still get ranked.  
> Ties: Welch's t-test (Bessel-corrected).

---

##### A Few Details
* **UTF-8 Validation:** Full validation, both libraries, every test.
* **Schema-Free Traversal:** No schemas. `Jsonifier (generic)` walks its stage-1 tape via `jsonifier::generic`, `simdjson (ondemand)` walks On Demand. Same structs, same field-by-field fill.
* **Streaming:** `jsonifier_core::iterateMany` vs `ondemand::parser::iterate_many` (unthreaded), 1 MiB batches.

##### The Test Variants
* **Amazon Cellphones:** Ratings per brand over `amazon_cellphones.ndjson` (from the simdjson repo, 10 MiB for Large).
* **Stream Formats:** Sums `"id"` over `{"id","name","payload","flag"}` docs (same as simdjson's stream benchmarks), 16/4096-byte payloads, 16 MB total.
* **Stream:** Each corpus doc's main record array, split into one doc per record, 4 MiB total.
* **(NDJSON) vs. (Comma-Separated):** Newline vs comma separators (simdjson `stream_format::comma_delimited`, Jsonifier `allowCommaSeparated`).
* **Key Traversal Order:** Standard = document order. `Reverse` = each object's keys backwards, worst case for forward-only parsers like simdjson On Demand ($O(N^2)$ rescans).
* **Sparse:** Same doc, only a few fields per record of the main arrays (like Twitter Partial). `Sparse Reverse` = same fields, reversed.

---
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 652.532 | 0.227954 | 856.724ms | 905 | 2560 | 23271.7 | 1322.66 | 0.0234255 | 8.15257 | 37.3039 | 6.70055 | 0.00457571 | 0.000197255 | 8.02831e-05 | 1(Win) | true |
| simdjson (ondemand) | 491.462 | 0.0987659 | 891.899ms | 905 | 160 | 481.339 | 1756.14 | 0.0085422 | 10.7244 | 50.5039 | 9.81436 | 0.0441851 | 0.000103591 | 1.38122e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 669.294 | 0.117768 | 842.953ms | 905 | 2560 | 5904.21 | 1289.53 | 0.028028 | 7.9428 | 36.6829 | 6.58011 | 0.00589693 | 0.000175242 | 4.74793e-05 | 1(Win) | true |
| simdjson (ondemand) | 513.06 | 0.144944 | 887.069ms | 905 | 80 | 475.612 | 1682.21 | 0.0825487 | 10.2795 | 49.8851 | 9.69615 | 0.040221 | 8.28729e-05 | 2.76243e-05 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 720.199 | 0.0487428 | 963.189ms | 1811 | 4890 | 6681.31 | 2398.09 | 0.172889 | 7.22862 | 36.2684 | 7.56764 | 0.000599043 | 9.28206e-05 | 1.8406e-05 | 1(Win) | true |
| simdjson (ondemand) | 438.944 | 0.0471815 | 1110.9ms | 1811 | 2560 | 8822.74 | 3934.68 | 0.161487 | 11.8124 | 59.291 | 11.4395 | 0.00174498 | 0.000117554 | 3.1923e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.969 | 0.0488281 | 941.52ms | 1811 | 4890 | 6069.17 | 2281.61 | 0.0307792 | 6.91008 | 35.2435 | 7.32965 | 0.0011134 | 8.88684e-05 | 1.53572e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.813 | 0.0530911 | 1122.25ms | 1811 | 1280 | 5271.98 | 3822.61 | 0.0750213 | 11.5261 | 58.2435 | 11.2082 | 0.00222123 | 8.88666e-05 | 1.29417e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 721.72 | 0.0790471 | 896.85ms | 1313 | 160 | 300.943 | 1734.99 | 0.295237 | 7.3035 | 36.4326 | 6.76923 | 0.000771135 | 0.000104722 | 0 | 1(Win) | true |
| simdjson (ondemand) | 375.64 | 0.0400056 | 1054.7ms | 1313 | 4890 | 8696.33 | 3333.44 | 0.0435339 | 13.809 | 56.6771 | 11.0312 | 0.000828587 | 0.000168209 | 4.78151e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 763.958 | 0.139701 | 883.553ms | 1313 | 80 | 419.452 | 1639.06 | 0.166738 | 6.9113 | 35.1721 | 6.48896 | 0.000828256 | 6.66413e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 383.948 | 0.0769885 | 1047.18ms | 1313 | 80 | 504.344 | 3261.31 | 0.0617464 | 13.5861 | 55.38 | 10.7395 | 0.000971059 | 0.000104722 | 1.90404e-05 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 944.108 | 0.101314 | 1149.08ms | 4215 | 1280 | 23817.8 | 4257.71 | 0.635515 | 5.4818 | 24.0754 | 4.3497 | 0.00349496 | 3.92942e-05 | 6.3019e-06 | 1(Win) | true |
| Jsonifier (generic) | 695.148 | 0.0541122 | 1298.96ms | 4215 | 1280 | 12532.6 | 5782.56 | 0.0444296 | 7.47988 | 27.2289 | 5.57058 | 0.00334723 | 4.37426e-05 | 1.26038e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1230.26 | 0.0601665 | 1096.21ms | 4215 | 2560 | 9893.52 | 3267.39 | 0.13614 | 4.22714 | 19.5734 | 3.27189 | 0.00314177 | 7.43253e-05 | 3.46604e-05 | 1(Win) | true |
| Jsonifier (generic) | 856.689 | 0.0950225 | 1243.39ms | 4215 | 640 | 12722.8 | 4692.18 | 0.224238 | 6.06867 | 22.0318 | 4.32029 | 0.00226572 | 4.15184e-05 | 1.03796e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 709.283 | 0.076551 | 881.069ms | 1213 | 320 | 498.81 | 1630.95 | 0.0780444 | 7.44236 | 37.3462 | 6.96702 | 0.00415035 | 0.000118508 | 7.72877e-06 | 1(Win) | true |
| simdjson (ondemand) | 366.167 | 0.0413511 | 1033.65ms | 1213 | 160 | 273.059 | 3159.23 | 0.0116708 | 14.2502 | 59.2786 | 12.0322 | 0.0113407 | 0.000154575 | 0 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 767.601 | 0.0832546 | 864.955ms | 1213 | 4890 | 7697.97 | 1507.04 | 0.0451307 | 6.86214 | 35.8013 | 6.61171 | 0.00362602 | 0.000213266 | 2.52884e-05 | 1(Win) | true |
| simdjson (ondemand) | 369.203 | 0.0600643 | 1029.79ms | 1213 | 640 | 2266.75 | 3133.25 | 0.0769872 | 14.1513 | 57.8895 | 11.7164 | 0.0149487 | 0.000109491 | 7.72877e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.72 | 0.0343563 | 6996.46ms | 94653 | 1280 | 591467 | 62568.2 | 0.121536 | 3.51045 | 15.1163 | 2.92863 | 0.00873996 | 2.97221e-05 | 2.2013e-05 | 1(Win) | true |
| simdjson (ondemand) | 1265.54 | 0.0204528 | 7893.16ms | 94653 | 4890 | 1.04071e+06 | 71327.5 | 0.0911274 | 4.03261 | 16.5855 | 3.09583 | 0.0110691 | 4.15704e-05 | 2.76113e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2058.97 | 0.0283682 | 6370.59ms | 94653 | 2560 | 395981 | 43841.4 | 0.0547502 | 2.46227 | 11.2204 | 2.04762 | 0.00611581 | 7.70908e-06 | 4.39517e-06 | 1(Win) | true |
| simdjson (ondemand) | 1703.21 | 0.0442524 | 7292.83ms | 94653 | 640 | 352036 | 52998.9 | 0.0554328 | 2.97749 | 12.7174 | 2.22268 | 0.00786565 | 1.22157e-05 | 6.28942e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1854.57 | 0.0405434 | 7188.71ms | 124597 | 640 | 431866 | 64071.4 | 0.0935501 | 2.73377 | 11.8564 | 2.23221 | 0.00698043 | 1.39951e-05 | 1.00323e-05 | 1(Win) | true |
| simdjson (ondemand) | 1611.3 | 0.0450022 | 8118.13ms | 124597 | 640 | 704874 | 73744.9 | 0.0186043 | 3.15616 | 12.9152 | 2.36968 | 0.00898256 | 6.93486e-06 | 3.83737e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2617.7 | 0.0361561 | 6521.32ms | 124597 | 640 | 172393 | 45392.9 | 0.0612709 | 1.93338 | 8.90903 | 1.56781 | 0.00462433 | 6.05703e-06 | 3.86245e-06 | 1(Win) | true |
| simdjson (ondemand) | 2169.41 | 0.0339585 | 7464.05ms | 124597 | 1280 | 442833 | 54773 | 0.0629927 | 2.345 | 9.9824 | 1.70916 | 0.00632444 | 1.94502e-05 | 1.52241e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1146.17 | 0.0332368 | 8642.16ms | 94653 | 1280 | 877037 | 78756.2 | 0.0430297 | 4.44072 | 20.561 | 4.20183 | 0.00989881 | 1.47331e-05 | 9.95412e-06 | 1(Win) | true |
| simdjson (ondemand) | 705.376 | 0.0282995 | 6913.86ms | 94653 | 2560 | 3.35757e+06 | 127972 | 0.00246276 | 7.19397 | 35.1358 | 7.03518 | 0.0120334 | 3.51489e-05 | 2.85087e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1499.73 | 0.020034 | 8009.21ms | 94653 | 4890 | 711035 | 60189.7 | 0.014471 | 3.39219 | 16.7003 | 3.34441 | 0.00707167 | 1.2289e-05 | 6.59172e-06 | 1(Win) | true |
| simdjson (ondemand) | 821.938 | 0.0326414 | 6626.75ms | 94653 | 2560 | 3.28978e+06 | 109823 | 0.104617 | 6.17091 | 31.3085 | 6.1861 | 0.00965521 | 3.73816e-05 | 2.70561e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1450.72 | 0.10102 | 8932.38ms | 124597 | 160 | 1.09543e+06 | 81907.8 | 0.00446366 | 3.50105 | 16.267 | 3.25986 | 0.0081257 | 9.93202e-06 | 6.97248e-06 | 1(Win) | true |
| simdjson (ondemand) | 919.765 | 0.0736702 | 6997.36ms | 124597 | 2560 | 2.31892e+07 | 129191 | 0.124101 | 5.53226 | 26.6686 | 5.30136 | 0.00991676 | 3.44172e-05 | 2.27483e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1868.2 | 0.0357557 | 8334.23ms | 124597 | 2560 | 1.32404e+06 | 63604.1 | 0.0104585 | 2.71538 | 13.3278 | 2.60816 | 0.00576735 | 1.23774e-05 | 8.10739e-06 | 1(Win) | true |
| simdjson (ondemand) | 1065.44 | 0.0795999 | 6703ms | 124597 | 320 | 2.5219e+06 | 111526 | 0.258641 | 4.77058 | 23.7577 | 4.65681 | 0.00730335 | 5.43251e-05 | 4.8682e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2377.4 | 0.0476898 | 4522.61ms | 94653 | 1280 | 419686 | 37969.2 | 0.0392454 | 2.12966 | 9.36435 | 1.7535 | 0.00584047 | 1.03338e-05 | 5.62911e-06 | 1(Win) | true |
| simdjson (ondemand) | 1799.96 | 0.0525478 | 5578.38ms | 94653 | 640 | 444461 | 50150.2 | 0.0429458 | 2.81802 | 10.9775 | 1.9397 | 0.0110882 | 3.94698e-05 | 3.14801e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3263.89 | 0.115267 | 4012.63ms | 94653 | 160 | 162604 | 27656.7 | 0.00442951 | 1.56755 | 7.4584 | 1.30924 | 0.00345571 | 1.74321e-05 | 1.26119e-05 | 1(Win) | true |
| simdjson (ondemand) | 2344.02 | 0.0986384 | 5140.21ms | 94653 | 160 | 230864 | 38509.9 | 0.00470636 | 2.19305 | 9.08961 | 1.50021 | 0.00676517 | 1.36023e-05 | 9.57445e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2903.32 | 0.035618 | 4828.3ms | 124597 | 2560 | 544007 | 40927.2 | 0.140547 | 1.74533 | 7.51946 | 1.34881 | 0.00490452 | 1.8657e-05 | 1.3876e-05 | 1(Win) | true |
| simdjson (ondemand) | 2472.65 | 0.0221372 | 5567.05ms | 124597 | 4890 | 553406 | 48055.8 | 0.092778 | 2.06316 | 8.3181 | 1.42913 | 0.00599008 | 1.09588e-05 | 7.60407e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3930.01 | 0.0238425 | 4250.56ms | 124597 | 2560 | 133037 | 30235.3 | 0.0471836 | 1.29276 | 6.07112 | 1.01031 | 0.00261256 | 4.17283e-06 | 2.06917e-06 | 1(Win) | true |
| simdjson (ondemand) | 3045.59 | 0.0442815 | 5127.13ms | 124597 | 1280 | 382056 | 39015.4 | 0.0314037 | 1.67458 | 6.89678 | 1.09776 | 0.00499923 | 1.37945e-05 | 9.63105e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1826.92 | 0.0307094 | 5677.44ms | 94653 | 4890 | 1.12585e+06 | 49410 | 0.245279 | 2.78137 | 12.6353 | 2.4967 | 0.00715738 | 1.61369e-05 | 1.0876e-05 | 1(Win) | true |
| simdjson (ondemand) | 1554.02 | 0.0315735 | 6544.58ms | 94653 | 2560 | 861075 | 58086.8 | 0.0998991 | 3.28939 | 13.6165 | 2.44554 | 0.0089143 | 6.44212e-06 | 2.53393e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2211.66 | 0.0635713 | 5238.9ms | 94653 | 160 | 107715 | 40814.7 | 0.0440517 | 2.28661 | 10.7537 | 2.07042 | 0.00603916 | 6.6691e-06 | 3.56566e-06 | 1(Win) | true |
| simdjson (ondemand) | 1833.06 | 0.0372005 | 6123.79ms | 94653 | 2560 | 859114 | 49244.4 | 0.00208696 | 2.76668 | 11.779 | 2.03095 | 0.0071818 | 7.76686e-06 | 4.21358e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2281.42 | 0.0957505 | 5975.27ms | 124597 | 40 | 99482.6 | 52083.8 | 0.0185564 | 2.25911 | 10.0946 | 1.93333 | 0.00584424 | 4.7754e-05 | 4.55468e-05 | 1(Win) | true |
| simdjson (ondemand) | 2065.62 | 0.0326395 | 6509.01ms | 124597 | 2560 | 902490 | 57525.2 | 0.313663 | 2.47099 | 10.3208 | 1.81516 | 0.00640872 | 1.58292e-05 | 1.19416e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2809.91 | 0.0642061 | 5489.35ms | 124597 | 640 | 471806 | 42287.9 | 0.336178 | 1.8266 | 8.66387 | 1.60961 | 0.00461186 | 1.20639e-05 | 9.33008e-06 | 1(Win) | true |
| simdjson (ondemand) | 2455.78 | 0.051638 | 6041.12ms | 124597 | 1280 | 799067 | 48385.8 | 0.0148653 | 2.07645 | 8.91896 | 1.49972 | 0.00497624 | 1.14243e-05 | 8.37701e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 780.226 | 0.0986911 | 7998.25ms | 2090234 | 160 | 1.01725e+09 | 2.55491e+06 | 0.385205 | 6.52905 | 32.0432 | 6.35048 | 0.027566 | 0.104703 | 0.000332938 | 1(Win) | true |
| simdjson (ondemand) | 759.288 | 0.344528 | 8138.44ms | 2090234 | 80 | 6.54509e+09 | 2.62536e+06 | 0.00495624 | 6.65621 | 31.7773 | 5.65411 | 0.0226657 | 0.103679 | 0.00164086 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 917.612 | 0.145238 | 8021ms | 2090234 | 30 | 2.98645e+08 | 2.17238e+06 | 0.275866 | 5.56135 | 26.7196 | 5.06239 | 0.0267052 | 0.079285 | 0.000122682 | 1(Win) | true |
| simdjson (ondemand) | 895.037 | 0.0752691 | 8096.84ms | 2090234 | 160 | 4.49636e+08 | 2.22717e+06 | 0.0198264 | 5.64492 | 26.4289 | 4.36108 | 0.021712 | 0.0787324 | 0.0011588 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1807.59 | 0.0817472 | 8568.69ms | 5212421 | 80 | 4.04311e+08 | 2.75005e+06 | 0.160388 | 2.80922 | 13.6503 | 2.60269 | 0.0102021 | 0.0609387 | 0.00111435 | 1(Win) | true |
| simdjson (ondemand) | 1771.34 | 0.0576479 | 8761.04ms | 5212421 | 160 | 4.18758e+08 | 2.80632e+06 | 0.124775 | 2.85492 | 13.4607 | 2.2997 | 0.0103363 | 0.0618001 | 0.00372215 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2090.56 | 0.156474 | 8615.34ms | 5212421 | 30 | 4.15297e+08 | 2.37781e+06 | 0.0405671 | 2.42975 | 11.5101 | 2.08515 | 0.00982394 | 0.0505505 | 0.000571187 | 1(Win) | true |
| simdjson (ondemand) | 2049.33 | 0.0955179 | 8739.32ms | 5212421 | 160 | 8.58901e+08 | 2.42564e+06 | 0.191661 | 2.46616 | 11.3279 | 1.78361 | 0.0100336 | 0.0516215 | 0.00119774 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 726.125 | 0.176699 | 8548.27ms | 2090234 | 30 | 7.05926e+08 | 2.74526e+06 | 0.0567238 | 6.98173 | 35.0793 | 6.98988 | 0.0276154 | 0.156661 | 0.000811153 | 1(Win) | true |
| simdjson (ondemand) | 698.453 | 0.135218 | 8898.2ms | 2090234 | 160 | 2.38288e+09 | 2.85403e+06 | 0.832021 | 7.27097 | 36.0909 | 6.61271 | 0.0227642 | 0.180149 | 0.00457126 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 841.125 | 0.0779137 | 8538.17ms | 2090234 | 160 | 5.45527e+08 | 2.36992e+06 | 0.0884219 | 6.01255 | 29.7599 | 5.70275 | 0.0265772 | 0.130781 | 0.000712429 | 1(Win) | true |
| simdjson (ondemand) | 806.58 | 0.0949829 | 8889.74ms | 2090234 | 160 | 8.8167e+08 | 2.47143e+06 | 0.197443 | 6.28687 | 30.7474 | 5.32063 | 0.0218063 | 0.154514 | 0.00217513 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1634.74 | 0.280568 | 9386.23ms | 5212421 | 30 | 2.18364e+09 | 3.04083e+06 | 0.466518 | 3.10865 | 14.8594 | 2.85724 | 0.0103426 | 0.101231 | 0.00394228 | 1(Win) | true |
| simdjson (ondemand) | 1562.54 | 0.117281 | 9962.27ms | 5212421 | 160 | 2.22738e+09 | 3.18133e+06 | 0.179525 | 3.24248 | 15.1996 | 2.68602 | 0.0102663 | 0.120311 | 0.00193636 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1870.99 | 0.248429 | 9425.81ms | 5212421 | 160 | 6.9704e+09 | 2.65685e+06 | 0.319736 | 2.70358 | 12.7285 | 2.34156 | 0.00982399 | 0.0906286 | 0.001077 | 1(Win) | true |
| simdjson (ondemand) | 1795.54 | 0.164748 | 9904.62ms | 5212421 | 40 | 8.32127e+08 | 2.7685e+06 | 0.189117 | 2.82941 | 13.0603 | 2.16862 | 0.00988567 | 0.110176 | 0.000340307 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6952.39 | 0.260428 | 7483.91ms | 2090234 | 30 | 1.6727e+07 | 286722 | 0.465028 | 0.74043 | 3.65785 | 0.418406 | 0.0030957 | 0.0498074 | 0.000123001 | 1(Win) | true |
| Jsonifier (generic) | 6875.02 | 0.141241 | 7587.63ms | 2090234 | 320 | 5.36677e+07 | 289948 | 0.0556093 | 0.742692 | 3.27973 | 0.436447 | 0.0058896 | 0.0508466 | 7.63147e-05 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7001.69 | 0.121806 | 7458.26ms | 2090234 | 640 | 7.6966e+07 | 284703 | 0.233403 | 0.729564 | 3.65776 | 0.418389 | 0.00269107 | 0.0497563 | 0.000193209 | 1(Win) | true |
| Jsonifier (generic) | 6843.2 | 0.126291 | 7652.93ms | 2090234 | 640 | 8.66154e+07 | 291297 | 0.479533 | 0.746426 | 3.27964 | 0.436428 | 0.00584581 | 0.0508055 | 0.00017885 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10606.5 | 0.262904 | 6057.52ms | 5212421 | 640 | 9.71653e+08 | 468672 | 0.134024 | 0.478087 | 1.94446 | 0.198823 | 0.00213746 | 0.0394054 | 6.51748e-06 | 1(Win) | true |
| simdjson (ondemand) | 9938.37 | 0.371136 | 6476.65ms | 5212421 | 40 | 1.3784e+08 | 500178 | 0.233858 | 0.507557 | 2.19705 | 0.202784 | 0.00190664 | 0.0394776 | 8.31188e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10558.3 | 0.195999 | 6091.44ms | 5212421 | 640 | 5.44977e+08 | 470811 | 1.14246 | 0.47731 | 1.94442 | 0.198816 | 0.00212468 | 0.0393907 | 1.00229e-05 | 1(Win) | true |
| simdjson (ondemand) | 10038.2 | 0.243364 | 6432.21ms | 5212421 | 160 | 2.32378e+08 | 495201 | 0.0349685 | 0.50477 | 2.19702 | 0.202777 | 0.00182643 | 0.039397 | 2.32617e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5457.28 | 0.0751531 | 9530.62ms | 2090234 | 1280 | 9.64588e+07 | 365274 | 0.207511 | 0.936624 | 5.09756 | 0.738337 | 0.0026526 | 0.0744309 | 9.99985e-05 | 1(Win) | true |
| Jsonifier (generic) | 5379.41 | 0.137747 | 9699.93ms | 2090234 | 320 | 8.33751e+07 | 370562 | 0.0333921 | 0.953844 | 4.7195 | 0.756396 | 0.00580681 | 0.0757562 | 0.000109138 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5487.56 | 0.215804 | 9522.32ms | 2090234 | 40 | 2.45816e+07 | 363258 | 0.0399439 | 0.930467 | 5.09748 | 0.738319 | 0.00266571 | 0.0743121 | 3.26518e-06 | 1(Win) | true |
| Jsonifier (generic) | 5328.9 | 0.0865169 | 9736ms | 2090234 | 1280 | 1.34068e+08 | 374074 | 0.576643 | 0.958406 | 4.71941 | 0.756378 | 0.00588934 | 0.0756968 | 0.000167135 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8358.03 | 0.366367 | 7672.98ms | 5212421 | 160 | 7.59667e+08 | 594752 | 0.243184 | 0.603056 | 2.52183 | 0.327128 | 0.00216273 | 0.0590797 | 8.28909e-06 | 1(Win) | true |
| simdjson (ondemand) | 8018.38 | 0.235597 | 8045ms | 5212421 | 80 | 1.70662e+08 | 619945 | 0.0693869 | 0.631197 | 2.7744 | 0.33108 | 0.00188517 | 0.0591754 | 1.84511e-05 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8485.21 | 0.0737836 | 7626.53ms | 5212421 | 640 | 1.19579e+08 | 585837 | 0.243454 | 0.59905 | 2.52179 | 0.32712 | 0.0021167 | 0.0590581 | 9.21237e-06 | 1(Win) | true |
| simdjson (ondemand) | 7992.08 | 0.294771 | 8044.12ms | 5212421 | 30 | 1.00844e+08 | 621985 | 0.752465 | 0.627693 | 2.77436 | 0.331073 | 0.00189232 | 0.0591685 | 1.70106e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1251.37 | 0.131075 | 9949.06ms | 500299 | 1280 | 3.19694e+08 | 381280 | 0.143732 | 4.03438 | 17.9396 | 3.23276 | 0.0161853 | 0.0109512 | 0.00014747 | 1(Win) | true |
| simdjson (ondemand) | 1126.2 | 0.185803 | 5512.92ms | 500299 | 40 | 2.47851e+07 | 423656 | 0.140273 | 4.47394 | 18.6294 | 2.99423 | 0.0213924 | 0.0178104 | 6.30123e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.38 | 0.154077 | 9671.08ms | 500299 | 80 | 2.12498e+07 | 334498 | 0.14824 | 3.55023 | 16.8 | 2.95734 | 0.0111874 | 0.00836292 | 3.57536e-05 | 1(Win) | true |
| simdjson (ondemand) | 1243.76 | 0.382154 | 5364.05ms | 500299 | 160 | 3.43862e+08 | 383614 | 0.0451731 | 4.04214 | 17.4948 | 2.71984 | 0.0161202 | 0.0141209 | 4.11129e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2576.85 | 0.0663301 | 5522.64ms | 1151920 | 640 | 5.11762e+07 | 426318 | 0.712945 | 1.97371 | 8.56124 | 1.44239 | 0.00756694 | 0.0369119 | 3.7348e-05 | 1(Win) | true |
| simdjson (ondemand) | 2416.81 | 0.122236 | 6026.62ms | 1151920 | 80 | 2.4697e+07 | 454548 | 0.155818 | 2.09957 | 8.77842 | 1.3344 | 0.00961518 | 0.0366848 | 3.00043e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2860.51 | 0.0486122 | 5446.15ms | 1151920 | 640 | 2.23064e+07 | 384043 | 0.478224 | 1.77186 | 8.06799 | 1.32322 | 0.00546457 | 0.0324188 | 1.72511e-05 | 1(Win) | true |
| simdjson (ondemand) | 2653.23 | 0.421155 | 5852.49ms | 1151920 | 80 | 2.43259e+08 | 414046 | 0.903536 | 1.91001 | 8.28432 | 1.2149 | 0.00751976 | 0.0331357 | 1.66353e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 697.791 | 0.0427582 | 8791.12ms | 500299 | 640 | 5.4705e+07 | 683761 | 0.0657833 | 7.3146 | 35.8674 | 7.47256 | 0.0224518 | 0.0121637 | 0.000133183 | 1(Win) | true |
| simdjson (ondemand) | 413.377 | 0.105765 | 7351.43ms | 500299 | 320 | 4.76869e+08 | 1.15421e+06 | 0.0946165 | 12.2924 | 65.5822 | 13.0737 | 0.0340566 | 0.0181915 | 0.000242592 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 749.24 | 0.0571383 | 8661.36ms | 500299 | 320 | 4.23665e+07 | 636808 | 0.111829 | 6.78636 | 34.7038 | 7.1929 | 0.0161218 | 0.00713781 | 0.000120291 | 1(Win) | true |
| simdjson (ondemand) | 430.614 | 0.0759032 | 7258.14ms | 500299 | 320 | 2.26336e+08 | 1.10801e+06 | 0.192154 | 11.829 | 64.4396 | 12.7984 | 0.0281297 | 0.0130379 | 0.000526273 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1462.61 | 0.0829311 | 9732.1ms | 1151920 | 160 | 6.20787e+07 | 751094 | 0.33582 | 3.48874 | 16.5401 | 3.35417 | 0.0100732 | 0.0418588 | 8.79239e-05 | 1(Win) | true |
| simdjson (ondemand) | 916.288 | 0.0671582 | 7649.49ms | 1151920 | 160 | 1.03729e+08 | 1.19892e+06 | 0.426951 | 5.53637 | 29.1272 | 5.70398 | 0.0147532 | 0.0862645 | 5.29117e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1538.71 | 0.0999428 | 9605.55ms | 1151920 | 640 | 3.25849e+08 | 713948 | 0.0899741 | 3.28933 | 16.0379 | 3.23343 | 0.00783699 | 0.0367437 | 7.76109e-05 | 1(Win) | true |
| simdjson (ondemand) | 950.305 | 0.19288 | 7570.41ms | 1151920 | 40 | 1.98862e+08 | 1.156e+06 | 0.23302 | 5.33585 | 28.6316 | 5.58462 | 0.0123912 | 0.0776756 | 0.000147211 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5343.27 | 0.0541898 | 9674.84ms | 500299 | 640 | 1.49851e+06 | 89294 | 0.0164827 | 0.957279 | 4.95019 | 0.787881 | 0.000977725 | 3.46793e-05 | 3.12907e-05 | 1(Win) | true |
| simdjson (ondemand) | 4848.81 | 0.0318393 | 5403.97ms | 500299 | 1280 | 1.2564e+06 | 98399.8 | 0.038319 | 1.04516 | 5.51377 | 0.723761 | 0.00111258 | 1.09981e-05 | 4.95953e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5402.37 | 0.0314524 | 9592.87ms | 500299 | 4890 | 3.77317e+06 | 88317.2 | 0.15515 | 0.943519 | 4.92123 | 0.781097 | 0.000939359 | 1.34316e-05 | 9.04163e-06 | 1(Win) | true |
| simdjson (ondemand) | 4916.13 | 0.0279132 | 5330.08ms | 500299 | 1280 | 939379 | 97052.3 | 0.120136 | 1.03181 | 5.48485 | 0.716999 | 0.00108486 | 1.21021e-05 | 8.88531e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8609.85 | 0.267232 | 7087.31ms | 1151920 | 40 | 4.65041e+06 | 127593 | 0.0481645 | 0.597951 | 2.81771 | 0.375609 | 0.000946246 | 0.0081181 | 2.86478e-06 | 1(Win) | true |
| simdjson (ondemand) | 8237.84 | 0.109167 | 7232.72ms | 1151920 | 1280 | 2.71276e+07 | 133355 | 0.271869 | 0.615878 | 3.07884 | 0.347429 | 0.00110744 | 0.0111096 | 8.27762e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8658.68 | 0.111022 | 6959.57ms | 1151920 | 1280 | 2.53964e+07 | 126873 | 0.898299 | 0.587758 | 2.80513 | 0.372662 | 0.00087825 | 0.00709793 | 1.04805e-05 | 1(Win) | true |
| simdjson (ondemand) | 8374.55 | 0.105404 | 7184.68ms | 1151920 | 640 | 1.22354e+07 | 131178 | 0.160263 | 0.609965 | 3.06629 | 0.344492 | 0.00107393 | 0.00995323 | 1.63857e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3056.37 | 0.0196294 | 8359.29ms | 500299 | 2560 | 2.40382e+06 | 156108 | 0.0769089 | 1.67554 | 9.83161 | 1.81999 | 0.00204433 | 1.90253e-05 | 1.65979e-05 | 1(Win) | true |
| simdjson (ondemand) | 2875.76 | 0.0584316 | 8872.5ms | 500299 | 2560 | 2.40598e+07 | 165912 | 0.0331142 | 1.77494 | 10.1233 | 1.72865 | 0.00227153 | 4.93931e-05 | 3.6942e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3069.63 | 0.0416011 | 8359.93ms | 500299 | 640 | 2.67595e+06 | 155433 | 0.107048 | 1.66405 | 9.80264 | 1.81321 | 0.0019992 | 1.1996e-05 | 1.09341e-05 | 1(Win) | true |
| simdjson (ondemand) | 2888.5 | 0.106059 | 8796.01ms | 500299 | 640 | 1.96422e+07 | 165180 | 0.166837 | 1.76117 | 10.0943 | 1.72189 | 0.00223576 | 7.52363e-06 | 5.57791e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5517.66 | 0.241726 | 5292.47ms | 1151920 | 1280 | 2.96478e+08 | 199098 | 0.071902 | 0.927002 | 4.84651 | 0.82725 | 0.00151077 | 0.00829502 | 1.06093e-05 | 1(Win) | true |
| simdjson (ondemand) | 5445.2 | 0.549621 | 5397.59ms | 1151920 | 320 | 3.93455e+08 | 201748 | 0.251845 | 0.934425 | 5.08083 | 0.783871 | 0.0016057 | 0.0110155 | 4.07472e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5568.06 | 0.0842733 | 5284.9ms | 1151920 | 80 | 2.2116e+06 | 197296 | 0.0172043 | 0.922051 | 4.83393 | 0.824304 | 0.00149295 | 0.00366785 | 2.47413e-06 | 1(Win) | true |
| simdjson (ondemand) | 5506.07 | 0.0632682 | 5299.08ms | 1151920 | 1280 | 2.03959e+07 | 199517 | 0.102951 | 0.923315 | 5.06834 | 0.780939 | 0.00159022 | 0.00984656 | 7.97514e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1412.35 | 0.0360926 | 4556.93ms | 56369 | 1280 | 241571 | 38062.7 | 0.0290062 | 3.60195 | 15.518 | 2.9646 | 0.00648739 | 1.59524e-05 | 7.95539e-06 | 1(Win) | true |
| simdjson (ondemand) | 1246.19 | 0.0953337 | 5053.57ms | 56369 | 4890 | 8.27016e+06 | 43137.6 | 0.0128946 | 4.0847 | 16.9534 | 2.83978 | 0.00896121 | 6.02116e-05 | 3.98521e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1768.99 | 0.0276741 | 4128.02ms | 56369 | 2560 | 181058 | 30389 | 0.0398642 | 2.89522 | 13.185 | 2.45502 | 0.00546996 | 1.33953e-05 | 7.99004e-06 | 1(Win) | true |
| simdjson (ondemand) | 1408.8 | 0.0310197 | 4940.93ms | 56369 | 2560 | 358672 | 38158.5 | 0.110789 | 3.61631 | 14.6952 | 2.3474 | 0.0136766 | 1.9438e-05 | 1.17668e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1996.3 | 0.067335 | 4752.96ms | 83958 | 2560 | 1.86722e+06 | 40108.6 | 0.0429197 | 2.54652 | 10.8943 | 2.00097 | 0.00447569 | 2.76505e-05 | 1.63447e-05 | 1(Win) | true |
| simdjson (ondemand) | 1740.57 | 0.109087 | 5317.88ms | 83958 | 4890 | 1.2314e+07 | 46001.3 | 0.0103983 | 2.90776 | 11.7957 | 1.9253 | 0.00781031 | 6.59181e-05 | 2.54923e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2477.63 | 0.103006 | 4306.04ms | 83958 | 1280 | 1.41835e+06 | 32316.5 | 0.0257687 | 2.04892 | 9.33405 | 1.66038 | 0.00327647 | 1.11384e-05 | 6.5602e-06 | 1(Win) | true |
| simdjson (ondemand) | 2024.72 | 0.0416206 | 5083.8ms | 83958 | 4890 | 1.32471e+06 | 39545.5 | 0.357716 | 2.50833 | 10.2852 | 1.59539 | 0.00896325 | 1.56764e-05 | 9.4896e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.371 | 0.0186209 | 8316.54ms | 56369 | 4890 | 962857 | 75357.2 | 0.20538 | 7.14292 | 33.6446 | 7.18865 | 0.0102447 | 5.80639e-05 | 4.07409e-05 | 1(Win) | true |
| simdjson (ondemand) | 200.213 | 0.0411817 | 7038.9ms | 56369 | 1280 | 1.56501e+07 | 268503 | 0.0335396 | 25.3696 | 139.875 | 28.1045 | 0.0394688 | 0.000111015 | 7.57703e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.716 | 0.0333705 | 7941.8ms | 56369 | 4890 | 2.55558e+06 | 68505.9 | 0.0640101 | 6.47528 | 31.3328 | 6.68967 | 0.0090664 | 2.48654e-05 | 1.59989e-05 | 1(Win) | true |
| simdjson (ondemand) | 205.586 | 0.0471633 | 6948.55ms | 56369 | 1280 | 1.94677e+07 | 261486 | 0.187368 | 24.619 | 137.594 | 27.6144 | 0.0373479 | 0.000113441 | 8.73984e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 918.335 | 0.129839 | 9532.79ms | 83958 | 80 | 1.02524e+06 | 87188.9 | 0.0173157 | 5.57841 | 25.1771 | 5.16025 | 0.00777919 | 7.72708e-05 | 6.05958e-05 | 1(Win) | true |
| simdjson (ondemand) | 293.269 | 0.104976 | 7148ms | 83958 | 320 | 2.62858e+07 | 273021 | 0.0357559 | 17.2629 | 93.9415 | 18.8189 | 0.0259009 | 0.000439505 | 0.000353153 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1003.63 | 0.0235334 | 9074.03ms | 83958 | 2560 | 902373 | 79778.9 | 0.146367 | 5.06287 | 23.626 | 4.82547 | 0.00651198 | 3.84353e-05 | 3.06422e-05 | 1(Win) | true |
| simdjson (ondemand) | 302.306 | 0.06216 | 7072.1ms | 83958 | 640 | 1.73473e+07 | 264859 | 0.201175 | 16.7769 | 92.4129 | 18.4906 | 0.0245918 | 8.78788e-05 | 7.17062e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2294.74 | 0.0556026 | 3107.57ms | 56369 | 2560 | 434356 | 23426.5 | 0.0158666 | 2.21147 | 10.0055 | 1.77549 | 0.00428419 | 3.81069e-05 | 2.48571e-05 | 1(Win) | true |
| simdjson (ondemand) | 2142.51 | 0.0705149 | 3245.76ms | 56369 | 320 | 100172 | 25091 | 0.144638 | 2.3592 | 10.4228 | 1.69842 | 0.00412938 | 1.9736e-05 | 1.22519e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2873.23 | 0.0278954 | 2916.37ms | 56369 | 4890 | 133203 | 18709.8 | 0.207996 | 1.76997 | 8.34012 | 1.4148 | 0.00344246 | 1.78999e-05 | 1.03975e-05 | 1(Win) | true |
| simdjson (ondemand) | 2646 | 0.0630782 | 3072.04ms | 56369 | 40 | 6569.32 | 20316.6 | 0.244031 | 1.91533 | 8.8114 | 1.35119 | 0.00320167 | 7.98311e-06 | 3.99156e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3192.99 | 0.0898437 | 3252.63ms | 83958 | 320 | 162426 | 25076.4 | 0.107667 | 1.58713 | 7.21292 | 1.22015 | 0.00213727 | 3.30895e-05 | 2.3412e-05 | 1(Win) | true |
| simdjson (ondemand) | 3021.52 | 0.0595201 | 3427.38ms | 83958 | 1280 | 318427 | 26499.4 | 0.293746 | 1.68739 | 7.41611 | 1.16037 | 0.00325909 | 2.2649e-05 | 1.32972e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3953 | 0.0499691 | 3070.62ms | 83958 | 1280 | 131124 | 20255.2 | 0.100287 | 1.29628 | 6.08529 | 0.97469 | 0.00167287 | 1.70565e-05 | 1.11198e-05 | 1(Win) | true |
| simdjson (ondemand) | 3752.91 | 0.0823952 | 3135.59ms | 83958 | 320 | 98887.3 | 21335 | 0.114761 | 1.35301 | 6.33461 | 0.926817 | 0.00180604 | 1.00497e-05 | 7.25809e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.36 | 0.0396374 | 3717.35ms | 56369 | 1280 | 177327 | 29694.5 | 0.10638 | 2.81628 | 13.0874 | 2.50778 | 0.00623065 | 9.86801e-06 | 3.74208e-06 | 1(Win) | true |
| simdjson (ondemand) | 1350.19 | 0.0748552 | 4748.88ms | 56369 | 640 | 568476 | 39814.7 | 0.0877046 | 3.76842 | 17.4557 | 2.89404 | 0.00732863 | 3.26254e-05 | 2.17872e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2144.47 | 0.0356428 | 3539.26ms | 56369 | 2560 | 204373 | 25068 | 0.0819225 | 2.38408 | 11.4679 | 2.15886 | 0.00580233 | 2.66727e-05 | 1.83431e-05 | 1(Win) | true |
| simdjson (ondemand) | 1508.39 | 0.103991 | 4597.42ms | 56369 | 320 | 439537 | 35639.1 | 0.243432 | 3.37197 | 15.9034 | 2.56248 | 0.00700169 | 1.1254e-05 | 5.59927e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2388.63 | 0.0668608 | 4082.83ms | 83958 | 320 | 160738 | 33520.7 | 0.193498 | 2.11993 | 9.43597 | 1.73693 | 0.0042646 | 2.02482e-05 | 1.28785e-05 | 1(Win) | true |
| simdjson (ondemand) | 1941.68 | 0.20771 | 4858.07ms | 83958 | 80 | 586914 | 41236.8 | 0.385631 | 2.63954 | 12.0049 | 1.93766 | 0.00521347 | 3.64766e-05 | 2.53103e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2824.85 | 0.101606 | 3914.17ms | 83958 | 40 | 33176.8 | 28344.3 | 0.023074 | 1.8254 | 8.34173 | 1.5007 | 0.00373252 | 5.65759e-06 | 3.57322e-06 | 1(Win) | true |
| simdjson (ondemand) | 2196.98 | 0.0274827 | 4654.2ms | 83958 | 4890 | 490571 | 36444.9 | 0.0219479 | 2.31861 | 10.9546 | 1.7133 | 0.00483646 | 2.16999e-05 | 1.58688e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1294.94 | 0.0567505 | 4678.32ms | 53331 | 1280 | 635929 | 39276.2 | 0.28268 | 3.93215 | 13.634 | 2.70128 | 0.0121102 | 0.000142433 | 9.99507e-05 | 1(Win) | true |
| simdjson (ondemand) | 1006.38 | 0.225016 | 5769.89ms | 53331 | 30 | 387959 | 50538.1 | 0.363486 | 5.02574 | 18.7915 | 3.48661 | 0.0186721 | 0.000140006 | 0.00012438 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1613.79 | 0.0495364 | 4499.99ms | 53331 | 1280 | 311979 | 31516.1 | 0.0535055 | 3.18012 | 11.4116 | 2.19187 | 0.00990417 | 4.87814e-05 | 3.42935e-05 | 1(Win) | true |
| simdjson (ondemand) | 1213.04 | 0.0409468 | 5581.89ms | 53331 | 2560 | 754556 | 41928.2 | 0.329352 | 4.21298 | 16.6139 | 2.98845 | 0.0154647 | 6.09402e-05 | 4.47822e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1497.89 | 0.146746 | 4900.22ms | 65103 | 4890 | 1.80918e+07 | 41449.7 | 0.130727 | 3.40927 | 11.7239 | 2.27886 | 0.0104494 | 0.000162668 | 0.000113402 | 1(Win) | true |
| simdjson (ondemand) | 1230.49 | 0.0679537 | 5815.88ms | 65103 | 640 | 752410 | 50457.4 | 0.108065 | 4.14549 | 15.5763 | 2.85593 | 0.015942 | 4.49288e-05 | 2.56565e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1845.26 | 0.0997686 | 4662.49ms | 65103 | 320 | 360601 | 33646.9 | 0.106634 | 2.76788 | 9.90329 | 1.86175 | 0.00841066 | 4.00327e-05 | 2.80805e-05 | 1(Win) | true |
| simdjson (ondemand) | 1453.2 | 0.0390847 | 5578.9ms | 65103 | 2560 | 713844 | 42724.2 | 0.103883 | 3.49672 | 13.7963 | 2.44986 | 0.0129112 | 3.13326e-05 | 2.07544e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.983 | 0.0403321 | 5944.68ms | 53331 | 2560 | 1.13088e+06 | 52112 | 0.245379 | 5.22291 | 18.9308 | 3.84682 | 0.0157965 | 0.000112373 | 7.9127e-05 | 1(Win) | true |
| simdjson (ondemand) | 443.169 | 0.110987 | 6284.02ms | 53331 | 640 | 1.03835e+07 | 114765 | 0.14347 | 11.4981 | 40.7233 | 7.34983 | 0.0666907 | 0.000176463 | 0.000117222 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.55 | 0.0375325 | 5737.91ms | 53331 | 2560 | 696196 | 43937.8 | 0.0762793 | 4.40401 | 16.6218 | 3.3176 | 0.0131 | 3.99187e-05 | 2.43761e-05 | 1(Win) | true |
| simdjson (ondemand) | 480.017 | 0.0582729 | 6136.16ms | 53331 | 2560 | 9.75934e+06 | 105955 | 0.0208412 | 10.6072 | 38.4905 | 6.84006 | 0.061343 | 0.000121141 | 9.4655e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1095.07 | 0.0365556 | 6443.41ms | 65103 | 2560 | 1.09968e+06 | 56696.9 | 0.0169782 | 4.66928 | 16.4921 | 3.32691 | 0.0145982 | 0.0001166 | 7.68974e-05 | 1(Win) | true |
| simdjson (ondemand) | 560.038 | 0.0598282 | 6055.43ms | 65103 | 2560 | 1.12621e+07 | 110862 | 0.0249249 | 9.1168 | 33.2181 | 5.95838 | 0.0481615 | 8.72236e-05 | 5.3419e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1281.8 | 0.0281669 | 6190.18ms | 65103 | 4890 | 910230 | 48437.6 | 0.0764608 | 4.00573 | 14.6108 | 2.89656 | 0.0116007 | 0.000100106 | 8.042e-05 | 1(Win) | true |
| simdjson (ondemand) | 610.805 | 0.074194 | 5904.23ms | 65103 | 1280 | 7.28021e+06 | 101648 | 0.171313 | 8.37291 | 31.3805 | 5.53887 | 0.0438183 | 5.94011e-05 | 4.48568e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8240.96 | 0.0535415 | 1349.44ms | 53331 | 1280 | 13976.4 | 6171.66 | 0.0209672 | 0.627457 | 2.88718 | 0.418162 | 0.000664336 | 4.26288e-06 | 1.09868e-06 | 1(Win) | true |
| simdjson (ondemand) | 6744.28 | 0.0318197 | 1486.35ms | 53331 | 4890 | 28157.1 | 7541.27 | 0.144861 | 0.759252 | 3.34571 | 0.415875 | 0.000861978 | 3.44724e-06 | 7.13221e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8918.49 | 0.0345856 | 1318.06ms | 53331 | 4890 | 19022.9 | 5702.8 | 0.0574477 | 0.578793 | 2.71585 | 0.380286 | 0.000726358 | 3.99557e-06 | 1.2884e-06 | 1(Win) | true |
| simdjson (ondemand) | 7281.78 | 0.0463238 | 1448.9ms | 53331 | 4890 | 51191.9 | 6984.61 | 0.0346865 | 0.706603 | 3.18573 | 0.380267 | 0.000817666 | 1.01116e-05 | 5.99336e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8522.53 | 0.101175 | 1467.79ms | 65103 | 320 | 17384.4 | 7285.05 | 0.0261169 | 0.607035 | 2.69806 | 0.356343 | 0.000714013 | 6.52812e-06 | 4.56008e-06 | 1(Win) | true |
| simdjson (ondemand) | 7609.81 | 0.035566 | 1556.9ms | 65103 | 1280 | 10777.9 | 8158.82 | 0.051882 | 0.679254 | 2.98485 | 0.352534 | 0.000752785 | 3.69607e-06 | 1.23602e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9151.42 | 0.0557447 | 1423.98ms | 65103 | 640 | 9154.02 | 6784.42 | 0.139349 | 0.558317 | 2.55772 | 0.325315 | 0.000666396 | 2.18404e-06 | 3.84007e-07 | 1(Win) | true |
| simdjson (ondemand) | 8149.92 | 0.090859 | 1516.99ms | 65103 | 320 | 15331.4 | 7618.12 | 0.0285995 | 0.631689 | 2.85196 | 0.323011 | 0.000706189 | 2.01604e-06 | 9.60017e-08 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5710.22 | 0.117722 | 1618.35ms | 53331 | 160 | 17590.9 | 8906.91 | 0.192247 | 0.889835 | 4.28098 | 0.7142 | 0.00182785 | 5.50805e-06 | 2.69543e-06 | 1(Win) | true |
| simdjson (ondemand) | 4087.35 | 0.0710862 | 1982.64ms | 53331 | 40 | 3129.73 | 12443.4 | 0.282283 | 1.26466 | 5.90098 | 0.94761 | 0.00235792 | 9.84418e-06 | 5.62525e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6124.36 | 0.0306012 | 1584.52ms | 53331 | 4890 | 31580.7 | 8304.6 | 0.0331847 | 0.836083 | 4.10969 | 0.676361 | 0.00164744 | 3.53927e-06 | 6.94049e-07 | 1(Win) | true |
| simdjson (ondemand) | 4292.06 | 0.0887857 | 1947.17ms | 53331 | 40 | 4427.65 | 11849.9 | 0.0245492 | 1.2047 | 5.73878 | 0.911609 | 0.00217697 | 4.21893e-06 | 0 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6303.94 | 0.0331305 | 1717.31ms | 65103 | 4890 | 52064.7 | 9848.92 | 0.0356276 | 0.813165 | 3.81793 | 0.607607 | 0.00144446 | 5.76717e-06 | 2.01348e-06 | 1(Win) | true |
| simdjson (ondemand) | 4747.74 | 0.057602 | 2053.8ms | 65103 | 640 | 36314.8 | 13077.2 | 0.0629952 | 1.08474 | 5.07619 | 0.787829 | 0.00200958 | 4.39208e-06 | 1.60803e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6687.73 | 0.0336939 | 1675.86ms | 65103 | 2560 | 25048.8 | 9283.72 | 0.267363 | 0.766411 | 3.67762 | 0.57661 | 0.00130808 | 3.75007e-06 | 1.35002e-06 | 1(Win) | true |
| simdjson (ondemand) | 4966.16 | 0.0457294 | 2013.83ms | 65103 | 1280 | 41837.1 | 12502 | 0.151028 | 1.03759 | 4.94332 | 0.758337 | 0.00194351 | 3.82807e-06 | 1.22402e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1284.06 | 0.0460754 | 1613.14ms | 11812 | 2560 | 41827 | 8772.82 | 0.116408 | 3.98922 | 18.1686 | 3.39625 | 0.00512019 | 3.16812e-05 | 1.35588e-05 | 1(Win) | true |
| simdjson (ondemand) | 1045.34 | 0.0791464 | 1821.24ms | 11812 | 640 | 46556.3 | 10776.3 | 0.189699 | 4.93198 | 20.2722 | 3.51981 | 0.00900977 | 2.71175e-05 | 1.13761e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1403.1 | 0.0719432 | 1596.24ms | 11812 | 320 | 10675.7 | 8028.48 | 0.128672 | 3.6889 | 17.0736 | 3.15044 | 0.00474253 | 1.11116e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (ondemand) | 1106.63 | 0.0463346 | 1802.74ms | 11812 | 2560 | 56949.3 | 10179.3 | 0.0917877 | 4.62807 | 19.2106 | 3.28209 | 0.00807081 | 3.7237e-05 | 1.61382e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2474.91 | 0.0757637 | 1724.96ms | 25388 | 80 | 4394.93 | 9782.95 | 0.0465311 | 2.09055 | 9.37266 | 1.63885 | 0.00292412 | 8.86245e-06 | 2.46179e-06 | 1(Win) | true |
| simdjson (ondemand) | 2104.06 | 0.150878 | 1916.01ms | 25388 | 80 | 24114.7 | 11507.2 | 0.127366 | 2.40937 | 10.0874 | 1.67384 | 0.00400484 | 9.84717e-06 | 5.41594e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2647.95 | 0.0947194 | 1728.32ms | 25388 | 160 | 12001.5 | 9143.63 | 0.151084 | 1.94669 | 8.87002 | 1.52639 | 0.0026964 | 3.54498e-05 | 2.14176e-05 | 1(Win) | true |
| simdjson (ondemand) | 2265.5 | 0.0422046 | 1875.63ms | 25388 | 4890 | 99484.7 | 10687.2 | 0.26318 | 2.25834 | 9.57381 | 1.55904 | 0.00348837 | 2.1845e-05 | 1.25335e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 786.513 | 0.0643392 | 2186.66ms | 11812 | 2560 | 217384 | 14322.5 | 0.113899 | 6.50361 | 29.365 | 5.95992 | 0.0147266 | 7.01088e-05 | 4.02133e-05 | 1(Win) | true |
| simdjson (ondemand) | 686.704 | 0.117081 | 2380.27ms | 11812 | 160 | 59020.4 | 16404.2 | 0.05746 | 7.38418 | 33.0921 | 6.09948 | 0.0133662 | 6.98442e-05 | 3.33347e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 821.775 | 0.0556041 | 2165.09ms | 11812 | 1280 | 74364.2 | 13707.9 | 0.087943 | 6.21246 | 28.2974 | 5.72054 | 0.0147462 | 6.0783e-05 | 3.51205e-05 | 1(Win) | true |
| simdjson (ondemand) | 730.044 | 0.176808 | 2360.87ms | 11812 | 80 | 59544.7 | 15430.3 | 0.00113412 | 7.07149 | 32.0207 | 5.86031 | 0.0130799 | 2.85726e-05 | 9.52421e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1551.02 | 0.0653984 | 2315.43ms | 25388 | 640 | 66701.3 | 15610.2 | 0.376136 | 3.2963 | 14.7301 | 2.90247 | 0.00684926 | 2.191e-05 | 1.12627e-05 | 1(Win) | true |
| simdjson (ondemand) | 1427.16 | 0.0720115 | 2444.77ms | 25388 | 1280 | 191041 | 16965.1 | 0.0658125 | 3.59237 | 15.8508 | 2.838 | 0.00645288 | 3.86809e-05 | 2.52334e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1641.56 | 0.0435208 | 2284.66ms | 25388 | 1280 | 52741.2 | 14749.3 | 0.113603 | 3.12137 | 14.1985 | 2.78395 | 0.00666343 | 2.67105e-05 | 1.73249e-05 | 1(Win) | true |
| simdjson (ondemand) | 1484.73 | 0.106755 | 2418.22ms | 25388 | 320 | 96980.3 | 16307.2 | 0.283367 | 3.4299 | 15.3514 | 2.72645 | 0.00645064 | 1.46477e-05 | 4.30814e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2400.71 | 0.0442282 | 1197.6ms | 11812 | 2560 | 11025.7 | 4692.27 | 0.0887807 | 2.15513 | 10.3996 | 1.86624 | 0.0033976 | 2.31491e-05 | 7.37465e-06 | 1(Win) | true |
| simdjson (ondemand) | 2067.85 | 0.101197 | 1276.54ms | 11812 | 320 | 9725.21 | 5447.6 | 0.0598672 | 2.50733 | 11.4714 | 1.83949 | 0.0032504 | 1.16407e-05 | 1.58737e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2452.63 | 0.0624499 | 1197.42ms | 11812 | 2560 | 21061.4 | 4592.95 | 0.0189538 | 2.11447 | 10.2116 | 1.82061 | 0.00321419 | 1.68327e-05 | 3.14167e-06 | 1(Win) | true |
| simdjson (ondemand) | 2111.19 | 0.122437 | 1270.57ms | 11812 | 320 | 13657.3 | 5335.77 | 0.190412 | 2.45494 | 11.2847 | 1.79402 | 0.00307341 | 1.21698e-05 | 2.38105e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4202.87 | 0.0376941 | 1305.63ms | 25388 | 2560 | 12071.3 | 5760.8 | 0.131313 | 1.22608 | 5.673 | 0.930794 | 0.00191434 | 9.32404e-06 | 2.64643e-06 | 1(Win) | true |
| simdjson (ondemand) | 3952.46 | 0.0696352 | 1337.62ms | 25388 | 1280 | 23291.1 | 6125.77 | 0.0452188 | 1.30586 | 5.97255 | 0.887073 | 0.00187724 | 9.87794e-06 | 2.80029e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4295.8 | 0.0279011 | 1300.29ms | 25388 | 4890 | 12092.6 | 5636.18 | 0.0790753 | 1.19999 | 5.58551 | 0.909564 | 0.0018222 | 7.7408e-06 | 2.10234e-06 | 1(Win) | true |
| simdjson (ondemand) | 4016.23 | 0.0651761 | 1367.07ms | 25388 | 640 | 9880.45 | 6028.51 | 0.181551 | 1.28725 | 5.88569 | 0.865921 | 0.00189041 | 7.75465e-06 | 2.3387e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1766.39 | 0.0345847 | 1364.5ms | 11812 | 4890 | 23787.6 | 6377.3 | 0.219734 | 2.9067 | 13.7036 | 2.57831 | 0.00762167 | 1.78322e-05 | 4.25895e-06 | 1(Win) | true |
| simdjson (ondemand) | 1614.25 | 0.0255241 | 1428.04ms | 11812 | 4890 | 15513.6 | 6978.34 | 0.0906442 | 3.1737 | 14.3788 | 2.37843 | 0.00755833 | 2.37012e-05 | 8.36209e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1804.2 | 0.040164 | 1364.96ms | 11812 | 2560 | 16098.6 | 6243.64 | 0.0380219 | 2.85452 | 13.5156 | 2.53268 | 0.00728523 | 2.39097e-05 | 7.27544e-06 | 1(Win) | true |
| simdjson (ondemand) | 1644.36 | 0.0419349 | 1418.5ms | 11812 | 2560 | 21127.5 | 6850.59 | 0.189985 | 3.12164 | 14.1921 | 2.33297 | 0.00735319 | 1.43194e-05 | 2.97632e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3273.89 | 0.12205 | 1464.07ms | 25388 | 320 | 26070.8 | 7395.46 | 0.0553243 | 1.55061 | 7.21636 | 1.2823 | 0.00328132 | 6.89302e-06 | 9.84717e-07 | 1(Win) | true |
| simdjson (ondemand) | 3224.15 | 0.0724889 | 1484.53ms | 25388 | 80 | 2370.61 | 7509.54 | 0.0241301 | 1.60667 | 7.32523 | 1.13782 | 0.00353612 | 8.3701e-06 | 3.44651e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3389.82 | 0.0804079 | 1455.69ms | 25388 | 80 | 2638.71 | 7142.52 | 0.0129523 | 1.52863 | 7.12888 | 1.26107 | 0.0030802 | 2.21561e-05 | 1.72326e-05 | 1(Win) | true |
| simdjson (ondemand) | 3250.63 | 0.0792899 | 1487.02ms | 25388 | 2560 | 89288.8 | 7448.36 | 0.0502637 | 1.57483 | 7.23838 | 1.11667 | 0.003276 | 1.00934e-05 | 3.0157e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1537.57 | 0.0264603 | 7460.27ms | 108313 | 2560 | 808951 | 67181.1 | 0.0279588 | 3.29352 | 14.7548 | 2.81716 | 0.00406717 | 2.89417e-05 | 1.87499e-05 | 1(Win) | true |
| simdjson (ondemand) | 1437.8 | 0.102551 | 7942.45ms | 108313 | 320 | 1.73698e+06 | 71842.7 | 0.204971 | 3.53429 | 16.4494 | 2.45138 | 0.00647894 | 2.89381e-05 | 1.97633e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1670.71 | 0.0513246 | 7093.71ms | 108313 | 640 | 644452 | 61827.3 | 0.0213023 | 3.04233 | 14.0168 | 2.64686 | 0.00348241 | 1.87535e-05 | 1.38343e-05 | 1(Win) | true |
| simdjson (ondemand) | 1553.72 | 0.0532238 | 7599.22ms | 108313 | 1280 | 1.60264e+06 | 66482.5 | 0.0281662 | 3.27236 | 15.7286 | 2.28477 | 0.00597362 | 1.20239e-05 | 7.76828e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2341.63 | 0.0676252 | 8233.92ms | 183677 | 160 | 409460 | 74806.1 | 0.0656544 | 2.15804 | 9.4263 | 1.71097 | 0.00229006 | 1.01401e-05 | 6.22696e-06 | 1(Win) | true |
| simdjson (ondemand) | 2316.49 | 0.0468165 | 8300.31ms | 183677 | 1280 | 1.6042e+06 | 75618 | 0.332857 | 2.19393 | 10.2182 | 1.46798 | 0.00403149 | 1.37937e-05 | 9.65945e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2515.44 | 0.0312925 | 7914.44ms | 183677 | 1280 | 607816 | 69637.2 | 0.0190229 | 2.01342 | 9.01236 | 1.61519 | 0.00201107 | 7.1457e-06 | 4.28742e-06 | 1(Win) | true |
| simdjson (ondemand) | 2481.23 | 0.0611341 | 7988.11ms | 183677 | 4890 | 9.10858e+06 | 70597.2 | 0.183115 | 2.04886 | 9.79527 | 1.37029 | 0.00362388 | 1.76512e-05 | 1.39148e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 631.396 | 0.0606239 | 8757.96ms | 108313 | 320 | 3.14771e+06 | 163598 | 0.086441 | 8.06521 | 36.7512 | 7.35903 | 0.0101643 | 2.80437e-05 | 1.77437e-05 | 1(Win) | true |
| simdjson (ondemand) | 236.938 | 0.0853334 | 5667.23ms | 108313 | 640 | 8.8575e+07 | 435960 | 0.221764 | 21.5297 | 99.9535 | 18.0914 | 0.0792099 | 0.00027911 | 0.000236612 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 656.46 | 0.0945012 | 8473.49ms | 108313 | 160 | 3.53785e+06 | 157352 | 0.0448718 | 7.73149 | 36.0328 | 7.19408 | 0.00944981 | 2.56779e-05 | 1.66762e-05 | 1(Win) | true |
| simdjson (ondemand) | 241.39 | 0.135461 | 5579.65ms | 108313 | 160 | 5.37617e+07 | 427920 | 0.0246062 | 21.1081 | 99.2364 | 17.9269 | 0.0761577 | 4.87014e-05 | 3.37563e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 960.345 | 0.0424038 | 9714.92ms | 183677 | 2560 | 1.53146e+07 | 182401 | 0.100303 | 5.3113 | 23.8384 | 4.61256 | 0.00675894 | 2.998e-05 | 1.92253e-05 | 1(Win) | true |
| simdjson (ondemand) | 409.738 | 0.0767081 | 5545.05ms | 183677 | 640 | 6.88271e+07 | 427512 | 0.0150994 | 12.4777 | 58.6301 | 10.5308 | 0.0419512 | 0.0001079 | 8.76284e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 993.535 | 0.0727908 | 9460.84ms | 183677 | 1280 | 2.10817e+07 | 176308 | 0.326331 | 5.12926 | 23.4143 | 4.51526 | 0.00629566 | 1.75155e-05 | 8.5876e-06 | 1(Win) | true |
| simdjson (ondemand) | 414.423 | 0.0631257 | 5492.36ms | 183677 | 640 | 4.55632e+07 | 422679 | 0.165325 | 12.3009 | 58.2078 | 10.4338 | 0.0412745 | 2.39721e-05 | 1.67413e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5008.92 | 0.0267041 | 2797.92ms | 108313 | 4890 | 148299 | 20622.3 | 0.689722 | 1.02088 | 5.5017 | 0.852382 | 0.000893982 | 3.93467e-06 | 1.35939e-06 | 1(Win) | true |
| simdjson (ondemand) | 4236.31 | 0.0270664 | 3177.07ms | 108313 | 4890 | 212987 | 24383.3 | 0.135911 | 1.2036 | 6.07973 | 0.765467 | 0.00167026 | 6.0927e-06 | 3.45322e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5228.96 | 0.0313635 | 2720.49ms | 108313 | 4890 | 187710 | 19754.5 | 0.120351 | 0.976875 | 5.3187 | 0.803782 | 0.000700734 | 6.19465e-06 | 4.31605e-06 | 1(Win) | true |
| simdjson (ondemand) | 4462.23 | 0.115042 | 3046.79ms | 108313 | 160 | 113472 | 23148.8 | 0.135341 | 1.14398 | 5.89738 | 0.716978 | 0.00144287 | 1.55798e-06 | 3.46219e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6846.96 | 0.0962044 | 3304.84ms | 183677 | 160 | 96922.4 | 25583.3 | 0.0992841 | 0.752471 | 3.79782 | 0.533894 | 0.00057499 | 4.83185e-06 | 3.36869e-06 | 1(Win) | true |
| simdjson (ondemand) | 6223.21 | 0.0249753 | 3540.26ms | 183677 | 2560 | 126515 | 28147.5 | 0.221945 | 0.816729 | 4.09533 | 0.473119 | 0.00119621 | 3.87484e-06 | 2.42231e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7121.99 | 0.0566426 | 3191.5ms | 183677 | 1280 | 248429 | 24595.4 | 0.188833 | 0.714213 | 3.69028 | 0.5053 | 0.000455028 | 1.96081e-06 | 6.25248e-07 | 1(Win) | true |
| simdjson (ondemand) | 6552.53 | 0.0548204 | 3420.87ms | 183677 | 320 | 68726.9 | 26732.9 | 0.125975 | 0.786815 | 3.9878 | 0.444525 | 0.00116242 | 9.25538e-06 | 7.48597e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3426.22 | 0.0240084 | 3746.32ms | 108313 | 2560 | 134121 | 30148.4 | 0.0189878 | 1.49857 | 7.98944 | 1.4489 | 0.00149432 | 3.89136e-06 | 1.51471e-06 | 1(Win) | true |
| simdjson (ondemand) | 2533.34 | 0.0473156 | 4805.59ms | 108313 | 1280 | 476423 | 40774.4 | 0.138685 | 2.014 | 10.3325 | 1.59398 | 0.00342149 | 5.00575e-06 | 2.08453e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3562.34 | 0.0379314 | 3642.96ms | 108313 | 1280 | 154845 | 28996.5 | 0.186511 | 1.44357 | 7.80531 | 1.40025 | 0.00129581 | 1.27308e-05 | 9.1171e-06 | 1(Win) | true |
| simdjson (ondemand) | 2582.85 | 0.169479 | 4711.22ms | 108313 | 80 | 367522 | 39992.7 | 0.0487201 | 1.95898 | 10.1484 | 1.54533 | 0.00315013 | 4.61625e-06 | 2.65434e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4960.64 | 0.0409222 | 4245.39ms | 183677 | 1280 | 267278 | 35311.6 | 0.279608 | 1.02238 | 5.33292 | 0.898186 | 0.000851325 | 5.38905e-06 | 3.3219e-06 | 1(Win) | true |
| simdjson (ondemand) | 3965.43 | 0.0370869 | 5165.61ms | 183677 | 2560 | 687084 | 44173.7 | 0.0255398 | 1.28889 | 6.58849 | 0.95883 | 0.00207441 | 4.43841e-06 | 2.34149e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5182.78 | 0.0622503 | 4137.84ms | 183677 | 640 | 283300 | 33798.1 | 0.0268486 | 0.989218 | 5.22434 | 0.869494 | 0.000704651 | 4.87439e-06 | 2.87529e-06 | 1(Win) | true |
| simdjson (ondemand) | 4138.72 | 0.179417 | 5020.21ms | 183677 | 40 | 230655 | 42324.2 | 0.154185 | 1.24472 | 6.47991 | 0.930139 | 0.00196731 | 2.04163e-06 | 1.36108e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 596.238 | 0.124911 | 9162.19ms | 1834197 | 40 | 5.37174e+08 | 2.93377e+06 | 0.210192 | 8.47398 | 35.2001 | 7.39616 | 0.0427897 | 0.138753 | 0.00226307 | 1(Win) | true |
| simdjson (ondemand) | 592.932 | 0.0961823 | 9225.67ms | 1834197 | 80 | 6.44113e+08 | 2.95013e+06 | 0.369629 | 8.5346 | 36.8495 | 6.28437 | 0.038142 | 0.139274 | 0.0113123 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 649.669 | 0.0846388 | 9203.19ms | 1834197 | 80 | 4.15467e+08 | 2.69249e+06 | 0.582675 | 7.83438 | 32.2077 | 6.69674 | 0.0416021 | 0.117952 | 0.00488903 | 1(Win) | true |
| simdjson (ondemand) | 642.113 | 0.0828096 | 9165.06ms | 1834197 | 160 | 8.14236e+08 | 2.72417e+06 | 0.197859 | 7.87433 | 33.8585 | 5.58498 | 0.0369998 | 0.118659 | 0.00710261 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2203.03 | 0.145615 | 9960.36ms | 7351818 | 80 | 1.71813e+09 | 3.18255e+06 | 0.0109688 | 2.30086 | 9.58799 | 1.88639 | 0.0109745 | 0.0581652 | 0.00206615 | 1(Win) | true |
| simdjson (ondemand) | 2154.72 | 0.533432 | 10184.4ms | 7351818 | 80 | 2.41022e+10 | 3.2539e+06 | 0.255134 | 2.34366 | 10.1037 | 1.60974 | 0.00894675 | 0.0578803 | 0.001912 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2352.42 | 0.0964058 | 9968.56ms | 7351818 | 80 | 6.60473e+08 | 2.98043e+06 | 0.148805 | 2.14244 | 8.83612 | 1.71004 | 0.0110558 | 0.0536011 | 0.00524755 | 1(Win) | true |
| simdjson (ondemand) | 2337.88 | 0.105218 | 10076.6ms | 7351818 | 80 | 7.96552e+08 | 2.99897e+06 | 0.00168977 | 2.16333 | 9.35196 | 1.43343 | 0.00895047 | 0.0535999 | 0.00192133 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 389.464 | 0.220971 | 6792.23ms | 1834197 | 30 | 2.95494e+09 | 4.49136e+06 | 0.0189488 | 12.9872 | 61.6091 | 13.5443 | 0.0441317 | 0.344241 | 0.00481679 | 1(Win) | true |
| simdjson (ondemand) | 270.858 | 0.131524 | 9656.12ms | 1834197 | 80 | 5.77181e+09 | 6.4581e+06 | 1.6404 | 18.7684 | 104.93 | 21.1332 | 0.0396321 | 0.789266 | 0.0368776 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 410.758 | 0.193025 | 6812.63ms | 1834197 | 30 | 2.02706e+09 | 4.25853e+06 | 0.0515106 | 12.298 | 58.6197 | 12.8453 | 0.0427448 | 0.322859 | 0.0020727 | 1(Win) | true |
| simdjson (ondemand) | 285.181 | 0.0870662 | 9691.16ms | 1834197 | 80 | 2.2816e+09 | 6.13374e+06 | 0.388591 | 17.8336 | 101.946 | 20.4362 | 0.0385444 | 0.767757 | 0.0154815 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1368.86 | 0.190607 | 8119.36ms | 7351818 | 80 | 7.62505e+09 | 5.12197e+06 | 0.573533 | 3.71887 | 16.1875 | 3.42781 | 0.0114719 | 0.18707 | 0.00385918 | 1(Win) | true |
| simdjson (ondemand) | 929.088 | 0.233126 | 5331.77ms | 7351818 | 40 | 1.23799e+10 | 7.54636e+06 | 0.0039301 | 5.47029 | 27.0836 | 5.31268 | 0.00970294 | 0.436166 | 0.00407739 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.59 | 0.197115 | 7885.97ms | 7351818 | 80 | 7.50796e+09 | 4.9147e+06 | 0.94452 | 3.54801 | 15.4419 | 3.25349 | 0.0111869 | 0.181742 | 0.00209611 | 1(Win) | true |
| simdjson (ondemand) | 958.022 | 0.310974 | 5404.25ms | 7351818 | 30 | 1.55385e+10 | 7.31846e+06 | 0.105468 | 5.32148 | 26.3384 | 5.13852 | 0.00942217 | 0.430835 | 0.00531121 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4366.51 | 0.0651247 | 5214.02ms | 1834197 | 640 | 4.35607e+07 | 400601 | 0.135838 | 1.17547 | 6.3732 | 0.867841 | 0.00352372 | 0.0752987 | 0.000178528 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 4327.16 | 0.515147 | 5254.65ms | 1834197 | 320 | 1.38771e+09 | 404243 | 0.135351 | 1.18826 | 6.02484 | 0.923116 | 0.00634406 | 0.0755499 | 5.88575e-05 | 1(Tie) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4370.83 | 0.187109 | 5198.84ms | 1834197 | 40 | 2.24292e+07 | 400205 | 0.0570736 | 1.17581 | 6.02462 | 0.923066 | 0.00648131 | 0.0755408 | 1.30302e-05 | 1(Win) | true |
| simdjson (ondemand) | 4341.28 | 0.0758303 | 5234.48ms | 1834197 | 160 | 1.49369e+07 | 402928 | 0.23485 | 1.16996 | 6.37297 | 0.86779 | 0.0034266 | 0.0754631 | 6.32089e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9792.55 | 0.146609 | 9236.86ms | 7351818 | 640 | 7.05176e+08 | 715977 | 0.118352 | 0.524545 | 2.49481 | 0.256655 | 0.000773795 | 0.0424152 | 0.000197785 | 1(Win) | true |
| Jsonifier (generic) | 9420.6 | 0.503668 | 9676.02ms | 7351818 | 40 | 5.62058e+08 | 744246 | 0.140535 | 0.545113 | 2.25894 | 0.261914 | 0.00243191 | 0.0423787 | 0.000213199 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9661.19 | 0.308622 | 9257.95ms | 7351818 | 640 | 3.21043e+09 | 725712 | 0.187584 | 0.527868 | 2.49475 | 0.256642 | 0.000782074 | 0.0424168 | 0.000117924 | 1(Win) | true |
| Jsonifier (generic) | 9331.67 | 0.317746 | 9671.32ms | 7351818 | 80 | 4.55954e+08 | 751338 | 0.0279905 | 0.544484 | 2.25888 | 0.261901 | 0.00243062 | 0.0423636 | 0.00019637 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3061.35 | 0.0878068 | 7358.38ms | 1834197 | 640 | 1.61102e+08 | 571390 | 0.110867 | 1.65817 | 8.47945 | 1.62435 | 0.00610163 | 0.113216 | 2.45083e-06 | 1(Win) | true |
| simdjson (ondemand) | 2443.78 | 0.175821 | 9178.09ms | 1834197 | 80 | 1.26706e+08 | 715786 | 0.157919 | 2.06826 | 12.6838 | 2.27012 | 0.00344015 | 0.150495 | 7.27839e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3090.92 | 0.131192 | 7359.07ms | 1834197 | 320 | 1.76393e+08 | 565924 | 0.312053 | 1.66252 | 8.47922 | 1.6243 | 0.00624609 | 0.113164 | 3.28482e-06 | 1(Win) | true |
| simdjson (ondemand) | 2472.29 | 0.146101 | 9180.27ms | 1834197 | 320 | 3.4194e+08 | 707533 | 0.103293 | 2.07096 | 12.6836 | 2.27007 | 0.00335851 | 0.150411 | 3.37171e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7328.16 | 0.136232 | 6164.98ms | 7351818 | 320 | 5.43634e+08 | 956753 | 1.0951 | 0.694455 | 2.87135 | 0.436869 | 0.00241249 | 0.0635534 | 1.32684e-05 | 1(Win) | true |
| simdjson (ondemand) | 6256.26 | 0.178055 | 7140.03ms | 7351818 | 160 | 6.37075e+08 | 1.12068e+06 | 0.0456798 | 0.811613 | 4.06923 | 0.606507 | 0.000803906 | 0.0848094 | 3.35419e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7308.25 | 0.160152 | 6109.92ms | 7351818 | 160 | 3.77699e+08 | 959360 | 0.0314401 | 0.697136 | 2.8713 | 0.436856 | 0.00239287 | 0.0635397 | 3.49208e-05 | 1(Win) | true |
| simdjson (ondemand) | 6287.09 | 0.0952002 | 7073.34ms | 7351818 | 320 | 3.60675e+08 | 1.11518e+06 | 0.340746 | 0.807338 | 4.06918 | 0.606495 | 0.000793479 | 0.0847928 | 5.22056e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1145.11 | 0.0320948 | 8935.55ms | 409725 | 1280 | 1.53523e+07 | 341229 | 0.0594755 | 4.45435 | 18.6831 | 3.58053 | 0.0137409 | 0.0252009 | 0.000114404 | 1(Win) | true |
| simdjson (ondemand) | 937.933 | 0.122057 | 5388.74ms | 409725 | 640 | 1.65482e+08 | 416602 | 0.0852707 | 5.40469 | 21.0167 | 3.75124 | 0.0194966 | 0.0382981 | 0.00013805 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1383.65 | 0.0601388 | 8527.5ms | 409725 | 640 | 1.84596e+07 | 282401 | 0.154891 | 3.66274 | 15.7026 | 2.90969 | 0.0103996 | 0.00537561 | 5.7245e-05 | 1(Win) | true |
| simdjson (ondemand) | 1107.55 | 0.164729 | 5136.04ms | 409725 | 30 | 1.01326e+07 | 352801 | 0.0540162 | 4.55955 | 18.0424 | 3.082 | 0.0157147 | 0.0183827 | 1.2366e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1798.88 | 0.105322 | 9378.95ms | 676745 | 320 | 4.56912e+07 | 358776 | 0.0748696 | 2.82324 | 11.8396 | 2.18809 | 0.00976021 | 0.0245839 | 8.08696e-05 | 1(Win) | true |
| simdjson (ondemand) | 1489.95 | 0.0905 | 5614.28ms | 676745 | 640 | 9.83523e+07 | 433165 | 0.0693833 | 3.41784 | 13.2473 | 2.2971 | 0.0130212 | 0.0345998 | 6.11382e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2176.5 | 0.0565391 | 8901.17ms | 676745 | 1280 | 3.59783e+07 | 296528 | 0.205867 | 2.32907 | 10.035 | 1.78189 | 0.00729673 | 0.00991544 | 2.91746e-05 | 1(Win) | true |
| simdjson (ondemand) | 1749.38 | 0.417504 | 5313.39ms | 676745 | 160 | 3.79597e+08 | 368927 | 0.0339518 | 2.89462 | 11.4448 | 1.89166 | 0.0105961 | 0.0157288 | 3.01905e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 839.167 | 0.0512182 | 6010.34ms | 409725 | 640 | 3.64012e+07 | 465633 | 0.0886349 | 6.06716 | 28.3116 | 5.7895 | 0.0123691 | 0.0271238 | 3.79523e-05 | 1(Win) | true |
| simdjson (ondemand) | 452.788 | 0.0636674 | 5492ms | 409725 | 320 | 9.66004e+07 | 862973 | 0.00150825 | 11.2082 | 50.4861 | 9.25541 | 0.0351991 | 0.0417366 | 5.62878e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 974.831 | 0.0748488 | 5784.83ms | 409725 | 320 | 2.88036e+07 | 400833 | 0.026279 | 5.23472 | 25.3384 | 5.11631 | 0.00894374 | 0.0096078 | 1.00525e-05 | 1(Win) | true |
| simdjson (ondemand) | 495.262 | 0.147744 | 5340.46ms | 409725 | 30 | 4.07621e+07 | 788964 | 0.0441903 | 10.3397 | 47.5217 | 8.5845 | 0.0312106 | 0.0184327 | 6.46775e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1258.58 | 0.112116 | 6676.74ms | 676745 | 320 | 1.05772e+08 | 512795 | 0.364404 | 4.04554 | 18.2038 | 3.67752 | 0.00890404 | 0.024664 | 1.31512e-05 | 1(Win) | true |
| simdjson (ondemand) | 728.879 | 0.060111 | 5630.12ms | 676745 | 320 | 9.0656e+07 | 885461 | 0.212687 | 6.94917 | 30.8713 | 5.5912 | 0.0228554 | 0.0402431 | 0.00019984 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.73 | 0.0672681 | 6376.55ms | 676745 | 160 | 1.46914e+07 | 450466 | 0.0567665 | 3.53622 | 16.4046 | 3.27024 | 0.00669359 | 0.0100306 | 8.72744e-06 | 1(Win) | true |
| simdjson (ondemand) | 796.333 | 0.163458 | 5505.12ms | 676745 | 40 | 7.01992e+07 | 810458 | 0.184009 | 6.40068 | 29.0765 | 5.18503 | 0.0204388 | 0.0170054 | 4.17439e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2429.23 | 0.049203 | 8654.23ms | 409725 | 640 | 4.00877e+06 | 160851 | 0.229945 | 2.10549 | 9.61437 | 1.76263 | 0.00678904 | 0.000180933 | 5.91593e-05 | 1(Win) | true |
| simdjson (ondemand) | 2001.08 | 0.07749 | 5203.95ms | 409725 | 320 | 7.32648e+06 | 195266 | 0.0386646 | 2.54829 | 11.0298 | 1.79964 | 0.0072117 | 0.00059286 | 1.52999e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2841.49 | 0.026635 | 8496ms | 409725 | 2560 | 3.43429e+06 | 137514 | 0.114384 | 1.78701 | 8.59049 | 1.52801 | 0.00467187 | 2.53018e-05 | 1.14492e-05 | 1(Win) | true |
| simdjson (ondemand) | 2249.09 | 0.0324219 | 5119.22ms | 409725 | 1280 | 4.06125e+06 | 173735 | 0.234784 | 2.25557 | 10.0158 | 1.56464 | 0.0060052 | 0.000151464 | 3.29337e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3503.88 | 0.0574887 | 9813.29ms | 676745 | 2560 | 2.8705e+07 | 184194 | 0.0144323 | 1.4519 | 6.39998 | 1.10306 | 0.00489538 | 0.000667236 | 3.70876e-05 | 1(Win) | true |
| simdjson (ondemand) | 3090.79 | 0.0616289 | 5517.68ms | 676745 | 320 | 5.29944e+06 | 208812 | 0.00741602 | 1.64732 | 7.0671 | 1.09077 | 0.00492403 | 0.00137292 | 5.21799e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3932.79 | 0.0329016 | 9906.98ms | 676745 | 2560 | 7.46316e+06 | 164106 | 0.0804694 | 1.29248 | 5.78246 | 0.961379 | 0.00453852 | 0.000338896 | 4.38854e-06 | 1(Win) | true |
| simdjson (ondemand) | 3458.32 | 0.113797 | 5418.15ms | 676745 | 1280 | 5.77285e+07 | 186621 | 0.017838 | 1.46369 | 6.45235 | 0.948282 | 0.00402245 | 0.00064002 | 6.47285e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1830.75 | 0.0735503 | 5635.63ms | 409725 | 160 | 3.9429e+06 | 213434 | 0.0564544 | 2.76721 | 12.6223 | 2.39711 | 0.00960957 | 7.07792e-05 | 5.58301e-06 | 1(Win) | true |
| simdjson (ondemand) | 1457.43 | 0.126341 | 7018.86ms | 409725 | 80 | 9.17891e+06 | 268105 | 0.0571138 | 3.48497 | 15.3107 | 2.61244 | 0.01205 | 0.000713954 | 7.16029e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2095.11 | 0.0629224 | 5521.45ms | 409725 | 320 | 4.40688e+06 | 186503 | 0.302103 | 2.42901 | 11.5983 | 2.16044 | 0.00732722 | 1.3416e-05 | 5.71267e-06 | 1(Win) | true |
| simdjson (ondemand) | 1608.82 | 0.0670241 | 6901.67ms | 409725 | 320 | 8.47977e+06 | 242877 | 0.0340424 | 3.17798 | 14.2911 | 2.37458 | 0.0105099 | 7.42953e-05 | 1.39575e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2777.54 | 0.0697595 | 6161.73ms | 676745 | 320 | 8.40786e+06 | 232362 | 0.142036 | 1.83902 | 8.31876 | 1.50224 | 0.00661215 | 0.000648167 | 6.76492e-06 | 1(Win) | true |
| simdjson (ondemand) | 2299.04 | 0.166898 | 7363.06ms | 676745 | 40 | 8.78051e+06 | 280724 | 0.00418246 | 2.2183 | 9.71284 | 1.59304 | 0.0078411 | 0.00142816 | 1.85077e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3043.99 | 0.110465 | 6161.44ms | 676745 | 160 | 8.7768e+06 | 212022 | 0.0479189 | 1.67138 | 7.69956 | 1.35914 | 0.00621668 | 0.000481579 | 2.35041e-05 | 1(Win) | true |
| simdjson (ondemand) | 2475.06 | 0.181491 | 7386.3ms | 676745 | 30 | 6.71905e+06 | 260759 | 0.0239615 | 2.04612 | 9.09785 | 1.44975 | 0.00735728 | 0.000761291 | 2.06873e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1685.76 | 0.0458954 | 8025.41ms | 264040 | 2560 | 1.20316e+07 | 149373 | 0.156817 | 3.02308 | 10.463 | 1.89313 | 0.0133467 | 8.46685e-05 | 3.58492e-05 | 1(Win) | true |
| simdjson (ondemand) | 1650.71 | 0.0630474 | 8157.54ms | 264040 | 2560 | 2.36795e+07 | 152545 | 0.0339466 | 3.05771 | 11.2479 | 1.83756 | 0.00844572 | 0.000355419 | 5.85553e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2165.56 | 0.0381894 | 7009.01ms | 264040 | 2560 | 5.04807e+06 | 116279 | 0.7584 | 2.35701 | 9.03209 | 1.5642 | 0.00639373 | 3.3707e-05 | 1.72885e-05 | 1(Win) | true |
| simdjson (ondemand) | 1875.78 | 0.0802284 | 8023.7ms | 264040 | 640 | 7.42358e+06 | 134242 | 0.0391494 | 2.68788 | 9.81503 | 1.50842 | 0.0100853 | 3.71274e-05 | 1.26401e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2193.61 | 0.14379 | 8391.08ms | 360584 | 1280 | 6.50371e+07 | 156764 | 0.065436 | 2.32954 | 8.11955 | 1.40834 | 0.00981565 | 0.000306179 | 3.40203e-05 | 1(Win) | true |
| simdjson (ondemand) | 2112.74 | 0.111623 | 8776.02ms | 360584 | 1280 | 4.22508e+07 | 162764 | 0.124341 | 2.42276 | 8.60654 | 1.36762 | 0.00948939 | 0.00087238 | 0.00010119 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2815.43 | 0.042123 | 7400.79ms | 360584 | 1280 | 3.38824e+06 | 122141 | 0.138409 | 1.80789 | 7.05567 | 1.16304 | 0.00382446 | 3.18624e-05 | 1.02265e-05 | 1(Win) | true |
| simdjson (ondemand) | 2473 | 0.0656853 | 8267.13ms | 360584 | 1280 | 1.06785e+07 | 139054 | 0.0237037 | 2.04537 | 7.54354 | 1.12266 | 0.00751625 | 0.000432837 | 7.74135e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 698.675 | 0.262691 | 9305.71ms | 264040 | 320 | 2.86834e+08 | 360408 | 0.0760645 | 7.2677 | 27.0426 | 5.08452 | 0.0272219 | 0.00147323 | 0.000112317 | 1(Win) | true |
| simdjson (ondemand) | 279.235 | 0.108097 | 5718.63ms | 264040 | 320 | 3.04071e+08 | 901779 | 0.02279 | 18.0378 | 72.6752 | 12.7188 | 0.0868583 | 0.000759887 | 0.000123975 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 782.149 | 0.0628652 | 8863.93ms | 264040 | 640 | 2.62157e+07 | 321944 | 0.358037 | 6.54587 | 25.6219 | 4.75593 | 0.0187692 | 0.000224049 | 3.38194e-05 | 1(Win) | true |
| simdjson (ondemand) | 287.574 | 0.259894 | 5659.05ms | 264040 | 40 | 2.07154e+08 | 875628 | 0.00857648 | 17.5848 | 71.2519 | 12.3902 | 0.0856003 | 0.000170997 | 5.95554e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 880.387 | 0.0935507 | 5083.41ms | 360584 | 320 | 4.27277e+07 | 390600 | 0.0419458 | 5.77262 | 20.9283 | 3.89334 | 0.0220377 | 0.00259525 | 3.87306e-05 | 1(Win) | true |
| simdjson (ondemand) | 394.073 | 0.103989 | 5543.07ms | 360584 | 320 | 2.63504e+08 | 872628 | 0.0974958 | 12.7872 | 52.8689 | 9.19521 | 0.0529535 | 0.00363581 | 0.00029415 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 945.129 | 0.0847914 | 9780.47ms | 360584 | 320 | 3.04568e+07 | 363844 | 0.0901067 | 5.36721 | 19.8862 | 3.65239 | 0.0190122 | 0.000545946 | 4.81944e-05 | 1(Win) | true |
| simdjson (ondemand) | 407.621 | 0.190863 | 5499.87ms | 360584 | 40 | 1.03706e+08 | 843627 | 0.0657895 | 12.3478 | 51.8262 | 8.95449 | 0.0488811 | 0.00158756 | 0.00028544 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7080.69 | 0.0667241 | 4310.03ms | 264040 | 160 | 90089.5 | 35562.7 | 0.0955146 | 0.714155 | 3.43058 | 0.483173 | 0.00126018 | 3.00617e-06 | 2.08302e-06 | 1(Win) | true |
| simdjson (ondemand) | 6150.72 | 0.0603019 | 4912.24ms | 264040 | 1280 | 780116 | 40939.6 | 0.0385567 | 0.822487 | 3.88498 | 0.435078 | 0.00103316 | 5.00043e-06 | 2.44695e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7300.26 | 0.0836251 | 4314.03ms | 264040 | 80 | 66561.8 | 34493 | 0.144892 | 0.693006 | 3.34709 | 0.464407 | 0.00125322 | 2.51382e-05 | 2.18243e-05 | 1(Win) | true |
| simdjson (ondemand) | 6336.19 | 0.0703475 | 4793.56ms | 264040 | 160 | 125055 | 39741.3 | 0.0118251 | 0.798025 | 3.80157 | 0.41635 | 0.00100515 | 3.71629e-06 | 2.69845e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8084.73 | 0.0651378 | 5012.14ms | 360584 | 1280 | 982557 | 42534.4 | 0.0121137 | 0.624369 | 2.94062 | 0.377158 | 0.00091721 | 3.42977e-06 | 1.87413e-06 | 1(Win) | true |
| simdjson (ondemand) | 7498.44 | 0.0458812 | 5353.38ms | 360584 | 640 | 283349 | 45860.1 | 0.0252743 | 0.677605 | 3.19559 | 0.335345 | 0.000734702 | 7.77385e-06 | 4.94424e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8341.83 | 0.0355826 | 4973.26ms | 360584 | 2560 | 550815 | 41223.5 | 0.181013 | 0.607295 | 2.87949 | 0.363416 | 0.000865047 | 1.73406e-05 | 1.48934e-05 | 1(Win) | true |
| simdjson (ondemand) | 7704.65 | 0.137199 | 5275.81ms | 360584 | 80 | 299984 | 44632.8 | 0.0828553 | 0.658765 | 3.13452 | 0.321631 | 0.000711242 | 3.11994e-06 | 2.32262e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5079.98 | 0.0491901 | 5708.6ms | 264040 | 1280 | 760995 | 49568.8 | 0.102747 | 0.994428 | 5.17444 | 0.871853 | 0.00175063 | 4.58027e-06 | 2.78722e-06 | 1(Win) | true |
| simdjson (ondemand) | 3892.92 | 0.0576318 | 7257.28ms | 264040 | 640 | 889390 | 64683.6 | 0.00920502 | 1.30127 | 6.37663 | 0.935427 | 0.00185045 | 2.21557e-05 | 1.43918e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5211.46 | 0.0338058 | 5632.31ms | 264040 | 4890 | 1.30471e+06 | 48318.2 | 0.0298925 | 0.972116 | 5.09516 | 0.854428 | 0.00173973 | 1.08298e-05 | 8.50478e-06 | 1(Win) | true |
| simdjson (ondemand) | 3942.52 | 0.031156 | 7195.85ms | 264040 | 4890 | 1.93635e+06 | 63869.8 | 0.0244209 | 1.28059 | 6.29742 | 0.918039 | 0.00179925 | 1.38465e-05 | 1.13317e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5935.29 | 0.0625579 | 6597.64ms | 360584 | 1280 | 1.68153e+06 | 57938.2 | 0.157453 | 0.86064 | 4.3277 | 0.670188 | 0.00136649 | 3.24842e-05 | 2.93101e-05 | 1(Win) | true |
| simdjson (ondemand) | 4927.24 | 0.0650178 | 7701.8ms | 360584 | 640 | 1.3178e+06 | 69791.5 | 0.161953 | 1.03167 | 5.0322 | 0.703856 | 0.00136889 | 3.00121e-05 | 2.27669e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6029.24 | 0.049068 | 6512.54ms | 360584 | 2560 | 2.00505e+06 | 57035.3 | 0.386063 | 0.839995 | 4.26965 | 0.657428 | 0.00136069 | 1.35739e-05 | 9.67289e-06 | 1(Win) | true |
| simdjson (ondemand) | 5022.74 | 0.0518569 | 7628.33ms | 360584 | 1280 | 1.61345e+06 | 68464.6 | 0.163776 | 1.01046 | 4.97426 | 0.691143 | 0.00136325 | 5.0504e-06 | 3.48393e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1879.95 | 0.105818 | 854.912ms | 2632 | 2560 | 5110.19 | 1335.18 | 0.165317 | 2.82256 | 11.095 | 2.03761 | 0.000623931 | 0.000136095 | 6.2779e-05 | 1(Win) | true |
| simdjson (ondemand) | 1609.29 | 0.082708 | 873.909ms | 2632 | 320 | 532.538 | 1559.74 | 0.308591 | 3.28551 | 12.136 | 2.1174 | 0.00246486 | 3.91812e-05 | 2.37462e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2415.79 | 0.105299 | 834.088ms | 2632 | 160 | 191.521 | 1039.03 | 0.0397164 | 2.21604 | 9.07029 | 1.57105 | 0.000764628 | 4.74924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1903.48 | 0.0571929 | 857.612ms | 2632 | 4890 | 2781.42 | 1318.67 | 0.149103 | 2.78069 | 10.3986 | 1.71847 | 0.00225229 | 4.55305e-05 | 1.07222e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2349.38 | 0.0864938 | 855.373ms | 3370 | 320 | 447.996 | 1367.97 | 0.0655194 | 2.24184 | 8.89466 | 1.5724 | 0.000526706 | 3.98739e-05 | 3.7092e-06 | 1(Win) | true |
| simdjson (ondemand) | 1996.18 | 0.129188 | 877.785ms | 3370 | 1280 | 5537.57 | 1610.02 | 0.102199 | 2.64159 | 9.75727 | 1.66469 | 0.00186202 | 0.000107103 | 5.54062e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2971.69 | 0.113942 | 836.686ms | 3370 | 1280 | 1943.71 | 1081.5 | 0.00101132 | 1.79828 | 7.42967 | 1.23264 | 0.00063265 | 8.97162e-05 | 4.42786e-05 | 1(Win) | true |
| simdjson (ondemand) | 2372.96 | 0.0707018 | 863.013ms | 3370 | 320 | 293.421 | 1354.38 | 0.0380565 | 2.23675 | 8.4003 | 1.35312 | 0.0015523 | 4.45104e-05 | 9.273e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1296.42 | 0.128457 | 917.919ms | 2632 | 1280 | 7917.89 | 1936.16 | 0.448653 | 4.04789 | 16.0057 | 3.19567 | 0.00486174 | 0.00011042 | 5.22416e-05 | 1(Win) | true |
| simdjson (ondemand) | 713.136 | 0.100508 | 1072.62ms | 2632 | 80 | 1001.2 | 3519.76 | 0.0500995 | 7.30927 | 30.8518 | 5.89438 | 0.0136683 | 0.000128229 | 3.32447e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1530.36 | 0.133334 | 892.997ms | 2632 | 1280 | 6121.82 | 1640.19 | 0.0919874 | 3.44356 | 14.1284 | 2.7595 | 0.0045655 | 4.63051e-05 | 1.12794e-05 | 1(Win) | true |
| simdjson (ondemand) | 775.414 | 0.0622005 | 1052.1ms | 2632 | 2560 | 10378.4 | 3237.07 | 0.122549 | 6.71759 | 29.1128 | 5.4943 | 0.0112306 | 0.000132385 | 7.59878e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1595.2 | 0.115371 | 920.715ms | 3370 | 1280 | 6915.64 | 2014.72 | 0.121092 | 3.2921 | 13.278 | 2.59881 | 0.00330513 | 8.27615e-05 | 3.61647e-05 | 1(Win) | true |
| simdjson (ondemand) | 921.814 | 0.0700485 | 1071.07ms | 3370 | 160 | 954.314 | 3486.47 | 0.0459127 | 5.65552 | 24.0774 | 4.55935 | 0.00995734 | 2.59644e-05 | 3.7092e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1814.01 | 0.0478067 | 905.763ms | 3370 | 4890 | 3508.04 | 1771.7 | 0.0847354 | 2.89658 | 11.8119 | 2.25816 | 0.00355598 | 4.10818e-05 | 5.21867e-06 | 1(Win) | true |
| simdjson (ondemand) | 998.313 | 0.0413042 | 1048.59ms | 3370 | 4890 | 8646.15 | 3219.31 | 0.00258466 | 5.21265 | 22.719 | 4.24689 | 0.00854254 | 3.68341e-05 | 1.08621e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3190.28 | 0.199374 | 794.23ms | 2632 | 80 | 196.853 | 786.788 | 0.160721 | 1.69469 | 6.7728 | 1.19301 | 0.000569909 | 1.8997e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2433.31 | 0.115436 | 820.704ms | 2632 | 2560 | 3629.91 | 1031.55 | 0.12749 | 2.1886 | 8.23176 | 1.34726 | 0.00226242 | 2.18168e-05 | 5.19448e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4040 | 0.0790278 | 780.838ms | 2632 | 4890 | 1178.9 | 621.304 | 0.0407542 | 1.35635 | 5.70555 | 0.93997 | 0.000763763 | 2.9758e-05 | 7.84742e-06 | 1(Win) | true |
| simdjson (ondemand) | 2967.38 | 0.0946322 | 808.31ms | 2632 | 320 | 205.047 | 845.888 | 0.0931842 | 1.81529 | 7.16489 | 1.09422 | 0.000761066 | 3.20574e-05 | 1.18731e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3852.42 | 0.110903 | 803.153ms | 3370 | 1280 | 1095.7 | 834.251 | 0.375885 | 1.4022 | 5.67211 | 0.950149 | 0.00111392 | 1.11276e-05 | 3.7092e-06 | 1(Win) | true |
| simdjson (ondemand) | 3076.85 | 0.130009 | 824.806ms | 3370 | 1280 | 2360.49 | 1044.54 | 0.216923 | 1.73589 | 6.50267 | 1.02789 | 0.00186364 | 1.57641e-05 | 2.31825e-07 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4888.03 | 0.294388 | 788.137ms | 3370 | 30 | 112.397 | 657.5 | 0.126582 | 1.13177 | 4.83858 | 0.752522 | 0.000593472 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3760.28 | 0.102183 | 805.408ms | 3370 | 1280 | 976.314 | 854.691 | 0.0212934 | 1.43526 | 5.66944 | 0.830267 | 0.000594167 | 3.89466e-05 | 2.99054e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2334.52 | 0.0933876 | 828.348ms | 2632 | 4890 | 4930.2 | 1075.2 | 0.0280064 | 2.28783 | 9.1117 | 1.731 | 0.00254761 | 5.99822e-05 | 3.10789e-05 | 1(Win) | true |
| simdjson (ondemand) | 2011.08 | 0.046418 | 847.684ms | 2632 | 4890 | 1641.32 | 1248.12 | 0.478169 | 2.62797 | 10.1364 | 1.71315 | 0.00408951 | 2.74271e-05 | 9.09057e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2815.4 | 0.182676 | 814.698ms | 2632 | 40 | 106.1 | 891.55 | 0.403544 | 1.87979 | 8.04749 | 1.48062 | 0.00113982 | 1.8997e-05 | 1.8997e-05 | 1(Win) | true |
| simdjson (ondemand) | 2408.21 | 0.107152 | 826.13ms | 2632 | 1280 | 1596.61 | 1042.3 | 0.166752 | 2.2048 | 9.07257 | 1.46277 | 0.00114219 | 2.34494e-05 | 7.12386e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2904.12 | 0.0825949 | 835.399ms | 3370 | 2560 | 2138.83 | 1106.66 | 0.00183544 | 1.81681 | 7.58279 | 1.38902 | 0.00121105 | 3.33828e-05 | 8.46161e-06 | 1(Win) | true |
| simdjson (ondemand) | 2592.39 | 0.0361685 | 847.765ms | 3370 | 1280 | 257.353 | 1239.74 | 0.153683 | 2.05148 | 7.98071 | 1.31365 | 0.00321796 | 1.3214e-05 | 3.01372e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3495.56 | 0.0401979 | 816.207ms | 3370 | 1280 | 174.841 | 919.418 | 0.113479 | 1.53892 | 6.75163 | 1.19347 | 0.000967637 | 1.62277e-05 | 6.95475e-07 | 1(Win) | true |
| simdjson (ondemand) | 3097.39 | 0.0781554 | 827.711ms | 3370 | 2560 | 1683.55 | 1037.61 | 0.130314 | 1.72024 | 7.14985 | 1.1181 | 0.000891946 | 1.44891e-05 | 3.24555e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 764.212 | 0.0306912 | 1305.39ms | 4630 | 4890 | 15377 | 5777.86 | 0.241235 | 6.72212 | 31.9933 | 6.25465 | 0.00275451 | 0.000115367 | 5.1986e-05 | 1(Win) | true |
| simdjson (ondemand) | 759.67 | 0.065059 | 1297.01ms | 4630 | 640 | 9151.8 | 5812.41 | 0.0789979 | 6.76536 | 32.3782 | 5.6784 | 0.00320161 | 0.000127565 | 4.72462e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 933.194 | 0.21782 | 1284.65ms | 4630 | 320 | 33991.1 | 4731.61 | 0.0117547 | 5.55452 | 27.4695 | 4.60821 | 0.00368723 | 4.58963e-05 | 1.61987e-05 | 1(Win) | true |
| Jsonifier (generic) | 924.276 | 0.0733116 | 1292.38ms | 4630 | 1280 | 15700.5 | 4777.26 | 0.187681 | 5.61442 | 27.6294 | 5.29482 | 0.00219543 | 5.11272e-05 | 1.29927e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1833.72 | 0.127918 | 1322.35ms | 11579 | 30 | 1780.17 | 6021.97 | 0.208246 | 2.83304 | 13.6276 | 2.32516 | 0.00265999 | 1.72726e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 1779.29 | 0.0573103 | 1344.77ms | 11579 | 160 | 2024.12 | 6206.19 | 0.0504282 | 2.91478 | 13.7778 | 2.62363 | 0.00222763 | 1.4034e-05 | 2.69885e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2187.06 | 0.0780813 | 1319.44ms | 11579 | 40 | 621.69 | 5049.05 | 0.0128754 | 2.37451 | 11.6825 | 1.8708 | 0.00138613 | 8.63632e-06 | 0 | 1(Win) | true |
| Jsonifier (generic) | 2086.54 | 0.0284879 | 1346.13ms | 11579 | 4890 | 11115.3 | 5292.31 | 0.0924873 | 2.48531 | 11.8656 | 2.17782 | 0.00181739 | 1.87739e-05 | 6.83488e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 711.98 | 0.0370969 | 1345.05ms | 4630 | 4890 | 25882.8 | 6201.74 | 0.251415 | 7.22833 | 35.1838 | 6.92894 | 0.00330524 | 0.000115897 | 4.21807e-05 | 1(Win) | true |
| simdjson (ondemand) | 684.528 | 0.131286 | 1362.92ms | 4630 | 40 | 2868.66 | 6450.45 | 0.00387585 | 7.57374 | 36.7164 | 6.63888 | 0.00451944 | 4.85961e-05 | 0 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 837.761 | 0.0625853 | 1350.07ms | 4630 | 640 | 6963.8 | 5270.61 | 0.0211031 | 6.18182 | 30.9881 | 6.00648 | 0.00280879 | 2.32856e-05 | 3.37473e-07 | 1(Win) | true |
| simdjson (ondemand) | 808.185 | 0.0304577 | 1366.54ms | 4630 | 4890 | 13540.8 | 5463.49 | 0.187013 | 6.33309 | 31.9471 | 5.6013 | 0.00336995 | 7.78244e-05 | 4.01048e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1646.9 | 0.0304082 | 1398.73ms | 11579 | 4890 | 20328.2 | 6705.08 | 0.0291951 | 3.14428 | 14.8526 | 2.82313 | 0.00159228 | 2.97591e-05 | 1.14091e-05 | 1(Win) | true |
| simdjson (ondemand) | 1642.15 | 0.0868707 | 1402.57ms | 11579 | 4890 | 166868 | 6724.49 | 0.857353 | 3.1384 | 15.412 | 2.68909 | 0.00165491 | 6.48342e-05 | 3.09071e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1938.79 | 0.0350614 | 1386.76ms | 11579 | 4890 | 19500.6 | 5695.61 | 0.0814693 | 2.67504 | 13.4813 | 2.27067 | 0.00147651 | 1.08616e-05 | 1.92507e-06 | 1(Win) | true |
| Jsonifier (generic) | 1902.13 | 0.0397992 | 1399.52ms | 11579 | 2560 | 13666.3 | 5805.38 | 0.0618343 | 2.72067 | 13.1449 | 2.44788 | 0.00183454 | 1.3528e-05 | 4.25069e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6975.44 | 0.125958 | 778.478ms | 4630 | 4890 | 3108.7 | 633.009 | 0.1018 | 0.784614 | 3.65594 | 0.505184 | 0.000433025 | 1.70489e-05 | 5.47686e-06 | 1(Win) | true |
| simdjson (ondemand) | 6598.44 | 0.0730862 | 781.824ms | 4630 | 160 | 38.2711 | 669.175 | 0.0766455 | 0.828588 | 4.10583 | 0.493089 | 0.000431965 | 2.69978e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6805.73 | 0.221497 | 780.77ms | 4630 | 4890 | 10098.5 | 648.793 | 1.1959 | 0.801199 | 3.61641 | 0.49676 | 0.000446232 | 2.01849e-05 | 8.65698e-06 | 1(Win) | true |
| simdjson (ondemand) | 6748.13 | 0.102437 | 782.511ms | 4630 | 160 | 71.8833 | 654.331 | 0.0296192 | 0.811258 | 4.0689 | 0.485097 | 0.000431965 | 5.39957e-06 | 1.34989e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11665.3 | 0.0852892 | 811.324ms | 11579 | 320 | 208.588 | 946.619 | 0.26878 | 0.461081 | 2.09111 | 0.225754 | 0.000172726 | 5.3977e-06 | 1.07954e-06 | 1(Win) | true |
| simdjson (ondemand) | 10956.3 | 0.0425809 | 816.061ms | 11579 | 2560 | 471.497 | 1007.87 | 0.107163 | 0.487649 | 2.36894 | 0.23154 | 0.000174953 | 8.97368e-06 | 2.69885e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11760.4 | 0.0530607 | 809.949ms | 11579 | 1280 | 317.725 | 938.961 | 0.007155 | 0.458198 | 2.07531 | 0.222385 | 0.000172794 | 1.65979e-05 | 7.2869e-06 | 1(Win) | true |
| simdjson (ondemand) | 11205.8 | 0.0414877 | 813.286ms | 11579 | 1280 | 213.948 | 985.438 | 0.128347 | 0.479205 | 2.35418 | 0.228344 | 0.000174886 | 1.55184e-05 | 6.67966e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5039.72 | 0.11562 | 801.637ms | 4630 | 1280 | 1313.48 | 876.142 | 0.109977 | 1.07035 | 5.16436 | 0.840605 | 0.000647948 | 3.10475e-05 | 1.58612e-05 | 1(Win) | true |
| simdjson (ondemand) | 4649.52 | 0.0689493 | 811.559ms | 4630 | 4890 | 2096.6 | 949.671 | 0.00334366 | 1.15413 | 5.59114 | 0.820086 | 0.000648257 | 1.66073e-05 | 4.19598e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5171.29 | 0.264126 | 799.862ms | 4630 | 640 | 3255.13 | 853.852 | 0.342668 | 1.04231 | 5.12484 | 0.832182 | 0.000648286 | 1.11366e-05 | 1.34989e-06 | 1(Win) | true |
| simdjson (ondemand) | 4739.74 | 0.22673 | 809.735ms | 4630 | 320 | 1427.65 | 931.594 | 0.120234 | 1.13379 | 5.55421 | 0.812095 | 0.000647948 | 1.2149e-05 | 1.34989e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10181.3 | 0.0426365 | 829.043ms | 11579 | 40 | 8.55385 | 1084.6 | 0.0737055 | 0.527021 | 2.69635 | 0.36048 | 0.000263408 | 2.15908e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 8505.17 | 0.105275 | 847.1ms | 11579 | 2560 | 4782.63 | 1298.34 | 0.101079 | 0.619411 | 2.96286 | 0.362294 | 0.000259967 | 6.44351e-06 | 1.07954e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10299.3 | 0.0669445 | 828.815ms | 11579 | 2560 | 1318.85 | 1072.17 | 0.0352068 | 0.519113 | 2.68054 | 0.357112 | 0.000280141 | 6.30857e-06 | 1.72052e-06 | 1(Win) | true |
| simdjson (ondemand) | 8660.37 | 0.0503068 | 850.299ms | 11579 | 4890 | 2012.02 | 1275.07 | 0.0375818 | 0.612739 | 2.9481 | 0.359098 | 0.000259178 | 8.53036e-06 | 1.23628e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1161.27 | 0.0753552 | 1153.34ms | 5092 | 640 | 6355.05 | 4181.74 | 0.0635919 | 4.47616 | 18.541 | 3.38119 | 0.00294825 | 5.0324e-05 | 1.4729e-05 | 1(Win) | true |
| simdjson (ondemand) | 1125.77 | 0.119746 | 1161.49ms | 5092 | 320 | 8537.92 | 4313.59 | 0.0987903 | 4.57903 | 18.6974 | 3.14022 | 0.00250086 | 3.55951e-05 | 9.81932e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1326.49 | 0.114311 | 1147.17ms | 5092 | 640 | 11207.9 | 3660.87 | 0.0605157 | 3.92283 | 16.7818 | 2.96131 | 0.00308357 | 2.76168e-05 | 3.06854e-07 | 1(Win) | true |
| simdjson (ondemand) | 1239.17 | 0.0726951 | 1258.86ms | 5092 | 4890 | 39685.6 | 3918.83 | 0.0823224 | 4.15991 | 17.063 | 2.74313 | 0.00514982 | 4.80324e-05 | 1.2731e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2054.21 | 0.0528048 | 1181.75ms | 9739 | 2560 | 14592.3 | 4521.36 | 0.0692153 | 2.50581 | 10.4031 | 1.80635 | 0.00145324 | 2.95205e-05 | 5.37465e-06 | 1(Win) | true |
| simdjson (ondemand) | 2050.78 | 0.0446026 | 1177.54ms | 9739 | 2560 | 10446 | 4528.93 | 0.0081255 | 2.53254 | 10.3751 | 1.67194 | 0.00165904 | 4.49225e-05 | 2.06162e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.05 | 0.194657 | 1171.71ms | 9739 | 320 | 19600.8 | 4020.62 | 0.00365318 | 2.24812 | 9.53507 | 1.59657 | 0.00169679 | 6.44958e-05 | 3.27292e-05 | 1(Win) | true |
| simdjson (ondemand) | 2281.08 | 0.093525 | 1192.96ms | 9739 | 1280 | 18561.5 | 4071.69 | 0.178126 | 2.2797 | 9.50857 | 1.46134 | 0.00242108 | 4.98158e-05 | 2.41458e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 710.369 | 0.0542571 | 1409.47ms | 5092 | 1280 | 17608.9 | 6836.04 | 0.261156 | 7.23815 | 31.6599 | 6.48429 | 0.00597153 | 0.000165701 | 7.28778e-05 | 1(Win) | true |
| simdjson (ondemand) | 441.983 | 0.0334146 | 1831.2ms | 5092 | 1280 | 17252.3 | 10987.1 | 0.00209759 | 11.6895 | 56.1084 | 10.9411 | 0.0137701 | 4.06581e-05 | 7.82477e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 769.506 | 0.0632689 | 1398.72ms | 5092 | 640 | 10202.7 | 6310.68 | 0.101295 | 6.7334 | 29.9768 | 6.07973 | 0.00647247 | 3.31402e-05 | 6.13708e-06 | 1(Win) | true |
| simdjson (ondemand) | 461.446 | 0.0467503 | 1817.1ms | 5092 | 1280 | 30982.3 | 10523.7 | 0.0813336 | 11.1378 | 54.4509 | 10.5414 | 0.0141983 | 8.86808e-05 | 4.11184e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1234.02 | 0.072095 | 1484.27ms | 9739 | 640 | 18844.1 | 7526.49 | 0.00965247 | 4.19381 | 17.6537 | 3.52993 | 0.00395607 | 2.77557e-05 | 6.89881e-06 | 1(Win) | true |
| simdjson (ondemand) | 829.489 | 0.108424 | 1854.64ms | 9739 | 40 | 5895.48 | 11197 | 0.403679 | 6.23369 | 29.8189 | 5.72749 | 0.00762655 | 2.8237e-05 | 2.567e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1327.2 | 0.0369703 | 1478.49ms | 9739 | 2560 | 17135.8 | 6998.09 | 0.128792 | 3.90489 | 16.7737 | 3.31841 | 0.00390934 | 3.65797e-05 | 1.47602e-05 | 1(Win) | true |
| simdjson (ondemand) | 866.931 | 0.135216 | 1842.43ms | 9739 | 80 | 16788.4 | 10713.5 | 0.324817 | 5.96091 | 28.9526 | 5.51792 | 0.00786272 | 2.69535e-05 | 5.134e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5108.47 | 0.229734 | 811.531ms | 5092 | 30 | 143.076 | 950.6 | 0.122579 | 1.03342 | 4.64513 | 0.716025 | 0.00125687 | 1.30924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4431.2 | 0.0840859 | 832.597ms | 5092 | 1280 | 1086.9 | 1095.89 | 0.156725 | 1.20526 | 5.2936 | 0.663002 | 0.00142181 | 1.91784e-05 | 7.05764e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5441.51 | 0.0729902 | 808.784ms | 5092 | 320 | 135.774 | 892.419 | 0.191527 | 0.98987 | 4.52003 | 0.689513 | 0.00141582 | 8.59191e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4467.72 | 0.206192 | 832.447ms | 5092 | 30 | 150.685 | 1086.93 | 0.0767271 | 1.17524 | 5.17145 | 0.637471 | 0.0018133 | 1.30924e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7605.61 | 0.107648 | 843.581ms | 9739 | 2560 | 4423.98 | 1221.18 | 0.00729367 | 0.700197 | 3.0192 | 0.405381 | 0.00072241 | 2.03756e-05 | 7.46034e-06 | 1(Win) | true |
| simdjson (ondemand) | 7066.03 | 0.0443109 | 849.321ms | 9739 | 640 | 217.11 | 1314.43 | 0.191256 | 0.751957 | 3.34726 | 0.372934 | 0.000576612 | 1.29954e-05 | 4.81312e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7739.43 | 0.128717 | 836.077ms | 9739 | 30 | 71.5816 | 1200.07 | 0.0250049 | 0.678865 | 2.95379 | 0.391519 | 0.000554472 | 1.36907e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7202.61 | 0.0527972 | 852.333ms | 9739 | 4890 | 2266.62 | 1289.51 | 0.149134 | 0.737485 | 3.2834 | 0.359585 | 0.000952803 | 8.10521e-06 | 2.30977e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3240.92 | 0.0956362 | 880.455ms | 5092 | 4890 | 10041.4 | 1498.37 | 0.262683 | 1.62968 | 7.87196 | 1.40475 | 0.00275503 | 1.90764e-05 | 4.17673e-06 | 1(Win) | true |
| simdjson (ondemand) | 2985.14 | 0.0746271 | 878.317ms | 5092 | 80 | 117.905 | 1626.76 | 0.00537849 | 1.77018 | 8.33189 | 1.30577 | 0.00197614 | 4.90966e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3309.3 | 0.0501174 | 865.574ms | 5092 | 2560 | 1384.59 | 1467.41 | 0.291404 | 1.60438 | 7.74686 | 1.37824 | 0.00303026 | 1.66468e-05 | 5.29323e-06 | 1(Win) | true |
| simdjson (ondemand) | 3041.17 | 0.0891613 | 881.452ms | 5092 | 1280 | 2594.52 | 1596.79 | 0.0289238 | 1.74 | 8.20974 | 1.28024 | 0.00249871 | 1.08933e-05 | 3.83567e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5195.72 | 0.112403 | 903.223ms | 9739 | 640 | 2583.88 | 1787.59 | 0.238053 | 1.0015 | 4.65736 | 0.772256 | 0.00139356 | 1.01076e-05 | 9.62624e-07 | 1(Win) | true |
| simdjson (ondemand) | 5006.05 | 0.0300531 | 905.526ms | 9739 | 1280 | 397.949 | 1855.32 | 0.020806 | 1.05181 | 4.9616 | 0.714139 | 0.000854971 | 2.08569e-05 | 9.46581e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5330.43 | 0.0682474 | 897.147ms | 9739 | 4890 | 6914.89 | 1742.42 | 0.0497109 | 0.986873 | 4.59195 | 0.758394 | 0.00171488 | 1.59584e-05 | 5.43847e-06 | 1(Win) | true |
| simdjson (ondemand) | 5149.8 | 0.0716798 | 905.303ms | 9739 | 320 | 534.801 | 1803.53 | 0.17305 | 1.02112 | 4.87175 | 0.695657 | 0.00114584 | 9.62624e-06 | 2.88787e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.27 | 0.0464394 | 1054.17ms | 4857 | 2560 | 5782.39 | 3236.29 | 0.338529 | 3.6052 | 14.5209 | 2.71032 | 0.00112989 | 9.49017e-05 | 4.37513e-05 | 1(Win) | true |
| simdjson (ondemand) | 1348.79 | 0.0378121 | 1076.38ms | 4857 | 4890 | 8245.55 | 3434.2 | 0.0860827 | 3.85325 | 15.3667 | 2.58122 | 0.00109512 | 6.53875e-05 | 2.5515e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1884.4 | 0.0441123 | 995.326ms | 4857 | 4890 | 5749.36 | 2458.08 | 0.115175 | 2.76833 | 11.5722 | 2.06713 | 0.00194428 | 4.23566e-05 | 8.42079e-06 | 1(Win) | true |
| simdjson (ondemand) | 1639.69 | 0.0710101 | 1038.98ms | 4857 | 4890 | 19677 | 2824.92 | 0.102955 | 3.16061 | 13.0568 | 2.08153 | 0.000610844 | 6.21455e-05 | 2.13888e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1901.06 | 0.0471476 | 1073.72ms | 6701 | 2560 | 6430.53 | 3361.59 | 0.0366056 | 2.72746 | 10.9357 | 1.97389 | 0.00100865 | 6.36565e-05 | 2.82724e-05 | 1(Win) | true |
| simdjson (ondemand) | 1786.02 | 0.0455259 | 1090.4ms | 6701 | 2560 | 6793.05 | 3578.11 | 0.404503 | 2.89502 | 11.5026 | 1.88554 | 0.000463084 | 5.17647e-05 | 1.98198e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2458.01 | 0.0352603 | 1047.85ms | 6701 | 4890 | 4109.53 | 2599.89 | 0.0819858 | 2.11823 | 8.81107 | 1.51022 | 0.00157526 | 4.58681e-05 | 1.48316e-05 | 1(Win) | true |
| simdjson (ondemand) | 2179.42 | 0.0836864 | 1043.78ms | 6701 | 2560 | 15415.1 | 2932.23 | 0.041733 | 2.3694 | 9.82883 | 1.5235 | 0.000861637 | 3.00795e-05 | 1.0318e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.59 | 0.0647023 | 1346.76ms | 4857 | 1280 | 20084.6 | 6122.2 | 0.10801 | 6.88766 | 29.6146 | 5.97241 | 0.0056941 | 7.86558e-05 | 3.86041e-05 | 1(Win) | true |
| simdjson (ondemand) | 219.432 | 0.0284344 | 2833.86ms | 4857 | 4890 | 176170 | 21109 | 0.704103 | 23.1706 | 115.717 | 22.2961 | 0.0425222 | 0.000216667 | 0.000134775 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 858.488 | 0.0496906 | 1293.2ms | 4857 | 320 | 2300.21 | 5395.53 | 0.0222357 | 6.0471 | 26.6689 | 5.33189 | 0.00660451 | 2.38058e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 228.096 | 0.0323134 | 2794.15ms | 4857 | 2560 | 110232 | 20307.2 | 0.108166 | 22.3629 | 113.403 | 21.7976 | 0.0430528 | 0.000132139 | 7.86558e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 916.158 | 0.0774897 | 1417.88ms | 6701 | 640 | 18698.5 | 6975.4 | 0.0382292 | 5.58969 | 23.4323 | 4.57947 | 0.00574844 | 4.43031e-05 | 1.58558e-05 | 1(Win) | true |
| simdjson (ondemand) | 300.855 | 0.0980015 | 2840.57ms | 6701 | 320 | 138670 | 21241.4 | 0.0432715 | 16.9201 | 83.9324 | 16.1173 | 0.0314323 | 0.000112856 | 6.66878e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1057.38 | 0.032349 | 1361.51ms | 6701 | 320 | 1223.17 | 6043.77 | 0.0293605 | 4.90691 | 21.3138 | 4.11909 | 0.00573422 | 1.53895e-05 | 1.86539e-06 | 1(Win) | true |
| simdjson (ondemand) | 313.837 | 0.0269686 | 2790.98ms | 6701 | 4890 | 147468 | 20362.7 | 0.0593821 | 16.3763 | 82.2553 | 15.7562 | 0.0318694 | 0.000129395 | 7.92544e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4122.41 | 0.064717 | 828.993ms | 4857 | 4890 | 2585.71 | 1123.61 | 0.0897272 | 1.29393 | 5.47272 | 0.868643 | 0.000248919 | 6.4377e-05 | 3.42305e-05 | 1(Win) | true |
| simdjson (ondemand) | 3678.2 | 0.0901068 | 845.467ms | 4857 | 2560 | 3296.26 | 1259.31 | 0.0595519 | 1.44386 | 6.01379 | 0.829731 | 0.000281568 | 5.57346e-05 | 3.20896e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4749.33 | 0.134978 | 817.797ms | 4857 | 1280 | 2218.24 | 975.294 | 0.151144 | 1.13049 | 4.89994 | 0.738522 | 0.000434778 | 2.26799e-05 | 6.27316e-06 | 1(Win) | true |
| simdjson (ondemand) | 4141.12 | 0.145845 | 835.234ms | 4857 | 160 | 425.797 | 1118.54 | 0.054729 | 1.29004 | 5.44328 | 0.700844 | 0.000976683 | 1.80152e-05 | 6.43401e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5166.95 | 0.0668535 | 842.993ms | 6701 | 4890 | 3343.24 | 1236.82 | 0.0279921 | 1.02972 | 4.40695 | 0.658111 | 0.00020395 | 2.80152e-05 | 1.05896e-05 | 1(Win) | true |
| simdjson (ondemand) | 4759.33 | 0.0815094 | 857.797ms | 6701 | 1280 | 1533.25 | 1342.75 | 0.202763 | 1.11516 | 4.73123 | 0.617072 | 0.000250312 | 1.469e-05 | 2.6815e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5827.2 | 0.0703476 | 832.615ms | 6701 | 4890 | 2910.49 | 1096.68 | 0.0683015 | 0.915423 | 3.99179 | 0.563797 | 0.000427522 | 3.51259e-05 | 1.82191e-05 | 1(Win) | true |
| simdjson (ondemand) | 5400.01 | 0.130091 | 841.315ms | 6701 | 80 | 189.616 | 1183.44 | 0.133963 | 1.00457 | 4.31771 | 0.523653 | 0.000693926 | 2.23847e-05 | 5.59618e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3050.44 | 0.171349 | 870.379ms | 4857 | 1280 | 8665.3 | 1518.47 | 0.0514748 | 1.73044 | 7.25633 | 1.28804 | 0.00188066 | 5.30806e-05 | 2.17148e-05 | 1(Win) | true |
| simdjson (ondemand) | 2118.7 | 0.183646 | 940.887ms | 4857 | 160 | 2579.17 | 2186.24 | 0.211137 | 2.47669 | 10.666 | 1.65061 | 0.00222231 | 5.79061e-05 | 3.86041e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3428.18 | 0.186806 | 859.716ms | 4857 | 1280 | 8154.56 | 1351.15 | 0.0589426 | 1.54548 | 6.70084 | 1.16574 | 0.00145151 | 3.02399e-05 | 1.44765e-05 | 1(Win) | true |
| simdjson (ondemand) | 2282.02 | 0.206601 | 927.36ms | 4857 | 80 | 1406.86 | 2029.78 | 0.0184784 | 2.30365 | 10.1128 | 1.52954 | 0.00251184 | 5.14721e-05 | 3.60305e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3836.45 | 0.0614912 | 887.306ms | 6701 | 4890 | 5130.44 | 1665.75 | 0.126315 | 1.37317 | 5.8157 | 0.984331 | 0.000674685 | 2.19727e-05 | 7.53787e-06 | 1(Win) | true |
| simdjson (ondemand) | 2880.36 | 0.0889618 | 941.293ms | 6701 | 1280 | 4986.56 | 2218.67 | 0.0622593 | 1.82073 | 8.0191 | 1.19654 | 0.00145186 | 4.59353e-05 | 2.83307e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4216.88 | 0.0463555 | 876.028ms | 6701 | 4890 | 2413.29 | 1515.48 | 0.057712 | 1.25327 | 5.41307 | 0.895687 | 0.000941043 | 2.05994e-05 | 7.35476e-06 | 1(Win) | true |
| simdjson (ondemand) | 3025.25 | 0.0679909 | 934.922ms | 6701 | 4890 | 10087.2 | 2112.41 | 0.448704 | 1.7224 | 7.61812 | 1.10879 | 0.00221845 | 1.23291e-05 | 3.78419e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1272.7 | 0.100292 | 851.035ms | 1691 | 160 | 258.395 | 1267.12 | 0.107149 | 4.17987 | 14.5405 | 2.83619 | 0.000887049 | 0.000136753 | 5.54406e-05 | 1(Win) | true |
| simdjson (ondemand) | 1215.27 | 0.167183 | 852.801ms | 1691 | 40 | 196.872 | 1327 | 0.105613 | 4.4479 | 16.7451 | 2.89651 | 0.00147842 | 0.00017741 | 0 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1474.25 | 0.159105 | 842.046ms | 1691 | 80 | 242.329 | 1093.89 | 0.172848 | 3.62364 | 12.9426 | 2.44471 | 0.000901833 | 0.000118273 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1360.74 | 0.062427 | 845.362ms | 1691 | 2560 | 1401.27 | 1185.14 | 0.134692 | 3.91312 | 15.1467 | 2.50503 | 0.00139502 | 9.4249e-05 | 3.14163e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.1 | 0.0838481 | 858.875ms | 2158 | 4890 | 6276.85 | 1351.21 | 0.0589749 | 3.47893 | 12.1209 | 2.32577 | 0.000468794 | 0.000163751 | 4.74764e-05 | 1(Win) | true |
| simdjson (ondemand) | 1502.24 | 0.112281 | 860.341ms | 2158 | 80 | 189.291 | 1369.97 | 0.0748749 | 3.53145 | 13.3346 | 2.27016 | 0.000926784 | 6.95088e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1764.25 | 0.0563386 | 843.015ms | 2158 | 640 | 276.422 | 1166.52 | 0.0465915 | 3.02345 | 10.8689 | 2.019 | 0.000472805 | 6.51645e-05 | 1.52051e-05 | 1(Win) | true |
| simdjson (ondemand) | 1727.84 | 0.0364491 | 849.766ms | 2158 | 1280 | 241.257 | 1191.1 | 0.11282 | 3.08411 | 12.082 | 1.96339 | 0.000463392 | 7.63873e-05 | 1.66532e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 944.709 | 0.092556 | 899.923ms | 1691 | 640 | 1597.64 | 1707.05 | 0.122686 | 5.57987 | 19.8386 | 4.08161 | 0.00152092 | 9.6097e-05 | 1.66322e-05 | 1(Win) | true |
| simdjson (ondemand) | 686.459 | 0.115067 | 964.128ms | 1691 | 4890 | 35733 | 2349.25 | 7.0863e-05 | 7.62716 | 30.1396 | 5.39503 | 0.00295792 | 0.00010485 | 3.20474e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1061.55 | 0.130409 | 889.278ms | 1691 | 640 | 2511.9 | 1519.15 | 0.115225 | 4.96355 | 18.3903 | 3.71851 | 0.000926781 | 6.37567e-05 | 1.84802e-06 | 1(Win) | true |
| simdjson (ondemand) | 736.847 | 0.0989452 | 947.126ms | 1691 | 640 | 3001.25 | 2188.6 | 0.244421 | 7.11656 | 28.5411 | 5.00237 | 0.00357961 | 7.39208e-05 | 4.62005e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1085.83 | 0.0690521 | 909.162ms | 2158 | 1280 | 2192.52 | 1895.35 | 0.00177246 | 4.84382 | 16.9768 | 3.48703 | 0.0011802 | 0.000129967 | 4.99595e-05 | 1(Win) | true |
| simdjson (ondemand) | 882.617 | 0.0758625 | 955.278ms | 2158 | 640 | 2002.59 | 2331.73 | 0.0406247 | 5.93584 | 23.6603 | 4.19463 | 0.000949954 | 4.70633e-05 | 7.2405e-07 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1195.06 | 0.176317 | 900.867ms | 2158 | 80 | 737.569 | 1722.11 | 0.0980862 | 4.41355 | 15.7247 | 3.17933 | 0.00185357 | 9.26784e-05 | 2.8962e-05 | 1(Win) | true |
| simdjson (ondemand) | 944.494 | 0.153455 | 957.826ms | 2158 | 80 | 894.455 | 2178.97 | 0.339599 | 5.55649 | 22.443 | 3.89342 | 0.00161608 | 3.47544e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4833.25 | 0.0696506 | 762.093ms | 1691 | 4890 | 264.099 | 333.66 | 0.0273925 | 1.19626 | 4.41573 | 0.712596 | 0.000591608 | 7.31649e-05 | 3.84569e-05 | 1(Win) | true |
| simdjson (ondemand) | 3906.53 | 0.638912 | 772.093ms | 1691 | 160 | 1113.03 | 412.812 | 0.0242182 | 1.42323 | 5.11886 | 0.719692 | 0.000591366 | 8.87049e-05 | 7.39208e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5381.09 | 0.158347 | 749.666ms | 1691 | 320 | 72.0639 | 299.691 | 0.00104275 | 1.0872 | 4.06682 | 0.633944 | 0.000591366 | 1.66322e-05 | 9.24009e-06 | 1(Win) | true |
| simdjson (ondemand) | 4466.82 | 0.188648 | 751.549ms | 1691 | 160 | 74.2191 | 361.031 | 0.025974 | 1.28313 | 4.77055 | 0.642224 | 0.000591366 | 1.10881e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5468.71 | 0.0883419 | 753.178ms | 2158 | 320 | 35.3685 | 376.328 | 0.000830399 | 1.04625 | 3.8531 | 0.57924 | 0.000926784 | 1.01367e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4928.23 | 0.213827 | 761.551ms | 2158 | 80 | 63.7873 | 417.6 | 0.221996 | 1.14534 | 4.2507 | 0.572289 | 0.000463392 | 0 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5953.92 | 0.184736 | 752.761ms | 2158 | 320 | 130.482 | 345.659 | 0.0117543 | 0.962858 | 3.5797 | 0.517609 | 0.000925336 | 2.02734e-05 | 1.15848e-05 | 1(Win) | true |
| simdjson (ondemand) | 5293.77 | 0.0660383 | 756.721ms | 2158 | 2560 | 168.735 | 388.764 | 0.107697 | 1.06251 | 3.97776 | 0.511585 | 0.000463392 | 3.36683e-05 | 1.61101e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3388.13 | 0.0779915 | 768.993ms | 1691 | 40 | 5.51218 | 475.975 | 0.012254 | 1.65052 | 6.68007 | 1.20225 | 0.000591366 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2584.98 | 0.0515193 | 779.833ms | 1691 | 4890 | 505.154 | 623.86 | 0.0548879 | 2.12066 | 8.68717 | 1.43998 | 0.000811949 | 4.03919e-05 | 1.66889e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3586.59 | 0.105856 | 760.317ms | 1691 | 2560 | 579.96 | 449.637 | 0.0208458 | 1.56361 | 6.33117 | 1.1236 | 0.000593214 | 2.91063e-05 | 8.08508e-06 | 1(Win) | true |
| simdjson (ondemand) | 2678.35 | 0.0647366 | 783.447ms | 1691 | 4890 | 742.953 | 602.11 | 0.103305 | 2.04477 | 8.33885 | 1.36251 | 0.00116169 | 4.72851e-05 | 2.24937e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3932.69 | 0.123768 | 770.691ms | 2158 | 4890 | 2051.41 | 523.313 | 0.217951 | 1.40076 | 5.63531 | 0.980538 | 0.00108599 | 5.43941e-05 | 1.83841e-05 | 1(Win) | true |
| simdjson (ondemand) | 3200.96 | 0.0795647 | 784.887ms | 2158 | 640 | 167.48 | 642.941 | 0.0369533 | 1.71142 | 7.04356 | 1.13531 | 0.000619063 | 1.59291e-05 | 2.8962e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4249.82 | 0.179601 | 767.367ms | 2158 | 640 | 484.125 | 484.262 | 0.2857 | 1.31029 | 5.36191 | 0.918906 | 0.00100933 | 2.31696e-05 | 7.96455e-06 | 1(Win) | true |
| simdjson (ondemand) | 3324.51 | 0.153434 | 779.607ms | 2158 | 1280 | 1154.79 | 619.047 | 0.133953 | 1.6436 | 6.77062 | 1.07461 | 0.000899632 | 1.95494e-05 | 5.06835e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1280.97 | 0.0697578 | 1050.49ms | 4390 | 4890 | 25418.3 | 3268.33 | 0.100597 | 4.06084 | 18.1157 | 3.37198 | 0.00223109 | 0.000103321 | 4.63034e-05 | 1(Win) | true |
| simdjson (ondemand) | 1049.88 | 0.133145 | 1128.67ms | 4390 | 640 | 18041.9 | 3987.72 | 0.0101473 | 4.94596 | 20.4005 | 3.53235 | 0.00412514 | 6.26424e-05 | 2.81179e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1423.05 | 0.101914 | 1040.9ms | 4390 | 640 | 5753.61 | 2942.02 | 0.0567003 | 3.66772 | 16.6216 | 3.04055 | 0.0025242 | 0.000108912 | 3.98633e-05 | 1(Win) | true |
| simdjson (ondemand) | 1150.14 | 0.0606889 | 1116.78ms | 4390 | 4890 | 23864.7 | 3640.1 | 0.0437117 | 4.50901 | 18.7929 | 3.17813 | 0.00419586 | 9.36317e-05 | 4.50457e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2404.12 | 0.0955719 | 1101.54ms | 9378 | 2560 | 32360.1 | 3720.1 | 0.0339488 | 2.14455 | 9.43954 | 1.64683 | 0.0010555 | 3.95707e-05 | 1.24543e-05 | 1(Win) | true |
| simdjson (ondemand) | 2091 | 0.159751 | 1158.56ms | 9378 | 30 | 1400.63 | 4277.17 | 0.109226 | 2.44637 | 10.1507 | 1.67914 | 0.00141821 | 2.84353e-05 | 1.06633e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2635.84 | 0.0685277 | 1095.38ms | 9378 | 1280 | 6920.31 | 3393.06 | 0.214707 | 1.95942 | 8.71316 | 1.48635 | 0.00130791 | 1.74111e-05 | 2.99904e-06 | 1(Win) | true |
| simdjson (ondemand) | 2326.76 | 0.0492196 | 1134.74ms | 9378 | 4890 | 17502.5 | 3843.78 | 0.221172 | 2.21947 | 9.42514 | 1.51866 | 0.0015371 | 2.61675e-05 | 9.87823e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 781.039 | 0.0534682 | 1269.28ms | 4390 | 160 | 1314.3 | 5360.33 | 0.0446368 | 6.64751 | 29.1993 | 5.90911 | 0.0112557 | 4.84055e-05 | 4.27107e-06 | 1(Win) | true |
| simdjson (ondemand) | 681.386 | 0.0566342 | 1347.99ms | 4390 | 1280 | 15499.2 | 6144.29 | 0.0540606 | 7.53939 | 32.9911 | 6.06697 | 0.0099774 | 7.15404e-05 | 3.63041e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 843.512 | 0.0734741 | 1254.24ms | 4390 | 640 | 8511.3 | 4963.33 | 0.00340005 | 6.14593 | 27.6474 | 5.56606 | 0.0104474 | 3.09653e-05 | 2.84738e-06 | 1(Win) | true |
| simdjson (ondemand) | 729.198 | 0.0542864 | 1327.43ms | 4390 | 160 | 1554.32 | 5741.42 | 0.00468068 | 7.11583 | 31.441 | 5.72392 | 0.00992454 | 4.41344e-05 | 1.28132e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1516.39 | 0.108213 | 1320.78ms | 9378 | 320 | 13034.8 | 5897.91 | 0.0659566 | 3.41774 | 14.7165 | 2.89209 | 0.00618735 | 1.83275e-05 | 2.99904e-06 | 1(Win) | true |
| simdjson (ondemand) | 1426.08 | 0.0621381 | 1367.08ms | 9378 | 1280 | 19438.4 | 6271.44 | 0.133451 | 3.62108 | 15.9003 | 2.84059 | 0.00483362 | 5.28997e-05 | 2.54918e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1630.43 | 0.107298 | 1308.35ms | 9378 | 40 | 1385.68 | 5485.4 | 0.0437717 | 3.18379 | 13.99 | 2.7315 | 0.00595543 | 1.59949e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1488.24 | 0.0551271 | 1341.53ms | 9378 | 1280 | 14048 | 6009.49 | 0.00808683 | 3.43688 | 15.1747 | 2.68 | 0.005217 | 1.8744e-05 | 4.33195e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2180.42 | 0.149172 | 936.71ms | 4390 | 1280 | 10501.2 | 1920.11 | 0.0594909 | 2.4094 | 10.6089 | 1.90205 | 0.00282727 | 8.09724e-05 | 4.96512e-05 | 1(Win) | true |
| simdjson (ondemand) | 1958.76 | 0.0766481 | 933.094ms | 4390 | 2560 | 6870.84 | 2137.39 | 0.0537414 | 2.676 | 11.6948 | 1.87335 | 0.0016788 | 4.71597e-05 | 2.42917e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.53 | 0.0904087 | 909.388ms | 4390 | 160 | 429.383 | 1811.97 | 0.0648043 | 2.27933 | 10.2645 | 1.82164 | 0.00224943 | 1.70843e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 2026.38 | 0.0945773 | 933.131ms | 4390 | 30 | 114.547 | 2066.07 | 0.0789928 | 2.54509 | 11.354 | 1.79339 | 0.00136674 | 0 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3923.03 | 0.07012 | 950.288ms | 9378 | 1280 | 3270.94 | 2279.76 | 0.150386 | 1.33673 | 5.79068 | 0.951376 | 0.00118829 | 3.40724e-05 | 1.44121e-05 | 1(Win) | true |
| simdjson (ondemand) | 3757.65 | 0.120022 | 959.829ms | 9378 | 640 | 5222.67 | 2380.1 | 0.0151625 | 1.3927 | 6.10471 | 0.908936 | 0.00131225 | 1.79942e-05 | 7.66421e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4106.56 | 0.0389711 | 943.231ms | 9378 | 640 | 461.03 | 2177.87 | 0.120743 | 1.2782 | 5.62945 | 0.913734 | 0.000982186 | 1.58283e-05 | 4.16533e-06 | 1(Win) | true |
| simdjson (ondemand) | 3894.85 | 0.175806 | 953.881ms | 9378 | 320 | 5215.05 | 2296.25 | 0.141872 | 1.34443 | 5.94519 | 0.871508 | 0.00148586 | 1.09965e-05 | 3.33227e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1718.89 | 0.0610025 | 966.693ms | 4390 | 2560 | 5651.54 | 2435.65 | 0.0853778 | 3.0203 | 13.8132 | 2.59339 | 0.0037161 | 3.90625e-05 | 1.49487e-05 | 1(Win) | true |
| simdjson (ondemand) | 1634.3 | 0.121022 | 978.233ms | 4390 | 40 | 384.461 | 2561.72 | 0.00227716 | 3.20373 | 14.4604 | 2.38451 | 0.00345103 | 3.41686e-05 | 1.13895e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1804.05 | 0.0602438 | 958.577ms | 4390 | 2560 | 5003.77 | 2320.69 | 0.0632158 | 2.89977 | 13.4688 | 2.51298 | 0.00336409 | 4.71597e-05 | 1.98427e-05 | 1(Win) | true |
| simdjson (ondemand) | 1674.39 | 0.195743 | 972.367ms | 4390 | 320 | 7665.46 | 2500.4 | 0.109978 | 3.12242 | 14.1772 | 2.31595 | 0.00353716 | 3.48804e-05 | 1.13895e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3289.89 | 0.124945 | 999.186ms | 9378 | 40 | 461.487 | 2718.5 | 0.111706 | 1.62042 | 7.39678 | 1.14758 | 0.00171945 | 2.13265e-05 | 2.66581e-06 | 1(Win) | true |
| Jsonifier (generic) | 3164.81 | 0.112647 | 994.374ms | 9378 | 80 | 810.692 | 2825.94 | 0.367109 | 1.6513 | 7.27138 | 1.28983 | 0.0018754 | 2.39923e-05 | 1.59949e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3297.69 | 0.0579573 | 1002.95ms | 9378 | 160 | 395.31 | 2712.07 | 0.0486489 | 1.58591 | 7.13713 | 1.25752 | 0.00159816 | 1.06633e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3242.45 | 0.146412 | 998.636ms | 9378 | 40 | 652.358 | 2758.28 | 0.0069483 | 1.58292 | 7.26679 | 1.11612 | 0.00198603 | 3.19898e-05 | 2.39923e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1481.55 | 0.0438637 | 1027.67ms | 4669 | 320 | 556.127 | 3005.43 | 0.0889264 | 3.52401 | 14.5768 | 2.78239 | 0.00207753 | 3.54733e-05 | 6.02377e-06 | 1(Win) | true |
| simdjson (ondemand) | 1448.75 | 0.142569 | 1033.19ms | 4669 | 80 | 1536.02 | 3073.47 | 0.0488285 | 3.60388 | 16.2722 | 2.41829 | 0.00180713 | 7.76398e-05 | 2.67723e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1633.03 | 0.13925 | 1004.28ms | 4669 | 40 | 576.644 | 2726.65 | 0.0238331 | 3.26109 | 13.7629 | 2.59756 | 0.00192225 | 1.07089e-05 | 5.35447e-06 | 1(Win) | true |
| simdjson (ondemand) | 1576.19 | 0.189505 | 1014.25ms | 4669 | 40 | 1146.38 | 2824.97 | 0.00265496 | 3.31584 | 15.4588 | 2.2341 | 0.00180445 | 2.14179e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2334.49 | 0.0493683 | 1039.07ms | 7932 | 4890 | 12513.7 | 3240.34 | 0.462654 | 2.23299 | 10.0968 | 1.44982 | 0.00149669 | 2.56784e-05 | 7.68289e-06 | 1(Win) | true |
| Jsonifier (generic) | 2258.72 | 0.0918654 | 1055.22ms | 7932 | 30 | 283.964 | 3349.03 | 0.0139324 | 2.31521 | 9.34405 | 1.69856 | 0.00127753 | 3.36191e-05 | 4.20239e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2528.5 | 0.0382337 | 1020.83ms | 7932 | 4890 | 6397.94 | 2991.71 | 0.021906 | 2.06739 | 9.61624 | 1.34065 | 0.00113011 | 2.53948e-05 | 9.02353e-06 | 1(Win) | true |
| Jsonifier (generic) | 2445.57 | 0.0971431 | 1032.65ms | 7932 | 640 | 5778.41 | 3093.16 | 0.124927 | 2.13479 | 8.84329 | 1.58233 | 0.00105762 | 2.87601e-05 | 8.47044e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 600.602 | 0.124841 | 1466.81ms | 4669 | 30 | 2569.86 | 7413.73 | 0.0368549 | 8.62554 | 37.2804 | 7.4245 | 0.00847433 | 7.85322e-05 | 1.42786e-05 | 1(Win) | true |
| simdjson (ondemand) | 231.925 | 0.138802 | 2631.97ms | 4669 | 320 | 227244 | 19198.9 | 0.000765011 | 22.0991 | 104.543 | 18.8925 | 0.0500522 | 0.000137208 | 7.29546e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 625.922 | 0.0377724 | 1442.79ms | 4669 | 1280 | 9242.02 | 7113.83 | 0.078943 | 8.27209 | 36.471 | 7.24138 | 0.00824086 | 6.87714e-05 | 2.07486e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.509 | 0.0735066 | 2626.91ms | 4669 | 1280 | 247227 | 18906.7 | 0.173866 | 21.8 | 103.734 | 18.71 | 0.0521167 | 8.81814e-05 | 4.51783e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 893.928 | 0.0337767 | 1572.22ms | 7932 | 4890 | 39948.9 | 8462.14 | 0.182231 | 5.77335 | 24.1813 | 4.65545 | 0.00563888 | 8.18563e-05 | 3.88785e-05 | 1(Win) | true |
| simdjson (ondemand) | 393.645 | 0.0419415 | 2665.61ms | 7932 | 4890 | 317653 | 19216.7 | 0.0546861 | 13.0082 | 61.2099 | 10.986 | 0.0284187 | 9.04931e-05 | 5.16919e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 922.171 | 0.0272714 | 1553ms | 7932 | 4890 | 24471.7 | 8202.97 | 0.0835313 | 5.59537 | 23.7068 | 4.54841 | 0.00629306 | 7.09507e-05 | 4.12246e-05 | 1(Win) | true |
| simdjson (ondemand) | 398.371 | 0.220292 | 2632.19ms | 7932 | 80 | 139984 | 18988.7 | 0.0918782 | 12.9524 | 60.7317 | 10.8781 | 0.0306181 | 8.82501e-05 | 3.78215e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4730.39 | 0.0526969 | 815.987ms | 4669 | 320 | 78.736 | 941.297 | 0.120367 | 1.13738 | 5.11501 | 0.768473 | 0.00086073 | 1.60634e-05 | 6.69308e-07 | 1(Win) | true |
| simdjson (ondemand) | 4184.92 | 0.163769 | 826.74ms | 4669 | 80 | 242.899 | 1063.99 | 0.0293793 | 1.27833 | 5.62947 | 0.697794 | 0.00144035 | 1.33862e-05 | 2.67723e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5157.08 | 0.0750962 | 805.827ms | 4669 | 320 | 134.532 | 863.416 | 0.0459868 | 1.04604 | 4.84108 | 0.706789 | 0.000862069 | 2.20872e-05 | 5.35447e-06 | 1(Win) | true |
| simdjson (ondemand) | 4497.83 | 0.203904 | 821.682ms | 4669 | 30 | 122.24 | 989.967 | 0.0168327 | 1.19355 | 5.35575 | 0.636111 | 0.0013993 | 3.56964e-05 | 7.13929e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6607.47 | 0.0527618 | 845.124ms | 7932 | 4890 | 1784.2 | 1144.85 | 0.0408758 | 0.805685 | 3.57426 | 0.48651 | 0.000513903 | 3.44699e-05 | 1.4747e-05 | 1(Win) | true |
| simdjson (ondemand) | 6211.48 | 0.0399075 | 844.088ms | 7932 | 1280 | 302.338 | 1217.83 | 0.100295 | 0.85788 | 3.81228 | 0.432426 | 0.000952333 | 1.60544e-05 | 4.82618e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7123.83 | 0.0680059 | 832.59ms | 7932 | 4890 | 2550 | 1061.86 | 0.017052 | 0.747921 | 3.41301 | 0.450202 | 0.000505447 | 1.39478e-05 | 2.52659e-06 | 1(Win) | true |
| simdjson (ondemand) | 6593.61 | 0.0653649 | 835.366ms | 7932 | 4890 | 2749.9 | 1147.25 | 0.0261857 | 0.808091 | 3.65116 | 0.396117 | 0.000831377 | 1.78924e-05 | 8.86884e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3287.32 | 0.042272 | 859.225ms | 4669 | 4890 | 1603.17 | 1354.51 | 0.047271 | 1.60732 | 7.44356 | 1.32127 | 0.00150709 | 2.69366e-05 | 7.66488e-06 | 1(Win) | true |
| simdjson (ondemand) | 2518.21 | 0.0804922 | 895.276ms | 4669 | 2560 | 5185.76 | 1768.2 | 0.00311482 | 2.08722 | 9.78068 | 1.52538 | 0.00286389 | 2.49317e-05 | 9.37031e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3504.27 | 0.118303 | 842.709ms | 4669 | 40 | 90.3872 | 1270.65 | 0.106358 | 1.51726 | 7.16963 | 1.25958 | 0.00158492 | 2.14179e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2624.97 | 0.139751 | 891.555ms | 4669 | 1280 | 7193.15 | 1696.29 | 0.114963 | 1.99633 | 9.50696 | 1.4637 | 0.00285209 | 2.62703e-05 | 1.25495e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4832.42 | 0.0768102 | 876.857ms | 7932 | 80 | 115.655 | 1565.38 | 0.0686265 | 1.09506 | 4.9884 | 0.823122 | 0.000882501 | 1.10313e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3976.91 | 0.073898 | 907.616ms | 7932 | 1280 | 2529.01 | 1902.12 | 0.00628372 | 1.32362 | 6.23765 | 0.917045 | 0.00175821 | 3.28968e-05 | 1.48725e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5014.8 | 0.155226 | 871.797ms | 7932 | 2560 | 14035.5 | 1508.44 | 0.0195552 | 1.04695 | 4.82716 | 0.786813 | 0.00099764 | 1.85168e-05 | 7.92872e-06 | 1(Win) | true |
| simdjson (ondemand) | 4131.93 | 0.0840014 | 902.716ms | 7932 | 4890 | 11564.9 | 1830.76 | 0.00661114 | 1.26793 | 6.07653 | 0.880737 | 0.00159523 | 1.2865e-05 | 3.97035e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 571.72 | 0.0375558 | 1494.21ms | 4604 | 2560 | 21296 | 7679.84 | 0.00215149 | 8.97859 | 35.999 | 7.54551 | 0.0103695 | 0.000141351 | 6.93181e-05 | 1(Win) | true |
| simdjson (ondemand) | 545.704 | 0.0512067 | 1538.85ms | 4604 | 2560 | 43456 | 8045.97 | 0.105488 | 9.47173 | 38.6133 | 6.98176 | 0.0111945 | 0.000178428 | 9.90138e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 661.369 | 0.0526884 | 1481.67ms | 4604 | 1280 | 15661.1 | 6638.83 | 0.0595339 | 7.80621 | 31.4639 | 6.51694 | 0.00918648 | 5.41309e-05 | 1.32358e-05 | 1(Win) | true |
| simdjson (ondemand) | 608.334 | 0.0344054 | 1540.56ms | 4604 | 4890 | 30154.2 | 7217.61 | 0.183288 | 8.42298 | 34.3778 | 6.01597 | 0.0110046 | 9.64752e-05 | 4.76157e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2094.47 | 0.0613675 | 1566.44ms | 18245 | 4890 | 127094 | 8307.49 | 0.157357 | 2.44526 | 9.94629 | 1.95155 | 0.0026496 | 0.000100406 | 5.88558e-05 | 1(Win) | true |
| simdjson (ondemand) | 1993.01 | 0.0337867 | 1607.51ms | 18245 | 2560 | 22274.1 | 8730.41 | 0.0958598 | 2.57974 | 10.6427 | 1.79973 | 0.00311235 | 2.31014e-05 | 1.03838e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2397.36 | 0.0454745 | 1552.47ms | 18245 | 640 | 6971.65 | 7257.88 | 0.341352 | 2.15368 | 8.8137 | 1.69466 | 0.00246009 | 8.82091e-06 | 5.99479e-07 | 1(Win) | true |
| simdjson (ondemand) | 2189.16 | 0.127183 | 1618.67ms | 18245 | 30 | 3065.59 | 7948.17 | 0.150365 | 2.32298 | 9.58854 | 1.55922 | 0.00285558 | 6.75984e-05 | 5.11556e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 337.389 | 0.17178 | 2044.43ms | 4604 | 80 | 39980.3 | 13013.8 | 0.00288163 | 15.2998 | 67.3106 | 14.8366 | 0.0178025 | 6.78758e-05 | 1.90052e-05 | 1(Win) | true |
| simdjson (ondemand) | 241.866 | 0.111821 | 2544.31ms | 4604 | 160 | 65930.5 | 18153.5 | 0.0623546 | 21.3271 | 110.267 | 22.1179 | 0.0208664 | 0.000232135 | 0.000166974 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 363.115 | 0.109044 | 2032.63ms | 4604 | 320 | 55633.5 | 12091.8 | 0.0300139 | 14.2182 | 62.9796 | 13.8456 | 0.0159915 | 0.000204985 | 0.000131679 | 1(Win) | true |
| simdjson (ondemand) | 257.609 | 0.0925452 | 2533.93ms | 4604 | 160 | 39808.5 | 17044.1 | 0.117059 | 20.027 | 105.913 | 21.1219 | 0.0207265 | 9.09535e-05 | 2.85078e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1240.01 | 0.0307878 | 2136.38ms | 18245 | 2560 | 47778.9 | 14032 | 0.0106108 | 4.15327 | 18.0025 | 3.83626 | 0.0047983 | 3.39134e-05 | 1.43875e-05 | 1(Win) | true |
| simdjson (ondemand) | 921.474 | 0.278295 | 2631.21ms | 18245 | 30 | 82842.7 | 18882.6 | 0.179322 | 5.59251 | 28.6774 | 5.61074 | 0.0059103 | 0.000118754 | 0.000109619 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1331.49 | 0.0241824 | 2135.67ms | 18245 | 4890 | 48833.5 | 13067.9 | 0.314039 | 3.87053 | 16.9158 | 3.58772 | 0.00439227 | 4.44193e-05 | 2.49949e-05 | 1(Win) | true |
| simdjson (ondemand) | 971.441 | 0.0190947 | 2623.38ms | 18245 | 4890 | 57199.4 | 17911.3 | 0.0511777 | 5.30016 | 27.5813 | 5.36015 | 0.00607462 | 3.23365e-05 | 1.69921e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3825.48 | 0.171699 | 836.842ms | 4604 | 2560 | 9942.03 | 1147.76 | 1.06053 | 1.39082 | 6.51151 | 1.01434 | 0.000667388 | 2.52837e-05 | 9.58745e-06 | 1(Win) | true |
| simdjson (ondemand) | 3794.61 | 0.0771214 | 836.718ms | 4604 | 4890 | 3893.99 | 1157.09 | 0.0199239 | 1.40326 | 6.91464 | 0.961121 | 0.000697358 | 2.00768e-05 | 5.55221e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3987.53 | 0.465115 | 829.525ms | 4604 | 320 | 8393.32 | 1101.11 | 0.248091 | 1.34017 | 6.42268 | 0.994353 | 0.000663825 | 1.35752e-05 | 1.35752e-06 | 1(Win) | true |
| simdjson (ondemand) | 3903.18 | 0.0793258 | 833.022ms | 4604 | 2560 | 2038.45 | 1124.91 | 0.0770797 | 1.36679 | 6.82732 | 0.941573 | 0.000659158 | 1.91749e-05 | 3.2241e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10752.8 | 0.043858 | 887.406ms | 18245 | 2560 | 1289.38 | 1618.16 | 0.010717 | 0.49108 | 2.43053 | 0.29208 | 0.000123386 | 9.09924e-06 | 1.62716e-06 | 1(Win) | true |
| simdjson (ondemand) | 8763.36 | 0.0965015 | 917.672ms | 18245 | 320 | 1174.8 | 1985.52 | 0.0187329 | 0.59089 | 2.66281 | 0.283804 | 0.000199884 | 5.82351e-06 | 1.7128e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11132.4 | 0.0718074 | 884.404ms | 18245 | 80 | 100.772 | 1562.99 | 0.0664234 | 0.474886 | 2.40811 | 0.287038 | 0.000109619 | 1.64429e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9036.39 | 0.0659288 | 921.556ms | 18245 | 1280 | 2062.8 | 1925.52 | 0.0375974 | 0.581992 | 2.64078 | 0.278871 | 0.000198899 | 8.26425e-06 | 1.32742e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2582.21 | 0.0418861 | 897.339ms | 4604 | 320 | 162.321 | 1700.37 | 0.0687824 | 2.04316 | 9.16638 | 1.7487 | 0.00086881 | 1.62902e-05 | 4.7513e-06 | 1(Win) | true |
| simdjson (ondemand) | 2249.36 | 0.0445859 | 912.751ms | 4604 | 2560 | 1939.04 | 1951.98 | 0.0185074 | 2.33252 | 13.3165 | 2.35295 | 0.00109908 | 2.79988e-05 | 6.27851e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2621.69 | 0.0814482 | 900.866ms | 4604 | 2560 | 4763.35 | 1674.77 | 0.380942 | 2.01439 | 9.07754 | 1.72871 | 0.00106853 | 2.70655e-05 | 8.82385e-06 | 1(Win) | true |
| simdjson (ondemand) | 2273.53 | 0.187953 | 911.825ms | 4604 | 2560 | 33729.5 | 1931.24 | 0.0397612 | 2.31587 | 13.2291 | 2.33341 | 0.00126283 | 4.49677e-05 | 2.12112e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7936.08 | 0.0990799 | 937.378ms | 18245 | 2560 | 12080.5 | 2192.49 | 0.0818176 | 0.659226 | 3.10869 | 0.4792 | 0.000282291 | 8.34989e-06 | 1.9269e-06 | 1(Win) | true |
| simdjson (ondemand) | 6713.9 | 0.150496 | 981.212ms | 18245 | 160 | 2433.93 | 2591.61 | 0.107203 | 0.777235 | 4.27832 | 0.634859 | 0.000293574 | 3.35708e-05 | 2.32941e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8325.64 | 0.117439 | 932.952ms | 18245 | 1280 | 7710.61 | 2089.9 | 0.107027 | 0.627701 | 3.08627 | 0.474157 | 0.000267753 | 1.07906e-05 | 3.93944e-06 | 1(Win) | true |
| simdjson (ondemand) | 6754.08 | 0.0718113 | 980.49ms | 18245 | 640 | 2190.39 | 2576.19 | 0.0610527 | 0.76578 | 4.25629 | 0.629926 | 0.00028441 | 7.27939e-06 | 2.05536e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1154.7 | 0.0986721 | 1131.31ms | 4926 | 1280 | 20627.5 | 4068.41 | 0.0373635 | 4.4813 | 17.1821 | 3.24239 | 0.00898691 | 7.21617e-05 | 2.5217e-05 | 1(Win) | true |
| simdjson (ondemand) | 989.539 | 0.0493728 | 1201.76ms | 4926 | 2560 | 14065 | 4747.47 | 0.0676558 | 5.21841 | 19.5077 | 3.39566 | 0.00991272 | 4.43279e-05 | 1.26878e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1394.15 | 0.0381456 | 1096.92ms | 4926 | 4890 | 8079.19 | 3369.65 | 0.0262293 | 3.735 | 14.4872 | 2.64779 | 0.00901543 | 5.92823e-05 | 2.28328e-05 | 1(Win) | true |
| simdjson (ondemand) | 1149.49 | 0.0629636 | 1170.34ms | 4926 | 1280 | 8475.55 | 4086.85 | 0.197746 | 4.49663 | 16.8886 | 2.81628 | 0.0107887 | 6.20115e-05 | 2.82303e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1849.86 | 0.0339062 | 1151.95ms | 8150 | 4890 | 9924.4 | 4201.64 | 0.0357102 | 2.80205 | 10.9156 | 1.97976 | 0.00515957 | 5.52775e-05 | 2.36868e-05 | 1(Win) | true |
| simdjson (ondemand) | 1568.15 | 0.0409162 | 1234.85ms | 8150 | 2560 | 10528.5 | 4956.43 | 0.0216134 | 3.296 | 12.3189 | 2.08466 | 0.00580967 | 5.67964e-05 | 2.64571e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2220.92 | 0.206996 | 1122ms | 8150 | 40 | 2099.11 | 3499.65 | 0.499919 | 2.34697 | 9.28613 | 1.62012 | 0.00515337 | 5.21472e-05 | 2.76074e-05 | 1(Win) | true |
| simdjson (ondemand) | 1836.96 | 0.194082 | 1191.72ms | 8150 | 40 | 2697.41 | 4231.15 | 0.104494 | 2.83181 | 10.7043 | 1.72699 | 0.0061319 | 6.13497e-05 | 3.06748e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 832.165 | 0.0924914 | 1292.73ms | 4926 | 640 | 17448.3 | 5645.27 | 0.0190461 | 6.22806 | 26.8603 | 5.46143 | 0.00870984 | 8.59597e-05 | 4.409e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.228 | 0.0229582 | 1768.86ms | 4926 | 4890 | 27937.1 | 10411.1 | 0.0185143 | 11.413 | 49.1975 | 8.94032 | 0.0294085 | 9.6562e-05 | 4.44202e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 961.716 | 0.0619262 | 1254.65ms | 4926 | 1280 | 11712.6 | 4884.81 | 0.112336 | 5.39708 | 24.1768 | 4.86764 | 0.00806213 | 0.000133856 | 7.26375e-05 | 1(Win) | true |
| simdjson (ondemand) | 488.32 | 0.0411497 | 1727.05ms | 4926 | 2560 | 40119.3 | 9620.34 | 0.0231227 | 10.5615 | 46.528 | 8.34755 | 0.0279639 | 0.000101344 | 4.58346e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1260.15 | 0.0596397 | 1347.76ms | 8150 | 640 | 8660.15 | 6167.89 | 0.00613091 | 4.11221 | 17.3065 | 3.47657 | 0.00613708 | 2.07055e-05 | 3.06748e-06 | 1(Win) | true |
| simdjson (ondemand) | 738.626 | 0.033785 | 1781.45ms | 8150 | 2560 | 32355.9 | 10522.8 | 0.14639 | 6.97395 | 29.9496 | 5.37742 | 0.0175818 | 7.65913e-05 | 3.84394e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.47 | 0.0357506 | 1314.41ms | 8150 | 2560 | 9632.76 | 5425.9 | 0.0409014 | 3.6199 | 15.6845 | 3.11767 | 0.00612049 | 2.49233e-05 | 8.24387e-06 | 1(Win) | true |
| simdjson (ondemand) | 804.422 | 0.0610026 | 1736.22ms | 8150 | 160 | 5558.58 | 9662.14 | 0.0406706 | 6.43217 | 28.3353 | 5.01902 | 0.0161281 | 2.9908e-05 | 1.07362e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2574.45 | 0.0655842 | 902.289ms | 4926 | 4890 | 7003.71 | 1824.78 | 0.361124 | 2.03465 | 8.75863 | 1.58222 | 0.00195524 | 3.88158e-05 | 1.61075e-05 | 1(Win) | true |
| simdjson (ondemand) | 2102.24 | 0.052397 | 945.103ms | 4926 | 4890 | 6704.19 | 2234.67 | 0.217287 | 2.48794 | 10.2505 | 1.6149 | 0.00296951 | 2.94751e-05 | 1.10428e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2861.99 | 0.0745777 | 894.012ms | 4926 | 1280 | 1918.14 | 1641.44 | 0.00280804 | 1.84436 | 8.15185 | 1.43402 | 0.00219039 | 4.09181e-05 | 1.91903e-05 | 1(Win) | true |
| simdjson (ondemand) | 2298.6 | 0.108966 | 935.199ms | 4926 | 80 | 396.766 | 2043.76 | 0.0312022 | 2.28727 | 9.64657 | 1.46813 | 0.00330644 | 1.77629e-05 | 2.53756e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3812.71 | 0.0670624 | 924.409ms | 8150 | 1280 | 2392.31 | 2038.56 | 0.0021844 | 1.37766 | 5.87926 | 0.992638 | 0.00133301 | 2.73198e-05 | 1.00652e-05 | 1(Win) | true |
| simdjson (ondemand) | 3351.36 | 0.0591984 | 952.851ms | 8150 | 2560 | 4825.38 | 2319.19 | 0.0623314 | 1.56174 | 6.55791 | 0.976197 | 0.00166147 | 1.9028e-05 | 4.36158e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4157.33 | 0.139228 | 917.351ms | 8150 | 40 | 271.02 | 1869.58 | 0.0512332 | 1.26697 | 5.51252 | 0.903067 | 0.00174233 | 5.21472e-05 | 2.45399e-05 | 1(Win) | true |
| simdjson (ondemand) | 3602.93 | 0.0540639 | 946.467ms | 8150 | 2560 | 3482.24 | 2157.26 | 0.439125 | 1.45255 | 6.19288 | 0.887485 | 0.00172215 | 2.41085e-05 | 6.03911e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1935.16 | 0.102671 | 966.694ms | 4926 | 80 | 496.977 | 2427.6 | 0.0329652 | 2.70785 | 11.8084 | 2.22452 | 0.00347391 | 2.03004e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1507.51 | 0.0385608 | 1033.37ms | 4926 | 4890 | 7061.06 | 3116.26 | 0.00029733 | 3.44364 | 14.5828 | 2.43443 | 0.00722023 | 2.21271e-05 | 2.36631e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2058.95 | 0.0965118 | 964.789ms | 4926 | 1280 | 6206.79 | 2281.65 | 0.0515245 | 2.53702 | 11.1955 | 2.0745 | 0.00421885 | 1.45909e-05 | 3.17194e-07 | 1(Win) | true |
| simdjson (ondemand) | 1580.59 | 0.0613362 | 1032.28ms | 4926 | 2560 | 8507.94 | 2972.18 | 0.291494 | 3.26208 | 13.9724 | 2.28583 | 0.00735764 | 5.53504e-05 | 2.80717e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2958.79 | 0.0557497 | 985.218ms | 8150 | 2560 | 5490.51 | 2626.9 | 0.00929472 | 1.76074 | 7.82295 | 1.39877 | 0.00197302 | 4.04045e-05 | 1.24137e-05 | 1(Win) | true |
| simdjson (ondemand) | 2426.89 | 0.0467185 | 1040.91ms | 8150 | 2560 | 5731.04 | 3202.63 | 0.101643 | 2.14254 | 9.21656 | 1.47975 | 0.00400508 | 1.43309e-05 | 2.1089e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3135.19 | 0.147167 | 978.066ms | 8150 | 80 | 1064.88 | 2479.1 | 0.0161323 | 1.67139 | 7.45252 | 1.3081 | 0.00277147 | 2.60736e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2567.19 | 0.120326 | 1033.35ms | 8150 | 160 | 2123.42 | 3027.61 | 0.0702366 | 2.02083 | 8.84761 | 1.38994 | 0.00392868 | 2.07055e-05 | 5.3681e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2172.85 | 0.0730021 | 845.94ms | 2821 | 4890 | 3995.07 | 1238.15 | 0.0715093 | 2.44574 | 9.0833 | 1.59624 | 0.000360066 | 0.000141141 | 8.48877e-05 | 1(Win) | true |
| simdjson (ondemand) | 2019.9 | 0.0379587 | 851.604ms | 2821 | 4890 | 1249.91 | 1331.9 | 0.0556036 | 2.62438 | 9.93584 | 1.52818 | 0.000365793 | 5.16141e-05 | 1.60931e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2428.6 | 0.0333668 | 839.575ms | 2821 | 640 | 87.4388 | 1107.76 | 0.014526 | 2.20094 | 8.48933 | 1.44845 | 0.000358915 | 3.32329e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2127.22 | 0.098845 | 854.92ms | 2821 | 1280 | 2000.33 | 1264.71 | 0.281859 | 2.49902 | 9.53563 | 1.42822 | 0.000631148 | 6.86813e-05 | 3.2679e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2813.07 | 0.0893025 | 846.506ms | 3770 | 4890 | 6370.27 | 1278.09 | 0.035193 | 1.88759 | 7.16234 | 1.19655 | 0.000297147 | 0.00010008 | 3.70485e-05 | 1(Win) | true |
| simdjson (ondemand) | 2572.61 | 0.0503851 | 859.794ms | 3770 | 4890 | 2424.65 | 1397.55 | 0.0393477 | 2.06063 | 7.77109 | 1.16313 | 0.000268995 | 4.44799e-05 | 1.23133e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3064.92 | 0.0351609 | 848.049ms | 3770 | 4890 | 831.903 | 1173.06 | 0.232739 | 1.73822 | 6.76631 | 1.09735 | 0.00026574 | 4.23101e-05 | 1.08488e-05 | 1(Win) | true |
| simdjson (ondemand) | 2712.92 | 0.0679346 | 856.293ms | 3770 | 2560 | 2075.07 | 1325.27 | 0.0658923 | 1.95774 | 7.47162 | 1.08833 | 0.000455073 | 7.91611e-05 | 3.34673e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.969 | 0.21771 | 1029.16ms | 2821 | 40 | 1780.19 | 3064.25 | 0.00380749 | 5.94725 | 24.5537 | 4.57356 | 0.00212691 | 7.08968e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 351.434 | 0.0313486 | 1497.67ms | 2821 | 4890 | 28162 | 7655.26 | 0.0445638 | 14.6978 | 66.9273 | 11.5175 | 0.0145673 | 0.000162961 | 0.000104678 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 915.203 | 0.110459 | 1022.6ms | 2821 | 640 | 6747.64 | 2939.58 | 0.025999 | 5.63096 | 24.0259 | 4.44027 | 0.00140797 | 4.54183e-05 | 7.75434e-06 | 1(Win) | true |
| simdjson (ondemand) | 354.766 | 0.050666 | 1490.4ms | 2821 | 2560 | 37791.7 | 7583.35 | 0.248321 | 14.542 | 66.5285 | 11.4169 | 0.013655 | 0.000106345 | 6.12039e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1097.39 | 0.111832 | 1051.49ms | 3770 | 80 | 1073.94 | 3276.26 | 0.0751054 | 4.75587 | 19.4886 | 3.59761 | 0.00213528 | 5.96817e-05 | 3.31565e-05 | 1(Win) | true |
| simdjson (ondemand) | 469.385 | 0.0465563 | 1489.05ms | 3770 | 2560 | 32555.3 | 7659.71 | 0.0114553 | 10.9937 | 49.6525 | 8.49417 | 0.0120805 | 8.12334e-05 | 4.46577e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1137.57 | 0.144145 | 1046.48ms | 3770 | 40 | 830.203 | 3160.55 | 0.0363728 | 4.58941 | 19.0936 | 3.49788 | 0.00192971 | 4.64191e-05 | 1.98939e-05 | 1(Win) | true |
| simdjson (ondemand) | 467.395 | 0.0328326 | 1503.08ms | 3770 | 4890 | 31191.4 | 7692.32 | 0.224449 | 10.921 | 49.3541 | 8.41884 | 0.012025 | 6.44958e-05 | 2.52776e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5994.76 | 0.10001 | 769.164ms | 2821 | 320 | 64.4616 | 448.778 | 0.0229738 | 0.921704 | 3.63524 | 0.507621 | 0.000358915 | 4.2095e-05 | 9.96987e-06 | 1(Win) | true |
| simdjson (ondemand) | 5281.08 | 0.34091 | 773.053ms | 2821 | 80 | 241.285 | 509.425 | 0.156794 | 1.03689 | 4.00284 | 0.450904 | 0.00120082 | 8.86211e-06 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6166.01 | 0.0678566 | 769.52ms | 2821 | 640 | 56.1 | 436.314 | 0.107909 | 0.897948 | 3.55229 | 0.488834 | 0.000650811 | 2.60324e-05 | 2.76941e-06 | 1(Win) | true |
| simdjson (ondemand) | 5705.37 | 0.168761 | 767.203ms | 2821 | 320 | 202.644 | 471.541 | 0.22152 | 0.976106 | 3.92449 | 0.43318 | 0.000554989 | 1.44009e-05 | 1.10776e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6925.48 | 0.0577056 | 773.021ms | 3770 | 640 | 57.438 | 519.148 | 0.0562504 | 0.80251 | 3.13316 | 0.402122 | 0.000531333 | 1.28481e-05 | 8.28912e-07 | 1(Win) | true |
| simdjson (ondemand) | 6599.85 | 0.285824 | 776.746ms | 3770 | 80 | 193.956 | 544.763 | 0.163181 | 0.839516 | 3.32493 | 0.35305 | 0.000570292 | 6.29973e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7195.56 | 0.154167 | 777.285ms | 3770 | 160 | 94.942 | 499.663 | 0.0200095 | 0.774799 | 3.07109 | 0.388064 | 0.000508952 | 1.49204e-05 | 1.65782e-06 | 1(Win) | true |
| simdjson (ondemand) | 6762.46 | 0.0375344 | 774.933ms | 3770 | 4890 | 194.733 | 531.663 | 0.150642 | 0.81359 | 3.26631 | 0.339788 | 0.000496439 | 1.30185e-05 | 2.06126e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4242.9 | 0.258088 | 783.607ms | 2821 | 640 | 1713.94 | 634.075 | 0.164339 | 1.2736 | 5.24566 | 0.867069 | 0.00141904 | 3.10174e-05 | 8.30822e-06 | 1(Win) | true |
| simdjson (ondemand) | 3683.57 | 0.0648784 | 792.364ms | 2821 | 640 | 143.697 | 730.355 | 0.195796 | 1.47804 | 6.25629 | 0.901453 | 0.000851316 | 3.37868e-05 | 1.71703e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4410.31 | 0.0482511 | 781.612ms | 2821 | 4890 | 423.635 | 610.007 | 0.1647 | 1.24167 | 5.16306 | 0.848635 | 0.00137705 | 2.10951e-05 | 2.10226e-06 | 1(Win) | true |
| simdjson (ondemand) | 3704.56 | 0.0614164 | 796.895ms | 2821 | 640 | 127.316 | 726.217 | 0.22059 | 1.44508 | 6.17831 | 0.884084 | 0.000833592 | 1.27393e-05 | 3.87717e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5250.12 | 0.118885 | 792.922ms | 3770 | 2560 | 1696.84 | 684.814 | 0.0380319 | 1.03179 | 4.44403 | 0.679576 | 0.0009031 | 2.20698e-05 | 5.906e-06 | 1(Win) | true |
| simdjson (ondemand) | 4516.39 | 0.152992 | 798.965ms | 3770 | 1280 | 1898.66 | 796.067 | 0.0237439 | 1.18009 | 5.02308 | 0.692838 | 0.000806532 | 9.94695e-06 | 2.90119e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5438.23 | 0.195341 | 794.435ms | 3770 | 80 | 133.427 | 661.125 | 0.105992 | 1.0053 | 4.38223 | 0.665782 | 0.000809019 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4638.04 | 0.135049 | 799.435ms | 3770 | 1280 | 1402.84 | 775.188 | 0.0406316 | 1.15647 | 4.96472 | 0.679841 | 0.000756797 | 1.1812e-05 | 4.35179e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4959.12 | 0.07975 | 6106.1ms | 277673 | 640 | 1.16064e+06 | 53398.5 | 0.0217714 | 1.03218 | 4.20971 | 0.692768 | 0.00463279 | 3.46631e-06 | 2.29587e-06 | 1(Win) | true |
| simdjson (ondemand) | 4199.17 | 0.0605366 | 7051.27ms | 277673 | 1280 | 1.86546e+06 | 63062.3 | 0.0624041 | 1.20512 | 4.65244 | 0.757382 | 0.00309128 | 2.14112e-06 | 1.02976e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3999.93 | 0.199076 | 7886.86ms | 10548466 | 30 | 7.52028e+08 | 2.515e+06 | 0.0205583 | 1.26935 | 4.20881 | 0.692842 | 0.011384 | 0.0171605 | 0.000661436 | 1(Win) | true |
| simdjson (ondemand) | 3695.61 | 0.221146 | 8508.2ms | 10548466 | 160 | 5.79811e+09 | 2.7221e+06 | 0.390748 | 1.38146 | 4.6488 | 0.75738 | 0.00887879 | 0.0179614 | 0.000509214 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3740.35 | 0.147045 | 6195.57ms | 16002592 | 40 | 1.43985e+09 | 4.08017e+06 | 0.0727303 | 1.3572 | 7.61693 | 1.22417 | 0.000786846 | 0.0325532 | 0.00609576 | 1(Win) | true |
| simdjson (ondemand) | 3189.39 | 0.0969197 | 7196.1ms | 16002592 | 30 | 6.45226e+08 | 4.78501e+06 | 0.180374 | 1.58358 | 8.48831 | 1.2264 | 0.00141822 | 0.0354204 | 0.00928246 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3582.1 | 0.136876 | 6465.27ms | 16002591 | 80 | 2.72049e+09 | 4.26042e+06 | 0.365201 | 1.41146 | 7.88139 | 1.31417 | 0.000824569 | 0.0358505 | 0.00637037 | 1(Win) | true |
| simdjson (ondemand) | 2022.47 | 0.225687 | 5350.61ms | 16002591 | 30 | 8.70068e+09 | 7.54587e+06 | 0.880634 | 2.51781 | 12.65 | 2.08617 | 0.00138177 | 0.0515488 | 0.00801653 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18964.9 | 0.380021 | 5207.73ms | 16197086 | 30 | 2.87416e+08 | 814492 | 0.190483 | 0.267345 | 1.17036 | 0.0705008 | 5.83232e-05 | 0.0157127 | 0.0022426 | 1(Win) | true |
| simdjson (ondemand) | 16070.5 | 0.281315 | 6221.75ms | 16197086 | 320 | 2.33963e+09 | 961184 | 0.998279 | 0.314604 | 1.26024 | 0.0744755 | 0.000115326 | 0.0157363 | 0.00208862 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 19875.4 | 0.234865 | 5077.89ms | 16197085 | 40 | 1.33271e+08 | 777177 | 0.968125 | 0.254806 | 1.17451 | 0.0719474 | 6.98845e-05 | 0.0157249 | 0.000479381 | 1(Win) | true |
| simdjson (ondemand) | 16463.9 | 0.988676 | 6076.43ms | 16197085 | 80 | 6.88342e+09 | 938217 | 0.298962 | 0.309457 | 1.32914 | 0.0888035 | 0.000120816 | 0.0157682 | 0.000634365 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1847.47 | 0.139584 | 8610.39ms | 4212000 | 80 | 7.36857e+08 | 2.17425e+06 | 0.0930522 | 2.74231 | 11.4589 | 2.05248 | 0.0142257 | 0.0665785 | 0.00483036 | 1(Win) | true |
| simdjson (ondemand) | 1576.13 | 0.201769 | 9841.45ms | 4212000 | 40 | 1.0577e+09 | 2.54857e+06 | 0.686275 | 3.22061 | 13.524 | 2.36416 | 0.0104417 | 0.0664632 | 0.00575842 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1705.43 | 0.601058 | 9394.97ms | 4211999 | 30 | 6.01259e+09 | 2.35534e+06 | 0.499755 | 2.97917 | 12.3882 | 2.2687 | 0.0153292 | 0.0679282 | 0.00384127 | 1(Win) | true |
| simdjson (ondemand) | 1346.68 | 0.765733 | 5409.18ms | 4211999 | 80 | 4.17343e+10 | 2.9828e+06 | 0.53937 | 3.77908 | 15.595 | 2.79498 | 0.0105259 | 0.069809 | 0.00274283 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1460.2 | 0.836992 | 5053.08ms | 4212000 | 80 | 4.24116e+10 | 2.75091e+06 | 0.738569 | 3.46688 | 15.1241 | 2.90335 | 0.0147402 | 0.0666483 | 0.010184 | 1(Win) | true |
| simdjson (ondemand) | 1293.73 | 1.00213 | 5572.84ms | 4212000 | 40 | 3.87254e+10 | 3.10488e+06 | 1.18922 | 3.90735 | 16.6576 | 2.8979 | 0.0107331 | 0.0670996 | 0.00338313 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1459.25 | 0.179964 | 5065.32ms | 4211999 | 30 | 7.36228e+08 | 2.7527e+06 | 0.480576 | 3.45715 | 15.3424 | 2.96053 | 0.0153688 | 0.0678762 | 0.00375693 | 1(Win) | true |
| simdjson (ondemand) | 1171.04 | 0.158572 | 6110.35ms | 4211999 | 40 | 1.18344e+09 | 3.43018e+06 | 0.499379 | 4.3275 | 18.7287 | 3.32871 | 0.011008 | 0.0701314 | 0.00596485 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1450.51 | 0.168999 | 9961.84ms | 4525120 | 160 | 4.04488e+09 | 2.97515e+06 | 0.0834424 | 3.48298 | 16.5879 | 2.84081 | 0.0105867 | 0.0784393 | 0.00352907 | 1(Win) | true |
| simdjson (ondemand) | 1316.25 | 0.108855 | 5368.04ms | 4525120 | 40 | 5.095e+08 | 3.27863e+06 | 0.27943 | 3.84921 | 17.2028 | 2.62223 | 0.0144185 | 0.0774806 | 0.00557752 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1261.98 | 0.89053 | 5793.32ms | 4525119 | 30 | 2.78209e+10 | 3.41961e+06 | 0.33316 | 4.01468 | 18.8086 | 3.39521 | 0.0109471 | 0.0775284 | 0.00768154 | 1(Win) | true |
| simdjson (ondemand) | 913.961 | 1.30358 | 7614.99ms | 4525119 | 80 | 3.03088e+11 | 4.72174e+06 | 0.654045 | 5.56407 | 21.744 | 3.56361 | 0.0170871 | 0.0933936 | 0.00791917 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 802.641 | 0.453179 | 8650.34ms | 4525120 | 80 | 4.7495e+10 | 5.37662e+06 | 1.69541 | 6.3197 | 31.3195 | 6.31957 | 0.0162508 | 0.0778547 | 0.00910059 | 1(Win) | true |
| simdjson (ondemand) | 599.852 | 0.680561 | 5318.22ms | 4525120 | 30 | 7.19163e+10 | 7.19426e+06 | 0.789384 | 8.47485 | 42.9346 | 8.0864 | 0.0247395 | 0.0779742 | 0.0085729 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 793.786 | 0.894143 | 8590.43ms | 4525119 | 30 | 7.08906e+10 | 5.43659e+06 | 0.172345 | 6.40307 | 31.0507 | 6.32069 | 0.0161555 | 0.0778183 | 0.00877604 | 1(Win) | true |
| simdjson (ondemand) | 526.682 | 0.18309 | 5965.24ms | 4525119 | 30 | 6.75167e+09 | 8.19372e+06 | 0.675269 | 9.61712 | 47.4756 | 9.02779 | 0.0271977 | 0.09431 | 0.00867098 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1227.76 | 0.10798 | 5341.61ms | 4203059 | 80 | 9.94207e+08 | 3.26477e+06 | 1.19627 | 4.11913 | 17.8304 | 3.28646 | 0.0182796 | 0.0888779 | 0.00686289 | 1(Win) | true |
| simdjson (ondemand) | 954.555 | 0.706447 | 6709.3ms | 4203059 | 40 | 3.52005e+10 | 4.19918e+06 | 0.238249 | 5.27789 | 19.9861 | 3.46943 | 0.025161 | 0.0882546 | 0.010088 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1104.3 | 0.461565 | 5882.41ms | 4203058 | 80 | 2.24549e+10 | 3.62976e+06 | 0.641998 | 4.59119 | 19.9748 | 3.82216 | 0.0196057 | 0.0884667 | 0.00934725 | 1(Win) | true |
| simdjson (ondemand) | 817.206 | 0.141832 | 7875.95ms | 4203058 | 30 | 1.45191e+09 | 4.90494e+06 | 0.035672 | 6.20949 | 24.2756 | 4.35384 | 0.0265182 | 0.104892 | 0.0123321 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 781.104 | 0.965145 | 8114.21ms | 4203059 | 30 | 7.35901e+10 | 5.13164e+06 | 0.9807 | 6.51769 | 27.6601 | 5.54107 | 0.0253115 | 0.0883215 | 0.0100705 | 1(Win) | true |
| simdjson (ondemand) | 725.286 | 0.666087 | 8770.28ms | 4203059 | 40 | 5.42043e+10 | 5.52658e+06 | 0.279452 | 6.99725 | 28.3948 | 5.06159 | 0.0274623 | 0.0880782 | 0.0142582 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 736.052 | 0.454068 | 8598.08ms | 4203058 | 80 | 4.89153e+10 | 5.44574e+06 | 0.123883 | 6.8814 | 29.801 | 6.07565 | 0.0270871 | 0.0890527 | 0.00914544 | 1(Win) | true |
| simdjson (ondemand) | 627.659 | 0.443356 | 10008.9ms | 4203058 | 80 | 6.41325e+10 | 6.38619e+06 | 0.2482 | 8.11867 | 32.6837 | 5.94564 | 0.0289624 | 0.104274 | 0.0112778 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1710.63 | 0.892519 | 7650.1ms | 4197496 | 80 | 3.48974e+10 | 2.3401e+06 | 0.166736 | 2.95351 | 15.4784 | 2.85201 | 0.000470724 | 0.0819059 | 0.0022422 | 1(Win) | true |
| simdjson (ondemand) | 1351.63 | 0.873323 | 9513.77ms | 4197496 | 160 | 1.07037e+11 | 2.96164e+06 | 0.319213 | 3.74715 | 18.5261 | 2.73403 | 0.00565131 | 0.0814562 | 0.00397221 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1428.49 | 1.40929 | 9002.96ms | 4197495 | 40 | 6.23859e+10 | 2.80228e+06 | 1.17087 | 3.54402 | 17.7657 | 3.38961 | 0.000664712 | 0.0845046 | 0.00424889 | 1(Win) | true |
| simdjson (ondemand) | 1051.51 | 1.08126 | 5969.24ms | 4197495 | 80 | 1.35551e+11 | 3.80695e+06 | 1.19139 | 4.84652 | 23.2609 | 3.71908 | 0.00594175 | 0.103238 | 0.004933 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 918.189 | 1.13544 | 6698.58ms | 4197496 | 40 | 9.80176e+10 | 4.35972e+06 | 0.33073 | 5.49525 | 26.9149 | 5.51385 | 0.000794533 | 0.0822276 | 0.00612753 | 1(Win) | true |
| simdjson (ondemand) | 747.178 | 0.700896 | 8256.35ms | 4197496 | 80 | 1.12805e+11 | 5.35755e+06 | 0.570384 | 6.7674 | 34.5338 | 5.38612 | 0.00850425 | 0.0818827 | 0.00668518 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 947.557 | 1.29152 | 6540.11ms | 4197495 | 30 | 8.93083e+10 | 4.22459e+06 | 0.431996 | 5.34621 | 27.2051 | 5.60614 | 0.00102148 | 0.0846677 | 0.00361267 | 1(Win) | true |
| simdjson (ondemand) | 639.714 | 0.551555 | 9583.8ms | 4197495 | 80 | 9.52962e+10 | 6.25755e+06 | 0.0489393 | 7.93193 | 39.2688 | 6.37123 | 0.00872534 | 0.103639 | 0.00778893 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1291.27 | 0.890663 | 5812.03ms | 4506447 | 80 | 7.02996e+10 | 3.32827e+06 | 0.159007 | 3.92083 | 15.8377 | 2.89712 | 0.0168539 | 0.080454 | 0.0119945 | 1(Win) | true |
| simdjson (ondemand) | 1035.14 | 1.374 | 7111.71ms | 4506447 | 30 | 9.76251e+10 | 4.15178e+06 | 1.97623 | 4.9117 | 18.1956 | 3.10547 | 0.0167829 | 0.0790671 | 0.0113274 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1175.42 | 1.39326 | 6182.8ms | 4506446 | 30 | 7.78517e+10 | 3.65629e+06 | 0.206871 | 4.30795 | 17.5071 | 3.3124 | 0.0196425 | 0.0811885 | 0.00710831 | 1(Win) | true |
| simdjson (ondemand) | 907.617 | 0.281875 | 7847.46ms | 4506446 | 80 | 1.42517e+10 | 4.73513e+06 | 1.44937 | 5.58409 | 21.5787 | 3.80993 | 0.01702 | 0.0864313 | 0.0124415 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 889.651 | 0.101018 | 8102.88ms | 4506447 | 80 | 1.90509e+09 | 4.83075e+06 | 0.173588 | 5.70386 | 26.3563 | 5.35491 | 0.015381 | 0.0809563 | 0.00582249 | 1(Win) | true |
| simdjson (ondemand) | 517.335 | 0.141541 | 6217.29ms | 4506447 | 30 | 4.14774e+09 | 8.30735e+06 | 0.705733 | 9.8497 | 43.5972 | 7.74267 | 0.0323564 | 0.0790361 | 0.0101628 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 889.615 | 0.143106 | 8073.91ms | 4506446 | 30 | 1.43383e+09 | 4.83095e+06 | 0.374121 | 5.72542 | 26.2142 | 5.36734 | 0.0157227 | 0.0813325 | 0.0031503 | 1(Win) | true |
| simdjson (ondemand) | 474.965 | 0.107768 | 6688.78ms | 4506446 | 40 | 3.80352e+09 | 9.04842e+06 | 0.0772185 | 10.6903 | 46.9802 | 8.44709 | 0.0325375 | 0.0867631 | 0.0161198 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1893.03 | 0.0845652 | 7314.32ms | 4219120 | 160 | 5.1693e+08 | 2.12551e+06 | 0.0611128 | 2.67772 | 9.30168 | 1.57728 | 0.0167494 | 0.0535976 | 0.00101161 | 1(Win) | true |
| simdjson (ondemand) | 1774.86 | 0.245268 | 7765.37ms | 4219120 | 160 | 4.94672e+09 | 2.26703e+06 | 0.368968 | 2.83565 | 9.92054 | 1.52641 | 0.0144645 | 0.0538469 | 0.00174332 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1773.94 | 0.144509 | 7771.54ms | 4219119 | 80 | 8.59505e+08 | 2.26821e+06 | 0.916511 | 2.87054 | 10.3254 | 1.83207 | 0.0162632 | 0.0531638 | 0.00291181 | 1(Win) | true |
| simdjson (ondemand) | 1496 | 0.141917 | 9104.32ms | 4219119 | 160 | 2.33114e+09 | 2.68962e+06 | 0.0770874 | 3.36275 | 11.9558 | 1.94835 | 0.0155895 | 0.0550912 | 0.00522736 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 755.449 | 0.278448 | 8356.25ms | 4219120 | 40 | 8.79795e+09 | 5.32619e+06 | 0.200376 | 6.71932 | 25.6531 | 4.71924 | 0.0230705 | 0.0545298 | 0.00354073 | 1(Win) | true |
| simdjson (ondemand) | 291.1 | 0.210586 | 9846.86ms | 4219120 | 40 | 3.38904e+10 | 1.38223e+07 | 0.171813 | 17.3774 | 70.1315 | 12.1605 | 0.0796225 | 0.0551001 | 0.0162161 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 757.923 | 0.217169 | 8317.66ms | 4219119 | 80 | 1.06336e+10 | 5.3088e+06 | 0.0983594 | 6.71825 | 25.5494 | 4.72308 | 0.0220553 | 0.0546553 | 0.00449884 | 1(Win) | true |
| simdjson (ondemand) | 283.98 | 0.1318 | 10150ms | 4219119 | 30 | 1.04621e+10 | 1.41688e+07 | 0.506158 | 17.8215 | 72.1678 | 12.5827 | 0.081434 | 0.0556729 | 0.0144372 | 2(Loss) | true |
