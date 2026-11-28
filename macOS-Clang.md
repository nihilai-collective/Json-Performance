# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the Clang 23.1.6 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [899f304](https://github.com/nihilai-collective/Jsonifier/commit/899f304)  
| Glaze: [283c9664](https://github.com/stephenberry/glaze/commit/283c9664)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `NEON` |
| **simdjson (ondemand)** | `arm64` |
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
* **simdjson (reflection):** Not in this run, since this toolchain does not support P2996 static reflection yet.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [23af44c](https://github.com/nihilai-collective/benchmarksuite/commit/23af44c)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1174.68 | 0.69212 | 95.1269ms | 905 | 30 | 775.789 | 734.733 | 0.400838 | 1(Win) | true |
| Glaze | 959.539 | 1.19404 | 82.8365ms | 905 | 160 | 18455.7 | 899.469 | 0.226339 | 2(Loss) | true |
| simdjson (ondemand) | 273.868 | 0.790694 | 311.929ms | 905 | 320 | 198693 | 3151.43 | 1.42055 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1292.56 | 0.570932 | 74.0777ms | 905 | 40 | 581.333 | 667.725 | 0.344387 | 1(Win) | true |
| Jsonifier | 1230.46 | 0.372084 | 76.261ms | 905 | 640 | 4359.4 | 701.427 | 0.0737881 | 2(Loss) | true |
| simdjson (ondemand) | 281.946 | 0.24201 | 310.129ms | 905 | 30 | 1646.46 | 3061.13 | 0.136301 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1032.3 | 0.0590483 | 94.4496ms | 905 | 640 | 155.984 | 836.07 | 0.0924232 | 1(Win) | true |
| Glaze | 123.49 | 0.182949 | 711.539ms | 905 | 4890 | 799472 | 6989.04 | 0.28058 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1176.13 | 0.327271 | 83.882ms | 905 | 80 | 461.412 | 733.825 | 0.359822 | 1(Win) | true |
| Glaze | 715.811 | 0.353535 | 140.744ms | 905 | 160 | 2907.27 | 1205.73 | 0.0885607 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 873 | 0.165896 | 210.691ms | 1811 | 160 | 1723.46 | 1978.36 | 0.360495 | 1(Win) | true |
| Glaze | 770.352 | 0.0955009 | 219.76ms | 1811 | 160 | 733.49 | 2241.97 | 0.103532 | 2(Loss) | true |
| simdjson (ondemand) | 284.171 | 0.185196 | 641.127ms | 1811 | 30 | 3800.7 | 6077.7 | 0.0476927 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1045.08 | 0.1114 | 176.348ms | 1811 | 160 | 542.279 | 1652.6 | 0.25049 | 1(Win) | true |
| Glaze | 904.539 | 0.233277 | 194.228ms | 1811 | 40 | 793.574 | 1909.38 | 0.0920047 | 2(Loss) | true |
| simdjson (ondemand) | 300.293 | 0.0243419 | 607.554ms | 1811 | 30 | 58.8 | 5751.4 | 0.931306 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 279.532 | 0.397632 | 686.963ms | 1997 | 2560 | 1.87886e+06 | 6813.12 | 0.548308 | 1(Win) | true |
| Glaze | 208.602 | 0.276565 | 820.813ms | 1798 | 640 | 330765 | 8220 | 1.14655 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 912.45 | 0.474979 | 228.148ms | 1997 | 160 | 15725.6 | 2087.22 | 0.0885559 | 1(Win) | true |
| Glaze | 676.026 | 0.101629 | 283.081ms | 1798 | 320 | 2126.35 | 2536.45 | 0.194529 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1093.68 | 0.0534885 | 122.824ms | 1313 | 1280 | 480.046 | 1144.92 | 0.165471 | 1(Win) | true |
| Glaze | 614.082 | 0.196772 | 200.618ms | 1313 | 80 | 1287.94 | 2039.1 | 0.175016 | 2(Loss) | true |
| simdjson (ondemand) | 264.956 | 0.281984 | 463.372ms | 1313 | 4890 | 868445 | 4725.98 | 0.924034 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1464.68 | 0.203054 | 88.8264ms | 1313 | 160 | 482.156 | 854.913 | 0.153289 | 1(Win) | true |
| Glaze | 778.058 | 0.313513 | 165.759ms | 1313 | 640 | 16292.8 | 1609.36 | 0.00961083 | 2(Loss) | true |
| simdjson (ondemand) | 288.309 | 0.320217 | 436.886ms | 1313 | 1280 | 247578 | 4343.16 | 0.673007 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1163.33 | 0.616754 | 115.969ms | 1313 | 30 | 1322.1 | 1076.37 | 0.654593 | 1(Win) | true |
| Glaze | 162.434 | 0.379226 | 784.331ms | 1313 | 2560 | 2.18783e+06 | 7708.82 | 0.0213488 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1395.95 | 0.551278 | 102.573ms | 1313 | 1280 | 31299.7 | 897.004 | 0.180224 | 1(Win) | true |
| Glaze | 804.875 | 0.261021 | 184.724ms | 1313 | 80 | 1319.21 | 1555.74 | 0.571205 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1166.88 | 0.141362 | 358.536ms | 4215 | 4890 | 115962 | 3444.85 | 0.69572 | 1(Win) | true |
| Glaze | 759.424 | 0.252586 | 533.044ms | 4215 | 2560 | 457600 | 5293.14 | 0.294174 | 2(Loss) | true |
| simdjson (ondemand) | 654.801 | 0.224117 | 667.951ms | 4215 | 30 | 5678.67 | 6138.87 | 2.05421 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1634.42 | 0.128404 | 310.354ms | 4215 | 40 | 398.917 | 2459.43 | 0.0125352 | 1(Win) | true |
| Glaze | 994.043 | 0.30847 | 468.553ms | 4215 | 40 | 6223.99 | 4043.82 | 0.358313 | 2(Loss) | true |
| simdjson (ondemand) | 820.69 | 0.109905 | 601.415ms | 4215 | 40 | 1159.13 | 4898 | 0.094507 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 716.635 | 0.515828 | 566.403ms | 4215 | 1280 | 1.07157e+06 | 5609.18 | 1.03578 | 1(Win) | true |
| Glaze | 434.02 | 0.670822 | 928.679ms | 4215 | 640 | 2.47042e+06 | 9261.64 | 1.22964 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3210.6 | 0.385988 | 137.485ms | 4215 | 640 | 14946.8 | 1252.02 | 1.88253 | 1(Win) | true |
| Glaze | 1717.39 | 0.295867 | 235.278ms | 4215 | 2560 | 122770 | 2340.61 | 2.30267 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1023.75 | 0.153003 | 118.889ms | 1213 | 320 | 956.494 | 1129.97 | 0.185082 | 1(Win) | true |
| Glaze | 612.055 | 0.208274 | 194.526ms | 1213 | 80 | 1239.66 | 1890.04 | 0.0323963 | 2(Loss) | true |
| simdjson (ondemand) | 247.361 | 0.184516 | 483.39ms | 1213 | 30 | 2233.83 | 4676.6 | 0.319012 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1390.51 | 0.180765 | 87.1642ms | 1213 | 2560 | 5789.49 | 831.93 | 0.290407 | 1(Win) | true |
| Glaze | 730.789 | 0.147625 | 163.184ms | 1213 | 4890 | 26703.4 | 1582.96 | 0.330502 | 2(Loss) | true |
| simdjson (ondemand) | 258.826 | 0.202719 | 455.717ms | 1213 | 4890 | 401424 | 4469.45 | 0.550037 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1053.32 | 0.139066 | 116.431ms | 1213 | 4890 | 11406.5 | 1098.25 | 0.858425 | 1(Win) | true |
| Glaze | 162.358 | 0.092931 | 742.44ms | 1213 | 30 | 1315.27 | 7125.03 | 0.214276 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1271.07 | 0.580315 | 104.362ms | 1213 | 4890 | 136401 | 910.103 | 0.598219 | 1(Win) | true |
| Glaze | 743.076 | 0.184911 | 171.926ms | 1213 | 1280 | 10607 | 1556.78 | 0.670198 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6940.37 | 0.413985 | 6336.73ms | 466906 | 320 | 2.25742e+07 | 64157.4 | 0.969163 | 1(Win) | true |
| Jsonifier | 6561.44 | 0.410321 | 7391.86ms | 466906 | 640 | 4.96236e+07 | 67862.6 | 0.380784 | 2(Loss) | true |
| Glaze | 1594.79 | 0.346464 | 7916.41ms | 466906 | 160 | 1.49723e+08 | 279207 | 0.242347 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7453.23 | 0.133911 | 5934.35ms | 466906 | 2560 | 1.63849e+07 | 59742.7 | 0.0931597 | 1(Win) | true |
| Jsonifier | 6265.66 | 0.68646 | 6895.2ms | 466906 | 320 | 7.61564e+07 | 71066.2 | 0.618024 | 2(Loss) | true |
| Glaze | 1481.18 | 0.824542 | 7650.75ms | 466906 | 80 | 4.91543e+08 | 300623 | 0.495975 | 3(Loss) | true |
