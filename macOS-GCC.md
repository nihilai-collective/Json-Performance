# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

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

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 861.353 | 1.32158 | 111.718ms | 905 | 640 | 112229 | 1002 | 0.280224 | 1(Win) | true |
| simdjson (ondemand) | 400.165 | 0.359977 | 223.403ms | 905 | 2560 | 154316 | 2156.8 | 0.46151 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 915.792 | 0.430959 | 102.011ms | 905 | 4890 | 80664.7 | 942.436 | 0.0810017 | 1(Win) | true |
| simdjson (ondemand) | 408.016 | 0.328481 | 212.925ms | 905 | 2560 | 123596 | 2115.3 | 0.0803023 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 581.595 | 0.356976 | 290.268ms | 1811 | 1280 | 143841 | 2969.6 | 0.270124 | 1(Win) | true |
| simdjson (ondemand) | 308.5 | 0.789445 | 617.592ms | 1811 | 160 | 312530 | 5598.4 | 0.878187 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 668.281 | 0.458912 | 261.889ms | 1811 | 2560 | 360096 | 2584.4 | 0.147253 | 1(Win) | true |
| simdjson (ondemand) | 316.244 | 0.212861 | 557.913ms | 1811 | 2560 | 345960 | 5461.3 | 0.663902 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 669.29 | 0.426274 | 189.794ms | 1313 | 2560 | 162824 | 1870.9 | 0.250586 | 1(Win) | true |
| simdjson (ondemand) | 310.128 | 0.341623 | 410.654ms | 1313 | 320 | 60882.1 | 4037.6 | 0.0198098 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 795.587 | 0.660202 | 162.699ms | 1313 | 2560 | 276406 | 1573.9 | 0.478805 | 1(Win) | true |
| simdjson (ondemand) | 332.883 | 0.895646 | 396.531ms | 1313 | 320 | 363219 | 3761.6 | 0.339127 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 604.654 | 0.444098 | 673.589ms | 4215 | 320 | 278926 | 6648 | 0.144613 | 1(Win) | true |
| simdjson (ondemand) | 486.981 | 0.536937 | 873.672ms | 4215 | 640 | 1.25718e+06 | 8254.4 | 0.398949 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 852.434 | 0.48186 | 586.332ms | 4215 | 640 | 330443 | 4715.6 | 1.0824 | 1(Win) | true |
| simdjson (ondemand) | 672.658 | 0.21162 | 704.912ms | 4215 | 4890 | 782042 | 5975.9 | 0.565414 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 614.535 | 0.466751 | 195.002ms | 1213 | 4890 | 377493 | 1882.41 | 0.0418728 | 1(Win) | true |
| simdjson (ondemand) | 261.614 | 0.279238 | 439.188ms | 1213 | 2560 | 390288 | 4421.8 | 0.144947 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 751.271 | 0.922898 | 160.392ms | 1213 | 1280 | 258492 | 1539.8 | 0.14308 | 1(Win) | true |
| simdjson (ondemand) | 303.783 | 0.345498 | 390.23ms | 1213 | 1280 | 221562 | 3808 | 0.021004 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1014.08 | 0.160892 | 9004.1ms | 94653 | 1280 | 2.62544e+07 | 89014.8 | 0.214335 | 1(Win) | true |
| simdjson (ondemand) | 731.708 | 0.427403 | 6364.11ms | 94653 | 30 | 8.34047e+06 | 123366 | 0.194054 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1559.68 | 0.180266 | 7649.78ms | 94653 | 640 | 6.96631e+06 | 57876 | 0.136657 | 1(Win) | true |
| simdjson (ondemand) | 946.405 | 0.42489 | 5806.85ms | 94653 | 320 | 5.25554e+07 | 95380 | 0.178974 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1198.3 | 0.467411 | 9513.01ms | 124597 | 320 | 6.87439e+07 | 99161.6 | 0.31076 | 1(Win) | true |
| simdjson (ondemand) | 980.598 | 0.131657 | 6691.28ms | 124597 | 160 | 4.07234e+06 | 121176 | 0.22265 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1905.91 | 0.337646 | 8253.11ms | 124597 | 160 | 7.09016e+06 | 62345.6 | 0.0976161 | 1(Win) | true |
| simdjson (ondemand) | 1198.53 | 0.413127 | 6101.22ms | 124597 | 80 | 1.34207e+07 | 99142.4 | 0.135379 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 830.868 | 0.225312 | 5640.37ms | 94653 | 160 | 9.58721e+06 | 108643 | 0.305388 | 1(Win) | true |
| simdjson (ondemand) | 489.011 | 0.0844355 | 9778.38ms | 94653 | 640 | 1.55475e+07 | 184593 | 0.0729722 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1125.74 | 0.275993 | 5093.93ms | 94653 | 160 | 7.83625e+06 | 80185.6 | 0.0239502 | 1(Win) | true |
| simdjson (ondemand) | 568.026 | 0.0910441 | 9292.98ms | 94653 | 1280 | 2.67946e+07 | 158916 | 0.429485 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1047.26 | 0.122807 | 5872.37ms | 124597 | 640 | 1.2426e+07 | 113463 | 0.249327 | 1(Win) | true |
| simdjson (ondemand) | 609.474 | 0.208382 | 5010.29ms | 124597 | 160 | 2.64086e+07 | 194963 | 0.299465 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1452.42 | 0.123837 | 5369.16ms | 124597 | 1280 | 1.31385e+07 | 81811.8 | 0.194727 | 1(Win) | true |
| simdjson (ondemand) | 706.484 | 0.519514 | 9665.47ms | 124597 | 40 | 3.05398e+07 | 168192 | 0.417771 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1601.09 | 0.166588 | 5682.64ms | 94653 | 640 | 5.64551e+06 | 56379.2 | 0.0454274 | 1(Win) | true |
| simdjson (ondemand) | 1092.77 | 0.20868 | 8478.96ms | 94653 | 80 | 2.37717e+06 | 82604.8 | 0.470389 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2390.93 | 0.215198 | 4852.84ms | 94653 | 320 | 2.11232e+06 | 37754.4 | 0.221997 | 1(Win) | true |
| simdjson (ondemand) | 1272.55 | 0.109009 | 7870.3ms | 94653 | 2560 | 1.53068e+07 | 70935 | 0.127278 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2037.36 | 0.0623963 | 6072ms | 124597 | 4890 | 6.47596e+06 | 58322.9 | 0.627811 | 1(Win) | true |
| simdjson (ondemand) | 1355.72 | 0.165821 | 8716.65ms | 124597 | 1280 | 2.70376e+07 | 87647.2 | 0.0182583 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2677.83 | 0.141094 | 5319.8ms | 124597 | 1280 | 5.01737e+06 | 44373.6 | 0.0414833 | 1(Win) | true |
| simdjson (ondemand) | 1754.75 | 0.163751 | 7976.14ms | 124597 | 320 | 3.93461e+06 | 67716 | 0.0508262 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1323.21 | 0.269468 | 6885.82ms | 94653 | 160 | 5.4069e+06 | 68219.2 | 0.190337 | 1(Win) | true |
| simdjson (ondemand) | 929.074 | 0.189669 | 9604.27ms | 94653 | 320 | 1.0867e+07 | 97159.2 | 0.432052 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1795.94 | 0.0848306 | 6064.65ms | 94653 | 1280 | 2.32703e+06 | 50262.4 | 0.113673 | 1(Win) | true |
| simdjson (ondemand) | 1106.61 | 0.0792276 | 9101.83ms | 94653 | 4890 | 2.04239e+07 | 81571.4 | 0.251506 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1632.35 | 0.223777 | 7318.08ms | 124597 | 160 | 4.24558e+06 | 72793.6 | 0.0439406 | 1(Win) | true |
| simdjson (ondemand) | 1210.27 | 0.0751886 | 9729.3ms | 124597 | 4890 | 2.66478e+07 | 98180.3 | 0.187959 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2184.81 | 0.0555557 | 6537.3ms | 124597 | 4890 | 4.4643e+06 | 54386.8 | 0.142065 | 1(Win) | true |
| simdjson (ondemand) | 1510.82 | 0.133025 | 8934.61ms | 124597 | 640 | 7.00538e+06 | 78649.2 | 0.0767378 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 524.768 | 0.111727 | 5838.36ms | 2090234 | 30 | 5.40377e+08 | 3.79864e+06 | 4.73991 | 1(Win) | true |
| simdjson (ondemand) | 519.263 | 0.133722 | 5812.94ms | 2090234 | 30 | 7.90572e+08 | 3.83891e+06 | 4.8252 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 620.422 | 0.392901 | 5864.33ms | 2090234 | 30 | 4.78083e+09 | 3.21298e+06 | 4.62559 | 1(Win) | true |
| Jsonifier (generic) | 604.29 | 0.483475 | 5771.94ms | 2090234 | 80 | 2.03487e+10 | 3.29875e+06 | 0.01387 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1267.51 | 0.378382 | 6050.9ms | 5212421 | 80 | 1.76168e+10 | 3.92182e+06 | 0.539919 | 1(Win) | true |
| simdjson (ondemand) | 1183.08 | 0.215844 | 6237.09ms | 5212421 | 80 | 6.57993e+09 | 4.2017e+06 | 0.0735922 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1427.65 | 0.783621 | 6090.94ms | 5212421 | 30 | 2.23341e+10 | 3.48191e+06 | 1.89106 | 1(Win) | true |
| simdjson (ondemand) | 1350.41 | 0.275935 | 6415.16ms | 5212421 | 80 | 8.25373e+09 | 3.68107e+06 | 0.148961 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 488.807 | 0.0983878 | 6173.12ms | 2090234 | 30 | 4.82968e+08 | 4.0781e+06 | 1.03397 | 1(Win) | true |
| simdjson (ondemand) | 470.084 | 0.511984 | 6424.22ms | 2090234 | 40 | 1.88544e+10 | 4.24052e+06 | 0.736157 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 572.647 | 0.336018 | 6048.08ms | 2090234 | 80 | 1.09454e+10 | 3.48103e+06 | 0.825525 | 1(Win) | true |
| simdjson (ondemand) | 558.71 | 0.210611 | 6394.95ms | 2090234 | 40 | 2.25859e+09 | 3.56787e+06 | 0.178283 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1105.56 | 0.429264 | 6751.93ms | 5212421 | 30 | 1.1176e+10 | 4.49633e+06 | 1.91307 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1069.19 | 0.198009 | 6851.42ms | 5212421 | 80 | 6.78003e+09 | 4.64929e+06 | 5.5618 | -(Loss) | false |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1279.5 | 0.298185 | 6545.91ms | 5212421 | 80 | 1.07365e+10 | 3.88509e+06 | 5.07053 | -(Win) | false |
| simdjson (ondemand) | 1187.87 | 0.29033 | 7155.1ms | 5212421 | 40 | 5.90455e+09 | 4.18476e+06 | 0.489073 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4693.4 | 0.109017 | 5628.99ms | 2090234 | 320 | 6.86045e+07 | 424725 | 0.0831847 | 1(Win) | true |
| simdjson (ondemand) | 3569.03 | 0.271002 | 7094.22ms | 2090234 | 40 | 9.1642e+07 | 558528 | 0.112421 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4479.31 | 0.203972 | 5786.96ms | 2090234 | 40 | 3.29585e+07 | 445024 | 1.46197 | 1(Win) | true |
| simdjson (ondemand) | 3548.41 | 0.199837 | 7202.67ms | 2090234 | 40 | 5.04119e+07 | 561773 | 0.0954082 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6892.64 | 0.281472 | 9486.79ms | 5212421 | 40 | 1.64831e+08 | 721197 | 0.576275 | 1(Win) | true |
| simdjson (ondemand) | 5453.82 | 0.141342 | 5835.47ms | 5212421 | 80 | 1.32774e+08 | 911462 | 0.144438 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6768.37 | 0.733167 | 9702.58ms | 5212421 | 30 | 8.69836e+08 | 734438 | 1.77856 | 1(Win) | true |
| simdjson (ondemand) | 5360.92 | 0.592245 | 5800.04ms | 5212421 | 30 | 9.04742e+08 | 927258 | 0.847332 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3673.37 | 0.15044 | 7192.18ms | 2090234 | 160 | 1.06637e+08 | 542662 | 0.101529 | 1(Win) | true |
| simdjson (ondemand) | 2919.96 | 0.101913 | 8497.16ms | 2090234 | 640 | 3.09798e+08 | 682682 | 0.0111338 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3660.55 | 0.347581 | 7263.02ms | 2090234 | 30 | 1.07481e+08 | 544563 | 0.0313303 | 1(Win) | true |
| simdjson (ondemand) | 2928.42 | 0.146453 | 8665.85ms | 2090234 | 320 | 3.18031e+08 | 680709 | 0.0893985 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5637.29 | 0.574791 | 5650.8ms | 5212421 | 40 | 1.02759e+09 | 881798 | 0.754171 | 1(Win) | true |
| simdjson (ondemand) | 4952.28 | 0.0958952 | 6496.86ms | 5212421 | 40 | 3.70614e+07 | 1.00377e+06 | 0.069972 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5500.01 | 0.253552 | 5586.61ms | 5212421 | 160 | 8.40243e+08 | 903808 | 0.156955 | 1(Win) | true |
| simdjson (ondemand) | 4939.59 | 0.233132 | 6652.67ms | 5212421 | 40 | 2.20171e+08 | 1.00635e+06 | 0.0818942 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 962.337 | 0.571908 | 6148.38ms | 500299 | 40 | 3.21601e+08 | 495795 | 0.220792 | 1(Win) | true |
| simdjson (ondemand) | 879.142 | 0.0633961 | 7015.89ms | 500299 | 160 | 1.89403e+07 | 542714 | 0.0135596 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1045.25 | 1.49771 | 6256.64ms | 500299 | 40 | 1.86954e+09 | 456467 | 1.47829 | 1(Win) | true |
| simdjson (ondemand) | 935.425 | 0.381043 | 7074.16ms | 500299 | 160 | 6.0438e+08 | 510059 | 0.310526 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2046.89 | 0.0641969 | 7133.14ms | 1151920 | 320 | 3.7987e+07 | 536696 | 0.452576 | 1(Win) | true |
| simdjson (ondemand) | 1678.97 | 0.34465 | 8160.77ms | 1151920 | 160 | 8.13648e+08 | 654306 | 0.0545608 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2223.17 | 0.221542 | 6943.49ms | 1151920 | 30 | 3.5953e+07 | 494140 | 0.176455 | 1(Win) | true |
| simdjson (ondemand) | 1896.96 | 0.114524 | 8135.04ms | 1151920 | 320 | 1.40759e+08 | 579115 | 0.0157457 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 548.567 | 0.0580236 | 5668.89ms | 500299 | 160 | 4.07502e+07 | 869762 | 0.225209 | 1(Win) | true |
| simdjson (ondemand) | 290.079 | 0.358131 | 10385.2ms | 500299 | 30 | 1.04096e+09 | 1.6448e+06 | 0.933141 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 552.285 | 0.282088 | 5870.48ms | 500299 | 30 | 1.78165e+08 | 863906 | 0.127584 | 1(Win) | true |
| simdjson (ondemand) | 292.377 | 0.548129 | 5391.42ms | 500299 | 40 | 3.20035e+09 | 1.63187e+06 | 3.42935 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1063.41 | 0.725786 | 6793.61ms | 1151920 | 40 | 2.24864e+09 | 1.03305e+06 | 0.162876 | 1(Win) | true |
| simdjson (ondemand) | 571.027 | 0.221195 | 5769.89ms | 1151920 | 40 | 7.24337e+08 | 1.92383e+06 | 0.621752 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1090.21 | 0.458994 | 6716.27ms | 1151920 | 40 | 8.55653e+08 | 1.00765e+06 | 0.716881 | 1(Win) | true |
| simdjson (ondemand) | 645.623 | 0.10382 | 5463.79ms | 1151920 | 80 | 2.49652e+08 | 1.70155e+06 | 0.124465 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3017.7 | 0.234369 | 8266.48ms | 500299 | 320 | 4.394e+07 | 158108 | 0.214581 | 1(Win) | true |
| simdjson (ondemand) | 2759 | 0.137266 | 8785.89ms | 500299 | 2560 | 1.44252e+08 | 172933 | 0.0780041 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3071.15 | 0.116599 | 8132.05ms | 500299 | 1280 | 4.20008e+07 | 155356 | 0.251021 | 1(Win) | true |
| simdjson (ondemand) | 2909.85 | 0.662511 | 8531.4ms | 500299 | 30 | 3.54019e+07 | 163968 | 0.0364166 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4929.06 | 0.512742 | 5552.36ms | 1151920 | 40 | 5.22366e+07 | 222874 | 0.365062 | 1(Win) | true |
| simdjson (ondemand) | 4726.39 | 0.107099 | 6592.33ms | 1151920 | 160 | 9.91458e+06 | 232430 | 0.0309674 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5023.18 | 0.565264 | 5634.75ms | 1151920 | 80 | 1.22259e+08 | 218698 | 0.513858 | 1(Win) | true |
| simdjson (ondemand) | 4332.12 | 0.175112 | 6379.04ms | 1151920 | 320 | 6.30996e+07 | 253584 | 0.0283849 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1994.23 | 0.17012 | 6336.71ms | 500299 | 80 | 1.32528e+07 | 239251 | 0.0401413 | 1(Win) | true |
| simdjson (ondemand) | 1723.1 | 1.2288 | 7088.69ms | 500299 | 30 | 3.47316e+08 | 276898 | 1.07778 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1828.71 | 0.413754 | 6915.15ms | 500299 | 30 | 3.49604e+07 | 260907 | 0.0914943 | 1(Win) | true |
| simdjson (ondemand) | 1732.39 | 0.265369 | 6938.16ms | 500299 | 1280 | 6.83715e+08 | 275412 | 1.74691 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3556.21 | 0.342284 | 8444.55ms | 1151920 | 80 | 8.94402e+07 | 308912 | 2.09631 | 1(Win) | true |
| simdjson (ondemand) | 3065.07 | 0.31969 | 9441.53ms | 1151920 | 160 | 2.10059e+08 | 358411 | 0.462568 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3394.04 | 0.451163 | 8444.62ms | 1151920 | 160 | 3.4119e+08 | 323672 | 0.222446 | 1(Win) | true |
| simdjson (ondemand) | 3097.77 | 0.299864 | 9204.01ms | 1151920 | 30 | 3.39247e+07 | 354628 | 0.00721935 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1227.94 | 0.177366 | 4337.18ms | 56369 | 4890 | 2.94832e+07 | 43778.6 | 0.328382 | 1(Win) | true |
| simdjson (ondemand) | 752.885 | 0.370338 | 6893.09ms | 56369 | 1280 | 8.95012e+07 | 71402.2 | 1.33376 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1513.92 | 0.392437 | 3975.58ms | 56369 | 1280 | 2.48558e+07 | 35509 | 0.227501 | 1(Win) | true |
| simdjson (ondemand) | 1096.69 | 0.0585061 | 5524.97ms | 56369 | 2560 | 2.10552e+06 | 49018.3 | 0.137075 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1626.19 | 0.28914 | 4805.11ms | 83958 | 160 | 3.24277e+06 | 49236.8 | 0.0552127 | 1(Win) | true |
| simdjson (ondemand) | 1217.35 | 0.567873 | 6801.66ms | 83958 | 40 | 5.58026e+06 | 65772.8 | 0.309084 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2074.14 | 0.099574 | 4427.14ms | 83958 | 1280 | 1.89125e+06 | 38603.2 | 0.00932652 | 1(Win) | true |
| simdjson (ondemand) | 1434.41 | 0.304155 | 6077.53ms | 83958 | 320 | 9.224e+06 | 55820 | 0.176592 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 617.828 | 0.0675539 | 9108.64ms | 56369 | 1280 | 4.42239e+06 | 87010.8 | 0.178509 | 1(Win) | true |
| simdjson (ondemand) | 159.893 | 0.0762131 | 8773.45ms | 56369 | 640 | 4.20205e+07 | 336210 | 0.222223 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 655.677 | 0.17875 | 8643.15ms | 56369 | 320 | 6.87294e+06 | 81988 | 0.104515 | 1(Win) | true |
| simdjson (ondemand) | 158.605 | 0.290566 | 8571.67ms | 56369 | 80 | 7.75938e+07 | 338941 | 0.465721 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 801.086 | 0.0766298 | 5344.28ms | 83958 | 640 | 3.75441e+06 | 99950 | 0.0308249 | 1(Win) | true |
| simdjson (ondemand) | 234.301 | 0.392748 | 8669.7ms | 83958 | 40 | 7.20553e+07 | 341734 | 0.457359 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 861.066 | 0.701419 | 5108.65ms | 83958 | 30 | 1.27623e+07 | 92987.7 | 0.898148 | 1(Win) | true |
| simdjson (ondemand) | 251.477 | 0.0493826 | 8474.73ms | 83958 | 1280 | 3.16437e+07 | 318394 | 0.0115567 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1727.88 | 0.329304 | 3183.69ms | 56369 | 320 | 3.35891e+06 | 31112 | 0.531997 | 1(Win) | true |
| simdjson (ondemand) | 1467.25 | 0.240211 | 3842.9ms | 56369 | 160 | 1.23931e+06 | 36638.4 | 0.265679 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2269.94 | 0.203843 | 2837.68ms | 56369 | 320 | 745749 | 23682.4 | 0.0168873 | 1(Win) | true |
| simdjson (ondemand) | 1747.33 | 0.181763 | 3638.52ms | 56369 | 320 | 1.00068e+06 | 30765.6 | 0.153183 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2472.23 | 0.212445 | 3308.85ms | 83958 | 320 | 1.51492e+06 | 32387.2 | 0.173207 | 1(Win) | true |
| simdjson (ondemand) | 1916.76 | 0.164043 | 4136.02ms | 83958 | 40 | 187828 | 41772.8 | 0.462586 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3013.9 | 0.309608 | 3219.79ms | 83958 | 320 | 2.16491e+06 | 26566.4 | 0.479501 | 1(Win) | true |
| simdjson (ondemand) | 2227.25 | 0.188055 | 3915.03ms | 83958 | 640 | 2.92509e+06 | 35949.6 | 0.176111 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1493.18 | 0.0636304 | 3802.04ms | 56369 | 30 | 15743.7 | 36002.1 | 0.0710564 | 1(Win) | true |
| simdjson (ondemand) | 1034.07 | 0.0597723 | 5320.68ms | 56369 | 2560 | 2.47182e+06 | 51986.3 | 0.00634823 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1786.82 | 0.193408 | 3470.52ms | 56369 | 320 | 1.08347e+06 | 30085.6 | 0.0451839 | 1(Win) | true |
| simdjson (ondemand) | 1109.56 | 0.114794 | 5213.12ms | 56369 | 2560 | 7.91869e+06 | 48449.4 | 1.86112 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1999.6 | 0.0693569 | 4169.42ms | 83958 | 4890 | 3.77162e+06 | 40042.4 | 0.174065 | 1(Win) | true |
| simdjson (ondemand) | 1393.78 | 0.152958 | 5686.77ms | 83958 | 640 | 4.94156e+06 | 57447.2 | 0.0695807 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2361.11 | 0.168738 | 3973.27ms | 83958 | 30 | 98228.7 | 33911.5 | 0.100756 | 1(Win) | true |
| simdjson (ondemand) | 1638.92 | 0.104348 | 5466.21ms | 83958 | 640 | 1.66323e+06 | 48854.4 | 0.254802 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1222.72 | 0.0976492 | 4428.49ms | 53331 | 1280 | 2.11179e+06 | 41596 | 0.0529177 | 1(Win) | true |
| simdjson (ondemand) | 799.771 | 0.117476 | 6396.1ms | 53331 | 2560 | 1.42878e+07 | 63593.7 | 0.473505 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1469.99 | 0.257975 | 4064.1ms | 53331 | 2560 | 2.03951e+07 | 34599.1 | 1.18326 | 1(Win) | true |
| simdjson (ondemand) | 948.33 | 0.0750499 | 6129.88ms | 53331 | 4890 | 7.92226e+06 | 53631.5 | 0.0456075 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1388.25 | 0.182486 | 4630.13ms | 65103 | 160 | 1.06572e+06 | 44723.2 | 0.0429123 | 1(Win) | true |
| simdjson (ondemand) | 1021.38 | 0.131835 | 6281.51ms | 65103 | 640 | 4.11025e+06 | 60787.2 | 0.275612 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1621.82 | 0.210531 | 4308.02ms | 65103 | 640 | 4.15727e+06 | 38282.4 | 0.180041 | 1(Win) | true |
| simdjson (ondemand) | 1199.11 | 0.0868058 | 5807.43ms | 65103 | 1280 | 2.5858e+06 | 51777.8 | 0.0312778 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 875.021 | 0.259648 | 5852.08ms | 53331 | 160 | 3.6443e+06 | 58124.8 | 0 | 1(Win) | true |
| simdjson (ondemand) | 448.087 | 0.115307 | 6052ms | 53331 | 320 | 5.4815e+06 | 113506 | 0.236257 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1092.21 | 0.476662 | 5434.6ms | 53331 | 80 | 3.94145e+06 | 46566.4 | 0.0274801 | 1(Win) | true |
| simdjson (ondemand) | 462.778 | 0.2225 | 5829.12ms | 53331 | 160 | 9.56743e+06 | 109902 | 0.00436732 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1028.31 | 0.303081 | 6420.96ms | 65103 | 40 | 1.33946e+06 | 60377.6 | 0.247946 | 1(Win) | true |
| simdjson (ondemand) | 542.691 | 0.0599334 | 5975.28ms | 65103 | 2560 | 1.20358e+07 | 114406 | 0.187228 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1211.66 | 0.0659801 | 5937.31ms | 65103 | 2560 | 2.92623e+06 | 51241.4 | 0.211996 | 1(Win) | true |
| simdjson (ondemand) | 600.065 | 0.146397 | 5871.86ms | 65103 | 160 | 3.67102e+06 | 103467 | 0.0324635 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5439.15 | 0.295658 | 969.292ms | 53331 | 640 | 489166 | 9350.8 | 0.0470327 | 1(Win) | true |
| simdjson (ondemand) | 3924.77 | 0.103367 | 1307.12ms | 53331 | 4890 | 877418 | 12958.8 | 0.0799188 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5802.54 | 0.42433 | 925.345ms | 53331 | 640 | 885344 | 8765.2 | 0.814317 | 1(Win) | true |
| simdjson (ondemand) | 4218.68 | 0.204853 | 1232.8ms | 53331 | 1280 | 780732 | 12056 | 0.0863386 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5390.58 | 0.138484 | 1166.71ms | 65103 | 2560 | 651283 | 11517.7 | 0.170749 | 1(Win) | true |
| simdjson (ondemand) | 4363.97 | 0.514969 | 1450.15ms | 65103 | 40 | 214714 | 14227.2 | 0.462687 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5365 | 0.210206 | 1175.77ms | 65103 | 4890 | 2.89375e+06 | 11572.6 | 0.150013 | 1(Win) | true |
| simdjson (ondemand) | 4856.01 | 0.260462 | 1380.41ms | 65103 | 160 | 177439 | 12785.6 | 0.0876754 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4044.44 | 0.146634 | 1261.51ms | 53331 | 2560 | 870471 | 12575.4 | 0.138557 | 1(Win) | true |
| simdjson (ondemand) | 2625.64 | 0.496248 | 1929.68ms | 53331 | 30 | 277210 | 19370.7 | 0.176523 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4377.92 | 0.096184 | 1199.53ms | 53331 | 4890 | 610575 | 11617.5 | 0.0842453 | 1(Win) | true |
| simdjson (ondemand) | 2901.75 | 0.55022 | 1923.16ms | 53331 | 30 | 279018 | 17527.5 | 0.0972763 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4383.32 | 0.0743687 | 1469.1ms | 65103 | 4890 | 542607 | 14164.4 | 0.67047 | 1(Win) | true |
| simdjson (ondemand) | 2965.22 | 0.128217 | 2074.42ms | 65103 | 2560 | 1.84509e+06 | 20938.4 | 0.00382059 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4721.88 | 0.332643 | 1415.4ms | 65103 | 80 | 153045 | 13148.8 | 0.170068 | 1(Win) | true |
| simdjson (ondemand) | 3282.39 | 0.175266 | 1991.87ms | 65103 | 80 | 87924 | 18915.2 | 0.0507271 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 820.978 | 0.230015 | 1480.39ms | 11812 | 640 | 637494 | 13721.2 | 0.312902 | 1(Win) | true |
| simdjson (ondemand) | 625.077 | 0.109019 | 1785.94ms | 11812 | 4890 | 1.88753e+06 | 18021.5 | 0.541636 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 889.064 | 0.466122 | 1435.28ms | 11812 | 160 | 558084 | 12670.4 | 0.44003 | 1(Win) | true |
| simdjson (ondemand) | 703.54 | 0.213014 | 1750.85ms | 11812 | 1280 | 1.489e+06 | 16011.6 | 0.743882 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1606.78 | 0.143797 | 1537.92ms | 25388 | 1280 | 600970 | 15068.6 | 0.00663588 | 1(Win) | true |
| simdjson (ondemand) | 1180.13 | 0.21702 | 2077.62ms | 25388 | 1280 | 2.53748e+06 | 20516.2 | 0.172249 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1717.8 | 0.0820637 | 1522.21ms | 25388 | 4890 | 654219 | 14094.7 | 0.0355638 | 1(Win) | true |
| simdjson (ondemand) | 1199.75 | 0.710201 | 1975.93ms | 25388 | 640 | 1.31468e+07 | 20180.8 | 0.0752624 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 598.428 | 0.3128 | 1882.72ms | 11812 | 160 | 554725 | 18824 | 0.401092 | 1(Win) | true |
| simdjson (ondemand) | 439.16 | 0.30143 | 2543.29ms | 11812 | 640 | 3.82609e+06 | 25650.8 | 0.380377 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 645.444 | 0.472355 | 1870.01ms | 11812 | 40 | 271848 | 17452.8 | 0.355741 | 1(Win) | true |
| simdjson (ondemand) | 481.962 | 0.387929 | 2524.22ms | 11812 | 80 | 657683 | 23372.8 | 0.192044 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1188.36 | 0.0857344 | 2073.4ms | 25388 | 4890 | 1.49203e+06 | 20374.1 | 3.6287 | 1(Win) | true |
| simdjson (ondemand) | 924.965 | 0.25191 | 2725.68ms | 25388 | 40 | 173922 | 26176 | 0.211451 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1267.58 | 0.463233 | 2060.56ms | 25388 | 80 | 626315 | 19100.8 | 0.55593 | 1(Win) | true |
| simdjson (ondemand) | 920.107 | 0.248725 | 2723.09ms | 25388 | 1280 | 5.48312e+06 | 26314.2 | 0.029633 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1538.9 | 0.134186 | 734.555ms | 11812 | 4890 | 471787 | 7320.03 | 0.268002 | 1(Win) | true |
| simdjson (ondemand) | 1299.02 | 0.256072 | 878.283ms | 11812 | 2560 | 1.26236e+06 | 8671.8 | 0.0161469 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1627.91 | 0.160666 | 718.678ms | 11812 | 2560 | 316428 | 6919.8 | 0.0837473 | 1(Win) | true |
| simdjson (ondemand) | 1351.2 | 0.202561 | 858.786ms | 11812 | 2560 | 730060 | 8336.9 | 0.621575 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2850.2 | 0.28084 | 886.774ms | 25388 | 640 | 364254 | 8494.8 | 0.277047 | 1(Win) | true |
| simdjson (ondemand) | 2320.92 | 0.378753 | 1106.84ms | 25388 | 640 | 999142 | 10432 | 0.648348 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2843.11 | 0.289269 | 887.835ms | 25388 | 640 | 388380 | 8516 | 0.0750962 | 1(Win) | true |
| simdjson (ondemand) | 2364.88 | 0.142575 | 1048.37ms | 25388 | 2560 | 545464 | 10238.1 | 0.0556434 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1167.19 | 0.597609 | 1020.86ms | 11812 | 80 | 266126 | 9651.2 | 0.265957 | 1(Win) | true |
| simdjson (ondemand) | 1125.31 | 0.172859 | 1005.2ms | 11812 | 2560 | 766527 | 10010.4 | 0.208217 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1255.44 | 0.338043 | 924.988ms | 11812 | 40 | 36801 | 8972.8 | 0.238322 | 1(Win) | true |
| simdjson (ondemand) | 1156.65 | 0.142268 | 993.85ms | 11812 | 4890 | 938799 | 9739.2 | 0.0974153 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2243.05 | 0.198464 | 1098.66ms | 25388 | 1280 | 587427 | 10794.2 | 0.470978 | 1(Win) | true |
| simdjson (ondemand) | 2085.65 | 0.370052 | 1260.7ms | 25388 | 320 | 590542 | 11608.8 | 0.582351 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2296.18 | 0.240107 | 1065.97ms | 25388 | 1280 | 820468 | 10544.4 | 0.155775 | 1(Win) | true |
| simdjson (ondemand) | 2060.52 | 0.396954 | 1217.23ms | 25388 | 320 | 696202 | 11750.4 | 0.0952251 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1251.55 | 0.108984 | 8402.54ms | 108313 | 1280 | 1.03562e+07 | 82533.8 | 0.244618 | 1(Win) | true |
| simdjson (ondemand) | 1162.31 | 0.099425 | 9089.48ms | 108313 | 640 | 4.99677e+06 | 88870.8 | 0.115807 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1360.68 | 0.125228 | 7984.89ms | 108313 | 640 | 5.78408e+06 | 75914.4 | 0.191106 | 1(Win) | true |
| simdjson (ondemand) | 1218.27 | 0.0742231 | 8640.58ms | 108313 | 2560 | 1.01389e+07 | 84788.5 | 0.0873176 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1924.93 | 0.376643 | 9123.55ms | 183677 | 30 | 3.52418e+06 | 90999.5 | 0.150263 | 1(Win) | true |
| simdjson (ondemand) | 1700.63 | 0.195213 | 5234.92ms | 183677 | 160 | 6.46886e+06 | 103002 | 0.146231 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2163.52 | 0.0453115 | 8571.21ms | 183677 | 30 | 40376.2 | 80964.3 | 0.147337 | 1(Win) | true |
| simdjson (ondemand) | 1854.96 | 0.255567 | 9569.95ms | 183677 | 80 | 4.65949e+06 | 94432 | 0.297317 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 530.979 | 0.237952 | 9883.76ms | 108313 | 80 | 1.71425e+07 | 194538 | 0.0180909 | 1(Win) | true |
| simdjson (ondemand) | 216.904 | 0.0917519 | 6142.83ms | 108313 | 320 | 6.1095e+07 | 476226 | 0.0466788 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 551.405 | 0.141921 | 9797.93ms | 108313 | 320 | 2.26183e+07 | 187331 | 0.0863388 | 1(Win) | true |
| simdjson (ondemand) | 215.189 | 0.235781 | 6229.74ms | 108313 | 640 | 8.19827e+08 | 480022 | 0.686884 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 806.495 | 0.730543 | 5820.74ms | 183677 | 40 | 1.00707e+08 | 217197 | 0.275242 | 1(Win) | true |
| simdjson (ondemand) | 356.188 | 0.193493 | 6157.21ms | 183677 | 640 | 5.79511e+08 | 491786 | 0.156084 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 823.34 | 1.09449 | 5772.44ms | 183677 | 30 | 1.62665e+08 | 212753 | 0.136557 | 1(Win) | true |
| simdjson (ondemand) | 372.558 | 0.141164 | 6044.77ms | 183677 | 320 | 1.40968e+08 | 470176 | 0.689758 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3183.41 | 0.245865 | 3333.27ms | 108313 | 40 | 254582 | 32448 | 0.144851 | 1(Win) | true |
| simdjson (ondemand) | 2718.07 | 0.053663 | 3940.73ms | 108313 | 40 | 16636.1 | 38003.2 | 0.0112284 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3270.05 | 0.11884 | 3215.49ms | 108313 | 4890 | 6.89109e+06 | 31588.3 | 1.01295 | 1(Win) | true |
| simdjson (ondemand) | 3058.03 | 0.283125 | 3505.19ms | 108313 | 320 | 2.92675e+06 | 33778.4 | 0.0734736 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4205.37 | 0.202073 | 4093.88ms | 183677 | 1280 | 9.06837e+06 | 41653.4 | 2.01466 | 1(Win) | true |
| simdjson (ondemand) | 3721.15 | 0.520886 | 4961.75ms | 183677 | 160 | 9.61967e+06 | 47073.6 | 0.454111 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4398.2 | 0.396182 | 3900.45ms | 183677 | 320 | 7.96708e+06 | 39827.2 | 0.148422 | 1(Win) | true |
| simdjson (ondemand) | 4251.98 | 0.156364 | 4534.84ms | 183677 | 40 | 165983 | 41196.8 | 0.232486 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2251.11 | 0.545363 | 4514.36ms | 108313 | 160 | 1.00198e+07 | 45886.4 | 1.43241 | 1(Win) | true |
| simdjson (ondemand) | 1813.15 | 0.138944 | 5572.74ms | 108313 | 2560 | 1.60404e+07 | 56970 | 0.0165026 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2549.75 | 0.44221 | 4351.26ms | 108313 | 80 | 2.56752e+06 | 40512 | 0.0315856 | 1(Win) | true |
| simdjson (ondemand) | 1896.69 | 0.149685 | 5429.07ms | 108313 | 4890 | 3.24962e+07 | 54460.9 | 1.01791 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3312.87 | 0.138346 | 5454.27ms | 183677 | 4890 | 2.61664e+07 | 52875 | 0.462448 | 1(Win) | true |
| simdjson (ondemand) | 2622.51 | 0.294336 | 6637.48ms | 183677 | 640 | 2.47367e+07 | 66794 | 0.382399 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3332.97 | 0.31813 | 5221.97ms | 183677 | 1280 | 3.57822e+07 | 52556.2 | 0.680696 | 1(Win) | true |
| simdjson (ondemand) | 2905.21 | 0.820089 | 6354.79ms | 183677 | 40 | 9.77995e+06 | 60294.4 | 0.102502 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 435.306 | 0.71327 | 6036.65ms | 1834197 | 80 | 6.57205e+10 | 4.01838e+06 | 1.03579 | 1(Win) | true |
| Jsonifier (generic) | 404.177 | 0.476983 | 6541.83ms | 1834197 | 30 | 1.27842e+10 | 4.32787e+06 | 2.61824 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 482.562 | 0.483937 | 6115.91ms | 1834197 | 30 | 9.23176e+09 | 3.62487e+06 | 0.276428 | 1(Win) | true |
| Jsonifier (generic) | 462.464 | 0.45939 | 6205.46ms | 1834197 | 80 | 2.41541e+10 | 3.78241e+06 | 0.172544 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1558.71 | 0.408539 | 6953.98ms | 7351818 | 40 | 1.35078e+10 | 4.49809e+06 | 1.65861 | 1(Win) | true |
| simdjson (ondemand) | 1508.52 | 0.341793 | 6958.46ms | 7351818 | 30 | 7.5707e+09 | 4.64777e+06 | 0.126707 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1615.92 | 0.462515 | 7046.27ms | 7351818 | 40 | 1.61088e+10 | 4.33886e+06 | 0.993578 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1612.27 | 1.14411 | 6960.13ms | 7351818 | 30 | 7.42627e+10 | 4.34866e+06 | 1.573 | 1(Tie) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 288.601 | 0.276868 | 9155.98ms | 1834197 | 80 | 2.25284e+10 | 6.06105e+06 | 3.60112 | 1(Win) | true |
| simdjson (ondemand) | 183.083 | 0.549136 | 6469.47ms | 1834197 | 30 | 8.25802e+10 | 9.55426e+06 | 3.81148 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 293.655 | 0.231637 | 9411.22ms | 1834197 | 80 | 1.52308e+10 | 5.95675e+06 | 1.17125 | 1(Win) | true |
| simdjson (ondemand) | 203.929 | 0.49446 | 6217.94ms | 1834197 | 30 | 5.39656e+10 | 8.57761e+06 | 4.15117 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1033.27 | 0.123837 | 10089.1ms | 7351818 | 40 | 2.82438e+09 | 6.7855e+06 | 5.08159 | -(Win) | false |
| simdjson (ondemand) | 698.543 | 0.145884 | 7024.11ms | 7351818 | 40 | 8.57583e+09 | 1.0037e+07 | 1.20448 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1106.96 | 0.657046 | 10000ms | 7351818 | 80 | 1.38551e+11 | 6.3338e+06 | 0.380666 | 1(Win) | true |
| simdjson (ondemand) | 754.298 | 0.335999 | 7091.87ms | 7351818 | 30 | 2.92617e+10 | 9.29505e+06 | 0.684005 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2728.62 | 0.219712 | 8351.77ms | 1834197 | 30 | 5.95161e+07 | 641067 | 0.00532474 | 1(Win) | true |
| Jsonifier (generic) | 2423.52 | 0.390645 | 9177.83ms | 1834197 | 160 | 1.27199e+09 | 721771 | 0.607741 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2622.46 | 0.142521 | 8378.32ms | 1834197 | 160 | 1.44594e+08 | 667018 | 0.0648079 | 1(Win) | true |
| Jsonifier (generic) | 2350.29 | 0.120237 | 9142.8ms | 1834197 | 320 | 2.56258e+08 | 744258 | 0.177349 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6132.31 | 0.21212 | 7672.59ms | 7351818 | 40 | 2.35268e+08 | 1.14333e+06 | 0.415666 | 1(Win) | true |
| simdjson (ondemand) | 5185.19 | 0.186096 | 8122.72ms | 7351818 | 30 | 1.89957e+08 | 1.35217e+06 | 0.390902 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5805.78 | 0.253759 | 7608.64ms | 7351818 | 160 | 1.50256e+09 | 1.20763e+06 | 0.345925 | 1(Win) | true |
| simdjson (ondemand) | 5287.06 | 0.557615 | 8206.06ms | 7351818 | 30 | 1.64041e+09 | 1.32611e+06 | 1.56062 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1906.61 | 0.303123 | 5938.52ms | 1834197 | 40 | 3.09361e+08 | 917453 | 0.8521 | 1(Win) | true |
| simdjson (ondemand) | 1621.18 | 0.140464 | 6970.56ms | 1834197 | 40 | 9.18797e+07 | 1.07898e+06 | 0.25775 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1864.09 | 0.289483 | 5804.73ms | 1834197 | 40 | 2.95164e+08 | 938381 | 1.01758 | 1(Win) | true |
| simdjson (ondemand) | 1632.43 | 0.127487 | 6915.27ms | 1834197 | 80 | 1.49296e+08 | 1.07155e+06 | 0.182199 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4632.52 | 0.318593 | 8958.53ms | 7351818 | 320 | 7.4401e+09 | 1.51348e+06 | 3.83335 | 1(Win) | true |
| simdjson (ondemand) | 4033.47 | 0.178141 | 5699.29ms | 7351818 | 160 | 1.53418e+09 | 1.73826e+06 | 1.98402 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4787.71 | 0.174828 | 9085.79ms | 7351818 | 160 | 1.04876e+09 | 1.46443e+06 | 0.215922 | 1(Win) | true |
| simdjson (ondemand) | 4060.58 | 0.0728818 | 5474.33ms | 7351818 | 160 | 2.5338e+08 | 1.72666e+06 | 0.762423 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 948.071 | 0.0737826 | 5424.07ms | 409725 | 320 | 2.95911e+07 | 412146 | 0.329859 | 1(Win) | true |
| simdjson (ondemand) | 605.612 | 0.0932097 | 8644.94ms | 409725 | 640 | 2.31472e+08 | 645206 | 0.193241 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1203.21 | 0.145019 | 5031.16ms | 409725 | 320 | 7.09746e+07 | 324753 | 0.377583 | 1(Win) | true |
| simdjson (ondemand) | 675.503 | 0.280854 | 8301.94ms | 409725 | 30 | 7.91796e+07 | 578449 | 0.019174 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1380.62 | 0.135964 | 6112.86ms | 676745 | 320 | 1.29272e+08 | 467468 | 2.4036 | 1(Win) | true |
| simdjson (ondemand) | 950.425 | 0.113992 | 8934.72ms | 676745 | 640 | 3.83479e+08 | 679059 | 0.554911 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1747.35 | 0.199141 | 5658.75ms | 676745 | 160 | 8.65628e+07 | 369355 | 0.155756 | 1(Win) | true |
| simdjson (ondemand) | 1076.6 | 0.286841 | 8584.92ms | 676745 | 30 | 8.87048e+07 | 599475 | 0.529558 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 644.145 | 0.135997 | 7832.33ms | 409725 | 320 | 2.17785e+08 | 606609 | 2.01371 | 1(Win) | true |
| simdjson (ondemand) | 348.422 | 0.240895 | 7495.12ms | 409725 | 30 | 2.18953e+08 | 1.12147e+06 | 2.39588 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 799.416 | 0.395647 | 7185.95ms | 409725 | 40 | 1.49595e+08 | 488787 | 0.327098 | 1(Win) | true |
| simdjson (ondemand) | 361.46 | 0.476343 | 7347.11ms | 409725 | 40 | 1.06063e+09 | 1.08102e+06 | 0.353903 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 997.787 | 0.086939 | 8491.7ms | 676745 | 80 | 2.52985e+07 | 646826 | 0.161513 | 1(Win) | true |
| simdjson (ondemand) | 535.262 | 0.162606 | 7644.63ms | 676745 | 40 | 1.53763e+08 | 1.20575e+06 | 0.373829 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1111.19 | 0.148204 | 8143.5ms | 676745 | 160 | 1.18554e+08 | 580816 | 0.911156 | 1(Win) | true |
| simdjson (ondemand) | 609.676 | 0.0906418 | 7499.59ms | 676745 | 40 | 3.68272e+07 | 1.05859e+06 | 0.099053 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1643.25 | 0.118922 | 6145.32ms | 409725 | 1280 | 1.02356e+08 | 237788 | 0.202607 | 1(Win) | true |
| simdjson (ondemand) | 1099.72 | 0.2362 | 9145.64ms | 409725 | 80 | 5.63466e+07 | 355312 | 0.136178 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1907.08 | 0.0857979 | 6086.95ms | 409725 | 1280 | 3.9556e+07 | 204892 | 0.139096 | 1(Win) | true |
| simdjson (ondemand) | 1193.14 | 0.312871 | 9070.43ms | 409725 | 320 | 3.35957e+08 | 327493 | 0.187743 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2248.75 | 0.343476 | 7287.85ms | 676745 | 40 | 3.88706e+07 | 287002 | 0.334855 | 1(Win) | true |
| simdjson (ondemand) | 1659.26 | 0.253192 | 9959.88ms | 676745 | 320 | 3.10363e+08 | 388965 | 0.0735772 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2667.66 | 0.343971 | 7007.5ms | 676745 | 80 | 5.54018e+07 | 241933 | 0.0951424 | 1(Win) | true |
| simdjson (ondemand) | 1840.22 | 0.165013 | 9854.95ms | 676745 | 80 | 2.67943e+07 | 350717 | 0.00456229 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1382.93 | 0.18742 | 7418.24ms | 409725 | 80 | 2.24339e+07 | 282547 | 0.53286 | 1(Win) | true |
| simdjson (ondemand) | 893.05 | 0.290978 | 5571.33ms | 409725 | 80 | 1.29671e+08 | 437539 | 0.746401 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1492.16 | 0.268413 | 7328.92ms | 409725 | 320 | 1.58093e+08 | 261865 | 0.733348 | 1(Win) | true |
| simdjson (ondemand) | 984.758 | 0.197622 | 5404.32ms | 409725 | 160 | 9.83827e+07 | 396792 | 0.82655 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1975.3 | 0.361425 | 8762.98ms | 676745 | 30 | 4.18352e+07 | 326733 | 0.201507 | 1(Win) | true |
| simdjson (ondemand) | 1430.31 | 0.152196 | 5852.35ms | 676745 | 80 | 3.77298e+07 | 451226 | 0.342069 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2102.27 | 0.440379 | 8251.47ms | 676745 | 80 | 1.46223e+08 | 306998 | 0.122104 | 1(Win) | true |
| simdjson (ondemand) | 1499.24 | 0.519969 | 5739.54ms | 676745 | 80 | 4.00821e+08 | 430480 | 0.630088 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1677.3 | 0.311618 | 8141.62ms | 264040 | 30 | 6.56573e+06 | 150127 | 0.045452 | 1(Win) | true |
| simdjson (ondemand) | 1255.69 | 0.312841 | 5108.98ms | 264040 | 30 | 1.1807e+07 | 200533 | 0.0467866 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2083.81 | 0.358613 | 7346.57ms | 264040 | 30 | 5.63376e+06 | 120841 | 0.701213 | 1(Win) | true |
| simdjson (ondemand) | 1486.01 | 0.197997 | 9851.17ms | 264040 | 80 | 9.00543e+06 | 169453 | 0.143315 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1927.79 | 0.173523 | 9249.74ms | 360584 | 320 | 3.06589e+07 | 178380 | 0.104605 | 1(Win) | true |
| simdjson (ondemand) | 1604.72 | 0.229443 | 5430.32ms | 360584 | 640 | 1.54718e+08 | 214292 | 0.0824362 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2345.83 | 0.129056 | 8428.6ms | 360584 | 320 | 1.14532e+07 | 146592 | 0.248236 | 1(Win) | true |
| simdjson (ondemand) | 1895.55 | 0.274979 | 5162.73ms | 360584 | 80 | 1.99082e+07 | 181414 | 0.0141093 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 652.2 | 0.222176 | 5123.93ms | 264040 | 30 | 2.20747e+07 | 386091 | 0.220531 | 1(Win) | true |
| simdjson (ondemand) | 289.202 | 0.148579 | 5863.11ms | 264040 | 40 | 6.69438e+07 | 870701 | 0.0418797 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 677.743 | 0.186773 | 5016.59ms | 264040 | 160 | 7.70477e+07 | 371539 | 0.115545 | 1(Win) | true |
| simdjson (ondemand) | 274.56 | 0.309972 | 5865.54ms | 264040 | 40 | 3.23274e+08 | 917133 | 0.199043 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 763.882 | 0.108681 | 5749.6ms | 360584 | 640 | 1.53197e+08 | 450174 | 0.385152 | 1(Win) | true |
| simdjson (ondemand) | 377.859 | 0.324919 | 5897.75ms | 360584 | 40 | 3.49756e+08 | 910074 | 0.0325728 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 836.217 | 0.113811 | 5690.46ms | 360584 | 320 | 7.00967e+07 | 411233 | 0.379265 | 1(Win) | true |
| simdjson (ondemand) | 391.666 | 0.112042 | 5664.3ms | 360584 | 320 | 3.09666e+08 | 877993 | 0.738476 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4435.37 | 0.177115 | 5792.54ms | 264040 | 320 | 3.23548e+06 | 56772.8 | 0.0225409 | 1(Win) | true |
| simdjson (ondemand) | 3783.9 | 0.248149 | 7121.62ms | 264040 | 80 | 2.1816e+06 | 66547.2 | 0.421375 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4552.04 | 0.254066 | 5541.58ms | 264040 | 320 | 6.32078e+06 | 55317.6 | 0.460555 | 1(Win) | true |
| simdjson (ondemand) | 3904.63 | 0.310969 | 6895.78ms | 264040 | 80 | 3.21739e+06 | 64489.6 | 0.17337 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4814.03 | 0.299432 | 7140.37ms | 360584 | 1280 | 5.85601e+07 | 71432.8 | 0.0436965 | 1(Win) | true |
| simdjson (ondemand) | 4164.41 | 0.0834189 | 8316.56ms | 360584 | 4890 | 2.3203e+07 | 82575.9 | 0.0699421 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5080.48 | 0.272602 | 7015.99ms | 360584 | 80 | 2.72364e+06 | 67686.4 | 0.0757002 | 1(Win) | true |
| simdjson (ondemand) | 4360.15 | 0.200015 | 8139.41ms | 360584 | 160 | 3.9816e+06 | 78868.8 | 0.168098 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3165.38 | 0.121145 | 8200.64ms | 264040 | 1280 | 1.18881e+07 | 79550.6 | 0.184625 | 1(Win) | true |
| simdjson (ondemand) | 2407.71 | 0.200706 | 5360.16ms | 264040 | 320 | 1.40994e+07 | 104584 | 0.200012 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3127.59 | 0.476981 | 8148.22ms | 264040 | 80 | 1.17981e+07 | 80512 | 0.710339 | 1(Win) | true |
| simdjson (ondemand) | 2509.35 | 0.146835 | 5270.33ms | 264040 | 1280 | 2.779e+07 | 100348 | 1.39644 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3206.35 | 1.58065 | 5267.81ms | 360584 | 320 | 9.19629e+08 | 107250 | 0.485706 | 1(Win) | true |
| simdjson (ondemand) | 3003.31 | 0.526467 | 5934.4ms | 360584 | 30 | 1.09013e+07 | 114500 | 0.059657 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3724.21 | 0.0803597 | 9409.81ms | 360584 | 4890 | 2.69234e+07 | 92336.3 | 0.24053 | 1(Win) | true |
| simdjson (ondemand) | 3086.85 | 0.141431 | 5883.84ms | 360584 | 640 | 1.58873e+07 | 111402 | 0.0582018 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1143.59 | 0.389983 | 225.655ms | 2632 | 2560 | 187569 | 2194.9 | 0.204601 | 1(Win) | true |
| simdjson (ondemand) | 780.204 | 0.461978 | 309.928ms | 2632 | 1280 | 282754 | 3217.2 | 0.16137 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1703.67 | 0.504718 | 177.339ms | 2632 | 4890 | 270401 | 1473.33 | 0.844283 | 1(Win) | true |
| simdjson (ondemand) | 1125.39 | 0.701434 | 254.65ms | 2632 | 1280 | 313292 | 2230.4 | 0.631655 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1393.7 | 0.811451 | 244.256ms | 3370 | 640 | 224090 | 2306 | 0.155871 | 1(Win) | true |
| simdjson (ondemand) | 1058.38 | 0.247634 | 311.052ms | 3370 | 1280 | 72377.8 | 3036.6 | 0.308601 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1998.18 | 0.453188 | 192.224ms | 3370 | 4890 | 259810 | 1608.4 | 0.764903 | 1(Win) | true |
| simdjson (ondemand) | 1362.11 | 0.387533 | 267.612ms | 3370 | 4890 | 408849 | 2359.49 | 0.518895 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 878.661 | 0.310452 | 294.389ms | 2632 | 2560 | 201353 | 2856.7 | 0.491152 | 1(Win) | true |
| simdjson (ondemand) | 452.191 | 0.173947 | 556.646ms | 2632 | 4890 | 455901 | 5550.91 | 0.111948 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1193.11 | 0.478567 | 242.588ms | 2632 | 1280 | 129749 | 2103.8 | 0.314705 | 1(Win) | true |
| simdjson (ondemand) | 530.538 | 0.199529 | 504.823ms | 2632 | 4890 | 435773 | 4731.18 | 0.109683 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1006.41 | 0.280181 | 323.684ms | 3370 | 2560 | 204939 | 3193.4 | 0.00626253 | 1(Win) | true |
| simdjson (ondemand) | 576.889 | 0.17312 | 562.517ms | 3370 | 4890 | 454864 | 5571.06 | 0.0186182 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1364.74 | 0.314573 | 264.907ms | 3370 | 4890 | 268356 | 2354.94 | 0.24407 | 1(Win) | true |
| simdjson (ondemand) | 670.173 | 0.365069 | 514.111ms | 3370 | 1280 | 392326 | 4795.6 | 0.141596 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2012.94 | 0.519283 | 128.52ms | 2632 | 4890 | 205034 | 1246.97 | 0.202797 | 1(Win) | true |
| simdjson (ondemand) | 1261.41 | 0.857214 | 194.681ms | 2632 | 2560 | 744871 | 1989.9 | 0.744228 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3310.29 | 0.849354 | 84.5258ms | 2632 | 4890 | 202827 | 758.263 | 0.0576543 | 1(Win) | true |
| simdjson (ondemand) | 1908.77 | 0.520422 | 142.482ms | 2632 | 4890 | 229027 | 1315.02 | 0.406453 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2517.14 | 1.4091 | 130.875ms | 3370 | 640 | 207161 | 1276.8 | 0.440529 | 1(Win) | true |
| simdjson (ondemand) | 1831.39 | 0.376114 | 179.278ms | 3370 | 4890 | 213032 | 1754.88 | 0.702619 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3692.42 | 0.817606 | 96.7982ms | 3370 | 2560 | 129648 | 870.4 | 0.115022 | 1(Win) | true |
| simdjson (ondemand) | 2401.43 | 0.535496 | 144.655ms | 3370 | 4890 | 251155 | 1338.32 | 0.016429 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1731.41 | 0.514418 | 149.234ms | 2632 | 4890 | 271964 | 1449.72 | 0.0776153 | 1(Win) | true |
| simdjson (ondemand) | 1195.88 | 0.232258 | 212.47ms | 2632 | 4890 | 116211 | 2098.94 | 0.997894 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2377.34 | 0.34041 | 116.241ms | 2632 | 4890 | 63168.8 | 1055.83 | 0.64648 | 1(Win) | true |
| simdjson (ondemand) | 1500.97 | 0.596278 | 175.025ms | 2632 | 2560 | 254546 | 1672.3 | 0.317936 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2068.19 | 0.506815 | 161.822ms | 3370 | 4890 | 303309 | 1553.96 | 0.800725 | 1(Win) | true |
| simdjson (ondemand) | 1579.05 | 0.179665 | 208.476ms | 3370 | 4890 | 65388.9 | 2035.33 | 0.00830856 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2755.39 | 1.29419 | 128.412ms | 3370 | 640 | 145838 | 1166.4 | 0.0685401 | 1(Win) | true |
| simdjson (ondemand) | 1969.84 | 0.47932 | 172.493ms | 3370 | 4890 | 299059 | 1631.54 | 0.00869942 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 487.579 | 0.141605 | 923.065ms | 4630 | 1280 | 210494 | 9056 | 0.229156 | 1(Win) | true |
| simdjson (ondemand) | 478.657 | 0.288023 | 941.884ms | 4630 | 640 | 451803 | 9224.8 | 0.130254 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 551.645 | 0.262636 | 913.595ms | 4630 | 30 | 13257.9 | 8004.27 | 0 | 1(Win) | true |
| simdjson (ondemand) | 503.996 | 0.371538 | 1000.3ms | 4630 | 1280 | 1.3562e+06 | 8761 | 0.784557 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1084.22 | 0.125879 | 1008.9ms | 11579 | 4890 | 803754 | 10184.9 | 0.26653 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1074.8 | 2.49093 | 1061.55ms | 11579 | 30 | 1.96487e+06 | 10274.1 | 0.417014 | 1(Tie) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1269.15 | 0.288644 | 992.648ms | 11579 | 640 | 403667 | 8700.8 | 0.20269 | 1(Win) | true |
| simdjson (ondemand) | 1244.61 | 0.108882 | 1006.16ms | 11579 | 4890 | 456343 | 8872.31 | 0.218128 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 455.795 | 0.130959 | 980.968ms | 4630 | 2560 | 412038 | 9687.5 | 0.342564 | 1(Win) | true |
| simdjson (ondemand) | 439.442 | 0.362037 | 1021.5ms | 4630 | 40 | 52932.9 | 10048 | 0.0424809 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 515.566 | 0.265263 | 976.689ms | 4630 | 640 | 330314 | 8564.4 | 0.237629 | 1(Win) | true |
| simdjson (ondemand) | 490.133 | 0.244306 | 1036.71ms | 4630 | 640 | 310013 | 9008.8 | 0.0266477 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1059.75 | 0.370283 | 1085.99ms | 11579 | 320 | 476378 | 10420 | 0.192308 | 1(Win) | true |
| simdjson (ondemand) | 986.322 | 0.766911 | 1098.86ms | 11579 | 30 | 221165 | 11195.7 | 0.0761615 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1187.98 | 0.14571 | 1058.76ms | 11579 | 2560 | 469620 | 9295.3 | 0.280001 | 1(Win) | true |
| simdjson (ondemand) | 1130.3 | 0.546802 | 1102.03ms | 11579 | 160 | 456598 | 9769.6 | 0.196915 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4742.25 | 0.626354 | 96.192ms | 4630 | 2560 | 87070.8 | 931.1 | 0.594209 | 1(Win) | true |
| simdjson (ondemand) | 3995.22 | 1.13193 | 114.854ms | 4630 | 640 | 100161 | 1105.2 | 0.324675 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4827.81 | 0.691861 | 94.3841ms | 4630 | 2560 | 102504 | 914.6 | 0.174634 | 1(Win) | true |
| simdjson (ondemand) | 4001.29 | 0.420559 | 113.491ms | 4630 | 4890 | 105323 | 1103.52 | 0.256409 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6851.95 | 1.72651 | 172.306ms | 11579 | 640 | 495488 | 1611.6 | 0.123946 | 1(Win) | true |
| simdjson (ondemand) | 5809.01 | 0.282435 | 193.998ms | 11579 | 4890 | 140957 | 1900.94 | 0.22904 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 7105.92 | 0.65862 | 159.369ms | 11579 | 2560 | 268171 | 1554 | 0.154679 | 1(Win) | true |
| simdjson (ondemand) | 5775.42 | 1.19098 | 191.41ms | 11579 | 320 | 165933 | 1912 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3607.96 | 0.511298 | 126.895ms | 4630 | 4890 | 191468 | 1223.83 | 0.022336 | 1(Win) | true |
| simdjson (ondemand) | 3144.95 | 1.06295 | 146.159ms | 4630 | 1280 | 285084 | 1404 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3610.98 | 1.36285 | 125.219ms | 4630 | 640 | 177742 | 1222.8 | 0.423453 | 1(Win) | true |
| simdjson (ondemand) | 3205.14 | 0.516333 | 140.088ms | 4630 | 4890 | 247422 | 1377.64 | 0.308431 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5513.58 | 0.430185 | 203.745ms | 11579 | 2560 | 190031 | 2002.8 | 0.477042 | 1(Win) | true |
| simdjson (ondemand) | 4927.53 | 0.569964 | 220.764ms | 11579 | 1280 | 208828 | 2241 | 0.782515 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5933.36 | 0.456555 | 185.766ms | 11579 | 4890 | 353051 | 1861.1 | 1.11949 | 1(Win) | true |
| simdjson (ondemand) | 4787.14 | 0.396926 | 238.039ms | 11579 | 4890 | 409938 | 2306.72 | 1.19411 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 785.88 | 1.06143 | 607.209ms | 5092 | 640 | 2.75312e+06 | 6179.2 | 0.103681 | 1(Win) | true |
| simdjson (ondemand) | 680.661 | 0.725106 | 754.83ms | 5092 | 320 | 856382 | 7134.4 | 0.734639 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1004.82 | 0.774857 | 559.728ms | 5092 | 320 | 448736 | 4832.8 | 0.515807 | 1(Win) | true |
| simdjson (ondemand) | 870.979 | 0.160669 | 639.45ms | 5092 | 4890 | 392405 | 5575.46 | 0.462361 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1456.77 | 0.163117 | 641.26ms | 9739 | 4890 | 528883 | 6375.66 | 0.500582 | 1(Win) | true |
| simdjson (ondemand) | 1297.55 | 0.214082 | 724.934ms | 9739 | 1280 | 300576 | 7158 | 0.0111776 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1726.65 | 0.230497 | 626.876ms | 9739 | 2560 | 393539 | 5379.1 | 0.251603 | 1(Win) | true |
| simdjson (ondemand) | 1524.5 | 0.255582 | 687.229ms | 9739 | 640 | 155173 | 6092.4 | 0.230324 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 535.256 | 0.134158 | 919.3ms | 5092 | 2560 | 379249 | 9072.5 | 0.475104 | 1(Win) | true |
| simdjson (ondemand) | 320.908 | 0.158078 | 1614.86ms | 5092 | 1280 | 732438 | 15132.4 | 1.7017 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 602.791 | 0.236321 | 918.081ms | 5092 | 4890 | 1.77238e+06 | 8056.04 | 1.16081 | 1(Win) | true |
| simdjson (ondemand) | 352.966 | 0.369522 | 1499.66ms | 5092 | 640 | 1.65414e+06 | 13758 | 0.292788 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 948.667 | 0.371541 | 996.648ms | 9739 | 320 | 423413 | 9790.4 | 0.295034 | 1(Win) | true |
| simdjson (ondemand) | 624.518 | 0.334521 | 1583.49ms | 9739 | 320 | 792017 | 14872 | 0.107701 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1062.82 | 0.150224 | 965.597ms | 9739 | 2560 | 441194 | 8738.9 | 0.154721 | 1(Win) | true |
| simdjson (ondemand) | 635.918 | 0.213806 | 1604.19ms | 9739 | 1280 | 1.24818e+06 | 14605.4 | 0.0506919 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3350.77 | 0.520423 | 149.683ms | 5092 | 4890 | 278170 | 1449.25 | 0.0101304 | 1(Win) | true |
| simdjson (ondemand) | 2938.86 | 0.463399 | 167.236ms | 5092 | 4890 | 286707 | 1652.38 | 0.436294 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3425.1 | 0.696233 | 145.909ms | 5092 | 2560 | 249448 | 1417.8 | 0.728189 | 1(Win) | true |
| simdjson (ondemand) | 3209.17 | 0.977713 | 161.605ms | 5092 | 1280 | 280173 | 1513.2 | 1.76578 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 3959.68 | 2.74191 | 227.352ms | 9739 | 80 | 330905 | 2345.6 | 2.3743 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3756.98 | 0.337522 | 257.836ms | 9739 | 4890 | 340457 | 2472.15 | 4.81446 | 1(Tie) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4471.07 | 0.4117 | 206.43ms | 9739 | 4890 | 357665 | 2077.32 | 0.196167 | 1(Win) | true |
| simdjson (ondemand) | 3778.02 | 0.329156 | 245.873ms | 9739 | 4890 | 320194 | 2458.39 | 3.44885 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1967.95 | 0.348011 | 257.498ms | 5092 | 4890 | 360615 | 2467.6 | 1.8457 | 1(Win) | true |
| simdjson (ondemand) | 1826.7 | 2.07766 | 276.32ms | 5092 | 320 | 976203 | 2658.4 | 0.575061 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2160.91 | 0.300139 | 232.973ms | 5092 | 4890 | 222462 | 2247.25 | 0.408861 | 1(Win) | true |
| Jsonifier (generic) | 1937.02 | 0.619945 | 249.089ms | 5092 | 1280 | 309189 | 2507 | 0.231889 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3412.64 | 0.837878 | 278.993ms | 9739 | 640 | 332805 | 2721.6 | 0.816327 | 1(Win) | true |
| simdjson (ondemand) | 3131.86 | 0.596911 | 306.541ms | 9739 | 640 | 200551 | 2965.6 | 0.161594 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3533.78 | 0.408355 | 269.675ms | 9739 | 2560 | 294894 | 2628.3 | 0.0114129 | 1(Win) | true |
| simdjson (ondemand) | 3057.22 | 0.739985 | 302.513ms | 9739 | 640 | 323445 | 3038 | 3.07555 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1125.58 | 0.709692 | 423.478ms | 4857 | 160 | 136472 | 4115.2 | 0.077821 | 1(Win) | true |
| simdjson (ondemand) | 618.754 | 0.381802 | 714.429ms | 4857 | 1280 | 1.04565e+06 | 7486 | 0.679297 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1746.21 | 0.401869 | 314.147ms | 4857 | 2560 | 290905 | 2652.6 | 0.143461 | 1(Win) | true |
| simdjson (ondemand) | 1079.42 | 0.611903 | 491.36ms | 4857 | 320 | 220634 | 4291.2 | 0.411831 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1372.55 | 0.252665 | 472.814ms | 6701 | 2560 | 354289 | 4656 | 0.223868 | 1(Win) | true |
| simdjson (ondemand) | 985.561 | 0.286524 | 729.73ms | 6701 | 1280 | 441819 | 6484.2 | 0.893135 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2015.19 | 0.525943 | 405.945ms | 6701 | 640 | 178034 | 3171.2 | 0.576875 | 1(Win) | true |
| simdjson (ondemand) | 1350.13 | 0.425441 | 512.406ms | 6701 | 2560 | 1.03812e+06 | 4733.3 | 0.383865 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 555.545 | 0.134814 | 835.966ms | 4857 | 4890 | 617840 | 8337.75 | 0.0245599 | 1(Win) | true |
| simdjson (ondemand) | 162.43 | 0.382404 | 2872.2ms | 4857 | 160 | 1.90268e+06 | 28516.8 | 0.196762 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 680.916 | 0.21857 | 729.04ms | 4857 | 2560 | 565942 | 6802.6 | 0.0411777 | 1(Win) | true |
| simdjson (ondemand) | 167.214 | 0.144634 | 2827.51ms | 4857 | 4890 | 7.84954e+06 | 27701.1 | 0.628546 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 685.551 | 0.263314 | 984.726ms | 6701 | 1280 | 771182 | 9321.8 | 4.03747 | 1(Win) | true |
| simdjson (ondemand) | 217.827 | 0.167485 | 2933.6ms | 6701 | 4890 | 1.18064e+07 | 29337.9 | 0.437733 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 834.495 | 0.157171 | 812.137ms | 6701 | 4890 | 708415 | 7658.01 | 0.15369 | 1(Win) | true |
| simdjson (ondemand) | 242.773 | 0.278331 | 2835.47ms | 6701 | 40 | 214714 | 26323.2 | 0.331179 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2560.53 | 0.506823 | 183.025ms | 4857 | 2560 | 215193 | 1809 | 0.444198 | 1(Win) | true |
| simdjson (ondemand) | 2139.79 | 0.449661 | 220.993ms | 4857 | 2560 | 242553 | 2164.7 | 0.583264 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3303.85 | 1.54388 | 160.705ms | 4857 | 640 | 299850 | 1402 | 0.199317 | 1(Win) | true |
| simdjson (ondemand) | 2636.16 | 0.566304 | 193.23ms | 4857 | 2560 | 253473 | 1757.1 | 0.582777 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3180.48 | 0.174473 | 204.707ms | 6701 | 4890 | 60097.9 | 2009.31 | 0.145139 | 1(Win) | true |
| simdjson (ondemand) | 2557.35 | 0.443202 | 259.051ms | 6701 | 2560 | 314009 | 2498.9 | 1.4164 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3860.91 | 1.65838 | 196.019ms | 6701 | 320 | 241111 | 1655.2 | 1.72075 | 1(Win) | true |
| simdjson (ondemand) | 3254.85 | 0.636326 | 219.231ms | 6701 | 1280 | 199796 | 1963.4 | 0.316779 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2068.9 | 0.386741 | 220.977ms | 4857 | 4890 | 366615 | 2238.87 | 0.543093 | 1(Win) | true |
| simdjson (ondemand) | 1507.81 | 1.52145 | 353.443ms | 4857 | 40 | 87381.3 | 3072 | 0.278552 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2609.87 | 1.01827 | 203.849ms | 4857 | 640 | 209029 | 1774.8 | 2.22565 | 1(Win) | true |
| simdjson (ondemand) | 1715.55 | 1.03709 | 291.79ms | 4857 | 320 | 250906 | 2700 | 0.0296209 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2673.21 | 0.464486 | 243.713ms | 6701 | 2560 | 315645 | 2390.6 | 0.0334756 | 1(Win) | true |
| simdjson (ondemand) | 1920.47 | 0.316676 | 337.241ms | 6701 | 2560 | 284271 | 3327.6 | 0.0541223 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3156.15 | 0.522547 | 222.39ms | 6701 | 320 | 35823.3 | 2024.8 | 0.277338 | 1(Win) | true |
| simdjson (ondemand) | 2125.54 | 0.174199 | 317.214ms | 6701 | 4890 | 134135 | 3006.56 | 1.76207 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 928.74 | 0.775498 | 178.062ms | 1691 | 1280 | 232098 | 1736.4 | 0.57924 | 1(Win) | true |
| simdjson (ondemand) | 769.694 | 0.589587 | 212.778ms | 1691 | 640 | 97662.4 | 2095.2 | 0.692042 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1152.15 | 0.70542 | 163.107ms | 1691 | 2560 | 249577 | 1399.7 | 2.3921 | 1(Win) | true |
| simdjson (ondemand) | 922.536 | 0.689823 | 201.101ms | 1691 | 4890 | 711058 | 1748.08 | 0.0413488 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1041.93 | 0.389778 | 199.726ms | 2158 | 2560 | 151739 | 1975.2 | 0.893126 | 1(Win) | true |
| simdjson (ondemand) | 1006.08 | 0.620528 | 209.494ms | 2158 | 320 | 51560.2 | 2045.6 | 0.117463 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1413.63 | 0.53179 | 169.852ms | 2158 | 4890 | 293105 | 1455.85 | 0.0103373 | 1(Win) | true |
| simdjson (ondemand) | 1223.85 | 1.11479 | 194.799ms | 2158 | 640 | 224912 | 1681.6 | 0.478011 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 761.053 | 0.242093 | 217.939ms | 1691 | 4890 | 128686 | 2118.99 | 1.24486 | 1(Win) | true |
| simdjson (ondemand) | 537.268 | 0.428459 | 348.048ms | 1691 | 80 | 13231.6 | 3001.6 | 0.213675 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 931.529 | 1.46503 | 199.817ms | 1691 | 320 | 205843 | 1731.2 | 1.59624 | 1(Win) | true |
| simdjson (ondemand) | 569.765 | 0.487427 | 310.732ms | 1691 | 2560 | 487253 | 2830.4 | 0.297661 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 886.814 | 0.307377 | 236.822ms | 2158 | 4890 | 248822 | 2320.7 | 0.535736 | 1(Win) | true |
| simdjson (ondemand) | 661.873 | 0.243946 | 312.922ms | 2158 | 2560 | 147292 | 3109.4 | 0.575754 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1051.9 | 0.280964 | 221.332ms | 2158 | 4890 | 147763 | 1956.49 | 0.271072 | 1(Win) | true |
| simdjson (ondemand) | 772.815 | 0.295539 | 292.067ms | 2158 | 4890 | 302894 | 2663.03 | 0.034868 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3697.92 | 2.33103 | 46.231ms | 1691 | 2560 | 264551 | 436.1 | 0.0229358 | 1(Win) | true |
| simdjson (ondemand) | 2886.47 | 1.27949 | 59.006ms | 1691 | 4890 | 249882 | 558.698 | 0.0361871 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4396.57 | 5.21704 | 41.6481ms | 1691 | 640 | 234362 | 366.8 | 0.108932 | 1(Win) | true |
| simdjson (ondemand) | 3210.8 | 1.44964 | 54.3921ms | 1691 | 4890 | 259234 | 502.263 | 0.0323793 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3979.17 | 1.92096 | 57.5229ms | 2158 | 2560 | 252692 | 517.2 | 1.78504 | 1(Win) | true |
| simdjson (ondemand) | 3378.25 | 1.59611 | 70.0621ms | 2158 | 2560 | 242039 | 609.2 | 0.684708 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 4019.59 | 3.88106 | 52.5619ms | 2158 | 640 | 252708 | 512 | 2.23642 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3664.58 | 3.52099 | 60.958ms | 2158 | 640 | 250244 | 561.6 | 0.707214 | 1(Tie) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2613.29 | 1.56921 | 64.905ms | 1691 | 2560 | 240056 | 617.1 | 0.691986 | 1(Win) | true |
| simdjson (ondemand) | 1888.22 | 0.691378 | 88.396ms | 1691 | 4890 | 170499 | 854.066 | 1.20468 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2877.19 | 1.82113 | 60.8289ms | 1691 | 2560 | 266731 | 560.5 | 0.773103 | 1(Win) | true |
| simdjson (ondemand) | 2084.89 | 1.08448 | 82.2341ms | 1691 | 2560 | 180136 | 773.5 | 0.272232 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2822.89 | 1.02273 | 76.513ms | 2158 | 4890 | 271860 | 729.05 | 0.701402 | 1(Win) | true |
| simdjson (ondemand) | 2213.41 | 1.03326 | 91.6132ms | 2158 | 1280 | 118143 | 929.8 | 0.237171 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2955.76 | 0.972503 | 71.884ms | 2158 | 4890 | 224211 | 696.278 | 0.386119 | 1(Win) | true |
| simdjson (ondemand) | 2538.69 | 0.736361 | 86.1691ms | 2158 | 4890 | 174251 | 810.667 | 0.433964 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 816.68 | 0.704966 | 574.1ms | 4390 | 80 | 104484 | 5126.4 | 0.501882 | 1(Win) | true |
| simdjson (ondemand) | 620.572 | 0.36723 | 723.884ms | 4390 | 640 | 392826 | 6746.4 | 0.333135 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 795.695 | 1.15063 | 518.672ms | 4390 | 320 | 1.17289e+06 | 5261.6 | 0.58948 | 1(Win) | true |
| simdjson (ondemand) | 693.225 | 0.0923429 | 673.556ms | 4390 | 4890 | 152088 | 6039.35 | 1.16764 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1588.03 | 0.152394 | 569.96ms | 9378 | 4890 | 360200 | 5631.84 | 0.0149697 | 1(Win) | true |
| simdjson (ondemand) | 1183.76 | 0.799648 | 765.857ms | 9378 | 80 | 291998 | 7555.2 | 0.127226 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1779.78 | 0.17195 | 553.003ms | 9378 | 2560 | 191133 | 5025.1 | 0.518083 | 1(Win) | true |
| simdjson (ondemand) | 1294.07 | 0.222292 | 737.394ms | 9378 | 1280 | 302111 | 6911.2 | 0.311562 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 598.318 | 0.32026 | 716.959ms | 4390 | 30 | 15065.7 | 6997.33 | 0 | 1(Win) | true |
| simdjson (ondemand) | 477.141 | 0.760435 | 986.306ms | 4390 | 40 | 178081 | 8774.4 | 0.0243191 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 658.814 | 0.380216 | 698.756ms | 4390 | 640 | 373632 | 6354.8 | 0.474323 | 1(Win) | true |
| simdjson (ondemand) | 480.53 | 0.991015 | 924.424ms | 4390 | 30 | 223651 | 8712.53 | 0.0980392 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1182.51 | 0.507408 | 791.146ms | 9378 | 160 | 235639 | 7563.2 | 0.147866 | 1(Win) | true |
| simdjson (ondemand) | 923.769 | 0.254716 | 1001.86ms | 9378 | 640 | 389214 | 9681.6 | 0.476974 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1260.08 | 0.370132 | 821.885ms | 9378 | 160 | 110422 | 7097.6 | 0.135074 | 1(Win) | true |
| simdjson (ondemand) | 985.277 | 0.259367 | 975.565ms | 9378 | 640 | 354742 | 9077.2 | 0.242954 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1556.98 | 0.283856 | 281.398ms | 4390 | 4890 | 284884 | 2688.94 | 0.716995 | 1(Win) | true |
| simdjson (ondemand) | 1253.35 | 0.235073 | 337.054ms | 4390 | 4890 | 301509 | 3340.36 | 0.189589 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1685.57 | 0.426681 | 271.826ms | 4390 | 2560 | 287528 | 2483.8 | 0.265018 | 1(Win) | true |
| simdjson (ondemand) | 1391.92 | 0.17574 | 324.367ms | 4390 | 2560 | 71528.7 | 3007.8 | 0.26 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2731.36 | 0.576124 | 333.118ms | 9378 | 1280 | 455518 | 3274.4 | 0.367827 | 1(Win) | true |
| simdjson (ondemand) | 2237.68 | 0.351077 | 424.403ms | 9378 | 80 | 15751.5 | 3996.8 | 0.08 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2924.64 | 0.336582 | 332.207ms | 9378 | 640 | 67801.1 | 3058 | 0.247912 | 1(Win) | true |
| simdjson (ondemand) | 2456.48 | 0.420284 | 383.619ms | 9378 | 1280 | 299702 | 3640.8 | 0.295761 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1179.47 | 0.807983 | 364.934ms | 4390 | 320 | 263217 | 3549.6 | 0.202429 | 1(Win) | true |
| simdjson (ondemand) | 1083.11 | 0.18612 | 388.396ms | 4390 | 4890 | 253094 | 3865.39 | 0.20715 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1260.43 | 0.584432 | 354.85ms | 4390 | 640 | 241181 | 3321.6 | 0.288184 | 1(Win) | true |
| simdjson (ondemand) | 1162.21 | 0.332443 | 379.271ms | 4390 | 2560 | 367143 | 3602.3 | 0.312708 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 2022.7 | 0.98713 | 469.097ms | 9378 | 320 | 609618 | 4421.6 | 1.82388 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1991.53 | 0.356694 | 457.796ms | 9378 | 1280 | 328434 | 4490.8 | 0.346174 | 1(Tie) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2243.52 | 0.449617 | 409.744ms | 9378 | 640 | 205602 | 3986.4 | 0.638086 | 1(Win) | true |
| simdjson (ondemand) | 1989.22 | 0.356133 | 450.698ms | 9378 | 4890 | 1.25369e+06 | 4496.02 | 0.0884526 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1151.02 | 0.247063 | 391.223ms | 4669 | 2560 | 233852 | 3868.5 | 0.157436 | 1(Win) | true |
| simdjson (ondemand) | 1046.39 | 0.176163 | 430.955ms | 4669 | 4890 | 274790 | 4255.31 | 0.394148 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1334.07 | 0.226855 | 352.602ms | 4669 | 4890 | 280348 | 3337.69 | 0.045368 | 1(Win) | true |
| simdjson (ondemand) | 1176.07 | 0.272543 | 396.04ms | 4669 | 2560 | 272580 | 3786.1 | 0.663798 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1810.05 | 0.561656 | 445.165ms | 7932 | 320 | 176310 | 4179.2 | 0.114987 | 1(Win) | true |
| simdjson (ondemand) | 1608.11 | 1.12641 | 531.851ms | 7932 | 80 | 224606 | 4704 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1959.83 | 0.383426 | 413.089ms | 7932 | 1280 | 280352 | 3859.8 | 0.108696 | 1(Win) | true |
| simdjson (ondemand) | 1772.97 | 0.240226 | 451.715ms | 7932 | 2560 | 268933 | 4266.6 | 0.145104 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 476.898 | 0.304917 | 942.254ms | 4669 | 1280 | 1.03746e+06 | 9336.8 | 0.0643032 | 1(Win) | true |
| simdjson (ondemand) | 197.484 | 0.16549 | 2339.96ms | 4669 | 2560 | 3.56424e+06 | 22547.2 | 1.37609 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 515.105 | 0.905681 | 923.847ms | 4669 | 30 | 183877 | 8644.27 | 0.197044 | 1(Win) | true |
| simdjson (ondemand) | 200.312 | 0.407187 | 2239.93ms | 4669 | 320 | 2.62162e+06 | 22228.8 | 0.422878 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 712.064 | 0.16095 | 1070.74ms | 7932 | 2560 | 748426 | 10623.4 | 0.0752488 | 1(Win) | true |
| simdjson (ondemand) | 336.238 | 0.225192 | 2244.82ms | 7932 | 640 | 1.6427e+06 | 22497.6 | 0.149127 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 775.331 | 0.104976 | 1035.56ms | 7932 | 4890 | 512951 | 9756.53 | 0.0826281 | 1(Win) | true |
| simdjson (ondemand) | 342.642 | 0.095623 | 2305.74ms | 7932 | 4890 | 2.1793e+06 | 22077.1 | 0.195127 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3147.45 | 0.515734 | 152.024ms | 4669 | 4890 | 260310 | 1414.7 | 0.184195 | 1(Win) | true |
| simdjson (ondemand) | 2918.69 | 0.487806 | 156.129ms | 4669 | 4890 | 270816 | 1525.58 | 0.116945 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3481.95 | 0.524781 | 131.13ms | 4669 | 4890 | 220226 | 1278.8 | 0.0779394 | 1(Win) | true |
| simdjson (ondemand) | 3221.97 | 0.576607 | 144.074ms | 4669 | 4890 | 310508 | 1381.98 | 1.2165 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4377.63 | 0.780847 | 178.226ms | 7932 | 1280 | 233040 | 1728 | 0.348432 | 1(Win) | true |
| simdjson (ondemand) | 3897.04 | 0.383752 | 193.667ms | 7932 | 2560 | 142049 | 1941.1 | 0.087656 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4753.27 | 0.471224 | 165.319ms | 7932 | 4890 | 275008 | 1591.44 | 0.0528411 | 1(Win) | true |
| simdjson (ondemand) | 4393.9 | 0.551106 | 178.239ms | 7932 | 2560 | 230449 | 1721.6 | 0.596003 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2352.32 | 0.395248 | 193.057ms | 4669 | 2560 | 143296 | 1892.9 | 0.100274 | 1(Win) | true |
| simdjson (ondemand) | 1826.01 | 0.344552 | 255.468ms | 4669 | 4890 | 345191 | 2438.49 | 0.93473 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2516.22 | 0.713845 | 184.23ms | 4669 | 1280 | 204253 | 1769.6 | 0.112892 | 1(Win) | true |
| simdjson (ondemand) | 1969.09 | 0.432917 | 230.07ms | 4669 | 2560 | 245338 | 2261.3 | 0.0927808 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3182.66 | 0.669452 | 240.916ms | 7932 | 1280 | 324067 | 2376.8 | 0.660681 | 1(Win) | true |
| simdjson (ondemand) | 2838.48 | 0.385661 | 274.355ms | 7932 | 2560 | 270425 | 2665 | 0.648673 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3651.53 | 0.275765 | 212.95ms | 7932 | 4890 | 159589 | 2071.61 | 0.374597 | 1(Win) | true |
| simdjson (ondemand) | 2997.52 | 0.631089 | 257.287ms | 7932 | 1280 | 324663 | 2523.6 | 0.670177 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 343.893 | 0.102752 | 1282.58ms | 4604 | 4890 | 841622 | 12767.7 | 0.0501436 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 343.884 | 0.345024 | 1304.16ms | 4604 | 640 | 1.242e+06 | 12768 | 0.554435 | 1(Tie) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 450.178 | 0.145916 | 1176.03ms | 4604 | 2560 | 518500 | 9753.3 | 3.66731 | 1(Win) | true |
| simdjson (ondemand) | 398.757 | 0.181388 | 1257.22ms | 4604 | 1280 | 510598 | 11011 | 0.0236072 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1322.65 | 0.54862 | 1341.34ms | 18245 | 160 | 833410 | 13155.2 | 0.796332 | 1(Win) | true |
| simdjson (ondemand) | 1232.54 | 0.159066 | 1420.05ms | 18245 | 1280 | 645433 | 14117 | 0.097659 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1506.42 | 0.212195 | 1301.44ms | 18245 | 1280 | 768905 | 11550.4 | 0.0519733 | 1(Win) | true |
| simdjson (ondemand) | 1401.28 | 0.146813 | 1442.36ms | 18245 | 2560 | 850763 | 12417.1 | 0.790189 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 236.321 | 0.0935528 | 1897.36ms | 4604 | 4890 | 1.47737e+06 | 18579.5 | 0.113572 | 1(Win) | true |
| simdjson (ondemand) | 164.307 | 0.105793 | 2790.34ms | 4604 | 4890 | 3.90825e+06 | 26722.7 | 2.03649 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 258.737 | 0.131031 | 1859.99ms | 4604 | 2560 | 1.26573e+06 | 16969.8 | 0.00589317 | 1(Win) | true |
| simdjson (ondemand) | 172.606 | 0.159658 | 2741.59ms | 4604 | 2560 | 4.22259e+06 | 25437.8 | 1.41152 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 840.992 | 0.305481 | 2092.58ms | 18245 | 2560 | 1.02262e+07 | 20689.6 | 1.86803 | 1(Win) | true |
| simdjson (ondemand) | 622.773 | 0.194449 | 2899.18ms | 18245 | 640 | 1.88894e+06 | 27939.2 | 0.0944017 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 941.547 | 0.391057 | 1969.21ms | 18245 | 320 | 1.67122e+06 | 18480 | 0.849858 | 1(Win) | true |
| simdjson (ondemand) | 642.78 | 0.165603 | 2873.66ms | 18245 | 1280 | 2.57224e+06 | 27069.6 | 0.0443105 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2397.07 | 0.469837 | 185.061ms | 4604 | 2560 | 189602 | 1831.7 | 0.461906 | 1(Win) | true |
| Jsonifier (generic) | 2344.76 | 0.416995 | 193.176ms | 4604 | 4890 | 298158 | 1872.57 | 1.72584 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2692.7 | 0.632847 | 169.27ms | 4604 | 2560 | 272604 | 1630.6 | 0.258239 | 1(Win) | true |
| simdjson (ondemand) | 2537.2 | 0.404285 | 176.534ms | 4604 | 4890 | 239358 | 1730.54 | 0.0890144 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6112.91 | 0.694556 | 283.433ms | 18245 | 640 | 250142 | 2846.4 | 0.112296 | 1(Win) | true |
| simdjson (ondemand) | 5328.21 | 0.232867 | 329.673ms | 18245 | 4890 | 282780 | 3265.6 | 0.0613071 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6439.6 | 0.703707 | 278.194ms | 18245 | 640 | 231385 | 2702 | 0.690973 | 1(Win) | true |
| simdjson (ondemand) | 5399.63 | 0.212685 | 327.733ms | 18245 | 4890 | 229692 | 3222.41 | 0.12687 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1867.34 | 0.329288 | 239.332ms | 4604 | 4890 | 293148 | 2351.33 | 0.333758 | 1(Win) | true |
| simdjson (ondemand) | 1452.92 | 0.633211 | 322.976ms | 4604 | 1280 | 468701 | 3022 | 1.46387 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1802.43 | 0.434204 | 247.245ms | 4604 | 2560 | 286406 | 2436 | 1.66317 | 1(Win) | true |
| simdjson (ondemand) | 1463.77 | 0.373745 | 307.192ms | 4604 | 1280 | 160874 | 2999.6 | 0.294236 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4767.11 | 0.401513 | 369.833ms | 18245 | 4890 | 1.05023e+06 | 3649.96 | 1.2536 | 1(Win) | true |
| simdjson (ondemand) | 3863.19 | 0.298775 | 458.054ms | 18245 | 2560 | 463579 | 4504 | 0.464088 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5097.2 | 0.319921 | 352.437ms | 18245 | 2560 | 305317 | 3413.6 | 0.42007 | 1(Win) | true |
| simdjson (ondemand) | 3931.99 | 0.196591 | 443.336ms | 18245 | 4890 | 370084 | 4425.19 | 0.508488 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 846.817 | 0.442441 | 560.707ms | 4926 | 640 | 385569 | 5547.6 | 0.151188 | 1(Win) | true |
| simdjson (ondemand) | 515.862 | 0.518399 | 852.127ms | 4926 | 2560 | 5.70546e+06 | 9106.7 | 0.212382 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1119.51 | 0.221193 | 505.188ms | 4926 | 2560 | 220554 | 4196.3 | 0.409169 | 1(Win) | true |
| simdjson (ondemand) | 704.176 | 0.153813 | 757.965ms | 4926 | 4890 | 514897 | 6671.34 | 0.457489 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1377.9 | 0.488073 | 577.536ms | 8150 | 320 | 242549 | 5640.8 | 0.0425291 | 1(Win) | true |
| simdjson (ondemand) | 926.173 | 0.812163 | 855.3ms | 8150 | 1280 | 5.94603e+06 | 8392 | 0.291601 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1718.04 | 0.196327 | 537.512ms | 8150 | 4890 | 385761 | 4524.03 | 0.266136 | 1(Win) | true |
| simdjson (ondemand) | 1090.56 | 0.207783 | 803.454ms | 8150 | 1280 | 280701 | 7127 | 0.560888 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 601.588 | 0.273442 | 787.025ms | 4926 | 1280 | 583623 | 7809 | 0.476068 | 1(Win) | true |
| simdjson (ondemand) | 320.183 | 0.10019 | 1445.58ms | 4926 | 4890 | 1.0567e+06 | 14672.3 | 0.0459485 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 783.384 | 0.337922 | 707.12ms | 4926 | 40 | 16426 | 5996.8 | 0.177557 | 1(Win) | true |
| simdjson (ondemand) | 356.493 | 0.167187 | 1456.8ms | 4926 | 1280 | 621298 | 13177.8 | 0.0227604 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 920.731 | 0.306725 | 851.118ms | 8150 | 640 | 429071 | 8441.6 | 0.640301 | 1(Win) | true |
| simdjson (ondemand) | 544.777 | 0.25689 | 1528.02ms | 8150 | 160 | 214927 | 14267.2 | 0.568689 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1114.76 | 0.105474 | 783.548ms | 8150 | 4890 | 264458 | 6972.31 | 0.23596 | 1(Win) | true |
| simdjson (ondemand) | 592.195 | 0.335724 | 1422.58ms | 8150 | 640 | 1.2426e+06 | 13124.8 | 1.17463 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1664.47 | 1.58894 | 294.514ms | 4926 | 80 | 160895 | 2822.4 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1195.37 | 0.422188 | 404.113ms | 4926 | 640 | 176188 | 3930 | 0.817686 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1906.34 | 0.448729 | 278.092ms | 4926 | 2560 | 313037 | 2464.3 | 0.279217 | 1(Win) | true |
| simdjson (ondemand) | 1327.82 | 0.229969 | 391.848ms | 4926 | 4890 | 323712 | 3537.98 | 0.0419291 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2381.26 | 0.919952 | 337.358ms | 8150 | 160 | 144262 | 3264 | 0.0981354 | 1(Win) | true |
| simdjson (ondemand) | 1770.4 | 0.193857 | 443.74ms | 8150 | 4890 | 354195 | 4390.22 | 0.258439 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2661.16 | 0.296905 | 327.026ms | 8150 | 4890 | 367720 | 2920.7 | 0.310483 | 1(Win) | true |
| simdjson (ondemand) | 1865.06 | 0.303041 | 449.316ms | 8150 | 4890 | 779911 | 4167.41 | 1.2369 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1293.02 | 0.452063 | 362.856ms | 4926 | 1280 | 345292 | 3633.2 | 0.0770077 | 1(Win) | true |
| simdjson (ondemand) | 932.769 | 0.324305 | 503.33ms | 4926 | 640 | 170737 | 5036.4 | 0.00794155 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1569.12 | 0.153193 | 339.169ms | 4926 | 2560 | 53851 | 2993.9 | 0.0300702 | 1(Win) | true |
| simdjson (ondemand) | 1045.26 | 0.382121 | 481.31ms | 4926 | 1280 | 377534 | 4494.4 | 1.12501 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1953.78 | 0.143998 | 405.772ms | 8150 | 4890 | 160466 | 3978.16 | 0.253427 | 1(Win) | true |
| simdjson (ondemand) | 1529.05 | 0.480619 | 531.642ms | 8150 | 160 | 95498.6 | 5083.2 | 0.094518 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1999.81 | 0.562385 | 407.94ms | 8150 | 1280 | 611529 | 3886.6 | 0.689119 | 1(Win) | true |
| simdjson (ondemand) | 1617.51 | 0.466538 | 500.787ms | 8150 | 1280 | 643292 | 4805.2 | 0.899192 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1845.21 | 1.3694 | 150.201ms | 2821 | 640 | 255127 | 1458 | 0.635008 | 1(Win) | true |
| simdjson (ondemand) | 1358.2 | 0.468167 | 204.934ms | 2821 | 320 | 27519 | 1980.8 | 0 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2059.36 | 0.53127 | 146.168ms | 2821 | 4890 | 235550 | 1306.39 | 0.100537 | 1(Win) | true |
| simdjson (ondemand) | 1461.89 | 0.49383 | 201.219ms | 2821 | 2560 | 211433 | 1840.3 | 1.13356 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2060.82 | 0.408315 | 175.539ms | 3770 | 4890 | 248143 | 1744.62 | 0.311734 | 1(Win) | true |
| simdjson (ondemand) | 1751.38 | 0.192507 | 209.503ms | 3770 | 4890 | 76370.2 | 2052.87 | 0.074537 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2410.64 | 0.720402 | 167.513ms | 3770 | 4890 | 564514 | 1491.45 | 2.18201 | 1(Win) | true |
| simdjson (ondemand) | 1901.77 | 0.293165 | 205.664ms | 3770 | 4890 | 150210 | 1890.53 | 0.0726269 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 701.54 | 0.212609 | 392.115ms | 2821 | 4890 | 325067 | 3834.87 | 0.74105 | 1(Win) | true |
| simdjson (ondemand) | 301.931 | 0.139678 | 913.074ms | 2821 | 4890 | 757454 | 8910.37 | 0.037352 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 753.674 | 0.777892 | 415.093ms | 2821 | 320 | 246733 | 3569.6 | 0.0897263 | 1(Win) | true |
| simdjson (ondemand) | 307.993 | 0.184222 | 887.939ms | 2821 | 2560 | 662901 | 8735 | 0.0733222 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 869.535 | 0.397324 | 423.009ms | 3770 | 2560 | 690937 | 4134.8 | 0.591431 | 1(Win) | true |
| simdjson (ondemand) | 416.727 | 0.186131 | 876.006ms | 3770 | 2560 | 660175 | 8627.6 | 0.0324435 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 891.351 | 0.454576 | 433.449ms | 3770 | 640 | 215169 | 4033.6 | 0.618639 | 1(Win) | true |
| simdjson (ondemand) | 425.399 | 0.126214 | 865.422ms | 3770 | 4890 | 556432 | 8451.72 | 0.206502 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3763.2 | 1.30907 | 73.282ms | 2821 | 2560 | 224212 | 714.9 | 1.14601 | 1(Win) | true |
| simdjson (ondemand) | 3436.49 | 0.775662 | 81.2639ms | 2821 | 4890 | 180315 | 782.868 | 0.965478 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4030.53 | 1.06268 | 73.6069ms | 2821 | 4890 | 246033 | 667.485 | 0.196671 | 1(Win) | true |
| simdjson (ondemand) | 3561.44 | 1.60629 | 80.2468ms | 2821 | 1280 | 188456 | 755.4 | 0.398724 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4317.94 | 0.677443 | 84.642ms | 3770 | 4890 | 155591 | 832.654 | 1.35781 | 1(Win) | true |
| simdjson (ondemand) | 4070.82 | 0.741364 | 92.3881ms | 3770 | 2560 | 109754 | 883.2 | 0.585322 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4614.14 | 0.802181 | 84.278ms | 3770 | 4890 | 191054 | 779.203 | 0.257755 | 1(Win) | true |
| simdjson (ondemand) | 4130.22 | 0.808761 | 92.66ms | 3770 | 2560 | 126887 | 870.5 | 0.44602 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3008.96 | 0.697874 | 93.4812ms | 2821 | 2560 | 99670.5 | 894.1 | 0.122878 | 1(Win) | true |
| simdjson (ondemand) | 2524.7 | 1.37738 | 115.041ms | 2821 | 320 | 68936.1 | 1065.6 | 0.452489 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3043.34 | 1.0355 | 95.5789ms | 2821 | 1280 | 107255 | 884 | 0.500227 | 1(Win) | true |
| simdjson (ondemand) | 2038.74 | 1.67252 | 123.428ms | 2821 | 640 | 311751 | 1319.6 | 2.58085 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3343.89 | 2.88514 | 127.98ms | 3770 | 80 | 76984.1 | 1075.2 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3027.28 | 0.518845 | 122.349ms | 3770 | 4890 | 185679 | 1187.65 | 0.27453 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3601.11 | 1.42843 | 122.082ms | 3770 | 30 | 6101.63 | 998.4 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3213 | 0.833437 | 119.561ms | 3770 | 1280 | 111331 | 1119 | 0.0178699 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3684.13 | 0.271267 | 7250.03ms | 277673 | 40 | 1.52073e+06 | 71878.4 | 0.0326371 | 1(Win) | true |
| simdjson (ondemand) | 2995.14 | 0.0677565 | 8827.67ms | 277673 | 4890 | 1.75487e+07 | 88413.1 | 0.289232 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3299.68 | 0.431571 | 9869.14ms | 10548466 | 40 | 6.92465e+09 | 3.04872e+06 | 1.80614 | 1(Win) | true |
| simdjson (ondemand) | 2796.91 | 0.136677 | 5384.41ms | 10548466 | 80 | 1.93331e+09 | 3.59675e+06 | 0.352936 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2349.92 | 0.275282 | 9999.89ms | 16002592 | 40 | 1.27847e+10 | 6.49437e+06 | 1.82449 | 1(Win) | true |
| simdjson (ondemand) | 2243.43 | 0.374054 | 10141ms | 16002592 | 30 | 1.94243e+10 | 6.80264e+06 | 0.603482 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2324.73 | 0.210029 | 10117.2ms | 16002591 | 80 | 1.52084e+10 | 6.56473e+06 | 0.194628 | 1(Win) | true |
| simdjson (ondemand) | 1278.73 | 0.531741 | 8281.52ms | 16002591 | 30 | 1.20822e+11 | 1.19347e+07 | 1.51518 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 10122 | 0.388561 | 9883.57ms | 16197086 | 40 | 1.40643e+09 | 1.52605e+06 | 1.10327 | 1(Win) | true |
| simdjson (ondemand) | 8663.03 | 0.155873 | 5922.47ms | 16197086 | 30 | 2.31737e+08 | 1.78307e+06 | 0.186297 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 10189 | 0.174498 | 9876.84ms | 16197085 | 320 | 2.23944e+09 | 1.51602e+06 | 0.471015 | 1(Win) | true |
| simdjson (ondemand) | 8293.35 | 0.0956118 | 5973.29ms | 16197085 | 30 | 9.51388e+07 | 1.86255e+06 | 1.48583 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1375.98 | 0.852218 | 5666.58ms | 4212000 | 40 | 2.47578e+10 | 2.91928e+06 | 0.180901 | 1(Win) | true |
| simdjson (ondemand) | 931.718 | 0.500167 | 8126.59ms | 4212000 | 40 | 1.85993e+10 | 4.31126e+06 | 0.734336 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1278.66 | 0.373315 | 6117.09ms | 4211999 | 40 | 5.50148e+09 | 3.14148e+06 | 1.13895 | 1(Win) | true |
| simdjson (ondemand) | 796.477 | 0.339542 | 9289.39ms | 4211999 | 30 | 8.79709e+09 | 5.0433e+06 | 1.15335 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1155.05 | 0.419606 | 6814.06ms | 4212000 | 40 | 8.51761e+09 | 3.47766e+06 | 1.47043 | 1(Win) | true |
| simdjson (ondemand) | 828.988 | 0.394587 | 8807.64ms | 4212000 | 40 | 1.46227e+10 | 4.84552e+06 | 0.619907 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1140.05 | 0.881464 | 6441.1ms | 4211999 | 30 | 2.89376e+10 | 3.52343e+06 | 3.73823 | 1(Win) | true |
| simdjson (ondemand) | 723.592 | 0.36097 | 9832.04ms | 4211999 | 30 | 1.20463e+10 | 5.5513e+06 | 1.68017 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1016.48 | 0.589544 | 6953.62ms | 4525120 | 40 | 2.50583e+10 | 4.24551e+06 | 1.37761 | 1(Win) | true |
| simdjson (ondemand) | 890.814 | 0.294216 | 7662.71ms | 4525120 | 40 | 8.12602e+09 | 4.84444e+06 | 0.708561 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 953.979 | 0.100687 | 7896.09ms | 4525119 | 80 | 1.65965e+09 | 4.52367e+06 | 6.417 | -(Win) | false |
| simdjson (ondemand) | 663.041 | 0.367135 | 10271.5ms | 4525119 | 40 | 2.28398e+10 | 6.50863e+06 | 0.742895 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 579.022 | 0.209404 | 5520.37ms | 4525120 | 40 | 9.74315e+09 | 7.45306e+06 | 1.33446 | 1(Win) | true |
| simdjson (ondemand) | 414.04 | 0.879475 | 7605.64ms | 4525120 | 30 | 2.52083e+11 | 1.04229e+07 | 0.664847 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 587.976 | 0.392317 | 5546.63ms | 4525119 | 40 | 3.31647e+10 | 7.33957e+06 | 1.48183 | 1(Win) | true |
| simdjson (ondemand) | 358.217 | 0.662594 | 8713.51ms | 4525119 | 30 | 1.91154e+11 | 1.20471e+07 | 0.928766 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 868.211 | 0.234616 | 7745.66ms | 4203059 | 30 | 3.5198e+09 | 4.61679e+06 | 4.33036 | 1(Win) | true |
| simdjson (ondemand) | 627.283 | 0.501803 | 10067.3ms | 4203059 | 30 | 3.08454e+10 | 6.39002e+06 | 1.75903 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 738.485 | 0.458162 | 8766.69ms | 4203058 | 40 | 2.4737e+10 | 5.4278e+06 | 0.671942 | 1(Win) | true |
| simdjson (ondemand) | 476.072 | 2.59135 | 5766.72ms | 4203058 | 40 | 1.90414e+12 | 8.41962e+06 | 1.36893 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 620.769 | 0.576937 | 10419ms | 4203059 | 30 | 4.16341e+10 | 6.45707e+06 | 1.47535 | 1(Win) | true |
| simdjson (ondemand) | 497.256 | 0.726509 | 5860.87ms | 4203059 | 30 | 1.02891e+11 | 8.06095e+06 | 1.1857 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 575.137 | 0.288884 | 5214.1ms | 4203058 | 40 | 1.62142e+10 | 6.96938e+06 | 0.671606 | 1(Win) | true |
| simdjson (ondemand) | 451.088 | 0.656614 | 6766.63ms | 4203058 | 30 | 1.02129e+11 | 8.88596e+06 | 3.01456 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1277.66 | 0.155011 | 10073.5ms | 4197496 | 80 | 1.88697e+09 | 3.1331e+06 | 0.24727 | 1(Win) | true |
| simdjson (ondemand) | 1174.1 | 0.185734 | 5271.52ms | 4197496 | 80 | 3.20806e+09 | 3.40945e+06 | 0.0123876 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1108.13 | 0.452496 | 5457.89ms | 4197495 | 30 | 8.01588e+09 | 3.61243e+06 | 0.412483 | 1(Win) | true |
| simdjson (ondemand) | 746.573 | 0.607904 | 7771.76ms | 4197495 | 80 | 8.49954e+10 | 5.36189e+06 | 2.68153 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 817.681 | 0.118216 | 7994.9ms | 4197496 | 30 | 1.00482e+09 | 4.89561e+06 | 1.24659 | 1(Win) | true |
| simdjson (ondemand) | 561.837 | 0.604134 | 10114.6ms | 4197496 | 30 | 5.55839e+10 | 7.12492e+06 | 1.26706 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 760.34 | 0.347831 | 7948.78ms | 4197495 | 40 | 1.34141e+10 | 5.26481e+06 | 0.746656 | 1(Win) | true |
| simdjson (ondemand) | 499.611 | 0.260589 | 5675.37ms | 4197495 | 40 | 1.74376e+10 | 8.01231e+06 | 0.384905 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1055.36 | 0.230802 | 7438.81ms | 4506447 | 80 | 7.06705e+09 | 4.07225e+06 | 0.29014 | 1(Win) | true |
| simdjson (ondemand) | 645.205 | 0.99706 | 5199.17ms | 4506447 | 30 | 1.32324e+11 | 6.66096e+06 | 2.25903 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 964.106 | 0.230331 | 7764.88ms | 4506446 | 30 | 3.16261e+09 | 4.45769e+06 | 1.22191 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 585.826 | 0.405327 | 5898.64ms | 4506446 | 40 | 3.53672e+10 | 7.3361e+06 | 12.655 | -(Loss) | false |

----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 673.936 | 0.504526 | 10738.9ms | 4506447 | 30 | 3.10541e+10 | 6.37699e+06 | 0.396992 | 1(Win) | true |
| simdjson (ondemand) | 371.086 | 0.864807 | 8577.52ms | 4506447 | 30 | 3.0094e+11 | 1.15814e+07 | 0.353083 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 704.388 | 0.191172 | 10748.4ms | 4506446 | 30 | 4.08143e+09 | 6.1013e+06 | 5.31309 | -(Win) | false |
| simdjson (ondemand) | 338.441 | 0.827814 | 9475.43ms | 4506446 | 40 | 4.42006e+11 | 1.26985e+07 | 0.058128 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1672.95 | 0.220646 | 8585.25ms | 4219120 | 40 | 1.12649e+09 | 2.40513e+06 | 0.522797 | 1(Win) | true |
| simdjson (ondemand) | 1382.95 | 0.256344 | 10169.3ms | 4219120 | 160 | 8.90012e+09 | 2.90947e+06 | 1.75364 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1431.32 | 0.566427 | 9543.31ms | 4219119 | 30 | 7.60639e+09 | 2.81115e+06 | 0.213549 | 1(Win) | true |
| simdjson (ondemand) | 1200.29 | 0.748127 | 5677.69ms | 4219119 | 30 | 1.88686e+10 | 3.35223e+06 | 0.420786 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 635.875 | 0.34313 | 9945.1ms | 4219120 | 80 | 3.77145e+10 | 6.32776e+06 | 1.16517 | 1(Win) | true |
| simdjson (ondemand) | 289.397 | 0.700682 | 10424.9ms | 4219120 | 40 | 3.79628e+11 | 1.39036e+07 | 1.3642 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 636.604 | 0.462925 | 10062.2ms | 4219119 | 80 | 6.84883e+10 | 6.32052e+06 | 1.08477 | 1(Win) | true |
| simdjson (ondemand) | 261.077 | 0.71966 | 10912.3ms | 4219119 | 30 | 3.69047e+11 | 1.54118e+07 | 1.64031 | 2(Loss) | true |
