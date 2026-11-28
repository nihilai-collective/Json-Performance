# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the GCC 16.2.0 compiler).  

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
| **simdjson (reflection)** | `icelake` |
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
* **simdjson (reflection):** The C++26 static reflection API (P2996). Minified serialization only, for now.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [23af44c](https://github.com/nihilai-collective/benchmarksuite/commit/23af44c)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2840.61 | 0.0877865 | 33.2123ms | 905 | 320 | 22.7656 | 303.834 | 0.0215943 | 0.797959 | 1(Win) | true |
| Glaze | 2376.09 | 0.225437 | 39.7045ms | 905 | 30 | 20.1161 | 363.233 | 0 | 0.970976 | 2(Loss) | true |
| simdjson (reflection) | 1247.24 | 0.0330026 | 72.4202ms | 905 | 320 | 16.6895 | 691.987 | 0.0189635 | 1.91203 | 3(Loss) | true |
| simdjson (ondemand) | 497.627 | 0.176306 | 176.651ms | 905 | 4890 | 45722.7 | 1734.38 | 0.119254 | 4.90101 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2476.92 | 0.0328764 | 37.6588ms | 905 | 1280 | 16.7978 | 348.447 | 0.0806502 | 0.924298 | 1(Win) | true |
| Jsonifier | 2452.57 | 0.0625579 | 38.654ms | 905 | 320 | 15.5084 | 351.906 | 0.0195403 | 0.93606 | 2(Loss) | true |
| simdjson (reflection) | 1309.67 | 0.152615 | 69.1256ms | 905 | 30 | 30.3448 | 659 | 0 | 1.81845 | 3(Loss) | true |
| simdjson (ondemand) | 507.64 | 0.260235 | 172.479ms | 905 | 4890 | 95724.9 | 1700.17 | 0.0675204 | 4.80329 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1946.99 | 0.113093 | 44.0564ms | 905 | 80 | 20.1062 | 443.288 | 0.0760778 | 1.20275 | 1(Win) | true |
| simdjson (reflection) | 269.551 | 0.0375062 | 321.432ms | 905 | 30 | 43.2655 | 3201.9 | 0.202372 | 9.11182 | 2(Loss) | true |
| Glaze | 208.559 | 0.024218 | 417.98ms | 905 | 80 | 80.3538 | 4138.27 | 0.0126848 | 11.7922 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3267.99 | 0.341746 | 33.6532ms | 905 | 30 | 24.4379 | 264.1 | 0.113464 | 0.685488 | 1(Win) | true |
| simdjson (reflection) | 2536.59 | 0.0806601 | 41.1142ms | 905 | 40 | 3.01282 | 340.25 | 0.0244978 | 0.899917 | 2(Loss) | true |
| Glaze | 1122.44 | 0.151439 | 85.516ms | 905 | 80 | 108.475 | 768.925 | 0.0650682 | 2.12983 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.32 | 0.0762848 | 120.691ms | 1811 | 40 | 31.9872 | 1172.25 | 0.0440554 | 1.64658 | 1(Win) | true |
| Glaze | 1080.01 | 0.0368432 | 164.016ms | 1811 | 160 | 55.5415 | 1599.16 | 0.140506 | 2.25485 | 2(Loss) | true |
| simdjson (ondemand) | 420.33 | 0.140031 | 417.882ms | 1811 | 40 | 1324.23 | 4108.93 | 0.0131809 | 5.85493 | 3(Loss) | true |
| simdjson (reflection) | 392.977 | 0.165073 | 450.125ms | 1811 | 4890 | 257374 | 4394.92 | 0.120499 | 6.26346 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1550.43 | 0.0497341 | 113.322ms | 1811 | 80 | 24.5544 | 1113.95 | 0.132237 | 1.55957 | 1(Win) | true |
| Glaze | 1063.42 | 0.0463752 | 161.245ms | 1811 | 80 | 45.3823 | 1624.1 | 0.067684 | 2.28927 | 2(Loss) | true |
| simdjson (ondemand) | 429.468 | 0.162687 | 405.31ms | 1811 | 2560 | 109577 | 4021.5 | 0.0494265 | 5.72832 | 3(Loss) | true |
| simdjson (reflection) | 402.052 | 0.136787 | 432.331ms | 1811 | 4890 | 168839 | 4295.73 | 0.0343955 | 6.12114 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 389.875 | 0.215787 | 499.286ms | 1997 | 1280 | 142222 | 4884.87 | 0.104721 | 6.31727 | 1(Win) | true |
| simdjson (reflection) | 325.698 | 0.255221 | 583.77ms | 1997 | 1280 | 285080 | 5847.4 | 1.06406 | 7.56802 | 2(Loss) | true |
| Glaze | 290.797 | 0.0520188 | 603.387ms | 1798 | 30 | 282.254 | 5896.57 | 0.0960089 | 8.47762 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 928.412 | 0.175148 | 212.881ms | 1997 | 4890 | 63123.6 | 2051.34 | 0.0114439 | 2.63225 | 1(Win) | true |
| simdjson (reflection) | 743.263 | 0.0421885 | 261.319ms | 1997 | 30 | 35.0575 | 2562.33 | 0.0130073 | 3.2986 | 2(Loss) | true |
| Glaze | 595.219 | 0.0711139 | 318.253ms | 1798 | 80 | 335.757 | 2880.8 | 0.242399 | 4.1228 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1768.8 | 0.0618367 | 74.1177ms | 1313 | 160 | 30.661 | 707.925 | 0.0494647 | 1.34903 | 1(Win) | true |
| simdjson (reflection) | 1028.34 | 0.0247817 | 126.261ms | 1313 | 320 | 29.1386 | 1217.67 | 0.125139 | 2.35736 | 2(Loss) | true |
| Glaze | 934.412 | 0.0908629 | 137.318ms | 1313 | 30 | 44.4782 | 1340.07 | 0.151964 | 2.60244 | 3(Loss) | true |
| simdjson (ondemand) | 355.025 | 0.0305489 | 357.765ms | 1313 | 30 | 34.8276 | 3527 | 0.0755501 | 6.92138 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1976.05 | 0.114188 | 67.3711ms | 1313 | 40 | 20.9429 | 633.675 | 0.0539474 | 1.20188 | 1(Win) | true |
| simdjson (reflection) | 1106.2 | 0.0546986 | 116.787ms | 1313 | 80 | 30.6695 | 1131.96 | 0.0231952 | 2.18899 | 2(Loss) | true |
| Glaze | 1021.48 | 0.201649 | 124.96ms | 1313 | 4890 | 29878.9 | 1225.84 | 0.00211362 | 2.37284 | 3(Loss) | true |
| simdjson (ondemand) | 357.498 | 0.140939 | 353.372ms | 1313 | 4890 | 119166 | 3502.6 | 0.146058 | 6.87479 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 385.709 | 0.0449487 | 325.316ms | 1313 | 40 | 85.1737 | 3246.43 | 0.117961 | 6.36915 | 1(Win) | true |
| simdjson (reflection) | 368.561 | 0.0544879 | 334.318ms | 1313 | 30 | 102.809 | 3397.47 | 0.205612 | 6.66527 | 2(Loss) | true |
| Glaze | 323.905 | 0.0497915 | 388.921ms | 1313 | 30 | 111.154 | 3865.87 | 0.0585985 | 7.59327 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2650.85 | 0.145854 | 55.1835ms | 1313 | 30 | 14.2402 | 472.367 | 0.0564852 | 0.884996 | 1(Win) | true |
| simdjson (reflection) | 2407.56 | 0.0421629 | 57.5329ms | 1313 | 320 | 15.3881 | 520.1 | 0.00240344 | 0.976642 | 2(Loss) | true |
| Glaze | 1374.91 | 0.046157 | 100.936ms | 1313 | 160 | 28.2732 | 910.731 | 0.0666117 | 1.74999 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1440.11 | 0.175527 | 282.832ms | 4215 | 30 | 720.133 | 2791.27 | 0.156685 | 1.70348 | 1(Win) | true |
| simdjson (reflection) | 1060.92 | 0.164185 | 383.624ms | 4215 | 2560 | 99068.3 | 3788.92 | 0.0803199 | 2.31779 | 2(Loss) | true |
| Glaze | 1043.02 | 0.0528083 | 387.536ms | 4215 | 80 | 331.365 | 3853.95 | 0.0805017 | 2.35808 | 3(Loss) | true |
| simdjson (ondemand) | 740.747 | 0.0809038 | 532.288ms | 4215 | 30 | 578.248 | 5426.6 | 0.0442462 | 3.32539 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1938.92 | 0.179124 | 245.386ms | 4215 | 4890 | 67436.2 | 2073.19 | 0.0305478 | 1.2605 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1299.28 | 0.191451 | 350.346ms | 4215 | 4890 | 171559 | 3093.82 | 0.0253854 | 1.88953 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1296.36 | 0.0448943 | 345.322ms | 4215 | 80 | 155.03 | 3100.79 | 0.239284 | 1.8946 | 2(Tie) | true |
| simdjson (ondemand) | 864.274 | 0.149996 | 500.526ms | 4215 | 30 | 1460.07 | 4651 | 0.137076 | 2.84834 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1836.07 | 0.0635067 | 222.765ms | 4215 | 80 | 154.648 | 2189.31 | 0.171563 | 1.33287 | 1(Win) | true |
| simdjson (reflection) | 1573.35 | 0.0925373 | 262.422ms | 4215 | 80 | 447.164 | 2554.89 | 0.214324 | 1.55842 | 2(Loss) | true |
| Glaze | 1012.57 | 0.195056 | 401.317ms | 4215 | 4890 | 293207 | 3969.85 | 0.299228 | 2.42935 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5710.82 | 0.0335163 | 80.3098ms | 4215 | 640 | 35.6197 | 703.881 | 0.0603431 | 0.417587 | 1(Win) | true |
| simdjson (reflection) | 3960.85 | 0.110164 | 105.946ms | 4215 | 30 | 37.4989 | 1014.87 | 0.0558678 | 0.608992 | 2(Loss) | true |
| Glaze | 2686.09 | 0.0535009 | 151.745ms | 4215 | 40 | 25.641 | 1496.5 | 0.0133663 | 0.906115 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1689.51 | 0.130095 | 71.1167ms | 1213 | 30 | 23.8034 | 684.7 | 0.043834 | 1.41311 | 1(Win) | true |
| simdjson (reflection) | 1044.02 | 0.100413 | 112.903ms | 1213 | 30 | 37.1368 | 1108.03 | 0.00300842 | 2.31833 | 2(Loss) | true |
| Glaze | 967.931 | 0.288594 | 123.126ms | 1213 | 2560 | 30454.2 | 1195.13 | 0.0136276 | 2.49407 | 3(Loss) | true |
| simdjson (ondemand) | 323.358 | 0.05352 | 363.616ms | 1213 | 160 | 586.553 | 3577.48 | 0.0546524 | 7.60186 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1891.99 | 0.14199 | 64.1212ms | 1213 | 40 | 30.1481 | 611.425 | 0.0340618 | 1.25431 | 1(Win) | true |
| simdjson (reflection) | 1181.8 | 0.0688224 | 102.484ms | 1213 | 80 | 36.3063 | 978.85 | 0.0843537 | 2.03885 | 2(Loss) | true |
| Glaze | 1011.88 | 0.131309 | 116.667ms | 1213 | 80 | 180.278 | 1143.22 | 0 | 2.37242 | 3(Loss) | true |
| simdjson (ondemand) | 334.125 | 0.0320437 | 351.474ms | 1213 | 30 | 36.9241 | 3462.2 | 0.017333 | 7.3562 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 369.536 | 0.108309 | 317.809ms | 1213 | 30 | 344.875 | 3130.43 | 0.350159 | 6.64806 | 1(Win) | true |
| simdjson (reflection) | 346.035 | 0.193708 | 341.268ms | 1213 | 4890 | 205063 | 3343.03 | 0.588076 | 7.09988 | 2(Loss) | true |
| Glaze | 300.996 | 0.030699 | 392.695ms | 1213 | 160 | 222.726 | 3843.27 | 0.112246 | 8.17053 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2620.77 | 0.150356 | 51.6908ms | 1213 | 30 | 13.2138 | 441.4 | 0.143277 | 0.888761 | 1(Win) | true |
| simdjson (reflection) | 2559.59 | 0.0812306 | 52.4921ms | 1213 | 80 | 10.7823 | 451.95 | 0.116298 | 0.910892 | 2(Loss) | true |
| Glaze | 1382.46 | 0.0697671 | 91.7882ms | 1213 | 80 | 27.2652 | 836.775 | 0 | 1.73734 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21170.6 | 0.0764264 | 2114.72ms | 466906 | 4890 | 1.26354e+06 | 21032.8 | 0.125934 | 0.116798 | 1(Win) | true |
| simdjson (ondemand) | 15883.2 | 0.1117 | 2796.72ms | 466906 | 1280 | 1.25516e+06 | 28034.4 | 0.213656 | 0.155709 | 2(Loss) | true |
| Glaze | 2804.01 | 0.0781863 | 8149.4ms | 466906 | 640 | 9.86598e+06 | 158800 | 0.108909 | 0.882797 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21222.4 | 0.181827 | 2124.36ms | 466906 | 1280 | 1.86292e+06 | 20981.4 | 0.00114684 | 0.116513 | 1(Win) | true |
| simdjson (ondemand) | 18312.8 | 0.192219 | 2454.05ms | 466906 | 640 | 1.39804e+06 | 24315 | 0.164662 | 0.135049 | 2(Loss) | true |
| Glaze | 2809.5 | 0.124716 | 8142.74ms | 466906 | 320 | 1.25024e+07 | 158489 | 0.162811 | 0.881069 | 3(Loss) | true |
