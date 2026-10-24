# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.4 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier: [cb40a92](https://github.com/nihilai-collective/jsonifier/commit/cb40a92)  
| Glaze: [1476d6b](https://github.com/stephenberry/glaze/commit/1476d6b)  
| Simdjson: [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **Glaze** | utf8: `NEON64`, escape: `NEON`, float: `NEON`, struct-skip: `NEON64` |

> **Adaptive Sampling & Convergence (Apple M1 (Virtual)-NEON):**  
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

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 972.294 | 0.876246 | 8934.22ms | 94653 | 2560 | 1.69421e+09 | 92840.4 | 0.649044 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 957.446 | 0.145796 | 5557.4ms | 94653 | 40 | 755776 | 94280.1 | 0.673492 | 1(Tie) | true |
| glaze | 914.009 | 0.289534 | 6679.38ms | 94653 | 160 | 1.30824e+07 | 98760.7 | 0.699883 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 867.129 | 0.541294 | 6249.28ms | 94653 | 160 | 5.08029e+07 | 104100 | 5.25953 | -(Loss) | false |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2028.93 | 0.901289 | 7520.82ms | 94653 | 40 | 6.43167e+06 | 44490.5 | 0.21727 | 1(Win) | true |
| jsonifier (two-stage) | 1295.15 | 0.121487 | 5347.87ms | 94653 | 1280 | 9.17706e+06 | 69697.2 | 0.4906 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1180.47 | 0.444708 | 5499.41ms | 94653 | 80 | 9.25127e+06 | 76468.2 | 0.0933775 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1179.02 | 0.322531 | 5157.34ms | 94653 | 1280 | 7.80508e+07 | 76561.9 | 1.12803 | 3(Tie) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10523 | 0.0553729 | 1142.99ms | 94653 | 40 | 902.49 | 8578.15 | 0.734622 | 1(Win) | true |
| glaze | 2951.23 | 0.207676 | 3890.7ms | 94653 | 80 | 322794 | 30586.6 | 0.198191 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10078.7 | 0.82067 | 1083.57ms | 94653 | 160 | 864401 | 8956.31 | 1.47035 | 1(Win) | true |
| glaze | 3465.62 | 0.17487 | 2827.52ms | 94653 | 320 | 663874 | 26046.7 | 0.844132 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze | 1131.55 | 0.199892 | 5633.23ms | 124611 | 1280 | 5.64116e+07 | 105023 | 0.15438 | 1(Win) | true |
| simdjson (ondemand) | 1079.75 | 1.25906 | 6377.05ms | 124611 | 30 | 5.76082e+07 | 110061 | 2.72078 | 2(Loss) | true |
| jsonifier STATISTICAL TIE | 902.283 | 2.53584 | 5752.65ms | 124611 | 2560 | 2.85569e+10 | 131708 | 3.95695 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 867.25 | 0.812646 | 7306.31ms | 124611 | 2560 | 3.17444e+09 | 137029 | 2.55198 | 3(Tie) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1553.69 | 5.89471 | 5630.33ms | 124611 | 30 | 6.09857e+08 | 76487.6 | 2.22632 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1413.29 | 1.15727 | 6000.57ms | 124611 | 30 | 2.84079e+07 | 84086.1 | 0.094061 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1312.39 | 2.09392 | 5706.02ms | 124611 | 40 | 1.43804e+08 | 90551.1 | 0.477967 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1263.07 | 1.55779 | 6265.73ms | 124611 | 640 | 1.37485e+09 | 94087.1 | 0.024586 | 3(Tie) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14497.3 | 0.112934 | 991.667ms | 136037 | 80 | 8171.04 | 8948.89 | 0.220765 | 1(Win) | true |
| glaze | 2828.99 | 0.566688 | 4695.83ms | 136076 | 2560 | 1.72993e+08 | 45872.3 | 0.151239 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14448.7 | 0.330964 | 955.556ms | 136037 | 1280 | 1.13039e+06 | 8978.99 | 0.000974507 | 1(Win) | true |
| glaze | 2682.55 | 0.403998 | 4399.94ms | 136076 | 30 | 1.1459e+06 | 48376.4 | 0.00303169 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1357.7 | 0.200528 | 207.942ms | 2632 | 30 | 412.323 | 1848.77 | 0.282273 | 1(Win) | true |
| jsonifier (two-stage) | 1155.99 | 0.307924 | 239.429ms | 2632 | 4890 | 218606 | 2171.37 | 0.451411 | 2(Loss) | true |
| simdjson (ondemand) | 1015.69 | 0.265837 | 280.276ms | 2632 | 80 | 3452.76 | 2471.29 | 0.400683 | 3(Loss) | true |
| glaze | 978.347 | 0.127748 | 262.5ms | 2632 | 640 | 6874.97 | 2565.62 | 0.0308865 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1804.47 | 0.399103 | 197.179ms | 2632 | 2560 | 78900.9 | 1391.03 | 0.513713 | 1(Win) | true |
| simdjson (ondemand) | 1390.78 | 0.577926 | 232.826ms | 2632 | 320 | 34813.7 | 1804.79 | 0.0792399 | 2(Loss) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1274.97 | 1.09608 | 237.387ms | 2632 | 4890 | 2.27702e+06 | 1968.73 | 0.404744 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1238.63 | 1.18895 | 245.133ms | 2632 | 80 | 46441.1 | 2026.49 | 1.88996 | 3(Tie) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7397.11 | 0.202152 | 40.0127ms | 2632 | 640 | 301.151 | 339.331 | 0.58048 | 1(Win) | true |
| glaze | 2429.1 | 0.356141 | 136.313ms | 2632 | 30 | 406.299 | 1033.33 | 0.52944 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8574.84 | 0.802131 | 36.2104ms | 2632 | 80 | 441.063 | 292.725 | 2.08229 | 1(Win) | true |
| glaze | 3060.83 | 0.264146 | 98.2483ms | 2632 | 160 | 750.763 | 820.062 | 0.0304762 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1500.47 | 0.373597 | 282.777ms | 3643 | 30 | 2244.87 | 2315.43 | 4.18764 | 1(Win) | true |
| jsonifier (two-stage) | 1398.29 | 0.753208 | 262.768ms | 3643 | 160 | 56036.6 | 2484.62 | 0.405852 | 2(Loss) | true |
| simdjson (ondemand) | 1356.91 | 0.174804 | 284.786ms | 3643 | 40 | 801.272 | 2560.4 | 0.0260308 | 3(Loss) | true |
| glaze | 1068.48 | 2.74849 | 326.885ms | 3643 | 160 | 1.27789e+06 | 3251.56 | 1.49877 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1966.68 | 0.270025 | 209.523ms | 3643 | 2560 | 58250.4 | 1766.55 | 0.0197645 | 1(Win) | true |
| jsonifier (two-stage) | 1907.1 | 0.180386 | 217.878ms | 3643 | 4890 | 52806.8 | 1821.74 | 0.00814056 | 2(Loss) | true |
| simdjson (ondemand) | 1873.32 | 0.234158 | 229.315ms | 3643 | 1280 | 24139.3 | 1854.59 | 1.90571 | 3(Loss) | true |
| glaze | 1726.29 | 0.407994 | 232.619ms | 3643 | 40 | 2696.87 | 2012.55 | 0.208295 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8545.9 | 0.201904 | 47.6906ms | 3643 | 4890 | 3294.58 | 406.538 | 1.83223 | 1(Win) | true |
| glaze | 2834.76 | 0.251403 | 127.805ms | 3682 | 4890 | 47422.5 | 1238.7 | 0.518795 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11688.6 | 0.883036 | 37.0802ms | 3643 | 30 | 206.668 | 297.233 | 0.950979 | 1(Win) | true |
| glaze | 3422.45 | 0.597398 | 121.9ms | 3682 | 80 | 3005.47 | 1026 | 0.306078 | 2(Loss) | true |
