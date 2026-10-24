# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1017-azure using the Clang 24.0.0 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier: [cb40a92](https://github.com/nihilai-collective/jsonifier/commit/cb40a92)  
| Glaze: [1476d6b](https://github.com/stephenberry/glaze/commit/1476d6b)  
| Simdjson: [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **Glaze** | utf8: `AVX2`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX2` |

> **Adaptive Sampling & Convergence (AMD EPYC 7763 64-Core Processor-AVX2):**  
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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 950.091 | 0.073908 | 9508.94ms | 94653 | 4890 | 2.41118e+07 | 95010 | 0.369098 | 2.45349 | 1(Win) | true |
| jsonifier (two-stage) | 803.898 | 0.2826 | 5772.55ms | 94653 | 320 | 3.22226e+07 | 112288 | 0.0714856 | 2.89966 | 2(Loss) | true |
| simdjson (ondemand) | 761.415 | 0.102771 | 6077.08ms | 94653 | 2560 | 3.80019e+07 | 118553 | 0.740706 | 3.06164 | 3(Loss) | true |
| glaze | 756.755 | 0.102152 | 6125.79ms | 94653 | 1280 | 1.90046e+07 | 119283 | 0.237902 | 3.0806 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1458.61 | 0.118056 | 8413.61ms | 94653 | 4890 | 2.61022e+07 | 61886.4 | 0.0197972 | 1.59782 | 1(Win) | true |
| jsonifier (two-stage) | 1138.17 | 0.267254 | 5154.21ms | 94653 | 320 | 1.43765e+07 | 79309.8 | 0.097261 | 2.04802 | 2(Loss) | true |
| simdjson (ondemand) | 1065.79 | 0.114778 | 5464.03ms | 94653 | 2560 | 2.41926e+07 | 84695.8 | 0.166647 | 2.18686 | 3(Loss) | true |
| glaze | 1027.62 | 0.110271 | 5610.71ms | 94653 | 2560 | 2.40194e+07 | 87841.7 | 0.0688715 | 2.26842 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9500.3 | 0.311411 | 955.591ms | 94653 | 2560 | 2.24131e+06 | 9501.6 | 0.279188 | 0.24456 | 1(Win) | true |
| glaze | 2737.74 | 0.140266 | 3290.87ms | 94653 | 4890 | 1.04592e+07 | 32971.8 | 0.119266 | 0.850646 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9550.56 | 0.208015 | 977.32ms | 94653 | 4890 | 1.89021e+06 | 9451.61 | 0.128989 | 0.24323 | 1(Win) | true |
| glaze | 3084.41 | 0.542243 | 2928.91ms | 94653 | 320 | 8.05864e+06 | 29265.9 | 0.119501 | 0.755076 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1015.7 | 0.158456 | 5982.7ms | 124611 | 2560 | 8.79915e+07 | 117002 | 0.289997 | 2.29495 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 980.824 | 0.0956332 | 6206.91ms | 124611 | 2560 | 3.43707e+07 | 121162 | 0.108807 | 2.3766 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 976.994 | 0.52789 | 6087.39ms | 124611 | 30 | 1.23691e+07 | 121637 | 0.155358 | 2.38595 | 2(Tie) | true |
| glaze | 920.039 | 0.222162 | 6639.96ms | 124611 | 320 | 2.63507e+07 | 129167 | 0.0991782 | 2.53389 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1455.33 | 0.1701 | 5331.68ms | 124611 | 640 | 1.23475e+07 | 81657.4 | 0.2968 | 1.60134 | 1(Win) | true |
| jsonifier | 1394.76 | 0.213299 | 5487.79ms | 124611 | 640 | 2.11383e+07 | 85203.2 | 0.316753 | 1.67121 | 2(Loss) | true |
| simdjson (ondemand) | 1360.04 | 0.111367 | 5585.25ms | 124611 | 2560 | 2.42415e+07 | 87378.5 | 0.216971 | 1.71381 | 3(Loss) | true |
| glaze | 1222.96 | 0.0865113 | 6100.47ms | 124611 | 2560 | 1.80913e+07 | 97172.3 | 0.052077 | 1.90617 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12104 | 0.13726 | 1091.4ms | 136037 | 30 | 6493.27 | 10718.4 | 0.0884 | 0.192014 | 1(Win) | true |
| glaze | 1928.09 | 0.106134 | 6717.66ms | 136076 | 2560 | 1.30634e+07 | 67306.1 | 0.136384 | 1.20871 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12060.6 | 0.335455 | 1085.85ms | 136037 | 1280 | 1.66667e+06 | 10756.9 | 0.0278824 | 0.192517 | 1(Win) | true |
| glaze | 2038.41 | 0.136788 | 6387.06ms | 136076 | 1280 | 9.70703e+06 | 63663.5 | 0.0421374 | 1.14337 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1534.36 | 0.171787 | 168.898ms | 2632 | 160 | 1263.63 | 1635.91 | 0.0588011 | 1.48581 | 1(Win) | true |
| jsonifier (two-stage) | 1264.06 | 0.110949 | 204.1ms | 2632 | 40 | 194.153 | 1985.72 | 0.0172032 | 1.81192 | 2(Loss) | true |
| simdjson (ondemand) | 1039.11 | 0.123792 | 253.024ms | 2632 | 80 | 715.357 | 2415.6 | 0.126422 | 2.20997 | 3(Loss) | true |
| glaze | 1033.34 | 0.110272 | 242.485ms | 2632 | 40 | 286.994 | 2429.07 | 0.458625 | 2.22264 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1801.82 | 0.14604 | 157.049ms | 2632 | 40 | 165.558 | 1393.08 | 0.0830803 | 1.25919 | 1(Win) | true |
| jsonifier (two-stage) | 1430.67 | 0.0625086 | 194.465ms | 2632 | 160 | 192.44 | 1754.47 | 0.137695 | 1.59606 | 2(Loss) | true |
| glaze | 1263.47 | 0.0469748 | 207.993ms | 2632 | 160 | 139.347 | 1986.66 | 0.26075 | 1.81091 | 3(Loss) | true |
| simdjson (ondemand) | 1221.92 | 0.227633 | 226.484ms | 2632 | 30 | 655.959 | 2054.2 | 0.0600036 | 1.87439 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6465.51 | 0.255248 | 42.5656ms | 2632 | 80 | 78.5563 | 388.225 | 0.122202 | 0.327417 | 1(Win) | true |
| glaze | 2319.57 | 0.136155 | 114.018ms | 2632 | 320 | 694.664 | 1082.13 | 0.335304 | 0.972042 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7147.19 | 0.103486 | 39.0674ms | 2632 | 640 | 84.5371 | 351.197 | 0.00177966 | 0.292033 | 1(Win) | true |
| glaze | 2579.26 | 0.117132 | 101.47ms | 2632 | 320 | 415.8 | 973.175 | 0.179503 | 0.871456 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1636.84 | 0.146667 | 218.064ms | 3643 | 40 | 387.64 | 2122.53 | 0.0647394 | 1.39918 | 1(Win) | true |
| jsonifier | 1433.98 | 0.123988 | 248.736ms | 3643 | 30 | 270.717 | 2422.8 | 0.152483 | 1.60083 | 2(Loss) | true |
| simdjson (ondemand) | 1395.89 | 0.160695 | 258.073ms | 3643 | 30 | 479.886 | 2488.9 | 0.3319 | 1.64565 | 3(Loss) | true |
| glaze | 1316.01 | 0.103168 | 272.016ms | 3643 | 80 | 593.442 | 2639.97 | 0.0331333 | 1.74714 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1848.19 | 0.146375 | 210.381ms | 3643 | 30 | 227.131 | 1879.8 | 0.136726 | 1.23654 | 1(Win) | true |
| simdjson (ondemand) | 1640.73 | 0.183592 | 232.082ms | 3643 | 160 | 2418.1 | 2117.5 | 0.672736 | 1.39759 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1618.73 | 0.0771352 | 233.898ms | 3643 | 320 | 877.051 | 2146.27 | 0.0923714 | 1.4161 | 3(Tie) | true |
| jsonifier STATISTICAL TIE | 1616.42 | 0.120012 | 233.352ms | 3643 | 30 | 199.609 | 2149.33 | 0.122669 | 1.41768 | 3(Tie) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8222.8 | 0.405353 | 46.1894ms | 3643 | 80 | 234.658 | 422.512 | 0.00295858 | 0.259257 | 1(Win) | true |
| glaze | 1891.34 | 0.417251 | 189.586ms | 3682 | 4890 | 293447 | 1856.58 | 0.13885 | 1.20891 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9363.33 | 0.118498 | 40.8824ms | 3643 | 320 | 61.863 | 371.047 | 0.00589513 | 0.220611 | 1(Win) | true |
| glaze | 2010.67 | 0.360211 | 178.057ms | 3682 | 4890 | 193511 | 1746.39 | 0.109538 | 1.13578 | 2(Loss) | true |
