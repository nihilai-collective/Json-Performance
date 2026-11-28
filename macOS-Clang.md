# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the Clang 23.1.6 compiler).  

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
| Jsonifier STATISTICAL TIE | 1263.3 | 0.118942 | 71.6362ms | 905 | 640 | 422.604 | 683.189 | 0.284633 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1261.57 | 0.0649105 | 74.5503ms | 905 | 2560 | 504.83 | 684.129 | 0.031471 | 1(Tie) | true |
| simdjson (ondemand) | 309.84 | 0.114307 | 326.082ms | 905 | 40 | 405.536 | 2785.55 | 0.0185447 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1373.76 | 0.10399 | 66.711ms | 905 | 320 | 136.586 | 628.256 | 0.186676 | 1(Win) | true |
| Glaze | 1334.02 | 0.482804 | 69.7169ms | 905 | 2560 | 24977.7 | 646.971 | 0.126331 | 2(Loss) | true |
| simdjson (ondemand) | 283.798 | 0.118227 | 319.267ms | 905 | 80 | 1034.19 | 3041.16 | 0.290616 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1031.26 | 0.06399 | 87.1587ms | 905 | 1280 | 367.109 | 836.913 | 0.154825 | 1(Win) | true |
| Glaze | 131.229 | 0.243389 | 675.523ms | 905 | 4890 | 1.25299e+06 | 6576.88 | 0.5699 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1264.82 | 0.121831 | 79.6658ms | 905 | 640 | 442.321 | 682.369 | 0.00870055 | 1(Win) | true |
| Glaze | 766.603 | 0.051376 | 125.939ms | 905 | 640 | 214.12 | 1125.84 | 0.0759963 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 855.821 | 0.235281 | 204.462ms | 1811 | 30 | 676.34 | 2018.07 | 0.00165172 | 1(Win) | true |
| Glaze | 767.589 | 0.118747 | 226.811ms | 1811 | 80 | 571.1 | 2250.04 | 0.0472437 | 2(Loss) | true |
| simdjson (ondemand) | 250.334 | 2.49403 | 630.644ms | 1811 | 320 | 9.47439e+06 | 6899.2 | 0.829197 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 960.263 | 0.413193 | 188.538ms | 1811 | 1280 | 70692.4 | 1798.57 | 1.31662 | 1(Win) | true |
| Glaze | 912.888 | 0.0941784 | 194.65ms | 1811 | 160 | 507.955 | 1891.91 | 0.0132159 | 2(Loss) | true |
| simdjson (ondemand) | 299.784 | 0.0687541 | 578.471ms | 1811 | 30 | 470.695 | 5761.17 | 0.167509 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 301.252 | 0.251249 | 640.33ms | 1997 | 1280 | 322935 | 6321.91 | 0.104595 | 1(Win) | true |
| Glaze | 209.453 | 0.097935 | 824.287ms | 1798 | 40 | 2571.23 | 8186.57 | 0.196987 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 922.16 | 0.137954 | 219.651ms | 1997 | 4890 | 39693.6 | 2065.25 | 0.225877 | 1(Win) | true |
| Glaze | 709.009 | 0.0537459 | 258.8ms | 1798 | 160 | 270.325 | 2418.46 | 0.0752595 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1047.12 | 0.180165 | 127.849ms | 1313 | 80 | 371.336 | 1195.83 | 0.525398 | 1(Win) | true |
| Glaze | 641.267 | 0.0567404 | 192.085ms | 1313 | 640 | 785.628 | 1952.66 | 0.0239314 | 2(Loss) | true |
| simdjson (ondemand) | 289.42 | 0.103851 | 454.497ms | 1313 | 30 | 605.638 | 4326.5 | 0.0615977 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1405.23 | 0.0754512 | 92.5113ms | 1313 | 2560 | 1157.2 | 891.083 | 0.0039455 | 1(Win) | true |
| Glaze | 821.098 | 0.309602 | 160.903ms | 1313 | 30 | 668.759 | 1525 | 0.0875082 | 2(Loss) | true |
| simdjson (ondemand) | 303.791 | 0.0668995 | 430.879ms | 1313 | 40 | 304.148 | 4121.82 | 0.157743 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1201.78 | 0.139804 | 108.065ms | 1313 | 160 | 339.498 | 1041.93 | 0.0257868 | 1(Win) | true |
| Glaze | 178.14 | 0.046097 | 715.948ms | 1313 | 160 | 1679.85 | 7029.14 | 0.0448822 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1476.05 | 0.13187 | 96.2614ms | 1313 | 320 | 400.472 | 848.328 | 0.143502 | 1(Win) | true |
| Glaze | 826.461 | 0.141944 | 170.702ms | 1313 | 4890 | 22616.5 | 1515.1 | 1.12427 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1031.24 | 0.107933 | 364.272ms | 4215 | 40 | 708.025 | 3897.97 | 0.0558294 | 1(Win) | true |
| Glaze | 806.864 | 0.194456 | 497.277ms | 4215 | 1280 | 120128 | 4981.93 | 0.169461 | 2(Loss) | true |
| simdjson (ondemand) | 680.586 | 0.0873595 | 594.704ms | 4215 | 80 | 2129.8 | 5906.29 | 0.106992 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1528.92 | 0.116353 | 342.952ms | 4215 | 30 | 280.74 | 2629.13 | 0.106386 | 1(Win) | true |
| Glaze | 1042.25 | 0.101445 | 477.3ms | 4215 | 80 | 1224.64 | 3856.8 | 0.0110183 | 2(Loss) | true |
| simdjson (ondemand) | 818.684 | 0.100498 | 552.291ms | 4215 | 4890 | 119066 | 4910 | 0.135294 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 601.712 | 0.0751563 | 563.548ms | 4215 | 30 | 756.259 | 6680.5 | 0.0214509 | 1(Win) | true |
| Glaze | 503.846 | 0.0465205 | 815.13ms | 4215 | 80 | 1101.99 | 7978.1 | 0.0128493 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3335.43 | 0.161004 | 141.437ms | 4215 | 160 | 602.401 | 1205.16 | 0.0849785 | 1(Win) | true |
| Glaze | 1965.09 | 0.0635525 | 231.401ms | 4215 | 320 | 540.81 | 2045.57 | 0.0129871 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1104.67 | 0.252625 | 134.751ms | 1213 | 30 | 209.959 | 1047.2 | 0.136686 | 1(Win) | true |
| Glaze | 586.923 | 0.201724 | 202.993ms | 1213 | 320 | 5058.53 | 1970.97 | 0.150397 | 2(Loss) | true |
| simdjson (ondemand) | 221.726 | 0.393753 | 524.072ms | 1213 | 1280 | 540190 | 5217.28 | 0.398117 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1463.82 | 0.176044 | 94.5645ms | 1213 | 30 | 58.0644 | 790.267 | 0.528657 | 1(Win) | true |
| Glaze | 763.418 | 0.308584 | 161.623ms | 1213 | 30 | 655.941 | 1515.3 | 0.182249 | 2(Loss) | true |
| simdjson (ondemand) | 228.801 | 0.402753 | 487.563ms | 1213 | 1280 | 530752 | 5055.94 | 1.53676 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1021.62 | 0.515267 | 125.178ms | 1213 | 320 | 10893.3 | 1132.33 | 1.93534 | 1(Win) | true |
| Glaze | 162.026 | 0.120998 | 804.111ms | 1213 | 40 | 2985.16 | 7139.65 | 0.261001 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1006.82 | 0.847806 | 112.517ms | 1213 | 80 | 7591.09 | 1148.97 | 1.37418 | 1(Win) | true |
| Glaze | 660.91 | 0.606081 | 196.614ms | 1213 | 640 | 72024 | 1750.32 | 0.0400979 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6781.71 | 0.38942 | 6602.53ms | 466906 | 640 | 4.18405e+07 | 65658.4 | 0.776939 | 1(Win) | true |
| Jsonifier | 6247.2 | 0.297042 | 7074.38ms | 466906 | 1280 | 5.73767e+07 | 71276.2 | 0.806401 | 2(Loss) | true |
| Glaze | 1579.87 | 0.166649 | 7449.47ms | 466906 | 1280 | 2.82378e+08 | 281844 | 1.86635 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6898.49 | 0.696994 | 6872.54ms | 466906 | 160 | 3.23839e+07 | 64546.9 | 2.1839 | 1(Win) | true |
| Jsonifier | 6248.51 | 0.153931 | 7476.12ms | 466906 | 4890 | 5.88396e+07 | 71261.2 | 0.868211 | 2(Loss) | true |
| Glaze | 1618.72 | 0.315828 | 7322.36ms | 466906 | 80 | 6.03821e+07 | 275080 | 0.132921 | 3(Loss) | true |
