# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [8c470bc](https://github.com/nihilai-collective/Jsonifier/commit/8c470bc)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **simdjson (reflection)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **How the sampling/convergence works (Apple M2 Pro (Virtual)-NEON):**  
> The iterations grow geometrically (100 → 200 → 400 ...) up to a max of 100000.  
> Scores come from a trailing window of `max(iterations/10, 30)` (capped at 100000) over at most 5s.  
> The epoch that counts is whichever one has the lowest (RSE + epoch-over-epoch mean shift).  
> Converged means RSE ≤ 10% and mean shift ≤ 5%. Ties get called using Welch's t-test with Bessel-corrected variance.

---

##### The Test Variants
* **Standard vs. (Reused):** Standard builds, parses/serializes, and tears everything down every iteration. `(Reused)` keeps the buffer/object around across iterations and clears it outside the timed region, so you just see the raw parse/format throughput.
* **Document Sizes:** "Small" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`), so dispatch/setup/small-alloc latency dominates instead of bulk SIMD throughput.
* **Key Traversal Order:** Standard tests go in key order, `Reverse` tests go backwards, which hits single-pass forward-only decoders (simdjson On Demand) with an $O(N^2)$ penalty that hash/DOM-indexed ones dodge.

##### A Few Details
* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC it uses `find_field` / `find_field_unordered` instead, because of some pretty severe compiler overhead when instantiating `object::for_each`.
* **simdjson (reflection):** The C++26 static reflection API (P2996). Minified serialization only, for now.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [23af44c](https://github.com/nihilai-collective/benchmarksuite/commit/23af44c)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1810.14 | 2.94571 | 50.0669ms | 905 | 1280 | 252501 | 476.8 | 3.48178 | 1(Win) | true |
| Glaze | 1343.31 | 1.48484 | 68.4552ms | 905 | 2560 | 232994 | 642.5 | 0.0778816 | 2(Loss) | true |
| simdjson (reflection) | 827.969 | 1.31397 | 109.98ms | 905 | 640 | 120067 | 1042.4 | 0.610221 | 3(Loss) | true |
| simdjson (ondemand) | 404.175 | 0.393435 | 234.735ms | 905 | 2560 | 180694 | 2135.4 | 0.909513 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1612.62 | 3.70433 | 53.7638ms | 905 | 640 | 251554 | 535.2 | 0.904977 | 1(Win) | true |
| Glaze | 1387.02 | 1.4765 | 62.924ms | 905 | 4890 | 412774 | 622.253 | 0.772961 | 2(Loss) | true |
| simdjson (reflection) | 823.231 | 1.46953 | 112.108ms | 905 | 640 | 151911 | 1048.4 | 3.59684 | 3(Loss) | true |
| simdjson (ondemand) | 345.341 | 1.60036 | 231ms | 905 | 160 | 255951 | 2499.2 | 1.56047 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1581.88 | 1.83136 | 56.2742ms | 905 | 2560 | 255585 | 545.6 | 0.619308 | 1(Win) | true |
| simdjson (reflection) | 201.861 | 0.914581 | 416.708ms | 905 | 640 | 978630 | 4275.6 | 2.71958 | 2(Loss) | true |
| Glaze | 114.345 | 0.220895 | 746.766ms | 905 | 4890 | 1.3594e+06 | 7548.02 | 0.416628 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3077.48 | 2.30186 | 39.0659ms | 905 | 4890 | 203785 | 280.448 | 0.444352 | 1(Win) | true |
| simdjson (reflection) | 2197.24 | 3.49592 | 48.841ms | 905 | 1280 | 241366 | 392.8 | 1.76166 | 2(Loss) | true |
| Glaze | 708.833 | 2.71269 | 138.492ms | 905 | 160 | 174554 | 1217.6 | 0.661376 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 854.12 | 0.418716 | 201.945ms | 1811 | 4890 | 350547 | 2022.09 | 2.12082 | 1(Win) | true |
| Glaze | 681.465 | 1.142 | 224.61ms | 1811 | 320 | 268061 | 2534.4 | 2.39173 | 2(Loss) | true |
| simdjson (reflection) | 242.299 | 0.882121 | 737.949ms | 1811 | 320 | 1.26515e+06 | 7128 | 1.85185 | 3(Loss) | true |
| simdjson (ondemand) | 236.417 | 0.304233 | 719.892ms | 1811 | 4890 | 2.41546e+06 | 7305.32 | 1.06831 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 911.236 | 0.544055 | 185.278ms | 1811 | 4890 | 519960 | 1895.34 | 3.64425 | 1(Win) | true |
| Glaze | 833.866 | 1.68524 | 185.98ms | 1811 | 640 | 779739 | 2071.2 | 0.7393 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 247.663 | 0.556186 | 724.99ms | 1811 | 1280 | 1.92559e+06 | 6973.6 | 0.0746226 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 244.162 | 1.40153 | 655.307ms | 1811 | 160 | 1.57255e+06 | 7073.6 | 1.05192 | 3(Tie) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 307.973 | 0.298506 | 644.734ms | 1997 | 4890 | 1.66627e+06 | 6183.94 | 1.63773 | 1(Win) | true |
| Jsonifier | 286.016 | 0.264487 | 645.932ms | 1997 | 4890 | 1.51668e+06 | 6658.67 | 2.13883 | 2(Loss) | true |
| Glaze | 208.075 | 0.545474 | 946.897ms | 1798 | 320 | 646602 | 8240.8 | 0.242107 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1125.85 | 1.10252 | 197.354ms | 1997 | 640 | 222613 | 1691.6 | 0.118371 | 1(Win) | true |
| Jsonifier | 893.706 | 1.08085 | 219.064ms | 1997 | 1280 | 679056 | 2131 | 0.476368 | 2(Loss) | true |
| Glaze | 589.489 | 1.79051 | 301.065ms | 1798 | 160 | 434011 | 2908.8 | 2.59594 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1254.18 | 0.865452 | 110.55ms | 1313 | 80 | 5972.9 | 998.4 | 0 | 1(Win) | true |
| Glaze | 864.522 | 0.97366 | 157.388ms | 1313 | 1280 | 254567 | 1448.4 | 0.415973 | 2(Loss) | true |
| simdjson (reflection) | 611.264 | 0.790027 | 203.835ms | 1313 | 2560 | 670495 | 2048.5 | 1.03865 | 3(Loss) | true |
| simdjson (ondemand) | 295.845 | 1.68432 | 460.447ms | 1313 | 30 | 152465 | 4232.53 | 0 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1781.95 | 1.29865 | 78.751ms | 1313 | 2560 | 213189 | 702.7 | 2.29422 | 1(Win) | true |
| Glaze | 883.929 | 0.725042 | 141.395ms | 1313 | 2560 | 270060 | 1416.6 | 1.07021 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 788.089 | 0.47113 | 172.198ms | 1313 | 4890 | 274012 | 1588.88 | 5.20403 | -(Loss) | false |
| simdjson (ondemand) | 312.562 | 0.267492 | 428.634ms | 1313 | 4890 | 561551 | 4006.16 | 0.166631 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 279.803 | 0.954264 | 457.515ms | 1313 | 160 | 291797 | 4475.2 | 0.320741 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 275.444 | 0.279867 | 448.347ms | 1313 | 4890 | 791544 | 4546.02 | 3.87144 | 1(Tie) | true |
| Glaze | 177.382 | 0.825563 | 703.685ms | 1313 | 320 | 1.08683e+06 | 7059.2 | 2.17693 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2756.27 | 2.24597 | 56.3868ms | 1313 | 2560 | 266522 | 454.3 | 0.419982 | 1(Win) | true |
| simdjson (reflection) | 2475.52 | 1.43826 | 63.329ms | 1313 | 4890 | 258808 | 505.822 | 3.87258 | 2(Loss) | true |
| Glaze | 921.123 | 1.1141 | 149.739ms | 1313 | 1280 | 293599 | 1359.4 | 0.577094 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 831.727 | 0.460728 | 485.931ms | 4215 | 2560 | 1.26929e+06 | 4833 | 2.22141 | 1(Win) | true |
| Glaze | 639.434 | 0.78684 | 694.993ms | 4215 | 320 | 782937 | 6286.4 | 0.46024 | 2(Loss) | true |
| simdjson (reflection) | 589.698 | 0.586292 | 728.384ms | 4215 | 1280 | 2.04444e+06 | 6816.6 | 1.02509 | 3(Loss) | true |
| simdjson (ondemand) | 484.399 | 0.439332 | 875.75ms | 4215 | 1280 | 1.70132e+06 | 8298.4 | 0.717841 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1706.1 | 0.445859 | 350.629ms | 4215 | 2560 | 282503 | 2356.1 | 1.44315 | 1(Win) | true |
| simdjson (reflection) | 804.076 | 1.1164 | 640.402ms | 4215 | 320 | 996753 | 4999.2 | 1.21477 | 2(Loss) | true |
| Glaze | 766.716 | 0.74309 | 611.519ms | 4215 | 2560 | 3.88552e+06 | 5242.8 | 0.440562 | 3(Loss) | true |
| simdjson (ondemand) | 648.136 | 0.351686 | 719.655ms | 4215 | 1280 | 608952 | 6202 | 0.951833 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 754.909 | 1.58895 | 573.918ms | 4215 | 40 | 286342 | 5324.8 | 0.16 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 740.665 | 2.50213 | 518.885ms | 4215 | 30 | 553214 | 5427.2 | 1.39535 | 1(Tie) | true |
| Glaze | 460.346 | 0.758076 | 880.041ms | 4215 | 320 | 1.40218e+06 | 8732 | 1.15015 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4999.67 | 1.98496 | 88.1569ms | 4215 | 640 | 163003 | 804 | 4.82955 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4975.54 | 0.999413 | 89.451ms | 4215 | 2560 | 166896 | 807.9 | 2.91997 | 1(Tie) | true |
| Glaze | 2632.79 | 1.30732 | 180.543ms | 4215 | 640 | 254983 | 1526.8 | 1.89536 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1139.82 | 0.648326 | 106.28ms | 1213 | 2560 | 110834 | 1014.9 | 2.43238 | 1(Win) | true |
| Glaze | 851.595 | 1.05309 | 143.94ms | 1213 | 1280 | 261936 | 1358.4 | 0.0589275 | 2(Loss) | true |
| simdjson (reflection) | 733.549 | 0.869255 | 184.393ms | 1213 | 1280 | 240529 | 1577 | 0.165142 | 3(Loss) | true |
| simdjson (ondemand) | 277.794 | 1.8858 | 449.371ms | 1213 | 30 | 185007 | 4164.27 | 0.204499 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1525.29 | 0.82813 | 76.566ms | 1213 | 4890 | 192897 | 758.42 | 4.81681 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 870.159 | 0.528351 | 137ms | 1213 | 4890 | 241256 | 1329.42 | 0.937404 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 866.263 | 1.00786 | 141.71ms | 1213 | 1280 | 231864 | 1335.4 | 1.53589 | 2(Tie) | true |
| simdjson (ondemand) | 320.25 | 0.30457 | 398.072ms | 1213 | 2560 | 309854 | 3612.2 | 0.997643 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 284.01 | 0.139538 | 426.079ms | 1213 | 4890 | 157961 | 4073.12 | 0.0644218 | 1(Win) | true |
| simdjson (reflection) | 274.75 | 0.651798 | 461.37ms | 1213 | 320 | 241003 | 4210.4 | 2.47274 | 2(Loss) | true |
| Glaze | 176.056 | 1.48663 | 713.943ms | 1213 | 30 | 286249 | 6570.67 | 0 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2678.4 | 1.68634 | 52.802ms | 1213 | 4890 | 259400 | 431.902 | 3.40001 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2525.78 | 3.05829 | 57.4531ms | 1213 | 1280 | 251130 | 458 | 0.865801 | 1(Tie) | true |
| Glaze | 969.5 | 1.90123 | 145.293ms | 1213 | 640 | 329364 | 1193.2 | 0.699068 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7536.22 | 0.111169 | 6407.8ms | 466906 | 1280 | 5.52238e+06 | 59084.8 | 0.288916 | 1(Win) | true |
| Jsonifier | 7090.34 | 0.40488 | 6640.13ms | 466906 | 640 | 4.13769e+07 | 62800.4 | 1.73466 | 2(Loss) | true |
| Glaze | 1835.63 | 0.123359 | 6751.7ms | 466906 | 640 | 5.73076e+07 | 242574 | 1.71439 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7764.79 | 0.463773 | 6161.7ms | 466906 | 320 | 2.2634e+07 | 57345.6 | 0.251741 | 1(Win) | true |
| simdjson (ondemand) | 7598.78 | 0.303451 | 6426.27ms | 466906 | 80 | 2.52952e+06 | 58598.4 | 0.919814 | 2(Loss) | true |
| Glaze | 1620.53 | 0.453049 | 7036.72ms | 466906 | 320 | 4.95887e+08 | 274771 | 0.510948 | 3(Loss) | true |
