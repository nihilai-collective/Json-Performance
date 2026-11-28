# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the Clang 24.0.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [8c470bc](https://github.com/nihilai-collective/Jsonifier/commit/8c470bc)  
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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1794.09 | 0.161919 | 48.1883ms | 905 | 30 | 18.2023 | 481.067 | 0 | 1.30033 | 1(Win) | true |
| Glaze | 1415.2 | 0.0835591 | 67.4987ms | 905 | 320 | 83.0993 | 609.859 | 0.0281748 | 1.67166 | 2(Loss) | true |
| simdjson (ondemand) | 413.456 | 0.0600152 | 200.939ms | 905 | 30 | 47.0851 | 2087.47 | 0.0127763 | 5.90947 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1811.57 | 0.163857 | 50.0584ms | 905 | 80 | 48.7538 | 476.425 | 0.319071 | 1.28808 | 1(Win) | true |
| Glaze | 1459.32 | 0.0300212 | 62.629ms | 905 | 320 | 10.0879 | 591.422 | 0.094492 | 1.61972 | 2(Loss) | true |
| simdjson (ondemand) | 436.264 | 0.0527278 | 201.252ms | 905 | 30 | 32.6437 | 1978.33 | 0.350913 | 5.59827 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2070.39 | 0.215401 | 43.9472ms | 905 | 30 | 24.1885 | 416.867 | 0.208333 | 1.11731 | 1(Win) | true |
| Glaze | 193.587 | 0.0579969 | 450.628ms | 905 | 30 | 200.575 | 4458.33 | 0.149757 | 12.7116 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3892.67 | 0.0436747 | 30.0058ms | 905 | 1280 | 12.0025 | 221.718 | 0.113236 | 0.557611 | 1(Win) | true |
| Glaze | 938.189 | 0.0677404 | 100.28ms | 905 | 160 | 62.1344 | 919.938 | 0.0475802 | 2.56112 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1294.9 | 0.0870006 | 136.99ms | 1811 | 80 | 107.721 | 1333.78 | 0.0581395 | 1.87294 | 1(Win) | true |
| Glaze | 848.658 | 0.10148 | 207.366ms | 1811 | 30 | 127.955 | 2035.1 | 0.0327692 | 2.87707 | 2(Loss) | true |
| simdjson (ondemand) | 427.996 | 0.0875089 | 410.772ms | 1811 | 80 | 997.589 | 4035.32 | 0.125302 | 5.74654 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1401.31 | 0.0371799 | 127.467ms | 1811 | 160 | 33.5974 | 1232.49 | 0.219094 | 1.72836 | 1(Win) | true |
| Glaze | 883.61 | 0.0555376 | 200.952ms | 1811 | 30 | 35.3517 | 1954.6 | 0.242752 | 2.7617 | 2(Loss) | true |
| simdjson (ondemand) | 436.799 | 0.120204 | 403.163ms | 1811 | 40 | 903.59 | 3954 | 0.151976 | 5.6296 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 356.784 | 0.017577 | 548.252ms | 1997 | 80 | 70.4247 | 5337.93 | 0.0445127 | 6.9045 | 1(Win) | true |
| Glaze | 272.999 | 0.0644198 | 634.995ms | 1798 | 40 | 654.872 | 6281 | 0.018578 | 9.02977 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 896.736 | 0.0245318 | 225.244ms | 1997 | 160 | 43.4314 | 2123.8 | 0.243075 | 2.72599 | 1(Win) | true |
| Glaze | 537.655 | 0.0941588 | 329.12ms | 1798 | 30 | 270.53 | 3189.23 | 0.0355489 | 4.56704 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.15 | 0.044044 | 88.9446ms | 1313 | 320 | 44.8495 | 849.997 | 0.0767795 | 1.62685 | 1(Win) | true |
| Glaze | 880.797 | 0.0362625 | 146.309ms | 1313 | 160 | 42.5219 | 1421.64 | 0.105624 | 2.75808 | 2(Loss) | true |
| simdjson (ondemand) | 327.725 | 0.0371928 | 380.296ms | 1313 | 160 | 323.109 | 3820.81 | 0.340745 | 7.50031 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1542.66 | 0.0980638 | 84.6869ms | 1313 | 40 | 25.3436 | 811.7 | 0.0164291 | 1.55286 | 1(Win) | true |
| Glaze | 921.496 | 0.0548657 | 138.552ms | 1313 | 40 | 22.2333 | 1358.85 | 0.0355819 | 2.63163 | 2(Loss) | true |
| simdjson (ondemand) | 351.179 | 0.0265379 | 366.652ms | 1313 | 80 | 71.6297 | 3565.62 | 0.0574604 | 6.99351 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 327.786 | 0.242852 | 387.847ms | 1313 | 1280 | 110165 | 3820.1 | 0.0602237 | 7.50004 | 1(Win) | true |
| Glaze | 273.714 | 0.490795 | 467.209ms | 1313 | 320 | 161318 | 4574.75 | 0.307335 | 8.99017 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2218.66 | 0.0361371 | 66.884ms | 1313 | 640 | 26.6216 | 564.383 | 0.143892 | 1.06338 | 1(Win) | true |
| Glaze | 1007.05 | 0.253196 | 133.607ms | 1313 | 4890 | 48467.6 | 1243.41 | 0.140463 | 2.40535 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1307.37 | 0.0936073 | 324.443ms | 4215 | 30 | 248.506 | 3074.67 | 0.229276 | 1.87704 | 1(Win) | true |
| Glaze | 965.175 | 0.0662353 | 420.767ms | 4215 | 40 | 304.384 | 4164.77 | 0.0350036 | 2.54785 | 2(Loss) | true |
| simdjson (ondemand) | 815.404 | 0.274949 | 502.941ms | 4215 | 1280 | 235160 | 4929.75 | 0.118205 | 3.01983 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1858.73 | 0.0851449 | 257.062ms | 4215 | 80 | 271.25 | 2162.62 | 0.0866251 | 1.31539 | 1(Win) | true |
| Glaze | 1255.42 | 0.0271314 | 364.353ms | 4215 | 320 | 241.498 | 3201.92 | 0.0240148 | 1.95539 | 2(Loss) | true |
| simdjson (ondemand) | 952.291 | 0.175307 | 472.787ms | 4215 | 40 | 2190.37 | 4221.12 | 0.12166 | 2.5841 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1743.71 | 0.0424325 | 233.759ms | 4215 | 160 | 153.097 | 2305.28 | 0.115901 | 1.40345 | 1(Win) | true |
| Glaze | 879.864 | 0.281177 | 459.179ms | 4215 | 1280 | 211219 | 4568.59 | 0.23938 | 2.7973 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5758.66 | 0.140514 | 78.9356ms | 4215 | 30 | 28.8609 | 698.033 | 0.138293 | 0.413064 | 1(Win) | true |
| Glaze | 2167.21 | 0.150605 | 196.873ms | 4215 | 30 | 234.097 | 1854.8 | 0.0161769 | 1.12511 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1560.21 | 0.332654 | 76.565ms | 1213 | 4890 | 29747.6 | 741.444 | 0.334293 | 1.52945 | 1(Win) | true |
| Glaze | 891.734 | 0.161918 | 133.501ms | 1213 | 320 | 1411.85 | 1297.26 | 0.00963665 | 2.71821 | 2(Loss) | true |
| simdjson (ondemand) | 302.805 | 0.130927 | 384.627ms | 1213 | 40 | 1000.73 | 3820.3 | 0.0139625 | 8.12133 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1767.11 | 0.155797 | 68.745ms | 1213 | 30 | 31.2057 | 654.633 | 0.101735 | 1.34248 | 1(Win) | true |
| Glaze | 960.753 | 0.0554252 | 123.65ms | 1213 | 80 | 35.629 | 1204.06 | 0.0176517 | 2.51795 | 2(Loss) | true |
| simdjson (ondemand) | 307.923 | 0.303087 | 382.054ms | 1213 | 640 | 82976 | 3756.81 | 0.0253354 | 7.98233 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 308.173 | 0.0575051 | 382.271ms | 1213 | 80 | 372.766 | 3753.76 | 0.0502576 | 7.97518 | 1(Win) | true |
| Glaze | 252.066 | 0.334205 | 475.238ms | 1213 | 30 | 7057.32 | 4589.3 | 0.012346 | 9.76263 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2135.12 | 0.14942 | 64.9595ms | 1213 | 40 | 26.2154 | 541.8 | 0.202616 | 1.1006 | 1(Win) | true |
| Glaze | 1052.34 | 0.0904924 | 120.724ms | 1213 | 80 | 79.1639 | 1099.28 | 0.215586 | 2.29475 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 23663.4 | 0.0698191 | 1993.84ms | 466906 | 30 | 5178.13 | 18817.1 | 0.00372017 | 0.104473 | 1(Win) | true |
| Jsonifier | 21757.8 | 0.410326 | 2085.04ms | 466906 | 80 | 564126 | 20465.1 | 0.0104435 | 0.113618 | 2(Loss) | true |
| Glaze | 2627.59 | 0.0402233 | 8785.48ms | 466906 | 2560 | 1.18943e+07 | 169462 | 0.42795 | 0.942078 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21832.5 | 0.0686021 | 2075.35ms | 466906 | 30 | 5872.82 | 20395.1 | 0.140523 | 0.113246 | 1(Win) | true |
| simdjson (ondemand) | 19801.2 | 0.0773286 | 2282.3ms | 466906 | 4890 | 1.47865e+06 | 22487.3 | 0.652701 | 0.124867 | 2(Loss) | true |
| Glaze | 2661.43 | 0.104134 | 8643.88ms | 466906 | 320 | 9.71326e+06 | 167307 | 0.00797498 | 0.930103 | 3(Loss) | true |
