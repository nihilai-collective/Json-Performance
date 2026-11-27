# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 874.211 | 0.0530872 | 813.161ms | 905 | 4890 | 1343.24 | 987.262 | 0.136138 | 6.11517 | 28.2088 | 4.59448 | 0.00322114 | 0.000163373 | 3.09573e-05 | 1(Win) | true |
| simdjson (ondemand) | 520.019 | 0.393841 | 879.778ms | 905 | 30 | 1281.8 | 1659.7 | 0.130375 | 10.1015 | 50.8144 | 9.59227 | 0.0365009 | 0.000257827 | 0.000257827 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 977.003 | 0.0687599 | 802.575ms | 905 | 4890 | 1804.2 | 883.39 | 0.166357 | 5.50141 | 26.8022 | 4.48398 | 0.00298343 | 0.000138743 | 3.05054e-05 | 1(Win) | true |
| simdjson (ondemand) | 541.511 | 0.0942116 | 881.789ms | 905 | 320 | 721.51 | 1593.83 | 0.131389 | 9.75429 | 50.1282 | 9.45304 | 0.031982 | 4.14365e-05 | 1.03591e-05 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 777.112 | 0.0538629 | 939.734ms | 1811 | 2560 | 3668.51 | 2222.46 | 0.0315042 | 6.72055 | 30.4401 | 6.63225 | 0.000778015 | 0.000123378 | 3.81781e-05 | 1(Win) | true |
| simdjson (ondemand) | 457.682 | 0.0625762 | 1097.44ms | 1811 | 1280 | 7137.35 | 3773.59 | 0.0152973 | 11.3677 | 57.8609 | 11.5036 | 0.00091455 | 0.000142791 | 3.62369e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.516 | 0.258981 | 922.759ms | 1811 | 30 | 885.013 | 2097.23 | 0.0158965 | 6.37646 | 29.3412 | 6.38929 | 0.00145408 | 9.20302e-05 | 9.20302e-05 | 1(Win) | true |
| simdjson (ondemand) | 445.566 | 0.163245 | 1091.94ms | 1811 | 30 | 1201.2 | 3876.2 | 0.29666 | 11.4678 | 56.7841 | 11.2662 | 0.002448 | 0.000257685 | 0.000110436 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 895.609 | 0.138217 | 862.323ms | 1313 | 1280 | 4779.96 | 1398.13 | 0.344781 | 5.92577 | 29.035 | 5.7936 | 0.000869907 | 0.000234435 | 9.63919e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.557 | 0.0430505 | 1036.35ms | 1313 | 2560 | 4659.79 | 3133.9 | 0.126437 | 13.0329 | 55.2513 | 10.936 | 0.00247495 | 0.000211229 | 9.93669e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1000.4 | 0.0671166 | 844.074ms | 1313 | 2560 | 1806.68 | 1251.67 | 0.20781 | 5.30809 | 27.7113 | 5.50647 | 0.00214293 | 0.000117515 | 1.16027e-05 | 1(Win) | true |
| simdjson (ondemand) | 415.588 | 0.0240812 | 1022.34ms | 1313 | 160 | 84.2324 | 3013.02 | 0.00726069 | 12.5634 | 53.754 | 10.6101 | 0.00152323 | 3.33206e-05 | 4.76009e-06 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 894.545 | 0.114818 | 1176.92ms | 4215 | 1280 | 34073.7 | 4493.61 | 0.13942 | 5.73628 | 25.4792 | 4.21139 | 0.00371849 | 4.89324e-05 | 1.01942e-05 | 1(Win) | true |
| Jsonifier (generic) | 828.716 | 0.0580026 | 1212.57ms | 4215 | 2560 | 20263.7 | 4850.56 | 0.00997691 | 6.16921 | 21.3661 | 4.91886 | 0.00192301 | 7.67349e-05 | 2.53003e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1091.89 | 0.11293 | 1141.76ms | 4215 | 1280 | 22124.4 | 3681.46 | 0.205354 | 4.67338 | 21.3381 | 3.18553 | 0.00404322 | 3.65139e-05 | 7.7847e-06 | 1(Win) | true |
| Jsonifier (generic) | 1038.86 | 0.0515146 | 1162.26ms | 4215 | 2560 | 10171.3 | 3869.36 | 0.0607301 | 4.96847 | 16.6009 | 3.76275 | 0.00184108 | 3.41044e-05 | 4.63375e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.094 | 0.0537683 | 845.781ms | 1213 | 4890 | 2414.93 | 1306.99 | 0.0104433 | 5.96425 | 30.0264 | 5.98351 | 0.00170849 | 0.000166061 | 2.8323e-05 | 1(Win) | true |
| simdjson (ondemand) | 376.351 | 0.0713994 | 1024.3ms | 1213 | 640 | 3082.5 | 3073.74 | 0.0234289 | 13.9047 | 58.7205 | 11.8104 | 0.00347666 | 0.000247321 | 0.000113355 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 995.617 | 0.08193 | 828.605ms | 1213 | 320 | 289.984 | 1161.9 | 0.0360531 | 5.34074 | 28.4419 | 5.63067 | 0.00179823 | 0.00010305 | 1.28813e-05 | 1(Win) | true |
| simdjson (ondemand) | 389.391 | 0.0226928 | 1015.93ms | 1213 | 320 | 145.438 | 2970.81 | 0.00504887 | 13.4082 | 57.2597 | 11.4946 | 0.00634532 | 0.000193219 | 1.28813e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.18 | 0.0253445 | 6497.52ms | 94653 | 1280 | 271737 | 57489.1 | 0.0437486 | 3.22612 | 14.2473 | 2.80962 | 0.00913928 | 8.8316e-06 | 5.25769e-06 | 1(Win) | true |
| simdjson (ondemand) | 1273.65 | 0.0478735 | 7842.25ms | 94653 | 640 | 736782 | 70873.5 | 0.0134126 | 4.0039 | 15.8434 | 3.10317 | 0.0121331 | 2.34244e-05 | 1.56328e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2275.83 | 0.0319201 | 5947.22ms | 94653 | 1280 | 205176 | 39663.8 | 0.0784902 | 2.22115 | 10.4664 | 1.94124 | 0.00631993 | 1.54182e-05 | 1.06392e-05 | 1(Win) | true |
| simdjson (ondemand) | 1675.03 | 0.0402435 | 7394.61ms | 94653 | 640 | 301020 | 53890.4 | 0.0130543 | 3.03031 | 12.0929 | 2.24294 | 0.00945232 | 1.83235e-05 | 1.23312e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2037.08 | 0.120894 | 6664.82ms | 124597 | 40 | 198913 | 58330.9 | 0.0201682 | 2.52772 | 11.2751 | 2.14485 | 0.00697729 | 1.32427e-05 | 7.82523e-06 | 1(Win) | true |
| simdjson (ondemand) | 1642.13 | 0.0799256 | 7964.64ms | 124597 | 160 | 535171 | 72360.2 | 0.0405445 | 3.0943 | 12.3801 | 2.37419 | 0.00945137 | 5.06633e-06 | 2.30744e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2899.04 | 0.063779 | 6065.46ms | 124597 | 320 | 218681 | 40987.7 | 0.03191 | 1.748 | 8.39641 | 1.48486 | 0.00439201 | 4.99109e-06 | 2.43284e-06 | 1(Win) | true |
| simdjson (ondemand) | 2162.66 | 0.0580209 | 7487.13ms | 124597 | 320 | 325205 | 54943.8 | 0.0346724 | 2.34722 | 9.51904 | 1.71908 | 0.00674959 | 1.14369e-05 | 6.82199e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1166.15 | 0.0653098 | 8480.5ms | 94653 | 2560 | 6.54269e+06 | 77406.9 | 0.0323616 | 4.3636 | 20.3338 | 4.12888 | 0.0104496 | 3.52067e-05 | 1.94543e-05 | 1(Win) | true |
| simdjson (ondemand) | 711.261 | 0.075279 | 6948.7ms | 94653 | 320 | 2.92085e+06 | 126913 | 0.446414 | 7.15439 | 34.1518 | 7.07104 | 0.0134407 | 3.36756e-05 | 2.20212e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1522.7 | 0.0231543 | 7934.29ms | 94653 | 4890 | 921326 | 59281.8 | 0.0510307 | 3.33441 | 16.5582 | 3.26323 | 0.00738866 | 1.27168e-05 | 7.93556e-06 | 1(Win) | true |
| simdjson (ondemand) | 809.529 | 0.113411 | 6722.93ms | 94653 | 40 | 639697 | 111507 | 0.413591 | 6.2436 | 30.4059 | 6.21247 | 0.0109571 | 1.0829e-05 | 3.16947e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1495.39 | 0.0796647 | 8630.56ms | 124597 | 160 | 641148 | 79460.8 | 0.17151 | 3.38276 | 15.9192 | 3.17607 | 0.00853662 | 3.26051e-05 | 2.29741e-05 | 1(Win) | true |
| simdjson (ondemand) | 907.597 | 0.158257 | 6974.07ms | 124597 | 40 | 1.71718e+06 | 130923 | 0.019188 | 5.56825 | 25.9986 | 5.32597 | 0.0102521 | 1.26408e-05 | 8.22652e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1953.54 | 0.0174429 | 8111.66ms | 124597 | 4890 | 550451 | 60825.4 | 0.0187375 | 2.59383 | 13.0456 | 2.51824 | 0.00562364 | 2.08065e-05 | 1.58433e-05 | 1(Win) | true |
| simdjson (ondemand) | 1056.85 | 0.0272792 | 6748.75ms | 124597 | 2560 | 2.40821e+06 | 112433 | 0.130305 | 4.8034 | 23.1629 | 4.67771 | 0.00868503 | 1.67446e-05 | 1.01201e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2692.93 | 0.0491661 | 4090.81ms | 94653 | 640 | 173833 | 33520.4 | 0.0360405 | 1.88535 | 8.84308 | 1.64076 | 0.00533508 | 8.41891e-06 | 4.65516e-06 | 1(Win) | true |
| simdjson (ondemand) | 1900.84 | 0.0226157 | 5521.01ms | 94653 | 2560 | 295282 | 47488.6 | 0.14245 | 2.68075 | 10.6628 | 1.9762 | 0.0083572 | 1.31236e-05 | 8.87287e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3821.25 | 0.0191686 | 3604.66ms | 94653 | 4890 | 100265 | 23622.7 | 0.0666092 | 1.33129 | 6.99845 | 1.20952 | 0.00230259 | 5.25005e-06 | 2.55157e-06 | 1(Win) | true |
| simdjson (ondemand) | 2306.16 | 0.0594446 | 5177.86ms | 94653 | 320 | 173246 | 39142.1 | 0.204802 | 2.22599 | 8.83642 | 1.55045 | 0.00710711 | 3.05062e-05 | 2.41012e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3416.26 | 0.0165388 | 4213.12ms | 124597 | 4890 | 161819 | 34782.2 | 0.0425796 | 1.48856 | 7.17579 | 1.26302 | 0.00291734 | 1.12986e-05 | 7.75835e-06 | 1(Win) | true |
| simdjson (ondemand) | 2444.77 | 0.0228565 | 5609.99ms | 124597 | 2560 | 315935 | 48603.8 | 0.0114338 | 2.07692 | 8.15313 | 1.45488 | 0.00673184 | 1.67415e-05 | 1.27223e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4509.58 | 0.04659 | 3878.34ms | 124597 | 640 | 96451.2 | 26349.4 | 0.212644 | 1.12768 | 5.77635 | 0.935493 | 0.00170081 | 5.65573e-06 | 3.72451e-06 | 1(Win) | true |
| simdjson (ondemand) | 3043 | 0.0336876 | 5137.74ms | 124597 | 1280 | 221493 | 39048.6 | 0.0309706 | 1.6755 | 6.77486 | 1.13259 | 0.00499159 | 1.0233e-05 | 7.00383e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1978.18 | 0.06737 | 5343.07ms | 94653 | 80 | 75606.7 | 45631.9 | 0.129875 | 2.60469 | 12.3298 | 2.42524 | 0.00670753 | 6.07482e-06 | 2.24504e-06 | 1(Win) | true |
| simdjson (ondemand) | 1597.72 | 0.0154992 | 6393.06ms | 94653 | 4890 | 374970 | 56498.1 | 0.18563 | 3.20382 | 13.2188 | 2.51031 | 0.00919351 | 9.74607e-06 | 5.37103e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2393.22 | 0.025472 | 5008.07ms | 94653 | 2560 | 236304 | 37718.3 | 0.0899607 | 2.12776 | 10.4805 | 1.99093 | 0.00553168 | 1.55543e-05 | 1.12252e-05 | 1(Win) | true |
| simdjson (ondemand) | 1855.3 | 0.022 | 6089.18ms | 94653 | 2560 | 293310 | 48654.3 | 0.00835143 | 2.75764 | 11.3965 | 2.08434 | 0.00860629 | 5.4434e-06 | 1.95616e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2478.72 | 0.0215091 | 5521.15ms | 124597 | 2560 | 272173 | 47938.1 | 0.265811 | 2.04883 | 9.80569 | 1.85829 | 0.00507236 | 7.73431e-06 | 4.56472e-06 | 1(Win) | true |
| simdjson (ondemand) | 2109.09 | 0.0390374 | 6351.33ms | 124597 | 640 | 309577 | 56339.5 | 0.119736 | 2.40647 | 10.1071 | 1.86408 | 0.0067609 | 8.85354e-06 | 5.45509e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3028.33 | 0.0241732 | 5154.45ms | 124597 | 2560 | 230312 | 39237.8 | 0.0197903 | 1.68228 | 8.40273 | 1.529 | 0.00406548 | 4.85628e-06 | 2.26668e-06 | 1(Win) | true |
| simdjson (ondemand) | 2453.92 | 0.0223028 | 6048.97ms | 124597 | 2560 | 298576 | 48422.5 | 0.00518978 | 2.07634 | 8.72503 | 1.54098 | 0.00646117 | 8.83473e-06 | 5.64319e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 807.213 | 0.0751384 | 7703.72ms | 2090234 | 160 | 5.5088e+08 | 2.46949e+06 | 0.227759 | 6.28899 | 30.4159 | 5.62526 | 0.022817 | 0.103605 | 0.000552262 | 1(Win) | true |
| Jsonifier (generic) | 781.212 | 0.124224 | 8027.28ms | 2090234 | 40 | 4.01904e+08 | 2.55168e+06 | 1.26786 | 6.47651 | 30.3131 | 6.22188 | 0.0269788 | 0.103639 | 0.00080961 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 951.617 | 0.0820693 | 7714.18ms | 2090234 | 80 | 2.36438e+08 | 2.09475e+06 | 0.279928 | 5.33094 | 25.0907 | 4.35762 | 0.0219478 | 0.0788239 | 0.000185679 | 1(Win) | true |
| Jsonifier (generic) | 916.141 | 0.112064 | 7969.87ms | 2090234 | 40 | 2.37827e+08 | 2.17587e+06 | 0.159036 | 5.51395 | 24.9876 | 4.95425 | 0.0260968 | 0.0785777 | 0.00121344 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1849.33 | 0.114515 | 8428.54ms | 5212421 | 80 | 7.57989e+08 | 2.68798e+06 | 0.823541 | 2.76212 | 13.0195 | 2.55373 | 0.0100345 | 0.0604931 | 0.000891723 | 1(Win) | true |
| simdjson (ondemand) | 1803.05 | 0.693221 | 8521.34ms | 5212421 | 80 | 2.92211e+10 | 2.75697e+06 | 0.0142745 | 2.80702 | 13.0109 | 2.29201 | 0.0102526 | 0.0606016 | 0.000332453 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2157.64 | 0.0828181 | 8444.24ms | 5212421 | 160 | 5.82494e+08 | 2.30388e+06 | 0.211994 | 2.36315 | 10.8792 | 2.0449 | 0.00958115 | 0.0505479 | 0.000307608 | 1(Win) | true |
| simdjson (ondemand) | 2121.19 | 0.671161 | 8476.31ms | 5212421 | 30 | 7.42158e+09 | 2.34348e+06 | 0.123247 | 2.39224 | 10.8695 | 1.78261 | 0.00988305 | 0.0506084 | 0.000231127 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 730.157 | 0.0644116 | 8486.82ms | 2090234 | 160 | 4.94773e+08 | 2.7301e+06 | 0.0637006 | 6.92072 | 33.1543 | 6.85438 | 0.0273143 | 0.156428 | 0.00131363 | 1(Win) | true |
| simdjson (ondemand) | 727.085 | 0.0834151 | 8511.26ms | 2090234 | 40 | 2.09203e+08 | 2.74163e+06 | 0.290187 | 6.95448 | 34.7293 | 6.58347 | 0.0230443 | 0.180226 | 0.00181534 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.689 | 0.128555 | 8460.71ms | 2090234 | 40 | 3.63836e+08 | 2.34604e+06 | 0.0554614 | 5.95589 | 27.8699 | 5.59548 | 0.0262562 | 0.130761 | 0.00137577 | 1(Win) | true |
| simdjson (ondemand) | 832.326 | 0.620363 | 8572.53ms | 2090234 | 80 | 1.76598e+10 | 2.39498e+06 | 0.107638 | 6.08524 | 29.4113 | 5.31785 | 0.0221291 | 0.154332 | 0.000843608 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1667.14 | 0.145479 | 9273.54ms | 5212421 | 160 | 3.01063e+09 | 2.98173e+06 | 0.0650539 | 3.04195 | 14.1457 | 2.80467 | 0.0100816 | 0.101531 | 0.00250477 | 1(Win) | true |
| simdjson (ondemand) | 1616.85 | 0.1226 | 9606.99ms | 5212421 | 80 | 1.13661e+09 | 3.07446e+06 | 0.00482093 | 3.12887 | 14.7176 | 2.67159 | 0.0103475 | 0.121139 | 0.00146305 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1914.5 | 0.155325 | 9244.7ms | 5212421 | 40 | 6.50596e+08 | 2.59647e+06 | 0.207406 | 2.63794 | 12.0336 | 2.3013 | 0.00968926 | 0.0911344 | 0.000691195 | 1(Win) | true |
| simdjson (ondemand) | 1845.01 | 0.233995 | 9602.46ms | 5212421 | 40 | 1.58985e+09 | 2.69427e+06 | 0.867509 | 2.74986 | 12.6013 | 2.16734 | 0.00997452 | 0.110913 | 0.00078571 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7599.91 | 0.044479 | 6918.18ms | 2090234 | 1280 | 1.74218e+07 | 262293 | 0.0581514 | 0.668476 | 3.18846 | 0.436419 | 0.00635833 | 0.0507149 | 5.77649e-06 | 1(Win) | true |
| simdjson (ondemand) | 7228.47 | 0.0615128 | 7257.48ms | 2090234 | 1280 | 3.68331e+07 | 275771 | 0.105561 | 0.703271 | 3.66628 | 0.418407 | 0.00285604 | 0.0508811 | 1.52159e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7587.25 | 0.138581 | 6904.88ms | 2090234 | 80 | 1.06052e+07 | 262731 | 0.0460712 | 0.668257 | 3.18839 | 0.436402 | 0.0063996 | 0.0506512 | 3.80938e-06 | 1(Win) | true |
| simdjson (ondemand) | 7248.36 | 0.11431 | 7247.68ms | 2090234 | 160 | 1.58124e+07 | 275014 | 0.00662737 | 0.704394 | 3.6662 | 0.41839 | 0.00285939 | 0.050828 | 2.81069e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11198.1 | 0.120117 | 5718.76ms | 5212421 | 160 | 4.54903e+07 | 443909 | 0.165996 | 0.450988 | 1.95455 | 0.198819 | 0.00219854 | 0.0393934 | 5.50008e-06 | 1(Win) | true |
| simdjson (ondemand) | 9546.31 | 0.0620958 | 6804.96ms | 5212421 | 320 | 3.34567e+07 | 520720 | 0.218791 | 0.532822 | 2.27766 | 0.202787 | 0.00216113 | 0.0394183 | 5.28425e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11296.1 | 0.0556172 | 5724.61ms | 5212421 | 320 | 1.91687e+07 | 440060 | 0.0880505 | 0.44908 | 1.95452 | 0.198812 | 0.00212077 | 0.0393833 | 2.53541e-06 | 1(Win) | true |
| simdjson (ondemand) | 9577.12 | 0.0988729 | 6706.4ms | 5212421 | 160 | 4.2139e+07 | 519045 | 0.116294 | 0.52812 | 2.27763 | 0.20278 | 0.00214933 | 0.039457 | 5.50848e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5767.99 | 0.673687 | 9103.62ms | 2090234 | 160 | 8.67318e+08 | 345598 | 0.456405 | 0.883476 | 4.62832 | 0.756385 | 0.00630445 | 0.0760168 | 4.12334e-06 | 1(Win) | true |
| simdjson (ondemand) | 5420.82 | 0.117777 | 9577.88ms | 2090234 | 640 | 1.20049e+08 | 367731 | 0.0560091 | 0.931422 | 5.10597 | 0.73834 | 0.00285008 | 0.0753796 | 5.24089e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5742.22 | 0.198229 | 9068.35ms | 2090234 | 1280 | 6.0614e+08 | 347148 | 0.221855 | 0.882874 | 4.62825 | 0.756367 | 0.00635327 | 0.0759467 | 3.51075e-06 | 1(Win) | true |
| simdjson (ondemand) | 5428.2 | 0.0488206 | 9686.59ms | 2090234 | 640 | 2.05714e+07 | 367231 | 0.207604 | 0.92784 | 5.10589 | 0.738322 | 0.00287502 | 0.0753171 | 2.96842e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8713.83 | 0.167163 | 7321.57ms | 5212421 | 40 | 3.6375e+07 | 570467 | 0.0638878 | 0.576445 | 2.53192 | 0.327124 | 0.00226194 | 0.0590773 | 4.11997e-06 | 1(Win) | true |
| simdjson (ondemand) | 7688.59 | 0.349853 | 8366.05ms | 5212421 | 640 | 3.27444e+09 | 646536 | 0.0675951 | 0.663036 | 2.85499 | 0.331083 | 0.0021568 | 0.0590852 | 7.28009e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8880.33 | 0.168933 | 7354.07ms | 5212421 | 30 | 2.68271e+07 | 559771 | 0.0463976 | 0.57387 | 2.53189 | 0.327117 | 0.00214075 | 0.059059 | 2.26382e-06 | 1(Win) | true |
| simdjson (ondemand) | 7711.09 | 0.0940845 | 8392.17ms | 5212421 | 320 | 1.17715e+08 | 644650 | 0.191851 | 0.656774 | 2.85496 | 0.331076 | 0.00215076 | 0.059134 | 1.22826e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1409.01 | 0.149884 | 8884.23ms | 500299 | 320 | 8.24307e+07 | 338622 | 0.365323 | 3.5871 | 16.0981 | 3.00896 | 0.0157056 | 0.020669 | 0.000313712 | 1(Win) | true |
| simdjson (ondemand) | 1141.97 | 0.0763586 | 5419.92ms | 500299 | 160 | 1.62849e+07 | 417806 | 0.222385 | 4.40721 | 17.6965 | 3.05735 | 0.0236595 | 0.0285356 | 0.000125225 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1613.13 | 0.0960317 | 8655.92ms | 500299 | 160 | 1.29084e+07 | 295775 | 0.208692 | 3.14132 | 14.9927 | 2.73963 | 0.0108578 | 0.0155599 | 0.000237883 | 1(Win) | true |
| simdjson (ondemand) | 1285.39 | 0.0619757 | 5250.43ms | 500299 | 320 | 1.69348e+07 | 371187 | 0.0710532 | 3.90963 | 16.5796 | 2.78509 | 0.0173639 | 0.023734 | 5.8921e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2890.69 | 0.0533818 | 9922.65ms | 1151920 | 640 | 2.63394e+07 | 380032 | 0.0498772 | 1.74756 | 7.84234 | 1.34547 | 0.00747644 | 0.0366238 | 5.54563e-05 | 1(Win) | true |
| simdjson (ondemand) | 2410.18 | 0.154531 | 5891.22ms | 1151920 | 640 | 3.17511e+08 | 455799 | 0.11581 | 2.099 | 8.4507 | 1.36134 | 0.0106199 | 0.0360693 | 4.0834e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3302.09 | 0.060325 | 9606.44ms | 1151920 | 1280 | 5.1555e+07 | 332685 | 0.0660362 | 1.54037 | 7.35976 | 1.22816 | 0.00526904 | 0.0319592 | 2.88689e-05 | 1(Win) | true |
| simdjson (ondemand) | 2650.61 | 1.06288 | 5853.73ms | 1151920 | 80 | 1.55242e+09 | 414454 | 0.637467 | 1.91261 | 7.96665 | 1.24336 | 0.00824682 | 0.0311708 | 1.8697e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.681 | 0.0878707 | 8469.69ms | 500299 | 640 | 2.11862e+08 | 654776 | 0.0801823 | 6.99314 | 34.7986 | 7.24304 | 0.021171 | 0.0195459 | 0.000199097 | 1(Win) | true |
| simdjson (ondemand) | 419.426 | 0.209927 | 7272.32ms | 500299 | 80 | 4.56223e+08 | 1.13756e+06 | 0.311136 | 12.1421 | 63.4939 | 13.1108 | 0.0361094 | 0.0305774 | 0.000114856 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.745 | 0.0844423 | 8264.5ms | 500299 | 160 | 4.21738e+07 | 607997 | 0.0733549 | 6.49727 | 33.6561 | 6.96693 | 0.0155532 | 0.0149535 | 5.89522e-05 | 1(Win) | true |
| simdjson (ondemand) | 439.128 | 0.0606411 | 7159.19ms | 500299 | 320 | 1.38918e+08 | 1.08652e+06 | 0.228696 | 11.559 | 62.368 | 12.8379 | 0.0294825 | 0.021542 | 6.86027e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.47 | 0.071778 | 9249.46ms | 1151920 | 160 | 4.28628e+07 | 721089 | 0.0341866 | 3.32434 | 16.019 | 3.22027 | 0.0096591 | 0.0370448 | 6.96392e-05 | 1(Win) | true |
| simdjson (ondemand) | 925.642 | 0.2515 | 7556.82ms | 1151920 | 30 | 2.67272e+08 | 1.1868e+06 | 0.308124 | 5.50007 | 28.3063 | 5.71958 | 0.0153684 | 0.0897812 | 0.000714315 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1629.42 | 0.117257 | 9139.06ms | 1151920 | 80 | 4.99973e+07 | 674202 | 0.143153 | 3.11949 | 15.5241 | 3.10073 | 0.00732679 | 0.0324013 | 2.87346e-05 | 1(Win) | true |
| simdjson (ondemand) | 972.749 | 0.12677 | 7431.09ms | 1151920 | 40 | 8.19856e+07 | 1.12933e+06 | 0.113399 | 5.22663 | 27.8167 | 5.60092 | 0.0126832 | 0.0802253 | 0.000124792 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5437.72 | 0.0257273 | 9487.89ms | 500299 | 2560 | 1.30453e+06 | 87743 | 0.0464694 | 0.933957 | 4.95866 | 0.768281 | 0.000964696 | 1.40822e-05 | 1.10044e-05 | 1(Win) | true |
| simdjson (ondemand) | 4870.08 | 0.0292386 | 5387.99ms | 500299 | 1280 | 1.05029e+06 | 97970.1 | 0.000770319 | 1.04629 | 5.63921 | 0.726658 | 0.00109727 | 4.97999e-05 | 4.72842e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5563.41 | 0.0685237 | 9421.79ms | 500299 | 160 | 552560 | 85760.8 | 0.0952098 | 0.925476 | 4.93347 | 0.762054 | 0.000935253 | 2.33236e-05 | 2.16745e-05 | 1(Win) | true |
| simdjson (ondemand) | 4986.06 | 0.10669 | 5361.14ms | 500299 | 80 | 833834 | 95691.3 | 0.0394392 | 1.02596 | 5.6139 | 0.720413 | 0.0010403 | 1.47412e-05 | 8.24507e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9121.08 | 0.0614082 | 6552.93ms | 1151920 | 1280 | 7.00189e+06 | 120441 | 0.0821819 | 0.557856 | 2.86119 | 0.358334 | 0.000718729 | 0.00411291 | 1.32706e-05 | 1(Win) | true |
| simdjson (ondemand) | 7952.73 | 0.500114 | 7416.03ms | 1151920 | 2560 | 1.22177e+09 | 138136 | 0.610239 | 0.64207 | 3.21265 | 0.348681 | 0.000985982 | 0.0113226 | 6.15989e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9202.8 | 0.150338 | 6583.3ms | 1151920 | 320 | 1.03061e+07 | 119372 | 0.145686 | 0.558135 | 2.85025 | 0.35563 | 0.000748438 | 0.00383821 | 2.39736e-05 | 1(Win) | true |
| simdjson (ondemand) | 8150.29 | 0.0210573 | 7328.92ms | 1151920 | 2560 | 2.06227e+06 | 134787 | 0.10343 | 0.624026 | 3.20165 | 0.345969 | 0.000955094 | 0.0110769 | 6.84964e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3074.01 | 0.0783458 | 8230.5ms | 500299 | 80 | 1.18296e+06 | 155212 | 0.0561096 | 1.64585 | 9.39647 | 1.8077 | 0.00190606 | 4.03509e-05 | 3.50041e-05 | 1(Win) | true |
| simdjson (ondemand) | 2885.99 | 0.0942469 | 8933.08ms | 500299 | 30 | 728324 | 165324 | 0.0112494 | 1.78379 | 10.1904 | 1.73301 | 0.00248678 | 0.000102339 | 4.13086e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3116.45 | 0.0251049 | 8216.49ms | 500299 | 2560 | 3.78177e+06 | 153098 | 0.128472 | 1.64474 | 9.37127 | 1.80146 | 0.00192856 | 1.87333e-05 | 1.42501e-05 | 1(Win) | true |
| simdjson (ondemand) | 2853.46 | 0.119173 | 8905.81ms | 500299 | 160 | 6.35322e+06 | 167208 | 0.0568166 | 1.77723 | 10.1651 | 1.72677 | 0.00238868 | 8.73103e-05 | 7.09576e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5788.8 | 0.211374 | 5071.86ms | 1151920 | 640 | 1.02979e+08 | 189773 | 0.339852 | 0.881606 | 4.79747 | 0.812939 | 0.00122002 | 0.00405208 | 6.40235e-06 | 1(Win) | true |
| simdjson (ondemand) | 5369.6 | 0.113295 | 5487.43ms | 1151920 | 80 | 4.29807e+06 | 204588 | 0.219917 | 0.947407 | 5.18929 | 0.785758 | 0.00162849 | 0.0117797 | 5.6102e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5744.84 | 0.333897 | 5034.07ms | 1151920 | 30 | 1.22302e+07 | 191225 | 0.211699 | 0.879538 | 4.78653 | 0.810227 | 0.0012465 | 0.00378441 | 1.59155e-06 | 1(Win) | true |
| simdjson (ondemand) | 5409.45 | 0.120594 | 5512.66ms | 1151920 | 80 | 4.79823e+06 | 203081 | 1.04742 | 0.944287 | 5.1783 | 0.783046 | 0.00160319 | 0.0113588 | 9.54927e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1653.24 | 0.104197 | 4014.01ms | 56369 | 2560 | 2.93874e+06 | 32516.6 | 0.172617 | 3.10918 | 13.3828 | 2.65095 | 0.0055054 | 6.55973e-05 | 4.86194e-05 | 1(Win) | true |
| simdjson (ondemand) | 1299.39 | 0.0512555 | 4896.14ms | 56369 | 1280 | 575565 | 41371.6 | 0.349089 | 3.92575 | 15.8049 | 2.81499 | 0.00953278 | 3.36095e-05 | 2.00409e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2080.27 | 0.019895 | 3654.4ms | 56369 | 4890 | 129253 | 25841.7 | 0.0900919 | 2.44785 | 11.1914 | 2.17196 | 0.00409408 | 1.17361e-05 | 3.88544e-06 | 1(Win) | true |
| simdjson (ondemand) | 1524.3 | 0.0268715 | 4628.59ms | 56369 | 4890 | 439170 | 35267.1 | 0.187963 | 3.35 | 13.6843 | 2.35276 | 0.00980401 | 1.76024e-05 | 9.35989e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2167.63 | 0.0864471 | 4479.54ms | 83958 | 40 | 40786.4 | 36938.3 | 0.128068 | 2.37841 | 10.2549 | 1.92422 | 0.00465352 | 3.27545e-05 | 2.02482e-05 | 1(Win) | true |
| simdjson (ondemand) | 1840.58 | 0.0504584 | 5093.95ms | 83958 | 1280 | 616726 | 43501.9 | 0.112852 | 2.76243 | 11.0768 | 1.909 | 0.0076392 | 2.30863e-05 | 1.28319e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2662.63 | 0.041037 | 4091.73ms | 83958 | 2560 | 389848 | 30071.3 | 0.0525708 | 1.90777 | 8.77832 | 1.60068 | 0.00324188 | 2.18859e-05 | 1.02637e-05 | 1(Win) | true |
| simdjson (ondemand) | 2114.38 | 0.0629723 | 4858.17ms | 83958 | 320 | 181973 | 37868.6 | 0.0161935 | 2.39558 | 9.65718 | 1.60044 | 0.0085701 | 6.9231e-06 | 2.90324e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 702.132 | 0.142923 | 8412.27ms | 56369 | 80 | 957936 | 76563.5 | 0.0487905 | 7.19967 | 34.0652 | 7.07589 | 0.0110752 | 1.64097e-05 | 8.20486e-06 | 1(Win) | true |
| simdjson (ondemand) | 194.64 | 0.125867 | 7257.5ms | 56369 | 640 | 7.73435e+07 | 276190 | 0.0489397 | 26.2383 | 132.888 | 28.2674 | 0.0365067 | 0.000293324 | 0.000205842 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 778.674 | 0.030597 | 7995.02ms | 56369 | 2560 | 1.14227e+06 | 69037.5 | 0.246786 | 6.51102 | 31.8698 | 6.59187 | 0.00978025 | 4.22578e-05 | 2.78577e-05 | 1(Win) | true |
| simdjson (ondemand) | 199.8 | 0.0527752 | 7172.76ms | 56369 | 640 | 1.29042e+07 | 269058 | 0.0452988 | 25.4525 | 130.771 | 27.8026 | 0.033659 | 6.6221e-05 | 4.01096e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 930.677 | 0.0378082 | 9349.87ms | 83958 | 1280 | 1.35428e+06 | 86032.7 | 0.141341 | 5.46277 | 24.1563 | 5.06228 | 0.00723369 | 7.53818e-05 | 5.8437e-05 | 1(Win) | true |
| simdjson (ondemand) | 285.91 | 0.117471 | 7319.62ms | 83958 | 640 | 6.92636e+07 | 280048 | 0.0446169 | 17.6753 | 89.3846 | 18.9348 | 0.0235121 | 0.000139095 | 8.61294e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1013.99 | 0.0234873 | 9002.43ms | 83958 | 2560 | 880564 | 78963.8 | 0.0681133 | 5.01051 | 22.6829 | 4.73781 | 0.0064565 | 3.46807e-05 | 2.38354e-05 | 1(Win) | true |
| simdjson (ondemand) | 294.128 | 0.0694106 | 7254.92ms | 83958 | 320 | 1.14249e+07 | 272223 | 0.0171154 | 17.1819 | 87.954 | 18.6212 | 0.021166 | 9.82262e-05 | 8.02485e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2448.16 | 0.0399373 | 2972.43ms | 56369 | 4890 | 376068 | 21958.4 | 0.181449 | 2.07543 | 9.5231 | 1.70865 | 0.00529561 | 2.35049e-05 | 1.46928e-05 | 1(Win) | true |
| simdjson (ondemand) | 2104.81 | 0.0918451 | 3304.11ms | 56369 | 1280 | 704334 | 25540.4 | 0.148846 | 2.40948 | 10.0999 | 1.68715 | 0.0052921 | 8.349e-05 | 6.34768e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3138.06 | 0.0814242 | 2795.51ms | 56369 | 1280 | 249044 | 17130.9 | 0.206736 | 1.62524 | 7.91268 | 1.35635 | 0.00363597 | 2.04151e-05 | 1.39011e-05 | 1(Win) | true |
| simdjson (ondemand) | 2574.33 | 0.0825183 | 3111.42ms | 56369 | 2560 | 760138 | 20882.2 | 0.208628 | 1.96645 | 8.55036 | 1.35106 | 0.0034463 | 9.68229e-05 | 7.7773e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3569.44 | 0.128081 | 2992.32ms | 83958 | 4890 | 4.03651e+06 | 22431.7 | 0.0323716 | 1.4222 | 6.92909 | 1.17095 | 0.00202545 | 2.80596e-05 | 1.74228e-05 | 1(Win) | true |
| simdjson (ondemand) | 3024.3 | 0.0476656 | 3417.42ms | 83958 | 2560 | 407687 | 26475.1 | 0.185414 | 1.68404 | 7.25226 | 1.1534 | 0.00284889 | 3.54623e-05 | 2.69899e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4397.23 | 0.21644 | 2849.42ms | 83958 | 320 | 497041 | 18208.9 | 0.05756 | 1.15409 | 5.84552 | 0.934324 | 0.00184512 | 1.46278e-05 | 9.97523e-06 | 1(Win) | true |
| simdjson (ondemand) | 3622.23 | 0.0423656 | 3218.73ms | 83958 | 640 | 56128 | 22104.8 | 0.0681231 | 1.40075 | 6.20491 | 0.926011 | 0.00213302 | 1.33809e-05 | 8.82137e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1877.11 | 0.0283255 | 3595.42ms | 56369 | 2560 | 168461 | 28638.6 | 0.224455 | 2.7133 | 12.9149 | 2.46606 | 0.00371242 | 0.000119061 | 9.46331e-05 | 1(Win) | true |
| simdjson (ondemand) | 1355.88 | 0.0312959 | 4710.03ms | 56369 | 1280 | 197072 | 39647.9 | 0.00250059 | 3.76311 | 16.5755 | 2.96884 | 0.010824 | 1.02838e-05 | 4.39348e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2222.09 | 0.132291 | 3435.08ms | 56369 | 80 | 81941.7 | 24192.3 | 0.0465323 | 2.27585 | 11.2854 | 2.11077 | 0.00309745 | 2.04013e-05 | 1.37487e-05 | 1(Win) | true |
| simdjson (ondemand) | 1515.8 | 0.0172142 | 4568.35ms | 56369 | 4890 | 182256 | 35464.9 | 0.081451 | 3.3769 | 15.0507 | 2.63772 | 0.0103514 | 3.57308e-05 | 2.58231e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2730.09 | 0.0486269 | 3682.11ms | 83958 | 4890 | 994561 | 29328.2 | 0.0748548 | 1.8774 | 9.24078 | 1.69763 | 0.00280979 | 5.96632e-05 | 4.3412e-05 | 1(Win) | true |
| simdjson (ondemand) | 1964 | 0.0641102 | 4821.97ms | 83958 | 1280 | 874393 | 40768.1 | 0.0377106 | 2.59352 | 11.4716 | 1.98512 | 0.00702656 | 1.93828e-05 | 9.82634e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3238.76 | 0.0700766 | 3524ms | 83958 | 2560 | 768336 | 24722 | 0.188161 | 1.5797 | 8.15817 | 1.46156 | 0.0020998 | 6.0298e-06 | 1.99598e-06 | 1(Win) | true |
| simdjson (ondemand) | 2199.81 | 0.0179029 | 4665.07ms | 83958 | 4890 | 207639 | 36398 | 0.230877 | 2.31767 | 10.4535 | 1.76438 | 0.00669623 | 1.298e-05 | 7.57025e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1335.04 | 0.0264314 | 4563.83ms | 53331 | 4890 | 495817 | 38096.5 | 0.0902303 | 3.81862 | 13.3854 | 2.60854 | 0.0120944 | 0.000157077 | 0.000116708 | 1(Win) | true |
| simdjson (ondemand) | 1027.44 | 0.0391556 | 5681.27ms | 53331 | 2560 | 961787 | 49502.3 | 0.130778 | 4.95474 | 17.7272 | 3.48605 | 0.0201827 | 0.00013401 | 9.32267e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1656.58 | 0.0600943 | 4336.85ms | 53331 | 640 | 217861 | 30702 | 0.420237 | 3.06269 | 11.1982 | 2.1112 | 0.00957417 | 6.41337e-05 | 4.75509e-05 | 1(Win) | true |
| simdjson (ondemand) | 1230.45 | 0.0787961 | 5423.72ms | 53331 | 4890 | 5.18738e+06 | 41334.7 | 0.1196 | 4.14782 | 15.5931 | 3.00155 | 0.0166892 | 7.16903e-05 | 4.69576e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1526.83 | 0.0326269 | 4822.01ms | 65103 | 2560 | 450623 | 40664 | 0.182229 | 3.3317 | 11.6034 | 2.21568 | 0.0104468 | 5.12469e-05 | 3.08166e-05 | 1(Win) | true |
| simdjson (ondemand) | 1246.24 | 0.068174 | 5744.13ms | 65103 | 640 | 738271 | 49819.4 | 0.0647255 | 4.09463 | 14.7462 | 2.85737 | 0.0169069 | 6.95772e-05 | 4.48328e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1913.11 | 0.136292 | 4564.36ms | 65103 | 80 | 156515 | 32453.5 | 0.133136 | 2.69415 | 9.81215 | 1.80822 | 0.00820988 | 3.43686e-05 | 2.41924e-05 | 1(Win) | true |
| simdjson (ondemand) | 1486.44 | 0.25963 | 5503.89ms | 65103 | 30 | 352809 | 41769 | 0.00422943 | 3.46671 | 12.9965 | 2.46098 | 0.0144627 | 9.62577e-05 | 7.83374e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 967.422 | 0.0415538 | 6026.23ms | 53331 | 1280 | 610884 | 52573.1 | 0.1305 | 5.27536 | 19.2573 | 3.79366 | 0.0169979 | 0.00010269 | 6.48368e-05 | 1(Win) | true |
| simdjson (ondemand) | 475.37 | 0.0844538 | 5882.51ms | 53331 | 640 | 5.22533e+06 | 106991 | 0.0471494 | 10.7351 | 36.9571 | 7.48217 | 0.0721766 | 0.000141774 | 9.4633e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1140.82 | 0.0942969 | 5777.08ms | 53331 | 320 | 565546 | 44582.2 | 0.0192869 | 4.47231 | 16.9978 | 3.2803 | 0.0140765 | 2.20322e-05 | 1.2774e-05 | 1(Win) | true |
| simdjson (ondemand) | 518.934 | 0.0627009 | 5721.65ms | 53331 | 1280 | 4.83384e+06 | 98009.3 | 0.0100032 | 9.78986 | 34.7504 | 6.98331 | 0.064878 | 0.000103217 | 7.47103e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1109.03 | 0.0862698 | 6354.06ms | 65103 | 640 | 1.49284e+06 | 55983.2 | 0.0858638 | 4.61694 | 16.5847 | 3.26492 | 0.0144975 | 0.000364567 | 0.000282437 | 1(Win) | true |
| simdjson (ondemand) | 599.732 | 0.104675 | 5701.37ms | 65103 | 320 | 3.75774e+06 | 103525 | 0.122743 | 8.53434 | 30.2036 | 6.06528 | 0.0529291 | 6.24491e-05 | 3.68647e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1300.31 | 0.0505941 | 6100.54ms | 65103 | 1280 | 746998 | 47747.9 | 0.00343753 | 3.90957 | 14.7429 | 2.84803 | 0.011774 | 1.98004e-05 | 1.02602e-05 | 1(Win) | true |
| simdjson (ondemand) | 647.007 | 0.104626 | 5575.6ms | 65103 | 320 | 3.2256e+06 | 95960.4 | 0.0100703 | 7.84683 | 28.3947 | 5.65665 | 0.0497105 | 3.12486e-05 | 1.91043e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8778.52 | 0.0422905 | 1310.86ms | 53331 | 2560 | 15368.9 | 5793.73 | 0.090184 | 0.586965 | 2.7349 | 0.380248 | 0.000613628 | 4.86349e-06 | 1.45026e-06 | 1(Win) | true |
| simdjson (ondemand) | 6678.67 | 0.0387832 | 1500.43ms | 53331 | 640 | 5582.74 | 7615.35 | 0.0618788 | 0.775097 | 3.396 | 0.4212 | 0.000866757 | 3.98455e-06 | 1.14263e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9354.18 | 0.0531747 | 1304.54ms | 53331 | 1280 | 10699.6 | 5437.18 | 0.322044 | 0.551709 | 2.58246 | 0.344509 | 0.000635916 | 1.04155e-05 | 6.34305e-06 | 1(Win) | true |
| simdjson (ondemand) | 7057.97 | 0.0729571 | 1477.06ms | 53331 | 30 | 829.197 | 7206.1 | 0.000462573 | 0.73406 | 3.24637 | 0.386173 | 0.000851287 | 6.25027e-06 | 0 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9038.17 | 0.026186 | 1421.07ms | 65103 | 4890 | 15823 | 6869.43 | 0.00853674 | 0.566963 | 2.66803 | 0.335008 | 0.000545645 | 6.02789e-06 | 2.86788e-06 | 1(Win) | true |
| simdjson (ondemand) | 7533.66 | 0.0266854 | 1557.65ms | 65103 | 2560 | 12381.6 | 8241.29 | 0.744965 | 0.682126 | 3.04874 | 0.356451 | 0.000727015 | 3.79207e-06 | 1.14002e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9539.82 | 0.038887 | 1398.2ms | 65103 | 2560 | 16397.3 | 6508.2 | 0.0657476 | 0.539286 | 2.54236 | 0.30567 | 0.000620639 | 3.59406e-06 | 6.24011e-07 | 1(Win) | true |
| simdjson (ondemand) | 7985.63 | 0.0398948 | 1530.75ms | 65103 | 80 | 769.673 | 7774.85 | 0.218177 | 0.648589 | 2.92646 | 0.327804 | 0.000695436 | 4.03207e-06 | 1.15202e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6100.62 | 0.0282678 | 1568.01ms | 53331 | 2560 | 14217.9 | 8336.92 | 0.0903902 | 0.845516 | 4.13679 | 0.69108 | 0.00173336 | 4.56319e-06 | 1.73592e-06 | 1(Win) | true |
| simdjson (ondemand) | 4102.39 | 0.0205399 | 1981.24ms | 53331 | 4890 | 31709.6 | 12397.7 | 0.125844 | 1.25501 | 5.85733 | 0.957173 | 0.00232619 | 1.04874e-05 | 5.7863e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6388.56 | 0.107375 | 1549.38ms | 53331 | 30 | 2192.21 | 7961.17 | 0.0284796 | 0.81068 | 3.9835 | 0.655379 | 0.00168757 | 1.12505e-05 | 5.00022e-06 | 1(Win) | true |
| simdjson (ondemand) | 4245.29 | 0.0265679 | 1951.76ms | 53331 | 2560 | 25935.7 | 11980.4 | 0.235006 | 1.21159 | 5.70769 | 0.922147 | 0.00232495 | 4.84884e-06 | 9.96137e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6540.58 | 0.0761453 | 1686.47ms | 65103 | 160 | 8359.43 | 9492.59 | 0.0152115 | 0.790622 | 3.76803 | 0.585396 | 0.00132674 | 5.18409e-06 | 2.11204e-06 | 1(Win) | true |
| simdjson (ondemand) | 4657.56 | 0.0386565 | 2061.66ms | 65103 | 1280 | 33989 | 13330.4 | 0.047449 | 1.09119 | 5.06315 | 0.79491 | 0.00205676 | 1.52403e-05 | 8.95216e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6722.36 | 0.0505808 | 1665.82ms | 65103 | 30 | 654.714 | 9235.9 | 0.081139 | 0.755724 | 3.64441 | 0.556533 | 0.00126876 | 1.28002e-05 | 1.07522e-05 | 1(Win) | true |
| simdjson (ondemand) | 4922.07 | 0.0738172 | 2026.35ms | 65103 | 40 | 3468.02 | 12614 | 0.0737157 | 1.05014 | 4.94086 | 0.766263 | 0.0020122 | 1.49763e-05 | 1.22882e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1468.35 | 0.0716173 | 1505.03ms | 11812 | 320 | 9659.92 | 7671.74 | 0.195385 | 3.52466 | 16.866 | 3.2144 | 0.00455152 | 1.34926e-05 | 2.64561e-06 | 1(Win) | true |
| simdjson (ondemand) | 1089.27 | 0.0877506 | 1766.56ms | 11812 | 80 | 6588.23 | 10341.6 | 0.578385 | 4.66901 | 19.215 | 3.59736 | 0.0095422 | 2.85726e-05 | 1.37572e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1584.38 | 0.137068 | 1481.39ms | 11812 | 40 | 3798.91 | 7109.9 | 0.0281377 | 3.21058 | 15.7365 | 2.95733 | 0.00421817 | 1.69319e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1182.83 | 0.0847522 | 1745.33ms | 11812 | 30 | 1954.46 | 9523.6 | 0.0584171 | 4.37439 | 18.2208 | 3.37072 | 0.00828818 | 2.82199e-05 | 1.69319e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2822.02 | 0.0810759 | 1595.26ms | 25388 | 1280 | 61934.2 | 8579.63 | 0.106333 | 1.83201 | 8.79355 | 1.56113 | 0.0019081 | 2.47718e-05 | 1.26782e-05 | 1(Win) | true |
| simdjson (ondemand) | 2250.07 | 0.0360945 | 1819.42ms | 25388 | 4890 | 73765.9 | 10760.5 | 0.104306 | 2.28242 | 9.62222 | 1.69787 | 0.00364382 | 3.07779e-05 | 1.85183e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3045.18 | 0.0548448 | 1586.88ms | 25388 | 1280 | 24339.6 | 7950.89 | 0.00780119 | 1.69032 | 8.33796 | 1.45592 | 0.001675 | 1.87404e-05 | 8.43164e-06 | 1(Win) | true |
| simdjson (ondemand) | 2413.78 | 0.0938749 | 1802.98ms | 25388 | 40 | 3546.68 | 10030.7 | 0.0821488 | 2.14312 | 9.13802 | 1.58835 | 0.00358043 | 2.26485e-05 | 3.93887e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 840.393 | 0.106385 | 2082.6ms | 11812 | 30 | 6100.44 | 13404.2 | 0.167577 | 6.14835 | 28.6371 | 5.80084 | 0.0143329 | 6.49057e-05 | 3.38639e-05 | 1(Win) | true |
| simdjson (ondemand) | 725.213 | 0.0644094 | 2296.57ms | 11812 | 320 | 32030.5 | 15533.1 | 0.0976289 | 7.11643 | 31.4302 | 6.1374 | 0.0142974 | 2.91018e-05 | 1.0847e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 874.58 | 0.0412768 | 2065.68ms | 11812 | 1280 | 36180.1 | 12880.2 | 0.0807817 | 5.81693 | 27.6068 | 5.56443 | 0.0142223 | 4.02133e-05 | 1.96437e-05 | 1(Win) | true |
| simdjson (ondemand) | 751.592 | 0.0362129 | 2301.99ms | 11812 | 4890 | 144051 | 14987.9 | 0.00660685 | 6.792 | 30.4015 | 5.90442 | 0.0140822 | 5.72881e-05 | 3.07476e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1655.23 | 0.0419016 | 2220.79ms | 25388 | 4890 | 183701 | 14627.5 | 0.0132644 | 3.0751 | 14.2762 | 2.78202 | 0.00658798 | 3.34522e-05 | 1.87197e-05 | 1(Win) | true |
| simdjson (ondemand) | 1498.49 | 0.0452903 | 2361.37ms | 25388 | 2560 | 137088 | 16157.5 | 0.0437298 | 3.39843 | 15.1852 | 2.8545 | 0.00737476 | 3.97733e-05 | 2.44333e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1752.9 | 0.142799 | 2194.54ms | 25388 | 320 | 124493 | 13812.5 | 0.0466282 | 2.91562 | 13.7775 | 2.66772 | 0.00645507 | 5.34209e-05 | 3.23726e-05 | 1(Win) | true |
| simdjson (ondemand) | 1577.8 | 0.0841556 | 2356.21ms | 25388 | 320 | 53366.8 | 15345.4 | 0.0288481 | 3.27149 | 14.7003 | 2.74484 | 0.00726487 | 1.40322e-05 | 5.66212e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2770.17 | 0.0765061 | 1153.44ms | 11812 | 4890 | 47330 | 4066.47 | 0.167261 | 1.86197 | 9.12834 | 1.62657 | 0.00181347 | 2.94837e-05 | 1.29846e-05 | 1(Win) | true |
| simdjson (ondemand) | 2058.03 | 0.159681 | 1299.18ms | 11812 | 160 | 12222.7 | 5473.58 | 0.0707304 | 2.48244 | 11.0704 | 1.86624 | 0.00334194 | 2.64561e-05 | 3.17474e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2819.35 | 0.175392 | 1162.52ms | 11812 | 640 | 31430.5 | 3995.54 | 0.0307077 | 1.81766 | 8.94269 | 1.58136 | 0.00171105 | 4.06102e-05 | 1.91807e-05 | 1(Win) | true |
| simdjson (ondemand) | 2142.95 | 0.0952825 | 1279.65ms | 11812 | 1280 | 32111.3 | 5256.68 | 0.171147 | 2.39781 | 10.8839 | 1.82061 | 0.00273378 | 4.17346e-05 | 1.52784e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4686.79 | 0.0734655 | 1264.08ms | 25388 | 1280 | 18436.7 | 5165.99 | 0.268197 | 1.09334 | 5.36013 | 0.865527 | 0.00133712 | 1.73249e-05 | 9.8164e-06 | 1(Win) | true |
| simdjson (ondemand) | 3902.23 | 0.131901 | 1360.74ms | 25388 | 2560 | 171463 | 6204.63 | 0.269925 | 1.31217 | 5.86175 | 0.89952 | 0.00199858 | 1.58324e-05 | 7.80081e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4863.04 | 0.0368566 | 1250.74ms | 25388 | 4890 | 16465.7 | 4978.76 | 0.209805 | 1.05752 | 5.27395 | 0.844494 | 0.00117907 | 1.49419e-05 | 6.09759e-06 | 1(Win) | true |
| simdjson (ondemand) | 3974.8 | 0.037392 | 1358.64ms | 25388 | 4890 | 25368.4 | 6091.34 | 0.187522 | 1.28537 | 5.77497 | 0.878289 | 0.00190657 | 1.94608e-05 | 9.64983e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.55 | 0.036858 | 1311.26ms | 11812 | 4890 | 21998.7 | 5754.55 | 0.137018 | 2.62267 | 12.9768 | 2.45386 | 0.00639894 | 2.47746e-05 | 8.39672e-06 | 1(Win) | true |
| simdjson (ondemand) | 1687.02 | 0.0532797 | 1394.2ms | 11812 | 640 | 8100.45 | 6677.32 | 0.0165232 | 3.06993 | 13.7276 | 2.38876 | 0.00682899 | 1.91807e-05 | 4.49754e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2040.08 | 0.0348814 | 1290.38ms | 11812 | 640 | 2374.22 | 5521.74 | 0.0923625 | 2.54451 | 12.795 | 2.40865 | 0.0057644 | 2.19586e-05 | 5.29123e-06 | 1(Win) | true |
| simdjson (ondemand) | 1737.4 | 0.0220269 | 1384.55ms | 11812 | 4890 | 9973.87 | 6483.71 | 0.0491375 | 2.97586 | 13.5196 | 2.33889 | 0.00619387 | 1.87671e-05 | 5.5401e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3513.09 | 0.0487137 | 1409.41ms | 25388 | 640 | 7213.73 | 6891.9 | 0.0643457 | 1.44903 | 6.91118 | 1.20935 | 0.00348842 | 7.81619e-06 | 1.96943e-06 | 1(Win) | true |
| simdjson (ondemand) | 3263.35 | 0.0967354 | 1469.12ms | 25388 | 30 | 1545.33 | 7419.33 | 0.00449297 | 1.58724 | 7.08803 | 1.14066 | 0.00370779 | 6.56478e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3626.8 | 0.0270425 | 1399.63ms | 25388 | 4890 | 15937.2 | 6675.83 | 0.0257665 | 1.41521 | 6.81578 | 1.18615 | 0.00326734 | 1.01009e-05 | 3.00449e-06 | 1(Win) | true |
| simdjson (ondemand) | 3338.79 | 0.0840864 | 1459.73ms | 25388 | 640 | 23796.4 | 7251.69 | 0.0142188 | 1.54476 | 7.00126 | 1.11943 | 0.00342934 | 5.29285e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1681.28 | 0.0374736 | 6900.52ms | 108313 | 1280 | 678489 | 61438.5 | 0.0645008 | 3.05246 | 13.0819 | 2.64407 | 0.00374537 | 1.59766e-05 | 1.02928e-05 | 1(Win) | true |
| simdjson (ondemand) | 1514.73 | 0.0982863 | 7547.17ms | 108313 | 640 | 2.87513e+06 | 68193.9 | 0.0880183 | 3.34522 | 15.1474 | 2.4544 | 0.00622774 | 3.69012e-05 | 1.98499e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.63 | 0.0576015 | 6633.02ms | 108313 | 640 | 691112 | 57049.3 | 0.159099 | 2.82542 | 12.3934 | 2.48232 | 0.00340348 | 6.67914e-06 | 2.06289e-06 | 1(Win) | true |
| simdjson (ondemand) | 1633.72 | 0.0619411 | 7248.86ms | 108313 | 1280 | 1.96324e+06 | 63227.1 | 0.0376107 | 3.11054 | 14.4579 | 2.29223 | 0.00615963 | 1.00259e-05 | 3.72907e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2532.73 | 0.0248659 | 7642.8ms | 183677 | 2560 | 757145 | 69161.7 | 0.104382 | 1.99982 | 8.46946 | 1.61146 | 0.00208498 | 2.15392e-05 | 1.59821e-05 | 1(Win) | true |
| simdjson (ondemand) | 2420.66 | 0.0679167 | 7960.38ms | 183677 | 640 | 1.54587e+06 | 72363.7 | 0.431304 | 2.09073 | 9.51058 | 1.46884 | 0.00415629 | 9.57864e-06 | 6.12488e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2694.79 | 0.0279058 | 7397.15ms | 183677 | 2560 | 842345 | 65002.5 | 0.0245784 | 1.88224 | 8.07297 | 1.5183 | 0.00190185 | 1.57588e-05 | 1.20647e-05 | 1(Win) | true |
| simdjson (ondemand) | 2584.2 | 0.0603117 | 7698.5ms | 183677 | 1280 | 2.1393e+06 | 67784.3 | 0.165544 | 1.96526 | 9.11225 | 1.37512 | 0.00377757 | 1.16713e-05 | 7.03936e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 656.68 | 0.0456131 | 8411.99ms | 108313 | 2560 | 1.31787e+07 | 157299 | 0.0466573 | 7.722 | 36.5094 | 7.23069 | 0.00984179 | 5.69386e-05 | 3.55199e-05 | 1(Win) | true |
| simdjson (ondemand) | 248.261 | 0.0602857 | 5386.96ms | 108313 | 320 | 2.01337e+07 | 416075 | 0.393631 | 20.5199 | 90.5351 | 18.4057 | 0.0874526 | 0.000117743 | 9.84127e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.452 | 0.0252221 | 8178.78ms | 108313 | 2560 | 3.69835e+06 | 150697 | 0.108197 | 7.42162 | 35.8273 | 7.07308 | 0.00931837 | 2.09354e-05 | 1.31383e-05 | 1(Win) | true |
| simdjson (ondemand) | 252.151 | 0.11441 | 5377.83ms | 108313 | 80 | 1.75735e+07 | 409657 | 0.0452734 | 20.2012 | 89.8618 | 18.2495 | 0.0845914 | 0.000100865 | 7.74376e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1008.31 | 0.0251426 | 9254.74ms | 183677 | 2560 | 4.88407e+06 | 173724 | 0.092416 | 5.04599 | 23.0713 | 4.54365 | 0.00534895 | 4.09112e-05 | 3.16559e-05 | 1(Win) | true |
| simdjson (ondemand) | 428.635 | 0.0526285 | 5304.14ms | 183677 | 320 | 1.48022e+07 | 408664 | 0.0899356 | 11.9275 | 53.2919 | 10.719 | 0.0489417 | 6.58765e-05 | 4.68213e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1049.33 | 0.128191 | 9052.05ms | 183677 | 80 | 3.66342e+06 | 166933 | 0.0265081 | 4.87296 | 22.6683 | 4.45055 | 0.00505806 | 0.000105688 | 8.28901e-05 | 1(Win) | true |
| simdjson (ondemand) | 432.533 | 0.10245 | 5252.26ms | 183677 | 80 | 1.37715e+07 | 404982 | 0.102501 | 11.7565 | 52.8927 | 10.6264 | 0.0479079 | 4.11048e-05 | 3.15772e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5342.08 | 0.0185975 | 2659.79ms | 108313 | 4890 | 63235.4 | 19336.2 | 0.025252 | 0.959853 | 5.24191 | 0.807493 | 0.000860097 | 5.11469e-06 | 2.76975e-06 | 1(Win) | true |
| simdjson (ondemand) | 4444.37 | 0.032177 | 3050.56ms | 108313 | 1280 | 71588.3 | 23241.8 | 0.182235 | 1.14291 | 5.90505 | 0.771025 | 0.00148517 | 2.87794e-06 | 8.29483e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5576.03 | 0.0382115 | 2596.85ms | 108313 | 1280 | 64137.1 | 18524.9 | 0.157315 | 0.917492 | 5.07929 | 0.763934 | 0.00070576 | 2.65434e-06 | 9.95379e-07 | 1(Win) | true |
| simdjson (ondemand) | 4665.75 | 0.0198529 | 2956.8ms | 108313 | 4890 | 94465.6 | 22139 | 0.0960923 | 1.0941 | 5.74251 | 0.727688 | 0.00137854 | 2.40536e-06 | 5.79627e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7578.77 | 0.0174209 | 3040.68ms | 183677 | 4890 | 79280.1 | 23113 | 0.056517 | 0.675179 | 3.67928 | 0.502186 | 0.000521385 | 3.81215e-06 | 2.29687e-06 | 1(Win) | true |
| simdjson (ondemand) | 6428.51 | 0.0232878 | 3455.54ms | 183677 | 2560 | 103083 | 27248.6 | 0.0879616 | 0.792784 | 4.06154 | 0.476619 | 0.00103628 | 1.95869e-06 | 6.27375e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7817.72 | 0.0188254 | 2974.29ms | 183677 | 4890 | 87005.9 | 22406.5 | 0.0784384 | 0.651181 | 3.5845 | 0.476717 | 0.000412896 | 1.51083e-06 | 4.56478e-07 | 1(Win) | true |
| simdjson (ondemand) | 6657.31 | 0.0174274 | 3381.22ms | 183677 | 4890 | 102822 | 26312.1 | 0.28594 | 0.768225 | 3.96569 | 0.451064 | 0.000983339 | 1.02329e-05 | 8.3157e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3404.74 | 0.0771395 | 3778.34ms | 108313 | 1280 | 701063 | 30338.7 | 0.197257 | 1.50138 | 7.79926 | 1.4324 | 0.000914068 | 4.0825e-06 | 1.55077e-06 | 1(Win) | true |
| simdjson (ondemand) | 2688.75 | 0.0428196 | 4603.86ms | 108313 | 30 | 8118.37 | 38417.7 | 0.029665 | 1.91821 | 9.89856 | 1.62164 | 0.00367638 | 1.8465e-06 | 9.2325e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3497.42 | 0.0395539 | 3679.93ms | 108313 | 4890 | 667350 | 29534.7 | 0.0538812 | 1.46155 | 7.63886 | 1.38934 | 0.000731254 | 3.88369e-06 | 1.75776e-06 | 1(Win) | true |
| simdjson (ondemand) | 2747.88 | 0.102455 | 4536.31ms | 108313 | 30 | 44499.7 | 37590.9 | 0.0965704 | 1.87533 | 9.73722 | 1.57858 | 0.0035142 | 3.38525e-06 | 1.53875e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5413.19 | 0.0197854 | 3964.73ms | 183677 | 4890 | 200447 | 32359.5 | 0.0266958 | 0.947949 | 5.20744 | 0.878831 | 0.000588292 | 3.5494e-06 | 1.91053e-06 | 1(Win) | true |
| simdjson (ondemand) | 4115.94 | 0.021476 | 4975.01ms | 183677 | 2560 | 213855 | 42558.4 | 0.000446994 | 1.23589 | 6.40472 | 0.975321 | 0.00217537 | 4.52561e-06 | 2.70303e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5542.24 | 0.0236293 | 3904.21ms | 183677 | 2560 | 142785 | 31606 | 0.0326389 | 0.924895 | 5.11288 | 0.853439 | 0.000454972 | 2.56905e-06 | 1.25475e-06 | 1(Win) | true |
| simdjson (ondemand) | 4223.81 | 0.0449216 | 4888.26ms | 183677 | 640 | 222121 | 41471.6 | 0.0561241 | 1.21016 | 6.30925 | 0.949798 | 0.00206305 | 3.74298e-06 | 2.33086e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 640.905 | 0.141207 | 8566.07ms | 1834197 | 40 | 5.94121e+08 | 2.72931e+06 | 0.162844 | 7.93695 | 32.4902 | 7.02838 | 0.0429098 | 0.138999 | 0.000265743 | 1(Win) | true |
| simdjson (ondemand) | 623.133 | 0.120791 | 8798.14ms | 1834197 | 80 | 9.19795e+08 | 2.80715e+06 | 0.368913 | 8.19389 | 34.2355 | 6.13444 | 0.0378378 | 0.139065 | 0.001186 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 691.886 | 0.112104 | 8545.95ms | 1834197 | 160 | 1.28525e+09 | 2.5282e+06 | 0.15168 | 7.36155 | 29.5043 | 6.33443 | 0.0417524 | 0.117997 | 0.00605714 | 1(Win) | true |
| simdjson (ondemand) | 669.335 | 0.0943911 | 8856.32ms | 1834197 | 160 | 9.73616e+08 | 2.61338e+06 | 0.111402 | 7.57544 | 31.2502 | 5.44056 | 0.0368703 | 0.11835 | 0.00688669 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2221.33 | 0.0794814 | 9818.85ms | 7351818 | 160 | 1.00696e+09 | 3.15632e+06 | 0.0288506 | 2.27279 | 9.2228 | 1.84807 | 0.0112263 | 0.0588003 | 0.00420996 | 1(Win) | true |
| simdjson (ondemand) | 2189.03 | 0.126261 | 9942.85ms | 7351818 | 160 | 2.61663e+09 | 3.20289e+06 | 0.450052 | 2.30972 | 9.55834 | 1.56872 | 0.00934716 | 0.0588531 | 0.00533748 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2403.63 | 0.24265 | 9817.23ms | 7351818 | 40 | 2.0039e+09 | 2.91694e+06 | 0.0765956 | 2.10703 | 8.47845 | 1.67508 | 0.0109162 | 0.0534961 | 0.00501425 | 1(Win) | true |
| simdjson (ondemand) | 2383.51 | 0.124368 | 9930.43ms | 7351818 | 80 | 1.07069e+09 | 2.94157e+06 | 0.147212 | 2.12668 | 8.81426 | 1.39578 | 0.00907 | 0.0536616 | 0.00549119 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 399.292 | 0.109057 | 6586.08ms | 1834197 | 80 | 1.82602e+09 | 4.38082e+06 | 0.291619 | 12.6893 | 59.4419 | 13.354 | 0.0438606 | 0.344027 | 0.0120285 | 1(Win) | true |
| simdjson (ondemand) | 272.403 | 0.164649 | 9655.78ms | 1834197 | 30 | 3.35358e+09 | 6.42148e+06 | 0.146963 | 18.5371 | 101.258 | 20.9693 | 0.041967 | 0.788779 | 0.0218274 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 421.615 | 0.222417 | 6619.5ms | 1834197 | 30 | 2.55456e+09 | 4.14887e+06 | 0.0225601 | 12.0426 | 56.4599 | 12.6609 | 0.042831 | 0.32269 | 0.0107458 | 1(Win) | true |
| simdjson (ondemand) | 284.922 | 0.0904808 | 9586.82ms | 1834197 | 80 | 2.46856e+09 | 6.13932e+06 | 0.132606 | 17.743 | 98.2756 | 20.2762 | 0.0408958 | 0.767476 | 0.00522582 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1364.62 | 0.295941 | 7892.6ms | 7351818 | 40 | 9.24773e+09 | 5.13787e+06 | 0.515548 | 3.73905 | 15.7134 | 3.38497 | 0.0115037 | 0.186228 | 0.00474981 | 1(Win) | true |
| simdjson (ondemand) | 922.236 | 0.22202 | 5382.55ms | 7351818 | 30 | 8.54697e+09 | 7.60243e+06 | 0.367149 | 5.51373 | 26.28 | 5.27001 | 0.0104686 | 0.435943 | 0.00671931 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1433.94 | 0.234334 | 7861.99ms | 7351818 | 40 | 5.25118e+09 | 4.88948e+06 | 0.495956 | 3.5353 | 14.97 | 3.21224 | 0.0111822 | 0.180903 | 0.00286236 | 1(Win) | true |
| simdjson (ondemand) | 944.497 | 0.532692 | 5592.07ms | 7351818 | 30 | 4.69096e+10 | 7.42325e+06 | 0.842218 | 5.3812 | 25.5363 | 5.09717 | 0.0101933 | 0.430577 | 0.00661506 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4467.38 | 0.132867 | 5083.36ms | 1834197 | 320 | 8.66106e+07 | 391555 | 0.0832171 | 1.13744 | 5.76948 | 0.914934 | 0.00579317 | 0.0755215 | 1.1335e-05 | 1(Win) | true |
| simdjson (ondemand) | 4350.73 | 0.107326 | 5216.29ms | 1834197 | 320 | 5.95843e+07 | 402054 | 0.0553359 | 1.16838 | 6.52918 | 0.874486 | 0.00334902 | 0.075429 | 7.61062e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4496.42 | 0.0712863 | 5067.82ms | 1834197 | 640 | 4.9221e+07 | 389026 | 0.153147 | 1.13485 | 5.76928 | 0.914887 | 0.00568679 | 0.0754833 | 1.30873e-05 | 1(Win) | true |
| simdjson (ondemand) | 4370.32 | 0.100148 | 5206.38ms | 1834197 | 160 | 2.57081e+07 | 400251 | 0.0513336 | 1.16334 | 6.52898 | 0.874439 | 0.00339968 | 0.0753867 | 3.85046e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9983.17 | 0.604465 | 8971.73ms | 7351818 | 30 | 5.40651e+08 | 702306 | 0.236891 | 0.512353 | 2.24539 | 0.257067 | 0.00192852 | 0.0423788 | 0.00022759 | 1(Win) | true |
| simdjson (ondemand) | 9393.98 | 0.157162 | 9780.78ms | 7351818 | 80 | 1.10072e+08 | 746355 | 0.257932 | 0.543813 | 2.64676 | 0.256657 | 0.00106452 | 0.0424151 | 1.50082e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10132.5 | 0.114053 | 8930.83ms | 7351818 | 320 | 1.99308e+08 | 691958 | 0.299053 | 0.50332 | 2.24534 | 0.257055 | 0.00192036 | 0.0423417 | 8.54125e-06 | 1(Win) | true |
| simdjson (ondemand) | 9006.01 | 0.272366 | 9853.73ms | 7351818 | 80 | 3.59683e+08 | 778507 | 0.924974 | 0.563671 | 2.64671 | 0.256645 | 0.00109324 | 0.0424066 | 0.000400663 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3134.31 | 0.215176 | 7179.34ms | 1834197 | 320 | 4.61474e+08 | 558090 | 0.226974 | 1.61711 | 8.57463 | 1.61618 | 0.0057344 | 0.113104 | 6.08747e-06 | 1(Win) | true |
| simdjson (ondemand) | 2456.84 | 0.0889832 | 9184.11ms | 1834197 | 640 | 2.56882e+08 | 711982 | 0.119864 | 2.06863 | 12.8396 | 2.27677 | 0.00336086 | 0.150434 | 4.69722e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3145.32 | 0.225909 | 7166.63ms | 1834197 | 320 | 5.05104e+08 | 556137 | 0.228455 | 1.62231 | 8.57443 | 1.61614 | 0.00583496 | 0.113065 | 4.76026e-06 | 1(Win) | true |
| simdjson (ondemand) | 2462.61 | 0.092316 | 9134.38ms | 1834197 | 640 | 2.75191e+08 | 710313 | 0.0200857 | 2.06864 | 12.8394 | 2.27673 | 0.00343741 | 0.150362 | 2.59906e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7745.57 | 0.141875 | 5761.17ms | 7351818 | 320 | 5.27773e+08 | 905194 | 0.0315388 | 0.661359 | 2.94525 | 0.432024 | 0.00200398 | 0.0635564 | 2.64348e-06 | 1(Win) | true |
| simdjson (ondemand) | 6052.69 | 0.332139 | 7355.17ms | 7351818 | 40 | 5.92094e+08 | 1.15837e+06 | 0.0580882 | 0.842523 | 4.22114 | 0.606512 | 0.0010852 | 0.0847961 | 2.56365e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7647.8 | 0.180826 | 5792.32ms | 7351818 | 160 | 4.39701e+08 | 916766 | 0.219158 | 0.662896 | 2.9452 | 0.432012 | 0.00202635 | 0.0635494 | 1.15065e-05 | 1(Win) | true |
| simdjson (ondemand) | 6073.05 | 0.340826 | 7325.67ms | 7351818 | 80 | 1.2386e+09 | 1.15448e+06 | 0.198339 | 0.838115 | 4.22108 | 0.6065 | 0.00105698 | 0.0847711 | 1.32518e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1389.12 | 0.114721 | 7383.57ms | 409725 | 640 | 6.6645e+07 | 281289 | 0.0507582 | 3.66498 | 17.0455 | 3.35093 | 0.00828847 | 0.0272856 | 4.22311e-05 | 1(Win) | true |
| simdjson (ondemand) | 1019 | 0.0988141 | 9971ms | 409725 | 640 | 9.18874e+07 | 383459 | 0.0660762 | 4.99044 | 19.9009 | 3.77083 | 0.0150898 | 0.0382456 | 0.000133844 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1752.76 | 0.118436 | 7011ms | 409725 | 320 | 2.23077e+07 | 222930 | 0.0489095 | 2.89331 | 14.1906 | 2.70506 | 0.00575057 | 0.0130806 | 1.15931e-05 | 1(Win) | true |
| simdjson (ondemand) | 1229.77 | 0.0445685 | 9453.75ms | 409725 | 1280 | 2.56687e+07 | 317737 | 0.113658 | 4.14654 | 17.047 | 3.12522 | 0.01137 | 0.019866 | 5.25333e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2118.91 | 0.195272 | 8001.16ms | 676745 | 40 | 1.41503e+07 | 304588 | 0.0814904 | 2.39744 | 11.0145 | 2.06235 | 0.00645871 | 0.0323424 | 6.40936e-05 | 1(Win) | true |
| simdjson (ondemand) | 1613.14 | 0.114705 | 5222.5ms | 676745 | 80 | 1.68485e+07 | 400086 | 0.221457 | 3.15935 | 12.6299 | 2.30868 | 0.0107617 | 0.0353691 | 2.6875e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2634.87 | 0.193558 | 7584.68ms | 676745 | 640 | 1.43859e+08 | 244944 | 0.0806198 | 1.92938 | 9.28253 | 1.67059 | 0.00447974 | 0.0189032 | 8.23104e-05 | 1(Win) | true |
| simdjson (ondemand) | 1880.95 | 0.0812406 | 10056.2ms | 676745 | 1280 | 9.94604e+07 | 343121 | 0.185867 | 2.69767 | 10.9022 | 1.91788 | 0.00864343 | 0.0225988 | 6.13749e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 844.967 | 0.0777125 | 5960.81ms | 409725 | 320 | 4.13273e+07 | 462437 | 0.0112395 | 5.99771 | 27.9949 | 5.60035 | 0.0147281 | 0.0264309 | 0.000215724 | 1(Win) | true |
| simdjson (ondemand) | 454.177 | 0.0974981 | 5444.19ms | 409725 | 160 | 1.12576e+08 | 860335 | 0.193639 | 11.1717 | 46.7001 | 9.38366 | 0.0362148 | 0.0450848 | 4.72268e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 984.693 | 0.0865152 | 5739.42ms | 409725 | 320 | 3.77153e+07 | 396818 | 0.180252 | 5.1862 | 25.1434 | 4.95329 | 0.0114832 | 0.0132947 | 1.16694e-05 | 1(Win) | true |
| simdjson (ondemand) | 496.158 | 0.162072 | 5326.04ms | 409725 | 40 | 6.51658e+07 | 787540 | 0.0663568 | 10.3117 | 43.8515 | 8.73732 | 0.0323613 | 0.0222142 | 3.81964e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1333.06 | 0.0672207 | 6236.09ms | 676745 | 640 | 6.77855e+07 | 484144 | 0.105823 | 3.81374 | 17.8472 | 3.53475 | 0.00897212 | 0.031847 | 4.17116e-05 | 1(Win) | true |
| simdjson (ondemand) | 746.963 | 0.108123 | 5506.7ms | 676745 | 80 | 6.982e+07 | 864024 | 0.0832443 | 6.81906 | 28.6715 | 5.6668 | 0.0221303 | 0.0418922 | 4.31292e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1509.63 | 0.0851181 | 6087.23ms | 676745 | 320 | 4.23745e+07 | 427519 | 0.0847098 | 3.3654 | 16.1205 | 3.14294 | 0.0075642 | 0.0192578 | 4.9497e-05 | 1(Win) | true |
| simdjson (ondemand) | 801.301 | 0.0744283 | 5409.29ms | 676745 | 320 | 1.14997e+08 | 805433 | 0.0694814 | 6.34109 | 26.948 | 5.27578 | 0.0199123 | 0.0228077 | 6.28006e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2640.6 | 0.055952 | 7930.74ms | 409725 | 160 | 1.09681e+06 | 147975 | 0.00527931 | 1.9141 | 8.99136 | 1.64189 | 0.00640678 | 5.83776e-05 | 6.84911e-06 | 1(Win) | true |
| simdjson (ondemand) | 1981.76 | 0.043969 | 5173.79ms | 409725 | 80 | 601267 | 197170 | 0.151087 | 2.55105 | 10.7131 | 1.82774 | 0.00828095 | 0.00112197 | 5.73861e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3150.13 | 0.0400086 | 7618.89ms | 409725 | 320 | 788106 | 124041 | 0.296508 | 1.60475 | 8.00165 | 1.41425 | 0.00366425 | 6.53487e-05 | 2.08905e-05 | 1(Win) | true |
| simdjson (ondemand) | 2252.26 | 0.12156 | 5078.58ms | 409725 | 80 | 3.55809e+06 | 173490 | 0.0120742 | 2.26777 | 9.72675 | 1.59842 | 0.006838 | 0.000598328 | 2.21185e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3748.76 | 0.0298093 | 9186.35ms | 676745 | 2560 | 6.74246e+06 | 172162 | 0.278564 | 1.35491 | 6.17032 | 1.05057 | 0.00508156 | 0.000971751 | 1.43368e-05 | 1(Win) | true |
| simdjson (ondemand) | 3063.17 | 0.030004 | 5550.99ms | 676745 | 640 | 2.55768e+06 | 210695 | 0.0552244 | 1.65416 | 6.95239 | 1.10638 | 0.00590911 | 0.000837894 | 2.73437e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4358.07 | 0.0455662 | 8900.04ms | 676745 | 1280 | 5.8285e+06 | 148092 | 0.039926 | 1.16246 | 5.56839 | 0.912184 | 0.00333387 | 0.000410921 | 1.36487e-05 | 1(Win) | true |
| simdjson (ondemand) | 3423.5 | 0.0318962 | 5484.1ms | 676745 | 1280 | 4.62806e+06 | 188519 | 0.0579003 | 1.48362 | 6.35492 | 0.967453 | 0.00510378 | 0.000366694 | 1.23292e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1980.05 | 0.0288308 | 5232.74ms | 409725 | 1280 | 4.14338e+06 | 197340 | 0.0849922 | 2.5626 | 12.1662 | 2.33238 | 0.00891149 | 0.000183185 | 1.31605e-05 | 1(Win) | true |
| simdjson (ondemand) | 1440.1 | 0.0792789 | 7125.28ms | 409725 | 160 | 7.40351e+06 | 271332 | 0.00251082 | 3.547 | 14.7307 | 2.67462 | 0.0133326 | 0.00123758 | 3.3315e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2226.6 | 0.0479156 | 5172.48ms | 409725 | 640 | 4.52516e+06 | 175489 | 0.309245 | 2.29743 | 11.153 | 2.09971 | 0.00749813 | 8.5549e-05 | 5.81945e-06 | 1(Win) | true |
| simdjson (ondemand) | 1553.63 | 0.023145 | 7066.72ms | 409725 | 1280 | 4.33724e+06 | 251504 | 0.0484909 | 3.25977 | 13.7194 | 2.44014 | 0.0120534 | 0.00072914 | 1.09525e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3024.87 | 0.0781355 | 5642.06ms | 676745 | 1280 | 3.55748e+07 | 213362 | 0.191085 | 1.67711 | 8.02626 | 1.46185 | 0.00569476 | 0.00127344 | 1.774e-05 | 1(Win) | true |
| simdjson (ondemand) | 2256.66 | 0.105493 | 7456.85ms | 676745 | 80 | 7.28207e+06 | 285995 | 0.0531981 | 2.25345 | 9.43631 | 1.63076 | 0.00893799 | 0.00102993 | 6.18771e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3311.38 | 0.144167 | 5691.43ms | 676745 | 80 | 6.31612e+06 | 194902 | 0.266053 | 1.53856 | 7.41174 | 1.32069 | 0.00574278 | 0.000444314 | 1.57925e-05 | 1(Win) | true |
| simdjson (ondemand) | 2455.76 | 0.142033 | 7432.19ms | 676745 | 30 | 4.18004e+06 | 262809 | 0.348982 | 2.08702 | 8.82335 | 1.48867 | 0.00843823 | 0.000370942 | 1.22153e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1849.11 | 0.0993351 | 7335.83ms | 264040 | 320 | 5.8556e+06 | 136178 | 0.0336368 | 2.76108 | 9.4995 | 1.73761 | 0.0127764 | 0.000425516 | 9.6813e-05 | 1(Win) | true |
| simdjson (ondemand) | 1726.34 | 0.0479117 | 7850.4ms | 264040 | 2560 | 1.25028e+07 | 145862 | 0.118355 | 2.94134 | 10.6576 | 1.82896 | 0.00892881 | 0.00151681 | 5.229e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2289.02 | 0.305196 | 6446.21ms | 264040 | 30 | 3.38158e+06 | 110007 | 0.0430999 | 2.20874 | 8.13327 | 1.42647 | 0.00871926 | 2.08302e-05 | 1.28768e-05 | 1(Win) | true |
| simdjson (ondemand) | 2027.8 | 0.0685445 | 7469.52ms | 264040 | 1280 | 9.27356e+06 | 124178 | 0.0565902 | 2.50365 | 9.29185 | 1.51771 | 0.00825438 | 5.61912e-05 | 3.38609e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2270.99 | 0.0719022 | 8139.59ms | 360584 | 640 | 7.58662e+06 | 151423 | 0.149944 | 2.24682 | 7.75498 | 1.3465 | 0.0106968 | 0.000873418 | 2.87034e-05 | 1(Win) | true |
| simdjson (ondemand) | 2231.13 | 0.0648421 | 8247.86ms | 360584 | 1280 | 1.27847e+07 | 154128 | 0.0945565 | 2.25744 | 8.1897 | 1.35482 | 0.00705737 | 0.0027365 | 4.0869e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2733 | 0.0375586 | 7583.84ms | 360584 | 2560 | 5.71731e+06 | 125825 | 0.0492084 | 1.85679 | 6.75606 | 1.11904 | 0.00814505 | 4.01551e-05 | 7.07186e-06 | 1(Win) | true |
| simdjson (ondemand) | 2666.22 | 0.0501821 | 7803.75ms | 360584 | 1280 | 5.36204e+06 | 128977 | 0.151804 | 1.8987 | 7.20064 | 1.12994 | 0.00561431 | 9.96842e-05 | 7.69585e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 708.776 | 0.0714088 | 9304.67ms | 264040 | 640 | 4.11912e+07 | 355272 | 0.0151938 | 7.18608 | 27.4563 | 5.05808 | 0.0265309 | 0.0017886 | 8.12436e-05 | 1(Win) | true |
| simdjson (ondemand) | 303.033 | 0.0755243 | 5294.86ms | 264040 | 320 | 1.26033e+08 | 830959 | 0.305824 | 16.7013 | 64.2725 | 13.068 | 0.0944468 | 0.00478753 | 8.95461e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 766.853 | 0.0524645 | 9007.89ms | 264040 | 1280 | 3.7989e+07 | 328366 | 0.0897903 | 6.6232 | 26.0929 | 4.74777 | 0.0225413 | 0.000184871 | 3.84441e-05 | 1(Win) | true |
| simdjson (ondemand) | 313.719 | 0.0975171 | 5218.04ms | 264040 | 320 | 1.96052e+08 | 802656 | 0.0876821 | 16.1387 | 62.9066 | 12.7577 | 0.090248 | 0.000309446 | 4.082e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 893.708 | 0.0554262 | 10018ms | 360584 | 1280 | 5.82186e+07 | 384778 | 0.0850251 | 5.70824 | 21.136 | 3.90759 | 0.022232 | 0.00460735 | 6.51894e-05 | 1(Win) | true |
| simdjson (ondemand) | 433.807 | 0.13078 | 5054.82ms | 360584 | 160 | 1.71959e+08 | 792702 | 0.11948 | 11.6067 | 46.8452 | 9.4512 | 0.0529534 | 0.00377767 | 8.40997e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.929 | 0.0578435 | 9717.61ms | 360584 | 640 | 2.74804e+07 | 358234 | 0.133973 | 5.3493 | 20.1395 | 3.68097 | 0.0204986 | 0.000913288 | 0.000100969 | 1(Win) | true |
| simdjson (ondemand) | 447.125 | 0.174867 | 10041.1ms | 360584 | 80 | 1.44698e+08 | 769091 | 0.274734 | 11.2557 | 45.8448 | 9.22381 | 0.0519967 | 0.000369331 | 7.48439e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7537.43 | 0.027644 | 4080.68ms | 264040 | 4890 | 417065 | 33407.7 | 0.0352247 | 0.671817 | 3.39984 | 0.455567 | 0.00120345 | 1.95019e-06 | 8.94547e-07 | 1(Win) | true |
| simdjson (ondemand) | 6212.88 | 0.0539876 | 4859.24ms | 264040 | 320 | 153212 | 40530 | 0.151855 | 0.816903 | 3.97149 | 0.435095 | 0.00123798 | 4.53293e-06 | 2.52092e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7752.66 | 0.0863498 | 4030.91ms | 264040 | 40 | 31464.5 | 32480.2 | 0.0150627 | 0.652754 | 3.32174 | 0.43782 | 0.00125909 | 6.15437e-06 | 3.88199e-06 | 1(Win) | true |
| simdjson (ondemand) | 6374.12 | 0.0337079 | 4759.64ms | 264040 | 2560 | 453944 | 39504.8 | 0.0167126 | 0.794909 | 3.89331 | 0.417321 | 0.00124194 | 1.45885e-05 | 1.13456e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8592.1 | 0.154217 | 4757.69ms | 360584 | 2560 | 9.75254e+06 | 40022.8 | 0.0830439 | 0.586893 | 2.96668 | 0.356613 | 0.000807624 | 1.0637e-05 | 6.25613e-06 | 1(Win) | true |
| simdjson (ondemand) | 7446.64 | 0.0713484 | 5388.94ms | 360584 | 40 | 43423.1 | 46179.2 | 0.047744 | 0.679173 | 3.29781 | 0.335419 | 0.000943261 | 1.66397e-06 | 1.10931e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8830.95 | 0.0297992 | 4711ms | 360584 | 4890 | 658439 | 38940.3 | 0.0533898 | 0.571891 | 2.90947 | 0.343618 | 0.000828082 | 3.70281e-06 | 2.51183e-06 | 1(Win) | true |
| simdjson (ondemand) | 7622.43 | 0.0407069 | 5305.69ms | 360584 | 1280 | 431690 | 45114.2 | 0.0983751 | 0.662334 | 3.24057 | 0.322404 | 0.000918982 | 1.13076e-05 | 7.98184e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5122.96 | 0.175252 | 5680.64ms | 264040 | 160 | 1.18726e+06 | 49152.9 | 0.0757778 | 0.983757 | 5.14406 | 0.861907 | 0.00175525 | 9.08953e-06 | 5.25489e-06 | 1(Win) | true |
| simdjson (ondemand) | 3999.75 | 0.0330517 | 7079.72ms | 264040 | 2560 | 1.10841e+06 | 62955.9 | 0.0332194 | 1.26313 | 6.32691 | 0.948355 | 0.00222514 | 6.49316e-06 | 3.74588e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5257.5 | 0.0326967 | 5594.74ms | 264040 | 320 | 78476.5 | 47895 | 0.0756487 | 0.961824 | 5.06593 | 0.84413 | 0.00171585 | 2.20019e-05 | 1.72322e-05 | 1(Win) | true |
| simdjson (ondemand) | 4076.07 | 0.0664708 | 6994.15ms | 264040 | 80 | 134899 | 61777.2 | 0.0504283 | 1.24039 | 6.24874 | 0.930581 | 0.00225146 | 4.45008e-06 | 2.41441e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6207.67 | 0.0411886 | 6312.58ms | 360584 | 2560 | 1.33275e+06 | 55395.9 | 0.0934076 | 0.81797 | 4.24637 | 0.659148 | 0.0013494 | 5.82172e-06 | 3.86634e-06 | 1(Win) | true |
| simdjson (ondemand) | 4972.51 | 0.034481 | 7677.88ms | 360584 | 2560 | 1.45566e+06 | 69156.1 | 0.0296174 | 1.01656 | 5.0332 | 0.713514 | 0.00194152 | 1.58879e-05 | 1.1794e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6252.24 | 0.117523 | 6319.54ms | 360584 | 640 | 2.67402e+06 | 55001 | 0.193772 | 0.80533 | 4.18916 | 0.64613 | 0.00135327 | 1.48457e-05 | 1.17734e-05 | 1(Win) | true |
| simdjson (ondemand) | 5056.25 | 0.0386161 | 7624.37ms | 360584 | 1280 | 882879 | 68010.8 | 0.101311 | 0.99934 | 4.97595 | 0.700499 | 0.00191456 | 1.95451e-05 | 1.58164e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2036.35 | 0.282147 | 883.112ms | 2632 | 30 | 362.861 | 1232.63 | 0.00270431 | 2.60581 | 10.0828 | 1.88108 | 0.00158308 | 2.53293e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1569.07 | 0.105306 | 888.09ms | 2632 | 1280 | 3632.48 | 1599.72 | 0.249394 | 3.31551 | 11.6052 | 2.14058 | 0.00205523 | 9.14229e-05 | 3.85876e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2591.72 | 0.0554932 | 842.247ms | 2632 | 1280 | 369.729 | 968.495 | 0.163941 | 2.0418 | 8.27698 | 1.45251 | 0.00113358 | 8.13307e-05 | 2.64176e-05 | 1(Win) | true |
| simdjson (ondemand) | 1858.49 | 0.144756 | 894.012ms | 2632 | 80 | 305.787 | 1350.6 | 0 | 2.86441 | 9.91983 | 1.74392 | 0.00240786 | 0.000137728 | 9.49848e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2413.32 | 0.0880115 | 870.321ms | 3370 | 1280 | 1758.41 | 1331.73 | 0.243216 | 2.16615 | 8.40386 | 1.50178 | 0.000602513 | 0.000113594 | 5.07697e-05 | 1(Win) | true |
| simdjson (ondemand) | 1994.97 | 0.0599584 | 914.431ms | 3370 | 1280 | 1194.26 | 1611 | 0.132372 | 2.62465 | 9.36855 | 1.6822 | 0.00119019 | 2.36461e-05 | 1.8546e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3020.22 | 0.0771286 | 839.267ms | 3370 | 4890 | 3293.98 | 1064.12 | 0.00835425 | 1.75481 | 6.99288 | 1.16706 | 0.000760833 | 5.07303e-05 | 1.71124e-05 | 1(Win) | true |
| simdjson (ondemand) | 2284.89 | 0.0802716 | 874.554ms | 3370 | 4890 | 6233.92 | 1406.58 | 0.115834 | 2.29839 | 8.05282 | 1.3724 | 0.002199 | 5.6131e-05 | 1.89935e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1340.41 | 0.0812385 | 915.775ms | 2632 | 2560 | 5924.59 | 1872.61 | 0.0623265 | 3.87705 | 15.916 | 3.1155 | 0.0021658 | 0.000107452 | 4.28916e-05 | 1(Win) | true |
| simdjson (ondemand) | 705.323 | 0.0718727 | 1082.71ms | 2632 | 640 | 4187 | 3558.75 | 0.0352688 | 7.37941 | 29.3921 | 5.95517 | 0.0117698 | 5.46163e-05 | 1.60287e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1554.09 | 0.0694029 | 898.891ms | 2632 | 2560 | 3216.72 | 1615.13 | 0.00207998 | 3.34558 | 14.1094 | 2.68617 | 0.00289333 | 5.19448e-05 | 1.57319e-05 | 1(Win) | true |
| simdjson (ondemand) | 751.453 | 0.0293167 | 1067.66ms | 2632 | 4890 | 4689.3 | 3340.29 | 0.0297113 | 6.85039 | 27.7063 | 5.55737 | 0.010076 | 7.91734e-05 | 2.65724e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1680.69 | 0.0562559 | 919.976ms | 3370 | 320 | 370.315 | 1912.24 | 0.0690793 | 3.1291 | 12.9864 | 2.51573 | 0.00141691 | 3.98739e-05 | 4.6365e-06 | 1(Win) | true |
| simdjson (ondemand) | 906.187 | 0.0605478 | 1084.13ms | 3370 | 40 | 184.451 | 3546.6 | 0.104434 | 5.75027 | 23.0122 | 4.60415 | 0.00951039 | 1.48368e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1908.65 | 0.0377167 | 904.762ms | 3370 | 4890 | 1972.35 | 1683.85 | 0.210112 | 2.74867 | 11.576 | 2.18042 | 0.00222655 | 4.73321e-05 | 9.83051e-06 | 1(Win) | true |
| simdjson (ondemand) | 953.269 | 0.109391 | 1072.48ms | 3370 | 30 | 408.047 | 3371.43 | 0.382149 | 5.36843 | 21.6955 | 4.29347 | 0.00939664 | 0 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3542.3 | 0.114259 | 797.609ms | 2632 | 160 | 104.883 | 708.6 | 0.0229273 | 1.52929 | 6.37766 | 1.09195 | 0.000379939 | 4.27432e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2441.52 | 0.081187 | 822.514ms | 2632 | 160 | 111.466 | 1028.08 | 0.470309 | 2.19148 | 8.09119 | 1.3883 | 0.000384688 | 2.37462e-05 | 2.37462e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4439.75 | 0.111974 | 772.977ms | 2632 | 320 | 128.244 | 565.362 | 0.162243 | 1.24687 | 5.3617 | 0.847264 | 0.000387063 | 1.06858e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2837.2 | 0.119389 | 806.117ms | 2632 | 80 | 89.2506 | 884.7 | 0.195362 | 1.90118 | 7.06497 | 1.1421 | 0.000764628 | 1.8997e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4059.39 | 0.0659888 | 795.718ms | 3370 | 2560 | 698.746 | 791.716 | 0.0203235 | 1.32919 | 5.43056 | 0.877745 | 0.000301256 | 1.588e-05 | 5.33197e-06 | 1(Win) | true |
| simdjson (ondemand) | 3093.56 | 0.125151 | 822.572ms | 3370 | 1280 | 2163.82 | 1038.9 | 0.000827207 | 1.72598 | 6.45193 | 1.05816 | 0.000401984 | 3.33828e-05 | 8.80935e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4974.8 | 0.0839332 | 781.431ms | 3370 | 640 | 188.173 | 646.033 | 0.324729 | 1.10385 | 4.63769 | 0.686647 | 0.000765022 | 1.20549e-05 | 4.17285e-06 | 1(Win) | true |
| simdjson (ondemand) | 3531.74 | 0.131721 | 810.127ms | 3370 | 30 | 43.1034 | 910 | 0.182815 | 1.52372 | 5.65045 | 0.865875 | 0.000702275 | 0 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2559.45 | 0.0921411 | 815.219ms | 2632 | 1280 | 1045.19 | 980.706 | 0.219067 | 2.07873 | 8.88754 | 1.65958 | 0.00076344 | 3.2651e-05 | 1.12794e-05 | 1(Win) | true |
| simdjson (ondemand) | 2067.43 | 0.0598649 | 837.584ms | 2632 | 4890 | 2583.24 | 1214.1 | 0.177721 | 2.57717 | 9.8845 | 1.76558 | 0.00207296 | 8.13489e-05 | 5.07363e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2938.59 | 0.0673782 | 807.553ms | 2632 | 640 | 211.989 | 854.177 | 0.147403 | 1.80591 | 7.87082 | 1.41299 | 0.00117544 | 5.93655e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2341.8 | 0.0450998 | 854.761ms | 2632 | 2560 | 598.221 | 1071.86 | 0.0776015 | 2.28 | 8.85828 | 1.51938 | 0.0017118 | 6.456e-05 | 2.56756e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3140.19 | 0.0777735 | 817.803ms | 3370 | 2560 | 1622.01 | 1023.47 | 0.00927539 | 1.70317 | 7.37478 | 1.32196 | 0.000597645 | 2.81667e-05 | 8.80935e-06 | 1(Win) | true |
| simdjson (ondemand) | 2677.22 | 0.0530897 | 835.407ms | 3370 | 640 | 259.951 | 1200.45 | 0.296661 | 1.9891 | 7.84777 | 1.35282 | 0.0010701 | 1.48368e-05 | 3.7092e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3618.05 | 0.059812 | 807.502ms | 3370 | 4890 | 1380.37 | 888.291 | 0.0171097 | 1.48612 | 6.5819 | 1.12938 | 0.000893242 | 2.16029e-05 | 7.52459e-06 | 1(Win) | true |
| simdjson (ondemand) | 3034.75 | 0.0701582 | 825.101ms | 3370 | 1280 | 706.614 | 1059.03 | 0.153678 | 1.76185 | 7.04629 | 1.16053 | 0.00102304 | 2.22552e-05 | 2.55007e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 791.521 | 0.0381127 | 1285.85ms | 4630 | 4890 | 22104.7 | 5578.52 | 0.260481 | 6.50414 | 31.4203 | 5.76285 | 0.00436378 | 2.56618e-05 | 1.01145e-05 | 1(Win) | true |
| Jsonifier (generic) | 735.147 | 0.0619994 | 1324.93ms | 4630 | 80 | 1109.38 | 6006.3 | 0.110595 | 7.05583 | 31.2272 | 6.32829 | 0.00680076 | 2.15983e-05 | 0 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 949.035 | 0.0441536 | 1288.25ms | 4630 | 2560 | 10803.7 | 4652.63 | 0.110048 | 5.41952 | 26.7382 | 4.6743 | 0.00219113 | 3.071e-05 | 9.19614e-06 | 1(Win) | true |
| Jsonifier (generic) | 875.28 | 0.0469711 | 1331.82ms | 4630 | 80 | 449.18 | 5044.69 | 0.0245368 | 5.93413 | 26.5158 | 5.23175 | 0.00458153 | 1.61987e-05 | 8.09935e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1862.99 | 0.0462917 | 1334.18ms | 11579 | 4890 | 36815.9 | 5927.35 | 0.0347022 | 2.74504 | 13.3812 | 2.3445 | 0.00136881 | 1.73786e-05 | 7.34706e-06 | 1(Win) | true |
| Jsonifier (generic) | 1744.29 | 0.0431457 | 1365.8ms | 11579 | 1280 | 9549.68 | 6330.71 | 0.148901 | 2.95707 | 13.2828 | 2.57898 | 0.00246904 | 2.13884e-05 | 8.29897e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2226.21 | 0.0538055 | 1317.48ms | 11579 | 2560 | 18234.8 | 4960.26 | 0.0408727 | 2.30281 | 11.4869 | 1.90172 | 0.000999891 | 3.70755e-05 | 2.34463e-05 | 1(Win) | true |
| Jsonifier (generic) | 2077.24 | 0.0829119 | 1362.34ms | 11579 | 40 | 777.077 | 5316 | 0.0745619 | 2.49928 | 11.3795 | 2.13317 | 0.00217204 | 1.94317e-05 | 2.15908e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 715.343 | 0.043226 | 1350.71ms | 4630 | 2560 | 18224.8 | 6172.58 | 0.0399415 | 7.20727 | 35.8788 | 6.75594 | 0.00445675 | 8.3862e-05 | 5.09584e-05 | 1(Win) | true |
| Jsonifier (generic) | 678.2 | 0.102145 | 1393.58ms | 4630 | 30 | 1326.79 | 6510.63 | 0.0455457 | 7.64138 | 34.4138 | 7.03132 | 0.00897048 | 5.75954e-05 | 2.15983e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 826.271 | 0.0587115 | 1364.98ms | 4630 | 1280 | 12600.1 | 5343.9 | 0.213746 | 6.19258 | 31.1596 | 5.66588 | 0.00326978 | 2.61542e-05 | 3.88094e-06 | 1(Win) | true |
| Jsonifier (generic) | 801.22 | 0.0342093 | 1368.15ms | 4630 | 4890 | 17380.2 | 5510.99 | 0.0745734 | 6.43449 | 29.5616 | 5.91642 | 0.00449642 | 5.31786e-05 | 2.27025e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1677.91 | 0.0235174 | 1386.32ms | 11579 | 4890 | 11713.6 | 6581.14 | 0.198797 | 3.07486 | 15.1309 | 2.72459 | 0.00181951 | 2.49199e-05 | 8.54802e-06 | 1(Win) | true |
| Jsonifier (generic) | 1622.25 | 0.0481761 | 1410.2ms | 11579 | 1280 | 13765.1 | 6806.96 | 0.102769 | 3.15804 | 14.5622 | 2.85992 | 0.00208554 | 2.56391e-05 | 1.09303e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1954.42 | 0.0594016 | 1388.04ms | 11579 | 640 | 7209.11 | 5650.05 | 0.126829 | 2.64799 | 13.2513 | 2.28837 | 0.00175979 | 1.75425e-05 | 3.23862e-06 | 1(Win) | true |
| Jsonifier (generic) | 1879.77 | 0.0734761 | 1405.72ms | 11579 | 640 | 11923.5 | 5874.44 | 0.201889 | 2.7299 | 12.6663 | 2.4186 | 0.00217487 | 1.71377e-05 | 8.09655e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7870.03 | 0.0797618 | 768.304ms | 4630 | 4890 | 979.281 | 561.054 | 0.141575 | 0.699907 | 3.51188 | 0.492873 | 0.000432849 | 3.24195e-05 | 1.74906e-05 | 1(Win) | true |
| simdjson (ondemand) | 6486.68 | 0.0497653 | 780.363ms | 4630 | 4890 | 561.149 | 680.704 | 0.350037 | 0.836893 | 4.11512 | 0.493089 | 0.000432407 | 1.98757e-05 | 9.14283e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8102.5 | 0.0839756 | 769.343ms | 4630 | 2560 | 536.13 | 544.957 | 0.255173 | 0.679832 | 3.47819 | 0.485313 | 0.000432219 | 1.32458e-05 | 2.86852e-06 | 1(Win) | true |
| simdjson (ondemand) | 6735.78 | 0.16037 | 778.833ms | 4630 | 160 | 176.829 | 655.531 | 0.253918 | 0.811282 | 4.08013 | 0.485313 | 0.000431965 | 2.29482e-05 | 1.07991e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12930.6 | 0.0741696 | 802.199ms | 11579 | 320 | 128.382 | 853.987 | 0.046861 | 0.417261 | 2.09474 | 0.223681 | 0.000172726 | 4.04828e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11015.3 | 0.0420133 | 816.893ms | 11579 | 320 | 56.7645 | 1002.48 | 0.00623492 | 0.486373 | 2.45177 | 0.232576 | 0.000172726 | 8.36644e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 13151.7 | 0.0512406 | 799.442ms | 11579 | 2560 | 473.858 | 839.634 | 0.088985 | 0.409289 | 2.08135 | 0.220572 | 0.000172828 | 8.87247e-06 | 3.60971e-06 | 1(Win) | true |
| simdjson (ondemand) | 11082.1 | 0.0932453 | 818.341ms | 11579 | 1280 | 1105 | 996.436 | 0.139835 | 0.482933 | 2.43778 | 0.229467 | 0.000172726 | 8.02908e-06 | 3.37356e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5692.75 | 0.116417 | 795.613ms | 4630 | 160 | 130.459 | 775.638 | 0.159801 | 0.95058 | 5.06242 | 0.835853 | 0.000647948 | 1.61987e-05 | 9.44924e-06 | 1(Win) | true |
| simdjson (ondemand) | 5119.88 | 0.133237 | 804.825ms | 4630 | 40 | 52.8147 | 862.425 | 0.0241509 | 1.05574 | 5.58877 | 0.820734 | 0.000647948 | 0 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5738.69 | 0.07681 | 792.586ms | 4630 | 320 | 111.769 | 769.428 | 0.232448 | 0.932235 | 5.02851 | 0.827862 | 0.000649973 | 5.39957e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5147.36 | 0.0697667 | 802.751ms | 4630 | 4890 | 1751.45 | 857.821 | 0.245451 | 1.04726 | 5.55378 | 0.812959 | 0.000656649 | 1.8374e-05 | 6.31606e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10303.9 | 0.0795681 | 820.642ms | 11579 | 2560 | 1861.49 | 1071.69 | 0.00266087 | 0.519027 | 2.703 | 0.358753 | 0.000260237 | 1.24147e-05 | 5.02661e-06 | 1(Win) | true |
| simdjson (ondemand) | 9116.69 | 0.050999 | 838.002ms | 11579 | 2560 | 976.856 | 1211.25 | 0.00696643 | 0.579397 | 3.04102 | 0.363589 | 0.000261586 | 1.07954e-05 | 3.47477e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10494.4 | 0.0658597 | 821.27ms | 11579 | 1280 | 614.724 | 1052.24 | 0.111764 | 0.508894 | 2.68961 | 0.355558 | 0.00025909 | 7.08448e-06 | 3.37356e-07 | 1(Win) | true |
| simdjson (ondemand) | 8958.54 | 0.146809 | 837.039ms | 11579 | 1280 | 4191.65 | 1232.63 | 0.0259928 | 0.58608 | 3.02703 | 0.36048 | 0.000270222 | 9.04115e-06 | 2.09161e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1264.69 | 0.0647927 | 1108.69ms | 5092 | 160 | 990.327 | 3839.75 | 0.0205049 | 4.11559 | 16.7123 | 3.1632 | 0.001943 | 5.52337e-05 | 1.35016e-05 | 1(Win) | true |
| simdjson (ondemand) | 1131.81 | 0.0775361 | 1152.11ms | 5092 | 160 | 1770.74 | 4290.56 | 0.122358 | 4.59517 | 17.7518 | 3.13668 | 0.00220812 | 4.4187e-05 | 1.22742e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1440.96 | 0.0306478 | 1097.58ms | 5092 | 2560 | 2730.95 | 3370.06 | 0.00561038 | 3.61684 | 15.1208 | 2.77258 | 0.00142311 | 8.37711e-05 | 3.59786e-05 | 1(Win) | true |
| simdjson (ondemand) | 1259.36 | 0.0467933 | 1142.88ms | 5092 | 2560 | 8334.59 | 3856.02 | 0.129003 | 4.11217 | 16.2231 | 2.75648 | 0.00260933 | 0.000165471 | 9.35904e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2227.05 | 0.099206 | 1141.3ms | 9739 | 320 | 5477.63 | 4170.46 | 0.0265329 | 2.33368 | 9.6323 | 1.71619 | 0.00141345 | 8.40692e-05 | 4.65269e-05 | 1(Win) | true |
| simdjson (ondemand) | 2049.83 | 0.136823 | 1175.67ms | 9739 | 320 | 12298.9 | 4531.03 | 0.00131039 | 2.53119 | 9.93398 | 1.66834 | 0.00157068 | 3.81841e-05 | 1.7969e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2489.67 | 0.202625 | 1193.54ms | 9739 | 160 | 9142.24 | 3730.55 | 0.048227 | 2.08945 | 8.8006 | 1.51268 | 0.00145228 | 2.11777e-05 | 5.134e-06 | 1(Win) | true |
| simdjson (ondemand) | 2288.12 | 0.0502186 | 1167.77ms | 9739 | 640 | 2659.38 | 4059.15 | 0.193784 | 2.27363 | 9.13554 | 1.46884 | 0.00184712 | 1.81294e-05 | 2.24612e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 742.045 | 0.0319734 | 1399.24ms | 5092 | 1280 | 5604.1 | 6544.23 | 0.0253618 | 6.97978 | 30.8698 | 6.30185 | 0.00610839 | 3.03785e-05 | 5.6768e-06 | 1(Win) | true |
| simdjson (ondemand) | 451.475 | 0.0230489 | 1801.46ms | 5092 | 4890 | 30055.3 | 10756.1 | 0.0307564 | 11.3943 | 53.6296 | 10.9486 | 0.016229 | 0.000105663 | 4.99601e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 797.178 | 0.067012 | 1377.92ms | 5092 | 80 | 1333.1 | 6091.62 | 0.232565 | 6.5066 | 29.2492 | 5.90809 | 0.00650285 | 2.9458e-05 | 2.45483e-06 | 1(Win) | true |
| simdjson (ondemand) | 472.592 | 0.0501465 | 1795.16ms | 5092 | 40 | 1062.05 | 10275.5 | 0.045638 | 10.9452 | 52.1007 | 10.5703 | 0.0171053 | 0.000103103 | 5.40063e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1305.03 | 0.104785 | 1448.66ms | 9739 | 40 | 2224.56 | 7116.95 | 0.157357 | 3.9697 | 17.0865 | 3.40589 | 0.00326266 | 2.0536e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 847.462 | 0.030974 | 1834.16ms | 9739 | 320 | 3687.51 | 10959.6 | 0.236969 | 6.10213 | 28.6063 | 5.73355 | 0.00817429 | 0.000144394 | 8.7278e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.27 | 0.0334563 | 1437.48ms | 9739 | 1280 | 6375.94 | 6670.98 | 0.0397518 | 3.72033 | 16.2393 | 3.1993 | 0.00323771 | 4.2917e-05 | 2.4226e-05 | 1(Win) | true |
| simdjson (ondemand) | 886.782 | 0.055869 | 1815.98ms | 9739 | 30 | 1027.21 | 10473.6 | 0.0678353 | 5.83326 | 27.8069 | 5.53414 | 0.00860458 | 5.134e-05 | 1.0268e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5399.85 | 0.0505184 | 804.708ms | 5092 | 4890 | 1009.3 | 899.305 | 0.154651 | 0.994764 | 4.58229 | 0.691084 | 0.00116856 | 1.53816e-05 | 4.77914e-06 | 1(Win) | true |
| simdjson (ondemand) | 4418.16 | 0.0638704 | 826.289ms | 5092 | 160 | 78.8522 | 1099.12 | 0.0557572 | 1.20721 | 5.39022 | 0.6685 | 0.00128019 | 6.13708e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5524.18 | 0.0400186 | 799.359ms | 5092 | 4890 | 605.166 | 879.065 | 0.131593 | 0.973385 | 4.47059 | 0.666546 | 0.00131595 | 1.05221e-05 | 3.45383e-06 | 1(Win) | true |
| simdjson (ondemand) | 4547.35 | 0.148602 | 823.854ms | 5092 | 640 | 1611.73 | 1067.9 | 0.0419749 | 1.17283 | 5.27494 | 0.643363 | 0.000828505 | 5.21652e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7848.58 | 0.0362488 | 835.888ms | 9739 | 4890 | 899.795 | 1183.38 | 0.117034 | 0.678291 | 3.02639 | 0.385666 | 0.000762498 | 1.77433e-05 | 8.31519e-06 | 1(Win) | true |
| simdjson (ondemand) | 6891.36 | 0.114939 | 852.268ms | 9739 | 40 | 95.9872 | 1347.75 | 0.0160788 | 0.755976 | 3.46904 | 0.37663 | 0.000551905 | 7.701e-06 | 2.567e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8157.66 | 0.0319094 | 831.299ms | 9739 | 4890 | 645.422 | 1138.54 | 0.157514 | 0.649491 | 2.96817 | 0.372831 | 0.000525684 | 1.43836e-05 | 5.83743e-06 | 1(Win) | true |
| simdjson (ondemand) | 7182.78 | 0.063168 | 844.4ms | 9739 | 2560 | 1707.97 | 1293.07 | 0.0576117 | 0.73784 | 3.40877 | 0.363487 | 0.000420065 | 1.89717e-05 | 1.24339e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3184.57 | 0.0553202 | 871.419ms | 5092 | 2560 | 1821.73 | 1524.89 | 0.145623 | 1.65421 | 7.60055 | 1.39277 | 0.00349975 | 3.56718e-05 | 2.03291e-05 | 1(Win) | true |
| simdjson (ondemand) | 2905.49 | 0.0909072 | 885.756ms | 5092 | 1280 | 2954.93 | 1671.36 | 0.0171986 | 1.81351 | 8.32954 | 1.31383 | 0.00214322 | 4.18856e-05 | 2.07126e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3274.79 | 0.0425891 | 864.231ms | 5092 | 4890 | 1950.37 | 1482.88 | 0.0550244 | 1.61285 | 7.48885 | 1.36765 | 0.0036011 | 1.42973e-05 | 3.8956e-06 | 1(Win) | true |
| simdjson (ondemand) | 2974.1 | 0.0541305 | 882.97ms | 5092 | 2560 | 1999.82 | 1632.8 | 0.462922 | 1.78406 | 8.21426 | 1.28869 | 0.00248444 | 1.99455e-05 | 8.97548e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5227.82 | 0.0671287 | 891.235ms | 9739 | 640 | 910.302 | 1776.62 | 0.000351793 | 1.00739 | 4.62193 | 0.758805 | 0.00187006 | 6.57793e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4803.33 | 0.0521624 | 910.738ms | 9739 | 2560 | 2604.35 | 1933.62 | 0.273046 | 1.09401 | 5.03183 | 0.719171 | 0.000930457 | 2.7515e-05 | 1.42388e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5347.77 | 0.0978755 | 891.414ms | 9739 | 160 | 462.33 | 1736.77 | 0.0500461 | 0.985648 | 4.56371 | 0.745662 | 0.00155496 | 2.0536e-05 | 5.134e-06 | 1(Win) | true |
| simdjson (ondemand) | 4962.63 | 0.0709664 | 906.722ms | 9739 | 160 | 282.248 | 1871.56 | 0.147054 | 1.06076 | 4.94558 | 0.700893 | 0.00101011 | 7.05925e-06 | 6.4175e-07 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1623.48 | 0.077457 | 1010.37ms | 4857 | 320 | 1562.84 | 2853.13 | 0.0112827 | 3.21772 | 12.8359 | 2.47725 | 0.000921994 | 9.20064e-05 | 5.79061e-05 | 1(Win) | true |
| simdjson (ondemand) | 1384.08 | 0.0541707 | 1064.77ms | 4857 | 4890 | 16071.2 | 3346.61 | 0.0570869 | 3.71714 | 14.5324 | 2.59728 | 0.00192234 | 0.000113723 | 5.37668e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2213.74 | 0.0785697 | 957.809ms | 4857 | 160 | 432.426 | 2092.38 | 0.016426 | 2.375 | 9.96562 | 1.84435 | 0.00114139 | 3.21701e-05 | 9.00762e-06 | 1(Win) | true |
| simdjson (ondemand) | 1652.05 | 0.0869885 | 1026.19ms | 4857 | 320 | 1903.54 | 2803.78 | 0.19589 | 3.10543 | 12.2738 | 2.11159 | 0.00232783 | 5.98363e-05 | 1.35114e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2059.86 | 0.0341162 | 1036.48ms | 6701 | 4890 | 5478.15 | 3102.43 | 0.155817 | 2.52579 | 10.3023 | 1.90315 | 0.000534822 | 7.90408e-05 | 3.83607e-05 | 1(Win) | true |
| simdjson (ondemand) | 1904.98 | 0.0251154 | 1066.46ms | 6701 | 4890 | 3471.26 | 3354.67 | 0.0692114 | 2.73238 | 10.9093 | 1.89121 | 0.000308137 | 6.06691e-05 | 2.46583e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2707.61 | 0.0563914 | 982.092ms | 6701 | 1280 | 2267.47 | 2360.22 | 0.117337 | 1.94275 | 8.21266 | 1.44456 | 0.000873237 | 6.70376e-05 | 3.05458e-05 | 1(Win) | true |
| simdjson (ondemand) | 2303.06 | 0.0501608 | 1028.14ms | 6701 | 640 | 1239.88 | 2774.82 | 0.160289 | 2.26976 | 9.30995 | 1.54664 | 0.00055682 | 2.77477e-05 | 7.46157e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 725.554 | 0.0685224 | 1362.1ms | 4857 | 640 | 12247.4 | 6384.08 | 0.0590929 | 7.14765 | 29.875 | 5.87523 | 0.00679657 | 4.66466e-05 | 1.73718e-05 | 1(Win) | true |
| simdjson (ondemand) | 224.986 | 0.0241128 | 2793.17ms | 4857 | 4890 | 120512 | 20587.9 | 0.0180871 | 22.9095 | 107.434 | 22.5987 | 0.0480666 | 0.000223572 | 0.000124375 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.119 | 0.0311565 | 1312.73ms | 4857 | 2560 | 7869.53 | 5627.37 | 0.107508 | 6.28977 | 27.0896 | 5.25921 | 0.00750512 | 5.76648e-05 | 2.48514e-05 | 1(Win) | true |
| simdjson (ondemand) | 231.155 | 0.0353782 | 2772.56ms | 4857 | 640 | 32164.8 | 20038.5 | 0.167754 | 22.3166 | 105.267 | 22.127 | 0.0487586 | 0.000168571 | 0.000104231 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 946.242 | 0.0414611 | 1404.98ms | 6701 | 2560 | 20072.3 | 6753.64 | 0.0899282 | 5.45269 | 22.7626 | 4.51037 | 0.00468179 | 5.92262e-05 | 2.64653e-05 | 1(Win) | true |
| simdjson (ondemand) | 306.745 | 0.0251715 | 2825.15ms | 6701 | 4890 | 134478 | 20833.5 | 0.0159876 | 16.7401 | 78.0287 | 16.3395 | 0.0363183 | 0.000123719 | 6.06997e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1064.06 | 0.0615063 | 1363.96ms | 6701 | 640 | 8733.09 | 6005.85 | 0.136399 | 4.87105 | 20.7409 | 4.06387 | 0.00486121 | 2.91468e-05 | 3.49761e-06 | 1(Win) | true |
| simdjson (ondemand) | 313.797 | 0.0338175 | 2782.61ms | 6701 | 1280 | 60711.9 | 20365.3 | 0.0481635 | 16.2836 | 76.4477 | 15.9957 | 0.0377362 | 6.23741e-05 | 2.09857e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4445.55 | 0.10373 | 823.263ms | 4857 | 640 | 747.603 | 1041.94 | 0.0223392 | 1.19862 | 5.24954 | 0.815524 | 0.000209105 | 9.00762e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3773.94 | 0.107833 | 845.28ms | 4857 | 80 | 140.133 | 1227.36 | 0.0499287 | 1.41023 | 5.93515 | 0.826848 | 0.000239345 | 7.72082e-06 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5176.85 | 0.0397574 | 813.382ms | 4857 | 4890 | 618.801 | 894.752 | 0.0689737 | 1.03815 | 4.7064 | 0.694256 | 0.000570214 | 1.62521e-05 | 5.47352e-06 | 1(Win) | true |
| simdjson (ondemand) | 4098.11 | 0.168732 | 843.306ms | 4857 | 40 | 145.487 | 1130.28 | 0.0758826 | 1.27895 | 5.38872 | 0.704344 | 0.00107577 | 2.05888e-05 | 5.14721e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5449.25 | 0.0989971 | 841.583ms | 6701 | 2560 | 3450.57 | 1172.74 | 0.0566568 | 0.972406 | 4.2807 | 0.61752 | 0.000151155 | 1.17753e-05 | 2.33174e-06 | 1(Win) | true |
| simdjson (ondemand) | 4726.14 | 0.165895 | 866.463ms | 6701 | 40 | 201.276 | 1352.17 | 0.0154097 | 1.1032 | 4.72959 | 0.618266 | 0.00033204 | 1.11924e-05 | 3.73079e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6032.08 | 0.101937 | 830.878ms | 6701 | 320 | 373.218 | 1059.43 | 0.109849 | 0.86828 | 3.88718 | 0.529622 | 0.000447694 | 1.11924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5313.96 | 0.160746 | 868.119ms | 6701 | 30 | 112.11 | 1202.6 | 0.0138608 | 0.987703 | 4.33353 | 0.529473 | 0.000179078 | 0 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3192.32 | 0.042663 | 866.17ms | 4857 | 4890 | 1873.85 | 1450.98 | 0.0591948 | 1.65545 | 7.17604 | 1.25818 | 0.000623939 | 4.01672e-05 | 2.35782e-05 | 1(Win) | true |
| simdjson (ondemand) | 2251.86 | 0.0754061 | 927.33ms | 4857 | 80 | 192.467 | 2056.96 | 0.0967165 | 2.33326 | 10.2294 | 1.70311 | 0.0024475 | 2.05888e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3527.02 | 0.132699 | 853.942ms | 4857 | 80 | 242.967 | 1313.29 | 0.0943181 | 1.50357 | 6.6327 | 1.13609 | 0.00115812 | 1.02944e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2354.94 | 0.0781328 | 925.523ms | 4857 | 1280 | 3023.1 | 1966.92 | 0.0274934 | 2.2175 | 9.68334 | 1.58061 | 0.00354964 | 3.29743e-05 | 1.33506e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4018.41 | 0.0592709 | 879.938ms | 6701 | 1280 | 1137.27 | 1590.32 | 0.137607 | 1.31185 | 5.71736 | 0.955977 | 0.000463667 | 1.70217e-05 | 6.06253e-06 | 1(Win) | true |
| simdjson (ondemand) | 2991.12 | 0.061735 | 934.823ms | 6701 | 1280 | 2226.82 | 2136.52 | 0.0508533 | 1.75359 | 7.76914 | 1.23743 | 0.00115036 | 2.22681e-05 | 7.11181e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4395.09 | 0.132279 | 873.635ms | 6701 | 40 | 147.974 | 1454.03 | 0.119639 | 1.20464 | 5.32413 | 0.867482 | 0.00107074 | 7.46157e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3129.78 | 0.0501384 | 931.572ms | 6701 | 4890 | 5125.11 | 2041.86 | 0.00410189 | 1.66676 | 7.37338 | 1.14863 | 0.00214432 | 2.70387e-05 | 1.19629e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1341.76 | 0.0417345 | 839.249ms | 1691 | 2560 | 644.123 | 1201.9 | 0.0481102 | 3.95814 | 13.9302 | 2.67357 | 0.00059229 | 0.000100486 | 2.05592e-05 | 1(Win) | true |
| simdjson (ondemand) | 1195.68 | 0.0989085 | 856.166ms | 1691 | 160 | 284.736 | 1348.74 | 0.037058 | 4.43926 | 15.0982 | 2.8492 | 0.00155603 | 0.000188498 | 5.17445e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1551.73 | 0.0671269 | 829.769ms | 1691 | 320 | 155.739 | 1039.27 | 0.0607767 | 3.4442 | 12.469 | 2.30633 | 0.000591366 | 8.68569e-05 | 5.54406e-06 | 1(Win) | true |
| simdjson (ondemand) | 1382.89 | 0.0748608 | 844.698ms | 1691 | 2560 | 1951.02 | 1166.15 | 0.12158 | 3.8545 | 13.55 | 2.46482 | 0.00152508 | 8.82429e-05 | 1.70942e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1574.17 | 0.105979 | 854.094ms | 2158 | 80 | 153.579 | 1307.38 | 0.0477829 | 3.37456 | 11.7822 | 2.22614 | 0.000463392 | 1.73772e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1537.44 | 0.099977 | 857.003ms | 2158 | 4890 | 8758.27 | 1338.61 | 0.174917 | 3.48697 | 12.0806 | 2.24467 | 0.000642494 | 0.000240604 | 0.00012196 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1802.06 | 0.118029 | 841.789ms | 2158 | 2560 | 4651.39 | 1142.04 | 0.103437 | 2.96198 | 10.6659 | 1.943 | 0.000471176 | 0.000118382 | 4.2719e-05 | 1(Win) | true |
| simdjson (ondemand) | 1773.36 | 0.18198 | 843.474ms | 2158 | 40 | 178.41 | 1160.53 | 0.0954116 | 3.00916 | 10.8948 | 1.9481 | 0.000463392 | 0.000173772 | 0.000104263 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 922.638 | 0.0558628 | 893.701ms | 1691 | 640 | 610.169 | 1747.88 | 0.0498172 | 5.71152 | 20.3761 | 3.99645 | 0.00255119 | 0.000126589 | 5.26685e-05 | 1(Win) | true |
| simdjson (ondemand) | 699.621 | 0.0442605 | 952.392ms | 1691 | 640 | 666.154 | 2305.05 | 0.0524387 | 7.48817 | 27.7037 | 5.41277 | 0.00550894 | 0.000112729 | 2.77203e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1056 | 0.105139 | 882.798ms | 1691 | 1280 | 3299.88 | 1527.14 | 0.00434821 | 4.99736 | 18.8705 | 3.61916 | 0.00183924 | 0.000144145 | 4.80485e-05 | 1(Win) | true |
| simdjson (ondemand) | 773.94 | 0.0399254 | 938.417ms | 1691 | 640 | 442.947 | 2083.7 | 0.0895288 | 6.78672 | 26.1898 | 5.0343 | 0.00434931 | 0.000112729 | 2.95683e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1105.03 | 0.0529781 | 907.967ms | 2158 | 2560 | 2492.23 | 1862.42 | 0.0108238 | 4.76091 | 16.9314 | 3.35357 | 0.00202408 | 0.000110056 | 4.43481e-05 | 1(Win) | true |
| simdjson (ondemand) | 907.154 | 0.137945 | 963.551ms | 2158 | 30 | 293.816 | 2268.67 | 0.0161596 | 5.78284 | 21.8772 | 4.23494 | 0.00152919 | 0.000108125 | 4.63392e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1228.74 | 0.04866 | 896.397ms | 2158 | 4890 | 3248.13 | 1674.91 | 0.102541 | 4.26807 | 15.753 | 3.05792 | 0.00178695 | 9.34365e-05 | 4.24539e-05 | 1(Win) | true |
| simdjson (ondemand) | 990.601 | 0.0695096 | 954.75ms | 2158 | 640 | 1334.67 | 2077.56 | 0.142092 | 5.29983 | 20.6909 | 3.93837 | 0.00134239 | 7.02329e-05 | 7.96455e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5123.63 | 0.237277 | 763.365ms | 1691 | 80 | 44.6203 | 314.75 | 0.474308 | 1.14954 | 4.13779 | 0.645772 | 0.000887049 | 4.43525e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4020.14 | 0.0369495 | 751.598ms | 1691 | 2560 | 56.2423 | 401.146 | 0.167112 | 1.41268 | 5.10171 | 0.722058 | 0.000759305 | 3.04923e-05 | 6.23706e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5568.23 | 0.190079 | 742.85ms | 1691 | 160 | 48.489 | 289.619 | 0.00647361 | 1.04842 | 3.82141 | 0.571851 | 0.00116056 | 7.39208e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4339.08 | 0.0935056 | 751.757ms | 1691 | 2560 | 309.176 | 371.66 | 0.149996 | 1.31636 | 4.78001 | 0.647546 | 0.00114462 | 7.04557e-05 | 3.21093e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5519.91 | 0.160747 | 750.496ms | 2158 | 160 | 57.4703 | 372.837 | 0.0335154 | 1.03627 | 3.79935 | 0.550046 | 0.000923888 | 5.21316e-05 | 2.8962e-06 | 1(Win) | true |
| simdjson (ondemand) | 4774.18 | 0.217731 | 759.553ms | 2158 | 80 | 70.4753 | 431.075 | 0.0116003 | 1.17755 | 4.26877 | 0.578313 | 0.000834106 | 6.37164e-05 | 2.31696e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6069.09 | 0.107302 | 745.319ms | 2158 | 320 | 42.3661 | 339.1 | 0.0165853 | 0.948752 | 3.54495 | 0.491196 | 0.00092244 | 1.15848e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5220.9 | 0.100888 | 755.524ms | 2158 | 640 | 101.222 | 394.191 | 0.128263 | 1.08943 | 4.01669 | 0.519928 | 0.000898546 | 1.3757e-05 | 4.3443e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3452.96 | 0.105862 | 771.495ms | 1691 | 80 | 19.5555 | 467.038 | 0.0454789 | 1.61416 | 6.49911 | 1.16854 | 0.000591366 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2532.46 | 0.0937782 | 786.979ms | 1691 | 320 | 114.118 | 636.797 | 0.0142294 | 2.15186 | 8.47546 | 1.44885 | 0.000611694 | 1.84802e-05 | 1.84802e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3682.38 | 0.0899112 | 765.219ms | 1691 | 1280 | 198.458 | 437.941 | 0.202954 | 1.52446 | 6.17386 | 1.09344 | 0.000867183 | 5.54406e-05 | 1.94042e-05 | 1(Win) | true |
| simdjson (ondemand) | 2678.43 | 0.106221 | 777.41ms | 1691 | 160 | 65.444 | 602.094 | 0.0405001 | 2.04801 | 8.15376 | 1.37433 | 0.00109403 | 7.39208e-06 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3854.39 | 0.156494 | 768.223ms | 2158 | 160 | 111.714 | 533.944 | 0.064338 | 1.43709 | 5.54727 | 0.950417 | 0.000619787 | 1.73772e-05 | 1.15848e-05 | 1(Win) | true |
| simdjson (ondemand) | 3129.2 | 0.0810838 | 781.155ms | 2158 | 1280 | 364.011 | 657.685 | 0.0229208 | 1.74708 | 6.90825 | 1.14643 | 0.00049706 | 3.36683e-05 | 1.08608e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3979.17 | 0.0402848 | 766.555ms | 2158 | 1280 | 55.5659 | 517.2 | 0.000906314 | 1.3925 | 5.29286 | 0.891566 | 0.00124211 | 3.54785e-05 | 7.60253e-06 | 1(Win) | true |
| simdjson (ondemand) | 3291.86 | 0.0380682 | 779.479ms | 2158 | 1280 | 72.5027 | 625.188 | 0.0122478 | 1.66582 | 6.65616 | 1.08804 | 0.000846777 | 2.28076e-05 | 3.62025e-07 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1429.43 | 0.0430107 | 1022.47ms | 4390 | 4890 | 7760.13 | 2928.89 | 0.00832266 | 3.64735 | 16.733 | 3.16743 | 0.00143555 | 5.28716e-05 | 1.84468e-05 | 1(Win) | true |
| simdjson (ondemand) | 1097.86 | 0.064006 | 1107.49ms | 4390 | 1280 | 7625.75 | 3813.43 | 0.069668 | 4.67459 | 19.2125 | 3.55854 | 0.00322252 | 5.48121e-05 | 2.63383e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1613.4 | 0.0959455 | 1014.81ms | 4390 | 160 | 991.778 | 2594.91 | 0.0712426 | 3.24318 | 15.326 | 2.84897 | 0.00106777 | 3.84396e-05 | 9.96583e-06 | 1(Win) | true |
| simdjson (ondemand) | 1228.57 | 0.0364231 | 1092.65ms | 4390 | 2560 | 3943.87 | 3407.72 | 0.0695367 | 4.21681 | 17.7255 | 3.22779 | 0.00306262 | 4.42234e-05 | 2.00206e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2720.38 | 0.139884 | 1048.51ms | 9378 | 160 | 3383.9 | 3287.62 | 0.0271927 | 1.91661 | 8.79399 | 1.55118 | 0.00042853 | 5.66485e-05 | 3.06569e-05 | 1(Win) | true |
| simdjson (ondemand) | 2239.01 | 0.0934476 | 1125.99ms | 9378 | 320 | 4458.57 | 3994.43 | 0.0236322 | 2.32218 | 9.66347 | 1.68927 | 0.00171912 | 1.033e-05 | 2.33259e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2997.48 | 0.0351293 | 1043.06ms | 9378 | 4890 | 5372.26 | 2983.7 | 0.11598 | 1.7246 | 8.11079 | 1.39699 | 0.000478233 | 2.81083e-05 | 7.19606e-06 | 1(Win) | true |
| simdjson (ondemand) | 2435.91 | 0.090888 | 1113.49ms | 9378 | 640 | 7126.75 | 3671.55 | 0.0284625 | 2.11574 | 8.99435 | 1.53977 | 0.00188523 | 3.83211e-05 | 2.26594e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 820.405 | 0.0336065 | 1232.06ms | 4390 | 2560 | 7529.36 | 5103.12 | 0.104835 | 6.32043 | 28.3674 | 5.72164 | 0.0118457 | 0.000141301 | 7.18964e-05 | 1(Win) | true |
| simdjson (ondemand) | 710.389 | 0.0710723 | 1313.58ms | 4390 | 320 | 5614.2 | 5893.44 | 0.00996772 | 7.29842 | 31.2219 | 6.05991 | 0.0128666 | 4.91173e-05 | 2.42027e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 880.53 | 0.060582 | 1228.74ms | 4390 | 640 | 5310.18 | 4754.67 | 0.229771 | 5.89594 | 26.9683 | 5.40319 | 0.0120918 | 6.62016e-05 | 2.81179e-05 | 1(Win) | true |
| simdjson (ondemand) | 754.578 | 0.0759891 | 1302.33ms | 4390 | 320 | 5688.19 | 5548.31 | 0.0665623 | 6.87342 | 29.7927 | 5.74055 | 0.0127093 | 2.42027e-05 | 5.69476e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1617.76 | 0.0886362 | 1274.77ms | 9378 | 640 | 15367.2 | 5528.36 | 0.059826 | 3.18156 | 14.2372 | 2.7637 | 0.00556289 | 1.09965e-05 | 1.99936e-06 | 1(Win) | true |
| simdjson (ondemand) | 1498.56 | 0.0581513 | 1326.43ms | 9378 | 4890 | 58897.8 | 5968.1 | 0.235668 | 3.4513 | 15.2009 | 2.84112 | 0.0049749 | 6.12537e-05 | 3.10521e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1687.94 | 0.0679057 | 1305.31ms | 9378 | 2560 | 33140.5 | 5298.5 | 0.0630218 | 3.06484 | 13.5826 | 2.61442 | 0.00546887 | 4.92342e-05 | 2.97821e-05 | 1(Win) | true |
| simdjson (ondemand) | 1588.47 | 0.0399119 | 1319.34ms | 9378 | 4890 | 24693.2 | 5630.3 | 0.00546411 | 3.25907 | 14.5049 | 2.68629 | 0.00510984 | 3.93167e-05 | 1.77939e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2579.41 | 0.0441498 | 888.805ms | 4390 | 2560 | 1314.58 | 1623.1 | 0.113386 | 2.04194 | 9.3 | 1.65285 | 0.000886781 | 1.75292e-05 | 3.47024e-06 | 1(Win) | true |
| simdjson (ondemand) | 1942.34 | 0.034684 | 947.587ms | 4390 | 2560 | 1430.8 | 2155.46 | 0.0854293 | 2.68152 | 11.3444 | 1.90456 | 0.00227105 | 3.15881e-05 | 9.87685e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2650.43 | 0.120862 | 896.029ms | 4390 | 4890 | 17823.1 | 1579.6 | 0.0121822 | 1.976 | 9.0021 | 1.58338 | 0.00137499 | 3.04186e-05 | 1.21581e-05 | 1(Win) | true |
| simdjson (ondemand) | 2049.92 | 0.0727963 | 936.106ms | 4390 | 1280 | 2829.33 | 2042.34 | 0.0191992 | 2.55955 | 10.987 | 1.82278 | 0.00294419 | 2.40248e-05 | 4.62699e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4468.18 | 0.119938 | 927.331ms | 9378 | 160 | 922.126 | 2001.61 | 0.00874219 | 1.17622 | 5.4517 | 0.880145 | 0.00085506 | 1.26626e-05 | 6.66453e-06 | 1(Win) | true |
| simdjson (ondemand) | 3804.42 | 0.0723285 | 966.199ms | 9378 | 640 | 1850.31 | 2350.84 | 0.164365 | 1.37615 | 6.00768 | 0.920346 | 0.000937867 | 1.44954e-05 | 1.16629e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4514.44 | 0.0930849 | 927.941ms | 9378 | 640 | 2176.46 | 1981.1 | 0.213676 | 1.14343 | 5.31265 | 0.847622 | 0.0011433 | 1.21628e-05 | 1.99936e-06 | 1(Win) | true |
| simdjson (ondemand) | 3995.51 | 0.0555154 | 957.253ms | 9378 | 160 | 247.072 | 2238.4 | 0.130845 | 1.31268 | 5.84037 | 0.882064 | 0.000907043 | 7.33099e-06 | 1.99936e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1871.54 | 0.122857 | 945.115ms | 4390 | 1280 | 9668.11 | 2237 | 0.260655 | 2.74682 | 13.061 | 2.45786 | 0.00399541 | 3.89735e-05 | 1.33471e-05 | 1(Win) | true |
| simdjson (ondemand) | 1621.83 | 0.0418201 | 985.301ms | 4390 | 2560 | 2983.52 | 2581.43 | 0.0637924 | 3.19876 | 13.8995 | 2.40797 | 0.00470494 | 2.09104e-05 | 1.01438e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1962.27 | 0.274455 | 937.603ms | 4390 | 30 | 1028.67 | 2133.57 | 0.0828721 | 2.62657 | 12.7706 | 2.38838 | 0.00331055 | 3.79651e-05 | 1.5186e-05 | 1(Win) | true |
| simdjson (ondemand) | 1709.59 | 0.0501632 | 974.854ms | 4390 | 320 | 482.911 | 2448.92 | 0.00497644 | 3.0628 | 13.5421 | 2.3262 | 0.00460706 | 4.98292e-06 | 7.11845e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3391.26 | 0.0443939 | 991.692ms | 9378 | 1280 | 1754.51 | 2637.24 | 0.229914 | 1.54274 | 6.99829 | 1.22073 | 0.0022986 | 2.99904e-05 | 1.45787e-05 | 1(Win) | true |
| simdjson (ondemand) | 3207.11 | 0.0917602 | 997.861ms | 9378 | 30 | 196.437 | 2788.67 | 0.0227058 | 1.59957 | 7.1768 | 1.15067 | 0.00150352 | 0 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3544.89 | 0.0403784 | 986.908ms | 9378 | 1280 | 1328.38 | 2522.94 | 0.024457 | 1.47554 | 6.83365 | 1.18245 | 0.00215839 | 6.08139e-06 | 4.16533e-07 | 1(Win) | true |
| simdjson (ondemand) | 3365.64 | 0.0716041 | 985.963ms | 9378 | 80 | 289.635 | 2657.31 | 0.0362077 | 1.55412 | 7.03647 | 1.11772 | 0.00144221 | 5.33163e-06 | 2.66581e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1623.22 | 0.161439 | 999.604ms | 4669 | 80 | 1568.93 | 2743.14 | 0.0770697 | 3.21948 | 12.9218 | 2.61362 | 0.00179642 | 2.67723e-05 | 1.07089e-05 | 1(Win) | true |
| simdjson (ondemand) | 1492.37 | 0.299848 | 1026.34ms | 4669 | 640 | 51224.3 | 2983.65 | 0.00780356 | 3.49698 | 15.0621 | 2.43393 | 0.00140086 | 0.000134531 | 6.25803e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1726.38 | 0.0562873 | 983.578ms | 4669 | 4890 | 10306.3 | 2579.21 | 0.165813 | 3.01444 | 12.1305 | 2.43436 | 0.00173147 | 0.000168321 | 0.000108359 | 1(Win) | true |
| simdjson (ondemand) | 1619.59 | 0.055092 | 1001.97ms | 4669 | 2560 | 5872.95 | 2749.29 | 0.134881 | 3.22687 | 14.2652 | 2.25316 | 0.00141224 | 9.31175e-05 | 6.12417e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2427.33 | 0.129723 | 1042.48ms | 7932 | 40 | 653.733 | 3116.4 | 0.069573 | 2.14972 | 8.36561 | 1.58938 | 0.00105585 | 3.78215e-05 | 1.26072e-05 | 1(Win) | true |
| simdjson (ondemand) | 2410.48 | 0.0923967 | 1043.22ms | 7932 | 1280 | 10761.7 | 3138.19 | 0.340173 | 2.15381 | 9.43318 | 1.45171 | 0.000783811 | 3.63441e-05 | 8.07646e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2594.7 | 0.0763955 | 1030.65ms | 7932 | 320 | 1587.36 | 2915.38 | 0.0812089 | 2.00764 | 7.91427 | 1.48802 | 0.00103418 | 1.5365e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2579.52 | 0.0813847 | 1024.86ms | 7932 | 1280 | 7290.94 | 2932.54 | 0.0913544 | 2.01166 | 8.97781 | 1.34947 | 0.00088191 | 2.35399e-05 | 4.23522e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 623.199 | 0.0353568 | 1439.57ms | 4669 | 2560 | 16337.3 | 7144.92 | 0.117488 | 8.28429 | 37.063 | 7.30392 | 0.00804776 | 7.23689e-05 | 2.84456e-05 | 1(Win) | true |
| simdjson (ondemand) | 239.048 | 0.048427 | 2589.11ms | 4669 | 640 | 52075.4 | 18626.8 | 0.10515 | 21.5303 | 94.6263 | 19.2632 | 0.056246 | 0.000121145 | 6.62615e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 652.121 | 0.0418109 | 1414.72ms | 4669 | 1280 | 10432.3 | 6828.03 | 0.0525226 | 7.92272 | 36.2801 | 7.12551 | 0.00805178 | 3.69793e-05 | 7.52972e-06 | 1(Win) | true |
| simdjson (ondemand) | 243.579 | 0.0438279 | 2569.63ms | 4669 | 640 | 41081.8 | 18280.3 | 0.0749402 | 21.1505 | 93.8362 | 19.0831 | 0.0549499 | 3.88199e-05 | 1.13782e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 942.825 | 0.0406935 | 1527.52ms | 7932 | 1280 | 13644.7 | 8023.28 | 0.112252 | 5.48719 | 23.4244 | 4.59493 | 0.00512471 | 5.68307e-05 | 2.82676e-05 | 1(Win) | true |
| simdjson (ondemand) | 403.033 | 0.0257274 | 2593.55ms | 7932 | 2560 | 59691.9 | 18769.1 | 0.221243 | 12.643 | 55.5677 | 11.2029 | 0.0369385 | 7.65294e-05 | 3.59994e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.844 | 0.101171 | 1507.16ms | 7932 | 40 | 2460.22 | 7751.8 | 0.129694 | 5.30765 | 22.9647 | 4.49054 | 0.0050996 | 4.72769e-05 | 2.20625e-05 | 1(Win) | true |
| simdjson (ondemand) | 410.246 | 0.0497526 | 2569.65ms | 7932 | 640 | 53862.8 | 18439.1 | 0.206285 | 12.5061 | 55.1161 | 11.1004 | 0.0375201 | 3.84124e-05 | 1.73348e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4945.68 | 0.0542839 | 807.356ms | 4669 | 4890 | 1168.01 | 900.321 | 0.0392362 | 1.08261 | 4.92846 | 0.735918 | 0.0010751 | 1.69065e-05 | 5.43111e-06 | 1(Win) | true |
| simdjson (ondemand) | 4389.6 | 0.0331439 | 819.174ms | 4669 | 2560 | 289.365 | 1014.38 | 0.0221475 | 1.21358 | 5.52966 | 0.697794 | 0.00114878 | 2.27565e-05 | 5.18714e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5361.19 | 0.0637504 | 801.022ms | 4669 | 4890 | 1370.88 | 830.544 | 0.0241897 | 1.00262 | 4.68216 | 0.678946 | 0.00089828 | 2.17683e-05 | 8.23427e-06 | 1(Win) | true |
| simdjson (ondemand) | 4722.49 | 0.0342742 | 813.709ms | 4669 | 1280 | 133.675 | 942.873 | 0.0711248 | 1.13391 | 5.27029 | 0.639537 | 0.00111624 | 1.7402e-05 | 1.8406e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6965.05 | 0.0622558 | 826.131ms | 7932 | 2560 | 1170.35 | 1086.07 | 0.0787573 | 0.765663 | 3.49962 | 0.461549 | 0.000630112 | 7.83023e-06 | 1.32966e-06 | 1(Win) | true |
| simdjson (ondemand) | 6529.68 | 0.0579661 | 836.636ms | 7932 | 4890 | 2205.16 | 1158.49 | 0.216248 | 0.810369 | 3.82312 | 0.432426 | 0.000771099 | 1.37673e-05 | 4.89849e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7420.13 | 0.0529163 | 822.09ms | 7932 | 640 | 186.252 | 1019.46 | 0.147661 | 0.721083 | 3.35527 | 0.428013 | 0.000509014 | 6.89454e-06 | 3.54576e-06 | 1(Win) | true |
| simdjson (ondemand) | 6936.1 | 0.0894678 | 832.387ms | 7932 | 1280 | 1218.65 | 1090.6 | 0.0846003 | 0.768883 | 3.67045 | 0.398134 | 0.000743035 | 1.05388e-05 | 5.22015e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3389.25 | 0.0635731 | 848.518ms | 4669 | 4890 | 3411.12 | 1313.77 | 0.328821 | 1.56335 | 7.27843 | 1.31206 | 0.00151484 | 2.90827e-05 | 1.50232e-05 | 1(Win) | true |
| simdjson (ondemand) | 2646.8 | 0.113589 | 886.816ms | 4669 | 40 | 146.062 | 1682.3 | 0.0198102 | 1.99278 | 9.4667 | 1.54851 | 0.00284322 | 6.42536e-05 | 4.28357e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3549.81 | 0.190555 | 841.764ms | 4669 | 640 | 3656.45 | 1254.35 | 0.125096 | 1.49582 | 7.02613 | 1.2538 | 0.00132456 | 1.20475e-05 | 1.33862e-06 | 1(Win) | true |
| simdjson (ondemand) | 2785.48 | 0.0463498 | 881.785ms | 4669 | 160 | 87.8346 | 1598.54 | 0.0442004 | 1.89538 | 9.20732 | 1.49025 | 0.00257282 | 9.37031e-06 | 1.33862e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5000.86 | 0.230126 | 878.252ms | 7932 | 40 | 484.695 | 1512.65 | 0.148967 | 1.0571 | 4.90658 | 0.810136 | 0.000882501 | 9.45537e-06 | 3.15179e-06 | 1(Win) | true |
| simdjson (ondemand) | 4096.4 | 0.141772 | 907.311ms | 7932 | 30 | 205.62 | 1846.63 | 0.0451068 | 1.26233 | 6.12305 | 0.929148 | 0.00173979 | 5.4631e-05 | 8.40477e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5160.34 | 0.185901 | 874.716ms | 7932 | 160 | 1188.2 | 1465.9 | 0.126362 | 1.00729 | 4.7587 | 0.775845 | 0.000828133 | 1.26072e-05 | 9.45537e-06 | 1(Win) | true |
| simdjson (ondemand) | 4380.29 | 0.0402607 | 898.454ms | 7932 | 320 | 154.693 | 1726.95 | 0.16043 | 1.20363 | 5.97037 | 0.894856 | 0.00147228 | 1.4577e-05 | 3.93974e-07 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 601.606 | 0.034832 | 1458.37ms | 4604 | 2560 | 16544.1 | 7298.32 | 0.112926 | 8.54002 | 32.9484 | 6.91996 | 0.0108527 | 8.28084e-05 | 3.47863e-05 | 1(Win) | true |
| simdjson (ondemand) | 570.337 | 0.0854171 | 1503.88ms | 4604 | 640 | 27674.4 | 7698.47 | 0.198811 | 9.06564 | 36.3829 | 6.94353 | 0.0119427 | 0.000252837 | 0.000176138 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.326 | 0.0268785 | 1451.74ms | 4604 | 4890 | 14333.1 | 6369.57 | 0.00523196 | 7.48526 | 28.745 | 5.97004 | 0.00884107 | 0.000116863 | 5.48558e-05 | 1(Win) | true |
| simdjson (ondemand) | 644.411 | 0.0317998 | 1506.11ms | 4604 | 2560 | 12018 | 6813.53 | 0.103497 | 8.02851 | 32.4007 | 6.04192 | 0.0101681 | 7.28816e-05 | 2.94411e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2038.13 | 0.0741322 | 1585.54ms | 18245 | 320 | 12817 | 8537.13 | 0.179808 | 2.53801 | 10.2015 | 2.01551 | 0.0030224 | 7.70759e-06 | 8.56399e-07 | 1(Win) | true |
| simdjson (ondemand) | 2007.61 | 0.0601564 | 1595.03ms | 18245 | 2560 | 69587.5 | 8666.9 | 0.0508457 | 2.57444 | 10.6994 | 1.91068 | 0.00277495 | 4.68664e-05 | 3.53265e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2339.81 | 0.0340139 | 1563.18ms | 18245 | 2560 | 16378.7 | 7436.41 | 0.138152 | 2.1983 | 8.60184 | 1.64377 | 0.00240963 | 3.36779e-05 | 1.84126e-05 | 1(Win) | true |
| simdjson (ondemand) | 2313.52 | 0.0299089 | 1569.36ms | 18245 | 2560 | 12953.3 | 7520.92 | 0.111657 | 2.23017 | 9.19867 | 1.56267 | 0.0025061 | 3.07447e-05 | 1.43661e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 335.888 | 0.0262673 | 2031.6ms | 4604 | 2560 | 30182.4 | 13072 | 0.115052 | 15.3323 | 66.1073 | 14.5241 | 0.0197671 | 0.000431096 | 0.000289151 | 1(Win) | true |
| simdjson (ondemand) | 234.044 | 0.200766 | 2574.69ms | 4604 | 40 | 56743.8 | 18760.2 | 0.232266 | 21.6228 | 105.535 | 22.0936 | 0.0257711 | 0.000135752 | 5.43006e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 361.935 | 0.0251788 | 2030.83ms | 4604 | 2560 | 23884.6 | 12131.2 | 0.101501 | 14.2283 | 61.8254 | 13.5519 | 0.0187972 | 0.000161884 | 9.01051e-05 | 1(Win) | true |
| simdjson (ondemand) | 251.99 | 0.0878504 | 2560.3ms | 4604 | 320 | 74979.2 | 17424.1 | 0.222274 | 20.3118 | 101.165 | 21.1051 | 0.0260025 | 8.82385e-05 | 4.14042e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1214.86 | 0.0717336 | 2170.37ms | 18245 | 1280 | 135110 | 14322.4 | 0.083562 | 4.23077 | 17.7206 | 3.76142 | 0.00482992 | 6.94111e-05 | 4.25202e-05 | 1(Win) | true |
| simdjson (ondemand) | 907.137 | 0.0294846 | 2665.73ms | 18245 | 2560 | 81879.1 | 19181 | 0.0348897 | 5.67276 | 27.5733 | 5.59677 | 0.00619476 | 9.88499e-05 | 7.04388e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.81 | 0.0226761 | 2151.08ms | 18245 | 4890 | 43902.4 | 13213.6 | 0.160308 | 3.90108 | 16.6266 | 3.51335 | 0.00484178 | 3.04983e-05 | 1.54117e-05 | 1(Win) | true |
| simdjson (ondemand) | 969.765 | 0.0794415 | 2624.23ms | 18245 | 320 | 65012.9 | 17942.3 | 0.0392036 | 5.29167 | 26.4867 | 5.35084 | 0.00602391 | 3.57975e-05 | 1.90121e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4276.45 | 0.0484715 | 821.088ms | 4604 | 4890 | 1211.12 | 1026.72 | 0.0352129 | 1.24436 | 6.21986 | 0.990019 | 0.000435116 | 2.28307e-05 | 8.75028e-06 | 1(Win) | true |
| simdjson (ondemand) | 3802.36 | 0.142082 | 835.605ms | 4604 | 30 | 80.754 | 1154.73 | 0.176397 | 1.404 | 7.04974 | 0.978931 | 0.000448885 | 6.51607e-05 | 3.62004e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4403.78 | 0.20263 | 822.52ms | 4604 | 30 | 122.447 | 997.033 | 0.0401029 | 1.21492 | 6.14053 | 0.971329 | 0.000434405 | 7.24008e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3904.2 | 0.0628022 | 835.101ms | 4604 | 2560 | 1277.01 | 1124.61 | 0.0286822 | 1.36199 | 6.96829 | 0.960252 | 0.000435168 | 3.30894e-05 | 1.46781e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10850.2 | 0.0612875 | 878.126ms | 18245 | 320 | 309.108 | 1603.64 | 0.0140325 | 0.486773 | 2.40745 | 0.280789 | 0.00011236 | 6.50863e-06 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 9616.12 | 0.0315934 | 901.825ms | 18245 | 640 | 209.151 | 1809.44 | 0.0444519 | 0.547349 | 2.8028 | 0.284571 | 0.000115614 | 6.67991e-06 | 3.4256e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10977.7 | 0.082944 | 877.716ms | 18245 | 2560 | 4424.61 | 1585.01 | 0.407333 | 0.478118 | 2.3875 | 0.276076 | 0.00011069 | 1.29102e-05 | 4.11072e-06 | 1(Win) | true |
| simdjson (ondemand) | 9774.22 | 0.0366269 | 901.54ms | 18245 | 320 | 136.042 | 1780.17 | 0.0829638 | 0.538785 | 2.78224 | 0.279857 | 0.000112702 | 1.31885e-05 | 2.91176e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2414.75 | 0.079607 | 900.884ms | 4604 | 4890 | 10245.6 | 1818.29 | 0.28037 | 2.17786 | 9.22719 | 1.73002 | 0.00109423 | 3.50011e-05 | 1.95882e-05 | 1(Win) | true |
| simdjson (ondemand) | 2229.17 | 0.152394 | 914.803ms | 4604 | 30 | 270.299 | 1969.67 | 0.00169236 | 2.35817 | 13.3732 | 2.37467 | 0.000984651 | 2.17202e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2503.16 | 0.128324 | 897.549ms | 4604 | 2560 | 12970.2 | 1754.07 | 0.0573781 | 2.09011 | 9.1477 | 1.7109 | 0.00108966 | 1.59508e-05 | 2.88472e-06 | 1(Win) | true |
| simdjson (ondemand) | 2251.23 | 0.0793351 | 922.524ms | 4604 | 30 | 71.8264 | 1950.37 | 0.0887933 | 2.33592 | 13.2921 | 2.35599 | 0.00126701 | 0.000166522 | 0.000137562 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7591.45 | 0.0528932 | 952.781ms | 18245 | 4890 | 7186.98 | 2292.02 | 0.170152 | 0.68516 | 3.16839 | 0.468734 | 0.000279282 | 1.4033e-05 | 4.59548e-06 | 1(Win) | true |
| simdjson (ondemand) | 6577.94 | 0.032681 | 986.619ms | 18245 | 4890 | 3654.34 | 2645.17 | 0.11744 | 0.792717 | 4.39819 | 0.636613 | 0.000240534 | 7.92441e-06 | 9.19097e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7868.09 | 0.430655 | 948.037ms | 18245 | 80 | 7256.02 | 2211.44 | 0.0469372 | 0.666822 | 3.14853 | 0.463908 | 0.000303508 | 8.22143e-06 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 6687.26 | 0.0392519 | 981.115ms | 18245 | 2560 | 2670.26 | 2601.93 | 0.012249 | 0.782691 | 4.37775 | 0.631899 | 0.0002299 | 1.74919e-05 | 6.82978e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.09 | 0.0589188 | 1051.61ms | 4926 | 640 | 2394.11 | 3282.68 | 0.00157072 | 3.64371 | 15.5514 | 3.01198 | 0.00367819 | 2.79131e-05 | 5.7095e-06 | 1(Win) | true |
| simdjson (ondemand) | 1073.7 | 0.0347299 | 1163.8ms | 4926 | 2560 | 5911.15 | 4375.35 | 0.0565795 | 4.83893 | 18.5051 | 3.43402 | 0.00473682 | 7.50165e-05 | 2.86268e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1769.7 | 0.0444659 | 1027.46ms | 4926 | 4890 | 6813.2 | 2654.57 | 0.00787415 | 2.95317 | 12.9586 | 2.44214 | 0.00347868 | 4.08915e-05 | 1.40733e-05 | 1(Win) | true |
| simdjson (ondemand) | 1266.51 | 0.107838 | 1137.66ms | 4926 | 320 | 5119.91 | 3709.25 | 0.0275569 | 4.11086 | 15.9068 | 2.86216 | 0.00532823 | 4.88479e-05 | 1.64941e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2206.84 | 0.0544843 | 1085.83ms | 8150 | 1280 | 4713.29 | 3521.97 | 0.0123348 | 2.35939 | 10.0956 | 1.8535 | 0.0022985 | 4.11235e-05 | 1.7638e-05 | 1(Win) | true |
| simdjson (ondemand) | 1696.03 | 0.130882 | 1189.16ms | 8150 | 80 | 2878.07 | 4582.74 | 0.235402 | 3.0637 | 11.7348 | 2.0989 | 0.00282055 | 3.37423e-05 | 1.53374e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2691.92 | 0.0742952 | 1054.29ms | 8150 | 4890 | 22501.9 | 2887.32 | 0.126273 | 1.93421 | 8.5319 | 1.50982 | 0.0023767 | 3.50032e-05 | 1.01873e-05 | 1(Win) | true |
| simdjson (ondemand) | 1988.77 | 0.0723737 | 1158.14ms | 8150 | 1280 | 10240.4 | 3908.17 | 0.0275789 | 2.5867 | 10.1644 | 1.75325 | 0.00332899 | 5.05176e-05 | 1.8309e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 864.994 | 0.0466312 | 1266.34ms | 4926 | 2560 | 16419.4 | 5431.02 | 0.106522 | 5.99602 | 26.5826 | 5.27548 | 0.00962154 | 0.00012775 | 7.08137e-05 | 1(Win) | true |
| simdjson (ondemand) | 464.937 | 0.0263926 | 1737.05ms | 4926 | 4890 | 34775.5 | 10104.2 | 0.0290615 | 11.073 | 45.4415 | 9.07329 | 0.0272874 | 0.000221271 | 0.000133012 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 985.403 | 0.043419 | 1237.99ms | 4926 | 1280 | 5484.43 | 4767.39 | 0.0110955 | 5.26997 | 23.9896 | 4.70443 | 0.00973628 | 5.99498e-05 | 2.61685e-05 | 1(Win) | true |
| simdjson (ondemand) | 502.485 | 0.0821404 | 1702.08ms | 4926 | 640 | 37743 | 9349.14 | 0.0379737 | 10.2453 | 42.8488 | 8.50345 | 0.0269323 | 4.69448e-05 | 1.26878e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1311.06 | 0.0702746 | 1315.73ms | 8150 | 160 | 2777.08 | 5928.38 | 0.184889 | 3.95592 | 16.9772 | 3.33509 | 0.00628911 | 9.89264e-05 | 5.44479e-05 | 1(Win) | true |
| simdjson (ondemand) | 776.795 | 0.0629785 | 1733.41ms | 8150 | 320 | 12706.8 | 10005.8 | 0.00596494 | 6.6539 | 27.7747 | 5.45473 | 0.0142742 | 4.33282e-05 | 1.61043e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1485.55 | 0.0615678 | 1290.61ms | 8150 | 160 | 1660.22 | 5232.02 | 0.00704845 | 3.4957 | 15.4101 | 2.98969 | 0.0061273 | 5.06135e-05 | 2.30061e-05 | 1(Win) | true |
| simdjson (ondemand) | 834.454 | 0.04279 | 1693.85ms | 8150 | 1280 | 20333.2 | 9314.41 | 0.0488645 | 6.1614 | 26.2039 | 5.10884 | 0.0136956 | 8.10966e-05 | 4.71626e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2847.88 | 0.156884 | 886.646ms | 4926 | 40 | 267.892 | 1649.58 | 0.309724 | 1.81883 | 8.11206 | 1.45554 | 0.000553187 | 3.04507e-05 | 3.04507e-05 | 1(Win) | true |
| simdjson (ondemand) | 2186.16 | 0.0420117 | 949.099ms | 4926 | 320 | 260.803 | 2148.88 | 0.0762897 | 2.40043 | 9.94072 | 1.64251 | 0.00131636 | 1.71285e-05 | 1.26878e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3202.76 | 0.0882647 | 888.091ms | 4926 | 320 | 536.369 | 1466.8 | 0.0889205 | 1.6441 | 7.54689 | 1.3175 | 0.00112033 | 2.41068e-05 | 5.07511e-06 | 1(Win) | true |
| simdjson (ondemand) | 2344.58 | 0.0368746 | 929.574ms | 4926 | 2560 | 1397.51 | 2003.69 | 0.00257332 | 2.2514 | 9.36947 | 1.50345 | 0.00185075 | 3.14023e-05 | 1.36394e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4061.65 | 0.0960647 | 909.379ms | 8150 | 160 | 540.703 | 1913.62 | 0.137036 | 1.27391 | 5.63804 | 0.93816 | 0.000657975 | 9.96933e-06 | 4.60123e-06 | 1(Win) | true |
| simdjson (ondemand) | 3389.58 | 0.0450873 | 950.102ms | 8150 | 4890 | 5226.86 | 2293.04 | 0.126234 | 1.53749 | 6.44479 | 0.990675 | 0.000954897 | 2.41133e-05 | 8.0545e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4519.8 | 0.0913908 | 902.384ms | 8150 | 160 | 395.187 | 1719.64 | 0.0498171 | 1.16633 | 5.30049 | 0.854724 | 0.000931748 | 9.96933e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3661.59 | 0.0518414 | 940.157ms | 8150 | 4890 | 5921.6 | 2122.7 | 0.0464286 | 1.43196 | 6.09951 | 0.906626 | 0.000975222 | 3.84157e-05 | 2.05252e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2099.41 | 0.0356133 | 943.194ms | 4926 | 4890 | 3105.48 | 2237.67 | 0.115935 | 2.49115 | 11.3634 | 2.16058 | 0.00260543 | 2.75654e-05 | 9.71432e-06 | 1(Win) | true |
| simdjson (ondemand) | 1476.1 | 0.0449719 | 1040.6ms | 4926 | 1280 | 2622.11 | 3182.58 | 0.00574449 | 3.53177 | 14.0069 | 2.49899 | 0.00714671 | 2.41068e-05 | 1.0626e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2232.53 | 0.0577057 | 938.233ms | 4926 | 2560 | 3774.6 | 2104.25 | 0.025704 | 2.34813 | 10.7605 | 2.01583 | 0.00354885 | 2.80717e-05 | 1.31636e-05 | 1(Win) | true |
| simdjson (ondemand) | 1559.08 | 0.0289826 | 1032.95ms | 4926 | 320 | 244.05 | 3013.19 | 0.00933308 | 3.34852 | 13.4015 | 2.35323 | 0.00727771 | 5.7095e-06 | 6.34389e-07 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3112.53 | 0.0593707 | 971.711ms | 8150 | 2560 | 5626.95 | 2497.15 | 0.00550659 | 1.67668 | 7.53975 | 1.35742 | 0.00184131 | 2.5115e-05 | 7.62078e-06 | 1(Win) | true |
| simdjson (ondemand) | 2375.88 | 0.115089 | 1051.2ms | 8150 | 40 | 567.015 | 3271.4 | 0.103823 | 2.19604 | 8.94049 | 1.51693 | 0.00414724 | 4.90798e-05 | 1.53374e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3287.43 | 0.0622489 | 964.965ms | 8150 | 1280 | 2772.52 | 2364.29 | 0.124816 | 1.5732 | 7.17546 | 1.26994 | 0.00233762 | 7.95629e-06 | 9.58589e-08 | 1(Win) | true |
| simdjson (ondemand) | 2559.15 | 0.0923656 | 1041.7ms | 8150 | 40 | 314.779 | 3037.12 | 0.0551204 | 2.07668 | 8.5746 | 1.42883 | 0.00421472 | 1.53374e-05 | 9.20245e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2345.27 | 0.124275 | 838.683ms | 2821 | 40 | 81.2917 | 1147.12 | 0.0442941 | 2.26964 | 8.134 | 1.45445 | 0.000850762 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2039.06 | 0.118793 | 852.445ms | 2821 | 1280 | 3144.39 | 1319.39 | 0.215839 | 2.60261 | 9.42467 | 1.54839 | 0.000360854 | 5.5942e-05 | 1.93859e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2626.36 | 0.0683711 | 832.928ms | 2821 | 160 | 78.4805 | 1024.35 | 0 | 2.03609 | 7.57249 | 1.30946 | 0.000381071 | 2.21553e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2147.2 | 0.0822517 | 850.224ms | 2821 | 2560 | 2718.88 | 1252.94 | 0.0123787 | 2.46768 | 9.04927 | 1.45197 | 0.000361408 | 4.84646e-05 | 9.96987e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2846.23 | 0.143864 | 845.736ms | 3770 | 1280 | 4227.26 | 1263.2 | 0.199917 | 1.86569 | 6.8037 | 1.14514 | 0.000543352 | 0.000101749 | 4.04095e-05 | 1(Win) | true |
| simdjson (ondemand) | 2616.41 | 0.094904 | 857.125ms | 3770 | 2560 | 4353.92 | 1374.16 | 0.0818866 | 2.01933 | 7.45783 | 1.18435 | 0.000272091 | 4.28962e-05 | 8.49635e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3126.19 | 0.153295 | 839.052ms | 3770 | 40 | 124.328 | 1150.08 | 0.0732372 | 1.70612 | 6.43183 | 1.04881 | 0.000530504 | 1.32626e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2762.96 | 0.0724276 | 858.044ms | 3770 | 160 | 142.122 | 1301.27 | 0.00240156 | 1.92181 | 7.13369 | 1.10292 | 0.000530504 | 2.32095e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 850.354 | 0.0453152 | 1044.66ms | 2821 | 4890 | 10050.9 | 3163.76 | 0.874496 | 6.07642 | 25.0216 | 4.56363 | 0.00443881 | 0.000119974 | 5.61085e-05 | 1(Win) | true |
| simdjson (ondemand) | 386.358 | 0.0326725 | 1418.57ms | 2821 | 4890 | 25310.5 | 6963.28 | 0.00587931 | 13.3188 | 58.9234 | 11.9007 | 0.00732992 | 0.000184926 | 9.25719e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.473 | 0.0352467 | 1028.69ms | 2821 | 4890 | 5545.11 | 3021.22 | 0.153789 | 5.82396 | 24.4669 | 4.42219 | 0.0042665 | 5.12516e-05 | 1.42084e-05 | 1(Win) | true |
| simdjson (ondemand) | 392.067 | 0.0186135 | 1411.77ms | 2821 | 4890 | 7977.2 | 6861.88 | 0.0353762 | 13.1939 | 58.4885 | 11.7909 | 0.00834879 | 7.11868e-05 | 1.7398e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1076.07 | 0.12743 | 1060ms | 3770 | 80 | 1450.22 | 3341.18 | 0.0583287 | 4.84466 | 19.7491 | 3.62255 | 0.00243037 | 9.94695e-05 | 7.29443e-05 | 1(Win) | true |
| simdjson (ondemand) | 529.502 | 0.14969 | 1409.39ms | 3770 | 30 | 3099.24 | 6790.07 | 0.317591 | 9.7752 | 43.7796 | 8.76525 | 0.00768347 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1109.65 | 0.107737 | 1054.26ms | 3770 | 320 | 3899.31 | 3240.07 | 0.016206 | 4.70142 | 19.3332 | 3.51671 | 0.00246021 | 5.80239e-05 | 2.65252e-05 | 1(Win) | true |
| simdjson (ondemand) | 527.021 | 0.0554092 | 1409.59ms | 3770 | 640 | 9144.73 | 6822.03 | 0.0382868 | 9.82692 | 43.4554 | 8.68356 | 0.00891868 | 9.03515e-05 | 5.42938e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6181.44 | 0.118874 | 757.24ms | 2821 | 2560 | 685.244 | 435.225 | 0.0502866 | 0.904811 | 3.60759 | 0.4743 | 0.000588222 | 3.62792e-05 | 1.50933e-05 | 1(Win) | true |
| simdjson (ondemand) | 5143.85 | 0.0600588 | 766.104ms | 2821 | 2560 | 252.594 | 523.016 | 0.135373 | 1.07754 | 4.14179 | 0.454449 | 0.000434797 | 2.43708e-05 | 5.26188e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6176.93 | 0.060612 | 760.826ms | 2821 | 640 | 44.6023 | 435.542 | 0.287247 | 0.908811 | 3.53527 | 0.45693 | 0.00106345 | 9.96987e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5285.37 | 0.0990405 | 771.562ms | 2821 | 2560 | 650.611 | 509.012 | 0.0276961 | 1.04901 | 4.067 | 0.437079 | 0.000465676 | 3.39252e-05 | 9.8314e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6950.44 | 0.0835899 | 765.42ms | 3770 | 640 | 119.659 | 517.284 | 0.0217529 | 0.794894 | 3.16764 | 0.377719 | 0.00050688 | 4.97347e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6279.89 | 0.0710866 | 771.963ms | 3770 | 4890 | 809.958 | 572.518 | 0.112231 | 0.875359 | 3.46048 | 0.354908 | 0.000417189 | 1.43204e-05 | 3.52584e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7136.74 | 0.0728565 | 763.179ms | 3770 | 2560 | 344.874 | 503.781 | 0.0365341 | 0.780264 | 3.11353 | 0.364722 | 0.000500145 | 1.51277e-05 | 2.48674e-06 | 1(Win) | true |
| simdjson (ondemand) | 6464.7 | 0.0435704 | 774.14ms | 3770 | 2560 | 150.318 | 556.152 | 0.270103 | 0.854139 | 3.40451 | 0.34191 | 0.000470304 | 1.34698e-05 | 2.1759e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4530.39 | 0.14033 | 778.26ms | 2821 | 80 | 55.5555 | 593.837 | 0.0315843 | 1.21228 | 5.23467 | 0.850408 | 0.000722262 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3654.83 | 0.125899 | 786.522ms | 2821 | 2560 | 2198.64 | 736.098 | 0.142494 | 1.48777 | 6.26161 | 0.916342 | 0.000721015 | 3.04635e-05 | 1.30162e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4584.7 | 0.124917 | 782.997ms | 2821 | 640 | 343.88 | 586.803 | 0.100753 | 1.19566 | 5.16164 | 0.832683 | 0.000930521 | 1.10776e-05 | 2.21553e-06 | 1(Win) | true |
| simdjson (ondemand) | 3712.59 | 0.0799625 | 792.891ms | 2821 | 4890 | 1641.85 | 724.647 | 0.147651 | 1.46376 | 6.18681 | 0.898972 | 0.000737385 | 5.1904e-05 | 3.07365e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5197.05 | 0.0310024 | 783.442ms | 3770 | 2560 | 117.761 | 691.807 | 0.109039 | 1.04609 | 4.387 | 0.66366 | 0.000795756 | 1.91686e-05 | 3.73011e-06 | 1(Win) | true |
| simdjson (ondemand) | 4538.9 | 0.0488938 | 796.453ms | 3770 | 640 | 95.9996 | 792.12 | 0.0297767 | 1.19263 | 5.05676 | 0.702653 | 0.000549983 | 1.40915e-05 | 8.28912e-07 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5424.62 | 0.11978 | 784.362ms | 3770 | 320 | 201.681 | 662.784 | 0.026868 | 1.02327 | 4.33289 | 0.650398 | 0.000864556 | 2.40385e-05 | 7.46021e-06 | 1(Win) | true |
| simdjson (ondemand) | 4654.19 | 0.043351 | 795.639ms | 3770 | 1280 | 143.55 | 772.498 | 0.102755 | 1.16096 | 5.0008 | 0.689655 | 0.000602619 | 2.73541e-05 | 7.87467e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5857.27 | 0.124306 | 5285.27ms | 277673 | 640 | 2.02135e+06 | 45210.4 | 0.106311 | 0.873904 | 3.87618 | 0.653348 | 0.00433848 | 2.77417e-06 | 1.64875e-06 | 1(Win) | true |
| simdjson (ondemand) | 4625.56 | 0.0467298 | 6465.95ms | 277673 | 1280 | 916086 | 57249.2 | 0.152242 | 1.10927 | 4.46623 | 0.711352 | 0.00327831 | 4.21471e-06 | 2.75729e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4678.06 | 0.522819 | 6630.86ms | 10548466 | 80 | 1.01121e+10 | 2.15042e+06 | 0.173301 | 1.08954 | 3.87583 | 0.65398 | 0.0107521 | 0.0174676 | 0.00027915 | 1(Win) | true |
| simdjson (ondemand) | 4036.19 | 0.190632 | 7806.35ms | 10548466 | 40 | 9.02998e+08 | 2.4924e+06 | 0.157699 | 1.26253 | 4.46385 | 0.711749 | 0.00862894 | 0.017463 | 0.000261382 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4032.03 | 0.099134 | 5755.54ms | 16002592 | 80 | 1.12634e+09 | 3.78501e+06 | 0.627166 | 1.25993 | 7.26215 | 1.1795 | 0.000766624 | 0.0340308 | 0.00335143 | 1(Win) | true |
| simdjson (ondemand) | 3193.94 | 0.118966 | 7223.64ms | 16002592 | 80 | 2.58503e+09 | 4.77819e+06 | 0.355281 | 1.59263 | 7.89645 | 1.14061 | 0.00109928 | 0.0354533 | 0.00608882 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3652.69 | 0.0898066 | 6315.54ms | 16002591 | 80 | 1.12632e+09 | 4.17809e+06 | 0.34156 | 1.38866 | 7.36923 | 1.25497 | 0.000741205 | 0.0368899 | 0.00454233 | 1(Win) | true |
| simdjson (ondemand) | 1692.75 | 0.103376 | 6330.9ms | 16002591 | 40 | 3.47453e+09 | 9.01567e+06 | 0.197511 | 2.99388 | 12.8736 | 2.68263 | 0.00108281 | 0.0522841 | 0.0114285 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 20365.3 | 0.109214 | 9813.28ms | 16197086 | 640 | 4.39169e+08 | 758482 | 0.156866 | 0.248277 | 1.24513 | 0.0695898 | 5.80092e-05 | 0.0157148 | 0.000268948 | 1(Win) | true |
| simdjson (ondemand) | 17597.4 | 0.712512 | 5679.16ms | 16197086 | 80 | 3.12934e+09 | 877787 | 0.270667 | 0.286532 | 1.33582 | 0.0730644 | 8.54189e-05 | 0.0157224 | 0.00025423 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 19691.7 | 0.170098 | 10209.8ms | 16197085 | 320 | 5.69711e+08 | 784430 | 0.0206043 | 0.258602 | 1.2466 | 0.0707847 | 7.00693e-05 | 0.0157375 | 0.000656157 | 1(Win) | true |
| simdjson (ondemand) | 14219.8 | 0.799809 | 6909.75ms | 16197085 | 160 | 1.20775e+10 | 1.08628e+06 | 1.8394 | 0.356302 | 1.4183 | 0.0987389 | 9.47705e-05 | 0.015752 | 0.0030645 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1980.38 | 0.721877 | 8152.41ms | 4212000 | 40 | 8.57569e+09 | 2.02834e+06 | 0.736056 | 2.54993 | 10.8643 | 1.97769 | 0.0137817 | 0.0666297 | 0.0113668 | 1(Win) | true |
| simdjson (ondemand) | 1545.66 | 0.0908918 | 9980.17ms | 4212000 | 160 | 8.92733e+08 | 2.59882e+06 | 0.105377 | 3.28282 | 12.612 | 2.34621 | 0.0132072 | 0.0668903 | 0.00458646 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1889.19 | 0.161736 | 8531.68ms | 4211999 | 80 | 9.46084e+08 | 2.12625e+06 | 0.0669097 | 2.68026 | 11.672 | 2.16574 | 0.0143197 | 0.0680555 | 0.00447582 | 1(Win) | true |
| simdjson (ondemand) | 1278.07 | 0.187542 | 5639.21ms | 4211999 | 30 | 1.04228e+09 | 3.14292e+06 | 0.667953 | 3.97235 | 15.0855 | 3.11354 | 0.0133936 | 0.0687568 | 0.00901749 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1527.26 | 1.03924 | 10065.5ms | 4212000 | 80 | 5.97684e+10 | 2.63012e+06 | 0.000860221 | 3.31267 | 14.8801 | 2.8142 | 0.0147777 | 0.0667061 | 0.00273702 | 1(Win) | true |
| simdjson (ondemand) | 1276.87 | 0.82734 | 5644.75ms | 4212000 | 80 | 5.4193e+10 | 3.14588e+06 | 0.130368 | 3.95838 | 15.6867 | 2.92005 | 0.0143408 | 0.0661845 | 0.0040094 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1569.54 | 0.213158 | 9936.71ms | 4211999 | 160 | 4.76163e+09 | 2.55928e+06 | 1.18544 | 3.22073 | 14.9768 | 2.84322 | 0.0149651 | 0.0681938 | 0.00481293 | 1(Win) | true |
| simdjson (ondemand) | 1110.66 | 0.353514 | 6347.17ms | 4211999 | 80 | 1.30773e+10 | 3.61666e+06 | 0.334832 | 4.57465 | 18.1602 | 3.68737 | 0.0143897 | 0.0685196 | 0.00483293 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1693.55 | 0.128102 | 8757.08ms | 4525120 | 80 | 8.52435e+08 | 2.54819e+06 | 0.374522 | 2.9748 | 14.9125 | 2.63894 | 0.00995906 | 0.0769634 | 0.00229837 | 1(Win) | true |
| simdjson (ondemand) | 1348.83 | 0.115769 | 5176.89ms | 4525120 | 80 | 1.09754e+09 | 3.19944e+06 | 0.275134 | 3.73654 | 16.265 | 2.70299 | 0.0148897 | 0.0765659 | 0.00492462 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1382.03 | 1.1458 | 10369.7ms | 4525119 | 160 | 2.04816e+11 | 3.12258e+06 | 1.30776 | 3.68022 | 17.1258 | 3.19207 | 0.0104373 | 0.0774004 | 0.0051814 | 1(Win) | true |
| simdjson (ondemand) | 897.096 | 2.01765 | 7754.24ms | 4525119 | 30 | 2.82615e+11 | 4.81051e+06 | 0.0992653 | 5.64951 | 21.4765 | 4.24757 | 0.0177299 | 0.093125 | 0.00887265 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 855.354 | 0.146346 | 8144.06ms | 4525120 | 40 | 2.18068e+09 | 5.04527e+06 | 0.264575 | 5.95488 | 30.1097 | 6.04114 | 0.015385 | 0.077707 | 0.00491607 | 1(Win) | true |
| simdjson (ondemand) | 594.918 | 0.715874 | 5298.85ms | 4525120 | 30 | 8.08986e+10 | 7.25393e+06 | 0.0214798 | 8.52668 | 41.2329 | 8.13681 | 0.0254736 | 0.0767877 | 0.00884657 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 836.367 | 0.685982 | 8144.66ms | 4525119 | 40 | 5.01132e+10 | 5.15981e+06 | 0.0635479 | 6.06042 | 29.8375 | 6.04081 | 0.0152137 | 0.0776647 | 0.00514352 | 1(Win) | true |
| simdjson (ondemand) | 512.241 | 0.109227 | 6136.65ms | 4525119 | 30 | 2.54035e+09 | 8.42472e+06 | 0.179411 | 9.87359 | 46.4446 | 9.68143 | 0.028571 | 0.0929257 | 0.0122164 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1395.04 | 0.12148 | 9745.85ms | 4203059 | 160 | 1.94934e+09 | 2.8733e+06 | 1.58757 | 3.62668 | 16.6409 | 3.12536 | 0.0160329 | 0.0887071 | 0.00494235 | 1(Win) | true |
| simdjson (ondemand) | 1055.73 | 0.649438 | 6081.23ms | 4203059 | 80 | 4.86396e+10 | 3.79675e+06 | 0.0646832 | 4.83279 | 18.7597 | 3.51749 | 0.0223546 | 0.0867709 | 0.0134118 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.74 | 0.247181 | 5219.7ms | 4203058 | 40 | 2.53434e+09 | 3.22023e+06 | 0.0988524 | 4.08735 | 18.7647 | 3.65723 | 0.0179653 | 0.0882267 | 0.0061206 | 1(Win) | true |
| simdjson (ondemand) | 816.907 | 0.55472 | 7846.83ms | 4203058 | 80 | 5.92684e+10 | 4.90673e+06 | 0.444077 | 6.22378 | 23.8699 | 5.08231 | 0.0237008 | 0.102231 | 0.0076509 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 861.394 | 0.795445 | 7542.89ms | 4203059 | 30 | 4.11026e+10 | 4.65333e+06 | 0.250616 | 5.91705 | 26.7813 | 5.3214 | 0.0242149 | 0.0878765 | 0.00779063 | 1(Win) | true |
| simdjson (ondemand) | 771.712 | 0.484831 | 8215.9ms | 4203059 | 80 | 5.0733e+10 | 5.1941e+06 | 0.12438 | 6.5763 | 26.5741 | 5.07451 | 0.0265552 | 0.0866345 | 0.00838048 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 788.067 | 0.489513 | 8043.83ms | 4203058 | 80 | 4.95934e+10 | 5.08631e+06 | 0.715849 | 6.43303 | 28.9071 | 5.85404 | 0.0265158 | 0.0878439 | 0.00826147 | 1(Win) | true |
| simdjson (ondemand) | 627.597 | 0.491469 | 9946.24ms | 4203058 | 80 | 7.88227e+10 | 6.38682e+06 | 0.43944 | 8.06609 | 31.6824 | 6.63862 | 0.0279044 | 0.102578 | 0.014133 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1747.43 | 0.878021 | 7427.62ms | 4197496 | 160 | 6.4731e+10 | 2.29082e+06 | 0.278789 | 2.90148 | 13.9713 | 2.72555 | 0.000461613 | 0.0814967 | 0.00212511 | 1(Win) | true |
| simdjson (ondemand) | 1498.85 | 0.770977 | 8760.53ms | 4197496 | 160 | 6.78367e+10 | 2.67074e+06 | 0.690954 | 3.3741 | 16.4865 | 2.65769 | 0.00577512 | 0.0804483 | 0.00342488 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1603.15 | 0.929966 | 8187.34ms | 4197495 | 80 | 4.31374e+10 | 2.49698e+06 | 0.858708 | 3.16102 | 15.9897 | 3.22267 | 0.000590114 | 0.083982 | 0.0034049 | 1(Win) | true |
| simdjson (ondemand) | 982.558 | 0.947636 | 6306.67ms | 4197495 | 80 | 1.19244e+11 | 4.0741e+06 | 0.172757 | 5.16295 | 22.1783 | 4.43516 | 0.0063186 | 0.1016 | 0.00452015 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 999.309 | 1.26599 | 6296.83ms | 4197496 | 30 | 7.71548e+10 | 4.00581e+06 | 0.539516 | 5.05473 | 26.5731 | 5.3455 | 0.000865992 | 0.081751 | 0.0045747 | 1(Win) | true |
| simdjson (ondemand) | 808.27 | 0.690842 | 7669.42ms | 4197496 | 80 | 9.36515e+10 | 4.95261e+06 | 0.000876062 | 6.26723 | 30.2381 | 5.3241 | 0.0090409 | 0.0812039 | 0.00561431 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 983.358 | 1.1078 | 6262.22ms | 4197495 | 40 | 8.1346e+10 | 4.07079e+06 | 0.221411 | 5.14799 | 26.5403 | 5.39731 | 0.00120321 | 0.0840136 | 0.00513591 | 1(Win) | true |
| simdjson (ondemand) | 638.461 | 0.53224 | 9603.69ms | 4197495 | 80 | 8.90875e+10 | 6.26983e+06 | 0.0932383 | 7.94165 | 35.9299 | 7.10156 | 0.00971605 | 0.102242 | 0.00744842 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1558.06 | 0.952214 | 10334.6ms | 4506447 | 80 | 5.51903e+10 | 2.75836e+06 | 1.54081 | 3.25234 | 14.5981 | 2.72773 | 0.0125619 | 0.080494 | 0.00708423 | 1(Win) | true |
| simdjson (ondemand) | 1202.55 | 0.230054 | 6314.73ms | 4506447 | 80 | 5.40767e+09 | 3.5738e+06 | 0.200753 | 4.22315 | 17.1187 | 3.13833 | 0.0126854 | 0.078568 | 0.0149748 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1434.1 | 0.191184 | 5330.88ms | 4506446 | 30 | 9.84767e+08 | 2.99679e+06 | 0.601264 | 3.52344 | 16.2308 | 3.13803 | 0.0150526 | 0.0809298 | 0.0100393 | 1(Win) | true |
| simdjson (ondemand) | 935.198 | 0.0928622 | 7789.68ms | 4506446 | 80 | 1.4569e+09 | 4.59548e+06 | 0.368008 | 5.42757 | 21.1824 | 4.39851 | 0.0126638 | 0.0866026 | 0.0100791 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 925.92 | 0.0926076 | 7733.21ms | 4506447 | 40 | 7.39051e+08 | 4.64153e+06 | 0.0118711 | 5.47292 | 25.8845 | 5.15829 | 0.0181677 | 0.0809867 | 0.00575555 | 1(Win) | true |
| simdjson (ondemand) | 521.025 | 0.0730612 | 6163.07ms | 4506447 | 40 | 1.45273e+09 | 8.24852e+06 | 0.304216 | 9.72552 | 40.0712 | 7.89224 | 0.0332616 | 0.0786556 | 0.00770322 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 929.607 | 0.0883033 | 7771.15ms | 4506446 | 80 | 1.33325e+09 | 4.62312e+06 | 0.403592 | 5.48698 | 25.7063 | 5.16589 | 0.0180281 | 0.0811166 | 0.00433917 | 1(Win) | true |
| simdjson (ondemand) | 467.61 | 0.109363 | 6797.36ms | 4506446 | 40 | 4.04115e+09 | 9.19073e+06 | 0.219811 | 10.8918 | 44.1346 | 9.15229 | 0.0334735 | 0.0865945 | 0.0134371 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2009.15 | 0.0845229 | 7014.91ms | 4219120 | 160 | 4.58447e+08 | 2.00267e+06 | 0.126629 | 2.51495 | 8.88729 | 1.52469 | 0.0168366 | 0.0533348 | 0.0020128 | 1(Win) | true |
| simdjson (ondemand) | 1852.32 | 0.120442 | 7607.32ms | 4219120 | 80 | 5.47591e+08 | 2.17223e+06 | 0.361027 | 2.71101 | 9.38762 | 1.53463 | 0.0148696 | 0.0534671 | 0.00149411 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1876.92 | 0.151901 | 7494.37ms | 4219119 | 40 | 4.24163e+08 | 2.14376e+06 | 0.422403 | 2.71435 | 9.89982 | 1.7788 | 0.0170837 | 0.0525873 | 0.000782343 | 1(Win) | true |
| simdjson (ondemand) | 1441.9 | 0.279191 | 9627.26ms | 4219119 | 160 | 9.71175e+09 | 2.79054e+06 | 0.434831 | 3.50538 | 11.8307 | 2.29378 | 0.0170893 | 0.0550427 | 0.00157646 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 771.051 | 0.0950985 | 8381.2ms | 4219120 | 80 | 1.97022e+09 | 5.21842e+06 | 1.55184 | 6.58761 | 26.1127 | 4.7654 | 0.0222817 | 0.0535131 | 0.00304413 | 1(Win) | true |
| simdjson (ondemand) | 316.305 | 0.134053 | 9214.54ms | 4219120 | 40 | 1.16318e+10 | 1.27208e+07 | 0.695013 | 16.017 | 61.8949 | 12.5267 | 0.0878033 | 0.0539878 | 0.015391 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 771.561 | 0.099353 | 8375.88ms | 4219119 | 40 | 1.0738e+09 | 5.21497e+06 | 0.109103 | 6.58214 | 25.9953 | 4.76856 | 0.0218879 | 0.0535487 | 0.0044414 | 1(Win) | true |
| simdjson (ondemand) | 303.241 | 0.080399 | 9566.13ms | 4219119 | 30 | 3.41421e+09 | 1.32689e+07 | 0.174243 | 16.6942 | 64.3369 | 13.2857 | 0.0890498 | 0.0552536 | 0.0171624 | 2(Loss) | true |
