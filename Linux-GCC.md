# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **simdjson (reflection)** | `haswell` |
| **Glaze** | utf8: `AVX2`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX2` |

> **How the sampling/convergence works (Intel(R) Core(TM) i9-14900KF-AVX2):**  
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
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2416.46 | 0.123963 | 749.573ms | 905 | 4890 | 958.587 | 357.165 | 0.159371 | 2.35375 | 11.7072 | 1.86961 | 0.00111469 | 0.000113435 | 3.36689e-05 | 1(Win) | true |
| Glaze | 1821.44 | 0.133769 | 769.148ms | 905 | 2560 | 1028.53 | 473.842 | 0.0972644 | 3.07752 | 14.032 | 1.94917 | 0.00111576 | 0.000106181 | 5.52486e-05 | 2(Loss) | true |
| simdjson (reflection) | 1145.27 | 0.0820369 | 787.262ms | 905 | 2560 | 978.462 | 753.603 | 0.218005 | 4.74319 | 23.274 | 5.49061 | 0.0043996 | 9.92749e-05 | 3.79834e-05 | 3(Loss) | true |
| simdjson (ondemand) | 488.42 | 0.0351589 | 918.231ms | 905 | 4890 | 1887.52 | 1767.08 | 0.0820284 | 10.7923 | 50.8133 | 9.59227 | 0.0588609 | 0.000168796 | 2.41783e-05 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2643.35 | 0.0954824 | 739.763ms | 905 | 640 | 62.2034 | 326.508 | 0.253465 | 2.18757 | 11.0365 | 1.73039 | 0.0011067 | 6.38812e-05 | 5.17956e-06 | 1(Win) | true |
| Glaze | 1890.15 | 0.0318559 | 756.234ms | 905 | 4890 | 103.465 | 456.617 | 0.171901 | 2.95959 | 13.6652 | 2.06519 | 0.00113729 | 6.55301e-05 | 1.44618e-05 | 2(Loss) | true |
| simdjson (reflection) | 1188.27 | 0.0488318 | 786.693ms | 905 | 2560 | 322.044 | 726.332 | 0.181839 | 4.56445 | 22.7326 | 5.37127 | 0.00430162 | 0.000106181 | 2.15815e-05 | 3(Loss) | true |
| simdjson (ondemand) | 489.994 | 0.143263 | 892.363ms | 905 | 160 | 1018.83 | 1761.4 | 0.0326338 | 10.7475 | 50.1293 | 9.45304 | 0.0649931 | 0.00019337 | 0 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1798.74 | 0.0914238 | 758.048ms | 905 | 4890 | 940.995 | 479.821 | 0.282064 | 3.09915 | 11.0895 | 1.10276 | 0.00446712 | 5.87511e-05 | 1.9659e-05 | 1(Win) | true |
| simdjson (reflection) | 259.465 | 0.0685426 | 1048.29ms | 905 | 1280 | 6653.8 | 3326.36 | 0.0237863 | 20.066 | 95.1249 | 21.1436 | 0.0550898 | 0.000155387 | 2.41713e-05 | 2(Loss) | true |
| Glaze | 199.073 | 0.0426131 | 1177.7ms | 905 | 4890 | 16690.5 | 4335.47 | 0.126029 | 26.0715 | 111.054 | 23.5105 | 0.0883092 | 0.00026099 | 0.000100781 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3304.86 | 0.126856 | 738.942ms | 905 | 320 | 35.1207 | 261.153 | 0.0107707 | 1.79465 | 7.77459 | 0.271823 | 0.00221685 | 1.38122e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 3189.6 | 0.17671 | 744.095ms | 905 | 320 | 73.1642 | 270.591 | 0.0796233 | 1.85633 | 8.44862 | 1.05083 | 0.00116022 | 0.000141575 | 6.90608e-06 | 2(Loss) | true |
| Glaze | 684.641 | 0.049074 | 846.456ms | 905 | 80 | 30.6171 | 1260.62 | 0.00991473 | 7.76464 | 22.0398 | 3.36685 | 0.00553867 | 5.52486e-05 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1297.12 | 0.0462819 | 854.261ms | 1811 | 640 | 243.039 | 1331.49 | 0.0548896 | 4.10878 | 17.7747 | 3.6212 | 0.000980984 | 7.50621e-05 | 1.12162e-05 | 1(Win) | true |
| Glaze | 1037.82 | 0.0471959 | 883.835ms | 1811 | 2560 | 1579.23 | 1664.17 | 0.209079 | 5.08273 | 25.402 | 3.69188 | 0.000556064 | 0.000201891 | 5.52181e-05 | 2(Loss) | true |
| simdjson (ondemand) | 433.379 | 0.0596612 | 1118.14ms | 1811 | 2560 | 14471.9 | 3985.2 | 0.10667 | 11.9577 | 57.7504 | 11.4776 | 0.00150879 | 0.00024956 | 9.3612e-05 | 3(Loss) | true |
| simdjson (reflection) | 426.721 | 0.0823226 | 1126.13ms | 1811 | 2560 | 28420.1 | 4047.38 | 0.164565 | 12.1784 | 59.9023 | 11.9056 | 0.00134529 | 0.000257109 | 0.000119495 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1385.96 | 0.135436 | 842.443ms | 1811 | 2560 | 7291.99 | 1246.14 | 0.0134809 | 3.79851 | 16.8459 | 3.40972 | 0.000909805 | 0.00022799 | 8.67097e-05 | 1(Win) | true |
| Glaze | 1101.95 | 0.12916 | 874.281ms | 1811 | 1280 | 5245.37 | 1567.31 | 0.0134604 | 4.82884 | 24.7974 | 3.4804 | 0.00206033 | 0.00013028 | 2.89032e-05 | 2(Loss) | true |
| simdjson (ondemand) | 440.507 | 0.0654341 | 1108.92ms | 1811 | 2560 | 16849.2 | 3920.71 | 0.0461305 | 11.8315 | 56.7847 | 11.2662 | 0.00116131 | 0.000261208 | 7.89446e-05 | 3(Loss) | true |
| simdjson (reflection) | 416.755 | 0.083358 | 1134.49ms | 1811 | 2560 | 30549.9 | 4144.17 | 0.346476 | 12.4141 | 59.0812 | 11.6941 | 0.00113111 | 0.000413704 | 0.000192401 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 381.875 | 0.0328211 | 1215.95ms | 1997 | 4890 | 13101.8 | 4987.21 | 0.224039 | 13.6287 | 56.4497 | 9.65849 | 0.0128504 | 0.000191699 | 5.12015e-05 | 1(Win) | true |
| simdjson (reflection) | 366.342 | 0.0362943 | 1239.26ms | 1997 | 4890 | 17408.8 | 5198.66 | 0.0310602 | 14.1213 | 60.2429 | 10.7807 | 0.00858691 | 0.000198662 | 7.51639e-05 | 2(Loss) | true |
| Glaze | 272.417 | 0.0955313 | 1354.16ms | 1798 | 1280 | 46282 | 6294.42 | 0.705219 | 19.0797 | 77.9839 | 14.5161 | 0.0113985 | 0.000240284 | 7.56048e-05 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 960.528 | 0.0863576 | 921.69ms | 1997 | 320 | 938.182 | 1982.75 | 0.034032 | 5.47809 | 18.2639 | 0.948423 | 0.000500751 | 0.000226903 | 0.000117364 | 1(Win) | true |
| simdjson (reflection) | 844.59 | 0.160682 | 952.784ms | 1997 | 160 | 2100.47 | 2254.93 | 0.0266155 | 6.21408 | 19.2484 | 1.24286 | 0.00112043 | 5.32048e-05 | 2.19079e-05 | 2(Loss) | true |
| Glaze | 721.965 | 0.0771595 | 973.745ms | 1798 | 160 | 537.336 | 2375.06 | 0.0113142 | 7.39276 | 26.614 | 2.36263 | 0.000879449 | 0.000139043 | 8.69021e-05 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1837.85 | 0.152503 | 785.914ms | 1313 | 4890 | 5279.27 | 681.326 | 0.016974 | 2.96287 | 13.4813 | 2.46459 | 0.000764262 | 0.000138305 | 3.31746e-05 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 918.258 | 0.0540311 | 849.543ms | 1313 | 4890 | 2654.58 | 1363.64 | 0.230546 | 5.77837 | 27.5171 | 6.70373 | 0.00139941 | 0.000128026 | 3.25516e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 916.113 | 0.107553 | 851.965ms | 1313 | 30 | 64.8333 | 1366.83 | 0.226288 | 5.89185 | 24.4021 | 2.97563 | 0.000761615 | 0.000101549 | 0 | 2(Tie) | true |
| simdjson (ondemand) | 399.761 | 0.111286 | 1027.26ms | 1313 | 640 | 7776.54 | 3132.31 | 0.0327841 | 13.0451 | 55.243 | 10.933 | 0.00130308 | 0.000105912 | 2.38005e-06 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2218.76 | 0.11589 | 769.016ms | 1313 | 2560 | 1095.06 | 564.358 | 0.0269322 | 2.48542 | 12.0411 | 2.13861 | 0.00076935 | 0.000116622 | 2.94531e-05 | 1(Win) | true |
| simdjson (reflection) | 1044.12 | 0.190154 | 835.292ms | 1313 | 1280 | 6656.55 | 1199.26 | 0.151686 | 5.09542 | 26.246 | 6.38081 | 0.00166841 | 0.000212419 | 8.68717e-05 | 2(Loss) | true |
| Glaze | 978.547 | 0.152506 | 837.007ms | 1313 | 1280 | 4874.71 | 1279.63 | 0.0111739 | 5.41872 | 22.9589 | 2.64052 | 0.000778275 | 7.19964e-05 | 5.3551e-06 | 3(Loss) | true |
| simdjson (ondemand) | 413.18 | 0.0294475 | 1021.35ms | 1313 | 160 | 127.428 | 3030.57 | 0.10054 | 12.6378 | 53.7548 | 10.6101 | 0.00152323 | 0.000180883 | 4.76009e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 366.564 | 0.0698951 | 1064.07ms | 1313 | 80 | 456.05 | 3415.97 | 0.0358481 | 14.4805 | 69.1927 | 15.0335 | 0.0175838 | 0.000180883 | 0 | 1(Win) | true |
| simdjson (reflection) | 365.617 | 0.0661576 | 1059.63ms | 1313 | 160 | 821.403 | 3424.82 | 0.194885 | 14.2555 | 68.9733 | 14.9185 | 0.0152371 | 0.000390327 | 8.09216e-05 | 2(Loss) | true |
| Glaze | 316.266 | 0.047672 | 1115.13ms | 1313 | 2560 | 9119.92 | 3959.25 | 0.377935 | 16.4438 | 77.4501 | 15.3869 | 0.0313181 | 0.000422161 | 0.000194569 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3120.68 | 0.226258 | 765.656ms | 1313 | 80 | 65.9367 | 401.25 | 0.0748223 | 1.81712 | 8.69459 | 1.03275 | 0.000761615 | 5.71211e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 2842 | 0.105293 | 777.008ms | 1313 | 4890 | 1052.43 | 440.597 | 0.196951 | 1.97808 | 8.97411 | 1.03275 | 0.000764107 | 0.000169923 | 6.61935e-05 | 2(Loss) | true |
| Glaze | 1045.5 | 0.0978382 | 864.476ms | 1313 | 160 | 219.692 | 1197.67 | 0.0720664 | 5.09854 | 19.3252 | 2.52399 | 0.00129474 | 0.000161843 | 7.61615e-05 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1377.11 | 0.083338 | 1012.96ms | 4215 | 640 | 3787.23 | 2918.96 | 0.116562 | 3.79078 | 17.4771 | 3.1331 | 0.000465599 | 4.67082e-05 | 1.29745e-05 | 1(Win) | true |
| Glaze | 1002.06 | 0.049956 | 1123ms | 4215 | 2560 | 10280.7 | 4011.48 | 0.103123 | 5.15401 | 23.5224 | 4.66857 | 0.00145509 | 7.33986e-05 | 7.7847e-06 | 2(Loss) | true |
| simdjson (reflection) | 972.276 | 0.0313669 | 1138.98ms | 4215 | 4890 | 8223.73 | 4134.36 | 0.227851 | 5.26807 | 21.5898 | 4.52883 | 0.00158752 | 7.5929e-05 | 3.06627e-05 | 3(Loss) | true |
| simdjson (ondemand) | 917.763 | 0.0393831 | 1160.64ms | 4215 | 4890 | 14550 | 4379.93 | 0.0357606 | 5.63595 | 25.7144 | 4.23772 | 0.00258338 | 6.03551e-05 | 1.63017e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1978.63 | 0.0335525 | 972.684ms | 4215 | 4890 | 2272.09 | 2031.58 | 0.208886 | 2.65414 | 12.8567 | 2.01827 | 0.000971309 | 3.83284e-05 | 3.78432e-06 | 1(Win) | true |
| Glaze | 1339.56 | 0.0979767 | 1069.54ms | 4215 | 160 | 1383.04 | 3000.78 | 0.0873452 | 3.89738 | 18.9642 | 3.56062 | 0.00187426 | 4.15184e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 1268.32 | 0.148005 | 1094.3ms | 4215 | 320 | 7041.13 | 3169.35 | 0.22617 | 4.10953 | 16.8842 | 3.43013 | 0.00191355 | 3.85528e-05 | 9.6382e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1137.65 | 0.0529166 | 1123.62ms | 4215 | 2560 | 8949.62 | 3533.38 | 0.050232 | 4.5681 | 21.5563 | 3.20902 | 0.00227193 | 4.55034e-05 | 6.48725e-06 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1577.36 | 0.0562879 | 983.142ms | 4215 | 2560 | 5267.49 | 2548.4 | 0.00821662 | 3.27878 | 14.3535 | 2.82539 | 0.00110904 | 7.92371e-05 | 2.28907e-05 | 1(Win) | true |
| simdjson (reflection) | 1451.2 | 0.047451 | 1002.64ms | 4215 | 2560 | 4422.56 | 2769.95 | 0.00430137 | 3.53313 | 15.3979 | 3.05931 | 0.00110626 | 7.40473e-05 | 1.68668e-05 | 2(Loss) | true |
| Glaze | 929.324 | 0.115943 | 1161.07ms | 4215 | 640 | 16096.6 | 4325.44 | 0.119458 | 5.4815 | 28.0553 | 5.90558 | 0.00359468 | 7.59935e-05 | 1.33452e-05 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4751.96 | 0.0926658 | 827.854ms | 4215 | 2560 | 1573 | 845.911 | 0.0168521 | 1.12279 | 5.32408 | 0.592408 | 0.000956128 | 2.63197e-05 | 3.89235e-06 | 1(Win) | true |
| simdjson (reflection) | 4445.18 | 0.149243 | 831.71ms | 4215 | 2560 | 4662.78 | 904.291 | 0.0997112 | 1.19201 | 6.24887 | 0.71815 | 0.000674118 | 3.10461e-05 | 8.98947e-06 | 2(Loss) | true |
| Glaze | 2797.54 | 0.0489053 | 893.219ms | 4215 | 4890 | 2414.7 | 1436.88 | 0.127922 | 1.8621 | 9.10605 | 1.49395 | 0.00113937 | 4.48782e-05 | 1.65443e-05 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1894.02 | 0.11974 | 774.814ms | 1213 | 640 | 342.303 | 610.769 | 0.0860312 | 2.89959 | 13.488 | 2.28195 | 0.000874639 | 0.000171321 | 4.63726e-05 | 1(Win) | true |
| simdjson (reflection) | 994.069 | 0.0735276 | 827.987ms | 1213 | 4890 | 3580.13 | 1163.71 | 0.0860232 | 5.36366 | 26.6208 | 6.20363 | 0.000832663 | 0.000169264 | 6.9796e-05 | 2(Loss) | true |
| Glaze | 848.208 | 0.0534911 | 851.422ms | 1213 | 80 | 42.5766 | 1363.83 | 0.0311526 | 6.24682 | 23.2201 | 3.35284 | 0.00120569 | 0.00016488 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 377.388 | 0.0371487 | 1022.48ms | 1213 | 4890 | 6340.77 | 3065.3 | 0.409651 | 13.8285 | 58.7238 | 11.8054 | 0.00421187 | 0.00014701 | 5.85005e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2192.21 | 0.130017 | 773.015ms | 1213 | 4890 | 2301.8 | 527.691 | 0.198847 | 2.50663 | 12.0998 | 1.97115 | 0.00191214 | 0.000124419 | 2.30968e-05 | 1(Win) | true |
| simdjson (reflection) | 1093.72 | 0.200531 | 832.012ms | 1213 | 320 | 1439.54 | 1057.68 | 0.866935 | 4.89149 | 25.202 | 5.83759 | 0.00189097 | 0.000115932 | 2.57626e-06 | 2(Loss) | true |
| Glaze | 883.86 | 0.0478392 | 849.82ms | 1213 | 320 | 125.451 | 1308.81 | 0.0977983 | 5.91773 | 21.6867 | 3.00165 | 0.00086047 | 8.75927e-05 | 1.0305e-05 | 3(Loss) | true |
| simdjson (ondemand) | 378.291 | 0.0798308 | 1029.14ms | 1213 | 1280 | 7628.16 | 3057.98 | 0.0234074 | 13.7878 | 57.2605 | 11.4946 | 0.0075085 | 0.000280168 | 0.000108847 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 343.15 | 0.0543478 | 1055.94ms | 1213 | 2560 | 8593.24 | 3371.14 | 0.0495345 | 15.1731 | 73.4823 | 16.1113 | 0.0179633 | 0.000315914 | 8.30843e-05 | 1(Win) | true |
| Jsonifier | 338.841 | 0.0336827 | 1057.08ms | 1213 | 4890 | 6466.24 | 3414.01 | 0.065921 | 15.3991 | 73.451 | 16.2036 | 0.0205817 | 0.000287445 | 5.88377e-05 | 2(Loss) | true |
| Glaze | 296.666 | 0.0589829 | 1107.95ms | 1213 | 1280 | 6770.96 | 3899.36 | 0.0339684 | 17.5334 | 84.5787 | 17.6496 | 0.0333748 | 0.000407049 | 0.000171321 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3157.98 | 0.220124 | 776.936ms | 1213 | 80 | 52.015 | 366.312 | 0.146948 | 1.77997 | 8.39736 | 1.11789 | 0.000824402 | 6.18302e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 3035 | 0.0318297 | 780.693ms | 1213 | 4890 | 71.9743 | 381.156 | 0.0163383 | 1.853 | 8.70074 | 1.11789 | 0.000824402 | 0.000117675 | 4.99025e-05 | 2(Loss) | true |
| Glaze | 953.622 | 0.0673793 | 861.715ms | 1213 | 2560 | 1710.26 | 1213.07 | 0.165144 | 5.48004 | 19.723 | 2.73207 | 0.000856283 | 0.000129457 | 2.86609e-05 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1845.84 | 0.104209 | 5606.69ms | 94653 | 80 | 207771 | 48903.5 | 0.0497927 | 2.7442 | 12.3107 | 2.36913 | 0.00807449 | 1.36023e-05 | 1.05649e-05 | 1(Win) | true |
| simdjson (reflection) | 1418.01 | 0.0223261 | 7149.63ms | 94653 | 2560 | 517099 | 63658.2 | 0.204855 | 3.57124 | 14.2028 | 2.61341 | 0.00750019 | 2.47244e-05 | 1.73042e-05 | 2(Loss) | true |
| Glaze | 1402.77 | 0.0807341 | 7185.31ms | 94653 | 4890 | 1.31983e+07 | 64349.8 | 0.156278 | 3.615 | 15.529 | 3.09425 | 0.0143575 | 1.95483e-05 | 8.8689e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1384.23 | 0.0179778 | 7251.29ms | 94653 | 4890 | 672098 | 65211.8 | 0.171881 | 3.6637 | 16.9069 | 2.9515 | 0.0145253 | 1.5815e-05 | 1.01976e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1330.5 | 0.0619506 | 7513.58ms | 94653 | 640 | 1.1306e+06 | 67845.1 | 0.0926391 | 3.82786 | 14.4659 | 2.89504 | 0.0179443 | 1.4015e-05 | 8.99668e-06 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3021.56 | 0.0443699 | 4968.63ms | 94653 | 1280 | 224902 | 29874.7 | 0.103461 | 1.68555 | 8.35321 | 1.47237 | 0.00484233 | 4.80373e-06 | 1.90664e-06 | 1(Win) | true |
| Glaze | 2004.14 | 0.0495961 | 6496.89ms | 94653 | 4890 | 2.44015e+06 | 45040.8 | 0.0791348 | 2.52974 | 11.7749 | 2.2388 | 0.0090066 | 1.23365e-05 | 7.26364e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1995.23 | 0.023284 | 6539.07ms | 94653 | 2560 | 284078 | 45241.9 | 0.043103 | 2.5404 | 12.9373 | 2.05323 | 0.0090635 | 8.88112e-06 | 4.9523e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1982.9 | 0.0408423 | 6522.36ms | 94653 | 1280 | 442484 | 45523.3 | 0.00239055 | 2.5615 | 10.6423 | 2.02181 | 0.00717921 | 2.23514e-05 | 1.81089e-05 | 4(Loss) | true |
| simdjson (reflection) | 1820.07 | 0.0374514 | 6931.96ms | 94653 | 640 | 220806 | 49596 | 0.0169497 | 2.77998 | 11.1315 | 1.89809 | 0.00421371 | 8.60049e-06 | 5.13388e-06 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15979.2 | 0.0677487 | 1306.13ms | 94653 | 1280 | 18748.7 | 5649.11 | 0.00305644 | 0.318443 | 1.28806 | 0.180354 | 6.4025e-05 | 5.80244e-06 | 2.60821e-06 | 1(Win) | true |
| simdjson (reflection) | 13783.8 | 0.0700153 | 1395.58ms | 94653 | 2560 | 53821.3 | 6548.84 | 0.286839 | 0.367334 | 2.03779 | 0.29568 | 2.18231e-05 | 1.02843e-05 | 4.15168e-06 | 2(Loss) | true |
| Glaze | 7890.18 | 0.0553437 | 1887.23ms | 94653 | 1280 | 51314.6 | 11440.6 | 0.00540868 | 0.644474 | 3.47099 | 0.569174 | 6.60719e-05 | 8.0805e-06 | 3.11995e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16150.4 | 0.116396 | 1296.11ms | 94653 | 30 | 1269.7 | 5589.23 | 0.0525094 | 0.315524 | 1.28243 | 0.179086 | 7.43065e-05 | 7.04327e-06 | 5.28245e-06 | 1(Win) | true |
| simdjson (reflection) | 13912.5 | 0.053358 | 1389ms | 94653 | 2560 | 30682.7 | 6488.25 | 0.128794 | 0.364178 | 2.03222 | 0.294423 | 3.22519e-05 | 4.60151e-06 | 2.146e-06 | 2(Loss) | true |
| Glaze | 9376.73 | 0.0910448 | 1714.05ms | 94653 | 320 | 24582.5 | 9626.83 | 0.000844003 | 0.541824 | 3.41879 | 0.557426 | 6.13095e-05 | 6.80116e-06 | 4.62215e-06 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2138.53 | 0.0446537 | 6307.84ms | 124597 | 640 | 393986 | 55563.9 | 0.0758629 | 2.3729 | 10.6134 | 2.03791 | 0.00822072 | 3.68689e-06 | 1.01577e-06 | 1(Win) | true |
| simdjson (reflection) | 1801.83 | 0.0200738 | 7352.95ms | 124597 | 4890 | 856957 | 65946.9 | 0.136842 | 2.81717 | 11.1532 | 2.00615 | 0.00666982 | 1.44417e-05 | 8.50841e-06 | 2(Loss) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1655.64 | 0.103394 | 7949.39ms | 124597 | 160 | 881039 | 71769.6 | 0.0335162 | 3.06926 | 13.5921 | 2.3498 | 0.0113774 | 3.46116e-06 | 1.3042e-06 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1653.34 | 0.1134 | 7432.59ms | 124597 | 40 | 265692 | 71869.5 | 0.122491 | 3.05772 | 11.3465 | 2.21697 | 0.0154681 | 3.93268e-05 | 3.23041e-05 | 3(Tie) | true |
| Glaze | 1622.1 | 0.0365738 | 8066.91ms | 124597 | 2560 | 1.83755e+06 | 73253.9 | 0.0592333 | 3.12077 | 13.7826 | 2.74153 | 0.0141065 | 2.58145e-05 | 1.72744e-05 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3390.57 | 0.0391569 | 5485.16ms | 124597 | 2560 | 482087 | 35045.7 | 0.0462914 | 1.50115 | 7.60636 | 1.35953 | 0.00474792 | 1.3343e-05 | 4.90958e-06 | 1(Win) | true |
| simdjson (ondemand) | 2531.35 | 0.0566166 | 6674.17ms | 124597 | 320 | 226021 | 46941.4 | 0.118232 | 2.00092 | 8.41824 | 1.55112 | 0.00569963 | 1.87103e-05 | 1.40704e-05 | 2(Loss) | true |
| simdjson (reflection) | 2331.02 | 0.0274721 | 7091.99ms | 124597 | 2560 | 502050 | 50975.4 | 0.0424143 | 2.17419 | 8.7865 | 1.45669 | 0.00307387 | 2.3275e-05 | 1.60518e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 2238.99 | 0.0749905 | 7296.37ms | 124597 | 320 | 506845 | 53070.9 | 0.0606309 | 2.25976 | 10.5819 | 1.67189 | 0.00866298 | 9.27992e-06 | 6.39562e-06 | 4(Loss) | true |
| Glaze | 2193.07 | 0.0669396 | 7378.71ms | 124597 | 80 | 105237 | 54182.1 | 0.113566 | 2.30636 | 10.9245 | 2.09235 | 0.00965332 | 4.41423e-06 | 8.02588e-07 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18400.8 | 0.0426493 | 1440.7ms | 136037 | 640 | 5786.85 | 7050.49 | 0.147058 | 0.275789 | 0.929652 | 0.125958 | 2.67505e-05 | 3.75587e-06 | 1.60802e-06 | 1(Win) | true |
| Glaze | 7235.71 | 0.0389962 | 2529.43ms | 136076 | 4890 | 239196 | 17935 | 0.118402 | 0.696382 | 3.79803 | 0.637813 | 5.17815e-05 | 4.7264e-06 | 1.49231e-06 | 2(Loss) | true |
| simdjson (reflection) | 642.05 | 0.134048 | 5310.77ms | 136037 | 1280 | 9.39096e+07 | 202064 | 0.0859994 | 7.85924 | 34.7218 | 7.10838 | 0.0276165 | 0.00673625 | 6.53659e-05 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18577 | 0.0343131 | 1436.32ms | 136037 | 2560 | 14700.2 | 6983.65 | 0.0722986 | 0.273705 | 0.925741 | 0.125084 | 5.01386e-05 | 2.60154e-06 | 8.55696e-07 | 1(Win) | true |
| Glaze | 8249.29 | 0.0197256 | 2310.22ms | 136076 | 4890 | 47086.9 | 15731.3 | 0.156726 | 0.614723 | 3.76371 | 0.630104 | 4.94371e-05 | 7.15347e-06 | 4.58062e-06 | 2(Loss) | true |
| simdjson (reflection) | 628.417 | 0.150195 | 5445.03ms | 136037 | 1280 | 1.23067e+08 | 206447 | 0.119454 | 8.01298 | 34.7252 | 7.10928 | 0.0278288 | 0.0282963 | 3.56865e-05 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 941.555 | 0.125917 | 7097.32ms | 2251027 | 160 | 1.31875e+09 | 2.28e+06 | 0.0161854 | 5.39515 | 28.4813 | 5.98156 | 0.0148085 | 0.0647561 | 0.000101931 | 1(Win) | true |
| Glaze | 848.966 | 0.0653564 | 7913.06ms | 2251027 | 160 | 4.36997e+08 | 2.52866e+06 | 0.268654 | 5.99296 | 30.2914 | 5.63895 | 0.00984623 | 0.0638828 | 0.000290379 | 2(Loss) | true |
| simdjson (reflection) | 844.01 | 0.0662718 | 7914.85ms | 2251027 | 160 | 4.54614e+08 | 2.54351e+06 | 0.0212006 | 5.9762 | 29.0609 | 5.33625 | 0.010857 | 0.101287 | 0.000976593 | 3(Loss) | true |
| Jsonifier (two-stage) | 804.433 | 0.0835177 | 8344.15ms | 2251027 | 30 | 1.49025e+08 | 2.66864e+06 | 0.00430662 | 6.28448 | 31.4667 | 6.35087 | 0.0225793 | 0.102844 | 0.000386031 | 4(Loss) | true |
| simdjson (ondemand) | 768.022 | 0.12996 | 8720.41ms | 2251027 | 30 | 3.95874e+08 | 2.79516e+06 | 0.107375 | 6.5996 | 30.7405 | 5.87541 | 0.0147981 | 0.109234 | 0.000452134 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1120.28 | 0.188343 | 7112.05ms | 2251027 | 30 | 3.90778e+08 | 1.91626e+06 | 0.0116655 | 4.52913 | 23.5703 | 4.81036 | 0.01421 | 0.0418605 | 1.85989e-05 | 1(Win) | true |
| simdjson (reflection) | 996.981 | 0.108794 | 7852.62ms | 2251027 | 80 | 4.39024e+08 | 2.15325e+06 | 0.0268766 | 5.0659 | 24.1863 | 4.17411 | 0.0092006 | 0.0751126 | 0.000631739 | 2(Loss) | true |
| Glaze | 990.692 | 0.146093 | 7916.99ms | 2251027 | 160 | 1.60348e+09 | 2.16692e+06 | 0.116543 | 5.11313 | 25.3558 | 4.46507 | 0.00896989 | 0.0408914 | 0.00186168 | 3(Loss) | true |
| Jsonifier (two-stage) | 934.852 | 0.108713 | 8348.1ms | 2251027 | 40 | 2.49285e+08 | 2.29635e+06 | 0.0636164 | 5.41848 | 26.6038 | 5.19389 | 0.0220297 | 0.0790764 | 0.000435013 | 4(Loss) | true |
| simdjson (ondemand) | 901.128 | 0.170024 | 8609.02ms | 2251027 | 30 | 4.92187e+08 | 2.38229e+06 | 0.160834 | 5.60456 | 25.8218 | 4.70742 | 0.0112715 | 0.0769222 | 0.000179222 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2097.9 | 0.0353096 | 6076.16ms | 2090326 | 320 | 3.60241e+07 | 950231 | 0.0224211 | 2.4468 | 7.77177 | 0.373354 | 0.00033621 | 0.0517397 | 7.6579e-05 | 1(Win) | true |
| simdjson (reflection) | 1591.86 | 0.12542 | 7919.08ms | 2090326 | 40 | 9.86752e+07 | 1.2523e+06 | 0.0965548 | 3.18874 | 10.1384 | 0.578353 | 0.00492014 | 0.0511321 | 0.000327341 | 2(Loss) | true |
| Glaze | 1463.81 | 0.0961356 | 8635.85ms | 2090234 | 320 | 5.48451e+08 | 1.36179e+06 | 0.0518504 | 3.43985 | 9.59421 | 0.598242 | 0.0117291 | 0.0698452 | 0.000336093 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2086.26 | 0.148767 | 6081ms | 2090326 | 30 | 6.06219e+07 | 955535 | 0.130465 | 2.444 | 7.7716 | 0.37332 | 0.000343567 | 0.0517533 | 4.47299e-05 | 1(Win) | true |
| simdjson (reflection) | 1616.94 | 0.0126699 | 7861.79ms | 2090326 | 80 | 1.95197e+06 | 1.23287e+06 | 0.175172 | 3.18224 | 10.1382 | 0.578319 | 0.00484789 | 0.0510773 | 7.34873e-05 | 2(Loss) | true |
| Glaze | 1547.61 | 0.0597809 | 8182.23ms | 2090234 | 160 | 9.48659e+07 | 1.28805e+06 | 0.131306 | 3.28216 | 9.5901 | 0.597292 | 0.0117445 | 0.0437892 | 6.50794e-05 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1992.79 | 0.133028 | 8027.09ms | 5373214 | 30 | 3.51038e+08 | 2.57141e+06 | 0.0969848 | 2.54418 | 13.7654 | 2.865 | 0.00567397 | 0.038532 | 0.000120071 | 1(Win) | true |
| Jsonifier (two-stage) | 1898.03 | 0.1248 | 8367.04ms | 5373214 | 40 | 4.54101e+08 | 2.69979e+06 | 0.102657 | 2.65863 | 13.9912 | 2.70406 | 0.00702365 | 0.0626048 | 0.00201908 | 2(Loss) | true |
| simdjson (reflection) | 1883.8 | 0.144045 | 8451.74ms | 5373214 | 40 | 6.14123e+08 | 2.72019e+06 | 0.0651701 | 2.67878 | 12.9387 | 2.26858 | 0.00468605 | 0.061363 | 0.000519996 | 3(Loss) | true |
| simdjson (ondemand) | 1714.46 | 0.0548741 | 9290.75ms | 5373214 | 80 | 2.15197e+08 | 2.98886e+06 | 0.0549539 | 2.94489 | 13.642 | 2.49411 | 0.00628621 | 0.0649196 | 0.000207646 | 4(Loss) | true |
| Glaze | 1622.4 | 0.167182 | 9895.94ms | 5373214 | 40 | 1.1153e+09 | 3.15846e+06 | 0.29692 | 3.13366 | 15.9048 | 2.91967 | 0.00493311 | 0.0411465 | 5.87079e-05 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2316.84 | 0.057596 | 8042.08ms | 5373214 | 160 | 2.59645e+08 | 2.21176e+06 | 0.0952353 | 2.18289 | 11.7314 | 2.38101 | 0.00532936 | 0.0281163 | 0.000410512 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2208.83 | 0.0747567 | 8371.03ms | 5373214 | 160 | 4.81243e+08 | 2.31992e+06 | 0.0410544 | 2.29206 | 11.9583 | 2.22019 | 0.00672829 | 0.0523718 | 0.00012833 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2205.12 | 0.216888 | 8340.36ms | 5373214 | 30 | 7.62075e+08 | 2.32382e+06 | 0.0997456 | 2.29707 | 10.8976 | 1.78195 | 0.00405931 | 0.0500181 | 0.000869287 | 2(Tie) | true |
| simdjson (ondemand) | 2012.57 | 0.0479993 | 9101.68ms | 5373214 | 160 | 2.38978e+08 | 2.54615e+06 | 0.251875 | 2.50799 | 11.5823 | 2.00522 | 0.00492352 | 0.0508827 | 0.00027584 | 4(Loss) | true |
| Glaze | 1828.29 | 0.150664 | 9849.89ms | 5373214 | 160 | 2.85311e+09 | 2.80278e+06 | 0.0429736 | 2.77062 | 13.8601 | 2.43497 | 0.00444959 | 0.0302188 | 0.000114148 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6099.53 | 0.0597675 | 6601.1ms | 6661989 | 40 | 1.55026e+07 | 1.04162e+06 | 0.0437342 | 0.828052 | 2.48939 | 0.117147 | 0.000111198 | 0.0280193 | 8.76615e-06 | 1(Win) | true |
| Glaze | 3305.5 | 0.0700533 | 5990.61ms | 6661897 | 160 | 2.90069e+08 | 1.92204e+06 | 0.110945 | 1.52272 | 4.33449 | 0.464354 | 0.00373771 | 0.0636043 | 0.00186125 | 2(Loss) | true |
| simdjson (reflection) | 445.055 | 0.384859 | 10072.6ms | 6661989 | 40 | 1.20738e+11 | 1.42755e+07 | 0.900933 | 11.3311 | 36.3504 | 4.85759 | 0.0133646 | 0.25507 | 0.0942898 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6108.12 | 0.0327948 | 6600.37ms | 6661989 | 320 | 3.72352e+07 | 1.04015e+06 | 0.254739 | 0.827813 | 2.48933 | 0.117136 | 0.000103562 | 0.0280004 | 5.44812e-05 | 1(Win) | true |
| Glaze | 3953.93 | 0.107708 | 5020.97ms | 6661897 | 30 | 8.9858e+07 | 1.60683e+06 | 0.00531303 | 1.28116 | 4.33307 | 0.464028 | 0.00373031 | 0.0248209 | 6.23846e-05 | 2(Loss) | true |
| simdjson (reflection) | 443.771 | 0.392312 | 10132.3ms | 6661989 | 30 | 9.46398e+10 | 1.43168e+07 | 0.0868034 | 11.3872 | 36.3409 | 4.85387 | 0.0134874 | 0.255256 | 0.0986744 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2562.6 | 0.0516321 | 9922.75ms | 500299 | 640 | 5.91449e+06 | 186187 | 0.000824938 | 1.98335 | 9.65309 | 1.69343 | 0.00755361 | 0.00115139 | 4.97921e-05 | 1(Win) | true |
| Glaze | 1985.98 | 0.100559 | 6358.8ms | 500299 | 160 | 9.3384e+06 | 240245 | 0.0816475 | 2.58581 | 11.5064 | 2.23425 | 0.010149 | 0.000420723 | 4.07881e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1924.41 | 0.0689864 | 6560.55ms | 500299 | 320 | 9.36143e+06 | 247932 | 0.160563 | 2.64936 | 12.5476 | 2.15832 | 0.0109177 | 0.0147633 | 0.000117523 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1546.03 | 0.0455203 | 8080.54ms | 500299 | 640 | 1.26303e+07 | 308612 | 0.112287 | 3.30484 | 13.703 | 2.37513 | 0.01542 | 0.0140077 | 0.000228417 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1543.34 | 0.0977383 | 8149.37ms | 500299 | 160 | 1.46078e+07 | 309149 | 0.0857789 | 3.32367 | 14.0855 | 2.42378 | 0.0137424 | 0.0144597 | 0.000182866 | 4(Tie) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3122.23 | 0.0453814 | 9745.9ms | 500299 | 640 | 3.07799e+06 | 152815 | 0.0350639 | 1.63192 | 8.53478 | 1.41854 | 0.00575996 | 0.000760139 | 3.83271e-05 | 1(Win) | true |
| Glaze | 2300.05 | 0.0611841 | 6298.27ms | 500299 | 640 | 1.03096e+07 | 207440 | 0.236488 | 2.20997 | 10.3983 | 1.96307 | 0.0067282 | 0.000424755 | 4.64347e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2255.17 | 0.0752965 | 6374.55ms | 500299 | 160 | 4.06041e+06 | 211568 | 0.0794376 | 2.24694 | 11.4214 | 1.88186 | 0.00791608 | 0.0116472 | 0.000147787 | 3(Loss) | true |
| simdjson (reflection) | 1802.18 | 0.0695711 | 7812.39ms | 500299 | 320 | 1.0856e+07 | 264748 | 0.0501182 | 2.83362 | 12.6263 | 2.11198 | 0.00985286 | 0.0147089 | 0.000140635 | 4(Loss) | true |
| simdjson (ondemand) | 1779.58 | 0.0429024 | 7782.42ms | 500299 | 640 | 8.46771e+06 | 268109 | 0.05188 | 2.84812 | 13.0174 | 2.16015 | 0.00829576 | 0.00825566 | 0.000141072 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 12475.9 | 0.0249047 | 4565.12ms | 500299 | 4890 | 443597 | 38243.6 | 0.139821 | 0.410244 | 1.90811 | 0.192687 | 0.00104183 | 0.000743118 | 1.25467e-05 | 1(Win) | true |
| Jsonifier | 11751.9 | 0.0292688 | 4819.97ms | 500299 | 4890 | 690497 | 40599.5 | 0.0104405 | 0.4374 | 1.8325 | 0.215383 | 0.00158027 | 0.00476323 | 1.92956e-05 | 2(Loss) | true |
| Glaze | 6291.86 | 0.164022 | 8467.05ms | 500299 | 30 | 464116 | 75831.6 | 0.00896643 | 0.818382 | 3.76548 | 0.550691 | 0.00158012 | 0.0203306 | 8.1418e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 12537.1 | 0.0646204 | 4571.79ms | 500299 | 320 | 193533 | 38056.8 | 0.0915753 | 0.411001 | 1.90708 | 0.192453 | 0.00106934 | 0.000658025 | 7.35185e-06 | 1(Win) | true |
| Jsonifier | 11833.6 | 0.0673988 | 4827.73ms | 500299 | 640 | 472617 | 40319.2 | 0.0169865 | 0.434852 | 1.83144 | 0.215147 | 0.00157264 | 0.0044868 | 1.6968e-05 | 2(Loss) | true |
| Glaze | 7261.99 | 0.0246532 | 7324.69ms | 500299 | 4890 | 1.28294e+06 | 65701.4 | 0.00155346 | 0.70138 | 3.75128 | 0.547385 | 0.00156064 | 0.000691088 | 2.44688e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4063.17 | 0.157259 | 7164.46ms | 1151920 | 40 | 7.23116e+06 | 270370 | 0.0751553 | 1.25332 | 6.07408 | 1.12477 | 0.00431375 | 0.0188824 | 3.31837e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 3678.74 | 0.0933105 | 7882.99ms | 1151920 | 160 | 1.2423e+07 | 298623 | 0.106286 | 1.38664 | 6.25494 | 0.981089 | 0.00616599 | 0.0559524 | 4.75076e-05 | 2(Loss) | true |
| simdjson (reflection) | 3048.52 | 0.0348732 | 9388.57ms | 1151920 | 640 | 1.01072e+07 | 360357 | 0.0558474 | 1.66072 | 6.74803 | 1.07317 | 0.00746618 | 0.0478817 | 7.00217e-05 | 3(Loss) | true |
| simdjson (ondemand) | 3010.27 | 0.0385355 | 9497.99ms | 1151920 | 640 | 1.26571e+07 | 364936 | 0.149291 | 1.67926 | 6.91583 | 1.09448 | 0.00721283 | 0.0490629 | 5.57995e-05 | 4(Loss) | true |
| Glaze | 2583.59 | 0.0371278 | 5508.31ms | 1151920 | 640 | 1.59506e+07 | 425206 | 0.174055 | 1.96172 | 8.47786 | 1.61279 | 0.00713728 | 0.0146642 | 5.96436e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4700.11 | 0.113082 | 6988.84ms | 1151920 | 320 | 2.23544e+07 | 233730 | 0.229182 | 1.07618 | 5.58836 | 1.00638 | 0.00312953 | 0.0130369 | 1.32822e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 4216.11 | 0.0334907 | 7769.6ms | 1151920 | 640 | 4.87357e+06 | 260561 | 0.14747 | 1.20022 | 5.77047 | 0.863063 | 0.0049035 | 0.0478785 | 2.15293e-05 | 2(Loss) | true |
| simdjson (reflection) | 3571.92 | 0.0515026 | 8953.1ms | 1151920 | 320 | 8.02878e+06 | 307554 | 0.115374 | 1.41666 | 6.25085 | 0.951377 | 0.00486354 | 0.0372736 | 2.9874e-05 | 3(Loss) | true |
| simdjson (ondemand) | 3565.72 | 0.0449306 | 8927.59ms | 1151920 | 640 | 1.22635e+07 | 308088 | 0.00576015 | 1.43015 | 6.42358 | 0.973279 | 0.00442324 | 0.0370321 | 7.32134e-05 | 4(Loss) | true |
| Glaze | 2883.64 | 0.0510355 | 5405.53ms | 1151920 | 320 | 1.20964e+07 | 380962 | 0.210138 | 1.75912 | 7.99323 | 1.49521 | 0.00532454 | 0.00982514 | 2.18195e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18512.2 | 0.0375341 | 8246.89ms | 1439562 | 4890 | 3.78882e+06 | 74160.3 | 0.0169998 | 0.275876 | 0.694256 | 0.0753139 | 0.00050395 | 0.0187126 | 2.99384e-06 | 1(Win) | true |
| Glaze | 5775.71 | 0.0766274 | 6288.97ms | 1439584 | 1280 | 4.2466e+07 | 237701 | 0.321531 | 0.874589 | 3.12248 | 0.499194 | 0.000874132 | 0.0618603 | 1.07437e-05 | 2(Loss) | true |
| simdjson (reflection) | 575.822 | 1.02754 | 7333.94ms | 1439562 | 40 | 2.40075e+10 | 2.3842e+06 | 0.408509 | 8.71327 | 35.5653 | 6.42571 | 0.0157799 | 0.312585 | 0.000826571 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18556.8 | 0.0289021 | 8209.26ms | 1439562 | 2560 | 1.17045e+06 | 73982.1 | 0.0763269 | 0.274819 | 0.693874 | 0.0752278 | 0.000506145 | 0.0186149 | 3.52185e-06 | 1(Win) | true |
| Glaze | 7923.49 | 0.0588382 | 9274.41ms | 1439584 | 2560 | 2.66073e+07 | 173269 | 0.00766164 | 0.638453 | 3.11679 | 0.497885 | 0.000866907 | 0.0181163 | 1.29095e-05 | 2(Loss) | true |
| simdjson (reflection) | 579.554 | 0.934702 | 7356.16ms | 1439562 | 40 | 1.96101e+10 | 2.36884e+06 | 0.50253 | 8.70069 | 35.5655 | 6.42567 | 0.0159322 | 0.311955 | 0.0160851 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2567.68 | 0.0267766 | 2824ms | 56369 | 4890 | 153681 | 20936.3 | 0.0962879 | 1.98829 | 8.9343 | 1.73788 | 0.00256562 | 2.58304e-05 | 1.65322e-05 | 1(Win) | true |
| Glaze | 2041.7 | 0.0360695 | 3368.15ms | 56369 | 4890 | 441049 | 26329.8 | 0.145662 | 2.50722 | 11.1974 | 2.27331 | 0.00641168 | 2.33634e-05 | 1.36879e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1835.09 | 0.0199434 | 3653.95ms | 56369 | 4890 | 166907 | 29294.3 | 0.0114608 | 2.7877 | 12.8619 | 2.22999 | 0.00377463 | 2.62258e-05 | 1.75697e-05 | 3(Loss) | true |
| simdjson (reflection) | 1615.77 | 0.207428 | 4063.17ms | 56369 | 30 | 142883 | 33270.7 | 0.148059 | 3.18061 | 13.5965 | 2.31319 | 0.00408972 | 2.6019e-05 | 1.18268e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1344.7 | 0.0378835 | 4738.37ms | 56369 | 2560 | 587178 | 39977.4 | 0.220135 | 3.80462 | 15.0594 | 2.75152 | 0.00896604 | 2.55155e-05 | 1.62642e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3744.85 | 0.0313051 | 2525.12ms | 56369 | 4890 | 98753.1 | 14355.1 | 0.0393272 | 1.37292 | 6.87239 | 1.26353 | 0.00165641 | 1.76931e-05 | 1.02886e-05 | 1(Win) | true |
| Glaze | 2998.01 | 0.0665812 | 2862.84ms | 56369 | 4890 | 696988 | 17931.1 | 0.141547 | 1.70498 | 8.91579 | 1.74675 | 0.00217277 | 1.37169e-05 | 7.94502e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2350.02 | 0.0650525 | 3353.6ms | 56369 | 320 | 70862.3 | 22875.4 | 0.00178962 | 2.15777 | 10.8042 | 1.75708 | 0.00292559 | 1.61325e-05 | 1.04778e-05 | 3(Loss) | true |
| simdjson (reflection) | 1901.94 | 0.108785 | 3950.33ms | 56369 | 80 | 75634 | 28264.7 | 0.0954785 | 2.71004 | 11.9912 | 1.93965 | 0.00253952 | 1.68532e-05 | 9.97889e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1647.83 | 0.0722544 | 4378.79ms | 56369 | 640 | 355604 | 32623.4 | 0.0782595 | 3.10656 | 12.8092 | 2.23988 | 0.00824664 | 1.87104e-05 | 9.67398e-06 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13642.9 | 0.0529309 | 1123.93ms | 56369 | 4890 | 21271.2 | 3940.33 | 0.120444 | 0.380829 | 1.45303 | 0.199276 | 0.000276142 | 1.48053e-05 | 7.20493e-06 | 1(Win) | true |
| simdjson (reflection) | 13342 | 0.0928723 | 1130.6ms | 56369 | 320 | 4480.87 | 4029.21 | 0.0549416 | 0.389814 | 1.67644 | 0.268304 | 0.000187381 | 8.14943e-06 | 2.16209e-06 | 2(Loss) | true |
| Glaze | 6446.4 | 0.0555724 | 1568.28ms | 56369 | 2560 | 54979.9 | 8339.17 | 0.0389551 | 0.801726 | 3.05409 | 0.466072 | 8.25822e-05 | 1.34299e-05 | 5.75865e-06 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13940.8 | 0.0536103 | 1113.7ms | 56369 | 4890 | 20898.2 | 3856.14 | 0.329701 | 0.373121 | 1.44342 | 0.197094 | 0.000274843 | 1.66845e-05 | 8.7105e-06 | 1(Win) | true |
| simdjson (reflection) | 13721.3 | 0.0489752 | 1118.34ms | 56369 | 2560 | 9425.1 | 3917.84 | 0.141291 | 0.37828 | 1.66689 | 0.266122 | 0.000192371 | 1.45803e-05 | 7.72671e-06 | 2(Loss) | true |
| Glaze | 7434.17 | 0.0978066 | 1461.94ms | 56369 | 320 | 16006.7 | 7231.16 | 0.326635 | 0.69714 | 2.97538 | 0.448722 | 5.28881e-05 | 1.21964e-05 | 7.76136e-06 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3223.47 | 0.0233913 | 3224.84ms | 83958 | 2560 | 86422.9 | 24839.3 | 0.111728 | 1.57304 | 7.26673 | 1.437 | 0.00188766 | 1.67169e-05 | 9.55649e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2559.35 | 0.0568591 | 3859.66ms | 83958 | 80 | 25313.7 | 31284.8 | 0.118846 | 1.97763 | 9.24089 | 1.53617 | 0.00241624 | 3.57322e-06 | 1.33996e-06 | 2(Loss) | true |
| Glaze | 2438.48 | 0.057687 | 4011.02ms | 83958 | 320 | 114813 | 32835.4 | 0.00328353 | 2.07419 | 10.0009 | 2.0785 | 0.00336623 | 2.11415e-05 | 1.09802e-05 | 3(Loss) | true |
| simdjson (reflection) | 2325.56 | 0.0695075 | 4175.55ms | 83958 | 320 | 183267 | 34429.8 | 0.165488 | 2.18143 | 9.62529 | 1.57688 | 0.00204652 | 1.73822e-05 | 9.34247e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1938.52 | 0.0226415 | 4869.8ms | 83958 | 2560 | 223890 | 41304.1 | 0.244057 | 2.6084 | 10.573 | 1.86305 | 0.00514907 | 1.7331e-05 | 9.33316e-06 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4351.02 | 0.0217488 | 2921.56ms | 83958 | 2560 | 41006.5 | 18402.3 | 0.0263994 | 1.16423 | 5.90532 | 1.1256 | 0.00166105 | 1.29669e-05 | 7.05338e-06 | 1(Win) | true |
| Glaze | 3293.74 | 0.108093 | 3537.15ms | 83958 | 320 | 220948 | 24309.3 | 0.143707 | 1.54683 | 8.4912 | 1.73109 | 0.00206859 | 4.91317e-06 | 1.6005e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 3220.81 | 0.052859 | 3559.38ms | 83958 | 320 | 55256.1 | 24859.7 | 0.00725267 | 1.57289 | 7.88101 | 1.22448 | 0.00203766 | 8.11418e-06 | 3.7221e-06 | 3(Loss) | true |
| simdjson (reflection) | 2622.62 | 0.0224411 | 4148.68ms | 83958 | 4890 | 229535 | 30530 | 0.160026 | 1.9335 | 8.58703 | 1.34234 | 0.00214452 | 1.15697e-05 | 5.93831e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2333.81 | 0.0274758 | 4548.3ms | 83958 | 4890 | 434513 | 34308 | 0.19507 | 2.17799 | 9.08777 | 1.52848 | 0.00555672 | 1.15259e-05 | 5.61192e-06 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18497.5 | 0.0946786 | 1228.75ms | 94370 | 320 | 6790.39 | 4865.42 | 0.0517309 | 0.280429 | 0.910522 | 0.119063 | 0.000161068 | 2.98029e-06 | 2.98029e-07 | 1(Win) | true |
| Glaze | 5769.03 | 0.0706649 | 2300.24ms | 94370 | 2560 | 311108 | 15600.2 | 0.2413 | 0.877037 | 3.65717 | 0.618163 | 0.000400791 | 6.54422e-06 | 2.29317e-06 | 2(Loss) | true |
| simdjson (reflection) | 564.37 | 0.1228 | 8560.68ms | 94370 | 2560 | 9.81687e+07 | 159467 | 0.27689 | 8.92835 | 38.8362 | 7.54198 | 0.0221409 | 0.00942239 | 0.000131646 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18757.3 | 0.0695727 | 1213.8ms | 94370 | 160 | 1782.89 | 4798.04 | 0.0138096 | 0.277052 | 0.904864 | 0.117792 | 0.000156498 | 4.56978e-06 | 2.84783e-06 | 1(Win) | true |
| Glaze | 7086.21 | 0.0299809 | 2007.74ms | 94370 | 4890 | 70898.5 | 12700.5 | 0.155849 | 0.720806 | 3.60407 | 0.605966 | 0.000294802 | 6.0199e-06 | 2.32085e-06 | 2(Loss) | true |
| simdjson (reflection) | 562.009 | 0.172811 | 8579.49ms | 94370 | 1280 | 9.80246e+07 | 160137 | 0.435341 | 8.93601 | 38.8342 | 7.54117 | 0.0222478 | 0.0135772 | 0.000150885 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1883.69 | 0.114613 | 3467.97ms | 53331 | 640 | 612901 | 27000.4 | 0.18955 | 2.69134 | 8.43115 | 1.63265 | 0.0108544 | 6.5247e-05 | 3.50992e-05 | 1(Win) | true |
| simdjson (reflection) | 1656.01 | 0.0844994 | 3793.57ms | 53331 | 320 | 215521 | 30712.6 | 0.0983868 | 3.05472 | 10.8142 | 1.88687 | 0.00600917 | 6.0237e-05 | 3.39859e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1568.83 | 0.0451317 | 4021.37ms | 53331 | 4890 | 1.04684e+06 | 32419.3 | 0.133678 | 3.22044 | 11.3841 | 1.95372 | 0.00802802 | 6.92438e-05 | 4.43539e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1497.77 | 0.0312375 | 4164.78ms | 53331 | 2560 | 288048 | 33957.5 | 0.291933 | 3.38294 | 11.0617 | 2.03872 | 0.00219426 | 0.000106198 | 6.93268e-05 | 4(Loss) | true |
| Glaze | 1475.43 | 0.041897 | 4199.22ms | 53331 | 4890 | 1.02e+06 | 34471.7 | 0.0452251 | 3.42949 | 11.6038 | 2.26513 | 0.0194017 | 9.16451e-05 | 5.48874e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2667.81 | 0.0428519 | 3223.49ms | 53331 | 4890 | 326360 | 19064.5 | 0.0250539 | 1.89787 | 6.21673 | 1.1349 | 0.00754975 | 2.57258e-05 | 1.48549e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2083.99 | 0.1098 | 3716.45ms | 53331 | 640 | 459568 | 24405.2 | 0.140157 | 2.44265 | 9.16956 | 1.45585 | 0.00541313 | 1.79012e-05 | 8.90664e-06 | 2(Loss) | true |
| Glaze | 1957.41 | 0.0610252 | 3940.56ms | 53331 | 2560 | 643656 | 25983.5 | 0.213559 | 2.58289 | 9.37946 | 1.7647 | 0.0158863 | 2.03549e-05 | 9.96137e-06 | 3(Loss) | true |
| simdjson (reflection) | 1930.66 | 0.0384877 | 3938.3ms | 53331 | 2560 | 263166 | 26343.5 | 0.120675 | 2.62986 | 8.90465 | 1.44672 | 0.00816377 | 2.40025e-05 | 1.05473e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1664.78 | 0.0369992 | 4337.54ms | 53331 | 2560 | 327093 | 30550.9 | 0.00805456 | 3.04843 | 9.14809 | 1.61232 | 0.00926737 | 3.9948e-05 | 2.12045e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13993.9 | 0.120516 | 1141.79ms | 58581 | 320 | 7407.62 | 3992.26 | 0.0921247 | 0.365164 | 1.10848 | 0.165275 | 3.22203e-05 | 6.93484e-06 | 2.6139e-06 | 1(Win) | true |
| simdjson (reflection) | 11536.4 | 0.0854177 | 1226.43ms | 58581 | 1280 | 21901.9 | 4842.71 | 0.0695795 | 0.443168 | 1.48249 | 0.207678 | 3.17669e-05 | 2.98865e-05 | 1.84173e-05 | 2(Loss) | true |
| Glaze | 7298.94 | 0.104751 | 1507.29ms | 58581 | 1280 | 82284.4 | 7654.15 | 0.140828 | 0.694833 | 2.43669 | 0.371264 | 3.51543e-05 | 1.39764e-05 | 6.2947e-06 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14178.7 | 0.0667028 | 1137.01ms | 58581 | 320 | 2210.44 | 3940.22 | 7.93104e-05 | 0.360456 | 1.09925 | 0.163193 | 3.39274e-05 | 3.81416e-05 | 2.38985e-05 | 1(Win) | true |
| simdjson (reflection) | 11654.9 | 0.0718203 | 1222.1ms | 58581 | 1280 | 15170.5 | 4793.45 | 0.0181922 | 0.437018 | 1.47317 | 0.205545 | 3.39941e-05 | 4.67302e-05 | 2.95798e-05 | 2(Loss) | true |
| Glaze | 8625.55 | 0.152373 | 1387.41ms | 58581 | 1280 | 124671 | 6476.94 | 0.0695859 | 0.591877 | 2.36218 | 0.354176 | 3.30205e-05 | 1.88841e-05 | 1.03889e-05 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2115.33 | 0.111542 | 3700.46ms | 65103 | 640 | 685962 | 29351 | 0.105315 | 2.41403 | 7.61001 | 1.45972 | 0.00765335 | 6.83772e-05 | 3.62166e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1974.74 | 0.0292131 | 3889.42ms | 65103 | 1280 | 107981 | 31440.7 | 0.0742697 | 2.561 | 9.86187 | 1.64869 | 0.00126269 | 4.09327e-05 | 2.76485e-05 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1901.41 | 0.0398049 | 4045.82ms | 65103 | 1280 | 216238 | 32653.2 | 0.152611 | 2.67644 | 10.7785 | 2.11565 | 0.00114836 | 2.50564e-05 | 1.31882e-05 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1901.35 | 0.0539227 | 4006.59ms | 65103 | 4890 | 1.51611e+06 | 32654.2 | 0.00585704 | 2.70195 | 9.13896 | 1.55909 | 0.0088381 | 7.31042e-05 | 3.90321e-05 | 3(Tie) | true |
| simdjson (ondemand) | 1639.25 | 0.0726682 | 4501.92ms | 65103 | 640 | 484822 | 37875.4 | 0.01988 | 3.09123 | 9.3116 | 1.67713 | 0.00825356 | 8.58975e-05 | 4.56248e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2871.94 | 0.0445204 | 3457.04ms | 65103 | 4890 | 452978 | 21618.5 | 0.126558 | 1.76882 | 5.80186 | 1.05311 | 0.00535037 | 3.57244e-05 | 2.381e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2531.47 | 0.0411782 | 3644.17ms | 65103 | 4890 | 498769 | 24526.1 | 0.12906 | 2.00029 | 8.05099 | 1.24184 | 0.000897128 | 4.32506e-05 | 3.2756e-05 | 2(Loss) | true |
| simdjson (reflection) | 2314.04 | 0.0332323 | 3994.75ms | 65103 | 4890 | 388768 | 26830.6 | 0.105042 | 2.22261 | 7.58504 | 1.20421 | 0.00716944 | 4.46862e-05 | 2.855e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2014.25 | 0.042767 | 4345.31ms | 65103 | 1280 | 222436 | 30823.9 | 0.112719 | 2.55512 | 7.76166 | 1.33451 | 0.00767153 | 1.74603e-05 | 9.30017e-06 | 4(Loss) | true |
| Glaze | 1972.34 | 0.142613 | 3858.82ms | 65103 | 320 | 644927 | 31478.9 | 0.299066 | 2.56826 | 8.96638 | 1.70882 | 0.0133368 | 3.14886e-05 | 2.06884e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16462.4 | 0.114285 | 1195.42ms | 78778 | 640 | 17409.3 | 4563.63 | 0.0224551 | 0.309045 | 0.85223 | 0.122877 | 2.66374e-05 | 6.58496e-06 | 2.2611e-06 | 1(Win) | true |
| Glaze | 4856.6 | 0.116311 | 2284.21ms | 78778 | 2560 | 828752 | 15469.4 | 0.367408 | 1.05137 | 2.87243 | 0.44906 | 7.89402e-05 | 1.79748e-05 | 8.01798e-06 | 2(Loss) | true |
| simdjson (reflection) | 641.178 | 0.156274 | 6358.24ms | 78778 | 1280 | 4.2918e+07 | 117173 | 0.44197 | 7.88962 | 29.3666 | 6.6069 | 0.0369063 | 0.00956688 | 0.000209142 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16839.8 | 0.0406216 | 1181.93ms | 78778 | 4890 | 16060.5 | 4461.36 | 0.275681 | 0.306426 | 0.845566 | 0.121366 | 3.60932e-05 | 1.11883e-05 | 5.58635e-06 | 1(Win) | true |
| Glaze | 5399.63 | 0.397348 | 2123.25ms | 78778 | 160 | 489039 | 13913.6 | 0.0403218 | 0.946398 | 2.80596 | 0.434093 | 6.77537e-05 | 1.56294e-05 | 8.56838e-06 | 2(Loss) | true |
| simdjson (reflection) | 644.682 | 0.473021 | 6347.19ms | 78778 | 160 | 4.86183e+07 | 116536 | 0.341103 | 7.86333 | 29.3676 | 6.60714 | 0.0357785 | 0.00758111 | 0.000164862 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2577.98 | 0.0556073 | 1165.39ms | 11812 | 2560 | 15114.5 | 4369.63 | 0.0500454 | 1.98484 | 9.89035 | 1.59948 | 0.00261757 | 1.92468e-05 | 4.72904e-06 | 1(Win) | true |
| Glaze | 1920.03 | 0.0619378 | 1320.53ms | 11812 | 1280 | 16902.6 | 5866.99 | 0.225728 | 2.65314 | 13.1236 | 2.62724 | 0.00203296 | 5.16556e-05 | 2.4009e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1677.53 | 0.0865354 | 1409.49ms | 11812 | 640 | 21610.9 | 6715.09 | 0.0445091 | 3.06481 | 14.8052 | 2.29445 | 0.0077703 | 6.13783e-05 | 2.83081e-05 | 3(Loss) | true |
| simdjson (reflection) | 1573.29 | 0.0294825 | 1453.58ms | 11812 | 4890 | 21790.5 | 7160.03 | 0.0543102 | 3.23606 | 12.8495 | 2.04834 | 0.00442954 | 4.40092e-05 | 1.87325e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1225.97 | 0.0867425 | 1664.93ms | 11812 | 320 | 20328.3 | 9188.49 | 0.047931 | 4.21176 | 17.2639 | 3.08812 | 0.00667356 | 1.05825e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2989.45 | 0.0436522 | 1155.44ms | 11812 | 4890 | 13230.8 | 3768.18 | 0.0553698 | 1.72013 | 8.91231 | 1.37107 | 0.00178537 | 1.99271e-05 | 4.67446e-06 | 1(Win) | true |
| Glaze | 2146.34 | 0.0722985 | 1309.38ms | 11812 | 80 | 1151.86 | 5248.39 | 0.140478 | 2.3748 | 12.2608 | 2.42482 | 0.000819082 | 1.58737e-05 | 1.05825e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1843.07 | 0.0803885 | 1401.03ms | 11812 | 1280 | 30900.2 | 6111.98 | 0.410625 | 2.78698 | 13.8268 | 2.06578 | 0.00676179 | 3.98826e-05 | 1.56091e-05 | 3(Loss) | true |
| simdjson (reflection) | 1647.6 | 0.0507724 | 1476.98ms | 11812 | 4890 | 58926 | 6837.09 | 0.0269511 | 3.08375 | 12.3385 | 1.92245 | 0.0042691 | 2.29914e-05 | 5.85173e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1280.82 | 0.0294174 | 1669.16ms | 11812 | 4890 | 32733.1 | 8794.97 | 0.0755072 | 3.97086 | 16.4939 | 2.91483 | 0.00595549 | 2.64886e-05 | 8.84685e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12905.6 | 0.138837 | 814.619ms | 11812 | 80 | 117.487 | 872.862 | 0.0100255 | 0.410711 | 1.8736 | 0.221639 | 8.46597e-05 | 1.90484e-05 | 2.11649e-06 | 1(Win) | true |
| simdjson (reflection) | 9556.57 | 0.10909 | 851.793ms | 11812 | 40 | 66.141 | 1178.75 | 0.00706914 | 0.548021 | 2.32916 | 0.343041 | 0.000171436 | 3.38639e-05 | 8.46597e-06 | 2(Loss) | true |
| Glaze | 4569.75 | 0.0964957 | 993.296ms | 11812 | 2560 | 14485 | 2465.08 | 0.0436757 | 1.12588 | 4.62606 | 0.716983 | 0.000167071 | 4.7125e-05 | 2.64231e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13888.4 | 0.0354872 | 814.069ms | 11812 | 2560 | 212.092 | 811.093 | 0.0833442 | 0.38355 | 1.82586 | 0.210718 | 8.46597e-05 | 2.26861e-05 | 6.81246e-06 | 1(Win) | true |
| simdjson (reflection) | 10296.7 | 0.0565887 | 844.475ms | 11812 | 320 | 122.648 | 1094.02 | 0.0824828 | 0.510296 | 2.28149 | 0.332205 | 0.000107677 | 2.67207e-05 | 0 | 2(Loss) | true |
| Glaze | 5067.77 | 0.149941 | 957.913ms | 11812 | 2560 | 28437.7 | 2222.83 | 0.0441071 | 1.01723 | 4.35083 | 0.655943 | 0.000100236 | 1.5543e-05 | 5.48965e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3855.35 | 0.0524755 | 1362.62ms | 25388 | 2560 | 27802.4 | 6280.07 | 0.0240224 | 1.31494 | 6.30479 | 1.06988 | 0.00281517 | 1.60632e-05 | 5.72367e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3110.06 | 0.125336 | 1517.64ms | 25388 | 40 | 3808.28 | 7785.02 | 0.00331845 | 1.63473 | 7.92445 | 1.18828 | 0.00322987 | 7.87774e-06 | 0 | 2(Loss) | true |
| simdjson (reflection) | 3058.65 | 0.141487 | 1531.11ms | 25388 | 30 | 3763.15 | 7915.87 | 0.0379129 | 1.66176 | 6.74297 | 0.99614 | 0.00214274 | 1.18166e-05 | 1.31296e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2397.39 | 0.0226419 | 1786.86ms | 25388 | 4890 | 25569 | 10099.3 | 0.0183892 | 2.11904 | 8.74065 | 1.46731 | 0.00325193 | 1.53447e-05 | 6.79032e-06 | 4(Loss) | true |
| Glaze | 2389.08 | 0.0513351 | 1744.97ms | 25388 | 1280 | 34644.4 | 10134.4 | 0.000971313 | 2.12262 | 9.43428 | 1.81346 | 0.00572133 | 3.94502e-05 | 1.84327e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4209.93 | 0.0278276 | 1367.8ms | 25388 | 4890 | 12524.7 | 5751.14 | 0.159808 | 1.21168 | 5.88916 | 0.972389 | 0.00266863 | 1.25254e-05 | 4.71214e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3380.18 | 0.117045 | 1512.42ms | 25388 | 30 | 2108.64 | 7162.9 | 0.037215 | 1.50473 | 7.50886 | 1.09067 | 0.00275852 | 1.31296e-05 | 7.87774e-06 | 2(Loss) | true |
| simdjson (reflection) | 3227.28 | 0.0362305 | 1543.95ms | 25388 | 2560 | 18913.5 | 7502.25 | 0.148007 | 1.57494 | 6.45187 | 0.925477 | 0.0019784 | 1.03088e-05 | 2.95415e-06 | 3(Loss) | true |
| Glaze | 2586.27 | 0.145286 | 1720.73ms | 25388 | 40 | 7399.7 | 9361.7 | 0.143699 | 1.96404 | 8.91531 | 1.69497 | 0.0051678 | 5.12053e-05 | 3.34804e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2538.49 | 0.0747667 | 1746.3ms | 25388 | 30 | 1525.61 | 9537.9 | 0.045063 | 2.00169 | 8.37242 | 1.38455 | 0.00298698 | 4.98923e-05 | 1.70684e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19887.8 | 0.0433505 | 884.649ms | 31235 | 4890 | 2061.6 | 1497.8 | 0.191956 | 0.261747 | 0.757324 | 0.0838803 | 3.28796e-05 | 1.25705e-05 | 3.12297e-06 | 1(Win) | true |
| Glaze | 6625.8 | 0.105365 | 1185.34ms | 31235 | 1280 | 28721.8 | 4495.76 | 0.0482806 | 0.771598 | 3.75492 | 0.631919 | 0.00073913 | 3.1165e-05 | 1.69832e-05 | 2(Loss) | true |
| simdjson (reflection) | 550.199 | 0.117611 | 6164.04ms | 31235 | 4890 | 1.98265e+07 | 54140.4 | 0.225488 | 9.15706 | 38.2621 | 7.04985 | 0.015583 | 0.000169413 | 0.000110653 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20665.1 | 0.0666811 | 871.072ms | 31235 | 1280 | 1182.56 | 1441.47 | 0.270798 | 0.251646 | 0.739363 | 0.0796863 | 3.23655e-05 | 4.72727e-06 | 8.25396e-07 | 1(Win) | true |
| Glaze | 7441.38 | 0.193615 | 1139.11ms | 31235 | 640 | 38444.7 | 4003.03 | 0.221965 | 0.68561 | 3.62862 | 0.603938 | 0.000727049 | 1.47571e-05 | 4.70226e-06 | 2(Loss) | true |
| simdjson (reflection) | 544.102 | 0.218357 | 6282.89ms | 31235 | 1280 | 1.82922e+07 | 54747.1 | 0.00297113 | 9.25576 | 38.3009 | 7.06171 | 0.0180237 | 0.000143444 | 9.76469e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3194.96 | 0.105623 | 3965.72ms | 108313 | 80 | 93290.2 | 32330.7 | 0.201258 | 1.57691 | 7.50243 | 1.50359 | 0.00211228 | 1.88112e-05 | 1.40796e-05 | 1(Win) | true |
| Glaze | 2232.9 | 0.0560312 | 5382.27ms | 108313 | 1280 | 859990 | 46260.6 | 0.0368734 | 2.27558 | 10.076 | 1.9315 | 0.00302312 | 2.71998e-05 | 1.80899e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2195.57 | 0.0159742 | 5462.01ms | 108313 | 4890 | 276192 | 47047.1 | 0.0584689 | 2.33527 | 10.6723 | 1.91317 | 0.00288764 | 2.89323e-05 | 2.21467e-05 | 3(Loss) | true |
| simdjson (reflection) | 1758.03 | 0.0430173 | 6618.42ms | 108313 | 1280 | 817720 | 58756.3 | 0.012626 | 2.88586 | 12.7891 | 1.85468 | 0.0017601 | 4.99709e-05 | 3.83798e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1501.91 | 0.0230594 | 7616.74ms | 108313 | 2560 | 643890 | 68776.2 | 0.113495 | 3.37432 | 14.6876 | 2.52012 | 0.00291026 | 3.16177e-05 | 2.18262e-05 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3789.52 | 0.156398 | 3643.35ms | 108313 | 30 | 54522.3 | 27258.1 | 0.126896 | 1.33484 | 6.75956 | 1.32925 | 0.00205916 | 2.24658e-05 | 1.8465e-05 | 1(Win) | true |
| Glaze | 2479.23 | 0.0480749 | 5105.41ms | 108313 | 1280 | 513541 | 41664.3 | 0.0821408 | 2.05346 | 9.38492 | 1.7682 | 0.00287653 | 9.35512e-06 | 5.90015e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2445.26 | 0.0318887 | 5138.55ms | 108313 | 1280 | 232272 | 42243.2 | 0.0786712 | 2.08498 | 9.93231 | 1.73958 | 0.00270526 | 9.65806e-06 | 5.82802e-06 | 3(Loss) | true |
| simdjson (reflection) | 1807.61 | 0.0224115 | 6652.45ms | 108313 | 4890 | 802047 | 57144.6 | 0.0471046 | 2.825 | 12.4788 | 1.78181 | 0.0019267 | 2.18672e-05 | 1.58387e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1619.18 | 0.0396911 | 7305.11ms | 108313 | 2560 | 1.64133e+06 | 63794.8 | 0.112631 | 3.13377 | 14 | 2.36277 | 0.00265797 | 0.000111814 | 9.8254e-05 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19659.3 | 0.0286542 | 1259.32ms | 108313 | 4890 | 11084.3 | 5254.26 | 0.000737824 | 0.260894 | 1.17602 | 0.148717 | 5.92372e-05 | 3.79495e-06 | 1.12527e-06 | 1(Win) | true |
| simdjson (reflection) | 16984.4 | 0.0862398 | 1351.78ms | 108313 | 640 | 17605.9 | 6081.79 | 0.0215855 | 0.30354 | 1.45089 | 0.155854 | 5.58422e-05 | 5.06345e-06 | 2.07731e-06 | 2(Loss) | true |
| Glaze | 5755.03 | 0.080792 | 2530.55ms | 108313 | 4890 | 1.02828e+06 | 17948.7 | 0.269666 | 0.88293 | 3.01815 | 0.397469 | 0.000274641 | 5.7132e-06 | 1.99377e-06 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19627.5 | 0.336373 | 1250.32ms | 108313 | 80 | 25070.5 | 5262.79 | 0.133901 | 0.258945 | 1.171 | 0.147591 | 5.97805e-05 | 7.15519e-06 | 5.30869e-06 | 1(Win) | true |
| simdjson (reflection) | 16840.2 | 0.0624563 | 1347.6ms | 108313 | 160 | 2348.23 | 6133.86 | 0.0657798 | 0.302339 | 1.44602 | 0.154755 | 6.43967e-05 | 4.21233e-06 | 2.76975e-06 | 2(Loss) | true |
| Glaze | 6837.82 | 0.25847 | 2259.4ms | 108313 | 160 | 243930 | 15106.5 | 0.404645 | 0.754683 | 2.97166 | 0.386768 | 0.000275359 | 2.25042e-06 | 4.61625e-07 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4040.57 | 0.0473472 | 5093.03ms | 183677 | 640 | 269646 | 43352.3 | 0.43422 | 1.26161 | 5.87762 | 1.17775 | 0.00165741 | 9.46805e-06 | 6.20144e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3358.34 | 0.063109 | 5951.65ms | 183677 | 80 | 86682.7 | 52159.1 | 0.0149999 | 1.50535 | 7.01707 | 1.18184 | 0.00171259 | 2.10968e-06 | 6.12488e-07 | 2(Loss) | true |
| simdjson (reflection) | 2774.33 | 0.0802863 | 7053.43ms | 183677 | 80 | 205573 | 63138.8 | 0.178375 | 1.82196 | 8.11687 | 1.11465 | 0.00102061 | 7.82624e-06 | 6.46515e-06 | 3(Loss) | true |
| Glaze | 2589.23 | 0.0654682 | 7518.91ms | 183677 | 320 | 627740 | 67652.6 | 0.133045 | 1.96539 | 8.76916 | 1.71851 | 0.0033521 | 2.09097e-05 | 1.45806e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2414.9 | 0.0216331 | 8044.23ms | 183677 | 4890 | 1.20408e+06 | 72536.2 | 0.00529173 | 2.11167 | 9.2211 | 1.50345 | 0.00175075 | 2.63099e-05 | 1.87089e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4603.64 | 0.049417 | 4765.65ms | 183677 | 1280 | 452552 | 38049.9 | 0.0996602 | 1.1105 | 5.43584 | 1.07384 | 0.00143029 | 7.72416e-06 | 4.04072e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3743.63 | 0.103898 | 5596.15ms | 183677 | 640 | 1.51259e+06 | 46791 | 0.101933 | 1.35028 | 6.57587 | 1.07827 | 0.00151153 | 8.2771e-06 | 5.12959e-06 | 2(Loss) | true |
| simdjson (reflection) | 2811.73 | 0.0508624 | 7176.34ms | 183677 | 320 | 321297 | 62299.1 | 0.0153216 | 1.79936 | 7.94646 | 1.0743 | 0.0011992 | 3.3857e-06 | 1.24199e-06 | 3(Loss) | true |
| Glaze | 2788.38 | 0.0194749 | 7206.46ms | 183677 | 4890 | 731923 | 62820.8 | 0.00150873 | 1.82459 | 8.36951 | 1.62424 | 0.00318282 | 6.14019e-06 | 3.59282e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2559.51 | 0.0544512 | 7775.34ms | 183677 | 2560 | 3.55509e+06 | 68438.1 | 0.229654 | 1.97578 | 8.83736 | 1.41587 | 0.00163796 | 9.71262e-06 | 6.1504e-06 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26232.5 | 0.10365 | 1522.72ms | 213963 | 30 | 1950.12 | 7778.57 | 0.107445 | 0.19729 | 0.640377 | 0.0752747 | 4.34655e-05 | 1.86948e-06 | 0 | 1(Win) | true |
| Glaze | 5476.72 | 0.0952347 | 4467.91ms | 213963 | 1280 | 1.61153e+06 | 37257.9 | 0.0136781 | 0.924171 | 3.59472 | 0.575403 | 0.000533325 | 7.62033e-06 | 4.13331e-06 | 2(Loss) | true |
| simdjson (reflection) | 482.807 | 0.238773 | 5482.7ms | 213963 | 640 | 6.51751e+08 | 422635 | 0.00140453 | 10.3927 | 41.6024 | 8.43663 | 0.0402134 | 0.206985 | 0.00032464 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25871 | 0.0597052 | 1531.24ms | 213963 | 640 | 14192.4 | 7887.25 | 0.0305186 | 0.196252 | 0.6379 | 0.0747139 | 2.97949e-05 | 1.3656e-06 | 6.20726e-07 | 1(Win) | true |
| Glaze | 6298.38 | 0.166419 | 3978.78ms | 213963 | 640 | 1.86039e+06 | 32397.4 | 0.0165206 | 0.800743 | 3.56743 | 0.569169 | 0.000528377 | 4.20633e-06 | 2.4537e-06 | 2(Loss) | true |
| simdjson (reflection) | 486.751 | 0.244325 | 5475.15ms | 213963 | 640 | 6.71399e+08 | 419210 | 0.154773 | 10.4301 | 41.6031 | 8.43754 | 0.0391298 | 0.208923 | 0.000614023 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 828.295 | 0.0665067 | 6616.48ms | 1834197 | 160 | 3.15627e+08 | 2.11184e+06 | 0.132738 | 6.09466 | 25.7816 | 5.78192 | 0.0366542 | 0.0831344 | 0.00267141 | 1(Win) | true |
| Jsonifier (two-stage) | 710.518 | 0.129732 | 7650.65ms | 1834197 | 80 | 8.16069e+08 | 2.4619e+06 | 0.113785 | 7.09465 | 30.0091 | 6.27293 | 0.0462405 | 0.146752 | 0.00647867 | 2(Loss) | true |
| simdjson (reflection) | 670.03 | 0.0790667 | 8114.4ms | 1834197 | 40 | 1.70432e+08 | 2.61067e+06 | 0.272587 | 7.51874 | 32.2473 | 5.9494 | 0.0317071 | 0.135985 | 0.00182318 | 3(Loss) | true |
| Glaze | 653.583 | 0.229558 | 8327.5ms | 1834197 | 80 | 3.01972e+09 | 2.67636e+06 | 0.0904978 | 7.71774 | 32.3794 | 6.32443 | 0.0346494 | 0.0822488 | 0.00152312 | 4(Loss) | true |
| simdjson (ondemand) | 543.308 | 0.139634 | 9966.89ms | 1834197 | 40 | 8.08426e+08 | 3.21959e+06 | 0.318355 | 9.28942 | 37.5542 | 7.1635 | 0.0366757 | 0.148849 | 0.0117999 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 925.578 | 0.0555481 | 6556.51ms | 1834197 | 160 | 1.7633e+08 | 1.88988e+06 | 0.172718 | 5.46378 | 22.778 | 5.08164 | 0.0357114 | 0.0560481 | 0.002178 | 1(Win) | true |
| Jsonifier (two-stage) | 779.004 | 0.0597177 | 7641.49ms | 1834197 | 80 | 1.4385e+08 | 2.24547e+06 | 0.308985 | 6.46796 | 27.0056 | 5.57276 | 0.0453811 | 0.120249 | 0.00411046 | 2(Loss) | true |
| simdjson (reflection) | 749.102 | 0.117451 | 7859.34ms | 1834197 | 40 | 3.00873e+08 | 2.3351e+06 | 0.0586284 | 6.75192 | 29.2207 | 5.23318 | 0.0262045 | 0.111857 | 0.00550654 | 3(Loss) | true |
| Glaze | 714.293 | 0.11377 | 8299.63ms | 1834197 | 80 | 6.20987e+08 | 2.44889e+06 | 0.00271697 | 7.0624 | 29.3687 | 5.62402 | 0.0330404 | 0.0582665 | 0.00134959 | 4(Loss) | true |
| simdjson (ondemand) | 592.396 | 0.0742421 | 9894.28ms | 1834197 | 80 | 3.84467e+08 | 2.9528e+06 | 0.146314 | 8.55334 | 34.5296 | 6.46274 | 0.0315287 | 0.117938 | 0.02178 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1364.17 | 0.0366939 | 8525.77ms | 1922245 | 320 | 7.7807e+07 | 1.34382e+06 | 0.115494 | 3.70797 | 13.0169 | 0.630071 | 0.000686666 | 0.0586533 | 4.84899e-05 | 1(Win) | true |
| simdjson (reflection) | 1352.9 | 0.044544 | 8582.84ms | 1922245 | 80 | 2.91443e+07 | 1.35501e+06 | 0.0110999 | 3.73644 | 13.5128 | 1.13444 | 0.00872919 | 0.0506553 | 1.94174e-05 | 2(Loss) | true |
| Glaze | 994.251 | 0.213487 | 5472.57ms | 1833577 | 160 | 2.25564e+09 | 1.75875e+06 | 0.284224 | 5.08043 | 16.0488 | 1.05286 | 0.00102141 | 0.0497675 | 4.52667e-05 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1364.23 | 0.0368323 | 8520.76ms | 1922245 | 320 | 7.83886e+07 | 1.34376e+06 | 0.119378 | 3.7092 | 13.0167 | 0.630033 | 0.000723815 | 0.0584437 | 0.000135502 | 1(Win) | true |
| simdjson (reflection) | 1355.54 | 0.0712315 | 8575.81ms | 1922245 | 80 | 7.42385e+07 | 1.35238e+06 | 0.128031 | 3.74046 | 13.5126 | 1.1344 | 0.00879792 | 0.0507579 | 0.000401965 | 2(Loss) | true |
| Glaze | 990.218 | 0.205618 | 5496.92ms | 1833577 | 160 | 2.1095e+09 | 1.76591e+06 | 0.060436 | 5.10808 | 16.048 | 1.05269 | 0.00101463 | 0.0496013 | 0.000421993 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2558.9 | 0.0664249 | 8528.15ms | 7351818 | 80 | 2.64993e+08 | 2.73994e+06 | 0.0888777 | 1.97025 | 8.34819 | 1.61001 | 0.0122512 | 0.0614727 | 0.000405282 | 1(Win) | true |
| Jsonifier | 2525.83 | 0.101668 | 8619.88ms | 7351818 | 30 | 2.38931e+08 | 2.77581e+06 | 0.0165282 | 1.99315 | 8.39101 | 1.9096 | 0.00894763 | 0.0342062 | 0.000313959 | 2(Loss) | true |
| simdjson (reflection) | 2426.1 | 0.039757 | 9026.1ms | 7351818 | 80 | 1.05606e+08 | 2.88992e+06 | 0.281931 | 2.082 | 9.06163 | 1.52211 | 0.00776222 | 0.0584725 | 0.000213179 | 3(Loss) | true |
| Glaze | 2050.26 | 0.154376 | 5152.17ms | 7351818 | 40 | 1.11478e+09 | 3.41968e+06 | 0.311269 | 2.46983 | 11.2419 | 2.23985 | 0.00904533 | 0.0334381 | 0.000192711 | 4(Loss) | true |
| simdjson (ondemand) | 2002.31 | 0.0988718 | 5289.7ms | 7351818 | 40 | 4.79437e+08 | 3.50157e+06 | 0.663461 | 2.53083 | 10.3851 | 1.82505 | 0.00898796 | 0.0613758 | 0.000407613 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2771.92 | 0.098277 | 8528.11ms | 7351818 | 80 | 4.94335e+08 | 2.52938e+06 | 0.241614 | 1.82098 | 7.5997 | 1.43562 | 0.0120632 | 0.0547921 | 0.00070051 | 1(Win) | true |
| Jsonifier | 2752.24 | 0.0484108 | 8614.92ms | 7351818 | 160 | 2.43344e+08 | 2.54746e+06 | 0.151861 | 1.82908 | 7.64215 | 1.7349 | 0.00873832 | 0.0276732 | 8.62593e-05 | 2(Loss) | true |
| simdjson (reflection) | 2662.38 | 0.0390797 | 8828.18ms | 7351818 | 80 | 8.47312e+07 | 2.63345e+06 | 0.127854 | 1.89465 | 8.30605 | 1.34339 | 0.00653632 | 0.0519289 | 0.000215011 | 3(Loss) | true |
| Glaze | 2193.16 | 0.12415 | 5147.68ms | 7351818 | 30 | 4.72562e+08 | 3.19686e+06 | 0.0969191 | 2.30393 | 10.4908 | 2.06525 | 0.00859066 | 0.0273758 | 0.000170103 | 4(Loss) | true |
| simdjson (ondemand) | 2166.36 | 0.0910252 | 5217.17ms | 7351818 | 80 | 6.94289e+08 | 3.23641e+06 | 0.0612736 | 2.33082 | 9.63014 | 1.64996 | 0.00781907 | 0.053603 | 0.000820557 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6344.87 | 0.0546471 | 9523.39ms | 10018896 | 160 | 1.08355e+08 | 1.5059e+06 | 0.159624 | 0.795182 | 2.59976 | 0.119836 | 0.000118522 | 0.0248601 | 0.000282431 | 1(Win) | true |
| Glaze | 3707.39 | 0.156164 | 7961.54ms | 9930228 | 40 | 6.36511e+08 | 2.55441e+06 | 0.379548 | 1.36307 | 4.41557 | 0.474372 | 0.000767971 | 0.0417468 | 0.00101204 | 2(Loss) | true |
| simdjson (reflection) | 289.929 | 0.190744 | 9894.22ms | 10018896 | 30 | 1.18543e+11 | 3.29555e+07 | 0.82077 | 12.5115 | 35.8666 | 5.25146 | 0.0180447 | 0.267941 | 0.117766 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6358.41 | 0.0478698 | 9559.89ms | 10018896 | 80 | 4.13959e+07 | 1.5027e+06 | 0.0404741 | 0.794679 | 2.59972 | 0.119828 | 0.00013517 | 0.0248468 | 0.000175642 | 1(Win) | true |
| Glaze | 4074.86 | 0.182842 | 7271.54ms | 9930228 | 30 | 5.41711e+08 | 2.32406e+06 | 0.861266 | 1.24262 | 4.4153 | 0.474313 | 0.000758338 | 0.0224746 | 0.000178774 | 2(Loss) | true |
| simdjson (reflection) | 326.25 | 2.23239 | 8698.85ms | 10018896 | 30 | 1.28233e+13 | 2.92866e+07 | 1.88889 | 12.3341 | 35.8783 | 5.255 | 0.0176691 | 0.291193 | 0.152421 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 843.06 | 0.0671774 | 6476.29ms | 1834197 | 160 | 3.10843e+08 | 2.07485e+06 | 0.0815004 | 5.98236 | 25.2965 | 5.64135 | 0.0375266 | 0.0845141 | 0.000316126 | 1(Win) | true |
| Jsonifier (two-stage) | 717.184 | 0.156582 | 7575.01ms | 1834197 | 30 | 4.37558e+08 | 2.43902e+06 | 0.0283541 | 6.98586 | 29.5667 | 6.15309 | 0.046574 | 0.148468 | 0.000224313 | 2(Loss) | true |
| simdjson (reflection) | 668.644 | 0.0691269 | 8128.67ms | 1834197 | 80 | 2.6163e+08 | 2.61608e+06 | 0.11404 | 7.5395 | 32.2928 | 5.99748 | 0.0319811 | 0.136688 | 0.000303171 | 3(Loss) | true |
| Glaze | 647.262 | 0.166133 | 8427.65ms | 1834197 | 40 | 8.06312e+08 | 2.7025e+06 | 0.043386 | 7.84897 | 32.3365 | 6.31508 | 0.0347183 | 0.082787 | 0.00227151 | 4(Loss) | true |
| simdjson (ondemand) | 561.892 | 0.233165 | 9700.79ms | 1834197 | 30 | 1.58065e+09 | 3.1131e+06 | 0.471729 | 8.95474 | 36.9666 | 7.14919 | 0.0373869 | 0.149423 | 0.00013659 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 939.417 | 0.0614411 | 6475.4ms | 1834197 | 160 | 2.09418e+08 | 1.86204e+06 | 0.596058 | 5.3646 | 22.3226 | 4.95189 | 0.0366781 | 0.0575837 | 7.11858e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 797.202 | 0.0673691 | 7587.47ms | 1834197 | 80 | 1.7481e+08 | 2.19421e+06 | 0.119653 | 6.32897 | 26.5892 | 5.46282 | 0.0457477 | 0.121513 | 9.62819e-05 | 2(Loss) | true |
| simdjson (reflection) | 750.788 | 0.0770302 | 7973.94ms | 1834197 | 30 | 9.66275e+07 | 2.32985e+06 | 0.0617497 | 6.73047 | 29.2821 | 5.2941 | 0.0266098 | 0.112196 | 7.28929e-05 | 3(Loss) | true |
| Glaze | 709.454 | 0.0837918 | 8413.44ms | 1834197 | 160 | 6.82915e+08 | 2.46559e+06 | 0.0236396 | 7.1758 | 29.3585 | 5.6248 | 0.0333574 | 0.0588438 | 0.000661928 | 4(Loss) | true |
| simdjson (ondemand) | 624.285 | 0.122359 | 9439.84ms | 1834197 | 80 | 9.40347e+08 | 2.80197e+06 | 0.0258948 | 8.15973 | 33.9708 | 6.4563 | 0.0318814 | 0.118999 | 0.000319915 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1347.56 | 0.0609573 | 8636.46ms | 1922245 | 80 | 5.50128e+07 | 1.36038e+06 | 0.0731428 | 3.75451 | 13.1326 | 0.653489 | 0.00226568 | 0.0595354 | 6.76358e-05 | 1(Win) | true |
| simdjson (reflection) | 1342.28 | 0.153714 | 8687.49ms | 1922245 | 40 | 1.76287e+08 | 1.36573e+06 | 0.654474 | 3.79407 | 13.6344 | 1.13441 | 0.00918196 | 0.0529228 | 6.77073e-05 | 2(Loss) | true |
| Glaze | 952.2 | 0.255325 | 5697.74ms | 1833577 | 160 | 3.51761e+09 | 1.83642e+06 | 0.862976 | 5.27836 | 16.0436 | 1.0529 | 0.0010049 | 0.0768802 | 0.000113797 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1343.02 | 0.0347368 | 8601.11ms | 1922245 | 30 | 6.74459e+06 | 1.36498e+06 | 0.212845 | 3.76103 | 13.1325 | 0.653451 | 0.00242577 | 0.0595651 | 6.72304e-05 | 1(Win) | true |
| simdjson (reflection) | 1331.37 | 0.0746034 | 8716.03ms | 1922245 | 160 | 1.68833e+08 | 1.37693e+06 | 0.103148 | 3.80185 | 13.6342 | 1.13437 | 0.00970644 | 0.0528004 | 0.000146489 | 2(Loss) | true |
| Glaze | 1003.33 | 0.2615 | 5408.34ms | 1833577 | 160 | 3.32334e+09 | 1.74283e+06 | 0.225652 | 5.04434 | 16.0427 | 1.0527 | 0.000996836 | 0.0496126 | 6.292e-05 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2567.87 | 0.0676977 | 8514.64ms | 7351818 | 160 | 5.46653e+08 | 2.73037e+06 | 0.137326 | 1.96475 | 8.237 | 1.57998 | 0.0124008 | 0.0616849 | 0.00157642 | 1(Win) | true |
| Jsonifier | 2547.31 | 0.0732182 | 8577ms | 7351818 | 160 | 6.49807e+08 | 2.75241e+06 | 0.0400028 | 1.9801 | 8.24901 | 1.86881 | 0.00911988 | 0.0342127 | 0.000420144 | 2(Loss) | true |
| simdjson (reflection) | 2399.64 | 0.111698 | 9096.81ms | 7351818 | 160 | 1.70416e+09 | 2.92179e+06 | 0.0359375 | 2.09982 | 9.07273 | 1.53412 | 0.00780033 | 0.05869 | 0.000843031 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 2045.01 | 0.0858385 | 5155.65ms | 7351818 | 80 | 6.92869e+08 | 3.42845e+06 | 0.0265144 | 2.46978 | 11.2349 | 2.23756 | 0.0091086 | 0.0339795 | 0.0002357 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2044.07 | 0.189232 | 5172.63ms | 7351818 | 30 | 1.26388e+09 | 3.43003e+06 | 0.317622 | 2.46711 | 10.2389 | 1.82144 | 0.00908031 | 0.0617395 | 0.000945249 | 4(Tie) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2835.03 | 0.0668591 | 8521.98ms | 7351818 | 160 | 4.37438e+08 | 2.47308e+06 | 0.405862 | 1.788 | 7.49457 | 1.40783 | 0.0121221 | 0.0548667 | 0.000841067 | 1(Win) | true |
| Jsonifier | 2776.96 | 0.09676 | 8615.14ms | 7351818 | 160 | 9.54909e+08 | 2.52479e+06 | 0.0218333 | 1.81725 | 7.50676 | 1.69668 | 0.00892244 | 0.0277085 | 0.000431563 | 2(Loss) | true |
| simdjson (reflection) | 2662.28 | 0.0812758 | 8912.1ms | 7351818 | 160 | 7.33037e+08 | 2.63355e+06 | 0.135979 | 1.89571 | 8.32142 | 1.35862 | 0.00656205 | 0.0520583 | 0.000597685 | 3(Loss) | true |
| simdjson (ondemand) | 2236.68 | 0.0836911 | 5075.35ms | 7351818 | 80 | 5.50595e+08 | 3.13467e+06 | 0.547132 | 2.24961 | 9.4908 | 1.64843 | 0.0079031 | 0.053795 | 0.000578061 | 4(Loss) | true |
| Glaze | 2207.12 | 0.127439 | 5143.85ms | 7351818 | 40 | 6.55541e+08 | 3.17664e+06 | 0.131299 | 2.30123 | 10.4916 | 2.06527 | 0.00880636 | 0.0279183 | 0.000114849 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6397.08 | 0.102568 | 9461.33ms | 10018896 | 80 | 1.87754e+08 | 1.49361e+06 | 0.0675865 | 0.791397 | 2.60106 | 0.120868 | 0.00014427 | 0.0249624 | 0.00049996 | 1(Win) | true |
| Glaze | 3097.53 | 0.172093 | 9579.86ms | 9930228 | 160 | 4.42928e+09 | 3.05734e+06 | 0.0384076 | 1.62307 | 4.41437 | 0.474335 | 0.000700253 | 0.0757756 | 0.0103026 | 2(Loss) | true |
| simdjson (reflection) | 437.57 | 0.474413 | 6625.31ms | 10018896 | 30 | 3.21943e+11 | 2.1836e+07 | 2.26131 | 11.5364 | 35.8508 | 5.24904 | 0.0156111 | 0.314241 | 0.158582 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6386.58 | 0.0659855 | 9485.61ms | 10018896 | 80 | 7.79633e+07 | 1.49607e+06 | 0.241842 | 0.791508 | 2.60102 | 0.120861 | 0.00013677 | 0.0249411 | 0.000455106 | 1(Win) | true |
| Glaze | 4123.3 | 0.177499 | 7206.46ms | 9930228 | 80 | 1.32957e+09 | 2.29675e+06 | 0.216512 | 1.23922 | 4.414 | 0.474254 | 0.000760621 | 0.0224472 | 0.000987596 | 2(Loss) | true |
| simdjson (reflection) | 372.811 | 1.69495 | 7712.7ms | 10018896 | 30 | 5.66106e+12 | 2.5629e+07 | 0.741434 | 11.8056 | 35.8497 | 5.24643 | 0.0160262 | 0.290249 | 0.150672 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1544.01 | 0.737106 | 7431.94ms | 461466 | 640 | 2.82502e+09 | 285030 | 0.148331 | 3.27079 | 14.939 | 2.80837 | 0.00866833 | 0.0398425 | 5.8516e-05 | 1(Win) | true |
| simdjson (reflection) | 1176.3 | 0.197618 | 9763ms | 461466 | 640 | 3.4985e+08 | 374131 | 0.301417 | 4.28128 | 18.4618 | 3.18743 | 0.00989797 | 0.0617206 | 7.26083e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1134.09 | 0.392055 | 5062.92ms | 461466 | 320 | 7.40678e+08 | 388055 | 0.109247 | 4.49891 | 19.9238 | 3.43586 | 0.0209315 | 0.0814158 | 0.000540628 | 3(Loss) | true |
| Glaze | 1054.84 | 0.174588 | 5408.73ms | 461466 | 160 | 8.489e+07 | 417209 | 0.315774 | 4.81686 | 20.1344 | 3.93606 | 0.0241073 | 0.0368676 | 0.000114161 | 4(Loss) | true |
| simdjson (ondemand) | 989.317 | 0.305708 | 5758.93ms | 461466 | 320 | 5.91795e+08 | 444840 | 0.0676463 | 5.08626 | 20.1785 | 3.56355 | 0.0116163 | 0.0915716 | 0.000122002 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2404.62 | 0.765989 | 6501.65ms | 461466 | 320 | 6.28901e+08 | 183018 | 0.319222 | 2.10287 | 10.7456 | 1.88237 | 0.00663722 | 0.00471952 | 7.59197e-05 | 1(Win) | true |
| simdjson (reflection) | 1555.52 | 0.22442 | 9070.21ms | 461466 | 640 | 2.58005e+08 | 282920 | 0.0423019 | 3.23178 | 14.8656 | 2.35967 | 0.00373159 | 0.0220451 | 2.24387e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1525.08 | 0.153839 | 9329.67ms | 461466 | 1280 | 2.52253e+08 | 288568 | 0.276977 | 3.3208 | 15.7331 | 2.51029 | 0.0182999 | 0.0243213 | 2.36305e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1328.43 | 0.201926 | 5120.46ms | 461466 | 640 | 2.86396e+08 | 331284 | 0.0629845 | 3.79203 | 16.1988 | 2.66445 | 0.0036602 | 0.0270395 | 2.27773e-05 | 4(Loss) | true |
| Glaze | 1311 | 0.409895 | 5219.16ms | 461466 | 640 | 1.21171e+09 | 335688 | 0.124477 | 3.85652 | 16.3071 | 3.07786 | 0.0215329 | 0.0101633 | 5.01628e-05 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14440.8 | 0.120863 | 3858.04ms | 461466 | 40 | 54267.9 | 30475.3 | 0.416954 | 0.35056 | 1.53813 | 0.19386 | 0.000147248 | 0.00960878 | 1.77695e-05 | 1(Win) | true |
| simdjson (reflection) | 11516.5 | 0.271129 | 4613.25ms | 461466 | 2560 | 2.74809e+07 | 38213.8 | 0.0699867 | 0.439718 | 2.22329 | 0.309397 | 0.00170604 | 0.0120958 | 2.17877e-05 | 2(Loss) | true |
| Glaze | 4556.56 | 0.213877 | 5374.05ms | 461466 | 2560 | 1.09238e+08 | 96583.4 | 0.0281797 | 1.10733 | 4.6601 | 0.714436 | 0.00904201 | 0.0442523 | 2.48546e-05 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14455.1 | 0.115359 | 3846.38ms | 461466 | 30 | 37005 | 30445.2 | 0.0272696 | 0.350161 | 1.53911 | 0.193592 | 0.000143456 | 0.00941702 | 3.79226e-05 | 1(Win) | true |
| simdjson (reflection) | 11613.6 | 0.440177 | 4555.51ms | 461466 | 1280 | 3.56132e+07 | 37894.3 | 0.0226689 | 0.435134 | 2.22218 | 0.309145 | 0.00161312 | 0.0123057 | 3.3421e-05 | 2(Loss) | true |
| Glaze | 5232.96 | 0.149948 | 9325.44ms | 461466 | 40 | 636097 | 84099.3 | 0.243369 | 0.969335 | 4.64554 | 0.711034 | 0.00904075 | 0.0148563 | 3.28843e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2159.07 | 0.267492 | 8438.17ms | 728486 | 320 | 2.37073e+08 | 321777 | 0.10473 | 2.33944 | 10.7925 | 2.0408 | 0.00588458 | 0.0403292 | 2.49361e-05 | 1(Win) | true |
| simdjson (reflection) | 1764.92 | 0.197204 | 5127.88ms | 728486 | 160 | 9.64153e+07 | 393638 | 0.13894 | 2.85418 | 12.2623 | 2.04325 | 0.00751254 | 0.0576742 | 0.000214984 | 2(Loss) | true |
| Jsonifier (two-stage) | 1601.08 | 0.704136 | 5625.3ms | 728486 | 640 | 5.97461e+09 | 433918 | 0.0820229 | 3.16868 | 13.3802 | 2.24404 | 0.0160075 | 0.0723827 | 0.000165448 | 3(Loss) | true |
| simdjson (ondemand) | 1492.41 | 0.222422 | 6024.03ms | 728486 | 320 | 3.43063e+08 | 465515 | 0.00512362 | 3.38145 | 13.3501 | 2.28171 | 0.00863794 | 0.0740479 | 7.74337e-05 | 4(Loss) | true |
| Glaze | 1436.79 | 0.199938 | 6262.11ms | 728486 | 640 | 5.98173e+08 | 483535 | 0.295815 | 3.537 | 15.1964 | 2.98069 | 0.0145905 | 0.0325081 | 0.000322831 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3146.32 | 0.135155 | 7753.59ms | 728486 | 40 | 3.56254e+06 | 220810 | 0.208869 | 1.61112 | 8.13643 | 1.45429 | 0.00446663 | 0.00926888 | 1.58548e-05 | 1(Win) | true |
| simdjson (reflection) | 2297.25 | 0.164383 | 9610.07ms | 728486 | 320 | 7.90839e+07 | 302421 | 0.0120616 | 2.18129 | 9.9783 | 1.51756 | 0.00309614 | 0.0310585 | 2.13928e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2107.6 | 0.99604 | 5167.47ms | 728486 | 320 | 3.44962e+09 | 329635 | 0.468629 | 2.39557 | 10.7239 | 1.65763 | 0.0139378 | 0.0306076 | 0.000107582 | 3(Loss) | true |
| simdjson (ondemand) | 1987.5 | 0.0655967 | 5339.61ms | 728486 | 640 | 3.36491e+07 | 349555 | 0.0555135 | 2.54172 | 10.8257 | 1.71139 | 0.00311632 | 0.0329912 | 3.70117e-05 | 4(Loss) | true |
| Glaze | 1755.9 | 0.072797 | 6058.98ms | 728486 | 320 | 2.65471e+07 | 395658 | 0.31984 | 2.88155 | 12.7684 | 2.43608 | 0.012806 | 0.0115125 | 1.54816e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17973.7 | 0.111697 | 5322.57ms | 837491 | 40 | 98543.7 | 44436.8 | 0.0798963 | 0.286749 | 0.898443 | 0.106783 | 9.52846e-05 | 0.0146239 | 1.92838e-05 | 1(Win) | true |
| Glaze | 4845.11 | 0.174638 | 8867.29ms | 837491 | 2560 | 2.12163e+08 | 164845 | 0.0686527 | 1.03892 | 4.43636 | 0.730161 | 0.00587482 | 0.0587678 | 1.28224e-05 | 2(Loss) | true |
| simdjson (reflection) | 537.884 | 0.367818 | 9416.9ms | 837491 | 320 | 9.5455e+09 | 1.48488e+06 | 0.123402 | 9.35027 | 37.184 | 7.10508 | 0.0258779 | 0.350345 | 0.000873188 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17641.8 | 0.270141 | 5322.99ms | 837491 | 1280 | 1.91454e+07 | 45272.8 | 0.071789 | 0.286704 | 0.897786 | 0.106635 | 8.72584e-05 | 0.014282 | 2.52895e-06 | 1(Win) | true |
| Glaze | 5746.35 | 0.20225 | 7554.06ms | 837491 | 1280 | 1.01149e+08 | 138991 | 0.0264414 | 0.875414 | 4.42726 | 0.728068 | 0.00588784 | 0.0199495 | 1.49936e-05 | 2(Loss) | true |
| simdjson (reflection) | 546.584 | 1.02484 | 9366.2ms | 837491 | 30 | 6.72794e+09 | 1.46125e+06 | 0.152692 | 9.17676 | 37.1838 | 7.10495 | 0.0259536 | 0.349575 | 0.000136996 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8356.74 | 0.0281597 | 6070.37ms | 466906 | 4890 | 1.10091e+06 | 53283.5 | 0.0976327 | 0.605015 | 3.0724 | 0.406915 | 0.000962783 | 7.7388e-06 | 5.60274e-06 | 1(Win) | true |
| Jsonifier | 8347.74 | 0.0272758 | 6102.83ms | 466906 | 4890 | 1.03511e+06 | 53340.9 | 0.227367 | 0.605519 | 3.07366 | 0.407223 | 0.000970927 | 3.0992e-06 | 1.85269e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6905.83 | 0.0628779 | 7194.41ms | 466906 | 2560 | 4.20788e+06 | 64478.3 | 0.0441083 | 0.731371 | 3.59597 | 0.371507 | 0.000861396 | 6.00278e-06 | 3.17499e-06 | 3(Loss) | true |
| simdjson (reflection) | 6776.52 | 0.0319733 | 7329.54ms | 466906 | 1280 | 564977 | 65708.7 | 0.0572193 | 0.747197 | 3.56445 | 0.369929 | 0.000974952 | 4.28519e-06 | 2.56174e-06 | 4(Loss) | true |
| Glaze | 3231.02 | 0.0643964 | 7402.83ms | 466906 | 640 | 5.04062e+06 | 137813 | 0.0315953 | 1.56338 | 6.44723 | 1.02822 | 0.00153298 | 6.19102e-06 | 3.92544e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8658.02 | 0.134094 | 6002.75ms | 466906 | 30 | 142679 | 51429.3 | 0.0425646 | 0.594674 | 3.03887 | 0.399663 | 0.000939518 | 6.42528e-07 | 2.14176e-07 | 1(Win) | true |
| Jsonifier (two-stage) | 8515.56 | 0.128762 | 6003.26ms | 466906 | 640 | 2.90127e+06 | 52289.7 | 0.0612918 | 0.596783 | 3.03882 | 0.399721 | 0.000916589 | 1.82953e-05 | 1.68764e-05 | 2(Loss) | true |
| simdjson (ondemand) | 7100.14 | 0.0394615 | 7073.7ms | 466906 | 1280 | 783940 | 62713.7 | 0.0324995 | 0.716993 | 3.55207 | 0.361788 | 0.000882677 | 8.25246e-06 | 7.24349e-06 | 3(Loss) | true |
| simdjson (reflection) | 6947.31 | 0.209686 | 7311.82ms | 466906 | 30 | 541860 | 64093.3 | 0.0614351 | 0.741401 | 3.54128 | 0.364521 | 0.00095244 | 2.6415e-06 | 1.7848e-06 | 4(Loss) | true |
| Glaze | 3292.81 | 0.0742186 | 7360.22ms | 466906 | 640 | 6.44662e+06 | 135227 | 0.112865 | 1.54976 | 6.39747 | 1.01713 | 0.00150555 | 8.20227e-06 | 7.05107e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9569.12 | 0.217645 | 7108.14ms | 631514 | 80 | 1.5011e+06 | 62937.7 | 0.0705758 | 0.536856 | 2.69828 | 0.311943 | 0.000727577 | 4.87519e-05 | 1.5637e-05 | 1(Win) | true |
| Jsonifier | 9432.96 | 0.0720895 | 7105.08ms | 631514 | 40 | 84737.2 | 63846.2 | 0.0289712 | 0.536057 | 2.69858 | 0.312015 | 0.00073304 | 2.79883e-05 | 7.24449e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8186.65 | 0.0490179 | 8081.96ms | 631514 | 1280 | 1.66446e+06 | 73565.9 | 0.0255626 | 0.617419 | 3.02916 | 0.290049 | 0.000633663 | 1.24354e-05 | 3.91544e-06 | 3(Loss) | true |
| simdjson (reflection) | 8140.16 | 0.09917 | 8174.57ms | 631514 | 160 | 861351 | 73986.1 | 0.18347 | 0.627458 | 3.00761 | 0.289292 | 0.000728082 | 2.39504e-06 | 1.08865e-07 | 4(Loss) | true |
| Glaze | 3852.03 | 0.0368537 | 8372.64ms | 631514 | 2560 | 8.49938e+06 | 156348 | 0.121196 | 1.32207 | 5.85935 | 0.963143 | 0.0014715 | 6.52759e-06 | 4.33977e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9684.37 | 0.0640449 | 7030.81ms | 631514 | 1280 | 2.03049e+06 | 62188.7 | 0.265184 | 0.526782 | 2.67526 | 0.307062 | 0.000699913 | 2.6437e-06 | 2.0771e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 9668.04 | 0.0318439 | 7022.97ms | 631514 | 4890 | 1.92421e+06 | 62293.8 | 0.00487891 | 0.527079 | 2.67465 | 0.306899 | 0.000690223 | 6.67108e-06 | 5.80777e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8423.28 | 0.0590745 | 7948.12ms | 631514 | 320 | 570891 | 71499.3 | 0.0272612 | 0.603208 | 3.00059 | 0.283799 | 0.000641826 | 3.60245e-06 | 2.8305e-06 | 3(Loss) | true |
| simdjson (reflection) | 8208.84 | 0.0390188 | 8227.49ms | 631514 | 4890 | 4.00737e+06 | 73367.1 | 0.0537698 | 0.621796 | 2.9924 | 0.285764 | 0.00070769 | 1.20368e-05 | 1.12159e-05 | 4(Loss) | true |
| Glaze | 3863.53 | 0.108927 | 8343.47ms | 631514 | 30 | 864939 | 155883 | 0.0851149 | 1.30729 | 5.82639 | 0.956019 | 0.00145418 | 2.655e-05 | 2.47553e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2270.6 | 0.073744 | 5199.42ms | 466906 | 1280 | 2.67696e+07 | 196105 | 0.100485 | 2.19722 | 6.62104 | 1.2012 | 0.0104029 | 0.0140528 | 6.57788e-05 | 1(Win) | true |
| Glaze | 1726 | 0.146685 | 6818.85ms | 466906 | 640 | 9.16497e+07 | 257981 | 0.0409806 | 2.91551 | 10.4305 | 1.87129 | 0.0130369 | 0.0170376 | 7.26023e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1634.85 | 0.215947 | 7165.57ms | 466906 | 320 | 1.10701e+08 | 272366 | 0.137459 | 3.07707 | 9.39713 | 1.49232 | 0.020977 | 0.028194 | 0.00019919 | 3(Loss) | true |
| simdjson (reflection) | 1587.43 | 0.169232 | 7386.61ms | 466906 | 640 | 1.44216e+08 | 280501 | 0.191224 | 3.15912 | 10.0994 | 1.51196 | 0.0133674 | 0.0266209 | 0.000226193 | 4(Loss) | true |
| simdjson (ondemand) | 1148.78 | 0.132152 | 5054.53ms | 466906 | 640 | 1.67924e+08 | 387607 | 0.320167 | 4.3799 | 13.1012 | 2.73535 | 0.0137849 | 0.0465015 | 0.000120835 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3048.76 | 0.0696038 | 9306.47ms | 466906 | 1280 | 1.32278e+07 | 146051 | 0.250194 | 1.63756 | 5.18698 | 0.876202 | 0.00756197 | 0.00227771 | 1.40954e-05 | 1(Win) | true |
| Glaze | 2252.47 | 0.224252 | 5987.43ms | 466906 | 160 | 3.14437e+07 | 197683 | 0.063073 | 2.22592 | 8.99193 | 1.54406 | 0.00655748 | 0.0026751 | 3.96895e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2033.58 | 0.179575 | 6456.72ms | 466906 | 320 | 4.94744e+07 | 218962 | 0.116639 | 2.45862 | 7.9594 | 1.16669 | 0.0167803 | 0.0069382 | 2.27495e-05 | 3(Loss) | true |
| simdjson (reflection) | 1875.12 | 0.337961 | 7059.15ms | 466906 | 80 | 5.15256e+07 | 237465 | 0.254816 | 2.66157 | 9.0508 | 1.26695 | 0.00790031 | 0.0187926 | 2.7709e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1333.11 | 0.229767 | 9434.63ms | 466906 | 160 | 9.42378e+07 | 334014 | 0.000338682 | 3.7679 | 11.7593 | 2.43232 | 0.0105762 | 0.00930597 | 1.16324e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15593 | 0.0592577 | 3697.38ms | 475954 | 160 | 47608.1 | 29109.6 | 0.117776 | 0.324479 | 1.05401 | 0.138763 | 0.000265729 | 0.00377393 | 6.19808e-06 | 1(Win) | true |
| simdjson (reflection) | 12505.1 | 0.111504 | 4385.82ms | 475954 | 4890 | 8.01024e+06 | 36297.5 | 0.0242856 | 0.397777 | 1.27104 | 0.180557 | 0.000267574 | 0.00225494 | 4.58363e-06 | 2(Loss) | true |
| Glaze | 7451.62 | 0.247644 | 6918.32ms | 475954 | 2560 | 5.82538e+07 | 60913.6 | 0.201757 | 0.679761 | 2.22757 | 0.324927 | 0.000262646 | 0.0141709 | 6.80623e-06 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15659.7 | 0.0985747 | 3707.33ms | 475954 | 80 | 65310.8 | 28985.6 | 0.372072 | 0.322975 | 1.0529 | 0.138513 | 0.00025462 | 0.00368168 | 4.56977e-06 | 1(Win) | true |
| simdjson (reflection) | 12524.5 | 0.110137 | 4388.8ms | 475954 | 30 | 47796.5 | 36241.5 | 0.0271402 | 0.396281 | 1.26996 | 0.180312 | 0.000263051 | 0.00221695 | 1.48474e-05 | 2(Loss) | true |
| Glaze | 8472.37 | 0.110007 | 6128.38ms | 475954 | 4890 | 1.6985e+07 | 53574.8 | 0.151202 | 0.59185 | 2.21522 | 0.322105 | 0.000258647 | 0.000689836 | 4.19306e-06 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2597.41 | 0.201215 | 6154.98ms | 631514 | 30 | 6.53019e+06 | 231869 | 0.0358264 | 1.956 | 5.70893 | 1.04266 | 0.00775554 | 0.021928 | 0.00020596 | 1(Win) | true |
| simdjson (reflection) | 2066.28 | 0.0748804 | 7651.46ms | 631514 | 1280 | 6.09726e+07 | 291470 | 0.254887 | 2.4429 | 7.84593 | 1.13563 | 0.0100501 | 0.038208 | 5.93477e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2046.98 | 0.119975 | 7721.91ms | 631514 | 1280 | 1.59489e+08 | 294218 | 0.0584925 | 2.4883 | 7.47094 | 1.14017 | 0.0166611 | 0.0347728 | 0.00017199 | 3(Loss) | true |
| Glaze | 1885.55 | 0.0379685 | 8413.61ms | 631514 | 1280 | 1.88255e+07 | 319407 | 0.449281 | 2.69455 | 9.2881 | 1.71589 | 0.0105359 | 0.0187988 | 0.000127175 | 4(Loss) | true |
| simdjson (ondemand) | 1509.27 | 0.161291 | 5166.53ms | 631514 | 320 | 1.32557e+08 | 399040 | 0.357938 | 3.34311 | 10.066 | 2.03979 | 0.0107071 | 0.0492259 | 0.000143005 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3288.65 | 0.0932618 | 5602.01ms | 631514 | 1280 | 3.73377e+07 | 183132 | 0.0882082 | 1.5447 | 4.65055 | 0.803405 | 0.00583127 | 0.00528721 | 4.74195e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2523.96 | 0.117728 | 7052.76ms | 631514 | 640 | 5.05056e+07 | 238616 | 0.0398382 | 2.00979 | 6.40937 | 0.900268 | 0.0134701 | 0.0106339 | 1.67801e-05 | 2(Loss) | true |
| simdjson (reflection) | 2380.5 | 0.283679 | 7311.33ms | 631514 | 80 | 4.12074e+07 | 252997 | 0.516221 | 2.09807 | 7.06828 | 0.953525 | 0.00721573 | 0.028484 | 1.09855e-05 | 3(Loss) | true |
| Glaze | 2235.12 | 0.0702382 | 7825.34ms | 631514 | 320 | 1.1462e+07 | 269453 | 0.120038 | 2.26051 | 8.23177 | 1.47669 | 0.00830162 | 0.00399486 | 3.90827e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1749.97 | 0.153573 | 9655.06ms | 631514 | 640 | 1.78778e+08 | 344154 | 0.140038 | 2.89277 | 9.06973 | 1.81516 | 0.00810843 | 0.0199851 | 5.38562e-05 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18632 | 0.0776244 | 4453.14ms | 716365 | 80 | 64809.4 | 36667.1 | 0.033147 | 0.271451 | 0.751061 | 0.0922044 | 0.000176603 | 0.0038969 | 1.60358e-05 | 1(Win) | true |
| Glaze | 5109.06 | 0.106826 | 7285.69ms | 716365 | 2560 | 5.22373e+07 | 133719 | 0.0373857 | 0.985299 | 2.70587 | 0.438066 | 0.000356153 | 0.0480719 | 5.48396e-06 | 2(Loss) | true |
| simdjson (reflection) | 536.711 | 0.230217 | 8050.04ms | 716365 | 320 | 2.74797e+09 | 1.2729e+06 | 0.253113 | 9.4455 | 30.5385 | 6.83028 | 0.0701844 | 0.29354 | 0.00129595 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18630 | 0.117589 | 4429.99ms | 716365 | 2560 | 4.76008e+06 | 36670.9 | 0.229384 | 0.271341 | 0.750301 | 0.0920313 | 0.000175843 | 0.00353395 | 8.46068e-06 | 1(Win) | true |
| Glaze | 6470.63 | 0.199045 | 5769.93ms | 716365 | 640 | 2.82657e+07 | 105582 | 0.113434 | 0.780965 | 2.69622 | 0.435824 | 0.000330998 | 0.00260586 | 5.37872e-06 | 2(Loss) | true |
| simdjson (reflection) | 535.514 | 0.313069 | 8140.54ms | 716365 | 160 | 2.55227e+09 | 1.27574e+06 | 0.273247 | 9.3992 | 30.5378 | 6.83002 | 0.0700141 | 0.293109 | 0.00119039 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2977.28 | 0.133246 | 798.627ms | 2632 | 320 | 403.825 | 843.075 | 0.118473 | 1.82084 | 7.07219 | 1.25 | 0.00076819 | 3.68066e-05 | 2.01843e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2018.92 | 0.504208 | 842.125ms | 2632 | 160 | 6287.45 | 1243.28 | 0.521497 | 2.6238 | 10.8469 | 1.69377 | 0.00078125 | 5.22416e-05 | 4.74924e-06 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2002.34 | 0.0456875 | 861.376ms | 2632 | 4890 | 1603.99 | 1253.57 | 0.217362 | 2.64495 | 11.0171 | 2.11968 | 0.000709919 | 5.76513e-05 | 1.82588e-05 | 2(Tie) | true |
| simdjson (reflection) | 1785.78 | 0.0555555 | 859.974ms | 2632 | 4890 | 2981.82 | 1405.59 | 0.0431534 | 2.96329 | 9.50456 | 1.56345 | 0.00211492 | 5.22902e-05 | 1.24315e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1732.37 | 0.102603 | 871.86ms | 2632 | 2560 | 5657.84 | 1448.92 | 0.294367 | 3.05117 | 10.3822 | 1.95023 | 0.00167322 | 6.97545e-05 | 1.63255e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3544.32 | 0.0723947 | 797.292ms | 2632 | 2560 | 672.915 | 708.196 | 0.130563 | 1.53301 | 6.16109 | 1.00874 | 0.000767893 | 2.18168e-05 | 3.71034e-06 | 1(Win) | true |
| Glaze | 2550.87 | 0.058388 | 823.028ms | 2632 | 4890 | 1614.17 | 984.004 | 0.12769 | 2.09703 | 9.23366 | 1.68351 | 0.0010486 | 2.80487e-05 | 8.46899e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2336.45 | 0.0322852 | 838.958ms | 2632 | 1280 | 153.984 | 1074.31 | 0.000509051 | 2.28803 | 9.93085 | 1.44909 | 0.000760175 | 3.29479e-05 | 4.74924e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2104.2 | 0.0964842 | 853.13ms | 2632 | 80 | 105.975 | 1192.89 | 0.181612 | 2.52998 | 8.70555 | 1.55357 | 0.00138203 | 1.8997e-05 | 1.42477e-05 | 4(Loss) | true |
| simdjson (reflection) | 1990.58 | 0.178261 | 855.062ms | 2632 | 320 | 1616.87 | 1260.97 | 0.345754 | 2.67348 | 8.61816 | 1.32789 | 0.00209441 | 0.000213716 | 0.000140103 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9930.49 | 0.14654 | 738.806ms | 2632 | 1280 | 175.611 | 252.764 | 0.424723 | 0.601422 | 1.95821 | 0.301292 | 0.000379939 | 2.81986e-05 | 5.63972e-06 | 1(Win) | true |
| simdjson (reflection) | 7425.22 | 0.0885673 | 749.909ms | 2632 | 4890 | 438.338 | 338.047 | 0.414804 | 0.773158 | 2.72606 | 0.450608 | 0.000380483 | 3.5663e-05 | 5.90499e-06 | 2(Loss) | true |
| Glaze | 4510.54 | 0.142881 | 774.465ms | 2632 | 640 | 404.617 | 556.491 | 0.0897681 | 1.22277 | 4.13564 | 0.683891 | 0.000383501 | 2.73081e-05 | 1.78097e-06 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11721.9 | 0.218715 | 734.166ms | 2632 | 640 | 140.384 | 214.136 | 0.0386878 | 0.523716 | 1.74891 | 0.251682 | 0.000387063 | 2.49335e-05 | 1.42477e-05 | 1(Win) | true |
| simdjson (reflection) | 8441.82 | 0.455321 | 742.403ms | 2632 | 640 | 1173.04 | 297.337 | 0.222315 | 0.68985 | 2.51824 | 0.401216 | 0.000382314 | 1.48414e-05 | 4.74924e-06 | 2(Loss) | true |
| Glaze | 5410.55 | 0.131014 | 761.211ms | 2632 | 320 | 118.216 | 463.922 | 0.018184 | 1.05261 | 3.59005 | 0.569529 | 0.000379939 | 3.91812e-05 | 1.5435e-05 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3087.85 | 0.0951583 | 821.786ms | 3370 | 640 | 627.798 | 1040.81 | 0.06715 | 1.7297 | 6.83027 | 1.23027 | 0.000595326 | 3.38464e-05 | 6.02745e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2362.04 | 0.0967458 | 856.905ms | 3370 | 2560 | 4435.98 | 1360.64 | 0.0818012 | 2.23424 | 9.0914 | 1.40326 | 0.000711239 | 3.18759e-05 | 8.11387e-06 | 2(Loss) | true |
| simdjson (reflection) | 2198.45 | 0.0481264 | 873.026ms | 3370 | 4890 | 2420.49 | 1461.89 | 0.0188747 | 2.37127 | 7.73597 | 1.23473 | 0.00172544 | 4.29023e-05 | 1.12262e-05 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 2140.65 | 0.129772 | 884.178ms | 3370 | 640 | 2429.47 | 1501.36 | 0.243705 | 2.46976 | 10.635 | 2.05519 | 0.000646792 | 4.21921e-05 | 1.25185e-05 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2138.17 | 0.1097 | 895.621ms | 3370 | 80 | 217.509 | 1503.1 | 0.0332757 | 2.47536 | 8.52997 | 1.55935 | 0.00114614 | 0.000107567 | 3.7092e-05 | 4(Tie) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3618.65 | 0.0605911 | 817.021ms | 3370 | 320 | 92.6689 | 888.144 | 0.0309539 | 1.48934 | 6.1184 | 1.04184 | 0.000593472 | 1.48368e-05 | 5.5638e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2695.19 | 0.0573743 | 852.605ms | 3370 | 320 | 149.785 | 1192.45 | 0.27728 | 1.97535 | 8.37596 | 1.21217 | 0.000593472 | 1.66914e-05 | 0 | 2(Loss) | true |
| Glaze | 2588.57 | 0.135789 | 850.292ms | 3370 | 640 | 1819.07 | 1241.57 | 0.0325843 | 2.06077 | 9.15017 | 1.69021 | 0.00114151 | 2.36461e-05 | 4.6365e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2559.78 | 0.0673733 | 861.587ms | 3370 | 320 | 228.971 | 1255.53 | 0.124105 | 2.03885 | 7.11157 | 1.227 | 0.0012092 | 1.02003e-05 | 1.8546e-06 | 4(Loss) | true |
| simdjson (reflection) | 2489.84 | 0.192272 | 866.613ms | 3370 | 30 | 184.786 | 1290.8 | 0.185586 | 2.1348 | 7.04451 | 1.05104 | 0.00163205 | 0.000158259 | 2.96736e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11925.1 | 0.209226 | 752.351ms | 3643 | 640 | 237.795 | 291.337 | 0.0311162 | 0.489684 | 1.47049 | 0.224815 | 0.000274499 | 9.007e-06 | 1.71562e-06 | 1(Win) | true |
| Glaze | 4215.11 | 0.143694 | 808.562ms | 3682 | 2560 | 3668.34 | 833.057 | 0.383388 | 1.27085 | 4.28463 | 0.719175 | 0.000277214 | 9.145e-05 | 4.17996e-05 | 2(Loss) | true |
| simdjson (reflection) | 536.661 | 0.0673901 | 1387.63ms | 3643 | 4890 | 93072.1 | 6473.8 | 0.279991 | 9.45474 | 36.0244 | 7.55092 | 0.0156527 | 0.000283368 | 0.000126247 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15523.8 | 0.137766 | 737.087ms | 3643 | 2560 | 243.361 | 223.801 | 0.458502 | 0.392703 | 1.29701 | 0.181718 | 0.000274713 | 3.63497e-05 | 2.61632e-05 | 1(Win) | true |
| Glaze | 4897.13 | 0.45158 | 796.95ms | 3682 | 80 | 838.771 | 717.038 | 0.33408 | 1.10969 | 3.92205 | 0.637154 | 0.000271592 | 1.69745e-05 | 3.39489e-06 | 2(Loss) | true |
| simdjson (reflection) | 531.88 | 0.206615 | 1387.73ms | 3643 | 640 | 116572 | 6531.99 | 0.306987 | 9.50735 | 36.0458 | 7.55573 | 0.0159218 | 0.000229035 | 0.000135963 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 928.392 | 0.0791312 | 1206.1ms | 4630 | 80 | 1133.14 | 4756.09 | 0.0317912 | 5.59668 | 26.4309 | 5.69719 | 0.00345842 | 0.00011879 | 8.63931e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 783.009 | 0.14622 | 1294.86ms | 4630 | 320 | 21756.5 | 5639.16 | 0.0834708 | 6.60951 | 29.6672 | 6.11059 | 0.0031466 | 4.45464e-05 | 1.2824e-05 | 2(Loss) | true |
| simdjson (reflection) | 757.119 | 0.0965984 | 1318.93ms | 4630 | 320 | 10156 | 5831.99 | 0.0750199 | 6.83845 | 27.9585 | 5.18035 | 0.00978334 | 2.83477e-05 | 6.07451e-06 | 3(Loss) | true |
| Glaze | 723.66 | 0.0250999 | 1334.25ms | 4630 | 4890 | 11469.5 | 6101.64 | 0.270194 | 7.05832 | 30.5838 | 5.84255 | 0.0057519 | 0.000103884 | 3.70572e-05 | 4(Loss) | true |
| simdjson (ondemand) | 665.85 | 0.103375 | 1388.4ms | 4630 | 80 | 3759.51 | 6631.39 | 0.264026 | 7.78438 | 31.1352 | 6.01058 | 0.00784017 | 0.000275378 | 0.000197084 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1120.3 | 0.0865426 | 1214.66ms | 4630 | 320 | 3723.08 | 3941.36 | 0.0404529 | 4.55949 | 22.1035 | 4.71447 | 0.000888904 | 2.29482e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 923.181 | 0.0794082 | 1290.81ms | 4630 | 30 | 432.754 | 4782.93 | 0.00627191 | 5.63545 | 25.327 | 5.12462 | 0.00192945 | 5.0396e-05 | 7.19942e-06 | 2(Loss) | true |
| Glaze | 864.72 | 0.0474803 | 1336.78ms | 4630 | 160 | 940.498 | 5106.29 | 0.259421 | 6.00631 | 26.1114 | 4.82613 | 0.00441415 | 2.83477e-05 | 5.39957e-06 | 3(Loss) | true |
| simdjson (reflection) | 849.717 | 0.0970586 | 1336.52ms | 4630 | 80 | 2035.04 | 5196.45 | 0.0817198 | 6.00006 | 25.0257 | 4.51231 | 0.00866901 | 5.12959e-05 | 1.34989e-05 | 4(Loss) | true |
| simdjson (ondemand) | 744.487 | 0.0932191 | 1411.49ms | 4630 | 1280 | 39126.3 | 5930.95 | 0.0508714 | 6.82787 | 27.74 | 5.25033 | 0.00409692 | 7.35691e-05 | 3.03726e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2030.54 | 0.148931 | 947.807ms | 4630 | 40 | 419.536 | 2174.55 | 0.11254 | 2.53739 | 7.78488 | 0.411231 | 0.00024838 | 1.07991e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 1740.49 | 0.0541292 | 978.192ms | 4630 | 4890 | 9221.25 | 2536.93 | 0.123983 | 2.98416 | 9.91037 | 0.586826 | 0.000226318 | 5.23394e-05 | 2.09799e-05 | 2(Loss) | true |
| Glaze | 1542.56 | 0.0409399 | 1013.27ms | 4630 | 4890 | 6715.56 | 2862.46 | 0.0342402 | 3.34804 | 10.0108 | 0.722895 | 0.000220355 | 7.61902e-05 | 2.53084e-05 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2103.13 | 0.0692116 | 935.932ms | 4630 | 160 | 337.836 | 2099.49 | 0.0645572 | 2.49683 | 7.67322 | 0.385097 | 0.000236231 | 7.42441e-05 | 2.69978e-06 | 1(Win) | true |
| simdjson (reflection) | 1784.47 | 0.0378872 | 969.404ms | 4630 | 640 | 562.48 | 2474.41 | 0.23624 | 2.94816 | 9.84125 | 0.57041 | 0.00022172 | 3.00351e-05 | 6.41199e-06 | 2(Loss) | true |
| Glaze | 1716.07 | 0.250347 | 977.719ms | 4630 | 30 | 1244.79 | 2573.03 | 0.363998 | 2.99482 | 9.48315 | 0.60432 | 0.000215983 | 6.47948e-05 | 0 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1973.16 | 0.0299676 | 1293.57ms | 11579 | 4890 | 13754 | 5596.39 | 0.420272 | 2.60608 | 12.4859 | 2.64928 | 0.00211177 | 4.33406e-05 | 1.79614e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1932.74 | 0.0438918 | 1312.75ms | 11579 | 160 | 1006.2 | 5713.45 | 0.237723 | 2.68442 | 12.5652 | 2.46351 | 0.00172295 | 1.56533e-05 | 1.07954e-06 | 2(Loss) | true |
| simdjson (reflection) | 1758.27 | 0.0424725 | 1374.57ms | 11579 | 1280 | 9107.43 | 6280.38 | 0.490246 | 2.89273 | 11.7989 | 2.06572 | 0.00392852 | 9.27055e-05 | 5.33698e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1577.09 | 0.035245 | 1436.68ms | 11579 | 2560 | 15590.7 | 7001.89 | 0.175422 | 3.22396 | 13.0983 | 2.40349 | 0.00272348 | 4.29792e-05 | 1.98366e-05 | 4(Loss) | true |
| Glaze | 1381.16 | 0.0683922 | 1520.38ms | 11579 | 40 | 1195.99 | 7995.18 | 0.113217 | 3.68015 | 15.4857 | 2.88376 | 0.00580577 | 4.96589e-05 | 1.29545e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2333.58 | 0.0525712 | 1294.08ms | 11579 | 2560 | 15842.9 | 4732.04 | 0.0623845 | 2.21291 | 10.7749 | 2.26116 | 0.00168391 | 4.98613e-05 | 2.94175e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2238.86 | 0.100073 | 1320.82ms | 11579 | 640 | 15591.9 | 4932.24 | 0.286439 | 2.28627 | 10.8496 | 2.07445 | 0.00127008 | 1.80823e-05 | 4.58805e-06 | 2(Loss) | true |
| simdjson (reflection) | 1995.28 | 0.0342649 | 1380.24ms | 11579 | 4890 | 17585 | 5534.37 | 0.169564 | 2.55559 | 10.7243 | 1.81769 | 0.0028413 | 3.91549e-05 | 2.34364e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1745.47 | 0.0579399 | 1460.67ms | 11579 | 640 | 8599.08 | 6326.42 | 0.0104978 | 2.91377 | 11.9738 | 2.14682 | 0.00179595 | 1.25497e-05 | 2.69885e-07 | 4(Loss) | true |
| Glaze | 1562.75 | 0.0463241 | 1529.05ms | 11579 | 1280 | 13714.7 | 7066.11 | 0.227616 | 3.27927 | 13.7408 | 2.48778 | 0.00516972 | 5.35047e-05 | 2.73933e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6294.73 | 0.0549602 | 946.36ms | 14795 | 4890 | 7421.33 | 2241.5 | 0.057273 | 0.834073 | 2.50085 | 0.129436 | 6.81018e-05 | 2.62898e-05 | 1.03252e-05 | 1(Win) | true |
| Glaze | 3586.5 | 0.104638 | 1126.28ms | 14795 | 320 | 5422.73 | 3934.09 | 0.0281275 | 1.42483 | 4.53282 | 0.518756 | 6.80128e-05 | 1.4363e-05 | 1.26732e-06 | 2(Loss) | true |
| simdjson (reflection) | 474.368 | 0.102827 | 3714.11ms | 14795 | 2560 | 2.39469e+06 | 29744 | 0.0924938 | 10.8041 | 37.6348 | 5.21737 | 0.00430712 | 8.75771e-05 | 4.14255e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6513.79 | 0.0658916 | 939.222ms | 14795 | 320 | 651.887 | 2166.11 | 0.0225108 | 0.806059 | 2.46157 | 0.120514 | 6.80128e-05 | 9.71612e-06 | 8.4488e-07 | 1(Win) | true |
| Glaze | 3906.03 | 0.0811206 | 1090.86ms | 14795 | 4890 | 41988.5 | 3612.27 | 0.244547 | 1.31861 | 4.33721 | 0.47462 | 0.000132707 | 1.35457e-05 | 3.51083e-06 | 2(Loss) | true |
| simdjson (reflection) | 470.224 | 0.0974488 | 3744.47ms | 14795 | 2560 | 2.18883e+06 | 30006.1 | 0.0183301 | 10.8612 | 37.6661 | 5.2246 | 0.00438105 | 9.3148e-05 | 5.21449e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1920.79 | 0.0532702 | 889.44ms | 3223 | 4890 | 3553.36 | 1600.22 | 0.206387 | 2.70762 | 10.9156 | 1.93857 | 0.00108734 | 6.90335e-05 | 2.84255e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1451.33 | 0.0682985 | 941.713ms | 3223 | 2560 | 5356.11 | 2117.84 | 0.0426803 | 3.57085 | 14.4421 | 2.42755 | 0.00109576 | 9.88985e-05 | 5.34488e-05 | 2(Loss) | true |
| Glaze | 1383.7 | 0.172228 | 953.607ms | 3223 | 40 | 585.464 | 2221.35 | 0.27461 | 3.79215 | 14.6196 | 2.83339 | 0.001722 | 7.75675e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1218.09 | 0.0477518 | 984.37ms | 3223 | 4890 | 7099.88 | 2523.37 | 0.10001 | 4.235 | 15.6587 | 2.73844 | 0.00199004 | 9.25734e-05 | 3.01387e-05 | 4(Loss) | true |
| simdjson (reflection) | 1211.77 | 0.0446937 | 985.2ms | 3223 | 1280 | 1645.08 | 2536.54 | 0.27634 | 4.24235 | 15.3838 | 2.63885 | 0.00100062 | 7.22347e-05 | 2.2543e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2342.82 | 0.126896 | 916.102ms | 3223 | 80 | 221.733 | 1311.96 | 0.261327 | 2.22903 | 9.47161 | 1.56035 | 0.00108207 | 1.93919e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1714.15 | 0.111931 | 928.941ms | 3223 | 80 | 322.263 | 1793.12 | 0.115586 | 3.07478 | 12.9978 | 2.04902 | 0.00117903 | 7.75675e-05 | 1.55135e-05 | 2(Loss) | true |
| Glaze | 1610.97 | 0.140307 | 942.981ms | 3223 | 80 | 573.316 | 1907.97 | 0.0301276 | 3.26628 | 13.0661 | 2.43376 | 0.00127986 | 5.04189e-05 | 7.75675e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1401.84 | 0.0462295 | 971.53ms | 3223 | 4890 | 5024.23 | 2192.61 | 0.0406439 | 3.70463 | 14.112 | 2.34905 | 0.00169234 | 0.000160465 | 6.87162e-05 | 4(Loss) | true |
| simdjson (reflection) | 1381.12 | 0.0764089 | 975.343ms | 3223 | 2560 | 7402.6 | 2225.5 | 0.13801 | 3.7401 | 13.892 | 2.25039 | 0.00160286 | 0.00014653 | 5.15097e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8222.83 | 0.303644 | 757.396ms | 3223 | 30 | 38.6483 | 373.8 | 0.348993 | 0.71298 | 2.17716 | 0.283276 | 0.00031027 | 8.27386e-05 | 1.03423e-05 | 1(Win) | true |
| simdjson (reflection) | 7196.45 | 0.214874 | 763.02ms | 3223 | 2560 | 2156.21 | 427.113 | 0.0301718 | 0.783326 | 2.45734 | 0.313683 | 0.000311118 | 8.53242e-05 | 4.59345e-05 | 2(Loss) | true |
| Glaze | 3468.3 | 0.51792 | 808.969ms | 3223 | 320 | 6741.61 | 886.225 | 0.421385 | 1.55037 | 4.97084 | 0.759852 | 0.000316087 | 8.92026e-05 | 4.65405e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9071.4 | 0.204611 | 753.219ms | 3223 | 30 | 14.4195 | 338.833 | 0.343137 | 0.64561 | 2.01644 | 0.245734 | 0.00031027 | 0.00013445 | 4.13693e-05 | 1(Win) | true |
| simdjson (reflection) | 7820.99 | 0.0697652 | 758.133ms | 3223 | 1280 | 96.2244 | 393.005 | 0.0686291 | 0.723001 | 2.29693 | 0.27583 | 0.000310512 | 1.76951e-05 | 2.42398e-06 | 2(Loss) | true |
| Glaze | 4086.84 | 0.213248 | 789.9ms | 3223 | 4890 | 12578.3 | 752.094 | 0.370741 | 1.34023 | 4.40242 | 0.633571 | 0.000311666 | 0.000111862 | 5.8818e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2699.13 | 0.114474 | 929.764ms | 5839 | 1280 | 7139.27 | 2063.08 | 0.0821821 | 1.95779 | 7.84364 | 1.45008 | 0.000589918 | 4.04072e-05 | 1.61896e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2445.39 | 0.050512 | 951.872ms | 5839 | 320 | 423.369 | 2277.14 | 0.296615 | 2.14463 | 8.73574 | 1.39544 | 0.000611192 | 2.03374e-05 | 1.07039e-06 | 2(Loss) | true |
| simdjson (reflection) | 2172.48 | 0.0450883 | 981.356ms | 5839 | 4890 | 6531.31 | 2563.2 | 0.18207 | 2.40018 | 8.99452 | 1.46224 | 0.000604881 | 4.89271e-05 | 1.56553e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2127.25 | 0.051916 | 984.749ms | 5839 | 4890 | 9031.29 | 2617.7 | 0.0968729 | 2.45407 | 9.23549 | 1.53691 | 0.00103052 | 5.13436e-05 | 1.55502e-05 | 4(Loss) | true |
| Glaze | 1796.11 | 0.0810609 | 1030.52ms | 5839 | 4890 | 30884.6 | 3100.31 | 0.0454112 | 2.8967 | 11.2009 | 2.14044 | 0.0017239 | 7.84864e-05 | 3.67391e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3136.31 | 0.120866 | 921.775ms | 5839 | 1280 | 5894.67 | 1775.5 | 0.137756 | 1.67873 | 7.04675 | 1.24131 | 0.00063086 | 3.63932e-05 | 7.35892e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2792.92 | 0.0760169 | 942.28ms | 5839 | 4890 | 11232.8 | 1993.79 | 0.059347 | 1.87995 | 7.93852 | 1.1865 | 0.000636332 | 4.4269e-05 | 6.09399e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2439.52 | 0.0634163 | 974.143ms | 5839 | 2560 | 5364.26 | 2282.62 | 0.0379422 | 2.15179 | 8.38106 | 1.32103 | 0.000943213 | 4.26149e-05 | 8.09482e-06 | 3(Loss) | true |
| simdjson (reflection) | 2380.39 | 0.152128 | 985.114ms | 5839 | 80 | 1013.18 | 2339.32 | 0.0181643 | 2.20256 | 8.32899 | 1.28224 | 0.0011132 | 3.21117e-05 | 4.28156e-06 | 4(Loss) | true |
| Glaze | 2014.99 | 0.151413 | 1015.69ms | 5839 | 320 | 5602.83 | 2763.54 | 0.000904646 | 2.5918 | 10.3408 | 1.91985 | 0.00138027 | 2.99709e-05 | 1.07039e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16603.7 | 0.317291 | 760.339ms | 6938 | 40 | 63.9487 | 398.5 | 0.0251004 | 0.342563 | 1.0467 | 0.125829 | 0.000147737 | 3.24301e-05 | 0 | 1(Win) | true |
| Glaze | 2770.82 | 0.243703 | 964.807ms | 6960 | 1280 | 43624.8 | 2395.53 | 0.00736996 | 1.89052 | 4.28549 | 0.706322 | 0.00028803 | 3.69298e-05 | 1.11126e-05 | 2(Loss) | true |
| simdjson (reflection) | 517.893 | 0.0823422 | 2012.71ms | 6938 | 4890 | 541181 | 12776 | 0.109988 | 9.96082 | 38.5643 | 7.26074 | 0.0074562 | 0.000117989 | 4.96657e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17641.3 | 0.13967 | 756.827ms | 6938 | 320 | 87.8143 | 375.062 | 0.0316714 | 0.32618 | 1.00029 | 0.11473 | 0.000144584 | 2.38722e-05 | 9.45878e-06 | 1(Win) | true |
| Glaze | 3377.73 | 0.201155 | 921.205ms | 6960 | 4890 | 76408.4 | 1965.1 | 0.645762 | 1.55583 | 3.91135 | 0.627299 | 0.000318061 | 4.04297e-05 | 1.61895e-05 | 2(Loss) | true |
| simdjson (reflection) | 514.206 | 0.114717 | 2020.83ms | 6938 | 2560 | 557818 | 12867.6 | 0.0409595 | 9.99733 | 38.5842 | 7.26499 | 0.00823128 | 0.000106468 | 4.79695e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2355.2 | 0.0802141 | 917.633ms | 4857 | 2560 | 6371.18 | 1966.71 | 0.309421 | 2.22561 | 8.76385 | 1.60984 | 0.000247066 | 7.33477e-05 | 3.95692e-05 | 1(Win) | true |
| Glaze | 1810.81 | 0.199632 | 974.395ms | 4857 | 320 | 8344.51 | 2557.97 | 0.0488908 | 2.88798 | 11.344 | 2.24017 | 0.00091556 | 6.30533e-05 | 1.22246e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1665.36 | 0.053691 | 1001.28ms | 4857 | 2560 | 5709.06 | 2781.38 | 0.124684 | 3.1597 | 12.6866 | 2.06547 | 0.00106933 | 0.000101738 | 4.75313e-05 | 3(Loss) | true |
| simdjson (reflection) | 1576.65 | 0.0974021 | 1018.83ms | 4857 | 160 | 1310.15 | 2937.87 | 0.0639935 | 3.3134 | 12.8328 | 2.14947 | 0.000832561 | 4.50381e-05 | 1.67284e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1306.13 | 0.0657232 | 1077.12ms | 4857 | 2560 | 13907.1 | 3546.34 | 0.0635485 | 3.98812 | 14.3214 | 2.68293 | 0.00141693 | 0.000106483 | 5.51717e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3191.45 | 0.0485692 | 891.489ms | 4857 | 1280 | 636.052 | 1451.38 | 0.0852288 | 1.66767 | 6.69776 | 1.13136 | 0.00020621 | 5.22764e-05 | 1.57633e-05 | 1(Win) | true |
| Glaze | 2599.85 | 0.0739099 | 921.806ms | 4857 | 4890 | 8479.15 | 1781.64 | 0.00964262 | 2.02839 | 8.52357 | 1.58616 | 0.00143153 | 4.36197e-05 | 1.68837e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2034.14 | 0.164371 | 969.401ms | 4857 | 80 | 1120.77 | 2277.12 | 0.141426 | 2.584 | 10.6164 | 1.58102 | 0.000965102 | 0.000113239 | 4.88985e-05 | 3(Loss) | true |
| simdjson (reflection) | 1839.81 | 0.120624 | 1002.08ms | 4857 | 1280 | 11805 | 2517.65 | 0.206159 | 2.83695 | 11.476 | 1.82376 | 0.000871004 | 5.6941e-05 | 9.65102e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1577.51 | 0.0768798 | 1036.9ms | 4857 | 1280 | 6522.68 | 2936.27 | 0.070265 | 3.32342 | 11.9442 | 2.16286 | 0.00259355 | 4.47164e-05 | 4.66466e-06 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11159.8 | 0.188597 | 761.939ms | 4857 | 80 | 49.0214 | 415.062 | 0.268752 | 0.507744 | 1.65905 | 0.241713 | 0.000205888 | 2.31624e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7853.84 | 0.20685 | 778.081ms | 4857 | 80 | 119.063 | 589.775 | 0.127006 | 0.700399 | 2.06691 | 0.330245 | 0.000205888 | 2.57361e-05 | 5.14721e-06 | 2(Loss) | true |
| Glaze | 4136.26 | 0.21067 | 831.398ms | 4857 | 1280 | 7124.25 | 1119.85 | 0.0498561 | 1.30237 | 3.72967 | 0.610665 | 0.000415798 | 5.51717e-05 | 6.27316e-06 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11771.2 | 0.0738524 | 759.349ms | 4857 | 4890 | 412.981 | 393.501 | 0.288226 | 0.480046 | 1.59069 | 0.225448 | 0.000206015 | 2.03783e-05 | 7.57871e-06 | 1(Win) | true |
| simdjson (reflection) | 9260.29 | 0.132958 | 770.492ms | 4857 | 30 | 13.269 | 500.2 | 0.0998602 | 0.612552 | 1.93515 | 0.296685 | 0.000281381 | 2.74518e-05 | 0 | 2(Loss) | true |
| Glaze | 4931.82 | 0.399079 | 814.349ms | 4857 | 640 | 8991.24 | 939.206 | 0.0216226 | 1.09258 | 3.23286 | 0.496603 | 0.000209105 | 2.2519e-05 | 1.2868e-06 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2601.31 | 0.0673014 | 966.138ms | 6701 | 1280 | 3499.07 | 2456.67 | 0.214736 | 2.01028 | 7.52455 | 1.40263 | 0.000746973 | 4.52358e-05 | 1.65554e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2114.75 | 0.0800638 | 1022.32ms | 6701 | 1280 | 7492.78 | 3021.9 | 0.127073 | 2.42911 | 9.74168 | 1.53828 | 0.000933163 | 8.96555e-05 | 4.43031e-05 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2106.48 | 0.21429 | 1031.06ms | 6701 | 30 | 1267.91 | 3033.77 | 0.0373434 | 2.47847 | 9.7472 | 1.58021 | 0.000542208 | 0.00023877 | 0.000134308 | 2(Tie) | true |
| Glaze | 2025.81 | 0.113868 | 1039.84ms | 6701 | 80 | 1032.22 | 3154.57 | 0.0467356 | 2.57518 | 10.4326 | 2.11013 | 0.00108379 | 0.000119385 | 8.20773e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1756.86 | 0.0721968 | 1088.36ms | 6701 | 1280 | 8827.79 | 3637.5 | 0.26738 | 2.96758 | 10.8099 | 1.96359 | 0.00103576 | 4.08055e-05 | 1.10758e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3414.09 | 0.119768 | 932.749ms | 6701 | 1280 | 6433.14 | 1871.82 | 0.0563773 | 1.54082 | 6.02686 | 1.05611 | 0.000542013 | 4.27875e-05 | 1.01431e-05 | 1(Win) | true |
| Glaze | 2696.8 | 0.109731 | 985.533ms | 6701 | 1280 | 8654.6 | 2369.68 | 0.366099 | 1.95262 | 8.42934 | 1.64632 | 0.000949602 | 2.01696e-05 | 4.31372e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2665.11 | 0.184326 | 986.009ms | 6701 | 80 | 1562.83 | 2397.86 | 0.031789 | 1.96716 | 8.24071 | 1.18699 | 0.000936427 | 4.47694e-05 | 3.73079e-06 | 3(Loss) | true |
| simdjson (reflection) | 2372.57 | 0.0523325 | 1022.17ms | 6701 | 640 | 1271.64 | 2693.53 | 0.318322 | 2.16501 | 8.75989 | 1.34338 | 0.000844557 | 4.96661e-05 | 6.06253e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2128.64 | 0.0718966 | 1044.12ms | 6701 | 640 | 2981.74 | 3002.18 | 0.00520428 | 2.45303 | 9.02477 | 1.57409 | 0.00165227 | 2.0053e-05 | 1.39904e-06 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15158.3 | 0.0809382 | 769.466ms | 7376 | 1280 | 180.575 | 464.056 | 0.150059 | 0.367964 | 1.1833 | 0.169469 | 0.000135787 | 1.85356e-05 | 2.9657e-06 | 1(Win) | true |
| Glaze | 3118.15 | 0.12475 | 954.294ms | 7376 | 4890 | 38729.1 | 2255.92 | 0.237924 | 1.67227 | 4.11781 | 0.685738 | 0.000138098 | 5.75015e-05 | 1.83262e-05 | 2(Loss) | true |
| simdjson (reflection) | 536.984 | 0.164989 | 2064.6ms | 7376 | 640 | 298957 | 13099.7 | 0.0540514 | 9.54069 | 39.4162 | 8.02888 | 0.0127362 | 7.90147e-05 | 2.47848e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16952 | 0.13281 | 763.644ms | 7376 | 2560 | 777.506 | 414.954 | 0.648978 | 0.332047 | 1.09599 | 0.149268 | 0.000135575 | 2.52614e-05 | 7.25537e-06 | 1(Win) | true |
| Glaze | 3636.82 | 0.245145 | 919.669ms | 7376 | 2560 | 57555.1 | 1934.19 | 0.227294 | 1.43415 | 3.798 | 0.61307 | 0.000158453 | 3.52706e-05 | 1.48285e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.622 | 0.151972 | 2077.46ms | 7376 | 1280 | 525449 | 13332.1 | 0.458037 | 9.7689 | 39.3871 | 8.02319 | 0.0130416 | 0.000117251 | 5.77252e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2382.16 | 0.295692 | 788.982ms | 1691 | 40 | 160.281 | 676.975 | 0.00369276 | 2.33315 | 7.6369 | 1.3838 | 0.000591366 | 0.000133057 | 0.000118273 | 1(Win) | true |
| Glaze | 1966.04 | 0.219092 | 804.093ms | 1691 | 2560 | 8267.91 | 820.26 | 0.10025 | 2.74143 | 10.1023 | 1.98344 | 0.00115409 | 8.33919e-05 | 1.13191e-05 | 2(Loss) | true |
| simdjson (reflection) | 1778.55 | 0.183262 | 813.952ms | 1691 | 160 | 441.795 | 906.731 | 0.206523 | 3.02751 | 9.87995 | 1.644 | 0.00178519 | 0.000133057 | 3.69604e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1723.68 | 0.19035 | 814.207ms | 1691 | 1280 | 4059.68 | 935.595 | 0.110686 | 3.09592 | 11.0556 | 1.77173 | 0.00060615 | 9.8869e-05 | 2.07902e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1538.71 | 0.243758 | 828.269ms | 1691 | 80 | 522.135 | 1048.06 | 0.177394 | 3.47403 | 10.5695 | 1.6984 | 0.00178888 | 0.000125665 | 7.39208e-06 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3008.74 | 0.0813221 | 777.718ms | 1691 | 640 | 121.595 | 535.992 | 0.772622 | 1.84279 | 6.09758 | 1.00118 | 0.000591366 | 3.60364e-05 | 2.77203e-06 | 1(Win) | true |
| Glaze | 2478.14 | 0.0999303 | 790.469ms | 1691 | 320 | 135.326 | 650.756 | 0.0844457 | 2.20679 | 8.57363 | 1.60201 | 0.00115686 | 6.28326e-05 | 7.39208e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2098.9 | 0.336732 | 805.4ms | 1691 | 2560 | 17136.2 | 768.339 | 0.0159105 | 2.5851 | 9.51272 | 1.38853 | 0.000597603 | 7.46138e-05 | 1.17811e-05 | 3(Loss) | true |
| simdjson (reflection) | 2014.65 | 0.0997271 | 811.364ms | 1691 | 2560 | 1631.38 | 800.468 | 0.856307 | 2.71197 | 8.92727 | 1.38676 | 0.00177595 | 9.5866e-05 | 1.75562e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1809.01 | 0.215941 | 819.443ms | 1691 | 4890 | 18121.2 | 891.464 | 0.16412 | 2.99375 | 9.18332 | 1.35009 | 0.00150804 | 0.000149353 | 3.38615e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8504.68 | 0.0904947 | 743.583ms | 1996 | 640 | 26.2562 | 223.822 | 0.257631 | 0.715476 | 1.59719 | 0.26002 | 0.000501002 | 1.95704e-05 | 1.56563e-06 | 1(Win) | true |
| simdjson (reflection) | 6707.9 | 0.106683 | 747.343ms | 1996 | 40 | 3.66603 | 283.775 | 0.13783 | 0.887149 | 1.94539 | 0.288076 | 0.000501002 | 2.50501e-05 | 0 | 2(Loss) | true |
| Glaze | 5278.06 | 0.29264 | 754.723ms | 1996 | 4890 | 5446.88 | 360.651 | 0.346417 | 1.07863 | 3.45541 | 0.568637 | 0.000501924 | 6.86444e-05 | 4.35431e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10402.2 | 0.15946 | 735.739ms | 1996 | 320 | 27.2476 | 182.994 | 0.0682617 | 0.601577 | 1.35721 | 0.203908 | 0.000501002 | 2.50501e-05 | 3.13126e-06 | 1(Win) | true |
| simdjson (reflection) | 7614.14 | 0.12609 | 742.76ms | 1996 | 80 | 7.94937 | 250 | 0.020004 | 0.794282 | 1.70541 | 0.231463 | 0.000501002 | 0 | 0 | 2(Loss) | true |
| Glaze | 5376.26 | 0.470877 | 752.016ms | 1996 | 4890 | 13592 | 354.063 | 0.529485 | 1.06595 | 2.96042 | 0.462926 | 0.000501412 | 2.9302e-05 | 1.07577e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2579.35 | 0.304795 | 801.386ms | 2158 | 4890 | 28920.6 | 797.887 | 0.130863 | 2.10959 | 6.97637 | 1.26969 | 0.00046813 | 7.6853e-05 | 1.98055e-05 | 1(Win) | true |
| simdjson (reflection) | 2195.71 | 0.203316 | 817.326ms | 2158 | 1280 | 4648.41 | 937.294 | 0.214088 | 2.43193 | 8.00927 | 1.29935 | 0.00139488 | 0.000138656 | 3.69266e-05 | 2(Loss) | true |
| Glaze | 2070.74 | 0.138261 | 818.877ms | 2158 | 80 | 151.057 | 993.862 | 0.00880481 | 2.63479 | 9.6988 | 1.89481 | 0.000498146 | 7.53012e-05 | 2.31696e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 2000.78 | 0.207717 | 823.963ms | 2158 | 4890 | 22323.1 | 1028.61 | 0.0269712 | 2.65646 | 9.21872 | 1.44254 | 0.000467846 | 0.000110115 | 3.09876e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1960.32 | 0.16252 | 826.878ms | 2158 | 160 | 465.78 | 1049.84 | 0.239297 | 2.77565 | 8.54958 | 1.34198 | 0.00121061 | 9.84708e-05 | 2.31696e-05 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3310.68 | 0.225725 | 793.051ms | 2158 | 30 | 59.0678 | 621.633 | 0.430826 | 1.69095 | 5.76738 | 0.96988 | 0.000463392 | 0.000139018 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2530.36 | 0.276334 | 807.09ms | 2158 | 30 | 151.54 | 813.333 | 0.184767 | 2.13594 | 8.00973 | 1.14226 | 0.000463392 | 7.7232e-05 | 1.54464e-05 | 2(Loss) | true |
| simdjson (reflection) | 2463.68 | 0.206615 | 816.043ms | 2158 | 4890 | 14566.9 | 835.347 | 0.163518 | 2.19628 | 7.26274 | 1.09778 | 0.0011834 | 9.1257e-05 | 1.83841e-05 | 3(Loss) | true |
| Glaze | 2387.41 | 0.156675 | 811.174ms | 2158 | 30 | 54.723 | 862.033 | 0.563851 | 2.22765 | 8.49861 | 1.59546 | 0.000478838 | 4.63392e-05 | 1.54464e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2245.06 | 0.0653655 | 820.908ms | 2158 | 1280 | 459.572 | 916.691 | 0.347783 | 2.40179 | 7.46339 | 1.06905 | 0.00122618 | 6.48025e-05 | 3.62025e-06 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11425 | 0.0920138 | 740.574ms | 2866 | 4890 | 236.948 | 239.232 | 0.0524404 | 0.529253 | 1.15701 | 0.182833 | 0.000349132 | 4.17418e-05 | 7.42076e-06 | 1(Win) | true |
| Glaze | 3748.69 | 0.176752 | 790.878ms | 2866 | 2560 | 4251.71 | 729.116 | 0.215998 | 1.45131 | 4.05373 | 0.675855 | 0.000360095 | 6.01066e-05 | 1.94904e-05 | 2(Loss) | true |
| simdjson (reflection) | 523.319 | 0.0789729 | 1249.71ms | 2866 | 4890 | 83192.6 | 5222.88 | 0.196582 | 9.92242 | 35.9198 | 7.52443 | 0.00753314 | 0.000165683 | 6.1364e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13816.7 | 0.487063 | 735.75ms | 2866 | 4890 | 4539.67 | 197.821 | 0.145925 | 0.448366 | 0.98709 | 0.14201 | 0.000349561 | 2.14774e-05 | 8.63377e-06 | 1(Win) | true |
| Glaze | 4496.77 | 0.276761 | 780.268ms | 2866 | 4890 | 13837.9 | 607.821 | 0.181199 | 1.22272 | 3.3709 | 0.529658 | 0.000350774 | 2.92549e-05 | 9.13324e-06 | 2(Loss) | true |
| simdjson (reflection) | 523.512 | 0.115018 | 1249.48ms | 2866 | 2560 | 92314.3 | 5220.95 | 0.0437282 | 9.8604 | 35.4021 | 7.42272 | 0.00795902 | 0.000145701 | 4.83852e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2408.87 | 0.0732094 | 893.138ms | 4390 | 2560 | 4144.55 | 1738.01 | 0.169662 | 2.18055 | 10.3087 | 1.69499 | 0.0011499 | 2.7406e-05 | 6.94049e-06 | 1(Win) | true |
| Glaze | 1835.29 | 0.0639587 | 947.513ms | 4390 | 4890 | 10409.4 | 2281.18 | 0.0578844 | 2.8407 | 13.1419 | 2.61298 | 0.0006005 | 6.57751e-05 | 3.35397e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1596.56 | 0.0617022 | 984.936ms | 4390 | 160 | 418.873 | 2622.29 | 0.108566 | 3.27782 | 15.3175 | 2.40501 | 0.00395644 | 5.9795e-05 | 2.2779e-05 | 3(Loss) | true |
| simdjson (reflection) | 1532.27 | 0.0484276 | 995.128ms | 4390 | 2560 | 4482.12 | 2732.3 | 0.293786 | 3.41357 | 13.2278 | 2.12187 | 0.00196736 | 3.6838e-05 | 7.11845e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1193.08 | 0.0916637 | 1072.41ms | 4390 | 1280 | 13243.3 | 3509.1 | 0.135546 | 4.3638 | 17.3731 | 3.07722 | 0.0019259 | 6.83371e-05 | 2.11774e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2792.25 | 0.11288 | 894.532ms | 4390 | 160 | 458.324 | 1499.38 | 0.053384 | 1.87493 | 9.13599 | 1.4221 | 0.00091828 | 3.70159e-05 | 0 | 1(Win) | true |
| Glaze | 2137.9 | 0.0742949 | 935.372ms | 4390 | 640 | 1354.73 | 1958.3 | 0.0895226 | 2.44728 | 11.6973 | 2.28428 | 0.000594391 | 1.74402e-05 | 7.11845e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 1780.39 | 0.0801407 | 984.378ms | 4390 | 1280 | 4545.87 | 2351.53 | 0.0197716 | 2.96082 | 14.1437 | 2.13144 | 0.003687 | 2.22452e-05 | 3.2033e-06 | 3(Loss) | true |
| simdjson (reflection) | 1692.21 | 0.0579555 | 986.84ms | 4390 | 4890 | 10053.6 | 2474.07 | 0.0249378 | 3.09055 | 12.1715 | 1.87335 | 0.00210024 | 3.15366e-05 | 9.40975e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1310.51 | 0.087411 | 1061.82ms | 4390 | 1280 | 9981.44 | 3194.66 | 0.0759165 | 3.98123 | 15.9262 | 2.75923 | 0.00299936 | 8.2574e-05 | 3.89735e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11206.5 | 0.103267 | 748.925ms | 4390 | 640 | 95.2563 | 373.591 | 0.0133818 | 0.51558 | 2.01207 | 0.250569 | 0.00022779 | 2.2779e-05 | 7.11845e-07 | 1(Win) | true |
| simdjson (reflection) | 8665.73 | 0.162405 | 765.863ms | 4390 | 40 | 24.625 | 483.125 | 0.101872 | 0.655262 | 2.45854 | 0.375171 | 0.00022779 | 3.41686e-05 | 2.2779e-05 | 2(Loss) | true |
| Glaze | 3854.92 | 0.0978801 | 828.082ms | 4390 | 4890 | 5525.8 | 1086.05 | 0.409777 | 1.38591 | 4.76538 | 0.753075 | 0.000228582 | 7.55575e-05 | 3.54496e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12123.3 | 0.183085 | 746.699ms | 4390 | 160 | 63.9608 | 345.337 | 0.489861 | 0.480662 | 1.89818 | 0.224374 | 0.00022779 | 1.42369e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 9028.77 | 0.634764 | 763.397ms | 4390 | 2560 | 22178.8 | 463.699 | 0.211639 | 0.621605 | 2.34487 | 0.348975 | 0.00022868 | 5.62358e-05 | 1.91308e-05 | 2(Loss) | true |
| Glaze | 4226.76 | 0.232074 | 814.717ms | 4390 | 1280 | 6763.57 | 990.505 | 0.12019 | 1.26851 | 4.36743 | 0.663098 | 0.000229392 | 4.21768e-05 | 1.92198e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3691.83 | 0.0852833 | 957.973ms | 9378 | 2560 | 10927.1 | 2422.53 | 0.224896 | 1.41717 | 6.60621 | 1.13702 | 0.00152876 | 6.10221e-05 | 4.21115e-05 | 1(Win) | true |
| simdjson (reflection) | 3068.78 | 0.134598 | 1015.52ms | 9378 | 30 | 461.62 | 2914.37 | 0.00571847 | 1.73412 | 6.89401 | 1.02367 | 0.00115519 | 1.77721e-05 | 3.55442e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2998.35 | 0.0796971 | 1027.2ms | 9378 | 80 | 452.096 | 2982.82 | 0.0351891 | 1.77402 | 8.23683 | 1.25357 | 0.0019927 | 2.13265e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2392.8 | 0.0381759 | 1094.85ms | 9378 | 4890 | 9956.3 | 3737.7 | 0.10884 | 2.18023 | 8.80753 | 1.46556 | 0.00101351 | 2.5884e-05 | 7.04342e-06 | 4(Loss) | true |
| Glaze | 2388.85 | 0.0572584 | 1094ms | 9378 | 160 | 735.263 | 3743.88 | 0.0602287 | 2.17972 | 9.47121 | 1.81009 | 0.00356619 | 2.1993e-05 | 1.33291e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4103.47 | 0.0713013 | 961.031ms | 9378 | 4890 | 11809.2 | 2179.51 | 0.0167073 | 1.27949 | 6.05662 | 1.00928 | 0.00152742 | 1.19934e-05 | 3.53261e-06 | 1(Win) | true |
| simdjson (reflection) | 3333.94 | 0.0600546 | 1011.16ms | 9378 | 320 | 830.514 | 2682.58 | 0.0299475 | 1.56933 | 6.41118 | 0.909682 | 0.000575149 | 4.86511e-05 | 2.1993e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 3264.19 | 0.141824 | 1025.4ms | 9378 | 30 | 452.99 | 2739.9 | 0.0425625 | 1.63359 | 7.68735 | 1.12551 | 0.00204024 | 0.000131513 | 0.000113741 | 3(Loss) | true |
| Glaze | 2629.04 | 0.143795 | 1079.86ms | 9378 | 320 | 7657.06 | 3401.83 | 0.0127705 | 1.98235 | 8.81926 | 1.66112 | 0.0036395 | 2.06601e-05 | 2.66581e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2616.25 | 0.0384705 | 1086.54ms | 9378 | 4890 | 8457.21 | 3418.46 | 0.0861722 | 1.9931 | 8.15718 | 1.32203 | 0.00133917 | 1.76413e-05 | 1.61366e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 22751.1 | 0.226558 | 759.835ms | 11521 | 320 | 383.077 | 482.934 | 0.463511 | 0.24819 | 0.82571 | 0.097561 | 8.6798e-05 | 3.87879e-05 | 2.27845e-05 | 1(Win) | true |
| Glaze | 5542.62 | 0.150954 | 918.159ms | 11521 | 2560 | 22923.5 | 1982.33 | 0.161343 | 0.951892 | 3.9126 | 0.665481 | 0.000226895 | 8.6459e-05 | 5.22822e-05 | 2(Loss) | true |
| simdjson (reflection) | 525.276 | 0.146006 | 2822.08ms | 11521 | 2560 | 2.38773e+06 | 20917.2 | 0.461831 | 9.68044 | 38.0418 | 7.00811 | 0.0114673 | 9.53761e-05 | 4.83831e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26139.2 | 0.107907 | 753.699ms | 11521 | 4890 | 1006.01 | 420.338 | 0.303299 | 0.217829 | 0.774238 | 0.0854961 | 8.69755e-05 | 1.95429e-05 | 1.13423e-05 | 1(Win) | true |
| Glaze | 6749.3 | 0.101106 | 880.255ms | 11521 | 4890 | 13247.3 | 1627.91 | 0.0253966 | 0.781223 | 3.64795 | 0.607847 | 0.000273156 | 3.27667e-05 | 1.63833e-05 | 2(Loss) | true |
| simdjson (reflection) | 522.184 | 0.288904 | 2826.98ms | 11521 | 640 | 2.36495e+06 | 21041 | 0.0152553 | 9.74798 | 38.02 | 7.00109 | 0.0130217 | 5.27569e-05 | 2.41407e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3235.68 | 0.0899031 | 851.644ms | 4669 | 320 | 489.799 | 1376.13 | 0.0991384 | 1.63964 | 6.8293 | 1.36753 | 0.000637181 | 3.94892e-05 | 1.67327e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2178.39 | 0.0656639 | 921.225ms | 4669 | 4890 | 8809.25 | 2044.03 | 0.00897359 | 2.4187 | 9.93275 | 1.7689 | 0.00115179 | 8.78614e-05 | 5.53185e-05 | 2(Loss) | true |
| Glaze | 2120.43 | 0.0973049 | 929.688ms | 4669 | 1280 | 5344.14 | 2099.9 | 0.404813 | 2.48406 | 9.59006 | 1.81688 | 0.000992249 | 2.94496e-05 | 4.3505e-06 | 3(Loss) | true |
| simdjson (reflection) | 1774.37 | 0.0505038 | 971.258ms | 4669 | 4890 | 7854.46 | 2509.46 | 0.351662 | 2.96128 | 12.3502 | 1.80531 | 0.00101575 | 8.76862e-05 | 3.58716e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1381.69 | 0.108735 | 1045.1ms | 4669 | 320 | 3929.35 | 3222.66 | 0.148434 | 3.79516 | 14.674 | 2.54144 | 0.00139283 | 3.34654e-05 | 7.36239e-06 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3613.21 | 0.332775 | 842.71ms | 4669 | 320 | 5381.62 | 1232.34 | 0.114235 | 1.48508 | 6.3791 | 1.25723 | 0.000606393 | 3.54733e-05 | 2.20872e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2335.65 | 0.200716 | 912.708ms | 4669 | 320 | 4685.42 | 1906.41 | 0.249845 | 2.26353 | 8.88263 | 1.65282 | 0.00100798 | 1.27169e-05 | 0 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2326.64 | 0.0614486 | 912.227ms | 4669 | 2560 | 3540.43 | 1913.8 | 0.179152 | 2.25631 | 9.48212 | 1.65839 | 0.00109549 | 3.4804e-05 | 4.76882e-06 | 2(Tie) | true |
| simdjson (reflection) | 1829.91 | 0.0410116 | 969.2ms | 4669 | 4890 | 4869.82 | 2433.29 | 0.267607 | 2.86127 | 12.081 | 1.7342 | 0.00094186 | 4.16969e-05 | 9.28545e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1533.59 | 0.0978907 | 1020.37ms | 4669 | 40 | 323.126 | 2903.45 | 0.236514 | 3.469 | 13.8604 | 2.3776 | 0.00124224 | 1.07089e-05 | 0 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13952.9 | 0.0846274 | 750.765ms | 4669 | 160 | 11.6698 | 319.125 | 0.175953 | 0.415488 | 1.34911 | 0.178197 | 0.000215517 | 2.81109e-05 | 4.01585e-06 | 1(Win) | true |
| simdjson (reflection) | 10676.8 | 0.188722 | 761.229ms | 4669 | 640 | 396.453 | 417.045 | 0.881026 | 0.530592 | 1.6239 | 0.188477 | 0.000214179 | 1.87406e-05 | 1.67327e-06 | 2(Loss) | true |
| Glaze | 3952.34 | 0.395334 | 833.06ms | 4669 | 80 | 1586.93 | 1126.6 | 0.0732828 | 1.35099 | 3.43993 | 0.494969 | 0.000428357 | 2.94496e-05 | 2.67723e-06 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16019.8 | 0.141087 | 742.458ms | 4669 | 40 | 6.15128 | 277.95 | 0.0539957 | 0.375337 | 1.23752 | 0.152281 | 0.000214179 | 1.07089e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 11760.3 | 0.424777 | 755.343ms | 4669 | 4890 | 12648.7 | 378.623 | 0.145234 | 0.487993 | 1.51381 | 0.16299 | 0.000214441 | 2.54036e-05 | 2.45276e-06 | 2(Loss) | true |
| Glaze | 4587.13 | 0.147318 | 816.321ms | 4669 | 4890 | 9999.63 | 970.694 | 0.22259 | 1.16877 | 2.95716 | 0.386378 | 0.000214529 | 2.22063e-05 | 5.25592e-06 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3942.23 | 0.0577969 | 911.079ms | 7932 | 2560 | 3148.7 | 1918.85 | 0.128269 | 1.34789 | 5.51198 | 1.09518 | 0.000653504 | 1.98464e-05 | 7.63324e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3315.86 | 0.0646888 | 946.815ms | 7932 | 160 | 348.458 | 2281.32 | 0.00246562 | 1.58069 | 6.55724 | 1.08976 | 0.000822617 | 1.4971e-05 | 1.5759e-06 | 2(Loss) | true |
| simdjson (reflection) | 2827.18 | 0.0435216 | 989.698ms | 7932 | 4890 | 6631 | 2675.65 | 0.341956 | 1.85324 | 7.84884 | 1.08623 | 0.000605402 | 3.95746e-05 | 1.47728e-05 | 3(Loss) | true |
| Glaze | 2446.59 | 0.110229 | 1037.12ms | 7932 | 30 | 348.464 | 3091.87 | 0.0409845 | 2.17546 | 8.49206 | 1.65305 | 0.00177761 | 1.68095e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 2236.08 | 0.0394389 | 1061.3ms | 7932 | 4890 | 8704.59 | 3382.95 | 0.473006 | 2.33439 | 9.21672 | 1.51954 | 0.000798789 | 4.30551e-05 | 1.80728e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4260.8 | 0.0851471 | 900.931ms | 7932 | 1280 | 2925.05 | 1775.38 | 0.0467111 | 1.23928 | 5.2466 | 1.03013 | 0.00064592 | 9.55386e-06 | 1.18192e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3531.1 | 0.0539412 | 936.829ms | 7932 | 2560 | 3418.42 | 2142.26 | 0.0935271 | 1.48657 | 6.29198 | 1.02471 | 0.000682609 | 1.23609e-05 | 2.65932e-06 | 2(Loss) | true |
| simdjson (reflection) | 2926.17 | 0.0588977 | 982.678ms | 7932 | 2560 | 5934.76 | 2585.13 | 0.151091 | 1.78752 | 7.69037 | 1.04438 | 0.00047395 | 2.83169e-05 | 7.97797e-06 | 3(Loss) | true |
| Glaze | 2565.58 | 0.0420865 | 1019.43ms | 7932 | 2560 | 3942.04 | 2948.48 | 0.0144916 | 2.03959 | 8.07526 | 1.55648 | 0.00187615 | 1.95509e-05 | 6.20509e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2436.8 | 0.0523935 | 1037.43ms | 7932 | 2560 | 6772.06 | 3104.29 | 0.177842 | 2.14607 | 8.73777 | 1.4231 | 0.000795926 | 2.89571e-05 | 1.1376e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24218.3 | 0.10137 | 754.317ms | 9249 | 4890 | 666.543 | 364.21 | 0.029472 | 0.236299 | 0.74181 | 0.0934155 | 0.000108208 | 2.04963e-05 | 3.8251e-06 | 1(Win) | true |
| Glaze | 2998.85 | 0.152321 | 1012.9ms | 9249 | 2560 | 51385.5 | 2941.31 | 0.241125 | 1.746 | 3.78863 | 0.623527 | 0.000328541 | 5.32152e-05 | 2.4876e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.32 | 0.0695365 | 2414.91ms | 9249 | 4890 | 669162 | 16822.8 | 0.192218 | 9.85842 | 40.8036 | 8.29099 | 0.0144181 | 0.000151368 | 7.48216e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 28498.2 | 0.111743 | 747.402ms | 9249 | 80 | 9.56946 | 309.512 | 0.293952 | 0.207622 | 0.672721 | 0.0768732 | 0.00010812 | 2.70299e-06 | 0 | 1(Win) | true |
| Glaze | 3867.36 | 0.190044 | 947.037ms | 9249 | 4890 | 91870.8 | 2280.76 | 0.389323 | 1.36424 | 3.52752 | 0.565359 | 0.000427239 | 1.59858e-05 | 4.48841e-06 | 2(Loss) | true |
| simdjson (reflection) | 522.592 | 0.0689174 | 2415.71ms | 9249 | 4890 | 661654 | 16878.4 | 0.226167 | 9.85696 | 40.8179 | 8.29468 | 0.0145816 | 0.000108297 | 5.21805e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 868.262 | 0.0357388 | 1231.44ms | 4604 | 4890 | 15971.9 | 5056.9 | 0.141509 | 5.97516 | 24.4658 | 5.40899 | 0.00286929 | 8.83912e-05 | 3.78439e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 750.961 | 0.0634177 | 1312.32ms | 4604 | 1280 | 17598.2 | 5846.8 | 0.0680998 | 6.89687 | 29.199 | 5.90662 | 0.00297788 | 6.4482e-05 | 2.64715e-05 | 2(Loss) | true |
| simdjson (reflection) | 649.761 | 0.0848437 | 1406.85ms | 4604 | 640 | 21036.9 | 6757.43 | 0.0251407 | 7.95566 | 29.997 | 5.79127 | 0.00268381 | 9.19717e-05 | 3.59742e-05 | 3(Loss) | true |
| Glaze | 630.094 | 0.0986817 | 1420.55ms | 4604 | 320 | 15131.6 | 6968.36 | 0.0839316 | 8.21463 | 33.9523 | 6.95727 | 0.00600497 | 9.02748e-05 | 4.00467e-05 | 4(Loss) | true |
| simdjson (ondemand) | 500.447 | 0.0307085 | 1607.29ms | 4604 | 4890 | 35496 | 8773.58 | 0.0956219 | 10.2854 | 37.4225 | 7.56951 | 0.0047311 | 0.000186554 | 0.000104293 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1050.38 | 0.0476083 | 1226.91ms | 4604 | 4890 | 19366.4 | 4180.11 | 0.022904 | 4.94778 | 20.2954 | 4.44375 | 0.00267763 | 9.70082e-05 | 3.29579e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 887.578 | 0.0612225 | 1303.45ms | 4604 | 2560 | 23481.1 | 4946.85 | 0.0554733 | 5.85082 | 24.9628 | 4.93039 | 0.00246974 | 7.61905e-05 | 2.36717e-05 | 2(Loss) | true |
| simdjson (reflection) | 746.91 | 0.0472653 | 1400.78ms | 4604 | 4890 | 37750.9 | 5878.5 | 0.0703501 | 6.94144 | 26.0028 | 4.88986 | 0.00278055 | 0.000176427 | 0.000104559 | 3(Loss) | true |
| Glaze | 732.54 | 0.0320385 | 1410.85ms | 4604 | 4890 | 18032.8 | 5993.83 | 0.0996004 | 7.0528 | 29.3934 | 5.91073 | 0.00673288 | 8.42159e-05 | 3.58006e-05 | 4(Loss) | true |
| simdjson (ondemand) | 544.52 | 0.0501121 | 1626.9ms | 4604 | 2560 | 41799.1 | 8063.46 | 0.275278 | 9.45162 | 33.0647 | 6.59489 | 0.0103292 | 0.000143388 | 6.99969e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1946.56 | 0.0687807 | 959.082ms | 4918 | 2560 | 7030.99 | 2409.47 | 0.108707 | 2.68923 | 9.68931 | 0.818016 | 0.00067863 | 7.57739e-05 | 3.70927e-05 | 1(Win) | true |
| Jsonifier | 1496.22 | 0.276785 | 1032.21ms | 4918 | 640 | 48178.4 | 3134.69 | 0.111828 | 3.49683 | 9.09089 | 0.493088 | 0.000275455 | 4.92451e-05 | 9.53131e-06 | 2(Loss) | true |
| Glaze | 1215.31 | 0.0754437 | 1085.38ms | 4604 | 2560 | 19018.9 | 3612.84 | 0.459672 | 4.30421 | 12.7587 | 1.08275 | 0.000570665 | 0.00012311 | 4.14042e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1984.6 | 0.0866221 | 956.606ms | 4918 | 2560 | 10728.2 | 2363.28 | 0.101731 | 2.64984 | 9.58662 | 0.794226 | 0.00060913 | 0.00012764 | 8.26047e-05 | 1(Win) | true |
| Jsonifier | 1585.21 | 0.534081 | 1020.33ms | 4918 | 80 | 19976.1 | 2958.71 | 0.0621433 | 3.35313 | 8.98516 | 0.468686 | 0.000282127 | 3.05002e-05 | 2.28752e-05 | 2(Loss) | true |
| Glaze | 1280.71 | 0.0538979 | 1066.71ms | 4604 | 4890 | 16696.3 | 3428.34 | 0.0126049 | 4.08252 | 12.2183 | 0.967203 | 0.000540741 | 7.71535e-05 | 3.15365e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2626.8 | 0.0819936 | 1393.18ms | 18245 | 80 | 2359.85 | 6623.95 | 0.0742962 | 1.9733 | 7.95171 | 1.47794 | 0.00158331 | 3.22006e-05 | 1.50726e-05 | 1(Win) | true |
| simdjson (reflection) | 2419.14 | 0.0775479 | 1448.9ms | 18245 | 640 | 19910.6 | 7192.55 | 0.0341399 | 2.13938 | 7.94837 | 1.35961 | 0.00144235 | 3.33996e-05 | 1.27603e-05 | 2(Loss) | true |
| Jsonifier | 2355.77 | 0.0836792 | 1470.55ms | 18245 | 640 | 24447.5 | 7386.02 | 0.393862 | 2.21362 | 7.98833 | 1.79008 | 0.00202889 | 1.45588e-05 | 3.76816e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1847.24 | 0.0700214 | 1672.5ms | 18245 | 640 | 27840.8 | 9419.33 | 0.0347146 | 2.79601 | 10.278 | 1.90321 | 0.00186806 | 2.80042e-05 | 1.41306e-05 | 4(Loss) | true |
| Glaze | 1814.85 | 0.0767362 | 1685.59ms | 18245 | 320 | 17320.4 | 9587.46 | 0.0829823 | 2.84903 | 12.0814 | 2.37819 | 0.0037363 | 2.0211e-05 | 3.76816e-06 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3129.78 | 0.0962556 | 1388.97ms | 18245 | 30 | 859.082 | 5559.43 | 0.00539652 | 1.68931 | 6.89098 | 1.23683 | 0.00103042 | 2.74048e-05 | 3.65397e-06 | 1(Win) | true |
| Jsonifier | 2673.98 | 0.0442389 | 1471.57ms | 18245 | 2560 | 21213.9 | 6507.07 | 0.000816426 | 1.93612 | 6.93511 | 1.55089 | 0.00183177 | 2.91176e-05 | 1.22465e-05 | 2(Loss) | true |
| simdjson (reflection) | 2660.91 | 0.137273 | 1470.39ms | 18245 | 160 | 12891.9 | 6539.04 | 0.021883 | 1.94655 | 7.543 | 1.25547 | 0.000784119 | 1.74705e-05 | 2.05536e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2045.49 | 0.105133 | 1676.7ms | 18245 | 640 | 51185.4 | 8506.4 | 0.0122349 | 2.52696 | 9.40527 | 1.70275 | 0.0017879 | 2.31228e-05 | 7.62195e-06 | 4(Loss) | true |
| Glaze | 2016.2 | 0.027963 | 1675.59ms | 18245 | 4890 | 28477.4 | 8630.01 | 0.320889 | 2.56032 | 10.9605 | 2.12179 | 0.00343713 | 5.40249e-05 | 3.23701e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6974.52 | 0.10218 | 1062.88ms | 24893 | 4890 | 59152 | 3403.79 | 0.336516 | 0.747605 | 1.88061 | 0.0970153 | 4.47149e-05 | 2.39306e-05 | 1.26431e-05 | 1(Win) | true |
| Glaze | 3432.71 | 0.0800256 | 1410.17ms | 24579 | 4890 | 146023 | 6828.52 | 0.041441 | 1.51507 | 3.92176 | 0.474715 | 0.000199781 | 1.99432e-05 | 5.67429e-06 | 2(Loss) | true |
| simdjson (reflection) | 547.099 | 0.152849 | 5071.98ms | 24893 | 2560 | 1.12613e+07 | 43392.2 | 0.0640854 | 9.38049 | 35.6264 | 5.71968 | 0.00697063 | 0.000133195 | 7.89943e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7055.66 | 0.359604 | 1055.67ms | 24893 | 320 | 46846.7 | 3364.65 | 0.0678465 | 0.737544 | 1.86125 | 0.0925162 | 5.5613e-05 | 1.48134e-05 | 8.91315e-06 | 1(Win) | true |
| Glaze | 3700.31 | 0.346537 | 1362.53ms | 24579 | 320 | 154206 | 6334.7 | 0.326589 | 1.41002 | 3.77273 | 0.441597 | 0.000230888 | 2.28854e-05 | 1.57655e-05 | 2(Loss) | true |
| simdjson (reflection) | 546.288 | 0.115372 | 5071.43ms | 24893 | 4890 | 1.2292e+07 | 43456.6 | 0.175801 | 9.38702 | 35.6292 | 5.72043 | 0.00798123 | 0.000151996 | 0.000109573 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 928.365 | 0.0509036 | 1197.25ms | 4604 | 2560 | 14837.8 | 4729.51 | 0.0860864 | 5.53639 | 23.5416 | 5.14021 | 0.00383787 | 8.70507e-05 | 3.80104e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 775.591 | 0.0988806 | 1289.94ms | 4604 | 40 | 1253.39 | 5661.12 | 0.117163 | 6.68816 | 28.4554 | 5.70004 | 0.00585361 | 5.43006e-05 | 4.34405e-05 | 2(Loss) | true |
| Glaze | 641.071 | 0.0313682 | 1409.45ms | 4604 | 4890 | 22570.8 | 6849.04 | 0.0351508 | 7.98208 | 33.3914 | 6.83254 | 0.00447366 | 9.0079e-05 | 3.03817e-05 | 3(Loss) | true |
| simdjson (reflection) | 636.226 | 0.0752117 | 1414.41ms | 4604 | 160 | 4310.61 | 6901.19 | 0.315883 | 8.00737 | 29.6026 | 5.72502 | 0.00422323 | 4.34405e-05 | 8.14509e-06 | 4(Loss) | true |
| simdjson (ondemand) | 506.684 | 0.13151 | 1605.59ms | 4604 | 40 | 5194.86 | 8665.6 | 0.011926 | 10.2151 | 36.9317 | 7.46079 | 0.00703193 | 0.000173762 | 0.000103171 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1147.32 | 0.152077 | 1195.82ms | 4604 | 40 | 1354.84 | 3826.93 | 0.228772 | 4.54764 | 19.4788 | 4.20708 | 0.00329062 | 5.43006e-05 | 5.43006e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 912.983 | 0.0398589 | 1292.44ms | 4604 | 4890 | 17968.2 | 4809.2 | 0.129373 | 5.67776 | 24.424 | 4.77467 | 0.00473075 | 9.26997e-05 | 3.06482e-05 | 2(Loss) | true |
| Glaze | 736.39 | 0.0296272 | 1409.64ms | 4604 | 4890 | 15259.7 | 5962.49 | 0.0719514 | 7.01855 | 29.1183 | 5.84894 | 0.00655911 | 7.44884e-05 | 3.03817e-05 | 3(Loss) | true |
| simdjson (reflection) | 730.536 | 0.0517165 | 1425.99ms | 4604 | 2560 | 24733.6 | 6010.27 | 0.00632421 | 7.048 | 26.2007 | 4.95129 | 0.00425547 | 9.70623e-05 | 3.63135e-05 | 4(Loss) | true |
| simdjson (ondemand) | 541.251 | 0.0907301 | 1655.79ms | 4604 | 320 | 17335.1 | 8112.17 | 0.0255854 | 9.561 | 33.1077 | 6.60541 | 0.0145804 | 0.00010928 | 4.54768e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1919.66 | 0.0737447 | 964.36ms | 4918 | 4890 | 15874.5 | 2443.23 | 0.0832177 | 2.71742 | 9.67629 | 0.818829 | 0.000548713 | 8.66563e-05 | 3.67998e-05 | 1(Win) | true |
| Jsonifier | 1436.25 | 0.167551 | 1048.06ms | 4918 | 2560 | 76639 | 3265.56 | 0.10962 | 3.62847 | 9.11001 | 0.492274 | 0.00044265 | 7.79185e-05 | 3.7331e-05 | 2(Loss) | true |
| Glaze | 1227.04 | 0.141389 | 1084.87ms | 4604 | 320 | 8190.92 | 3578.3 | 0.0518147 | 4.24211 | 12.7118 | 1.08384 | 0.000659074 | 2.71503e-05 | 0 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1951.41 | 0.402792 | 960.616ms | 4918 | 40 | 3748.87 | 2403.47 | 0.0364189 | 2.68358 | 9.57361 | 0.795039 | 0.000640504 | 4.57503e-05 | 2.54168e-05 | 1(Win) | true |
| Jsonifier | 1456.03 | 0.170993 | 1043.02ms | 4918 | 2560 | 77667 | 3221.21 | 0.383527 | 3.59921 | 9.00427 | 0.467874 | 0.000493722 | 4.71006e-05 | 1.52501e-05 | 2(Loss) | true |
| Glaze | 1313.04 | 0.0499796 | 1056.04ms | 4604 | 4890 | 13658.6 | 3343.92 | 0.260921 | 3.97139 | 12.2024 | 0.96829 | 0.000870364 | 0.000120727 | 7.1246e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2734.93 | 0.0637123 | 1361.08ms | 18245 | 1280 | 21030.6 | 6362.05 | 0.0758564 | 1.89543 | 7.80126 | 1.43437 | 0.00111961 | 1.86267e-05 | 7.87887e-06 | 1(Win) | true |
| Jsonifier | 2515.05 | 0.0284537 | 1418.1ms | 18245 | 4890 | 18948.8 | 6918.27 | 0.03393 | 2.05543 | 7.8325 | 1.73872 | 0.00178075 | 2.50174e-05 | 1.21724e-05 | 2(Loss) | true |
| simdjson (reflection) | 2373.24 | 0.0296696 | 1459.6ms | 18245 | 4890 | 23138.5 | 7331.65 | 0.383011 | 2.17885 | 8.04527 | 1.38487 | 0.00151504 | 4.36123e-05 | 2.61494e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1881.75 | 0.0822189 | 1650.18ms | 18245 | 320 | 18495.1 | 9246.6 | 0.066183 | 2.74725 | 9.92859 | 1.82554 | 0.00208036 | 7.99877e-05 | 4.5903e-05 | 4(Loss) | true |
| Glaze | 1859.94 | 0.0572981 | 1662.57ms | 18245 | 320 | 9194.32 | 9355.02 | 0.0659971 | 2.78075 | 11.8215 | 2.31943 | 0.00355388 | 1.07906e-05 | 2.39792e-06 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3200.73 | 0.0485185 | 1355.59ms | 18245 | 2560 | 17809.2 | 5436.19 | 0.0854959 | 1.62443 | 6.74547 | 1.19496 | 0.000876524 | 5.57302e-05 | 3.11943e-05 | 1(Win) | true |
| Jsonifier | 2904.43 | 0.0842402 | 1416.21ms | 18245 | 40 | 1018.74 | 5990.77 | 0.114351 | 1.78636 | 6.77599 | 1.49888 | 0.00166484 | 2.05536e-05 | 9.59167e-06 | 2(Loss) | true |
| simdjson (reflection) | 2671.08 | 0.0461632 | 1473.71ms | 18245 | 2560 | 23149.6 | 6514.13 | 0.0332681 | 1.93995 | 7.54549 | 1.26207 | 0.000883033 | 4.41474e-05 | 2.18382e-05 | 3(Loss) | true |
| Glaze | 2049 | 0.0394561 | 1656.15ms | 18245 | 2560 | 28739 | 8491.84 | 0.131733 | 2.52397 | 10.802 | 2.08742 | 0.00337269 | 2.34653e-05 | 8.75668e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2038.65 | 0.065611 | 1685.56ms | 18245 | 1280 | 40139 | 8534.96 | 0.00474175 | 2.52567 | 9.53555 | 1.72937 | 0.00183338 | 2.82612e-05 | 8.86373e-06 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6490.12 | 0.360579 | 1086.43ms | 24893 | 320 | 55667.2 | 3657.84 | 0.175597 | 0.815318 | 1.87856 | 0.0964131 | 8.34823e-05 | 1.02941e-05 | 3.76612e-07 | 1(Win) | true |
| Glaze | 3690.74 | 0.196749 | 1358.58ms | 24579 | 640 | 99932 | 6351.12 | 0.0911654 | 1.42264 | 3.90553 | 0.474715 | 0.000307808 | 1.83719e-05 | 5.14921e-06 | 2(Loss) | true |
| simdjson (reflection) | 559.818 | 0.216743 | 4955.61ms | 24893 | 1280 | 1.08133e+07 | 42406.3 | 0.0555107 | 9.09244 | 35.6404 | 5.72675 | 0.00758004 | 6.87003e-05 | 3.99522e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6538.05 | 0.128087 | 1084.29ms | 24893 | 2560 | 55374.3 | 3631.02 | 0.270614 | 0.801925 | 1.8592 | 0.0919136 | 6.07757e-05 | 1.18319e-05 | 3.57781e-06 | 1(Win) | true |
| Glaze | 3904.29 | 0.0676596 | 1324.03ms | 24579 | 4890 | 80688.6 | 6003.74 | 0.138403 | 1.3362 | 3.76179 | 0.442166 | 0.000353012 | 1.30375e-05 | 4.25988e-06 | 2(Loss) | true |
| simdjson (reflection) | 558.5 | 0.324788 | 4969.96ms | 24893 | 640 | 1.2198e+07 | 42506.4 | 0.298272 | 9.20721 | 35.6502 | 5.72995 | 0.00903385 | 8.45494e-05 | 4.86457e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2110.44 | 0.0425238 | 947.1ms | 5094 | 4890 | 4685.41 | 2301.9 | 0.272489 | 2.47908 | 11.247 | 2.00039 | 0.00161295 | 0.000113691 | 6.24657e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1477.89 | 0.0870462 | 1048.7ms | 5094 | 80 | 654.972 | 3287.12 | 0.0251042 | 3.52879 | 16.2788 | 2.63585 | 0.00233608 | 3.43541e-05 | 2.45387e-06 | 2(Loss) | true |
| simdjson (reflection) | 1297.31 | 0.0517847 | 1106.4ms | 5094 | 2560 | 9626.62 | 3744.69 | 0.141115 | 3.99198 | 15.7892 | 2.56145 | 0.00322231 | 0.00013642 | 6.8785e-05 | 3(Loss) | true |
| Glaze | 1269.73 | 0.215279 | 1110.85ms | 5094 | 160 | 10854.8 | 3826.03 | 0.0102903 | 4.16775 | 17.4827 | 3.33118 | 0.00498626 | 5.03043e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1077.7 | 0.0632651 | 1185.57ms | 5094 | 160 | 1301.29 | 4507.78 | 0.094331 | 4.82336 | 17.3153 | 2.8938 | 0.00462922 | 6.25736e-05 | 2.33117e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2783.08 | 0.0901359 | 948.159ms | 5094 | 320 | 792.16 | 1745.56 | 0.0849304 | 1.89541 | 8.78426 | 1.44327 | 0.00133122 | 3.92619e-05 | 1.28828e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1794.02 | 0.0718792 | 1046.75ms | 5094 | 1280 | 4849.31 | 2707.89 | 0.0460536 | 2.91411 | 13.8153 | 2.07852 | 0.00216922 | 3.3894e-05 | 4.29427e-06 | 2(Loss) | true |
| Glaze | 1593.06 | 0.133017 | 1082.27ms | 5094 | 320 | 5265.27 | 3049.49 | 0.103095 | 3.27513 | 14.2952 | 2.62898 | 0.00484639 | 3.98753e-05 | 1.16559e-05 | 3(Loss) | true |
| simdjson (reflection) | 1470.19 | 0.119725 | 1122.87ms | 5094 | 80 | 1252.07 | 3304.34 | 0.212525 | 3.54902 | 14.9056 | 2.33608 | 0.00172752 | 4.41696e-05 | 2.45387e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1318.44 | 0.0616721 | 1152.81ms | 5094 | 1280 | 6609.72 | 3684.66 | 0.29088 | 3.94364 | 14.6853 | 2.31508 | 0.003715 | 6.71746e-05 | 2.62257e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12636 | 0.0939607 | 755.789ms | 5094 | 1280 | 167.034 | 384.459 | 0.292977 | 0.45013 | 1.71928 | 0.228897 | 0.000196309 | 3.88018e-05 | 9.50874e-06 | 1(Win) | true |
| simdjson (reflection) | 8379.22 | 0.177434 | 776.412ms | 5094 | 4890 | 5174.82 | 579.77 | 0.0849011 | 0.663299 | 2.40616 | 0.34413 | 0.000196631 | 6.87685e-05 | 3.31197e-05 | 2(Loss) | true |
| Glaze | 4276.52 | 0.0991602 | 835.989ms | 5094 | 4890 | 6204.69 | 1135.97 | 0.0822399 | 1.24974 | 5.14978 | 0.826659 | 0.000197313 | 7.46698e-05 | 2.10762e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14938.5 | 0.259661 | 746.426ms | 5094 | 2560 | 1825.39 | 325.201 | 0.164291 | 0.388558 | 1.60444 | 0.202788 | 0.000196923 | 2.64558e-05 | 8.20512e-06 | 1(Win) | true |
| simdjson (reflection) | 9353.88 | 0.054841 | 765.713ms | 5094 | 4890 | 396.692 | 519.358 | 0.130379 | 0.592903 | 2.29054 | 0.318218 | 0.00019639 | 5.7568e-05 | 2.51308e-05 | 2(Loss) | true |
| Glaze | 5152.93 | 0.0688599 | 814.74ms | 5094 | 1280 | 539.45 | 942.767 | 0.219283 | 1.04081 | 4.69925 | 0.724382 | 0.000196616 | 3.46609e-05 | 1.33429e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2741.31 | 0.0670621 | 1002.39ms | 8051 | 2560 | 9031.88 | 2800.86 | 0.155383 | 1.90512 | 8.44454 | 1.52851 | 0.00189655 | 4.83247e-05 | 2.3095e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2214.39 | 0.0833101 | 1066.56ms | 8051 | 160 | 1335.08 | 3467.34 | 0.111992 | 2.35397 | 10.9986 | 1.72364 | 0.00121802 | 6.52093e-05 | 2.71705e-05 | 2(Loss) | true |
| simdjson (reflection) | 1962.39 | 0.049641 | 1117.66ms | 8051 | 4890 | 18446.6 | 3912.58 | 0.0258911 | 2.64359 | 10.4943 | 1.63769 | 0.00216915 | 8.33897e-05 | 5.02421e-05 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1650.3 | 0.060889 | 1191.87ms | 8051 | 2560 | 20544.4 | 4652.51 | 0.120229 | 3.13617 | 11.487 | 1.85344 | 0.00289585 | 4.36184e-05 | 1.72727e-05 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1649.53 | 0.145534 | 1199.6ms | 8051 | 320 | 14684.5 | 4654.68 | 0.0721871 | 3.2017 | 13.4874 | 2.59061 | 0.00343668 | 6.17159e-05 | 2.01838e-05 | 4(Tie) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3482.68 | 0.0523833 | 996.131ms | 8051 | 4890 | 6521.82 | 2204.64 | 0.0227436 | 1.50685 | 6.87269 | 1.17327 | 0.00176744 | 3.09377e-05 | 1.1227e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2668.3 | 0.059309 | 1063.86ms | 8051 | 2560 | 7456.08 | 2877.5 | 0.195034 | 1.96137 | 9.43995 | 1.37101 | 0.00108114 | 2.75102e-05 | 8.10264e-06 | 2(Loss) | true |
| simdjson (reflection) | 2223.04 | 0.0600445 | 1134.18ms | 8051 | 2560 | 11010.1 | 3453.85 | 0.00221678 | 2.33442 | 10.0011 | 1.50851 | 0.000908515 | 2.56665e-05 | 6.84115e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2015.65 | 0.0441965 | 1160.44ms | 8051 | 4890 | 13859.7 | 3809.2 | 0.00960297 | 2.57754 | 9.72525 | 1.46752 | 0.00243235 | 2.34446e-05 | 5.7405e-06 | 4(Loss) | true |
| Glaze | 1996.89 | 0.0516837 | 1165.92ms | 8051 | 4890 | 19311 | 3844.99 | 0.204927 | 2.60801 | 11.4704 | 2.14632 | 0.00301 | 3.87103e-05 | 1.53419e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20939.3 | 0.109847 | 760.991ms | 9255 | 640 | 137.211 | 421.517 | 0.914928 | 0.272698 | 0.991464 | 0.125122 | 0.000108219 | 2.12723e-05 | 3.37655e-06 | 1(Win) | true |
| Glaze | 4591.59 | 0.080335 | 916.391ms | 9255 | 2560 | 6104.86 | 1922.26 | 0.240998 | 1.15363 | 4.8228 | 0.815451 | 0.000110413 | 3.83661e-05 | 7.68166e-06 | 2(Loss) | true |
| simdjson (reflection) | 531.062 | 0.134711 | 2401.18ms | 9255 | 2560 | 1.28325e+06 | 16620 | 0.036434 | 9.65563 | 38.078 | 7.2845 | 0.015656 | 0.000108007 | 5.63462e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23754.8 | 0.19684 | 752.174ms | 9255 | 320 | 171.169 | 371.556 | 0.500397 | 0.239636 | 0.932793 | 0.111615 | 0.00010805 | 1.65451e-05 | 4.05186e-06 | 1(Win) | true |
| Glaze | 5488.26 | 0.0734701 | 882.604ms | 9255 | 4890 | 6826.75 | 1608.21 | 0.178067 | 0.959228 | 4.47315 | 0.737007 | 0.000177696 | 2.2781e-05 | 5.72288e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.738 | 0.26507 | 2399.86ms | 9255 | 640 | 1.25306e+06 | 16693.1 | 0.204736 | 9.65574 | 38.0755 | 7.28344 | 0.016546 | 6.98947e-05 | 3.61291e-05 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5883.65 | 0.36035 | 759.377ms | 2889 | 40 | 113.897 | 468.275 | 0.16168 | 0.964148 | 3.79889 | 0.529941 | 0.000346141 | 0 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 5764.75 | 0.430598 | 761.962ms | 2889 | 4890 | 20710.4 | 477.933 | 0.114829 | 0.973487 | 3.79889 | 0.529941 | 0.000347485 | 3.64545e-05 | 7.50325e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5625.26 | 0.0486892 | 760.571ms | 2889 | 2560 | 145.585 | 489.784 | 0.369171 | 1.00988 | 3.89789 | 0.417792 | 0.000376969 | 4.96225e-05 | 1.32507e-05 | 3(Loss) | true |
| simdjson (reflection) | 5384.36 | 0.118848 | 762.895ms | 2889 | 2560 | 946.779 | 511.698 | 0.0195466 | 1.03184 | 3.87643 | 0.42333 | 0.000370073 | 4.32676e-05 | 1.62253e-05 | 4(Loss) | true |
| Glaze | 3140.97 | 0.0760093 | 801.156ms | 2889 | 4890 | 2173.75 | 877.169 | 0.0977889 | 1.721 | 7.24922 | 1.24264 | 0.000348476 | 1.43694e-05 | 4.31791e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6253.68 | 0.261344 | 760.829ms | 2889 | 30 | 39.7713 | 440.567 | 0.00756544 | 0.915334 | 3.66113 | 0.49775 | 0.000357679 | 2.3076e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 6189.82 | 0.148788 | 758.601ms | 2889 | 80 | 35.0884 | 445.113 | 0.109403 | 0.90752 | 3.66113 | 0.49775 | 0.000346141 | 2.59605e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 5709.11 | 0.0895986 | 763.697ms | 2889 | 320 | 59.8288 | 482.591 | 0.399231 | 0.977705 | 3.82381 | 0.400831 | 0.000376428 | 2.27155e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 5612.36 | 0.0762822 | 764.14ms | 2889 | 1280 | 179.499 | 490.91 | 0.708699 | 0.99892 | 3.81343 | 0.407061 | 0.000356957 | 3.92112e-05 | 5.94929e-06 | 4(Loss) | true |
| Glaze | 3183.97 | 0.152291 | 796.67ms | 2889 | 80 | 138.931 | 865.325 | 0.0925364 | 1.69798 | 7.17965 | 1.22603 | 0.000346141 | 2.59605e-05 | 1.29803e-05 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6798.86 | 0.0800949 | 769.146ms | 3808 | 1280 | 234.283 | 534.147 | 0.0178407 | 0.8163 | 3.2416 | 0.40021 | 0.000263015 | 1.78489e-05 | 4.92384e-06 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 6742.21 | 0.0913501 | 770.556ms | 3808 | 2560 | 619.794 | 538.635 | 0.141217 | 0.827369 | 3.30882 | 0.332458 | 0.000302406 | 9.95027e-06 | 2.97482e-06 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6719.79 | 0.23351 | 770.061ms | 3808 | 1280 | 2038.46 | 540.432 | 0.0160488 | 0.82322 | 3.2416 | 0.40021 | 0.000263426 | 2.1747e-05 | 5.94965e-06 | 2(Tie) | true |
| simdjson (reflection) | 6625.44 | 0.0678806 | 769.894ms | 3808 | 320 | 44.3001 | 548.128 | 0.0894291 | 0.834975 | 3.29254 | 0.33666 | 0.000273273 | 1.55922e-05 | 5.74449e-06 | 4(Loss) | true |
| Glaze | 3563.78 | 0.0571021 | 815.349ms | 3808 | 4890 | 1655.71 | 1019.03 | 0.148386 | 1.50845 | 6.58508 | 1.20746 | 0.000264538 | 9.77385e-06 | 3.54436e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7033.41 | 0.320649 | 770.127ms | 3808 | 1280 | 3508.58 | 516.334 | 0.129383 | 0.790391 | 3.19039 | 0.387868 | 0.000266093 | 2.87224e-05 | 3.48772e-06 | 1(Win) | true |
| Jsonifier | 6974.65 | 0.220728 | 768.045ms | 3808 | 320 | 422.681 | 520.684 | 0.116897 | 0.797175 | 3.19039 | 0.387868 | 0.000262605 | 5.17004e-05 | 2.21573e-05 | 2(Loss) | true |
| simdjson (ondemand) | 6929.92 | 0.0554125 | 766.346ms | 3808 | 1280 | 107.935 | 524.045 | 0.101179 | 0.800377 | 3.25263 | 0.31959 | 0.00029502 | 1.37457e-05 | 2.25676e-06 | 3(Loss) | true |
| simdjson (reflection) | 6780.58 | 0.15876 | 772.172ms | 3808 | 80 | 57.8403 | 535.587 | 0.109572 | 0.814447 | 3.24475 | 0.324317 | 0.000279018 | 3.61082e-05 | 6.56513e-06 | 4(Loss) | true |
| Glaze | 3564.53 | 0.104783 | 817.82ms | 3808 | 2560 | 2917.52 | 1018.81 | 0.224068 | 1.49749 | 6.53151 | 1.19433 | 0.000264554 | 3.23127e-05 | 1.41561e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3199.31 | 0.138627 | 808.411ms | 2889 | 160 | 228.032 | 861.175 | 0.211472 | 1.68615 | 5.34199 | 0.917272 | 0.000346141 | 6.92281e-05 | 4.32676e-06 | 1(Win) | true |
| Glaze | 2397.93 | 0.126579 | 835.449ms | 2889 | 80 | 169.215 | 1148.97 | 0.0021759 | 2.22255 | 8.91035 | 1.55625 | 0.000346141 | 8.65351e-06 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 2227.94 | 0.0699597 | 844.16ms | 2889 | 4890 | 3660.08 | 1236.64 | 0.353528 | 2.38109 | 8.27968 | 1.22984 | 0.000350529 | 5.03992e-05 | 9.2021e-06 | 3(Loss) | true |
| simdjson (reflection) | 1901.61 | 0.113407 | 870.397ms | 2889 | 2560 | 6911.42 | 1448.86 | 0.0095181 | 2.77372 | 9.23365 | 1.30357 | 0.00040685 | 6.39549e-05 | 1.35211e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1382.85 | 0.067594 | 922.461ms | 2889 | 1280 | 2321.53 | 1992.39 | 0.165591 | 3.79847 | 12.0654 | 2.39772 | 0.000658749 | 3.86704e-05 | 1.62253e-06 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3641.18 | 0.0419991 | 804.163ms | 2889 | 1280 | 129.271 | 756.669 | 0.213768 | 1.49099 | 4.75839 | 0.766701 | 0.000346141 | 4.73239e-05 | 5.67887e-06 | 1(Win) | true |
| Glaze | 2621.25 | 0.047989 | 831.267ms | 2889 | 2560 | 651.332 | 1051.09 | 0.0562233 | 2.04032 | 8.32399 | 1.40222 | 0.000347087 | 5.09746e-05 | 1.09521e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2494.41 | 0.0618326 | 836.16ms | 2889 | 4890 | 2280.89 | 1104.54 | 0.00881217 | 2.13343 | 7.69263 | 1.07684 | 0.000349963 | 5.42924e-05 | 1.21751e-05 | 3(Loss) | true |
| simdjson (reflection) | 2109.23 | 0.069252 | 858.082ms | 2889 | 4890 | 4001.48 | 1306.24 | 0.158425 | 2.51603 | 8.67047 | 1.15888 | 0.000351237 | 5.40092e-05 | 1.28122e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1421.99 | 0.103932 | 925.889ms | 2889 | 1280 | 5190.52 | 1937.54 | 0.221412 | 3.68499 | 11.6314 | 2.28557 | 0.00128856 | 4.75943e-05 | 7.3014e-06 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8556.79 | 0.462259 | 750.08ms | 2963 | 30 | 69.9092 | 330.233 | 0.12098 | 0.683643 | 1.57746 | 0.229497 | 0.000337496 | 2.24997e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7208.47 | 0.208867 | 759.881ms | 2963 | 1280 | 858.082 | 392.002 | 0.135537 | 0.785744 | 1.7948 | 0.270672 | 0.000337759 | 4.90424e-05 | 8.43739e-06 | 2(Loss) | true |
| Glaze | 5654.58 | 0.54365 | 767.453ms | 2963 | 40 | 295.23 | 499.725 | 0.134892 | 0.984568 | 2.99224 | 0.462707 | 0.000345933 | 7.59366e-05 | 2.53122e-05 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9904.01 | 0.306188 | 746.417ms | 2963 | 80 | 61.053 | 285.312 | 0.570657 | 0.592664 | 1.42558 | 0.19406 | 0.000337496 | 3.37496e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 8007.03 | 0.0473298 | 754.688ms | 2963 | 2560 | 71.4216 | 352.907 | 0.35383 | 0.724181 | 1.68579 | 0.244347 | 0.000337759 | 5.18109e-05 | 1.8325e-05 | 2(Loss) | true |
| Glaze | 6619.54 | 0.245123 | 756.966ms | 2963 | 640 | 700.736 | 426.878 | 0.0366164 | 0.851969 | 2.53156 | 0.36517 | 0.000337496 | 3.74409e-05 | 1.63475e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3269.77 | 0.0537505 | 832.293ms | 3808 | 320 | 114.044 | 1110.66 | 0.357179 | 1.63597 | 4.96035 | 0.868435 | 0.000262605 | 3.2005e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2786.16 | 0.0954168 | 850.492ms | 3808 | 80 | 123.743 | 1303.44 | 0.214316 | 1.90615 | 6.77285 | 0.967437 | 0.000262605 | 0.000105042 | 3.28256e-05 | 2(Loss) | true |
| simdjson (reflection) | 2472.67 | 0.0604862 | 866.683ms | 3808 | 4890 | 3859.07 | 1468.69 | 0.120232 | 2.13725 | 7.35688 | 1.00446 | 0.000266901 | 4.70434e-05 | 1.28886e-05 | 3(Loss) | true |
| Glaze | 2404.79 | 0.0689668 | 871.033ms | 3808 | 320 | 347.112 | 1510.15 | 0.0260668 | 2.20029 | 8.42174 | 1.5239 | 0.000264246 | 4.02114e-05 | 1.06683e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1789.78 | 0.050296 | 923.442ms | 3808 | 4890 | 5092.98 | 2029.08 | 0.115752 | 2.93431 | 9.50525 | 1.83456 | 0.000494385 | 5.32191e-05 | 1.0472e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3722.73 | 0.037873 | 823.073ms | 3808 | 320 | 43.6799 | 975.519 | 0.143077 | 1.44492 | 4.51602 | 0.754202 | 0.000262605 | 3.69288e-05 | 8.20641e-07 | 1(Win) | true |
| Jsonifier (two-stage) | 3146.86 | 0.0950382 | 838.67ms | 3808 | 2560 | 3079.47 | 1154.04 | 0.0350117 | 1.71005 | 6.32747 | 0.851366 | 0.000264759 | 6.2061e-05 | 1.87722e-05 | 2(Loss) | true |
| simdjson (reflection) | 2703.65 | 0.110898 | 864.94ms | 3808 | 1280 | 2840.21 | 1343.22 | 0.328987 | 1.96897 | 6.92805 | 0.89417 | 0.000268965 | 4.67765e-05 | 1.23096e-05 | 3(Loss) | true |
| Glaze | 2598.34 | 0.0571465 | 862.607ms | 3808 | 4890 | 3119.54 | 1397.66 | 0.00883861 | 2.05012 | 7.97637 | 1.4073 | 0.000265129 | 3.97935e-05 | 6.17578e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1864.07 | 0.0857809 | 920.027ms | 3808 | 2560 | 7149.75 | 1948.21 | 0.0984712 | 2.82301 | 9.17595 | 1.74948 | 0.000761042 | 5.66242e-05 | 1.41561e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12106.6 | 0.257845 | 752.267ms | 4300 | 40 | 30.5122 | 338.725 | 0.125628 | 0.475174 | 1.13442 | 0.159302 | 0.000232558 | 2.32558e-05 | 0 | 1(Win) | true |
| Glaze | 3567.32 | 0.227259 | 839.242ms | 4300 | 4890 | 33373.7 | 1149.55 | 0.0550931 | 1.50157 | 3.5886 | 0.603954 | 0.00062453 | 6.43458e-05 | 1.73111e-05 | 2(Loss) | true |
| simdjson (reflection) | 556.547 | 0.0749777 | 1469.88ms | 4300 | 4890 | 149248 | 7368.3 | 0.108556 | 9.29244 | 33.594 | 7.42861 | 0.00898954 | 0.000141057 | 5.0887e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14085.4 | 0.131989 | 745.845ms | 4300 | 640 | 94.5049 | 291.139 | 0.504331 | 0.416028 | 1.02674 | 0.133721 | 0.000232922 | 4.36047e-05 | 1.70785e-05 | 1(Win) | true |
| Glaze | 4436.82 | 0.397931 | 812.335ms | 4300 | 2560 | 34629.7 | 924.266 | 0.591547 | 1.21382 | 3.03163 | 0.47721 | 0.00023492 | 4.95094e-05 | 1.40807e-05 | 2(Loss) | true |
| simdjson (reflection) | 561.862 | 0.102007 | 1459.91ms | 4300 | 2560 | 141898 | 7298.59 | 0.393232 | 9.25553 | 33.5984 | 7.42861 | 0.00926517 | 9.22057e-05 | 3.50654e-05 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10348.9 | 0.0166304 | 5042.43ms | 466906 | 4890 | 250374 | 43026.6 | 0.0829271 | 0.496587 | 1.97404 | 0.0757841 | 3.12206e-05 | 0.000251048 | 7.00342e-06 | 1(Win) | true |
| simdjson (ondemand) | 9319.99 | 0.0222453 | 5523.7ms | 466906 | 2560 | 289166 | 47776.5 | 0.0822562 | 0.552007 | 2.07166 | 0.0435849 | 7.97688e-05 | 0.000750839 | 7.15147e-06 | 2(Loss) | true |
| Glaze | 2533.27 | 0.0982041 | 9397.71ms | 466906 | 40 | 1.19184e+06 | 175772 | 0.0154011 | 2.0315 | 8.75451 | 1.96144 | 0.0025549 | 0.00101584 | 3.06271e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10329.2 | 0.0695027 | 5034.83ms | 466906 | 2560 | 2.2981e+06 | 43108.5 | 0.113268 | 0.496037 | 1.97287 | 0.0755185 | 3.08187e-05 | 0.000162155 | 6.9398e-06 | 1(Win) | true |
| simdjson (ondemand) | 9371.36 | 0.0343271 | 5497.34ms | 466906 | 320 | 85128.9 | 47514.6 | 0.0824265 | 0.549907 | 2.07055 | 0.0433279 | 8.24376e-05 | 0.00153828 | 7.73041e-06 | 2(Loss) | true |
| Glaze | 2535.42 | 0.0448887 | 9383.41ms | 466906 | 640 | 3.97754e+06 | 175622 | 0.0601417 | 2.02447 | 8.75336 | 1.96118 | 0.00248127 | 0.000993876 | 2.96199e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4223.16 | 0.0428687 | 8448.08ms | 699405 | 2560 | 1.17356e+07 | 157940 | 0.193511 | 1.21044 | 4.75893 | 1.21772 | 0.00329968 | 0.000229677 | 9.86665e-06 | 1(Win) | true |
| Glaze | 3204.02 | 0.0316074 | 5486.63ms | 699405 | 1280 | 5.54187e+06 | 208178 | 0.531906 | 1.59784 | 6.28759 | 1.35582 | 0.0020429 | 0.000764864 | 1.61041e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2460.78 | 0.156993 | 7764.73ms | 767297 | 320 | 6.97423e+07 | 297366 | 0.320577 | 2.04952 | 8.02247 | 1.07878 | 0.00380306 | 0.101752 | 0.000122243 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4244.99 | 0.0861324 | 8477.51ms | 699405 | 640 | 1.17225e+07 | 157128 | 0.0174968 | 1.21013 | 4.75843 | 1.21762 | 0.00323032 | 0.000186096 | 1.38377e-05 | 1(Win) | true |
| Glaze | 3225.28 | 0.123749 | 5506.65ms | 699405 | 40 | 2.61978e+06 | 206805 | 0.0117637 | 1.5958 | 6.28688 | 1.35566 | 0.00206111 | 0.000747314 | 1.0366e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2489.83 | 0.136309 | 7731.52ms | 767297 | 640 | 1.02712e+08 | 293896 | 0.114914 | 2.03623 | 8.02298 | 1.07893 | 0.00367333 | 0.0951542 | 0.000158305 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2682.43 | 0.0973561 | 5924.3ms | 631514 | 640 | 3.05785e+07 | 224520 | 0.195508 | 1.89721 | 8.33046 | 1.35779 | 0.010128 | 3.07149e-05 | 2.31908e-05 | 1(Win) | true |
| Glaze | 2162.92 | 0.0862106 | 7310.15ms | 631514 | 640 | 3.68796e+07 | 278447 | 0.0712224 | 2.34368 | 9.80794 | 1.64391 | 0.00988455 | 2.27479e-05 | 2.12386e-05 | 2(Loss) | true |
