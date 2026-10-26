# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.4 compiler).  

Latest Results: (Oct 28, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| Glaze: [8ae6d0d](https://github.com/stephenberry/glaze/commit/8ae6d0d)  
| Simdjson: [ab504c9](https://github.com/simdjson/simdjson/commit/ab504c9)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **Adaptive Sampling & Convergence (Apple M2 Pro (Virtual)-NEON):**  
> Iterations scale geometrically (100 → 200 → 400 ...) up to a maximum of 100000.  
> Scores evaluate a trailing window of `max(iterations/10, 30)` (cap: 100000) over at most 5s.  
> Canonical epochs are chosen by minimum (RSE + epoch-over-epoch mean shift).  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Tie detection: Welch's t-test with Bessel-corrected variance.

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
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1308.28 | 0.436991 | 75.1788ms | 905 | 30 | 249.321 | 659.7 | 0.0151607 | 1(Win) | true |
| glaze | 1170.27 | 0.480814 | 77.2993ms | 905 | 30 | 377.224 | 737.5 | 0.00451998 | 2(Loss) | true |
| jsonifier (two-stage) | 344.339 | 0.135622 | 255.707ms | 905 | 4890 | 56505.7 | 2506.47 | 0.0693343 | 3(Loss) | true |
| simdjson (ondemand) | 193.448 | 0.164355 | 451.588ms | 905 | 1280 | 68824.6 | 4461.54 | 0.257601 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1384.02 | 0.224503 | 64.7412ms | 905 | 30 | 58.8 | 623.6 | 0.00534502 | 1(Win) | true |
| glaze | 1342.34 | 0.0942176 | 66.9403ms | 905 | 1280 | 469.726 | 642.962 | 0.090362 | 2(Loss) | true |
| jsonifier (two-stage) | 335.505 | 0.137457 | 257.454ms | 905 | 80 | 1000.28 | 2572.46 | 0.139264 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 183.732 | 0.259156 | 512.116ms | 905 | 80 | 11856 | 4697.46 | 5.89218 | -(Loss) | false |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2048.68 | 0.124954 | 45.2935ms | 905 | 640 | 177.349 | 421.283 | 0.234962 | 1(Win) | true |
| glaze | 134.79 | 0.0334234 | 650.803ms | 905 | 160 | 732.828 | 6403.09 | 0.0729672 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3055.52 | 0.124455 | 38.4374ms | 905 | 2560 | 316.365 | 282.464 | 0.142644 | 1(Win) | true |
| glaze | 763.377 | 0.0395746 | 127.918ms | 905 | 1280 | 256.249 | 1130.6 | 0.0529589 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 946.828 | 0.120424 | 190.414ms | 1811 | 4890 | 23595.5 | 1824.1 | 0.00382331 | 1(Win) | true |
| glaze | 856.194 | 0.136185 | 202.291ms | 1811 | 80 | 603.724 | 2017.19 | 0.335355 | 2(Loss) | true |
| jsonifier (two-stage) | 354.211 | 0.128404 | 492.778ms | 1811 | 1280 | 50173.9 | 4875.92 | 0.273499 | 3(Loss) | true |
| simdjson (ondemand) | 206.346 | 0.0909374 | 849.132ms | 1811 | 4890 | 283296 | 8369.96 | 0.0772628 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1124.26 | 0.148994 | 157.934ms | 1811 | 4890 | 25618.3 | 1536.21 | 0.181806 | 1(Win) | true |
| glaze | 1062.96 | 0.0463062 | 167.946ms | 1811 | 640 | 362.294 | 1624.81 | 0.0280724 | 2(Loss) | true |
| jsonifier (two-stage) | 382.265 | 0.11178 | 481.461ms | 1811 | 2560 | 65294.7 | 4518.08 | 0.0524817 | 3(Loss) | true |
| simdjson (ondemand) | 210.162 | 0.0628823 | 795.273ms | 1811 | 30 | 801.137 | 8217.97 | 0.0836266 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 316.024 | 0.0514617 | 556.467ms | 1811 | 80 | 632.785 | 5465.11 | 0.122058 | 1(Win) | true |
| glaze | 228.123 | 0.106448 | 763.36ms | 1798 | 40 | 2560.81 | 7516.6 | 0.186157 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 926.467 | 0.105941 | 199.923ms | 1811 | 2560 | 9984.89 | 1864.18 | 0.086322 | 1(Win) | true |
| glaze | 705.545 | 0.0505619 | 260.258ms | 1798 | 320 | 483.199 | 2430.33 | 0.0371468 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2293.34 | 0.12673 | 163.325ms | 3862 | 4890 | 20256 | 1605.99 | 0.0156405 | 1(Win) | true |
| glaze | 1356.01 | 0.257577 | 265.912ms | 3862 | 80 | 3915.66 | 2716.12 | 0.366821 | 2(Loss) | true |
| jsonifier (two-stage) | 880.915 | 0.0552947 | 427.383ms | 3862 | 320 | 1710.31 | 4180.98 | 0.155858 | 3(Loss) | true |
| simdjson (ondemand) | 495.683 | 0.0770962 | 760.427ms | 3862 | 80 | 2625.26 | 7430.34 | 0.0687584 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2801.76 | 0.186182 | 136.417ms | 3862 | 80 | 479.211 | 1314.56 | 0.000950878 | 1(Win) | true |
| glaze | 1639 | 0.0945375 | 230.517ms | 3862 | 160 | 722.095 | 2247.16 | 0.130613 | 2(Loss) | true |
| jsonifier (two-stage) | 946.753 | 0.158385 | 396.482ms | 3862 | 30 | 1138.94 | 3890.23 | 0.110411 | 3(Loss) | true |
| simdjson (ondemand) | 513.021 | 0.0696248 | 735.211ms | 3862 | 40 | 999.41 | 7179.23 | 0.0398298 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3453.74 | 0.0548674 | 111.076ms | 3862 | 1280 | 438.212 | 1066.41 | 0.0381098 | 1(Win) | true |
| glaze | 560.229 | 0.0448541 | 669.018ms | 3862 | 160 | 1391.29 | 6574.26 | 0.0447018 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3494.21 | 0.234627 | 117.332ms | 3862 | 4890 | 29908.3 | 1054.06 | 1.24349 | 1(Win) | true |
| glaze | 2320.04 | 0.137196 | 178.238ms | 3862 | 80 | 379.494 | 1587.51 | 0.0495813 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1384.42 | 0.0696706 | 662.201ms | 9578 | 40 | 845.221 | 6597.9 | 0.00909298 | 1(Win) | true |
| glaze | 1213.46 | 0.212584 | 762.812ms | 9578 | 2560 | 655539 | 7527.46 | 0.717333 | 2(Loss) | true |
| simdjson (ondemand) | 878.355 | 0.23971 | 1036.65ms | 9578 | 1280 | 795409 | 10399.3 | 0.490937 | 3(Loss) | true |
| jsonifier (two-stage) | 734.085 | 0.0995118 | 1257.36ms | 9578 | 30 | 4599.68 | 12443.1 | 0.168516 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2468.39 | 0.0828256 | 615.953ms | 9578 | 80 | 751.519 | 3700.5 | 0.296784 | 1(Win) | true |
| glaze | 1884.37 | 0.0550484 | 705.742ms | 9578 | 80 | 569.635 | 4847.4 | 0.0948063 | 2(Loss) | true |
| simdjson (ondemand) | 1190.57 | 0.043119 | 995.471ms | 9578 | 30 | 328.323 | 7672.23 | 0.0373502 | 3(Loss) | true |
| jsonifier (two-stage) | 969.736 | 0.043393 | 1201.98ms | 9578 | 80 | 1336.51 | 9419.36 | 0.0723768 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1393.77 | 0.115465 | 667.134ms | 9578 | 4890 | 280014 | 6553.64 | 0.0264296 | 1(Win) | true |
| glaze | 1167.24 | 0.0502354 | 795.197ms | 9578 | 80 | 1236.35 | 7825.56 | 0.00686899 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8241.41 | 0.114506 | 122.852ms | 9578 | 320 | 515.41 | 1108.34 | 0.141622 | 1(Win) | true |
| glaze | 4789.25 | 0.134452 | 220.465ms | 9578 | 80 | 526.063 | 1907.25 | 0.052459 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2362.92 | 0.12336 | 159.753ms | 3873 | 4890 | 18182.5 | 1563.14 | 0.119332 | 1(Win) | true |
| glaze | 1662.66 | 0.115774 | 225.833ms | 3873 | 4890 | 32345.7 | 2221.48 | 0.284267 | 2(Loss) | true |
| jsonifier (two-stage) | 851.304 | 0.143566 | 440.081ms | 3873 | 2560 | 99327.1 | 4338.74 | 0.035305 | 3(Loss) | true |
| simdjson (ondemand) | 488.373 | 0.0861094 | 786ms | 3873 | 80 | 3393 | 7563.04 | 0.0196642 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2826.51 | 0.346541 | 138.367ms | 3873 | 80 | 1640.56 | 1306.76 | 0.037292 | 1(Win) | true |
| glaze | 1921.57 | 0.196069 | 196.801ms | 3873 | 2560 | 36361.4 | 1922.17 | 0.124602 | 2(Loss) | true |
| jsonifier (two-stage) | 936.779 | 0.0457047 | 403.472ms | 3873 | 320 | 1039.18 | 3942.85 | 0.108307 | 3(Loss) | true |
| simdjson (ondemand) | 499.513 | 0.0965717 | 757.699ms | 3873 | 30 | 1529.76 | 7394.37 | 0.0770263 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3523.82 | 0.124543 | 108.146ms | 3873 | 160 | 272.661 | 1048.17 | 0.174416 | 1(Win) | true |
| glaze | 564.742 | 0.107929 | 663.777ms | 3873 | 30 | 1494.84 | 6540.3 | 0.0862069 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4023.51 | 0.150561 | 103.023ms | 3873 | 30 | 57.3103 | 918 | 0 | 1(Win) | true |
| glaze | 2422.82 | 0.0836913 | 171.06ms | 3873 | 320 | 520.909 | 1524.49 | 0.223935 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1605.23 | 0.0601113 | 5647.18ms | 94653 | 4890 | 5.58752e+06 | 56233.9 | 0.03305 | 1(Win) | true |
| jsonifier (two-stage) | 1125.88 | 0.0838063 | 8126.61ms | 94653 | 2560 | 1.15579e+07 | 80175.6 | 0.191594 | 2(Loss) | true |
| glaze | 1111.98 | 0.155001 | 8128.1ms | 94653 | 2560 | 4.05308e+07 | 81178.1 | 0.0017342 | 3(Loss) | true |
| simdjson (ondemand) | 909.515 | 0.0695758 | 5110.68ms | 94653 | 2560 | 1.22069e+07 | 99248.7 | 0.364169 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2398.32 | 0.075996 | 5339.24ms | 94653 | 4890 | 4.0008e+06 | 37638.1 | 0.0640845 | 1(Win) | true |
| jsonifier (two-stage) | 1542.13 | 0.0952256 | 7686.54ms | 94653 | 2560 | 7.95379e+06 | 58534.7 | 0.0475592 | 2(Loss) | true |
| glaze | 1458.42 | 0.0629493 | 7617.08ms | 94653 | 4890 | 7.42328e+06 | 61894.6 | 0.111345 | 3(Loss) | true |
| simdjson (ondemand) | 1121.63 | 0.184141 | 9678.42ms | 94653 | 320 | 7.0278e+06 | 80479.4 | 0.0649744 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12225.9 | 0.063269 | 791.668ms | 94653 | 30 | 654.654 | 7383.37 | 0.0559504 | 1(Win) | true |
| glaze | 3483.39 | 0.0344137 | 2644.29ms | 94653 | 30 | 2385.89 | 25913.9 | 0.0318903 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12663 | 0.020777 | 722.681ms | 94653 | 320 | 701.956 | 7128.5 | 0.188149 | 1(Win) | true |
| glaze | 3928.48 | 0.180241 | 2312.35ms | 94653 | 640 | 1.09776e+06 | 22977.9 | 0.25829 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1647.21 | 0.0554496 | 7273.7ms | 124597 | 4890 | 7.82387e+06 | 72136.9 | 0.168179 | 1(Win) | true |
| glaze | 1416.82 | 0.0620816 | 8391.32ms | 124597 | 4890 | 1.32563e+07 | 83867.6 | 0.39583 | 2(Loss) | true |
| jsonifier (two-stage) | 1408 | 0.116043 | 8467.65ms | 124597 | 640 | 6.13801e+06 | 84392.8 | 0.3477 | 3(Loss) | true |
| simdjson (ondemand) | 1165.96 | 0.134613 | 5270.65ms | 124597 | 640 | 1.20449e+07 | 101912 | 0.0389783 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2261.87 | 0.0613144 | 6833.4ms | 124597 | 4890 | 5.0736e+06 | 52534 | 0.098822 | 1(Win) | true |
| jsonifier (two-stage) | 1890.8 | 0.0850226 | 8237.91ms | 124597 | 2560 | 7.30856e+06 | 62843.6 | 0.0274049 | 2(Loss) | true |
| glaze | 1825.14 | 0.0645486 | 7971.12ms | 124597 | 4890 | 8.63586e+06 | 65104.6 | 0.193781 | 3(Loss) | true |
| simdjson (ondemand) | 1420.93 | 0.119191 | 5073ms | 124597 | 1280 | 1.27165e+07 | 83624.5 | 0.350069 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16970.4 | 0.0516789 | 774.094ms | 136037 | 40 | 624.333 | 7644.77 | 0.160092 | 1(Win) | true |
| glaze | 3715.46 | 0.0338045 | 3553.84ms | 136076 | 30 | 4182.24 | 34927.6 | 0.234411 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17543.4 | 0.127161 | 742.511ms | 136037 | 4890 | 432419 | 7395.09 | 0.0829147 | 1(Win) | true |
| glaze | 4167.51 | 0.0840116 | 3140.3ms | 136076 | 4890 | 3.34655e+06 | 31139 | 0.230522 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 846.541 | 0.216345 | 7891.9ms | 2251027 | 160 | 4.81591e+09 | 2.5359e+06 | 0.147495 | 1(Win) | true |
| jsonifier (two-stage) | 746.469 | 0.174951 | 8945.58ms | 2251027 | 160 | 4.05035e+09 | 2.87587e+06 | 0.0118539 | 2(Loss) | true |
| glaze | 622.046 | 0.154343 | 5239.2ms | 2251027 | 40 | 1.13489e+09 | 3.45111e+06 | 0.127824 | 3(Loss) | true |
| simdjson (ondemand) | 546.841 | 0.249634 | 5895.67ms | 2251027 | 30 | 2.88116e+09 | 3.92572e+06 | 0.0266674 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1056.05 | 0.563986 | 7889.69ms | 2251027 | 40 | 5.2576e+09 | 2.0328e+06 | 0.0656162 | 1(Win) | true |
| jsonifier (two-stage) | 914.267 | 0.170902 | 9015.75ms | 2251027 | 80 | 1.28824e+09 | 2.34805e+06 | 0.128642 | 2(Loss) | true |
| glaze | 726.66 | 0.397282 | 5185.52ms | 2251027 | 40 | 5.51007e+09 | 2.95427e+06 | 0.0666712 | 3(Loss) | true |
| simdjson (ondemand) | 629.17 | 0.216798 | 5941.51ms | 2251027 | 40 | 2.18875e+09 | 3.41203e+06 | 0.000417882 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3011.93 | 0.165492 | 8440.7ms | 2090234 | 40 | 4.79858e+07 | 661836 | 0.193064 | 1(Win) | true |
| glaze | 1888.33 | 0.119141 | 6689.46ms | 2090234 | 160 | 2.5309e+08 | 1.05564e+06 | 0.107403 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3025.59 | 0.165339 | 8422.49ms | 2090234 | 320 | 3.79727e+08 | 658848 | 0.0572229 | 1(Win) | true |
| glaze | 1953.05 | 0.231216 | 6424.47ms | 2090234 | 160 | 8.91084e+08 | 1.02066e+06 | 0.0199659 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1683.7 | 0.17357 | 9575.39ms | 5373214 | 160 | 4.46484e+09 | 3.04347e+06 | 0.0541379 | 1(Win) | true |
| jsonifier (two-stage) | 1604.21 | 0.1498 | 9966.56ms | 5373214 | 80 | 1.83173e+09 | 3.19429e+06 | 0.0912945 | 2(Loss) | true |
| glaze | 1250.02 | 0.244618 | 6154.72ms | 5373214 | 30 | 3.01672e+09 | 4.09938e+06 | 0.197609 | 3(Loss) | true |
| simdjson (ondemand) | 1214.54 | 0.118428 | 6346.99ms | 5373214 | 80 | 1.99731e+09 | 4.21914e+06 | 0.0102922 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2026.98 | 0.221637 | 9555.03ms | 5373214 | 30 | 9.4183e+08 | 2.52804e+06 | 0.047985 | 1(Win) | true |
| jsonifier (two-stage) | 1909 | 0.199179 | 9965.17ms | 5373214 | 160 | 4.57365e+09 | 2.68428e+06 | 0.141221 | 2(Loss) | true |
| glaze | 1431.95 | 0.13731 | 6199.75ms | 5373214 | 80 | 1.93154e+09 | 3.57854e+06 | 0.171265 | 3(Loss) | true |
| simdjson (ondemand) | 1385.21 | 0.126567 | 6391.73ms | 5373214 | 40 | 8.76879e+08 | 3.6993e+06 | 0.268511 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8498.52 | 0.123755 | 9539.17ms | 6661897 | 640 | 5.47793e+08 | 747575 | 0.159148 | 1(Win) | true |
| glaze | 3489.65 | 0.281088 | 5665.22ms | 6661897 | 160 | 4.1902e+09 | 1.8206e+06 | 0.0771977 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8509.7 | 0.150165 | 9587.25ms | 6661897 | 320 | 4.02213e+08 | 746593 | 0.160296 | 1(Win) | true |
| glaze | 3946.05 | 0.156886 | 10165.3ms | 6661897 | 320 | 2.04168e+09 | 1.61004e+06 | 0.0482163 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2342.97 | 0.280573 | 5265.29ms | 500299 | 40 | 1.30579e+07 | 203640 | 0.0535178 | 1(Win) | true |
| jsonifier (two-stage) | 1533.32 | 0.0907107 | 7986.89ms | 500299 | 1280 | 1.01981e+08 | 311169 | 0.0516186 | 2(Loss) | true |
| glaze | 1295.5 | 0.186719 | 9454.19ms | 500299 | 40 | 1.89158e+07 | 368293 | 0.040834 | 3(Loss) | true |
| simdjson (ondemand) | 1082.01 | 0.107335 | 5661.64ms | 500299 | 320 | 7.1684e+07 | 440957 | 0.0631518 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2915.42 | 0.225686 | 5066.62ms | 500299 | 160 | 2.18267e+07 | 163655 | 0.0271916 | 1(Win) | true |
| jsonifier (two-stage) | 1783.96 | 0.106748 | 7807.45ms | 500299 | 640 | 5.21661e+07 | 267452 | 0.0551565 | 2(Loss) | true |
| glaze | 1449.72 | 0.111282 | 9342.61ms | 500299 | 320 | 4.29232e+07 | 329114 | 0.000982743 | 3(Loss) | true |
| simdjson (ondemand) | 1179.32 | 0.0844833 | 5544.67ms | 500299 | 640 | 7.47688e+07 | 404575 | 0.00619168 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8397.87 | 0.027295 | 5789.48ms | 500299 | 40 | 9619.36 | 56814.7 | 0.0622398 | 1(Win) | true |
| glaze | 2153.01 | 0.089433 | 5718.06ms | 500299 | 640 | 2.51388e+07 | 221608 | 0.0302245 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8317.22 | 0.0796014 | 5724.7ms | 500299 | 4890 | 1.01965e+07 | 57365.6 | 0.138675 | 1(Win) | true |
| glaze | 2269.47 | 0.142257 | 5444.26ms | 500299 | 320 | 2.86224e+07 | 210235 | 0.0391551 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3273.29 | 0.0962548 | 8557.78ms | 1151920 | 1280 | 1.33576e+08 | 335612 | 0.119629 | 1(Win) | true |
| jsonifier (two-stage) | 2938.54 | 0.0657072 | 9598.4ms | 1151920 | 1280 | 7.72359e+07 | 373845 | 0.363772 | 2(Loss) | true |
| simdjson (ondemand) | 2193.68 | 0.171848 | 6512.66ms | 1151920 | 40 | 2.96244e+07 | 500783 | 0.150119 | 3(Loss) | true |
| glaze | 2138.8 | 0.0907344 | 6590.36ms | 1151920 | 640 | 1.39004e+08 | 513632 | 0.0210776 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3756.25 | 0.0700313 | 8370.69ms | 1151920 | 1280 | 5.36946e+07 | 292461 | 0.0500747 | 1(Win) | true |
| jsonifier (two-stage) | 3367.99 | 0.153178 | 9430.78ms | 1151920 | 160 | 3.99404e+07 | 326175 | 0.046423 | 2(Loss) | true |
| simdjson (ondemand) | 2359.75 | 0.224919 | 6329.98ms | 1151920 | 80 | 8.77112e+07 | 465540 | 0.283555 | 3(Loss) | true |
| glaze | 2323.27 | 0.110188 | 6491.62ms | 1151920 | 320 | 8.68691e+07 | 472849 | 0.0311762 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20117 | 0.0530647 | 6893.3ms | 1439562 | 4890 | 6.41289e+06 | 68244.4 | 0.198104 | 1(Win) | true |
| glaze | 3216.28 | 0.0961297 | 5485.55ms | 1439584 | 640 | 1.07761e+08 | 426857 | 0.0432572 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20173.9 | 0.079307 | 6806.04ms | 1439562 | 2560 | 7.45667e+06 | 68052 | 0.137451 | 1(Win) | true |
| glaze | 3612.59 | 0.155539 | 9822.44ms | 1439584 | 40 | 1.39758e+07 | 380030 | 0.155509 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2580.23 | 0.0745348 | 2095.91ms | 56369 | 4890 | 1.17921e+06 | 20834.5 | 0.0178478 | 1(Win) | true |
| glaze | 1602.12 | 0.190912 | 3442.56ms | 56369 | 30 | 123106 | 33554.2 | 0.186713 | 2(Loss) | true |
| simdjson (ondemand) | 1375.16 | 0.067405 | 3964.57ms | 56369 | 4890 | 3.39519e+06 | 39091.8 | 0.138369 | 3(Loss) | true |
| jsonifier (two-stage) | 1323.18 | 0.0763074 | 4108.48ms | 56369 | 4890 | 4.69989e+06 | 40627.8 | 0.122783 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3236.08 | 0.0323712 | 1803.89ms | 56369 | 80 | 2313.39 | 16612 | 0.830542 | 1(Win) | true |
| glaze | 1874.06 | 0.0708257 | 2989.48ms | 56369 | 4890 | 2.01839e+06 | 28685.2 | 0.0445455 | 2(Loss) | true |
| jsonifier (two-stage) | 1708.67 | 0.230398 | 3769.02ms | 56369 | 320 | 1.6814e+06 | 31461.7 | 0.237917 | 3(Loss) | true |
| simdjson (ondemand) | 1608.87 | 0.0715616 | 3475.66ms | 56369 | 4890 | 2.79581e+06 | 33413.3 | 0.00228261 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10951.6 | 0.109595 | 498.452ms | 56369 | 2560 | 74087.7 | 4908.66 | 0.125869 | 1(Win) | true |
| glaze | 2573.63 | 0.0847435 | 2093.63ms | 56369 | 4890 | 1.53218e+06 | 20887.8 | 0.0421896 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10014.4 | 0.466985 | 527.34ms | 56369 | 1280 | 804351 | 5368.03 | 0.437265 | 1(Win) | true |
| glaze | 2855.05 | 0.086192 | 1891.71ms | 56369 | 4890 | 1.28794e+06 | 18829 | 0.0918917 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2478.03 | 0.0506024 | 3320.81ms | 83958 | 40 | 10693.4 | 32311.4 | 0.169034 | 1(Win) | true |
| simdjson (ondemand) | 1979.35 | 0.0312063 | 4090.18ms | 83958 | 40 | 6374.2 | 40452.1 | 0.0532446 | 2(Loss) | true |
| glaze | 1942.67 | 0.0983721 | 4211.96ms | 83958 | 2560 | 4.20835e+06 | 41215.8 | 0.159171 | 3(Loss) | true |
| jsonifier (two-stage) | 1805.33 | 0.0684454 | 4439.67ms | 83958 | 4890 | 4.5062e+06 | 44351.3 | 0.167246 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2816.17 | 0.092135 | 2979.09ms | 83958 | 2560 | 1.75669e+06 | 28431.7 | 0.295222 | 1(Win) | true |
| jsonifier (two-stage) | 2285.82 | 0.0678509 | 4156.07ms | 83958 | 4890 | 2.76225e+06 | 35028.5 | 0.359234 | 2(Loss) | true |
| simdjson (ondemand) | 2280.03 | 0.0783504 | 3681.35ms | 83958 | 4890 | 3.70198e+06 | 35117.3 | 0.207678 | 3(Loss) | true |
| glaze | 2246.42 | 0.135566 | 3723.9ms | 83958 | 640 | 1.49425e+06 | 35642.7 | 0.40201 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 19125.3 | 0.0469253 | 479.702ms | 94370 | 160 | 780.166 | 4705.72 | 0.0665857 | 1(Win) | true |
| glaze | 2675.09 | 0.122206 | 3370.97ms | 94370 | 1280 | 2.16365e+06 | 33643.1 | 0.0564295 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 19813.7 | 0.110059 | 462.203ms | 94370 | 80 | 1999.31 | 4542.21 | 0.0112818 | 1(Win) | true |
| glaze | 2975.31 | 0.0874276 | 2985.4ms | 94370 | 4890 | 3.41987e+06 | 30248.4 | 0.143413 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1897.48 | 0.0280621 | 2704.77ms | 53331 | 30 | 1697.34 | 26804.2 | 0.130124 | 1(Win) | true |
| simdjson (ondemand) | 1590.85 | 0.145022 | 3248.44ms | 53331 | 1280 | 2.75158e+06 | 31970.7 | 0.0811631 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1541.22 | 0.0797118 | 3378.7ms | 53331 | 2560 | 1.7714e+06 | 33000.1 | 0.209186 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1538.41 | 0.0958295 | 3309.99ms | 53331 | 2560 | 2.56952e+06 | 33060.3 | 0.102818 | 3(Tie) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2631.21 | 0.0304804 | 2526.25ms | 53331 | 80 | 2777.02 | 19329.7 | 0.186154 | 1(Win) | true |
| simdjson (ondemand) | 2038.39 | 0.0467126 | 3017.37ms | 53331 | 30 | 4075.44 | 24951.3 | 0.000267187 | 2(Loss) | true |
| jsonifier (two-stage) | 2028.44 | 0.0979831 | 3100.01ms | 53331 | 2560 | 1.54517e+06 | 25073.6 | 0.0592792 | 3(Loss) | true |
| glaze | 1933.42 | 0.0977787 | 3142.9ms | 53331 | 2560 | 1.6937e+06 | 26305.9 | 0.166246 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15456 | 0.1006 | 368.099ms | 58581 | 160 | 2115.61 | 3614.6 | 0.0839636 | 1(Win) | true |
| glaze | 4021.33 | 0.130305 | 1397.9ms | 58581 | 2560 | 838951 | 13892.7 | 0.126226 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16312.1 | 0.187782 | 345.09ms | 58581 | 4890 | 202259 | 3424.89 | 0.115106 | 1(Win) | true |
| glaze | 4862.02 | 0.213274 | 1151.76ms | 58581 | 1280 | 768717 | 11490.5 | 0.00732207 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1876.75 | 0.0769626 | 3367.78ms | 65103 | 2560 | 1.65954e+06 | 33082.1 | 0.180098 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1873.07 | 0.102362 | 3329.94ms | 65103 | 2560 | 2.94719e+06 | 33147.2 | 0.0910703 | 1(Tie) | true |
| glaze | 1766.82 | 0.0660106 | 3675.31ms | 65103 | 4890 | 2.6312e+06 | 35140.6 | 0.351034 | 3(Loss) | true |
| jsonifier (two-stage) | 1702.96 | 0.485235 | 3592.04ms | 65103 | 80 | 2.50373e+06 | 36458.3 | 0.00257137 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2468.98 | 0.0665779 | 3110.79ms | 65103 | 40 | 11212.1 | 25146.8 | 0.159153 | 1(Win) | true |
| simdjson (ondemand) | 2355.71 | 0.0793823 | 3119.8ms | 65103 | 4890 | 2.1405e+06 | 26356 | 0.113496 | 2(Loss) | true |
| jsonifier (two-stage) | 2270.91 | 0.147707 | 3359.5ms | 65103 | 30 | 48924.6 | 27340.2 | 0.117029 | 3(Loss) | true |
| glaze | 2220.11 | 0.221585 | 3322.05ms | 65103 | 320 | 1.22881e+06 | 27965.8 | 0.0376435 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18080.6 | 0.0949062 | 422.498ms | 78778 | 40 | 622.062 | 4155.2 | 0.143389 | 1(Win) | true |
| glaze | 3636.47 | 0.069777 | 2102.66ms | 78778 | 30 | 6234.41 | 20659.7 | 0.18832 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 19912.8 | 0.118614 | 384.414ms | 78778 | 40 | 801.087 | 3772.88 | 0.128604 | 1(Win) | true |
| glaze | 4540.28 | 0.0701316 | 1698.25ms | 78778 | 30 | 4040.12 | 16547.1 | 0.041883 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2426.19 | 0.119038 | 470.961ms | 11812 | 30 | 916.414 | 4643 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 1283.17 | 0.0252455 | 894.772ms | 11812 | 160 | 785.902 | 8778.9 | 0.0562112 | 2(Loss) | true |
| glaze | 1061.73 | 0.262851 | 1073.7ms | 11812 | 80 | 62219.8 | 10609.9 | 0.221471 | 3(Loss) | true |
| simdjson (ondemand) | 1037.08 | 0.12161 | 1100.69ms | 11812 | 1280 | 223344 | 10862.1 | 0.0147064 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2591.26 | 0.0958248 | 463.127ms | 11812 | 30 | 520.599 | 4347.23 | 0.0322148 | 1(Win) | true |
| jsonifier (two-stage) | 1469.53 | 0.0495778 | 882.465ms | 11812 | 40 | 577.733 | 7665.6 | 0.00521839 | 2(Loss) | true |
| glaze | 1121.39 | 0.0986454 | 1028.63ms | 11812 | 4890 | 480172 | 10045.4 | 0.0909779 | 3(Loss) | true |
| simdjson (ondemand) | 1104.64 | 0.0359176 | 1058.41ms | 11812 | 160 | 2146.55 | 10197.7 | 0.0136692 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10473.6 | 0.183592 | 111.41ms | 11812 | 80 | 311.923 | 1075.54 | 0.0522721 | 1(Win) | true |
| glaze | 1828.88 | 0.0522103 | 675.247ms | 11812 | 80 | 827.329 | 6159.39 | 0.0338799 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10854.2 | 0.0493015 | 107.801ms | 11812 | 640 | 167.552 | 1037.83 | 0.0597346 | 1(Win) | true |
| glaze | 1970.26 | 0.095073 | 579.419ms | 11812 | 2560 | 75640.7 | 5717.43 | 0.0580525 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3141 | 0.0447211 | 782.022ms | 25388 | 30 | 356.506 | 7708.33 | 0.000432434 | 1(Win) | true |
| jsonifier (two-stage) | 2390.06 | 0.0419934 | 1028.18ms | 25388 | 40 | 723.871 | 10130.2 | 0.0384312 | 2(Loss) | true |
| simdjson (ondemand) | 2037.29 | 0.0732973 | 1241.2ms | 25388 | 4890 | 371052 | 11884.3 | 0.158676 | 3(Loss) | true |
| glaze | 1927.56 | 0.0543102 | 1276.86ms | 25388 | 160 | 7446 | 12560.9 | 0.00457749 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3265.14 | 0.0425372 | 776.215ms | 25388 | 30 | 298.478 | 7415.27 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 2674.2 | 0.198593 | 1017.18ms | 25388 | 640 | 206907 | 9053.89 | 0.0919476 | 2(Loss) | true |
| simdjson (ondemand) | 2148.48 | 0.101836 | 1149.1ms | 25388 | 4890 | 644036 | 11269.3 | 0.0851901 | 3(Loss) | true |
| glaze | 2006.4 | 0.0945741 | 1231.18ms | 25388 | 4890 | 636910 | 12067.4 | 0.0694366 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 21595.3 | 0.0433856 | 142.052ms | 31235 | 640 | 229.21 | 1379.37 | 0.00362471 | 1(Win) | true |
| glaze | 2922.47 | 0.0810526 | 1042.39ms | 31235 | 40 | 2730.09 | 10192.8 | 0.0442929 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 24684.7 | 0.0269022 | 125.046ms | 31235 | 1280 | 134.9 | 1206.74 | 0.023895 | 1(Win) | true |
| glaze | 3202.43 | 0.0261861 | 942.846ms | 31235 | 320 | 1898.53 | 9301.69 | 0.0097774 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2812.17 | 0.0757905 | 3760.71ms | 108313 | 2560 | 1.98403e+06 | 36731.5 | 0.0172261 | 1(Win) | true |
| jsonifier (two-stage) | 1771.24 | 0.111495 | 5835.68ms | 108313 | 2560 | 1.08232e+07 | 58318.1 | 0.228604 | 2(Loss) | true |
| glaze | 1637.21 | 0.0720616 | 6351.98ms | 108313 | 4890 | 1.01081e+07 | 63092.3 | 0.101322 | 3(Loss) | true |
| simdjson (ondemand) | 1297.73 | 0.0726541 | 8031.69ms | 108313 | 2560 | 8.56158e+06 | 79597.1 | 0.0653055 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3340.99 | 0.0662391 | 3311.52ms | 108313 | 4890 | 2.05092e+06 | 30917.6 | 0.280335 | 1(Win) | true |
| jsonifier (two-stage) | 1993.9 | 0.129048 | 5448.52ms | 108313 | 320 | 1.43024e+06 | 51805.6 | 0.00413186 | 2(Loss) | true |
| glaze | 1808.07 | 0.246618 | 5987.69ms | 108313 | 160 | 3.17616e+06 | 57130.2 | 0.0784789 | 3(Loss) | true |
| simdjson (ondemand) | 1415.06 | 0.016626 | 7654.85ms | 108313 | 30 | 4418.84 | 72997.3 | 0.0228723 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14131.9 | 0.0786799 | 744.529ms | 108313 | 160 | 5291.83 | 7309.36 | 0.0142817 | 1(Win) | true |
| glaze | 2076.02 | 0.0653273 | 4990.35ms | 108313 | 4890 | 5.16651e+06 | 49756.4 | 0.128097 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15000.9 | 0.066414 | 699.301ms | 108313 | 160 | 3346.32 | 6885.96 | 0.145343 | 1(Win) | true |
| glaze | 2232.14 | 0.0664198 | 4678.75ms | 108313 | 4890 | 4.6198e+06 | 46276.4 | 0.0564859 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2832.06 | 0.0534289 | 6248.74ms | 183677 | 4890 | 5.3403e+06 | 61851.8 | 0.0249031 | 1(Win) | true |
| jsonifier (two-stage) | 2574.22 | 0.100326 | 6830.53ms | 183677 | 1280 | 5.96561e+06 | 68047 | 0.14469 | 2(Loss) | true |
| glaze | 2191.03 | 0.118174 | 8120.54ms | 183677 | 160 | 1.42816e+06 | 79947.6 | 0.161507 | 3(Loss) | true |
| simdjson (ondemand) | 2076.96 | 0.0650129 | 8505.42ms | 183677 | 2560 | 7.69649e+06 | 84338.7 | 0.0241801 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3134.34 | 0.146815 | 5944.15ms | 183677 | 640 | 4.30862e+06 | 55886.8 | 0.356913 | 1(Win) | true |
| jsonifier (two-stage) | 2825.38 | 0.0736718 | 6495.66ms | 183677 | 2560 | 5.34072e+06 | 61998.1 | 0.058076 | 2(Loss) | true |
| glaze | 2346.33 | 0.0502672 | 7702.58ms | 183677 | 4890 | 6.88666e+06 | 74656.1 | 0.0253654 | 3(Loss) | true |
| simdjson (ondemand) | 2229.62 | 0.0908972 | 8086.96ms | 183677 | 2560 | 1.30554e+07 | 78564.1 | 0.258505 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 24905.3 | 0.125645 | 832.232ms | 213963 | 30 | 3179.1 | 8193.07 | 0.0683972 | 1(Win) | true |
| glaze | 2386.13 | 0.0862083 | 8624.29ms | 213963 | 1280 | 6.95664e+06 | 85515.6 | 0.0769789 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 25532.4 | 0.128444 | 809.389ms | 213963 | 30 | 3161.11 | 7991.83 | 0.0893375 | 1(Win) | true |
| glaze | 2570.28 | 0.141029 | 8009.91ms | 213963 | 640 | 8.02257e+06 | 79388.6 | 0.0979207 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 719.511 | 0.127467 | 7677.67ms | 1834197 | 80 | 7.68246e+08 | 2.43113e+06 | 0.0180267 | 1(Win) | true |
| jsonifier (two-stage) | 615.882 | 0.23613 | 8849.5ms | 1834197 | 30 | 1.34934e+09 | 2.8402e+06 | 0.0670402 | 2(Loss) | true |
| glaze | 515.67 | 0.12516 | 5146.55ms | 1834197 | 80 | 1.442e+09 | 3.39214e+06 | 0.197089 | 3(Loss) | true |
| simdjson (ondemand) | 445.911 | 0.151813 | 5897.26ms | 1834197 | 40 | 1.41865e+09 | 3.92281e+06 | 0.0234706 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 833.755 | 0.194239 | 7608.93ms | 1834197 | 40 | 6.64271e+08 | 2.09801e+06 | 0.0229193 | 1(Win) | true |
| jsonifier (two-stage) | 698.889 | 0.1977 | 8865.86ms | 1834197 | 40 | 9.79372e+08 | 2.50287e+06 | 0.0717996 | 2(Loss) | true |
| glaze | 571.527 | 0.176478 | 5200.9ms | 1834197 | 40 | 1.16698e+09 | 3.06062e+06 | 0.426183 | 3(Loss) | true |
| simdjson (ondemand) | 483.358 | 0.640835 | 5942.21ms | 1834197 | 30 | 1.61349e+10 | 3.6189e+06 | 0.210598 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1542.4 | 0.146175 | 7199.96ms | 1834197 | 320 | 8.79417e+08 | 1.1341e+06 | 0.0899432 | 1(Win) | true |
| glaze | 946.558 | 0.21121 | 5730.15ms | 1833577 | 160 | 2.43588e+09 | 1.84736e+06 | 0.152891 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1544.2 | 0.115304 | 7156.24ms | 1834197 | 320 | 5.45916e+08 | 1.13277e+06 | 0.111109 | 1(Win) | true |
| glaze | 946.253 | 0.358816 | 5791.92ms | 1833577 | 30 | 1.31901e+09 | 1.84796e+06 | 1.16629 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2106.19 | 0.391685 | 5068.23ms | 7351818 | 30 | 5.10025e+09 | 3.32888e+06 | 0.0220373 | 1(Win) | true |
| jsonifier (two-stage) | 2077.16 | 0.119974 | 5078.29ms | 7351818 | 80 | 1.31194e+09 | 3.37539e+06 | 0.138854 | 2(Loss) | true |
| glaze | 1639.78 | 0.170749 | 6550.44ms | 7351818 | 80 | 4.26412e+09 | 4.27573e+06 | 0.196592 | 3(Loss) | true |
| simdjson (ondemand) | 1553.23 | 0.27373 | 6759.86ms | 7351818 | 80 | 1.22139e+10 | 4.51397e+06 | 0.41939 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2333.12 | 0.233855 | 5059.76ms | 7351818 | 80 | 3.95093e+09 | 3.00509e+06 | 0.0389911 | 1(Win) | true |
| jsonifier (two-stage) | 2301.69 | 0.190142 | 5123.93ms | 7351818 | 30 | 1.00641e+09 | 3.04613e+06 | 0.00880431 | 2(Loss) | true |
| glaze | 1776 | 0.211192 | 6463.34ms | 7351818 | 30 | 2.08535e+09 | 3.94777e+06 | 0.354248 | 3(Loss) | true |
| simdjson (ondemand) | 1677.89 | 0.130173 | 6804.44ms | 7351818 | 80 | 2.367e+09 | 4.17862e+06 | 0.375985 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7460.46 | 0.174979 | 8044.38ms | 9930848 | 160 | 7.89466e+08 | 1.26946e+06 | 0.0466445 | 1(Win) | true |
| glaze | 3422.3 | 0.179351 | 8662.71ms | 9930228 | 80 | 1.97053e+09 | 2.7672e+06 | 0.049775 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7420.44 | 0.119043 | 8062.03ms | 9930848 | 320 | 7.38704e+08 | 1.27631e+06 | 0.586545 | 1(Win) | true |
| glaze | 3543.29 | 0.242532 | 8359.47ms | 9930228 | 30 | 1.26057e+09 | 2.67272e+06 | 0.0366978 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 722.867 | 0.209899 | 7528.39ms | 1834197 | 160 | 4.12778e+09 | 2.41985e+06 | 0.467953 | 1(Win) | true |
| jsonifier (two-stage) | 620.851 | 0.249351 | 8790.77ms | 1834197 | 30 | 1.48067e+09 | 2.81746e+06 | 0.163197 | 2(Loss) | true |
| glaze | 519.329 | 0.104086 | 5117.06ms | 1834197 | 80 | 9.83283e+08 | 3.36824e+06 | 1.53205 | 3(Loss) | true |
| simdjson (ondemand) | 446.286 | 0.108273 | 5911.17ms | 1834197 | 80 | 1.44078e+09 | 3.91952e+06 | 0.124646 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 836.673 | 0.349184 | 7526.91ms | 1834197 | 80 | 4.26362e+09 | 2.09069e+06 | 0.275736 | 1(Win) | true |
| jsonifier (two-stage) | 704.836 | 0.131426 | 8781.63ms | 1834197 | 80 | 8.51079e+08 | 2.48175e+06 | 0.0716142 | 2(Loss) | true |
| glaze | 573.34 | 0.175926 | 5069.44ms | 1834197 | 40 | 1.15236e+09 | 3.05094e+06 | 0.17072 | 3(Loss) | true |
| simdjson (ondemand) | 488.129 | 0.223373 | 5923.08ms | 1834197 | 80 | 5.12594e+09 | 3.58354e+06 | 0.0781959 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1555.99 | 0.296759 | 7124.41ms | 1834197 | 80 | 8.90375e+08 | 1.12419e+06 | 0.140898 | 1(Win) | true |
| glaze | 928.454 | 0.213173 | 5899.96ms | 1833577 | 80 | 1.28953e+09 | 1.88338e+06 | 0.252178 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1563.57 | 0.243737 | 7091.01ms | 1834197 | 80 | 5.94828e+08 | 1.11874e+06 | 0.114052 | 1(Win) | true |
| glaze | 948.598 | 0.159 | 5840.79ms | 1833577 | 160 | 1.37451e+09 | 1.84339e+06 | 0.533291 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2182.69 | 0.0813717 | 10039.6ms | 7351818 | 160 | 1.09313e+09 | 3.2122e+06 | 0.0269295 | 1(Win) | true |
| jsonifier (two-stage) | 2083.14 | 0.304193 | 5049.14ms | 7351818 | 80 | 8.38575e+09 | 3.36571e+06 | 0.11095 | 2(Loss) | true |
| glaze | 1645.61 | 0.150843 | 6455.04ms | 7351818 | 40 | 1.65213e+09 | 4.26057e+06 | 0.0712073 | 3(Loss) | true |
| simdjson (ondemand) | 1547.71 | 0.50955 | 6759.72ms | 7351818 | 30 | 1.59848e+10 | 4.53008e+06 | 0.415063 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2426.76 | 0.251852 | 10037.4ms | 7351818 | 30 | 1.58837e+09 | 2.88914e+06 | 0.190685 | 1(Win) | true |
| jsonifier (two-stage) | 2322.34 | 0.135172 | 5078.16ms | 7351818 | 80 | 1.33229e+09 | 3.01904e+06 | 0.1083 | 2(Loss) | true |
| glaze | 1784.72 | 0.220767 | 6437.7ms | 7351818 | 30 | 2.25651e+09 | 3.92847e+06 | 0.286236 | 3(Loss) | true |
| simdjson (ondemand) | 1688.33 | 0.178416 | 6827.3ms | 7351818 | 80 | 4.39173e+09 | 4.15277e+06 | 0.0751674 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7608.22 | 0.237015 | 7903.68ms | 9930848 | 30 | 2.61145e+08 | 1.24481e+06 | 0.106445 | 1(Win) | true |
| glaze | 3064.68 | 0.113033 | 9645.8ms | 9930228 | 80 | 9.75988e+08 | 3.09011e+06 | 0.0125776 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7575.61 | 0.125109 | 7871.53ms | 9930848 | 320 | 7.82821e+08 | 1.25017e+06 | 0.245088 | 1(Win) | true |
| glaze | 3527.5 | 0.116985 | 8352.18ms | 9930228 | 160 | 1.5782e+09 | 2.68468e+06 | 0.0635743 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1312.56 | 0.0751484 | 8579.16ms | 461466 | 1280 | 8.12624e+07 | 335290 | 0.103028 | 1(Win) | true |
| jsonifier (two-stage) | 1006.42 | 0.206551 | 5591.09ms | 461466 | 160 | 1.30527e+08 | 437283 | 0.0896934 | 2(Loss) | true |
| simdjson (ondemand) | 902.053 | 0.259861 | 6255.4ms | 461466 | 40 | 6.42921e+07 | 487874 | 0.00919721 | 3(Loss) | true |
| glaze | 871.43 | 0.134895 | 6455.29ms | 461466 | 640 | 2.9702e+08 | 505018 | 0.199695 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1788.72 | 0.0987462 | 8322ms | 461466 | 640 | 3.7776e+07 | 246035 | 0.124875 | 1(Win) | true |
| jsonifier (two-stage) | 1384.65 | 0.182365 | 5372.26ms | 461466 | 160 | 5.37529e+07 | 317833 | 0.171847 | 2(Loss) | true |
| simdjson (ondemand) | 1089.14 | 0.169764 | 6120.85ms | 461466 | 320 | 1.50575e+08 | 404069 | 0.00519068 | 3(Loss) | true |
| glaze | 1048.48 | 0.102091 | 6330.75ms | 461466 | 640 | 1.17519e+08 | 419738 | 0.129547 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11084.8 | 0.159349 | 4010.14ms | 461466 | 1280 | 5.1231e+06 | 39702 | 0.27202 | 1(Win) | true |
| glaze | 2324.45 | 0.0801536 | 9735.23ms | 461466 | 1280 | 2.94777e+07 | 189330 | 0.207722 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11172.1 | 0.0867353 | 3956.87ms | 461466 | 2560 | 2.98841e+06 | 39391.6 | 0.0240614 | 1(Win) | true |
| glaze | 2464.92 | 0.0686254 | 9135.12ms | 461466 | 2560 | 3.84313e+07 | 178541 | 0.252317 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1659.12 | 0.125431 | 5385.14ms | 728486 | 640 | 1.76553e+08 | 418738 | 0.196038 | 1(Win) | true |
| simdjson (ondemand) | 1331.89 | 0.141955 | 6653.52ms | 728486 | 640 | 3.50901e+08 | 521619 | 0.00466688 | 2(Loss) | true |
| glaze | 1287.9 | 0.189386 | 6901.98ms | 728486 | 160 | 1.66991e+08 | 539435 | 0.138749 | 3(Loss) | true |
| jsonifier (two-stage) | 1259.17 | 0.209906 | 7020.75ms | 728486 | 160 | 2.14608e+08 | 551745 | 0.150407 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2111.66 | 0.138311 | 5166.57ms | 728486 | 640 | 1.32521e+08 | 329001 | 0.018486 | 1(Win) | true |
| jsonifier (two-stage) | 1811.04 | 0.136183 | 6882.37ms | 728486 | 640 | 1.74668e+08 | 383613 | 0.00883014 | 2(Loss) | true |
| simdjson (ondemand) | 1607.85 | 0.166196 | 6474.41ms | 728486 | 30 | 1.54707e+07 | 432090 | 0.00128058 | 3(Loss) | true |
| glaze | 1541.34 | 0.156437 | 6706.28ms | 728486 | 640 | 3.18202e+08 | 450735 | 0.223158 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14552.4 | 0.101289 | 5485.68ms | 837491 | 2560 | 7.91148e+06 | 54883.9 | 0.095298 | 1(Win) | true |
| glaze | 2675.66 | 0.070503 | 7689.9ms | 837491 | 1280 | 5.66921e+07 | 298503 | 0.40745 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17982.6 | 0.158431 | 4502.43ms | 837491 | 1280 | 6.33795e+06 | 44414.8 | 0.0623245 | 1(Win) | true |
| glaze | 2868.08 | 0.098152 | 7138.16ms | 837491 | 1280 | 9.56283e+07 | 278477 | 0.166955 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4949.34 | 0.309995 | 9114.06ms | 466906 | 30 | 2.33343e+06 | 89966.8 | 0.0105213 | 1(Win) | true |
| jsonifier | 4905.64 | 0.0976335 | 9127.34ms | 466906 | 2560 | 2.01051e+07 | 90768.3 | 0.231781 | 2(Loss) | true |
| simdjson (ondemand) | 4286.36 | 0.193805 | 5379.79ms | 466906 | 160 | 6.48536e+06 | 103882 | 0.135511 | 3(Loss) | true |
| glaze | 2434.27 | 0.0639889 | 9414.74ms | 466906 | 2560 | 3.50728e+07 | 182920 | 0.0495329 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 5022.07 | 0.151918 | 9039.8ms | 466906 | 640 | 1.16116e+07 | 88663.8 | 0.019612 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 5005.59 | 0.106479 | 9091.14ms | 466906 | 2560 | 2.29677e+07 | 88955.9 | 0.129186 | 1(Tie) | true |
| simdjson (ondemand) | 4383.56 | 0.193603 | 5304.13ms | 466906 | 80 | 3.094e+06 | 101579 | 0.0764894 | 3(Loss) | true |
| glaze | 2460.51 | 0.090282 | 9455.52ms | 466906 | 1280 | 3.4168e+07 | 180969 | 0.171073 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 5471.04 | 0.180184 | 5715.54ms | 631514 | 80 | 3.14736e+06 | 110081 | 0.00659697 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 5450.72 | 0.606525 | 5794.19ms | 631514 | 30 | 1.34734e+07 | 110492 | 0.297466 | 1(Tie) | true |
| simdjson (ondemand) | 5041.89 | 0.0797398 | 6132.48ms | 631514 | 1280 | 1.16129e+07 | 119451 | 0.072327 | 3(Loss) | true |
| glaze | 3019.34 | 0.166455 | 5102.78ms | 631514 | 320 | 3.52766e+07 | 199467 | 0.089482 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 5537.77 | 0.0732412 | 5700.24ms | 631514 | 2560 | 1.62423e+07 | 108755 | 0.251155 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 5529.56 | 0.081601 | 5660.57ms | 631514 | 2560 | 2.02217e+07 | 108916 | 0.0168449 | 1(Tie) | true |
| simdjson (ondemand) | 5151.71 | 0.149916 | 6132.69ms | 631514 | 160 | 4.91453e+06 | 116905 | 0.365343 | 3(Loss) | true |
| glaze | 3052.1 | 0.104164 | 5128.61ms | 631514 | 640 | 2.70384e+07 | 197326 | 0.113438 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2364.07 | 0.150357 | 9712.81ms | 466906 | 320 | 2.56646e+07 | 188352 | 0.149929 | 1(Win) | true |
| jsonifier (two-stage) | 1788.42 | 0.113707 | 6492.61ms | 466906 | 640 | 5.12949e+07 | 248978 | 0.914216 | 2(Loss) | true |
| glaze | 1773.79 | 0.11298 | 6433.62ms | 466906 | 320 | 2.57402e+07 | 251032 | 0.108687 | 3(Loss) | true |
| simdjson (ondemand) | 1699.61 | 0.121357 | 6729.65ms | 466906 | 640 | 6.46944e+07 | 261987 | 0.00929884 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3037.86 | 0.102348 | 8953.6ms | 466906 | 1280 | 2.88068e+07 | 146575 | 0.311119 | 1(Win) | true |
| jsonifier (two-stage) | 2216.48 | 0.241254 | 6018.99ms | 466906 | 160 | 3.75837e+07 | 200894 | 0.178978 | 2(Loss) | true |
| glaze | 2132.55 | 0.112335 | 6093.21ms | 466906 | 640 | 3.52105e+07 | 208800 | 0.227967 | 3(Loss) | true |
| simdjson (ondemand) | 1996.05 | 0.244589 | 6342.14ms | 466906 | 40 | 1.19084e+07 | 223079 | 0.0448771 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16216.3 | 0.0707146 | 2823.36ms | 475954 | 4890 | 1.91582e+06 | 27990.7 | 0.0983904 | 1(Win) | true |
| glaze | 4193.57 | 0.0938425 | 5599.72ms | 475954 | 1280 | 1.3206e+07 | 108238 | 0.229396 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16454.9 | 0.0612867 | 2788.71ms | 475954 | 30 | 8574.19 | 27584.8 | 0.100317 | 1(Win) | true |
| glaze | 4636.66 | 0.112177 | 5050.6ms | 475954 | 640 | 7.71804e+06 | 97894.9 | 0.185214 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2316.11 | 0.0987196 | 6641.65ms | 631514 | 1280 | 8.43458e+07 | 260030 | 0.0104257 | 1(Win) | true |
| jsonifier (two-stage) | 2217.16 | 0.10605 | 7117.89ms | 631514 | 320 | 2.65546e+07 | 271635 | 0.106065 | 2(Loss) | true |
| simdjson (ondemand) | 2165.49 | 0.133591 | 7140.37ms | 631514 | 640 | 8.83462e+07 | 278116 | 0.0404927 | 3(Loss) | true |
| glaze | 1990.64 | 0.108434 | 7791.1ms | 631514 | 640 | 6.88798e+07 | 302545 | 0.190224 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2790.16 | 0.129623 | 6242.89ms | 631514 | 1280 | 1.00204e+08 | 215851 | 0.206821 | 1(Win) | true |
| jsonifier (two-stage) | 2681.26 | 0.19077 | 6669.09ms | 631514 | 1280 | 2.35028e+08 | 224617 | 0.0236214 | 2(Loss) | true |
| simdjson (ondemand) | 2502.15 | 0.338628 | 6772.67ms | 631514 | 40 | 2.65734e+07 | 240697 | 0.0257548 | 3(Loss) | true |
| glaze | 2316.74 | 0.0938456 | 7376.73ms | 631514 | 1280 | 7.61814e+07 | 259959 | 0.115629 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18290.3 | 0.110783 | 3772.98ms | 716365 | 2560 | 4.38345e+06 | 37352 | 0.144363 | 1(Win) | true |
| glaze | 4173.23 | 0.0648147 | 8384.89ms | 716365 | 2560 | 2.88212e+07 | 163705 | 0.177388 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18509 | 0.0799932 | 3693.88ms | 716365 | 4890 | 4.26305e+06 | 36910.7 | 0.0125773 | 1(Win) | true |
| glaze | 4830.43 | 0.109779 | 7304.68ms | 716365 | 640 | 1.54281e+07 | 141432 | 0.038537 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1683.92 | 0.149399 | 154.056ms | 2632 | 80 | 396.747 | 1490.61 | 0.000838574 | 1(Win) | true |
| jsonifier (two-stage) | 1378.63 | 0.0487656 | 187.272ms | 2632 | 640 | 504.525 | 1820.7 | 0.0139046 | 2(Loss) | true |
| glaze | 1184.6 | 0.0959868 | 216.033ms | 2632 | 4890 | 20228.3 | 2118.92 | 0.0168847 | 3(Loss) | true |
| simdjson (ondemand) | 1040.44 | 0.0660034 | 250.292ms | 2632 | 320 | 811.373 | 2412.51 | 0.160493 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2264.46 | 0.0772977 | 137.178ms | 2632 | 640 | 469.849 | 1108.47 | 0.0112756 | 1(Win) | true |
| jsonifier (two-stage) | 1780.92 | 0.278326 | 171.371ms | 2632 | 40 | 615.533 | 1409.42 | 0.276882 | 2(Loss) | true |
| glaze | 1647.09 | 0.121669 | 178.05ms | 2632 | 640 | 2200.27 | 1523.94 | 0.00205056 | 3(Loss) | true |
| simdjson (ondemand) | 1426.63 | 0.0526723 | 203.46ms | 2632 | 640 | 549.662 | 1759.44 | 0.115226 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8698.86 | 0.23937 | 32.1984ms | 2632 | 640 | 305.328 | 288.552 | 0.89141 | 1(Win) | true |
| glaze | 2698.91 | 0.0939216 | 96.6778ms | 2632 | 640 | 488.32 | 930.03 | 0.0623689 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10215.9 | 0.210837 | 27.6732ms | 2632 | 640 | 171.746 | 245.702 | 0.215118 | 1(Win) | true |
| glaze | 3207.11 | 0.133451 | 82.486ms | 2632 | 320 | 349.091 | 782.659 | 0.00519037 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1698.88 | 0.116847 | 193.005ms | 3370 | 2560 | 12508.5 | 1891.76 | 0.297241 | 1(Win) | true |
| jsonifier (two-stage) | 1649.79 | 0.14344 | 210.895ms | 3370 | 4890 | 38181.5 | 1948.05 | 0.130042 | 2(Loss) | true |
| glaze | 1454.48 | 0.072176 | 226.565ms | 3370 | 320 | 813.921 | 2209.65 | 0.0579507 | 3(Loss) | true |
| simdjson (ondemand) | 1292.67 | 0.0881634 | 252.784ms | 3370 | 320 | 1537.49 | 2486.24 | 0.339638 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2174.31 | 0.111683 | 178.774ms | 3370 | 160 | 436.03 | 1478.12 | 0.0359539 | 1(Win) | true |
| jsonifier (two-stage) | 2098.52 | 0.0697013 | 184.093ms | 3370 | 320 | 364.639 | 1531.5 | 0.0336567 | 2(Loss) | true |
| glaze | 2003.51 | 0.279211 | 185.75ms | 3370 | 40 | 802.42 | 1604.12 | 0.0897918 | 3(Loss) | true |
| simdjson (ondemand) | 1746.4 | 0.0533332 | 210.582ms | 3370 | 640 | 616.523 | 1840.29 | 0.00297176 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11630.9 | 0.433179 | 33.4407ms | 3643 | 160 | 267.882 | 298.706 | 0.406352 | 1(Win) | true |
| glaze | 3085.95 | 0.102713 | 119.146ms | 3682 | 320 | 437.113 | 1137.88 | 0.150821 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13568.1 | 0.114501 | 28.715ms | 3643 | 2560 | 220.056 | 256.058 | 0.179572 | 1(Win) | true |
| glaze | 3536.75 | 0.107916 | 103.207ms | 3682 | 320 | 367.351 | 992.841 | 0.0658268 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 783.82 | 0.106866 | 570.485ms | 4630 | 40 | 1449.66 | 5633.32 | 0.0716942 | 1(Win) | true |
| jsonifier (two-stage) | 714.581 | 0.126046 | 630.515ms | 4630 | 30 | 1819.87 | 6179.17 | 0.0907093 | 2(Loss) | true |
| glaze | 507.137 | 0.0320589 | 882.41ms | 4630 | 160 | 1246.6 | 8706.75 | 0.00545524 | 3(Loss) | true |
| simdjson (ondemand) | 469.877 | 0.0627905 | 955.941ms | 4630 | 30 | 1044.49 | 9397.17 | 0.0747893 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 967.716 | 0.102803 | 573.412ms | 4630 | 1280 | 28163.5 | 4562.82 | 0.00414372 | 1(Win) | true |
| jsonifier (two-stage) | 872.4 | 0.0300539 | 624.545ms | 4630 | 320 | 740.426 | 5061.34 | 0.00759376 | 2(Loss) | true |
| glaze | 576.144 | 0.0580046 | 880.907ms | 4630 | 30 | 592.852 | 7663.9 | 0.0169655 | 3(Loss) | true |
| simdjson (ondemand) | 529.726 | 0.0494747 | 988.803ms | 4630 | 80 | 1360.56 | 8335.46 | 0.0115484 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2766.41 | 0.0586402 | 165.003ms | 4630 | 640 | 560.66 | 1596.12 | 0.016052 | 1(Win) | true |
| glaze | 1649.04 | 0.0560022 | 274.887ms | 4630 | 160 | 359.772 | 2677.62 | 0.0394318 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2847.75 | 0.132626 | 160.679ms | 4630 | 80 | 338.303 | 1550.53 | 0.0982571 | 1(Win) | true |
| glaze | 1898.13 | 0.0380664 | 237.663ms | 4630 | 640 | 501.846 | 2326.24 | 0.0312908 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1589.88 | 0.0419368 | 704.719ms | 11579 | 160 | 1357.45 | 6945.57 | 0.0645612 | 1(Win) | true |
| jsonifier (two-stage) | 1556.89 | 0.0772215 | 759.852ms | 11579 | 40 | 1199.95 | 7092.73 | 0.063053 | 2(Loss) | true |
| simdjson (ondemand) | 1092.76 | 0.0427527 | 1022.72ms | 11579 | 80 | 1493.17 | 10105.2 | 0.0840617 | 3(Loss) | true |
| glaze | 1078.54 | 0.127655 | 1032.18ms | 11579 | 1280 | 218654 | 10238.5 | 0.0158537 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1884.78 | 0.0513125 | 704.51ms | 11579 | 80 | 723.032 | 5858.82 | 0.0967687 | 1(Win) | true |
| jsonifier (two-stage) | 1850.99 | 0.0845817 | 717.475ms | 11579 | 1280 | 32591 | 5965.78 | 0.286818 | 2(Loss) | true |
| simdjson (ondemand) | 1223.56 | 0.0568848 | 1061.75ms | 11579 | 40 | 1054.26 | 9025 | 0.0776225 | 3(Loss) | true |
| glaze | 1209.77 | 0.0653205 | 1028.06ms | 11579 | 30 | 1066.49 | 9127.83 | 0.0160707 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8074.62 | 0.0531826 | 179.282ms | 14795 | 320 | 276.36 | 1747.4 | 0.0602317 | 1(Win) | true |
| glaze | 3376.28 | 0.0264565 | 420.685ms | 14795 | 640 | 782.344 | 4179.04 | 0.00998185 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8442.63 | 0.0522903 | 172.233ms | 14795 | 320 | 244.381 | 1671.23 | 0.0551309 | 1(Win) | true |
| glaze | 3920.34 | 0.0893625 | 369.318ms | 14795 | 40 | 413.763 | 3599.07 | 0.0256944 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1289.64 | 0.179956 | 243.945ms | 3223 | 40 | 735.83 | 2383.38 | 0.0583565 | 1(Win) | true |
| jsonifier (two-stage) | 990.139 | 0.172747 | 315.348ms | 3223 | 320 | 9202.35 | 3104.3 | 0.0367299 | 2(Loss) | true |
| glaze | 909.251 | 0.210496 | 345.594ms | 3223 | 30 | 1519.02 | 3380.47 | 0.0423825 | 3(Loss) | true |
| simdjson (ondemand) | 854.545 | 0.162756 | 368.432ms | 3223 | 40 | 1370.83 | 3596.88 | 0.316631 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2034.47 | 0.0769056 | 205.762ms | 3223 | 320 | 432 | 1510.81 | 0.080734 | 1(Win) | true |
| jsonifier (two-stage) | 1434.05 | 0.0646385 | 278.785ms | 3223 | 320 | 614.218 | 2143.36 | 0.0403701 | 2(Loss) | true |
| glaze | 1212.71 | 0.152144 | 302.191ms | 3223 | 2560 | 38067.7 | 2534.57 | 0.285982 | 3(Loss) | true |
| simdjson (ondemand) | 1120.81 | 0.0439308 | 322.959ms | 3223 | 640 | 928.905 | 2742.38 | 0.0724121 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8146.42 | 0.107216 | 40.9598ms | 3223 | 2560 | 418.936 | 377.306 | 0.174144 | 1(Win) | true |
| glaze | 1912.97 | 0.126367 | 164.295ms | 3223 | 4890 | 20159.5 | 1606.76 | 0.0703143 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9690.84 | 0.368344 | 34.8665ms | 3223 | 320 | 436.772 | 317.175 | 0.157891 | 1(Win) | true |
| glaze | 2211.21 | 0.131174 | 144.165ms | 3223 | 160 | 531.96 | 1390.05 | 0.0754798 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1745.48 | 0.0467394 | 325.899ms | 5839 | 320 | 711.479 | 3190.24 | 0.0291821 | 1(Win) | true |
| jsonifier (two-stage) | 1626.29 | 0.12208 | 369.68ms | 5839 | 40 | 698.921 | 3424.05 | 0.0102229 | 2(Loss) | true |
| simdjson (ondemand) | 1463.85 | 0.0453325 | 388.271ms | 5839 | 320 | 951.604 | 3804.03 | 0.00377875 | 3(Loss) | true |
| glaze | 1378.51 | 0.173214 | 414.702ms | 5839 | 40 | 1958.31 | 4039.5 | 0.0189756 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2420.98 | 0.174213 | 284.613ms | 5839 | 1280 | 20552.7 | 2300.11 | 0.0534228 | 1(Win) | true |
| jsonifier (two-stage) | 2296.05 | 0.255028 | 309.233ms | 5839 | 2560 | 97932.6 | 2425.25 | 0.0684223 | 2(Loss) | true |
| simdjson (ondemand) | 1887.96 | 0.0694587 | 342.901ms | 5839 | 1280 | 5372.21 | 2949.48 | 0.128073 | 3(Loss) | true |
| glaze | 1750.95 | 0.137638 | 370.908ms | 5839 | 1280 | 24525.3 | 3180.27 | 0.02974 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16141.3 | 0.148983 | 44.0358ms | 6938 | 1280 | 477.392 | 409.916 | 0.0367969 | 1(Win) | true |
| glaze | 2471.69 | 0.170196 | 274.33ms | 6960 | 80 | 1671.16 | 2685.44 | 0.0404798 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18922 | 0.230948 | 38.0089ms | 6938 | 640 | 417.39 | 349.677 | 0.313321 | 1(Win) | true |
| glaze | 2858.29 | 0.0823394 | 237.263ms | 6960 | 640 | 2339.92 | 2322.22 | 0.112627 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2223.07 | 0.097892 | 211.513ms | 4857 | 160 | 665.649 | 2083.61 | 0.00989772 | 1(Win) | true |
| glaze | 1412.53 | 0.185423 | 335.341ms | 4857 | 80 | 2957.71 | 3279.21 | 0.0933042 | 2(Loss) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1307.82 | 0.0841797 | 357.475ms | 4857 | 40 | 355.563 | 3541.78 | 0.00305882 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1306.35 | 0.161577 | 360.895ms | 4857 | 40 | 1312.91 | 3545.75 | 0.273288 | 3(Tie) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2901.87 | 0.0741808 | 186.947ms | 4857 | 320 | 448.657 | 1596.21 | 0.106223 | 1(Win) | true |
| glaze | 1854.39 | 0.417577 | 262.979ms | 4857 | 2560 | 278514 | 2497.86 | 0.0889521 | 2(Loss) | true |
| jsonifier (two-stage) | 1768.11 | 0.0818365 | 322.919ms | 4857 | 80 | 367.709 | 2619.75 | 0.0800961 | 3(Loss) | true |
| simdjson (ondemand) | 1681.79 | 0.136241 | 292.201ms | 4857 | 80 | 1126.42 | 2754.2 | 0.0381091 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11250 | 0.138919 | 44.4252ms | 4857 | 640 | 209.379 | 411.733 | 0.0672155 | 1(Win) | true |
| glaze | 2443.92 | 0.146395 | 197.482ms | 4857 | 80 | 615.888 | 1895.31 | 0.0283675 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12473.6 | 0.198027 | 40.3843ms | 4857 | 320 | 173.041 | 371.344 | 0.139891 | 1(Win) | true |
| glaze | 2943.69 | 0.115918 | 162.227ms | 4857 | 320 | 1064.64 | 1573.53 | 0.0442676 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2209.89 | 0.0444455 | 294.269ms | 6701 | 320 | 528.621 | 2891.81 | 0.202318 | 1(Win) | true |
| simdjson (ondemand) | 1735.48 | 0.149756 | 380.786ms | 6701 | 40 | 1216.37 | 3682.3 | 0.313283 | 2(Loss) | true |
| glaze | 1685.3 | 0.121521 | 383.832ms | 6701 | 2560 | 54358 | 3791.94 | 0.0220809 | 3(Loss) | true |
| jsonifier (two-stage) | 1667.91 | 0.035273 | 389.536ms | 6701 | 320 | 584.483 | 3831.49 | 0.013048 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2325.19 | 0.534584 | 300.673ms | 6701 | 1280 | 276315 | 2748.41 | 0.878147 | 1(Win) | true |
| glaze | 2246.29 | 0.226778 | 301.706ms | 6701 | 1280 | 53279.1 | 2844.94 | 0.35913 | 2(Loss) | true |
| simdjson (ondemand) | 2220.72 | 0.142634 | 303.068ms | 6701 | 1280 | 21564.9 | 2877.7 | 0.155258 | 3(Loss) | true |
| jsonifier (two-stage) | 2178.78 | 0.0893683 | 349.492ms | 6701 | 4890 | 33599.3 | 2933.1 | 0.0211823 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16705.1 | 0.17683 | 45.4327ms | 7376 | 320 | 177.422 | 421.087 | 0.0593349 | 1(Win) | true |
| glaze | 2577.39 | 0.189175 | 282.578ms | 7376 | 30 | 799.702 | 2729.23 | 0.0586589 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18399.4 | 0.34282 | 41.426ms | 7376 | 160 | 274.845 | 382.312 | 0.410374 | 1(Win) | true |
| glaze | 2788.81 | 0.15381 | 259.736ms | 7376 | 30 | 451.54 | 2522.33 | 0.168116 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1760.28 | 0.080438 | 96.0448ms | 1691 | 640 | 347.558 | 916.141 | 0.197548 | 1(Win) | true |
| simdjson (ondemand) | 1548.22 | 0.201128 | 108.851ms | 1691 | 80 | 351.123 | 1041.62 | 0.395171 | 2(Loss) | true |
| glaze | 1409.62 | 0.179662 | 119.207ms | 1691 | 160 | 675.954 | 1144.04 | 0.512528 | 3(Loss) | true |
| jsonifier (two-stage) | 1323.61 | 0.0947714 | 124.933ms | 1691 | 320 | 426.651 | 1218.38 | 0.133452 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2580 | 0.29355 | 81.8486ms | 1691 | 2560 | 8618.94 | 625.064 | 1.18901 | 1(Win) | true |
| simdjson (ondemand) | 1980.56 | 0.066391 | 96.8787ms | 1691 | 4890 | 1429.01 | 814.244 | 0.0618443 | 2(Loss) | true |
| jsonifier (two-stage) | 1825.59 | 0.351774 | 111.369ms | 1691 | 30 | 289.689 | 883.367 | 0.00377358 | 3(Loss) | true |
| glaze | 1783.62 | 0.311283 | 107.508ms | 1691 | 80 | 633.699 | 904.15 | 0.349612 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10215.9 | 0.468332 | 21.8001ms | 1996 | 640 | 487.371 | 186.331 | 0.347628 | 1(Win) | true |
| glaze | 2847.39 | 0.20935 | 70.4673ms | 1996 | 160 | 313.396 | 668.519 | 0.0345794 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13870.6 | 0.201643 | 17.0607ms | 1996 | 4890 | 374.459 | 137.235 | 0.0457116 | 1(Win) | true |
| glaze | 3826.7 | 0.219438 | 53.3465ms | 1996 | 640 | 762.562 | 497.434 | 0.05783 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1900.09 | 0.103264 | 112.886ms | 2158 | 4890 | 6117.27 | 1083.12 | 0.0596201 | 1(Win) | true |
| simdjson (ondemand) | 1885.24 | 0.106439 | 112.537ms | 2158 | 320 | 432.039 | 1091.65 | 0.0952348 | 2(Loss) | true |
| glaze | 1670.23 | 0.21976 | 126.629ms | 2158 | 4890 | 35855.5 | 1232.18 | 0.423115 | 3(Loss) | true |
| jsonifier (two-stage) | 1634.86 | 0.163238 | 131.108ms | 2158 | 80 | 337.809 | 1258.84 | 0.0367537 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2609.93 | 0.24503 | 97.9257ms | 2158 | 80 | 298.657 | 788.538 | 0.134562 | 1(Win) | true |
| simdjson (ondemand) | 2453.05 | 0.39269 | 101.188ms | 2158 | 30 | 325.62 | 838.967 | 0.154713 | 2(Loss) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2143.17 | 0.0643126 | 119.95ms | 2158 | 320 | 122.048 | 960.272 | 0.284589 | 3(Tie) | true |
| glaze STATISTICAL TIE | 2140.9 | 0.188565 | 112.957ms | 2158 | 160 | 525.718 | 961.294 | 0.340176 | 3(Tie) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12659.4 | 0.127539 | 24.5297ms | 2866 | 4890 | 370.784 | 215.906 | 0.152958 | 1(Win) | true |
| glaze | 2799.61 | 0.342269 | 110.203ms | 2866 | 320 | 3573.09 | 976.291 | 0.376235 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16840.9 | 0.316155 | 19.2813ms | 2866 | 640 | 168.5 | 162.297 | 0.051961 | 1(Win) | true |
| glaze | 3483.3 | 0.243173 | 81.5103ms | 2866 | 2560 | 9320.56 | 784.667 | 0.0963218 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2347.52 | 0.171665 | 182.061ms | 4390 | 40 | 374.917 | 1783.42 | 0.00887884 | 1(Win) | true |
| jsonifier (two-stage) | 1253.92 | 0.115839 | 342.197ms | 4390 | 30 | 448.764 | 3338.83 | 0.0837914 | 2(Loss) | true |
| simdjson (ondemand) | 1027.01 | 0.105145 | 416.479ms | 4390 | 80 | 1469.75 | 4076.51 | 0.034048 | 3(Loss) | true |
| glaze | 1007.61 | 0.134011 | 418.137ms | 4390 | 2560 | 79372.2 | 4155.02 | 0.161643 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2682.01 | 0.054311 | 174.053ms | 4390 | 640 | 460.006 | 1561 | 0.0797399 | 1(Win) | true |
| jsonifier (two-stage) | 1480.77 | 0.0373533 | 332.523ms | 4390 | 320 | 356.915 | 2827.34 | 0.0549626 | 2(Loss) | true |
| simdjson (ondemand) | 1142.14 | 0.112763 | 384.776ms | 4390 | 80 | 1366.83 | 3665.6 | 0.0573222 | 3(Loss) | true |
| glaze | 1116.42 | 0.303813 | 389.133ms | 4390 | 640 | 83074.5 | 3750.06 | 0.0569482 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9705.17 | 0.18392 | 46.3152ms | 4390 | 640 | 402.865 | 431.381 | 0.149453 | 1(Win) | true |
| glaze | 1806.2 | 0.0547494 | 238.14ms | 4390 | 320 | 515.354 | 2317.92 | 0.00107854 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10392 | 0.194009 | 43.5724ms | 4390 | 640 | 390.975 | 402.869 | 0.0325682 | 1(Win) | true |
| glaze | 1955.8 | 0.127252 | 218.387ms | 4390 | 2560 | 18995.4 | 2140.63 | 0.0481337 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2984.49 | 0.127942 | 303.984ms | 9378 | 4890 | 71881.2 | 2996.68 | 0.114336 | 1(Win) | true |
| jsonifier (two-stage) | 2347.12 | 0.0334241 | 390.063ms | 9378 | 320 | 519.062 | 3810.43 | 0.0338593 | 2(Loss) | true |
| glaze | 1879.13 | 0.0853129 | 484.066ms | 9378 | 160 | 2637.88 | 4759.41 | 0.176313 | 3(Loss) | true |
| simdjson (ondemand) | 1690.87 | 0.791214 | 475.117ms | 9378 | 320 | 560451 | 5289.32 | 0.331061 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3200.05 | 0.0450685 | 297.933ms | 9378 | 160 | 253.847 | 2794.82 | 0.0377789 | 1(Win) | true |
| jsonifier (two-stage) | 2713.14 | 0.0550755 | 378.998ms | 9378 | 80 | 263.683 | 3296.39 | 0.0474229 | 2(Loss) | true |
| simdjson (ondemand) | 2215.69 | 0.14408 | 419.414ms | 9378 | 4890 | 165393 | 4036.47 | 0.00800078 | 3(Loss) | true |
| glaze | 2050.32 | 0.127714 | 458.238ms | 9378 | 80 | 2482.81 | 4362.02 | 0.0607885 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 21747.9 | 0.113912 | 54.727ms | 11521 | 640 | 211.966 | 505.211 | 0.130995 | 1(Win) | true |
| glaze | 2769.19 | 0.0652355 | 404.173ms | 11521 | 160 | 1071.92 | 3967.68 | 0.0379486 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 23519.2 | 0.104275 | 50.3355ms | 11521 | 1280 | 303.744 | 467.163 | 0.092733 | 1(Win) | true |
| glaze | 3151.51 | 0.189002 | 357.362ms | 11521 | 40 | 1736.75 | 3486.35 | 0.0320194 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2821.38 | 0.295351 | 155.011ms | 4669 | 4890 | 106245 | 1578.2 | 0.501355 | 1(Win) | true |
| jsonifier (two-stage) | 1815.88 | 0.0660862 | 250.339ms | 4669 | 160 | 420.161 | 2452.09 | 0.0864805 | 2(Loss) | true |
| glaze | 1457.43 | 0.157602 | 312.025ms | 4669 | 40 | 927.379 | 3055.18 | 0.283683 | 3(Loss) | true |
| simdjson (ondemand) | 1208.32 | 0.12615 | 374.778ms | 4669 | 1280 | 27660.9 | 3685.03 | 0.0669704 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3385.06 | 0.133105 | 143.835ms | 4669 | 2560 | 7847.76 | 1315.4 | 0.00531591 | 1(Win) | true |
| jsonifier (two-stage) | 1991.73 | 0.0831728 | 239.89ms | 4669 | 160 | 553.185 | 2235.6 | 0.0117404 | 2(Loss) | true |
| glaze | 1755.48 | 0.161279 | 269.957ms | 4669 | 80 | 1338.76 | 2536.46 | 0.00049281 | 3(Loss) | true |
| simdjson (ondemand) | 1417.07 | 0.0839724 | 330.291ms | 4669 | 80 | 556.964 | 3142.19 | 0.082415 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13869.8 | 0.0868323 | 35.3217ms | 4669 | 4890 | 379.996 | 321.036 | 0.241229 | 1(Win) | true |
| glaze | 1988.21 | 0.138619 | 229.544ms | 4669 | 80 | 771.01 | 2239.55 | 0.0960937 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15861.2 | 0.184121 | 31.211ms | 4669 | 1280 | 341.973 | 280.729 | 0.021424 | 1(Win) | true |
| glaze | 2264.2 | 0.0954192 | 200.928ms | 4669 | 4890 | 17218.7 | 1966.57 | 0.0174561 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2823.32 | 0.0627073 | 273.273ms | 7932 | 320 | 903.299 | 2679.31 | 0.0176149 | 1(Win) | true |
| jsonifier (two-stage) | 2338.87 | 0.271918 | 325.383ms | 7932 | 2560 | 198001 | 3234.27 | 0.650794 | 2(Loss) | true |
| glaze | 1970.74 | 0.153094 | 389.38ms | 7932 | 640 | 22100.5 | 3838.43 | 0.00712419 | 3(Loss) | true |
| simdjson (ondemand) | 1929.35 | 0.118873 | 397.122ms | 7932 | 40 | 868.897 | 3920.78 | 0.000212543 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3071.9 | 0.217246 | 261.584ms | 7932 | 40 | 1144.77 | 2462.5 | 0.0541162 | 1(Win) | true |
| jsonifier (two-stage) | 2853.41 | 0.0459029 | 281.941ms | 7932 | 320 | 473.878 | 2651.05 | 0.0986841 | 2(Loss) | true |
| glaze | 2291.31 | 0.144463 | 347.467ms | 7932 | 30 | 682.386 | 3301.4 | 0.0827247 | 3(Loss) | true |
| simdjson (ondemand) | 2250.59 | 0.087773 | 351.616ms | 7932 | 4890 | 42560.1 | 3361.14 | 0.169421 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 25721.2 | 0.292216 | 37.5672ms | 9249 | 320 | 321.34 | 342.928 | 0.194478 | 1(Win) | true |
| glaze | 2427.52 | 0.071198 | 370.992ms | 9249 | 160 | 1070.83 | 3633.56 | 0.0517476 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 27768.8 | 0.127349 | 34.9297ms | 9249 | 2560 | 418.897 | 317.642 | 0.0731176 | 1(Win) | true |
| glaze | 2628.93 | 0.0963229 | 343.966ms | 9249 | 80 | 835.564 | 3355.18 | 0.123537 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 677.23 | 0.0789914 | 661.079ms | 4604 | 40 | 1049.11 | 6483.35 | 0.169634 | 1(Win) | true |
| jsonifier (two-stage) | 575.824 | 0.0863989 | 767.996ms | 4604 | 4890 | 212235 | 7625.11 | 0.0378901 | 2(Loss) | true |
| glaze | 407.925 | 0.0941105 | 1094.23ms | 4604 | 80 | 8208.73 | 10763.5 | 0.0579167 | 3(Loss) | true |
| simdjson (ondemand) | 378.829 | 0.0600314 | 1221.12ms | 4604 | 30 | 1452.32 | 11590.2 | 0.179427 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 876.688 | 0.119866 | 645.378ms | 4604 | 40 | 1441.55 | 5008.3 | 0.109271 | 1(Win) | true |
| jsonifier (two-stage) | 724.365 | 0.042659 | 751.113ms | 4604 | 160 | 1069.79 | 6061.47 | 0.0603559 | 2(Loss) | true |
| glaze | 477.965 | 0.114338 | 1064.82ms | 4604 | 30 | 3309.65 | 9186.27 | 0.0739688 | 3(Loss) | true |
| simdjson (ondemand) | 432.7 | 0.112237 | 1151.51ms | 4604 | 2560 | 332053 | 10147.3 | 0.0446941 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2027.44 | 0.100484 | 223.184ms | 4604 | 2560 | 12122.9 | 2165.64 | 0.0426042 | 1(Win) | true |
| glaze | 1095.41 | 0.144708 | 411.681ms | 4604 | 30 | 1009.32 | 4008.3 | 0.0690711 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2085.65 | 0.111261 | 217.033ms | 4604 | 80 | 438.896 | 2105.2 | 0.0534677 | 1(Win) | true |
| glaze | 1185.04 | 0.10336 | 378.013ms | 4604 | 80 | 1173.28 | 3705.12 | 0.0249717 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1942.98 | 0.0451834 | 957.552ms | 18245 | 80 | 1309.77 | 8955.19 | 0.023026 | 1(Win) | true |
| jsonifier | 1868.38 | 0.219825 | 939.024ms | 18245 | 640 | 268219 | 9312.75 | 0.180023 | 2(Loss) | true |
| simdjson (ondemand) | 1363.68 | 0.0923683 | 1282.69ms | 18245 | 4890 | 679236 | 12759.5 | 0.128702 | 3(Loss) | true |
| glaze | 1293.71 | 0.0376583 | 1394ms | 18245 | 80 | 2052.23 | 13449.5 | 0.0345618 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2335.97 | 0.0989687 | 894.915ms | 18245 | 30 | 1630.31 | 7448.63 | 0.0931687 | 1(Win) | true |
| jsonifier | 2248.35 | 0.085557 | 922.275ms | 18245 | 30 | 1315.2 | 7738.9 | 0.232909 | 2(Loss) | true |
| simdjson (ondemand) | 1567.84 | 0.0624499 | 1257.43ms | 18245 | 40 | 1921.35 | 11097.9 | 0.0437961 | 3(Loss) | true |
| glaze | 1457.34 | 0.0898442 | 1349.9ms | 18245 | 2560 | 294569 | 11939.4 | 0.181359 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8758.09 | 0.0405899 | 273.532ms | 24579 | 320 | 377.656 | 2676.43 | 0.103343 | 1(Win) | true |
| glaze | 3233.47 | 0.117593 | 727.465ms | 24579 | 4890 | 355354 | 7249.29 | 0.0589667 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9344.94 | 0.1159 | 255.881ms | 24579 | 4890 | 41328.8 | 2508.35 | 0.0311969 | 1(Win) | true |
| glaze | 3874.49 | 0.180243 | 614.569ms | 24579 | 40 | 4756.38 | 6049.93 | 0.00234157 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 630.126 | 0.406424 | 659.594ms | 4604 | 1280 | 1.02656e+06 | 6967.99 | 0.525854 | 1(Win) | true |
| jsonifier (two-stage) | 606.313 | 0.0749693 | 739.346ms | 4604 | 30 | 884.23 | 7241.67 | 0.0773901 | 2(Loss) | true |
| glaze | 409.592 | 0.0654657 | 1095.4ms | 4604 | 40 | 1969.95 | 10719.7 | 0.0112708 | 3(Loss) | true |
| simdjson (ondemand) | 379.511 | 0.0607178 | 1175.25ms | 4604 | 30 | 1480.39 | 11569.4 | 0.0495315 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 955.951 | 0.103958 | 602.652ms | 4604 | 30 | 683.964 | 4593.03 | 0.0283117 | 1(Win) | true |
| jsonifier (two-stage) | 769.589 | 0.0843075 | 721.744ms | 4604 | 40 | 925.435 | 5705.27 | 0.0919585 | 2(Loss) | true |
| glaze | 477.475 | 0.0925453 | 1068.17ms | 4604 | 30 | 2172.7 | 9195.7 | 0.0732763 | 3(Loss) | true |
| simdjson (ondemand) | 436.546 | 0.0508131 | 1148.54ms | 4604 | 80 | 2089.55 | 10057.9 | 0.057202 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2003.33 | 0.180172 | 224.594ms | 4604 | 1280 | 19959.6 | 2191.71 | 0.0258141 | 1(Win) | true |
| glaze | 1069.62 | 0.232761 | 418.859ms | 4604 | 640 | 58426.6 | 4104.93 | 0.548026 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2104.95 | 0.0723887 | 222.065ms | 4604 | 160 | 364.795 | 2085.9 | 0.071363 | 1(Win) | true |
| glaze | 1182.79 | 0.0695421 | 380.775ms | 4604 | 160 | 1066.28 | 3712.18 | 0.0060615 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2029.44 | 0.0266389 | 872.951ms | 18245 | 160 | 834.616 | 8573.69 | 0.0209172 | 1(Win) | true |
| jsonifier | 2026.73 | 0.0299878 | 874.014ms | 18245 | 320 | 2120.98 | 8585.17 | 0.0760245 | 2(Loss) | true |
| simdjson (ondemand) | 1370.43 | 0.103532 | 1278.96ms | 18245 | 1280 | 221175 | 12696.6 | 0.0240218 | 3(Loss) | true |
| glaze | 1300.93 | 0.0599571 | 1358.41ms | 18245 | 30 | 1929.24 | 13374.9 | 0.0421009 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2473.11 | 0.072451 | 855.42ms | 18245 | 40 | 1039.32 | 7035.6 | 0.0521431 | 1(Win) | true |
| jsonifier | 2437.1 | 0.141298 | 855.183ms | 18245 | 2560 | 260527 | 7139.56 | 0.0846246 | 2(Loss) | true |
| simdjson (ondemand) | 1554.59 | 0.092989 | 1255.48ms | 18245 | 4890 | 529696 | 11192.5 | 0.0133912 | 3(Loss) | true |
| glaze | 1464.9 | 0.0750661 | 1373.67ms | 18245 | 30 | 2384.94 | 11877.8 | 0.186276 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9049.17 | 0.173383 | 290.988ms | 24579 | 30 | 605.126 | 2590.33 | 0.105409 | 1(Win) | true |
| glaze | 3257.32 | 0.0981188 | 725.192ms | 24579 | 2560 | 127630 | 7196.21 | 0.156163 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9675.04 | 0.0623371 | 247.92ms | 24579 | 320 | 729.904 | 2422.77 | 0.00528866 | 1(Win) | true |
| glaze | 3884.43 | 0.087546 | 613.876ms | 24579 | 80 | 2232.73 | 6034.44 | 0.170603 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1547.74 | 0.0652544 | 321.394ms | 5094 | 160 | 671.216 | 3138.78 | 0.0754103 | 1(Win) | true |
| jsonifier (two-stage) | 1138.8 | 0.0279529 | 434.339ms | 5094 | 320 | 455.016 | 4265.9 | 0.0177979 | 2(Loss) | true |
| simdjson (ondemand) | 945.015 | 0.085534 | 522.737ms | 5094 | 40 | 773.353 | 5140.68 | 0.0983015 | 3(Loss) | true |
| glaze | 929.606 | 0.140915 | 526.716ms | 5094 | 1280 | 69413.6 | 5225.89 | 0.0154453 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2014.76 | 0.0487651 | 314.802ms | 5094 | 160 | 221.212 | 2411.21 | 0.012962 | 1(Win) | true |
| jsonifier (two-stage) | 1474.23 | 0.0681977 | 428.799ms | 5094 | 80 | 404.035 | 3295.3 | 0.0113811 | 2(Loss) | true |
| simdjson (ondemand) | 1174.59 | 0.0662847 | 492.063ms | 5094 | 80 | 601.26 | 4135.93 | 0.0628243 | 3(Loss) | true |
| glaze | 1119.63 | 0.362337 | 499.972ms | 5094 | 2560 | 632755 | 4338.96 | 0.125151 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10485.9 | 0.162942 | 49.7591ms | 5094 | 320 | 182.357 | 463.291 | 0.168239 | 1(Win) | true |
| glaze | 2137.61 | 0.0841742 | 234.173ms | 5094 | 160 | 585.516 | 2272.64 | 0.0329904 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11445.5 | 0.111324 | 45.649ms | 5094 | 1280 | 285.786 | 424.449 | 0.0527979 | 1(Win) | true |
| glaze | 2486.62 | 0.075728 | 201.204ms | 5094 | 160 | 350.212 | 1953.66 | 0.184568 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1826.31 | 0.037527 | 427.615ms | 8051 | 160 | 398.251 | 4204.11 | 0.0237919 | 1(Win) | true |
| simdjson (ondemand) | 1409.2 | 0.0513846 | 555.149ms | 8051 | 80 | 627.063 | 5448.51 | 0.140895 | 2(Loss) | true |
| jsonifier (two-stage) | 1403.16 | 0.0569697 | 596.752ms | 8051 | 40 | 388.715 | 5471.95 | 0.00578676 | 3(Loss) | true |
| glaze | 1350.11 | 0.0829231 | 575.435ms | 8051 | 160 | 3558.24 | 5686.99 | 0.0369128 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2190.2 | 0.277586 | 423.285ms | 8051 | 30 | 2840.86 | 3505.63 | 0.0409033 | 1(Win) | true |
| jsonifier (two-stage) | 1908.91 | 0.0958865 | 550.752ms | 8051 | 30 | 446.234 | 4022.2 | 0.0356229 | 2(Loss) | true |
| simdjson (ondemand) | 1729.34 | 0.0550044 | 519.292ms | 8051 | 160 | 954.236 | 4439.88 | 0.170622 | 3(Loss) | true |
| glaze | 1656.01 | 0.20908 | 547.366ms | 8051 | 320 | 30071.1 | 4636.46 | 0.201727 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14346.4 | 0.0721708 | 65.2905ms | 9255 | 2560 | 504.696 | 615.225 | 0.0707447 | 1(Win) | true |
| glaze | 2496.98 | 0.0473044 | 361.398ms | 9255 | 320 | 894.694 | 3534.77 | 0.136227 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18489.1 | 0.124998 | 50.9399ms | 9255 | 1280 | 455.762 | 477.375 | 0.0762053 | 1(Win) | true |
| glaze | 2898.85 | 0.108998 | 313.364ms | 9255 | 640 | 7048.79 | 3044.74 | 0.187559 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 3852.66 | 0.404985 | 76.4193ms | 2889 | 30 | 251.637 | 715.133 | 0.0186411 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3843.79 | 0.143015 | 75.334ms | 2889 | 320 | 336.27 | 716.784 | 0.0649181 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3829.73 | 0.147618 | 76.0332ms | 2889 | 320 | 360.902 | 719.416 | 0.124823 | 1(Tie) | true |
| glaze | 2441.15 | 0.0519812 | 117.508ms | 2889 | 640 | 220.282 | 1128.63 | 0.00110752 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4137.56 | 0.0956062 | 72.438ms | 2889 | 320 | 129.696 | 665.891 | 0.0379986 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4136.71 | 0.0794489 | 72.9278ms | 2889 | 640 | 179.201 | 666.028 | 0.0403674 | 1(Tie) | true |
| simdjson (ondemand) | 4119.93 | 0.0809154 | 71.8822ms | 2889 | 320 | 93.6974 | 668.741 | 0.0734194 | 3(Loss) | true |
| glaze | 2516.68 | 0.0936089 | 115.398ms | 2889 | 4890 | 5135.48 | 1094.76 | 0.0357073 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 4613.78 | 0.106398 | 82.5799ms | 3808 | 320 | 224.437 | 787.119 | 0.0579982 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 4385.68 | 0.0707845 | 86.5547ms | 3808 | 640 | 219.875 | 828.056 | 0.00603787 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 4381.15 | 0.111752 | 86.4477ms | 3808 | 320 | 274.588 | 828.913 | 0.124565 | 2(Tie) | true |
| glaze | 3007.36 | 0.0941321 | 124.85ms | 3808 | 160 | 206.737 | 1207.57 | 0.023296 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 4883.67 | 0.128298 | 79.8488ms | 3808 | 320 | 291.265 | 743.619 | 0.0521372 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 4648.01 | 0.0978066 | 84.0483ms | 3808 | 640 | 373.746 | 781.322 | 0.0575615 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 4645.32 | 0.133499 | 84.154ms | 3808 | 320 | 348.551 | 781.775 | 0.0327887 | 2(Tie) | true |
| glaze | 3106.55 | 0.115272 | 123.752ms | 3808 | 160 | 290.541 | 1169.01 | 0.0171055 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2471.91 | 0.0950288 | 116.036ms | 2889 | 320 | 358.995 | 1114.59 | 0.138313 | 1(Win) | true |
| glaze | 1962.31 | 0.118887 | 144.483ms | 2889 | 4890 | 13625.1 | 1404.04 | 0.0486947 | 2(Loss) | true |
| jsonifier (two-stage) | 1849.72 | 0.0557816 | 153.219ms | 2889 | 640 | 441.822 | 1489.51 | 0.170333 | 3(Loss) | true |
| simdjson (ondemand) | 1776.49 | 0.0895849 | 160.451ms | 2889 | 320 | 617.714 | 1550.9 | 0.0907554 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2652.07 | 0.339788 | 124.638ms | 2889 | 2560 | 31899.3 | 1038.87 | 0.499566 | 1(Win) | true |
| glaze | 2282.22 | 0.0903895 | 136.854ms | 2889 | 640 | 762.076 | 1207.23 | 0.17958 | 2(Loss) | true |
| jsonifier (two-stage) | 2251 | 0.185335 | 143.285ms | 2889 | 80 | 411.67 | 1223.97 | 0.0897904 | 3(Loss) | true |
| simdjson (ondemand) | 1982.71 | 0.164247 | 152.599ms | 2889 | 160 | 833.475 | 1389.59 | 0.149999 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10457.5 | 0.152854 | 29.5987ms | 2963 | 4890 | 834.189 | 270.211 | 0.794012 | 1(Win) | true |
| glaze | 3287.1 | 0.0668762 | 89.8576ms | 2963 | 1280 | 423.05 | 859.645 | 0.115187 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14212.8 | 0.129427 | 22.9217ms | 2963 | 4890 | 323.79 | 198.817 | 0.120411 | 1(Win) | true |
| glaze | 4257.3 | 0.0866481 | 71.5285ms | 2963 | 640 | 211.686 | 663.739 | 0.0693974 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2369.56 | 0.136944 | 156.673ms | 3808 | 4890 | 21540.4 | 1532.6 | 0.045034 | 1(Win) | true |
| jsonifier (two-stage) | 2271.04 | 0.155606 | 164.995ms | 3808 | 80 | 495.321 | 1599.09 | 0.116337 | 2(Loss) | true |
| simdjson (ondemand) | 2212.27 | 0.0989932 | 168.332ms | 3808 | 4890 | 12913.3 | 1641.56 | 0.24754 | 3(Loss) | true |
| glaze | 2150.26 | 0.0883688 | 173.487ms | 3808 | 4890 | 10892.3 | 1688.91 | 0.0384796 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2787.17 | 0.377164 | 149.969ms | 3808 | 30 | 724.516 | 1302.97 | 0.012793 | 1(Win) | true |
| jsonifier (two-stage) | 2708.83 | 0.143779 | 154.746ms | 3808 | 80 | 297.243 | 1340.65 | 0.0783816 | 2(Loss) | true |
| simdjson (ondemand) | 2498.72 | 0.0948633 | 160.454ms | 3808 | 320 | 608.28 | 1453.38 | 0.23275 | 3(Loss) | true |
| glaze | 2475.5 | 0.104087 | 164.065ms | 3808 | 320 | 746.119 | 1467.01 | 0.100869 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13378.4 | 0.137849 | 33.7545ms | 4300 | 2560 | 457.063 | 306.525 | 0.249889 | 1(Win) | true |
| glaze | 3371.26 | 0.253367 | 128.536ms | 4300 | 40 | 379.938 | 1216.4 | 0.139562 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16694.3 | 0.156632 | 27.6117ms | 4300 | 1280 | 189.485 | 245.641 | 0.0254372 | 1(Win) | true |
| glaze | 4338.24 | 0.192426 | 97.9147ms | 4300 | 160 | 529.368 | 945.269 | 0.0522611 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2780.52 | 0.119397 | 8208.34ms | 466906 | 1280 | 4.67954e+07 | 160141 | 0.391659 | 1(Win) | true |
| glaze | 1861.97 | 0.137024 | 6135.52ms | 466906 | 640 | 6.87212e+07 | 239143 | 0.0165623 | 2(Loss) | true |
| simdjson (ondemand) | 907.246 | 0.159971 | 6299.44ms | 466906 | 160 | 9.86299e+07 | 490800 | 0.057325 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2817.68 | 0.266742 | 8198.42ms | 466906 | 40 | 7.1075e+06 | 158029 | 0.038779 | 1(Win) | true |
| glaze | 1861.62 | 0.0929306 | 6140.93ms | 466906 | 1280 | 6.32421e+07 | 239188 | 0.366478 | 2(Loss) | true |
| simdjson (ondemand) | 901.074 | 0.189604 | 6299.85ms | 466906 | 80 | 7.023e+07 | 494161 | 0.0621172 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3903.12 | 0.0893884 | 8810.53ms | 699405 | 1280 | 2.9868e+07 | 170890 | 0.0347758 | 1(Win) | true |
| glaze | 2405.38 | 0.0926059 | 7106.09ms | 699405 | 1280 | 8.44064e+07 | 277296 | 0.23989 | 2(Loss) | true |
| simdjson (ondemand) | 698.631 | 0.104365 | 6722.49ms | 767297 | 320 | 3.82373e+08 | 1.04741e+06 | 0.2799 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3903.89 | 0.222118 | 8802.69ms | 699405 | 160 | 2.30436e+07 | 170856 | 0.38381 | 1(Win) | true |
| glaze | 2421.42 | 0.133816 | 7054.36ms | 699405 | 320 | 4.34795e+07 | 275460 | 0.19851 | 2(Loss) | true |
| simdjson (ondemand) | 721.677 | 0.108048 | 6442.76ms | 767297 | 320 | 3.84086e+08 | 1.01396e+06 | 0.259139 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2512.36 | 0.161486 | 6125.6ms | 631514 | 640 | 9.59071e+07 | 239719 | 0.0125867 | 1(Win) | true |
| glaze | 1995.1 | 0.0681433 | 7793.97ms | 631514 | 1280 | 5.41615e+07 | 301868 | 0.417059 | 2(Loss) | true |
