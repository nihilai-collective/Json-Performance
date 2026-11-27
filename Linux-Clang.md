# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the Clang 24.0.0 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
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
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1878.7 | 0.138301 | 47.0822ms | 905 | 30 | 12.1103 | 459.4 | 0.079878 | 1.24475 | 1(Win) | true |
| Glaze | 1465.65 | 0.127115 | 63.6648ms | 905 | 30 | 16.8092 | 588.867 | 0.00566091 | 1.61068 | 2(Loss) | true |
| simdjson (ondemand) | 452.186 | 0.070126 | 185.511ms | 905 | 40 | 71.6609 | 1908.67 | 0.0423684 | 5.39892 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1931.14 | 0.123889 | 48.2956ms | 905 | 80 | 24.5259 | 446.925 | 0.0559065 | 1.20931 | 1(Win) | true |
| Glaze | 1474.67 | 0.15714 | 62.966ms | 905 | 30 | 25.3747 | 585.267 | 0.210287 | 1.60862 | 2(Loss) | true |
| simdjson (ondemand) | 474.696 | 0.500271 | 186.086ms | 905 | 640 | 52948.9 | 1818.16 | 0.101941 | 5.14123 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2224.56 | 0.128054 | 41.3255ms | 905 | 80 | 19.7462 | 387.975 | 0.0322082 | 1.04124 | 1(Win) | true |
| Glaze | 207.692 | 0.192727 | 418.31ms | 905 | 2560 | 164202 | 4155.55 | 0.127326 | 11.8475 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4132.95 | 0.0539531 | 28.4301ms | 905 | 1280 | 16.2488 | 208.828 | 0.0981134 | 0.526376 | 1(Win) | true |
| Glaze | 965.355 | 0.16366 | 100.207ms | 905 | 40 | 85.6385 | 894.05 | 0.0839584 | 2.48923 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1350.62 | 0.0261501 | 131.368ms | 1811 | 320 | 35.7821 | 1278.75 | 0.176999 | 1.79675 | 1(Win) | true |
| Glaze | 894.669 | 0.162185 | 196.257ms | 1811 | 4890 | 47933.9 | 1930.44 | 0.0142704 | 2.73046 | 2(Loss) | true |
| simdjson (ondemand) | 451.197 | 0.143824 | 385.304ms | 1811 | 4890 | 148209 | 3827.83 | 0.0105482 | 5.4505 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1379.44 | 0.496458 | 166.071ms | 1811 | 2560 | 98909.1 | 1252.03 | 1.0682 | 1.75666 | 1(Win) | true |
| Glaze | 944.082 | 0.0717565 | 186.319ms | 1811 | 30 | 51.6966 | 1829.4 | 0.0565167 | 2.58649 | 2(Loss) | true |
| simdjson (ondemand) | 435.035 | 0.131171 | 402.792ms | 1811 | 30 | 813.551 | 3970.03 | 0.0587391 | 5.65549 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 367.733 | 0.0166208 | 523.324ms | 1997 | 160 | 118.553 | 5179 | 0.314225 | 6.69881 | 1(Win) | true |
| Glaze | 287.846 | 0.0615691 | 618.887ms | 1798 | 40 | 538.076 | 5957.02 | 0.00153882 | 8.56449 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 946.191 | 0.0240476 | 212.886ms | 1997 | 160 | 37.4855 | 2012.79 | 0.0363433 | 2.58251 | 1(Win) | true |
| Glaze | 600.787 | 0.0563398 | 300.751ms | 1798 | 40 | 103.426 | 2854.1 | 0.109904 | 4.08323 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1465.16 | 0.141537 | 87.581ms | 1313 | 30 | 43.8954 | 854.633 | 0.234567 | 1.6343 | 1(Win) | true |
| Glaze | 931.132 | 0.051585 | 138.721ms | 1313 | 80 | 38.4986 | 1344.79 | 0.0921067 | 2.60757 | 2(Loss) | true |
| simdjson (ondemand) | 358.353 | 0.053577 | 369.824ms | 1313 | 40 | 140.192 | 3494.25 | 0.0767339 | 6.85588 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1662.5 | 0.0343521 | 79.7752ms | 1313 | 640 | 42.8443 | 753.188 | 0.158656 | 1.43814 | 1(Win) | true |
| Glaze | 993.168 | 0.046896 | 129.886ms | 1313 | 80 | 27.9669 | 1260.79 | 0.0287436 | 2.44197 | 2(Loss) | true |
| simdjson (ondemand) | 367.383 | 0.123235 | 344.197ms | 1313 | 4890 | 86271.9 | 3408.37 | 0.0477511 | 6.68699 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 338.329 | 0.0574712 | 375.895ms | 1313 | 40 | 180.972 | 3701.05 | 0.139344 | 7.26771 | 1(Win) | true |
| Glaze | 293.034 | 0.144799 | 432.837ms | 1313 | 30 | 1148.53 | 4273.13 | 0.170543 | 8.39855 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2335.57 | 0.178352 | 63.3496ms | 1313 | 30 | 27.4299 | 536.133 | 0.124502 | 1.00782 | 1(Win) | true |
| Glaze | 1164.27 | 0.0733683 | 117.914ms | 1313 | 160 | 99.6226 | 1075.5 | 0.282787 | 2.07647 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1355.64 | 0.133303 | 289.54ms | 4215 | 30 | 468.717 | 2965.2 | 0.557822 | 1.80919 | 1(Win) | true |
| Glaze | 1006.02 | 0.0885723 | 401.493ms | 4215 | 30 | 375.747 | 3995.67 | 0.276058 | 2.44512 | 2(Loss) | true |
| simdjson (ondemand) | 808.488 | 0.114981 | 500.183ms | 4215 | 4890 | 159813 | 4971.92 | 0.116229 | 3.04644 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2094.05 | 0.0953597 | 235.062ms | 4215 | 80 | 268.066 | 1919.6 | 0.270316 | 1.16605 | 1(Win) | true |
| Glaze | 1309.84 | 0.197013 | 355.631ms | 4215 | 4890 | 178756 | 3068.89 | 0.0645047 | 1.87431 | 2(Loss) | true |
| simdjson (ondemand) | 921.973 | 0.195371 | 470.019ms | 4215 | 2560 | 185746 | 4359.93 | 0.188431 | 2.66945 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1653.08 | 0.120798 | 233.947ms | 4215 | 30 | 258.851 | 2431.67 | 0.0424768 | 1.48084 | 1(Win) | true |
| Glaze | 925.983 | 0.0708621 | 448.277ms | 4215 | 40 | 378.51 | 4341.05 | 0.325662 | 2.65855 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6102.07 | 0.115142 | 73.6177ms | 4215 | 40 | 23.0128 | 658.75 | 0.0126518 | 0.390267 | 1(Win) | true |
| Glaze | 2240.69 | 0.185832 | 193.58ms | 4215 | 4890 | 54347.8 | 1793.97 | 0.239711 | 1.0886 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1610.91 | 0.569386 | 73.9638ms | 1213 | 1280 | 21399.5 | 718.109 | 0.0690357 | 1.48056 | 1(Win) | true |
| Glaze | 936.97 | 0.0968265 | 126.036ms | 1213 | 40 | 57.1635 | 1234.62 | 0.0195703 | 2.58601 | 2(Loss) | true |
| simdjson (ondemand) | 316.582 | 0.164079 | 368.916ms | 1213 | 4890 | 175779 | 3654.06 | 0.0829026 | 7.76591 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1838.15 | 0.431533 | 66.0155ms | 1213 | 30 | 221.264 | 629.333 | 0.159151 | 1.29233 | 1(Win) | true |
| Glaze | 1010.17 | 0.0428434 | 118.12ms | 1213 | 160 | 38.5143 | 1145.16 | 0.102711 | 2.39544 | 2(Loss) | true |
| simdjson (ondemand) | 326.082 | 0.078061 | 361.492ms | 1213 | 40 | 306.759 | 3547.6 | 0.146793 | 7.54046 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 323.431 | 0.12868 | 360.654ms | 1213 | 40 | 847.302 | 3576.68 | 0.13742 | 7.59893 | 1(Win) | true |
| Glaze | 260.322 | 0.180304 | 445.765ms | 1213 | 4890 | 313920 | 4443.76 | 0.1604 | 9.45349 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2263.26 | 0.103209 | 59.1131ms | 1213 | 80 | 22.2627 | 511.125 | 0.0734214 | 1.03709 | 1(Win) | true |
| Glaze | 1107.09 | 0.238221 | 112.141ms | 1213 | 4890 | 30298.7 | 1044.91 | 0.0405488 | 2.18158 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1762.22 | 0.064726 | 5133.16ms | 94653 | 4890 | 5.37545e+06 | 51224.1 | 0.16359 | 1.40421 | 1(Win) | true |
| Jsonifier (two-stage) | 1495.58 | 0.177284 | 6104.44ms | 94653 | 160 | 1.83192e+06 | 60356.5 | 0.0312524 | 1.65468 | 2(Loss) | true |
| Glaze | 1483.59 | 0.12853 | 6163.85ms | 94653 | 320 | 1.95703e+06 | 60844.3 | 0.152527 | 1.66807 | 3(Loss) | true |
| simdjson (ondemand) | 1127.13 | 0.156049 | 8038.21ms | 94653 | 320 | 4.99792e+06 | 80086.4 | 0.0339827 | 2.19583 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2647.83 | 0.0853224 | 4654.78ms | 94653 | 1280 | 1.08299e+06 | 34091.3 | 0.00758475 | 0.934327 | 1(Win) | true |
| Jsonifier (two-stage) | 2051.27 | 0.525868 | 5746.7ms | 94653 | 40 | 2.14209e+06 | 44006 | 0.0887915 | 1.20626 | 2(Loss) | true |
| Glaze | 2001.74 | 0.230797 | 5800.46ms | 94653 | 160 | 1.73314e+06 | 45094.9 | 0.00413035 | 1.23611 | 3(Loss) | true |
| simdjson (ondemand) | 1429.91 | 0.0562828 | 8364ms | 94653 | 2560 | 3.23178e+06 | 63128.5 | 0.114478 | 1.73068 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19086.8 | 0.289786 | 477.894ms | 94653 | 1280 | 240419 | 4729.35 | 0.364861 | 0.129003 | 1(Win) | true |
| Glaze | 5586.3 | 0.0841249 | 1620.27ms | 94653 | 4890 | 903605 | 16158.8 | 0.114989 | 0.442491 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19194.8 | 0.076527 | 475.697ms | 94653 | 80 | 1036.15 | 4702.74 | 0.018337 | 0.128244 | 1(Win) | true |
| Glaze | 6157.83 | 0.0849309 | 1468.69ms | 94653 | 4890 | 757973 | 14659.1 | 0.211249 | 0.401352 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2037.79 | 0.111274 | 5833.95ms | 124597 | 1280 | 5.38881e+06 | 58310.8 | 0.021372 | 1.2144 | 1(Win) | true |
| Jsonifier (two-stage) | 1754.84 | 0.100902 | 6812.31ms | 124597 | 640 | 2.98759e+06 | 67712.8 | 0.00840566 | 1.4103 | 2(Loss) | true |
| Glaze | 1703.75 | 0.0395075 | 6989.81ms | 124597 | 4890 | 3.71254e+06 | 69743.2 | 0.0465803 | 1.45261 | 3(Loss) | true |
| simdjson (ondemand) | 1445.52 | 0.0574763 | 8238.9ms | 124597 | 2560 | 5.71459e+06 | 82202.2 | 0.0983034 | 1.7122 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2823.2 | 0.0642408 | 5477.36ms | 124597 | 4890 | 3.57488e+06 | 42088.7 | 0.0788225 | 0.876419 | 1(Win) | true |
| Jsonifier (two-stage) | 2348.95 | 0.268414 | 6309.55ms | 124597 | 160 | 2.94984e+06 | 50586.3 | 0.108336 | 1.05348 | 2(Loss) | true |
| Glaze | 2217.97 | 0.191066 | 6591.15ms | 124597 | 320 | 3.35291e+06 | 53573.7 | 0.0864067 | 1.11571 | 3(Loss) | true |
| simdjson (ondemand) | 1842.44 | 0.0623278 | 7694.41ms | 124597 | 1280 | 2.06825e+06 | 64493.2 | 0.0934133 | 1.34319 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19484.6 | 0.0461554 | 667.267ms | 136037 | 30 | 283.333 | 6658.33 | 0.335293 | 0.126568 | 1(Win) | true |
| Glaze | 6251.84 | 0.138188 | 2082.91ms | 136076 | 2560 | 2.10634e+06 | 20757.4 | 0.194542 | 0.395489 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19701.3 | 0.193727 | 662.159ms | 136037 | 2560 | 416624 | 6585.09 | 0.0349982 | 0.125183 | 1(Win) | true |
| Glaze | 6655.69 | 0.0737927 | 1949.03ms | 136076 | 4890 | 1.01231e+06 | 19497.9 | 0.020415 | 0.371486 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 863.271 | 0.0868178 | 7748.42ms | 2251027 | 160 | 7.45769e+08 | 2.48676e+06 | 0.091199 | 2.86789 | 1(Win) | true |
| Jsonifier (two-stage) | 799.651 | 0.0316934 | 8345.5ms | 2251027 | 30 | 2.17179e+07 | 2.68461e+06 | 0.254563 | 3.09606 | 2(Loss) | true |
| Glaze | 771.369 | 0.373108 | 8727.78ms | 2251027 | 80 | 8.62573e+09 | 2.78303e+06 | 0.369619 | 3.20959 | 3(Loss) | true |
| simdjson (ondemand) | 758.53 | 0.0347619 | 8816.98ms | 2251027 | 80 | 7.74306e+07 | 2.83014e+06 | 0.230135 | 3.26391 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1044.23 | 0.0458639 | 7691.01ms | 2251027 | 30 | 2.66705e+07 | 2.05581e+06 | 0.150058 | 2.3709 | 1(Win) | true |
| Jsonifier (two-stage) | 952.595 | 0.0515968 | 8303.04ms | 2251027 | 80 | 1.08163e+08 | 2.25358e+06 | 0.112871 | 2.59898 | 2(Loss) | true |
| Glaze | 934.585 | 0.0611663 | 8662.21ms | 2251027 | 30 | 5.92201e+07 | 2.297e+06 | 0.0116196 | 2.64906 | 3(Loss) | true |
| simdjson (ondemand) | 916.118 | 0.0871204 | 8728.56ms | 2251027 | 80 | 3.33418e+08 | 2.34331e+06 | 0.205371 | 2.70246 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2039.41 | 0.0352092 | 6160.44ms | 2090326 | 320 | 3.79037e+07 | 977484 | 0.130632 | 1.21394 | 1(Win) | true |
| Glaze | 1032.2 | 0.0384794 | 6163.29ms | 2090234 | 80 | 4.41785e+07 | 1.93122e+06 | 0.066016 | 2.39854 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2041.98 | 0.0496477 | 6172.8ms | 2090326 | 30 | 7.04764e+06 | 976253 | 0.130019 | 1.21241 | 1(Win) | true |
| Glaze | 1056.97 | 0.0380003 | 5892.15ms | 2090234 | 40 | 2.05446e+07 | 1.88595e+06 | 0.0902581 | 2.34232 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1778.88 | 0.0745634 | 8999.27ms | 5373214 | 80 | 3.69075e+08 | 2.88062e+06 | 0.105088 | 1.39176 | 1(Win) | true |
| Jsonifier | 1755.08 | 0.0951693 | 9071.32ms | 5373214 | 40 | 3.08837e+08 | 2.9197e+06 | 0.234672 | 1.41063 | 2(Loss) | true |
| simdjson (ondemand) | 1708.34 | 0.0329106 | 9311.18ms | 5373214 | 160 | 1.55924e+08 | 2.99958e+06 | 0.128379 | 1.44923 | 3(Loss) | true |
| Glaze | 1605.72 | 0.101452 | 9901.98ms | 5373214 | 40 | 4.19291e+08 | 3.19128e+06 | 0.0377464 | 1.54186 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2088.49 | 0.0443444 | 8931.05ms | 5373214 | 80 | 9.47045e+07 | 2.45359e+06 | 0.024005 | 1.18544 | 1(Win) | true |
| Jsonifier | 2049.1 | 0.0628145 | 9299.26ms | 5373214 | 80 | 1.97401e+08 | 2.50075e+06 | 0.101426 | 1.20822 | 2(Loss) | true |
| simdjson (ondemand) | 2027.27 | 0.0376452 | 9225.07ms | 5373214 | 30 | 2.71635e+07 | 2.52768e+06 | 0.331433 | 1.22123 | 3(Loss) | true |
| Glaze | 1855.97 | 0.0792852 | 10018.1ms | 5373214 | 30 | 1.43758e+08 | 2.76098e+06 | 0.335964 | 1.33395 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5750.43 | 0.0445717 | 6986.43ms | 6661989 | 80 | 1.94006e+07 | 1.10485e+06 | 0.036987 | 0.430529 | 1(Win) | true |
| Glaze | 3343.3 | 0.0303363 | 5915.63ms | 6661897 | 160 | 5.31728e+07 | 1.9003e+06 | 0.165671 | 0.740501 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5730.16 | 0.107216 | 7027.5ms | 6661989 | 30 | 4.23948e+07 | 1.10876e+06 | 0.168287 | 0.43205 | 1(Win) | true |
| Glaze | 3610.58 | 0.0818151 | 5460.2ms | 6661897 | 160 | 3.31612e+08 | 1.75963e+06 | 0.289146 | 0.685696 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2164.66 | 0.272707 | 5488.16ms | 500299 | 80 | 2.89042e+07 | 220414 | 0.326433 | 1.14352 | 1(Win) | true |
| Jsonifier (two-stage) | 1850.32 | 0.149982 | 6510.92ms | 500299 | 160 | 2.3931e+07 | 257859 | 0.123948 | 1.33777 | 2(Loss) | true |
| Glaze | 1556.83 | 0.0755349 | 7863.52ms | 500299 | 640 | 3.42968e+07 | 306471 | 0.112649 | 1.59009 | 3(Loss) | true |
| simdjson (ondemand) | 1046.95 | 0.150998 | 5830.01ms | 500299 | 30 | 1.4206e+07 | 455726 | 0.0368288 | 2.36451 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2788.74 | 0.192078 | 5350.74ms | 500299 | 160 | 1.72791e+07 | 171089 | 0.588539 | 0.887627 | 1(Win) | true |
| Jsonifier (two-stage) | 2275.25 | 0.106896 | 6273.21ms | 500299 | 320 | 1.60794e+07 | 209701 | 0.0920807 | 1.08797 | 2(Loss) | true |
| Glaze | 1808.02 | 0.204694 | 7739.78ms | 500299 | 80 | 2.33429e+07 | 263892 | 0.4783 | 1.3692 | 3(Loss) | true |
| simdjson (ondemand) | 1188.4 | 0.1552 | 5519.72ms | 500299 | 80 | 3.10605e+07 | 401483 | 0.351836 | 2.08311 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10411.1 | 0.0711641 | 4615.71ms | 500299 | 2560 | 2.72287e+06 | 45828.1 | 0.0542827 | 0.237638 | 1(Win) | true |
| Glaze | 3743.09 | 0.138953 | 6434.06ms | 500299 | 320 | 1.0039e+07 | 127468 | 0.0571044 | 0.661216 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10239.8 | 0.382379 | 4657.71ms | 500299 | 160 | 5.07908e+06 | 46594.9 | 0.239749 | 0.241618 | 1(Win) | true |
| Glaze | 4255.99 | 0.0884589 | 5794.56ms | 500299 | 1280 | 1.25879e+07 | 112106 | 0.00938058 | 0.581581 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3814.21 | 0.136955 | 7376.45ms | 1151920 | 320 | 4.97903e+07 | 288017 | 0.0328768 | 0.649003 | 1(Win) | true |
| Jsonifier (two-stage) | 3563.08 | 0.25993 | 7738.91ms | 1151920 | 640 | 4.11042e+08 | 308316 | 0.403131 | 0.69473 | 2(Loss) | true |
| Glaze | 2439.8 | 0.0885305 | 5756.34ms | 1151920 | 320 | 5.08479e+07 | 450266 | 0.268087 | 1.01467 | 3(Loss) | true |
| simdjson (ondemand) | 2219.31 | 0.14209 | 6208.1ms | 1151920 | 80 | 3.95754e+07 | 495000 | 0.012501 | 1.11546 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4396.34 | 0.164479 | 7235.08ms | 1151920 | 320 | 5.40549e+07 | 249880 | 0.0667203 | 0.563078 | 1(Win) | true |
| Jsonifier (two-stage) | 4232.04 | 0.0677947 | 7535.81ms | 1151920 | 640 | 1.98206e+07 | 259581 | 0.179171 | 0.584935 | 2(Loss) | true |
| Glaze | 2694.76 | 0.110459 | 5636.65ms | 1151920 | 160 | 3.24433e+07 | 407664 | 0.182504 | 0.918681 | 3(Loss) | true |
| simdjson (ondemand) | 2643 | 0.207433 | 5646.46ms | 1151920 | 40 | 2.97347e+07 | 415647 | 0.103466 | 0.93665 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17254.7 | 0.252773 | 8265.65ms | 1439562 | 160 | 6.47186e+06 | 79565.4 | 0.00904049 | 0.143433 | 1(Win) | true |
| Glaze | 5385.25 | 0.0659025 | 6580.41ms | 1439584 | 640 | 1.80653e+07 | 254936 | 0.161873 | 0.459661 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16090.6 | 0.0675491 | 8545.07ms | 1439562 | 2560 | 8.5035e+06 | 85321.6 | 0.392313 | 0.153805 | 1(Win) | true |
| Glaze | 6500.78 | 0.066356 | 5392.48ms | 1439584 | 640 | 1.25685e+07 | 211189 | 0.00524606 | 0.380796 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2268.59 | 0.0388719 | 2329.5ms | 56369 | 40 | 3393.9 | 23696.5 | 0.606065 | 1.09006 | 1(Win) | true |
| Jsonifier (two-stage) | 1931.62 | 0.830892 | 2799.6ms | 56369 | 80 | 4.27776e+06 | 27830.4 | 0.888493 | 1.28049 | 2(Loss) | true |
| Glaze | 1493.75 | 0.193909 | 3602.1ms | 56369 | 640 | 3.11675e+06 | 35988.4 | 0.0015543 | 1.65613 | 3(Loss) | true |
| simdjson (ondemand) | 828.31 | 0.0481756 | 6601.91ms | 56369 | 4890 | 4.78033e+06 | 64900.4 | 0.0766493 | 2.98778 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3404.95 | 0.122986 | 1968.93ms | 56369 | 2560 | 965186 | 15788.1 | 0.0271813 | 0.725919 | 1(Win) | true |
| Jsonifier (two-stage) | 2547.55 | 0.280446 | 2534.4ms | 56369 | 320 | 1.12069e+06 | 21101.8 | 0.0241924 | 0.97061 | 2(Loss) | true |
| Glaze | 1900.59 | 0.0794901 | 3220.19ms | 56369 | 4890 | 2.47194e+06 | 28284.7 | 0.101594 | 1.30139 | 3(Loss) | true |
| simdjson (ondemand) | 962.92 | 0.317243 | 6012.61ms | 56369 | 80 | 2.50943e+06 | 55827.8 | 0.0469975 | 2.56996 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15234.1 | 0.0786654 | 354.443ms | 56369 | 40 | 308.23 | 3528.78 | 0.176096 | 0.16133 | 1(Win) | true |
| Glaze | 3922.92 | 0.102467 | 1377.11ms | 56369 | 2560 | 504747 | 13703.5 | 0.24995 | 0.629926 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15496.6 | 0.0688152 | 349.188ms | 56369 | 40 | 227.949 | 3469 | 0.119293 | 0.15848 | 1(Win) | true |
| Glaze | 4158.07 | 0.0719851 | 1299.88ms | 56369 | 4890 | 423536 | 12928.5 | 0.00807431 | 0.59419 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2902.53 | 0.0957318 | 2765.24ms | 83958 | 2560 | 1.78535e+06 | 27585.8 | 3.5401e-05 | 0.852158 | 1(Win) | true |
| Jsonifier (two-stage) | 2723.14 | 0.112261 | 2949.57ms | 83958 | 1280 | 1.39461e+06 | 29403.1 | 0.0950872 | 0.908338 | 2(Loss) | true |
| Glaze | 1961.61 | 0.064321 | 4091.52ms | 83958 | 4890 | 3.37066e+06 | 40817.9 | 0.062542 | 1.26131 | 3(Loss) | true |
| simdjson (ondemand) | 1200.66 | 0.0854505 | 6671.83ms | 83958 | 1280 | 4.15646e+06 | 66687.1 | 0.120336 | 2.06121 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3744.69 | 0.0914294 | 2483.56ms | 83958 | 2560 | 978375 | 21381.9 | 0.192772 | 0.660358 | 1(Win) | true |
| Jsonifier (two-stage) | 3393.05 | 0.0882619 | 2704.69ms | 83958 | 2560 | 1.11053e+06 | 23597.8 | 0.0194905 | 0.728825 | 2(Loss) | true |
| Glaze | 2354.32 | 0.107049 | 3745.47ms | 83958 | 1280 | 1.69657e+06 | 34009.3 | 0.0381712 | 1.0508 | 3(Loss) | true |
| simdjson (ondemand) | 1381.48 | 0.0821473 | 6132.46ms | 83958 | 2560 | 5.80314e+06 | 57958.6 | 0.194965 | 1.7913 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17119.8 | 0.0423342 | 506.706ms | 94370 | 30 | 148.585 | 5256.97 | 0.0386938 | 0.14388 | 1(Win) | true |
| Glaze | 3458.56 | 0.253505 | 2607.43ms | 94370 | 320 | 1.39252e+06 | 26021.9 | 0.108175 | 0.715143 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18545.5 | 0.0303625 | 491.078ms | 94370 | 80 | 173.682 | 4852.84 | 0.102155 | 0.132764 | 1(Win) | true |
| Glaze | 3681.92 | 0.0938275 | 2519.57ms | 94370 | 1280 | 673268 | 24443.3 | 0.184917 | 0.671691 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1941.48 | 0.0684686 | 2629.6ms | 53331 | 4890 | 1.57321e+06 | 26196.8 | 0.126035 | 1.27394 | 1(Win) | true |
| Jsonifier (two-stage) | 1567.08 | 0.124895 | 3706.46ms | 53331 | 2560 | 4.20639e+06 | 32455.5 | 0.122618 | 1.5786 | 2(Loss) | true |
| Glaze | 1440.47 | 0.0730064 | 3555.87ms | 53331 | 4890 | 3.24924e+06 | 35308.2 | 0.110779 | 1.71749 | 3(Loss) | true |
| simdjson (ondemand) | 991.33 | 0.144399 | 5124.78ms | 53331 | 1280 | 7.02522e+06 | 51305.2 | 0.111341 | 2.49616 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2656.96 | 0.119545 | 2456.89ms | 53331 | 2560 | 1.34057e+06 | 19142.3 | 0.107054 | 0.930551 | 1(Win) | true |
| Jsonifier (two-stage) | 2044.01 | 0.0758101 | 2996.8ms | 53331 | 4890 | 1.74003e+06 | 24882.7 | 0.158897 | 1.20993 | 2(Loss) | true |
| Glaze | 1826.56 | 0.112549 | 3339.86ms | 53331 | 1280 | 1.25716e+06 | 27845 | 0.0430132 | 1.35417 | 3(Loss) | true |
| simdjson (ondemand) | 1141.63 | 0.108444 | 5089.49ms | 53331 | 640 | 1.49381e+06 | 44550.5 | 0.0793689 | 2.16739 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16066.5 | 0.141651 | 346.547ms | 58581 | 40 | 970.449 | 3477.25 | 0.0772279 | 0.152952 | 1(Win) | true |
| Glaze | 5981.02 | 0.0942286 | 937.807ms | 58581 | 4890 | 378824 | 9340.75 | 0.0103069 | 0.412802 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16682.9 | 0.176143 | 338.095ms | 58581 | 2560 | 89072.9 | 3348.78 | 0.0503545 | 0.147258 | 1(Win) | true |
| Glaze | 6792.82 | 0.0983261 | 836.454ms | 58581 | 40 | 2615.84 | 8224.45 | 0.134536 | 0.363339 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2281.61 | 0.169161 | 2731.67ms | 65103 | 640 | 1.35613e+06 | 27212 | 0.207934 | 1.08402 | 1(Win) | true |
| Jsonifier (two-stage) | 1939.75 | 0.0932376 | 3089.63ms | 65103 | 2560 | 2.27999e+06 | 32007.8 | 0.251454 | 1.27525 | 2(Loss) | true |
| Glaze | 1626.45 | 0.127281 | 3833.47ms | 65103 | 1280 | 3.02176e+06 | 38173.5 | 0.143942 | 1.52118 | 3(Loss) | true |
| simdjson (ondemand) | 1249.43 | 0.140955 | 5038.73ms | 65103 | 640 | 3.13992e+06 | 49692.4 | 0.00139611 | 1.98053 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3212.94 | 0.100096 | 2360.59ms | 65103 | 2560 | 957797 | 19324.1 | 0.00712709 | 0.769547 | 1(Win) | true |
| Jsonifier (two-stage) | 2683.13 | 0.538757 | 2739.53ms | 65103 | 160 | 2.4867e+06 | 23139.8 | 0.110159 | 0.92168 | 2(Loss) | true |
| Glaze | 2008.66 | 0.0873099 | 3620.84ms | 65103 | 2560 | 1.86447e+06 | 30909.6 | 0.412049 | 1.23153 | 3(Loss) | true |
| simdjson (ondemand) | 1373.65 | 0.0573353 | 5078.16ms | 65103 | 4890 | 3.284e+06 | 45198.6 | 0.114591 | 1.80132 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16541.7 | 0.0955528 | 457.001ms | 78778 | 30 | 565.013 | 4541.77 | 0.169251 | 0.148847 | 1(Win) | true |
| Glaze | 5168.96 | 0.120263 | 1470.12ms | 78778 | 2560 | 782181 | 14534.6 | 0.126282 | 0.478123 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16650.3 | 0.11052 | 453.029ms | 78778 | 30 | 746.051 | 4512.13 | 0.0066483 | 0.147757 | 1(Win) | true |
| Glaze | 6021.33 | 0.0360026 | 1268.79ms | 78778 | 40 | 807.148 | 12477.1 | 0.117877 | 0.410337 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2233.34 | 0.0807593 | 511.105ms | 11812 | 30 | 497.789 | 5043.93 | 0.0726418 | 1.10255 | 1(Win) | true |
| Jsonifier (two-stage) | 1845.02 | 0.0653387 | 615.031ms | 11812 | 30 | 477.43 | 6105.53 | 0.120801 | 1.33595 | 2(Loss) | true |
| Glaze | 1691.06 | 0.086076 | 732.089ms | 11812 | 30 | 986.317 | 6661.4 | 0.498868 | 1.45854 | 3(Loss) | true |
| simdjson (ondemand) | 1007.78 | 0.157929 | 1124.53ms | 11812 | 1280 | 398890 | 11177.9 | 0.0201809 | 2.45101 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2464.78 | 0.041059 | 496.176ms | 11812 | 80 | 281.706 | 4570.3 | 0.0257161 | 0.998795 | 1(Win) | true |
| Jsonifier (two-stage) | 1980.44 | 0.141688 | 607.35ms | 11812 | 4890 | 317614 | 5688.04 | 0.259034 | 1.24436 | 2(Loss) | true |
| Glaze | 1859.91 | 0.141401 | 642.677ms | 11812 | 2560 | 187761 | 6056.63 | 0.0270954 | 1.32538 | 3(Loss) | true |
| simdjson (ondemand) | 1054.04 | 0.176057 | 1112.48ms | 11812 | 1280 | 453163 | 10687.3 | 0.122403 | 2.34273 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12199.4 | 0.0993136 | 95.5194ms | 11812 | 80 | 67.2783 | 923.388 | 0.16623 | 0.197297 | 1(Win) | true |
| Glaze | 3135.96 | 0.199205 | 377.306ms | 11812 | 30 | 1536.12 | 3592.13 | 0.012993 | 0.783889 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12733.2 | 0.0354811 | 91.6749ms | 11812 | 320 | 31.5293 | 884.678 | 0.066717 | 0.188739 | 1(Win) | true |
| Glaze | 3370.95 | 0.21367 | 340.765ms | 11812 | 40 | 2039.33 | 3341.72 | 0.141594 | 0.728791 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3585.85 | 0.136024 | 680.205ms | 25388 | 4890 | 412491 | 6752.05 | 0.134434 | 0.687799 | 1(Win) | true |
| Jsonifier (two-stage) | 3300.09 | 0.0496321 | 786.01ms | 25388 | 30 | 397.789 | 7336.73 | 0.0868533 | 0.747427 | 2(Loss) | true |
| Glaze | 2451.24 | 0.0530626 | 987.92ms | 25388 | 40 | 1098.81 | 9877.4 | 0.0148509 | 1.00736 | 3(Loss) | true |
| simdjson (ondemand) | 2035.37 | 0.134191 | 1193.84ms | 25388 | 2560 | 652315 | 11895.5 | 0.0715886 | 1.2137 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3834.53 | 0.134133 | 671.235ms | 25388 | 2560 | 183629 | 6314.18 | 0.0179688 | 0.643044 | 1(Win) | true |
| Jsonifier (two-stage) | 3531.14 | 0.0519453 | 730.483ms | 25388 | 30 | 380.575 | 6856.67 | 0.0982978 | 0.698439 | 2(Loss) | true |
| Glaze | 2644.06 | 0.118711 | 958.441ms | 25388 | 2560 | 302509 | 9157.08 | 0.0408286 | 0.933743 | 3(Loss) | true |
| simdjson (ondemand) | 2106.58 | 0.659702 | 1191.97ms | 25388 | 80 | 459925 | 11493.5 | 0.0353337 | 1.17239 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17813.3 | 0.104473 | 171.201ms | 31235 | 30 | 91.5644 | 1672.23 | 0.00398684 | 0.136762 | 1(Win) | true |
| Glaze | 5325.79 | 0.171444 | 564.206ms | 31235 | 2560 | 235396 | 5593.17 | 0.115179 | 0.462727 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18531 | 0.0832353 | 165.166ms | 31235 | 30 | 53.7057 | 1607.47 | 0.0828775 | 0.131515 | 1(Win) | true |
| Glaze | 5731.29 | 0.106606 | 523.178ms | 31235 | 4890 | 150124 | 5197.44 | 0.157824 | 0.429682 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2981.49 | 0.235956 | 3492.35ms | 108313 | 160 | 1.06925e+06 | 34645.6 | 0.00409521 | 0.829776 | 1(Win) | true |
| Jsonifier (two-stage) | 2435.29 | 0.0546146 | 4263.42ms | 108313 | 4890 | 2.62413e+06 | 42416 | 0.231088 | 1.016 | 2(Loss) | true |
| Glaze | 1685.17 | 0.0961877 | 6094.19ms | 108313 | 1280 | 4.44964e+06 | 61296.8 | 0.280929 | 1.46855 | 3(Loss) | true |
| simdjson (ondemand) | 653.854 | 0.131768 | 8150.89ms | 108313 | 160 | 6.93335e+06 | 157979 | 0.00213236 | 3.78587 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3421.55 | 0.0964681 | 3200.91ms | 108313 | 1280 | 1.08566e+06 | 30189.7 | 0.107622 | 0.722962 | 1(Win) | true |
| Jsonifier (two-stage) | 2763.75 | 0.16851 | 4097.51ms | 108313 | 320 | 1.26929e+06 | 37375 | 0.0912711 | 0.895167 | 2(Loss) | true |
| Glaze | 1835.16 | 0.07397 | 5850.01ms | 108313 | 2560 | 4.43775e+06 | 56286.7 | 0.164517 | 1.34848 | 3(Loss) | true |
| simdjson (ondemand) | 673.395 | 0.0613571 | 7959.15ms | 108313 | 640 | 5.66931e+06 | 153395 | 0.0206332 | 3.67597 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16656.5 | 0.12043 | 623.615ms | 108313 | 4890 | 272755 | 6201.49 | 0.020235 | 0.148001 | 1(Win) | true |
| Glaze | 3879.68 | 0.131326 | 2687.93ms | 108313 | 1280 | 1.56488e+06 | 26624.7 | 0.0501577 | 0.637537 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16849.2 | 0.0287004 | 620.686ms | 108313 | 30 | 92.8747 | 6130.57 | 0.147567 | 0.146338 | 1(Win) | true |
| Glaze | 4129.73 | 0.0571414 | 2562.22ms | 108313 | 4890 | 998915 | 25012.6 | 0.030774 | 0.59889 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3810.36 | 0.205946 | 4622.24ms | 183677 | 160 | 1.43419e+06 | 45971.6 | 0.177216 | 0.649402 | 1(Win) | true |
| Jsonifier (two-stage) | 3588.04 | 0.108033 | 4964.35ms | 183677 | 640 | 1.78029e+06 | 48819.9 | 0.0607924 | 0.689649 | 2(Loss) | true |
| Glaze | 2235.48 | 0.0500536 | 7864.96ms | 183677 | 4890 | 7.52223e+06 | 78358.1 | 0.390191 | 1.10713 | 3(Loss) | true |
| simdjson (ondemand) | 1080.81 | 0.138386 | 8375.07ms | 183677 | 160 | 8.04851e+06 | 162071 | 0.147487 | 2.29032 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4234.78 | 0.0941217 | 4343.68ms | 183677 | 4890 | 7.41202e+06 | 41364.2 | 0.513022 | 0.584271 | 1(Win) | true |
| Jsonifier (two-stage) | 4027.98 | 0.078698 | 4604.84ms | 183677 | 2560 | 2.99849e+06 | 43487.8 | 0.155146 | 0.614281 | 2(Loss) | true |
| Glaze | 2373.92 | 0.0547774 | 7582.79ms | 183677 | 1280 | 2.09118e+06 | 73788.7 | 0.206131 | 1.04256 | 3(Loss) | true |
| simdjson (ondemand) | 1114.49 | 0.112107 | 8166.34ms | 183677 | 160 | 4.9676e+06 | 157174 | 0.030709 | 2.22111 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21537.5 | 0.1144 | 954.266ms | 213963 | 2560 | 300730 | 9474.23 | 0.0200956 | 0.114644 | 1(Win) | true |
| Glaze | 4118.74 | 0.125347 | 4982.53ms | 213963 | 1280 | 4.93613e+06 | 49542.2 | 0.0413649 | 0.600791 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21656.3 | 0.24287 | 953.22ms | 213963 | 1280 | 670297 | 9422.24 | 0.275131 | 0.11401 | 1(Win) | true |
| Glaze | 4460.49 | 0.0942357 | 4631.96ms | 213963 | 1280 | 2.37877e+06 | 45746.3 | 0.0141527 | 0.554742 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 847.645 | 0.377442 | 6513.89ms | 1834197 | 80 | 4.85349e+09 | 2.06363e+06 | 0.389698 | 2.92075 | 1(Win) | true |
| Jsonifier (two-stage) | 779.781 | 0.81408 | 7095.51ms | 1834197 | 80 | 2.66791e+10 | 2.24323e+06 | 1.06403 | 3.17495 | 2(Loss) | true |
| Glaze | 693.518 | 0.0904209 | 7886.18ms | 1834197 | 30 | 1.5604e+08 | 2.52225e+06 | 0.183367 | 3.56987 | 3(Loss) | true |
| simdjson (ondemand) | 549.026 | 0.183126 | 9944.42ms | 1834197 | 30 | 1.02124e+09 | 3.18605e+06 | 1.06052 | 4.5089 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 960.841 | 0.0437563 | 6403.76ms | 1834197 | 160 | 1.01529e+08 | 1.82052e+06 | 0.246577 | 2.57661 | 1(Win) | true |
| Jsonifier (two-stage) | 816.583 | 0.190785 | 7512.84ms | 1834197 | 30 | 5.01072e+08 | 2.14213e+06 | 0.594645 | 3.03186 | 2(Loss) | true |
| Glaze | 771.795 | 0.0501031 | 7879.8ms | 1834197 | 160 | 2.06318e+08 | 2.26644e+06 | 0.285249 | 3.20784 | 3(Loss) | true |
| simdjson (ondemand) | 624.584 | 0.217988 | 9290.26ms | 1834197 | 30 | 1.11814e+09 | 2.80063e+06 | 0.035513 | 3.96365 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1359.42 | 0.0912405 | 8495.94ms | 1922245 | 160 | 2.42217e+08 | 1.34851e+06 | 0.0038632 | 1.82117 | 1(Win) | true |
| Glaze | 671.394 | 0.108613 | 8215.49ms | 1833577 | 40 | 3.20084e+08 | 2.60448e+06 | 0.625429 | 3.68731 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1419.9 | 0.0933876 | 8179.03ms | 1922245 | 80 | 1.16297e+08 | 1.29107e+06 | 0.0132924 | 1.74359 | 1(Win) | true |
| Glaze | 674.793 | 0.0524111 | 8127.1ms | 1833577 | 30 | 5.53382e+07 | 2.59136e+06 | 0.337161 | 3.66882 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2558.37 | 0.275953 | 8720.34ms | 7351818 | 80 | 4.57534e+09 | 2.74052e+06 | 1.01183 | 0.967693 | 1(Win) | true |
| Jsonifier (two-stage) | 2535.9 | 0.13316 | 8597.29ms | 7351818 | 30 | 4.06624e+08 | 2.7648e+06 | 1.11606 | 0.976178 | 2(Loss) | true |
| simdjson (ondemand) | 2072.38 | 0.140619 | 5146.55ms | 7351818 | 30 | 6.78985e+08 | 3.38318e+06 | 0.748535 | 1.19451 | 3(Loss) | true |
| Glaze | 2023.22 | 0.418571 | 5285.43ms | 7351818 | 30 | 6.31192e+09 | 3.46538e+06 | 1.93116 | 1.22356 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2870.42 | 0.205297 | 8448.66ms | 7351818 | 80 | 2.01167e+09 | 2.44259e+06 | 0.185124 | 0.862493 | 1(Win) | true |
| Jsonifier | 2649.55 | 0.225385 | 9088.44ms | 7351818 | 80 | 2.84569e+09 | 2.6462e+06 | 0.324978 | 0.93437 | 2(Loss) | true |
| simdjson (ondemand) | 2345.84 | 0.186586 | 10272.5ms | 7351818 | 40 | 1.24397e+09 | 2.9888e+06 | 1.64501 | 1.05531 | 3(Loss) | true |
| Glaze | 2140.06 | 0.147337 | 5272.31ms | 7351818 | 40 | 9.3201e+08 | 3.27618e+06 | 2.02122 | 1.15678 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4927.84 | 0.210017 | 5755.49ms | 10018896 | 40 | 6.6328e+08 | 1.93893e+06 | 1.42172 | 0.502364 | 1(Win) | true |
| Glaze | 3172.74 | 0.184261 | 8986.65ms | 9930228 | 160 | 4.83991e+09 | 2.98487e+06 | 1.35663 | 0.780264 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4961.82 | 0.075738 | 6151.86ms | 10018896 | 30 | 6.38128e+07 | 1.92566e+06 | 0.265471 | 0.498931 | 1(Win) | true |
| Glaze | 3637.62 | 0.0996374 | 7901.83ms | 9930228 | 30 | 2.0186e+08 | 2.60341e+06 | 1.07651 | 0.680553 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 810.748 | 0.190456 | 6729.97ms | 1834197 | 30 | 5.06559e+08 | 2.15755e+06 | 0.276368 | 3.05365 | 1(Win) | true |
| Jsonifier (two-stage) | 722.971 | 0.101095 | 7570.69ms | 1834197 | 80 | 4.78633e+08 | 2.4195e+06 | 0.0646419 | 3.4243 | 2(Loss) | true |
| Glaze | 645.357 | 0.199814 | 8451.3ms | 1834197 | 160 | 4.69313e+09 | 2.71048e+06 | 0.796283 | 3.83606 | 3(Loss) | true |
| simdjson (ondemand) | 554.528 | 0.289123 | 9623.3ms | 1834197 | 160 | 1.33085e+10 | 3.15444e+06 | 0.00945938 | 4.46435 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 904.107 | 0.123464 | 6786.33ms | 1834197 | 160 | 9.12965e+08 | 1.93476e+06 | 0.206946 | 2.73833 | 1(Win) | true |
| Jsonifier (two-stage) | 809.209 | 0.649634 | 7524.38ms | 1834197 | 80 | 1.5776e+10 | 2.16165e+06 | 0.202256 | 3.05945 | 2(Loss) | true |
| Glaze | 754.176 | 0.116688 | 8305.54ms | 1834197 | 40 | 2.92997e+08 | 2.31939e+06 | 1.1748 | 3.28272 | 3(Loss) | true |
| simdjson (ondemand) | 638.508 | 0.203546 | 9444.01ms | 1834197 | 30 | 9.3284e+08 | 2.73955e+06 | 0.950291 | 3.87722 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1430.44 | 0.0469027 | 8468.85ms | 1922245 | 30 | 1.08392e+07 | 1.28156e+06 | 0.055069 | 1.73076 | 1(Win) | true |
| Glaze | 627.727 | 0.36907 | 8489.16ms | 1833577 | 40 | 4.22799e+09 | 2.78566e+06 | 1.09272 | 3.94386 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1428.87 | 0.0985301 | 8127.93ms | 1922245 | 80 | 1.27838e+08 | 1.28297e+06 | 0.281877 | 1.73264 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 656.56 | 0.168728 | 8088.15ms | 1833577 | 80 | 1.61552e+09 | 2.66333e+06 | 3.73933 | 3.77068 | -(Loss) | false |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2805.31 | 0.0532731 | 7784.47ms | 7351818 | 40 | 7.09094e+07 | 2.49927e+06 | 0.0589949 | 0.882527 | 1(Win) | true |
| Jsonifier | 2658.71 | 0.140727 | 8330.58ms | 7351818 | 160 | 2.20354e+09 | 2.63708e+06 | 1.25137 | 0.931191 | 2(Loss) | true |
| simdjson (ondemand) | 2227.38 | 0.0539735 | 9789.61ms | 7351818 | 30 | 8.65936e+07 | 3.14776e+06 | 0.0837487 | 1.11152 | 3(Loss) | true |
| Glaze | 2161.09 | 0.0686115 | 10843.4ms | 7351818 | 40 | 1.98197e+08 | 3.2443e+06 | 0.238633 | 1.14561 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3092.52 | 0.128238 | 7769.75ms | 7351818 | 40 | 3.38111e+08 | 2.26716e+06 | 0.0696083 | 0.800568 | 1(Win) | true |
| Jsonifier | 2916.18 | 0.0958362 | 8326.81ms | 7351818 | 40 | 2.12363e+08 | 2.40425e+06 | 0.122165 | 0.848975 | 2(Loss) | true |
| simdjson (ondemand) | 2445.45 | 0.0319982 | 9718.73ms | 7351818 | 80 | 6.73305e+07 | 2.86705e+06 | 0.902023 | 1.0124 | 3(Loss) | true |
| Glaze | 2320.54 | 0.0879482 | 5186.15ms | 7351818 | 40 | 2.82439e+08 | 3.02138e+06 | 0.0631618 | 1.0669 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5034.44 | 0.0417681 | 5889.76ms | 10018896 | 30 | 1.88517e+07 | 1.89788e+06 | 0.0296998 | 0.491763 | 1(Win) | true |
| Glaze | 3361.28 | 0.0647735 | 8769.22ms | 9930228 | 80 | 2.66436e+08 | 2.81744e+06 | 0.0263295 | 0.736522 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5302.48 | 0.0518674 | 6260.3ms | 10018896 | 30 | 2.62054e+07 | 1.80194e+06 | 0.223837 | 0.466895 | 1(Win) | true |
| Glaze | 3961.23 | 0.0497214 | 7443.77ms | 9930228 | 40 | 5.65203e+07 | 2.39072e+06 | 0.159545 | 0.624992 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1481.28 | 0.185051 | 7682.91ms | 461466 | 80 | 2.41811e+07 | 297099 | 0.0743012 | 1.67114 | 1(Win) | true |
| Jsonifier (two-stage) | 1190.54 | 0.161435 | 9375.98ms | 461466 | 40 | 1.42445e+07 | 369655 | 0.171596 | 2.07929 | 2(Loss) | true |
| Glaze | 1101.25 | 0.0742454 | 5095.7ms | 461466 | 320 | 2.81706e+07 | 399625 | 0.370876 | 2.24793 | 3(Loss) | true |
| simdjson (ondemand) | 770.205 | 0.079463 | 7243.55ms | 461466 | 640 | 1.3194e+08 | 571391 | 0.167787 | 3.21421 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2141.41 | 0.190026 | 7087.54ms | 461466 | 80 | 1.2201e+07 | 205513 | 0.1198 | 1.15601 | 1(Win) | true |
| Jsonifier (two-stage) | 1638.11 | 0.0835169 | 8748.56ms | 461466 | 320 | 1.61098e+07 | 268656 | 0.282099 | 1.51119 | 2(Loss) | true |
| Glaze | 1365.72 | 0.286358 | 10014.5ms | 461466 | 30 | 2.55443e+07 | 322239 | 0.00226535 | 1.81266 | 3(Loss) | true |
| simdjson (ondemand) | 959.739 | 0.246382 | 6569.69ms | 461466 | 40 | 5.10566e+07 | 458550 | 0.409487 | 2.57948 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13260.4 | 0.238037 | 3313.33ms | 461466 | 640 | 3.99427e+06 | 33188.2 | 0.147129 | 0.186487 | 1(Win) | true |
| Glaze | 2971.2 | 0.0466229 | 7571.12ms | 461466 | 2560 | 1.22082e+07 | 148118 | 0.050765 | 0.833037 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13219.7 | 0.164737 | 3317.81ms | 461466 | 1280 | 3.84973e+06 | 33290.5 | 0.032131 | 0.187045 | 1(Win) | true |
| Glaze | 3172.27 | 0.0720929 | 7054.58ms | 461466 | 1280 | 1.28037e+07 | 138730 | 0.190331 | 0.780246 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1931.27 | 0.0956669 | 9219.16ms | 728486 | 320 | 3.78991e+07 | 359731 | 0.222273 | 1.2818 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.44 | 0.26094 | 5107.56ms | 728486 | 30 | 3.26609e+07 | 399864 | 0.683715 | 1.42478 | 2(Loss) | true |
| Glaze | 1380.06 | 0.0812304 | 6389.9ms | 728486 | 320 | 5.35096e+07 | 503410 | 0.0669167 | 1.79382 | 3(Loss) | true |
| simdjson (ondemand) | 1187.65 | 0.139793 | 7451.53ms | 728486 | 30 | 2.00611e+07 | 584969 | 0.0582882 | 2.08447 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2660.3 | 0.180901 | 8444.97ms | 728486 | 160 | 3.57097e+07 | 261151 | 0.105827 | 0.930526 | 1(Win) | true |
| Jsonifier (two-stage) | 2316.18 | 0.0760703 | 9495.55ms | 728486 | 1280 | 6.66405e+07 | 299950 | 0.0274374 | 1.06878 | 2(Loss) | true |
| Glaze | 1636.45 | 0.123091 | 6271.72ms | 728486 | 80 | 2.18466e+07 | 424540 | 0.121529 | 1.5128 | 3(Loss) | true |
| simdjson (ondemand) | 1428.76 | 0.12208 | 6965.16ms | 728486 | 640 | 2.25523e+08 | 486253 | 0.354349 | 1.73271 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16985 | 0.350647 | 4688.11ms | 837491 | 40 | 1.0875e+06 | 47023.4 | 0.0486223 | 0.145662 | 1(Win) | true |
| Glaze | 3578.94 | 0.297706 | 5701.01ms | 837491 | 40 | 1.76558e+07 | 223165 | 0.343513 | 0.691639 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17133.4 | 0.0523039 | 4672.07ms | 837491 | 4890 | 2.90705e+06 | 46616.3 | 0.144414 | 0.14439 | 1(Win) | true |
| Glaze | 3958.06 | 0.113368 | 5256.06ms | 837491 | 160 | 8.37324e+06 | 201789 | 0.294387 | 0.625401 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 10317.7 | 0.163832 | 4367.64ms | 466906 | 320 | 1.59972e+06 | 43156.7 | 0.139469 | 0.239806 | 1(Win) | true |
| Jsonifier | 10171.9 | 0.0877712 | 4360.16ms | 466906 | 2560 | 3.77917e+06 | 43775 | 0.280673 | 0.243241 | 2(Loss) | true |
| simdjson (ondemand) | 7857.72 | 0.169421 | 5611.72ms | 466906 | 640 | 5.89905e+06 | 56667.4 | 0.0548428 | 0.31492 | 3(Loss) | true |
| Glaze | 3304.12 | 0.0815823 | 6865.3ms | 466906 | 640 | 7.73605e+06 | 134764 | 0.0457072 | 0.74916 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 10451.5 | 0.0645735 | 4344.3ms | 466906 | 4890 | 3.70101e+06 | 42604.1 | 0.0756659 | 0.236732 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 10431.4 | 0.117982 | 4353.47ms | 466906 | 1280 | 3.24651e+06 | 42686.3 | 0.116557 | 0.23719 | 1(Tie) | true |
| simdjson (ondemand) | 8057 | 0.0547727 | 5585.77ms | 466906 | 4890 | 4.48074e+06 | 55265.8 | 0.0349884 | 0.3071 | 3(Loss) | true |
| Glaze | 3346.13 | 0.104108 | 6847.71ms | 466906 | 320 | 6.14179e+06 | 133072 | 0.0395878 | 0.739754 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 11616.4 | 0.0646256 | 5233.42ms | 631514 | 2560 | 2.87389e+06 | 51845.4 | 0.167043 | 0.212983 | 1(Win) | true |
| Jsonifier | 11240.4 | 0.18948 | 5373.68ms | 631514 | 640 | 6.59648e+06 | 53580 | 0.0781307 | 0.220106 | 2(Loss) | true |
| simdjson (ondemand) | 9463.86 | 0.145114 | 6500.91ms | 631514 | 1280 | 1.09159e+07 | 63637.7 | 0.0184538 | 0.261439 | 3(Loss) | true |
| Glaze | 3963.11 | 0.0385111 | 7805.89ms | 631514 | 2560 | 8.76808e+06 | 151966 | 0.0543215 | 0.6246 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 11928.1 | 0.208902 | 5115.82ms | 631514 | 320 | 3.56008e+06 | 50490.7 | 0.0199519 | 0.207436 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 11913.2 | 0.0808614 | 5147.31ms | 631514 | 2560 | 4.27795e+06 | 50554.1 | 0.0457693 | 0.207677 | 1(Tie) | true |
| simdjson (ondemand) | 9628.26 | 0.100515 | 6483.11ms | 631514 | 640 | 2.52993e+06 | 62551.2 | 0.0228835 | 0.256996 | 3(Loss) | true |
| Glaze | 4016.15 | 0.245587 | 7772.34ms | 631514 | 40 | 5.4252e+06 | 149959 | 0.0385086 | 0.61635 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1957.62 | 0.142221 | 5832.54ms | 466906 | 160 | 1.67435e+07 | 227458 | 0.0525979 | 1.26447 | 1(Win) | true |
| Glaze | 1708.23 | 0.111213 | 6769.98ms | 466906 | 320 | 2.68924e+07 | 260665 | 0.352325 | 1.4491 | 2(Loss) | true |
| Jsonifier (two-stage) | 1671.25 | 0.113201 | 6782.44ms | 466906 | 320 | 2.91091e+07 | 266434 | 0.299452 | 1.48114 | 3(Loss) | true |
| simdjson (ondemand) | 925.728 | 0.0740449 | 6105.76ms | 466906 | 320 | 4.05912e+07 | 481001 | 0.0845884 | 2.67417 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2426.06 | 0.0794423 | 5413.16ms | 466906 | 640 | 1.36063e+07 | 183539 | 0.208813 | 1.02033 | 1(Win) | true |
| Glaze | 2115.33 | 0.0512153 | 6081.38ms | 466906 | 1280 | 1.48769e+07 | 210500 | 0.130271 | 1.17026 | 2(Loss) | true |
| Jsonifier (two-stage) | 2017.33 | 0.0562455 | 6398.7ms | 466906 | 1280 | 1.97284e+07 | 220726 | 0.110749 | 1.22707 | 3(Loss) | true |
| simdjson (ondemand) | 1026.4 | 0.110334 | 5941.62ms | 466906 | 80 | 1.83288e+07 | 433824 | 0.0309246 | 2.41195 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17621.6 | 0.110225 | 2571.54ms | 475954 | 2560 | 2.06368e+06 | 25758.5 | 0.105253 | 0.140344 | 1(Win) | true |
| Glaze | 5869.04 | 0.367071 | 7732.6ms | 475954 | 40 | 3.22372e+06 | 77338.9 | 0.193874 | 0.421624 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17824.3 | 0.132667 | 2560.9ms | 475954 | 1280 | 1.46097e+06 | 25465.5 | 0.0184843 | 0.138753 | 1(Win) | true |
| Glaze | 6545.62 | 0.0717986 | 6943.21ms | 475954 | 4890 | 1.21219e+07 | 69344.9 | 0.0333858 | 0.37807 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2485.69 | 0.175815 | 6224.75ms | 631514 | 160 | 2.90335e+07 | 242290 | 0.0453486 | 0.995846 | 1(Win) | true |
| Jsonifier (two-stage) | 2199.28 | 0.0792699 | 6976.67ms | 631514 | 1280 | 6.0316e+07 | 273844 | 0.0981774 | 1.12554 | 2(Loss) | true |
| Glaze | 1896.51 | 0.0662877 | 8058.53ms | 631514 | 640 | 2.83599e+07 | 317562 | 0.173149 | 1.30527 | 3(Loss) | true |
| simdjson (ondemand) | 1225 | 0.0876309 | 6254.69ms | 631514 | 640 | 1.18792e+08 | 491640 | 0.288338 | 2.02088 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3040.27 | 0.0474965 | 5802.21ms | 631514 | 1280 | 1.13311e+07 | 198094 | 0.00142371 | 0.814199 | 1(Win) | true |
| Jsonifier (two-stage) | 2640.72 | 0.188169 | 6636.14ms | 631514 | 80 | 1.47336e+07 | 228066 | 0.1067 | 0.937381 | 2(Loss) | true |
| Glaze | 2209.54 | 0.155295 | 7569.35ms | 631514 | 160 | 2.86682e+07 | 272572 | 0.17035 | 1.12039 | 3(Loss) | true |
| simdjson (ondemand) | 1355.18 | 0.0813929 | 6012.19ms | 631514 | 160 | 2.09348e+07 | 444414 | 0.0697613 | 1.82655 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16004.4 | 0.148033 | 4296.84ms | 716365 | 640 | 2.55556e+06 | 42687 | 0.0363635 | 0.154596 | 1(Win) | true |
| Glaze | 4733.63 | 0.047953 | 7373.22ms | 716365 | 2560 | 1.22617e+07 | 144325 | 0.0577271 | 0.522864 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15984.6 | 0.077652 | 4280.69ms | 716365 | 4890 | 5.38616e+06 | 42739.8 | 0.0860148 | 0.154778 | 1(Win) | true |
| Glaze | 5485.1 | 0.192924 | 6427.29ms | 716365 | 160 | 9.23833e+06 | 124552 | 0.0246072 | 0.451272 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3013.38 | 0.219877 | 85.4641ms | 2632 | 40 | 134.179 | 832.975 | 0.0490451 | 0.7964 | 1(Win) | true |
| Jsonifier (two-stage) | 2481.53 | 0.197568 | 106.214ms | 2632 | 40 | 159.744 | 1011.5 | 0.102054 | 0.972245 | 2(Loss) | true |
| Glaze | 1995.45 | 0.177121 | 128.574ms | 2632 | 30 | 148.921 | 1257.9 | 0.0794344 | 1.21536 | 3(Loss) | true |
| simdjson (ondemand) | 1531.73 | 0.103249 | 168.66ms | 2632 | 80 | 229.018 | 1638.71 | 0.244259 | 1.58992 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3569.59 | 0.0742113 | 79.6033ms | 2632 | 160 | 43.5707 | 703.181 | 0.0506883 | 0.668401 | 1(Win) | true |
| Jsonifier (two-stage) | 2802.27 | 0.0589871 | 99.7579ms | 2632 | 640 | 178.668 | 895.728 | 0.264099 | 0.857813 | 2(Loss) | true |
| Glaze | 2476.58 | 0.094332 | 109.945ms | 2632 | 40 | 36.5635 | 1013.52 | 0.0599855 | 0.974943 | 3(Loss) | true |
| simdjson (ondemand) | 1739.39 | 0.0593441 | 155.541ms | 2632 | 320 | 234.684 | 1443.08 | 0.00736329 | 1.39476 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11593.8 | 0.10361 | 24.6363ms | 2632 | 640 | 32.2034 | 216.502 | 0.190886 | 0.188319 | 1(Win) | true |
| Glaze | 4007.14 | 0.0741303 | 65.8863ms | 2632 | 320 | 68.9994 | 626.4 | 0.00798148 | 0.592525 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12214.8 | 0.22913 | 23.0923ms | 2632 | 160 | 35.4717 | 205.494 | 0.0334672 | 0.177802 | 1(Win) | true |
| Glaze | 4351.34 | 0.0580538 | 60.619ms | 2632 | 640 | 71.774 | 576.85 | 0.16659 | 0.543572 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3284.21 | 0.080233 | 101.038ms | 3370 | 160 | 98.6338 | 978.587 | 0.224037 | 0.733501 | 1(Win) | true |
| Jsonifier (two-stage) | 2870.77 | 0.225042 | 114.198ms | 3370 | 4890 | 31038.4 | 1119.52 | 0.0185137 | 0.841494 | 2(Loss) | true |
| Glaze | 2307.5 | 0.0693728 | 142.343ms | 3370 | 40 | 37.3436 | 1392.8 | 0.0982201 | 1.05307 | 3(Loss) | true |
| simdjson (ondemand) | 1894.11 | 0.168613 | 173.972ms | 3370 | 40 | 327.41 | 1696.78 | 0.222965 | 1.28743 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3721.35 | 0.117833 | 95.7507ms | 3370 | 30 | 31.0678 | 863.633 | 0.0385817 | 0.64545 | 1(Win) | true |
| Jsonifier (two-stage) | 3194.63 | 0.10349 | 110.136ms | 3370 | 40 | 43.3583 | 1006.02 | 0.0802847 | 0.754332 | 2(Loss) | true |
| Glaze | 2684.03 | 0.310014 | 128.313ms | 3370 | 4890 | 67384.1 | 1197.41 | 0.0911753 | 0.902553 | 3(Loss) | true |
| simdjson (ondemand) | 2080.84 | 0.363669 | 163.44ms | 3370 | 2560 | 80767.6 | 1544.52 | 0.0414693 | 1.16689 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13149.7 | 0.161507 | 29.3817ms | 3643 | 160 | 29.1333 | 264.206 | 0.454481 | 0.170577 | 1(Win) | true |
| Glaze | 4424.94 | 0.0718346 | 82.4367ms | 3682 | 320 | 103.985 | 793.553 | 0.0554948 | 0.541737 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14622.3 | 0.0619714 | 26.633ms | 3643 | 1280 | 27.7511 | 237.598 | 0.511629 | 0.151281 | 1(Win) | true |
| Glaze | 4831.58 | 0.215061 | 75.8154ms | 3682 | 30 | 73.2885 | 726.767 | 0.00458631 | 0.494278 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 909.744 | 0.0466101 | 490.524ms | 4630 | 40 | 204.712 | 4853.57 | 0.159593 | 2.70624 | 1(Win) | true |
| Jsonifier (two-stage) | 838.091 | 0.373235 | 530.043ms | 4630 | 640 | 247471 | 5268.53 | 0.778646 | 2.93896 | 2(Loss) | true |
| Glaze | 770.777 | 0.0884026 | 578.701ms | 4630 | 40 | 1025.87 | 5728.65 | 0.138584 | 3.19844 | 3(Loss) | true |
| simdjson (ondemand) | 766.937 | 0.0798057 | 580.964ms | 4630 | 30 | 633.333 | 5757.33 | 0.0798343 | 3.21303 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1099.12 | 0.155463 | 481.074ms | 4630 | 4890 | 190735 | 4017.3 | 0.128528 | 2.23801 | 1(Win) | true |
| Jsonifier (two-stage) | 1002.22 | 0.0294533 | 525.953ms | 4630 | 80 | 134.708 | 4405.73 | 0.127512 | 2.45594 | 2(Loss) | true |
| Glaze | 904.178 | 0.233311 | 573.678ms | 4630 | 2560 | 332325 | 4883.45 | 0.10884 | 2.72365 | 3(Loss) | true |
| simdjson (ondemand) | 844.083 | 0.231953 | 610.209ms | 4630 | 2560 | 376904 | 5231.14 | 0.0333452 | 2.91784 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2114.03 | 0.0162927 | 213.757ms | 4630 | 320 | 37.0571 | 2088.67 | 0.0453545 | 1.15703 | 1(Win) | true |
| Glaze | 1050.54 | 0.035828 | 425.939ms | 4630 | 40 | 90.7077 | 4203.1 | 0.0847861 | 2.34266 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2114.49 | 0.0153615 | 210.735ms | 4630 | 320 | 32.9283 | 2088.22 | 0.040871 | 1.15674 | 1(Win) | true |
| Glaze | 1084.95 | 0.0362235 | 412.323ms | 4630 | 30 | 65.2 | 4069.8 | 0.0163781 | 2.2668 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1954.05 | 0.0601717 | 569.722ms | 11579 | 30 | 346.878 | 5651.13 | 0.218723 | 1.26073 | 1(Win) | true |
| Jsonifier | 1891.17 | 0.0449553 | 593.892ms | 11579 | 40 | 275.615 | 5839.02 | 0.12159 | 1.30342 | 2(Loss) | true |
| simdjson (ondemand) | 1770.81 | 0.113296 | 626.649ms | 11579 | 4890 | 244080 | 6235.89 | 0.0036649 | 1.39227 | 3(Loss) | true |
| Glaze | 1637.58 | 0.238226 | 680.07ms | 11579 | 1280 | 330313 | 6743.24 | 0.00413626 | 1.50612 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2265.34 | 0.143896 | 569.77ms | 11579 | 4890 | 240594 | 4874.59 | 0.0209748 | 1.08695 | 1(Win) | true |
| Jsonifier | 2197.38 | 0.173037 | 586.829ms | 11579 | 2560 | 193575 | 5025.35 | 0.00838647 | 1.12095 | 2(Loss) | true |
| simdjson (ondemand) | 1978.07 | 0.143595 | 641.739ms | 11579 | 4890 | 314230 | 5582.5 | 0.179252 | 1.24538 | 3(Loss) | true |
| Glaze | 1859.41 | 0.10535 | 678.823ms | 11579 | 4890 | 191411 | 5938.75 | 0.0323303 | 1.32575 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5791.11 | 0.0513076 | 247.31ms | 14795 | 40 | 62.5071 | 2436.43 | 0.0646021 | 0.422727 | 1(Win) | true |
| Glaze | 3428.38 | 0.0940685 | 418.695ms | 14795 | 30 | 449.637 | 4115.53 | 0.00890854 | 0.717751 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5944.46 | 0.0318835 | 242.464ms | 14795 | 80 | 45.8171 | 2373.57 | 0.0316079 | 0.411871 | 1(Win) | true |
| Glaze | 3752.49 | 0.0419505 | 381.502ms | 14795 | 80 | 199.047 | 3760.06 | 0.0628709 | 0.655263 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1928.77 | 0.0469421 | 163.436ms | 3223 | 160 | 89.5371 | 1593.6 | 0.0997166 | 1.26212 | 1(Win) | true |
| Jsonifier (two-stage) | 1589.98 | 0.245533 | 196.005ms | 3223 | 4890 | 110170 | 1933.16 | 0.37254 | 1.5353 | 2(Loss) | true |
| Glaze | 1371.84 | 0.0594806 | 229.1ms | 3223 | 160 | 284.173 | 2240.56 | 0.0924173 | 1.78333 | 3(Loss) | true |
| simdjson (ondemand) | 1067.77 | 0.129348 | 290.563ms | 3223 | 40 | 554.554 | 2878.6 | 0.0728989 | 2.29645 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2462.31 | 0.0304923 | 143.506ms | 3223 | 640 | 92.7242 | 1248.29 | 0.226546 | 0.984801 | 1(Win) | true |
| Jsonifier (two-stage) | 1926.53 | 0.0508543 | 180.144ms | 3223 | 320 | 210.656 | 1595.45 | 0.101367 | 1.26451 | 2(Loss) | true |
| Glaze | 1591.21 | 0.21843 | 212.932ms | 3223 | 40 | 712.122 | 1931.67 | 0.00388279 | 1.53512 | 3(Loss) | true |
| simdjson (ondemand) | 1234.9 | 0.0855997 | 268.273ms | 3223 | 80 | 363.152 | 2489.01 | 0.015566 | 1.98105 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10748.1 | 0.0705662 | 31.245ms | 3223 | 640 | 26.0636 | 285.977 | 0.16201 | 0.209683 | 1(Win) | true |
| Glaze | 2744.25 | 0.158275 | 112.321ms | 3223 | 80 | 251.415 | 1120.05 | 0.327037 | 0.882284 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11139.8 | 0.151783 | 30.1641ms | 3223 | 160 | 28.0625 | 275.919 | 0.00226521 | 0.201786 | 1(Win) | true |
| Glaze | 3027.8 | 0.180294 | 105.251ms | 3223 | 160 | 535.982 | 1015.16 | 0.0733183 | 0.796678 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2657.74 | 0.0769518 | 213.726ms | 5839 | 80 | 207.959 | 2095.2 | 0.0214731 | 0.919395 | 1(Win) | true |
| Jsonifier | 2563.37 | 0.10921 | 221.317ms | 5839 | 30 | 168.851 | 2172.33 | 0.0168818 | 0.953925 | 2(Loss) | true |
| simdjson (ondemand) | 1827.79 | 0.0872314 | 315.942ms | 5839 | 40 | 282.507 | 3046.57 | 0.318195 | 1.34251 | 3(Loss) | true |
| Glaze | 1801.17 | 0.0721118 | 309.608ms | 5839 | 40 | 198.81 | 3091.6 | 0.0344902 | 1.363 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3237.31 | 0.0912182 | 189.462ms | 5839 | 80 | 196.952 | 1720.1 | 0.364676 | 0.752789 | 1(Win) | true |
| Jsonifier | 3112.85 | 0.0608739 | 199.6ms | 5839 | 160 | 189.733 | 1788.88 | 0.138861 | 0.784058 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2063.26 | 0.039995 | 291.365ms | 5839 | 320 | 372.845 | 2698.88 | 0.00995882 | 1.18838 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2062.39 | 0.114112 | 295.514ms | 5839 | 40 | 379.717 | 2700.03 | 0.0496662 | 1.1891 | 3(Tie) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12527.5 | 0.186502 | 55.71ms | 6938 | 30 | 29.1092 | 528.167 | 0.23925 | 0.187119 | 1(Win) | true |
| Glaze | 4385.07 | 0.112968 | 156.916ms | 6960 | 80 | 233.918 | 1513.67 | 0.0429603 | 0.554723 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14135 | 0.145933 | 50.0926ms | 6938 | 80 | 37.3316 | 468.1 | 0.0801753 | 0.165296 | 1(Win) | true |
| Glaze | 4939.9 | 0.138584 | 138.551ms | 6960 | 30 | 104.023 | 1343.67 | 0.0297604 | 0.491475 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2196.31 | 0.369306 | 213.188ms | 4857 | 640 | 38824.2 | 2108.99 | 0.179763 | 1.11308 | 1(Win) | true |
| Jsonifier (two-stage) | 1788.51 | 0.28981 | 262.494ms | 4857 | 2560 | 144218 | 2589.87 | 0.0848072 | 1.3685 | 2(Loss) | true |
| Glaze | 1593.98 | 0.257119 | 291.013ms | 4857 | 40 | 2233.05 | 2905.93 | 0.010038 | 1.53847 | 3(Loss) | true |
| simdjson (ondemand) | 796.28 | 0.203146 | 588.193ms | 4857 | 1280 | 178744 | 5817.05 | 0.181156 | 3.09503 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3119.29 | 0.134251 | 171.503ms | 4857 | 40 | 158.972 | 1484.95 | 0.0280672 | 0.780852 | 1(Win) | true |
| Jsonifier (two-stage) | 2253.87 | 0.154291 | 229.004ms | 4857 | 30 | 301.637 | 2055.13 | 0.241089 | 1.08468 | 2(Loss) | true |
| Glaze | 2127.91 | 0.161363 | 241.291ms | 4857 | 4890 | 60331.8 | 2176.78 | 0.134789 | 1.14922 | 3(Loss) | true |
| simdjson (ondemand) | 900.048 | 0.220493 | 535.395ms | 4857 | 2560 | 329635 | 5146.39 | 0.0524819 | 2.73608 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12190.1 | 0.0427072 | 41.4245ms | 4857 | 1280 | 33.7079 | 379.979 | 0.182704 | 0.189479 | 1(Win) | true |
| Glaze | 3893.25 | 0.0817738 | 123.822ms | 4857 | 160 | 151.447 | 1189.75 | 0.00630424 | 0.621777 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13559.8 | 0.144655 | 37.0463ms | 4857 | 320 | 78.1348 | 341.597 | 0.126999 | 0.168646 | 1(Win) | true |
| Glaze | 4279.87 | 0.326193 | 110.671ms | 4857 | 2560 | 31905.5 | 1082.28 | 0.0493273 | 0.564623 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2618.58 | 0.115869 | 247.242ms | 6701 | 40 | 319.846 | 2440.47 | 0.0351584 | 0.93536 | 1(Win) | true |
| Jsonifier (two-stage) | 2352.09 | 0.120764 | 274.821ms | 6701 | 80 | 861.265 | 2716.97 | 0.0681368 | 1.04226 | 2(Loss) | true |
| Glaze | 1848.64 | 0.153443 | 350.201ms | 6701 | 30 | 844.093 | 3456.9 | 0.0770809 | 1.328 | 3(Loss) | true |
| simdjson (ondemand) | 1087.46 | 0.111032 | 592.163ms | 6701 | 40 | 1702.96 | 5876.6 | 0.338615 | 2.26621 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3421.63 | 0.0513219 | 208.551ms | 6701 | 80 | 73.5038 | 1867.7 | 0.12433 | 0.713513 | 1(Win) | true |
| Jsonifier (two-stage) | 2973.31 | 0.0556055 | 241.093ms | 6701 | 80 | 114.268 | 2149.31 | 0.100512 | 0.822351 | 2(Loss) | true |
| Glaze | 2407.68 | 0.0576444 | 284.185ms | 6701 | 80 | 187.278 | 2654.25 | 0.188733 | 1.01805 | 3(Loss) | true |
| simdjson (ondemand) | 1209.08 | 0.0759907 | 548.811ms | 6701 | 40 | 645.281 | 5285.48 | 0.0477496 | 2.03729 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14154.2 | 0.0923319 | 52.5581ms | 7376 | 320 | 67.3787 | 496.975 | 0.0163462 | 0.165863 | 1(Win) | true |
| Glaze | 3527.97 | 0.0408782 | 248.947ms | 7376 | 160 | 106.291 | 1993.87 | 0.748233 | 0.692632 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15976.7 | 0.0486458 | 46.9043ms | 7376 | 640 | 29.3588 | 440.284 | 0.0141934 | 0.145958 | 1(Win) | true |
| Glaze | 3813.4 | 0.0754092 | 188.916ms | 7376 | 80 | 154.794 | 1844.62 | 0.0108411 | 0.640152 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2530.01 | 0.449693 | 66.7346ms | 1691 | 2560 | 21033.6 | 637.413 | 0.0974734 | 0.939072 | 1(Win) | true |
| Glaze | 2041.33 | 0.0979498 | 82.1428ms | 1691 | 160 | 95.805 | 790.006 | 0.0071207 | 1.17355 | 2(Loss) | true |
| Jsonifier (two-stage) | 1906.73 | 0.203449 | 87.3035ms | 1691 | 40 | 118.435 | 845.775 | 0.375947 | 1.25955 | 3(Loss) | true |
| simdjson (ondemand) | 1450.93 | 0.0540053 | 113.788ms | 1691 | 320 | 115.297 | 1111.47 | 0.0489457 | 1.66533 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3249.7 | 0.101151 | 59.1607ms | 1691 | 160 | 40.3145 | 496.25 | 0.0731013 | 0.723111 | 1(Win) | true |
| Jsonifier (two-stage) | 2522.96 | 0.647279 | 72.1003ms | 1691 | 1280 | 21910.8 | 639.194 | 0.0952441 | 0.942016 | 2(Loss) | true |
| Glaze | 2350.93 | 0.0890597 | 79.6028ms | 1691 | 160 | 59.716 | 685.969 | 0.084806 | 1.0127 | 3(Loss) | true |
| simdjson (ondemand) | 1734.52 | 0.080978 | 102.194ms | 1691 | 320 | 181.389 | 929.744 | 0.0718767 | 1.38572 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14934.1 | 0.115008 | 15.1877ms | 1996 | 1280 | 27.506 | 127.463 | 0.0171649 | 0.132092 | 1(Win) | true |
| Glaze | 4622.03 | 0.0714109 | 43.9514ms | 1996 | 640 | 55.3559 | 411.839 | 0.0557401 | 0.502782 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16119.7 | 0.154513 | 14.2353ms | 1996 | 640 | 21.3069 | 118.088 | 0.345473 | 0.119386 | 1(Win) | true |
| Glaze | 5282.28 | 0.115988 | 38.6927ms | 1996 | 320 | 55.9058 | 360.363 | 0.292251 | 0.435634 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2672.18 | 0.0772989 | 80.4556ms | 2158 | 160 | 56.7072 | 770.169 | 0.080275 | 0.895783 | 1(Win) | true |
| Jsonifier (two-stage) | 2384.91 | 0.122694 | 89.5923ms | 2158 | 80 | 89.6796 | 862.938 | 0.163418 | 1.00701 | 2(Loss) | true |
| Glaze | 2070.45 | 0.0950374 | 101.253ms | 2158 | 80 | 71.3924 | 994 | 0.0301902 | 1.16602 | 3(Loss) | true |
| simdjson (ondemand) | 1809.22 | 0.0916286 | 123.973ms | 2158 | 80 | 86.9108 | 1137.53 | 0.127307 | 1.33551 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3557.37 | 0.182237 | 68.635ms | 2158 | 40 | 44.4609 | 578.525 | 0.196952 | 0.66469 | 1(Win) | true |
| Jsonifier (two-stage) | 3118.23 | 0.19695 | 75.9948ms | 2158 | 30 | 50.6897 | 660 | 0.0504796 | 0.763809 | 2(Loss) | true |
| Glaze | 2440.74 | 0.185933 | 92.5094ms | 2158 | 40 | 98.3179 | 843.2 | 0.0868947 | 0.982762 | 3(Loss) | true |
| simdjson (ondemand) | 2125.21 | 0.287101 | 105.609ms | 2158 | 4890 | 37798.8 | 968.39 | 0.0891165 | 1.13177 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15623.9 | 0.164283 | 20.0937ms | 2866 | 640 | 52.8617 | 174.939 | 0.277006 | 0.135454 | 1(Win) | true |
| Glaze | 4455.82 | 0.0739898 | 64.0136ms | 2866 | 320 | 65.9159 | 613.406 | 0.121396 | 0.532074 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17722 | 0.146384 | 18.0385ms | 2866 | 640 | 32.6208 | 154.228 | 0.165874 | 0.116353 | 1(Win) | true |
| Glaze | 5219.7 | 0.098361 | 55.1883ms | 2866 | 320 | 84.8901 | 523.638 | 0.178159 | 0.451277 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2242.27 | 0.111536 | 188.867ms | 4390 | 80 | 346.956 | 1867.14 | 0.197106 | 1.08862 | 1(Win) | true |
| Jsonifier (two-stage) | 1849.44 | 0.0983896 | 231.055ms | 4390 | 30 | 148.823 | 2263.73 | 0.0735705 | 1.32229 | 2(Loss) | true |
| Glaze | 1743.69 | 0.082262 | 244.056ms | 4390 | 80 | 312.088 | 2401.01 | 0.110768 | 1.40473 | 3(Loss) | true |
| simdjson (ondemand) | 1066.08 | 0.136098 | 395.362ms | 4390 | 4890 | 139689 | 3927.14 | 0.0492935 | 2.30688 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2609.02 | 0.055754 | 183.458ms | 4390 | 160 | 128.07 | 1604.67 | 0.0303892 | 0.933403 | 1(Win) | true |
| Jsonifier (two-stage) | 2077.75 | 0.0334514 | 224.963ms | 4390 | 320 | 145.385 | 2014.98 | 0.22445 | 1.17614 | 2(Loss) | true |
| Glaze | 1939.97 | 0.320488 | 236.336ms | 4390 | 1280 | 61231.6 | 2158.1 | 0.204227 | 1.26114 | 3(Loss) | true |
| simdjson (ondemand) | 1094.13 | 0.1141 | 405.604ms | 4390 | 80 | 1524.93 | 3826.44 | 0.0251476 | 2.24714 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11699.3 | 0.065947 | 38.6135ms | 4390 | 640 | 35.6435 | 357.853 | 0.228442 | 0.196635 | 1(Win) | true |
| Glaze | 3030.59 | 0.158081 | 141.128ms | 4390 | 160 | 763.055 | 1381.46 | 0.126066 | 0.801842 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12238.4 | 0.0533677 | 36.5413ms | 4390 | 640 | 21.3314 | 342.091 | 0.170533 | 0.187427 | 1(Win) | true |
| Glaze | 3195.9 | 0.500782 | 133.846ms | 4390 | 30 | 1291.1 | 1310 | 0.304414 | 0.759036 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3609.09 | 0.0794443 | 250.358ms | 9378 | 30 | 116.271 | 2478.07 | 0.0927282 | 0.678769 | 1(Win) | true |
| Jsonifier (two-stage) | 3329.32 | 0.0850888 | 272.178ms | 9378 | 40 | 208.985 | 2686.3 | 0.0892625 | 0.736282 | 2(Loss) | true |
| Glaze | 2487.85 | 0.0879533 | 357.041ms | 9378 | 40 | 399.887 | 3594.9 | 0.0881654 | 0.987948 | 3(Loss) | true |
| simdjson (ondemand) | 2140.22 | 0.123544 | 421.282ms | 9378 | 40 | 1066.11 | 4178.8 | 0.105979 | 1.14944 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3939.08 | 0.13977 | 246.837ms | 9378 | 30 | 302.12 | 2270.47 | 0.0132114 | 0.621561 | 1(Win) | true |
| Jsonifier (two-stage) | 3644.38 | 0.107969 | 268.241ms | 9378 | 30 | 210.616 | 2454.07 | 0.105834 | 0.671753 | 2(Loss) | true |
| Glaze | 2778.93 | 0.0372317 | 342.939ms | 9378 | 80 | 114.863 | 3218.35 | 0.0621051 | 0.883941 | 3(Loss) | true |
| simdjson (ondemand) | 2197.58 | 0.250809 | 433.882ms | 9378 | 30 | 3125.65 | 4069.73 | 0.0499374 | 1.11932 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17752.9 | 0.163488 | 64.6588ms | 11521 | 30 | 30.7138 | 618.9 | 0.210492 | 0.133435 | 1(Win) | true |
| Glaze | 5339.33 | 0.130487 | 211.165ms | 11521 | 30 | 216.303 | 2057.8 | 0.224654 | 0.457738 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18631.1 | 0.0326897 | 61.7151ms | 11521 | 640 | 23.7851 | 589.728 | 0.0646903 | 0.127142 | 1(Win) | true |
| Glaze | 5836.38 | 0.0654907 | 192.625ms | 11521 | 160 | 243.205 | 1882.55 | 0.0923803 | 0.418305 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3003.76 | 0.076694 | 151.772ms | 4669 | 80 | 103.402 | 1482.38 | 0.107819 | 0.809925 | 1(Win) | true |
| Jsonifier (two-stage) | 2342.3 | 0.0955001 | 196.842ms | 4669 | 80 | 263.671 | 1901 | 0.00657592 | 1.04257 | 2(Loss) | true |
| Glaze | 1670.78 | 0.155379 | 269.415ms | 4669 | 4890 | 83849.3 | 2665.04 | 0.072535 | 1.46748 | 3(Loss) | true |
| simdjson (ondemand) | 622.313 | 0.145119 | 720.655ms | 4669 | 4890 | 527216 | 7155.09 | 0.0866154 | 3.96276 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3380.3 | 0.0901019 | 138.533ms | 4669 | 40 | 56.3462 | 1317.25 | 0.0468366 | 0.718205 | 1(Win) | true |
| Jsonifier (two-stage) | 2456.89 | 0.318593 | 186.75ms | 4669 | 1280 | 42673.5 | 1812.34 | 0.0321908 | 0.99314 | 2(Loss) | true |
| Glaze | 1834.44 | 0.0435508 | 250.574ms | 4669 | 80 | 89.3973 | 2427.29 | 0.0344916 | 1.33491 | 3(Loss) | true |
| simdjson (ondemand) | 645.87 | 0.0957686 | 697.328ms | 4669 | 4890 | 213164 | 6894.12 | 0.044148 | 3.81773 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15052.5 | 0.192634 | 32.1756ms | 4669 | 80 | 25.9771 | 295.812 | 0.0380453 | 0.150661 | 1(Win) | true |
| Glaze | 3963.37 | 0.0419094 | 115.63ms | 4669 | 640 | 141.88 | 1123.46 | 0.074184 | 0.610622 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16322.2 | 0.283071 | 29.87ms | 4669 | 30 | 17.8897 | 272.8 | 0.0122205 | 0.137867 | 1(Win) | true |
| Glaze | 4260.35 | 0.0937008 | 107.923ms | 4669 | 160 | 153.449 | 1045.15 | 0.102962 | 0.566721 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3635.62 | 0.0986374 | 211.47ms | 7932 | 40 | 168.481 | 2080.68 | 0.0244371 | 0.672683 | 1(Win) | true |
| Jsonifier (two-stage) | 3366.18 | 0.273595 | 227.78ms | 7932 | 2560 | 96771.3 | 2247.22 | 0.128936 | 0.726878 | 2(Loss) | true |
| Glaze | 2137.96 | 0.548642 | 361.032ms | 7932 | 80 | 30146.4 | 3538.21 | 0.017314 | 1.14965 | 3(Loss) | true |
| simdjson (ondemand) | 1035.06 | 0.304218 | 736.757ms | 7932 | 320 | 158180 | 7308.29 | 0.23535 | 2.38326 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3910.84 | 0.0697257 | 198.877ms | 7932 | 40 | 72.7564 | 1934.25 | 0.404202 | 0.624748 | 1(Win) | true |
| Jsonifier (two-stage) | 3634.76 | 0.216388 | 214.65ms | 7932 | 30 | 608.42 | 2081.17 | 0.210974 | 0.67239 | 2(Loss) | true |
| Glaze | 2227.86 | 0.0668123 | 346.937ms | 7932 | 30 | 154.392 | 3395.43 | 0.058868 | 1.10233 | 3(Loss) | true |
| simdjson (ondemand) | 1066.57 | 0.12988 | 717.935ms | 7932 | 2560 | 217224 | 7092.37 | 0.201044 | 2.31186 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17206.7 | 0.0510787 | 54.218ms | 9249 | 640 | 43.8787 | 512.622 | 0.0243904 | 0.136844 | 1(Win) | true |
| Glaze | 4035.07 | 0.127941 | 221.216ms | 9249 | 30 | 234.654 | 2185.97 | 0.0289811 | 0.606343 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18883.5 | 0.0374364 | 49.3507ms | 9249 | 1280 | 39.1403 | 467.103 | 0.235607 | 0.123963 | 1(Win) | true |
| Glaze | 4344.45 | 0.10276 | 206.24ms | 9249 | 40 | 174.113 | 2030.3 | 0.0229798 | 0.562696 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 862.097 | 0.0630033 | 515.589ms | 4604 | 30 | 308.892 | 5093.07 | 0.0740115 | 2.85692 | 1(Win) | true |
| Jsonifier (two-stage) | 774.094 | 0.0975693 | 585.07ms | 4604 | 40 | 1225.1 | 5672.07 | 0.0748375 | 3.18152 | 2(Loss) | true |
| Glaze | 664.325 | 0.150216 | 665.026ms | 4604 | 4890 | 482003 | 6609.29 | 0.399609 | 3.71209 | 3(Loss) | true |
| simdjson (ondemand) | 527.719 | 0.347484 | 834.575ms | 4604 | 320 | 267476 | 8320.17 | 0.279185 | 4.6767 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1044.21 | 0.165649 | 503.999ms | 4604 | 2560 | 124197 | 4204.83 | 0.00347455 | 2.35597 | 1(Win) | true |
| Jsonifier (two-stage) | 910.079 | 0.162248 | 563.706ms | 4604 | 4890 | 299627 | 4824.54 | 0.0109949 | 2.70504 | 2(Loss) | true |
| Glaze | 775.573 | 0.155702 | 647.93ms | 4604 | 2560 | 198909 | 5661.25 | 0.0181022 | 3.17766 | 3(Loss) | true |
| simdjson (ondemand) | 561.805 | 0.108719 | 866.411ms | 4604 | 4890 | 353035 | 7815.37 | 0.114365 | 4.39078 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1886.99 | 0.0520998 | 251.979ms | 4918 | 40 | 67.0763 | 2485.53 | 0.112443 | 1.29864 | 1(Win) | true |
| Glaze | 854.818 | 0.106785 | 518.008ms | 4604 | 30 | 902.53 | 5136.43 | 0.000648963 | 2.88214 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1908.36 | 0.0732327 | 249.847ms | 4918 | 30 | 97.1828 | 2457.7 | 0.137172 | 1.28358 | 1(Win) | true |
| Glaze | 879.575 | 0.0378212 | 504.796ms | 4604 | 80 | 285.158 | 4991.86 | 0.00776324 | 2.80011 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2764.86 | 0.118846 | 635.795ms | 18245 | 4890 | 273539 | 6293.19 | 0.209277 | 0.891408 | 1(Win) | true |
| Jsonifier | 2333.76 | 0.180871 | 749.919ms | 18245 | 2560 | 465539 | 7455.7 | 0.0874613 | 1.05705 | 2(Loss) | true |
| simdjson (ondemand) | 1912.15 | 0.0495233 | 915.753ms | 18245 | 80 | 1624.63 | 9099.59 | 0.120053 | 1.29107 | 3(Loss) | true |
| Glaze | 1774.57 | 0.0966473 | 982.823ms | 18245 | 4890 | 439128 | 9805.09 | 0.0621737 | 1.39141 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3124.66 | 0.0457451 | 634.274ms | 18245 | 80 | 519.113 | 5568.54 | 0.00336725 | 0.788478 | 1(Win) | true |
| Jsonifier | 2663.57 | 0.0811647 | 737.347ms | 18245 | 30 | 843.362 | 6532.5 | 0.118752 | 0.926031 | 2(Loss) | true |
| simdjson (ondemand) | 2046.53 | 0.121711 | 983.504ms | 18245 | 2560 | 274124 | 8502.09 | 0.0811504 | 1.20538 | 3(Loss) | true |
| Glaze | 1994.73 | 0.0694246 | 959.418ms | 18245 | 30 | 1100.19 | 8722.87 | 0.0160523 | 1.23765 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6038.46 | 0.03712 | 402.256ms | 24893 | 80 | 170.376 | 3931.44 | 0.243186 | 0.407311 | 1(Win) | true |
| Glaze | 3834.38 | 0.0721751 | 616.008ms | 24579 | 30 | 584.028 | 6113.2 | 0.0714812 | 0.642828 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5823.22 | 0.0327777 | 413.664ms | 24893 | 80 | 142.848 | 4076.75 | 0.0539354 | 0.422482 | 1(Win) | true |
| Glaze | 4209.9 | 0.133713 | 568.35ms | 24579 | 4890 | 271047 | 5567.92 | 0.0978293 | 0.585383 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 937.007 | 0.151963 | 522.076ms | 4604 | 4890 | 247955 | 4685.9 | 0.099309 | 2.62631 | 1(Win) | true |
| Jsonifier (two-stage) | 832.914 | 0.187368 | 529.541ms | 4604 | 2560 | 249747 | 5271.51 | 0.00529054 | 2.95692 | 2(Loss) | true |
| Glaze | 673.853 | 0.164757 | 657.952ms | 4604 | 30 | 3457.39 | 6515.83 | 0.0255853 | 3.65939 | 3(Loss) | true |
| simdjson (ondemand) | 529.623 | 0.0514855 | 833.981ms | 4604 | 80 | 1457.46 | 8290.26 | 0.31279 | 4.65988 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1154.32 | 0.0619695 | 465.742ms | 4604 | 30 | 166.685 | 3803.73 | 0.265355 | 2.13068 | 1(Win) | true |
| Jsonifier (two-stage) | 965.441 | 0.0830894 | 534.6ms | 4604 | 80 | 1142.35 | 4547.89 | 0.199666 | 2.54832 | 2(Loss) | true |
| Glaze | 774.291 | 0.17398 | 653.636ms | 4604 | 2560 | 249172 | 5670.63 | 0.143166 | 3.18298 | 3(Loss) | true |
| simdjson (ondemand) | 588.889 | 0.0943111 | 829.723ms | 4604 | 30 | 1483.37 | 7455.93 | 0.220444 | 4.18744 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1901.16 | 0.0324088 | 250.968ms | 4918 | 80 | 51.1392 | 2467 | 0.100224 | 1.289 | 1(Win) | true |
| Glaze | 863.527 | 0.0518672 | 515.165ms | 4604 | 30 | 208.654 | 5084.63 | 0.034078 | 2.85277 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1929.5 | 0.040337 | 246.894ms | 4918 | 80 | 76.9108 | 2430.78 | 0.00411408 | 1.26905 | 1(Win) | true |
| Glaze | 889.16 | 0.0282514 | 499.461ms | 4604 | 160 | 311.394 | 4938.05 | 0.00455666 | 2.77002 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2893.42 | 0.168206 | 600.938ms | 18245 | 4890 | 500328 | 6013.58 | 0.240149 | 0.851449 | 1(Win) | true |
| Jsonifier | 2537.85 | 0.153788 | 690.345ms | 18245 | 2560 | 284604 | 6856.11 | 0.0535617 | 0.971769 | 2(Loss) | true |
| simdjson (ondemand) | 1925.4 | 0.0628739 | 947.759ms | 18245 | 30 | 968.516 | 9036.97 | 0.262946 | 1.28197 | 3(Loss) | true |
| Glaze | 1790.65 | 0.0682376 | 980.901ms | 18245 | 30 | 1318.97 | 9717 | 0.161834 | 1.37896 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3406.71 | 0.230573 | 593.638ms | 18245 | 640 | 88758.9 | 5107.5 | 0.291001 | 0.72284 | 1(Win) | true |
| Jsonifier | 2868.82 | 0.172949 | 687.982ms | 18245 | 4890 | 538053 | 6065.14 | 0.157527 | 0.859358 | 2(Loss) | true |
| simdjson (ondemand) | 2131.11 | 0.113001 | 905.454ms | 18245 | 30 | 2553.68 | 8164.67 | 0.0689489 | 1.15771 | 3(Loss) | true |
| Glaze | 1958.18 | 0.165346 | 964.344ms | 18245 | 2560 | 552596 | 8885.68 | 0.157362 | 1.26066 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5710.96 | 0.0326727 | 422.795ms | 24893 | 80 | 147.569 | 4156.89 | 0.190106 | 0.430918 | 1(Win) | true |
| Glaze | 3972.56 | 0.067177 | 596.278ms | 24579 | 30 | 471.357 | 5900.57 | 0.0446484 | 0.620678 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6005.52 | 0.0396896 | 397.59ms | 24893 | 40 | 98.4615 | 3953 | 0.0506201 | 0.409531 | 1(Win) | true |
| Glaze | 4360.92 | 0.0587331 | 545.28ms | 24579 | 40 | 398.656 | 5375.1 | 0.0434289 | 0.56487 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2121 | 0.170419 | 231.994ms | 5094 | 30 | 457.082 | 2290.43 | 0.090149 | 1.15434 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.25 | 0.403389 | 281.857ms | 5094 | 640 | 81437.1 | 2796.38 | 0.0625081 | 1.4121 | 2(Loss) | true |
| Glaze | 1282.71 | 0.0523539 | 382.32ms | 5094 | 80 | 314.521 | 3787.31 | 0.0617573 | 1.91662 | 3(Loss) | true |
| simdjson (ondemand) | 906.966 | 0.12883 | 538.823ms | 5094 | 4890 | 232853 | 5356.34 | 0.00695095 | 2.71596 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2650.44 | 0.0591808 | 229.285ms | 5094 | 80 | 94.1315 | 1832.91 | 0.223867 | 0.92032 | 1(Win) | true |
| Jsonifier (two-stage) | 2087.56 | 0.0768217 | 280.292ms | 5094 | 80 | 255.68 | 2327.12 | 0.24327 | 1.17257 | 2(Loss) | true |
| Glaze | 1584.55 | 0.0678194 | 356.899ms | 5094 | 40 | 172.933 | 3065.88 | 0.104756 | 1.54993 | 3(Loss) | true |
| simdjson (ondemand) | 1041.71 | 0.122981 | 509.219ms | 5094 | 4890 | 160846 | 4663.51 | 0.0818205 | 2.36189 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14649.1 | 0.109196 | 35.8079ms | 5094 | 80 | 10.4905 | 331.625 | 0.037679 | 0.155654 | 1(Win) | true |
| Glaze | 3356.32 | 0.227194 | 146.503ms | 5094 | 40 | 432.558 | 1447.42 | 0.0259014 | 0.724602 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15842.5 | 0.168734 | 32.8883ms | 5094 | 160 | 42.8346 | 306.644 | 0.00611496 | 0.141522 | 1(Win) | true |
| Glaze | 3709.24 | 0.257172 | 133.742ms | 5094 | 4890 | 55476.1 | 1309.71 | 0.0910055 | 0.65438 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2847.47 | 0.0428733 | 274.87ms | 8051 | 160 | 213.833 | 2696.44 | 0.107896 | 0.861109 | 1(Win) | true |
| Jsonifier (two-stage) | 2530.32 | 0.272062 | 305.478ms | 8051 | 1280 | 87235.8 | 3034.42 | 0.0735545 | 0.970092 | 2(Loss) | true |
| Glaze | 1692.75 | 0.0702929 | 460.499ms | 8051 | 30 | 304.971 | 4535.83 | 0.221445 | 1.45452 | 3(Loss) | true |
| simdjson (ondemand) | 1385.84 | 0.119899 | 558.237ms | 8051 | 4890 | 215780 | 5540.35 | 0.0537324 | 1.77783 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3405.75 | 0.0893664 | 270.702ms | 8051 | 30 | 121.771 | 2254.43 | 0.0266071 | 0.719165 | 1(Win) | true |
| Jsonifier (two-stage) | 3019.8 | 0.0864298 | 301.271ms | 8051 | 30 | 144.875 | 2542.57 | 0.352724 | 0.810997 | 2(Loss) | true |
| Glaze | 2026.38 | 0.178671 | 426.967ms | 8051 | 4890 | 224118 | 3789.04 | 0.0540051 | 1.21354 | 3(Loss) | true |
| simdjson (ondemand) | 1545.98 | 0.184038 | 554.208ms | 8051 | 40 | 3341.69 | 4966.45 | 0.0110755 | 1.59313 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19058.8 | 0.0548078 | 48.9279ms | 9255 | 320 | 20.6156 | 463.106 | 0.0188977 | 0.122698 | 1(Win) | true |
| Glaze | 4138.37 | 0.0846283 | 218.627ms | 9255 | 80 | 260.625 | 2132.79 | 0.0638427 | 0.591098 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19943.5 | 0.100477 | 46.8161ms | 9255 | 80 | 15.8188 | 442.562 | 0.0932941 | 0.116888 | 1(Win) | true |
| Glaze | 4561.64 | 0.0403256 | 198.337ms | 9255 | 320 | 194.815 | 1934.89 | 0.0303543 | 0.53536 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7098.65 | 0.198331 | 40.3696ms | 2889 | 40 | 23.7019 | 388.125 | 0.0279042 | 0.324152 | 1(Win) | true |
| Jsonifier (two-stage) | 7047.06 | 0.224621 | 41.4712ms | 2889 | 30 | 23.1368 | 390.967 | 0.0938727 | 0.326953 | 2(Loss) | true |
| simdjson (ondemand) | 6923.11 | 0.320455 | 42.734ms | 2889 | 30 | 48.792 | 397.967 | 0.167238 | 0.335918 | 3(Loss) | true |
| Glaze | 3416.73 | 0.0790616 | 84.4553ms | 2889 | 80 | 32.5158 | 806.375 | 0.139708 | 0.701138 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7668.28 | 0.0928243 | 38.8638ms | 2889 | 320 | 35.5937 | 359.294 | 0.123659 | 0.299595 | 1(Win) | true |
| Jsonifier (two-stage) | 7644.38 | 0.0414804 | 39.0071ms | 2889 | 1280 | 28.6092 | 360.417 | 0.103286 | 0.300358 | 2(Loss) | true |
| simdjson (ondemand) | 7095.2 | 0.067758 | 41.6621ms | 2889 | 640 | 44.3065 | 388.314 | 0.0567035 | 0.324665 | 3(Loss) | true |
| Glaze | 3411.06 | 0.320309 | 83.1557ms | 2889 | 4890 | 32731.5 | 807.716 | 0.127274 | 0.702757 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8413.28 | 0.199522 | 45.8262ms | 3808 | 40 | 29.6692 | 431.65 | 0.158057 | 0.27697 | 1(Win) | true |
| Jsonifier | 8355.45 | 0.132324 | 45.6867ms | 3808 | 80 | 26.4619 | 434.637 | 0.169394 | 0.278788 | 2(Loss) | true |
| simdjson (ondemand) | 8140.07 | 0.0744439 | 47.9333ms | 3808 | 320 | 35.2976 | 446.137 | 0.357352 | 0.286962 | 3(Loss) | true |
| Glaze | 3935.33 | 0.0514361 | 95.5495ms | 3808 | 160 | 36.0487 | 922.819 | 0.0616698 | 0.611425 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8613.32 | 0.185997 | 45.2114ms | 3808 | 40 | 24.5994 | 421.625 | 0.0888626 | 0.270339 | 1(Win) | true |
| Jsonifier | 8386.56 | 0.0726395 | 45.2844ms | 3808 | 320 | 31.6608 | 433.025 | 0.0461654 | 0.276856 | 2(Loss) | true |
| simdjson (ondemand) | 8201.89 | 0.177323 | 47.0581ms | 3808 | 80 | 49.3158 | 442.775 | 0.0225899 | 0.282908 | 3(Loss) | true |
| Glaze | 4018.88 | 0.103498 | 93.7047ms | 3808 | 30 | 26.2402 | 903.633 | 0.0110652 | 0.598302 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2567.59 | 0.0685935 | 112.957ms | 2889 | 160 | 86.6824 | 1073.06 | 0.00407731 | 0.940717 | 1(Win) | true |
| Glaze | 2174.04 | 0.0547281 | 129.55ms | 2889 | 160 | 76.966 | 1267.3 | 0.127077 | 1.11552 | 2(Loss) | true |
| Jsonifier (two-stage) | 2092.01 | 0.0976703 | 143.124ms | 2889 | 160 | 264.736 | 1316.99 | 0.229742 | 1.15992 | 3(Loss) | true |
| simdjson (ondemand) | 1057.31 | 0.0291837 | 265.293ms | 2889 | 320 | 185.064 | 2605.83 | 0.106977 | 2.31884 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2813.12 | 0.0346651 | 106.03ms | 2889 | 640 | 73.7703 | 979.397 | 0.0466065 | 0.856571 | 1(Win) | true |
| Glaze | 2339.11 | 0.036367 | 126.503ms | 2889 | 320 | 58.7163 | 1177.87 | 0.0503834 | 1.03506 | 2(Loss) | true |
| Jsonifier (two-stage) | 2285.72 | 0.0969182 | 129.216ms | 2889 | 160 | 218.363 | 1205.38 | 0.0968671 | 1.05945 | 3(Loss) | true |
| simdjson (ondemand) | 1088.91 | 0.109931 | 261.944ms | 2889 | 30 | 232.097 | 2530.2 | 0.0685527 | 2.24659 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13212.1 | 0.19373 | 24.1496ms | 2963 | 160 | 27.4686 | 213.875 | 0.0233836 | 0.164595 | 1(Win) | true |
| Glaze | 5311.3 | 0.0532268 | 56.3038ms | 2963 | 640 | 51.3218 | 532.023 | 0.148094 | 0.443995 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15261.4 | 0.151404 | 21.151ms | 2963 | 320 | 25.1479 | 185.156 | 0.0640939 | 0.140527 | 1(Win) | true |
| Glaze | 5590.78 | 0.0837676 | 52.4515ms | 2963 | 320 | 57.3616 | 505.428 | 0.00556428 | 0.420006 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2642.89 | 0.0948081 | 140.577ms | 3808 | 40 | 67.8872 | 1374.1 | 0.0315457 | 0.918822 | 1(Win) | true |
| Glaze | 2318.1 | 0.0820786 | 161.633ms | 3808 | 40 | 66.1378 | 1566.62 | 0.195897 | 1.04957 | 2(Loss) | true |
| Jsonifier | 2015.14 | 0.134645 | 124.112ms | 3808 | 40 | 235.515 | 1802.15 | 0.171385 | 1.20935 | 3(Loss) | true |
| simdjson (ondemand) | 1357.26 | 0.173232 | 270.248ms | 3808 | 4890 | 105058 | 2675.67 | 0.0647047 | 1.80659 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3324.64 | 0.0574576 | 116.878ms | 3808 | 160 | 63.0258 | 1092.33 | 0.0286005 | 0.727015 | 1(Win) | true |
| Jsonifier (two-stage) | 2852.98 | 0.22182 | 134.304ms | 3808 | 4890 | 38985.9 | 1272.91 | 0.129596 | 0.84927 | 2(Loss) | true |
| Glaze | 2479.24 | 0.0315865 | 155.381ms | 3808 | 320 | 68.5034 | 1464.8 | 0.0211161 | 0.980957 | 3(Loss) | true |
| simdjson (ondemand) | 1403.48 | 0.0506336 | 270.667ms | 3808 | 160 | 274.65 | 2587.56 | 0.0748214 | 1.74467 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11135.7 | 0.108008 | 39.1985ms | 4300 | 640 | 101.249 | 368.256 | 0.225384 | 0.206697 | 1(Win) | true |
| Glaze | 4107.47 | 0.0951959 | 102.655ms | 4300 | 80 | 72.2627 | 998.375 | 0.238454 | 0.586631 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12492 | 0.199988 | 35.4302ms | 4300 | 80 | 34.4804 | 328.275 | 0.0762137 | 0.182038 | 1(Win) | true |
| Glaze | 4675.41 | 0.224073 | 90.7826ms | 4300 | 40 | 154.503 | 877.1 | 0.236181 | 0.513924 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22472.8 | 0.723038 | 1987.7ms | 466906 | 160 | 3.28387e+06 | 19814 | 0.0468954 | 0.110007 | 1(Win) | true |
| simdjson (ondemand) | 21414.7 | 0.347663 | 1992.08ms | 466906 | 30 | 156774 | 20793 | 0.427281 | 0.115464 | 2(Loss) | true |
| Glaze | 2809.73 | 0.0900296 | 8152.34ms | 466906 | 640 | 1.3028e+07 | 158476 | 0.161349 | 0.880997 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 24701.5 | 0.0728348 | 1807.81ms | 466906 | 4890 | 842949 | 18026.3 | 0.054838 | 0.100073 | 1(Win) | true |
| Jsonifier | 22840.5 | 0.037488 | 1970.51ms | 466906 | 30 | 1602.34 | 19495.1 | 0.0703236 | 0.108271 | 2(Loss) | true |
| Glaze | 2772.36 | 0.106987 | 8196.12ms | 466906 | 1280 | 3.77944e+07 | 160613 | 0.0717483 | 0.892884 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5909.86 | 0.04304 | 5839.24ms | 699405 | 2560 | 6.04069e+06 | 112863 | 0.0889409 | 0.418788 | 1(Win) | true |
| Glaze | 3861.43 | 0.0548178 | 8903.5ms | 699405 | 1280 | 1.14766e+07 | 172735 | 0.0332877 | 0.641051 | 2(Loss) | true |
| simdjson (ondemand) | 2509.97 | 0.0647843 | 7446.35ms | 767297 | 640 | 2.28301e+07 | 291538 | 0.0718911 | 0.986256 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5886.08 | 0.314793 | 5861.09ms | 699405 | 30 | 3.81748e+06 | 113319 | 0.111801 | 0.420496 | 1(Win) | true |
| Glaze | 3816.48 | 0.0974811 | 9033.82ms | 699405 | 320 | 9.28799e+06 | 174769 | 0.0949419 | 0.648614 | 2(Loss) | true |
| simdjson (ondemand) | 2539.45 | 0.212948 | 7673.12ms | 767297 | 30 | 1.12958e+07 | 288153 | 0.0434796 | 0.974812 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4034.27 | 0.0481623 | 7669.72ms | 631514 | 1280 | 6.61702e+06 | 149286 | 0.135967 | 0.613588 | 1(Win) | true |
| Glaze | 2640.14 | 0.110455 | 5859.79ms | 631514 | 1280 | 8.12631e+07 | 228116 | 0.0432333 | 0.937653 | 2(Loss) | true |
