# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Windows 10.0.26100 using the MSVC 19.52.37029.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [5f487ec](https://github.com/nihilai-collective/Jsonifier/commit/5f487ec)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX512` |
| **simdjson (ondemand)** | `icelake` |
| **Glaze** | utf8: `AVX512BW`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX512BW` |

> **How the sampling/convergence works (AMD EPYC 9V45 96-Core Processor-AVX512):**  
> The iterations grow geometrically (100 → 200 → 400 ...) up to a max of 100000.  
> Scores come from a trailing window of `max(iterations/10, 30)` (capped at 100000) over at most 5s.  
> The epoch that counts is whichever one has the lowest (RSE + epoch-over-epoch mean shift).  
> Converged means RSE ≤ 5% and mean shift ≤ 2.5%. Ties get called using Welch's t-test with Bessel-corrected variance.

---

##### The Test Variants
* **Standard vs. (Reused):** Standard builds, parses/serializes, and tears everything down every iteration. `(Reused)` keeps the buffer/object around across iterations and clears it outside the timed region, so you just see the raw parse/format throughput.
* **Document Sizes:** "Small" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`), so dispatch/setup/small-alloc latency dominates instead of bulk SIMD throughput.
* **Key Traversal Order:** Standard tests go in key order, `Reverse` tests go backwards, which hits single-pass forward-only decoders (simdjson On Demand) with an $O(N^2)$ penalty that hash/DOM-indexed ones dodge.

##### A Few Details
* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC it uses `find_field` / `find_field_unordered` instead, because of some pretty severe compiler overhead when instantiating `object::for_each`.
* **simdjson (reflection):** Not in this run, since this toolchain does not support P2996 static reflection yet.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [23af44c](https://github.com/nihilai-collective/benchmarksuite/commit/23af44c)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 497.696 | 0.327171 | 178.179ms | 905 | 2560 | 82405.7 | 1734.14 | 0.00901104 | 4.89528 | 1(Win) | true |
| Glaze | 453.653 | 0.131406 | 205.538ms | 905 | 40 | 250 | 1902.5 | 0.307557 | 5.36514 | 2(Loss) | true |
| simdjson (ondemand) | 151.85 | 0.085392 | 587.161ms | 905 | 80 | 1884.49 | 5683.75 | 0.0219974 | 16.2098 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 580.707 | 0.260691 | 150.111ms | 905 | 80 | 1200.95 | 1486.25 | 0.422297 | 4.17751 | 1(Win) | true |
| Glaze | 554.364 | 0.504794 | 171.321ms | 905 | 320 | 19764.5 | 1556.88 | 0.280224 | 4.38834 | 2(Loss) | true |
| simdjson (ondemand) | 157.316 | 0.0706223 | 559.797ms | 905 | 80 | 1200.95 | 5486.25 | 0.022779 | 15.6197 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 858.248 | 0.201963 | 105.013ms | 905 | 160 | 659.984 | 1005.62 | 0.0621118 | 2.80349 | 1(Win) | true |
| Glaze | 84.955 | 0.302251 | 1139.51ms | 905 | 4890 | 4.61068e+06 | 10159.2 | 0.185514 | 29.0419 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1360.18 | 0.191248 | 76.9537ms | 905 | 2560 | 3770 | 634.531 | 0.39555 | 1.74007 | 1(Win) | true |
| Glaze | 475.687 | 0.153348 | 193.434ms | 905 | 160 | 1238.6 | 1814.38 | 0.0344353 | 5.11956 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 705.751 | 0.34017 | 247.526ms | 1811 | 2560 | 177405 | 2447.19 | 0.0159597 | 3.46621 | 1(Win) | true |
| Glaze | 382.844 | 0.104283 | 432.356ms | 1811 | 80 | 1770.57 | 4511.25 | 0.138351 | 6.42831 | 2(Loss) | true |
| simdjson (ondemand) | 303.533 | 0.122668 | 589.292ms | 1811 | 40 | 1948.72 | 5690 | 0.530035 | 8.11509 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 927.398 | 0.293688 | 189.954ms | 1811 | 4890 | 146280 | 1862.31 | 0.110716 | 2.62945 | 1(Win) | true |
| Glaze | 472.29 | 0.110106 | 380.904ms | 1811 | 160 | 2593.95 | 3656.88 | 0.221692 | 5.21578 | 2(Loss) | true |
| simdjson (ondemand) | 338.854 | 0.178527 | 540.437ms | 1811 | 4890 | 404883 | 5096.89 | 0.387497 | 7.26625 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 466.929 | 0.128598 | 425.581ms | 1997 | 80 | 2200.95 | 4078.75 | 0.639464 | 5.2491 | 1(Win) | true |
| Glaze | 130.707 | 0.37713 | 1337.97ms | 1798 | 2560 | 6.26625e+06 | 13118.8 | 0.357223 | 18.8909 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 714.462 | 0.141305 | 291.594ms | 1997 | 160 | 2270.05 | 2665.62 | 0.117371 | 3.43571 | 1(Win) | true |
| Glaze | 369.35 | 0.0844458 | 496.686ms | 1798 | 160 | 2459.12 | 4642.5 | 0.0538793 | 6.66015 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 840.209 | 0.389559 | 160.934ms | 1313 | 1280 | 43143 | 1490.31 | 0.74922 | 2.89368 | 1(Win) | true |
| Glaze | 343.532 | 0.218553 | 376.918ms | 1313 | 40 | 2538.46 | 3645 | 0.137363 | 7.10842 | 2(Loss) | true |
| simdjson (ondemand) | 262.993 | 0.132063 | 494.553ms | 1313 | 80 | 3162.97 | 4761.25 | 0.0788229 | 9.35388 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1352.79 | 0.374035 | 111.16ms | 1313 | 160 | 1917.85 | 925.625 | 0.338753 | 1.77595 | 1(Win) | true |
| Glaze | 410.538 | 0.232222 | 313.931ms | 1313 | 4890 | 245323 | 3050.08 | 0.0613157 | 5.94391 | 2(Loss) | true |
| simdjson (ondemand) | 300.946 | 0.232672 | 432.652ms | 1313 | 4890 | 458301 | 4160.8 | 0.0840174 | 8.15572 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 587.186 | 0.3517 | 219.469ms | 1313 | 40 | 2250 | 2132.5 | 0.274295 | 4.16131 | 1(Win) | true |
| Glaze | 126.288 | 0.283393 | 1010.19ms | 1313 | 2560 | 2.02125e+06 | 9915.2 | 0.467803 | 19.537 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1281 | 0.480631 | 109.319ms | 1313 | 80 | 1765.82 | 977.5 | 0.255102 | 1.88605 | 1(Win) | true |
| Glaze | 677.767 | 0.304108 | 208.012ms | 1313 | 80 | 2525.32 | 1847.5 | 0 | 3.59083 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 622.484 | 0.329823 | 663.37ms | 4215 | 1280 | 580646 | 6457.58 | 0.0616627 | 3.95289 | 1(Win) | true |
| Glaze | 485.085 | 0.150138 | 791.903ms | 4215 | 30 | 4643.68 | 8286.67 | 0.160643 | 5.09183 | 2(Loss) | true |
| simdjson (ondemand) | 388.064 | 0.429488 | 1059.16ms | 4215 | 320 | 633346 | 10358.4 | 0.0994575 | 6.35464 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.45 | 0.250627 | 511.473ms | 4215 | 30 | 3000 | 3990 | 0.333056 | 2.439 | 1(Win) | true |
| Glaze | 765.244 | 0.202838 | 633.417ms | 4215 | 4890 | 555141 | 5252.88 | 0.226441 | 3.21784 | 2(Loss) | true |
| simdjson (ondemand) | 505.31 | 0.0863196 | 918.847ms | 4215 | 80 | 3772.15 | 7955 | 0.157381 | 4.88477 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 482.338 | 0.153721 | 848.2ms | 4215 | 4890 | 802543 | 8333.87 | 0.10678 | 5.11633 | 1(Win) | true |
| Glaze | 392.297 | 0.185602 | 1043.51ms | 4215 | 30 | 10850.6 | 10246.7 | 1.05194 | 6.29447 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3407.46 | 0.190948 | 132.451ms | 4215 | 320 | 1623.73 | 1179.69 | 0.0794071 | 0.707367 | 1(Win) | true |
| Glaze | 1794.02 | 0.122725 | 236.476ms | 4215 | 320 | 2419.67 | 2240.62 | 0.0837521 | 1.36211 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 765.147 | 0.22233 | 155.298ms | 1213 | 160 | 1807.78 | 1511.88 | 0.124172 | 3.18444 | 1(Win) | true |
| Glaze | 332.655 | 0.192284 | 357.765ms | 1213 | 40 | 1788.46 | 3477.5 | 0.0239693 | 7.35577 | 2(Loss) | true |
| simdjson (ondemand) | 254.383 | 0.175842 | 463.817ms | 1213 | 40 | 2557.69 | 4547.5 | 0.238795 | 9.67168 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1272.97 | 0.349834 | 94.4389ms | 1213 | 80 | 808.544 | 908.75 | 0.137363 | 1.88139 | 1(Win) | true |
| Glaze | 388.516 | 0.111222 | 302.614ms | 1213 | 160 | 1754.72 | 2977.5 | 0.294737 | 6.25307 | 2(Loss) | true |
| simdjson (ondemand) | 287.584 | 0.166232 | 418.565ms | 1213 | 40 | 1788.46 | 4022.5 | 0.0207125 | 8.533 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 596.869 | 0.140309 | 215.596ms | 1213 | 320 | 2366.38 | 1938.12 | 0.289389 | 4.08983 | 1(Win) | true |
| Glaze | 116.038 | 0.1862 | 1007.87ms | 1213 | 2560 | 882108 | 9969.22 | 0.172703 | 21.2578 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1438.14 | 0.201659 | 90.6582ms | 1213 | 160 | 420.991 | 804.375 | 0.0776398 | 1.66685 | 1(Win) | true |
| Glaze | 647.165 | 0.208161 | 191.101ms | 1213 | 80 | 1107.59 | 1787.5 | 0.27894 | 3.75639 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22741.4 | 0.0929232 | 2040.66ms | 466906 | 30 | 9931.03 | 19580 | 0.440678 | 0.108619 | 1(Win) | true |
| simdjson (ondemand) | 20488.6 | 0.218829 | 2242.52ms | 466906 | 2560 | 5.79006e+06 | 21732.9 | 0.314986 | 0.12066 | 2(Loss) | true |
| Glaze | 1991.76 | 0.228092 | 6002.96ms | 466906 | 160 | 4.16029e+07 | 223559 | 0.19086 | 1.24282 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22874.6 | 0.174893 | 1966ms | 466906 | 2560 | 2.96714e+06 | 19465.9 | 0.078725 | 0.108066 | 1(Win) | true |
| simdjson (ondemand) | 21487.6 | 0.058563 | 2124.86ms | 466906 | 40 | 5891.03 | 20722.5 | 0.0603573 | 0.114962 | 2(Loss) | true |
| Glaze | 1954.68 | 0.125562 | 5968.25ms | 466906 | 640 | 5.23603e+07 | 227800 | 0.625388 | 1.26643 | 3(Loss) | true |
