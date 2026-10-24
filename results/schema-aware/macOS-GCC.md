# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier: [1ed6e0c](https://github.com/nihilai-collective/jsonifier/commit/1ed6e0c)  
| Glaze: [1476d6b](https://github.com/stephenberry/glaze/commit/1476d6b)  
| Simdjson: [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
| **simdjson (reflection)** | `arm64` |
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
* **simdjson (reflection):** C++26 static reflection API (P2996). Minified serialization only.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1252.24 | 0.280089 | 7394.44ms | 94653 | 640 | 2.60896e+07 | 72085.6 | 0.085381 | 1(Win) | true |
| glaze | 1124.74 | 0.0556824 | 8260.27ms | 94653 | 4890 | 9.76585e+06 | 80256.9 | 0.0514143 | 2(Loss) | true |
| jsonifier (two-stage) | 991.873 | 0.060473 | 9204.03ms | 94653 | 4890 | 1.48112e+07 | 91007.8 | 0.161822 | 3(Loss) | true |
| simdjson (reflection) | 884.32 | 0.0677844 | 5359.3ms | 94653 | 2560 | 1.2256e+07 | 102076 | 0.0604815 | 4(Loss) | true |
| simdjson (ondemand) | 844.608 | 0.153328 | 5571.18ms | 94653 | 1280 | 3.43727e+07 | 106876 | 0.119721 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2197.9 | 0.137662 | 6094.88ms | 94653 | 1280 | 4.09161e+06 | 41070.2 | 0.426223 | 1(Win) | true |
| glaze | 1657.8 | 0.112993 | 7319.59ms | 94653 | 1280 | 4.84528e+06 | 54450.4 | 0.016899 | 2(Loss) | true |
| jsonifier (two-stage) | 1441.61 | 0.181467 | 8135.35ms | 94653 | 640 | 8.2633e+06 | 62616.4 | 0.0991137 | 3(Loss) | true |
| simdjson (ondemand) | 1109.5 | 0.134756 | 5193.62ms | 94653 | 640 | 7.69292e+06 | 81359.2 | 0.0442678 | 4(Loss) | true |
| simdjson (reflection) | 1072.86 | 0.124595 | 5733.04ms | 94653 | 640 | 7.03328e+06 | 84137.6 | 0.328157 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12075.7 | 0.68761 | 773.456ms | 94653 | 320 | 845435 | 7475.2 | 0.743573 | 1(Win) | true |
| simdjson (reflection) | 8735.74 | 0.523013 | 1152.09ms | 94653 | 640 | 1.86928e+06 | 10333.2 | 0.527532 | 2(Loss) | true |
| glaze | 4430.47 | 0.671637 | 1963.41ms | 94653 | 320 | 5.99224e+06 | 20374.4 | 0.624259 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12407.1 | 0.278506 | 735.041ms | 94653 | 2560 | 1.05108e+06 | 7275.5 | 1.01899 | 1(Win) | true |
| simdjson (reflection) | 7561.98 | 0.558405 | 1116.81ms | 94653 | 2560 | 1.13746e+07 | 11937.1 | 0.217442 | 2(Loss) | true |
| glaze | 6623.86 | 0.634859 | 1621.73ms | 94653 | 30 | 224555 | 13627.7 | 0.498442 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1308.47 | 0.355607 | 9222.41ms | 124611 | 40 | 4.17242e+06 | 90822.4 | 0.0305451 | 1(Win) | true |
| jsonifier (two-stage) | 1251.16 | 0.111949 | 9537.3ms | 124611 | 1280 | 1.44724e+07 | 94982.4 | 0.125232 | 2(Loss) | true |
| simdjson (reflection) | 1119.14 | 0.251102 | 5571.04ms | 124611 | 160 | 1.13753e+07 | 106187 | 0.0467318 | 3(Loss) | true |
| simdjson (ondemand) | 1075.99 | 0.102585 | 5745.82ms | 124611 | 1280 | 1.64314e+07 | 110445 | 0.044748 | 4(Loss) | true |
| glaze | 905.393 | 0.197026 | 5815.46ms | 124611 | 320 | 2.1401e+07 | 131256 | 0.168504 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1913.48 | 0.116919 | 8189.76ms | 124611 | 2560 | 1.34983e+07 | 62105.9 | 0.0246414 | 1(Win) | true |
| glaze STATISTICAL TIE | 1809 | 0.128084 | 8527.14ms | 124611 | 640 | 4.5311e+06 | 65692.8 | 0.0462546 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1799.97 | 0.598735 | 8528.78ms | 124611 | 40 | 6.25045e+06 | 66022.4 | 0.167742 | 2(Tie) | true |
| simdjson (ondemand) | 1415.6 | 0.206995 | 5347.42ms | 124611 | 40 | 1.20784e+06 | 83948.8 | 0.266119 | 4(Loss) | true |
| simdjson (reflection) | 1348.03 | 0.467365 | 5498.51ms | 124611 | 80 | 1.35805e+07 | 88156.8 | 0.0181528 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14582.2 | 0.204082 | 901.626ms | 136037 | 320 | 105494 | 8896.8 | 0.170557 | 1(Win) | true |
| glaze | 4821.02 | 0.151478 | 2694.11ms | 136076 | 640 | 1.06405e+06 | 26918 | 0.609972 | 2(Loss) | true |
| simdjson (reflection) | 405.32 | 0.105062 | 8221.07ms | 136037 | 1280 | 1.44751e+08 | 320080 | 0.377971 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14925.4 | 0.205343 | 876.796ms | 136037 | 1280 | 407783 | 8692.2 | 0.10826 | 1(Win) | true |
| glaze | 5623.1 | 0.188608 | 2344.97ms | 136076 | 40 | 75786.5 | 23078.4 | 0.0554939 | 2(Loss) | true |
| simdjson (reflection) | 409.385 | 0.194223 | 8263.47ms | 136037 | 80 | 3.03068e+07 | 316902 | 0.198308 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1633.72 | 0.481106 | 157.235ms | 2632 | 4890 | 267184 | 1536.42 | 0.229553 | 1(Win) | true |
| jsonifier (two-stage) | 1409.68 | 0.485323 | 182.097ms | 2632 | 2560 | 191177 | 1780.6 | 0.280018 | 2(Loss) | true |
| glaze | 1180.1 | 0.564325 | 213.762ms | 2632 | 1280 | 184418 | 2127 | 0.633989 | 3(Loss) | true |
| simdjson (reflection) | 1103.86 | 0.409225 | 232.25ms | 2632 | 2560 | 221670 | 2273.9 | 0.381144 | 4(Loss) | true |
| simdjson (ondemand) | 959.507 | 1.071 | 265.114ms | 2632 | 320 | 251191 | 2616 | 0.122474 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2229.75 | 0.48265 | 142.387ms | 2632 | 4890 | 144356 | 1125.72 | 0.255234 | 1(Win) | true |
| glaze STATISTICAL TIE | 1854.09 | 0.715279 | 162.902ms | 2632 | 2560 | 240049 | 1353.8 | 0.207254 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1799.59 | 1.41604 | 167.457ms | 2632 | 640 | 249662 | 1394.8 | 0.371429 | 2(Tie) | true |
| simdjson (ondemand) | 1329.15 | 0.284744 | 218.261ms | 2632 | 4890 | 141399 | 1888.48 | 0.527561 | 4(Loss) | true |
| simdjson (reflection) | 1200.42 | 0.603682 | 239.28ms | 2632 | 2560 | 407910 | 2091 | 0.143266 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9602.7 | 2.56673 | 28.395ms | 2632 | 4890 | 220118 | 261.392 | 0.49682 | 1(Win) | true |
| simdjson (reflection) | 7551.78 | 2.10158 | 35.5269ms | 2632 | 4890 | 238601 | 332.381 | 0.508372 | 2(Loss) | true |
| glaze | 2861.46 | 0.812853 | 90.242ms | 2632 | 2560 | 130155 | 877.2 | 0.389105 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11464.9 | 2.71295 | 24.4961ms | 2632 | 4890 | 172513 | 218.935 | 0.0296944 | 1(Win) | true |
| simdjson (reflection) | 8229.71 | 2.2131 | 32.9782ms | 2632 | 4890 | 222799 | 305.001 | 0.461537 | 2(Loss) | true |
| glaze | 3267.21 | 0.822247 | 79.221ms | 2632 | 4890 | 195133 | 768.262 | 0.623675 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1829.12 | 0.401706 | 192.485ms | 3643 | 2560 | 149035 | 1899.4 | 0.0526759 | 1(Win) | true |
| jsonifier | 1773.61 | 0.21816 | 199.984ms | 3643 | 4890 | 89301.5 | 1958.84 | 0.50513 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1466.54 | 0.421038 | 240.833ms | 3643 | 2560 | 254690 | 2369 | 0.462185 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1457.03 | 0.311162 | 244.118ms | 3643 | 4890 | 269194 | 2384.46 | 0.0656604 | 3(Tie) | true |
| simdjson (ondemand) | 1277.37 | 0.300357 | 276.199ms | 3643 | 4890 | 326338 | 2719.83 | 0.0525992 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2297.82 | 0.510577 | 180.208ms | 3643 | 4890 | 291419 | 1511.97 | 0.183578 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2283.67 | 0.49246 | 181.962ms | 3643 | 4890 | 274476 | 1521.34 | 0.246541 | 1(Tie) | true |
| glaze | 2157.24 | 0.617128 | 189.573ms | 3643 | 2560 | 252878 | 1610.5 | 0.00620887 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1785.69 | 1.93105 | 242.382ms | 3643 | 40 | 56461.8 | 1945.6 | 0.440529 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1734.69 | 0.518543 | 229.121ms | 3643 | 640 | 69028 | 2002.8 | 0.14 | 4(Tie) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11390.9 | 2.1679 | 33.535ms | 3643 | 4890 | 213791 | 305.001 | 0.197512 | 1(Win) | true |
| glaze | 3506.39 | 0.537183 | 106.019ms | 3682 | 4890 | 141514 | 1001.44 | 0.273996 | 2(Loss) | true |
| simdjson (reflection) | 367.188 | 0.158196 | 949.819ms | 3643 | 4890 | 1.09558e+06 | 9461.74 | 0.0407892 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12883.6 | 2.36322 | 29.4589ms | 3643 | 4890 | 198593 | 269.664 | 0.658381 | 1(Win) | true |
| glaze | 4859.44 | 1.74959 | 75.3111ms | 3682 | 1280 | 204588 | 722.6 | 1.66032 | 2(Loss) | true |
| simdjson (reflection) | 367.535 | 0.211563 | 951.196ms | 3643 | 1280 | 511929 | 9452.8 | 0.288576 | 3(Loss) | true |
