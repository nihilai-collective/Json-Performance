# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Windows 10.0.26100 using the MSVC 19.52.37029.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 520.971 | 0.555445 | 168.106ms | 905 | 30 | 2540.23 | 1656.67 | 1.222 | 4.654 | 1(Win) | true |
| Glaze | 504.873 | 0.268608 | 175.457ms | 905 | 4890 | 103105 | 1709.49 | 0.247193 | 4.83077 | 2(Loss) | true |
| simdjson (ondemand) | 155.182 | 0.145968 | 557.531ms | 905 | 4890 | 322286 | 5561.7 | 0.027014 | 15.8538 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 641.692 | 0.592288 | 148.355ms | 905 | 40 | 2538.46 | 1345 | 0.123762 | 3.79003 | 1(Win) | true |
| Glaze | 608.871 | 0.429231 | 152.134ms | 905 | 40 | 1480.77 | 1417.5 | 0.0588235 | 3.99829 | 2(Loss) | true |
| simdjson (ondemand) | 164.67 | 0.105674 | 542.156ms | 905 | 80 | 2454.11 | 5241.25 | 0.023855 | 14.9434 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 948.434 | 0.527895 | 106.712ms | 905 | 40 | 923.077 | 910 | 0.364964 | 2.55887 | 1(Win) | true |
| Glaze | 87.7548 | 0.746724 | 1089.09ms | 905 | 1280 | 6.90376e+06 | 9835.08 | 0.0103276 | 28.1254 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1440.71 | 0.137953 | 71.6939ms | 905 | 320 | 218.554 | 599.062 | 0.15625 | 1.64214 | 1(Win) | true |
| Glaze | 511.76 | 0.370727 | 184.883ms | 905 | 1280 | 50036.1 | 1686.48 | 0.218199 | 4.75956 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 842.233 | 0.198129 | 218.488ms | 1811 | 160 | 2641.12 | 2050.62 | 0.152625 | 2.89953 | 1(Win) | true |
| Glaze | 415.919 | 0.135302 | 401.531ms | 1811 | 80 | 2525.32 | 4152.5 | 0.362538 | 5.91649 | 2(Loss) | true |
| simdjson (ondemand) | 310.351 | 0.137244 | 573.417ms | 1811 | 40 | 2333.33 | 5565 | 0.447227 | 7.94568 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1130.21 | 0.233334 | 160.1ms | 1811 | 160 | 2034.2 | 1528.12 | 0.204918 | 2.15181 | 1(Win) | true |
| Glaze | 474.438 | 0.0754445 | 361.861ms | 1811 | 320 | 2413.7 | 3640.31 | 0.00858516 | 5.17661 | 2(Loss) | true |
| simdjson (ondemand) | 347.04 | 0.157817 | 514.194ms | 1811 | 30 | 1850.57 | 4976.67 | 0.0670241 | 7.0989 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 492.175 | 0.295157 | 401.156ms | 1997 | 1280 | 166968 | 3869.53 | 0.165283 | 4.97492 | 1(Win) | true |
| Glaze | 146.807 | 0.125857 | 1253.55ms | 1798 | 30 | 6482.76 | 11680 | 0.142491 | 16.8088 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 731.089 | 0.0745709 | 271.777ms | 1997 | 160 | 603.774 | 2605 | 0.0479616 | 3.35244 | 1(Win) | true |
| Glaze | 391.224 | 0.210167 | 470.961ms | 1798 | 2560 | 217219 | 4382.93 | 0.2303 | 6.28409 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 545.214 | 0.254259 | 151.613ms | 1313 | 30 | 1022.99 | 2296.67 | 0.291121 | 4.5036 | 1(Win) | true |
| Glaze | 384.103 | 0.240633 | 342.947ms | 1313 | 40 | 2461.54 | 3260 | 0.102145 | 6.37317 | 2(Loss) | true |
| simdjson (ondemand) | 289.583 | 0.126302 | 445.869ms | 1313 | 320 | 9544.57 | 4324.06 | 0.00722648 | 8.48831 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1426.98 | 0.26644 | 92.6409ms | 1313 | 320 | 1749.22 | 877.5 | 0.0711744 | 1.68424 | 1(Win) | true |
| Glaze | 445.218 | 0.188293 | 290.899ms | 1313 | 40 | 1121.79 | 2812.5 | 0.383707 | 5.50535 | 2(Loss) | true |
| simdjson (ondemand) | 331.044 | 0.11302 | 400.164ms | 1313 | 80 | 1462.03 | 3782.5 | 0.263678 | 7.40386 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 603.639 | 0.231158 | 211.179ms | 1313 | 160 | 3678.85 | 2074.38 | 0.150421 | 4.04512 | 1(Win) | true |
| Glaze | 131.049 | 0.124002 | 1083.09ms | 1313 | 40 | 5615.38 | 9555 | 0.226244 | 18.8094 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1314.4 | 0.473333 | 106.427ms | 1313 | 640 | 13013.3 | 952.656 | 0.147396 | 1.83003 | 1(Win) | true |
| Glaze | 726.952 | 0.388196 | 182.248ms | 1313 | 40 | 1788.46 | 1722.5 | 0.241313 | 3.34901 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 647.648 | 0.317884 | 744.187ms | 4215 | 30 | 11678.2 | 6206.67 | 1.16773 | 3.79665 | 1(Win) | true |
| Glaze | 494.838 | 0.127732 | 807.108ms | 4215 | 30 | 3229.89 | 8123.33 | 0.0410509 | 4.98158 | 2(Loss) | true |
| simdjson (ondemand) | 404.502 | 0.17162 | 1025.24ms | 4215 | 40 | 11634.6 | 9937.5 | 0.0921582 | 6.0998 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 999.313 | 0.188564 | 502.716ms | 4215 | 40 | 2301.28 | 4022.5 | 0.0207125 | 2.45518 | 1(Win) | true |
| Glaze | 788.57 | 0.177859 | 631.47ms | 4215 | 80 | 6575.95 | 5097.5 | 0.44335 | 3.12238 | 2(Loss) | true |
| simdjson (ondemand) | 534.362 | 0.100831 | 903.357ms | 4215 | 40 | 2301.28 | 7522.5 | 0.32023 | 4.61719 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 525.818 | 0.20281 | 782.714ms | 4215 | 4890 | 1.17547e+06 | 7644.72 | 0.0853709 | 4.69174 | 1(Win) | true |
| Glaze | 416.409 | 0.184063 | 1142.51ms | 4215 | 30 | 9471.26 | 9653.33 | 0.0345185 | 5.92662 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3527.05 | 0.240353 | 129.506ms | 4215 | 320 | 2401.16 | 1139.69 | 0.463974 | 0.68491 | 1(Win) | true |
| Glaze | 1813.42 | 0.379809 | 267.481ms | 4215 | 30 | 2126.44 | 2216.67 | 0.15015 | 1.34389 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 856.696 | 0.212435 | 141.257ms | 1213 | 320 | 2633.13 | 1350.31 | 0.253924 | 2.83904 | 1(Win) | true |
| Glaze | 337.262 | 0.248094 | 387.269ms | 1213 | 30 | 2172.41 | 3430 | 0.193986 | 7.23842 | 2(Loss) | true |
| simdjson (ondemand) | 267.625 | 0.0766141 | 446.506ms | 1213 | 160 | 1754.72 | 4322.5 | 0.403226 | 9.19083 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1366.54 | 0.4417 | 87.6709ms | 1213 | 2560 | 35791 | 846.523 | 0.0877517 | 1.75648 | 1(Win) | true |
| Glaze | 420.148 | 0.336469 | 281.322ms | 1213 | 30 | 2574.71 | 2753.33 | 0.120919 | 5.79437 | 2(Loss) | true |
| simdjson (ondemand) | 309.307 | 0.20975 | 380.493ms | 1213 | 40 | 2461.54 | 3740 | 0.266667 | 8.01371 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 625.301 | 0.432779 | 185.14ms | 1213 | 40 | 2564.1 | 1850 | 0.180505 | 3.89186 | 1(Win) | true |
| Glaze | 120.001 | 0.0857643 | 987.716ms | 1213 | 80 | 5468.35 | 9640 | 0.258665 | 20.5526 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491 | 0.376967 | 85.4674ms | 1213 | 1280 | 10949.2 | 775.859 | 0.211907 | 1.61001 | 1(Win) | true |
| Glaze | 670.37 | 0.200632 | 193.379ms | 1213 | 160 | 1917.85 | 1725.62 | 0.108774 | 3.63513 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24811.7 | 0.821658 | 1872.86ms | 466906 | 80 | 1.73948e+06 | 17946.2 | 0.651991 | 0.0995658 | 1(Win) | true |
| simdjson (ondemand) | 22794.3 | 0.467866 | 1968.7ms | 466906 | 1280 | 1.0692e+07 | 19534.5 | 0.0495671 | 0.108447 | 2(Loss) | true |
| Glaze | 2002.4 | 0.280714 | 5571.79ms | 466906 | 80 | 3.11727e+07 | 222371 | 0.31748 | 1.23624 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24462.4 | 0.0637027 | 1780.31ms | 466906 | 40 | 5378.21 | 18202.5 | 0.4058 | 0.101106 | 1(Win) | true |
| simdjson (ondemand) | 23228.4 | 0.234691 | 1981.55ms | 466906 | 1280 | 2.59074e+06 | 19169.5 | 0.22834 | 0.106435 | 2(Loss) | true |
| Glaze | 2126.26 | 0.146911 | 5513.01ms | 466906 | 320 | 3.0289e+07 | 209418 | 0.394773 | 1.16426 | 3(Loss) | true |
