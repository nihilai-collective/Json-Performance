# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1910.73 | 0.155779 | 46.3337ms | 905 | 40 | 19.8051 | 451.7 | 0.00737898 | 1.22083 | 1(Win) | true |
| Glaze | 1475.66 | 0.13443 | 63.247ms | 905 | 40 | 24.7276 | 584.875 | 0.0555366 | 1.60298 | 2(Loss) | true |
| simdjson (ondemand) | 449.603 | 0.0357979 | 191.841ms | 905 | 80 | 37.7783 | 1919.64 | 0.309644 | 5.42938 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1867.86 | 0.134067 | 48.9318ms | 905 | 30 | 11.5126 | 462.067 | 0.303907 | 1.25053 | 1(Win) | true |
| Glaze | 1509.33 | 0.0305155 | 60.7288ms | 905 | 320 | 9.74357 | 571.825 | 0.124757 | 1.56762 | 2(Loss) | true |
| simdjson (ondemand) | 470.481 | 0.0532368 | 187.189ms | 905 | 320 | 305.202 | 1834.45 | 0.345804 | 5.18996 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2231.54 | 0.0501083 | 41.9908ms | 905 | 640 | 24.0374 | 386.762 | 0.154894 | 1.03639 | 1(Win) | true |
| Glaze | 198.489 | 0.679537 | 427.505ms | 905 | 1280 | 1.11753e+06 | 4348.23 | 0.627461 | 12.3985 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4126.95 | 0.163387 | 28.6327ms | 905 | 160 | 18.6808 | 209.131 | 0.0867432 | 0.526989 | 1(Win) | true |
| Glaze | 998.872 | 0.0792016 | 94.82ms | 905 | 80 | 37.4658 | 864.05 | 0.214567 | 2.40269 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1308.83 | 0.0366469 | 137.122ms | 1811 | 320 | 74.8335 | 1319.58 | 0.074416 | 1.85219 | 1(Win) | true |
| Glaze | 898.006 | 0.101263 | 200.106ms | 1811 | 30 | 113.789 | 1923.27 | 0.0520219 | 2.72006 | 2(Loss) | true |
| simdjson (ondemand) | 399.78 | 0.0680604 | 437.989ms | 1811 | 30 | 259.361 | 4320.13 | 0.0701646 | 6.15794 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1395.98 | 0.0845866 | 126.939ms | 1811 | 30 | 32.8552 | 1237.2 | 0.0565474 | 1.73379 | 1(Win) | true |
| Glaze | 947.882 | 0.0681602 | 191.976ms | 1811 | 30 | 46.2713 | 1822.07 | 0.0347712 | 2.57315 | 2(Loss) | true |
| simdjson (ondemand) | 407.373 | 0.0550653 | 433.26ms | 1811 | 80 | 436.013 | 4239.61 | 0.0469013 | 6.04161 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 363.335 | 0.251719 | 532.513ms | 1997 | 1280 | 222835 | 5241.68 | 0.347525 | 6.78021 | 1(Win) | true |
| Glaze | 286.852 | 0.088497 | 609.188ms | 1798 | 30 | 839.54 | 5977.67 | 0.172605 | 8.59192 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 954.302 | 0.0519497 | 212.551ms | 1997 | 160 | 171.977 | 1995.69 | 0.0909034 | 2.56093 | 1(Win) | true |
| Glaze | 593.306 | 0.0470431 | 302.94ms | 1798 | 80 | 147.878 | 2890.09 | 0.233669 | 4.13563 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1529.89 | 0.0599054 | 85.5947ms | 1313 | 160 | 38.4648 | 818.475 | 0.149893 | 1.56882 | 1(Win) | true |
| Glaze | 933.274 | 0.0991073 | 137.911ms | 1313 | 30 | 53.0448 | 1341.7 | 0.0992778 | 2.60188 | 2(Loss) | true |
| simdjson (ondemand) | 347.305 | 0.0672014 | 364.42ms | 1313 | 30 | 176.11 | 3605.4 | 0.0194116 | 7.07908 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1638.05 | 0.057585 | 78.1373ms | 1313 | 320 | 62.0078 | 764.431 | 0.00163523 | 1.45909 | 1(Win) | true |
| Glaze | 988.723 | 0.0367797 | 132.688ms | 1313 | 160 | 34.7151 | 1266.46 | 0.0735861 | 2.45265 | 2(Loss) | true |
| simdjson (ondemand) | 353.112 | 0.0287522 | 358.161ms | 1313 | 80 | 83.1644 | 3546.11 | 0.199559 | 6.95685 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 331.839 | 0.0186796 | 374.172ms | 1313 | 160 | 79.4929 | 3773.44 | 0.11342 | 7.40735 | 1(Win) | true |
| Glaze | 282.991 | 0.15405 | 449.378ms | 1313 | 4890 | 227206 | 4424.79 | 0.35147 | 8.69584 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2353.49 | 0.0848425 | 61.4937ms | 1313 | 80 | 16.3013 | 532.05 | 0.00939673 | 1.00015 | 1(Win) | true |
| Glaze | 1121.32 | 0.0780659 | 121.092ms | 1313 | 160 | 121.595 | 1116.7 | 0.0917041 | 2.15598 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1394.37 | 0.0546889 | 291.457ms | 4215 | 160 | 397.701 | 2882.83 | 0.168738 | 1.76039 | 1(Win) | true |
| Glaze | 1013.29 | 0.0576528 | 390.757ms | 4215 | 40 | 209.231 | 3967 | 0.159396 | 2.42709 | 2(Loss) | true |
| simdjson (ondemand) | 834.27 | 0.118621 | 492.541ms | 4215 | 30 | 979.995 | 4818.27 | 0.00830243 | 2.9528 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2015.28 | 0.154487 | 238.994ms | 4215 | 30 | 284.861 | 1994.63 | 0.247944 | 1.21249 | 1(Win) | true |
| Glaze | 1322.53 | 0.0488448 | 347.761ms | 4215 | 80 | 176.323 | 3039.43 | 0.185546 | 1.85628 | 2(Loss) | true |
| simdjson (ondemand) | 982.693 | 0.17836 | 442.375ms | 4215 | 2560 | 136268 | 4090.53 | 0.0813036 | 2.50358 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1829.19 | 0.0376506 | 224.816ms | 4215 | 160 | 109.532 | 2197.55 | 0.188062 | 1.33722 | 1(Win) | true |
| Glaze | 931.169 | 0.283951 | 435.224ms | 4215 | 1280 | 192325 | 4316.87 | 0.361626 | 2.64302 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5910.67 | 0.096548 | 76.48ms | 4215 | 160 | 68.9808 | 680.081 | 0.0266583 | 0.403302 | 1(Win) | true |
| Glaze | 2288.14 | 0.0646191 | 184.631ms | 4215 | 160 | 206.191 | 1756.77 | 0.0359454 | 1.0663 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1729.09 | 0.081738 | 70.3644ms | 1213 | 80 | 23.9234 | 669.025 | 0.149248 | 1.37705 | 1(Win) | true |
| Glaze | 961.857 | 0.0486149 | 123.112ms | 1213 | 160 | 54.6965 | 1202.68 | 0.011951 | 2.51974 | 2(Loss) | true |
| simdjson (ondemand) | 313.399 | 0.174403 | 371.269ms | 1213 | 30 | 1243.25 | 3691.17 | 0.172782 | 7.84765 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1913.03 | 0.0480143 | 63.8444ms | 1213 | 320 | 26.9755 | 604.7 | 0.0806835 | 1.23872 | 1(Win) | true |
| Glaze | 1024.48 | 0.0634382 | 117.804ms | 1213 | 80 | 41.0492 | 1129.16 | 0.00332094 | 2.36012 | 2(Loss) | true |
| simdjson (ondemand) | 327.309 | 0.263806 | 358.082ms | 1213 | 40 | 3477.24 | 3534.3 | 0.0745635 | 7.5095 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 330.821 | 0.034636 | 356.415ms | 1213 | 160 | 234.7 | 3496.78 | 0.432076 | 7.4296 | 1(Win) | true |
| Glaze | 266.558 | 0.319214 | 434.241ms | 1213 | 2560 | 491294 | 4339.79 | 0.377064 | 9.2335 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2275.19 | 0.0785079 | 59.7656ms | 1213 | 160 | 25.4937 | 508.444 | 0.0873524 | 1.03305 | 1(Win) | true |
| Glaze | 1118.23 | 0.143134 | 111.697ms | 1213 | 30 | 65.7759 | 1034.5 | 0.119363 | 2.1576 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 23213.8 | 0.208681 | 1915.62ms | 466906 | 640 | 1.02545e+06 | 19181.5 | 0.320373 | 0.106476 | 1(Win) | true |
| Jsonifier | 22654.8 | 0.0975336 | 1982.65ms | 466906 | 4890 | 1.79703e+06 | 19654.8 | 0.0229743 | 0.109128 | 2(Loss) | true |
| Glaze | 2827.86 | 0.0970932 | 8218.29ms | 466906 | 2560 | 5.98359e+07 | 157461 | 0.528516 | 0.875352 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 24623.6 | 0.0978543 | 1817.63ms | 466906 | 2560 | 801598 | 18083.3 | 0.147216 | 0.100396 | 1(Win) | true |
| Jsonifier | 22638.5 | 0.169578 | 1986.15ms | 466906 | 1280 | 1.42401e+06 | 19669 | 0.183605 | 0.109213 | 2(Loss) | true |
| Glaze | 2786.72 | 0.103893 | 8135.46ms | 466906 | 2560 | 7.0548e+07 | 159785 | 0.211905 | 0.888285 | 3(Loss) | true |
