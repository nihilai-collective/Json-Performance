# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

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
* **simdjson (reflection):** Not in this run, since this toolchain does not support P2996 static reflection yet.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2006.63 | 0.22644 | 759.204ms | 905 | 2560 | 2428.33 | 430.112 | 0.229608 | 2.80967 | 13.5039 | 2.2895 | 0.0011313 | 0.000220563 | 6.21547e-05 | 1(Win) | true |
| Glaze | 1505.58 | 0.20787 | 771.855ms | 905 | 320 | 454.382 | 573.25 | 0.0479491 | 3.66205 | 17.5934 | 2.2895 | 0.00113605 | 5.52486e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 479.878 | 0.121305 | 897.136ms | 905 | 1280 | 6092.66 | 1798.53 | 0.157216 | 10.9716 | 50.5039 | 9.81437 | 0.0478332 | 0.000175242 | 2.07182e-05 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2203.61 | 0.209573 | 751.781ms | 905 | 2560 | 1724.81 | 391.665 | 0.0420703 | 2.5935 | 12.842 | 2.17127 | 0.00112785 | 0.000163588 | 4.57528e-05 | 1(Win) | true |
| Glaze | 1560.15 | 0.0923867 | 770.872ms | 905 | 4890 | 1277.3 | 553.2 | 0.164222 | 3.53072 | 16.9249 | 2.17127 | 0.00111379 | 8.15736e-05 | 1.19762e-05 | 2(Loss) | true |
| simdjson (ondemand) | 488.503 | 0.109476 | 893.014ms | 905 | 2560 | 9577.17 | 1766.78 | 0.0781181 | 10.7784 | 49.8851 | 9.69614 | 0.0496102 | 0.000199845 | 3.02141e-05 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2298.73 | 0.261239 | 751.766ms | 905 | 1280 | 1231.42 | 375.457 | 1.0971 | 2.48181 | 9.3105 | 0.950277 | 0.00335808 | 7.07873e-05 | 3.45304e-06 | 1(Win) | true |
| Glaze | 222.889 | 0.0569994 | 1107.79ms | 905 | 4890 | 23821.6 | 3872.22 | 0.0509282 | 23.2275 | 112.869 | 22.9381 | 0.0754771 | 0.000354766 | 0.000154109 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4587.93 | 0.537821 | 739.841ms | 905 | 320 | 327.56 | 188.119 | 0.301424 | 1.38295 | 5.79779 | 0.272928 | 0.00223412 | 2.41713e-05 | 0 | 1(Win) | true |
| Glaze | 973.16 | 0.116736 | 832.621ms | 905 | 4890 | 5241.4 | 886.879 | 0.27733 | 5.54028 | 24.0597 | 3.14917 | 0.00129637 | 0.00010756 | 2.75678e-05 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1205.46 | 0.16658 | 885.204ms | 1811 | 1280 | 7291.04 | 1432.74 | 0.0109069 | 4.37687 | 20.3048 | 4.17559 | 0.000591869 | 0.000127692 | 2.37265e-05 | 1(Win) | true |
| Glaze | 853.709 | 0.0763092 | 924.483ms | 1811 | 4890 | 11654.1 | 2023.06 | 0.00420417 | 6.13898 | 30.1342 | 4.70735 | 0.000581879 | 0.000141376 | 4.01997e-05 | 2(Loss) | true |
| simdjson (ondemand) | 441.799 | 0.0651421 | 1116.94ms | 1811 | 4890 | 31711.7 | 3909.25 | 0.202643 | 11.7273 | 59.3617 | 11.466 | 0.00160505 | 0.000150297 | 3.95222e-05 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1341.02 | 0.205218 | 845.554ms | 1811 | 320 | 2235.37 | 1287.91 | 0.0174733 | 3.97266 | 19.2093 | 3.92159 | 0.000947336 | 8.45527e-05 | 3.45113e-06 | 1(Win) | true |
| Glaze | 910.312 | 0.0866011 | 908.137ms | 1811 | 2560 | 6911.04 | 1897.27 | 0.0159177 | 5.78352 | 29.0337 | 4.45334 | 0.00115074 | 0.00016889 | 2.6962e-05 | 2(Loss) | true |
| simdjson (ondemand) | 461.039 | 0.107095 | 1098.98ms | 1811 | 1280 | 20602.1 | 3746.11 | 0.0710824 | 11.2928 | 58.2435 | 11.2082 | 0.000677285 | 0.000104828 | 1.63929e-05 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 370.399 | 0.170474 | 1267.27ms | 1997 | 640 | 49171.6 | 5141.72 | 0.00714185 | 14.015 | 58.2233 | 10.346 | 0.0190606 | 0.000116581 | 2.42551e-05 | 1(Win) | true |
| Glaze | 304.966 | 0.285774 | 1290.05ms | 1798 | 320 | 82617.3 | 5622.61 | 0.0582131 | 17.0024 | 71.2831 | 12.1485 | 0.021882 | 0.000119925 | 1.91185e-05 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 938.266 | 0.0984964 | 931.431ms | 1997 | 4890 | 19545.8 | 2029.79 | 0.121855 | 5.58016 | 17.8127 | 1.04106 | 0.000520105 | 8.32537e-05 | 6.14419e-06 | 1(Win) | true |
| Glaze | 673.708 | 0.12941 | 990.666ms | 1798 | 1280 | 13886.1 | 2545.18 | 0.0259922 | 7.77076 | 26.4321 | 2.17241 | 0.000831219 | 0.000121663 | 3.69334e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1474.86 | 0.17731 | 812.427ms | 1313 | 2560 | 5801.48 | 849.015 | 0.0388627 | 3.63531 | 18.1889 | 2.90404 | 0.00077411 | 0.000164818 | 3.09406e-05 | 1(Win) | true |
| Glaze | 993.687 | 0.10952 | 846.377ms | 1313 | 4890 | 9313.81 | 1260.13 | 0.0618396 | 5.34511 | 26.9345 | 3.62529 | 0.00103153 | 0.000224591 | 4.12736e-05 | 2(Loss) | true |
| simdjson (ondemand) | 370.729 | 0.0615287 | 1062.53ms | 1313 | 4890 | 21119.3 | 3377.6 | 0.268573 | 14.0032 | 56.8325 | 11.0685 | 0.000890108 | 0.000179891 | 3.23959e-05 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1762.69 | 0.135629 | 793.139ms | 1313 | 80 | 74.2627 | 710.375 | 0.0140791 | 3.09197 | 16.7312 | 2.58873 | 0.000780655 | 0.000114242 | 1.90404e-05 | 1(Win) | true |
| Glaze | 1102.2 | 0.108234 | 832.403ms | 1313 | 4890 | 7393.4 | 1136.07 | 0.300458 | 4.81176 | 25.5309 | 3.30998 | 0.0019355 | 0.000119148 | 1.58864e-05 | 2(Loss) | true |
| simdjson (ondemand) | 382.867 | 0.0962142 | 1055.58ms | 1313 | 1280 | 12674.2 | 3270.52 | 0.0416905 | 13.5652 | 55.38 | 10.7395 | 0.000831231 | 0.000188024 | 6.06912e-05 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 336.728 | 0.0605872 | 1094.81ms | 1313 | 4890 | 24822.3 | 3718.65 | 0.186581 | 15.4504 | 74.0807 | 15.5248 | 0.0187965 | 0.000191416 | 4.99956e-05 | 1(Win) | true |
| Glaze | 306.514 | 0.111857 | 1137.2ms | 1313 | 1280 | 26728.1 | 4085.21 | 0.00686594 | 16.8489 | 83.2468 | 16.5423 | 0.0271212 | 0.000146373 | 2.49905e-05 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2403.43 | 0.278042 | 779.209ms | 1313 | 1280 | 2685.93 | 520.994 | 0.0792384 | 2.32148 | 12.3534 | 1.35263 | 0.000840156 | 0.000117217 | 1.13052e-05 | 1(Win) | true |
| Glaze | 1076.52 | 0.117417 | 850.365ms | 1313 | 2560 | 4775.18 | 1163.17 | 0.0410887 | 4.96183 | 21.3481 | 2.74334 | 0.00313482 | 0.000174338 | 5.32535e-05 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1237.53 | 0.0765579 | 1053.18ms | 4215 | 2560 | 15830.7 | 3248.18 | 0.747425 | 4.2141 | 18.0909 | 3.23179 | 0.00193654 | 0.000118439 | 6.10728e-05 | 1(Win) | true |
| simdjson (ondemand) | 949.394 | 0.0751808 | 1152.77ms | 4215 | 4890 | 49547.9 | 4234 | 0.171854 | 5.43811 | 24.1874 | 4.36465 | 0.00343466 | 8.45165e-05 | 2.49377e-05 | 2(Loss) | true |
| Glaze | 902.809 | 0.0711095 | 1172.91ms | 4215 | 2560 | 25662.5 | 4452.48 | 0.122919 | 5.7148 | 24.9618 | 5.07497 | 0.0026329 | 6.00534e-05 | 1.5384e-05 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1826.56 | 0.0597563 | 994.701ms | 4215 | 4890 | 8456.78 | 2200.72 | 0.20965 | 2.86441 | 13.0396 | 2.03749 | 0.000620629 | 6.68564e-05 | 1.89216e-05 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1220.73 | 0.097864 | 1100.84ms | 4215 | 2560 | 26585.5 | 3292.91 | 0.149966 | 4.19183 | 19.6527 | 3.27806 | 0.00234662 | 7.08037e-05 | 1.8535e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1219.85 | 0.240994 | 1106.08ms | 4215 | 320 | 20181.1 | 3295.27 | 0.177938 | 4.3058 | 20.013 | 3.89585 | 0.00224718 | 5.48636e-05 | 1.18624e-05 | 2(Tie) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1615.73 | 0.0941504 | 971.57ms | 4215 | 2560 | 14045.7 | 2487.88 | 0.151725 | 3.21816 | 13.5466 | 2.77438 | 0.00151375 | 8.30368e-05 | 2.53929e-05 | 1(Win) | true |
| Glaze | 879.796 | 0.0552716 | 1190.43ms | 4215 | 4890 | 31184.9 | 4568.94 | 0.572189 | 5.85162 | 29.5718 | 5.81329 | 0.00295653 | 7.25329e-05 | 2.22693e-05 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5392.16 | 0.116301 | 812.273ms | 4215 | 4890 | 3675.72 | 745.478 | 0.050568 | 1.00357 | 4.41186 | 0.567735 | 0.000978878 | 4.32286e-05 | 1.04797e-05 | 1(Win) | true |
| Glaze | 2180.01 | 0.0810884 | 930.062ms | 4215 | 4890 | 10932.1 | 1843.91 | 0.229524 | 2.40727 | 10.3618 | 1.5108 | 0.00143848 | 7.29695e-05 | 3.20697e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1702.9 | 0.192292 | 788.337ms | 1213 | 2560 | 4368.25 | 679.315 | 0.13099 | 3.20847 | 16.0503 | 2.9258 | 0.00152128 | 0.00037871 | 0.000174863 | 1(Win) | true |
| Glaze | 994.496 | 0.155743 | 835.321ms | 1213 | 2560 | 8401.8 | 1163.21 | 0.311437 | 5.36009 | 26.8368 | 3.83512 | 0.00216534 | 0.000213185 | 7.11691e-05 | 2(Loss) | true |
| simdjson (ondemand) | 353.25 | 0.19422 | 1051.18ms | 1213 | 320 | 12944.8 | 3274.75 | 0.027094 | 14.759 | 59.2787 | 12.0322 | 0.0114746 | 0.000157152 | 2.57626e-05 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2006.17 | 0.31943 | 775.4ms | 1213 | 640 | 2171.27 | 576.623 | 0.125619 | 2.73928 | 14.634 | 2.6249 | 0.00158826 | 0.0002821 | 0.000109491 | 1(Win) | true |
| Glaze | 1143.14 | 0.111114 | 820.884ms | 1213 | 4890 | 6182.6 | 1011.96 | 0.638395 | 4.67379 | 25.3553 | 3.50701 | 0.00112753 | 0.000101828 | 1.95564e-05 | 2(Loss) | true |
| simdjson (ondemand) | 374.307 | 0.0518615 | 1030.37ms | 1213 | 4890 | 12562.2 | 3090.53 | 0.103899 | 13.9363 | 57.8897 | 11.7164 | 0.015284 | 0.000159317 | 2.71429e-05 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 304.565 | 0.0698424 | 1108.48ms | 1213 | 2560 | 18015.3 | 3798.23 | 0.0943524 | 16.9323 | 77.6422 | 16.0412 | 0.0223999 | 0.000219626 | 5.15251e-05 | 1(Win) | true |
| Glaze | 281.406 | 0.0941256 | 1140.91ms | 1213 | 1280 | 19163.8 | 4110.81 | 0.055615 | 18.4761 | 90.4427 | 18.2811 | 0.0277759 | 0.00034393 | 0.00015844 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2371.63 | 0.224253 | 780.283ms | 1213 | 160 | 191.437 | 487.769 | 0.175237 | 2.36032 | 12.6216 | 1.46414 | 0.00108718 | 0.000139118 | 4.63726e-05 | 1(Win) | true |
| Glaze | 955.411 | 0.0935624 | 866.195ms | 1213 | 4890 | 6275.56 | 1210.8 | 0.495591 | 5.57216 | 21.9143 | 2.9695 | 0.00320505 | 0.000226247 | 7.51909e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1802.23 | 0.0424593 | 5757.94ms | 94653 | 2560 | 1.1578e+06 | 50086.8 | 0.0658539 | 2.8214 | 12.0654 | 2.47043 | 0.00926106 | 1.50798e-05 | 8.24145e-06 | 1(Win) | true |
| Glaze | 1430.89 | 0.0316273 | 7053.86ms | 94653 | 4890 | 1.94667e+06 | 63085.5 | 0.140397 | 3.54851 | 15.8331 | 3.11211 | 0.0157133 | 1.89887e-05 | 1.10273e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1397.05 | 0.0314331 | 7213.93ms | 94653 | 4890 | 2.01709e+06 | 64613.2 | 0.0575225 | 3.63491 | 16.3679 | 2.94707 | 0.0130652 | 4.11275e-05 | 3.1025e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1232.8 | 0.0511591 | 8068.76ms | 94653 | 1280 | 1.79613e+06 | 73222 | 0.0482812 | 4.10752 | 16.925 | 3.13362 | 0.0108169 | 2.54878e-05 | 1.26036e-05 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3111.35 | 0.172038 | 4885.49ms | 94653 | 320 | 797205 | 29012.5 | 0.0932255 | 1.62667 | 7.96657 | 1.55511 | 0.00490023 | 6.33894e-06 | 1.41966e-06 | 1(Win) | true |
| Glaze | 2112.6 | 0.0743122 | 6232.81ms | 94653 | 1280 | 1.29053e+06 | 42728.5 | 0.235961 | 2.41645 | 11.9558 | 2.23933 | 0.0097832 | 1.36518e-05 | 8.02273e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2056.02 | 0.254429 | 6370.84ms | 94653 | 160 | 1.99649e+06 | 43904.2 | 0.0470278 | 2.457 | 12.2662 | 2.0331 | 0.00829801 | 1.53851e-05 | 7.06528e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1690.1 | 0.0709824 | 7335.44ms | 94653 | 1280 | 1.83973e+06 | 53409.9 | 0.0466364 | 2.99613 | 12.9941 | 2.24738 | 0.0074417 | 1.09776e-05 | 5.24944e-06 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15561.4 | 0.190918 | 1317.27ms | 94653 | 320 | 39247.8 | 5800.77 | 0.0925743 | 0.326819 | 1.29682 | 0.184104 | 8.36278e-05 | 5.84371e-06 | 3.07043e-06 | 1(Win) | true |
| Glaze | 5288.9 | 0.072527 | 2433.4ms | 94653 | 2560 | 392263 | 17067.5 | 0.360831 | 0.955656 | 4.37683 | 0.66691 | 9.17702e-05 | 1.50385e-05 | 1.00862e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15513.5 | 0.058332 | 1320.15ms | 94653 | 2560 | 29491.8 | 5818.67 | 0.0644624 | 0.327833 | 1.29137 | 0.1829 | 7.95298e-05 | 3.97835e-06 | 1.23807e-06 | 1(Win) | true |
| Glaze | 5981.45 | 0.0481973 | 2254.39ms | 94653 | 2560 | 135438 | 15091.4 | 0.199455 | 0.84892 | 4.32645 | 0.655341 | 5.12109e-05 | 1.04163e-05 | 7.82051e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2111.22 | 0.226935 | 6343.12ms | 124597 | 160 | 2.61018e+06 | 56282.7 | 0.0620587 | 2.38448 | 10.6706 | 2.15318 | 0.00721667 | 9.78154e-06 | 6.16989e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1644.55 | 0.191383 | 8014.01ms | 124597 | 160 | 3.0595e+06 | 72254 | 0.0254982 | 3.06792 | 13.4648 | 2.39364 | 0.0121203 | 2.42281e-05 | 1.66035e-05 | 2(Loss) | true |
| Glaze | 1631.12 | 0.1128 | 8013.69ms | 124597 | 2560 | 1.72865e+07 | 72848.8 | 0.162238 | 3.10714 | 13.9268 | 2.76804 | 0.0118022 | 4.14367e-05 | 2.95045e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1577.81 | 0.0775076 | 8298.17ms | 124597 | 640 | 2.18059e+06 | 75310 | 0.215354 | 3.20852 | 13.1596 | 2.39452 | 0.00851202 | 2.05538e-05 | 9.44294e-06 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3386.23 | 0.0835477 | 5493.79ms | 124597 | 1280 | 1.10018e+06 | 35090.7 | 0.042459 | 1.49725 | 7.55419 | 1.45928 | 0.00428028 | 1.14243e-05 | 6.28903e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2347.28 | 0.112871 | 7080.18ms | 124597 | 640 | 2.08946e+06 | 50622.5 | 0.11277 | 2.15536 | 10.3515 | 1.70116 | 0.00839584 | 2.22969e-05 | 1.52617e-05 | 2(Loss) | true |
| Glaze | 2222.98 | 0.147433 | 7429.22ms | 124597 | 160 | 993703 | 53453 | 0.0494955 | 2.31232 | 10.9967 | 2.1101 | 0.00917483 | 1.8309e-05 | 1.32427e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2148.55 | 0.0536801 | 7528.36ms | 124597 | 4890 | 4.30982e+06 | 55304.6 | 0.123316 | 2.35855 | 10.1731 | 1.72241 | 0.00570223 | 3.99817e-05 | 2.93872e-05 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16558.8 | 0.0439599 | 1522.31ms | 136037 | 4890 | 58007.1 | 7834.82 | 0.139545 | 0.308036 | 1.29399 | 0.215125 | 0.00021991 | 3.23051e-06 | 8.92936e-07 | 1(Win) | true |
| Glaze | 5363.64 | 0.0707311 | 3164.91ms | 136076 | 2560 | 749731 | 24194.8 | 0.176973 | 0.93892 | 4.09524 | 0.690408 | 0.00145646 | 4.67053e-06 | 1.84869e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17309.8 | 0.109577 | 1491.33ms | 136037 | 640 | 43166.8 | 7494.87 | 0.0196632 | 0.298821 | 1.2901 | 0.214251 | 0.000209272 | 5.50172e-06 | 3.8133e-06 | 1(Win) | true |
| Glaze | 5860.09 | 0.110942 | 2937.68ms | 136076 | 320 | 193149 | 22145.1 | 0.00917331 | 0.864331 | 4.06236 | 0.682685 | 0.00161045 | 3.46773e-06 | 1.79128e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 884.147 | 0.075324 | 7544.02ms | 2251027 | 160 | 5.35179e+08 | 2.42804e+06 | 0.0434659 | 5.70886 | 29.7611 | 5.98378 | 0.00730876 | 0.0644085 | 3.65222e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 857.823 | 0.0898907 | 7782.76ms | 2251027 | 80 | 4.04842e+08 | 2.50255e+06 | 0.0931592 | 5.87097 | 31.7381 | 5.89909 | 0.0101789 | 0.0628076 | 0.000187631 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 857.143 | 0.119438 | 7773.26ms | 2251027 | 30 | 2.68449e+08 | 2.50454e+06 | 0.0324692 | 5.88919 | 32.2565 | 6.40511 | 0.0112501 | 0.102465 | 0.000100502 | 2(Tie) | true |
| simdjson (ondemand) | 803.007 | 0.0752757 | 8311.55ms | 2251027 | 80 | 3.23983e+08 | 2.67338e+06 | 0.0284173 | 6.28424 | 31.2861 | 5.42041 | 0.0145509 | 0.107727 | 8.48002e-05 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1042.51 | 0.119119 | 7554.37ms | 2251027 | 30 | 1.80504e+08 | 2.05921e+06 | 0.10516 | 4.84249 | 24.8257 | 4.78806 | 0.00674811 | 0.0417321 | 2.5381e-05 | 1(Win) | true |
| Glaze | 1012.4 | 0.113501 | 7803.72ms | 2251027 | 40 | 2.31695e+08 | 2.12046e+06 | 0.0139942 | 4.9805 | 26.7576 | 4.69617 | 0.00928199 | 0.0392279 | 6.0639e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1007.32 | 0.0650965 | 7794.07ms | 2251027 | 160 | 3.07935e+08 | 2.13114e+06 | 0.014727 | 5.01439 | 27.3741 | 5.2241 | 0.0105059 | 0.0787475 | 5.86677e-05 | 3(Loss) | true |
| simdjson (ondemand) | 956.874 | 0.0678597 | 8170.85ms | 2251027 | 80 | 1.85424e+08 | 2.2435e+06 | 0.0621143 | 5.27289 | 26.3448 | 4.22833 | 0.0108886 | 0.0752489 | 0.000234054 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1904.71 | 0.0609945 | 6639.34ms | 2090326 | 320 | 1.30408e+08 | 1.04661e+06 | 0.089163 | 2.65656 | 7.91866 | 0.405668 | 0.000244811 | 0.0507323 | 3.92388e-05 | 1(Win) | true |
| Glaze | 961.68 | 0.111679 | 6469.87ms | 2090234 | 160 | 8.5742e+08 | 2.07283e+06 | 0.0542625 | 5.24974 | 9.34212 | 0.534077 | 0.000241863 | 0.0694212 | 0.000764242 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1908.02 | 0.0794247 | 6635.38ms | 2090326 | 80 | 5.50886e+07 | 1.04479e+06 | 0.135522 | 2.65465 | 7.91827 | 0.405635 | 0.0002408 | 0.0505487 | 2.45536e-05 | 1(Win) | true |
| Glaze | 994.655 | 0.117167 | 6236.72ms | 2090234 | 160 | 8.82219e+08 | 2.00411e+06 | 0.523626 | 5.07905 | 9.33809 | 0.533136 | 0.000234681 | 0.0433358 | 0.000133011 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1912.65 | 0.0994402 | 8380.1ms | 5373214 | 80 | 5.67819e+08 | 2.67916e+06 | 0.0131589 | 2.65414 | 14.6392 | 3.0087 | 0.00326078 | 0.0382623 | 0.0005175 | 1(Win) | true |
| Jsonifier (two-stage) | 1895.23 | 0.0700345 | 8422.57ms | 5373214 | 160 | 5.73706e+08 | 2.70379e+06 | 0.225507 | 2.64831 | 14.307 | 2.71607 | 0.00460547 | 0.0624453 | 0.000499087 | 2(Loss) | true |
| simdjson (ondemand) | 1804.3 | 0.0721066 | 8841.4ms | 5373214 | 80 | 3.355e+08 | 2.84005e+06 | 0.000871895 | 2.79825 | 13.7963 | 2.30344 | 0.00633192 | 0.0646492 | 0.000653938 | 3(Loss) | true |
| Glaze | 1703.71 | 0.0416057 | 9355.56ms | 5373214 | 160 | 2.50555e+08 | 3.00773e+06 | 0.231537 | 2.96158 | 15.9991 | 2.99568 | 0.00510195 | 0.0406025 | 0.000468047 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2196.98 | 0.0705805 | 8426.96ms | 5373214 | 80 | 2.16808e+08 | 2.33243e+06 | 0.0126783 | 2.29796 | 12.5941 | 2.51409 | 0.00307514 | 0.0281069 | 0.000345091 | 1(Win) | true |
| Jsonifier (two-stage) | 2183.67 | 0.217983 | 8437.71ms | 5373214 | 40 | 1.04664e+09 | 2.34664e+06 | 0.0306112 | 2.29824 | 12.2637 | 2.22175 | 0.00431268 | 0.0523078 | 0.00202849 | 2(Loss) | true |
| simdjson (ondemand) | 2130.91 | 0.0972797 | 8663.94ms | 5373214 | 80 | 4.37798e+08 | 2.40475e+06 | 0.475058 | 2.37347 | 11.7272 | 1.8044 | 0.00486193 | 0.050817 | 0.00044911 | 3(Loss) | true |
| Glaze | 1951.88 | 0.0950943 | 9357.11ms | 5373214 | 40 | 2.49305e+08 | 2.62531e+06 | 0.00848828 | 2.58608 | 13.9455 | 2.50089 | 0.00465173 | 0.0297269 | 0.000385654 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5205.44 | 0.0659496 | 7779.07ms | 6661989 | 320 | 2.07332e+08 | 1.22052e+06 | 0.0469089 | 0.985354 | 2.95785 | 0.261242 | 7.62906e-05 | 0.0278388 | 0.000147463 | 1(Win) | true |
| Glaze | 3286.39 | 0.131513 | 6030.39ms | 6661897 | 160 | 1.03422e+09 | 1.93321e+06 | 0.577877 | 1.55011 | 4.23033 | 0.46932 | 7.64375e-05 | 0.0630756 | 0.00338083 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5200.53 | 0.0709153 | 7748.86ms | 6661989 | 320 | 2.40183e+08 | 1.22168e+06 | 0.116033 | 0.983729 | 2.9578 | 0.261231 | 7.53637e-05 | 0.027805 | 0.000140718 | 1(Win) | true |
| Glaze | 3947.57 | 0.188258 | 5027.57ms | 6661897 | 40 | 3.67203e+08 | 1.60942e+06 | 0.0461093 | 1.29056 | 4.22891 | 0.468988 | 8.30282e-05 | 0.02448 | 7.09933e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2295.16 | 0.0826122 | 5518.89ms | 500299 | 640 | 1.88756e+07 | 207882 | 0.012601 | 2.21009 | 9.84826 | 1.92019 | 0.0107812 | 0.0106245 | 3.32145e-05 | 1(Win) | true |
| Glaze | 1788.5 | 0.0546439 | 7039.91ms | 500299 | 1280 | 2.72005e+07 | 266773 | 0.318337 | 2.83799 | 12.5358 | 2.36605 | 0.014151 | 0.00549814 | 5.72252e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1685.35 | 0.0726767 | 7427.28ms | 500299 | 640 | 2.70925e+07 | 283100 | 0.0654521 | 2.9934 | 13.4126 | 2.37637 | 0.0147299 | 0.0450917 | 4.89457e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1114.2 | 0.0693797 | 5549.19ms | 500299 | 640 | 5.64905e+07 | 428219 | 0.342354 | 4.53866 | 19.193 | 2.85368 | 0.0160475 | 0.0478628 | 0.000155726 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2828.47 | 0.059358 | 5288.08ms | 500299 | 1280 | 1.28329e+07 | 168686 | 0.267071 | 1.7921 | 8.69672 | 1.64055 | 0.00757235 | 0.0054982 | 1.32796e-05 | 1(Win) | true |
| Glaze | 2155.33 | 0.164494 | 6839.46ms | 500299 | 160 | 2.12153e+07 | 221368 | 0.0512486 | 2.36395 | 11.3894 | 2.08902 | 0.00941807 | 0.0021267 | 3.05192e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1984.43 | 0.0775235 | 7201.6ms | 500299 | 640 | 2.22348e+07 | 240433 | 0.053942 | 2.54344 | 12.2645 | 2.09793 | 0.0108924 | 0.03341 | 2.00099e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1278.34 | 0.109577 | 5228.47ms | 500299 | 320 | 5.35246e+07 | 373236 | 0.128262 | 3.94123 | 18.0364 | 2.56943 | 0.00875024 | 0.0259814 | 3.86769e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10063.9 | 0.0884961 | 5519.11ms | 500299 | 640 | 1.12657e+06 | 47409.5 | 0.126709 | 0.50404 | 2.22115 | 0.242375 | 0.00176688 | 0.00327968 | 5.80903e-06 | 1(Win) | true |
| Glaze | 5068.67 | 0.067904 | 5216.89ms | 500299 | 2560 | 1.04593e+07 | 94131.6 | 0.039137 | 0.99636 | 4.19156 | 0.585182 | 0.00113306 | 0.0243559 | 2.93887e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10054.5 | 0.0299039 | 5512.64ms | 500299 | 4890 | 984695 | 47453.5 | 0.020496 | 0.502731 | 2.2201 | 0.242137 | 0.00171541 | 0.00299855 | 1.20333e-05 | 1(Win) | true |
| Glaze | 5827.39 | 0.059503 | 8953.06ms | 500299 | 4890 | 1.16064e+07 | 81875.8 | 0.0921381 | 0.86636 | 4.17823 | 0.582038 | 0.00110908 | 0.00262959 | 3.306e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3735.56 | 0.122066 | 7715.79ms | 1151920 | 160 | 2.06179e+07 | 294081 | 0.0210446 | 1.34938 | 6.48637 | 1.33532 | 0.00447364 | 0.0202512 | 3.78281e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 3442.56 | 0.11658 | 8360.99ms | 1151920 | 320 | 4.42873e+07 | 319110 | 0.0888646 | 1.46851 | 6.63875 | 1.07914 | 0.00659208 | 0.0544229 | 3.93202e-05 | 2(Loss) | true |
| Glaze | 2588.45 | 0.106671 | 5495.7ms | 1151920 | 160 | 3.27927e+07 | 424407 | 0.117851 | 1.94905 | 8.62325 | 1.67801 | 0.00735608 | 0.0167846 | 7.2976e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2367.36 | 0.0810917 | 6009.45ms | 1151920 | 640 | 9.06255e+07 | 464044 | 0.0312262 | 2.13856 | 9.02185 | 1.27285 | 0.0070865 | 0.0519082 | 0.000245777 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4355.38 | 0.151969 | 7493.96ms | 1151920 | 160 | 2.35085e+07 | 252230 | 0.000450975 | 1.16592 | 5.98751 | 1.21427 | 0.00321322 | 0.0136002 | 1.0005e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 3952.28 | 0.0640272 | 8193.07ms | 1151920 | 1280 | 4.05404e+07 | 277955 | 0.0539508 | 1.27726 | 6.14169 | 0.958566 | 0.00503719 | 0.0454764 | 6.66381e-05 | 2(Loss) | true |
| Glaze | 2892.18 | 0.106468 | 5382.95ms | 1151920 | 320 | 5.23337e+07 | 379837 | 0.0550541 | 1.74503 | 8.12476 | 1.55765 | 0.00543716 | 0.0108965 | 1.97252e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2707.51 | 0.208772 | 5707.1ms | 1151920 | 80 | 5.74036e+07 | 405745 | 0.0413821 | 1.87263 | 8.51559 | 1.14856 | 0.00411913 | 0.0381289 | 8.57698e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14007.4 | 0.0439975 | 5419.55ms | 1439562 | 2560 | 4.76039e+06 | 98010.7 | 0.0810816 | 0.360954 | 1.39302 | 0.220363 | 0.000678186 | 0.0191336 | 8.46313e-06 | 1(Win) | true |
| Glaze | 5273.98 | 0.161575 | 6843.53ms | 1439584 | 320 | 5.66106e+07 | 260315 | 0.282266 | 0.954555 | 3.07321 | 0.528545 | 0.00100071 | 0.0627799 | 5.7382e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14021.4 | 0.0437865 | 5422.11ms | 1439562 | 2560 | 4.70541e+06 | 97912.5 | 0.0302474 | 0.360119 | 1.39264 | 0.220277 | 0.000675317 | 0.0189471 | 4.44498e-06 | 1(Win) | true |
| Glaze | 7064.37 | 0.137529 | 5168.85ms | 1439584 | 320 | 2.28594e+07 | 194341 | 0.0749971 | 0.715386 | 3.06771 | 0.527269 | 0.000994107 | 0.0188737 | 1.80239e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2374.47 | 0.349644 | 2999.21ms | 56369 | 80 | 501289 | 22639.8 | 0.207663 | 2.14488 | 8.87018 | 1.86466 | 0.00420488 | 0.000253686 | 0.000203348 | 1(Win) | true |
| Glaze | 1952.01 | 0.044873 | 3503ms | 56369 | 4890 | 746788 | 27539.7 | 0.00344621 | 2.59314 | 11.6495 | 2.34003 | 0.00482123 | 6.27729e-05 | 3.31151e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1743.5 | 0.0863172 | 3837.76ms | 56369 | 1280 | 906652 | 30833.2 | 0.26192 | 2.9165 | 13.0288 | 2.37368 | 0.00559048 | 2.35058e-05 | 1.23489e-05 | 3(Loss) | true |
| simdjson (ondemand) | 933.445 | 0.0730231 | 6521.67ms | 56369 | 2560 | 4.52756e+06 | 57590.6 | 0.0636884 | 5.40126 | 22.4003 | 3.60691 | 0.0116043 | 0.000137951 | 8.64144e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3621 | 0.0596417 | 2597.15ms | 56369 | 4890 | 383383 | 14846.1 | 0.00865383 | 1.40316 | 6.70862 | 1.37008 | 0.00184023 | 1.25959e-05 | 5.8989e-06 | 1(Win) | true |
| Glaze | 2787.99 | 0.0637129 | 3029.75ms | 56369 | 4890 | 738010 | 19281.9 | 0.09145 | 1.81576 | 9.23069 | 1.78417 | 0.00323242 | 1.74936e-05 | 8.31143e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2302.11 | 0.0716015 | 3454.37ms | 56369 | 2560 | 715668 | 23351.4 | 0.295698 | 2.20782 | 10.8653 | 1.8785 | 0.00286607 | 1.49337e-05 | 8.46127e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1103.41 | 0.152832 | 6021.01ms | 56369 | 640 | 3.54826e+06 | 48719.6 | 0.0781161 | 4.58532 | 20.0662 | 3.07761 | 0.00945855 | 2.63609e-05 | 1.16698e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12658.4 | 0.102413 | 1166.34ms | 56369 | 1280 | 24212.5 | 4246.78 | 0.223236 | 0.403933 | 1.50946 | 0.214551 | 0.000170431 | 8.45434e-06 | 3.49261e-06 | 1(Win) | true |
| Glaze | 5048.67 | 0.0939156 | 1806.15ms | 56369 | 2560 | 256001 | 10647.9 | 0.284073 | 1.00158 | 3.48977 | 0.484735 | 0.000113046 | 1.90916e-05 | 8.87012e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12698 | 0.113389 | 1169.78ms | 56369 | 1280 | 29496.1 | 4233.57 | 0.0299224 | 0.402555 | 1.49976 | 0.212333 | 0.000166786 | 1.64652e-05 | 8.60679e-06 | 1(Win) | true |
| Glaze | 5553.63 | 0.0902464 | 1707.6ms | 56369 | 2560 | 195356 | 9679.74 | 0.156473 | 0.919861 | 3.41113 | 0.467048 | 0.000109532 | 1.06372e-05 | 3.81138e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3006.81 | 0.0526065 | 3411.05ms | 83958 | 4890 | 959620 | 26629.1 | 0.0889288 | 1.68666 | 7.55167 | 1.53009 | 0.00290193 | 3.26729e-05 | 1.76883e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2462.96 | 0.0995338 | 4005.63ms | 83958 | 1280 | 1.34017e+06 | 32509 | 0.122026 | 2.0624 | 9.38612 | 1.65029 | 0.00291209 | 5.66131e-05 | 3.81701e-05 | 2(Loss) | true |
| Glaze | 2212.23 | 0.0861582 | 4376.13ms | 83958 | 1280 | 1.24471e+06 | 36193.6 | 0.0539189 | 2.29695 | 10.6088 | 2.17474 | 0.00539497 | 3.75839e-05 | 1.75125e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1348.44 | 0.0674188 | 6709.77ms | 83958 | 2560 | 4.10264e+06 | 59378.7 | 0.11685 | 3.74207 | 15.4601 | 2.44256 | 0.00899521 | 7.74011e-05 | 3.28289e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4225.32 | 0.0669764 | 3012.18ms | 83958 | 4890 | 787693 | 18949.7 | 0.285085 | 1.20057 | 6.09968 | 1.19773 | 0.00136256 | 1.64022e-05 | 8.4739e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3173.05 | 0.0733062 | 3634.38ms | 83958 | 2560 | 875972 | 25233.9 | 0.136818 | 1.59642 | 7.93814 | 1.31936 | 0.00201714 | 1.63633e-05 | 1.0059e-05 | 2(Loss) | true |
| Glaze | 2882.39 | 0.0635016 | 3870.64ms | 83958 | 4890 | 1.52159e+06 | 27778.5 | 0.0387039 | 1.7617 | 8.98655 | 1.80239 | 0.00357825 | 2.37459e-05 | 1.55984e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1599.46 | 0.196068 | 6137.8ms | 83958 | 320 | 3.08276e+06 | 50059.7 | 0.127466 | 3.15796 | 13.8885 | 2.08586 | 0.00645408 | 2.25187e-05 | 1.35112e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15078.1 | 0.132926 | 1337.4ms | 94370 | 640 | 40287.9 | 5968.8 | 0.0606383 | 0.337247 | 1.33701 | 0.233538 | 0.000264004 | 1.20039e-05 | 5.91091e-06 | 1(Win) | true |
| Glaze | 3971.33 | 0.0772964 | 3011.76ms | 94370 | 2560 | 785517 | 22662 | 0.18627 | 1.2753 | 4.17865 | 0.678383 | 0.0015362 | 9.90947e-06 | 3.84126e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15460.8 | 0.105112 | 1323.59ms | 94370 | 1280 | 47919.5 | 5821.04 | 0.0788576 | 0.33226 | 1.33126 | 0.232245 | 0.000261578 | 3.09619e-06 | 9.18923e-07 | 1(Win) | true |
| Glaze | 4563.63 | 0.0628621 | 2719.78ms | 94370 | 4890 | 751509 | 19720.8 | 0.0167198 | 1.10525 | 4.12562 | 0.666091 | 0.00156537 | 1.58017e-05 | 8.19556e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1759.34 | 0.0765506 | 3633.86ms | 53331 | 4890 | 2.39479e+06 | 28908.8 | 0.164998 | 2.88019 | 8.59966 | 1.71939 | 0.0120526 | 0.000222015 | 0.000109502 | 1(Win) | true |
| Jsonifier (two-stage) | 1455.88 | 0.143654 | 4266.34ms | 53331 | 1280 | 3.2237e+06 | 34934.4 | 0.453821 | 3.4873 | 11.455 | 1.97896 | 0.0162215 | 0.000198847 | 8.66054e-05 | 2(Loss) | true |
| Glaze | 1444.98 | 0.0783503 | 4269.8ms | 53331 | 2560 | 1.94695e+06 | 35197.9 | 0.23629 | 3.53384 | 11.7063 | 2.2495 | 0.0220948 | 0.000111633 | 5.12937e-05 | 3(Loss) | true |
| simdjson (ondemand) | 961.068 | 0.105491 | 6046.21ms | 53331 | 1280 | 3.98927e+06 | 52920.7 | 0.3795 | 5.28567 | 15.5852 | 2.7722 | 0.0154296 | 0.000133468 | 5.37475e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2462.22 | 0.118532 | 3403.16ms | 53331 | 2560 | 1.53467e+06 | 20656.4 | 0.0557459 | 2.06086 | 6.33003 | 1.20325 | 0.0086022 | 5.39159e-05 | 2.54015e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1920.5 | 0.0801167 | 4013.35ms | 53331 | 4890 | 2.20132e+06 | 26482.8 | 0.123242 | 2.65105 | 9.18824 | 1.46346 | 0.0123849 | 5.18888e-05 | 1.80108e-05 | 2(Loss) | true |
| Glaze | 1905.45 | 0.123793 | 4014.29ms | 53331 | 1280 | 1.39754e+06 | 26692.1 | 0.156154 | 2.67842 | 9.43009 | 1.73225 | 0.0179317 | 3.89812e-05 | 1.82674e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1139.05 | 0.114246 | 5764.58ms | 53331 | 1280 | 3.33093e+06 | 44651.5 | 0.0401463 | 4.46325 | 13.5687 | 2.31259 | 0.0110572 | 3.57877e-05 | 1.65242e-05 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14980.4 | 0.205066 | 1115.73ms | 58581 | 4890 | 285998 | 3729.35 | 0.0569213 | 0.342548 | 1.12782 | 0.158208 | 4.44493e-05 | 2.14584e-05 | 1.108e-05 | 1(Win) | true |
| Glaze | 4924.33 | 0.130319 | 1883.37ms | 58581 | 4890 | 1.06892e+06 | 11345.1 | 0.0137451 | 1.02994 | 2.62459 | 0.382326 | 7.44639e-05 | 4.16077e-05 | 2.02157e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15173 | 0.590225 | 1104.01ms | 58581 | 640 | 302263 | 3682.01 | 0.0688687 | 0.33772 | 1.11872 | 0.156092 | 3.45675e-05 | 1.52567e-05 | 7.62833e-06 | 1(Win) | true |
| Glaze | 5635.29 | 0.208074 | 1740.93ms | 58581 | 2560 | 1.08932e+06 | 9913.8 | 0.280663 | 0.900515 | 2.55385 | 0.36587 | 5.27915e-05 | 1.89775e-05 | 7.42828e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2048 | 0.178744 | 3776.48ms | 65103 | 1280 | 3.7585e+06 | 30315.9 | 0.132513 | 2.4794 | 7.8095 | 1.5342 | 0.00969537 | 0.000113126 | 3.37806e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1691.08 | 0.201421 | 4418.99ms | 65103 | 640 | 3.49995e+06 | 36714.4 | 0.0869815 | 2.9946 | 9.96615 | 1.68144 | 0.0129703 | 0.000216196 | 8.80336e-05 | 2(Loss) | true |
| Glaze | 1532.41 | 0.0807458 | 4796.5ms | 65103 | 2560 | 2.73989e+06 | 40516 | 0.357664 | 3.31282 | 10.9126 | 2.10043 | 0.0204388 | 0.000102542 | 4.17127e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1148.58 | 0.206345 | 6140.22ms | 65103 | 320 | 3.98121e+06 | 54055.4 | 0.131895 | 4.40086 | 12.9806 | 2.27359 | 0.0125058 | 9.84018e-05 | 5.20329e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2835.9 | 0.227263 | 3531.52ms | 65103 | 1280 | 3.16875e+06 | 21893.2 | 0.187445 | 1.79967 | 5.95525 | 1.11296 | 0.00661183 | 4.54088e-05 | 1.53603e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2201.68 | 0.154915 | 4162.11ms | 65103 | 1280 | 2.44282e+06 | 28199.8 | 0.174374 | 2.29242 | 8.1162 | 1.26123 | 0.00977377 | 6.52212e-05 | 3.79687e-05 | 2(Loss) | true |
| Glaze | 1962.3 | 0.173713 | 4520.81ms | 65103 | 640 | 1.93339e+06 | 31640 | 0.293468 | 2.5824 | 9.06014 | 1.68007 | 0.0162462 | 3.27846e-05 | 1.55763e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1371.34 | 0.191598 | 5837.17ms | 65103 | 320 | 2.40793e+06 | 45274.8 | 0.0399319 | 3.70795 | 11.3507 | 1.90469 | 0.00887642 | 5.87051e-05 | 3.02405e-05 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15247.2 | 0.360905 | 1237.59ms | 78778 | 1280 | 404783 | 4927.35 | 0.371627 | 0.333706 | 1.1357 | 0.180063 | 2.8839e-05 | 7.17007e-06 | 3.87759e-06 | 1(Win) | true |
| Glaze | 4469.24 | 0.198267 | 2431.34ms | 78778 | 1280 | 1.42186e+06 | 16810.2 | 0.19131 | 1.13302 | 3.0214 | 0.489122 | 0.000340444 | 2.43168e-05 | 8.96507e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15461.5 | 0.18861 | 1231.95ms | 78778 | 4890 | 410720 | 4859.09 | 0.172856 | 0.330397 | 1.12873 | 0.178527 | 2.64054e-05 | 6.99592e-06 | 2.83731e-06 | 1(Win) | true |
| Glaze | 4979.21 | 0.118053 | 2260.64ms | 78778 | 4890 | 1.5515e+06 | 15088.4 | 0.0430852 | 1.01539 | 2.95713 | 0.474155 | 0.000343151 | 2.13668e-05 | 1.1518e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2526.98 | 0.124228 | 1182.72ms | 11812 | 1280 | 39255.1 | 4457.82 | 0.174161 | 2.03004 | 9.46583 | 1.77603 | 0.0043396 | 2.98954e-05 | 9.78877e-06 | 1(Win) | true |
| Glaze | 1784.46 | 0.19173 | 1369.63ms | 11812 | 640 | 93755.7 | 6312.74 | 0.0753611 | 2.84341 | 13.8212 | 2.68392 | 0.00226147 | 1.8387e-05 | 3.30702e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1714.42 | 0.0752835 | 1393.76ms | 11812 | 2560 | 62639.7 | 6570.6 | 0.219598 | 2.99141 | 14.6567 | 2.44188 | 0.00573702 | 4.04779e-05 | 1.68989e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1073.76 | 0.0594186 | 1784.59ms | 11812 | 4890 | 190015 | 10491 | 0.170529 | 4.76395 | 20.3222 | 3.36455 | 0.00818976 | 9.0269e-05 | 4.50999e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2924.83 | 0.362431 | 1171.67ms | 11812 | 160 | 31175.7 | 3851.44 | 0.0408771 | 1.74877 | 8.53471 | 1.55867 | 0.00321178 | 1.48154e-05 | 1.58737e-06 | 1(Win) | true |
| Glaze | 2017.52 | 0.218434 | 1347.53ms | 11812 | 640 | 95198.9 | 5583.49 | 0.0372892 | 2.51911 | 12.71 | 2.43481 | 0.00129093 | 1.12439e-05 | 5.29123e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 1889 | 0.0790339 | 1382.53ms | 11812 | 2560 | 56865.4 | 5963.35 | 0.00188656 | 2.7304 | 13.7074 | 2.22079 | 0.004666 | 2.54971e-05 | 7.93684e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1147.09 | 0.062229 | 1774.27ms | 11812 | 4890 | 182617 | 9820.29 | 0.0438718 | 4.44642 | 19.4824 | 3.17482 | 0.00666173 | 3.0661e-05 | 1.00414e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11781.4 | 0.133885 | 821.785ms | 11812 | 4890 | 8013.64 | 956.155 | 0.00356677 | 0.45328 | 2.12978 | 0.294277 | 0.000129119 | 1.9373e-05 | 6.44037e-06 | 1(Win) | true |
| Glaze | 3878.62 | 0.102187 | 1026.41ms | 11812 | 4890 | 43071.5 | 2904.33 | 0.126479 | 1.343 | 5.64045 | 0.823823 | 0.000432197 | 7.60206e-05 | 4.88221e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12995.9 | 0.248272 | 816.364ms | 11812 | 1280 | 5927.94 | 866.799 | 0.192257 | 0.414021 | 2.08119 | 0.283356 | 8.69746e-05 | 3.34009e-05 | 1.38895e-05 | 1(Win) | true |
| Glaze | 4393.03 | 0.110539 | 985.576ms | 11812 | 4890 | 39288 | 2564.24 | 0.0312122 | 1.18657 | 5.37437 | 0.765324 | 0.000483166 | 3.1215e-05 | 1.19285e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3691.84 | 0.136695 | 1392.57ms | 25388 | 1280 | 102869 | 6558.21 | 0.119305 | 1.38957 | 6.4624 | 1.23048 | 0.00331379 | 1.41245e-05 | 4.21582e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2970.78 | 0.136127 | 1550.46ms | 25388 | 160 | 19693.5 | 8150.01 | 0.000690179 | 1.71116 | 8.06346 | 1.30109 | 0.00423084 | 6.89302e-06 | 7.38538e-07 | 2(Loss) | true |
| Glaze | 2349.81 | 0.164444 | 1757.08ms | 25388 | 640 | 183741 | 10303.8 | 0.0964433 | 2.16548 | 9.67449 | 1.90256 | 0.00560519 | 2.84953e-05 | 1.1632e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2214.54 | 0.128917 | 1835.55ms | 25388 | 1280 | 254285 | 10933.2 | 0.0105053 | 2.31668 | 10.0812 | 1.59376 | 0.00354003 | 3.83424e-05 | 1.73556e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3981.39 | 0.0854319 | 1395.35ms | 25388 | 2560 | 69098.4 | 6081.27 | 0.0282743 | 1.27902 | 6.03029 | 1.13022 | 0.00308376 | 1.03241e-05 | 2.35409e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3175.82 | 0.0678776 | 1548.05ms | 25388 | 2560 | 68554.9 | 7623.82 | 0.00419617 | 1.61042 | 7.64093 | 1.20269 | 0.00401349 | 2.74644e-05 | 1.52939e-05 | 2(Loss) | true |
| Glaze | 2530.38 | 0.064759 | 1737.34ms | 25388 | 2560 | 98293.8 | 9568.49 | 0.0734925 | 2.03055 | 9.12904 | 1.78139 | 0.0051393 | 3.38804e-05 | 1.75403e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2317.79 | 0.0565931 | 1836.75ms | 25388 | 4890 | 170902 | 10446.1 | 0.108889 | 2.19905 | 9.69167 | 1.50634 | 0.00328086 | 2.41165e-05 | 9.80287e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16049.3 | 0.1197 | 924.071ms | 31235 | 2560 | 12635.8 | 1856.04 | 0.0390254 | 0.32269 | 1.44117 | 0.244694 | 0.000126786 | 1.81587e-05 | 9.3795e-06 | 1(Win) | true |
| Glaze | 5193.37 | 0.0654419 | 1311.31ms | 31235 | 4890 | 68897.7 | 5735.78 | 0.36704 | 0.981679 | 3.70453 | 0.654298 | 0.0022327 | 2.83555e-05 | 1.7448e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16398 | 0.166811 | 914.142ms | 31235 | 640 | 5876.68 | 1816.57 | 0.185445 | 0.315597 | 1.42296 | 0.240499 | 9.92977e-05 | 5.60269e-06 | 1.75084e-06 | 1(Win) | true |
| Glaze | 5783.12 | 0.111946 | 1253.89ms | 31235 | 1280 | 42558.1 | 5150.85 | 0.0875621 | 0.896422 | 3.58447 | 0.627565 | 0.00224545 | 1.4482e-05 | 6.07792e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2480 | 0.0402045 | 4909.31ms | 108313 | 4890 | 1.37124e+06 | 41651.3 | 0.00319742 | 2.04188 | 8.69621 | 1.76492 | 0.00293055 | 2.26848e-05 | 1.26725e-05 | 1(Win) | true |
| Glaze | 2286.17 | 0.0766188 | 5256.61ms | 108313 | 4890 | 5.86034e+06 | 45182.6 | 0.109697 | 2.21422 | 10.5617 | 1.88794 | 0.00279159 | 3.13188e-05 | 1.9039e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1934.15 | 0.198934 | 6058.45ms | 108313 | 160 | 1.806e+06 | 53406 | 0.00737223 | 2.61436 | 12.0538 | 2.14476 | 0.00299733 | 1.96191e-05 | 1.09059e-05 | 3(Loss) | true |
| simdjson (ondemand) | 715.638 | 0.0549515 | 7764.23ms | 108313 | 2560 | 1.61055e+07 | 144340 | 0.107351 | 7.04649 | 30.9486 | 4.41788 | 0.00408001 | 0.000104396 | 6.7354e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2935.5 | 0.04384 | 4461.86ms | 108313 | 4890 | 1.16371e+06 | 35188.3 | 0.0983328 | 1.7355 | 7.90885 | 1.58204 | 0.00248226 | 1.53044e-05 | 8.60001e-06 | 1(Win) | true |
| Glaze | 2565.39 | 0.115344 | 4938.31ms | 108313 | 2560 | 5.52184e+06 | 40264.9 | 0.106769 | 1.96712 | 9.83716 | 1.72039 | 0.00247237 | 1.18147e-05 | 6.34013e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2189.32 | 0.0423657 | 5646.17ms | 108313 | 4890 | 1.9538e+06 | 47181.5 | 0.296504 | 2.31351 | 11.2654 | 1.96154 | 0.00256734 | 2.03436e-05 | 1.33918e-05 | 3(Loss) | true |
| simdjson (ondemand) | 745.956 | 0.0638927 | 7551.47ms | 108313 | 2560 | 2.0039e+07 | 138474 | 0.0458137 | 6.77081 | 30.2844 | 4.26578 | 0.00328393 | 5.13269e-05 | 3.61979e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16501.4 | 0.112344 | 1372.17ms | 108313 | 1280 | 63303.9 | 6259.79 | 0.0122573 | 0.308153 | 1.46189 | 0.198342 | 0.000174891 | 4.10414e-06 | 1.39209e-06 | 1(Win) | true |
| Glaze | 4788.32 | 0.0771984 | 2903.79ms | 108313 | 4890 | 1.35619e+06 | 21572.4 | 0.0729119 | 1.06019 | 3.26116 | 0.410874 | 0.000279735 | 1.53932e-05 | 7.0556e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16638.7 | 0.0554468 | 1366.6ms | 108313 | 4890 | 57940.9 | 6208.15 | 0.0821035 | 0.305755 | 1.45658 | 0.197151 | 0.000165813 | 5.42055e-06 | 2.28453e-06 | 1(Win) | true |
| Glaze | 5184.31 | 0.0878299 | 2732.6ms | 108313 | 4890 | 1.49752e+06 | 19924.6 | 0.0462574 | 0.979958 | 3.21806 | 0.400866 | 0.000272193 | 2.27282e-05 | 1.33881e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3540.89 | 0.0714243 | 5687.85ms | 183677 | 2560 | 3.19607e+06 | 49470.1 | 0.0982563 | 1.43073 | 6.58341 | 1.31983 | 0.00163051 | 1.59204e-05 | 9.15968e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2974.9 | 0.0851214 | 6646.32ms | 183677 | 1280 | 3.21554e+06 | 58882.1 | 0.231951 | 1.70795 | 7.88234 | 1.33635 | 0.00185149 | 1.84299e-05 | 9.84235e-06 | 2(Loss) | true |
| Glaze | 2563.97 | 0.115927 | 7576.51ms | 183677 | 1280 | 8.02897e+06 | 68319 | 0.0816221 | 1.97022 | 9.22717 | 1.72705 | 0.0030796 | 2.38445e-05 | 1.34152e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1174.09 | 0.192318 | 7973.59ms | 183677 | 320 | 2.63447e+07 | 149194 | 0.125817 | 4.26561 | 18.772 | 2.62917 | 0.00237713 | 5.41201e-05 | 2.55884e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4013.27 | 0.15306 | 5271.81ms | 183677 | 640 | 2.85639e+06 | 43647.2 | 0.0359001 | 1.25661 | 6.11751 | 1.21146 | 0.00150735 | 6.67782e-06 | 3.47077e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3304.74 | 0.0455269 | 6194.91ms | 183677 | 4890 | 2.8476e+06 | 53005.1 | 0.0811014 | 1.53271 | 7.42117 | 1.22913 | 0.00166998 | 8.23776e-06 | 3.77096e-06 | 2(Loss) | true |
| Glaze | 2783.39 | 0.0908655 | 7220.17ms | 183677 | 2560 | 8.37141e+06 | 62933.2 | 0.0623743 | 1.82011 | 8.80146 | 1.62889 | 0.0028898 | 1.20754e-05 | 6.29502e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1225.59 | 0.055178 | 7787.55ms | 183677 | 2560 | 1.59219e+07 | 142926 | 0.0777952 | 4.09437 | 18.3769 | 2.53877 | 0.00184294 | 2.02993e-05 | 1.1633e-05 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18613 | 0.074032 | 1842.78ms | 213963 | 2560 | 168626 | 10962.9 | 0.218798 | 0.275843 | 1.25997 | 0.22123 | 0.000216681 | 3.92883e-06 | 1.6431e-06 | 1(Win) | true |
| Glaze | 4835.27 | 0.0485991 | 4979.11ms | 213963 | 4890 | 2.05685e+06 | 42200.6 | 0.0312068 | 1.04733 | 3.63887 | 0.597758 | 0.000657381 | 2.95896e-05 | 1.43929e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18815.8 | 0.0683092 | 1821.26ms | 213963 | 2560 | 140486 | 10844.7 | 0.097215 | 0.271519 | 1.25751 | 0.220674 | 0.000218079 | 1.25168e-05 | 9.1119e-06 | 1(Win) | true |
| Glaze | 5541.73 | 0.22275 | 4419.14ms | 213963 | 320 | 2.15264e+06 | 36820.8 | 0.078147 | 0.906421 | 3.61276 | 0.591747 | 0.000660511 | 1.10124e-05 | 6.32411e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 801.239 | 0.121075 | 6793.31ms | 1834197 | 80 | 5.58938e+08 | 2.18315e+06 | 0.0415305 | 6.32109 | 26.9259 | 5.92556 | 0.0301554 | 0.0813295 | 0.00183885 | 1(Win) | true |
| Jsonifier (two-stage) | 734.395 | 0.0830034 | 7434.89ms | 1834197 | 160 | 6.2538e+08 | 2.38186e+06 | 0.370114 | 6.87638 | 31.6592 | 6.69969 | 0.0396764 | 0.145172 | 0.000819459 | 2(Loss) | true |
| Glaze | 691.119 | 0.134512 | 7877.87ms | 1834197 | 40 | 4.63626e+08 | 2.53101e+06 | 0.482615 | 7.27665 | 32.0086 | 6.49912 | 0.0355149 | 0.0815892 | 0.000167689 | 3(Loss) | true |
| simdjson (ondemand) | 590.849 | 0.1369 | 9249.74ms | 1834197 | 40 | 6.57063e+08 | 2.96053e+06 | 0.0339154 | 8.578 | 36.8602 | 6.23538 | 0.0412835 | 0.146824 | 0.000522259 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 883.445 | 0.0808189 | 6800.86ms | 1834197 | 160 | 4.09713e+08 | 1.98001e+06 | 0.284672 | 5.72197 | 23.9201 | 5.22004 | 0.0298412 | 0.0550519 | 0.000295841 | 1(Win) | true |
| Jsonifier (two-stage) | 808.459 | 0.101876 | 7423.97ms | 1834197 | 30 | 1.4576e+08 | 2.16366e+06 | 0.0499759 | 6.26948 | 28.6526 | 5.99382 | 0.0386984 | 0.119158 | 0.000149911 | 2(Loss) | true |
| Glaze | 761.767 | 0.107935 | 7865.17ms | 1834197 | 40 | 2.45715e+08 | 2.29628e+06 | 0.0833666 | 6.62538 | 28.9944 | 5.79293 | 0.0340193 | 0.0580723 | 8.5487e-05 | 3(Loss) | true |
| simdjson (ondemand) | 647.977 | 0.084022 | 9081.77ms | 1834197 | 160 | 8.23151e+08 | 2.69952e+06 | 0.0426104 | 7.81174 | 33.8345 | 5.52875 | 0.0363622 | 0.118529 | 0.000996761 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1347.73 | 0.0703054 | 8657.73ms | 1922245 | 160 | 1.46322e+08 | 1.36021e+06 | 0.449954 | 3.79261 | 12.3635 | 0.737464 | 0.000699163 | 0.0569785 | 0.000113887 | 1(Win) | true |
| Glaze | 648.641 | 0.197298 | 8346.68ms | 1833577 | 80 | 2.26321e+09 | 2.69585e+06 | 0.372826 | 7.9043 | 16.012 | 0.996521 | 0.00112414 | 0.0492653 | 0.000297745 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1342.47 | 0.0806783 | 8659.93ms | 1922245 | 160 | 1.94197e+08 | 1.36554e+06 | 0.106545 | 3.79819 | 12.3634 | 0.737426 | 0.000717768 | 0.0570136 | 0.000878563 | 1(Win) | true |
| Glaze | 656.462 | 0.185396 | 8371.95ms | 1833577 | 80 | 1.95105e+09 | 2.66373e+06 | 0.0442081 | 7.83347 | 16.0113 | 0.996381 | 0.00111002 | 0.049134 | 0.000113958 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2513.23 | 0.0920221 | 8669.22ms | 7351818 | 160 | 1.05446e+09 | 2.78973e+06 | 0.0676688 | 2.009 | 8.7799 | 1.70859 | 0.0107411 | 0.0605961 | 0.00169359 | 1(Win) | true |
| Jsonifier | 2424.31 | 0.0494026 | 8980.85ms | 7351818 | 160 | 3.26613e+08 | 2.89206e+06 | 0.183209 | 2.0733 | 9.17715 | 2.08567 | 0.00751671 | 0.0333782 | 0.000602713 | 2(Loss) | true |
| Glaze | 2172.22 | 0.0800055 | 10038ms | 7351818 | 160 | 1.06694e+09 | 3.22768e+06 | 0.0447803 | 2.33259 | 11.0339 | 2.24411 | 0.00908072 | 0.0331523 | 0.000433974 | 3(Loss) | true |
| simdjson (ondemand) | 2151.38 | 0.0902978 | 10157.5ms | 7351818 | 160 | 1.38558e+09 | 3.25896e+06 | 0.139963 | 2.34871 | 10.0974 | 1.59516 | 0.00996409 | 0.0608734 | 0.00108867 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2736.48 | 0.101175 | 8664.51ms | 7351818 | 80 | 5.37575e+08 | 2.56214e+06 | 0.062313 | 1.84628 | 8.02891 | 1.53231 | 0.0104871 | 0.0540882 | 0.000663795 | 1(Win) | true |
| Jsonifier | 2617.65 | 0.138166 | 9008.29ms | 7351818 | 30 | 4.10858e+08 | 2.67844e+06 | 0.0820165 | 1.92809 | 8.42725 | 1.90977 | 0.00738044 | 0.0268226 | 0.000852973 | 2(Loss) | true |
| simdjson (ondemand) | 2346.71 | 0.0859848 | 9979.2ms | 7351818 | 80 | 5.27965e+08 | 2.98769e+06 | 0.436765 | 2.15124 | 9.34252 | 1.41876 | 0.00875539 | 0.0535006 | 0.000422186 | 3(Loss) | true |
| Glaze | 2329.55 | 0.0803025 | 10034.8ms | 7351818 | 160 | 9.34592e+08 | 3.00969e+06 | 0.103229 | 2.17266 | 10.2816 | 2.06796 | 0.00868906 | 0.0272952 | 0.00196472 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5097.55 | 0.0557549 | 5841.88ms | 10018896 | 80 | 8.73721e+07 | 1.87438e+06 | 0.0339777 | 0.992539 | 3.46093 | 0.404708 | 0.000339107 | 0.0245813 | 0.00012325 | 1(Win) | true |
| Glaze | 3712.6 | 0.140313 | 7941.47ms | 9930228 | 40 | 5.12409e+08 | 2.55083e+06 | 0.345719 | 1.36135 | 4.21672 | 0.48471 | 0.00108257 | 0.0412821 | 0.00109768 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5084.54 | 0.0337144 | 5843.78ms | 10018896 | 160 | 6.42226e+07 | 1.87918e+06 | 0.178067 | 0.993 | 3.4609 | 0.404701 | 0.000342646 | 0.0245691 | 9.95881e-05 | 1(Win) | true |
| Glaze | 4084.69 | 0.0651625 | 7195.66ms | 9930228 | 160 | 3.65189e+08 | 2.31847e+06 | 0.0237113 | 1.24046 | 4.21647 | 0.484654 | 0.0010887 | 0.0220054 | 0.000123872 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 819.641 | 0.125484 | 6668.82ms | 1834197 | 80 | 5.73731e+08 | 2.13414e+06 | 0.112096 | 6.21253 | 26.5154 | 5.79855 | 0.0308742 | 0.082066 | 0.00026637 | 1(Win) | true |
| Jsonifier (two-stage) | 740.177 | 0.0795646 | 7342.57ms | 1834197 | 80 | 2.82847e+08 | 2.36325e+06 | 0.0247718 | 6.8034 | 31.2334 | 6.59811 | 0.0401875 | 0.145768 | 0.00034603 | 2(Loss) | true |
| Glaze | 693.675 | 0.0780188 | 7850.67ms | 1834197 | 160 | 6.19296e+08 | 2.52168e+06 | 0.0245083 | 7.28721 | 31.9795 | 6.48914 | 0.0355461 | 0.0818169 | 0.000344817 | 3(Loss) | true |
| simdjson (ondemand) | 586.947 | 0.142852 | 9271.7ms | 1834197 | 30 | 5.43735e+08 | 2.98021e+06 | 0.00276722 | 8.60374 | 36.8368 | 6.22577 | 0.0412352 | 0.147066 | 0.000215389 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 911.261 | 0.0919173 | 6675.32ms | 1834197 | 160 | 4.98105e+08 | 1.91957e+06 | 0.148436 | 5.56815 | 23.5352 | 5.10337 | 0.0299815 | 0.0557949 | 9.19101e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 823.361 | 0.107597 | 7328.99ms | 1834197 | 160 | 8.36054e+08 | 2.12449e+06 | 0.149777 | 6.15121 | 28.2523 | 5.90312 | 0.0392628 | 0.119815 | 0.00061084 | 2(Loss) | true |
| Glaze | 765.519 | 0.188884 | 7830.71ms | 1834197 | 40 | 7.45126e+08 | 2.28502e+06 | 0.488267 | 6.60924 | 28.9963 | 5.79307 | 0.0343001 | 0.0585777 | 0.00026667 | 3(Loss) | true |
| simdjson (ondemand) | 647.458 | 0.149261 | 9146.65ms | 1834197 | 30 | 4.87849e+08 | 2.70168e+06 | 0.0304335 | 7.78332 | 33.8388 | 5.52779 | 0.0364472 | 0.119242 | 8.68682e-05 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1319.39 | 0.0689977 | 8775.18ms | 1922245 | 80 | 7.35241e+07 | 1.38943e+06 | 0.165275 | 3.82818 | 12.3442 | 0.737465 | 0.000619113 | 0.0584975 | 0.000440475 | 1(Win) | true |
| Glaze | 641.919 | 0.126972 | 8508.37ms | 1833577 | 80 | 9.57067e+08 | 2.72407e+06 | 0.0414877 | 7.89368 | 16.0115 | 0.996581 | 0.0011158 | 0.082493 | 0.000241468 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1330.26 | 0.0503994 | 8760.89ms | 1922245 | 320 | 1.54364e+08 | 1.37807e+06 | 0.0574562 | 3.82195 | 12.344 | 0.737427 | 0.000614589 | 0.0584023 | 0.000176857 | 1(Win) | true |
| Glaze | 664.4 | 0.160356 | 8234.58ms | 1833577 | 80 | 1.42496e+09 | 2.6319e+06 | 0.200893 | 7.68649 | 16.0106 | 0.996384 | 0.0010765 | 0.049105 | 0.000113883 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2529.1 | 0.0872449 | 8639.03ms | 7351818 | 160 | 9.35959e+08 | 2.77222e+06 | 0.103649 | 1.98522 | 8.67325 | 1.68326 | 0.0107854 | 0.0606248 | 0.00144742 | 1(Win) | true |
| Jsonifier | 2481.76 | 0.151215 | 8848.5ms | 7351818 | 30 | 5.47493e+08 | 2.8251e+06 | 0.0931866 | 2.04273 | 9.03079 | 2.04821 | 0.00761967 | 0.033598 | 0.00132975 | 2(Loss) | true |
| Glaze | 2156.36 | 0.0701628 | 10120.8ms | 7351818 | 80 | 4.16341e+08 | 3.25142e+06 | 0.0330292 | 2.33806 | 11.0268 | 2.24188 | 0.00908256 | 0.0333695 | 0.000141275 | 3(Loss) | true |
| simdjson (ondemand) | 2130.59 | 0.194931 | 10253.7ms | 7351818 | 40 | 1.64592e+09 | 3.29075e+06 | 0.0190964 | 2.37324 | 10.0918 | 1.59275 | 0.0100154 | 0.0609442 | 0.00325542 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2780.25 | 0.0838677 | 8629.47ms | 7351818 | 40 | 1.78924e+08 | 2.5218e+06 | 0.192924 | 1.81658 | 7.929 | 1.50967 | 0.0105637 | 0.0541514 | 0.000712878 | 1(Win) | true |
| Jsonifier | 2699.89 | 0.100144 | 8839.89ms | 7351818 | 80 | 5.41051e+08 | 2.59686e+06 | 0.0280249 | 1.87505 | 8.28721 | 1.87477 | 0.00741975 | 0.027077 | 0.000515141 | 2(Loss) | true |
| simdjson (ondemand) | 2344.54 | 0.123879 | 10045.3ms | 7351818 | 40 | 5.48948e+08 | 2.99046e+06 | 0.0139039 | 2.15353 | 9.34402 | 1.41869 | 0.0087663 | 0.0536058 | 0.00179932 | 3(Loss) | true |
| Glaze | 2298.29 | 0.186229 | 10204.2ms | 7351818 | 30 | 9.6827e+08 | 3.05064e+06 | 0.136147 | 2.17464 | 10.2819 | 2.06798 | 0.00876082 | 0.0275069 | 0.000897887 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4760.67 | 0.108313 | 6244.63ms | 10018896 | 160 | 7.56115e+08 | 2.00702e+06 | 0.0648746 | 1.06214 | 3.43761 | 0.404014 | 0.000236352 | 0.0246125 | 0.00154435 | 1(Win) | true |
| Glaze | 2977.06 | 0.161708 | 9987.19ms | 9930228 | 40 | 1.05844e+09 | 3.18106e+06 | 0.0834764 | 1.69517 | 4.21669 | 0.484739 | 0.00106932 | 0.0753744 | 0.0162219 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4833.38 | 0.0665793 | 6203.11ms | 10018896 | 160 | 2.77164e+08 | 1.97683e+06 | 0.0999167 | 1.05489 | 3.43758 | 0.404007 | 0.00023495 | 0.02464 | 0.000353631 | 1(Win) | true |
| Glaze | 4091.43 | 0.0865354 | 7202.56ms | 9930228 | 80 | 3.20957e+08 | 2.31465e+06 | 0.0524724 | 1.23525 | 4.21632 | 0.484654 | 0.00111033 | 0.0220355 | 0.000609454 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1612.01 | 0.0563716 | 7168.21ms | 461466 | 1280 | 3.03164e+07 | 273007 | 0.019678 | 3.13276 | 14.7673 | 2.94341 | 0.00683674 | 0.0331127 | 3.12946e-05 | 1(Win) | true |
| Glaze | 1185.31 | 0.0807921 | 9680.51ms | 461466 | 640 | 5.75886e+07 | 371287 | 0.00120062 | 4.26167 | 19.1483 | 3.78675 | 0.0127289 | 0.0276589 | 6.76614e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1132.78 | 0.0905667 | 5033.4ms | 461466 | 320 | 3.96164e+07 | 388503 | 0.0925448 | 4.44941 | 19.8289 | 3.51211 | 0.0175387 | 0.0718531 | 4.96041e-05 | 3(Loss) | true |
| simdjson (ondemand) | 818.267 | 0.0881054 | 6984.64ms | 461466 | 640 | 1.43706e+08 | 537830 | 0.0759674 | 6.1454 | 25.5576 | 4.45151 | 0.0106381 | 0.0831124 | 0.000163639 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2534.3 | 0.0619629 | 6277.45ms | 461466 | 1280 | 1.48197e+07 | 173653 | 0.135307 | 1.98898 | 10.3841 | 1.97127 | 0.00485455 | 0.00412692 | 1.92373e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1546.85 | 0.207041 | 9241.23ms | 461466 | 80 | 2.77578e+07 | 284506 | 0.179511 | 3.27363 | 15.4508 | 2.54139 | 0.0150416 | 0.0250327 | 1.70652e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1543.7 | 0.0878065 | 9154.93ms | 461466 | 640 | 4.0104e+07 | 285087 | 0.0888736 | 3.26895 | 15.2034 | 2.89846 | 0.0107623 | 0.00890572 | 3.01282e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1026.76 | 0.316341 | 6360.65ms | 461466 | 80 | 1.47077e+08 | 428619 | 0.245329 | 4.89061 | 21.4641 | 3.52344 | 0.00331666 | 0.0311601 | 4.17149e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13915.1 | 0.110692 | 3931.95ms | 461466 | 640 | 784360 | 31626.6 | 0.0137573 | 0.362945 | 1.61357 | 0.233608 | 0.000599056 | 0.00860184 | 6.7719e-06 | 1(Win) | true |
| Glaze | 3600.25 | 0.141819 | 6690.93ms | 461466 | 1280 | 3.84675e+07 | 122238 | 0.410594 | 1.39322 | 5.36925 | 0.79156 | 0.00990043 | 0.0417635 | 3.40119e-05 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13923.8 | 0.120662 | 3942.77ms | 461466 | 640 | 930863 | 31606.8 | 0.0796992 | 0.362951 | 1.61249 | 0.233365 | 0.000588075 | 0.00823393 | 8.39377e-06 | 1(Win) | true |
| Glaze | 3952.87 | 0.145812 | 6100.78ms | 461466 | 2560 | 6.74651e+07 | 111334 | 0.180845 | 1.2731 | 5.35473 | 0.788156 | 0.00997021 | 0.00927129 | 5.02441e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2218.99 | 0.116619 | 8214.22ms | 728486 | 320 | 4.26599e+07 | 313088 | 0.172354 | 2.27576 | 10.9573 | 2.17011 | 0.00462403 | 0.0331487 | 0.000165274 | 1(Win) | true |
| Jsonifier (two-stage) | 1667 | 0.129708 | 5440.19ms | 728486 | 80 | 2.33774e+07 | 416759 | 0.205877 | 3.03342 | 13.4491 | 2.31701 | 0.0125088 | 0.0635395 | 5.99359e-05 | 2(Loss) | true |
| Glaze | 1395.61 | 0.123032 | 6457.23ms | 728486 | 160 | 6.00165e+07 | 497804 | 0.209826 | 3.61717 | 14.8008 | 2.94196 | 0.0102144 | 0.0313672 | 0.000126976 | 3(Loss) | true |
| simdjson (ondemand) | 1234.24 | 0.171003 | 7222.11ms | 728486 | 320 | 2.96485e+08 | 562889 | 0.371376 | 4.05296 | 16.6976 | 2.84294 | 0.00742102 | 0.0699255 | 0.000260819 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3267.79 | 0.125401 | 7351.24ms | 728486 | 320 | 2.27449e+07 | 212602 | 0.0972318 | 1.54241 | 8.18403 | 1.55517 | 0.00341228 | 0.00889601 | 2.13971e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.99 | 0.0606061 | 9970.6ms | 728486 | 1280 | 4.61699e+07 | 313370 | 0.0741411 | 2.28262 | 10.6703 | 1.70079 | 0.0108824 | 0.0288706 | 5.51486e-05 | 2(Loss) | true |
| Glaze | 1708.64 | 0.17412 | 6142.79ms | 728486 | 160 | 8.01968e+07 | 406602 | 0.0156243 | 2.96662 | 12.3013 | 2.37938 | 0.00877032 | 0.011865 | 2.19462e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1562.44 | 0.1507 | 6551.11ms | 728486 | 320 | 1.43685e+08 | 444651 | 0.0623914 | 3.21783 | 14.1064 | 2.25544 | 0.00259473 | 0.0319342 | 0.000133526 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14375.6 | 0.044801 | 6343.32ms | 837491 | 4890 | 3.02965e+06 | 55559 | 0.222472 | 0.352911 | 1.40067 | 0.242219 | 0.000473436 | 0.0161712 | 2.43311e-05 | 1(Win) | true |
| Glaze | 3874.77 | 0.115842 | 5476.8ms | 837491 | 1280 | 7.29809e+07 | 206127 | 0.029579 | 1.3002 | 4.56912 | 0.770719 | 0.00620552 | 0.0570846 | 5.21433e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14511.3 | 0.223822 | 6313.04ms | 837491 | 40 | 607031 | 55039.3 | 0.0679673 | 0.349971 | 1.40008 | 0.242085 | 0.000469318 | 0.0160659 | 1.81494e-05 | 1(Win) | true |
| Glaze | 4440.62 | 0.0684618 | 9602.25ms | 837491 | 2560 | 3.88159e+07 | 179861 | 0.0404036 | 1.1352 | 4.56028 | 0.768648 | 0.00620113 | 0.0170835 | 7.51202e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8391.46 | 0.15862 | 6070.53ms | 466906 | 320 | 2.26698e+06 | 53063 | 0.00477639 | 0.605365 | 3.03638 | 0.422091 | 0.000973811 | 1.11773e-05 | 7.20836e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 8352.73 | 0.0716765 | 6084.39ms | 466906 | 1280 | 1.86881e+06 | 53309 | 0.102013 | 0.604255 | 3.03329 | 0.421434 | 0.000939912 | 7.02765e-06 | 3.16579e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6843.87 | 0.0386542 | 7279.35ms | 466906 | 2560 | 1.61916e+06 | 65062.1 | 0.0986706 | 0.737814 | 3.47604 | 0.378539 | 0.000714164 | 9.47561e-06 | 4.54956e-06 | 3(Loss) | true |
| Glaze | 3386.72 | 0.0575343 | 7120.76ms | 466906 | 1280 | 7.32429e+06 | 131477 | 0.0116282 | 1.50355 | 5.74476 | 0.997128 | 0.00171178 | 2.21287e-05 | 1.64129e-05 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8545.09 | 0.0666826 | 6032.98ms | 466906 | 640 | 772735 | 52109 | 0.060892 | 0.591433 | 2.99791 | 0.413554 | 0.000911901 | 1.88408e-06 | 1.11104e-06 | 1(Win) | true |
| Jsonifier | 8503.94 | 0.0340051 | 6039.36ms | 466906 | 4890 | 1.5503e+06 | 52361.2 | 0.0906209 | 0.592778 | 2.99907 | 0.413777 | 0.000939981 | 4.24629e-06 | 3.24505e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7030.01 | 0.0333712 | 7136.84ms | 466906 | 2560 | 1.14375e+06 | 63339.3 | 0.0806225 | 0.718543 | 3.43396 | 0.369445 | 0.000714284 | 1.95101e-06 | 8.95188e-07 | 3(Loss) | true |
| Glaze | 3437.13 | 0.0616464 | 7076.03ms | 466906 | 320 | 2.04095e+06 | 129549 | 0.068926 | 1.48174 | 5.69176 | 0.985533 | 0.0016122 | 2.24215e-06 | 9.50405e-07 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9467.03 | 0.151084 | 7090.91ms | 631514 | 320 | 2.95614e+06 | 63616.4 | 0.0706881 | 0.528055 | 2.67674 | 0.327108 | 0.000625001 | 4.73069e-05 | 1.45979e-06 | 1(Win) | true |
| Jsonifier | 9314.67 | 0.0952353 | 7143.01ms | 631514 | 1280 | 4.8533e+06 | 64657 | 0.575609 | 0.540765 | 2.67674 | 0.327108 | 0.000989193 | 4.37478e-05 | 2.71669e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8268.13 | 0.199608 | 8050.24ms | 631514 | 80 | 1.69121e+06 | 72841 | 0.160726 | 0.615112 | 2.90442 | 0.295473 | 0.000538151 | 2.51578e-05 | 7.46223e-06 | 3(Loss) | true |
| Glaze | 4008.03 | 0.107691 | 8008.65ms | 631514 | 80 | 2.09487e+06 | 150263 | 0.00614793 | 1.26206 | 5.34723 | 0.944654 | 0.00127357 | 2.17929e-05 | 1.54787e-05 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9593.41 | 0.0916159 | 7065.96ms | 631514 | 1280 | 4.2342e+06 | 62778.3 | 0.310491 | 0.526658 | 2.65194 | 0.321348 | 0.000792304 | 4.80814e-05 | 3.83627e-06 | 1(Win) | true |
| Jsonifier | 9552.47 | 0.0487366 | 7109.35ms | 631514 | 4890 | 4.61695e+06 | 63047.5 | 0.270349 | 0.524524 | 2.65194 | 0.321348 | 0.000716971 | 5.00715e-05 | 8.17006e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8508.54 | 0.093298 | 7951.98ms | 631514 | 320 | 1.39557e+06 | 70782.8 | 0.00335103 | 0.602618 | 2.87999 | 0.290641 | 0.000573399 | 1.34894e-05 | 2.87504e-06 | 3(Loss) | true |
| Glaze | 4050.25 | 0.0221248 | 8003.25ms | 631514 | 2560 | 2.77078e+06 | 148697 | 0.0132765 | 1.25192 | 5.31281 | 0.936974 | 0.00121873 | 8.93624e-06 | 4.39173e-06 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1988.45 | 0.114391 | 5898.08ms | 466906 | 1280 | 8.39893e+07 | 223932 | 0.176536 | 2.53987 | 7.33108 | 1.40113 | 0.0115044 | 0.0160022 | 0.000120159 | 1(Win) | true |
| Glaze | 1864.68 | 0.105354 | 6308.91ms | 466906 | 640 | 4.05068e+07 | 238795 | 0.118573 | 2.71834 | 10.058 | 1.80149 | 0.0121299 | 0.0120931 | 9.16974e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1614.48 | 0.370143 | 7268.12ms | 466906 | 30 | 3.12649e+07 | 275802 | 0.0539709 | 3.12825 | 9.74104 | 1.58398 | 0.0205671 | 0.0304518 | 0.000118939 | 3(Loss) | true |
| simdjson (ondemand) | 923.668 | 0.267804 | 6244.1ms | 466906 | 80 | 1.33338e+08 | 482074 | 0.0897269 | 5.44121 | 18.6804 | 3.16318 | 0.0129579 | 0.045863 | 0.000150619 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2594.7 | 0.172859 | 5339.62ms | 466906 | 640 | 5.63179e+07 | 171610 | 0.0308791 | 1.955 | 5.84017 | 1.05907 | 0.00817967 | 0.00265717 | 7.00589e-05 | 1(Win) | true |
| Glaze | 2343.32 | 0.118064 | 5780.94ms | 466906 | 640 | 3.22112e+07 | 190019 | 0.0958212 | 2.16177 | 8.57405 | 1.45943 | 0.0092106 | 0.00232992 | 2.37099e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2012.75 | 0.114382 | 6654.96ms | 466906 | 1280 | 8.19606e+07 | 221228 | 0.169043 | 2.50735 | 8.25312 | 1.24285 | 0.0165007 | 0.00772285 | 5.50348e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1043.33 | 0.174068 | 5876.87ms | 466906 | 160 | 8.83028e+07 | 426784 | 0.102181 | 4.82193 | 17.284 | 2.84229 | 0.00942457 | 0.0110402 | 4.79352e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16888 | 0.116326 | 3446.95ms | 475954 | 4890 | 4.78005e+06 | 26877.3 | 0.13882 | 0.298485 | 1.08677 | 0.142858 | 0.000265044 | 0.000930292 | 1.33539e-05 | 1(Win) | true |
| Glaze | 6090.65 | 0.127587 | 8220.61ms | 475954 | 4890 | 4.42107e+07 | 74524.9 | 0.362706 | 0.826344 | 2.36368 | 0.337182 | 0.000347806 | 0.0161668 | 3.39935e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16928.4 | 0.24834 | 3428.78ms | 475954 | 1280 | 5.67545e+06 | 26813.2 | 0.0277888 | 0.297354 | 1.08564 | 0.142608 | 0.000266127 | 0.000751317 | 1.7158e-05 | 1(Win) | true |
| Glaze | 6747.67 | 0.156856 | 7476.33ms | 475954 | 4890 | 5.44419e+07 | 67268.4 | 0.0752011 | 0.748035 | 2.35134 | 0.334375 | 0.000333424 | 0.00181477 | 3.05575e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2505.6 | 0.111928 | 6359.66ms | 631514 | 1280 | 9.26461e+07 | 240365 | 0.00847122 | 2.01829 | 6.13699 | 1.13865 | 0.00798222 | 0.0198541 | 0.000317994 | 1(Win) | true |
| Glaze | 2015.91 | 0.112851 | 7851.79ms | 631514 | 640 | 7.2747e+07 | 298753 | 0.0152857 | 2.50052 | 9.08601 | 1.66295 | 0.0105978 | 0.0183292 | 0.0001264 | 2(Loss) | true |
| Jsonifier (two-stage) | 1987.19 | 0.179599 | 7940.64ms | 631514 | 320 | 9.48072e+07 | 303070 | 0.383544 | 2.53684 | 7.7693 | 1.22079 | 0.0163009 | 0.0348356 | 0.000216132 | 3(Loss) | true |
| simdjson (ondemand) | 1225.56 | 0.125979 | 6371.74ms | 631514 | 640 | 2.45288e+08 | 491416 | 0.282202 | 4.12939 | 14.1519 | 2.35614 | 0.00955774 | 0.0438126 | 0.000600746 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3187.12 | 0.131493 | 5797.96ms | 631514 | 1280 | 7.90289e+07 | 188966 | 0.00613332 | 1.58718 | 5.03688 | 0.886626 | 0.00581497 | 0.00534637 | 6.11267e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2470.31 | 0.1588 | 7245.64ms | 631514 | 320 | 4.79642e+07 | 243799 | 0.422303 | 2.06801 | 6.66919 | 0.968856 | 0.0135343 | 0.0139371 | 0.000130916 | 2(Loss) | true |
| Glaze | 2425.81 | 0.124107 | 7276.86ms | 631514 | 640 | 6.07607e+07 | 248271 | 0.170106 | 2.07854 | 7.98776 | 1.41114 | 0.00837593 | 0.00422112 | 6.59279e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1391.7 | 0.256833 | 5988.34ms | 631514 | 40 | 4.94126e+07 | 432751 | 0.0268847 | 3.63316 | 13.1132 | 2.11688 | 0.00687522 | 0.015433 | 9.28325e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16608.2 | 0.309751 | 5035.9ms | 716365 | 160 | 2.59757e+06 | 41134.9 | 0.273968 | 0.303373 | 1.08505 | 0.173199 | 0.000223202 | 0.00640094 | 7.6602e-06 | 1(Win) | true |
| Glaze | 4142.51 | 0.170782 | 8901.02ms | 716365 | 640 | 5.07698e+07 | 164919 | 0.0343261 | 1.22113 | 2.81742 | 0.4635 | 0.000532652 | 0.0450889 | 7.82859e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16632.9 | 0.861473 | 5006.36ms | 716365 | 30 | 3.75608e+06 | 41073.8 | 0.094472 | 0.304096 | 1.08434 | 0.173036 | 0.000224885 | 0.00613905 | 9.0131e-05 | 1(Win) | true |
| Glaze | 4777.43 | 0.123968 | 7711.06ms | 716365 | 1280 | 4.02261e+07 | 143001 | 0.0703169 | 1.06155 | 2.80754 | 0.461218 | 0.000533235 | 0.00643849 | 3.6976e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2949.37 | 0.179638 | 817.822ms | 2632 | 2560 | 5983.41 | 851.054 | 0.0914847 | 1.81378 | 6.81497 | 1.33853 | 0.000767151 | 5.32805e-05 | 5.49131e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2021.05 | 0.115873 | 858.622ms | 2632 | 4890 | 10127.3 | 1241.96 | 0.152946 | 2.58594 | 10.4593 | 1.71657 | 0.00100929 | 7.08598e-05 | 1.39855e-05 | 2(Loss) | true |
| Glaze | 1935.88 | 0.079602 | 863.488ms | 2632 | 4890 | 5209.2 | 1296.6 | 0.385343 | 2.71396 | 11.3583 | 2.13336 | 0.00109273 | 5.79621e-05 | 1.5384e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1384.13 | 0.188505 | 916.461ms | 2632 | 320 | 3739.48 | 1813.46 | 0.0510334 | 3.73675 | 12.9616 | 2.2234 | 0.00477417 | 0.000144852 | 5.58036e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3589.47 | 0.147989 | 809.822ms | 2632 | 80 | 85.6758 | 699.288 | 0.0232325 | 1.48959 | 5.79293 | 1.07827 | 0.000759878 | 2.84954e-05 | 4.74924e-06 | 1(Win) | true |
| Glaze | 2443.72 | 0.165024 | 844.382ms | 2632 | 320 | 919.419 | 1027.15 | 0.0974516 | 2.15402 | 9.47948 | 1.69947 | 0.00149364 | 5.10543e-05 | 7.12386e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2340.88 | 0.19252 | 849.391ms | 2632 | 40 | 170.461 | 1072.28 | 0.143982 | 2.24606 | 9.43731 | 1.45631 | 0.00114932 | 3.79939e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1693.06 | 0.134441 | 890.953ms | 2632 | 1280 | 5085.15 | 1482.57 | 0.0842422 | 3.10053 | 11.2223 | 1.82257 | 0.00185428 | 6.7083e-05 | 8.90483e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9070.02 | 0.491903 | 759.095ms | 2632 | 160 | 296.506 | 276.744 | 0.00225846 | 0.63964 | 1.94947 | 0.31193 | 0.000674392 | 1.66223e-05 | 0 | 1(Win) | true |
| Glaze | 3397.47 | 0.178777 | 803.316ms | 2632 | 2560 | 4466.04 | 738.806 | 0.127893 | 1.57176 | 4.75874 | 0.740122 | 0.000391961 | 4.49694e-05 | 8.16276e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10667 | 0.261182 | 749.504ms | 2632 | 2560 | 966.971 | 235.312 | 0.166612 | 0.556803 | 1.74071 | 0.263719 | 0.000383204 | 2.28557e-05 | 2.07779e-06 | 1(Win) | true |
| Glaze | 3621.66 | 0.187311 | 794.276ms | 2632 | 2560 | 4314.43 | 693.073 | 0.0563931 | 1.48447 | 4.30509 | 0.647417 | 0.000386766 | 3.93296e-05 | 1.27636e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3091.16 | 0.135798 | 837.267ms | 3370 | 30 | 59.8034 | 1039.7 | 0.0224373 | 1.69834 | 6.87389 | 1.33947 | 0.000613254 | 9.8912e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 2365.26 | 0.0890974 | 871.471ms | 3370 | 4890 | 7167.08 | 1358.79 | 0.127622 | 2.19848 | 9.03353 | 1.46469 | 0.000899553 | 6.42018e-05 | 1.49278e-05 | 2(Loss) | true |
| Glaze | 2043.58 | 0.113575 | 899.189ms | 3370 | 2560 | 8167.33 | 1572.67 | 0.0361528 | 2.54051 | 10.7683 | 2.06172 | 0.0015523 | 4.52059e-05 | 4.75241e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1712.52 | 0.0991983 | 931.375ms | 3370 | 2560 | 8872.28 | 1876.69 | 0.148357 | 3.02745 | 10.5119 | 1.77181 | 0.00370514 | 8.65866e-05 | 3.80193e-05 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3625.32 | 0.169688 | 831.325ms | 3370 | 1280 | 2896.53 | 886.51 | 0.00149813 | 1.46099 | 6.07419 | 1.1362 | 0.000597645 | 3.01372e-05 | 1.62277e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2682.93 | 0.18287 | 866.533ms | 3370 | 1280 | 6142.35 | 1197.9 | 0.00156521 | 1.95427 | 8.23531 | 1.26142 | 0.000629868 | 3.66283e-05 | 3.7092e-06 | 2(Loss) | true |
| Glaze | 2471.25 | 0.137124 | 871.481ms | 3370 | 160 | 508.83 | 1300.51 | 0.0389423 | 2.11574 | 9.29733 | 1.72285 | 0.00106825 | 2.22552e-05 | 3.7092e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2080.65 | 0.118453 | 899.858ms | 3370 | 2560 | 8570.31 | 1544.65 | 0.0438954 | 2.5063 | 9.04481 | 1.4362 | 0.00145992 | 2.97895e-05 | 3.36146e-06 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10978.2 | 0.291214 | 761.97ms | 3643 | 2560 | 2174.3 | 316.466 | 0.587019 | 0.520414 | 1.75872 | 0.293989 | 0.000442094 | 2.54126e-05 | 2.35898e-06 | 1(Win) | true |
| Glaze | 3379.42 | 0.156822 | 835.979ms | 3682 | 2560 | 6797.27 | 1039.06 | 0.0240919 | 1.55801 | 4.54943 | 0.761 | 0.000283049 | 2.85383e-05 | 3.2888e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12483.1 | 0.183746 | 757.995ms | 3643 | 2560 | 669.503 | 278.316 | 0.560637 | 0.466952 | 1.66813 | 0.272303 | 0.00027525 | 1.97296e-05 | 2.35898e-06 | 1(Win) | true |
| Glaze | 3695.34 | 0.118378 | 827.307ms | 3682 | 4890 | 6187.44 | 950.231 | 0.7755 | 1.42422 | 4.19772 | 0.680609 | 0.000329076 | 2.02722e-05 | 3.27687e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 825.576 | 0.0396836 | 1271.41ms | 4630 | 4890 | 22028.2 | 5348.4 | 0.0672878 | 6.17178 | 27.4305 | 5.71922 | 0.00805253 | 6.93441e-05 | 2.10683e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 783.336 | 0.0702838 | 1297.57ms | 4630 | 1280 | 20090.3 | 5636.8 | 0.212973 | 6.50308 | 30.2782 | 6.19309 | 0.00882728 | 5.3152e-05 | 1.61987e-05 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 743.093 | 0.110231 | 1330.37ms | 4630 | 640 | 27457.7 | 5942.07 | 0.0354864 | 6.84346 | 31.5719 | 6.12419 | 0.00477322 | 0.000116766 | 5.36582e-05 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 742.865 | 0.136308 | 1333.07ms | 4630 | 640 | 42011.4 | 5943.89 | 0.0166427 | 6.85143 | 32.3581 | 5.67344 | 0.00254961 | 3.64471e-05 | 3.37473e-06 | 3(Tie) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 985.127 | 0.106639 | 1278.15ms | 4630 | 640 | 14621.4 | 4482.18 | 0.0202846 | 5.18277 | 23.0261 | 4.69698 | 0.00609341 | 2.66604e-05 | 1.34989e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 930.12 | 0.0882927 | 1306.41ms | 4630 | 160 | 2810.96 | 4747.25 | 0.0699915 | 5.48614 | 25.8743 | 5.17084 | 0.00809125 | 5.12959e-05 | 0 | 2(Loss) | true |
| Glaze | 879.992 | 0.0841858 | 1336.66ms | 4630 | 4890 | 87255.2 | 5017.67 | 0.0449272 | 5.78698 | 27.0981 | 5.08553 | 0.00287774 | 5.37528e-05 | 1.76231e-05 | 3(Loss) | true |
| simdjson (ondemand) | 863.224 | 0.0553955 | 1348.27ms | 4630 | 4890 | 39262.1 | 5115.14 | 0.0772711 | 5.90352 | 28.7717 | 4.85205 | 0.00154571 | 5.75512e-05 | 1.34713e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1949.5 | 0.10936 | 960.67ms | 4630 | 2560 | 15706.5 | 2264.95 | 0.0497982 | 2.64041 | 7.98359 | 0.456372 | 0.000396109 | 3.40004e-05 | 2.78415e-06 | 1(Win) | true |
| Glaze | 968.836 | 0.0410873 | 1192.25ms | 4630 | 4890 | 17146.9 | 4557.54 | 0.0423847 | 5.26604 | 9.76048 | 0.676459 | 0.000262934 | 7.48652e-05 | 2.8356e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1995 | 0.253059 | 949.914ms | 4630 | 320 | 10038.5 | 2213.28 | 0.00465958 | 2.58225 | 7.87991 | 0.433261 | 0.000223407 | 2.15983e-05 | 0 | 1(Win) | true |
| Glaze | 1008.13 | 0.0552736 | 1171.23ms | 4630 | 1280 | 7501.99 | 4379.91 | 0.14742 | 5.08154 | 9.27775 | 0.568036 | 0.000226613 | 9.06115e-05 | 4.28591e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1798.45 | 0.177485 | 1352.81ms | 11579 | 320 | 38002.9 | 6140.06 | 0.0645769 | 2.87203 | 13.2513 | 2.60204 | 0.00478749 | 3.07669e-05 | 1.26846e-05 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1789.32 | 0.0969337 | 1349.89ms | 11579 | 2560 | 91612.4 | 6171.38 | 0.0667017 | 2.86823 | 13.6301 | 2.32378 | 0.00172828 | 5.64735e-05 | 3.46802e-05 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 1786.82 | 0.133193 | 1352.49ms | 11579 | 1280 | 86727.2 | 6180.02 | 0.0654375 | 2.89538 | 13.5569 | 2.90578 | 0.00485699 | 1.44389e-05 | 2.49644e-06 | 2(Tie) | true |
| Glaze | 1535.73 | 0.0557078 | 1439.63ms | 11579 | 4890 | 78460.9 | 7190.45 | 0.120124 | 3.3341 | 15.4061 | 3.01477 | 0.00654836 | 1.68841e-05 | 4.32699e-06 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2144.84 | 0.0573268 | 1349.26ms | 11579 | 2560 | 22300.2 | 5148.45 | 0.142694 | 2.38312 | 11.0491 | 2.07937 | 0.00290305 | 1.85883e-05 | 3.20489e-06 | 1(Win) | true |
| Jsonifier | 2124.32 | 0.0815929 | 1351.93ms | 11579 | 1280 | 23025.9 | 5198.18 | 0.058625 | 2.39902 | 11.3792 | 2.38527 | 0.00357544 | 2.72584e-05 | 7.2869e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2094.64 | 0.0583265 | 1361.89ms | 11579 | 4890 | 46234.2 | 5271.83 | 0.165918 | 2.43488 | 11.9424 | 1.91588 | 0.000497728 | 2.82226e-05 | 9.04253e-06 | 3(Loss) | true |
| Glaze | 1824.63 | 0.081451 | 1437.39ms | 11579 | 2560 | 62204.7 | 6051.95 | 0.0408792 | 2.79085 | 13.3379 | 2.51611 | 0.00415903 | 4.08539e-05 | 1.66317e-05 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5288.81 | 0.498443 | 1001.08ms | 14795 | 40 | 7073.02 | 2667.82 | 0.130086 | 0.97071 | 2.98946 | 0.275769 | 0.000307536 | 1.01386e-05 | 0 | 1(Win) | true |
| Glaze | 3358.25 | 0.0841109 | 1153.85ms | 14795 | 4890 | 61068.6 | 4201.48 | 0.0870924 | 1.54098 | 4.4613 | 0.536195 | 0.000998735 | 3.1321e-05 | 1.40157e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4410.39 | 0.0903769 | 1056.03ms | 14795 | 4890 | 40879.1 | 3199.18 | 0.10882 | 1.16066 | 2.96715 | 0.270903 | 0.000283106 | 1.21912e-05 | 1.9351e-06 | 1(Win) | true |
| Glaze | 3735.24 | 0.0794134 | 1109.79ms | 14795 | 4890 | 44003.7 | 3777.43 | 0.358561 | 1.37412 | 4.24475 | 0.486786 | 0.00105835 | 1.39466e-05 | 3.26203e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1727.12 | 0.204881 | 914.578ms | 3223 | 1280 | 17017.2 | 1779.66 | 0.108313 | 2.99802 | 11.6255 | 2.25349 | 0.00114048 | 0.00015465 | 7.56283e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.73 | 0.133595 | 961.023ms | 3223 | 2560 | 23075 | 2247.29 | 0.307599 | 3.77458 | 15.1247 | 2.64257 | 0.00113685 | 6.5084e-05 | 1.80587e-05 | 2(Loss) | true |
| Glaze | 1294.2 | 0.0864651 | 977.307ms | 3223 | 2560 | 10795.4 | 2374.97 | 0.0124328 | 3.97379 | 15.4753 | 2.94415 | 0.00174733 | 6.33872e-05 | 1.33319e-05 | 3(Loss) | true |
| simdjson (ondemand) | 977.58 | 0.11705 | 1054.15ms | 3223 | 4890 | 66232.2 | 3144.18 | 0.0114075 | 5.24609 | 19.6174 | 3.14117 | 0.00216643 | 0.000115796 | 4.19404e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2213.89 | 0.0931818 | 895.87ms | 3223 | 4890 | 8184.25 | 1388.37 | 0.234525 | 2.35591 | 9.63668 | 1.76823 | 0.0011454 | 7.18887e-05 | 2.22709e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1608.32 | 0.305753 | 947.229ms | 3223 | 4890 | 166964 | 1911.11 | 0.0991122 | 3.21336 | 13.3692 | 2.20571 | 0.00111488 | 4.77778e-05 | 7.55054e-06 | 2(Loss) | true |
| Glaze | 1590.2 | 0.134275 | 954.557ms | 3223 | 640 | 4311.11 | 1932.9 | 0.232914 | 3.24931 | 13.4353 | 2.45206 | 0.00112182 | 3.24814e-05 | 3.87837e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1105.23 | 0.179826 | 1034.2ms | 3223 | 1280 | 32013.2 | 2781.04 | 0.249954 | 4.64296 | 17.9231 | 2.7189 | 0.00157923 | 5.69636e-05 | 1.16351e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7604.27 | 0.240826 | 775.394ms | 3223 | 320 | 303.224 | 404.206 | 0.246788 | 0.737706 | 2.42166 | 0.319268 | 0.000466374 | 3.97533e-05 | 9.69594e-06 | 1(Win) | true |
| Glaze | 2856.86 | 0.21875 | 845.235ms | 3223 | 2560 | 14180.1 | 1075.9 | 0.0998346 | 1.8369 | 5.18275 | 0.772263 | 0.000316815 | 6.24176e-05 | 2.04827e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8751.91 | 0.406836 | 768.943ms | 3223 | 1280 | 2613.15 | 351.202 | 0.0731326 | 0.646466 | 2.2628 | 0.282035 | 0.000310512 | 2.7391e-05 | 7.51435e-06 | 1(Win) | true |
| Glaze | 3129.93 | 0.177185 | 833.305ms | 3223 | 4890 | 14805.2 | 982.032 | 1.03254 | 1.67747 | 4.65095 | 0.652498 | 0.000317503 | 3.62299e-05 | 6.97949e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2462.96 | 0.200292 | 962.37ms | 5839 | 2560 | 52496.3 | 2260.9 | 0.169381 | 2.08936 | 8.37164 | 1.65525 | 0.000605974 | 2.42844e-05 | 2.74287e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2312.22 | 0.150132 | 980.248ms | 5839 | 2560 | 33466.1 | 2408.29 | 0.0460922 | 2.22344 | 9.10396 | 1.5167 | 0.000640159 | 8.24199e-05 | 4.74316e-05 | 2(Loss) | true |
| Glaze | 1786.78 | 0.0819407 | 1048.95ms | 5839 | 4890 | 31889.2 | 3116.5 | 0.223276 | 2.86369 | 11.3055 | 2.18359 | 0.00183142 | 4.48644e-05 | 1.39391e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1715.18 | 0.158467 | 1062.99ms | 5839 | 640 | 16940.1 | 3246.61 | 0.054931 | 2.98175 | 11.3173 | 1.75116 | 0.0013329 | 4.121e-05 | 9.6335e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2950.62 | 0.211061 | 956.349ms | 5839 | 30 | 475.978 | 1887.23 | 0.190392 | 1.78487 | 7.503 | 1.43364 | 0.000588 | 0.000165553 | 8.56311e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2678.23 | 0.135631 | 969.124ms | 5839 | 2560 | 20358 | 2079.17 | 0.112062 | 1.92729 | 8.23566 | 1.29509 | 0.000610791 | 3.31152e-05 | 8.69691e-06 | 2(Loss) | true |
| Glaze | 2046.07 | 0.170675 | 1031.19ms | 5839 | 30 | 647.289 | 2721.57 | 0.0709871 | 2.50883 | 10.3523 | 1.94622 | 0.0015699 | 1.14175e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1945.67 | 0.138692 | 1048.04ms | 5839 | 1280 | 20167.4 | 2862 | 0.175009 | 2.66412 | 10.4254 | 1.52663 | 0.000793827 | 3.57242e-05 | 5.21815e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10677.6 | 0.317763 | 796.055ms | 6938 | 1280 | 4962.97 | 619.673 | 0.315324 | 0.50574 | 1.76564 | 0.271404 | 0.000151003 | 1.85797e-05 | 2.92772e-06 | 1(Win) | true |
| Glaze | 3143.53 | 0.180442 | 949.38ms | 6960 | 4890 | 70984.9 | 2111.5 | 0.0916884 | 1.64912 | 4.23262 | 0.722702 | 0.000295848 | 2.51804e-05 | 4.81865e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11653.1 | 0.250462 | 789.778ms | 6938 | 2560 | 5177.35 | 567.795 | 0.199525 | 0.467104 | 1.7188 | 0.260162 | 0.000144866 | 1.6215e-05 | 3.20923e-06 | 1(Win) | true |
| Glaze | 3556.05 | 0.248491 | 924.232ms | 6960 | 2560 | 55073.8 | 1866.56 | 0.0617325 | 1.45454 | 3.8717 | 0.645259 | 0.000292408 | 2.43579e-05 | 5.5563e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2215.25 | 0.100798 | 942.779ms | 4857 | 4890 | 21722 | 2090.96 | 0.0710675 | 2.32612 | 8.75448 | 1.73708 | 0.00119293 | 4.88827e-05 | 1.49048e-05 | 1(Win) | true |
| Glaze | 1702.71 | 0.0758213 | 1008.61ms | 4857 | 4890 | 20804 | 2720.36 | 0.0930927 | 3.0255 | 11.8964 | 2.27363 | 0.000326643 | 9.19551e-05 | 3.84409e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1678.25 | 0.120713 | 1012.6ms | 4857 | 2560 | 28416.5 | 2760.01 | 0.14133 | 3.05847 | 12.5976 | 2.15627 | 0.00153274 | 5.93538e-05 | 2.21973e-05 | 3(Loss) | true |
| simdjson (ondemand) | 767.079 | 0.171431 | 1346.25ms | 4857 | 640 | 68583 | 6038.48 | 0.278654 | 6.63492 | 23.4638 | 3.91692 | 0.00362814 | 3.73173e-05 | 6.75571e-06 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3168.84 | 0.213482 | 907.357ms | 4857 | 30 | 292.133 | 1461.73 | 0.0205194 | 1.64204 | 6.59049 | 1.24398 | 0.000425503 | 0 | 0 | 1(Win) | true |
| Glaze | 2394.21 | 0.106989 | 953.841ms | 4857 | 4890 | 20950.8 | 1934.67 | 0.158897 | 2.16497 | 8.97735 | 1.62034 | 0.00121638 | 6.3156e-05 | 1.92415e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2100.98 | 0.273276 | 978.506ms | 4857 | 1280 | 46462.8 | 2204.69 | 0.189586 | 2.45037 | 10.4793 | 1.67387 | 0.000934701 | 4.63249e-05 | 1.7211e-05 | 3(Loss) | true |
| simdjson (ondemand) | 883.201 | 0.115245 | 1291.05ms | 4857 | 1280 | 46759.7 | 5244.56 | 0.0265673 | 5.77532 | 21.3967 | 3.45296 | 0.00308157 | 3.08833e-05 | 6.91656e-06 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9841.49 | 0.259463 | 781.694ms | 4857 | 2560 | 3817.74 | 470.66 | 0.26529 | 0.560932 | 1.78011 | 0.271773 | 0.000264679 | 5.85495e-05 | 2.77467e-05 | 1(Win) | true |
| Glaze | 3126.49 | 0.132845 | 884.547ms | 4857 | 4890 | 18941.9 | 1481.53 | 0.101923 | 1.66637 | 4.16821 | 0.63496 | 0.000212751 | 6.48822e-05 | 2.33256e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11365.5 | 0.292765 | 777.404ms | 4857 | 1280 | 1822.24 | 407.548 | 0.752828 | 0.491686 | 1.66049 | 0.242537 | 0.000206049 | 1.43157e-05 | 2.2519e-06 | 1(Win) | true |
| Glaze | 3608.97 | 0.185529 | 864.944ms | 4857 | 2560 | 14515.5 | 1283.47 | 0.415744 | 1.44848 | 3.68582 | 0.525428 | 0.000211116 | 7.77711e-05 | 2.83901e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2602.41 | 0.237049 | 987.753ms | 6701 | 4890 | 165696 | 2455.64 | 0.0864336 | 1.9765 | 7.77481 | 1.49963 | 0.00104688 | 5.95095e-05 | 2.61231e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2179.67 | 0.228868 | 1040.31ms | 6701 | 40 | 1801.07 | 2931.9 | 0.0204604 | 2.35371 | 9.77108 | 1.6314 | 0.00124235 | 3.35771e-05 | 3.73079e-06 | 2(Loss) | true |
| Glaze | 1943.99 | 0.355022 | 1070.8ms | 6701 | 640 | 87172.9 | 3287.35 | 0.0247696 | 2.69131 | 11.0987 | 2.17669 | 0.00129622 | 0.000263953 | 0.00015646 | 3(Loss) | true |
| simdjson (ondemand) | 1041.29 | 0.210537 | 1354.23ms | 6701 | 320 | 53424.9 | 6137.16 | 0.0781509 | 4.8865 | 17.4123 | 2.86174 | 0.00261295 | 8.11446e-05 | 3.73079e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3498.81 | 0.174379 | 954.535ms | 6701 | 1280 | 12984.9 | 1826.5 | 0.2103 | 1.4782 | 6.1846 | 1.13729 | 0.00038089 | 3.04292e-05 | 6.99522e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2708.07 | 0.277896 | 1004.11ms | 6701 | 4890 | 210297 | 2359.83 | 0.178004 | 1.90244 | 8.14699 | 1.26235 | 0.000667879 | 5.87771e-05 | 2.33155e-05 | 2(Loss) | true |
| Glaze | 2583.52 | 0.162653 | 1013.48ms | 6701 | 1280 | 20720.1 | 2473.59 | 0.157952 | 2.00201 | 8.97403 | 1.70184 | 0.000869273 | 4.18548e-05 | 1.36407e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1208.2 | 0.268538 | 1301.07ms | 6701 | 30 | 6052.51 | 5289.33 | 0.049761 | 4.22613 | 15.9124 | 2.52529 | 0.00263642 | 3.48207e-05 | 9.94876e-06 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11222.6 | 0.209594 | 798.937ms | 7376 | 40 | 69.0359 | 626.8 | 0.583044 | 0.482067 | 1.60073 | 0.273048 | 0.000179637 | 2.7115e-05 | 1.69469e-05 | 1(Win) | true |
| Glaze | 2573.93 | 0.152341 | 1017.28ms | 7376 | 4890 | 84759.4 | 2732.9 | 0.21825 | 1.99871 | 4.57077 | 0.739426 | 0.00054851 | 4.28073e-05 | 1.12563e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12289.5 | 0.174043 | 799.254ms | 7376 | 2560 | 2540.56 | 572.385 | 0.172548 | 0.441853 | 1.52183 | 0.254745 | 0.000136051 | 1.60466e-05 | 4.97814e-06 | 1(Win) | true |
| Glaze | 2828.03 | 0.182591 | 985.257ms | 7376 | 2560 | 52804.8 | 2487.35 | 0.248085 | 1.83404 | 4.2523 | 0.667028 | 0.00055967 | 4.10961e-05 | 1.30279e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2209.51 | 0.327418 | 808.022ms | 1691 | 1280 | 7309.9 | 729.873 | 0.260069 | 2.42899 | 7.48019 | 1.4453 | 0.00178149 | 0.000150614 | 3.97324e-05 | 1(Win) | true |
| Glaze | 1938.02 | 0.425815 | 826.165ms | 1691 | 160 | 2008.78 | 832.119 | 0.113287 | 2.78515 | 10.1307 | 1.91839 | 0.00125665 | 4.43525e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1730.37 | 0.194978 | 827.192ms | 1691 | 4890 | 16146.9 | 931.974 | 0.0643366 | 3.04449 | 10.7246 | 1.77117 | 0.000608418 | 0.000162898 | 5.51458e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1357.48 | 0.307748 | 855.172ms | 1691 | 1280 | 17108.8 | 1187.98 | 0.231147 | 3.86269 | 12.495 | 2.06978 | 0.0011989 | 0.000163088 | 5.17445e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2825.66 | 0.26506 | 794.162ms | 1691 | 2560 | 5858.33 | 570.72 | 0.276249 | 1.94116 | 5.98167 | 1.07274 | 0.00177964 | 0.000142066 | 5.75196e-05 | 1(Win) | true |
| Glaze | 2304.95 | 0.206069 | 816.573ms | 1691 | 4890 | 10164.9 | 699.653 | 0.140252 | 2.33547 | 8.78238 | 1.57836 | 0.000865765 | 0.000124804 | 3.60383e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2121.08 | 0.348035 | 819.574ms | 1691 | 640 | 4481.27 | 760.305 | 0.268085 | 2.51699 | 9.22531 | 1.39858 | 0.000602454 | 7.20727e-05 | 1.84802e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1551.46 | 0.304965 | 849.386ms | 1691 | 40 | 401.946 | 1039.45 | 0.107544 | 3.38733 | 11.1331 | 1.73034 | 0.00144885 | 0.000103489 | 2.95683e-05 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9529.12 | 0.30236 | 751.146ms | 1996 | 4890 | 1783.91 | 199.76 | 0.145477 | 0.63962 | 1.63477 | 0.254008 | 0.000791358 | 5.75794e-05 | 1.19872e-05 | 1(Win) | true |
| Glaze | 3923.71 | 0.18867 | 777.646ms | 1996 | 4890 | 4096.77 | 485.136 | 0.258428 | 1.39749 | 3.74549 | 0.585171 | 0.00050469 | 6.76199e-05 | 1.55731e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12873.2 | 0.400143 | 745.078ms | 1996 | 4890 | 1711.93 | 147.868 | 0.0411188 | 0.503967 | 1.38477 | 0.196894 | 0.000501309 | 4.30308e-05 | 7.88899e-06 | 1(Win) | true |
| Glaze | 4196.5 | 0.444683 | 768.138ms | 1996 | 640 | 2603.91 | 453.6 | 0.302214 | 1.3131 | 3.25601 | 0.480461 | 0.000501785 | 2.58329e-05 | 7.82816e-07 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2556.65 | 0.233378 | 811.195ms | 2158 | 4890 | 17257.9 | 804.97 | 0.303147 | 2.09079 | 6.88462 | 1.31696 | 0.000473342 | 0.000108504 | 2.67232e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2116.65 | 0.219866 | 831.407ms | 2158 | 2560 | 11699.4 | 972.305 | 0.210639 | 2.49161 | 8.943 | 1.443 | 0.000472624 | 0.000103901 | 2.73329e-05 | 2(Loss) | true |
| Glaze | 1958.86 | 0.148452 | 839.774ms | 2158 | 4890 | 11895.3 | 1050.63 | 0.104757 | 2.67623 | 9.8304 | 1.88554 | 0.00097047 | 0.000104903 | 2.56808e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1717.27 | 0.204166 | 858.157ms | 2158 | 2560 | 15326.2 | 1198.43 | 0.334408 | 3.05569 | 9.92261 | 1.61029 | 0.00104897 | 9.05063e-05 | 1.81013e-05 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3200.45 | 0.189737 | 807.089ms | 2158 | 160 | 238.18 | 643.044 | 0.14308 | 1.68661 | 5.7683 | 1.03661 | 0.000466288 | 6.37164e-05 | 5.7924e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2525.24 | 0.161985 | 823.652ms | 2158 | 2560 | 4461.59 | 814.985 | 0.00853087 | 2.09961 | 7.82577 | 1.16265 | 0.000469546 | 7.49392e-05 | 1.23089e-05 | 2(Loss) | true |
| Glaze | 2387.62 | 0.0998906 | 825.746ms | 2158 | 4890 | 3625.19 | 861.959 | 0.0589109 | 2.23104 | 8.59314 | 1.58248 | 0.000957298 | 8.16859e-05 | 1.53516e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1932.88 | 0.265531 | 846.55ms | 2158 | 40 | 319.731 | 1064.75 | 0.051682 | 2.67096 | 8.91288 | 1.35589 | 0.000926784 | 0.000393883 | 0 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9958.6 | 0.314327 | 761.455ms | 2866 | 640 | 476.321 | 274.459 | 0.124262 | 0.573321 | 1.54676 | 0.255059 | 0.000657493 | 2.83496e-05 | 1.63555e-06 | 1(Win) | true |
| Glaze | 3488.68 | 0.260063 | 814.884ms | 2866 | 2560 | 10627.5 | 783.458 | 0.178915 | 1.52172 | 4.22226 | 0.730287 | 0.000359277 | 5.71081e-05 | 1.36296e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12605.8 | 0.414869 | 754.676ms | 2866 | 4890 | 3956.77 | 216.822 | 0.212242 | 0.476676 | 1.36427 | 0.213538 | 0.000349489 | 2.42602e-05 | 4.35256e-06 | 1(Win) | true |
| Glaze | 3891.25 | 0.274909 | 807.03ms | 2866 | 2560 | 9545.33 | 702.404 | 0.444859 | 1.36667 | 3.57397 | 0.584438 | 0.000353416 | 4.14341e-05 | 1.36296e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2351.8 | 0.0588657 | 913.113ms | 4390 | 2560 | 2811.22 | 1780.18 | 0.187829 | 2.20034 | 9.92642 | 1.88246 | 0.00229214 | 3.07873e-05 | 7.47437e-06 | 1(Win) | true |
| Glaze | 1713.95 | 0.05761 | 981.883ms | 4390 | 4890 | 9683.56 | 2442.67 | 0.0762772 | 2.9863 | 13.8775 | 2.67426 | 0.000596681 | 4.08998e-05 | 7.6396e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1580.58 | 0.051506 | 997.718ms | 4390 | 4890 | 9101.68 | 2648.8 | 0.0458625 | 3.25026 | 15.1886 | 2.55513 | 0.00361842 | 6.13963e-05 | 1.84468e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1082.75 | 0.0565171 | 1124.43ms | 4390 | 4890 | 23353.1 | 3866.68 | 0.0458701 | 4.71264 | 20.298 | 3.35262 | 0.00303325 | 7.61631e-05 | 2.781e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2731.98 | 0.104935 | 913.756ms | 4390 | 2560 | 6619.91 | 1532.45 | 0.0150624 | 1.90164 | 8.69577 | 1.59751 | 0.00229686 | 3.09653e-05 | 6.22864e-06 | 1(Win) | true |
| Glaze | 2017.72 | 0.0636171 | 967.661ms | 4390 | 4890 | 8520.52 | 2074.94 | 0.0444039 | 2.54992 | 12.3059 | 2.32984 | 0.000597193 | 4.89121e-05 | 1.19718e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1758.07 | 0.0981788 | 997.929ms | 4390 | 2560 | 13993.6 | 2381.37 | 0.0661601 | 2.93388 | 13.9581 | 2.27016 | 0.00352159 | 6.9049e-05 | 2.90967e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1164.84 | 0.0939558 | 1117.1ms | 4390 | 2560 | 29193.1 | 3594.16 | 0.132364 | 4.39354 | 19.0039 | 3.06128 | 0.00378924 | 4.04862e-05 | 4.36005e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10702.9 | 0.204245 | 767.138ms | 4390 | 2560 | 1634.08 | 391.169 | 0.334212 | 0.52293 | 2.28223 | 0.324374 | 0.000335279 | 4.36895e-05 | 1.44149e-05 | 1(Win) | true |
| Glaze | 3646.46 | 0.116843 | 847.566ms | 4390 | 4890 | 8800.3 | 1148.13 | 0.16696 | 1.43902 | 5.80228 | 0.86606 | 0.000461217 | 6.03249e-05 | 2.03567e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11970.1 | 0.165552 | 760.725ms | 4390 | 2560 | 858.314 | 349.758 | 0.32179 | 0.471712 | 2.16447 | 0.297267 | 0.000229392 | 4.95622e-05 | 1.62835e-05 | 1(Win) | true |
| Glaze | 3911.07 | 0.603665 | 837.261ms | 4390 | 160 | 6681.13 | 1070.46 | 0.107898 | 1.34296 | 5.37927 | 0.771071 | 0.000605068 | 6.12187e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3489.31 | 0.118764 | 995.767ms | 9378 | 1280 | 11861 | 2563.13 | 0.203075 | 1.46735 | 6.81062 | 1.30987 | 0.0015071 | 1.5495e-05 | 1.16629e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2788.6 | 0.0809197 | 1058.06ms | 9378 | 1280 | 8621.16 | 3207.18 | 0.00752762 | 1.83714 | 8.40147 | 1.37161 | 0.0022008 | 2.35758e-05 | 4.49856e-06 | 2(Loss) | true |
| Glaze | 2347.78 | 0.0933505 | 1117.74ms | 9378 | 1280 | 16186.4 | 3809.37 | 0.0249938 | 2.1752 | 9.76061 | 1.91032 | 0.00282251 | 2.40756e-05 | 5.16501e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2212.75 | 0.153866 | 1136.04ms | 9378 | 1280 | 49505.3 | 4041.83 | 0.033644 | 2.33812 | 10.1286 | 1.59981 | 0.00151918 | 3.79045e-05 | 1.11631e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3890.75 | 0.130313 | 991.918ms | 9378 | 1280 | 11485.2 | 2298.67 | 0.195891 | 1.32373 | 6.23331 | 1.17648 | 0.00150593 | 1.96604e-05 | 2.33259e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3065.42 | 0.116339 | 1053.76ms | 9378 | 30 | 345.633 | 2917.57 | 0.246243 | 1.67429 | 7.82502 | 1.23822 | 0.00209711 | 7.81972e-05 | 7.10884e-06 | 2(Loss) | true |
| Glaze | 2589.14 | 0.170719 | 1105.34ms | 9378 | 160 | 5564.07 | 3454.26 | 0.0166433 | 1.97748 | 9.0081 | 1.74579 | 0.00307835 | 2.93239e-05 | 7.99744e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2394.42 | 0.102369 | 1125.1ms | 9378 | 1280 | 18714 | 3735.17 | 0.0608495 | 2.16206 | 9.51845 | 1.46257 | 0.00157533 | 2.34092e-05 | 3.41557e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17036.4 | 0.162145 | 791.38ms | 11521 | 2560 | 2799.45 | 644.932 | 0.130088 | 0.315139 | 1.50569 | 0.253711 | 0.000127654 | 9.49353e-06 | 1.59356e-06 | 1(Win) | true |
| Glaze | 4839.38 | 0.0907436 | 955.469ms | 11521 | 2560 | 10866.1 | 2270.39 | 0.0949855 | 1.08033 | 3.86954 | 0.687961 | 0.00116262 | 2.28523e-05 | 6.61157e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17871.3 | 0.132168 | 790.402ms | 11521 | 4890 | 3228.74 | 614.801 | 0.272402 | 0.301925 | 1.47704 | 0.246854 | 8.74015e-05 | 1.65608e-05 | 7.33079e-06 | 1(Win) | true |
| Glaze | 5469.99 | 0.266172 | 928.436ms | 11521 | 320 | 9147.08 | 2008.65 | 0.290996 | 0.959362 | 3.62026 | 0.633279 | 0.00123931 | 2.38695e-05 | 5.69612e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2519.24 | 0.218214 | 905.319ms | 4669 | 1280 | 19040.8 | 1767.48 | 0.108278 | 2.05175 | 8.16727 | 1.6404 | 0.00138112 | 2.00792e-05 | 1.67327e-06 | 1(Win) | true |
| Glaze | 2110.6 | 0.23257 | 944.471ms | 4669 | 2560 | 61628.8 | 2109.69 | 0.749432 | 2.47528 | 10.0878 | 1.7961 | 0.000807018 | 2.80273e-05 | 4.68516e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1904.12 | 0.0930113 | 968.334ms | 4669 | 4890 | 23133.5 | 2338.46 | 0.62824 | 2.70454 | 11.3864 | 1.99122 | 0.00118175 | 3.5346e-05 | 4.77412e-06 | 3(Loss) | true |
| simdjson (ondemand) | 656.9 | 0.0831583 | 1423.59ms | 4669 | 80 | 2541.85 | 6778.36 | 0.122483 | 7.74442 | 31.5676 | 4.51403 | 0.00301189 | 0.000176697 | 0.000104412 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2749.45 | 0.227809 | 901.988ms | 4669 | 640 | 8711.25 | 1619.49 | 0.00636734 | 1.88802 | 7.70165 | 1.52667 | 0.00111473 | 1.37208e-05 | 0 | 1(Win) | true |
| Glaze | 2338.98 | 0.202574 | 926.263ms | 4669 | 1280 | 19035.9 | 1903.69 | 0.0501744 | 2.2226 | 9.35875 | 1.63097 | 0.000794302 | 2.81109e-05 | 6.69308e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2025.43 | 0.104836 | 957.705ms | 4669 | 4890 | 25974.4 | 2198.4 | 0.120366 | 2.55096 | 10.9349 | 1.8807 | 0.00120194 | 5.64573e-05 | 2.28194e-05 | 3(Loss) | true |
| simdjson (ondemand) | 679.86 | 0.125882 | 1404.68ms | 4669 | 2560 | 174012 | 6549.44 | 0.0946586 | 7.43409 | 30.8385 | 4.34761 | 0.00239152 | 9.83046e-05 | 4.87758e-05 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11420.4 | 0.136668 | 769.337ms | 4669 | 4890 | 1388.44 | 389.889 | 0.782923 | 0.48702 | 1.6209 | 0.232598 | 0.000272257 | 1.4848e-05 | 2.32136e-06 | 1(Win) | true |
| Glaze | 2537.59 | 0.17197 | 914.548ms | 4669 | 4890 | 44526.4 | 1754.7 | 0.833209 | 2.03892 | 3.66588 | 0.505034 | 0.000218208 | 3.29371e-05 | 7.70868e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12929.8 | 0.158741 | 766.552ms | 4669 | 4890 | 1461.33 | 344.375 | 0.064939 | 0.438939 | 1.51253 | 0.207111 | 0.000214617 | 1.93155e-05 | 6.3509e-06 | 1(Win) | true |
| Glaze | 2777.15 | 0.129207 | 892.967ms | 4669 | 4890 | 20985.9 | 1603.34 | 0.758007 | 1.86651 | 3.1949 | 0.397516 | 0.000218033 | 2.48342e-05 | 6.1319e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3549.62 | 0.112249 | 945.903ms | 7932 | 4890 | 27982 | 2131.09 | 0.314469 | 1.45673 | 6.17801 | 1.2297 | 0.000778086 | 2.41831e-05 | 5.13052e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2929.79 | 0.114028 | 993.292ms | 7932 | 2560 | 22189.7 | 2581.94 | 0.0105007 | 1.75335 | 7.41352 | 1.22806 | 0.000901806 | 3.68365e-05 | 1.0588e-05 | 2(Loss) | true |
| Glaze | 2361.35 | 0.393799 | 1058.03ms | 7932 | 320 | 50926.4 | 3203.48 | 0.0142403 | 2.16696 | 8.9323 | 1.66452 | 0.00159599 | 2.16686e-05 | 3.93974e-07 | 3(Loss) | true |
| simdjson (ondemand) | 1087 | 0.0875249 | 1434.94ms | 7932 | 4890 | 181416 | 6959.09 | 0.0539837 | 4.67147 | 19.0932 | 2.68054 | 0.00168204 | 4.28489e-05 | 1.62424e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3808.14 | 0.142245 | 938.328ms | 7932 | 4890 | 39041 | 1986.41 | 0.268558 | 1.35443 | 5.95247 | 1.1736 | 0.000760606 | 1.80471e-05 | 3.99613e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3085.9 | 0.347507 | 982.8ms | 7932 | 640 | 46441.8 | 2451.32 | 0.0254392 | 1.67197 | 7.18848 | 1.17196 | 0.000653996 | 3.13209e-05 | 9.65236e-06 | 2(Loss) | true |
| Glaze | 2563.71 | 0.221481 | 1037.77ms | 7932 | 1280 | 54664.9 | 2950.62 | 0.0184514 | 1.99074 | 8.50277 | 1.56732 | 0.00148735 | 2.24565e-05 | 5.71262e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1131.94 | 0.0872197 | 1418.06ms | 7932 | 4890 | 166134 | 6682.82 | 0.0429479 | 4.46283 | 18.664 | 2.58258 | 0.00127606 | 3.60168e-05 | 1.60619e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13720 | 0.369575 | 794.727ms | 9249 | 1280 | 7225.96 | 642.895 | 0.458769 | 0.399031 | 1.37582 | 0.240134 | 0.00014233 | 8.78473e-06 | 8.44686e-08 | 1(Win) | true |
| Glaze | 2654.98 | 0.131158 | 1067.66ms | 9249 | 4890 | 92846.9 | 3322.26 | 1.10664 | 1.95827 | 3.89123 | 0.651206 | 0.000416538 | 3.63053e-05 | 1.4416e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14981.4 | 0.541936 | 784.941ms | 9249 | 640 | 6515.71 | 588.766 | 0.622196 | 0.363391 | 1.31355 | 0.225322 | 0.000109133 | 7.43324e-06 | 1.52043e-06 | 1(Win) | true |
| Glaze | 2955.69 | 0.269731 | 1034.77ms | 9249 | 1280 | 82936.5 | 2984.26 | 0.0933719 | 1.76434 | 3.62255 | 0.590442 | 0.000353586 | 2.21308e-05 | 7.17983e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 751.003 | 0.427232 | 1315.26ms | 4604 | 160 | 99823.8 | 5846.47 | 0.010796 | 6.76792 | 25.447 | 5.64444 | 0.00513005 | 6.51607e-05 | 1.76477e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 674.273 | 0.329697 | 1396.23ms | 4604 | 160 | 73748 | 6511.78 | 0.0662781 | 7.54136 | 30.2871 | 6.30083 | 0.00714596 | 0.000147969 | 8.9596e-05 | 2(Loss) | true |
| Glaze | 640.294 | 0.0697319 | 1427.63ms | 4604 | 2560 | 58534.9 | 6857.34 | 0.134648 | 7.97206 | 33.9711 | 6.91985 | 0.00549183 | 7.22028e-05 | 3.10532e-05 | 3(Loss) | true |
| simdjson (ondemand) | 497.19 | 0.205121 | 1623.1ms | 4604 | 320 | 105001 | 8831.07 | 0.00729014 | 10.2064 | 40.5404 | 7.21742 | 0.00652761 | 0.000192088 | 0.000107244 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 919.329 | 0.165124 | 1312.74ms | 4604 | 2560 | 159216 | 4776 | 0.599085 | 5.59935 | 20.8606 | 4.59731 | 0.00540444 | 0.000109789 | 5.34522e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 788.186 | 0.0797619 | 1393.02ms | 4604 | 4890 | 96541.2 | 5570.66 | 0.223204 | 6.49036 | 25.9035 | 5.29909 | 0.00632903 | 0.000328025 | 0.000211162 | 2(Loss) | true |
| Glaze | 764.535 | 0.15233 | 1413.63ms | 4604 | 640 | 48980.9 | 5742.99 | 0.0768646 | 6.7837 | 29.3901 | 5.86664 | 0.00479576 | 5.26037e-05 | 1.62902e-05 | 3(Loss) | true |
| simdjson (ondemand) | 557.176 | 0.0769698 | 1621.6ms | 4604 | 2560 | 94181.8 | 7880.31 | 0.048726 | 9.11702 | 37.4991 | 6.51412 | 0.00271062 | 0.000131764 | 6.47365e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1642.18 | 0.575352 | 1017.28ms | 4918 | 320 | 86407.3 | 2856.06 | 0.0553955 | 3.11397 | 8.95323 | 0.571169 | 0.000474024 | 8.19693e-05 | 2.35106e-05 | 1(Win) | true |
| Glaze | 835.613 | 0.208734 | 1262.61ms | 4604 | 320 | 38494.5 | 5254.49 | 0.00118945 | 6.10015 | 12.9915 | 1.08666 | 0.00153535 | 3.80104e-05 | 4.07255e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1692.73 | 0.0981787 | 1009.04ms | 4918 | 4890 | 36186.5 | 2770.78 | 0.16302 | 3.05896 | 8.88634 | 0.555104 | 0.000472992 | 5.49295e-05 | 2.13314e-05 | 1(Win) | true |
| Glaze | 877.338 | 0.0699367 | 1238.17ms | 4604 | 2560 | 31360.8 | 5004.59 | 0.223186 | 5.86884 | 12.4472 | 0.970679 | 0.000832327 | 5.48945e-05 | 1.73083e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2380.58 | 0.0827891 | 1467.87ms | 18245 | 4890 | 179051 | 7309.06 | 0.335827 | 2.15874 | 8.60312 | 1.64483 | 0.00184493 | 0.000105999 | 7.1499e-05 | 1(Win) | true |
| Jsonifier | 2092.34 | 0.0860777 | 1571.09ms | 18245 | 4890 | 250560 | 8315.94 | 0.0264873 | 2.43558 | 9.19216 | 2.0912 | 0.00236264 | 2.35715e-05 | 1.07153e-05 | 2(Loss) | true |
| Glaze | 1879.19 | 0.13325 | 1667.91ms | 18245 | 80 | 12177.8 | 9259.17 | 0.0210646 | 2.70073 | 11.8384 | 2.39151 | 0.00335023 | 2.60345e-05 | 1.57577e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1835.56 | 0.0927245 | 1689.6ms | 18245 | 1280 | 98889.6 | 9479.29 | 0.0452344 | 2.76431 | 11.082 | 1.84812 | 0.00193495 | 8.26853e-05 | 4.78727e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2737.55 | 0.258817 | 1462.65ms | 18245 | 640 | 173193 | 6355.97 | 0.0673862 | 1.85963 | 7.50271 | 1.39359 | 0.00171203 | 1.47301e-05 | 5.56659e-06 | 1(Win) | true |
| Jsonifier | 2386.45 | 0.155091 | 1558.86ms | 18245 | 1280 | 163669 | 7291.09 | 0.499093 | 2.13413 | 8.09663 | 1.84105 | 0.00215813 | 1.61859e-05 | 4.75301e-06 | 2(Loss) | true |
| Glaze | 2073.9 | 0.0520884 | 1666.66ms | 18245 | 4890 | 93390.7 | 8389.88 | 0.158548 | 2.44955 | 10.7292 | 2.13642 | 0.00325025 | 1.96485e-05 | 7.45365e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2021.84 | 0.0725695 | 1707.47ms | 18245 | 2560 | 99848.2 | 8605.9 | 0.298646 | 2.52382 | 10.3568 | 1.67916 | 0.00201791 | 2.38293e-05 | 9.97705e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5510.63 | 0.109884 | 1172.86ms | 24893 | 2560 | 57366.8 | 4308 | 0.0125205 | 0.925936 | 2.96843 | 0.378741 | 0.000133917 | 2.3805e-05 | 1.19888e-05 | 1(Win) | true |
| Glaze | 3494.6 | 0.10694 | 1418.34ms | 24579 | 2560 | 131720 | 6707.59 | 0.112258 | 1.4545 | 3.73498 | 0.479556 | 0.000310749 | 2.10577e-05 | 9.83754e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5626.17 | 0.153786 | 1160.29ms | 24893 | 1280 | 53897.8 | 4219.53 | 0.268358 | 0.907138 | 2.94774 | 0.373921 | 0.000124407 | 6.08856e-06 | 6.59071e-07 | 1(Win) | true |
| Glaze | 3715.26 | 0.088688 | 1377.6ms | 24579 | 2560 | 80153 | 6309.21 | 0.0255266 | 1.37445 | 3.59514 | 0.447659 | 0.000219795 | 3.72523e-05 | 2.45223e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 819.33 | 0.10225 | 1274.5ms | 4604 | 1280 | 38431.6 | 5358.91 | 0.0932592 | 6.24724 | 23.9112 | 5.27129 | 0.00749603 | 5.63369e-05 | 1.37448e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 728.144 | 0.110665 | 1334.3ms | 4604 | 1280 | 56999 | 6030.01 | 0.119013 | 6.98906 | 29.3147 | 6.11816 | 0.0064504 | 0.000104698 | 3.90286e-05 | 2(Loss) | true |
| Glaze | 654.835 | 0.0809501 | 1412.55ms | 4604 | 4890 | 144063 | 6705.08 | 0.322397 | 7.77436 | 32.8602 | 6.67496 | 0.00835883 | 9.16337e-05 | 3.97982e-05 | 3(Loss) | true |
| simdjson (ondemand) | 510.691 | 0.108703 | 1603.24ms | 4604 | 1280 | 111802 | 8597.6 | 0.0527042 | 9.96137 | 39.5821 | 7.00326 | 0.0076759 | 7.38149e-05 | 1.66296e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 990.58 | 0.161416 | 1274.14ms | 4604 | 320 | 16380.8 | 4432.47 | 0.0810024 | 5.15802 | 19.6486 | 4.29518 | 0.00638032 | 4.4798e-05 | 4.07255e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 865.353 | 0.106329 | 1343.41ms | 4604 | 1280 | 37256 | 5073.9 | 0.120013 | 5.89052 | 25.051 | 5.14205 | 0.00524476 | 7.50027e-05 | 2.63019e-05 | 2(Loss) | true |
| Glaze | 772.726 | 0.126019 | 1402.78ms | 4604 | 1280 | 65630.2 | 5682.11 | 0.0306566 | 6.62846 | 28.7263 | 5.72568 | 0.0060742 | 5.07371e-05 | 1.66296e-05 | 3(Loss) | true |
| simdjson (ondemand) | 548.937 | 0.0975014 | 1646.82ms | 4604 | 1280 | 77849.7 | 7998.57 | 0.12465 | 9.26889 | 37.5331 | 6.51723 | 0.00729698 | 5.41309e-05 | 1.08601e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1680.77 | 0.208691 | 1010.49ms | 4918 | 640 | 21704.4 | 2790.49 | 0.0428729 | 3.03364 | 8.90626 | 0.571371 | 0.000601744 | 7.33911e-05 | 2.95471e-05 | 1(Win) | true |
| Glaze | 819.247 | 0.149066 | 1264.72ms | 4604 | 640 | 40848.6 | 5359.45 | 0.299931 | 6.23576 | 12.9353 | 1.08428 | 0.00176545 | 7.7039e-05 | 2.44353e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1703.88 | 0.0842714 | 1009.65ms | 4918 | 4890 | 26312.8 | 2752.63 | 0.0899311 | 3.0215 | 8.83937 | 0.555308 | 0.000478523 | 0.000167824 | 9.41826e-05 | 1(Win) | true |
| Glaze | 861.697 | 0.0469922 | 1245.73ms | 4604 | 4890 | 28036.4 | 5095.43 | 0.12251 | 5.94836 | 12.437 | 0.970896 | 0.00104244 | 7.87081e-05 | 2.76722e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2545.52 | 0.0901258 | 1416.45ms | 18245 | 2560 | 97156.5 | 6835.45 | 0.111292 | 2.01172 | 8.35237 | 1.59677 | 0.00165315 | 1.65927e-05 | 6.27312e-06 | 1(Win) | true |
| Jsonifier | 2261.12 | 0.0813906 | 1504.35ms | 18245 | 4890 | 191821 | 7695.19 | 0.128297 | 2.25941 | 8.86621 | 2.02335 | 0.00224476 | 2.43112e-05 | 1.03903e-05 | 2(Loss) | true |
| Glaze | 1906.61 | 0.114053 | 1652.87ms | 18245 | 640 | 69335.2 | 9126.03 | 0.135332 | 2.66752 | 11.4816 | 2.31236 | 0.00347338 | 9.07783e-06 | 1.79844e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1894.08 | 0.0520627 | 1651.99ms | 18245 | 4890 | 111855 | 9186.43 | 0.124262 | 2.70684 | 10.8598 | 1.79819 | 0.001908 | 3.14398e-05 | 1.32372e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2966.83 | 0.0606374 | 1421.21ms | 18245 | 4890 | 61843.3 | 5864.78 | 0.565309 | 1.7269 | 7.27646 | 1.35045 | 0.0014515 | 1.28786e-05 | 3.84451e-06 | 1(Win) | true |
| Jsonifier | 2593.72 | 0.0846466 | 1500.25ms | 18245 | 4890 | 157677 | 6708.43 | 0.736368 | 1.97561 | 7.79003 | 1.77704 | 0.00200568 | 2.05115e-05 | 9.87468e-06 | 2(Loss) | true |
| Glaze | 2130.37 | 0.0512807 | 1639.32ms | 18245 | 4890 | 85781.6 | 8167.5 | 0.137003 | 2.40398 | 10.4569 | 2.0786 | 0.0032198 | 2.0534e-05 | 8.54087e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2025.17 | 0.0514707 | 1698.97ms | 18245 | 4890 | 95629.9 | 8591.76 | 0.114761 | 2.52141 | 10.4149 | 1.69075 | 0.00169802 | 1.88191e-05 | 7.07256e-06 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4651.77 | 0.115914 | 1250.44ms | 24893 | 1280 | 44792.2 | 5103.39 | 0.163854 | 1.10764 | 2.94738 | 0.378661 | 0.000150237 | 8.85038e-06 | 2.1969e-06 | 1(Win) | true |
| Glaze | 3313.52 | 0.076811 | 1451.84ms | 24579 | 4890 | 144380 | 7074.16 | 0.26284 | 1.5557 | 3.7399 | 0.481021 | 0.000378854 | 9.75112e-06 | 2.77058e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4665.7 | 0.0860466 | 1241.8ms | 24893 | 4890 | 93733.8 | 5088.15 | 0.181599 | 1.09474 | 2.92669 | 0.37384 | 0.000129429 | 3.05602e-05 | 1.91084e-05 | 1(Win) | true |
| Glaze | 3660.43 | 0.105484 | 1376.38ms | 24579 | 2560 | 116810 | 6403.71 | 0.0330484 | 1.41395 | 3.59408 | 0.447374 | 0.000297621 | 9.72629e-06 | 2.08193e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2083.62 | 0.0667244 | 969.812ms | 5094 | 4890 | 11834.7 | 2331.52 | 0.0657081 | 2.46979 | 10.8481 | 2.0905 | 0.00244985 | 3.67327e-05 | 8.35017e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1441.52 | 0.200632 | 1066.68ms | 5094 | 40 | 1828.69 | 3370.07 | 0.115344 | 3.55139 | 15.9358 | 2.66333 | 0.00165881 | 0.00021594 | 0.000147232 | 2(Loss) | true |
| Glaze | 1269.75 | 0.0950281 | 1112.67ms | 5094 | 1280 | 16919.8 | 3825.96 | 0.324724 | 4.02409 | 16.4299 | 3.16608 | 0.00375764 | 5.49053e-05 | 1.34963e-05 | 3(Loss) | true |
| simdjson (ondemand) | 848.596 | 0.0615287 | 1313.67ms | 5094 | 4890 | 60671 | 5724.77 | 0.0465342 | 6.01126 | 22.7517 | 3.80566 | 0.00538141 | 0.000130391 | 6.09001e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2801.71 | 0.116787 | 966.838ms | 5094 | 640 | 2624.45 | 1733.95 | 0.142309 | 1.86346 | 8.35218 | 1.52277 | 0.00223333 | 4.66235e-05 | 1.77905e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1781.58 | 0.187145 | 1067.06ms | 5094 | 640 | 16666.3 | 2726.8 | 0.0410684 | 2.93636 | 13.4397 | 2.0956 | 0.00161526 | 7.23891e-05 | 3.28205e-05 | 2(Loss) | true |
| Glaze | 1664.53 | 0.0627313 | 1085.39ms | 5094 | 4890 | 16391.2 | 2918.54 | 0.276941 | 3.08221 | 13.0832 | 2.42638 | 0.00370125 | 3.65722e-05 | 8.26988e-06 | 3(Loss) | true |
| simdjson (ondemand) | 992.865 | 0.184935 | 1280.19ms | 5094 | 320 | 26201.5 | 4892.93 | 0.0229232 | 5.12827 | 19.8002 | 3.14449 | 0.00460039 | 5.03043e-05 | 1.28828e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12713 | 0.233327 | 762.093ms | 5094 | 160 | 127.197 | 382.131 | 0.0670132 | 0.448287 | 1.78308 | 0.26757 | 0.000636779 | 5.76659e-05 | 4.41696e-05 | 1(Win) | true |
| Glaze | 3566.58 | 0.424883 | 869.331ms | 5094 | 640 | 21435.5 | 1362.09 | 0.17628 | 1.4588 | 5.90872 | 0.910288 | 0.000210726 | 4.04888e-05 | 1.04289e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14394.1 | 0.126172 | 758.073ms | 5094 | 4890 | 886.721 | 337.501 | 0.170273 | 0.397838 | 1.6755 | 0.243227 | 0.00048993 | 4.31961e-05 | 1.52953e-05 | 1(Win) | true |
| Glaze | 4241.09 | 0.214466 | 843.13ms | 5094 | 2560 | 15449.7 | 1145.46 | 0.0534432 | 1.24562 | 5.4413 | 0.804084 | 0.000250218 | 5.51353e-05 | 1.75605e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2715.35 | 0.150894 | 1015.16ms | 8051 | 80 | 1456.41 | 2827.64 | 0.205096 | 1.89037 | 8.53571 | 1.64327 | 0.00170941 | 0.000111787 | 5.12359e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2111.84 | 0.15155 | 1098.89ms | 8051 | 30 | 910.769 | 3635.7 | 0.0412746 | 2.42138 | 11.0148 | 1.78624 | 0.00170165 | 7.03846e-05 | 4.5543e-05 | 2(Loss) | true |
| Glaze | 1423.52 | 0.0431146 | 1273.77ms | 8051 | 4890 | 26444 | 5393.69 | 0.0921874 | 3.57827 | 13.1828 | 2.56962 | 0.00276034 | 0.000100357 | 4.79306e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1291.78 | 0.0532959 | 1330.98ms | 8051 | 4890 | 49070.5 | 5943.77 | 0.112908 | 3.93993 | 14.8707 | 2.42989 | 0.00340795 | 7.21627e-05 | 3.13949e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3406.95 | 0.122825 | 1013.66ms | 8051 | 2560 | 19614.8 | 2253.64 | 0.11885 | 1.51904 | 6.95616 | 1.28406 | 0.00155969 | 3.7311e-05 | 1.49438e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2496.26 | 0.129858 | 1102.03ms | 8051 | 2560 | 40841.5 | 3075.82 | 0.380304 | 2.05342 | 9.43548 | 1.42703 | 0.00163571 | 3.89121e-05 | 1.34882e-05 | 2(Loss) | true |
| Glaze | 1834.64 | 0.126185 | 1212.92ms | 8051 | 40 | 1115.51 | 4185.02 | 0.101057 | 2.78453 | 11.0647 | 2.1016 | 0.00283505 | 2.17364e-05 | 3.1052e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1508.33 | 0.169685 | 1298.34ms | 8051 | 640 | 47750.1 | 5090.42 | 0.0652455 | 3.37978 | 13.0845 | 2.02795 | 0.00274461 | 3.70684e-05 | 1.16445e-05 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14205.4 | 0.132792 | 792.988ms | 9255 | 4890 | 3328.9 | 621.33 | 0.0496417 | 0.380791 | 1.50319 | 0.261697 | 0.000285061 | 2.74875e-05 | 7.07074e-06 | 1(Win) | true |
| Glaze | 3472.82 | 0.12942 | 994.173ms | 9255 | 2560 | 27697 | 2541.52 | 0.100634 | 1.481 | 4.95181 | 0.855538 | 0.000281014 | 4.96775e-05 | 1.94152e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16467.3 | 0.118947 | 783.928ms | 9255 | 4890 | 1987.57 | 535.988 | 0.124565 | 0.330594 | 1.44009 | 0.247758 | 0.000216762 | 2.13006e-05 | 4.88323e-06 | 1(Win) | true |
| Glaze | 3844.08 | 0.119149 | 961.827ms | 9255 | 4890 | 36597.7 | 2296.06 | 0.161957 | 1.34133 | 4.61632 | 0.778498 | 0.000228142 | 2.99402e-05 | 1.00758e-05 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5984.29 | 0.214794 | 762.664ms | 2889 | 40 | 39.1179 | 460.4 | 0.0797044 | 0.936353 | 3.69505 | 0.535479 | 0.000354794 | 8.65351e-06 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 5902.64 | 0.242363 | 764.706ms | 2889 | 2560 | 3276.23 | 466.768 | 0.245806 | 0.952095 | 3.69505 | 0.535479 | 0.000351684 | 7.76112e-05 | 4.1645e-05 | 2(Loss) | true |
| simdjson (ondemand) | 5459.46 | 0.215319 | 769.556ms | 2889 | 2560 | 3022.73 | 504.659 | 0.183007 | 1.01477 | 3.79716 | 0.435445 | 0.000853047 | 2.90704e-05 | 3.78591e-06 | 3(Loss) | true |
| Glaze | 3064.34 | 0.0867794 | 808.268ms | 2889 | 160 | 97.4037 | 899.106 | 0.0423852 | 1.75751 | 6.80547 | 1.23364 | 0.000354794 | 4.32676e-05 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5962.19 | 0.15588 | 767.04ms | 2889 | 4890 | 2537.31 | 462.106 | 0.252644 | 0.935141 | 3.61925 | 0.51748 | 0.00053443 | 3.53927e-05 | 2.54827e-06 | 1(Win) | true |
| Jsonifier | 5889.43 | 0.226525 | 771.125ms | 2889 | 2560 | 2874.9 | 467.816 | 0.102266 | 0.938484 | 3.61925 | 0.51748 | 0.000489194 | 5.40845e-05 | 7.57182e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5740.24 | 0.142286 | 770.592ms | 2889 | 1280 | 596.992 | 479.974 | 0.116842 | 0.963644 | 3.72032 | 0.417792 | 0.00100976 | 3.73183e-05 | 4.59718e-06 | 3(Loss) | true |
| Glaze | 3043.6 | 0.0960707 | 813.09ms | 2889 | 4890 | 3698.37 | 905.231 | 0.239066 | 1.75689 | 6.72897 | 1.21634 | 0.000366527 | 3.05085e-05 | 3.53927e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6776.46 | 0.205201 | 775.809ms | 3808 | 4890 | 5913.64 | 535.912 | 0.0778291 | 0.816543 | 3.2198 | 0.422007 | 0.000268298 | 2.92141e-05 | 5.69246e-06 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 6699.08 | 0.424408 | 778.471ms | 3808 | 1280 | 6775.49 | 542.103 | 0.166296 | 0.818811 | 3.2198 | 0.422007 | 0.000272248 | 5.23158e-05 | 2.60553e-05 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6645.48 | 0.263746 | 777.264ms | 3808 | 2560 | 5318.07 | 546.475 | 0.126323 | 0.83214 | 3.19695 | 0.346114 | 0.000533416 | 4.85204e-05 | 1.84644e-05 | 2(Tie) | true |
| Glaze | 3370.3 | 0.24911 | 833.506ms | 3808 | 640 | 4611.24 | 1077.53 | 0.14042 | 1.59012 | 6.48057 | 1.20746 | 0.000279838 | 2.62605e-05 | 1.0258e-05 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7046.85 | 0.240635 | 781.933ms | 3808 | 40 | 61.5154 | 515.35 | 0.299865 | 0.771698 | 3.16229 | 0.408351 | 0.000262605 | 1.31303e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 6902.68 | 0.207955 | 777.015ms | 3808 | 2560 | 3064.35 | 526.113 | 0.154226 | 0.796441 | 3.16229 | 0.408351 | 0.000386624 | 2.10289e-05 | 3.89804e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6813.79 | 0.249593 | 784.15ms | 3808 | 2560 | 4530.23 | 532.977 | 0.152973 | 0.801293 | 3.13866 | 0.332721 | 0.000539161 | 2.30805e-05 | 2.76966e-06 | 3(Loss) | true |
| Glaze | 3332.96 | 0.194251 | 839.955ms | 3808 | 1280 | 5734.16 | 1089.6 | 0.142267 | 1.57274 | 6.42227 | 1.19433 | 0.000384265 | 1.29251e-05 | 0 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2666.12 | 0.181991 | 831.898ms | 2889 | 30 | 106.11 | 1033.4 | 0.0258114 | 1.97073 | 5.99238 | 1.08377 | 0.00211146 | 6.92281e-05 | 2.3076e-05 | 1(Win) | true |
| Glaze | 2392.61 | 0.276477 | 849.543ms | 2889 | 1280 | 12974.2 | 1151.53 | 0.28191 | 2.21272 | 8.84112 | 1.51713 | 0.000363448 | 3.73183e-05 | 5.40845e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 2202.95 | 0.284419 | 855.985ms | 2889 | 2560 | 32392.6 | 1250.67 | 0.00843225 | 2.38618 | 8.55244 | 1.3001 | 0.000699988 | 8.53182e-05 | 2.46084e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1010.55 | 0.095543 | 1008.16ms | 2889 | 4890 | 33180.4 | 2726.39 | 0.261143 | 5.08354 | 17.3925 | 2.86154 | 0.000367164 | 7.2555e-05 | 1.45818e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3041.14 | 0.250107 | 820.037ms | 2889 | 4890 | 25106.3 | 905.964 | 0.691797 | 1.74966 | 5.4396 | 0.941156 | 0.00138909 | 9.66221e-05 | 3.70915e-05 | 1(Win) | true |
| Glaze | 2640.9 | 0.258409 | 839.755ms | 2889 | 160 | 1162.86 | 1043.27 | 0.178243 | 1.99635 | 8.16476 | 1.34995 | 0.000354794 | 4.75943e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 2434.78 | 0.469616 | 848.361ms | 2889 | 640 | 18073.5 | 1131.59 | 0.17567 | 2.19318 | 7.99827 | 1.15749 | 0.000697149 | 6.76056e-05 | 1.24394e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1042.86 | 0.0980271 | 1008.81ms | 2889 | 4890 | 32797.9 | 2641.94 | 0.180575 | 4.94548 | 16.9841 | 2.7577 | 0.000423792 | 0.000105116 | 4.08432e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8229.76 | 0.254963 | 768.431ms | 2963 | 4890 | 3747.59 | 343.356 | 0.312624 | 0.693909 | 1.59939 | 0.232535 | 0.000458553 | 4.99687e-05 | 1.35274e-05 | 1(Win) | true |
| Glaze | 4111.49 | 0.446239 | 801.752ms | 2963 | 1280 | 12039.6 | 687.279 | 0.337489 | 1.30765 | 3.21532 | 0.482619 | 0.000347515 | 2.21482e-05 | 1.58201e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9520.83 | 0.246342 | 762.214ms | 2963 | 4890 | 2613.97 | 296.795 | 0.0049273 | 0.605388 | 1.42457 | 0.193385 | 0.000338393 | 2.88493e-05 | 5.93551e-06 | 1(Win) | true |
| Glaze | 4242.73 | 0.230995 | 798.862ms | 2963 | 4890 | 11574 | 666.019 | 0.406373 | 1.26466 | 2.73068 | 0.379346 | 0.000339911 | 3.69934e-05 | 6.97077e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3167.56 | 0.617286 | 849.637ms | 3808 | 4890 | 244921 | 1146.5 | 0.0167584 | 1.6549 | 5.36581 | 0.94853 | 0.000532138 | 6.2456e-05 | 1.91718e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2627.86 | 0.296561 | 876.947ms | 3808 | 320 | 5374.86 | 1381.96 | 0.242948 | 1.98096 | 7.0281 | 1.03624 | 0.000954405 | 3.2005e-05 | 7.38577e-06 | 2(Loss) | true |
| Glaze | 2576.88 | 0.136347 | 876.271ms | 3808 | 30 | 110.769 | 1409.3 | 0.282258 | 1.9837 | 8.276 | 1.46481 | 0.00052521 | 7.0028e-05 | 3.5014e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1301.67 | 0.197266 | 1018.03ms | 3808 | 1280 | 38770.9 | 2789.94 | 0.0295232 | 3.94109 | 13.5113 | 2.18671 | 0.00027594 | 3.61082e-05 | 2.0516e-07 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3556.77 | 0.184351 | 846.238ms | 3808 | 320 | 1133.77 | 1021.04 | 0.517459 | 1.48384 | 4.94643 | 0.840336 | 0.000527672 | 3.69288e-05 | 4.1032e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2830.34 | 0.253818 | 875.517ms | 3808 | 2560 | 27152 | 1283.09 | 0.340056 | 1.82104 | 6.60767 | 0.928047 | 0.000531467 | 3.7134e-05 | 2.0516e-06 | 2(Loss) | true |
| Glaze | 2801.65 | 0.268873 | 870.771ms | 3808 | 640 | 7773.9 | 1296.23 | 0.194296 | 1.8572 | 7.85033 | 1.35662 | 0.000297072 | 3.28256e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1323.96 | 0.0816862 | 1020.36ms | 3808 | 4890 | 24550 | 2742.98 | 0.332129 | 3.82321 | 13.2014 | 2.10793 | 0.000348099 | 5.72468e-05 | 9.55904e-06 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9030.7 | 0.295152 | 782.638ms | 4300 | 4890 | 8784.03 | 454.096 | 0.0516818 | 0.608067 | 1.45605 | 0.233256 | 0.000375422 | 4.18985e-05 | 7.32392e-06 | 1(Win) | true |
| Glaze | 2987.04 | 0.70162 | 876.896ms | 4300 | 320 | 29690 | 1372.87 | 0.0443674 | 1.74028 | 3.77884 | 0.636744 | 0.000236192 | 6.10465e-05 | 3.34302e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10354.2 | 0.453453 | 780.372ms | 4300 | 1280 | 4128.39 | 396.053 | 0.13435 | 0.538508 | 1.34674 | 0.207209 | 0.000233467 | 2.41642e-05 | 7.26744e-07 | 1(Win) | true |
| Glaze | 3584.47 | 0.488959 | 856.797ms | 4300 | 640 | 20026.8 | 1144.05 | 0.16882 | 1.45964 | 3.20907 | 0.507209 | 0.000238009 | 3.56105e-05 | 2.90698e-06 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11203.1 | 0.160572 | 4736.6ms | 466906 | 2560 | 1.04271e+07 | 39745.9 | 0.0582092 | 0.453082 | 1.82619 | 0.103014 | 0.000483718 | 2.76647e-05 | 5.98438e-06 | 1(Win) | true |
| simdjson (ondemand) | 9168.31 | 0.0383934 | 5623.37ms | 466906 | 4890 | 1.70021e+06 | 48566.9 | 0.016428 | 0.551962 | 2.12712 | 0.0439747 | 6.98805e-05 | 0.000387466 | 1.79268e-06 | 2(Loss) | true |
| Glaze | 2608.61 | 0.0364022 | 9066.44ms | 466906 | 2560 | 9.88405e+06 | 170695 | 0.0536954 | 1.91916 | 7.74721 | 1.47693 | 0.0025239 | 0.000615179 | 2.06646e-06 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11115.4 | 0.0295326 | 4748.63ms | 466906 | 4890 | 684418 | 40059.5 | 0.371162 | 0.45135 | 1.82507 | 0.102764 | 0.000454758 | 2.23247e-05 | 2.73436e-06 | 1(Win) | true |
| simdjson (ondemand) | 9102.38 | 0.0813718 | 5639.49ms | 466906 | 1280 | 2.02818e+06 | 48918.7 | 0.112273 | 0.556861 | 2.12607 | 0.0437391 | 6.54659e-05 | 0.000948821 | 3.71127e-06 | 2(Loss) | true |
| Glaze | 2623.81 | 0.243787 | 9026.13ms | 466906 | 40 | 6.84665e+06 | 169706 | 0.221543 | 1.91098 | 7.74608 | 1.47668 | 0.00253723 | 0.000639636 | 1.39214e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4363.87 | 0.164678 | 8180.12ms | 699405 | 1280 | 8.1095e+07 | 152847 | 0.221317 | 1.14402 | 4.31682 | 0.737579 | 0.00441463 | 0.00304327 | 4.29606e-06 | 1(Win) | true |
| Glaze | 3902.7 | 0.0485541 | 9130.14ms | 699405 | 2560 | 1.76286e+07 | 170908 | 0.0346006 | 1.29627 | 5.22157 | 1.16245 | 0.00247909 | 0.00102303 | 1.15578e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2315.64 | 0.126037 | 8289.88ms | 767297 | 1280 | 2.03044e+08 | 316004 | 0.194466 | 2.15253 | 8.6478 | 1.18016 | 0.0030322 | 0.100398 | 8.55275e-06 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4416.39 | 0.154846 | 8187.46ms | 699405 | 640 | 3.50028e+07 | 151029 | 0.307845 | 1.14129 | 4.31603 | 0.737401 | 0.00440979 | 0.00290925 | 2.70319e-06 | 1(Win) | true |
| Glaze | 3852.32 | 0.161284 | 9152.06ms | 699405 | 160 | 1.24772e+07 | 173144 | 0.218105 | 1.29067 | 5.22079 | 1.16228 | 0.00244881 | 0.000895011 | 3.30638e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2294.7 | 0.161567 | 8315.18ms | 767297 | 640 | 1.69886e+08 | 318887 | 0.145076 | 2.16441 | 8.64826 | 1.18029 | 0.0032486 | 0.100863 | 1.16175e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3343.85 | 0.0626177 | 9596.2ms | 631514 | 2560 | 3.25616e+07 | 180109 | 0.238201 | 1.50851 | 6.95146 | 1.21163 | 0.00769683 | 2.43283e-05 | 1.10245e-05 | 1(Win) | true |
| Glaze | 2592.94 | 0.0598557 | 6101.23ms | 631514 | 320 | 6.18503e+06 | 232268 | 0.252287 | 1.95487 | 8.44884 | 1.51664 | 0.00370023 | 6.03708e-06 | 4.56245e-06 | 2(Loss) | true |
