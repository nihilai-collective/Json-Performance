# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the GCC 16.2.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [899f304](https://github.com/nihilai-collective/Jsonifier/commit/899f304)  
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
| Jsonifier | 2678.28 | 0.195238 | 36.3397ms | 905 | 40 | 15.8333 | 322.25 | 0.0878462 | 0.846022 | 1(Win) | true |
| Glaze | 2239.37 | 0.046424 | 41.676ms | 905 | 1280 | 40.9769 | 385.409 | 0.0263588 | 1.0274 | 2(Loss) | true |
| simdjson (reflection) | 1157.77 | 0.125827 | 78.0373ms | 905 | 30 | 26.3954 | 745.467 | 0.0446947 | 2.06361 | 3(Loss) | true |
| simdjson (ondemand) | 468.714 | 0.171429 | 189.277ms | 905 | 30 | 298.93 | 1841.37 | 0.0325951 | 5.2018 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2313.71 | 0.0327002 | 40.2079ms | 905 | 1280 | 19.0454 | 373.027 | 0.0343356 | 0.992295 | 1(Win) | true |
| Jsonifier | 2308.98 | 0.0705801 | 40.6272ms | 905 | 320 | 22.2726 | 373.791 | 0.475105 | 0.994572 | 2(Loss) | true |
| simdjson (reflection) | 1247.15 | 0.0659608 | 72.8585ms | 905 | 80 | 16.6695 | 692.038 | 0.0343072 | 1.9075 | 3(Loss) | true |
| simdjson (ondemand) | 474.007 | 0.063165 | 186.234ms | 905 | 160 | 211.641 | 1820.81 | 0.0442602 | 5.14319 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1954.86 | 0.0288956 | 47.0045ms | 905 | 640 | 10.4163 | 441.503 | 0.00778651 | 1.18874 | 1(Win) | true |
| simdjson (reflection) | 258.501 | 0.0501348 | 343.981ms | 905 | 40 | 112.076 | 3338.78 | 0.476685 | 9.5013 | 2(Loss) | true |
| Glaze | 196.394 | 0.0328546 | 453.174ms | 905 | 80 | 166.772 | 4394.61 | 0.0167791 | 12.5273 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3125.88 | 0.142554 | 35.7277ms | 905 | 160 | 24.7874 | 276.106 | 0.0158428 | 0.713619 | 1(Win) | true |
| simdjson (reflection) | 2389.47 | 0.232355 | 42.9176ms | 905 | 30 | 21.131 | 361.2 | 0.0921999 | 0.959374 | 2(Loss) | true |
| Glaze | 1062.2 | 0.0925828 | 89.8299ms | 905 | 320 | 181.09 | 812.534 | 0.137881 | 2.25027 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1376.56 | 0.0852124 | 129.784ms | 1811 | 40 | 45.7205 | 1254.65 | 0.0968786 | 1.75866 | 1(Win) | true |
| Glaze | 1034.45 | 0.0480793 | 175.291ms | 1811 | 160 | 103.099 | 1669.59 | 0.78515 | 2.35339 | 2(Loss) | true |
| simdjson (ondemand) | 367.012 | 0.152888 | 470.128ms | 1811 | 40 | 2070.54 | 4705.85 | 0.123048 | 6.70635 | 3(Loss) | true |
| simdjson (reflection) | 346.217 | 0.150197 | 504.207ms | 1811 | 2560 | 143715 | 4988.51 | 0.0944483 | 7.11235 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.97 | 0.0389189 | 121.589ms | 1811 | 160 | 33.5918 | 1177.33 | 0.0806263 | 1.64793 | 1(Win) | true |
| Glaze | 1028.33 | 0.0372139 | 173.34ms | 1811 | 160 | 62.5028 | 1679.52 | 0.0234387 | 2.36757 | 2(Loss) | true |
| simdjson (ondemand) | 384.057 | 0.0986413 | 454.281ms | 1811 | 80 | 1574.18 | 4497 | 0.338521 | 6.40697 | 3(Loss) | true |
| simdjson (reflection) | 345.826 | 0.217388 | 506.886ms | 1811 | 1280 | 150870 | 4994.14 | 0.0217959 | 7.12032 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 372.86 | 0.0639556 | 521.59ms | 1997 | 80 | 853.714 | 5107.79 | 0.22295 | 6.60525 | 1(Win) | true |
| simdjson (reflection) | 305.758 | 0.040476 | 622.997ms | 1997 | 30 | 190.685 | 6228.73 | 0.349603 | 8.06164 | 2(Loss) | true |
| Glaze | 271.757 | 0.1429 | 634.989ms | 1798 | 2560 | 208124 | 6309.7 | 0.0998406 | 9.07127 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 881.911 | 0.0567143 | 225.478ms | 1997 | 40 | 60 | 2159.5 | 0.05869 | 2.77181 | 1(Win) | true |
| simdjson (reflection) | 715.801 | 0.0283527 | 277.379ms | 1997 | 80 | 45.5252 | 2660.64 | 0.00422813 | 3.4242 | 2(Loss) | true |
| Glaze | 543.657 | 0.0495916 | 321.99ms | 1798 | 80 | 195.721 | 3154.03 | 0.0801206 | 4.51557 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1699.48 | 0.126417 | 77.3339ms | 1313 | 30 | 26.0276 | 736.8 | 0.135538 | 1.40454 | 1(Win) | true |
| simdjson (reflection) | 985.473 | 0.112096 | 132.312ms | 1313 | 30 | 60.8609 | 1270.63 | 0.201592 | 2.45669 | 2(Loss) | true |
| Glaze | 901.83 | 0.0709314 | 142.839ms | 1313 | 160 | 155.195 | 1388.48 | 0.182636 | 2.69321 | 3(Loss) | true |
| simdjson (ondemand) | 336.281 | 0.0508509 | 377.205ms | 1313 | 30 | 107.559 | 3723.6 | 0.11651 | 7.30942 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1917.24 | 0.0891794 | 68.9153ms | 1313 | 80 | 27.1391 | 653.112 | 0.0592961 | 1.23978 | 1(Win) | true |
| simdjson (reflection) | 1066.57 | 0.0723322 | 122.688ms | 1313 | 40 | 28.8455 | 1174.03 | 0.0943155 | 2.26729 | 2(Loss) | true |
| Glaze | 980.922 | 0.0328513 | 131.327ms | 1313 | 640 | 112.55 | 1276.53 | 0.0161545 | 2.46996 | 3(Loss) | true |
| simdjson (ondemand) | 341.363 | 0.305947 | 371.863ms | 1313 | 640 | 80606.1 | 3668.16 | 0.0386071 | 7.19979 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 358.151 | 0.140267 | 353.608ms | 1313 | 4890 | 117602 | 3496.22 | 0.128507 | 6.85906 | 1(Win) | true |
| Jsonifier | 353.764 | 0.184275 | 355.527ms | 1313 | 2560 | 108912 | 3539.58 | 0.533964 | 6.94337 | 2(Loss) | true |
| Glaze | 311.816 | 0.0500328 | 413.871ms | 1313 | 40 | 161.474 | 4015.75 | 0.0344596 | 7.89 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2506.73 | 0.104118 | 59.6651ms | 1313 | 40 | 10.8199 | 499.525 | 0.152042 | 0.932597 | 1(Win) | true |
| simdjson (reflection) | 2421.4 | 0.0530816 | 60.9566ms | 1313 | 320 | 24.1121 | 517.128 | 0.00422991 | 0.968262 | 2(Loss) | true |
| Glaze | 1211.25 | 0.309226 | 112.355ms | 1313 | 2560 | 26161 | 1033.79 | 0.434985 | 1.98639 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1378.74 | 0.112528 | 299.4ms | 4215 | 80 | 861.088 | 2915.53 | 0.21818 | 1.77887 | 1(Win) | true |
| Glaze | 1005.49 | 0.172714 | 404.544ms | 4215 | 2560 | 122049 | 3997.78 | 0.0883302 | 2.44566 | 2(Loss) | true |
| simdjson (reflection) | 988.966 | 0.361545 | 407.597ms | 4215 | 640 | 138209 | 4064.58 | 0.112815 | 2.48656 | 3(Loss) | true |
| simdjson (ondemand) | 706.987 | 0.0551108 | 574.756ms | 4215 | 160 | 1570.97 | 5685.73 | 0.335132 | 3.4848 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1784.99 | 0.17321 | 264.642ms | 4215 | 30 | 456.447 | 2251.97 | 0.0755466 | 1.3698 | 1(Win) | true |
| Glaze | 1219.69 | 0.0639173 | 371.104ms | 4215 | 40 | 177.497 | 3295.7 | 0.752853 | 2.01276 | 2(Loss) | true |
| simdjson (reflection) | 1192.72 | 0.114279 | 383.267ms | 4215 | 30 | 445.013 | 3370.23 | 0.0247202 | 2.05901 | 3(Loss) | true |
| simdjson (ondemand) | 815.687 | 0.232818 | 530.474ms | 4215 | 1280 | 168497 | 4928.04 | 0.00456551 | 3.01871 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1683.96 | 0.223691 | 246.407ms | 4215 | 40 | 1140.48 | 2387.07 | 0.200332 | 1.45295 | 1(Win) | true |
| simdjson (reflection) | 1497.09 | 0.185183 | 276.809ms | 4215 | 30 | 741.689 | 2685.03 | 0.174739 | 1.63646 | 2(Loss) | true |
| Glaze | 919.973 | 0.220612 | 441.059ms | 4215 | 4890 | 454374 | 4369.41 | 0.448564 | 2.67415 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5364.03 | 0.0941036 | 84.8649ms | 4215 | 80 | 39.7847 | 749.388 | 0.20224 | 0.445549 | 1(Win) | true |
| simdjson (reflection) | 3851.06 | 0.0870654 | 113.476ms | 4215 | 40 | 33.0359 | 1043.8 | 0.0543183 | 0.625629 | 2(Loss) | true |
| Glaze | 2741.66 | 0.084145 | 163.26ms | 4215 | 30 | 45.6609 | 1466.17 | 0.0227299 | 0.885987 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1578.2 | 0.729392 | 75.3909ms | 1213 | 1280 | 36587.3 | 732.991 | 0.151258 | 1.50968 | 1(Win) | true |
| simdjson (reflection) | 1007.02 | 0.13007 | 118.461ms | 1213 | 80 | 178.601 | 1148.74 | 0.111954 | 2.40004 | 2(Loss) | true |
| Glaze | 909.274 | 0.0614021 | 131.849ms | 1213 | 160 | 97.638 | 1272.23 | 0.0427216 | 2.65672 | 3(Loss) | true |
| simdjson (ondemand) | 300.705 | 0.123975 | 387.122ms | 1213 | 4890 | 111228 | 3846.98 | 0.128516 | 8.17507 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1761.11 | 0.100084 | 68.2678ms | 1213 | 80 | 34.5758 | 656.862 | 0.0931594 | 1.3468 | 1(Win) | true |
| simdjson (reflection) | 1122.84 | 0.0490171 | 107.687ms | 1213 | 640 | 163.216 | 1030.25 | 0.0212281 | 2.14758 | 2(Loss) | true |
| Glaze | 945.95 | 0.266033 | 125.188ms | 1213 | 4890 | 51756.7 | 1222.9 | 0.0411113 | 2.541 | 3(Loss) | true |
| simdjson (ondemand) | 312.157 | 0.0253348 | 375.711ms | 1213 | 40 | 35.259 | 3705.85 | 0.00674655 | 7.87232 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 345.847 | 0.310643 | 336.827ms | 1213 | 1280 | 138193 | 3344.85 | 0.0852782 | 7.09984 | 1(Win) | true |
| simdjson (reflection) | 338.228 | 0.0922184 | 347.115ms | 1213 | 30 | 298.441 | 3420.2 | 0 | 7.25982 | 2(Loss) | true |
| Glaze | 278.207 | 0.240121 | 419.307ms | 1213 | 1280 | 127602 | 4158.08 | 0.256578 | 8.83921 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2595.7 | 0.125844 | 53.5355ms | 1213 | 80 | 25.1631 | 445.663 | 0.00280489 | 0.895373 | 1(Win) | true |
| simdjson (reflection) | 2190.46 | 0.0468009 | 61.9842ms | 1213 | 320 | 19.5484 | 528.112 | 0.0722432 | 1.072 | 2(Loss) | true |
| Glaze | 1312.58 | 0.0585549 | 96.702ms | 1213 | 160 | 42.6107 | 881.325 | 0.0155991 | 1.82931 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21618.2 | 0.319596 | 2130.02ms | 466906 | 320 | 1.38667e+06 | 20597.3 | 0.0464499 | 0.114363 | 1(Win) | true |
| simdjson (ondemand) | 17080.9 | 0.204549 | 2607.81ms | 466906 | 1280 | 3.63949e+06 | 26068.7 | 0.247317 | 0.144762 | 2(Loss) | true |
| Glaze | 2661.79 | 0.0933138 | 8669.54ms | 466906 | 320 | 7.79745e+06 | 167284 | 0.091949 | 0.929946 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21135.2 | 0.10249 | 2107.91ms | 466906 | 4890 | 2.27991e+06 | 21068 | 0.209755 | 0.116962 | 1(Win) | true |
| simdjson (ondemand) | 17408.6 | 0.37523 | 2606.67ms | 466906 | 160 | 1.47383e+06 | 25578 | 0.0613697 | 0.142063 | 2(Loss) | true |
| Glaze | 2653.86 | 0.172829 | 8660.59ms | 466906 | 80 | 6.72703e+06 | 167784 | 0.321232 | 0.93272 | 3(Loss) | true |
