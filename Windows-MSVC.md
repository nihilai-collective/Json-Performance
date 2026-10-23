# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.44.35228.0 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier: [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| Glaze: [628bec1](https://github.com/stephenberry/glaze/commit/628bec1)  
| Simdjson: [2cc1e70](https://github.com/simdjson/simdjson/commit/2cc1e70)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **Glaze** | utf8: `AVX2`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX2` |

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations scale geometrically (100 → 200 → 400 ...) up to a maximum of 100000.  
> Scores evaluate a trailing window of `max(iterations/10, 30)` (cap: 100000) over at most 5s.  
> Canonical epochs are chosen by minimum (RSE + epoch-over-epoch mean shift).  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Test Variants
* **Standard vs. (Reused):** Standard measures full instantiation, parsing/serialization, and teardown per iteration. `(Reused)` holds the buffer/object across iterations and clears it outside the timed region to isolate raw parse/format throughput.
* **Document Sizes:** "Small" tests cap minified payloads at 5 KiB (via `GenerateSmallJson.py`) to highlight dispatch, setup, and small-allocation latency rather than bulk vector throughput.
* **Key Traversal Order:** Standard tests provide keys in sequential order. Tests labeled `Reverse` parse keys backwards to highlight the $O(N^2)$ penalty inherent to single-pass forward-only decoders (e.g., simdjson On Demand) versus hash/DOM-indexed alternatives.

##### Implementation Details
* **simdjson (ondemand):** Includes the harness mapping layer (`include/common.hpp`). On MSVC, uses `find_field` / `find_field_unordered` due to severe compiler overhead when instantiating `object::for_each`.
* **simdjson (reflection):** Absent from this run; current toolchain lacks P2996 static reflection support.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 461.942 | 0.294726 | 189.567ms | 905 | 4890 | 148275 | 1868.36 | 0.500333 | 6.50832 | 1(Win) | true |
| glaze | 444.035 | 0.169275 | 196.25ms | 905 | 2560 | 27713.5 | 1943.71 | 0.202567 | 6.77662 | 2(Loss) | true |
| jsonifier (two-stage) | 132.753 | 0.192608 | 656.68ms | 905 | 4890 | 766773 | 6501.35 | 0.0303828 | 22.8254 | 3(Loss) | true |
| simdjson (ondemand) | 122.566 | 0.401325 | 706.044ms | 905 | 4890 | 3.90532e+06 | 7041.7 | 0.0335766 | 24.7303 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 535.344 | 0.221783 | 166.661ms | 905 | 1280 | 16364.2 | 1612.19 | 0.13587 | 5.61973 | 1(Win) | true |
| glaze | 518.774 | 0.40953 | 170.931ms | 905 | 4890 | 226997 | 1663.68 | 0.0792203 | 5.79771 | 2(Loss) | true |
| jsonifier (two-stage) | 141.749 | 0.26413 | 620.961ms | 905 | 160 | 41382.1 | 6088.75 | 0.164508 | 21.3793 | 3(Loss) | true |
| simdjson (ondemand) | 130.832 | 0.172458 | 667.666ms | 905 | 2560 | 331338 | 6596.8 | 0.113562 | 23.1664 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1241.83 | 0.566591 | 72.7809ms | 905 | 80 | 1240.51 | 695 | 0.714286 | 2.37902 | 1(Win) | true |
| glaze | 89.4894 | 0.281285 | 1020.3ms | 905 | 4890 | 3.5988e+06 | 9644.44 | 0.240571 | 33.8875 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1894.27 | 0.864765 | 53.19ms | 905 | 160 | 2483.88 | 455.625 | 0.137363 | 1.52968 | 1(Win) | true |
| glaze | 270.198 | 0.169641 | 332.05ms | 905 | 4890 | 143583 | 3194.23 | 0.201412 | 11.1002 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 539.082 | 0.669571 | 319.903ms | 1811 | 2560 | 1.17804e+06 | 3203.79 | 0.0646625 | 5.60143 | 1(Win) | true |
| glaze | 417.679 | 0.184707 | 403.542ms | 1811 | 40 | 2333.33 | 4135 | 0.121065 | 7.25134 | 2(Loss) | true |
| jsonifier (two-stage) | 302.536 | 0.313597 | 573.976ms | 1811 | 640 | 205119 | 5708.75 | 0.142528 | 10.0069 | 3(Loss) | true |
| simdjson (ondemand) | 166.398 | 0.211692 | 1051.57ms | 1811 | 160 | 77244.9 | 10379.4 | 0.114541 | 18.2284 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 684.987 | 0.531805 | 255.89ms | 1811 | 2560 | 460274 | 2521.37 | 0.402728 | 4.38228 | 1(Win) | true |
| glaze | 529.787 | 0.240633 | 334.339ms | 1811 | 40 | 2461.54 | 3260 | 0.102145 | 5.66786 | 2(Loss) | true |
| jsonifier (two-stage) | 345.337 | 0.218341 | 506.49ms | 1811 | 2560 | 305254 | 5001.21 | 0.234084 | 8.75464 | 3(Loss) | true |
| simdjson (ondemand) | 179.533 | 0.0503034 | 983.39ms | 1811 | 80 | 1873.42 | 9620 | 0.0259943 | 16.8848 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 222.776 | 0.119329 | 782.143ms | 1811 | 1280 | 109547 | 7752.66 | 0.405468 | 13.6096 | 1(Win) | true |
| glaze | 140.9 | 0.572675 | 1221.42ms | 1798 | 1280 | 6.21706e+06 | 12169.7 | 0.262609 | 21.5302 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 819.504 | 0.355872 | 224.735ms | 1811 | 40 | 2250 | 2107.5 | 0.676752 | 3.65185 | 1(Win) | true |
| glaze | 318.719 | 0.212849 | 561.857ms | 1798 | 160 | 20981.1 | 5380 | 0.0930233 | 9.48671 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1531.38 | 0.438597 | 245.377ms | 3862 | 2560 | 284859 | 2405.08 | 0.35927 | 1.96924 | 1(Win) | true |
| glaze | 1038.95 | 0.246374 | 364.846ms | 3862 | 40 | 3051.28 | 3545 | 0.234522 | 2.91348 | 2(Loss) | true |
| jsonifier (two-stage) | 555.886 | 0.206181 | 663.01ms | 3862 | 320 | 59717.5 | 6625.62 | 0.0942418 | 5.44957 | 3(Loss) | true |
| simdjson (ondemand) | 378.038 | 0.127683 | 986.928ms | 3862 | 640 | 99038.3 | 9742.66 | 0.180898 | 8.02305 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2012.89 | 0.516688 | 183.419ms | 3862 | 4890 | 437071 | 1829.75 | 0.451883 | 1.48325 | 1(Win) | true |
| glaze | 1304.9 | 0.236906 | 291.392ms | 3862 | 40 | 1788.46 | 2822.5 | 0.265018 | 2.30336 | 2(Loss) | true |
| jsonifier (two-stage) | 620.741 | 0.188171 | 598.419ms | 3862 | 4890 | 609559 | 5933.37 | 0.0107852 | 4.87063 | 3(Loss) | true |
| simdjson (ondemand) | 404.439 | 0.0508644 | 929.099ms | 3862 | 30 | 643.678 | 9106.67 | 0.0366166 | 7.49116 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 525.054 | 0.185269 | 707.044ms | 3862 | 320 | 54046.9 | 7014.69 | 0.00445514 | 5.77224 | 1(Win) | true |
| glaze | 356.198 | 0.366847 | 1050.51ms | 3862 | 4890 | 7.03595e+06 | 10340 | 0.193982 | 8.51221 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4721.91 | 0.952284 | 94.1013ms | 3862 | 30 | 1655.17 | 780 | 0 | 0.622639 | 1(Win) | true |
| glaze | 1099.62 | 0.288324 | 364.499ms | 3862 | 4890 | 456049 | 3349.43 | 0.0248956 | 2.73121 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 973.951 | 0.352354 | 945.584ms | 9578 | 640 | 698899 | 9378.59 | 0.138089 | 3.1131 | 1(Win) | true |
| glaze | 793.489 | 0.155199 | 1159.26ms | 9578 | 4890 | 1.56083e+06 | 11511.6 | 0.295097 | 3.82296 | 2(Loss) | true |
| jsonifier (two-stage) | 698.879 | 0.339109 | 1314.41ms | 9578 | 1280 | 2.5144e+06 | 13069.9 | 0.231984 | 4.34065 | 3(Loss) | true |
| simdjson (ondemand) | 637.624 | 0.138844 | 1441.05ms | 9578 | 4890 | 1.93458e+06 | 14325.5 | 0.358278 | 4.75918 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1685.39 | 0.17446 | 740.175ms | 9578 | 320 | 28608.1 | 5419.69 | 0.190641 | 1.79368 | 1(Win) | true |
| glaze | 1198.19 | 0.569505 | 968.371ms | 9578 | 320 | 603179 | 7623.44 | 0.257584 | 2.52756 | 2(Loss) | true |
| jsonifier (two-stage) | 1035.12 | 0.167606 | 1098.12ms | 9578 | 320 | 69999.6 | 8824.38 | 0.514374 | 2.92961 | 3(Loss) | true |
| simdjson (ondemand) | 880.647 | 0.164009 | 1229.63ms | 9578 | 4890 | 1.41511e+06 | 10372.2 | 0.235778 | 3.44464 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1176.7 | 0.436307 | 779.787ms | 9578 | 2560 | 2.9366e+06 | 7762.66 | 0.345385 | 2.57443 | 1(Win) | true |
| glaze | 909.903 | 0.0929167 | 1047.05ms | 9578 | 80 | 6960.44 | 10038.8 | 0.11194 | 3.33358 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7472.53 | 0.284926 | 139.481ms | 9578 | 2560 | 31054.1 | 1222.38 | 0.556121 | 0.399595 | 1(Win) | true |
| glaze | 2391.96 | 0.286132 | 407.549ms | 9578 | 320 | 38205.3 | 3818.75 | 0.0655093 | 1.25436 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1584.7 | 0.115789 | 243.368ms | 3873 | 2560 | 18645.7 | 2330.78 | 0.563277 | 1.90155 | 1(Win) | true |
| glaze | 1034.14 | 0.149011 | 361.945ms | 3873 | 4890 | 138510 | 3571.64 | 0.379289 | 2.92315 | 2(Loss) | true |
| jsonifier (two-stage) | 575.997 | 0.235956 | 652.248ms | 3873 | 320 | 73260.2 | 6412.5 | 0.165418 | 5.25631 | 3(Loss) | true |
| simdjson (ondemand) | 376.425 | 0.153802 | 984.016ms | 3873 | 4890 | 1.1137e+06 | 9812.25 | 0.232467 | 8.05708 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2012.85 | 0.121239 | 185.363ms | 3873 | 2560 | 12670.6 | 1835 | 0.0255515 | 1.49123 | 1(Win) | true |
| glaze | 1293.32 | 0.164772 | 287.77ms | 3873 | 4890 | 108283 | 2855.89 | 0.0968962 | 2.3192 | 2(Loss) | true |
| jsonifier (two-stage) | 639.054 | 0.207061 | 583.91ms | 3873 | 2560 | 366656 | 5779.77 | 0.136708 | 4.73797 | 3(Loss) | true |
| simdjson (ondemand) | 409.843 | 0.17163 | 918.236ms | 3873 | 320 | 76559.5 | 9012.19 | 0.211967 | 7.39324 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 541.316 | 0.207063 | 709.365ms | 3873 | 30 | 5988.51 | 6823.33 | 0.146771 | 5.59581 | 1(Win) | true |
| glaze | 369.512 | 0.224998 | 1003.79ms | 3873 | 4890 | 2.47345e+06 | 9995.83 | 0.112753 | 8.20562 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5507.67 | 0.380271 | 83.8883ms | 3873 | 320 | 2081.11 | 670.625 | 0 | 0.533681 | 1(Win) | true |
| glaze | 1123.58 | 0.265817 | 352.427ms | 3873 | 640 | 48869.3 | 3287.34 | 0.176174 | 2.68434 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 588.929 | 1.04759 | 5060.89ms | 2090234 | 40 | 5.02928e+10 | 3.38479e+06 | 1.19428 | 5.16055 | 1(Win) | true |
| jsonifier (two-stage) | 567.337 | 0.420677 | 5281.62ms | 2090234 | 80 | 1.74781e+10 | 3.51361e+06 | 0.54837 | 5.35698 | 2(Loss) | true |
| glaze | 385.3 | 0.434534 | 7836.59ms | 2090234 | 80 | 4.04325e+10 | 5.17364e+06 | 0.897212 | 7.88823 | 3(Loss) | true |
| simdjson (ondemand) | 371.702 | 0.274533 | 8078.12ms | 2090234 | 80 | 1.73413e+10 | 5.36291e+06 | 0.16338 | 8.17669 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 711.029 | 0.544525 | 5000.14ms | 2090234 | 80 | 1.86441e+10 | 2.80355e+06 | 0.647323 | 4.27426 | 1(Win) | true |
| jsonifier (two-stage) | 659.834 | 1.01621 | 5317.23ms | 2090234 | 30 | 2.82756e+10 | 3.02107e+06 | 0.361662 | 4.60594 | 2(Loss) | true |
| glaze | 428.279 | 0.386906 | 7809.78ms | 2090234 | 80 | 2.5944e+10 | 4.65445e+06 | 0.0153324 | 7.09662 | 3(Loss) | true |
| simdjson (ondemand) | 409.436 | 0.23997 | 7993.8ms | 2090234 | 80 | 1.09199e+10 | 4.86865e+06 | 1.27121 | 7.42253 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1397.96 | 0.295528 | 9188.5ms | 2090234 | 30 | 5.32741e+08 | 1.42593e+06 | 0.169298 | 2.17367 | 1(Win) | true |
| glaze | 814.334 | 0.168599 | 7569.03ms | 2090234 | 160 | 2.72529e+09 | 2.44789e+06 | 0.0908237 | 3.73189 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1695.17 | 0.27039 | 7405.63ms | 2090234 | 40 | 4.04396e+08 | 1.17593e+06 | 0.17371 | 1.79263 | 1(Win) | true |
| glaze | 1096.28 | 0.199445 | 5659.84ms | 2090234 | 40 | 5.26085e+08 | 1.81834e+06 | 0.10923 | 2.77228 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1698.62 | 0.52322 | 5676.24ms | 6661897 | 40 | 1.5319e+10 | 3.74026e+06 | 0.725222 | 1.78918 | 1(Win) | true |
| jsonifier | 1563.7 | 0.658221 | 6029.93ms | 6661897 | 80 | 5.72169e+10 | 4.06299e+06 | 0.930311 | 1.94349 | 2(Loss) | true |
| simdjson (ondemand) | 1121.66 | 0.338846 | 8544.21ms | 6661897 | 40 | 1.47347e+10 | 5.66418e+06 | 0.35292 | 2.70963 | 3(Loss) | true |
| glaze | 1060.73 | 0.462415 | 9049.5ms | 6661897 | 30 | 2.30127e+10 | 5.98951e+06 | 0.786046 | 2.86523 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1943.63 | 0.501409 | 5675.2ms | 6661897 | 80 | 2.14903e+10 | 3.26877e+06 | 0.335306 | 1.56359 | 1(Win) | true |
| jsonifier | 1833.43 | 0.693746 | 6045.85ms | 6661897 | 30 | 1.73376e+10 | 3.46524e+06 | 0.576416 | 1.65759 | 2(Loss) | true |
| simdjson (ondemand) | 1229.77 | 0.257496 | 8511.21ms | 6661897 | 80 | 1.41572e+10 | 5.16623e+06 | 0.775558 | 2.47126 | 3(Loss) | true |
| glaze | 1149.12 | 0.523937 | 9133.21ms | 6661897 | 30 | 2.51737e+10 | 5.52884e+06 | 0.284001 | 2.64491 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3139.78 | 0.138555 | 6287.62ms | 6661897 | 160 | 1.25766e+09 | 2.02348e+06 | 0.688616 | 0.967896 | 1(Win) | true |
| glaze | 1402.22 | 0.155609 | 6792.55ms | 6661897 | 80 | 3.97673e+09 | 4.53089e+06 | 0.104282 | 2.16739 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5196.09 | 0.247726 | 7717.37ms | 6661897 | 80 | 7.33967e+08 | 1.2227e+06 | 0.0282241 | 0.584755 | 1(Win) | true |
| glaze | 3080.58 | 0.111447 | 6409.6ms | 6661897 | 160 | 8.45256e+08 | 2.06237e+06 | 0.0878678 | 0.986452 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1858.79 | 0.193878 | 6543.44ms | 500299 | 1280 | 3.17003e+08 | 256684 | 0.0401597 | 1.63486 | 1(Win) | true |
| jsonifier (two-stage) | 1329.14 | 0.165524 | 9182.35ms | 500299 | 640 | 2.25952e+08 | 358970 | 0.0147971 | 2.28628 | 2(Loss) | true |
| glaze | 919.8 | 0.249805 | 6617.34ms | 500299 | 320 | 5.37312e+08 | 518724 | 0.166177 | 3.30411 | 3(Loss) | true |
| simdjson (ondemand) | 516.764 | 0.190765 | 5864.17ms | 500299 | 160 | 4.96352e+08 | 923288 | 0.0625767 | 5.88098 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2271.1 | 0.120118 | 6265.05ms | 500299 | 1280 | 8.15103e+07 | 210084 | 0.267871 | 1.33804 | 1(Win) | true |
| jsonifier (two-stage) | 1553.52 | 0.420648 | 8872.49ms | 500299 | 30 | 5.00708e+07 | 307123 | 0.0889188 | 1.95611 | 2(Loss) | true |
| glaze | 1029.91 | 0.16773 | 6340.37ms | 500299 | 640 | 3.86424e+08 | 463265 | 0.0893577 | 2.95088 | 3(Loss) | true |
| simdjson (ondemand) | 551.83 | 0.1746 | 5682.75ms | 500299 | 320 | 7.29272e+08 | 864619 | 0.194284 | 5.50747 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8821.3 | 0.227229 | 5447.74ms | 500299 | 40 | 604199 | 54087.5 | 0.0107838 | 0.344351 | 1(Win) | true |
| glaze | 4434.83 | 0.244845 | 5522.4ms | 500299 | 2560 | 1.77634e+08 | 107585 | 0.0684671 | 0.685074 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8892.05 | 0.133811 | 5399.14ms | 500299 | 2560 | 1.31971e+07 | 53657.2 | 0.00232955 | 0.341641 | 1(Win) | true |
| glaze | 4978.96 | 0.13299 | 9618.73ms | 500299 | 2560 | 4.15776e+07 | 95827.7 | 0.518739 | 0.610142 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3215.2 | 0.15038 | 5447.11ms | 1439562 | 320 | 1.3194e+08 | 426995 | 0.0182266 | 0.945132 | 1(Win) | true |
| jsonifier | 2946.31 | 0.139784 | 5949.16ms | 1439562 | 320 | 1.3576e+08 | 465963 | 0.0998945 | 1.03136 | 2(Loss) | true |
| glaze | 2012.47 | 0.279645 | 8702.71ms | 1439562 | 80 | 2.91143e+08 | 682184 | 0.24927 | 1.51007 | 3(Loss) | true |
| simdjson (ondemand) | 1384.33 | 0.331818 | 6285.45ms | 1439562 | 30 | 3.24867e+08 | 991727 | 0.0517884 | 2.1953 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3626.69 | 0.160342 | 5295.89ms | 1439562 | 640 | 2.35785e+08 | 378548 | 0.0777039 | 0.837852 | 1(Win) | true |
| jsonifier | 3281.71 | 0.132524 | 5791.78ms | 1439562 | 640 | 1.96711e+08 | 418341 | 0.0157592 | 0.925976 | 2(Loss) | true |
| glaze | 2187.32 | 0.214058 | 8417.61ms | 1439562 | 640 | 1.15526e+09 | 627652 | 0.04862 | 1.38935 | 3(Loss) | true |
| simdjson (ondemand) | 1443.18 | 0.119182 | 6216.31ms | 1439562 | 320 | 4.11334e+08 | 951286 | 0.270021 | 2.10583 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4531.27 | 0.132395 | 7782.25ms | 1439562 | 1280 | 2.05956e+08 | 302978 | 0.172723 | 0.670265 | 1(Win) | true |
| glaze | 1953.19 | 0.154377 | 8991.43ms | 1439584 | 320 | 3.76792e+08 | 702899 | 0.250439 | 1.55553 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15649.3 | 0.1462 | 8831.25ms | 1439562 | 1280 | 2.1056e+07 | 87727.6 | 0.229305 | 0.194097 | 1(Win) | true |
| glaze | 7403.14 | 0.206917 | 9475.81ms | 1439584 | 1280 | 1.88471e+08 | 185448 | 0.0464464 | 0.41029 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1225.42 | 0.0932108 | 4397.96ms | 56369 | 4890 | 8.17619e+06 | 43868.7 | 0.0520305 | 2.47872 | 1(Win) | true |
| glaze | 1210.31 | 0.230347 | 4474.83ms | 56369 | 640 | 6.69941e+06 | 44416.6 | 0.0794398 | 2.50976 | 2(Loss) | true |
| jsonifier (two-stage) | 1078.27 | 0.118734 | 4994.62ms | 56369 | 1280 | 4.48523e+06 | 49855.4 | 0.00391743 | 2.81735 | 3(Loss) | true |
| simdjson (ondemand) | 605.579 | 0.462847 | 8877.03ms | 56369 | 160 | 2.70105e+07 | 88770.6 | 0.0513701 | 5.01741 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1997.62 | 0.15211 | 3153.06ms | 56369 | 4890 | 8.19368e+06 | 26910.9 | 0.526188 | 1.51922 | 1(Win) | true |
| jsonifier | 1793.87 | 0.167989 | 3470.71ms | 56369 | 1280 | 3.24393e+06 | 29967.5 | 0.156665 | 1.69299 | 2(Loss) | true |
| jsonifier (two-stage) | 1503.36 | 0.185756 | 4052.68ms | 56369 | 1280 | 5.6474e+06 | 35758.4 | 0.274312 | 2.02023 | 3(Loss) | true |
| simdjson (ondemand) | 754.896 | 0.135267 | 7549.09ms | 56369 | 1280 | 1.18768e+07 | 71212 | 0.0469328 | 4.02469 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10262.2 | 0.175393 | 538.203ms | 56369 | 320 | 27013.2 | 5238.44 | 0.857582 | 0.294793 | 1(Win) | true |
| glaze | 4397.4 | 0.430531 | 1213.92ms | 56369 | 4890 | 1.35459e+07 | 12224.9 | 0.082546 | 0.689684 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10777.5 | 0.165524 | 503.488ms | 56369 | 640 | 43626.5 | 4987.97 | 0.29048 | 0.28062 | 1(Win) | true |
| glaze | 5037.28 | 0.212996 | 1078.94ms | 56369 | 2560 | 1.32273e+06 | 10672 | 0.619476 | 0.600607 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1747.46 | 0.231074 | 5164.06ms | 94370 | 1280 | 1.81286e+07 | 51502.3 | 0.0335128 | 1.73846 | 1(Win) | true |
| jsonifier (two-stage) | 1706.18 | 0.0754111 | 5281.91ms | 94370 | 4890 | 7.73748e+06 | 52748.5 | 0.0811136 | 1.78052 | 2(Loss) | true |
| jsonifier | 1463.93 | 0.0761162 | 6157.36ms | 94370 | 4890 | 1.07075e+07 | 61477.1 | 0.144708 | 2.07529 | 3(Loss) | true |
| simdjson (ondemand) | 987.699 | 0.0614563 | 9143.02ms | 94370 | 4890 | 1.53342e+07 | 91119.1 | 0.103445 | 3.0764 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2652.16 | 0.12352 | 3841.7ms | 94370 | 2560 | 4.49762e+06 | 33933.9 | 0.146293 | 1.14491 | 1(Win) | true |
| jsonifier (two-stage) | 2310.54 | 0.115019 | 4356.25ms | 94370 | 2560 | 5.13833e+06 | 38951.2 | 0.0464539 | 1.31463 | 2(Loss) | true |
| jsonifier | 1896.89 | 0.110162 | 5229.32ms | 94370 | 2560 | 6.99339e+06 | 47445.1 | 0.00922034 | 1.60138 | 3(Loss) | true |
| simdjson (ondemand) | 1208.87 | 0.094478 | 7848.72ms | 94370 | 4890 | 2.41924e+07 | 74448.2 | 0.144348 | 2.51332 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12536.3 | 0.19086 | 719.661ms | 94370 | 4890 | 918057 | 7179.04 | 0.182282 | 0.241555 | 1(Win) | true |
| glaze | 4327.51 | 0.163482 | 2095.85ms | 94370 | 4890 | 5.65254e+06 | 20796.8 | 0.94132 | 0.701432 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13233.1 | 0.23876 | 690.606ms | 94370 | 2560 | 675001 | 6800.98 | 0.0728913 | 0.228794 | 1(Win) | true |
| glaze | 5300.25 | 0.548135 | 1729.79ms | 94370 | 80 | 693013 | 16980 | 0.74162 | 0.57177 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1510.7 | 0.153289 | 776.84ms | 11812 | 30 | 3919.54 | 7456.67 | 0.356347 | 2.00645 | 1(Win) | true |
| jsonifier (two-stage) | 1198.78 | 0.189289 | 945.309ms | 11812 | 320 | 101244 | 9396.88 | 0.390884 | 2.53018 | 2(Loss) | true |
| glaze | 950.14 | 0.539251 | 1183.19ms | 11812 | 320 | 1.30799e+06 | 11855.9 | 0.108185 | 3.19189 | 3(Loss) | true |
| simdjson (ondemand) | 502.865 | 0.272267 | 2279.84ms | 11812 | 80 | 297593 | 22401.2 | 0.431518 | 6.03969 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1720.69 | 0.159338 | 759.273ms | 11812 | 30 | 3264.37 | 6546.67 | 0.101937 | 1.75842 | 1(Win) | true |
| jsonifier (two-stage) | 1349.94 | 0.234662 | 935.551ms | 11812 | 2560 | 981629 | 8344.69 | 0.322888 | 2.2454 | 2(Loss) | true |
| glaze | 1128.28 | 0.308341 | 1089.39ms | 11812 | 2560 | 2.42613e+06 | 9984.02 | 0.478429 | 2.68739 | 3(Loss) | true |
| simdjson (ondemand) | 533.956 | 0.116655 | 2222ms | 11812 | 4890 | 2.96179e+06 | 21096.9 | 0.18428 | 5.68585 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7860.73 | 0.671354 | 142.562ms | 11812 | 1280 | 118477 | 1433.05 | 0.136478 | 0.381053 | 1(Win) | true |
| glaze | 3322.49 | 0.272369 | 343.3ms | 11812 | 4890 | 417009 | 3390.47 | 0.133873 | 0.908137 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9383.06 | 0.208824 | 122.872ms | 11812 | 1280 | 8045.05 | 1200.55 | 1.15142 | 0.317042 | 1(Win) | true |
| glaze | 3894.49 | 0.259291 | 294.454ms | 11812 | 40 | 2250 | 2892.5 | 0.0865052 | 0.770541 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2846.06 | 0.159908 | 1056.48ms | 31235 | 2560 | 717097 | 10466.4 | 0.247204 | 1.06591 | 1(Win) | true |
| jsonifier | 2440.42 | 0.176158 | 1226.84ms | 31235 | 4890 | 2.26083e+06 | 12206.1 | 0.148394 | 1.24311 | 2(Loss) | true |
| glaze | 1919.84 | 0.108828 | 1558.35ms | 31235 | 4890 | 1.39427e+06 | 15515.9 | 0.0541558 | 1.58075 | 3(Loss) | true |
| simdjson (ondemand) | 1242.73 | 0.122392 | 2408.79ms | 31235 | 2560 | 2.20331e+06 | 23969.7 | 0.356435 | 2.44316 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3253.15 | 0.12483 | 1053.59ms | 31235 | 30 | 3919.54 | 9156.67 | 0.0728597 | 0.931867 | 1(Win) | true |
| jsonifier | 2702.32 | 0.183814 | 1213.04ms | 31235 | 160 | 65688.3 | 11023.1 | 0.30141 | 1.12282 | 2(Loss) | true |
| glaze | 2164.57 | 0.484098 | 1474.13ms | 31235 | 1280 | 5.6809e+06 | 13761.6 | 0.106273 | 1.40214 | 3(Loss) | true |
| simdjson (ondemand) | 1321.92 | 0.132333 | 2359.12ms | 31235 | 4890 | 4.34826e+06 | 22533.9 | 0.0681635 | 2.2968 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13822.7 | 0.369665 | 227.4ms | 31235 | 40 | 2538.46 | 2155 | 0.0772798 | 0.218589 | 1(Win) | true |
| glaze | 5441.82 | 0.255664 | 548.532ms | 31235 | 4890 | 957728 | 5473.91 | 1.58025 | 0.555984 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14613.2 | 0.202299 | 209.992ms | 31235 | 640 | 10883.3 | 2038.44 | 0.0765931 | 0.205491 | 1(Win) | true |
| glaze | 6493.74 | 0.212344 | 468.642ms | 31235 | 1280 | 121446 | 4587.19 | 0.760572 | 0.46323 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2082.1 | 0.149924 | 4969.9ms | 108313 | 640 | 3.54061e+06 | 49611.1 | 0.106251 | 1.45901 | 1(Win) | true |
| glaze | 1493.03 | 0.143093 | 6902.12ms | 108313 | 4890 | 4.79256e+07 | 69185.1 | 0.145476 | 2.03494 | 2(Loss) | true |
| jsonifier (two-stage) | 1475.82 | 0.121887 | 6997.53ms | 108313 | 2560 | 1.86315e+07 | 69991.7 | 0.125451 | 2.05867 | 3(Loss) | true |
| simdjson (ondemand) | 679.45 | 0.143266 | 7805.38ms | 108313 | 1280 | 6.07219e+07 | 152028 | 0.0683936 | 4.47248 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2670.65 | 0.181964 | 4120.23ms | 108313 | 1280 | 6.34026e+06 | 38678 | 0.355547 | 1.13733 | 1(Win) | true |
| glaze | 1868.25 | 0.0887244 | 5795.78ms | 108313 | 4890 | 1.17676e+07 | 55289.9 | 0.107172 | 1.62613 | 2(Loss) | true |
| jsonifier (two-stage) | 1753.08 | 0.107293 | 6134.8ms | 108313 | 4890 | 1.9544e+07 | 58922.3 | 0.157457 | 1.73296 | 3(Loss) | true |
| simdjson (ondemand) | 747.421 | 0.0780598 | 7198.32ms | 108313 | 2560 | 2.97938e+07 | 138202 | 0.106728 | 4.0658 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12234 | 0.167334 | 866.301ms | 108313 | 30 | 5988.51 | 8443.33 | 0.0394633 | 0.247238 | 1(Win) | true |
| glaze | 4117.88 | 0.191106 | 2523.7ms | 108313 | 2560 | 5.88306e+06 | 25084.6 | 1.86951 | 0.737295 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12564.4 | 0.194567 | 827.94ms | 108313 | 2560 | 655025 | 8221.29 | 0.329134 | 0.241014 | 1(Win) | true |
| glaze | 4460.98 | 0.460409 | 2291.58ms | 108313 | 320 | 3.63696e+06 | 23155.3 | 0.316149 | 0.680007 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2669.17 | 0.483806 | 7816.63ms | 213963 | 40 | 5.47179e+06 | 76447.5 | 0.040349 | 1.13852 | 1(Win) | true |
| jsonifier | 2225.22 | 0.378845 | 9302.2ms | 213963 | 160 | 1.93097e+07 | 91699.4 | 0.0852695 | 1.36542 | 2(Loss) | true |
| glaze | 2193.95 | 0.0794417 | 9312.28ms | 213963 | 4890 | 2.6695e+07 | 93006.2 | 0.0112415 | 1.38493 | 3(Loss) | true |
| simdjson (ondemand) | 1260.58 | 0.07016 | 8305.98ms | 213963 | 2560 | 3.30182e+07 | 161870 | 0.0135399 | 2.41072 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3103.16 | 0.0948083 | 6901.11ms | 213963 | 4890 | 1.90051e+07 | 65755.8 | 0.61906 | 0.978971 | 1(Win) | true |
| glaze | 2582.5 | 0.0583655 | 8188.41ms | 213963 | 4890 | 1.03997e+07 | 79013.1 | 0.00724078 | 1.17654 | 2(Loss) | true |
| jsonifier | 2524.15 | 0.265352 | 8460.51ms | 213963 | 160 | 7.36228e+06 | 80839.4 | 0.477825 | 1.20374 | 3(Loss) | true |
| simdjson (ondemand) | 1384.86 | 0.19091 | 7693.52ms | 213963 | 320 | 2.53203e+07 | 147344 | 0.206571 | 2.19436 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15936.8 | 0.245802 | 1311.52ms | 213963 | 160 | 158476 | 12803.8 | 0.00976372 | 0.190347 | 1(Win) | true |
| glaze | 4617.97 | 0.200876 | 4460.79ms | 213963 | 4890 | 3.8525e+07 | 44186.3 | 1.29021 | 0.657772 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 16124 | 0.262434 | 1267.62ms | 213963 | 2560 | 2.82365e+06 | 12655.1 | 0.0503385 | 0.188112 | 1(Win) | true |
| glaze | 5531.52 | 0.280326 | 3709.82ms | 213963 | 2560 | 2.7375e+07 | 36888.8 | 0.747583 | 0.548755 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 493.699 | 0.845548 | 5267.85ms | 1834197 | 80 | 7.18015e+10 | 3.5431e+06 | 0.412102 | 6.15572 | 1(Win) | true |
| jsonifier (two-stage) | 455.667 | 0.215271 | 5796.5ms | 1834197 | 30 | 2.04875e+09 | 3.83883e+06 | 0.018933 | 6.66975 | 2(Loss) | true |
| glaze | 312.889 | 0.256582 | 8432.95ms | 1834197 | 80 | 1.64609e+10 | 5.59056e+06 | 0.328358 | 9.71372 | 3(Loss) | true |
| simdjson (ondemand) | 36.7704 | 0.113454 | 14266.2ms | 1834197 | 30 | 8.73891e+10 | 4.75716e+07 | 0.0116793 | 82.6616 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 542.823 | 0.61161 | 5227.99ms | 1834197 | 30 | 1.16532e+10 | 3.22246e+06 | 0.0871729 | 5.59885 | 1(Win) | true |
| jsonifier (two-stage) | 492.071 | 0.222631 | 5780.58ms | 1834197 | 80 | 5.01067e+09 | 3.55483e+06 | 0.0112862 | 6.17638 | 2(Loss) | true |
| glaze | 329.938 | 0.554637 | 8402.28ms | 1834197 | 40 | 3.45863e+10 | 5.30168e+06 | 0.0100607 | 9.2118 | 3(Loss) | true |
| simdjson (ondemand) | 36.6085 | 0.147508 | 14317.2ms | 1834197 | 30 | 1.49033e+11 | 4.7782e+07 | 0.739853 | 83.0262 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 884.762 | 0.17313 | 6125.95ms | 1834197 | 160 | 1.87457e+09 | 1.97706e+06 | 0.158028 | 3.43484 | 1(Win) | true |
| glaze | 673.934 | 0.299005 | 8067.13ms | 1833577 | 80 | 4.81517e+09 | 2.59467e+06 | 0.389089 | 4.50955 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1021.64 | 0.200015 | 5334.45ms | 1834197 | 30 | 3.51842e+08 | 1.71218e+06 | 0.225324 | 2.97455 | 1(Win) | true |
| glaze | 736.583 | 0.242672 | 7361.88ms | 1833577 | 160 | 5.31025e+09 | 2.37398e+06 | 0.45207 | 4.12605 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2188.27 | 0.272318 | 6503.51ms | 9930848 | 80 | 1.11125e+10 | 4.32798e+06 | 0.0916683 | 1.38887 | 1(Win) | true |
| jsonifier | 2019.32 | 0.441697 | 7020.94ms | 9930848 | 40 | 1.71661e+10 | 4.6901e+06 | 0.103125 | 1.5051 | 2(Loss) | true |
| glaze | 1372.89 | 0.545559 | 10274.8ms | 9930848 | 40 | 5.6656e+10 | 6.89845e+06 | 0.372759 | 2.21371 | 3(Loss) | true |
| simdjson (ondemand) | 194.8 | 0.174186 | 14564.3ms | 9930848 | 30 | 2.15152e+11 | 4.86181e+07 | 0.0889554 | 15.6031 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2352.25 | 0.282923 | 6501.96ms | 9930848 | 30 | 3.89281e+09 | 4.02627e+06 | 0.150074 | 1.29201 | 1(Win) | true |
| jsonifier | 2182.52 | 0.203535 | 6940.14ms | 9930848 | 80 | 6.24057e+09 | 4.33939e+06 | 0.0812529 | 1.39252 | 2(Loss) | true |
| glaze | 1453.31 | 0.481849 | 10137.8ms | 9930848 | 30 | 2.95799e+10 | 6.51669e+06 | 1.00488 | 2.09123 | 3(Loss) | true |
| simdjson (ondemand) | 195.517 | 0.215649 | 14691ms | 9930848 | 30 | 3.27356e+11 | 4.84397e+07 | 0.708383 | 15.5459 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3230.26 | 0.543263 | 9584.59ms | 9930848 | 30 | 7.61095e+09 | 2.9319e+06 | 0.165696 | 0.94081 | 1(Win) | true |
| glaze | 1920.11 | 0.464792 | 7705.96ms | 9930228 | 30 | 1.57653e+10 | 4.9321e+06 | 0.799306 | 1.58285 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5056.49 | 0.251529 | 5836.86ms | 9930848 | 80 | 1.77558e+09 | 1.873e+06 | 0.318349 | 0.600972 | 1(Win) | true |
| glaze | 3327.51 | 0.243661 | 8837.22ms | 9930228 | 160 | 7.69436e+09 | 2.84603e+06 | 0.0342904 | 0.913235 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 512.869 | 0.576087 | 5122.6ms | 1834197 | 30 | 1.15818e+10 | 3.41067e+06 | 1.14162 | 5.92583 | 1(Win) | true |
| jsonifier (two-stage) | 466.039 | 0.153303 | 5680.71ms | 1834197 | 40 | 1.32436e+09 | 3.75339e+06 | 1.43372 | 6.52139 | 2(Loss) | true |
| glaze | 310.221 | 0.787094 | 8488.33ms | 1834197 | 30 | 5.90912e+10 | 5.63864e+06 | 0.238318 | 9.79728 | 3(Loss) | true |
| simdjson (ondemand) | 261.146 | 0.402682 | 10079.2ms | 1834197 | 40 | 2.91011e+10 | 6.69827e+06 | 0.643229 | 11.6385 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 554.96 | 0.299517 | 5146.47ms | 1834197 | 80 | 7.13022e+09 | 3.15199e+06 | 0.485213 | 5.47644 | 1(Win) | true |
| jsonifier (two-stage) | 497.98 | 0.188777 | 5722.67ms | 1834197 | 80 | 3.51768e+09 | 3.51264e+06 | 0.0605658 | 6.10312 | 2(Loss) | true |
| glaze | 323.634 | 0.462413 | 8562.23ms | 1834197 | 40 | 2.49864e+10 | 5.40495e+06 | 0.2466 | 9.39115 | 3(Loss) | true |
| simdjson (ondemand) | 271.713 | 0.260126 | 10143.5ms | 1834197 | 30 | 8.41319e+09 | 6.43777e+06 | 0.523104 | 11.1858 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 900.045 | 0.194198 | 6135.3ms | 1834197 | 40 | 5.6979e+08 | 1.94349e+06 | 0.292557 | 3.37645 | 1(Win) | true |
| glaze | 603.036 | 0.145262 | 9008.44ms | 1833577 | 160 | 2.8388e+09 | 2.89972e+06 | 0.749797 | 5.03974 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 992.539 | 0.415988 | 5395.12ms | 1834197 | 80 | 4.29981e+09 | 1.76238e+06 | 0.00340438 | 3.06174 | 1(Win) | true |
| glaze | 755.856 | 0.328136 | 7209.77ms | 1833577 | 40 | 2.30509e+09 | 2.31345e+06 | 0.401586 | 4.02089 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2230.01 | 0.159088 | 6403.09ms | 9930848 | 80 | 3.65193e+09 | 4.24697e+06 | 0.0688547 | 1.36288 | 1(Win) | true |
| jsonifier | 2052.15 | 0.214287 | 6967.11ms | 9930848 | 80 | 7.82408e+09 | 4.61505e+06 | 0.0711224 | 1.48102 | 2(Loss) | true |
| glaze | 1383.54 | 0.736461 | 10343.4ms | 9930848 | 30 | 7.62453e+10 | 6.84535e+06 | 0.424707 | 2.19674 | 3(Loss) | true |
| simdjson (ondemand) | 1282.75 | 0.568169 | 5153.46ms | 9930848 | 40 | 7.0389e+10 | 7.3832e+06 | 0.115883 | 2.36942 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2395.26 | 0.493526 | 6359.39ms | 9930848 | 30 | 1.14237e+10 | 3.95397e+06 | 1.66814 | 1.26885 | 1(Win) | true |
| jsonifier | 2220.55 | 0.153417 | 6840.52ms | 9930848 | 30 | 1.28447e+09 | 4.26508e+06 | 0.387001 | 1.36869 | 2(Loss) | true |
| glaze | 1459.24 | 0.295934 | 10279.3ms | 9930848 | 80 | 2.95121e+10 | 6.49022e+06 | 0.495893 | 2.08281 | 3(Loss) | true |
| simdjson (ondemand) | 1342.04 | 0.420516 | 5129.36ms | 9930848 | 30 | 2.64196e+10 | 7.05699e+06 | 0.50144 | 2.26471 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3056.42 | 0.173711 | 9683.43ms | 9930848 | 40 | 1.15895e+09 | 3.09866e+06 | 0.665138 | 0.994345 | 1(Win) | true |
| glaze DID NOT CONVERGE | 1356.19 | 0.231699 | 10863.1ms | 9930228 | 40 | 1.0471e+10 | 6.98295e+06 | 3.85981 | 2.24104 | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4965.72 | 0.291316 | 5925.18ms | 9930848 | 30 | 9.26105e+08 | 1.90724e+06 | 0.0166062 | 0.611937 | 1(Win) | true |
| glaze | 3357.13 | 0.192417 | 8737.15ms | 9930228 | 160 | 4.71398e+09 | 2.82092e+06 | 0.855457 | 0.905221 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 935.39 | 0.242811 | 8364.97ms | 642697 | 80 | 2.02514e+08 | 655260 | 0.522241 | 3.24889 | 1(Win) | true |
| jsonifier (two-stage) | 817.099 | 0.0599456 | 9580.96ms | 642697 | 640 | 1.29407e+08 | 750122 | 0.0721653 | 3.71929 | 2(Loss) | true |
| glaze | 698.844 | 0.183406 | 5529.16ms | 642697 | 320 | 8.27997e+08 | 877053 | 0.0466188 | 4.34856 | 3(Loss) | true |
| simdjson (ondemand) | 447.826 | 0.25515 | 8702.69ms | 642697 | 40 | 4.87804e+08 | 1.36866e+06 | 0.287409 | 6.78641 | 4(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 979.929 | 0.138665 | 8385.63ms | 642697 | 640 | 4.81436e+08 | 625477 | 0.030861 | 3.10113 | 1(Win) | true |
| jsonifier (two-stage) | 855.381 | 0.151482 | 9590.97ms | 642697 | 160 | 1.88511e+08 | 716551 | 0.145438 | 3.55279 | 2(Loss) | true |
| glaze | 788.837 | 0.110589 | 5114.68ms | 642697 | 320 | 2.36272e+08 | 776997 | 0.191637 | 3.85276 | 3(Loss) | true |
| simdjson (ondemand) | 478.667 | 0.127341 | 8297.13ms | 642697 | 160 | 4.25403e+08 | 1.28048e+06 | 0.266473 | 6.34928 | 4(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1472.92 | 0.099612 | 5298.5ms | 642697 | 640 | 1.09966e+08 | 416129 | 0.487915 | 2.06279 | 1(Win) | true |
| glaze | 927.339 | 0.200071 | 8308.62ms | 642692 | 640 | 1.11912e+09 | 660943 | 0.363446 | 3.27599 | 2(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1874.61 | 0.169116 | 8372.68ms | 642697 | 160 | 4.8919e+07 | 326960 | 0.0848008 | 1.62117 | 1(Win) | true |
| glaze | 1309.61 | 0.213504 | 5956.29ms | 642692 | 80 | 7.98782e+07 | 468018 | 0.046451 | 2.32071 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1473.28 | 0.162988 | 5028.7ms | 1225964 | 160 | 2.67679e+08 | 793583 | 0.0207087 | 2.06277 | 1(Win) | true |
| glaze | 1239.35 | 0.161204 | 5965.91ms | 1225964 | 320 | 7.40066e+08 | 943375 | 0.474214 | 2.45207 | 2(Loss) | true |
| jsonifier | 1205.14 | 0.0788021 | 6134.86ms | 1225964 | 320 | 1.87028e+08 | 970154 | 0.345142 | 2.52181 | 3(Loss) | true |
| simdjson (ondemand) | 833.089 | 0.283383 | 8879.99ms | 1225964 | 80 | 1.26535e+09 | 1.40342e+06 | 0.107443 | 3.64799 | 4(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1550.1 | 0.0808419 | 10030.7ms | 1225964 | 640 | 2.37952e+08 | 754256 | 0.354121 | 1.96049 | 1(Win) | true |
| glaze | 1373.34 | 0.134655 | 5579.42ms | 1225964 | 320 | 4.20529e+08 | 851332 | 0.325954 | 2.2129 | 2(Loss) | true |
| jsonifier | 1244.72 | 0.153042 | 6129.57ms | 1225964 | 320 | 6.61279e+08 | 939306 | 0.488471 | 2.4415 | 3(Loss) | true |
| simdjson (ondemand) | 888.012 | 0.207459 | 8510.41ms | 1225964 | 160 | 1.19372e+09 | 1.31662e+06 | 0.133665 | 3.42242 | 4(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2342.58 | 0.0951189 | 6310.8ms | 1225964 | 640 | 1.44238e+08 | 499095 | 0.445908 | 1.29676 | 1(Win) | true |
| glaze | 1541.3 | 0.152196 | 9868.69ms | 1225970 | 160 | 2.13261e+08 | 758564 | 0.814437 | 1.97114 | 2(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3447.22 | 0.366209 | 8544.3ms | 1225964 | 640 | 9.87311e+08 | 339163 | 0.103533 | 0.881431 | 1(Win) | true |
| glaze | 2186.5 | 0.0889315 | 6843.06ms | 1225970 | 640 | 1.44728e+08 | 534724 | 0.0712476 | 1.38991 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 967.021 | 0.656465 | 5095.44ms | 409725 | 80 | 5.62893e+08 | 404070 | 0.591245 | 3.14264 | 1(Win) | true |
| jsonifier (two-stage) | 897.566 | 0.1719 | 5564.7ms | 409725 | 640 | 3.58415e+08 | 435338 | 0.247257 | 3.38561 | 2(Loss) | true |
| glaze | 821.902 | 0.154414 | 6104.14ms | 409725 | 320 | 1.72452e+08 | 475414 | 0.437432 | 3.69749 | 3(Loss) | true |
| simdjson (ondemand) | 519.325 | 0.303108 | 9609.09ms | 409725 | 40 | 2.08047e+08 | 752408 | 0.0745941 | 5.85177 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1445.44 | 0.116869 | 8441.73ms | 409725 | 640 | 6.388e+07 | 270329 | 0.406524 | 2.10252 | 1(Win) | true |
| jsonifier (two-stage) | 1261 | 0.164412 | 9397.25ms | 409725 | 640 | 1.66114e+08 | 309870 | 0.151246 | 2.41007 | 2(Loss) | true |
| glaze | 1085.14 | 0.303611 | 5314.29ms | 409725 | 640 | 7.64946e+08 | 360088 | 0.673483 | 2.80058 | 3(Loss) | true |
| simdjson (ondemand) | 633.427 | 0.28745 | 8612.28ms | 409725 | 80 | 2.5154e+08 | 616874 | 0.251645 | 4.79795 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3437.09 | 0.210371 | 5846.91ms | 409725 | 2560 | 1.46425e+08 | 113685 | 0.579321 | 0.883431 | 1(Win) | true |
| glaze | 2749.76 | 0.149009 | 7302.53ms | 409725 | 1280 | 5.73889e+07 | 142101 | 0.109417 | 1.10502 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9018.48 | 0.0790757 | 4379.71ms | 409725 | 4890 | 5.74003e+06 | 43327.1 | 0.0605445 | 0.336787 | 1(Win) | true |
| glaze | 2952.97 | 0.36729 | 6839.77ms | 409725 | 160 | 3.77926e+07 | 132322 | 0.138111 | 1.02897 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1589.15 | 0.141597 | 6032.12ms | 785750 | 640 | 2.85316e+08 | 471542 | 0.00523575 | 1.91227 | 1(Win) | true |
| jsonifier | 1390.72 | 0.165651 | 6884.19ms | 785750 | 320 | 2.54936e+08 | 538822 | 0.265808 | 2.18526 | 2(Loss) | true |
| glaze | 1342.38 | 0.176027 | 7163.96ms | 785750 | 320 | 3.08975e+08 | 558223 | 1.19491 | 2.26388 | 3(Loss) | true |
| simdjson (ondemand) | 949.947 | 0.187697 | 10067ms | 785750 | 320 | 7.01511e+08 | 788833 | 0.0871177 | 3.19914 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2190.11 | 0.489667 | 5075.97ms | 785750 | 160 | 4.49116e+08 | 342151 | 0.0398374 | 1.38752 | 1(Win) | true |
| jsonifier | 1852.74 | 0.131436 | 5919.89ms | 785750 | 320 | 9.04311e+07 | 404455 | 0.0670332 | 1.64029 | 2(Loss) | true |
| glaze | 1699.61 | 1.00266 | 6341.75ms | 785750 | 40 | 7.81699e+08 | 440895 | 0.480492 | 1.78806 | 3(Loss) | true |
| simdjson (ondemand) | 1146.77 | 0.141125 | 9076.82ms | 785750 | 640 | 5.4426e+08 | 653445 | 0.572719 | 2.64998 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4160.1 | 0.228405 | 9160.94ms | 785750 | 640 | 1.08331e+08 | 180128 | 0.409999 | 0.730022 | 1(Win) | true |
| glaze | 2193.99 | 0.114585 | 8665.36ms | 785750 | 1280 | 1.96049e+08 | 341546 | 0.601468 | 1.38417 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12847.3 | 0.133428 | 5871.09ms | 785750 | 1280 | 7.75256e+06 | 58327.3 | 0.0112499 | 0.236432 | 1(Win) | true |
| glaze | 4461.81 | 0.131703 | 8591.76ms | 785750 | 2560 | 1.2525e+08 | 167948 | 0.193602 | 0.681018 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 6025.92 | 0.200472 | 4258.97ms | 264040 | 640 | 4.49139e+06 | 41787.5 | 0.0388721 | 0.504084 | 1(Win) | true |
| jsonifier | 5953.13 | 0.24252 | 4231.47ms | 264040 | 2560 | 2.69392e+07 | 42298.5 | 0.0652486 | 0.51025 | 2(Loss) | true |
| glaze | 2247.55 | 0.141509 | 5755.63ms | 264040 | 2560 | 6.43472e+07 | 112037 | 0.231147 | 1.35198 | 3(Loss) | true |
| simdjson (ondemand) | 1946.08 | 0.0957256 | 6687.5ms | 264040 | 1280 | 1.96374e+07 | 129392 | 0.149033 | 1.5615 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6448.9 | 0.508772 | 4161.58ms | 264040 | 30 | 1.18395e+06 | 39046.7 | 0.127888 | 0.470815 | 1(Win) | true |
| jsonifier (two-stage) | 6317.55 | 0.096191 | 4149.3ms | 264040 | 4890 | 7.18819e+06 | 39858.5 | 0.693353 | 0.480781 | 2(Loss) | true |
| glaze | 2340.54 | 0.280395 | 5606.74ms | 264040 | 640 | 5.82409e+07 | 107585 | 0.511353 | 1.29814 | 3(Loss) | true |
| simdjson (ondemand) | 2000.97 | 0.280176 | 6566.87ms | 264040 | 30 | 3.72944e+06 | 125843 | 0.220334 | 1.51873 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 7547.93 | 0.140969 | 5080.6ms | 399947 | 640 | 3.24769e+06 | 50533 | 0.202319 | 0.402489 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 7541.59 | 0.0725887 | 5078.19ms | 399947 | 4890 | 6.59061e+06 | 50575.4 | 0.265488 | 0.402818 | 1(Tie) | true |
| glaze | 3312.86 | 0.156244 | 5915.25ms | 399947 | 1280 | 4.14205e+07 | 115133 | 0.443773 | 0.917244 | 3(Loss) | true |
| simdjson (ondemand) | 2752.29 | 0.198944 | 7098.79ms | 399947 | 40 | 3.04046e+06 | 138582 | 0.247733 | 1.10407 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 7896.88 | 0.290537 | 4966.32ms | 399947 | 40 | 787692 | 48300 | 0.0897976 | 0.384614 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 7860.35 | 0.191457 | 4980.29ms | 399947 | 4890 | 4.22058e+07 | 48524.5 | 0.0516024 | 0.386419 | 1(Tie) | true |
| glaze | 3410.48 | 0.312354 | 5750.99ms | 399947 | 640 | 7.80998e+07 | 111838 | 0.00391208 | 0.890892 | 3(Loss) | true |
| simdjson (ondemand) | 2826.03 | 0.328324 | 6992.48ms | 399947 | 80 | 1.57088e+07 | 134966 | 0.132265 | 1.07529 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1379.99 | 0.134987 | 9381.58ms | 264040 | 640 | 3.88286e+07 | 182471 | 0.109743 | 2.20214 | 1(Win) | true |
| glaze | 1222.87 | 0.173804 | 5274.24ms | 264040 | 320 | 4.09874e+07 | 205917 | 0.0159323 | 2.48514 | 2(Loss) | true |
| jsonifier (two-stage) | 1212.8 | 0.27409 | 5327.74ms | 264040 | 160 | 5.18166e+07 | 207626 | 0.158287 | 2.50571 | 3(Loss) | true |
| simdjson (ondemand) | 814.482 | 0.273994 | 8101.92ms | 264040 | 160 | 1.1481e+08 | 309164 | 0.425934 | 3.73128 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1961.46 | 0.121872 | 7571.33ms | 264040 | 2560 | 6.26652e+07 | 128378 | 0.054861 | 1.54923 | 1(Win) | true |
| glaze | 1688.34 | 0.115496 | 8626.09ms | 264040 | 2560 | 7.59623e+07 | 149146 | 0.00285488 | 1.79989 | 2(Loss) | true |
| jsonifier (two-stage) | 1622.85 | 0.308464 | 8976.12ms | 264040 | 2560 | 5.86448e+08 | 155164 | 0.674143 | 1.87248 | 3(Loss) | true |
| simdjson (ondemand) | 1002.33 | 0.499811 | 7070.28ms | 264040 | 30 | 4.72991e+07 | 251223 | 0.681299 | 3.03193 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14185 | 0.414064 | 1805.79ms | 264040 | 1280 | 6.91554e+06 | 17751.7 | 0.27562 | 0.213962 | 1(Win) | true |
| glaze | 4380.13 | 0.857608 | 5796.82ms | 263923 | 30 | 7.28585e+06 | 57463.3 | 1.82243 | 0.693536 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14389.8 | 0.16771 | 1753.12ms | 264040 | 2560 | 2.20491e+06 | 17499.1 | 0.00691952 | 0.210753 | 1(Win) | true |
| glaze | 5203.49 | 0.181895 | 4826.98ms | 263923 | 4890 | 3.78545e+07 | 48370.7 | 0.936415 | 0.58362 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1741.52 | 0.442501 | 5593.71ms | 399947 | 40 | 3.75695e+07 | 219015 | 0.128772 | 1.74501 | 1(Win) | true |
| glaze | 1598.61 | 0.159151 | 6148.17ms | 399947 | 320 | 4.61414e+07 | 238594 | 0.145564 | 1.90101 | 2(Loss) | true |
| jsonifier | 1487.82 | 0.296391 | 6627.73ms | 399947 | 80 | 4.61875e+07 | 256361 | 0.318434 | 2.04264 | 3(Loss) | true |
| simdjson (ondemand) | 1188.26 | 0.233481 | 8266.36ms | 399947 | 160 | 8.98681e+07 | 320990 | 0.0943286 | 2.5576 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2346.99 | 0.208602 | 9295.15ms | 399947 | 1280 | 1.47106e+08 | 162514 | 0.059742 | 1.29478 | 1(Win) | true |
| glaze | 2097.71 | 0.704282 | 5188.86ms | 399947 | 80 | 1.31189e+08 | 181826 | 0.0350732 | 1.44866 | 2(Loss) | true |
| jsonifier | 1901.53 | 0.25942 | 5634.86ms | 399947 | 160 | 4.33237e+07 | 200585 | 0.0973102 | 1.59818 | 3(Loss) | true |
| simdjson (ondemand) | 1449.13 | 0.191142 | 7239.89ms | 399947 | 320 | 8.09938e+07 | 263205 | 0.0346808 | 2.09717 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15389.9 | 0.308894 | 2489.95ms | 399947 | 160 | 937722 | 24783.8 | 0.17119 | 0.19729 | 1(Win) | true |
| glaze | 3481.06 | 0.386679 | 5615.5ms | 399830 | 1280 | 2.29636e+08 | 109538 | 0.807997 | 0.872895 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15612.6 | 0.120956 | 2465.65ms | 399947 | 4890 | 4.26988e+06 | 24430.2 | 0.00676121 | 0.194375 | 1(Win) | true |
| glaze | 3963.07 | 0.200203 | 9662.22ms | 399830 | 4890 | 1.81442e+08 | 96215.3 | 0.205981 | 0.766629 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 575.182 | 0.215063 | 783.322ms | 4630 | 2560 | 697785 | 7676.72 | 0.0366502 | 5.26944 | 1(Win) | true |
| jsonifier (two-stage) | 545.545 | 0.13276 | 823.197ms | 4630 | 4890 | 564606 | 8093.76 | 0.160299 | 5.55566 | 2(Loss) | true |
| glaze STATISTICAL TIE | 339.833 | 0.313942 | 1303.43ms | 4630 | 2560 | 4.25959e+06 | 12993.2 | 0.0833464 | 8.928 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 337.384 | 0.340186 | 1349.8ms | 4630 | 80 | 158576 | 13087.5 | 0.038219 | 8.99041 | 3(Tie) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 716.15 | 0.418783 | 753.544ms | 4630 | 160 | 106673 | 6165.62 | 0.39378 | 4.2308 | 1(Win) | true |
| jsonifier (two-stage) | 678.918 | 0.378765 | 796.92ms | 4630 | 160 | 97092.8 | 6503.75 | 0.459154 | 4.46118 | 2(Loss) | true |
| glaze | 380.6 | 0.209269 | 1300.01ms | 4630 | 2560 | 1.50894e+06 | 11601.4 | 0.283038 | 7.96854 | 3(Loss) | true |
| simdjson (ondemand) | 377.502 | 0.166424 | 1336.74ms | 4630 | 30 | 11367.8 | 11696.7 | 0.847697 | 8.04113 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2021.12 | 0.343686 | 225.21ms | 4630 | 320 | 18040.7 | 2184.69 | 0.836879 | 1.49155 | 1(Win) | true |
| glaze | 1114.33 | 0.494168 | 401.685ms | 4630 | 4890 | 1.87495e+06 | 3962.47 | 0.505648 | 2.71534 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1985.73 | 0.328019 | 224.951ms | 4630 | 4890 | 260152 | 2223.62 | 0.138378 | 1.51068 | 1(Win) | true |
| glaze | 1191.96 | 0.246662 | 375.027ms | 4630 | 4890 | 408277 | 3704.42 | 0.384333 | 2.52877 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1609.1 | 0.279711 | 878.732ms | 14795 | 2560 | 1.54e+06 | 8768.63 | 0.213841 | 1.88351 | 1(Win) | true |
| jsonifier | 1514.31 | 0.143207 | 943.566ms | 14795 | 40 | 7121.79 | 9317.5 | 0.0982845 | 2.00433 | 2(Loss) | true |
| simdjson (ondemand) | 1004.91 | 0.219213 | 1420.56ms | 14795 | 640 | 606297 | 14040.6 | 0.104717 | 3.01826 | 3(Loss) | true |
| glaze | 901.495 | 0.301889 | 1553.04ms | 14795 | 4890 | 1.09171e+07 | 15651.3 | 0.425077 | 3.36602 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1969.85 | 0.124774 | 851.399ms | 14795 | 4890 | 390592 | 7162.78 | 0.268031 | 1.53827 | 1(Win) | true |
| jsonifier | 1805.38 | 0.174004 | 923.439ms | 14795 | 640 | 118357 | 7815.31 | 0.00399872 | 1.67928 | 2(Loss) | true |
| simdjson (ondemand) | 1104.37 | 0.153954 | 1421.22ms | 14795 | 4890 | 1.89187e+06 | 12776.2 | 0.175159 | 2.74661 | 3(Loss) | true |
| glaze | 1018.35 | 0.125759 | 1522.58ms | 14795 | 4890 | 1.48463e+06 | 13855.3 | 0.225386 | 2.97834 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5953.42 | 0.359056 | 250.823ms | 14795 | 30 | 2172.41 | 2370 | 0.565771 | 0.505123 | 1(Win) | true |
| glaze | 2931.53 | 0.256425 | 485.752ms | 14795 | 2560 | 389943 | 4813.05 | 0.0502937 | 1.03188 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6021.51 | 0.250802 | 239.616ms | 14795 | 1280 | 44207.1 | 2343.2 | 0.428258 | 0.498549 | 1(Win) | true |
| glaze | 3229.41 | 0.20472 | 442.285ms | 14795 | 4890 | 391213 | 4369.1 | 0.108988 | 0.934881 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 997.02 | 0.155107 | 495.867ms | 5092 | 160 | 9131.68 | 4870.62 | 0.115355 | 3.03604 | 1(Win) | true |
| jsonifier (two-stage) | 845.46 | 0.520876 | 582.745ms | 5092 | 80 | 71606 | 5743.75 | 0.454939 | 3.57946 | 2(Loss) | true |
| glaze | 681.347 | 0.18111 | 720.899ms | 5092 | 4890 | 814769 | 7127.22 | 0.144792 | 4.44556 | 3(Loss) | true |
| simdjson (ondemand) | 475.088 | 0.242951 | 1023.52ms | 5092 | 2560 | 1.57872e+06 | 10221.5 | 0.0519469 | 6.3821 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1341.93 | 0.190984 | 461.527ms | 5092 | 80 | 3821.2 | 3618.75 | 0.652025 | 2.24789 | 1(Win) | true |
| jsonifier (two-stage) | 1052.74 | 0.255844 | 553.203ms | 5092 | 320 | 44568.9 | 4612.81 | 0.0203197 | 2.87324 | 2(Loss) | true |
| glaze | 843.349 | 0.201183 | 668.338ms | 5092 | 320 | 42943.2 | 5758.12 | 0.195759 | 3.58816 | 3(Loss) | true |
| simdjson (ondemand) | 536.777 | 0.125903 | 995.016ms | 5092 | 2560 | 332127 | 9046.8 | 0.924033 | 5.64653 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7617.43 | 0.425187 | 67.776ms | 5092 | 320 | 2351.1 | 637.5 | 0.293255 | 0.388768 | 1(Win) | true |
| glaze | 3482.89 | 0.404224 | 142.699ms | 5092 | 4890 | 155328 | 1394.27 | 0.251138 | 0.857199 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8066.21 | 0.371627 | 62.2552ms | 5092 | 1280 | 6407.13 | 602.031 | 0.234131 | 0.365246 | 1(Win) | true |
| glaze | 4479.1 | 0.612994 | 112.772ms | 5092 | 4890 | 215982 | 1084.17 | 0.988966 | 0.662294 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1767.29 | 0.232489 | 640.208ms | 11724 | 320 | 69229.5 | 6326.56 | 0.21285 | 1.71391 | 1(Win) | true |
| jsonifier | 1590.35 | 0.148799 | 713.177ms | 11724 | 640 | 70040.5 | 7030.47 | 0.10902 | 1.90421 | 2(Loss) | true |
| glaze | 1311.32 | 0.149988 | 861.181ms | 11724 | 1280 | 209341 | 8526.41 | 0.31967 | 2.31149 | 3(Loss) | true |
| simdjson (ondemand) | 1047.95 | 0.295602 | 1068.75ms | 11724 | 4890 | 4.86399e+06 | 10669.3 | 0.126895 | 2.89363 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2180.69 | 0.264195 | 605.823ms | 11724 | 2560 | 469735 | 5127.23 | 0.0631948 | 1.38688 | 1(Win) | true |
| jsonifier | 1915.97 | 0.445403 | 673.815ms | 11724 | 160 | 108094 | 5835.62 | 0.0321199 | 1.57836 | 2(Loss) | true |
| glaze | 1546 | 0.257017 | 809.857ms | 11724 | 4890 | 1.68953e+06 | 7232.15 | 0.14079 | 1.95816 | 3(Loss) | true |
| simdjson (ondemand) | 1176.13 | 0.183836 | 1037.1ms | 11724 | 4890 | 1.49352e+06 | 9506.5 | 0.527482 | 2.57779 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12714.6 | 0.457792 | 91.8289ms | 11724 | 640 | 10372.1 | 879.375 | 0.177368 | 0.234189 | 1(Win) | true |
| glaze | 4560.84 | 0.345309 | 251.541ms | 11746 | 640 | 46034.8 | 2456.09 | 0.209497 | 0.658945 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15539.1 | 0.344549 | 75.4227ms | 11724 | 2560 | 15734.1 | 719.531 | 0.205873 | 0.190828 | 1(Win) | true |
| glaze | 5861.77 | 0.281212 | 196.982ms | 11746 | 4890 | 141221 | 1911 | 1.10445 | 0.508293 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1146.92 | 0.595028 | 407.133ms | 4857 | 2560 | 1.47837e+06 | 4038.63 | 0.315284 | 2.63547 | 1(Win) | true |
| glaze | 1010.47 | 0.334033 | 463.764ms | 4857 | 4890 | 1.14651e+06 | 4584.01 | 0.0250388 | 2.9921 | 2(Loss) | true |
| jsonifier (two-stage) | 974.724 | 0.260895 | 479.052ms | 4857 | 2560 | 393501 | 4752.11 | 0.00164398 | 3.10643 | 3(Loss) | true |
| simdjson (ondemand) | 634.023 | 0.262868 | 734.828ms | 4857 | 4890 | 1.80348e+06 | 7305.73 | 0.308706 | 4.77883 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1813.58 | 0.37959 | 303.462ms | 4857 | 320 | 30077.5 | 2554.06 | 0.20757 | 1.65373 | 1(Win) | true |
| jsonifier | 1649.5 | 0.141107 | 336.16ms | 4857 | 160 | 2512.19 | 2808.12 | 0.0222519 | 1.8334 | 2(Loss) | true |
| jsonifier (two-stage) | 1312.65 | 0.202866 | 410.39ms | 4857 | 80 | 4099.68 | 3528.75 | 0.317797 | 2.30433 | 3(Loss) | true |
| simdjson (ondemand) | 825.599 | 0.530106 | 601.613ms | 4857 | 1280 | 1.13223e+06 | 5610.47 | 0.161268 | 3.66961 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9621.8 | 0.514488 | 50.4878ms | 4857 | 640 | 3926.03 | 481.406 | 0.620509 | 0.304775 | 1(Win) | true |
| glaze | 3553.96 | 0.448043 | 128.428ms | 4857 | 30 | 1022.99 | 1303.33 | 0 | 0.844685 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10845 | 0.275015 | 46.3508ms | 4857 | 2560 | 3532.09 | 427.109 | 0.238357 | 0.269344 | 1(Win) | true |
| glaze | 4864.98 | 0.336599 | 99.5318ms | 4857 | 1280 | 13146.4 | 952.109 | 0.0901787 | 0.606585 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1370.87 | 0.301348 | 514.266ms | 7376 | 320 | 76512.5 | 5131.25 | 0.428135 | 2.20762 | 1(Win) | true |
| glaze | 1343.81 | 0.377972 | 525.318ms | 7376 | 4890 | 1.91422e+06 | 5234.58 | 0.223076 | 2.2515 | 2(Loss) | true |
| jsonifier | 1291.49 | 0.260144 | 563.505ms | 7376 | 30 | 6022.99 | 5446.67 | 0.2442 | 2.34018 | 3(Loss) | true |
| simdjson (ondemand) | 942.254 | 0.182206 | 746.486ms | 7376 | 4890 | 904771 | 7465.4 | 0.355997 | 3.21539 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2312.01 | 0.260175 | 360.214ms | 7376 | 40 | 2506.41 | 3042.5 | 0.0822368 | 1.3047 | 1(Win) | true |
| jsonifier (two-stage) | 1905.02 | 0.142712 | 423.183ms | 7376 | 80 | 2221.52 | 3692.5 | 0.135227 | 1.58715 | 2(Loss) | true |
| jsonifier | 1560.58 | 0.707771 | 498.409ms | 7376 | 40 | 40711.5 | 4507.5 | 0.389755 | 1.93291 | 3(Loss) | true |
| simdjson (ondemand) | 1224.31 | 0.127886 | 618.106ms | 7376 | 4890 | 264006 | 5745.5 | 0.10471 | 2.47432 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11682.8 | 0.160146 | 62.2395ms | 7376 | 4890 | 4546.6 | 602.106 | 0.110671 | 0.251847 | 1(Win) | true |
| glaze | 3812.95 | 0.264302 | 193.123ms | 7376 | 640 | 15215.9 | 1844.84 | 0.463665 | 0.785981 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13523.4 | 0.317316 | 54.5785ms | 7376 | 1280 | 3487.07 | 520.156 | 0.0901984 | 0.216592 | 1(Win) | true |
| glaze | 4508.4 | 0.195054 | 159.884ms | 7376 | 4890 | 45291.4 | 1560.27 | 0.217798 | 0.660658 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1347.27 | 0.569017 | 316.158ms | 4390 | 40 | 12506.4 | 3107.5 | 0.187366 | 2.24986 | 1(Win) | true |
| jsonifier (two-stage) | 1070.77 | 0.390638 | 393.248ms | 4390 | 4890 | 1.14075e+06 | 3909.92 | 0.0949147 | 2.82288 | 2(Loss) | true |
| glaze | 939.408 | 0.844946 | 473.815ms | 4390 | 30 | 42540.2 | 4456.67 | 0.223881 | 3.21606 | 3(Loss) | true |
| simdjson (ondemand) | 495.173 | 0.281989 | 848.435ms | 4390 | 4890 | 2.77963e+06 | 8454.89 | 0.134219 | 6.12169 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1665.77 | 0.315393 | 307.093ms | 4390 | 30 | 1885.06 | 2513.33 | 0 | 1.81282 | 1(Win) | true |
| jsonifier (two-stage) | 1240.25 | 0.241239 | 383.357ms | 4390 | 640 | 42440.9 | 3375.62 | 0.0462663 | 2.4368 | 2(Loss) | true |
| glaze | 1138.81 | 0.263054 | 423.883ms | 4390 | 4890 | 457324 | 3676.32 | 0.693496 | 2.65414 | 3(Loss) | true |
| simdjson (ondemand) | 550.397 | 0.16167 | 820.187ms | 4390 | 2560 | 387147 | 7606.56 | 0.179031 | 5.50422 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7771.01 | 1.01739 | 52.1729ms | 4390 | 80 | 2403.48 | 538.75 | 0.691244 | 0.378531 | 1(Win) | true |
| glaze | 3369.52 | 0.346302 | 125.282ms | 4390 | 160 | 2962.26 | 1242.5 | 0 | 0.887116 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9754.07 | 0.419142 | 45.5455ms | 4390 | 640 | 2071.38 | 429.219 | 0.471014 | 0.297496 | 1(Win) | true |
| glaze | 3858.09 | 0.279898 | 110.75ms | 4390 | 2560 | 23617 | 1085.16 | 0.480046 | 0.766622 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2596.79 | 0.195252 | 429.708ms | 11521 | 640 | 43679.6 | 4231.09 | 0.00369303 | 1.16361 | 1(Win) | true |
| jsonifier | 2227.1 | 0.248093 | 496.561ms | 11521 | 640 | 95875.5 | 4933.44 | 0.460277 | 1.35814 | 2(Loss) | true |
| glaze | 1856.49 | 0.546384 | 595.314ms | 11521 | 4890 | 5.11332e+06 | 5918.32 | 0.896407 | 1.63163 | 3(Loss) | true |
| simdjson (ondemand) | 1246.25 | 0.261112 | 899.226ms | 11521 | 320 | 169578 | 8816.25 | 0.479752 | 2.43141 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3075.52 | 0.186149 | 424.925ms | 11521 | 80 | 3537.97 | 3572.5 | 0.487465 | 0.983763 | 1(Win) | true |
| jsonifier | 2508.79 | 0.203547 | 487.808ms | 11521 | 4890 | 388588 | 4379.51 | 0.0789316 | 1.20629 | 2(Loss) | true |
| glaze | 2221.06 | 0.148431 | 538.19ms | 11521 | 4890 | 263644 | 4946.87 | 0.381187 | 1.36136 | 3(Loss) | true |
| simdjson (ondemand) | 1362.62 | 0.513181 | 880.093ms | 11521 | 30 | 51367.8 | 8063.33 | 0 | 2.22337 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15808.8 | 0.216919 | 72.3325ms | 11521 | 4890 | 11114.4 | 695.01 | 1.06066 | 0.186869 | 1(Win) | true |
| glaze | 5208.79 | 0.167066 | 217.203ms | 11521 | 160 | 1987.03 | 2109.38 | 0.324867 | 0.578213 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 18531.7 | 0.185108 | 62.0087ms | 11521 | 2560 | 3083.47 | 592.891 | 0.0658415 | 0.159079 | 1(Win) | true |
| glaze | 6690.48 | 0.214258 | 169.055ms | 11521 | 2560 | 31694.1 | 1642.23 | 0.64048 | 0.444736 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2089.86 | 0.128054 | 219.083ms | 4669 | 320 | 2382.05 | 2130.62 | 0.471559 | 1.44313 | 1(Win) | true |
| jsonifier (two-stage) | 1421.17 | 0.27112 | 316.878ms | 4669 | 4890 | 352848 | 3133.13 | 0.399427 | 2.1241 | 2(Loss) | true |
| glaze | 1318.24 | 0.151417 | 342.481ms | 4669 | 2560 | 66965.7 | 3377.77 | 0.0520135 | 2.28995 | 3(Loss) | true |
| simdjson (ondemand) | 650.378 | 0.195554 | 691.366ms | 4669 | 4890 | 876515 | 6846.34 | 0.113837 | 4.65755 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2395.94 | 0.155929 | 211.263ms | 4669 | 320 | 2687.21 | 1858.44 | 0.585089 | 1.25881 | 1(Win) | true |
| glaze | 1605.91 | 0.166501 | 296.722ms | 4669 | 4890 | 104219 | 2772.7 | 0.583904 | 1.87185 | 2(Loss) | true |
| jsonifier (two-stage) | 1562.52 | 0.246224 | 309.361ms | 4669 | 1280 | 63017.9 | 2849.69 | 0.120482 | 1.93045 | 3(Loss) | true |
| simdjson (ondemand) | 729.802 | 0.195691 | 623.489ms | 4669 | 640 | 91234.7 | 6101.25 | 0.0153633 | 4.15158 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8846.43 | 0.662252 | 47.6091ms | 4669 | 30 | 333.333 | 503.333 | 0 | 0.327679 | 1(Win) | true |
| glaze | 3237.23 | 1.04087 | 134.031ms | 4669 | 640 | 131181 | 1375.47 | 1.347 | 0.922487 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11386.4 | 0.454837 | 41.2593ms | 4669 | 2560 | 8098.93 | 391.055 | 0.288845 | 0.253634 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3769.24 | 0.841505 | 112.275ms | 4669 | 1280 | 126492 | 1181.33 | 9.27037 | 0.784553 | -(Loss) | false |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2531.88 | 0.247069 | 351.228ms | 9249 | 4890 | 362283 | 3483.78 | 0.0617988 | 1.19317 | 1(Win) | true |
| jsonifier | 2030.04 | 0.201012 | 439.875ms | 9249 | 40 | 3051.28 | 4345 | 0.114943 | 1.48928 | 2(Loss) | true |
| glaze | 1982.98 | 0.305554 | 455.15ms | 9249 | 160 | 29556.2 | 4448.12 | 0.070205 | 1.5264 | 3(Loss) | true |
| simdjson (ondemand) | 1210.99 | 0.657335 | 719.542ms | 9249 | 160 | 366778 | 7283.75 | 0.120275 | 2.50079 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2750.51 | 0.310277 | 340.333ms | 9249 | 640 | 63364.2 | 3206.88 | 0.205058 | 1.09856 | 1(Win) | true |
| glaze | 2315.1 | 0.291077 | 414.001ms | 9249 | 30 | 3689.66 | 3810 | 0.26178 | 1.29955 | 2(Loss) | true |
| jsonifier | 2143.83 | 0.314702 | 432.268ms | 9249 | 320 | 53648.5 | 4114.38 | 0.62672 | 1.40878 | 3(Loss) | true |
| simdjson (ondemand) | 1396.74 | 0.189019 | 650.872ms | 9249 | 4890 | 696748 | 6315.07 | 0.0365854 | 2.16949 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 16058.2 | 0.242914 | 58.0404ms | 9249 | 4890 | 8705.77 | 549.284 | 0.247215 | 0.182802 | 1(Win) | true |
| glaze | 3409.42 | 0.509605 | 249.566ms | 9249 | 2560 | 444976 | 2587.11 | 1.40246 | 0.883869 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 18424.1 | 0.360596 | 50.9078ms | 9249 | 2560 | 7629.54 | 478.75 | 1.11344 | 0.158693 | 1(Win) | true |
| glaze | 5230.86 | 0.607512 | 191.088ms | 9249 | 160 | 16790.9 | 1686.25 | 2.42976 | 0.569447 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 442.324 | 0.224211 | 998.356ms | 4604 | 4890 | 2.42221e+06 | 9926.46 | 0.183887 | 6.85553 | 1(Win) | true |
| jsonifier (two-stage) | 397.932 | 0.194287 | 1113.95ms | 4604 | 2560 | 1.17647e+06 | 11033.8 | 0.381593 | 7.62153 | 2(Loss) | true |
| glaze | 285.351 | 0.161445 | 1546.04ms | 4604 | 2560 | 1.57979e+06 | 15387.1 | 0.00583925 | 10.6361 | 3(Loss) | true |
| simdjson (ondemand) | 39.0555 | 0.204512 | 5746.82ms | 4604 | 320 | 1.69159e+07 | 112422 | 0.104626 | 77.801 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 541.346 | 0.237979 | 944.652ms | 4604 | 4890 | 1.82183e+06 | 8110.74 | 0.0958593 | 5.59922 | 1(Win) | true |
| jsonifier (two-stage) | 480.467 | 0.153966 | 1045.87ms | 4604 | 2560 | 506799 | 9138.44 | 0.102694 | 6.31056 | 2(Loss) | true |
| glaze | 324.825 | 0.138905 | 1478.73ms | 4604 | 4890 | 1.72392e+06 | 13517.2 | 0.0263615 | 9.34104 | 3(Loss) | true |
| simdjson (ondemand) | 39.4758 | 0.108997 | 5758.17ms | 4604 | 2560 | 3.76248e+07 | 111226 | 0.244894 | 76.9762 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1598.56 | 0.337286 | 289.321ms | 4604 | 30 | 2574.71 | 2746.67 | 0.121507 | 1.88506 | 1(Win) | true |
| glaze | 924.879 | 0.161867 | 480.294ms | 4604 | 1280 | 75583.2 | 4747.34 | 0.663702 | 3.26928 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1698.54 | 0.221188 | 273.772ms | 4604 | 40 | 1307.69 | 2585 | 0.321337 | 1.77397 | 1(Win) | true |
| glaze | 1002 | 0.323397 | 445.8ms | 4604 | 4890 | 982008 | 4381.94 | 0.255366 | 3.01252 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1913.5 | 0.268881 | 1232.62ms | 24579 | 160 | 173585 | 12250 | 0.0102051 | 1.58541 | 1(Win) | true |
| jsonifier | 1766.24 | 0.211228 | 1339.85ms | 24579 | 2560 | 2.01176e+06 | 13271.4 | 0.864818 | 1.71759 | 2(Loss) | true |
| glaze | 1246.5 | 0.266129 | 1927.5ms | 24579 | 160 | 400730 | 18805 | 0.601255 | 2.43473 | 3(Loss) | true |
| simdjson (ondemand) | 204.435 | 0.119586 | 5890.53ms | 24579 | 1280 | 2.40652e+07 | 114659 | 0.168694 | 14.8636 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2323.34 | 0.197463 | 1147.36ms | 24579 | 4890 | 1.94083e+06 | 10089.1 | 0.0294301 | 1.30504 | 1(Win) | true |
| jsonifier | 2064.83 | 0.242115 | 1288.97ms | 24579 | 1280 | 966969 | 11352.2 | 0.327878 | 1.46892 | 2(Loss) | true |
| glaze | 1335.16 | 0.268973 | 1889.48ms | 24579 | 4890 | 1.0904e+07 | 17556.2 | 0.220538 | 2.27291 | 3(Loss) | true |
| simdjson (ondemand) | 206.914 | 0.0938748 | 5895.82ms | 24579 | 2560 | 2.89525e+07 | 113285 | 0.14773 | 14.686 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6418.72 | 0.240267 | 367.507ms | 24579 | 320 | 24636 | 3651.88 | 0.0171174 | 0.470393 | 1(Win) | true |
| glaze | 3037.32 | 0.253898 | 782.19ms | 24579 | 4890 | 1.87748e+06 | 7717.44 | 0.229085 | 0.997446 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6758.34 | 0.389147 | 349.351ms | 24579 | 2560 | 466353 | 3468.36 | 0.0900191 | 0.446766 | 1(Win) | true |
| glaze | 3415.56 | 0.190756 | 694.313ms | 24579 | 1280 | 219367 | 6862.81 | 0.0934345 | 0.88536 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 474.8 | 0.139538 | 940.599ms | 4604 | 40 | 6660.26 | 9247.5 | 0.117286 | 6.38514 | 1(Win) | true |
| jsonifier (two-stage) | 423.406 | 0.227615 | 1055.71ms | 4604 | 320 | 178282 | 10370 | 0.326521 | 7.15922 | 2(Loss) | true |
| glaze | 281.884 | 0.315265 | 1557.91ms | 4604 | 1280 | 3.08669e+06 | 15576.3 | 0.380119 | 10.761 | 3(Loss) | true |
| simdjson (ondemand) | 250.292 | 0.446729 | 1762.88ms | 4604 | 640 | 3.93046e+06 | 17542.3 | 0.227646 | 12.1217 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 576.21 | 0.116022 | 895.117ms | 4604 | 30 | 2344.83 | 7620 | 0.0437254 | 5.26515 | 1(Win) | true |
| jsonifier (two-stage) | 505.841 | 0.185956 | 997.917ms | 4604 | 4890 | 1.27401e+06 | 8680.04 | 0.0828947 | 5.99201 | 2(Loss) | true |
| glaze | 318.077 | 0.189323 | 1509.11ms | 4604 | 2560 | 1.74845e+06 | 13803.9 | 0.110201 | 9.5358 | 3(Loss) | true |
| simdjson (ondemand) | 274.028 | 0.1437 | 1738.68ms | 4604 | 2560 | 1.35716e+06 | 16022.9 | 0.0109695 | 11.0703 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1548.71 | 0.595898 | 285.853ms | 4604 | 1280 | 365328 | 2835.08 | 0.556972 | 1.94725 | 1(Win) | true |
| glaze | 932.266 | 0.322721 | 473.902ms | 4604 | 2560 | 591406 | 4709.73 | 0.0755325 | 3.24297 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1648.88 | 0.309337 | 271.872ms | 4604 | 2560 | 173700 | 2662.85 | 0.00440102 | 1.82869 | 1(Win) | true |
| glaze | 995.577 | 0.400128 | 440.443ms | 4604 | 4890 | 1.52275e+06 | 4410.22 | 0.285804 | 3.03762 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2000.35 | 0.387251 | 1172.52ms | 24579 | 1280 | 2.63579e+06 | 11718.1 | 0.182343 | 1.51605 | 1(Win) | true |
| jsonifier | 1867.56 | 0.199005 | 1262.27ms | 24579 | 1280 | 798575 | 12551.3 | 0.109046 | 1.62385 | 2(Loss) | true |
| simdjson (ondemand) | 1225.29 | 0.306964 | 1913.56ms | 24579 | 1280 | 4.414e+06 | 19130.4 | 0.154537 | 2.47569 | 3(Loss) | true |
| glaze | 1214.99 | 0.195714 | 1926.99ms | 24579 | 640 | 912450 | 19292.7 | 0.267167 | 2.4975 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2432.28 | 0.271195 | 1093.2ms | 24579 | 320 | 218581 | 9637.19 | 0.0551554 | 1.24643 | 1(Win) | true |
| jsonifier | 2174.93 | 0.300019 | 1216.99ms | 24579 | 2560 | 2.67654e+06 | 10777.5 | 0.0282627 | 1.39424 | 2(Loss) | true |
| glaze | 1345.08 | 0.150305 | 1917.72ms | 24579 | 2560 | 1.75639e+06 | 17426.7 | 0.186148 | 2.25565 | 3(Loss) | true |
| simdjson (ondemand) | 1338.68 | 0.0838149 | 1883.92ms | 24579 | 40 | 8615.38 | 17510 | 0.303663 | 2.26649 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6634.53 | 0.304861 | 355.321ms | 24579 | 4890 | 567312 | 3533.09 | 0.246991 | 0.454708 | 1(Win) | true |
| glaze | 2997.9 | 0.22616 | 784.321ms | 24579 | 4890 | 1.5291e+06 | 7818.94 | 0.132956 | 1.01058 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7147.81 | 0.0978474 | 336.392ms | 24579 | 160 | 1647.41 | 3279.38 | 0.209205 | 0.42147 | 1(Win) | true |
| glaze | 3186.87 | 0.261305 | 738.952ms | 24579 | 4890 | 1.80635e+06 | 7355.3 | 0.0294179 | 0.948754 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 701.328 | 0.197294 | 162.838ms | 1181 | 1280 | 12849.8 | 1605.94 | 0.126324 | 4.28198 | 1(Win) | true |
| jsonifier (two-stage) | 643.594 | 0.457509 | 185.218ms | 1181 | 40 | 2564.1 | 1750 | 0.382409 | 4.67316 | 2(Loss) | true |
| glaze | 279.651 | 0.247591 | 405.954ms | 1181 | 4890 | 486236 | 4027.48 | 0.220062 | 10.817 | 3(Loss) | true |
| simdjson (ondemand) | 240.532 | 0.286266 | 480.328ms | 1181 | 160 | 28748.4 | 4682.5 | 0.186517 | 12.5728 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 893.77 | 0.216143 | 150.165ms | 1181 | 640 | 4748.02 | 1260.16 | 0.185644 | 3.35853 | 1(Win) | true |
| jsonifier (two-stage) | 760.933 | 0.299252 | 169.046ms | 1181 | 4890 | 95938.2 | 1480.14 | 0.00352408 | 3.94669 | 2(Loss) | true |
| glaze | 605.532 | 0.463611 | 206.993ms | 1181 | 40 | 2974.36 | 1860 | 0.178891 | 4.95362 | 3(Loss) | true |
| simdjson (ondemand) | 401.887 | 0.201506 | 303.548ms | 1181 | 40 | 1275.64 | 2802.5 | 0.148456 | 7.45849 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1996.75 | 0.47627 | 59.1642ms | 1181 | 320 | 2309.46 | 564.062 | 0.496141 | 1.46989 | 1(Win) | true |
| glaze | 1158.14 | 0.516574 | 95.1167ms | 1181 | 80 | 2018.99 | 972.5 | 0.25641 | 2.56704 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2128.11 | 0.21031 | 55.4944ms | 1181 | 4890 | 6058.13 | 529.243 | 0.308209 | 1.37156 | 1(Win) | true |
| glaze | 1325.53 | 0.232783 | 88.8677ms | 1181 | 640 | 2503.81 | 849.688 | 0.258112 | 2.22372 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1240.04 | 0.145892 | 195.007ms | 2496 | 4890 | 38352.1 | 1919.59 | 0.345697 | 2.42549 | 1(Win) | true |
| jsonifier | 1048.91 | 0.165748 | 235.37ms | 2496 | 160 | 2263.76 | 2269.38 | 0.356751 | 2.87526 | 2(Loss) | true |
| glaze | 562.673 | 0.184052 | 428.691ms | 2496 | 1280 | 77601 | 4230.47 | 0.298277 | 5.3789 | 3(Loss) | true |
| simdjson (ondemand) | 493.386 | 0.247176 | 485.204ms | 2496 | 4890 | 695406 | 4824.56 | 0.227204 | 6.13601 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1521.41 | 0.271488 | 178.947ms | 2496 | 4890 | 88227.7 | 1564.58 | 0.208616 | 1.97458 | 1(Win) | true |
| jsonifier | 1261.12 | 0.197133 | 214.239ms | 2496 | 80 | 1107.59 | 1887.5 | 0 | 2.38295 | 2(Loss) | true |
| glaze | 1202.54 | 0.243102 | 219.882ms | 2496 | 1280 | 29640 | 1979.45 | 0.0908588 | 2.49861 | 3(Loss) | true |
| simdjson (ondemand) | 815.37 | 0.13387 | 309.975ms | 2496 | 2560 | 39100.8 | 2919.38 | 0.287164 | 3.68104 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3811.93 | 0.502268 | 64.5855ms | 2496 | 1280 | 12591.6 | 624.453 | 0.0876534 | 0.773772 | 1(Win) | true |
| glaze | 2021.34 | 0.204194 | 124.274ms | 2507 | 320 | 1866.67 | 1182.81 | 0.0264271 | 1.48395 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3312.18 | 0.271209 | 74.8592ms | 2496 | 2560 | 9725.47 | 718.672 | 0.0868904 | 0.890727 | 1(Win) | true |
| glaze | 2238.34 | 0.181704 | 108.874ms | 2507 | 4890 | 18420.1 | 1068.14 | 0.254299 | 1.32557 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1143.02 | 0.213519 | 421.777ms | 4926 | 30 | 2310.34 | 4110 | 0.0810373 | 2.64926 | 1(Win) | true |
| jsonifier (two-stage) | 974.71 | 0.262392 | 481.524ms | 4926 | 320 | 51178.6 | 4819.69 | 0.136346 | 3.10652 | 2(Loss) | true |
| glaze | 826.417 | 0.35037 | 573.095ms | 4926 | 4890 | 1.93979e+06 | 5684.54 | 0.394099 | 3.66338 | 3(Loss) | true |
| simdjson (ondemand) | 506.951 | 0.1211 | 932.095ms | 4926 | 4890 | 615817 | 9266.77 | 0.16737 | 5.98067 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1391.34 | 0.445465 | 416.594ms | 4926 | 2560 | 579144 | 3376.45 | 0.0474109 | 2.17386 | 1(Win) | true |
| glaze | 1210.77 | 0.287158 | 475.499ms | 4926 | 30 | 3724.14 | 3880 | 0.258398 | 2.50266 | 2(Loss) | true |
| jsonifier (two-stage) | 1195.82 | 0.264879 | 476.066ms | 4926 | 4890 | 529492 | 3928.51 | 0.117253 | 2.52909 | 3(Loss) | true |
| simdjson (ondemand) | 619.354 | 0.16208 | 842.42ms | 4926 | 320 | 48363.6 | 7585 | 0.206424 | 4.89372 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7934.01 | 0.223626 | 61.2174ms | 4926 | 1280 | 2244.18 | 592.109 | 0.517241 | 0.370581 | 1(Win) | true |
| glaze | 3026.29 | 0.175549 | 158.076ms | 4926 | 4890 | 36313.9 | 1552.33 | 0.385685 | 0.992045 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10062.2 | 0.799486 | 50.4632ms | 4926 | 160 | 2229.17 | 466.875 | 0.134048 | 0.29131 | 1(Win) | true |
| glaze | 3706.35 | 0.41575 | 133.954ms | 4926 | 80 | 2221.52 | 1267.5 | 0.19685 | 0.802274 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1777.57 | 0.149063 | 514.441ms | 9463 | 4890 | 280064 | 5076.95 | 0.524285 | 1.70303 | 1(Win) | true |
| jsonifier | 1561.17 | 0.283075 | 584.01ms | 9463 | 2560 | 685484 | 5780.66 | 0.0682968 | 1.93944 | 2(Loss) | true |
| glaze | 1361.93 | 0.185319 | 666.843ms | 9463 | 4890 | 737387 | 6626.34 | 0.325937 | 2.22435 | 3(Loss) | true |
| simdjson (ondemand) | 942.988 | 0.161033 | 960.865ms | 9463 | 2560 | 608016 | 9570.23 | 0.126372 | 3.21541 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2103.15 | 0.187279 | 512.54ms | 9463 | 4890 | 315795 | 4291 | 0.183865 | 1.43913 | 1(Win) | true |
| glaze STATISTICAL TIE | 1825 | 0.31712 | 569.789ms | 9463 | 160 | 39345.9 | 4945 | 0.533672 | 1.65768 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 1824.88 | 0.17205 | 578.253ms | 9463 | 640 | 46331.7 | 4945.31 | 0.374223 | 1.65907 | 2(Tie) | true |
| simdjson (ondemand) | 1141.51 | 0.240212 | 875.826ms | 9463 | 2560 | 923264 | 7905.86 | 0.922291 | 2.6552 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14101 | 1.22573 | 68.7461ms | 9463 | 40 | 2461.54 | 640 | 0 | 0.207569 | 1(Win) | true |
| glaze | 4182 | 0.440769 | 225.985ms | 9463 | 640 | 57902 | 2157.97 | 0.108727 | 0.719326 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 17220.5 | 0.456689 | 54.805ms | 9463 | 320 | 1832.97 | 524.062 | 1.00354 | 0.17139 | 1(Win) | true |
| glaze | 5284.56 | 0.505962 | 178.016ms | 9463 | 2560 | 191124 | 1707.73 | 0.718795 | 0.56318 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4946.28 | 0.367755 | 57.5843ms | 2821 | 640 | 2560.62 | 543.906 | 0.0287191 | 0.595009 | 1(Win) | true |
| jsonifier | 4786.13 | 0.528927 | 58.1349ms | 2821 | 4890 | 43225.3 | 562.106 | 0.671067 | 0.614635 | 2(Loss) | true |
| glaze | 2397.34 | 0.214486 | 113.993ms | 2821 | 4890 | 28330.6 | 1122.21 | 0.400293 | 1.24866 | 3(Loss) | true |
| simdjson (ondemand) | 1992.83 | 0.416699 | 139ms | 2821 | 80 | 2531.65 | 1350 | 0.184843 | 1.5044 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5367.63 | 0.299746 | 54.3312ms | 2821 | 2560 | 5778.13 | 501.211 | 0.42682 | 0.54543 | 1(Win) | true |
| jsonifier (two-stage) | 5262.23 | 0.262935 | 54.5735ms | 2821 | 640 | 1156.49 | 511.25 | 0.183711 | 0.557668 | 2(Loss) | true |
| glaze | 2448.52 | 0.406811 | 109.763ms | 2821 | 320 | 6393.42 | 1098.75 | 0.17094 | 1.20198 | 3(Loss) | true |
| simdjson (ondemand) | 2043.92 | 0.315331 | 135.152ms | 2821 | 80 | 1378.16 | 1316.25 | 0.285714 | 1.467 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6632.93 | 0.490673 | 64.1914ms | 4147 | 160 | 1369.5 | 596.25 | 0.845666 | 0.448657 | 1(Win) | true |
| jsonifier (two-stage) | 6373.17 | 0.697104 | 63.8168ms | 4147 | 4890 | 91508.4 | 620.552 | 0.259609 | 0.463773 | 2(Loss) | true |
| glaze | 3391.34 | 0.193072 | 119.029ms | 4147 | 2560 | 12977.9 | 1166.17 | 0.0670376 | 0.882547 | 3(Loss) | true |
| simdjson (ondemand) | 2788.81 | 0.196517 | 145.917ms | 4147 | 2560 | 19882.4 | 1418.12 | 0.0110193 | 1.0759 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7105.92 | 0.529403 | 60.5518ms | 4147 | 320 | 2778.12 | 556.562 | 0.0561167 | 0.415405 | 1(Win) | true |
| jsonifier | 7001.74 | 0.369247 | 61.2974ms | 4147 | 640 | 2784.01 | 564.844 | 0.0829187 | 0.41944 | 2(Loss) | true |
| glaze | 3543.25 | 0.614923 | 115.383ms | 4147 | 4890 | 230364 | 1116.18 | 0.189699 | 0.83288 | 3(Loss) | true |
| simdjson (ondemand) | 2900.18 | 0.297257 | 141.888ms | 4147 | 1280 | 21032.6 | 1363.67 | 0.212424 | 1.03211 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1575.73 | 0.304804 | 173.51ms | 2821 | 640 | 17332.5 | 1707.34 | 0.0824327 | 1.90285 | 1(Win) | true |
| glaze | 1530.76 | 0.534673 | 182.629ms | 2821 | 40 | 3532.05 | 1757.5 | 0.0474383 | 1.97547 | 2(Loss) | true |
| jsonifier (two-stage) | 1339.25 | 0.182777 | 203.106ms | 2821 | 1280 | 17255.9 | 2008.83 | 0.323839 | 2.24477 | 3(Loss) | true |
| simdjson (ondemand) | 947.868 | 0.279006 | 288.576ms | 2821 | 1280 | 80269.1 | 2838.28 | 0.269024 | 3.18423 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2209 | 0.223368 | 142.123ms | 2821 | 2560 | 18945.1 | 1217.89 | 0.0770367 | 1.35311 | 1(Win) | true |
| glaze | 1922.94 | 0.419982 | 156.013ms | 2821 | 640 | 22096.1 | 1399.06 | 0.0894254 | 1.54989 | 2(Loss) | true |
| jsonifier (two-stage) | 1805.58 | 0.402111 | 171.899ms | 2821 | 40 | 1435.9 | 1490 | 0 | 1.66381 | 3(Loss) | true |
| simdjson (ondemand) | 1093.62 | 0.216953 | 264.496ms | 2821 | 1280 | 36459.7 | 2460 | 0.427378 | 2.75954 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9664.9 | 0.544351 | 30.102ms | 2821 | 2560 | 5877.73 | 278.359 | 0.140528 | 0.293567 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3540.29 | 1.32642 | 70.384ms | 2819 | 2560 | 259725 | 759.375 | 2.52083 | 0.835902 | -(Loss) | false |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11744.9 | 1.10983 | 25.4953ms | 2821 | 320 | 2068.08 | 229.062 | 0.410959 | 0.230127 | 1(Win) | true |
| glaze | 5360.07 | 1.07166 | 57.7159ms | 2819 | 320 | 9245.2 | 501.562 | 0.0623441 | 0.53458 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1890.74 | 0.156615 | 216.686ms | 4147 | 2560 | 27473.4 | 2091.72 | 0.0149421 | 1.5914 | 1(Win) | true |
| jsonifier (two-stage) | 1857.84 | 0.329278 | 216.263ms | 4147 | 320 | 15722.6 | 2128.75 | 0.0880023 | 1.62202 | 2(Loss) | true |
| jsonifier | 1652.46 | 0.564261 | 252.306ms | 4147 | 30 | 5471.26 | 2393.33 | 0.13947 | 1.82501 | 3(Loss) | true |
| simdjson (ondemand) | 1352.94 | 0.280209 | 296.058ms | 4147 | 4890 | 328086 | 2923.19 | 0.0124678 | 2.23064 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2392.6 | 0.357666 | 184.702ms | 4147 | 640 | 22369.9 | 1652.97 | 0.0661251 | 1.25466 | 1(Tie) | true |
| glaze STATISTICAL TIE | 2371.75 | 0.449775 | 185.129ms | 4147 | 40 | 2250 | 1667.5 | 0.250501 | 1.26 | 1(Tie) | true |
| jsonifier | 1953.63 | 0.311477 | 221.225ms | 4147 | 640 | 25445.6 | 2024.38 | 0.263117 | 1.53763 | 3(Loss) | true |
| simdjson (ondemand) | 1539.9 | 0.231095 | 273ms | 4147 | 640 | 22544.8 | 2568.28 | 0.397019 | 1.96032 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11761.7 | 0.659798 | 35.8796ms | 4147 | 1280 | 6300.23 | 336.25 | 0.0464468 | 0.243822 | 1(Win) | true |
| glaze | 3059.32 | 0.710997 | 121.331ms | 4145 | 1280 | 108030 | 1292.11 | 1.59091 | 0.977416 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14698.8 | 0.961867 | 30.364ms | 4147 | 320 | 2143.32 | 269.062 | 1.05634 | 0.190693 | 1(Win) | true |
| glaze | 5350.9 | 0.536585 | 97.5264ms | 4145 | 160 | 2514.15 | 738.75 | 1.99005 | 0.543886 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3176.24 | 0.12922 | 7170.13ms | 466906 | 2560 | 8.40107e+07 | 140190 | 0.110859 | 0.956697 | 1(Win) | true |
| glaze | 1927.86 | 0.107863 | 5891.86ms | 466906 | 640 | 3.97219e+07 | 230969 | 0.0902309 | 1.57639 | 2(Loss) | true |
| simdjson (ondemand) | 1141.23 | 0.214993 | 10030.1ms | 466906 | 320 | 2.2517e+08 | 390172 | 0.325674 | 2.66236 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3189.95 | 0.338488 | 7120.84ms | 466906 | 320 | 7.14378e+07 | 139587 | 0.334464 | 0.952548 | 1(Win) | true |
| glaze | 1917.57 | 0.19534 | 5907.9ms | 466906 | 160 | 3.29197e+07 | 232208 | 0.187786 | 1.58474 | 2(Loss) | true |
| simdjson (ondemand) | 1139.73 | 0.257865 | 5026.55ms | 466906 | 320 | 3.24783e+08 | 390687 | 0.42024 | 2.66612 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2474.7 | 0.122729 | 6923.42ms | 699405 | 1280 | 1.40061e+08 | 269530 | 0.259443 | 1.22758 | 1(Win) | true |
| glaze | 2433.08 | 0.0901993 | 7010.22ms | 699405 | 1280 | 7.82639e+07 | 274140 | 0.283676 | 1.24908 | 2(Loss) | true |
| simdjson (ondemand) | 929.34 | 0.201615 | 10025.9ms | 767297 | 640 | 1.61289e+09 | 787389 | 0.0959985 | 3.26934 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3898.05 | 0.287878 | 8760.13ms | 699405 | 80 | 1.9412e+07 | 171112 | 0.0335923 | 0.779595 | 1(Win) | true |
| glaze | 2424.07 | 0.224954 | 7009.13ms | 699405 | 1280 | 4.90413e+08 | 275159 | 0.0281576 | 1.25368 | 2(Loss) | true |
| simdjson (ondemand) | 924.261 | 0.263583 | 10019.7ms | 767297 | 320 | 1.39355e+09 | 791715 | 0.0546186 | 3.28734 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2963.75 | 0.253299 | 5192.55ms | 631514 | 320 | 8.47813e+07 | 203208 | 0.309753 | 1.02541 | 1(Win) | true |
| glaze | 2411.16 | 0.105303 | 6394.94ms | 631514 | 640 | 4.42766e+07 | 249780 | 0.28475 | 1.26041 | 2(Loss) | true |
