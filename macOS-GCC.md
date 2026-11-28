# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [5f487ec](https://github.com/nihilai-collective/Jsonifier/commit/5f487ec)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **simdjson (reflection)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **How the sampling/convergence works (Apple M2 Pro (Virtual)-NEON):**  
> The iterations grow geometrically (100 → 200 → 400 ...) up to a max of 100000.  
> Scores come from a trailing window of `max(iterations/10, 30)` (capped at 100000) over at most 5s.  
> The epoch that counts is whichever one has the lowest (RSE + epoch-over-epoch mean shift).  
> Converged means RSE ≤ 10% and mean shift ≤ 5%. Ties get called using Welch's t-test with Bessel-corrected variance.

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

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2098 | 1.71862 | 43.4519ms | 905 | 4890 | 244430 | 411.38 | 1.90239 | 1(Win) | true |
| Glaze | 1495.47 | 1.24864 | 62.4689ms | 905 | 4890 | 253934 | 577.126 | 2.72794 | 2(Loss) | true |
| simdjson (reflection) | 878.18 | 0.4255 | 98.466ms | 905 | 1280 | 22384 | 982.8 | 0.162536 | 3(Loss) | true |
| simdjson (ondemand) | 424.965 | 1.99837 | 223.781ms | 905 | 30 | 49415.7 | 2030.93 | 0 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1924.36 | 2.23427 | 47.702ms | 905 | 2560 | 257060 | 448.5 | 0.510204 | 1(Win) | true |
| Glaze | 1667.13 | 1.91821 | 54.6601ms | 905 | 2560 | 252457 | 517.7 | 0.798287 | 2(Loss) | true |
| simdjson (reflection) | 981.883 | 0.770463 | 90.7709ms | 905 | 2560 | 117414 | 879 | 0.0909298 | 3(Loss) | true |
| simdjson (ondemand) | 405.847 | 0.511034 | 223.814ms | 905 | 1280 | 151175 | 2126.6 | 2.64604 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1748.18 | 2.14076 | 53.374ms | 905 | 2560 | 285959 | 493.7 | 3.93684 | 1(Win) | true |
| simdjson (reflection) | 220.577 | 0.300628 | 402.345ms | 905 | 1280 | 177111 | 3912.8 | 0.102333 | 2(Loss) | true |
| Glaze | 127.28 | 0.135533 | 680.285ms | 905 | 4890 | 413025 | 6780.91 | 0.431163 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3295.44 | 3.4332 | 35.7458ms | 905 | 2560 | 206971 | 261.9 | 1.09517 | 1(Win) | true |
| simdjson (reflection) | 2719.58 | 2.25648 | 42.092ms | 905 | 4890 | 250765 | 317.356 | 0.0137879 | 2(Loss) | true |
| Glaze | 811.161 | 1.16595 | 125.751ms | 905 | 640 | 98496.3 | 1064 | 1.14068 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 967.24 | 1.05431 | 199.608ms | 1811 | 640 | 226822 | 1785.6 | 2.14818 | 1(Win) | true |
| Glaze | 920.141 | 0.454527 | 193.209ms | 1811 | 2560 | 186333 | 1877 | 0.656293 | 2(Loss) | true |
| simdjson (ondemand) | 298.848 | 1.24775 | 661.851ms | 1811 | 40 | 207993 | 5779.2 | 0.257732 | 3(Loss) | true |
| simdjson (reflection) | 273.761 | 0.674373 | 666.333ms | 1811 | 320 | 579221 | 6308.8 | 0.433011 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1093.38 | 1.6565 | 161.262ms | 1811 | 640 | 438182 | 1579.6 | 0.126454 | 1(Win) | true |
| Glaze | 1039.8 | 0.821388 | 178.781ms | 1811 | 1280 | 238257 | 1661 | 0.823979 | 2(Loss) | true |
| simdjson (reflection) | 282.405 | 0.268871 | 627.936ms | 1811 | 2560 | 692180 | 6115.7 | 1.13324 | 3(Loss) | true |
| simdjson (ondemand) | 279.667 | 0.25815 | 623.88ms | 1811 | 4890 | 1.24282e+06 | 6175.57 | 1.52337 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 311.541 | 0.240939 | 619.078ms | 1997 | 4890 | 1.06084e+06 | 6113.11 | 0.338325 | 1(Win) | true |
| Jsonifier | 308.045 | 0.194182 | 630.28ms | 1997 | 2560 | 368966 | 6182.5 | 0.250081 | 2(Loss) | true |
| Glaze | 204.408 | 0.171986 | 845.817ms | 1798 | 4890 | 1.01784e+06 | 8388.63 | 0.197479 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 1033.25 | 1.60941 | 201.84ms | 1997 | 160 | 140799 | 1843.2 | 0.348432 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1009.17 | 0.396356 | 202.36ms | 1997 | 4890 | 273593 | 1887.18 | 0.886104 | 1(Tie) | true |
| Glaze | 656.071 | 1.03645 | 286.794ms | 1798 | 320 | 234814 | 2613.6 | 0.0919118 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1171.57 | 1.96431 | 112.203ms | 1313 | 160 | 70523.3 | 1068.8 | 0.595238 | 1(Win) | true |
| Glaze | 806.45 | 0.70099 | 166.204ms | 1313 | 2560 | 303276 | 1552.7 | 0.811294 | 2(Loss) | true |
| simdjson (reflection) | 650.717 | 0.447465 | 196.585ms | 1313 | 2560 | 189803 | 1924.3 | 2.68534 | 3(Loss) | true |
| simdjson (ondemand) | 294.754 | 0.373067 | 431.06ms | 1313 | 1280 | 321509 | 4248.2 | 0.631549 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1637.69 | 1.10918 | 80.4009ms | 1313 | 2560 | 184124 | 764.6 | 0.984201 | 1(Win) | true |
| Glaze | 915.868 | 1.72421 | 144.133ms | 1313 | 640 | 355653 | 1367.2 | 1.06446 | 2(Loss) | true |
| simdjson (reflection) | 775.052 | 1.20756 | 166.595ms | 1313 | 640 | 243593 | 1615.6 | 0.17301 | 3(Loss) | true |
| simdjson (ondemand) | 307.448 | 1.15091 | 404.066ms | 1313 | 320 | 703099 | 4072.8 | 0.295508 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 248.576 | 0.436301 | 513.639ms | 1313 | 2560 | 1.23659e+06 | 5037.4 | 2.65141 | 1(Win) | true |
| simdjson (reflection) | 243.709 | 0.419303 | 531.56ms | 1313 | 2560 | 1.18818e+06 | 5138 | 0.0544662 | 2(Loss) | true |
| Glaze | 176.263 | 0.727045 | 852.82ms | 1313 | 40 | 106706 | 7104 | 0.41866 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 2502.35 | 1.98623 | 63.8569ms | 1313 | 2560 | 252892 | 500.4 | 2.7972 | 1(Win) | true |
| Jsonifier | 1993.37 | 1.18584 | 71.9178ms | 1313 | 4890 | 271340 | 628.169 | 1.6783 | 2(Loss) | true |
| Glaze | 803.5 | 2.54949 | 170.743ms | 1313 | 160 | 252571 | 1558.4 | 2.31092 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 836.469 | 1.3078 | 475.372ms | 4215 | 320 | 1.26395e+06 | 4805.6 | 0.720993 | 1(Win) | true |
| simdjson (reflection) | 554.616 | 0.293305 | 713.769ms | 4215 | 4890 | 2.20982e+06 | 7247.78 | 0.146245 | 2(Loss) | true |
| Glaze | 543.142 | 0.473953 | 711.006ms | 4215 | 2560 | 3.14978e+06 | 7400.9 | 0.239733 | 3(Loss) | true |
| simdjson (ondemand) | 437.556 | 0.470446 | 906.671ms | 4215 | 2560 | 4.78176e+06 | 9186.8 | 1.45555 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1504.39 | 2.22771 | 376.223ms | 4215 | 80 | 283454 | 2672 | 0.119904 | 1(Win) | true |
| simdjson (reflection) | 804.291 | 0.255693 | 600.447ms | 4215 | 4890 | 798576 | 4997.86 | 0.324455 | 2(Loss) | true |
| Glaze | 797.21 | 0.338708 | 607.566ms | 4215 | 4890 | 1.4263e+06 | 5042.26 | 0.128235 | 3(Loss) | true |
| simdjson (ondemand) | 640.698 | 0.405921 | 750.267ms | 4215 | 2560 | 1.66039e+06 | 6274 | 0.496556 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 880.492 | 2.08401 | 499.451ms | 4215 | 30 | 271560 | 4565.33 | 0 | 1(Win) | true |
| simdjson (reflection) | 657.56 | 0.287367 | 586.081ms | 4215 | 4890 | 1.50907e+06 | 6113.11 | 0.272236 | 2(Loss) | true |
| Glaze | 514.085 | 0.639199 | 807.222ms | 4215 | 160 | 399685 | 7819.2 | 3.79921 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6542.54 | 1.57819 | 73.1169ms | 4215 | 2560 | 240693 | 614.4 | 0.392157 | 1(Win) | true |
| simdjson (reflection) | 5311.49 | 3.21373 | 92.5041ms | 4215 | 320 | 189292 | 756.8 | 2.87474 | 2(Loss) | true |
| Glaze | 2446.88 | 2.3645 | 183.55ms | 4215 | 640 | 965667 | 1642.8 | 2.72636 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1139.04 | 0.963638 | 109.068ms | 1213 | 1280 | 122598 | 1015.6 | 0.833995 | 1(Win) | true |
| Glaze STATISTICAL TIE | 765.762 | 0.65073 | 157.298ms | 1213 | 4890 | 472547 | 1510.66 | 0.907723 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 723.004 | 5.05153 | 188.48ms | 1213 | 40 | 261304 | 1600 | 0.26738 | 2(Tie) | true |
| simdjson (ondemand) | 238.694 | 1.27363 | 453.335ms | 1213 | 320 | 1.21919e+06 | 4846.4 | 0.980713 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1479.73 | 0.781971 | 76.0141ms | 1213 | 4890 | 182746 | 781.769 | 2.4464 | 1(Win) | true |
| Glaze | 835.419 | 0.639555 | 132.659ms | 1213 | 4890 | 383511 | 1384.7 | 3.01839 | 2(Loss) | true |
| simdjson (reflection) | 640.961 | 2.78592 | 165.994ms | 1213 | 80 | 202249 | 1804.8 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 289.781 | 4.03356 | 429.164ms | 1213 | 160 | 4.14839e+06 | 3992 | 0.438947 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 259.106 | 0.26247 | 458.278ms | 1213 | 4890 | 671484 | 4464.61 | 4.24265 | 1(Win) | true |
| Jsonifier | 222.258 | 0.473552 | 495.319ms | 1213 | 1280 | 777596 | 5204.8 | 0.564186 | 2(Loss) | true |
| Glaze | 147.516 | 0.378157 | 777.101ms | 1213 | 4890 | 4.30029e+06 | 7841.92 | 0.0748754 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2685.88 | 2.28466 | 53.7229ms | 1213 | 2560 | 247874 | 430.7 | 1.07947 | 1(Win) | true |
| simdjson (reflection) | 2406 | 2.92274 | 60.073ms | 1213 | 1280 | 252766 | 480.8 | 1.5561 | 2(Loss) | true |
| Glaze | 680.795 | 3.12831 | 155.173ms | 1213 | 80 | 226047 | 1699.2 | 2.90698 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7918.27 | 0.091592 | 5781.36ms | 466906 | 1280 | 3.39565e+06 | 56234 | 0.035553 | 1(Win) | true |
| simdjson (ondemand) | 7216.7 | 0.271346 | 6224ms | 466906 | 160 | 4.48486e+06 | 61700.8 | 0.325199 | 2(Loss) | true |
| Glaze | 1725.14 | 0.193884 | 6947.07ms | 466906 | 1280 | 3.20558e+08 | 258111 | 2.26378 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7946.51 | 0.0478551 | 5631.95ms | 466906 | 4890 | 3.51618e+06 | 56034.2 | 0.0111721 | 1(Win) | true |
| simdjson (ondemand) | 6788.32 | 0.142015 | 6615.03ms | 466906 | 4890 | 4.24338e+07 | 65594.4 | 0.0305961 | 2(Loss) | true |
| Glaze | 1763.22 | 0.434177 | 6409.74ms | 466906 | 30 | 3.60662e+07 | 252535 | 2.55836 | 3(Loss) | true |
