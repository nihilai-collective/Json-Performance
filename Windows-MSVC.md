# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Windows 10.0.26100 using the MSVC 19.52.37029.0 compiler).  

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

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 534.515 | 0.131606 | 165.16ms | 905 | 320 | 1445.04 | 1614.69 | 0.213344 | 4.54975 | 1(Win) | true |
| Glaze | 501.037 | 0.426242 | 177.014ms | 905 | 1280 | 69005.1 | 1722.58 | 0.176566 | 4.8621 | 2(Loss) | true |
| simdjson (ondemand) | 161.986 | 0.192556 | 544.072ms | 905 | 2560 | 269461 | 5328.09 | 0.125211 | 15.1879 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 643.823 | 0.284893 | 138.011ms | 905 | 2560 | 37339.3 | 1340.55 | 0.309833 | 3.77168 | 1(Win) | true |
| Glaze | 592.415 | 0.26959 | 149.312ms | 905 | 160 | 2468.16 | 1456.88 | 0.560828 | 4.09608 | 2(Loss) | true |
| simdjson (ondemand) | 166.056 | 0.0481 | 531.371ms | 905 | 40 | 250 | 5197.5 | 0.0480769 | 14.7962 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 886.342 | 0.508376 | 100.976ms | 905 | 80 | 1960.44 | 973.75 | 0.386598 | 2.69256 | 1(Win) | true |
| Glaze | 91.6269 | 0.794761 | 1047.38ms | 905 | 1280 | 7.17356e+06 | 9419.45 | 0.267181 | 26.9278 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1455.98 | 0.4994 | 70.7758ms | 905 | 4890 | 42854.4 | 592.781 | 0.0276736 | 1.61768 | 1(Win) | true |
| Glaze | 317.016 | 0.245608 | 180.661ms | 905 | 40 | 1788.46 | 2722.5 | 0.0919118 | 7.72019 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 833.579 | 0.395508 | 209.659ms | 1811 | 2560 | 171907 | 2071.91 | 0.118635 | 2.93269 | 1(Win) | true |
| Glaze | 414.92 | 0.130854 | 403.002ms | 1811 | 80 | 2373.42 | 4162.5 | 0.180505 | 5.92442 | 2(Loss) | true |
| simdjson (ondemand) | 310.63 | 0.184952 | 551.446ms | 1811 | 30 | 3172.41 | 5560 | 0.120048 | 7.92965 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1132.99 | 0.223365 | 163.864ms | 1811 | 160 | 1854.95 | 1524.38 | 0.123153 | 2.14133 | 1(Win) | true |
| Glaze | 490.829 | 0.124799 | 349.287ms | 1811 | 80 | 1542.72 | 3518.75 | 0.177936 | 4.99971 | 2(Loss) | true |
| simdjson (ondemand) | 369.83 | 0.182219 | 493.721ms | 1811 | 30 | 2172.41 | 4670 | 0.213675 | 6.65187 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 494.672 | 0.227807 | 404.562ms | 1997 | 40 | 3076.92 | 3850 | 0.172861 | 4.9841 | 1(Win) | true |
| Glaze | 130.031 | 0.397686 | 1266.27ms | 1798 | 4890 | 1.34485e+07 | 13186.9 | 0.0371842 | 18.9934 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 759.516 | 0.0833033 | 275.272ms | 1997 | 160 | 698.113 | 2507.5 | 0.0996016 | 3.22625 | 1(Win) | true |
| Glaze | 379.15 | 0.103884 | 457.299ms | 1798 | 80 | 1765.82 | 4522.5 | 0.165563 | 6.49311 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 866.557 | 0.551299 | 151.874ms | 1313 | 40 | 2538.46 | 1445 | 0.115207 | 2.79436 | 1(Win) | true |
| Glaze | 377.128 | 0.174539 | 335.209ms | 1313 | 4890 | 164227 | 3320.29 | 0.0537019 | 6.49265 | 2(Loss) | true |
| simdjson (ondemand) | 287.129 | 0.175085 | 440.737ms | 1313 | 4890 | 285091 | 4361.02 | 0.0812868 | 8.5574 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1487.36 | 0.328107 | 99.0302ms | 1313 | 320 | 2441.61 | 841.875 | 0 | 1.61756 | 1(Win) | true |
| Glaze | 445.614 | 0.198251 | 286.174ms | 1313 | 30 | 931.034 | 2810 | 0 | 5.47314 | 2(Loss) | true |
| simdjson (ondemand) | 328.372 | 0.325529 | 397.221ms | 1313 | 640 | 98618.3 | 3813.28 | 0.0368641 | 7.47819 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 610.073 | 0.273735 | 208.131ms | 1313 | 80 | 2525.32 | 2052.5 | 0 | 4.0021 | 1(Win) | true |
| Glaze | 132.846 | 0.498058 | 952.412ms | 1313 | 2560 | 5.64198e+06 | 9425.74 | 0.101431 | 18.5761 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1355.53 | 0.365341 | 123.099ms | 1313 | 160 | 1822.33 | 923.75 | 0.135135 | 1.76798 | 1(Win) | true |
| Glaze | 736.032 | 0.165126 | 181.308ms | 1313 | 80 | 631.329 | 1701.25 | 0.516987 | 3.30906 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 658.703 | 0.151401 | 634.956ms | 4215 | 80 | 6829.11 | 6102.5 | 0.205255 | 3.73443 | 1(Win) | true |
| Glaze | 516.233 | 0.171233 | 752.714ms | 4215 | 30 | 5333.33 | 7786.67 | 0.17094 | 4.78402 | 2(Loss) | true |
| simdjson (ondemand) | 271.146 | 0.197326 | 1017.25ms | 4215 | 40 | 34230.8 | 14825 | 0.0112435 | 9.11647 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1051.24 | 0.213295 | 488.285ms | 4215 | 4890 | 325283 | 3823.8 | 0.166875 | 2.33747 | 1(Win) | true |
| Glaze | 802.343 | 0.336319 | 604.838ms | 4215 | 30 | 8517.24 | 5010 | 0.199203 | 3.06571 | 2(Loss) | true |
| simdjson (ondemand) | 545.419 | 0.115463 | 869.48ms | 4215 | 30 | 2172.41 | 7370 | 0.135501 | 4.528 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 512.558 | 0.281026 | 766.301ms | 4215 | 40 | 19429.5 | 7842.5 | 0.159642 | 4.8232 | 1(Win) | true |
| Glaze | 415.405 | 0.146007 | 1005.39ms | 4215 | 30 | 5988.51 | 9676.67 | 0.171939 | 5.94182 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3625.39 | 0.327966 | 122.939ms | 4215 | 4890 | 64662.2 | 1108.77 | 0.0478973 | 0.666138 | 1(Win) | true |
| Glaze | 1865.04 | 0.500566 | 244.732ms | 4215 | 640 | 74494.4 | 2155.31 | 0.247093 | 1.3098 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 828.675 | 0.328212 | 141.919ms | 1213 | 4890 | 102653 | 1395.97 | 0.142541 | 2.93007 | 1(Win) | true |
| Glaze | 337.507 | 0.326635 | 342.539ms | 1213 | 1280 | 160432 | 3427.5 | 0.0364564 | 7.22382 | 2(Loss) | true |
| simdjson (ondemand) | 274.45 | 0.0953112 | 429.525ms | 1213 | 80 | 1291.14 | 4215 | 0.118765 | 8.96245 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1394.79 | 0.435531 | 88.3889ms | 1213 | 160 | 2087.66 | 829.375 | 0.0753012 | 1.72776 | 1(Win) | true |
| Glaze | 415.931 | 0.181966 | 283.471ms | 1213 | 80 | 2049.05 | 2781.25 | 0.0449236 | 5.84623 | 2(Loss) | true |
| simdjson (ondemand) | 309.048 | 0.297564 | 381.831ms | 1213 | 1280 | 158796 | 3743.12 | 0.141726 | 7.95691 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 617.375 | 0.264192 | 188.765ms | 1213 | 80 | 1960.44 | 1873.75 | 0.469169 | 3.94191 | 1(Win) | true |
| Glaze | 120.689 | 0.137509 | 961.963ms | 1213 | 40 | 6948.72 | 9585 | 0.0521376 | 20.4404 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.64 | 0.511767 | 94.7013ms | 1213 | 80 | 1291.14 | 785 | 0 | 1.61582 | 1(Win) | true |
| Glaze | 696.347 | 0.116012 | 181.668ms | 1213 | 640 | 2377.15 | 1661.25 | 0.0753012 | 3.49845 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24585.2 | 0.327661 | 1856.1ms | 466906 | 2560 | 9.01567e+06 | 18111.5 | 0.405762 | 0.100536 | 1(Win) | true |
| simdjson (ondemand) | 22005.2 | 0.522164 | 2076.27ms | 466906 | 1280 | 1.429e+07 | 20235.1 | 0.310215 | 0.112342 | 2(Loss) | true |
| Glaze | 1973.7 | 0.824887 | 5748.08ms | 466906 | 80 | 2.77062e+08 | 225605 | 0.0741897 | 1.25421 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25132 | 0.0490361 | 1833.99ms | 466906 | 40 | 3019.23 | 17717.5 | 0.0329133 | 0.0983368 | 1(Win) | true |
| simdjson (ondemand) | 22924.4 | 0.156988 | 1980.64ms | 466906 | 2560 | 2.38034e+06 | 19423.7 | 0.0106598 | 0.107855 | 2(Loss) | true |
| Glaze | 2064.55 | 0.23133 | 5645.75ms | 466906 | 80 | 1.99142e+07 | 215678 | 0.024336 | 1.19911 | 3(Loss) | true |
