# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the Clang 23.1.6 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier (Generic): [fececf7](https://github.com/nihilai-collective/Jsonifier/commit/fececf7)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `NEON` |
| **simdjson (ondemand)** | `arm64` |

> SIMD paths above are whatever each library picked at build/run time on this box.

> **Sampling (Apple M2 Pro (Virtual)-NEON):**  
> Iterations: 100 → 200 → 400 ... (max 100000), doubling per epoch.  
> Window: last `max(iterations/10, 30)` samples (max 100000). Runs for 5s or until the cap.  
> Epoch used: lowest RSE + mean shift (1st epoch is just a fallback).  
> Converged = RSE ≤ 10% and mean shift ≤ 5%. Non-converged ones still get ranked.  
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

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 350.3 | 0.887566 | 343.615ms | 905 | 640 | 306054 | 2463.81 | 3.08724 | 1(Win) | true |
| simdjson (ondemand) | 246.449 | 0.931713 | 379.695ms | 905 | 320 | 340690 | 3502.05 | 0.302653 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 322.364 | 0.992628 | 260.602ms | 905 | 640 | 452018 | 2677.33 | 0.533915 | 1(Win) | true |
| simdjson (ondemand) | 238.975 | 0.32595 | 385.246ms | 905 | 2560 | 354760 | 3611.58 | 0.150342 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 422.644 | 0.705637 | 411.102ms | 1811 | 320 | 266073 | 4086.43 | 2.82491 | 1(Win) | true |
| simdjson (ondemand) | 262.939 | 0.295389 | 683.464ms | 1811 | 2560 | 963730 | 6568.47 | 1.33874 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 494.657 | 0.831333 | 370.432ms | 1811 | 320 | 269606 | 3491.52 | 0.883481 | 1(Win) | true |
| simdjson (ondemand) | 261.528 | 0.446621 | 645.531ms | 1811 | 1280 | 1.1135e+06 | 6603.89 | 3.26426 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 424.183 | 0.412992 | 277.879ms | 1313 | 1280 | 190247 | 2951.97 | 1.15348 | 1(Win) | true |
| simdjson (ondemand) | 247.958 | 0.288599 | 494.413ms | 1313 | 4890 | 1.03866e+06 | 5049.95 | 1.23987 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 510.656 | 0.40377 | 249.512ms | 1313 | 4890 | 479346 | 2452.09 | 1.98468 | 1(Win) | true |
| simdjson (ondemand) | 260.631 | 0.763275 | 470.692ms | 1313 | 320 | 430319 | 4804.4 | 2.73351 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 629.6 | 0.306912 | 667.551ms | 4215 | 1280 | 491477 | 6384.59 | 1.40128 | 1(Win) | true |
| Jsonifier (generic) | 528.548 | 1.56211 | 719.214ms | 4215 | 80 | 1.12912e+06 | 7605.25 | 3.91496 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 756.224 | 0.563692 | 644.208ms | 4215 | 1280 | 1.14918e+06 | 5315.53 | 1.07565 | 1(Win) | true |
| Jsonifier (generic) | 658.073 | 1.58575 | 662.676ms | 4215 | 80 | 750599 | 6108.35 | 0.288963 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 490.084 | 0.371366 | 263.035ms | 1213 | 40 | 3073.58 | 2360.43 | 0.449316 | 1(Win) | true |
| simdjson (ondemand) | 203.712 | 1.19579 | 549.514ms | 1213 | 160 | 737772 | 5678.64 | 2.46881 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 515.078 | 0.276888 | 249.284ms | 1213 | 2560 | 98997.5 | 2245.89 | 0.540194 | 1(Win) | true |
| simdjson (ondemand) | 238.451 | 2.17334 | 484.385ms | 1213 | 30 | 333502 | 4851.33 | 0.489536 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 922.48 | 0.393901 | 5198.8ms | 94653 | 640 | 9.50841e+07 | 97853.7 | 0.10833 | 1(Win) | true |
| simdjson (ondemand) | 740.536 | 0.207374 | 6460.42ms | 94653 | 2560 | 1.63578e+08 | 121896 | 0.701845 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1199.03 | 0.576964 | 5054.88ms | 94653 | 320 | 6.03751e+07 | 75284.5 | 2.01282 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 970.32 | 1.00224 | 6227ms | 94653 | 40 | 3.47733e+07 | 93029.2 | 5.2869 | -(Loss) | false |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1148.14 | 0.582993 | 5408.97ms | 124597 | 320 | 1.16495e+08 | 103494 | 0.798078 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1137.76 | 0.359984 | 6107.7ms | 124597 | 40 | 5.65378e+06 | 104438 | 0.0901719 | 1(Tie) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1417.4 | 0.208283 | 5061.51ms | 124597 | 2560 | 7.8051e+07 | 83833 | 3.18923 | 1(Win) | true |
| simdjson (ondemand) | 1188.18 | 0.652834 | 5875.93ms | 124597 | 320 | 1.36398e+08 | 100006 | 0.419793 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 701.946 | 0.762893 | 5908.48ms | 94653 | 160 | 1.53996e+08 | 128597 | 2.36307 | 1(Win) | true |
| simdjson (ondemand) | 395.959 | 0.597703 | 5479.37ms | 94653 | 160 | 2.97071e+08 | 227973 | 0.870391 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1013.13 | 0.216164 | 5505.51ms | 94653 | 640 | 2.37401e+07 | 89098.1 | 0.893006 | 1(Win) | true |
| simdjson (ondemand) | 500.76 | 0.481193 | 5126.99ms | 94653 | 320 | 2.40768e+08 | 180262 | 3.96139 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1007.4 | 0.699218 | 6247.53ms | 124597 | 320 | 2.17664e+08 | 117952 | 0.948773 | 1(Win) | true |
| simdjson (ondemand) | 585.158 | 0.570273 | 5131.1ms | 124597 | 320 | 4.29126e+08 | 203065 | 0.116523 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1199.28 | 0.580089 | 5996.61ms | 124597 | 320 | 1.0571e+08 | 99080.6 | 0.960455 | 1(Win) | true |
| simdjson (ondemand) | 756.941 | 0.0698987 | 9083.84ms | 124597 | 2560 | 3.08226e+07 | 156980 | 0.130837 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1806.57 | 0.300262 | 5112.6ms | 94653 | 40 | 900370 | 49966.7 | 0.271376 | 1(Win) | true |
| simdjson (ondemand) | 1389.39 | 0.201557 | 6783.6ms | 94653 | 320 | 5.48739e+06 | 64969.6 | 0.25012 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2076.8 | 0.153802 | 4864.57ms | 94653 | 1280 | 5.72023e+06 | 43465 | 0.00839685 | 1(Win) | true |
| simdjson (ondemand) | 1572.67 | 0.312249 | 6997.46ms | 94653 | 40 | 1.28485e+06 | 57397.8 | 0.224407 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1823.6 | 0.582089 | 6236.91ms | 124597 | 320 | 4.60349e+07 | 65159.7 | 0.0762735 | 1(Win) | true |
| simdjson (ondemand) | 1490.72 | 0.40095 | 7690.04ms | 124597 | 640 | 6.53708e+07 | 79709.9 | 0.461924 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2055.6 | 0.424841 | 5777.12ms | 124597 | 640 | 3.85986e+07 | 57805.5 | 1.40885 | 1(Win) | true |
| simdjson (ondemand) | 1733.1 | 1.26996 | 6960.1ms | 124597 | 80 | 6.0651e+07 | 68561.9 | 0.877448 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1470.88 | 0.107165 | 6203.95ms | 94653 | 2560 | 1.10729e+07 | 61370.3 | 0.331941 | 1(Win) | true |
| simdjson (ondemand) | 1193.87 | 0.222066 | 7650.53ms | 94653 | 80 | 2.25533e+06 | 75609.9 | 0.182364 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1694.05 | 0.313044 | 5849.24ms | 94653 | 80 | 2.22597e+06 | 53285.4 | 0.0763228 | 1(Win) | true |
| simdjson (ondemand) | 1306.99 | 0.0924655 | 7372.55ms | 94653 | 2560 | 1.04406e+07 | 69065.7 | 0.375605 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1832.82 | 0.0560094 | 6552.2ms | 124597 | 4890 | 6.44773e+06 | 64831.8 | 0.181336 | 1(Win) | true |
| simdjson (ondemand) | 1534.22 | 0.0602081 | 8135.65ms | 124597 | 4890 | 1.06331e+07 | 77450 | 0.38758 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2078.97 | 0.0477755 | 6563.86ms | 124597 | 30 | 22369.2 | 57155.7 | 0.102457 | 1(Win) | true |
| simdjson (ondemand) | 1692.25 | 0.172854 | 7560.97ms | 124597 | 320 | 4.71407e+06 | 70217.2 | 0.0701843 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 528.138 | 0.194996 | 5719.3ms | 2090234 | 80 | 4.3335e+09 | 3.7744e+06 | 0.156783 | 1(Win) | true |
| simdjson (ondemand) | 493.482 | 0.150289 | 6151.23ms | 2090234 | 30 | 1.10566e+09 | 4.03946e+06 | 0.00505869 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 612.823 | 0.157427 | 5681.13ms | 2090234 | 40 | 1.04892e+09 | 3.25282e+06 | 0.0245811 | 1(Win) | true |
| simdjson (ondemand) | 564.278 | 0.147409 | 6092.28ms | 2090234 | 80 | 2.1694e+09 | 3.53266e+06 | 0.347166 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1198.02 | 0.166051 | 6335.16ms | 5212421 | 30 | 1.42414e+09 | 4.1493e+06 | 0.366719 | 1(Win) | true |
| simdjson (ondemand) | 1142.86 | 0.19639 | 6548.4ms | 5212421 | 80 | 5.83746e+09 | 4.34959e+06 | 0.194288 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1364.03 | 0.131908 | 6363.12ms | 5212421 | 80 | 1.8487e+09 | 3.64431e+06 | 0.0732114 | 1(Win) | true |
| simdjson (ondemand) | 1298.54 | 0.237537 | 6619.33ms | 5212421 | 80 | 6.6149e+09 | 3.82811e+06 | 0.338327 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 498.936 | 0.10706 | 6133.77ms | 2090234 | 80 | 1.46366e+09 | 3.99531e+06 | 0.00309028 | 1(Win) | true |
| simdjson (ondemand) | 454.046 | 0.155966 | 6663.53ms | 2090234 | 30 | 1.40661e+09 | 4.39031e+06 | 0.168586 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 570.598 | 0.568658 | 6146.21ms | 2090234 | 30 | 1.184e+10 | 3.49353e+06 | 0.196404 | 1(Win) | true |
| simdjson (ondemand) | 514.491 | 0.186123 | 6762.13ms | 2090234 | 30 | 1.56012e+09 | 3.87451e+06 | 0.722607 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1125.05 | 0.213585 | 6710.56ms | 5212421 | 30 | 2.67174e+09 | 4.41841e+06 | 0.0752442 | 1(Win) | true |
| simdjson (ondemand) | 1048.22 | 0.355077 | 7456.99ms | 5212421 | 40 | 1.13418e+10 | 4.74229e+06 | 4.7688 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1258.94 | 0.794542 | 6780.8ms | 5212421 | 30 | 2.95274e+10 | 3.94853e+06 | 0.527791 | 1(Win) | true |
| simdjson (ondemand) | 1180.02 | 0.160597 | 7227.28ms | 5212421 | 40 | 1.83076e+09 | 4.21258e+06 | 0.632554 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4480.13 | 0.173897 | 5787.87ms | 2090234 | 160 | 9.57889e+07 | 444943 | 0.0349155 | 1(Win) | true |
| simdjson (ondemand) | 3266.55 | 0.128852 | 7858.98ms | 2090234 | 640 | 3.95707e+08 | 610248 | 0.185831 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4508.04 | 0.194504 | 5666.61ms | 2090234 | 40 | 2.95893e+07 | 442189 | 0.0521297 | 1(Win) | true |
| simdjson (ondemand) | 3369.69 | 0.254492 | 7829.82ms | 2090234 | 80 | 1.81321e+08 | 591568 | 0.244251 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6435.43 | 0.263047 | 9921.16ms | 5212421 | 40 | 1.65139e+08 | 772435 | 0.021848 | 1(Win) | true |
| simdjson (ondemand) | 5460.08 | 0.162659 | 5830.82ms | 5212421 | 160 | 3.50878e+08 | 910417 | 0.0417903 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5781.68 | 0.541667 | 5366.25ms | 5212421 | 320 | 6.94043e+09 | 859777 | 1.31779 | 1(Win) | true |
| simdjson (ondemand) | 5445.4 | 0.309203 | 5822.13ms | 5212421 | 160 | 1.27475e+09 | 912872 | 0.00798173 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3532.5 | 0.177193 | 7230.37ms | 2090234 | 640 | 6.3988e+08 | 564304 | 0.218654 | 1(Win) | true |
| simdjson (ondemand) | 2794.81 | 0.242526 | 9266.83ms | 2090234 | 320 | 9.57531e+08 | 713252 | 0.0685637 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3536.07 | 0.535065 | 7465.73ms | 2090234 | 40 | 3.63933e+08 | 563734 | 0.184313 | 1(Win) | true |
| simdjson (ondemand) | 2809.68 | 0.157574 | 9327.1ms | 2090234 | 160 | 1.9997e+08 | 709478 | 0.0666288 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5464.53 | 0.146217 | 5747.49ms | 5212421 | 320 | 5.66136e+08 | 909676 | 0.769689 | 1(Win) | true |
| simdjson (ondemand) | 4764.08 | 0.171429 | 6736.42ms | 5212421 | 320 | 1.02386e+09 | 1.04342e+06 | 0.200942 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5506.9 | 0.231601 | 5849.17ms | 5212421 | 40 | 1.74826e+08 | 902677 | 0.00349227 | 1(Win) | true |
| simdjson (ondemand) | 4751.41 | 0.165382 | 6579.42ms | 5212421 | 320 | 9.57989e+08 | 1.04621e+06 | 0.205351 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 962.326 | 0.165464 | 6548.11ms | 500299 | 40 | 2.69204e+07 | 495801 | 0.25043 | 1(Win) | true |
| simdjson (ondemand) | 848.444 | 0.222244 | 7218.21ms | 500299 | 80 | 1.24958e+08 | 562350 | 0.643568 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1040.19 | 0.126344 | 6345.27ms | 500299 | 320 | 1.07472e+08 | 458688 | 0.131798 | 1(Win) | true |
| simdjson (ondemand) | 912.326 | 0.098353 | 7161.79ms | 500299 | 640 | 1.69322e+08 | 522973 | 0.0211492 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1921.79 | 0.102308 | 7374.58ms | 1151920 | 320 | 1.09446e+08 | 571631 | 0.117236 | 1(Win) | true |
| simdjson (ondemand) | 1769.31 | 0.0986631 | 8032.34ms | 1151920 | 320 | 1.20088e+08 | 620897 | 0.0436652 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2069.34 | 0.249914 | 7282.01ms | 1151920 | 30 | 5.2806e+07 | 530872 | 0.528792 | 1(Win) | true |
| simdjson (ondemand) | 1893.46 | 0.197135 | 8141.63ms | 1151920 | 30 | 3.92446e+07 | 580185 | 0.00645813 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 544.371 | 0.205368 | 5642.31ms | 500299 | 80 | 2.59194e+08 | 876466 | 0.204487 | 1(Win) | true |
| simdjson (ondemand) | 303.64 | 0.11171 | 10004.7ms | 500299 | 320 | 9.85999e+08 | 1.57134e+06 | 0.0464248 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 569.821 | 0.182968 | 5568.53ms | 500299 | 80 | 1.87768e+08 | 837319 | 0.0400022 | 1(Win) | true |
| simdjson (ondemand) | 311.031 | 0.404683 | 10021ms | 500299 | 30 | 1.15612e+09 | 1.534e+06 | 0.35217 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1125.59 | 0.359027 | 6237.34ms | 1151920 | 40 | 4.91137e+08 | 975987 | 0.10418 | 1(Win) | true |
| simdjson (ondemand) | 664.816 | 0.16529 | 5235.05ms | 1151920 | 160 | 1.1936e+09 | 1.65242e+06 | 0.074232 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1171.6 | 0.252834 | 6128.13ms | 1151920 | 320 | 1.7985e+09 | 937658 | 0.0452899 | 1(Win) | true |
| simdjson (ondemand) | 681.635 | 0.273069 | 5185.88ms | 1151920 | 30 | 5.8104e+08 | 1.61165e+06 | 0.00560058 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3193.1 | 0.18611 | 7506.53ms | 500299 | 640 | 4.94942e+07 | 149423 | 1.52468 | 1(Win) | true |
| simdjson (ondemand) | 3016.52 | 0.0695507 | 8191.44ms | 500299 | 2560 | 3.09806e+07 | 158170 | 0.00389277 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3386.72 | 0.13001 | 7340.63ms | 500299 | 640 | 2.14702e+07 | 140880 | 0.0671099 | 1(Win) | true |
| simdjson (ondemand) | 3040.01 | 0.0883661 | 8095.93ms | 500299 | 1280 | 2.46201e+07 | 156947 | 0.0203603 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5142.16 | 0.113132 | 5514.02ms | 1151920 | 640 | 3.73854e+07 | 213637 | 0.0780362 | 1(Win) | true |
| simdjson (ondemand) | 5009.97 | 0.115445 | 5617.7ms | 1151920 | 640 | 4.10114e+07 | 219274 | 0.353863 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5168.72 | 0.12166 | 5529.98ms | 1151920 | 640 | 4.27908e+07 | 212539 | 0.252765 | 1(Win) | true |
| simdjson (ondemand) | 5080.22 | 0.267129 | 5677.1ms | 1151920 | 30 | 1.00102e+07 | 216242 | 0.190994 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1978.73 | 0.213222 | 6147.04ms | 500299 | 320 | 8.45863e+07 | 241125 | 0.0433806 | 1(Win) | true |
| simdjson (ondemand) | 1791.08 | 0.0848503 | 6987.01ms | 500299 | 1280 | 6.53955e+07 | 266389 | 0.824129 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2007.65 | 0.17946 | 6235.27ms | 500299 | 80 | 1.45515e+07 | 237652 | 0.0806766 | 1(Win) | true |
| simdjson (ondemand) | 1797.72 | 0.0903021 | 6860.45ms | 500299 | 1280 | 7.35229e+07 | 265405 | 0.0710426 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3519.9 | 0.0764624 | 8074ms | 1151920 | 1280 | 7.28938e+07 | 312099 | 0.24448 | 1(Win) | true |
| simdjson (ondemand) | 3371.79 | 0.127073 | 8438.09ms | 1151920 | 320 | 5.48508e+07 | 325808 | 0.00133995 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3534.29 | 0.178571 | 8033.79ms | 1151920 | 320 | 9.85849e+07 | 310828 | 0.222286 | 1(Win) | true |
| simdjson (ondemand) | 3381.69 | 0.141238 | 8380.42ms | 1151920 | 320 | 6.73647e+07 | 324854 | 0.0355988 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1286.7 | 0.0325497 | 4225.19ms | 56369 | 80 | 14794.9 | 41779.6 | 0.0432515 | 1(Win) | true |
| simdjson (ondemand) | 1027.29 | 0.0659579 | 5356.08ms | 56369 | 4890 | 5.82557e+06 | 52329.7 | 0.22134 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1436.01 | 0.130903 | 3850.13ms | 56369 | 1280 | 3.07382e+06 | 37435.4 | 0.241306 | 1(Win) | true |
| simdjson (ondemand) | 1128.75 | 0.156889 | 4883.47ms | 56369 | 320 | 1.78658e+06 | 47625.9 | 0.00524241 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1775.26 | 0.0754041 | 4626.02ms | 83958 | 4890 | 5.65587e+06 | 45102.4 | 0.0767479 | 1(Win) | true |
| simdjson (ondemand) | 1495.22 | 0.0487225 | 5577.22ms | 83958 | 30 | 20422 | 53549.9 | 0.0237728 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1976.32 | 0.155161 | 4229.47ms | 83958 | 320 | 1.26451e+06 | 40514 | 0.0287021 | 1(Win) | true |
| simdjson (ondemand) | 1616.43 | 0.112871 | 5054.04ms | 83958 | 1280 | 4.00113e+06 | 49534.1 | 0.0504779 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 648.55 | 0.0555505 | 8381.13ms | 56369 | 4890 | 1.03676e+07 | 82889 | 0.048728 | 1(Win) | true |
| simdjson (ondemand) | 145.46 | 0.0687588 | 9532.6ms | 56369 | 1280 | 8.26538e+07 | 369571 | 0.0702506 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 693.353 | 0.172754 | 8256.72ms | 56369 | 160 | 2.87044e+06 | 77532.9 | 0.100019 | 1(Win) | true |
| simdjson (ondemand) | 147.494 | 0.0950306 | 9594.94ms | 56369 | 1280 | 1.53556e+08 | 364473 | 0.251805 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 850.934 | 0.0912658 | 9526.99ms | 83958 | 1280 | 9.43972e+06 | 94094.9 | 0.189742 | 1(Win) | true |
| simdjson (ondemand) | 212.238 | 0.0999335 | 9828.24ms | 83958 | 1280 | 1.81932e+08 | 377258 | 0.033614 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 893.225 | 0.0626946 | 9190.09ms | 83958 | 2560 | 8.08544e+06 | 89639.9 | 0.0679607 | 1(Win) | true |
| simdjson (ondemand) | 215.952 | 0.109496 | 9586.65ms | 83958 | 640 | 1.05483e+08 | 370770 | 0.365013 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2193.58 | 0.111228 | 2461.58ms | 56369 | 2560 | 1.90214e+06 | 24506.8 | 0.011303 | 1(Win) | true |
| simdjson (ondemand) | 1757.91 | 0.142435 | 3060.24ms | 56369 | 1280 | 2.42844e+06 | 30580.4 | 0.0871633 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2420.31 | 0.0234362 | 2302.43ms | 56369 | 80 | 2167.71 | 22211 | 0.118887 | 1(Win) | true |
| simdjson (ondemand) | 1891.59 | 0.0683577 | 2999.25ms | 56369 | 4890 | 1.84549e+06 | 28419.3 | 0.0205872 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2858.28 | 0.126213 | 2832.54ms | 83958 | 640 | 800016 | 28012.8 | 0.0605828 | 1(Win) | true |
| simdjson (ondemand) | 2486.83 | 0.0403814 | 3348.25ms | 83958 | 40 | 6761.69 | 32197 | 0.085329 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3075.1 | 0.0935797 | 2664.46ms | 83958 | 4890 | 2.90321e+06 | 26037.7 | 0.0921621 | 1(Win) | true |
| simdjson (ondemand) | 2650.33 | 0.0877656 | 3091.74ms | 83958 | 2560 | 1.79976e+06 | 30210.8 | 0.187858 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1714.26 | 0.108958 | 3145.14ms | 56369 | 2560 | 2.98871e+06 | 31359.1 | 0.155795 | 1(Win) | true |
| simdjson (ondemand) | 966.019 | 0.0820607 | 5576.03ms | 56369 | 2560 | 5.3385e+06 | 55648.6 | 0.125932 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1831.29 | 0.0913878 | 3089.54ms | 56369 | 2560 | 1.8424e+06 | 29355.1 | 0.0777901 | 1(Win) | true |
| simdjson (ondemand) | 1006.63 | 0.0545471 | 5508.82ms | 56369 | 4890 | 4.14946e+06 | 53403.5 | 0.0304481 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2263.57 | 0.0917553 | 3546.33ms | 83958 | 2560 | 2.69674e+06 | 35372.7 | 0.0436416 | 1(Win) | true |
| simdjson (ondemand) | 1405.02 | 0.0622799 | 5918.03ms | 83958 | 30 | 37790.1 | 56987.5 | 0.00959366 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2436.65 | 0.145618 | 3375.52ms | 83958 | 320 | 732693 | 32860.2 | 0.075291 | 1(Win) | true |
| simdjson (ondemand) | 1449.16 | 0.078149 | 5741.77ms | 83958 | 2560 | 4.77287e+06 | 55251.8 | 0.0719455 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1227.44 | 0.0411619 | 4194.84ms | 53331 | 30 | 8727.07 | 41436 | 0.150688 | 1(Win) | true |
| simdjson (ondemand) | 725.931 | 0.302414 | 6318.49ms | 53331 | 1280 | 5.74622e+07 | 70062.3 | 0.286655 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1494.92 | 0.0552818 | 3939.47ms | 53331 | 30 | 10612.3 | 34022.2 | 0.147081 | 1(Win) | true |
| simdjson (ondemand) | 942.432 | 0.148731 | 6059.86ms | 53331 | 320 | 2.06163e+06 | 53967.2 | 0.0208098 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1389.45 | 0.10296 | 4499.34ms | 65103 | 1280 | 2.70938e+06 | 44684.7 | 0.0216179 | 1(Win) | true |
| simdjson (ondemand) | 987.011 | 0.0547006 | 6381.08ms | 65103 | 30 | 35519.3 | 62904.1 | 0.0731267 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1666.38 | 0.102879 | 4284.59ms | 65103 | 1280 | 1.8807e+06 | 37258.7 | 0.00795473 | 1(Win) | true |
| simdjson (ondemand) | 1112.6 | 0.0743956 | 6164.2ms | 65103 | 4890 | 8.42799e+06 | 55803.4 | 0.439419 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 923.554 | 0.0577961 | 5513.29ms | 53331 | 4890 | 4.95383e+06 | 55070.3 | 0.136402 | 1(Win) | true |
| simdjson (ondemand) | 341.522 | 0.260786 | 7761.43ms | 53331 | 320 | 4.82658e+07 | 148923 | 0.00969976 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1076.3 | 0.105377 | 5353.76ms | 53331 | 2560 | 6.34781e+06 | 47254.8 | 0.225382 | 1(Win) | true |
| simdjson (ondemand) | 364.089 | 0.131336 | 7524.33ms | 53331 | 640 | 2.15422e+07 | 139692 | 0.181767 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1045.48 | 0.0243772 | 6240.04ms | 65103 | 40 | 8383.02 | 59386.4 | 0.34904 | 1(Win) | true |
| simdjson (ondemand) | 419.26 | 0.1142 | 7604.14ms | 65103 | 640 | 1.8304e+07 | 148087 | 0.0851086 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1198.16 | 0.0954341 | 5817.34ms | 65103 | 2560 | 6.26065e+06 | 51818.7 | 0.211069 | 1(Win) | true |
| simdjson (ondemand) | 449.784 | 0.196344 | 7525.44ms | 65103 | 80 | 5.87651e+06 | 138037 | 0.0399961 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5655.84 | 0.0522894 | 912.868ms | 53331 | 40 | 884.408 | 8992.55 | 0.0357576 | 1(Win) | true |
| simdjson (ondemand) | 4341.56 | 0.124494 | 1174.45ms | 53331 | 2560 | 544506 | 11714.8 | 0.0061417 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5948.59 | 0.0677263 | 874.966ms | 53331 | 30 | 1005.93 | 8550 | 0.000389862 | 1(Win) | true |
| simdjson (ondemand) | 4563.18 | 0.0638833 | 1188.6ms | 53331 | 30 | 1520.97 | 11145.8 | 0.0619449 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5616.08 | 0.117326 | 1146.15ms | 65103 | 4890 | 822690 | 11055.2 | 0.623791 | 1(Win) | true |
| simdjson (ondemand) | 4857.02 | 0.0915211 | 1286.94ms | 65103 | 4890 | 669289 | 12783 | 0.0235615 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5948.45 | 0.0377041 | 1066.32ms | 65103 | 40 | 619.487 | 10437.5 | 0.052962 | 1(Win) | true |
| simdjson (ondemand) | 4990.2 | 0.150907 | 1263.3ms | 65103 | 1280 | 451224 | 12441.8 | 0.635007 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4258.08 | 0.0482791 | 1208.75ms | 53331 | 30 | 997.633 | 11944.4 | 0.197748 | 1(Win) | true |
| simdjson (ondemand) | 2661.99 | 0.209461 | 1967.62ms | 53331 | 1280 | 2.05004e+06 | 19106.1 | 0.161272 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4455.75 | 0.0567882 | 1166.56ms | 53331 | 40 | 1680.72 | 11414.5 | 0.0185401 | 1(Win) | true |
| simdjson (ondemand) | 2757.09 | 0.205267 | 1866.98ms | 53331 | 1280 | 1.83529e+06 | 18447.1 | 0.425463 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4445.37 | 0.0293285 | 1416.45ms | 65103 | 80 | 1342.32 | 13966.7 | 0.0230065 | 1(Win) | true |
| simdjson (ondemand) | 3065.47 | 0.133171 | 2025.2ms | 65103 | 2560 | 1.86236e+06 | 20253.7 | 0.144677 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4554.71 | 0.128437 | 1372.92ms | 65103 | 4890 | 1.4989e+06 | 13631.4 | 0.0700117 | 1(Win) | true |
| simdjson (ondemand) | 3181.69 | 0.118713 | 1990.13ms | 65103 | 30 | 16099.1 | 19513.8 | 0.113895 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 906.928 | 0.0956052 | 1305.66ms | 11812 | 4890 | 689561 | 12420.8 | 0.25515 | 1(Win) | true |
| simdjson (ondemand) | 815.025 | 0.137709 | 1399.27ms | 11812 | 640 | 231851 | 13821.4 | 0.0431129 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 957.738 | 0.0929084 | 1200.35ms | 11812 | 4890 | 583945 | 11761.9 | 0.271985 | 1(Win) | true |
| simdjson (ondemand) | 856.917 | 0.0785955 | 1345.43ms | 11812 | 30 | 3202.48 | 13145.7 | 0.106638 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1708.23 | 0.0834653 | 1509.36ms | 25388 | 30 | 4198.52 | 14173.6 | 0.088349 | 1(Win) | true |
| simdjson (ondemand) | 1638.65 | 0.0495161 | 1596.81ms | 25388 | 80 | 4282.23 | 14775.5 | 0.0180164 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1786.14 | 0.0783677 | 1389.15ms | 25388 | 30 | 3385.5 | 13555.4 | 0.0417862 | 1(Win) | true |
| simdjson (ondemand) | 1712.22 | 0.0630299 | 1453.8ms | 25388 | 40 | 3177.53 | 14140.6 | 0.0372311 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 673.309 | 0.0799337 | 1702.5ms | 11812 | 30 | 5365.36 | 16730.5 | 0.00796884 | 1(Win) | true |
| simdjson (ondemand) | 553.239 | 0.103795 | 2085.07ms | 11812 | 2560 | 1.14345e+06 | 20361.5 | 0.195341 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 698.107 | 0.0629712 | 1659.44ms | 11812 | 30 | 3097.48 | 16136.2 | 0.0769931 | 1(Win) | true |
| simdjson (ondemand) | 574.166 | 0.21365 | 2056.39ms | 11812 | 320 | 562248 | 19619.4 | 0.0893881 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1291.51 | 0.111464 | 1887.35ms | 25388 | 40 | 17465.7 | 18746.9 | 0.139595 | 1(Win) | true |
| simdjson (ondemand) | 1147.82 | 0.0659011 | 2133.62ms | 25388 | 80 | 15459.2 | 21093.8 | 0.0880997 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1347.08 | 0.039415 | 1845.9ms | 25388 | 30 | 1505.62 | 17973.6 | 0.116789 | 1(Win) | true |
| simdjson (ondemand) | 1173.98 | 0.113594 | 2083.64ms | 25388 | 2560 | 1.40502e+06 | 20623.7 | 0.16057 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1565.46 | 0.0347599 | 730.853ms | 11812 | 160 | 1001.01 | 7195.83 | 0.000955423 | 1(Win) | true |
| simdjson (ondemand) | 1437.1 | 0.14022 | 792.178ms | 11812 | 40 | 4832.25 | 7838.55 | 0.0125464 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1622.86 | 0.135453 | 750.438ms | 11812 | 4890 | 432284 | 6941.32 | 0.857683 | 1(Win) | true |
| simdjson (ondemand) | 1517.86 | 0.178605 | 767.974ms | 11812 | 1280 | 224894 | 7421.49 | 0.0016948 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2762.27 | 0.0664685 | 891.454ms | 25388 | 30 | 1018.3 | 8765.2 | 0.0627875 | 1(Win) | true |
| simdjson (ondemand) | 2746.31 | 0.0522762 | 894.072ms | 25388 | 80 | 1699.24 | 8816.15 | 0.0172948 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2858.26 | 0.0711564 | 872.486ms | 25388 | 30 | 1089.94 | 8470.83 | 0.115036 | 1(Win) | true |
| simdjson (ondemand) | 2847.28 | 0.115189 | 870.382ms | 25388 | 4890 | 469168 | 8503.51 | 0.0569414 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1301.7 | 0.108975 | 869.183ms | 11812 | 4890 | 434904 | 8653.93 | 0.284437 | 1(Win) | true |
| simdjson (ondemand) | 1172.06 | 0.106711 | 996.747ms | 11812 | 30 | 3155.64 | 9611.13 | 0.0142176 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1365.19 | 0.0782966 | 851.058ms | 11812 | 30 | 1252.19 | 8251.47 | 0.119313 | 1(Win) | true |
| simdjson (ondemand) | 1218.7 | 0.0691721 | 955.182ms | 11812 | 80 | 3270.45 | 9243.31 | 0.0628438 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2380.08 | 0.177197 | 1028.28ms | 25388 | 640 | 207953 | 10172.7 | 0.0519274 | 1(Win) | true |
| simdjson (ondemand) | 2285.17 | 0.0614377 | 1074.82ms | 25388 | 80 | 3389.85 | 10595.2 | 0.0916346 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2483.81 | 0.0530666 | 1010.24ms | 25388 | 40 | 1070.35 | 9747.9 | 0.0639863 | 1(Win) | true |
| simdjson (ondemand) | 2347.28 | 0.115138 | 1052.75ms | 25388 | 4890 | 689714 | 10314.9 | 0.0113714 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1272.59 | 0.175529 | 8440.06ms | 108313 | 320 | 6.49573e+06 | 81169.1 | 0.0849373 | 1(Win) | true |
| simdjson (ondemand) | 1109.13 | 0.184734 | 9437.93ms | 108313 | 320 | 9.47189e+06 | 93131.5 | 0.00486855 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1373.9 | 0.101387 | 7815.61ms | 108313 | 1280 | 7.43755e+06 | 75184.3 | 0.168991 | 1(Win) | true |
| simdjson (ondemand) | 1185.87 | 0.299989 | 9121.12ms | 108313 | 80 | 5.46248e+06 | 87105.3 | 0.115007 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1879.22 | 0.242976 | 9382.73ms | 183677 | 40 | 2.05184e+06 | 93213.4 | 0.119511 | 1(Win) | true |
| simdjson (ondemand) | 1786.95 | 0.0948725 | 5080.77ms | 183677 | 1280 | 1.10707e+07 | 98026 | 0.0245435 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1990.45 | 0.107819 | 9086.73ms | 183677 | 2560 | 2.30482e+07 | 88004.2 | 0.0245072 | 1(Win) | true |
| simdjson (ondemand) | 1896.27 | 0.0635014 | 9543.43ms | 183677 | 4890 | 1.68262e+07 | 92375.3 | 0.0341931 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 545.68 | 0.083451 | 9747.47ms | 108313 | 1280 | 3.19418e+07 | 189297 | 0.00872191 | 1(Win) | true |
| simdjson (ondemand) | 160.073 | 0.126747 | 8192.65ms | 108313 | 640 | 4.28135e+08 | 645302 | 0.292964 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 566.898 | 0.17985 | 9574.81ms | 108313 | 80 | 8.59133e+06 | 182211 | 0.118164 | 1(Win) | true |
| simdjson (ondemand) | 161.469 | 0.191954 | 8265.94ms | 108313 | 160 | 2.41266e+08 | 639722 | 0.946945 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 833.497 | 0.172824 | 5450.73ms | 183677 | 80 | 1.05536e+07 | 210160 | 0.202316 | 1(Win) | true |
| simdjson (ondemand) | 271.698 | 0.163039 | 8263.71ms | 183677 | 160 | 1.76781e+08 | 644715 | 0.0208188 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 860.049 | 0.218976 | 5306.32ms | 183677 | 30 | 5.96732e+06 | 203672 | 0.0149937 | 1(Win) | true |
| simdjson (ondemand) | 274.313 | 0.132533 | 8216.15ms | 183677 | 320 | 2.29199e+08 | 638569 | 0.0067314 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3343.34 | 0.0591412 | 3120.29ms | 108313 | 40 | 13354.9 | 30895.8 | 0.0406368 | 1(Win) | true |
| simdjson (ondemand) | 2707.8 | 0.0757755 | 3831.22ms | 108313 | 4890 | 4.08598e+06 | 38147.4 | 0.281605 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3498.21 | 0.058138 | 3046.43ms | 108313 | 40 | 11788.3 | 29528.1 | 0.0416097 | 1(Win) | true |
| simdjson (ondemand) | 2834.53 | 0.0860956 | 3704.47ms | 108313 | 30 | 29531.2 | 36441.7 | 0.0266249 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4462.51 | 0.075086 | 3988.34ms | 183677 | 4890 | 4.24795e+06 | 39253.3 | 0.0142726 | 1(Win) | true |
| simdjson (ondemand) | 4101.91 | 0.118903 | 4334.65ms | 183677 | 1280 | 3.30015e+06 | 42704 | 0.0096915 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4646.53 | 0.0632759 | 3838.31ms | 183677 | 30 | 17070.6 | 37698.7 | 0.21417 | 1(Win) | true |
| simdjson (ondemand) | 4203.4 | 0.200261 | 4181.31ms | 183677 | 640 | 4.45739e+06 | 41673 | 0.0391294 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2452.04 | 0.0771865 | 4212.32ms | 108313 | 4890 | 5.17008e+06 | 42126.3 | 0.0224605 | 1(Win) | true |
| simdjson (ondemand) | 1693.84 | 0.0866479 | 6110.16ms | 108313 | 2560 | 7.14783e+06 | 60983.1 | 0.146629 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2565.45 | 0.0388824 | 4212.97ms | 108313 | 30 | 7352.96 | 40264.1 | 0.0513015 | 1(Win) | true |
| simdjson (ondemand) | 1733.08 | 0.0691153 | 6025.04ms | 108313 | 4890 | 8.29812e+06 | 59602 | 0.0818287 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3422.69 | 0.229622 | 5166.29ms | 183677 | 160 | 2.20963e+06 | 51178.4 | 0.137123 | 1(Win) | true |
| simdjson (ondemand) | 2658.3 | 0.0757034 | 6665.49ms | 183677 | 2560 | 6.37051e+06 | 65894.9 | 0.107294 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3536.14 | 0.0670628 | 4996.35ms | 183677 | 4890 | 5.39663e+06 | 49536.5 | 0.270211 | 1(Win) | true |
| simdjson (ondemand) | 2706.52 | 0.0955129 | 6496.3ms | 183677 | 2560 | 9.78251e+06 | 64720.7 | 0.233237 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 432.012 | 0.312232 | 6092.43ms | 1834197 | 80 | 1.27863e+10 | 4.04902e+06 | 0.945853 | 1(Win) | true |
| simdjson (ondemand) | 414.387 | 0.16868 | 6360.99ms | 1834197 | 40 | 2.02799e+09 | 4.22124e+06 | 0.284029 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 474.15 | 0.208215 | 6097.8ms | 1834197 | 30 | 1.77013e+09 | 3.68918e+06 | 0.604337 | 1(Win) | true |
| simdjson (ondemand) | 449.455 | 0.208737 | 6396.08ms | 1834197 | 30 | 1.97989e+09 | 3.89189e+06 | 0.375618 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1519.33 | 0.227109 | 7048.58ms | 7351818 | 40 | 4.39354e+09 | 4.6147e+06 | 0.188173 | 1(Win) | true |
| simdjson (ondemand) | 1467.46 | 0.165367 | 7293.3ms | 7351818 | 30 | 1.87274e+09 | 4.77781e+06 | 0.0917437 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1639.74 | 0.162202 | 6915.82ms | 7351818 | 80 | 3.84807e+09 | 4.27582e+06 | 0.136674 | 1(Win) | true |
| simdjson (ondemand) | 1563.11 | 0.361227 | 7266.18ms | 7351818 | 40 | 1.05009e+10 | 4.48543e+06 | 0.0767696 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 293.139 | 0.297696 | 9005.15ms | 1834197 | 40 | 1.26227e+10 | 5.96723e+06 | 0.362627 | 1(Win) | true |
| simdjson (ondemand) | 193.19 | 0.165702 | 6399.6ms | 1834197 | 30 | 6.75306e+09 | 9.05442e+06 | 0.157043 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 310.938 | 0.226582 | 8957.43ms | 1834197 | 40 | 6.49911e+09 | 5.62564e+06 | 0.245362 | 1(Win) | true |
| simdjson (ondemand) | 200.716 | 0.133758 | 6392.95ms | 1834197 | 40 | 5.43537e+09 | 8.71493e+06 | 0.115994 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1039.57 | 0.137119 | 10210.5ms | 7351818 | 30 | 2.56568e+09 | 6.74437e+06 | 0.140597 | 1(Win) | true |
| simdjson (ondemand) | 688.217 | 0.234051 | 7130.35ms | 7351818 | 40 | 2.27414e+10 | 1.01875e+07 | 1.79212 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1085.17 | 0.37767 | 10288.8ms | 7351818 | 40 | 2.38166e+10 | 6.46096e+06 | 0.0200387 | 1(Win) | true |
| simdjson (ondemand) | 714.353 | 0.28235 | 7138.18ms | 7351818 | 40 | 3.07184e+10 | 9.81482e+06 | 0.501146 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2837.32 | 0.379861 | 7849.54ms | 1834197 | 40 | 2.19373e+08 | 616506 | 0.685591 | 1(Win) | true |
| simdjson (ondemand) | 2455.16 | 0.156721 | 9099.09ms | 1834197 | 30 | 3.74034e+07 | 712471 | 0.637263 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2857.28 | 0.269333 | 7839.72ms | 1834197 | 40 | 1.08749e+08 | 612200 | 0.0739163 | 1(Win) | true |
| simdjson (ondemand) | 2458.93 | 0.523644 | 9096.2ms | 1834197 | 40 | 5.5505e+08 | 711377 | 0.211856 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5893.57 | 0.220406 | 7511.24ms | 7351818 | 160 | 1.10002e+09 | 1.18964e+06 | 0.061902 | 1(Win) | true |
| simdjson (ondemand) | 5428.72 | 0.107464 | 8281.02ms | 7351818 | 320 | 6.16413e+08 | 1.29151e+06 | 0.00057297 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5923.95 | 0.155274 | 7532.28ms | 7351818 | 160 | 5.40362e+08 | 1.18354e+06 | 0.0183033 | 1(Win) | true |
| simdjson (ondemand) | 5433.26 | 0.336974 | 8274.21ms | 7351818 | 30 | 5.6726e+08 | 1.29043e+06 | 0.084881 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2102.67 | 0.172788 | 5244.13ms | 1834197 | 320 | 6.61194e+08 | 831909 | 0.00547566 | 1(Win) | true |
| simdjson (ondemand) | 1344.3 | 0.11441 | 8261.43ms | 1834197 | 160 | 3.54609e+08 | 1.30122e+06 | 0.0162936 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2101.17 | 0.183465 | 5285.93ms | 1834197 | 320 | 7.4649e+08 | 832501 | 0.217249 | 1(Win) | true |
| simdjson (ondemand) | 1319.56 | 0.152066 | 8323.68ms | 1834197 | 160 | 6.5015e+08 | 1.32561e+06 | 0.0293227 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4889.61 | 0.164478 | 9077.54ms | 7351818 | 320 | 1.77994e+09 | 1.4339e+06 | 0.0763156 | 1(Win) | true |
| simdjson (ondemand) | 3691.86 | 0.167968 | 5952.35ms | 7351818 | 160 | 1.62807e+09 | 1.89911e+06 | 0.0826747 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4876.42 | 0.210165 | 9094.98ms | 7351818 | 320 | 2.92186e+09 | 1.43778e+06 | 0.0908613 | 1(Win) | true |
| simdjson (ondemand) | 3685.68 | 0.367802 | 5989.47ms | 7351818 | 40 | 1.95813e+09 | 1.90229e+06 | 0.00258279 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1083.56 | 0.288499 | 9278.3ms | 409725 | 30 | 3.24704e+07 | 360611 | 0.00580463 | 1(Win) | true |
| simdjson (ondemand) | 797.52 | 0.213976 | 6293.1ms | 409725 | 80 | 8.79273e+07 | 489949 | 0.0316948 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1221.72 | 0.103602 | 8938.07ms | 409725 | 640 | 7.02679e+07 | 319831 | 0.0654016 | 1(Win) | true |
| simdjson (ondemand) | 864.073 | 0.148031 | 6057.07ms | 409725 | 640 | 2.86793e+08 | 452212 | 1.13229 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1639.74 | 0.266155 | 5071.83ms | 676745 | 30 | 3.29224e+07 | 393596 | 0.0575286 | 1(Win) | true |
| simdjson (ondemand) | 1260.57 | 0.102903 | 6516.15ms | 676745 | 640 | 1.77646e+08 | 511987 | 0.673321 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1822.74 | 0.157888 | 9829.23ms | 676745 | 320 | 1.00012e+08 | 354080 | 0.260555 | 1(Win) | true |
| simdjson (ondemand) | 1371.68 | 0.136078 | 6365.85ms | 676745 | 640 | 2.62362e+08 | 470514 | 0.239899 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 733.134 | 0.110198 | 6816.22ms | 409725 | 640 | 2.20772e+08 | 532978 | 0.135319 | 1(Win) | true |
| simdjson (ondemand) | 340.14 | 0.170974 | 7279.13ms | 409725 | 320 | 1.23446e+09 | 1.14877e+06 | 0.354939 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 795.473 | 0.113168 | 6688.2ms | 409725 | 640 | 1.97771e+08 | 491210 | 0.137162 | 1(Win) | true |
| simdjson (ondemand) | 353.724 | 0.119744 | 7197.12ms | 409725 | 320 | 5.599e+08 | 1.10466e+06 | 0.145022 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1087.66 | 0.142608 | 7551.43ms | 676745 | 320 | 2.2914e+08 | 593379 | 0.145302 | 1(Win) | true |
| simdjson (ondemand) | 546.916 | 0.181294 | 7435.58ms | 676745 | 80 | 3.66156e+08 | 1.18006e+06 | 0.141612 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1171.31 | 0.121708 | 7388.31ms | 676745 | 640 | 2.87823e+08 | 551003 | 0.0138073 | 1(Win) | true |
| simdjson (ondemand) | 567.902 | 0.259929 | 7353.39ms | 676745 | 160 | 1.39615e+09 | 1.13645e+06 | 0.0135441 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1820.73 | 0.251459 | 5458.65ms | 409725 | 320 | 9.31918e+07 | 214608 | 0.13139 | 1(Win) | true |
| simdjson (ondemand) | 1299.1 | 0.107281 | 7730.65ms | 409725 | 640 | 6.66384e+07 | 300781 | 0.19519 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1972.09 | 0.384173 | 5403.54ms | 409725 | 160 | 9.27058e+07 | 198137 | 0.291209 | 1(Win) | true |
| simdjson (ondemand) | 1375 | 0.117869 | 7634.4ms | 409725 | 640 | 7.18056e+07 | 284178 | 0.077659 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2591.82 | 0.0968923 | 6404.57ms | 676745 | 1280 | 7.45127e+07 | 249012 | 0.153628 | 1(Win) | true |
| simdjson (ondemand) | 2022.44 | 0.219078 | 8200.33ms | 676745 | 40 | 1.95505e+07 | 319117 | 0.118703 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2781.8 | 0.21202 | 6297.07ms | 676745 | 160 | 3.87144e+07 | 232006 | 0.142116 | 1(Win) | true |
| simdjson (ondemand) | 2122.63 | 0.148879 | 8105.43ms | 676745 | 640 | 1.31143e+08 | 304054 | 0.0433571 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1547.88 | 0.15823 | 6531.19ms | 409725 | 80 | 1.27637e+07 | 252438 | 0.339246 | 1(Win) | true |
| simdjson (ondemand) | 1000.64 | 0.107209 | 5038.93ms | 409725 | 640 | 1.12169e+08 | 390495 | 0.137738 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1637.73 | 0.170681 | 6388.54ms | 409725 | 320 | 5.30667e+07 | 238589 | 0.281793 | 1(Win) | true |
| simdjson (ondemand) | 1046.57 | 0.18175 | 9931.98ms | 409725 | 320 | 1.47349e+08 | 373357 | 0.0569974 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2221.67 | 0.111008 | 7548.12ms | 676745 | 640 | 6.65554e+07 | 290500 | 0.131534 | 1(Win) | true |
| simdjson (ondemand) | 1560.89 | 0.12696 | 5323.37ms | 676745 | 640 | 1.7637e+08 | 413479 | 0.0559436 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2330.47 | 0.264262 | 7369.25ms | 676745 | 320 | 1.7139e+08 | 276938 | 0.108688 | 1(Win) | true |
| simdjson (ondemand) | 1623.93 | 0.117793 | 5290.2ms | 676745 | 640 | 1.40261e+08 | 397428 | 0.177773 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1604.09 | 0.0649795 | 8086.96ms | 264040 | 2560 | 2.66363e+07 | 156979 | 0.0531861 | 1(Win) | true |
| simdjson (ondemand) | 1404.17 | 0.0731625 | 9196.45ms | 264040 | 2560 | 4.40676e+07 | 179329 | 0.0343396 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1873.68 | 0.0789546 | 7632.86ms | 264040 | 1280 | 1.44117e+07 | 134392 | 0.0727021 | 1(Win) | true |
| simdjson (ondemand) | 1597.68 | 0.0599386 | 8800.9ms | 264040 | 2560 | 2.28461e+07 | 157609 | 0.0190735 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2015.18 | 0.187969 | 8796.11ms | 360584 | 320 | 3.29236e+07 | 170644 | 0.186606 | 1(Win) | true |
| simdjson (ondemand) | 1844.79 | 0.0964952 | 9649.4ms | 360584 | 640 | 2.07067e+07 | 186406 | 0.13102 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2319.83 | 0.215087 | 8367.42ms | 360584 | 160 | 1.62647e+07 | 148235 | 0.0972508 | 1(Win) | true |
| simdjson (ondemand) | 2071.52 | 0.0727505 | 9243.52ms | 360584 | 1280 | 1.86688e+07 | 166003 | 0.134559 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 654.45 | 0.114152 | 9912.47ms | 264040 | 320 | 6.17309e+07 | 384763 | 0.215043 | 1(Win) | true |
| simdjson (ondemand) | 194.626 | 0.117648 | 8231.52ms | 264040 | 160 | 3.707e+08 | 1.2938e+06 | 0.121228 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 695.569 | 0.143633 | 9705.23ms | 264040 | 160 | 4.32603e+07 | 362017 | 0.280269 | 1(Win) | true |
| simdjson (ondemand) | 196.699 | 0.326814 | 8191.08ms | 264040 | 80 | 1.40032e+09 | 1.28017e+06 | 0.0808592 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 833.623 | 0.126634 | 5264.25ms | 360584 | 320 | 8.73222e+07 | 412512 | 0.498317 | 1(Win) | true |
| simdjson (ondemand) | 264.37 | 0.118344 | 8343.32ms | 360584 | 320 | 7.58287e+08 | 1.30075e+06 | 0.145112 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 885.426 | 0.378273 | 5170.08ms | 360584 | 30 | 6.47502e+07 | 388378 | 0.000755284 | 1(Win) | true |
| simdjson (ondemand) | 268.496 | 0.339913 | 8166.31ms | 360584 | 30 | 5.68583e+08 | 1.28076e+06 | 0.14041 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4613.83 | 0.0547031 | 5491.76ms | 264040 | 4890 | 4.35861e+06 | 54576.8 | 0.15896 | 1(Win) | true |
| simdjson (ondemand) | 3635.51 | 0.0323474 | 7005.76ms | 264040 | 40 | 20079.3 | 69263.5 | 0.0333018 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4772.03 | 0.0616754 | 5470.13ms | 264040 | 4890 | 5.17926e+06 | 52767.6 | 0.0862969 | 1(Win) | true |
| simdjson (ondemand) | 3696.31 | 0.113211 | 7004.33ms | 264040 | 1280 | 7.61352e+06 | 68124.1 | 0.0991775 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5074.36 | 0.0644035 | 6850.07ms | 360584 | 4890 | 9.31492e+06 | 67768.1 | 0.0692607 | 1(Win) | true |
| simdjson (ondemand) | 4358.73 | 0.131738 | 7967.41ms | 360584 | 640 | 6.91351e+06 | 78894.5 | 0.0519886 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5231.02 | 0.0745327 | 6742.67ms | 360584 | 2560 | 6.14574e+06 | 65738.5 | 0.171813 | 1(Win) | true |
| simdjson (ondemand) | 4456.28 | 0.157996 | 7977.42ms | 360584 | 640 | 9.5135e+06 | 77167.4 | 0.135778 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3302.23 | 0.13502 | 7628.17ms | 264040 | 2560 | 2.71369e+07 | 76254 | 0.171458 | 1(Win) | true |
| simdjson (ondemand) | 2383.16 | 0.166563 | 5469.62ms | 264040 | 320 | 9.91149e+06 | 105661 | 0.115419 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3416.69 | 0.0828242 | 7513.95ms | 264040 | 2560 | 9.53858e+06 | 73699.5 | 0.208421 | 1(Win) | true |
| simdjson (ondemand) | 2426.23 | 0.113608 | 5390.21ms | 264040 | 1280 | 1.77951e+07 | 103786 | 0.0078812 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3826 | 0.0507966 | 9064.27ms | 360584 | 4890 | 1.0193e+07 | 89879.8 | 0.000600034 | 1(Win) | true |
| simdjson (ondemand) | 2993.44 | 0.134563 | 5933.82ms | 360584 | 640 | 1.52934e+07 | 114878 | 0.0180798 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3914.52 | 0.0812572 | 8997.43ms | 360584 | 2560 | 1.30443e+07 | 87847.3 | 0.0189205 | 1(Win) | true |
| simdjson (ondemand) | 3054.76 | 0.113516 | 5838.25ms | 360584 | 640 | 1.04508e+07 | 112572 | 0.150955 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1167.24 | 0.121547 | 219.536ms | 2632 | 80 | 546.553 | 2150.44 | 0.225607 | 1(Win) | true |
| simdjson (ondemand) | 946.273 | 0.210668 | 289.415ms | 2632 | 80 | 2498.19 | 2652.59 | 0.373236 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1645.49 | 0.0395122 | 181.15ms | 2632 | 1280 | 464.999 | 1525.42 | 0.151108 | 1(Win) | true |
| simdjson (ondemand) | 1315.34 | 0.0334198 | 218.777ms | 2632 | 1280 | 520.611 | 1908.3 | 0.0191633 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1439.73 | 0.175328 | 231.51ms | 3370 | 40 | 612.717 | 2232.28 | 0.0458962 | 1(Win) | true |
| simdjson (ondemand) | 1244.08 | 0.0770988 | 270.831ms | 3370 | 160 | 634.719 | 2583.35 | 0.0430828 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1960.22 | 0.150405 | 191.918ms | 3370 | 80 | 486.478 | 1639.55 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1631.56 | 0.124579 | 224.516ms | 3370 | 80 | 481.766 | 1969.83 | 0.264682 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 907.76 | 0.0661245 | 282.603ms | 2632 | 160 | 534.903 | 2765.12 | 0.153483 | 1(Win) | true |
| simdjson (ondemand) | 480.284 | 0.0493625 | 533.029ms | 2632 | 160 | 1064.85 | 5226.23 | 0.168337 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1196.76 | 0.111443 | 237.516ms | 2632 | 80 | 437.076 | 2097.39 | 0.074442 | 1(Win) | true |
| simdjson (ondemand) | 548.947 | 0.0410541 | 487.059ms | 2632 | 320 | 1127.65 | 4572.52 | 0.0478855 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1098.18 | 0.0648423 | 299.114ms | 3370 | 160 | 576.172 | 2926.56 | 0.0363186 | 1(Win) | true |
| simdjson (ondemand) | 620.56 | 0.103186 | 528.952ms | 3370 | 30 | 856.759 | 5179 | 0.377663 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1415.03 | 0.0849941 | 254.595ms | 3370 | 4890 | 18222.8 | 2271.24 | 0.125777 | 1(Win) | true |
| simdjson (ondemand) | 703.771 | 0.0805972 | 489.262ms | 3370 | 80 | 1083.75 | 4566.66 | 0.0227138 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2486.78 | 0.106382 | 105.534ms | 2632 | 320 | 368.966 | 1009.37 | 0.103203 | 1(Win) | true |
| simdjson (ondemand) | 1828.59 | 0.0844943 | 141.613ms | 2632 | 320 | 430.47 | 1372.68 | 0.0939341 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3256.03 | 0.108892 | 83.0165ms | 2632 | 640 | 450.987 | 770.898 | 0.0573929 | 1(Win) | true |
| simdjson (ondemand) | 2319.5 | 0.0306824 | 114.596ms | 2632 | 2560 | 282.228 | 1082.16 | 0.0393971 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2882.44 | 0.0772811 | 115.226ms | 3370 | 640 | 475.188 | 1114.99 | 0.0854159 | 1(Win) | true |
| simdjson (ondemand) | 2300.76 | 0.0884869 | 143.209ms | 3370 | 320 | 488.907 | 1396.88 | 0.318234 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3679.31 | 0.0568166 | 94.8768ms | 3370 | 640 | 157.637 | 873.502 | 0.0666769 | 1(Win) | true |
| simdjson (ondemand) | 2907.96 | 0.153139 | 117.078ms | 3370 | 160 | 458.325 | 1105.2 | 0.189651 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1868.9 | 0.0843706 | 146.5ms | 2632 | 320 | 410.895 | 1343.07 | 0.0318867 | 1(Win) | true |
| simdjson (ondemand) | 1554.61 | 0.201484 | 166.355ms | 2632 | 40 | 423.323 | 1614.6 | 0.03921 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2264.66 | 0.386686 | 126.147ms | 2632 | 30 | 551.068 | 1108.37 | 0.00601522 | 1(Win) | true |
| simdjson (ondemand) | 1891.92 | 0.0927225 | 138.751ms | 2632 | 320 | 484.271 | 1326.73 | 0.0854282 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2152.5 | 0.0569847 | 152.274ms | 3370 | 640 | 463.31 | 1493.1 | 0.0256323 | 1(Win) | true |
| simdjson (ondemand) | 1698.09 | 0.275179 | 190.977ms | 3370 | 2560 | 69440.1 | 1892.65 | 2.80762 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2703.16 | 0.326798 | 126.837ms | 3370 | 30 | 452.892 | 1188.93 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2413.56 | 0.14164 | 139.708ms | 3370 | 4890 | 17395 | 1331.59 | 0.0393743 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 482.818 | 0.0352352 | 927.264ms | 4630 | 80 | 830.688 | 9145.29 | 0.108233 | 1(Win) | true |
| simdjson (ondemand) | 454.572 | 0.0535496 | 984.943ms | 4630 | 40 | 1082.25 | 9713.55 | 0.0406814 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 548.587 | 0.0714793 | 926.376ms | 4630 | 40 | 1324.01 | 8048.88 | 0.0470859 | 1(Win) | true |
| simdjson (ondemand) | 512.126 | 0.0611099 | 982.696ms | 4630 | 40 | 1110.43 | 8621.92 | 0.00512234 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1092.7 | 0.093376 | 1019.95ms | 11579 | 1280 | 113978 | 10105.8 | 0.121737 | 1(Win) | true |
| simdjson (ondemand) | 1059.09 | 0.0422131 | 1103.35ms | 11579 | 80 | 1549.75 | 10426.5 | 0.0940797 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1225.11 | 0.0450796 | 1017.23ms | 11579 | 40 | 660.408 | 9013.55 | 0.0112806 | 1(Win) | true |
| simdjson (ondemand) | 1180.97 | 0.206255 | 1049.78ms | 11579 | 640 | 238041 | 9350.42 | 0.0420445 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 454.297 | 0.0871679 | 988.804ms | 4630 | 30 | 2153.36 | 9719.43 | 0.0150923 | 1(Win) | true |
| simdjson (ondemand) | 418.782 | 0.0614591 | 1066.81ms | 4630 | 40 | 1679.65 | 10543.7 | 0.00600711 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 512.547 | 0.0311477 | 982.225ms | 4630 | 160 | 1152.04 | 8614.84 | 0.148511 | 1(Win) | true |
| simdjson (ondemand) | 466.866 | 0.0312616 | 1068.84ms | 4630 | 160 | 1398.69 | 9457.76 | 0.105622 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1033.59 | 0.111251 | 1090.71ms | 11579 | 1280 | 180827 | 10683.7 | 0.358355 | 1(Win) | true |
| simdjson (ondemand) | 977.92 | 0.0844319 | 1188.5ms | 11579 | 4890 | 444486 | 11291.9 | 0.00557272 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1154.61 | 0.061675 | 1075.11ms | 11579 | 30 | 1043.79 | 9563.93 | 0.0278748 | 1(Win) | true |
| simdjson (ondemand) | 1094.71 | 0.0268854 | 1134.64ms | 11579 | 160 | 1176.78 | 10087.2 | 0.0903173 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5045.56 | 0.0647373 | 92.2695ms | 4630 | 320 | 102.708 | 875.128 | 0.133018 | 1(Win) | true |
| simdjson (ondemand) | 4527.79 | 0.0850623 | 101.319ms | 4630 | 640 | 440.396 | 975.202 | 0.0200239 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5152.86 | 0.0989094 | 89.6406ms | 4630 | 640 | 459.748 | 856.905 | 0.0644083 | 1(Win) | true |
| simdjson (ondemand) | 4637.78 | 0.250296 | 99.186ms | 4630 | 40 | 227.148 | 952.075 | 0.0760915 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6857.08 | 0.0719753 | 165.979ms | 11579 | 320 | 429.913 | 1610.39 | 0.031058 | 1(Win) | true |
| simdjson (ondemand) | 6701.98 | 0.0757517 | 171.748ms | 11579 | 320 | 498.506 | 1647.66 | 0.032253 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6922.2 | 0.10225 | 164.872ms | 11579 | 160 | 425.695 | 1595.24 | 0.155783 | 1(Win) | true |
| simdjson (ondemand) | 6794.45 | 0.0620461 | 167.315ms | 11579 | 160 | 162.698 | 1625.24 | 0.0469382 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3835.63 | 0.0697105 | 119.484ms | 4630 | 640 | 412.159 | 1151.18 | 0.00149305 | 1(Win) | true |
| simdjson (ondemand) | 3553.96 | 0.0404727 | 128.495ms | 4630 | 1280 | 323.647 | 1242.42 | 0.0604654 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3897.91 | 0.04328 | 117.367ms | 4630 | 1280 | 307.668 | 1132.79 | 0.013171 | 1(Win) | true |
| simdjson (ondemand) | 3625.05 | 0.119952 | 126.091ms | 4630 | 160 | 341.563 | 1218.06 | 0.0804938 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5879.58 | 0.0935758 | 194.06ms | 11579 | 40 | 123.548 | 1878.12 | 0.0536595 | 1(Win) | true |
| simdjson (ondemand) | 5755.92 | 0.0704059 | 197.338ms | 11579 | 160 | 291.911 | 1918.47 | 0.0664149 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5904.1 | 0.052079 | 192.571ms | 11579 | 320 | 303.606 | 1870.33 | 0.0147055 | 1(Win) | true |
| simdjson (ondemand) | 5815.79 | 0.0966165 | 194.111ms | 11579 | 160 | 538.452 | 1898.72 | 0.0968692 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 853.188 | 0.126281 | 585.116ms | 5092 | 1280 | 66126.4 | 5691.72 | 0.324477 | 1(Win) | true |
| simdjson (ondemand) | 770.702 | 0.0410587 | 641.683ms | 5092 | 320 | 2141.73 | 6300.89 | 0.0314341 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1043.13 | 0.0991466 | 532.558ms | 5092 | 2560 | 54537.6 | 4655.32 | 0.0135831 | 1(Win) | true |
| simdjson (ondemand) | 916.731 | 0.163353 | 652.781ms | 5092 | 30 | 2246.3 | 5297.2 | 0.262968 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1457.4 | 0.270808 | 635.708ms | 9739 | 2560 | 762489 | 6372.86 | 0.0341358 | 1(Win) | true |
| simdjson (ondemand) | 1386.79 | 0.100363 | 678.252ms | 9739 | 2560 | 115664 | 6697.37 | 0.0653689 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1781.64 | 0.130944 | 590.828ms | 9739 | 1280 | 59644.5 | 5213.08 | 0.0225595 | 1(Win) | true |
| simdjson (ondemand) | 1632.24 | 0.0428004 | 642.169ms | 9739 | 320 | 1898.04 | 5690.24 | 0.134732 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 564.833 | 0.0509581 | 875.01ms | 5092 | 80 | 1535.51 | 8597.42 | 0.222825 | 1(Win) | true |
| simdjson (ondemand) | 309.163 | 0.0707429 | 1588.65ms | 5092 | 40 | 4938.88 | 15707.3 | 0.196046 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 643.818 | 0.0935181 | 827.809ms | 5092 | 40 | 1990.22 | 7542.68 | 0.0668866 | 1(Win) | true |
| simdjson (ondemand) | 328.016 | 0.0946345 | 1546.03ms | 5092 | 4890 | 959830 | 14804.5 | 0.00588145 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 994.67 | 0.0500185 | 1002.55ms | 9739 | 40 | 872.554 | 9337.6 | 0.0617956 | 1(Win) | true |
| simdjson (ondemand) | 582.382 | 0.0424811 | 1616.94ms | 9739 | 80 | 3671.92 | 15948 | 0.0660393 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1116.04 | 0.0893186 | 904.209ms | 9739 | 30 | 1657.59 | 8322.17 | 0 | 1(Win) | true |
| simdjson (ondemand) | 625.005 | 0.0614778 | 1570.25ms | 9739 | 40 | 3338.56 | 14860.4 | 0.070202 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3558.76 | 0.239301 | 140.381ms | 5092 | 40 | 426.51 | 1364.55 | 0.0549934 | 1(Win) | true |
| simdjson (ondemand) | 3002.25 | 0.150232 | 165.824ms | 5092 | 2560 | 15116.4 | 1617.49 | 0.136142 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3750.14 | 0.0416388 | 133.491ms | 5092 | 1280 | 372.126 | 1294.92 | 0.0746261 | 1(Win) | true |
| simdjson (ondemand) | 3134.04 | 0.14469 | 160.643ms | 5092 | 80 | 402.101 | 1549.47 | 0.169126 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5243.36 | 0.138536 | 182.789ms | 9739 | 80 | 481.749 | 1771.35 | 0.0888362 | 1(Win) | true |
| simdjson (ondemand) | 4725.25 | 0.129207 | 202.145ms | 9739 | 40 | 257.994 | 1965.58 | 0.019082 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5412.58 | 0.0628563 | 176.212ms | 9739 | 320 | 372.278 | 1715.97 | 0.123442 | 1(Win) | true |
| simdjson (ondemand) | 4844.3 | 0.101797 | 195.927ms | 9739 | 4890 | 18627.3 | 1917.27 | 0.0104131 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2400.17 | 0.0434319 | 208.615ms | 5092 | 640 | 494.188 | 2023.24 | 0.00324367 | 1(Win) | true |
| simdjson (ondemand) | 2017.55 | 0.159111 | 246.49ms | 5092 | 30 | 439.995 | 2406.93 | 0.0595857 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2449.08 | 0.146068 | 202.126ms | 5092 | 4890 | 41019.7 | 1982.83 | 0.010979 | 1(Win) | true |
| simdjson (ondemand) | 2088.6 | 0.131315 | 243.14ms | 5092 | 40 | 372.869 | 2325.05 | 0.47017 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3746.53 | 0.147718 | 257.419ms | 9739 | 40 | 536.408 | 2479.05 | 0.050448 | 1(Win) | true |
| simdjson (ondemand) | 3336.6 | 0.153312 | 282.605ms | 9739 | 2560 | 46624.5 | 2783.62 | 0.129763 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 3458.43 | 0.0343757 | 274.277ms | 9739 | 640 | 545.448 | 2685.56 | 0.00930817 | 1(Win) | true |
| Jsonifier (generic) | 3354.82 | 0.600704 | 263.33ms | 9739 | 1280 | 354015 | 2768.51 | 0.947894 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1279.73 | 0.153631 | 366.495ms | 4857 | 30 | 927.638 | 3619.5 | 0.0774186 | 1(Win) | true |
| simdjson (ondemand) | 1043.82 | 0.154119 | 454.3ms | 4857 | 40 | 1870.92 | 4437.52 | 0.0291163 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1659.53 | 0.0620097 | 294.028ms | 4857 | 160 | 479.298 | 2791.15 | 0.019261 | 1(Win) | true |
| simdjson (ondemand) | 1254.73 | 0.192029 | 386.878ms | 4857 | 30 | 1507.62 | 3691.63 | 0.000902935 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1690.08 | 0.0863831 | 389.308ms | 6701 | 80 | 853.518 | 3781.22 | 0.024469 | 1(Win) | true |
| simdjson (ondemand) | 1406.19 | 0.175611 | 463.497ms | 6701 | 30 | 1910.8 | 4544.6 | 0.0638527 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2114.59 | 0.0443378 | 319.512ms | 6701 | 320 | 574.547 | 3022.13 | 0.0602173 | 1(Win) | true |
| simdjson (ondemand) | 1671.08 | 0.0575055 | 399.97ms | 6701 | 320 | 1547.58 | 3824.22 | 0.0339006 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 653.054 | 0.0927213 | 746.889ms | 4857 | 40 | 1730.05 | 7092.82 | 0.10387 | 1(Win) | true |
| simdjson (ondemand) | 143.888 | 0.0518004 | 3313.43ms | 4857 | 30 | 8342.09 | 32191.7 | 0.00455584 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 745 | 0.0414629 | 642.627ms | 4857 | 160 | 1063.32 | 6217.44 | 0.00412164 | 1(Win) | true |
| simdjson (ondemand) | 145.651 | 0.163649 | 3183.35ms | 4857 | 1280 | 3.46692e+06 | 31802 | 0.257094 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 822.164 | 0.0325097 | 792.821ms | 6701 | 160 | 1021.67 | 7772.86 | 0.0199452 | 1(Win) | true |
| simdjson (ondemand) | 195.441 | 0.300862 | 3288.17ms | 6701 | 160 | 1.54847e+06 | 32698.2 | 0.243322 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 927.883 | 0.0258541 | 711.614ms | 6701 | 320 | 1014.61 | 6887.26 | 0.026083 | 1(Win) | true |
| simdjson (ondemand) | 199.373 | 0.0817377 | 3329.07ms | 6701 | 4890 | 3.35659e+06 | 32053.3 | 0.358224 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3254.15 | 0.176564 | 147.901ms | 4857 | 80 | 505.309 | 1423.41 | 0.0447667 | 1(Win) | true |
| simdjson (ondemand) | 2608.41 | 0.107862 | 183.45ms | 4857 | 160 | 587.008 | 1775.79 | 0.452319 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3693.29 | 0.185092 | 129.392ms | 4857 | 30 | 161.661 | 1254.17 | 0.114416 | 1(Win) | true |
| simdjson (ondemand) | 2888.43 | 0.266834 | 164.225ms | 4857 | 2560 | 46874.5 | 1603.64 | 0.210878 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3892.8 | 0.0747047 | 168.804ms | 6701 | 320 | 481.284 | 1641.64 | 0.144274 | 1(Win) | true |
| simdjson (ondemand) | 3345.19 | 0.129363 | 196.577ms | 6701 | 80 | 488.592 | 1910.38 | 0.0536256 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4399.4 | 0.121559 | 149.825ms | 6701 | 80 | 249.433 | 1452.6 | 0.106819 | 1(Win) | true |
| simdjson (ondemand) | 3736.36 | 0.173979 | 175.797ms | 6701 | 40 | 354.189 | 1710.38 | 0.0433816 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2539.49 | 0.162513 | 185.346ms | 4857 | 80 | 702.924 | 1823.99 | 0.231485 | 1(Win) | true |
| simdjson (ondemand) | 1463.34 | 0.0944409 | 323.185ms | 4857 | 160 | 1429.83 | 3165.35 | 0.0422366 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2862.91 | 0.187352 | 166.505ms | 4857 | 2560 | 23522.2 | 1617.93 | 0.0179418 | 1(Win) | true |
| simdjson (ondemand) | 1576.17 | 0.0752101 | 300.209ms | 4857 | 1280 | 6253.06 | 2938.76 | 0.0427392 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3130.08 | 0.168845 | 209.476ms | 6701 | 30 | 356.506 | 2041.67 | 0.20204 | 1(Win) | true |
| simdjson (ondemand) | 1919.64 | 0.0960327 | 335.263ms | 6701 | 4890 | 49979 | 3329.05 | 0.0293994 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3476.82 | 0.0803783 | 189.034ms | 6701 | 160 | 349.23 | 1838.05 | 0.029932 | 1(Win) | true |
| simdjson (ondemand) | 2088.46 | 0.0789598 | 311.6ms | 6701 | 160 | 934.021 | 3059.94 | 0.0850413 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1053.41 | 0.0596144 | 159.086ms | 1691 | 640 | 533.063 | 1530.9 | 0.0305264 | 1(Win) | true |
| simdjson (ondemand) | 828.045 | 0.105979 | 199.463ms | 1691 | 4890 | 20831.9 | 1947.56 | 0.0734877 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1146.42 | 0.482547 | 164.819ms | 1691 | 1280 | 58978.4 | 1406.7 | 0.863369 | 1(Win) | true |
| simdjson (ondemand) | 978.161 | 0.132 | 187.151ms | 1691 | 160 | 757.77 | 1648.67 | 0.0466068 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1208.18 | 0.095453 | 173.403ms | 2158 | 160 | 422.999 | 1703.41 | 0.106291 | 1(Win) | true |
| simdjson (ondemand) | 1044.66 | 0.0738539 | 204.118ms | 2158 | 320 | 677.411 | 1970.05 | 0.448318 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1471.51 | 0.111093 | 159.417ms | 2158 | 4890 | 11804.6 | 1398.58 | 0.284922 | 1(Win) | true |
| simdjson (ondemand) | 1225.64 | 0.202121 | 188.895ms | 2158 | 40 | 460.746 | 1679.15 | 0.17142 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 847.079 | 0.147119 | 193.756ms | 1691 | 2560 | 20082.4 | 1903.79 | 0.0401381 | 1(Win) | true |
| simdjson (ondemand) | 494.683 | 0.149655 | 331.43ms | 1691 | 1280 | 30466.8 | 3259.99 | 0.151037 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 981.4 | 0.0722054 | 184.638ms | 1691 | 320 | 450.49 | 1643.23 | 0.000190174 | 1(Win) | true |
| simdjson (ondemand) | 543.457 | 0.0611012 | 319.331ms | 1691 | 320 | 1051.98 | 2967.42 | 0.0343194 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 970.019 | 0.0638393 | 217.469ms | 2158 | 320 | 587.041 | 2121.64 | 0.100554 | 1(Win) | true |
| simdjson (ondemand) | 633.625 | 0.106571 | 332.918ms | 2158 | 80 | 958.531 | 3248.03 | 0.0261629 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 956.05 | 1.37276 | 211.16ms | 2158 | 80 | 69859 | 2152.64 | 0.0702133 | 1(Win) | true |
| simdjson (ondemand) | 689.572 | 0.0604295 | 319.805ms | 2158 | 320 | 1040.86 | 2984.5 | 0.338826 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3883.08 | 0.119966 | 44.4502ms | 1691 | 640 | 158.866 | 415.305 | 0.0184319 | 1(Win) | true |
| simdjson (ondemand) | 3243.78 | 0.0602318 | 53.1279ms | 1691 | 2560 | 229.549 | 497.156 | 0.0548916 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4245.19 | 0.143705 | 41.1645ms | 1691 | 640 | 190.729 | 379.88 | 0.155306 | 1(Win) | true |
| simdjson (ondemand) | 3576.52 | 0.222265 | 48.6096ms | 1691 | 320 | 321.411 | 450.903 | 0.0270364 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4349.97 | 0.0613246 | 50.658ms | 2158 | 4890 | 411.632 | 473.114 | 0.0481253 | 1(Win) | true |
| simdjson (ondemand) | 3819.13 | 0.127987 | 57.3873ms | 2158 | 640 | 304.43 | 538.873 | 0.1306 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4667.58 | 0.224885 | 47.1779ms | 2158 | 4890 | 4807.86 | 440.92 | 0.177397 | 1(Win) | true |
| simdjson (ondemand) | 4183.88 | 0.0542407 | 52.7562ms | 2158 | 4890 | 348.1 | 491.895 | 0.0703223 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2754.63 | 0.216315 | 62.4996ms | 1691 | 80 | 128.3 | 585.438 | 0.176904 | 1(Win) | true |
| simdjson (ondemand) | 1946.99 | 0.16824 | 87.3668ms | 1691 | 320 | 621.395 | 828.284 | 0.166859 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2940.11 | 0.116312 | 58.5119ms | 1691 | 640 | 260.488 | 548.505 | 0.0823939 | 1(Win) | true |
| simdjson (ondemand) | 2049.75 | 0.254918 | 81.695ms | 1691 | 160 | 643.591 | 786.763 | 0.365161 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3184.08 | 0.255523 | 68.1473ms | 2158 | 160 | 436.43 | 646.35 | 0.164655 | 1(Win) | true |
| simdjson (ondemand) | 2073.22 | 0.494851 | 100.474ms | 2158 | 2560 | 61773.5 | 992.674 | 0.389232 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3385.06 | 0.0963416 | 66.045ms | 2158 | 1280 | 439.144 | 607.973 | 0.12526 | 1(Win) | true |
| simdjson (ondemand) | 2539.46 | 0.17259 | 85.4173ms | 2158 | 320 | 626.037 | 810.419 | 0.0277557 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 917.198 | 0.0742231 | 471.884ms | 4390 | 80 | 918.271 | 4564.59 | 0.0896283 | 1(Win) | true |
| simdjson (ondemand) | 791.257 | 0.0550254 | 536.261ms | 4390 | 160 | 1356.25 | 5291.11 | 0.0101596 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1001.16 | 0.0854706 | 441.065ms | 4390 | 80 | 1021.99 | 4181.79 | 0.0116563 | 1(Win) | true |
| simdjson (ondemand) | 857.427 | 0.0877103 | 504.159ms | 4390 | 2560 | 46954.4 | 4882.78 | 0.0306656 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1711.38 | 0.110943 | 528.031ms | 9378 | 2560 | 86053.4 | 5225.92 | 0.0379424 | 1(Win) | true |
| simdjson (ondemand) | 1565.73 | 0.161537 | 575.381ms | 9378 | 1280 | 108979 | 5712.06 | 0.0186729 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1864.36 | 0.0533374 | 501.267ms | 9378 | 160 | 1047.48 | 4797.12 | 0.0268318 | 1(Win) | true |
| simdjson (ondemand) | 1706.6 | 0.104576 | 544.176ms | 9378 | 40 | 1201.38 | 5240.57 | 0.100873 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 650.076 | 0.126916 | 650.63ms | 4390 | 1280 | 85515.1 | 6440.21 | 0.0646747 | 1(Win) | true |
| simdjson (ondemand) | 545.983 | 0.134016 | 776.571ms | 4390 | 30 | 3168.13 | 7668.07 | 0.0735189 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 696.321 | 0.105696 | 622.384ms | 4390 | 30 | 1211.57 | 6012.5 | 0.184957 | 1(Win) | true |
| simdjson (ondemand) | 578.755 | 0.0760938 | 746.151ms | 4390 | 160 | 4847.95 | 7233.86 | 0.0360155 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1269.72 | 0.0621622 | 764.487ms | 9378 | 80 | 1533.73 | 7043.75 | 0.0450957 | 1(Win) | true |
| simdjson (ondemand) | 1116.33 | 0.117631 | 806.045ms | 9378 | 40 | 3552.56 | 8011.57 | 0.1507 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1350.3 | 0.0440879 | 683.504ms | 9378 | 80 | 682.161 | 6623.38 | 0.0396481 | 1(Win) | true |
| simdjson (ondemand) | 1184.75 | 0.121544 | 775.341ms | 9378 | 40 | 3367.4 | 7548.93 | 0.0958007 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1543.24 | 0.0454572 | 275.818ms | 4390 | 320 | 486.652 | 2712.89 | 0.013821 | 1(Win) | true |
| simdjson (ondemand) | 1385.46 | 0.100943 | 308.813ms | 4390 | 80 | 744.366 | 3021.84 | 0.173846 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1652.58 | 0.067545 | 265.664ms | 4390 | 4890 | 14318.5 | 2533.38 | 0.117446 | 1(Win) | true |
| simdjson (ondemand) | 1491.68 | 0.0512323 | 295.016ms | 4390 | 320 | 661.635 | 2806.66 | 0.0789905 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2780.12 | 0.0586567 | 327.81ms | 9378 | 160 | 569.703 | 3216.97 | 0.171846 | 1(Win) | true |
| simdjson (ondemand) | 2616.23 | 0.0418883 | 345.474ms | 9378 | 640 | 1312.3 | 3418.49 | 0.129703 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2950.7 | 0.0575333 | 317.47ms | 9378 | 160 | 486.553 | 3031 | 0.00866126 | 1(Win) | true |
| simdjson (ondemand) | 2790.36 | 0.0972935 | 331.842ms | 9378 | 80 | 777.961 | 3205.16 | 0.421797 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1269.08 | 0.037132 | 335.591ms | 4390 | 320 | 480.173 | 3298.95 | 0.134314 | 1(Win) | true |
| simdjson (ondemand) | 1123.39 | 0.119807 | 378.195ms | 4390 | 1280 | 25517.5 | 3726.78 | 0.423624 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1342.21 | 0.0298646 | 325.688ms | 4390 | 640 | 555.37 | 3119.21 | 0.0229873 | 1(Win) | true |
| simdjson (ondemand) | 1174.43 | 0.150083 | 368.372ms | 4390 | 2560 | 73278.1 | 3564.81 | 0.162307 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2384.11 | 0.0534111 | 409.034ms | 9378 | 160 | 642.321 | 3751.32 | 0.0492916 | 1(Win) | true |
| simdjson (ondemand) | 2188.88 | 0.0839482 | 415.709ms | 9378 | 80 | 941.22 | 4085.91 | 0.19206 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2499.76 | 0.108249 | 372.322ms | 9378 | 30 | 449.978 | 3577.77 | 0.0382135 | 1(Win) | true |
| simdjson (ondemand) | 2296.55 | 0.0504649 | 402.455ms | 9378 | 320 | 1235.94 | 3894.34 | 0.0790586 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1181.57 | 0.0586428 | 382.622ms | 4669 | 160 | 781.407 | 3768.46 | 0.103715 | 1(Win) | true |
| simdjson (ondemand) | 1030.47 | 0.0800355 | 442.195ms | 4669 | 160 | 1913.65 | 4321.04 | 0.139528 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1366.56 | 0.0949924 | 342.277ms | 4669 | 30 | 287.402 | 3258.33 | 0.0848384 | 1(Win) | true |
| simdjson (ondemand) | 1175.02 | 0.0370892 | 397.08ms | 4669 | 320 | 632.117 | 3789.46 | 0.106659 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1780.46 | 0.0502018 | 430.942ms | 7932 | 160 | 727.879 | 4248.64 | 0.0410594 | 1(Win) | true |
| simdjson (ondemand) | 1670.18 | 0.115112 | 469.354ms | 7932 | 40 | 1087.28 | 4529.18 | 0.0630696 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2024.95 | 0.0280344 | 391.521ms | 7932 | 640 | 701.941 | 3735.68 | 0.0104577 | 1(Win) | true |
| simdjson (ondemand) | 1889.65 | 0.0733536 | 416.398ms | 7932 | 80 | 689.816 | 4003.14 | 0.0265487 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 506.585 | 0.0758981 | 886.22ms | 4669 | 40 | 1780.18 | 8789.65 | 0.0400252 | 1(Win) | true |
| simdjson (ondemand) | 148.749 | 0.0772184 | 3057.05ms | 4669 | 4890 | 2.61272e+06 | 29934.4 | 0.158133 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 542.944 | 0.046735 | 844.483ms | 4669 | 80 | 1175.2 | 8201.04 | 0.0129574 | 1(Win) | true |
| simdjson (ondemand) | 152.02 | 0.0794931 | 2948.87ms | 4669 | 4890 | 2.65104e+06 | 29290.3 | 0.0366659 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 781.752 | 0.0736887 | 983.309ms | 7932 | 30 | 1525.28 | 9676.4 | 0.0853583 | 1(Win) | true |
| simdjson (ondemand) | 254.084 | 0.0496144 | 3068ms | 7932 | 80 | 17454.9 | 29771.9 | 0.0386 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 819.006 | 0.123077 | 939.682ms | 7932 | 4890 | 631907 | 9236.25 | 0.051322 | 1(Win) | true |
| simdjson (ondemand) | 258.157 | 0.0777475 | 2978.23ms | 7932 | 80 | 41520.3 | 29302.1 | 0.138877 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3399.32 | 0.125152 | 135.94ms | 4669 | 160 | 429.992 | 1309.88 | 0.00143145 | 1(Win) | true |
| simdjson (ondemand) | 2756.88 | 0.131661 | 164.838ms | 4669 | 80 | 361.756 | 1615.12 | 0.0958758 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3681.12 | 0.119957 | 124.794ms | 4669 | 160 | 336.869 | 1209.61 | 0.0201552 | 1(Win) | true |
| simdjson (ondemand) | 3028.58 | 0.0538896 | 151.811ms | 4669 | 640 | 401.753 | 1470.23 | 0.0413243 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4659.12 | 0.195453 | 167.236ms | 7932 | 30 | 302.11 | 1623.6 | 0.0821895 | 1(Win) | true |
| simdjson (ondemand) | 4200.07 | 0.194198 | 184.394ms | 7932 | 40 | 489.331 | 1801.05 | 0.0157291 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4984.49 | 0.135488 | 155.696ms | 7932 | 4890 | 20674.5 | 1517.62 | 0.0780838 | 1(Win) | true |
| simdjson (ondemand) | 4528.82 | 0.0399896 | 171.761ms | 7932 | 640 | 285.542 | 1670.31 | 0.0308795 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2543.27 | 0.0771807 | 179.856ms | 4669 | 160 | 292.147 | 1750.78 | 0.0745539 | 1(Win) | true |
| simdjson (ondemand) | 1746.87 | 0.103948 | 262.946ms | 4669 | 80 | 561.631 | 2548.96 | 0.0799984 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2729.59 | 0.146635 | 168.262ms | 4669 | 40 | 228.871 | 1631.28 | 0.0413958 | 1(Win) | true |
| simdjson (ondemand) | 1842.49 | 0.0717433 | 247.358ms | 4669 | 160 | 480.973 | 2416.68 | 0.00129311 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3632.78 | 0.0713046 | 214.583ms | 7932 | 80 | 176.365 | 2082.3 | 0.00120058 | 1(Win) | true |
| simdjson (ondemand) | 2734.32 | 0.121586 | 284.203ms | 7932 | 2560 | 28964.9 | 2766.51 | 0.0194109 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3383.32 | 0.179914 | 235.559ms | 7932 | 4890 | 79125.9 | 2235.83 | 2.2298 | 1(Win) | true |
| simdjson (ondemand) | 2860.74 | 0.155406 | 268.818ms | 7932 | 2560 | 43230.2 | 2644.26 | 0.177467 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 349.136 | 0.969502 | 1223.11ms | 4604 | 80 | 1.18924e+06 | 12575.9 | 0.574713 | 1(Win) | true |
| simdjson (ondemand) | 338.439 | 0.0747626 | 1315.79ms | 4604 | 4890 | 460032 | 12973.4 | 0.155467 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 432.003 | 0.0662392 | 1162.87ms | 4604 | 40 | 1812.96 | 10163.6 | 0.0302458 | 1(Win) | true |
| simdjson (ondemand) | 382.311 | 0.109671 | 1283.08ms | 4604 | 4890 | 775760 | 11484.7 | 0.213437 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1352.9 | 0.058872 | 1303.29ms | 18245 | 30 | 1719.86 | 12861.1 | 0.0318893 | 1(Win) | true |
| simdjson (ondemand) | 1257.81 | 0.0662951 | 1416.68ms | 18245 | 30 | 2523.14 | 13833.4 | 0.0496137 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1530.8 | 0.0927499 | 1280.11ms | 18245 | 2560 | 284525 | 11366.5 | 0.0382713 | 1(Win) | true |
| simdjson (ondemand) | 1386.23 | 0.0886467 | 1413.87ms | 18245 | 4890 | 605416 | 12551.9 | 0.450281 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 248.26 | 0.0738286 | 1793.3ms | 4604 | 30 | 5114.79 | 17686 | 0.0324069 | 1(Win) | true |
| simdjson (ondemand) | 161.382 | 0.0455232 | 2769.92ms | 4604 | 30 | 4602 | 27206.9 | 0.107088 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 271.334 | 0.0682297 | 1774.6ms | 4604 | 30 | 3657.03 | 16181.9 | 0.0255494 | 1(Win) | true |
| simdjson (ondemand) | 168.897 | 0.0755995 | 2790.39ms | 4604 | 4890 | 1.88875e+06 | 25996.4 | 0.0673978 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 902.031 | 0.0868185 | 1942.86ms | 18245 | 4890 | 1.37144e+06 | 19289.6 | 0.0366949 | 1(Win) | true |
| simdjson (ondemand) | 609.575 | 0.113822 | 2864.87ms | 18245 | 2560 | 2.70227e+06 | 28544.1 | 0.0449909 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 979.688 | 0.13213 | 1909.23ms | 18245 | 2560 | 1.40979e+06 | 17760.5 | 0.0537646 | 1(Win) | true |
| simdjson (ondemand) | 644.428 | 0.0982191 | 2895.2ms | 18245 | 2560 | 1.80041e+06 | 27000.4 | 0.011629 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2669.86 | 0.204446 | 169.462ms | 4604 | 160 | 1808.73 | 1644.55 | 0.0791115 | 1(Win) | true |
| simdjson (ondemand) | 2444.24 | 0.104817 | 185.209ms | 4604 | 160 | 567.235 | 1796.35 | 0.0591827 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2885 | 0.0411007 | 157.081ms | 4604 | 1280 | 500.825 | 1521.91 | 0.0412378 | 1(Win) | true |
| simdjson (ondemand) | 2512 | 0.14659 | 179.759ms | 4604 | 40 | 262.605 | 1747.9 | 0.040032 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6676.8 | 0.0707025 | 269.085ms | 18245 | 160 | 543.176 | 2606.01 | 0.0328676 | 1(Win) | true |
| simdjson (ondemand) | 6161.74 | 0.0418258 | 288.822ms | 18245 | 320 | 446.396 | 2823.84 | 0.0227917 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6798.55 | 0.0653974 | 263.439ms | 18245 | 160 | 448.225 | 2559.34 | 0.0014652 | 1(Win) | true |
| simdjson (ondemand) | 6266.33 | 0.0419402 | 284.194ms | 18245 | 320 | 433.981 | 2776.71 | 0.0604723 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2088.28 | 0.0860455 | 215.925ms | 4604 | 160 | 523.683 | 2102.55 | 0.0237863 | 1(Win) | true |
| simdjson (ondemand) | 1334.09 | 0.0404321 | 335.706ms | 4604 | 160 | 283.319 | 3291.18 | 0.0473078 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2125.08 | 0.0642327 | 211.381ms | 4604 | 320 | 563.616 | 2066.14 | 0.0755668 | 1(Win) | true |
| simdjson (ondemand) | 1346.96 | 0.100514 | 332.047ms | 4604 | 30 | 322.064 | 3259.73 | 0.00102259 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5538.16 | 0.043332 | 320.274ms | 18245 | 320 | 593.095 | 3141.8 | 0.0288366 | 1(Win) | true |
| simdjson (ondemand) | 4029.53 | 0.0980141 | 441.424ms | 18245 | 30 | 537.375 | 4318.07 | 0.0964008 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5617.51 | 0.058238 | 315.847ms | 18245 | 160 | 520.635 | 3097.42 | 0.207659 | 1(Win) | true |
| simdjson (ondemand) | 4061.2 | 0.0772843 | 436.092ms | 18245 | 40 | 438.554 | 4284.4 | 0.00933532 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1067.33 | 0.132243 | 449.793ms | 4926 | 30 | 1016.4 | 4401.47 | 0.0977902 | 1(Win) | true |
| simdjson (ondemand) | 711.002 | 0.729589 | 607.21ms | 4926 | 320 | 743625 | 6607.29 | 0.117676 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1236.81 | 0.0471863 | 419.222ms | 4926 | 320 | 1027.93 | 3798.31 | 0.16116 | 1(Win) | true |
| simdjson (ondemand) | 920.86 | 0.0738163 | 547.328ms | 4926 | 80 | 1134.48 | 5101.54 | 0.0296391 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1653.72 | 0.0666569 | 477.421ms | 8150 | 160 | 1570.38 | 4699.99 | 0.533417 | 1(Win) | true |
| simdjson (ondemand) | 1273.97 | 0.126142 | 611.83ms | 8150 | 4890 | 289617 | 6100.97 | 0.396721 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1897.77 | 0.0552782 | 447.523ms | 8150 | 160 | 820.082 | 4095.57 | 0.0207498 | 1(Win) | true |
| simdjson (ondemand) | 1442.88 | 0.0869273 | 572.31ms | 8150 | 4890 | 107221 | 5386.77 | 0.0138262 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 743.075 | 0.0349628 | 641.534ms | 4926 | 160 | 781.731 | 6322.11 | 0.00326247 | 1(Win) | true |
| simdjson (ondemand) | 338.489 | 0.0928396 | 1392.14ms | 4926 | 4890 | 811848 | 13878.7 | 0.451524 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 830.861 | 0.0803878 | 604.869ms | 4926 | 30 | 619.775 | 5654.13 | 0.0730495 | 1(Win) | true |
| simdjson (ondemand) | 355.551 | 0.167836 | 1350.22ms | 4926 | 2560 | 1.25891e+06 | 13212.7 | 0.0611961 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1115.82 | 0.0561333 | 708.639ms | 8150 | 40 | 611.549 | 6965.7 | 0.0153108 | 1(Win) | true |
| simdjson (ondemand) | 552.247 | 0.103982 | 1407.31ms | 8150 | 4890 | 1.04731e+06 | 14074.2 | 0.401238 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1224.12 | 0.0938011 | 695.727ms | 8150 | 4890 | 173456 | 6349.39 | 0.128576 | 1(Win) | true |
| simdjson (ondemand) | 583.32 | 0.134855 | 1367.94ms | 8150 | 2560 | 826560 | 13324.5 | 0.00947707 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1713.8 | 0.0664063 | 280.424ms | 4926 | 160 | 530.162 | 2741.16 | 0.207055 | 1(Win) | true |
| simdjson (ondemand) | 1358.18 | 0.0508371 | 350.237ms | 4926 | 320 | 989.425 | 3458.88 | 0.00768009 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1957.42 | 0.0757102 | 257.199ms | 4926 | 160 | 528.264 | 2400 | 0.0203084 | 1(Win) | true |
| simdjson (ondemand) | 1471.93 | 0.172267 | 336.065ms | 4926 | 30 | 906.869 | 3191.6 | 0.132464 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2483.07 | 0.104151 | 317.389ms | 8150 | 80 | 850.273 | 3130.18 | 0.0999344 | 1(Win) | true |
| simdjson (ondemand) | 2115.66 | 0.0683846 | 374.758ms | 8150 | 160 | 1009.86 | 3673.76 | 0.0514043 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2849.5 | 0.0898072 | 294.132ms | 8150 | 80 | 480.053 | 2727.65 | 0.0926563 | 1(Win) | true |
| simdjson (ondemand) | 2267.15 | 0.0516269 | 361.303ms | 8150 | 320 | 1002.44 | 3428.29 | 0.126955 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1437.58 | 0.344488 | 330.716ms | 4926 | 640 | 81106.2 | 3267.85 | 0.491641 | 1(Win) | true |
| simdjson (ondemand) | 1000.77 | 0.0333498 | 478.381ms | 4926 | 640 | 1568.51 | 4694.2 | 0.0121811 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1636.39 | 0.127073 | 305.617ms | 4926 | 30 | 399.247 | 2870.83 | 0.0475826 | 1(Win) | true |
| simdjson (ondemand) | 1034.35 | 0.176631 | 506.272ms | 4926 | 40 | 2574.23 | 4541.77 | 0.246656 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2161.57 | 0.0501368 | 365.96ms | 8150 | 160 | 520.006 | 3595.74 | 0.200639 | 1(Win) | true |
| simdjson (ondemand) | 1572.57 | 0.242608 | 496.718ms | 8150 | 2560 | 368086 | 4942.52 | 0.00665506 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2379.47 | 0.128683 | 346.344ms | 8150 | 2560 | 45231.4 | 3266.47 | 0.112774 | 1(Win) | true |
| simdjson (ondemand) | 1696.7 | 0.300798 | 472.616ms | 8150 | 640 | 121517 | 4580.92 | 0.021143 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1762.88 | 0.177493 | 159.156ms | 2821 | 80 | 586.967 | 1526.09 | 0.133333 | 1(Win) | true |
| simdjson (ondemand) | 1474.46 | 0.0830298 | 187.286ms | 2821 | 320 | 734.44 | 1824.61 | 0.0328946 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1989.33 | 0.059283 | 149.843ms | 2821 | 2560 | 1645.48 | 1352.37 | 0.400462 | 1(Win) | true |
| simdjson (ondemand) | 1624.52 | 0.126097 | 180.462ms | 2821 | 2560 | 11163.7 | 1656.07 | 0.239987 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2158.2 | 0.0797249 | 170.709ms | 3770 | 320 | 564.468 | 1665.91 | 0.0611155 | 1(Win) | true |
| simdjson (ondemand) | 1921.96 | 0.0811596 | 192.143ms | 3770 | 320 | 737.607 | 1870.67 | 0.241303 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2457 | 0.0663872 | 162.286ms | 3770 | 320 | 301.989 | 1463.31 | 0.0335172 | 1(Win) | true |
| simdjson (ondemand) | 2084.76 | 0.0765173 | 187.482ms | 3770 | 320 | 557.239 | 1724.59 | 0.0993813 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 731.877 | 0.0430848 | 391.853ms | 2821 | 320 | 802.653 | 3675.91 | 0.081594 | 1(Win) | true |
| simdjson (ondemand) | 216.842 | 0.0551062 | 1268.54ms | 2821 | 80 | 3739.49 | 12406.8 | 0.046972 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 726.373 | 0.809473 | 388.459ms | 2821 | 320 | 287635 | 3703.77 | 1.8802 | 1(Win) | true |
| simdjson (ondemand) | 218.286 | 0.0386612 | 1256.52ms | 2821 | 160 | 3632.68 | 12324.7 | 0.0611441 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 812.789 | 0.370635 | 432.845ms | 3770 | 2560 | 688113 | 4423.48 | 0.31038 | 1(Win) | true |
| simdjson (ondemand) | 281.459 | 0.0958661 | 1283.57ms | 3770 | 4890 | 733317 | 12774 | 0.161845 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 978.741 | 0.0321564 | 387.777ms | 3770 | 640 | 893.021 | 3673.45 | 0.0565395 | 1(Win) | true |
| simdjson (ondemand) | 288.43 | 0.0700751 | 1280.28ms | 3770 | 30 | 2289.03 | 12465.3 | 0.13326 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4084.51 | 0.152274 | 69.3765ms | 2821 | 320 | 321.905 | 658.663 | 0.0275255 | 1(Win) | true |
| simdjson (ondemand) | 3418.97 | 0.109692 | 81.8842ms | 2821 | 640 | 476.808 | 786.878 | 0.350308 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4312.2 | 0.0759682 | 68.0023ms | 2821 | 640 | 143.764 | 623.884 | 0.0907441 | 1(Win) | true |
| simdjson (ondemand) | 3611.52 | 0.154861 | 80.4445ms | 2821 | 320 | 425.85 | 744.925 | 0.0201403 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4591.55 | 0.127176 | 81.8307ms | 3770 | 320 | 317.34 | 783.038 | 0.0271453 | 1(Win) | true |
| simdjson (ondemand) | 4191.26 | 0.146928 | 89.7859ms | 3770 | 320 | 508.341 | 857.822 | 0.0564338 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4818.08 | 0.0504743 | 80.7061ms | 3770 | 1280 | 181.588 | 746.221 | 0.0258661 | 1(Win) | true |
| simdjson (ondemand) | 4422.36 | 0.208056 | 87.2055ms | 3770 | 160 | 457.78 | 812.994 | 0.0684668 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3069.67 | 0.0821212 | 91.0351ms | 2821 | 320 | 165.761 | 876.419 | 0.0769587 | 1(Win) | true |
| simdjson (ondemand) | 2396.94 | 0.0618438 | 116.62ms | 2821 | 640 | 308.365 | 1122.4 | 0.0229646 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3200.3 | 0.161796 | 91.3822ms | 2821 | 160 | 295.992 | 840.644 | 0.000743483 | 1(Win) | true |
| simdjson (ondemand) | 2500.02 | 0.0774637 | 114.214ms | 2821 | 640 | 444.73 | 1076.12 | 0.060875 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3610.34 | 0.103359 | 104.397ms | 3770 | 4890 | 5180.75 | 995.849 | 0.0313265 | 1(Win) | true |
| simdjson (ondemand) | 3022.41 | 0.100016 | 123.116ms | 3770 | 320 | 452.967 | 1189.57 | 0.0443768 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3777.55 | 0.137498 | 101.511ms | 3770 | 160 | 274.015 | 951.769 | 0.227347 | 1(Win) | true |
| simdjson (ondemand) | 3128.69 | 0.0451998 | 121.983ms | 3770 | 4890 | 1319.29 | 1149.15 | 0.0713228 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3821.53 | 0.165856 | 7041.63ms | 277673 | 320 | 4.22676e+06 | 69294.2 | 0.0179927 | 1(Win) | true |
| simdjson (ondemand) | 3155.13 | 0.059825 | 8461.59ms | 277673 | 4890 | 1.23284e+07 | 83929.8 | 0.286558 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3333.56 | 0.231664 | 9465.38ms | 10548466 | 30 | 1.46622e+09 | 3.01774e+06 | 0.544933 | 1(Win) | true |
| simdjson (ondemand) | 2870.35 | 0.198427 | 5280.64ms | 10548466 | 30 | 1.45087e+09 | 3.50473e+06 | 0.410491 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2493.06 | 0.190517 | 9245.82ms | 16002592 | 80 | 1.08812e+10 | 6.1215e+06 | 0.0403465 | 1(Win) | true |
| simdjson (ondemand) | 2152.42 | 0.189629 | 5017.94ms | 16002592 | 40 | 7.23096e+09 | 7.09028e+06 | 0.409308 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2513.39 | 0.122298 | 9173.51ms | 16002591 | 80 | 4.41153e+09 | 6.07199e+06 | 0.0407087 | 1(Win) | true |
| simdjson (ondemand) | 1427.48 | 0.161713 | 7561.39ms | 16002591 | 30 | 8.96711e+09 | 1.0691e+07 | 0.0569078 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 9712.68 | 0.142301 | 10083.8ms | 16197086 | 320 | 1.63892e+09 | 1.59037e+06 | 0.117887 | 1(Win) | true |
| simdjson (ondemand) | 8680.6 | 0.198175 | 5564.29ms | 16197086 | 160 | 1.98972e+09 | 1.77946e+06 | 0.216829 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 9733.48 | 0.129762 | 10048.2ms | 16197085 | 320 | 1.357e+09 | 1.58697e+06 | 0.149393 | 1(Win) | true |
| simdjson (ondemand) | 8451.4 | 0.245411 | 5694.14ms | 16197085 | 30 | 6.03571e+08 | 1.82772e+06 | 0.281889 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1304.02 | 0.421952 | 5662.23ms | 4212000 | 80 | 1.35154e+10 | 3.08039e+06 | 2.23723 | 1(Win) | true |
| simdjson (ondemand) | 1083.88 | 0.173056 | 6769.29ms | 4212000 | 80 | 3.2906e+09 | 3.70601e+06 | 0.115021 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1296.67 | 0.144443 | 5790.44ms | 4211999 | 80 | 1.60177e+09 | 3.09785e+06 | 0.177915 | 1(Win) | true |
| simdjson (ondemand) | 966.143 | 0.157767 | 7458.16ms | 4211999 | 80 | 3.44203e+09 | 4.15764e+06 | 0.0755584 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1163.49 | 0.163149 | 6357.59ms | 4212000 | 40 | 1.26906e+09 | 3.45244e+06 | 0.0990554 | 1(Win) | true |
| simdjson (ondemand) | 928.832 | 0.146012 | 7684.04ms | 4212000 | 80 | 3.18986e+09 | 4.32466e+06 | 0.337169 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1160.02 | 0.22892 | 6369.06ms | 4211999 | 40 | 2.51345e+09 | 3.46275e+06 | 0.249289 | 1(Win) | true |
| simdjson (ondemand) | 841.058 | 0.190079 | 8362.01ms | 4211999 | 80 | 6.593e+09 | 4.77598e+06 | 0.394853 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1030.78 | 0.167448 | 6739.07ms | 4525120 | 30 | 1.47439e+09 | 4.18663e+06 | 0.455488 | 1(Win) | true |
| simdjson (ondemand) | 903.027 | 0.174442 | 7588.4ms | 4525120 | 40 | 2.77985e+09 | 4.77892e+06 | 0.287121 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 906.125 | 0.231531 | 7556.38ms | 4525119 | 80 | 9.72726e+09 | 4.76257e+06 | 0.181481 | 1(Win) | true |
| simdjson (ondemand) | 716.023 | 0.133432 | 9456.74ms | 4525119 | 80 | 5.17386e+09 | 6.02702e+06 | 0.0649407 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 612.348 | 0.119703 | 5133.38ms | 4525120 | 40 | 2.84665e+09 | 7.04745e+06 | 0.532865 | 1(Win) | true |
| simdjson (ondemand) | 417.667 | 0.120669 | 7468.37ms | 4525120 | 40 | 6.21804e+09 | 1.03324e+07 | 0.242591 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 610.083 | 0.190004 | 5271.71ms | 4525119 | 30 | 5.41913e+09 | 7.07361e+06 | 0.11009 | 1(Win) | true |
| simdjson (ondemand) | 371.789 | 0.202362 | 8380.49ms | 4525119 | 30 | 1.65519e+10 | 1.16074e+07 | 2.03788 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 876.364 | 0.159781 | 7032.52ms | 4203059 | 80 | 4.27269e+09 | 4.57384e+06 | 0.029205 | 1(Win) | true |
| simdjson (ondemand) | 810.479 | 0.134614 | 7624.07ms | 4203059 | 40 | 1.77291e+09 | 4.94565e+06 | 0.405572 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 781.916 | 0.133586 | 7882.07ms | 4203058 | 30 | 1.40688e+09 | 5.12632e+06 | 0.445936 | 1(Win) | true |
| simdjson (ondemand) | 681.063 | 0.294007 | 9023.98ms | 4203058 | 30 | 8.98243e+09 | 5.88543e+06 | 0.268449 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 678.862 | 0.129436 | 9046.51ms | 4203059 | 40 | 2.33636e+09 | 5.90452e+06 | 0.13608 | 1(Win) | true |
| simdjson (ondemand) | 607.27 | 0.167491 | 10130.4ms | 4203059 | 40 | 4.88888e+09 | 6.60061e+06 | 0.615441 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 625.083 | 0.153627 | 9868.15ms | 4203058 | 40 | 3.88197e+09 | 6.4125e+06 | 0.7651 | 1(Win) | true |
| simdjson (ondemand) | 529.367 | 0.103535 | 5384.57ms | 4203058 | 40 | 2.45838e+09 | 7.57197e+06 | 0.201271 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1346.06 | 0.0935824 | 9471.57ms | 4197496 | 30 | 2.3236e+08 | 2.97389e+06 | 1.26266 | 1(Win) | true |
| simdjson (ondemand) | 1104.12 | 0.1538 | 5582.91ms | 4197496 | 40 | 1.24372e+09 | 3.62555e+06 | 0.221035 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1180.15 | 0.29343 | 5155.57ms | 4197495 | 80 | 7.92515e+09 | 3.39198e+06 | 0.305259 | 1(Win) | true |
| simdjson (ondemand) | 849.897 | 0.298259 | 7198.77ms | 4197495 | 30 | 5.92048e+09 | 4.71003e+06 | 0.0369603 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 814.707 | 0.163518 | 7499.84ms | 4197496 | 30 | 1.93655e+09 | 4.91348e+06 | 0.163705 | 1(Win) | true |
| simdjson (ondemand) | 524.962 | 0.143144 | 5384.2ms | 4197496 | 40 | 4.76578e+09 | 7.6254e+06 | 0.083086 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 804.548 | 0.128456 | 7604.14ms | 4197495 | 80 | 3.26795e+09 | 4.97552e+06 | 0.0349664 | 1(Win) | true |
| simdjson (ondemand) | 461.271 | 0.10247 | 6130.16ms | 4197495 | 40 | 3.16314e+09 | 8.67828e+06 | 0.00985159 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1163.66 | 0.301088 | 6055.84ms | 4506447 | 80 | 9.89218e+09 | 3.69324e+06 | 0.706377 | 1(Win) | true |
| simdjson (ondemand) | 776.809 | 0.25311 | 8914.05ms | 4506447 | 80 | 1.56873e+10 | 5.53248e+06 | 0.347768 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1071.95 | 0.151477 | 6578.16ms | 4506446 | 40 | 1.47526e+09 | 4.00921e+06 | 0.0735814 | 1(Win) | true |
| simdjson (ondemand) | 671.966 | 0.202777 | 10151.3ms | 4506446 | 40 | 6.7278e+09 | 6.39568e+06 | 0.317721 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 731.329 | 0.229319 | 9293.04ms | 4506447 | 80 | 1.45283e+10 | 5.87654e+06 | 0.0953453 | 1(Win) | true |
| simdjson (ondemand) | 355.538 | 0.204788 | 8753.32ms | 4506447 | 40 | 2.45114e+10 | 1.20878e+07 | 0.104135 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 726.166 | 0.129287 | 9423.33ms | 4506446 | 80 | 4.6838e+09 | 5.91832e+06 | 0.086785 | 1(Win) | true |
| simdjson (ondemand) | 331.047 | 0.191805 | 9390.96ms | 4506446 | 40 | 2.4801e+10 | 1.29821e+07 | 0.128414 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1659.87 | 0.106119 | 8396.98ms | 4219120 | 160 | 1.05876e+09 | 2.42409e+06 | 0.146662 | 1(Win) | true |
| simdjson (ondemand) | 1417.36 | 0.24251 | 9741.61ms | 4219120 | 160 | 7.58343e+09 | 2.83885e+06 | 1.40288 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1510.43 | 0.213411 | 9202.54ms | 4219119 | 30 | 9.69607e+08 | 2.66391e+06 | 0.17908 | 1(Win) | true |
| simdjson (ondemand) | 1224.79 | 0.128913 | 5366.84ms | 4219119 | 80 | 1.43484e+09 | 3.28519e+06 | 0.559774 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 685.215 | 0.282759 | 9289.24ms | 4219120 | 80 | 2.20553e+10 | 5.87212e+06 | 0.263916 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 195.435 | 0.25256 | 6313.21ms | 4219120 | 30 | 8.11132e+10 | 2.05883e+07 | 5.83984 | -(Loss) | false |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 682.816 | 0.166422 | 9287.56ms | 4219119 | 80 | 7.69395e+09 | 5.89275e+06 | 0.116798 | 1(Win) | true |
| simdjson (ondemand) | 189.99 | 0.433263 | 6405.99ms | 4219119 | 30 | 2.52583e+11 | 2.11783e+07 | 0.79999 | 2(Loss) | true |
