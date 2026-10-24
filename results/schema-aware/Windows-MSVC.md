# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26100 using the MSVC 19.51.36260.0 compiler).  

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
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 543.514 | 0.188158 | 8520.07ms | 94653 | 1280 | 1.24998e+08 | 166083 | 0.130459 | 4.28937 | 1(Win) | true |
| glaze DID NOT CONVERGE | 471.824 | 1.9409 | 6143.02ms | 94653 | 160 | 2.20616e+09 | 191318 | 3.07333 | 4.94112 | -(Loss) | false |
| jsonifier (two-stage) | 447.104 | 0.177778 | 5538.07ms | 94653 | 1280 | 1.649e+08 | 201895 | 0.148619 | 5.21451 | 3(Loss) | true |
| simdjson (ondemand) | 342.871 | 0.153628 | 6716.35ms | 94653 | 1280 | 2.0939e+08 | 263271 | 0.0224094 | 6.80026 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 808.586 | 0.192882 | 7253.46ms | 94653 | 1280 | 5.93483e+07 | 111637 | 0.0334622 | 2.88284 | 1(Win) | true |
| jsonifier (two-stage) | 618.282 | 0.254034 | 9000.71ms | 94653 | 640 | 8.8036e+07 | 145998 | 0.160791 | 3.77047 | 2(Loss) | true |
| simdjson (ondemand) | 449.797 | 0.143188 | 5818.06ms | 94653 | 1280 | 1.05696e+08 | 200686 | 0.154475 | 5.18343 | 3(Loss) | true |
| glaze | 424.785 | 0.772365 | 8996.02ms | 94653 | 30 | 8.08162e+07 | 212503 | 0.198035 | 5.48829 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6603.37 | 0.0836535 | 1442.86ms | 94653 | 40 | 5230.77 | 13670 | 0.367107 | 0.351092 | 1(Win) | true |
| glaze | 2292.86 | 0.17859 | 3950.51ms | 94653 | 4890 | 2.41733e+07 | 39369.3 | 0.121609 | 1.01585 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6636.51 | 0.257703 | 1367.07ms | 94653 | 4890 | 6.00809e+06 | 13601.7 | 0.11546 | 0.350203 | 1(Win) | true |
| glaze | 2584.3 | 0.168828 | 3490.65ms | 94653 | 4890 | 1.70051e+07 | 34929.4 | 0.0831456 | 0.901339 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 607.854 | 0.230537 | 5008.71ms | 124611 | 1280 | 2.60018e+08 | 195505 | 0.36411 | 3.83556 | 1(Win) | true |
| jsonifier | 602.349 | 0.200179 | 5050.24ms | 124611 | 1280 | 1.99647e+08 | 197291 | 0.21465 | 3.8707 | 2(Loss) | true |
| jsonifier (two-stage) | 570.38 | 0.266232 | 5318.57ms | 124611 | 640 | 1.96918e+08 | 208349 | 0.0283398 | 4.08768 | 3(Loss) | true |
| simdjson (ondemand) | 445.008 | 0.241669 | 6812.15ms | 124611 | 640 | 2.66562e+08 | 267048 | 0.042028 | 5.23952 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 873.256 | 0.122739 | 8443.75ms | 124611 | 2560 | 7.14229e+07 | 136086 | 0.00780815 | 2.66953 | 1(Win) | true |
| jsonifier | 835.71 | 0.118995 | 8720.79ms | 124611 | 2560 | 7.32997e+07 | 142200 | 0.0352565 | 2.78952 | 2(Loss) | true |
| jsonifier (two-stage) | 780.04 | 0.230995 | 9320.49ms | 124611 | 640 | 7.9262e+07 | 152349 | 0.137003 | 2.98849 | 3(Loss) | true |
| simdjson (ondemand) | 573.773 | 0.128881 | 5969.38ms | 124611 | 1280 | 9.12047e+07 | 207117 | 0.0365265 | 4.06353 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8743.72 | 0.112382 | 1581.11ms | 136037 | 40 | 11121.8 | 14837.5 | 0.106598 | 0.265892 | 1(Win) | true |
| glaze | 1348.01 | 0.141778 | 9647.35ms | 136076 | 2560 | 4.7691e+07 | 96269.8 | 0.00872462 | 1.72911 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8498.85 | 0.071932 | 1563.51ms | 136037 | 80 | 9645.57 | 15265 | 0.326477 | 0.273754 | 1(Win) | true |
| glaze | 1415.29 | 0.132527 | 9170.78ms | 136076 | 2560 | 3.78028e+07 | 91693.3 | 0.00877663 | 1.6469 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 730.867 | 0.17519 | 353.971ms | 2632 | 160 | 5792.06 | 3434.38 | 0.0181951 | 3.15041 | 1(Win) | true |
| glaze | 614.272 | 0.127427 | 422.742ms | 2632 | 160 | 4338.05 | 4086.25 | 0.0305998 | 3.76458 | 2(Loss) | true |
| jsonifier (two-stage) | 597.636 | 0.0920204 | 433.497ms | 2632 | 160 | 2389.94 | 4200 | 0.0594884 | 3.86915 | 3(Loss) | true |
| simdjson (ondemand) | 365.309 | 0.320132 | 693.392ms | 2632 | 4890 | 2.36602e+06 | 6871.08 | 0.0955617 | 6.34618 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1016.22 | 0.155646 | 298.216ms | 2632 | 160 | 2364.78 | 2470 | 0.45755 | 2.24777 | 1(Win) | true |
| jsonifier | 907.186 | 0.0978915 | 329.215ms | 2632 | 320 | 2347.57 | 2766.88 | 0.157871 | 2.53697 | 2(Loss) | true |
| jsonifier (two-stage) | 696.758 | 0.10133 | 412.465ms | 2632 | 160 | 2132.08 | 3602.5 | 0.138985 | 3.30884 | 3(Loss) | true |
| simdjson (ondemand) | 481.953 | 0.0779639 | 576.016ms | 2632 | 160 | 2637.97 | 5208.12 | 0.22853 | 4.8082 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4876.88 | 0.19231 | 57.007ms | 2632 | 1280 | 1254.01 | 514.688 | 0.0911577 | 0.44409 | 1(Win) | true |
| glaze | 1708.8 | 0.149463 | 154.069ms | 2632 | 640 | 3084.87 | 1468.91 | 0.266638 | 1.32412 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5579.87 | 0.313693 | 50.7272ms | 2632 | 1280 | 2548.84 | 449.844 | 0.24255 | 0.383257 | 1(Win) | true |
| glaze | 1711.41 | 0.596847 | 147.031ms | 2632 | 30 | 2298.85 | 1466.67 | 0.226757 | 1.3122 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 798.904 | 0.153024 | 449.412ms | 3643 | 80 | 3542.72 | 4348.75 | 0.0287522 | 2.89082 | 1(Win) | true |
| jsonifier | 785.027 | 0.139161 | 456.48ms | 3643 | 160 | 6068.79 | 4425.62 | 0.127262 | 2.94052 | 2(Loss) | true |
| glaze | 722.294 | 0.2079 | 479.048ms | 3643 | 30 | 3000 | 4810 | 0.345304 | 3.2082 | 3(Loss) | true |
| simdjson (ondemand) | 494.19 | 0.47215 | 710.468ms | 3643 | 2560 | 2.82053e+06 | 7030.16 | 0.214019 | 4.69152 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1128.39 | 0.469783 | 353.089ms | 3643 | 4890 | 1.02307e+06 | 3078.94 | 0.270681 | 2.03357 | 1(Win) | true |
| jsonifier (two-stage) | 930.064 | 0.428225 | 420.185ms | 3643 | 4890 | 1.25125e+06 | 3735.48 | 0.281234 | 2.48306 | 2(Loss) | true |
| jsonifier | 916.081 | 0.122092 | 432.055ms | 3643 | 80 | 1715.19 | 3792.5 | 0 | 2.51306 | 3(Loss) | true |
| simdjson (ondemand) | 651.216 | 0.158112 | 587.57ms | 3643 | 40 | 2846.15 | 5335 | 0.0938086 | 3.55228 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6843.68 | 0.233062 | 56.5318ms | 3643 | 640 | 895.907 | 507.656 | 0.52599 | 0.315065 | 1(Win) | true |
| glaze | 1262.25 | 0.186742 | 286.751ms | 3682 | 320 | 8635.97 | 2781.88 | 0.224165 | 1.8195 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7018.66 | 0.349175 | 54.7045ms | 3643 | 160 | 477.987 | 495 | 0 | 0.307262 | 1(Win) | true |
| glaze | 1344.64 | 0.290048 | 266.477ms | 3682 | 4890 | 280546 | 2611.43 | 0.269052 | 1.70155 | 2(Loss) | true |
