# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the Clang 24.0.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [c4ad752](https://github.com/nihilai-collective/Jsonifier/commit/c4ad752)  
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
| Jsonifier | 1750.3 | 0.158987 | 48.9981ms | 905 | 30 | 18.4379 | 493.1 | 0 | 1.33385 | 1(Win) | true |
| Glaze | 1376.76 | 0.087999 | 64.5357ms | 905 | 160 | 48.6917 | 626.888 | 0.0858146 | 1.72026 | 2(Loss) | true |
| simdjson (ondemand) | 436.257 | 0.215075 | 203.398ms | 905 | 4890 | 88532.1 | 1978.36 | 0.415361 | 5.59728 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1711.71 | 0.456286 | 52.1215ms | 905 | 160 | 846.902 | 504.219 | 0.201638 | 1.36527 | 1(Win) | true |
| Glaze | 1390.71 | 0.376001 | 67.2337ms | 905 | 30 | 163.352 | 620.6 | 0.323311 | 1.70162 | 2(Loss) | true |
| simdjson (ondemand) | 443.387 | 0.0469464 | 200.72ms | 905 | 80 | 66.8076 | 1946.55 | 0.526356 | 5.50985 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2121.29 | 0.134105 | 43.5174ms | 905 | 80 | 23.8163 | 406.863 | 0.0030722 | 1.09052 | 1(Win) | true |
| Glaze | 196.57 | 0.0378807 | 442.231ms | 905 | 30 | 82.9885 | 4390.67 | 0.0394933 | 12.5135 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3996.01 | 0.131503 | 29.3107ms | 905 | 320 | 25.8148 | 215.984 | 0.0708461 | 0.543936 | 1(Win) | true |
| Glaze | 932.853 | 0.145067 | 101.882ms | 905 | 80 | 144.111 | 925.2 | 0.0351399 | 2.57584 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1314.94 | 0.0755942 | 135.045ms | 1811 | 40 | 39.4333 | 1313.45 | 0.041892 | 1.84335 | 1(Win) | true |
| Glaze | 778.861 | 0.572109 | 212.807ms | 1811 | 80 | 12875.5 | 2217.47 | 0.408699 | 3.13798 | 2(Loss) | true |
| simdjson (ondemand) | 421.238 | 0.268018 | 411.62ms | 1811 | 1280 | 154568 | 4100.07 | 0.615609 | 5.83826 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1403.15 | 0.0866456 | 127.043ms | 1811 | 40 | 45.4968 | 1230.88 | 0.0777973 | 1.72702 | 1(Win) | true |
| Glaze | 897.244 | 0.109255 | 198.716ms | 1811 | 40 | 176.913 | 1924.9 | 0.0346458 | 2.72125 | 2(Loss) | true |
| simdjson (ondemand) | 438.203 | 0.165343 | 400.827ms | 1811 | 30 | 1274.02 | 3941.33 | 0.0228297 | 5.61055 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 349.448 | 0.16104 | 546.002ms | 1997 | 4890 | 376675 | 5449.99 | 0.0404443 | 7.04987 | 1(Win) | true |
| Glaze | 273.15 | 0.0665831 | 646.673ms | 1798 | 40 | 698.82 | 6277.52 | 0.0110194 | 9.02656 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 895.087 | 0.0298625 | 224.511ms | 1997 | 320 | 129.19 | 2127.71 | 0.448289 | 2.73027 | 1(Win) | true |
| Glaze | 576.854 | 0.053901 | 310.461ms | 1798 | 80 | 205.367 | 2972.51 | 0.289734 | 4.25351 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1440.03 | 0.0925798 | 90.9884ms | 1313 | 80 | 51.8456 | 869.55 | 0.409931 | 1.66431 | 1(Win) | true |
| Glaze | 859.117 | 0.0407857 | 149.088ms | 1313 | 160 | 56.5407 | 1457.51 | 0.0728451 | 2.82741 | 2(Loss) | true |
| simdjson (ondemand) | 335.037 | 0.0693889 | 363.843ms | 1313 | 40 | 269.02 | 3737.43 | 0.0568897 | 7.33701 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1605.12 | 0.0604005 | 82.4031ms | 1313 | 320 | 71.0469 | 780.112 | 0.0464461 | 1.48996 | 1(Win) | true |
| Glaze | 909.854 | 0.288582 | 138.638ms | 1313 | 2560 | 40379.8 | 1376.24 | 1.11485 | 2.66603 | 2(Loss) | true |
| simdjson (ondemand) | 357.483 | 0.0492763 | 349.187ms | 1313 | 40 | 119.167 | 3502.75 | 0.193078 | 6.87173 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 327.414 | 0.0725263 | 388.554ms | 1313 | 30 | 230.806 | 3824.43 | 0.252525 | 7.50881 | 1(Win) | true |
| Glaze | 286.14 | 0.181034 | 456.141ms | 1313 | 2560 | 160670 | 4376.08 | 0.128366 | 8.60115 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2229.56 | 0.116634 | 67.044ms | 1313 | 40 | 17.1635 | 561.625 | 0.0489411 | 1.05588 | 1(Win) | true |
| Glaze | 1112.35 | 0.274024 | 123.597ms | 1313 | 30 | 285.459 | 1125.7 | 0.115617 | 2.17091 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1350.05 | 0.0789299 | 301.214ms | 4215 | 40 | 220.922 | 2977.47 | 0.224239 | 1.81735 | 1(Win) | true |
| Glaze | 969.145 | 0.389832 | 410.988ms | 4215 | 640 | 167322 | 4147.72 | 0.202024 | 2.53792 | 2(Loss) | true |
| simdjson (ondemand) | 803.905 | 0.245527 | 500.641ms | 4215 | 1280 | 192927 | 5000.26 | 0.220408 | 3.0632 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1958.55 | 0.0436912 | 248.672ms | 4215 | 160 | 128.657 | 2052.4 | 0.535152 | 1.24755 | 1(Win) | true |
| Glaze | 1271.48 | 0.283669 | 358.691ms | 4215 | 30 | 2412.81 | 3161.47 | 0.274434 | 1.9311 | 2(Loss) | true |
| simdjson (ondemand) | 939.218 | 0.0807784 | 461.551ms | 4215 | 80 | 956.187 | 4279.88 | 0.237133 | 2.61917 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1795.41 | 0.0730105 | 234.215ms | 4215 | 80 | 213.762 | 2238.9 | 0.101509 | 1.36281 | 1(Win) | true |
| Glaze | 891.597 | 0.0755795 | 453.5ms | 4215 | 30 | 348.326 | 4508.47 | 0.0295652 | 2.75954 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5721.74 | 0.111153 | 79.4232ms | 4215 | 80 | 48.7834 | 702.538 | 0.101521 | 0.416041 | 1(Win) | true |
| Glaze | 2101.14 | 0.149869 | 199.931ms | 4215 | 40 | 328.83 | 1913.12 | 0.00653424 | 1.16241 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1595.13 | 0.483388 | 73.9149ms | 1213 | 80 | 983.131 | 725.212 | 0.254018 | 1.49471 | 1(Win) | true |
| Glaze | 921.089 | 0.186256 | 128.905ms | 1213 | 80 | 437.752 | 1255.91 | 0.0984369 | 2.62966 | 2(Loss) | true |
| simdjson (ondemand) | 298.976 | 0.0957829 | 387.403ms | 1213 | 30 | 412.047 | 3869.23 | 0.112984 | 8.22295 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1820.99 | 0.0932015 | 67.0044ms | 1213 | 80 | 28.0441 | 635.263 | 0.159637 | 1.30258 | 1(Win) | true |
| Glaze | 972.788 | 0.107592 | 121.918ms | 1213 | 30 | 49.1092 | 1189.17 | 0.0196177 | 2.48634 | 2(Loss) | true |
| simdjson (ondemand) | 309.026 | 0.136923 | 380.624ms | 1213 | 40 | 1050.86 | 3743.4 | 0.255795 | 7.95418 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 309.964 | 0.140883 | 377.823ms | 1213 | 4890 | 135185 | 3732.07 | 0.0585121 | 7.9301 | 1(Win) | true |
| Glaze | 244.633 | 0.180808 | 500.334ms | 1213 | 2560 | 187140 | 4728.74 | 0.671226 | 10.063 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2115.88 | 0.18173 | 64.834ms | 1213 | 40 | 39.4865 | 546.725 | 0.157242 | 1.11127 | 1(Win) | true |
| Glaze | 1049.63 | 0.0656549 | 119.603ms | 1213 | 160 | 83.7734 | 1102.11 | 0.304168 | 2.29998 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19976 | 0.486142 | 2226.23ms | 466906 | 160 | 1.87884e+06 | 22290.6 | 0.304998 | 0.123776 | 1(Win) | true |
| simdjson (ondemand) | 19510.4 | 0.113261 | 2290.72ms | 466906 | 2560 | 1.7105e+06 | 22822.5 | 0.262035 | 0.126716 | 2(Loss) | true |
| Glaze | 2624.47 | 0.0834521 | 8745.15ms | 466906 | 640 | 1.28301e+07 | 169663 | 0.081305 | 0.94319 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 23488.8 | 0.437929 | 1919.22ms | 466906 | 80 | 551359 | 18957 | 0.0321885 | 0.105255 | 1(Win) | true |
| Jsonifier | 19950.4 | 0.0838582 | 2229.01ms | 466906 | 4890 | 1.713e+06 | 22319.2 | 0.607306 | 0.123933 | 2(Loss) | true |
| Glaze | 2536.18 | 0.134034 | 8754.25ms | 466906 | 640 | 3.54415e+07 | 175570 | 0.0136102 | 0.976031 | 3(Loss) | true |
