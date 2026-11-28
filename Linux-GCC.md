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
| Jsonifier | 2796.52 | 0.223565 | 33.9162ms | 905 | 80 | 38.0854 | 308.625 | 0.121655 | 0.814613 | 1(Win) | true |
| Glaze | 2372.63 | 0.206569 | 40.3743ms | 905 | 80 | 45.1707 | 363.762 | 0.359515 | 0.969157 | 2(Loss) | true |
| simdjson (reflection) | 1209.57 | 0.0894119 | 74.3371ms | 905 | 640 | 260.499 | 713.539 | 0.152422 | 1.97424 | 3(Loss) | true |
| simdjson (ondemand) | 528.279 | 0.0549549 | 172.658ms | 905 | 40 | 32.2436 | 1633.75 | 0.109275 | 4.60956 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2484.38 | 0.15109 | 37.6298ms | 905 | 80 | 22.0405 | 347.4 | 0.0431593 | 0.925594 | 1(Win) | true |
| Jsonifier | 2458.66 | 0.0659354 | 37.6673ms | 905 | 320 | 17.143 | 351.034 | 0.0365126 | 0.934413 | 2(Loss) | true |
| simdjson (reflection) | 1289.52 | 0.127575 | 70.7377ms | 905 | 30 | 21.8724 | 669.3 | 0.044843 | 1.84052 | 3(Loss) | true |
| simdjson (ondemand) | 521.661 | 0.052878 | 166.577ms | 905 | 40 | 30.6147 | 1654.47 | 0.140331 | 4.66414 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2076.57 | 0.144473 | 44.7111ms | 905 | 80 | 28.8449 | 415.625 | 0.00601468 | 1.11952 | 1(Win) | true |
| simdjson (reflection) | 265.473 | 0.325047 | 332.929ms | 905 | 2560 | 285884 | 3251.09 | 0.0318264 | 9.25166 | 2(Loss) | true |
| Glaze | 209.645 | 0.0260359 | 423.783ms | 905 | 80 | 91.91 | 4116.84 | 0.287922 | 11.7351 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3292.67 | 0.0455419 | 34.2625ms | 905 | 1280 | 18.2404 | 262.12 | 0.0256389 | 0.678662 | 1(Win) | true |
| simdjson (reflection) | 2544.94 | 0.238982 | 39.2403ms | 905 | 30 | 19.7057 | 339.133 | 0.384805 | 0.894328 | 2(Loss) | true |
| Glaze | 1113.51 | 0.168131 | 86.3142ms | 905 | 160 | 271.721 | 775.094 | 0.823564 | 2.1478 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.62 | 0.0605137 | 121.2ms | 1811 | 80 | 40.2403 | 1172.01 | 0.107605 | 1.64446 | 1(Win) | true |
| Glaze | 1027.26 | 0.064946 | 167.423ms | 1811 | 40 | 47.6917 | 1681.28 | 0.0945807 | 2.37025 | 2(Loss) | true |
| simdjson (ondemand) | 416.798 | 0.149159 | 426.476ms | 1811 | 2560 | 97796.7 | 4143.74 | 0.172403 | 5.90322 | 3(Loss) | true |
| simdjson (reflection) | 392.514 | 0.413295 | 440.617ms | 1811 | 4890 | 1.61717e+06 | 4400.1 | 0.269293 | 6.27083 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.44 | 0.0740801 | 116.212ms | 1811 | 40 | 30.4487 | 1177.75 | 0.0297089 | 1.64989 | 1(Win) | true |
| Glaze | 1118.98 | 0.0494113 | 158.493ms | 1811 | 80 | 46.5302 | 1543.46 | 0.0267328 | 2.17497 | 2(Loss) | true |
| simdjson (ondemand) | 422.791 | 0.634015 | 416.724ms | 1811 | 320 | 214652 | 4085.01 | 0.0422454 | 5.81971 | 3(Loss) | true |
| simdjson (reflection) | 401.988 | 0.1497 | 435.755ms | 1811 | 2560 | 105900 | 4296.41 | 0.0256053 | 6.12221 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 392.705 | 0.0364373 | 498.724ms | 1997 | 30 | 93.6782 | 4849.67 | 0.0267988 | 6.27014 | 1(Win) | true |
| simdjson (reflection) | 318.534 | 0.184498 | 590.596ms | 1997 | 1280 | 155754 | 5978.92 | 0.0413079 | 7.73831 | 2(Loss) | true |
| Glaze | 289.552 | 0.060922 | 609.158ms | 1798 | 30 | 390.478 | 5921.93 | 0.0489465 | 8.51472 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 935.567 | 0.0528427 | 214.28ms | 1997 | 40 | 46.2846 | 2035.65 | 0.0695444 | 2.61296 | 1(Win) | true |
| simdjson (reflection) | 742.297 | 0.0421337 | 259.783ms | 1997 | 30 | 35.0575 | 2565.67 | 0.104045 | 3.30085 | 2(Loss) | true |
| Glaze | 584.172 | 0.0604561 | 311.961ms | 1798 | 80 | 251.923 | 2935.28 | 0.0281143 | 4.20104 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1769.78 | 0.2519 | 74.1422ms | 1313 | 160 | 508.238 | 707.531 | 0.268699 | 1.35047 | 1(Win) | true |
| simdjson (reflection) | 1037.1 | 0.0560904 | 130.664ms | 1313 | 160 | 73.3805 | 1207.38 | 0.489363 | 2.33652 | 2(Loss) | true |
| Glaze | 928.174 | 0.39052 | 139.232ms | 1313 | 2560 | 71055.5 | 1349.07 | 0.0263422 | 2.6155 | 3(Loss) | true |
| simdjson (ondemand) | 354.186 | 0.0148973 | 359.274ms | 1313 | 160 | 44.3817 | 3535.36 | 0.0213865 | 6.93988 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1968.41 | 0.077859 | 66.8416ms | 1313 | 320 | 78.4991 | 636.134 | 0.0378118 | 1.20712 | 1(Win) | true |
| simdjson (reflection) | 1111.4 | 0.0827746 | 120.53ms | 1313 | 30 | 26.092 | 1126.67 | 0.0354904 | 2.17157 | 2(Loss) | true |
| Glaze | 1006.16 | 0.0684327 | 127.748ms | 1313 | 80 | 58.0252 | 1244.51 | 0.331358 | 2.40732 | 3(Loss) | true |
| simdjson (ondemand) | 359.067 | 0.0299381 | 355.886ms | 1313 | 40 | 43.6 | 3487.3 | 0.190805 | 6.84933 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 384.947 | 0.4033 | 371.093ms | 1313 | 1280 | 220290 | 3252.85 | 0.00120086 | 6.38072 | 1(Win) | true |
| simdjson (reflection) | 372.832 | 0.112468 | 336.356ms | 1313 | 40 | 570.715 | 3358.55 | 0.272185 | 6.59099 | 2(Loss) | true |
| Glaze | 316.312 | 0.168668 | 392.923ms | 1313 | 30 | 1337.47 | 3958.67 | 0.278646 | 7.77492 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2612.15 | 0.0566135 | 55.578ms | 1313 | 320 | 23.5681 | 479.366 | 0.00456353 | 0.898025 | 1(Win) | true |
| simdjson (reflection) | 2547.08 | 0.0919347 | 57.4627ms | 1313 | 80 | 16.3416 | 491.613 | 0.226809 | 0.917527 | 2(Loss) | true |
| Glaze | 1317.14 | 0.0586613 | 102.126ms | 1313 | 80 | 24.8804 | 950.675 | 0.023673 | 1.82738 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1443.11 | 0.161745 | 286.996ms | 4215 | 30 | 608.947 | 2785.47 | 0.285625 | 1.69957 | 1(Win) | true |
| Glaze | 1061.15 | 0.058158 | 388.686ms | 4215 | 80 | 388.283 | 3788.09 | 0.294881 | 2.31783 | 2(Loss) | true |
| simdjson (reflection) | 1032.89 | 0.148515 | 388.069ms | 4215 | 4890 | 163357 | 3891.74 | 0.00876324 | 2.38041 | 3(Loss) | true |
| simdjson (ondemand) | 738.602 | 0.198389 | 550.191ms | 4215 | 1280 | 149218 | 5442.36 | 0.0348086 | 3.33604 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1909.25 | 0.35603 | 251.347ms | 4215 | 320 | 17980.2 | 2105.41 | 0.0552455 | 1.28083 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1269.44 | 0.0572687 | 354.807ms | 4215 | 80 | 263.086 | 3166.55 | 0.309651 | 1.93401 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1257.45 | 0.488196 | 357.908ms | 4215 | 320 | 77938.1 | 3196.72 | 0.0966766 | 1.95304 | 2(Tie) | true |
| simdjson (ondemand) | 805.089 | 0.0926031 | 533.452ms | 4215 | 80 | 1710.21 | 4992.91 | 0.0117653 | 3.05967 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1792.18 | 0.131532 | 228.568ms | 4215 | 160 | 1392.57 | 2242.94 | 0.159085 | 1.36547 | 1(Win) | true |
| simdjson (reflection) | 1589.1 | 0.125151 | 263.697ms | 4215 | 80 | 801.768 | 2529.56 | 0.394259 | 1.54192 | 2(Loss) | true |
| Glaze | 983.942 | 0.148557 | 414.14ms | 4215 | 4890 | 180115 | 4085.34 | 0.427005 | 2.50025 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5316.71 | 0.0535994 | 84.7605ms | 4215 | 2560 | 420.406 | 756.057 | 0.157076 | 0.449042 | 1(Win) | true |
| simdjson (reflection) | 4112.84 | 0.0640995 | 109.307ms | 4215 | 80 | 31.3986 | 977.362 | 0.062708 | 0.585519 | 2(Loss) | true |
| Glaze | 2510.71 | 0.0770219 | 161.225ms | 4215 | 30 | 45.6195 | 1601.03 | 0.0229071 | 0.970249 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1707.09 | 0.098647 | 70.1048ms | 1213 | 80 | 35.7494 | 677.65 | 0.0184495 | 1.39289 | 1(Win) | true |
| simdjson (reflection) | 1050.04 | 0.150154 | 113.096ms | 1213 | 40 | 109.456 | 1101.67 | 0.0582786 | 2.29773 | 2(Loss) | true |
| Glaze | 936.066 | 0.0526905 | 137.847ms | 1213 | 640 | 271.364 | 1235.82 | 0.0736571 | 2.57851 | 3(Loss) | true |
| simdjson (ondemand) | 321.563 | 0.136321 | 371.838ms | 1213 | 40 | 961.997 | 3597.45 | 0.239871 | 7.6434 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1907.19 | 0.101085 | 63.4011ms | 1213 | 160 | 60.1484 | 606.55 | 0.0206126 | 1.24163 | 1(Win) | true |
| simdjson (reflection) | 1123.9 | 0.073876 | 103.689ms | 1213 | 40 | 23.1276 | 1029.28 | 0.186676 | 2.14711 | 2(Loss) | true |
| Glaze | 959.997 | 0.285287 | 124.157ms | 1213 | 2560 | 30254.3 | 1205.01 | 0.116869 | 2.50437 | 3(Loss) | true |
| simdjson (ondemand) | 328.051 | 0.0249175 | 367.226ms | 1213 | 40 | 30.8821 | 3526.3 | 0.00850822 | 7.48965 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 355.208 | 0.241756 | 329.111ms | 1213 | 1280 | 79345.3 | 3256.7 | 0.00244694 | 6.91478 | 1(Win) | true |
| simdjson (reflection) | 349.011 | 0.0950758 | 378.673ms | 1213 | 40 | 397.23 | 3314.53 | 0.0736114 | 7.04207 | 2(Loss) | true |
| Glaze | 296.349 | 0.140533 | 408.182ms | 1213 | 30 | 902.809 | 3903.53 | 0.02477 | 8.29651 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2711.21 | 0.217603 | 51.2089ms | 1213 | 40 | 34.4814 | 426.675 | 0.38716 | 0.863623 | 1(Win) | true |
| simdjson (reflection) | 2557.89 | 0.0698682 | 53.5065ms | 1213 | 160 | 15.9748 | 452.25 | 0.127304 | 0.912217 | 2(Loss) | true |
| Glaze | 1354.68 | 0.385948 | 94.8548ms | 1213 | 30 | 325.857 | 853.933 | 0.0390198 | 1.77469 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21970 | 0.491425 | 2153.9ms | 466906 | 160 | 1.58721e+06 | 20267.5 | 0.0482223 | 0.112527 | 1(Win) | true |
| simdjson (ondemand) | 18262.2 | 0.0460164 | 2531.25ms | 466906 | 30 | 3776.6 | 24382.4 | 0.86897 | 0.135416 | 2(Loss) | true |
| Glaze | 2755.12 | 0.241248 | 8374.7ms | 466906 | 640 | 9.72937e+07 | 161618 | 0.208743 | 0.898464 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22070.6 | 0.177834 | 2061.39ms | 466906 | 640 | 823838 | 20175.1 | 0.18393 | 0.112023 | 1(Win) | true |
| simdjson (ondemand) | 18016.4 | 0.145337 | 2480.29ms | 466906 | 4890 | 6.30932e+06 | 24715 | 0.00977959 | 0.137254 | 2(Loss) | true |
| Glaze | 2662.81 | 0.256161 | 8280.39ms | 466906 | 80 | 1.4679e+07 | 167221 | 0.0318863 | 0.929583 | 3(Loss) | true |
