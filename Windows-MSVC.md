# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on Windows 10.0.26200 using the MSVC 19.52.37029.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 642.139 | 0.135004 | 138.969ms | 905 | 2560 | 8428.98 | 1344.06 | 0.0638978 | 4.67091 | 1(Win) | true |
| Glaze | 626.41 | 1.14773 | 140.796ms | 905 | 4890 | 1.22283e+06 | 1377.81 | 0.0368236 | 4.78667 | 2(Loss) | true |
| simdjson (ondemand) | 182.597 | 0.267098 | 498.81ms | 905 | 30 | 4781.61 | 4726.67 | 0.212014 | 16.5958 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.706 | 0.211577 | 122.548ms | 905 | 320 | 1971.39 | 1173.12 | 0.0533049 | 4.06509 | 1(Win) | true |
| Glaze | 714.716 | 0.167482 | 127.093ms | 905 | 1280 | 5235.72 | 1207.58 | 0.457239 | 4.18244 | 2(Loss) | true |
| simdjson (ondemand) | 182.282 | 0.220193 | 471.822ms | 905 | 640 | 69566.5 | 4734.84 | 0.0560686 | 16.5953 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1147.9 | 0.527012 | 83.273ms | 905 | 160 | 2512.19 | 751.875 | 0.25 | 2.58497 | 1(Win) | true |
| Glaze | 100.551 | 1.6524 | 967.082ms | 905 | 640 | 1.28746e+07 | 8583.44 | 0.116639 | 30.1523 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1626.53 | 0.688895 | 63.9019ms | 905 | 160 | 2137.97 | 530.625 | 0.35461 | 1.78311 | 1(Win) | true |
| Glaze | 529.291 | 1.00557 | 189.376ms | 905 | 160 | 43018.5 | 1630.62 | 0.346154 | 5.67113 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 762.098 | 0.440121 | 245.357ms | 1811 | 320 | 31835.4 | 2266.25 | 0.0551876 | 3.95152 | 1(Win) | true |
| Glaze | 451.826 | 0.238585 | 394.897ms | 1811 | 40 | 3326.92 | 3822.5 | 0.503944 | 6.69651 | 2(Loss) | true |
| simdjson (ondemand) | 330.23 | 0.227348 | 560.745ms | 1811 | 30 | 4241.38 | 5230 | 0.0637755 | 9.1605 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 980.961 | 0.220075 | 182.792ms | 1811 | 160 | 2402.12 | 1760.62 | 1.55011 | 3.05504 | 1(Win) | true |
| Glaze | 596.238 | 0.201593 | 316.722ms | 1811 | 30 | 1022.99 | 2896.67 | 0 | 5.05489 | 2(Loss) | true |
| simdjson (ondemand) | 364.56 | 0.608177 | 494.845ms | 1811 | 640 | 531299 | 4737.5 | 0.158562 | 8.29686 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 493.86 | 0.457137 | 405.005ms | 1997 | 2560 | 795575 | 3856.33 | 0.222352 | 6.12542 | 1(Win) | true |
| Glaze | 152.52 | 0.907481 | 1144.81ms | 1798 | 40 | 416353 | 11242.5 | 1.10162 | 19.8955 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 811.571 | 0.394777 | 270.738ms | 1997 | 30 | 2574.71 | 2346.67 | 0 | 3.69534 | 1(Win) | true |
| Glaze | 440.515 | 0.192678 | 427.557ms | 1798 | 40 | 2250 | 3892.5 | 0.0642674 | 6.87152 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1010.07 | 0.312862 | 132.585ms | 1313 | 640 | 9627.45 | 1239.69 | 2.33875 | 2.96665 | 1(Win) | true |
| Glaze | 366.133 | 0.217188 | 368.186ms | 1313 | 30 | 1655.17 | 3420 | 0 | 8.27086 | 2(Loss) | true |
| simdjson (ondemand) | 324.959 | 0.240418 | 420.958ms | 1313 | 30 | 2574.71 | 3853.33 | 0.434405 | 9.29086 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1471.52 | 0.328928 | 92.0675ms | 1313 | 320 | 2506.96 | 850.938 | 0.331614 | 2.02002 | 1(Win) | true |
| Glaze | 417.391 | 0.159821 | 325.244ms | 1313 | 30 | 689.655 | 3000 | 0.896861 | 7.15065 | 2(Loss) | true |
| simdjson (ondemand) | 368.422 | 0.110954 | 375.465ms | 1313 | 80 | 1137.66 | 3398.75 | 0.40293 | 8.17011 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 608.96 | 1.30455 | 219.309ms | 1313 | 640 | 460524 | 2056.25 | 0.136965 | 4.93147 | 1(Win) | true |
| Glaze | 135.265 | 1.62936 | 918.455ms | 1313 | 4890 | 1.11249e+08 | 9257.18 | 1.2392 | 22.4072 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1521.24 | 0.207911 | 104.426ms | 1313 | 640 | 1874.41 | 823.125 | 0 | 1.94853 | 1(Win) | true |
| Glaze | 726.6 | 0.455747 | 191.398ms | 1313 | 30 | 1850.57 | 1723.33 | 0.38835 | 4.1183 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 652.638 | 1.10401 | 650.417ms | 4215 | 640 | 2.9592e+06 | 6159.22 | 0.11909 | 4.63638 | 1(Win) | true |
| Glaze | 518.425 | 0.344098 | 778.314ms | 4215 | 80 | 56947.8 | 7753.75 | 0.847187 | 5.84295 | 2(Loss) | true |
| simdjson (ondemand) | 482.724 | 0.179053 | 894.618ms | 4215 | 320 | 71139.4 | 8327.19 | 0.748659 | 6.27908 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1188.83 | 0.273851 | 465.519ms | 4215 | 80 | 6859.18 | 3381.25 | 0.697504 | 2.53992 | 1(Win) | true |
| Glaze | 849.24 | 0.25492 | 601.844ms | 4215 | 30 | 4367.82 | 4733.33 | 0.141044 | 3.56233 | 2(Loss) | true |
| simdjson (ondemand) | 688.606 | 0.170066 | 721.076ms | 4215 | 40 | 3942.31 | 5837.5 | 0.0714286 | 4.4026 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 581.517 | 0.344324 | 714.407ms | 4215 | 40 | 22660.3 | 6912.5 | 0.521086 | 5.20888 | 1(Win) | true |
| Glaze | 458.253 | 0.986559 | 936.49ms | 4215 | 160 | 1.19826e+06 | 8771.88 | 0.826738 | 6.61466 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5134.99 | 0.515935 | 92.4595ms | 4215 | 640 | 10439.7 | 782.812 | 0.521669 | 0.576021 | 1(Win) | true |
| Glaze | 1707.57 | 0.313359 | 268.27ms | 4215 | 320 | 17412.9 | 2354.06 | 0.76244 | 1.75978 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 994.301 | 0.150044 | 125.332ms | 1213 | 1280 | 3900.61 | 1163.44 | 0.242326 | 3.00461 | 1(Win) | true |
| Glaze | 340.613 | 0.152203 | 370.202ms | 1213 | 80 | 2137.66 | 3396.25 | 0.0367918 | 8.88511 | 2(Loss) | true |
| simdjson (ondemand) | 287.763 | 0.184771 | 436.52ms | 1213 | 30 | 1655.17 | 4020 | 0.248139 | 10.5053 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1458.83 | 0.925311 | 84.8688ms | 1213 | 2560 | 137825 | 792.969 | 0.664485 | 2.0141 | 1(Win) | true |
| Glaze | 383.049 | 0.245954 | 320.943ms | 1213 | 30 | 1655.17 | 3020 | 0.778643 | 7.79481 | 2(Loss) | true |
| simdjson (ondemand) | 324.832 | 0.153912 | 382.301ms | 1213 | 80 | 2403.48 | 3561.25 | 0.0351124 | 9.27876 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 593.234 | 0.233702 | 207.989ms | 1213 | 320 | 6645.77 | 1950 | 2.5609 | 5.07948 | -(Win) | false |
| Glaze | 137.266 | 0.853821 | 908.227ms | 1213 | 160 | 828421 | 8427.5 | 0.882837 | 22.0745 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1573.89 | 0.730113 | 94.8256ms | 1213 | 80 | 2303.8 | 735 | 0 | 1.88631 | 1(Win) | true |
| Glaze | 647.618 | 0.142297 | 210.621ms | 1213 | 320 | 2067.4 | 1786.25 | 0.66925 | 4.6467 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 857.135 | 0.640417 | 5359.83ms | 94653 | 2560 | 1.16449e+09 | 105314 | 0.92474 | 3.54476 | 1(Win) | true |
| Glaze | 804.924 | 0.568791 | 5726.72ms | 94653 | 2560 | 1.04161e+09 | 112145 | 1.63254 | 3.77476 | 2(Loss) | true |
| Jsonifier (two-stage) | 765.139 | 0.75414 | 6019.86ms | 94653 | 2560 | 2.02643e+09 | 117976 | 0.467576 | 3.97111 | 3(Loss) | true |
| simdjson (ondemand) | 681.906 | 0.888456 | 6740.02ms | 94653 | 1280 | 1.77053e+09 | 132376 | 1.82796 | 4.45592 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1386.17 | 0.537794 | 8345.51ms | 94653 | 4890 | 5.99762e+08 | 65120.7 | 0.698981 | 2.19168 | 1(Win) | true |
| Glaze | 1329.35 | 0.57747 | 9235.52ms | 94653 | 640 | 9.84079e+07 | 67904.1 | 1.07262 | 2.28533 | 2(Loss) | true |
| Jsonifier (two-stage) | 1209.51 | 0.481217 | 9336.63ms | 94653 | 2560 | 3.30197e+08 | 74632.1 | 0.747201 | 2.51194 | 3(Loss) | true |
| simdjson (ondemand) | 1064.7 | 0.771479 | 5344.32ms | 94653 | 40 | 1.71128e+07 | 84782.5 | 0.739663 | 2.85377 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11259.5 | 0.352789 | 830.439ms | 94653 | 4890 | 3.91174e+06 | 8017.06 | 0.0846635 | 0.269039 | 1(Win) | true |
| Glaze | 3824.43 | 1.04158 | 2360.31ms | 94653 | 4890 | 2.95547e+08 | 23603 | 0.38889 | 0.793804 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11987.8 | 0.108432 | 811.704ms | 94653 | 40 | 2666.67 | 7530 | 0.578807 | 0.252609 | 1(Win) | true |
| Glaze | 4513.97 | 1.18386 | 2056.73ms | 94653 | 80 | 4.48379e+06 | 19997.5 | 0.755763 | 0.672155 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1062.83 | 0.693614 | 5771.64ms | 124597 | 2560 | 1.53945e+09 | 111801 | 1.23395 | 2.85883 | 1(Win) | true |
| Jsonifier (two-stage) | 956.575 | 1.45346 | 6227.06ms | 124597 | 640 | 2.08623e+09 | 124219 | 1.0657 | 3.17636 | 2(Loss) | true |
| Glaze | 901.495 | 0.696351 | 6656.39ms | 124597 | 2560 | 2.15668e+09 | 131809 | 0.661159 | 3.37041 | 3(Loss) | true |
| simdjson (ondemand) | 827.255 | 0.780189 | 7315.73ms | 124597 | 2560 | 3.21497e+09 | 143638 | 0.821045 | 3.67274 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1640.52 | 0.740851 | 9100.17ms | 124597 | 4890 | 1.40807e+09 | 72431.2 | 1.89576 | 1.85187 | 1(Win) | true |
| Jsonifier (two-stage) | 1450.92 | 0.711234 | 5236.51ms | 124597 | 2560 | 8.68544e+08 | 81896.2 | 0.877251 | 2.09398 | 2(Loss) | true |
| Glaze | 1390.3 | 0.897952 | 5470.9ms | 124597 | 1280 | 7.53899e+08 | 85467 | 0.0360024 | 2.18523 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1281.76 | 0.779436 | 5648.07ms | 124597 | 2560 | 1.3366e+09 | 92704.4 | 2.72942 | 2.37046 | -(Loss) | false |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12735.5 | 0.755608 | 1145.84ms | 136037 | 320 | 1.89594e+06 | 10186.9 | 1.91961 | 0.238128 | 1(Win) | true |
| Glaze | 4449.01 | 0.976759 | 2990.65ms | 136076 | 80 | 6.49382e+06 | 29168.8 | 0.0128546 | 0.682533 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12983.2 | 1.71698 | 1069.81ms | 136037 | 80 | 2.35488e+06 | 9992.5 | 1.03986 | 0.233077 | 1(Win) | true |
| Glaze | 4558.58 | 1.35771 | 2829.15ms | 136076 | 2560 | 3.82437e+08 | 28467.7 | 0.351136 | 0.665733 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 645.825 | 0.743456 | 10022.5ms | 2251027 | 160 | 9.77151e+10 | 3.32404e+06 | 0.982683 | 4.70584 | 1(Win) | true |
| Jsonifier (two-stage) | 611.747 | 0.672942 | 5274.67ms | 2251027 | 80 | 4.46133e+10 | 3.50921e+06 | 0.554125 | 4.96735 | 2(Loss) | true |
| simdjson (ondemand) | 385.659 | 0.940834 | 8421.82ms | 2251027 | 40 | 1.09709e+11 | 5.56644e+06 | 0.868577 | 7.87997 | 3(Loss) | true |
| Glaze | 353.04 | 1.11087 | 9074.35ms | 2251027 | 30 | 1.36886e+11 | 6.08075e+06 | 1.36755 | 8.60853 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 793.753 | 0.541815 | 10082.2ms | 2251027 | 160 | 3.43569e+10 | 2.70455e+06 | 2.01075 | 3.82839 | 1(Win) | true |
| Jsonifier (two-stage) | 733.676 | 0.849765 | 5446.1ms | 2251027 | 40 | 2.47293e+10 | 2.92602e+06 | 0.533415 | 4.1417 | 2(Loss) | true |
| simdjson (ondemand) | 452.454 | 0.78802 | 8044.95ms | 2251027 | 80 | 1.11835e+11 | 4.74467e+06 | 1.5302 | 6.71724 | 3(Loss) | true |
| Glaze | 388.257 | 1.74965 | 9132.25ms | 2251027 | 80 | 7.4871e+11 | 5.52919e+06 | 1.73581 | 7.82799 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1326.57 | 0.629347 | 9400.06ms | 2090326 | 160 | 1.43109e+10 | 1.50274e+06 | 0.159505 | 2.29071 | 1(Win) | true |
| Glaze | 776.45 | 0.620762 | 7901.39ms | 2090234 | 160 | 4.06381e+10 | 2.56733e+06 | 0.288498 | 3.91395 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1673.89 | 1.30575 | 7626.68ms | 2090326 | 30 | 7.25461e+09 | 1.19093e+06 | 0.404958 | 1.81532 | 1(Win) | true |
| Glaze | 1094.2 | 0.414307 | 5824.9ms | 2090234 | 160 | 9.11507e+09 | 1.82179e+06 | 0.0582528 | 2.77733 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 1365.23 | 0.740974 | 5685.63ms | 5373214 | 80 | 6.18808e+10 | 3.75344e+06 | 3.73995 | 2.22579 | -(Win) | false |
| Jsonifier | 1235.71 | 2.26923 | 6051.05ms | 5373214 | 30 | 2.65652e+11 | 4.14684e+06 | 0.0130237 | 2.45934 | 2(Loss) | true |
| simdjson (ondemand) | 962.133 | 0.784106 | 8175.02ms | 5373214 | 30 | 5.23201e+10 | 5.32597e+06 | 0.153635 | 3.15883 | 3(Loss) | true |
| Glaze | 787.166 | 1.03239 | 9708.5ms | 5373214 | 30 | 1.35502e+11 | 6.50981e+06 | 1.97669 | 3.86109 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1657.81 | 0.563219 | 5680.98ms | 5373214 | 80 | 2.42462e+10 | 3.091e+06 | 1.16995 | 1.83321 | 1(Win) | true |
| Jsonifier (two-stage) | 1580.56 | 0.943027 | 5744.46ms | 5373214 | 80 | 7.47799e+10 | 3.24208e+06 | 1.84359 | 1.92277 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1051.18 | 0.993102 | 8068.58ms | 5373214 | 30 | 7.03117e+10 | 4.87483e+06 | 2.6059 | 2.89106 | -(Loss) | false |
| Glaze | 938.088 | 0.697588 | 9373.99ms | 5373214 | 40 | 5.80818e+10 | 5.46249e+06 | 0.42614 | 3.23983 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2694.05 | 1.20747 | 6873.92ms | 6661989 | 80 | 6.48691e+10 | 2.3583e+06 | 4.61086 | 1.12805 | -(Win) | false |
| Glaze | 1319.47 | 0.800082 | 7224.41ms | 6661897 | 30 | 4.45236e+10 | 4.81504e+06 | 2.1593 | 2.30326 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4901.07 | 0.23665 | 8793.43ms | 6661989 | 80 | 7.52886e+08 | 1.29632e+06 | 2.02579 | 0.619967 | 1(Win) | true |
| Glaze | 3095.18 | 0.369796 | 6506.44ms | 6661897 | 160 | 9.21866e+09 | 2.05264e+06 | 0.797796 | 0.981791 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1508.47 | 0.564382 | 8065.34ms | 500299 | 640 | 2.03944e+09 | 316295 | 0.0762825 | 2.01442 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1129.34 | 0.771839 | 5362.22ms | 500299 | 640 | 6.80524e+09 | 422479 | 2.66829 | 2.69042 | -(Loss) | false |
| Glaze | 748.546 | 1.12021 | 7962.27ms | 500299 | 640 | 3.26287e+10 | 637399 | 0.815171 | 4.05961 | 3(Loss) | true |
| simdjson (ondemand) | 551.783 | 1.01645 | 5544.4ms | 500299 | 160 | 1.23599e+10 | 864692 | 0.457024 | 5.50735 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1805.43 | 1.33301 | 7858.95ms | 500299 | 160 | 1.98555e+09 | 264270 | 1.07064 | 1.68309 | 1(Win) | true |
| Jsonifier (two-stage) | 1289.63 | 0.791485 | 5208.89ms | 500299 | 640 | 5.48772e+09 | 369967 | 0.721052 | 2.35599 | 2(Loss) | true |
| Glaze | 901.068 | 2.02342 | 7377.88ms | 500299 | 40 | 4.59173e+09 | 529508 | 0.152102 | 3.37274 | 3(Loss) | true |
| simdjson (ondemand) | 630.748 | 0.575469 | 5089.92ms | 500299 | 320 | 6.06374e+09 | 756438 | 1.78898 | 4.818 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9589.2 | 0.47201 | 5085.6ms | 500299 | 4890 | 2.69716e+08 | 49756.2 | 0.643614 | 0.316736 | 1(Win) | true |
| Glaze | 3846.89 | 1.67704 | 6480.43ms | 500299 | 320 | 1.38444e+09 | 124028 | 0.234777 | 0.789692 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9543.3 | 1.02315 | 4993.65ms | 500299 | 1280 | 3.34929e+08 | 49995.5 | 0.16521 | 0.318274 | 1(Win) | true |
| Glaze | 4203.53 | 0.571834 | 5828.64ms | 500299 | 2560 | 1.07848e+09 | 113505 | 0.785618 | 0.722661 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2660.36 | 0.635488 | 5351.66ms | 1151920 | 80 | 5.50894e+08 | 412935 | 0.635468 | 1.14236 | 1(Win) | true |
| Jsonifier (two-stage) | 2590.99 | 0.553614 | 5389.63ms | 1151920 | 640 | 3.52622e+09 | 423992 | 0.592843 | 1.17279 | 2(Loss) | true |
| Glaze | 1477.27 | 0.625617 | 9379.41ms | 1151920 | 640 | 1.38524e+10 | 743641 | 0.00516856 | 2.05717 | 3(Loss) | true |
| simdjson (ondemand) | 1275.01 | 0.336944 | 5493.75ms | 1151920 | 80 | 6.74257e+08 | 861608 | 0.139469 | 2.38361 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3077.72 | 0.470847 | 5123.24ms | 1151920 | 80 | 2.25963e+08 | 356939 | 0.144424 | 0.987371 | 1(Win) | true |
| Jsonifier | 3046.11 | 0.149571 | 5131.55ms | 1151920 | 640 | 1.86222e+08 | 360643 | 0.0926737 | 0.99768 | 2(Loss) | true |
| Glaze | 1679.94 | 0.350072 | 9094.78ms | 1151920 | 80 | 4.19241e+08 | 653926 | 0.353541 | 1.80914 | 3(Loss) | true |
| simdjson (ondemand) | 1457.03 | 0.161495 | 5031.6ms | 1151920 | 160 | 2.37217e+08 | 753968 | 0.6933 | 2.08583 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3932.23 | 0.829368 | 8805.32ms | 1439562 | 640 | 5.36609e+09 | 349134 | 1.07104 | 0.772279 | 1(Win) | true |
| Glaze | 1749.79 | 0.793834 | 5036.11ms | 1439584 | 320 | 1.2414e+10 | 784606 | 2.14996 | 1.73627 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12371.9 | 0.812565 | 5677.4ms | 1439562 | 1280 | 1.04067e+09 | 110967 | 0.535147 | 0.245409 | 1(Win) | true |
| Glaze | 6518.16 | 0.802977 | 5346.98ms | 1439584 | 640 | 1.83067e+09 | 210626 | 0.230328 | 0.466035 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1260.49 | 0.696722 | 4275.82ms | 56369 | 4890 | 4.31748e+08 | 42648.2 | 0.140834 | 2.40959 | 1(Win) | true |
| Glaze | 1076.53 | 0.562014 | 5017.54ms | 56369 | 4890 | 3.85152e+08 | 49936.1 | 0.433316 | 2.8214 | 2(Loss) | true |
| Jsonifier (two-stage) | 1012.36 | 0.685792 | 5414.69ms | 56369 | 80 | 1.06092e+07 | 53101.2 | 0.115213 | 3.00091 | 3(Loss) | true |
| simdjson (ondemand) | 768.104 | 0.495193 | 7292.81ms | 56369 | 160 | 1.92181e+07 | 69987.5 | 0.0553364 | 3.95535 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2113.67 | 0.717194 | 3223.33ms | 56369 | 30 | 998161 | 25433.3 | 0.508541 | 1.43624 | 1(Win) | true |
| Glaze | 1770.55 | 0.801899 | 3559.81ms | 56369 | 4890 | 2.89876e+08 | 30362.1 | 0.103407 | 1.71513 | 2(Loss) | true |
| Jsonifier (two-stage) | 1445.84 | 0.266251 | 4211.98ms | 56369 | 4890 | 4.79219e+07 | 37181 | 0.283064 | 2.1005 | 3(Loss) | true |
| simdjson (ondemand) | 1010.1 | 0.501833 | 5952.9ms | 56369 | 320 | 2.28254e+07 | 53220 | 0.395368 | 3.00737 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10645.1 | 0.183857 | 537.401ms | 56369 | 30 | 2586.21 | 5050 | 0 | 0.284125 | 1(Win) | true |
| Glaze | 4112.22 | 0.587323 | 1361.38ms | 56369 | 640 | 3.77279e+06 | 13072.7 | 0.521973 | 0.737411 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10973.1 | 0.739414 | 514.498ms | 56369 | 320 | 419905 | 4899.06 | 0.791039 | 0.275001 | 1(Win) | true |
| Glaze | 4321.34 | 1.32202 | 1223.33ms | 56369 | 2560 | 6.92402e+07 | 12440 | 0.701248 | 0.700612 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1680.94 | 0.834807 | 5083.22ms | 83958 | 30 | 4.74368e+06 | 47633.3 | 0.0630208 | 1.80759 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1452.62 | 0.910992 | 5926.1ms | 83958 | 40 | 1.00857e+07 | 55120 | 1.0176 | 2.09118 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1446.15 | 0.354664 | 5906.59ms | 83958 | 30 | 1.15678e+06 | 55366.7 | 0.060241 | 2.10025 | 2(Tie) | true |
| simdjson (ondemand) | 996.034 | 1.02349 | 7967.4ms | 83958 | 2560 | 1.73295e+09 | 80387.4 | 1.02214 | 3.04992 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2397.63 | 1.84749 | 3966.91ms | 83958 | 640 | 2.43615e+08 | 33394.8 | 1.46925 | 1.26651 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2129.48 | 1.97235 | 4563.38ms | 83958 | 30 | 1.64993e+07 | 37600 | 0.0797236 | 1.42621 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2055.21 | 0.929129 | 4786.48ms | 83958 | 80 | 1.04822e+07 | 38958.8 | 0.393097 | 1.47776 | 2(Tie) | true |
| simdjson (ondemand) | 1357.41 | 0.65823 | 6468.43ms | 83958 | 4890 | 7.37168e+08 | 58986.3 | 0.859363 | 2.2375 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10664.4 | 1.7571 | 854.305ms | 94370 | 4890 | 1.07522e+08 | 8439.14 | 0.885884 | 0.284228 | 1(Win) | true |
| Glaze | 3396.28 | 2.24118 | 2609.93ms | 94370 | 640 | 2.25733e+08 | 26499.1 | 0.131906 | 0.893568 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12253 | 0.11891 | 815.77ms | 94370 | 40 | 3051.28 | 7345 | 0.34153 | 0.246643 | 1(Win) | true |
| Glaze | 3992.51 | 2.10447 | 2272.58ms | 94370 | 1280 | 2.88052e+08 | 22541.8 | 0.398702 | 0.759752 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 947.805 | 1.26351 | 5288.2ms | 53331 | 2560 | 1.17685e+09 | 53661.2 | 0.209358 | 3.2046 | 1(Win) | true |
| Glaze | 890.469 | 0.883151 | 5677.07ms | 53331 | 4890 | 1.24423e+09 | 57116.4 | 0.499437 | 3.41102 | 2(Loss) | true |
| Jsonifier (two-stage) | 867.888 | 0.638488 | 5861.83ms | 53331 | 4890 | 6.84615e+08 | 58602.5 | 0.292936 | 3.49857 | 3(Loss) | true |
| simdjson (ondemand) | 675.637 | 0.773778 | 7508.46ms | 53331 | 2560 | 8.68572e+08 | 75277.7 | 0.256219 | 4.49647 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1700.25 | 0.219693 | 3987.71ms | 53331 | 640 | 2.76404e+06 | 29913.4 | 0.34356 | 1.78599 | 1(Win) | true |
| Glaze | 1551.21 | 0.979822 | 4451.6ms | 53331 | 40 | 4.1283e+06 | 32787.5 | 0.432736 | 1.95794 | 2(Loss) | true |
| Jsonifier (two-stage) | 1298.89 | 1.50928 | 4693.97ms | 53331 | 1280 | 4.47065e+08 | 39157 | 0.260885 | 2.33831 | 3(Loss) | true |
| simdjson (ondemand) | 914.77 | 0.818412 | 6222.94ms | 53331 | 2560 | 5.30055e+08 | 55599.1 | 0.0840985 | 3.32075 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10542.7 | 3.38876 | 530.433ms | 58581 | 2560 | 8.25527e+07 | 5299.14 | 0 | 0.286884 | 1(Win) | true |
| Glaze | 5177.68 | 0.426 | 1159.98ms | 58581 | 40 | 84512.8 | 10790 | 0.652985 | 0.585334 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12575.6 | 0.178184 | 470.308ms | 58581 | 40 | 2506.41 | 4442.5 | 0.965909 | 0.238961 | 1(Win) | true |
| Glaze | 5760.36 | 1.49445 | 990.421ms | 58581 | 2560 | 5.37797e+07 | 9698.55 | 0.200577 | 0.524947 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.015 | 0.918997 | 6371.28ms | 65103 | 4890 | 1.67119e+09 | 63612.8 | 1.16136 | 3.11207 | 1(Win) | true |
| Glaze STATISTICAL TIE | 921.13 | 1.87798 | 6899.67ms | 65103 | 640 | 1.02547e+09 | 67403.1 | 0.00510017 | 3.29733 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 904.787 | 0.878186 | 6797.08ms | 65103 | 4890 | 1.77579e+09 | 68620.7 | 0.607114 | 3.35736 | 2(Tie) | true |
| simdjson (ondemand) | 652.018 | 0.963781 | 9464.32ms | 65103 | 2560 | 2.15616e+09 | 95223 | 0.76388 | 4.65941 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1663.66 | 0.730196 | 4590.33ms | 65103 | 4890 | 3.6313e+08 | 37319.6 | 0.244845 | 1.82524 | 1(Win) | true |
| Glaze | 1601.17 | 1.42014 | 4656.09ms | 65103 | 1280 | 3.88151e+08 | 38776 | 0.04132 | 1.89666 | 2(Loss) | true |
| Jsonifier (two-stage) | 1476.85 | 0.771863 | 5011.06ms | 65103 | 4890 | 5.14896e+08 | 42040.2 | 0.35454 | 2.05656 | 3(Loss) | true |
| simdjson (ondemand) | 1168.68 | 0.176923 | 6012.85ms | 65103 | 4890 | 4.32006e+07 | 53126 | 0.100715 | 2.59926 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11088.1 | 1.05265 | 712.128ms | 78778 | 160 | 813930 | 6775.62 | 0.0829493 | 0.272983 | 1(Win) | true |
| Glaze | 2988.12 | 1.21074 | 2364.96ms | 78778 | 2560 | 2.37221e+08 | 25142.4 | 0.559317 | 1.01604 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11862.4 | 0.138217 | 702.327ms | 78778 | 30 | 2298.85 | 6333.33 | 0.849257 | 0.255109 | 1(Win) | true |
| Glaze | 3475.23 | 0.704683 | 2144.37ms | 78778 | 4890 | 1.13485e+08 | 21618.3 | 1.43178 | 0.872494 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1229.45 | 2.15914 | 984.831ms | 11812 | 40 | 1.56548e+06 | 9162.5 | 0.190632 | 2.46606 | 1(Win) | true |
| Jsonifier (two-stage) | 1009.86 | 0.806487 | 1112.69ms | 11812 | 4890 | 3.95753e+07 | 11154.8 | 1.0417 | 3.00284 | 2(Loss) | true |
| Glaze | 925.525 | 1.16919 | 1275.06ms | 11812 | 80 | 1.62005e+06 | 12171.2 | 1.59641 | 3.27786 | 3(Loss) | true |
| simdjson (ondemand) | 571.029 | 0.929345 | 2005.26ms | 11812 | 2560 | 8.60448e+07 | 19727.2 | 0.396005 | 5.31603 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1433.29 | 0.905079 | 1000.17ms | 11812 | 160 | 809597 | 7859.38 | 2.47402 | 2.11543 | 1(Win) | true |
| Jsonifier (two-stage) | 1233.48 | 0.172633 | 1095.99ms | 11812 | 40 | 9942.31 | 9132.5 | 0.445131 | 2.46084 | 2(Loss) | true |
| Glaze | 1129.02 | 0.467197 | 1204.61ms | 11812 | 40 | 86916.7 | 9977.5 | 0.2428 | 2.68498 | 3(Loss) | true |
| simdjson (ondemand) | 610.595 | 1.25988 | 1928.44ms | 11812 | 4890 | 2.64185e+08 | 18448.9 | 2.42518 | 4.97081 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9711.04 | 0.522309 | 133.294ms | 11812 | 80 | 2936.71 | 1160 | 1.2766 | 0.307179 | 1(Win) | true |
| Glaze | 3220.82 | 0.239818 | 357.971ms | 11812 | 40 | 2814.1 | 3497.5 | 0.166508 | 0.933932 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10258.2 | 0.205409 | 118.598ms | 11812 | 160 | 814.072 | 1098.12 | 1.56069 | 0.289678 | 1(Win) | true |
| Glaze | 3700.82 | 0.561107 | 315.478ms | 11812 | 2560 | 746762 | 3043.87 | 0.805951 | 0.810859 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2287.11 | 0.520221 | 1099.96ms | 25388 | 320 | 970531 | 10586.2 | 0.0118064 | 1.32717 | 1(Win) | true |
| Jsonifier (two-stage) | 2183.06 | 0.0504032 | 1114.21ms | 25388 | 4890 | 152810 | 11090.8 | 0.045971 | 1.38883 | 2(Loss) | true |
| Glaze | 1466.22 | 0.206015 | 1671.57ms | 25388 | 160 | 185173 | 16513.1 | 0.147392 | 2.07014 | 3(Loss) | true |
| simdjson (ondemand) | 1239.74 | 0.14276 | 1977.85ms | 25388 | 640 | 497496 | 19529.8 | 0.0744608 | 2.4493 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2579.39 | 1.0045 | 1124.51ms | 25388 | 30 | 266713 | 9386.67 | 0.635145 | 1.17463 | 1(Win) | true |
| Jsonifier (two-stage) | 2401.97 | 1.06678 | 1158.18ms | 25388 | 320 | 3.70016e+06 | 10080 | 0.167131 | 1.26251 | 2(Loss) | true |
| Glaze | 1599.25 | 0.997131 | 1658.94ms | 25388 | 4890 | 1.11439e+08 | 15139.5 | 1.05716 | 1.89682 | 3(Loss) | true |
| simdjson (ondemand) | 1359.69 | 0.877236 | 2015.59ms | 25388 | 160 | 3.90417e+06 | 17806.9 | 0.845688 | 2.23174 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14321.2 | 0.483524 | 230.52ms | 31235 | 30 | 3034.48 | 2080 | 0.636943 | 0.209941 | 1(Win) | true |
| Glaze | 5180.21 | 0.447044 | 601.227ms | 31235 | 4890 | 3.23146e+06 | 5750.35 | 0.488806 | 0.584159 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 15641.9 | 0.199427 | 212.834ms | 31235 | 160 | 2307.78 | 1904.38 | 2.65176 | 0.190498 | -(Win) | false |
| Glaze | 5625.74 | 1.98348 | 537.104ms | 31235 | 4890 | 5.39374e+07 | 5294.95 | 2.3607 | 0.535854 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2023.99 | 0.558904 | 5257.25ms | 108313 | 640 | 5.20713e+07 | 51035.5 | 3.49784 | 1.50083 | -(Win) | false |
| Jsonifier (two-stage) STATISTICAL TIE | 1375.22 | 0.690822 | 7553.48ms | 108313 | 2560 | 6.89272e+08 | 75112 | 0.195507 | 2.20911 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1368.15 | 0.801311 | 7827.82ms | 108313 | 40 | 1.46405e+07 | 75500 | 0.365108 | 2.22109 | 2(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 857.36 | 0.597412 | 6060.39ms | 108313 | 2560 | 1.32624e+09 | 120481 | 2.75479 | 3.54376 | -(Loss) | false |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2518.79 | 0.547278 | 4438.64ms | 108313 | 2560 | 1.28953e+08 | 41009.8 | 0.0716805 | 1.20579 | 1(Win) | true |
| Glaze | 1719.01 | 0.302838 | 6465.25ms | 108313 | 640 | 2.11937e+07 | 60090.2 | 0.0418467 | 1.76729 | 2(Loss) | true |
| Jsonifier (two-stage) | 1578.55 | 1.84387 | 6754.28ms | 108313 | 640 | 9.31719e+08 | 65436.7 | 0.344309 | 1.92451 | 3(Loss) | true |
| simdjson (ondemand) | 959.306 | 0.474807 | 5654.54ms | 108313 | 2560 | 6.69146e+08 | 107677 | 0.0966946 | 3.1671 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14948.7 | 0.162214 | 742.847ms | 108313 | 40 | 5025.64 | 6910 | 0.290276 | 0.202458 | 1(Win) | true |
| Glaze | 3776.06 | 0.680889 | 2742.25ms | 108313 | 4890 | 1.69646e+08 | 27355.3 | 0.830324 | 0.804027 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15280.4 | 0.23092 | 706.036ms | 108313 | 30 | 7310.34 | 6760 | 0.346363 | 0.19821 | 1(Win) | true |
| Glaze | 4549.05 | 1.06778 | 2287.28ms | 108313 | 1280 | 7.52477e+07 | 22707 | 0.0825054 | 0.666912 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2573.76 | 0.537746 | 6773.72ms | 183677 | 1280 | 1.7145e+08 | 68059.1 | 0.142252 | 1.18034 | 1(Win) | true |
| Jsonifier (two-stage) | 2272.15 | 0.747822 | 7782.21ms | 183677 | 1280 | 4.25445e+08 | 77093.6 | 0.509151 | 1.33706 | 2(Loss) | true |
| Glaze | 1721.94 | 2.01664 | 5284.67ms | 183677 | 160 | 6.73364e+08 | 101727 | 0.134733 | 1.76465 | 3(Loss) | true |
| simdjson (ondemand) | 1455.63 | 0.353394 | 6232.32ms | 183677 | 1280 | 2.31494e+08 | 120339 | 0.29523 | 2.08737 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3069.98 | 1.62332 | 5967.59ms | 183677 | 640 | 5.49072e+08 | 57058.4 | 0.504761 | 0.989487 | 1(Win) | true |
| Jsonifier (two-stage) | 2636.57 | 0.614217 | 6890.62ms | 183677 | 2560 | 4.26301e+08 | 66438 | 0.0538276 | 1.15219 | 2(Loss) | true |
| Glaze | 2136.85 | 0.354142 | 8813.18ms | 183677 | 40 | 3.37115e+06 | 81975 | 0.00203318 | 1.42192 | 3(Loss) | true |
| simdjson (ondemand) | 1658.22 | 0.255818 | 5674.8ms | 183677 | 160 | 1.16845e+07 | 105636 | 2.03672 | 1.83246 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13864.5 | 1.07424 | 1580.04ms | 213963 | 80 | 1.99969e+06 | 14717.5 | 0.289608 | 0.218816 | 1(Win) | true |
| Glaze | 4182.27 | 0.263472 | 4977.17ms | 213963 | 2560 | 4.2302e+07 | 48789.5 | 0.93339 | 0.726362 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14583.5 | 0.266542 | 1447.33ms | 213963 | 320 | 445075 | 13991.9 | 0.0268085 | 0.207844 | 1(Win) | true |
| Glaze | 4756.87 | 0.461804 | 4328.56ms | 213963 | 2560 | 1.00459e+08 | 42896.1 | 1.62857 | 0.638342 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 672.489 | 0.468856 | 8237.18ms | 1834197 | 80 | 1.18985e+10 | 2.60112e+06 | 0.112289 | 4.51916 | 1(Win) | true |
| Jsonifier (two-stage) | 553.621 | 0.366572 | 10011.1ms | 1834197 | 160 | 2.14637e+10 | 3.15961e+06 | 0.952704 | 5.48945 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 308.212 | 0.867358 | 8570.28ms | 1834197 | 40 | 9.69282e+10 | 5.6754e+06 | 3.33938 | 9.86115 | -(Loss) | false |
| simdjson (ondemand) | 202.753 | 0.491512 | 6063.08ms | 1834197 | 40 | 7.19261e+10 | 8.62738e+06 | 0.170098 | 14.9906 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 756.689 | 0.609418 | 8149.79ms | 1834197 | 80 | 1.58773e+10 | 2.31169e+06 | 0.420481 | 4.01629 | 1(Win) | true |
| Jsonifier (two-stage) | 617.509 | 0.586645 | 9741.25ms | 1834197 | 40 | 1.10463e+10 | 2.83271e+06 | 0.0442548 | 4.92161 | 2(Loss) | true |
| Glaze | 332.106 | 0.377542 | 8480.98ms | 1834197 | 80 | 3.16343e+10 | 5.26707e+06 | 0.929397 | 9.15166 | 3(Loss) | true |
| simdjson (ondemand) | 212.91 | 0.155539 | 6046.5ms | 1834197 | 30 | 4.89893e+09 | 8.21582e+06 | 0.408871 | 14.2755 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 990.695 | 0.94534 | 5748.58ms | 1922245 | 30 | 9.17983e+09 | 1.85041e+06 | 0.629565 | 3.06748 | 1(Win) | true |
| Glaze | 664.815 | 0.273079 | 8418.26ms | 1833577 | 40 | 2.06364e+09 | 2.63026e+06 | 0.556671 | 4.57139 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1154.65 | 0.673445 | 10050ms | 1922245 | 160 | 1.82911e+10 | 1.58766e+06 | 1.29631 | 2.6318 | 1(Win) | true |
| Glaze | 677.731 | 0.899394 | 7808.72ms | 1833577 | 80 | 4.30798e+10 | 2.58013e+06 | 0.838982 | 4.48418 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 1992.34 | 1.3097 | 5318.14ms | 7351818 | 40 | 8.497e+10 | 3.5191e+06 | 6.41833 | 1.52528 | -(Win) | false |
| Jsonifier DID NOT CONVERGE | 1868.58 | 1.50687 | 5388.35ms | 7351818 | 40 | 1.27873e+11 | 3.75217e+06 | 3.29945 | 1.62644 | -(Loss) | false |
| Glaze | 1107.59 | 0.308788 | 9582.15ms | 7351818 | 80 | 3.05664e+10 | 6.33019e+06 | 0.7101 | 2.7441 | 3(Loss) | true |
| simdjson (ondemand) | 681.193 | 0.733406 | 7246.11ms | 7351818 | 30 | 1.70946e+11 | 1.02926e+07 | 1.12292 | 4.46178 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2315.33 | 0.213098 | 5374.44ms | 7351818 | 40 | 1.66565e+09 | 3.02819e+06 | 0.786728 | 1.31261 | 1(Win) | true |
| Jsonifier | 2194.9 | 0.803002 | 5454.42ms | 7351818 | 40 | 2.63181e+10 | 3.19434e+06 | 0.155228 | 1.38465 | 2(Loss) | true |
| Glaze | 1144.56 | 0.488874 | 9594.85ms | 7351818 | 80 | 7.17456e+10 | 6.1257e+06 | 0.958591 | 2.65533 | 3(Loss) | true |
| simdjson (ondemand) | 728.536 | 0.280942 | 7425.1ms | 7351818 | 30 | 2.19302e+10 | 9.62374e+06 | 2.122 | 4.17193 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2996.63 | 0.120218 | 9941.08ms | 10018896 | 160 | 2.35089e+09 | 3.1885e+06 | 0.281171 | 1.0142 | 1(Win) | true |
| Glaze | 1670.32 | 0.838086 | 8528.76ms | 9930228 | 40 | 9.03144e+10 | 5.6697e+06 | 1.83713 | 1.81956 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4788.29 | 0.171101 | 6246.69ms | 10018896 | 80 | 9.32551e+08 | 1.99544e+06 | 0.0382266 | 0.63464 | 1(Win) | true |
| Glaze | 3277.29 | 0.230277 | 9056.07ms | 9930228 | 80 | 3.54227e+09 | 2.88964e+06 | 0.171508 | 0.927255 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 667.88 | 0.961334 | 8278.98ms | 1834197 | 80 | 5.07146e+10 | 2.61907e+06 | 1.17924 | 4.55031 | 1(Win) | true |
| Jsonifier (two-stage) | 522.747 | 1.48468 | 10067.3ms | 1834197 | 30 | 7.40452e+10 | 3.34622e+06 | 1.56382 | 5.81374 | 2(Loss) | true |
| simdjson (ondemand) | 356.83 | 0.87905 | 7285.06ms | 1834197 | 30 | 5.5708e+10 | 4.90213e+06 | 2.42089 | 8.51683 | 3(Loss) | true |
| Glaze | 304.668 | 0.637188 | 8694.36ms | 1834197 | 80 | 1.07069e+11 | 5.74143e+06 | 0.458622 | 9.97586 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 743.055 | 1.53651 | 8283.45ms | 1834197 | 30 | 3.925e+10 | 2.3541e+06 | 0.207574 | 4.08995 | 1(Win) | true |
| Jsonifier (two-stage) | 586.751 | 1.49752 | 9761.74ms | 1834197 | 30 | 5.9793e+10 | 2.98121e+06 | 1.51519 | 5.17934 | 2(Loss) | true |
| simdjson (ondemand) | 373.165 | 0.570077 | 7516.19ms | 1834197 | 40 | 2.85639e+10 | 4.68754e+06 | 0.534858 | 8.14425 | 3(Loss) | true |
| Glaze | 327.319 | 0.718511 | 8724.81ms | 1834197 | 40 | 5.89762e+10 | 5.34411e+06 | 1.25351 | 9.28545 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 952.988 | 1.60149 | 5736.51ms | 1922245 | 40 | 3.79623e+10 | 1.92363e+06 | 0.345886 | 3.18887 | 1(Win) | true |
| Glaze | 574.971 | 0.328154 | 9565.67ms | 1833577 | 160 | 1.59361e+10 | 3.04126e+06 | 0.445865 | 5.28578 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1206.11 | 0.39328 | 10118.4ms | 1922245 | 40 | 1.42925e+09 | 1.51993e+06 | 0.488361 | 2.51949 | 1(Win) | true |
| Glaze | 731.349 | 0.315485 | 7669.53ms | 1833577 | 30 | 1.70698e+09 | 2.39097e+06 | 2.00916 | 4.15553 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2021.12 | 0.947816 | 5278.31ms | 7351818 | 80 | 8.64858e+10 | 3.46899e+06 | 1.61545 | 1.5037 | 1(Win) | true |
| Jsonifier | 1954.53 | 1.17226 | 5467.73ms | 7351818 | 40 | 7.07312e+10 | 3.58718e+06 | 2.35395 | 1.55493 | 2(Loss) | true |
| simdjson (ondemand) | 1353.62 | 0.365263 | 7897.59ms | 7351818 | 80 | 2.86351e+10 | 5.17963e+06 | 0.590311 | 2.2453 | 3(Loss) | true |
| Glaze | 1105.17 | 0.504686 | 9797.97ms | 7351818 | 40 | 4.10049e+10 | 6.34405e+06 | 0.668526 | 2.75003 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2268.21 | 0.796822 | 5119.87ms | 7351818 | 80 | 4.8533e+10 | 3.09109e+06 | 1.16594 | 1.33985 | 1(Win) | true |
| Jsonifier | 2120.91 | 0.79049 | 5451.86ms | 7351818 | 40 | 2.73147e+10 | 3.30576e+06 | 1.75344 | 1.43294 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1439.68 | 0.384436 | 8025.18ms | 7351818 | 40 | 1.40205e+10 | 4.86999e+06 | 4.52417 | 2.11104 | -(Loss) | false |
| Glaze | 1110.19 | 0.66826 | 9956.83ms | 7351818 | 80 | 1.42488e+11 | 6.31538e+06 | 0.666207 | 2.73764 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2972.74 | 0.951159 | 5039.21ms | 10018896 | 30 | 2.80384e+10 | 3.21413e+06 | 3.12807 | 1.02235 | -(Win) | false |
| Glaze | 1204.76 | 0.971549 | 5522.56ms | 9930228 | 40 | 2.33295e+11 | 7.86064e+06 | 0.143019 | 2.52276 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4492.35 | 0.796689 | 6571.37ms | 10018896 | 160 | 4.594e+10 | 2.1269e+06 | 0.836427 | 0.676442 | 1(Win) | true |
| Glaze | 3205.1 | 1.18523 | 9275.97ms | 9930228 | 30 | 3.67929e+10 | 2.95473e+06 | 1.73447 | 0.948203 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 881.751 | 0.417545 | 6359.85ms | 461466 | 640 | 2.77955e+09 | 499107 | 2.51861 | 3.44635 | -(Win) | false |
| Jsonifier (two-stage) | 723.746 | 0.590517 | 7920.18ms | 461466 | 80 | 1.03148e+09 | 608070 | 0.400814 | 4.19869 | 2(Loss) | true |
| Glaze | 706.041 | 0.2498 | 8000.67ms | 461466 | 640 | 1.55162e+09 | 623318 | 0.0715164 | 4.30438 | 3(Loss) | true |
| simdjson (ondemand) | 570.353 | 0.487653 | 5108.25ms | 461466 | 80 | 1.13267e+09 | 771606 | 0.507548 | 5.3281 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1334.3 | 0.814313 | 5348.4ms | 461466 | 30 | 2.16409e+08 | 329827 | 1.28567 | 2.27758 | 1(Win) | true |
| Glaze STATISTICAL TIE | 959.807 | 0.152961 | 7240.13ms | 461466 | 40 | 1.96758e+07 | 458518 | 0.307834 | 3.16648 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 952.103 | 0.52272 | 6972.49ms | 461466 | 320 | 1.8681e+09 | 462228 | 0.679099 | 3.19172 | 2(Tie) | true |
| simdjson (ondemand) | 698.675 | 1.06569 | 9091.8ms | 461466 | 160 | 7.20957e+09 | 629890 | 0.314144 | 4.34938 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3626.94 | 1.42659 | 6239.6ms | 461466 | 80 | 2.3971e+08 | 121339 | 0.265457 | 0.837071 | 1(Win) | true |
| Glaze | 2861.85 | 0.454531 | 7839.73ms | 461466 | 2560 | 1.2507e+09 | 153778 | 0.18175 | 1.06162 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10478.1 | 0.235777 | 4237.35ms | 461466 | 2560 | 2.51048e+07 | 42000.7 | 0.25567 | 0.289758 | 1(Win) | true |
| Glaze | 3269.68 | 0.515274 | 7340.26ms | 461466 | 30 | 1.443e+07 | 134597 | 1.03338 | 0.929302 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1268.03 | 0.308078 | 7100.7ms | 728486 | 320 | 9.11704e+08 | 547888 | 0.124471 | 2.3965 | 1(Win) | true |
| Jsonifier (two-stage) | 1083.93 | 0.369561 | 8352.03ms | 728486 | 640 | 3.59081e+09 | 640943 | 0.015263 | 2.80351 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 882.99 | 1.23896 | 9230.83ms | 728486 | 160 | 1.52042e+10 | 786802 | 0.409711 | 3.44133 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 874.674 | 0.166209 | 5035.91ms | 728486 | 320 | 5.57711e+08 | 794282 | 0.222269 | 3.47444 | 3(Tie) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1807.36 | 0.899012 | 6187.12ms | 728486 | 30 | 3.58265e+08 | 384393 | 0.304433 | 1.68148 | 1(Win) | true |
| Jsonifier (two-stage) | 1508.18 | 0.343179 | 7146.09ms | 728486 | 80 | 1.99926e+08 | 460648 | 0.666861 | 2.01495 | 2(Loss) | true |
| Glaze | 1257.54 | 0.205915 | 8109.44ms | 728486 | 640 | 8.28239e+08 | 552459 | 0.221471 | 2.41669 | 3(Loss) | true |
| simdjson (ondemand) | 1088.07 | 0.220741 | 9259.4ms | 728486 | 640 | 1.27139e+09 | 638508 | 0.127755 | 2.79278 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3821.23 | 0.674684 | 5252.45ms | 837491 | 1280 | 2.54545e+09 | 209015 | 0.327 | 0.794659 | 1(Win) | true |
| Glaze | 2011.16 | 2.07584 | 9619.34ms | 837491 | 80 | 5.43681e+09 | 397130 | 0.259403 | 1.51003 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12977.9 | 0.225098 | 6650.14ms | 837491 | 40 | 767635 | 61542.5 | 1.65788 | 0.233985 | 1(Win) | true |
| Glaze | 4377.18 | 0.220167 | 9775.4ms | 837491 | 1280 | 2.06579e+08 | 182467 | 0.678323 | 0.694119 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6763.97 | 0.694744 | 6950.65ms | 466906 | 160 | 3.34677e+07 | 65830.6 | 1.5415 | 0.449139 | 1(Win) | true |
| Jsonifier (two-stage) | 6245.33 | 0.969838 | 7020.07ms | 466906 | 1280 | 6.12008e+08 | 71297.5 | 0.610966 | 0.486409 | 2(Loss) | true |
| simdjson (ondemand) | 3968.63 | 1.04956 | 5596.65ms | 466906 | 640 | 8.87509e+08 | 112199 | 0.103997 | 0.765603 | 3(Loss) | true |
| Glaze | 2769.46 | 0.431009 | 8272.66ms | 466906 | 2560 | 1.22937e+09 | 160781 | 1.21888 | 1.09723 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7091.09 | 0.149755 | 6524.4ms | 466906 | 80 | 707429 | 62793.8 | 0.11731 | 0.428411 | 1(Win) | true |
| Jsonifier | 7031.64 | 0.112252 | 6509.43ms | 466906 | 640 | 3.23382e+06 | 63324.7 | 0.0813593 | 0.43206 | 2(Loss) | true |
| simdjson (ondemand) | 4467.28 | 0.107393 | 5277.37ms | 466906 | 40 | 458333 | 99675 | 0.407978 | 0.680203 | 3(Loss) | true |
| Glaze | 2979.19 | 0.148651 | 7777.42ms | 466906 | 2560 | 1.26367e+08 | 149462 | 1.16768 | 1.02 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7946.97 | 0.0518247 | 7655.15ms | 631514 | 1280 | 1.97445e+06 | 75784.7 | 0.121172 | 0.382332 | 1(Win) | true |
| Jsonifier (two-stage) | 7908.55 | 0.186609 | 7667.58ms | 631514 | 4890 | 9.87522e+07 | 76152.9 | 0.316597 | 0.384179 | 2(Loss) | true |
| simdjson (ondemand) | 5195.44 | 0.0979831 | 5959.04ms | 631514 | 160 | 2.06416e+06 | 115921 | 0.0231786 | 0.584862 | 3(Loss) | true |
| Glaze | 3597.74 | 0.219208 | 8685.57ms | 631514 | 2560 | 3.44714e+08 | 167399 | 1.10838 | 0.844673 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 8235.95 | 0.187117 | 7615.49ms | 631514 | 160 | 2.99563e+06 | 73125.6 | 0.725462 | 0.368924 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 8228.14 | 0.134786 | 7540.32ms | 631514 | 320 | 3.11458e+06 | 73195 | 0.0495007 | 0.369266 | 1(Tie) | true |
| simdjson (ondemand) | 5320.2 | 0.342018 | 5813.68ms | 631514 | 2560 | 3.8375e+08 | 113202 | 0.193647 | 0.571143 | 3(Loss) | true |
| Glaze | 3750.46 | 0.277835 | 8444.13ms | 631514 | 80 | 1.59242e+07 | 160582 | 0.147681 | 0.810255 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1389.52 | 0.803214 | 8433.2ms | 466906 | 160 | 1.06001e+09 | 320452 | 0.0931407 | 2.18682 | 1(Win) | true |
| Glaze | 1111.47 | 1.32136 | 10082.6ms | 466906 | 160 | 4.48356e+09 | 400618 | 2.0636 | 2.73385 | 2(Loss) | true |
| Jsonifier (two-stage) | 1056.57 | 0.882506 | 5545.8ms | 466906 | 160 | 2.2132e+09 | 421437 | 0.389549 | 2.87596 | 3(Loss) | true |
| simdjson (ondemand) | 885.983 | 0.463466 | 6361.77ms | 466906 | 640 | 3.47236e+09 | 502579 | 0.669712 | 3.42886 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2221.27 | 0.31141 | 6198.3ms | 466906 | 160 | 6.2351e+07 | 200461 | 0.0477254 | 1.36814 | 1(Win) | true |
| Glaze | 1611.5 | 0.558569 | 8047.3ms | 466906 | 1280 | 3.04904e+09 | 276312 | 0.225201 | 1.88566 | 2(Loss) | true |
| Jsonifier (two-stage) | 1531.8 | 0.265187 | 8837.59ms | 466906 | 160 | 9.5078e+07 | 290688 | 1.08485 | 1.98386 | 3(Loss) | true |
| simdjson (ondemand) | 1190.01 | 0.718063 | 5165.27ms | 466906 | 320 | 2.31011e+09 | 374179 | 0.924304 | 2.55336 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 5330.24 | 0.216038 | 8665.97ms | 475954 | 4890 | 1.65503e+08 | 85156.5 | 0.0687627 | 0.570029 | 1(Win) | true |
| Jsonifier | 4212.48 | 0.123962 | 5465.26ms | 475954 | 2560 | 4.56744e+07 | 107752 | 1.12402 | 0.720789 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15185.4 | 0.310498 | 3065.34ms | 475954 | 1280 | 1.10257e+07 | 29890.9 | 0.224757 | 0.199867 | 1(Win) | true |
| Glaze | 5902.37 | 0.460406 | 8253.77ms | 475954 | 1280 | 1.60461e+08 | 76902.2 | 2.10636 | 0.514734 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1536.02 | 0.994396 | 5169.64ms | 631514 | 160 | 2.43225e+09 | 392089 | 0.233751 | 1.97826 | 1(Win) | true |
| Glaze | 1399.83 | 0.498086 | 5619.65ms | 631514 | 320 | 1.46951e+09 | 430236 | 0.0462896 | 2.17087 | 2(Loss) | true |
| Jsonifier (two-stage) | 1348.22 | 0.610908 | 5681.99ms | 631514 | 640 | 4.76622e+09 | 446705 | 0.82857 | 2.25368 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1138.73 | 0.617828 | 6731.68ms | 631514 | 640 | 6.83344e+09 | 528886 | 4.0114 | 2.66838 | -(Loss) | false |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2175.86 | 0.461529 | 8041.09ms | 631514 | 1280 | 2.08886e+09 | 276791 | 0.173123 | 1.3966 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1915.05 | 0.548125 | 9106.91ms | 631514 | 640 | 1.90172e+09 | 314488 | 0.55028 | 1.58674 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1903.15 | 1.15228 | 9514.36ms | 631514 | 320 | 4.25486e+09 | 316453 | 2.28206 | 1.59684 | 2(Tie) | true |
| simdjson (ondemand) | 1589.52 | 0.290921 | 5315.99ms | 631514 | 640 | 7.77615e+08 | 378893 | 0.936557 | 1.91192 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4222.04 | 0.695472 | 8673.68ms | 716365 | 40 | 5.06575e+07 | 161812 | 1.36191 | 0.719273 | 1(Win) | true |
| Glaze | 1785.51 | 0.185019 | 9804.37ms | 716365 | 1280 | 6.41482e+08 | 382624 | 0.148424 | 1.70105 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13027.1 | 0.771947 | 5151.66ms | 716365 | 2560 | 4.19554e+08 | 52442.9 | 0.19374 | 0.232881 | 1(Win) | true |
| Glaze | 3388.81 | 0.485739 | 5230.28ms | 716365 | 640 | 6.13707e+08 | 201599 | 0.42424 | 0.896724 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1425.67 | 0.220075 | 185.422ms | 2632 | 160 | 2402.12 | 1760.62 | 0.0355114 | 2.11025 | 1(Win) | true |
| Jsonifier (two-stage) | 1238.3 | 0.228094 | 206.674ms | 2632 | 640 | 13681.3 | 2027.03 | 0.100309 | 2.43204 | 2(Loss) | true |
| Glaze | 1007.05 | 0.648634 | 276.245ms | 2632 | 40 | 10455.1 | 2492.5 | 0.100402 | 2.9929 | 3(Loss) | true |
| simdjson (ondemand) | 841.6 | 0.447388 | 304.149ms | 2632 | 40 | 7121.79 | 2982.5 | 0.0838926 | 3.59022 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1894.39 | 0.367681 | 165.201ms | 2632 | 80 | 1898.73 | 1325 | 0.56926 | 1.58318 | 1(Win) | true |
| Glaze | 1773.9 | 0.404079 | 176.908ms | 2632 | 40 | 1307.69 | 1415 | 0.117647 | 1.68812 | 2(Loss) | true |
| Jsonifier (two-stage) | 1602.53 | 0.0951511 | 186.237ms | 2632 | 4890 | 10861.7 | 1566.32 | 0.266977 | 1.8742 | 3(Loss) | true |
| simdjson (ondemand) | 1185.04 | 0.161431 | 249.69ms | 2632 | 160 | 1870.68 | 2118.12 | 0.674091 | 2.54547 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9112 | 0.672827 | 30.0302ms | 2632 | 640 | 2198.53 | 275.469 | 0.0566893 | 0.31488 | 1(Win) | true |
| Glaze | 3643.29 | 0.141509 | 72.0426ms | 2632 | 4890 | 4647.92 | 688.957 | 0.668503 | 0.811611 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8993.4 | 0.290682 | 28.8028ms | 2632 | 2560 | 1685.01 | 279.102 | 0.975127 | 0.311153 | 1(Win) | true |
| Glaze | 4151.89 | 0.298637 | 63.8985ms | 2632 | 4890 | 15939.5 | 604.56 | 0.942496 | 0.709324 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1623.69 | 0.141351 | 202.336ms | 3370 | 1280 | 10019.9 | 1979.38 | 0.126462 | 1.85473 | 1(Win) | true |
| Jsonifier (two-stage) | 1550.73 | 0.191088 | 213.874ms | 3370 | 160 | 2509.43 | 2072.5 | 0 | 1.95017 | 2(Loss) | true |
| Glaze | 1149.74 | 0.22686 | 286.371ms | 3370 | 640 | 25737 | 2795.31 | 0.291513 | 2.6265 | 3(Loss) | true |
| simdjson (ondemand) | 1047.41 | 0.248453 | 308.337ms | 3370 | 2560 | 148782 | 3068.4 | 0.154278 | 2.88052 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2094.59 | 0.287237 | 183.888ms | 3370 | 640 | 12431.5 | 1534.38 | 0.182964 | 1.43298 | 1(Win) | true |
| Jsonifier (two-stage) | 1953.73 | 0.340258 | 196.727ms | 3370 | 80 | 2506.33 | 1645 | 0 | 1.53686 | 2(Loss) | true |
| Glaze | 1930.26 | 0.458716 | 202.246ms | 3370 | 40 | 2333.33 | 1665 | 0.1 | 1.55869 | 3(Loss) | true |
| simdjson (ondemand) | 1465.8 | 0.107151 | 255.228ms | 3370 | 2560 | 14130.1 | 2192.58 | 0.142323 | 2.05286 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10026 | 0.284544 | 37.1981ms | 3643 | 2560 | 2488.89 | 346.523 | 0.415357 | 0.286813 | 1(Win) | true |
| Glaze | 3894.15 | 0.547514 | 92.1008ms | 3682 | 640 | 15599.5 | 901.719 | 0.33032 | 0.762569 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11309.8 | 0.470753 | 32.6952ms | 3643 | 320 | 669.181 | 307.188 | 0.511247 | 0.250694 | 1(Win) | true |
| Glaze | 4581.68 | 0.248865 | 80.1187ms | 3682 | 640 | 2328.22 | 766.406 | 0.0611247 | 0.645039 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 585.854 | 0.272267 | 767.424ms | 4630 | 160 | 67373.8 | 7536.88 | 0.00829325 | 5.17479 | 1(Win) | true |
| Jsonifier (two-stage) | 540.454 | 0.215902 | 824.19ms | 4630 | 640 | 199130 | 8170 | 0.168016 | 5.61043 | 2(Loss) | true |
| simdjson (ondemand) | 337.416 | 0.209218 | 1337.47ms | 4630 | 160 | 119936 | 13086.2 | 0 | 8.99518 | 3(Loss) | true |
| Glaze | 315.411 | 0.287662 | 1405.12ms | 4630 | 4890 | 7.93019e+06 | 13999.2 | 0.0504271 | 9.60471 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 732.613 | 0.126558 | 766.094ms | 4630 | 2560 | 148946 | 6027.07 | 0.406721 | 4.12894 | 1(Win) | true |
| Jsonifier (two-stage) | 666.084 | 0.60518 | 826.724ms | 4630 | 2560 | 4.12016e+06 | 6629.06 | 0.00942907 | 4.54976 | 2(Loss) | true |
| simdjson (ondemand) | 365.121 | 0.35275 | 1382.35ms | 4630 | 2560 | 4.65868e+06 | 12093.3 | 0.689045 | 8.30865 | 3(Loss) | true |
| Glaze | 356.319 | 0.201261 | 1397.65ms | 4630 | 1280 | 796184 | 12392 | 0.164904 | 8.51608 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1822 | 0.13995 | 249.63ms | 4630 | 320 | 3680.94 | 2423.44 | 0.0901829 | 1.65575 | 1(Win) | true |
| Glaze | 1157.17 | 0.125045 | 388.034ms | 4630 | 640 | 14570.6 | 3815.78 | 0.143114 | 2.61286 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1863.09 | 0.359056 | 244.147ms | 4630 | 30 | 2172.41 | 2370 | 0 | 1.6298 | 1(Win) | true |
| Glaze | 1235.11 | 0.259123 | 363.745ms | 4630 | 320 | 27460.8 | 3575 | 0.192678 | 2.44647 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1302.7 | 0.244488 | 875.051ms | 11579 | 30 | 12885.1 | 8476.67 | 0.0785855 | 2.32843 | 1(Win) | true |
| Jsonifier | 1247 | 0.15708 | 902.682ms | 11579 | 320 | 61915.3 | 8855.31 | 0.0529624 | 2.43122 | 2(Loss) | true |
| simdjson (ondemand) | 808.093 | 0.369379 | 1382.62ms | 11579 | 80 | 203823 | 13665 | 0.0182983 | 3.75691 | 3(Loss) | true |
| Glaze | 712.224 | 0.23204 | 1577.61ms | 11579 | 160 | 207088 | 15504.4 | 0.108959 | 4.26021 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1565.91 | 0.154255 | 868.589ms | 11579 | 320 | 37864.8 | 7051.88 | 0.0531491 | 1.93487 | 1(Win) | true |
| Jsonifier | 1512.68 | 0.217188 | 889.781ms | 11579 | 320 | 80438.9 | 7300 | 0.0856898 | 2.00361 | 2(Loss) | true |
| simdjson (ondemand) | 882.853 | 0.22334 | 1418.66ms | 11579 | 4890 | 3.81599e+06 | 12507.9 | 0.00188344 | 3.43643 | 3(Loss) | true |
| Glaze | 784.509 | 0.201914 | 1565.89ms | 11579 | 4890 | 3.94991e+06 | 14075.8 | 0.189813 | 3.86893 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4733.53 | 0.840433 | 317.388ms | 14795 | 640 | 401649 | 2980.78 | 0.360389 | 0.637709 | 1(Win) | true |
| Glaze | 2851.87 | 0.204537 | 529.33ms | 14795 | 40 | 4096.15 | 4947.5 | 0.151822 | 1.06216 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5036.9 | 0.173842 | 300.337ms | 14795 | 80 | 1897.15 | 2801.25 | 2.31037 | 0.598479 | 1(Win) | true |
| Glaze | 3135.47 | 0.184546 | 482.208ms | 14795 | 30 | 2068.97 | 4500 | 0.446429 | 0.966495 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 813.287 | 0.246418 | 382.132ms | 3223 | 4890 | 424118 | 3779.35 | 0.537489 | 3.71525 | 1(Win) | true |
| Jsonifier (two-stage) | 699.61 | 0.124784 | 447.358ms | 3223 | 1280 | 38471.4 | 4393.44 | 0.192417 | 4.32312 | 2(Loss) | true |
| Glaze | 623.19 | 0.828171 | 503.634ms | 3223 | 1280 | 2.13565e+06 | 4932.19 | 1.45598 | 4.85844 | 3(Loss) | true |
| simdjson (ondemand) | 540.37 | 0.122116 | 579.75ms | 3223 | 160 | 7719.73 | 5688.12 | 0.25336 | 5.60248 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.71 | 0.155224 | 344.421ms | 3223 | 2560 | 44706.4 | 2692.19 | 0.505269 | 2.63922 | 1(Win) | true |
| Jsonifier (two-stage) | 902.729 | 0.140228 | 417.551ms | 3223 | 4890 | 111477 | 3404.89 | 0.240205 | 3.34555 | 2(Loss) | true |
| Glaze | 816.657 | 0.184536 | 451.413ms | 3223 | 80 | 3859.18 | 3763.75 | 0.500668 | 3.70096 | 3(Loss) | true |
| simdjson (ondemand) | 689.652 | 0.156553 | 516.45ms | 3223 | 640 | 31157.7 | 4456.88 | 0.258759 | 4.38693 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7318.32 | 1.52503 | 41.3702ms | 3223 | 40 | 1641.03 | 420 | 0 | 0.401916 | 1(Win) | true |
| Glaze | 3325.96 | 0.125185 | 97.3068ms | 3223 | 4890 | 6544.84 | 924.151 | 0.115416 | 0.895853 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10161 | 0.580675 | 34.2634ms | 3223 | 80 | 246.835 | 302.5 | 0 | 0.283013 | 1(Win) | true |
| Glaze | 4158.91 | 0.26115 | 79.3485ms | 3223 | 640 | 2384.1 | 739.062 | 0.595491 | 0.71201 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1224.74 | 0.293255 | 475.526ms | 5839 | 30 | 5333.33 | 4546.67 | 1.18694 | 2.46675 | 1(Win) | true |
| Jsonifier (two-stage) | 1201.14 | 0.107193 | 489.674ms | 5839 | 1280 | 31610.4 | 4636.02 | 0.455376 | 2.51807 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 945.417 | 0.205129 | 620.345ms | 5839 | 30 | 4379.31 | 5890 | 0.169492 | 3.20986 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 942.178 | 1.39752 | 604.508ms | 5839 | 4890 | 3.33609e+07 | 5910.25 | 0.362362 | 3.21357 | 3(Tie) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1659.76 | 0.36893 | 438.647ms | 5839 | 40 | 6128.21 | 3355 | 0.641658 | 1.82484 | 1(Win) | true |
| Jsonifier (two-stage) | 1501.29 | 0.713368 | 458.549ms | 5839 | 1280 | 896156 | 3709.14 | 0.592546 | 2.01275 | 2(Loss) | true |
| simdjson (ondemand) | 1199.46 | 0.449769 | 550.964ms | 5839 | 80 | 34879.7 | 4642.5 | 0.588865 | 2.52154 | 3(Loss) | true |
| Glaze | 1187.63 | 0.156403 | 550.772ms | 5839 | 80 | 4302.22 | 4688.75 | 0.401499 | 2.54616 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8305.35 | 0.41841 | 77.5103ms | 6938 | 30 | 333.333 | 796.667 | 0 | 0.358369 | 1(Win) | true |
| Glaze | 4030.91 | 0.562598 | 164.215ms | 6960 | 30 | 2574.71 | 1646.67 | 0.20202 | 0.745374 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10006.2 | 0.828914 | 75.7426ms | 6938 | 80 | 2403.48 | 661.25 | 0.93633 | 0.295701 | 1(Win) | true |
| Glaze | 5122.45 | 0.483595 | 138.085ms | 6960 | 640 | 25130.8 | 1295.78 | 0.108643 | 0.5837 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1287.45 | 0.35144 | 375.198ms | 4857 | 2560 | 409280 | 3597.81 | 0.488784 | 2.34781 | 1(Win) | true |
| Jsonifier (two-stage) | 1008.42 | 0.389632 | 482.666ms | 4857 | 30 | 9609.2 | 4593.33 | 0.361533 | 3.00165 | 2(Loss) | true |
| Glaze | 998.275 | 0.284868 | 504.006ms | 4857 | 30 | 5241.38 | 4640 | 0.429185 | 3.03378 | 3(Loss) | true |
| simdjson (ondemand) | 740.083 | 0.533029 | 654.364ms | 4857 | 80 | 89036.4 | 6258.75 | 0.380914 | 4.09434 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1960.18 | 0.691226 | 291.724ms | 4857 | 1280 | 341503 | 2363.05 | 0.0363805 | 1.53683 | 1(Win) | true |
| Glaze | 1754.54 | 0.34459 | 319.76ms | 4857 | 30 | 2482.76 | 2640 | 0.126422 | 1.71894 | 2(Loss) | true |
| Jsonifier (two-stage) | 1347 | 0.16758 | 407.082ms | 4857 | 80 | 2656.65 | 3438.75 | 0.542299 | 2.24453 | 3(Loss) | true |
| simdjson (ondemand) | 1080.56 | 0.216115 | 498.719ms | 4857 | 30 | 2574.71 | 4286.67 | 0.547303 | 2.79986 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9387.2 | 0.925687 | 55.5423ms | 4857 | 640 | 13352.8 | 493.438 | 0.317662 | 0.312081 | 1(Win) | true |
| Glaze | 3474 | 0.656532 | 132.856ms | 4857 | 30 | 2298.85 | 1333.33 | 0.250627 | 0.86819 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10832.4 | 0.879549 | 47.9104ms | 4857 | 4890 | 69170.2 | 427.607 | 1.23829 | 0.267733 | 1(Win) | true |
| Glaze | 4199.57 | 1.51203 | 113.474ms | 4857 | 1280 | 356004 | 1102.97 | 0.0850702 | 0.71087 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1551.11 | 0.316573 | 434.452ms | 6701 | 30 | 5103.45 | 4120 | 0.324675 | 1.95569 | 1(Win) | true |
| Jsonifier (two-stage) | 1338.81 | 0.374939 | 501.458ms | 6701 | 30 | 9609.2 | 4773.33 | 0.350385 | 2.25343 | 2(Loss) | true |
| Glaze | 1166.16 | 0.228219 | 569.204ms | 6701 | 40 | 6256.41 | 5480 | 0.243902 | 2.59838 | 3(Loss) | true |
| simdjson (ondemand) | 1013.3 | 0.283781 | 676.129ms | 6701 | 30 | 9609.2 | 6306.67 | 0.942408 | 2.992 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2131.99 | 0.10513 | 365.017ms | 6701 | 2560 | 25421.5 | 2997.46 | 0.36229 | 1.416 | 1(Win) | true |
| Glaze | 1936.54 | 0.251653 | 394.379ms | 6701 | 30 | 2068.97 | 3300 | 0.801603 | 1.5626 | 2(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1644.97 | 1.18043 | 439.415ms | 6701 | 4890 | 1.02838e+07 | 3884.91 | 2.92212 | 1.83833 | -(Loss) | false |
| simdjson (ondemand) | 1453.5 | 0.17185 | 506.526ms | 6701 | 30 | 1712.64 | 4396.67 | 0.995406 | 2.0821 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8443.27 | 0.316304 | 92.4891ms | 7376 | 320 | 2222.18 | 833.125 | 0.150263 | 0.353433 | 1(Win) | true |
| Glaze | 3281.94 | 1.35488 | 227.858ms | 7376 | 30 | 25298.9 | 2143.33 | 0.15528 | 0.916147 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8876.09 | 0.286337 | 84.0596ms | 7376 | 160 | 823.899 | 792.5 | 0.955414 | 0.328269 | 1(Win) | true |
| Glaze | 3722.47 | 1.07591 | 200.797ms | 7376 | 320 | 132276 | 1889.69 | 0.247443 | 0.80193 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1209.4 | 0.21154 | 147.177ms | 1691 | 320 | 2546.14 | 1333.44 | 0.163781 | 2.47423 | 1(Win) | true |
| Glaze | 1174.45 | 0.3078 | 149.616ms | 1691 | 160 | 2858.1 | 1373.12 | 2.09447 | 2.54448 | 2(Loss) | true |
| Jsonifier (two-stage) | 977.14 | 0.786961 | 180.775ms | 1691 | 1280 | 215919 | 1650.39 | 0.728383 | 3.07289 | 3(Loss) | true |
| simdjson (ondemand) | 774.388 | 0.280401 | 225.38ms | 1691 | 80 | 2727.85 | 2082.5 | 0 | 3.89162 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1741.65 | 0.265025 | 119.594ms | 1691 | 320 | 1927.02 | 925.938 | 0.64538 | 1.70786 | 1(Win) | true |
| Glaze | 1647.02 | 0.169946 | 122.096ms | 1691 | 1280 | 3544.22 | 979.141 | 0.199872 | 1.81061 | 2(Loss) | true |
| Jsonifier (two-stage) | 1323.12 | 0.104111 | 153.802ms | 1691 | 4890 | 7873.87 | 1218.83 | 0.191416 | 2.2599 | 3(Loss) | true |
| simdjson (ondemand) | 876.708 | 0.132704 | 215.131ms | 1691 | 2560 | 15254.1 | 1839.45 | 0.42653 | 3.42844 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10181.9 | 0.503765 | 21.9192ms | 1996 | 1280 | 1135.35 | 186.953 | 0.869925 | 0.268559 | 1(Win) | true |
| Glaze | 4350.93 | 0.900662 | 51.4815ms | 1996 | 160 | 2484.28 | 437.5 | 0.286533 | 0.668171 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14366.3 | 1.97917 | 17.5479ms | 1996 | 320 | 2200.63 | 132.5 | 2.30415 | 0.186645 | 1(Win) | true |
| Glaze | 5058.7 | 1.88494 | 39.3736ms | 1996 | 2560 | 128789 | 376.289 | 0.532248 | 0.554415 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1266.48 | 0.528364 | 173.697ms | 2158 | 40 | 2948.72 | 1625 | 0.510204 | 2.38844 | 1(Win) | true |
| Jsonifier | 1210.61 | 0.421244 | 161.42ms | 2158 | 40 | 2051.28 | 1700 | 0.195695 | 2.48561 | 2(Loss) | true |
| Glaze | 1100.55 | 0.436629 | 164.073ms | 2158 | 40 | 2666.67 | 1870 | 0.35524 | 2.74164 | 3(Loss) | true |
| simdjson (ondemand) | 985.698 | 0.159777 | 212.093ms | 2158 | 2560 | 28489.5 | 2087.89 | 0.112381 | 3.05377 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1843.7 | 0.37183 | 147.369ms | 2158 | 80 | 1378.16 | 1116.25 | 1.43488 | 1.62188 | 1(Win) | true |
| Glaze | 1776.02 | 0.134959 | 141.828ms | 2158 | 2560 | 6261.14 | 1158.79 | 0.673006 | 1.68263 | 2(Loss) | true |
| Jsonifier (two-stage) | 1601.58 | 0.525005 | 156.484ms | 2158 | 40 | 1820.51 | 1285 | 0.12987 | 1.85883 | 3(Loss) | true |
| simdjson (ondemand) | 1073 | 0.607605 | 235.763ms | 2158 | 2560 | 347683 | 1918.01 | 0.40283 | 2.80263 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8038.91 | 1.62111 | 32.3831ms | 2866 | 80 | 2430.38 | 340 | 0 | 0.360459 | 1(Win) | true |
| Glaze | 3632.2 | 3.62338 | 81.3062ms | 2866 | 40 | 29737.2 | 752.5 | 0.550661 | 0.803367 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12548.5 | 0.983529 | 24.5284ms | 2866 | 320 | 1468.55 | 217.812 | 0.428571 | 0.221212 | 1(Win) | true |
| Glaze | 4924.74 | 1.1057 | 71.643ms | 2866 | 80 | 3012.66 | 555 | 1.83486 | 0.589519 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1139.61 | 0.27282 | 380.666ms | 4390 | 80 | 8036.39 | 3673.75 | 1.11036 | 2.65368 | 1(Win) | true |
| Jsonifier (two-stage) | 976.901 | 0.135426 | 449.578ms | 4390 | 160 | 5389.54 | 4285.62 | 0.808586 | 3.10043 | 2(Loss) | true |
| Glaze | 878.982 | 0.43817 | 489.302ms | 4390 | 4890 | 2.12993e+06 | 4763.05 | 0.0377077 | 3.44282 | 3(Loss) | true |
| simdjson (ondemand) | 598.625 | 0.403256 | 749.549ms | 4390 | 80 | 63631.3 | 6993.75 | 2.18531 | 5.06462 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1355.07 | 0.421873 | 375.761ms | 4390 | 1280 | 217460 | 3089.61 | 0.869805 | 2.23008 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1147.69 | 0.13084 | 430.164ms | 4390 | 1280 | 29159 | 3647.89 | 0.657419 | 2.63361 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1142.33 | 0.301912 | 442.08ms | 4390 | 40 | 4897.44 | 3665 | 0.22686 | 2.64727 | 2(Tie) | true |
| simdjson (ondemand) | 666.503 | 1.31139 | 695.012ms | 4390 | 2560 | 1.7371e+07 | 6281.48 | 2.05758 | 4.54523 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9316.56 | 0.622919 | 52.6696ms | 4390 | 320 | 2507.45 | 449.375 | 1.90996 | 0.311029 | 1(Win) | true |
| Glaze | 3413.01 | 0.669437 | 135.053ms | 4390 | 30 | 2022.99 | 1226.67 | 0 | 0.87631 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9303.62 | 1.2501 | 47.6314ms | 4390 | 80 | 2531.65 | 450 | 0.558659 | 0.311022 | 1(Win) | true |
| Glaze | 3992.02 | 0.377976 | 115.901ms | 4390 | 160 | 2514.15 | 1048.75 | 0.358852 | 0.743803 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2082.32 | 0.262967 | 441.157ms | 9378 | 40 | 5102.56 | 4295 | 0.0388199 | 1.4478 | 1(Win) | true |
| Jsonifier (two-stage) | 1980.58 | 0.144857 | 454.885ms | 9378 | 1280 | 54767.4 | 4515.62 | 0.329804 | 1.52747 | 2(Loss) | true |
| Glaze | 1422.82 | 0.130691 | 656.194ms | 9378 | 1280 | 86380.9 | 6285.78 | 1.63578 | 2.12933 | 3(Loss) | true |
| simdjson (ondemand) | 1217.59 | 0.115952 | 747.053ms | 9378 | 640 | 46425.6 | 7345.31 | 0.110737 | 2.4888 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2371.83 | 0.113862 | 430.167ms | 9378 | 2560 | 47189.8 | 3770.74 | 0.225305 | 1.27498 | 1(Win) | true |
| Jsonifier (two-stage) | 2274.76 | 0.114144 | 444.625ms | 9378 | 2560 | 51558.1 | 3931.64 | 0.097462 | 1.32937 | 2(Loss) | true |
| Glaze | 1675.46 | 0.27628 | 594.559ms | 9378 | 640 | 139198 | 5337.97 | 0.0849593 | 1.80625 | 3(Loss) | true |
| simdjson (ondemand) | 1381.7 | 0.0774923 | 717.26ms | 9378 | 2560 | 64409.2 | 6472.85 | 0.128377 | 2.19308 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12975.1 | 0.197238 | 92.2017ms | 11521 | 1280 | 3570.65 | 846.797 | 0.398296 | 0.228965 | 1(Win) | true |
| Glaze | 4742.52 | 0.614654 | 240.618ms | 11521 | 2560 | 519113 | 2316.76 | 0.551662 | 0.633532 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15084.5 | 0.132477 | 80.514ms | 11521 | 4890 | 4553.13 | 728.384 | 1.38748 | 0.196227 | 1(Win) | true |
| Glaze | 6287.71 | 0.194399 | 181.856ms | 11521 | 1280 | 14770.5 | 1747.42 | 0.271981 | 0.475161 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2189.41 | 0.199252 | 223.48ms | 4669 | 160 | 2627.36 | 2033.75 | 0.184729 | 1.38103 | 1(Win) | true |
| Jsonifier (two-stage) | 1446.27 | 0.16027 | 318.711ms | 4669 | 80 | 1947.78 | 3078.75 | 0.203417 | 2.08903 | 2(Loss) | true |
| Glaze | 1311.07 | 0.147424 | 352.582ms | 4669 | 160 | 4011.01 | 3396.25 | 0.0367918 | 2.30309 | 3(Loss) | true |
| simdjson (ondemand) | 897.061 | 0.352305 | 504.284ms | 4669 | 4890 | 1.49538e+06 | 4963.66 | 0.847375 | 3.37416 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2486.68 | 0.162705 | 205.877ms | 4669 | 160 | 1358.1 | 1790.62 | 1.34298 | 1.21287 | 1(Win) | true |
| Jsonifier (two-stage) | 1594.52 | 0.198121 | 315.949ms | 4669 | 40 | 1224.36 | 2792.5 | 1.79222 | 1.89672 | 2(Loss) | true |
| Glaze | 1557.24 | 0.4099 | 307.438ms | 4669 | 4890 | 671744 | 2859.37 | 0.0208004 | 1.93727 | 3(Loss) | true |
| simdjson (ondemand) | 982.403 | 0.110011 | 480.916ms | 4669 | 2560 | 63646.9 | 4532.46 | 0.0559881 | 3.08166 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14061.2 | 0.241584 | 34.3589ms | 4669 | 4890 | 2861.87 | 316.667 | 0.218404 | 0.203771 | 1(Win) | true |
| Glaze | 3128.77 | 0.325018 | 152.579ms | 4669 | 4890 | 104623 | 1423.15 | 0.430113 | 0.958497 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16942.5 | 0.727487 | 32.16ms | 4669 | 640 | 2339.5 | 262.812 | 0.718563 | 0.166268 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3364.97 | 0.965926 | 128.62ms | 4669 | 4890 | 798880 | 1323.25 | 10.4706 | 0.887564 | -(Loss) | false |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2678.9 | 0.2069 | 305.519ms | 7932 | 640 | 21845.1 | 2823.75 | 0.264901 | 1.1269 | 1(Win) | true |
| Jsonifier (two-stage) | 2339.25 | 0.128277 | 333.32ms | 7932 | 160 | 2753.14 | 3233.75 | 0.423403 | 1.29034 | 2(Loss) | true |
| Glaze | 1716.53 | 0.278714 | 460.757ms | 7932 | 1280 | 193104 | 4406.88 | 0.525518 | 1.76295 | 3(Loss) | true |
| simdjson (ondemand) | 1456.44 | 0.452972 | 529.953ms | 7932 | 4890 | 2.70664e+06 | 5193.84 | 0.41493 | 2.07806 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2946.27 | 0.144672 | 283.598ms | 7932 | 160 | 2207.55 | 2567.5 | 0.868726 | 1.02532 | 1(Win) | true |
| Jsonifier (two-stage) | 2570.06 | 0.312634 | 321.416ms | 7932 | 30 | 2540.23 | 2943.33 | 0 | 1.17134 | 2(Loss) | true |
| Glaze | 1931.83 | 0.709323 | 411.549ms | 7932 | 2560 | 1.97495e+06 | 3915.74 | 0.150861 | 1.5655 | 3(Loss) | true |
| simdjson (ondemand) | 1572.26 | 0.531958 | 505.288ms | 7932 | 80 | 52403.5 | 4811.25 | 0.542636 | 1.92579 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10316.4 | 0.654648 | 84.2695ms | 9249 | 80 | 2506.33 | 855 | 0.588235 | 0.287584 | 1(Win) | true |
| Glaze | 3046.93 | 1.56972 | 303.024ms | 9249 | 4890 | 1.00976e+07 | 2894.89 | 0.404353 | 0.99011 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12379.7 | 0.522229 | 76.4776ms | 9249 | 80 | 1107.59 | 712.5 | 0.34965 | 0.239362 | 1(Win) | true |
| Glaze | 3034.04 | 0.446432 | 309.443ms | 9249 | 640 | 107804 | 2907.19 | 1.82566 | 0.989808 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 462.181 | 0.226142 | 989.708ms | 4604 | 40 | 18461.5 | 9500 | 0.175747 | 6.56382 | 1(Win) | true |
| Jsonifier (two-stage) | 435.443 | 0.260804 | 1067.63ms | 4604 | 30 | 20747.1 | 10083.3 | 0.427913 | 6.97037 | 2(Loss) | true |
| Glaze | 272.434 | 0.584655 | 1629.69ms | 4604 | 1280 | 1.13647e+07 | 16116.6 | 0.370259 | 11.1406 | 3(Loss) | true |
| simdjson (ondemand) | 157.764 | 0.125304 | 2858.01ms | 4604 | 320 | 389165 | 27830.9 | 0.00112284 | 19.2536 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 565.328 | 0.128508 | 955.591ms | 4604 | 30 | 2988.51 | 7766.67 | 0.0429 | 5.36011 | 1(Win) | true |
| Jsonifier (two-stage) | 502.42 | 0.630149 | 1036.15ms | 4604 | 4890 | 1.48297e+07 | 8739.14 | 0.390399 | 6.03472 | 2(Loss) | true |
| Glaze | 310.641 | 0.166449 | 1596.76ms | 4604 | 160 | 88559.4 | 14134.4 | 0.41293 | 9.77188 | 3(Loss) | true |
| simdjson (ondemand) | 169.004 | 0.331884 | 2750.99ms | 4604 | 30 | 223034 | 25980 | 0.0384763 | 17.9666 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1449.07 | 0.276474 | 329.912ms | 4918 | 30 | 2402.3 | 3236.67 | 0.20555 | 2.08555 | 1(Win) | true |
| Glaze | 883.611 | 0.291815 | 498.084ms | 4604 | 320 | 67284.4 | 4969.06 | 0.0816891 | 3.42455 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1525.26 | 0.178309 | 315.308ms | 4918 | 80 | 2405.06 | 3075 | 0.0812348 | 1.97556 | 1(Win) | true |
| Glaze | 939.382 | 0.420056 | 470.598ms | 4604 | 4890 | 1.88499e+06 | 4674.05 | 0.121878 | 3.22185 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1578.61 | 0.281471 | 1135.71ms | 18245 | 320 | 308001 | 11022.2 | 0.493709 | 1.92089 | 1(Win) | true |
| Jsonifier | 1327.27 | 0.211714 | 1355.36ms | 18245 | 1280 | 986001 | 13109.5 | 0.207221 | 2.28608 | 2(Loss) | true |
| Glaze | 939.767 | 0.477712 | 1874.01ms | 18245 | 80 | 625848 | 18515 | 0.134844 | 3.231 | 3(Loss) | true |
| simdjson (ondemand) | 592.414 | 0.312873 | 2975.54ms | 18245 | 2560 | 2.1618e+07 | 29371 | 0.0600784 | 5.12583 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1892.82 | 0.112807 | 1101.39ms | 18245 | 40 | 4301.28 | 9192.5 | 0.00906454 | 1.60302 | 1(Win) | true |
| Jsonifier | 1532.12 | 0.100648 | 1336.79ms | 18245 | 30 | 3919.54 | 11356.7 | 0.471837 | 1.97752 | 2(Loss) | true |
| Glaze | 1042.41 | 0.193938 | 1832.21ms | 18245 | 160 | 167669 | 16691.9 | 0.123411 | 2.91235 | 3(Loss) | true |
| simdjson (ondemand) | 644.649 | 0.263666 | 2919.8ms | 18245 | 640 | 3.24138e+06 | 26991.1 | 0.0480714 | 4.71076 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5349.06 | 0.831378 | 461.149ms | 24893 | 320 | 435658 | 4438.12 | 0.266854 | 0.564925 | 1(Win) | true |
| Glaze | 2857.42 | 0.835784 | 862.194ms | 24579 | 30 | 141023 | 8203.33 | 0.984817 | 1.0597 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5639.43 | 0.114617 | 434.217ms | 24893 | 1280 | 29798.1 | 4209.61 | 0.485724 | 0.535995 | 1(Win) | true |
| Glaze | 3300.3 | 0.5954 | 775.67ms | 24579 | 40 | 71532.1 | 7102.5 | 0.69707 | 0.91792 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 510.548 | 0.136563 | 928.137ms | 4604 | 30 | 4137.93 | 8600 | 0.15528 | 5.9313 | 1(Win) | true |
| Jsonifier (two-stage) | 446.211 | 0.177692 | 1029.73ms | 4604 | 320 | 97830.7 | 9840 | 0.0826394 | 6.79739 | 2(Loss) | true |
| simdjson (ondemand) | 306.258 | 0.131595 | 1496.78ms | 4604 | 30 | 10678.2 | 14336.7 | 0.116117 | 9.90589 | 3(Loss) | true |
| Glaze | 270.531 | 0.0601812 | 1680ms | 4604 | 30 | 2862.07 | 16230 | 0.0410931 | 11.2227 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 631.624 | 1.71523 | 832.525ms | 4604 | 4890 | 6.95195e+07 | 6951.47 | 0.647789 | 4.79473 | 1(Win) | true |
| Jsonifier (two-stage) | 560.308 | 0.437988 | 975.27ms | 4604 | 80 | 94238.9 | 7836.25 | 0.111785 | 5.40853 | 2(Loss) | true |
| simdjson (ondemand) | 323.834 | 1.08909 | 1466.35ms | 4604 | 4890 | 1.06626e+08 | 13558.5 | 0.32715 | 9.36861 | 3(Loss) | true |
| Glaze | 309.267 | 0.138324 | 1666.78ms | 4604 | 320 | 123409 | 14197.2 | 0.174193 | 9.81458 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1576.53 | 0.356016 | 320.874ms | 4918 | 40 | 4487.18 | 2975 | 0.393701 | 1.92076 | 1(Win) | true |
| Glaze | 867.115 | 2.46692 | 509.888ms | 4604 | 1280 | 1.99728e+07 | 5063.59 | 0.592025 | 3.49124 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1634.21 | 0.417522 | 304.777ms | 4918 | 40 | 5743.59 | 2870 | 0.819672 | 1.83997 | 1(Win) | true |
| Glaze | 952.175 | 0.761073 | 475.892ms | 4604 | 640 | 788261 | 4611.25 | 0.469803 | 3.17943 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1642.26 | 0.0785738 | 1125.74ms | 18245 | 80 | 5544.3 | 10595 | 0.39953 | 1.84717 | 1(Win) | true |
| Jsonifier | 1471.75 | 0.111227 | 1266.87ms | 18245 | 40 | 6916.67 | 11822.5 | 0.817953 | 2.06027 | 2(Loss) | true |
| simdjson (ondemand) | 1095.43 | 0.840191 | 1616.06ms | 18245 | 4890 | 8.70933e+07 | 15884 | 1.36454 | 2.76987 | 3(Loss) | true |
| Glaze | 927.165 | 0.135993 | 1982.6ms | 18245 | 30 | 19540.2 | 18766.7 | 0.23144 | 3.27591 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2063.22 | 0.131297 | 1049.42ms | 18245 | 30 | 3678.16 | 8433.33 | 1.24902 | 1.4697 | 1(Win) | true |
| Jsonifier | 1772.44 | 0.467245 | 1170.56ms | 18245 | 160 | 336632 | 9816.88 | 0.197755 | 1.71103 | 2(Loss) | true |
| simdjson (ondemand) | 1280.34 | 0.0824795 | 1562.99ms | 18245 | 40 | 5025.64 | 13590 | 0.418719 | 2.36988 | 3(Loss) | true |
| Glaze | 1048.14 | 0.263588 | 1900.19ms | 18245 | 160 | 306352 | 16600.6 | 0.19994 | 2.89665 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5410.78 | 0.872057 | 462.378ms | 24893 | 40 | 58557.7 | 4387.5 | 1.25 | 0.558725 | 1(Win) | true |
| Glaze | 2984.13 | 0.96799 | 836.335ms | 24579 | 40 | 231256 | 7855 | 0.0212224 | 1.01588 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5628.47 | 1.04077 | 446.757ms | 24893 | 320 | 616641 | 4217.81 | 0.742756 | 0.537176 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3078.51 | 2.18704 | 740.245ms | 24579 | 2560 | 7.09901e+07 | 7614.18 | 3.26402 | 0.983794 | -(Loss) | false |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.76 | 0.113527 | 516.63ms | 5094 | 160 | 4792.06 | 4820.62 | 0.14282 | 3.0066 | 1(Win) | true |
| Jsonifier (two-stage) | 832.922 | 0.197858 | 622.7ms | 5094 | 40 | 5326.92 | 5832.5 | 0.976231 | 3.62996 | 2(Loss) | true |
| Glaze | 679.205 | 0.240016 | 766.107ms | 5094 | 40 | 11788.5 | 7152.5 | 1.02401 | 4.45654 | 3(Loss) | true |
| simdjson (ondemand) | 533.546 | 0.817336 | 939.29ms | 5094 | 2560 | 1.4178e+07 | 9105.16 | 0.287406 | 5.68266 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1298.94 | 0.274956 | 504.848ms | 5094 | 30 | 3172.41 | 3740 | 0.620018 | 2.32051 | 1(Win) | true |
| Jsonifier (two-stage) | 1021.66 | 0.216496 | 610.785ms | 5094 | 160 | 16956 | 4755 | 0.768212 | 2.9664 | 2(Loss) | true |
| Glaze | 951.309 | 0.264451 | 645.111ms | 5094 | 30 | 5471.26 | 5106.67 | 0.327439 | 3.18318 | 3(Loss) | true |
| simdjson (ondemand) | 716.522 | 0.178902 | 840.968ms | 5094 | 30 | 4413.79 | 6780 | 0.196271 | 4.21885 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9728.19 | 0.177137 | 55.8738ms | 5094 | 320 | 250.392 | 499.375 | 0.125 | 0.301288 | 1(Win) | true |
| Glaze | 3339.57 | 0.120007 | 152.124ms | 5094 | 4890 | 14902.4 | 1454.68 | 0.0749368 | 0.897882 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13047.1 | 0.475229 | 40.6114ms | 5094 | 640 | 2003.89 | 372.344 | 0.0419463 | 0.22222 | 1(Win) | true |
| Glaze | 3860.36 | 0.715448 | 128.374ms | 5094 | 1280 | 103760 | 1258.44 | 0.637261 | 0.772298 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1391.11 | 0.347712 | 581.149ms | 8051 | 160 | 58930.4 | 5519.38 | 0.011325 | 2.17892 | 1(Win) | true |
| Jsonifier (two-stage) | 1254.5 | 0.434137 | 615.293ms | 8051 | 4890 | 3.45236e+06 | 6120.37 | 0.186344 | 2.41521 | 2(Loss) | true |
| Glaze | 953.793 | 0.183392 | 847.711ms | 8051 | 40 | 8717.95 | 8050 | 0.374065 | 3.18193 | 3(Loss) | true |
| simdjson (ondemand) | 851.946 | 0.137535 | 921.056ms | 8051 | 640 | 98329.4 | 9012.34 | 0.196296 | 3.55923 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1722.98 | 0.152544 | 561.273ms | 8051 | 1280 | 59147.8 | 4456.25 | 0.408562 | 1.75746 | 1(Win) | true |
| Jsonifier (two-stage) | 1533.83 | 0.11808 | 611.758ms | 8051 | 1280 | 44720.3 | 5005.78 | 2.10536 | 1.97492 | 2(Loss) | true |
| Glaze | 1275.95 | 0.252023 | 728.632ms | 8051 | 160 | 36798.7 | 6017.5 | 0.501044 | 2.37461 | 3(Loss) | true |
| simdjson (ondemand) | 1093.35 | 0.15705 | 856.59ms | 8051 | 40 | 4865.38 | 7022.5 | 0.801435 | 2.77261 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11225.8 | 0.492784 | 87.541ms | 9255 | 80 | 1200.95 | 786.25 | 0.15873 | 0.263494 | 1(Win) | true |
| Glaze | 3922.51 | 0.829456 | 245.744ms | 9255 | 640 | 222942 | 2250.16 | 1.03766 | 0.766376 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13716.5 | 0.876695 | 71.1434ms | 9255 | 4890 | 155622 | 643.476 | 0.225103 | 0.215384 | 1(Win) | true |
| Glaze | 5299.07 | 1.56228 | 177.583ms | 9255 | 320 | 216683 | 1665.62 | 0.0375094 | 0.564405 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5046.67 | 0.294046 | 58.6757ms | 2889 | 1280 | 3298.57 | 545.938 | 0.633641 | 0.582586 | 1(Win) | true |
| Jsonifier (two-stage) | 4972.23 | 0.172658 | 58.0419ms | 2889 | 4890 | 4475.84 | 554.11 | 0.4755 | 0.591204 | 2(Loss) | true |
| simdjson (ondemand) | 3685.84 | 0.751626 | 71.4425ms | 2889 | 80 | 2525.32 | 747.5 | 0 | 0.798308 | 3(Loss) | true |
| Glaze | 3037.04 | 0.215101 | 97.2742ms | 2889 | 1280 | 4874.02 | 907.188 | 0.137979 | 0.98028 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5446.4 | 0.17863 | 56.5468ms | 2889 | 4890 | 3992.95 | 505.869 | 0.236889 | 0.538032 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5440.62 | 0.271183 | 54.9496ms | 2889 | 1280 | 2413.97 | 506.406 | 0.613309 | 0.537774 | 1(Tie) | true |
| simdjson (ondemand) | 4360.3 | 0.412907 | 66.5843ms | 2889 | 320 | 2178.29 | 631.875 | 0.492126 | 0.678152 | 3(Loss) | true |
| Glaze | 3037.21 | 0.142343 | 92.2344ms | 2889 | 4890 | 8153.18 | 907.137 | 0.0313923 | 0.970728 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6142.23 | 0.291045 | 64.427ms | 3808 | 640 | 1895.15 | 591.25 | 0.158311 | 0.481349 | 1(Win) | true |
| Jsonifier | 6018.17 | 0.566106 | 63.1003ms | 3808 | 640 | 7468.6 | 603.438 | 0.259605 | 0.488291 | 2(Loss) | true |
| simdjson (ondemand) | 4944.62 | 0.215749 | 76.7116ms | 3808 | 1280 | 3213.93 | 734.453 | 0.223881 | 0.596976 | 3(Loss) | true |
| Glaze | 3434.13 | 0.525938 | 114.116ms | 3808 | 80 | 2474.68 | 1057.5 | 0.714286 | 0.871389 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6727.12 | 0.379223 | 58.375ms | 3808 | 640 | 2682.29 | 539.844 | 0.144928 | 0.433814 | 1(Win) | true |
| Jsonifier (two-stage) | 6580.46 | 0.307527 | 58.4716ms | 3808 | 1280 | 3686.86 | 551.875 | 0.312411 | 0.443406 | 2(Loss) | true |
| simdjson (ondemand) | 5178.74 | 0.178253 | 71.257ms | 3808 | 80 | 125 | 701.25 | 0.178571 | 0.569482 | 3(Loss) | true |
| Glaze | 3665.96 | 0.411741 | 109.035ms | 3808 | 640 | 10647.5 | 990.625 | 0.906533 | 0.806336 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1880.46 | 0.15983 | 151.1ms | 2889 | 4890 | 26815.7 | 1465.15 | 0.267126 | 1.59516 | 1(Win) | true |
| Glaze | 1670.43 | 0.240391 | 171.651ms | 2889 | 160 | 2515.33 | 1649.38 | 0.64006 | 1.7999 | 2(Loss) | true |
| simdjson (ondemand) | 1406.59 | 0.20439 | 198.126ms | 2889 | 160 | 2564.47 | 1958.75 | 0.191816 | 2.14221 | 3(Loss) | true |
| Jsonifier (two-stage) | 1354.31 | 0.185151 | 210.839ms | 2889 | 160 | 2270.05 | 2034.38 | 0.0307314 | 2.22569 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2389.63 | 0.38634 | 139.768ms | 2889 | 640 | 12698.5 | 1152.97 | 0.283784 | 1.24945 | 1(Win) | true |
| Glaze | 2004.95 | 0.106013 | 158.045ms | 2889 | 2560 | 5433.09 | 1374.18 | 0.173099 | 1.49453 | 2(Loss) | true |
| Jsonifier (two-stage) | 1595.33 | 0.157758 | 199.817ms | 2889 | 4890 | 36298.1 | 1727.01 | 1.71276 | 1.88255 | 3(Loss) | true |
| simdjson (ondemand) | 1563.35 | 0.557957 | 195.678ms | 2889 | 640 | 61881.8 | 1762.34 | 0.00886682 | 1.92435 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10460.9 | 0.320377 | 29.8594ms | 2963 | 4890 | 3662.29 | 270.123 | 0.233963 | 0.271379 | 1(Win) | true |
| Glaze | 4843.1 | 0.387764 | 62.384ms | 2963 | 4890 | 25030 | 583.456 | 0.285178 | 0.60762 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12147.6 | 0.288235 | 25.6835ms | 2963 | 4890 | 2198.3 | 232.618 | 0.100483 | 0.227826 | 1(Win) | true |
| Glaze | 5811.28 | 0.590518 | 51.7493ms | 2963 | 160 | 1319.18 | 486.25 | 0.511509 | 0.502643 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1897.75 | 0.100839 | 197.129ms | 3808 | 2560 | 9532.71 | 1913.63 | 0.148791 | 1.58629 | 1(Win) | true |
| simdjson (ondemand) | 1841.55 | 0.210234 | 205.834ms | 3808 | 640 | 11000.6 | 1972.03 | 0.825083 | 1.63725 | 2(Loss) | true |
| Glaze | 1807.78 | 0.11425 | 204.698ms | 3808 | 2560 | 13485.2 | 2008.87 | 0.337535 | 1.66665 | 3(Loss) | true |
| Jsonifier (two-stage) | 1743.16 | 0.332182 | 212.727ms | 3808 | 30 | 1436.78 | 2083.33 | 0.318979 | 1.71509 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2280.43 | 0.17206 | 183.418ms | 3808 | 160 | 1201.26 | 1592.5 | 0.0785546 | 1.31962 | 1(Win) | true |
| Glaze | 2158.45 | 0.275205 | 196.621ms | 3808 | 80 | 1715.19 | 1682.5 | 0.296296 | 1.39109 | 2(Loss) | true |
| Jsonifier (two-stage) | 2072.6 | 0.112778 | 198.392ms | 3808 | 640 | 2499.12 | 1752.19 | 0.26824 | 1.44963 | 3(Loss) | true |
| simdjson (ondemand) | 2028.82 | 0.268371 | 196.846ms | 3808 | 40 | 923.077 | 1790 | 0.373832 | 1.47863 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8771.76 | 0.280141 | 51.6642ms | 4300 | 1280 | 2195.47 | 467.5 | 0.30171 | 0.331469 | 1(Win) | true |
| Glaze | 3869.82 | 0.495111 | 115.216ms | 4300 | 320 | 8808.68 | 1059.69 | 0.557185 | 0.767151 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10263 | 0.244442 | 42.8465ms | 4300 | 2560 | 2442.18 | 399.57 | 0.340998 | 0.282537 | 1(Win) | true |
| Glaze | 4554.07 | 0.883767 | 100.197ms | 4300 | 1280 | 81063.1 | 900.469 | 0.500691 | 0.64881 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9869.39 | 1.46077 | 4405.74ms | 466906 | 1280 | 5.5597e+08 | 45116.9 | 0.258725 | 0.307767 | 1(Win) | true |
| simdjson (ondemand) | 8467.79 | 1.47948 | 5394.12ms | 466906 | 320 | 1.93682e+08 | 52584.7 | 0.046926 | 0.35872 | 2(Loss) | true |
| Glaze | 1894.86 | 0.202841 | 6051.18ms | 466906 | 640 | 1.4541e+08 | 234991 | 0.388196 | 1.60385 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10197.4 | 0.658357 | 4389.58ms | 466906 | 2560 | 2.11563e+08 | 43665.5 | 0.0605267 | 0.297603 | 1(Win) | true |
| simdjson (ondemand) | 8927.4 | 0.922809 | 5354.02ms | 466906 | 40 | 8.4741e+06 | 49877.5 | 0.774204 | 0.340221 | 2(Loss) | true |
| Glaze | 1907.49 | 0.0698657 | 6336.47ms | 466906 | 1280 | 3.40465e+07 | 233436 | 2.45306 | 1.59314 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2691.55 | 0.138826 | 6383.76ms | 699405 | 160 | 1.89371e+07 | 247814 | 0.0113505 | 1.12917 | 1(Win) | true |
| Jsonifier | 2591.75 | 0.071486 | 6796.92ms | 699405 | 1280 | 4.33234e+07 | 257357 | 0.219017 | 1.17211 | 2(Loss) | true |
| simdjson (ondemand) | 1480.35 | 0.313792 | 6630.61ms | 767297 | 320 | 7.69897e+08 | 494311 | 0.593625 | 2.05225 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3483.76 | 0.494845 | 9757.93ms | 699405 | 2560 | 2.29794e+09 | 191461 | 0.458653 | 0.872171 | 1(Win) | true |
| Glaze | 2519.13 | 0.720665 | 6724ms | 699405 | 320 | 1.16512e+09 | 264775 | 0.226447 | 1.20604 | 2(Loss) | true |
| simdjson (ondemand) | 1291.13 | 0.767211 | 7264.99ms | 767297 | 320 | 6.05017e+09 | 566753 | 0.317057 | 2.35281 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2724.49 | 0.719756 | 5615.3ms | 631514 | 1280 | 3.24023e+09 | 221054 | 0.447944 | 1.11533 | 1(Win) | true |
| Glaze | 2378.75 | 0.5645 | 7075.42ms | 631514 | 30 | 6.12801e+07 | 253183 | 0.318906 | 1.27747 | 2(Loss) | true |
