# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Windows 10.0.26100 using the MSVC 19.52.37029.0 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
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
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 502.336 | 0.35025 | 176.523ms | 905 | 640 | 23176.4 | 1718.12 | 0.218739 | 4.84824 | 1(Win) | true |
| Glaze | 451.429 | 0.0975232 | 200.625ms | 905 | 320 | 1112.46 | 1911.88 | 0.325839 | 5.40416 | 2(Loss) | true |
| simdjson (ondemand) | 152.281 | 0.313122 | 579.639ms | 905 | 1280 | 403128 | 5667.66 | 0.0910596 | 16.1464 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 594.072 | 0.135932 | 149.602ms | 905 | 640 | 2495.99 | 1452.81 | 0.55615 | 4.08628 | 1(Win) | true |
| Glaze | 533.071 | 0.311335 | 166.97ms | 905 | 320 | 8130.78 | 1619.06 | 0.250289 | 4.55917 | 2(Loss) | true |
| simdjson (ondemand) | 159.681 | 0.0925069 | 556.653ms | 905 | 40 | 1000 | 5405 | 0.0308261 | 15.4117 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 846.801 | 0.157482 | 106.804ms | 905 | 640 | 1648.84 | 1019.22 | 0.138164 | 2.84974 | 1(Win) | true |
| Glaze | 84.6152 | 0.462214 | 1106.1ms | 905 | 2560 | 5.69018e+06 | 10200 | 0.156495 | 29.1645 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1408.38 | 0.313792 | 96.5049ms | 905 | 320 | 1183.29 | 612.812 | 0.255624 | 1.67808 | 1(Win) | true |
| Glaze | 430.596 | 0.127803 | 208.72ms | 905 | 160 | 1049.92 | 2004.38 | 0.279851 | 5.66918 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 798.353 | 0.518984 | 217.832ms | 1811 | 30 | 3781.61 | 2163.33 | 0 | 3.06368 | 1(Win) | true |
| Glaze | 393.418 | 0.167427 | 427.416ms | 1811 | 30 | 1620.69 | 4390 | 0.0759878 | 6.24082 | 2(Loss) | true |
| simdjson (ondemand) | 292.122 | 0.475829 | 594.065ms | 1811 | 1280 | 1.01302e+06 | 5912.27 | 0.250371 | 8.43208 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1140.94 | 0.255955 | 158.285ms | 1811 | 80 | 1200.95 | 1513.75 | 0.0825083 | 2.13441 | 1(Win) | true |
| Glaze | 491.12 | 0.19679 | 361.149ms | 1811 | 30 | 1436.78 | 3516.67 | 0.189934 | 5.00283 | 2(Loss) | true |
| simdjson (ondemand) | 336.231 | 0.174209 | 530.261ms | 1811 | 30 | 2402.3 | 5136.67 | 0.129618 | 7.31377 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 464.509 | 0.123505 | 435.332ms | 1997 | 40 | 1025.64 | 4100 | 0.162338 | 5.27187 | 1(Win) | true |
| Glaze | 135.085 | 0.565061 | 1326.84ms | 1798 | 2560 | 1.31703e+07 | 12693.6 | 0.368481 | 18.277 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 694.752 | 0.202048 | 296.285ms | 1997 | 80 | 2454.11 | 2741.25 | 0.0456204 | 3.52923 | 1(Win) | true |
| Glaze | 216.412 | 0.144261 | 486.289ms | 1798 | 30 | 3919.54 | 7923.33 | 0.126369 | 11.3852 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 883.904 | 0.809464 | 148.58ms | 1313 | 1280 | 168316 | 1416.64 | 1.94138 | 2.74976 | 1(Win) | true |
| Glaze | 352.849 | 0.279328 | 372.783ms | 1313 | 160 | 15721.7 | 3548.75 | 0.141093 | 6.94081 | 2(Loss) | true |
| simdjson (ondemand) | 278.958 | 0.0885614 | 475.934ms | 1313 | 80 | 1264.24 | 4488.75 | 0.251256 | 8.81254 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1475.86 | 0.329794 | 89.7732ms | 1313 | 320 | 2505.39 | 848.438 | 0.110619 | 1.62331 | 1(Win) | true |
| Glaze | 412.352 | 0.294683 | 312.431ms | 1313 | 30 | 2402.3 | 3036.67 | 0.219058 | 5.91813 | 2(Loss) | true |
| simdjson (ondemand) | 314.091 | 0.158338 | 407.215ms | 1313 | 30 | 1195.4 | 3986.67 | 0.167504 | 7.82374 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 584.275 | 0.183265 | 225.573ms | 1313 | 160 | 2468.16 | 2143.12 | 0.263158 | 4.18556 | 1(Win) | true |
| Glaze | 122.091 | 0.369833 | 1043.14ms | 1313 | 4890 | 7.03524e+06 | 10256 | 0.301199 | 20.2093 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1274.48 | 0.619272 | 107.21ms | 1313 | 40 | 1480.77 | 982.5 | 0.0847458 | 1.8905 | 1(Win) | true |
| Glaze | 666.05 | 0.395096 | 216.103ms | 1313 | 30 | 1655.17 | 1880 | 0.17762 | 3.66469 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 605.686 | 0.233913 | 687.696ms | 4215 | 30 | 7229.89 | 6636.67 | 0.100351 | 4.06335 | 1(Win) | true |
| Glaze | 477.782 | 0.203357 | 812.47ms | 4215 | 30 | 8781.61 | 8413.33 | 0.238284 | 5.16667 | 2(Loss) | true |
| simdjson (ondemand) | 382.957 | 0.261055 | 1094.29ms | 4215 | 1280 | 961098 | 10496.6 | 0.108549 | 6.43919 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1009.98 | 0.157393 | 547.277ms | 4215 | 80 | 3139.24 | 3980 | 0.125786 | 2.42996 | 1(Win) | true |
| Glaze | 789.926 | 0.17823 | 631.269ms | 4215 | 80 | 6580.7 | 5088.75 | 0.0737463 | 3.11714 | 2(Loss) | true |
| simdjson (ondemand) | 512.349 | 0.239943 | 920.812ms | 4215 | 1280 | 453617 | 7845.7 | 0.0408098 | 4.8153 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 489.55 | 0.190128 | 846.996ms | 4215 | 2560 | 623925 | 8211.09 | 0.227916 | 5.03915 | 1(Win) | true |
| Glaze | 402.445 | 0.273161 | 1025.03ms | 4215 | 1280 | 952857 | 9988.28 | 0.462458 | 6.13527 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3432.01 | 0.304158 | 135.328ms | 4215 | 320 | 4061.13 | 1171.25 | 0.106838 | 0.705741 | 1(Win) | true |
| Glaze | 1762.14 | 0.397896 | 255.075ms | 4215 | 1280 | 105454 | 2281.17 | 0.00342466 | 1.38653 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 797.798 | 0.552166 | 157.242ms | 1213 | 40 | 2564.1 | 1450 | 0.230415 | 3.04042 | 1(Win) | true |
| Glaze | 349.753 | 0.127517 | 355.875ms | 1213 | 40 | 711.538 | 3307.5 | 0.276382 | 6.98918 | 2(Loss) | true |
| simdjson (ondemand) | 261.13 | 0.165643 | 470.137ms | 1213 | 40 | 2153.85 | 4430 | 0.0753012 | 9.40695 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1334.94 | 0.215368 | 90.7641ms | 1213 | 640 | 2229.17 | 866.562 | 0 | 1.80117 | 1(Win) | true |
| Glaze | 398.899 | 0.123468 | 303.349ms | 1213 | 40 | 512.821 | 2900 | 0.115075 | 6.11307 | 2(Loss) | true |
| simdjson (ondemand) | 286.693 | 0.189284 | 420.816ms | 1213 | 40 | 2333.33 | 4035 | 0.373134 | 8.58234 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 608.246 | 0.0869065 | 197.63ms | 1213 | 320 | 874.216 | 1901.88 | 0.652955 | 4.01872 | 1(Win) | true |
| Glaze | 121.052 | 0.144005 | 974.121ms | 1213 | 80 | 15150.3 | 9556.25 | 0.117586 | 20.3616 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1481.9 | 0.401527 | 91.0877ms | 1213 | 160 | 1571.93 | 780.625 | 0.08 | 1.61793 | 1(Win) | true |
| Glaze | 654.433 | 0.313435 | 187.308ms | 1213 | 4890 | 150105 | 1767.65 | 0.407818 | 3.72215 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 774.461 | 0.886897 | 6041.21ms | 94653 | 640 | 6.83906e+08 | 116556 | 0.304316 | 3.19592 | 1(Win) | true |
| Glaze | 716.209 | 0.29183 | 6639.95ms | 94653 | 2560 | 3.46328e+08 | 126036 | 0.0439909 | 3.45584 | 2(Loss) | true |
| Jsonifier (two-stage) | 702.53 | 0.783336 | 6657.19ms | 94653 | 640 | 6.48357e+08 | 128490 | 0.405964 | 3.52323 | 3(Loss) | true |
| simdjson (ondemand) | 622.349 | 0.373524 | 7540.01ms | 94653 | 2560 | 7.51413e+08 | 145044 | 0.000888729 | 3.97728 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1209.87 | 0.217462 | 9457.15ms | 94653 | 640 | 1.68475e+07 | 74609.7 | 0.344774 | 2.04555 | 1(Win) | true |
| simdjson (ondemand) | 1115.63 | 0.552005 | 5229.14ms | 94653 | 80 | 1.59591e+07 | 80912.5 | 0.297499 | 2.21839 | 2(Loss) | true |
| Glaze | 1082.4 | 0.153552 | 5366.71ms | 94653 | 1280 | 2.09903e+07 | 83396.5 | 0.174407 | 2.28658 | 3(Loss) | true |
| Jsonifier (two-stage) | 1056.79 | 0.738431 | 5507.35ms | 94653 | 40 | 1.59138e+07 | 85417.5 | 0.0829948 | 2.34178 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11465 | 0.120775 | 832.452ms | 94653 | 30 | 2712.64 | 7873.33 | 0.212134 | 0.214822 | 1(Win) | true |
| Glaze | 4502.15 | 0.0472484 | 2044.31ms | 94653 | 40 | 3589.74 | 20050 | 0.333611 | 0.549182 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11758.8 | 0.10231 | 831.314ms | 94653 | 30 | 1850.57 | 7676.67 | 0.432339 | 0.209897 | 1(Win) | true |
| Glaze | 4966.01 | 0.371146 | 1861.96ms | 94653 | 640 | 2.91287e+06 | 18177.2 | 0.220541 | 0.497736 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 931.601 | 0.696123 | 6673.36ms | 124597 | 1280 | 1.00911e+09 | 127549 | 0.206658 | 2.65684 | 1(Win) | true |
| simdjson (ondemand) | 877.52 | 0.299267 | 7191.09ms | 124597 | 1280 | 2.10198e+08 | 135410 | 0.362163 | 2.82067 | 2(Loss) | true |
| Jsonifier (two-stage) | 838.882 | 0.497508 | 6847.27ms | 124597 | 640 | 3.17829e+08 | 141647 | 2.07359 | 2.95067 | 3(Loss) | true |
| Glaze | 821.409 | 0.599934 | 7546.46ms | 124597 | 1280 | 9.6408e+08 | 144660 | 0.386158 | 3.01331 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.6 | 0.214594 | 5081.58ms | 124597 | 640 | 1.93468e+07 | 81020.9 | 0.331374 | 1.68755 | 1(Win) | true |
| simdjson (ondemand) | 1419.87 | 0.130091 | 5317.36ms | 124597 | 1280 | 1.51714e+07 | 83687.4 | 0.529394 | 1.74316 | 2(Loss) | true |
| Jsonifier (two-stage) | 1356.77 | 0.206261 | 5939.31ms | 124597 | 320 | 1.04421e+07 | 87579.4 | 0.347317 | 1.82426 | 3(Loss) | true |
| Glaze | 1294.43 | 0.11111 | 5811.15ms | 124597 | 1280 | 1.33159e+07 | 91797.1 | 0.0805306 | 1.91205 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10346.1 | 0.471877 | 1291.91ms | 136037 | 1280 | 4.48151e+06 | 12539.5 | 0.455006 | 0.238648 | 1(Win) | true |
| Glaze | 3854.52 | 0.283533 | 3440.15ms | 136076 | 4890 | 4.45592e+07 | 33667.5 | 0.0788192 | 0.641741 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10728.6 | 0.143195 | 1272.31ms | 136037 | 40 | 11993.6 | 12092.5 | 0.57527 | 0.230142 | 1(Win) | true |
| Glaze | 4206.1 | 0.0672606 | 3208.62ms | 136076 | 30 | 12919.5 | 30853.3 | 0.505213 | 0.587902 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 509.159 | 2.18305 | 6197.8ms | 2251027 | 80 | 6.77753e+11 | 4.21626e+06 | 1.57331 | 4.86218 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 500.688 | 1.08176 | 6617.66ms | 2251027 | 80 | 1.72101e+11 | 4.2876e+06 | 6.60238 | 4.94443 | -(Tie) | false |
| simdjson (ondemand) | 184.763 | 1.23221 | 8321.46ms | 2251027 | 40 | 8.19897e+11 | 1.16189e+07 | 0.603562 | 13.3995 | 3(Loss) | true |
| Glaze | 168.346 | 0.524242 | 9000.72ms | 2251027 | 40 | 1.78764e+11 | 1.2752e+07 | 0.420342 | 14.7066 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 649.219 | 1.05813 | 6370.05ms | 2251027 | 80 | 9.7937e+10 | 3.30666e+06 | 0.293617 | 3.81312 | 1(Win) | true |
| Jsonifier (two-stage) | 622.639 | 0.834843 | 6524.35ms | 2251027 | 40 | 3.31404e+10 | 3.44782e+06 | 0.767708 | 3.97589 | 2(Loss) | true |
| simdjson (ondemand) | 204.007 | 0.850692 | 8215.04ms | 2251027 | 30 | 2.40401e+11 | 1.05229e+07 | 0.502676 | 12.1354 | 3(Loss) | true |
| Glaze | 183.525 | 0.779328 | 9017.16ms | 2251027 | 40 | 3.32409e+11 | 1.16973e+07 | 0.417587 | 13.49 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1285.22 | 0.13064 | 9864.85ms | 2090326 | 30 | 1.23181e+08 | 1.55108e+06 | 0.335512 | 1.92621 | 1(Win) | true |
| Glaze | 687.98 | 0.358354 | 9489.4ms | 2090234 | 40 | 4.31243e+09 | 2.89747e+06 | 0.0438506 | 3.59848 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.77 | 0.229158 | 7849.38ms | 2090326 | 40 | 3.08189e+08 | 1.21128e+06 | 0.525404 | 1.50428 | 1(Win) | true |
| Glaze | 886.646 | 0.225644 | 7105.06ms | 2090234 | 40 | 1.02943e+09 | 2.24825e+06 | 0.0357187 | 2.7923 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1296.2 | 1.66363 | 5969.2ms | 5373214 | 40 | 1.73019e+11 | 3.95332e+06 | 1.32131 | 1.91003 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1266.18 | 0.665422 | 6191.51ms | 5373214 | 40 | 2.90091e+10 | 4.04706e+06 | 0.182987 | 1.95532 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 428.345 | 3.27152 | 7914.74ms | 5373214 | 30 | 4.59515e+12 | 1.1963e+07 | 3.90769 | 5.77985 | -(Tie) | false |
| Glaze STATISTICAL TIE | 421.218 | 0.267145 | 8646.58ms | 5373214 | 30 | 3.16861e+10 | 1.21654e+07 | 0.819209 | 5.87777 | 3(Tie) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1533.34 | 0.878122 | 6047.84ms | 5373214 | 80 | 6.8896e+10 | 3.34193e+06 | 0.524214 | 1.6146 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1499.67 | 1.15078 | 6329.62ms | 5373214 | 40 | 6.18476e+10 | 3.41695e+06 | 1.97668 | 1.65088 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 492.755 | 1.07215 | 7680.43ms | 5373214 | 40 | 4.97257e+11 | 1.03993e+07 | 2.93644 | 5.0244 | -(Loss) | false |
| Glaze | 439.832 | 0.295667 | 8664.78ms | 5373214 | 30 | 3.55977e+10 | 1.16506e+07 | 1.17012 | 5.62884 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2767.71 | 0.120942 | 7295.24ms | 6661989 | 80 | 6.16612e+08 | 2.29554e+06 | 0.388697 | 0.894488 | 1(Win) | true |
| Glaze | 1040.62 | 1.30872 | 8700.68ms | 6661897 | 40 | 2.55364e+11 | 6.10526e+06 | 1.15295 | 2.3789 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4567.4 | 0.0663548 | 8969.23ms | 6661989 | 80 | 6.81561e+07 | 1.39102e+06 | 0.518844 | 0.542045 | 1(Win) | true |
| Glaze | 2523.86 | 0.140518 | 7845.28ms | 6661897 | 40 | 5.00484e+08 | 2.51729e+06 | 0.0206945 | 0.980938 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1484.86 | 0.301911 | 8412.23ms | 500299 | 40 | 3.7645e+07 | 321325 | 0.0212616 | 1.66723 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.49 | 0.277407 | 5266.21ms | 500299 | 30 | 3.61052e+07 | 395463 | 0.30001 | 2.05191 | 2(Loss) | true |
| Glaze | 672.882 | 0.286165 | 9252.41ms | 500299 | 160 | 6.58771e+08 | 709073 | 0.212612 | 3.67919 | 3(Loss) | true |
| simdjson (ondemand) | 637.813 | 0.322056 | 9640.23ms | 500299 | 30 | 1.74123e+08 | 748060 | 0.969572 | 3.88154 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1674.25 | 0.177205 | 8251.46ms | 500299 | 160 | 4.0803e+07 | 284976 | 0.445433 | 1.47858 | 1(Win) | true |
| Jsonifier (two-stage) | 1347.24 | 0.325742 | 5097.59ms | 500299 | 80 | 1.06466e+08 | 354149 | 0.248747 | 1.83748 | 2(Loss) | true |
| Glaze | 778.771 | 0.161913 | 8504.14ms | 500299 | 160 | 1.57444e+08 | 612661 | 0.166719 | 3.17898 | 3(Loss) | true |
| simdjson (ondemand) | 643.838 | 0.121179 | 10118.9ms | 500299 | 160 | 1.29026e+08 | 741060 | 0.327005 | 3.84521 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8762.98 | 0.432304 | 5555.85ms | 500299 | 160 | 8.86452e+06 | 54447.5 | 0.251901 | 0.282349 | 1(Win) | true |
| Glaze | 3184.93 | 0.148688 | 7817.24ms | 500299 | 1280 | 6.35074e+07 | 149806 | 0.543638 | 0.777168 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8695.37 | 0.160122 | 5471.67ms | 500299 | 1280 | 9.88089e+06 | 54870.9 | 0.285143 | 0.284551 | 1(Win) | true |
| Glaze | 3312.21 | 0.0887427 | 7421.82ms | 500299 | 1280 | 2.0917e+07 | 144050 | 0.122745 | 0.747313 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2554.03 | 0.1061 | 5627.89ms | 1151920 | 640 | 1.33293e+08 | 430127 | 0.057 | 0.969277 | 1(Win) | true |
| Jsonifier (two-stage) | 2419.89 | 1.27611 | 5740.8ms | 1151920 | 30 | 1.00682e+09 | 453970 | 1.71022 | 1.02303 | 2(Loss) | true |
| Glaze | 1358.11 | 0.25886 | 5269.12ms | 1151920 | 40 | 1.75374e+08 | 808888 | 1.15911 | 1.8229 | 3(Loss) | true |
| simdjson (ondemand) | 1310.96 | 0.230915 | 5246ms | 1151920 | 30 | 1.12329e+08 | 837980 | 0.403309 | 1.8885 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2777.49 | 0.192416 | 5532.88ms | 1151920 | 320 | 1.85341e+08 | 395522 | 0.325628 | 0.891309 | 1(Win) | true |
| Jsonifier (two-stage) | 2763.33 | 0.162727 | 5761.15ms | 1151920 | 160 | 6.69601e+07 | 397548 | 0.26139 | 0.895859 | 2(Loss) | true |
| Glaze | 1434.91 | 0.294644 | 5106.7ms | 1151920 | 30 | 1.52655e+08 | 765590 | 0.168782 | 1.72533 | 3(Loss) | true |
| simdjson (ondemand) | 1328.63 | 0.101918 | 5479.3ms | 1151920 | 320 | 2.27242e+08 | 826833 | 0.333134 | 1.86334 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3711.87 | 0.645251 | 9421.51ms | 1439562 | 30 | 1.70865e+08 | 369860 | 0.460846 | 0.666781 | 1(Win) | true |
| Glaze | 1971.07 | 0.125753 | 8902.17ms | 1439584 | 320 | 2.45505e+08 | 696522 | 0.28332 | 1.25583 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12218.3 | 0.464329 | 5787.18ms | 1439562 | 80 | 2.17763e+07 | 112362 | 0.630113 | 0.202573 | 1(Win) | true |
| Glaze | 5919.7 | 0.10731 | 6013.97ms | 1439584 | 640 | 3.96402e+07 | 231920 | 0.140476 | 0.418173 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1271.86 | 0.216957 | 4322.95ms | 56369 | 640 | 5.38181e+06 | 42266.9 | 0.177017 | 1.94523 | 1(Win) | true |
| Jsonifier (two-stage) | 966.012 | 0.272768 | 5689.58ms | 56369 | 320 | 7.37317e+06 | 55649.1 | 0.116377 | 2.56142 | 2(Loss) | true |
| Glaze | 940.05 | 0.252721 | 5842.52ms | 56369 | 640 | 1.33672e+07 | 57185.9 | 0.551123 | 2.63239 | 3(Loss) | true |
| simdjson (ondemand) | 740.55 | 0.282783 | 7517.55ms | 56369 | 320 | 1.34843e+07 | 72591.6 | 0.398928 | 3.34197 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1812.51 | 0.123511 | 3480.56ms | 56369 | 2560 | 3.43533e+06 | 29659.3 | 0.0610163 | 1.36472 | 1(Win) | true |
| Jsonifier (two-stage) | 1279.53 | 0.113855 | 4763.28ms | 56369 | 2560 | 5.85766e+06 | 42013.5 | 0.180419 | 1.9335 | 2(Loss) | true |
| Glaze | 1227.48 | 0.503282 | 4857.41ms | 56369 | 160 | 7.77306e+06 | 43795 | 0.477218 | 2.01583 | 3(Loss) | true |
| simdjson (ondemand) | 1039.56 | 0.352168 | 5892.59ms | 56369 | 320 | 1.06129e+07 | 51712.2 | 0.195573 | 2.38043 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10721 | 0.435438 | 512.386ms | 56369 | 1280 | 610196 | 5014.22 | 0.0747314 | 0.229645 | 1(Win) | true |
| Glaze | 2936.78 | 0.45602 | 1831.34ms | 56369 | 320 | 2.22976e+06 | 18305 | 0.239578 | 0.841585 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12104.2 | 0.124709 | 461.247ms | 56369 | 80 | 2454.11 | 4441.25 | 0.084507 | 0.203159 | 1(Win) | true |
| Glaze | 3180.1 | 0.379547 | 1763.9ms | 56369 | 320 | 1.31728e+06 | 16904.4 | 0.272851 | 0.777227 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1631.84 | 0.456558 | 5090.34ms | 83958 | 320 | 1.60588e+07 | 49066.6 | 0.171617 | 1.51633 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1348.85 | 0.33947 | 6229ms | 83958 | 160 | 6.49712e+06 | 59360.6 | 0.216309 | 1.83463 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1341.33 | 0.787267 | 6207.86ms | 83958 | 30 | 6.62547e+06 | 59693.3 | 0.350565 | 1.84448 | 2(Tie) | true |
| simdjson (ondemand) | 1065.47 | 0.22026 | 7779.14ms | 83958 | 640 | 1.75343e+07 | 75148.3 | 0.0770797 | 2.32258 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2222.45 | 0.322612 | 4242.69ms | 83958 | 320 | 4.32286e+06 | 36027.2 | 0.434407 | 1.11324 | 1(Win) | true |
| Glaze | 1894.71 | 0.149757 | 4927.13ms | 83958 | 1280 | 5.1265e+06 | 42259 | 0.0231143 | 1.30584 | 2(Loss) | true |
| Jsonifier (two-stage) | 1750.57 | 0.0890684 | 5302.62ms | 83958 | 4890 | 8.11565e+06 | 45738.7 | 0.267198 | 1.41337 | 3(Loss) | true |
| simdjson (ondemand) | 1403.86 | 0.0752404 | 6276.5ms | 83958 | 4890 | 9.00509e+06 | 57034.6 | 0.54036 | 1.7627 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10979.9 | 0.0712422 | 844.476ms | 94370 | 30 | 1022.99 | 8196.67 | 0 | 0.223935 | 1(Win) | true |
| Glaze | 3114.93 | 0.270814 | 2972.56ms | 94370 | 160 | 979566 | 28892.5 | 0.327727 | 0.794033 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11330 | 0.130626 | 827.017ms | 94370 | 30 | 3229.89 | 7943.33 | 0.167574 | 0.217626 | 1(Win) | true |
| Glaze | 3269.94 | 0.109073 | 2774.73ms | 94370 | 2560 | 2.30709e+06 | 27522.9 | 0.4023 | 0.756387 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1087.19 | 0.494794 | 4777.12ms | 53331 | 1280 | 6.85821e+07 | 46781.7 | 0.441819 | 2.2757 | 1(Win) | true |
| Glaze | 982.41 | 0.25504 | 5272.22ms | 53331 | 2560 | 4.46303e+07 | 51771.1 | 0.669566 | 2.51853 | 2(Loss) | true |
| Jsonifier (two-stage) | 961.967 | 0.685915 | 5491.58ms | 53331 | 80 | 1.05213e+07 | 52871.2 | 0.224099 | 2.57178 | 3(Loss) | true |
| simdjson (ondemand) | 633.513 | 0.159469 | 8171.33ms | 53331 | 2560 | 4.19607e+07 | 80283.1 | 0.480541 | 3.90664 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1652.45 | 0.107968 | 3862.2ms | 53331 | 4890 | 5.40009e+06 | 30778.8 | 0.268394 | 1.49674 | 1(Win) | true |
| Glaze | 1343.81 | 0.279591 | 4535.54ms | 53331 | 640 | 7.16657e+06 | 37848 | 0.0342771 | 1.84097 | 2(Loss) | true |
| Jsonifier (two-stage) | 1306.35 | 0.695588 | 4677.91ms | 53331 | 30 | 2.20023e+06 | 38933.3 | 0.2317 | 1.89355 | 3(Loss) | true |
| simdjson (ondemand) | 794.632 | 0.780146 | 7450.87ms | 53331 | 40 | 9.97331e+06 | 64005 | 0.0078125 | 3.11475 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10778.2 | 0.186919 | 539.584ms | 58581 | 30 | 2816.09 | 5183.33 | 0 | 0.228541 | 1(Win) | true |
| Glaze | 4481.93 | 0.126122 | 1316.74ms | 58581 | 80 | 19772.2 | 12465 | 0.776119 | 0.551464 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11858.3 | 0.136109 | 480.751ms | 58581 | 80 | 3289.56 | 4711.25 | 0.0795334 | 0.207711 | 1(Win) | true |
| Glaze | 5308.05 | 0.143328 | 1087.76ms | 58581 | 40 | 9102.56 | 10525 | 0.429389 | 0.46499 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1170.96 | 0.484393 | 5400.77ms | 65103 | 160 | 1.05545e+07 | 53022.5 | 0.4903 | 2.11293 | 1(Win) | true |
| Jsonifier (two-stage) | 1112.21 | 0.157888 | 5669.8ms | 65103 | 4890 | 3.79872e+07 | 55823.2 | 0.383612 | 2.22469 | 2(Loss) | true |
| Glaze | 1106.66 | 0.172352 | 5786.65ms | 65103 | 4890 | 4.57207e+07 | 56103.1 | 0.131311 | 2.23578 | 3(Loss) | true |
| simdjson (ondemand) | 737.941 | 0.194681 | 8327.78ms | 65103 | 2560 | 6.86821e+07 | 84135.5 | 0.290973 | 3.35373 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1706.57 | 0.5765 | 4478.31ms | 65103 | 160 | 7.03839e+06 | 36381.2 | 0.0274791 | 1.44947 | 1(Win) | true |
| Jsonifier (two-stage) | 1568.37 | 0.187693 | 4763.68ms | 65103 | 1280 | 7.06658e+06 | 39587 | 0.142888 | 1.57728 | 2(Loss) | true |
| Glaze | 1541.86 | 0.16471 | 4854.02ms | 65103 | 1280 | 5.6307e+06 | 40267.7 | 0.356102 | 1.6046 | 3(Loss) | true |
| simdjson (ondemand) | 913.408 | 0.0911017 | 7547.27ms | 65103 | 4890 | 1.87514e+07 | 67973 | 0.15174 | 2.70939 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10296.3 | 0.15387 | 771.639ms | 78778 | 30 | 3781.61 | 7296.67 | 0.0457038 | 0.239234 | 1(Win) | true |
| Glaze | 4264.42 | 0.235888 | 1774.79ms | 78778 | 2560 | 4.42124e+06 | 17617.5 | 0.272201 | 0.579639 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10312.8 | 0.0926056 | 745.725ms | 78778 | 40 | 1820.51 | 7285 | 0.0228728 | 0.239072 | 1(Win) | true |
| Glaze | 4813.75 | 0.153078 | 1637.1ms | 78778 | 2560 | 1.4612e+06 | 15607.1 | 0.0528385 | 0.513359 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1171.38 | 0.122971 | 998.186ms | 11812 | 30 | 4195.4 | 9616.67 | 0.03465 | 2.10744 | 1(Win) | true |
| Jsonifier (two-stage) | 1013.73 | 0.143005 | 1136.85ms | 11812 | 4890 | 1.23485e+06 | 11112.2 | 0.717021 | 2.43497 | 2(Loss) | true |
| Glaze | 805.168 | 0.507091 | 1451.95ms | 11812 | 320 | 1.61063e+06 | 13990.6 | 0.0892658 | 3.06843 | 3(Loss) | true |
| simdjson (ondemand) | 561.678 | 0.365655 | 2037.66ms | 11812 | 160 | 860471 | 20055.6 | 0.115437 | 4.40135 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1311.04 | 0.15346 | 1002.87ms | 11812 | 4890 | 850192 | 8592.27 | 0.114747 | 1.88245 | 1(Win) | true |
| Jsonifier (two-stage) | 1130.19 | 0.145603 | 1134.71ms | 11812 | 4890 | 1.0299e+06 | 9967.18 | 0.180051 | 2.18457 | 2(Loss) | true |
| Glaze | 906.308 | 0.133697 | 1330.1ms | 11812 | 4890 | 1.35036e+06 | 12429.3 | 0.318027 | 2.72585 | 3(Loss) | true |
| simdjson (ondemand) | 623.053 | 0.53636 | 1933.55ms | 11812 | 160 | 1.50463e+06 | 18080 | 0.0828958 | 3.96698 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7144.1 | 0.657158 | 162.589ms | 11812 | 1280 | 137436 | 1576.8 | 0.644875 | 0.340715 | 1(Win) | true |
| Glaze | 2769.47 | 0.251698 | 410.058ms | 11812 | 2560 | 268322 | 4067.5 | 0.461167 | 0.88779 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7844.91 | 0.187088 | 148.736ms | 11812 | 320 | 2309.46 | 1435.94 | 0.0652458 | 0.309509 | 1(Win) | true |
| Glaze | 3175.42 | 0.225409 | 375.874ms | 11812 | 40 | 2557.69 | 3547.5 | 0.0234962 | 0.774255 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2093.25 | 0.126638 | 1180.92ms | 25388 | 30 | 6436.78 | 11566.7 | 0.143885 | 1.18171 | 1(Win) | true |
| Jsonifier (two-stage) | 1991.42 | 0.249934 | 1227.53ms | 25388 | 1280 | 1.18194e+06 | 12158.1 | 0.0719166 | 1.24004 | 2(Loss) | true |
| Glaze | 1394.93 | 0.28957 | 1765.07ms | 25388 | 640 | 1.61673e+06 | 17357 | 0.171645 | 1.77184 | 3(Loss) | true |
| simdjson (ondemand) | 1157.99 | 0.142578 | 2109.37ms | 25388 | 2560 | 2.27507e+06 | 20908.6 | 0.282717 | 2.13501 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2367.07 | 0.160962 | 1144.45ms | 25388 | 4890 | 1.32553e+06 | 10228.6 | 0.274058 | 1.04316 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.53 | 0.104641 | 1213.73ms | 25388 | 30 | 3919.54 | 10923.3 | 0 | 1.11405 | 2(Loss) | true |
| Glaze | 1585.59 | 0.109447 | 1710.44ms | 25388 | 30 | 8379.31 | 15270 | 0.152572 | 1.55882 | 3(Loss) | true |
| simdjson (ondemand) | 1250.17 | 0.189925 | 1992.87ms | 25388 | 2560 | 3.46354e+06 | 19366.8 | 0.354425 | 1.97753 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11143.5 | 0.139634 | 271.842ms | 31235 | 160 | 2229.17 | 2673.12 | 0.116768 | 0.220182 | 1(Win) | true |
| Glaze | 3904.07 | 0.102691 | 768.197ms | 31235 | 80 | 4911.39 | 7630 | 0.326584 | 0.631914 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11939.1 | 0.28522 | 255.251ms | 31235 | 40 | 2025.64 | 2495 | 0.0667557 | 0.205848 | 1(Win) | true |
| Glaze | 4260 | 0.118854 | 715.347ms | 31235 | 40 | 2762.82 | 6992.5 | 0.0119161 | 0.5791 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1484.74 | 0.119996 | 7095.67ms | 108313 | 1280 | 8.92083e+06 | 69571.2 | 0.190873 | 1.6669 | 1(Win) | true |
| Jsonifier (two-stage) | 1083.1 | 0.130039 | 9682.66ms | 108313 | 1280 | 1.9687e+07 | 95370.2 | 0.285241 | 2.28516 | 2(Loss) | true |
| Glaze | 968.713 | 0.0872515 | 5579.42ms | 108313 | 2560 | 2.21593e+07 | 106632 | 0.324648 | 2.55505 | 3(Loss) | true |
| simdjson (ondemand) | 824.357 | 0.530201 | 6516.56ms | 108313 | 320 | 1.41241e+08 | 125304 | 1.44589 | 3.00254 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1721.86 | 0.0679353 | 6351.19ms | 108313 | 4890 | 8.12199e+06 | 59990.4 | 0.492725 | 1.43721 | 1(Win) | true |
| Jsonifier (two-stage) | 1237.37 | 0.373466 | 8844.5ms | 108313 | 160 | 1.55521e+07 | 83480 | 0.228573 | 2.00012 | 2(Loss) | true |
| Glaze | 1098.16 | 0.575459 | 5143.85ms | 108313 | 40 | 1.17198e+07 | 94062.5 | 0.411878 | 2.25391 | 3(Loss) | true |
| simdjson (ondemand) | 941.76 | 0.863626 | 5910.39ms | 108313 | 30 | 2.69187e+07 | 109683 | 0.112571 | 2.62793 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14629.1 | 0.212244 | 721.21ms | 108313 | 2560 | 574957 | 7060.94 | 0.28294 | 0.168506 | 1(Win) | true |
| Glaze | 2947.71 | 0.13545 | 3533.91ms | 108313 | 2560 | 5.76751e+06 | 35042.5 | 0.203467 | 0.839173 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15432.6 | 0.0996016 | 672.858ms | 108313 | 30 | 1333.33 | 6693.33 | 0 | 0.159813 | 1(Win) | true |
| Glaze | 3129.98 | 0.270345 | 3363.02ms | 108313 | 320 | 2.54721e+06 | 33001.9 | 0.591148 | 0.790269 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2023.06 | 0.0931555 | 8870.45ms | 183677 | 2560 | 1.66552e+07 | 86585.7 | 0.513011 | 1.22339 | 1(Win) | true |
| Jsonifier (two-stage) | 1784.33 | 0.660862 | 5016.6ms | 183677 | 40 | 1.6836e+07 | 98170 | 0.511928 | 1.38679 | 2(Loss) | true |
| Glaze | 1409.21 | 0.104551 | 6474.13ms | 183677 | 1280 | 2.16184e+07 | 124303 | 0.0710963 | 1.75652 | 3(Loss) | true |
| simdjson (ondemand) | 1382.72 | 0.142406 | 6532.53ms | 183677 | 640 | 2.08295e+07 | 126684 | 0.145875 | 1.79008 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2275.92 | 0.0848054 | 8096.52ms | 183677 | 2560 | 1.09064e+07 | 76965.7 | 0.786364 | 1.08741 | 1(Win) | true |
| Jsonifier (two-stage) | 2068.83 | 0.211337 | 9136.2ms | 183677 | 320 | 1.02461e+07 | 84670 | 0.056806 | 1.1963 | 2(Loss) | true |
| Glaze | 1575.69 | 0.118779 | 5926.59ms | 183677 | 1280 | 2.23181e+07 | 111169 | 0.315245 | 1.57088 | 3(Loss) | true |
| simdjson (ondemand) | 1544.07 | 0.148678 | 6013.84ms | 183677 | 640 | 1.82075e+07 | 113446 | 0.15965 | 1.60303 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13627.6 | 0.0711225 | 1600.76ms | 213963 | 30 | 3402.3 | 14973.3 | 0.244282 | 0.181286 | 1(Win) | true |
| Glaze | 3578.59 | 0.35748 | 5917.28ms | 213963 | 80 | 3.3239e+06 | 57020 | 0.271098 | 0.691467 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13759.3 | 0.0494807 | 1572.83ms | 213963 | 40 | 2153.85 | 14830 | 0.0674764 | 0.179643 | 1(Win) | true |
| Glaze | 3694.23 | 0.5928 | 5566.45ms | 213963 | 80 | 8.57699e+06 | 55235 | 0.445536 | 0.669742 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 602.385 | 0.363398 | 9176.1ms | 1834197 | 80 | 8.90837e+09 | 2.90384e+06 | 0.320515 | 4.10997 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 583.255 | 1.66389 | 8923.23ms | 1834197 | 160 | 3.98423e+11 | 2.99908e+06 | 2.8046 | 4.24475 | -(Tie) | false |
| Glaze | 195.296 | 0.543883 | 6415.22ms | 1834197 | 30 | 7.11933e+10 | 8.95682e+06 | 0.874262 | 12.6772 | 3(Loss) | true |
| simdjson (ondemand) | 122.876 | 2.095 | 9690.05ms | 1834197 | 30 | 2.66839e+12 | 1.42357e+07 | 1.74541 | 20.1489 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 711.635 | 0.317356 | 8770.88ms | 1834197 | 40 | 2.43406e+09 | 2.45804e+06 | 0.155242 | 3.47893 | 1(Win) | true |
| Jsonifier (two-stage) | 671.473 | 0.384091 | 9275.86ms | 1834197 | 80 | 8.00926e+09 | 2.60506e+06 | 0.787079 | 3.68704 | 2(Loss) | true |
| Glaze | 200.776 | 0.437475 | 6344.04ms | 1834197 | 40 | 5.81076e+10 | 8.71231e+06 | 0.260203 | 12.3311 | 3(Loss) | true |
| simdjson (ondemand) | 132.606 | 0.459437 | 9573.77ms | 1834197 | 40 | 1.46918e+11 | 1.31911e+07 | 0.793982 | 18.6703 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 978.937 | 0.095453 | 5946.1ms | 1922245 | 160 | 5.1122e+08 | 1.87264e+06 | 0.00864496 | 2.52894 | 1(Win) | true |
| Glaze | 483.602 | 0.0910858 | 5438.8ms | 1833577 | 30 | 3.2542e+08 | 3.61585e+06 | 0.544918 | 5.11937 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1176.61 | 0.0905331 | 10047.5ms | 1922245 | 80 | 1.59169e+08 | 1.55803e+06 | 0.793946 | 2.10413 | 1(Win) | true |
| Glaze | 573.336 | 0.0917473 | 9540.95ms | 1833577 | 80 | 6.26406e+08 | 3.04993e+06 | 0.0636085 | 4.31822 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2197.36 | 0.115854 | 10084.4ms | 7351818 | 40 | 5.46596e+08 | 3.19075e+06 | 0.180925 | 1.12671 | 1(Win) | true |
| Jsonifier | 2120.84 | 0.168124 | 10164.9ms | 7351818 | 160 | 4.94257e+09 | 3.30588e+06 | 2.40343 | 1.16736 | 2(Loss) | true |
| Glaze | 697.513 | 0.574739 | 7246.61ms | 7351818 | 30 | 1.00126e+11 | 1.00518e+07 | 0.00736135 | 3.54948 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 494.023 | 1.68835 | 9996.24ms | 7351818 | 30 | 1.72244e+12 | 1.41921e+07 | 2.77119 | 5.01149 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2447.54 | 0.33433 | 9966.04ms | 7351818 | 80 | 7.33787e+09 | 2.86461e+06 | 0.761354 | 1.01153 | 1(Win) | true |
| Jsonifier DID NOT CONVERGE | 2347.98 | 0.181787 | 10127.6ms | 7351818 | 160 | 4.71463e+09 | 2.98608e+06 | 10.1532 | 1.05443 | -(Loss) | false |
| Glaze DID NOT CONVERGE | 732.054 | 0.359044 | 7025.5ms | 7351818 | 40 | 4.72997e+10 | 9.57749e+06 | 2.77867 | 3.38202 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 507.962 | 1.57963 | 10037.2ms | 7351818 | 40 | 1.9015e+12 | 1.38027e+07 | 5.19192 | 4.87397 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2854.06 | 0.106648 | 5113.4ms | 10018896 | 80 | 1.01978e+09 | 3.34778e+06 | 0.451277 | 0.867447 | 1(Win) | true |
| Glaze | 1463.15 | 0.575313 | 9780.69ms | 9930228 | 30 | 4.1598e+10 | 6.47249e+06 | 1.27279 | 1.69209 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4952.46 | 0.204027 | 6064.34ms | 10018896 | 80 | 1.23955e+09 | 1.9293e+06 | 0.672252 | 0.499901 | 1(Win) | true |
| Glaze | 2729.1 | 0.180969 | 5338.1ms | 9930228 | 80 | 3.15484e+09 | 3.47008e+06 | 0.162735 | 0.907177 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 678.874 | 0.136713 | 8230.8ms | 1834197 | 30 | 3.72265e+08 | 2.57666e+06 | 3.02018 | 3.6469 | -(Win) | false |
| Jsonifier (two-stage) | 569.898 | 0.500257 | 9089.6ms | 1834197 | 30 | 7.07303e+09 | 3.06937e+06 | 0.914112 | 4.34396 | 2(Loss) | true |
| simdjson (ondemand) | 236.194 | 0.49725 | 5364.9ms | 1834197 | 40 | 5.42455e+10 | 7.40589e+06 | 1.4037 | 10.4821 | 3(Loss) | true |
| Glaze | 198.939 | 0.357518 | 6239.64ms | 1834197 | 40 | 3.95283e+10 | 8.79278e+06 | 1.0441 | 12.445 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 770.643 | 1.17473 | 8110.2ms | 1834197 | 160 | 1.13758e+11 | 2.26983e+06 | 0.739907 | 3.21257 | 1(Win) | true |
| Jsonifier (two-stage) | 667.624 | 0.220323 | 9209.04ms | 1834197 | 30 | 9.99696e+08 | 2.62008e+06 | 0.0986949 | 3.70826 | 2(Loss) | true |
| simdjson (ondemand) | 240.443 | 0.101365 | 5394.69ms | 1834197 | 30 | 1.63141e+09 | 7.27501e+06 | 2.1772 | 10.2969 | 3(Loss) | true |
| Glaze | 207.812 | 0.378854 | 6275.5ms | 1834197 | 40 | 4.06776e+10 | 8.41736e+06 | 1.37222 | 11.9137 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 969.311 | 0.959631 | 5876.49ms | 1922245 | 160 | 5.27011e+10 | 1.89124e+06 | 0.117091 | 2.55404 | 1(Win) | true |
| Glaze | 482.854 | 0.943468 | 5489.53ms | 1833577 | 30 | 3.50222e+10 | 3.62146e+06 | 2.28322 | 5.1273 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1175.64 | 0.233846 | 9908.17ms | 1922245 | 160 | 2.12741e+09 | 1.55932e+06 | 1.16706 | 2.10588 | 1(Win) | true |
| Glaze | 575.105 | 0.0807742 | 9621.18ms | 1833577 | 40 | 2.41273e+08 | 3.04055e+06 | 0.0276617 | 4.30493 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2149.48 | 0.365785 | 10172.3ms | 7351818 | 80 | 1.13885e+10 | 3.26183e+06 | 0.329155 | 1.1518 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2148.43 | 1.06367 | 10140.6ms | 7351818 | 40 | 4.81973e+10 | 3.26343e+06 | 0.475472 | 1.15235 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 839.308 | 1.64355 | 5913.47ms | 7351818 | 40 | 7.54008e+11 | 8.3536e+06 | 2.73086 | 2.94982 | -(Loss) | false |
| Glaze | 708.62 | 0.395996 | 7015.38ms | 7351818 | 30 | 4.60538e+10 | 9.89421e+06 | 1.81783 | 3.49383 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2418.24 | 0.294747 | 10249.8ms | 7351818 | 80 | 5.84223e+09 | 2.89932e+06 | 0.0445562 | 1.02379 | 1(Win) | true |
| Jsonifier | 2368.06 | 0.348823 | 5020.38ms | 7351818 | 30 | 3.19989e+09 | 2.96075e+06 | 0.710006 | 1.04548 | 2(Loss) | true |
| simdjson (ondemand) | 886.694 | 0.272921 | 5872.12ms | 7351818 | 30 | 1.39713e+10 | 7.90717e+06 | 1.09489 | 2.79215 | 3(Loss) | true |
| Glaze | 701.841 | 1.50326 | 7014.99ms | 7351818 | 30 | 6.76557e+11 | 9.98979e+06 | 1.56705 | 3.52756 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2823.06 | 0.0964151 | 5136.06ms | 10018896 | 80 | 8.51885e+08 | 3.38455e+06 | 0.0483681 | 0.876967 | 1(Win) | true |
| Glaze | 1019.7 | 1.31486 | 6359.47ms | 9930228 | 30 | 4.47353e+11 | 9.28723e+06 | 0.890396 | 2.42775 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4761.91 | 0.770803 | 6353.88ms | 10018896 | 30 | 7.17603e+09 | 2.0065e+06 | 0.291036 | 0.51991 | 1(Win) | true |
| Glaze | 2695.4 | 0.187084 | 5393.4ms | 9930228 | 30 | 1.29619e+09 | 3.51347e+06 | 0.487833 | 0.918524 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 787.683 | 0.323722 | 7216.59ms | 461466 | 80 | 2.61705e+08 | 558712 | 2.10306 | 3.1429 | 1(Win) | true |
| Jsonifier (two-stage) | 686.544 | 0.231935 | 8355.47ms | 461466 | 160 | 3.53667e+08 | 641020 | 0.978245 | 3.60595 | 2(Loss) | true |
| Glaze | 601.651 | 0.200716 | 9425.14ms | 461466 | 80 | 1.72443e+08 | 731468 | 0.421678 | 4.11475 | 3(Loss) | true |
| simdjson (ondemand) | 495.314 | 0.257387 | 5767.17ms | 461466 | 30 | 1.56896e+08 | 888503 | 0.0431251 | 4.99829 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1082.64 | 0.289573 | 6471.58ms | 461466 | 30 | 4.15672e+07 | 406497 | 1.09009 | 2.28657 | 1(Win) | true |
| Jsonifier (two-stage) | 888.927 | 0.0969531 | 7592.41ms | 461466 | 640 | 1.47452e+08 | 495078 | 0.264863 | 2.78498 | 2(Loss) | true |
| Glaze | 769.224 | 0.302577 | 8657.94ms | 461466 | 40 | 1.19869e+08 | 572120 | 0.881828 | 3.21834 | 3(Loss) | true |
| simdjson (ondemand) | 600.728 | 0.183559 | 5320.85ms | 461466 | 80 | 1.44666e+08 | 732591 | 0.290076 | 4.12113 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3144.02 | 0.638337 | 7183.31ms | 461466 | 640 | 5.10961e+08 | 139976 | 0.602709 | 0.786881 | 1(Win) | true |
| Glaze | 2568.36 | 0.492791 | 8977.41ms | 461466 | 30 | 2.13902e+07 | 171350 | 0.496569 | 0.963759 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10222.8 | 0.100288 | 4323.66ms | 461466 | 4890 | 9.11485e+06 | 43049.9 | 0.053295 | 0.241985 | 1(Win) | true |
| Glaze | 2717.6 | 0.401991 | 8453.59ms | 461466 | 40 | 1.69512e+07 | 161940 | 0.171138 | 0.910821 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1181.96 | 0.297387 | 7593.86ms | 728486 | 320 | 9.77756e+08 | 587786 | 0.0570261 | 2.0945 | 1(Win) | true |
| Jsonifier (two-stage) | 1022.17 | 0.0919104 | 8824.39ms | 728486 | 640 | 2.49752e+08 | 679672 | 0.304425 | 2.42196 | 2(Loss) | true |
| Glaze | 886.714 | 0.374881 | 5037.57ms | 728486 | 40 | 3.45082e+08 | 783498 | 1.41662 | 2.79195 | 3(Loss) | true |
| simdjson (ondemand) | 736.576 | 0.220005 | 5948.83ms | 728486 | 30 | 1.29179e+08 | 943200 | 0.12354 | 3.36115 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1526.37 | 0.212673 | 7060.2ms | 728486 | 80 | 7.49617e+07 | 455159 | 0.125348 | 1.62192 | 1(Win) | true |
| Jsonifier (two-stage) | 1288.91 | 0.180229 | 8198.24ms | 728486 | 80 | 7.54989e+07 | 539014 | 1.24291 | 1.92067 | 2(Loss) | true |
| Glaze | 1045.15 | 0.14309 | 9442.5ms | 728486 | 160 | 1.44752e+08 | 664724 | 0.697315 | 2.36871 | 3(Loss) | true |
| simdjson (ondemand) | 888.908 | 0.111207 | 5514.77ms | 728486 | 160 | 1.20868e+08 | 781564 | 0.0404801 | 2.78512 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3421.28 | 0.201084 | 6203.62ms | 837491 | 320 | 7.05161e+07 | 233449 | 1.12573 | 0.723297 | 1(Win) | true |
| Glaze | 1993.68 | 0.143038 | 5085.15ms | 837491 | 640 | 2.1015e+08 | 400612 | 0.26169 | 1.24145 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11965.6 | 0.223745 | 6744.1ms | 837491 | 640 | 1.42752e+07 | 66749.4 | 0.0191913 | 0.206801 | 1(Win) | true |
| Glaze | 3363.27 | 0.295769 | 6096.18ms | 837491 | 160 | 7.89333e+07 | 237475 | 0.820446 | 0.736027 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7732.49 | 0.168839 | 5920ms | 466906 | 1280 | 1.20997e+07 | 57585.1 | 0.359177 | 0.319955 | 1(Win) | true |
| Jsonifier (two-stage) | 7599.3 | 0.332306 | 5844.51ms | 466906 | 320 | 1.21322e+07 | 58594.4 | 0.0149309 | 0.325622 | 2(Loss) | true |
| simdjson (ondemand) | 3306.92 | 0.354997 | 7033.48ms | 466906 | 80 | 1.8279e+07 | 134650 | 0.279573 | 0.748429 | 3(Loss) | true |
| Glaze | 2833.18 | 0.258466 | 8246.25ms | 466906 | 80 | 1.3201e+07 | 157165 | 0.138198 | 0.873678 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 8060.39 | 0.653882 | 5765.93ms | 466906 | 80 | 1.04384e+07 | 55242.5 | 0.252787 | 0.306915 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 7989.96 | 0.140355 | 5761.51ms | 466906 | 1280 | 7.83131e+06 | 55729.5 | 0.0343338 | 0.309678 | 1(Tie) | true |
| simdjson (ondemand) | 3480.26 | 0.56289 | 6677.47ms | 466906 | 30 | 1.55598e+07 | 127943 | 0.616245 | 0.711205 | 3(Loss) | true |
| Glaze | 2912.35 | 0.1453 | 7919.82ms | 466906 | 320 | 1.57927e+07 | 152892 | 0.397388 | 0.849968 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9156.35 | 0.12921 | 6611.7ms | 631514 | 1280 | 9.24533e+06 | 65775 | 0.384406 | 0.270261 | 1(Win) | true |
| Jsonifier | 8703.15 | 0.097043 | 6919.89ms | 631514 | 2560 | 1.15447e+07 | 69200.1 | 0.013493 | 0.284321 | 2(Loss) | true |
| simdjson (ondemand) | 4115.51 | 0.119453 | 7424.79ms | 631514 | 1280 | 3.91129e+07 | 146339 | 0.79652 | 0.601446 | 3(Loss) | true |
| Glaze | 3532.41 | 0.416414 | 9292.02ms | 631514 | 40 | 2.0162e+07 | 170495 | 0.227251 | 0.700674 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9290.41 | 0.101717 | 6714.47ms | 631514 | 2560 | 1.11308e+07 | 64825.9 | 0.0521559 | 0.266373 | 1(Win) | true |
| Jsonifier | 9180.03 | 0.260985 | 6733.66ms | 631514 | 320 | 9.38119e+06 | 65605.3 | 0.153619 | 0.269552 | 2(Loss) | true |
| simdjson (ondemand) | 4315.99 | 0.416755 | 7091.41ms | 631514 | 80 | 2.70556e+07 | 139541 | 0.0707176 | 0.573504 | 3(Loss) | true |
| Glaze | 3431.07 | 0.157594 | 8973.61ms | 631514 | 1280 | 9.79483e+07 | 175531 | 0.298776 | 0.721474 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1374.66 | 0.767562 | 8238.83ms | 466906 | 320 | 1.97809e+09 | 323918 | 0.0496128 | 1.80079 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1107.73 | 0.859401 | 5189.39ms | 466906 | 160 | 1.90944e+09 | 401973 | 2.82964 | 2.23478 | -(Loss) | false |
| Glaze | 1064.5 | 0.42577 | 5222.76ms | 466906 | 640 | 2.03002e+09 | 418297 | 1.56188 | 2.32555 | 3(Loss) | true |
| simdjson (ondemand) | 902.691 | 0.304261 | 6346.93ms | 466906 | 30 | 6.75763e+07 | 493277 | 0.753011 | 2.74246 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1955.87 | 0.220959 | 6912.15ms | 466906 | 160 | 4.04878e+07 | 227662 | 0.478946 | 1.26565 | 1(Win) | true |
| Jsonifier (two-stage) | 1446.17 | 0.156388 | 9072.25ms | 466906 | 320 | 7.41958e+07 | 307901 | 0.195601 | 1.71176 | 2(Loss) | true |
| Glaze | 1414.76 | 0.479454 | 9123.49ms | 466906 | 30 | 6.83141e+07 | 314737 | 0.126929 | 1.74977 | 3(Loss) | true |
| simdjson (ondemand) | 1195.58 | 0.188466 | 5199.69ms | 466906 | 160 | 7.88293e+07 | 372435 | 0.490059 | 2.07059 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4791.96 | 0.21027 | 9493.73ms | 475954 | 320 | 1.26943e+07 | 94722.2 | 0.487531 | 0.516461 | 1(Win) | true |
| Jsonifier | 3570.91 | 0.359379 | 6545.82ms | 475954 | 160 | 3.33886e+07 | 127112 | 0.168936 | 0.692863 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13601.7 | 0.15482 | 3371.73ms | 475954 | 2560 | 6.83348e+06 | 33371.3 | 0.380262 | 0.181843 | 1(Win) | true |
| Glaze | 5366.94 | 0.145785 | 8566.86ms | 475954 | 1280 | 1.94585e+07 | 84574.3 | 0.186482 | 0.461133 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1580.03 | 0.443372 | 5057.21ms | 631514 | 40 | 1.14244e+08 | 381170 | 0.98021 | 1.5668 | 1(Win) | true |
| Jsonifier (two-stage) | 1395.21 | 0.668802 | 5545.3ms | 631514 | 320 | 2.66707e+09 | 431662 | 0.0509398 | 1.77433 | 2(Loss) | true |
| Glaze | 1261.41 | 0.567024 | 5957.18ms | 631514 | 320 | 2.34535e+09 | 477449 | 0.952543 | 1.96255 | 3(Loss) | true |
| simdjson (ondemand) | 1204.31 | 0.444975 | 6494.89ms | 631514 | 30 | 1.48554e+08 | 500087 | 0.148194 | 2.05563 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2034.4 | 0.267685 | 8671.56ms | 631514 | 160 | 1.00476e+08 | 296038 | 0.308128 | 1.21679 | 1(Win) | true |
| Jsonifier (two-stage) | 1747.61 | 0.256367 | 9972.67ms | 631514 | 160 | 1.24888e+08 | 344618 | 0.35436 | 1.41652 | 2(Loss) | true |
| Glaze | 1682.47 | 0.189591 | 5160ms | 631514 | 320 | 1.47385e+08 | 357960 | 0.161854 | 1.47139 | 3(Loss) | true |
| simdjson (ondemand) | 1540.96 | 0.232976 | 5455.56ms | 631514 | 160 | 1.32655e+08 | 390833 | 0.75648 | 1.60652 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3477.96 | 0.251826 | 5069.57ms | 716365 | 640 | 1.56603e+08 | 196431 | 0.0288663 | 0.711507 | 1(Win) | true |
| Glaze | 2408.39 | 0.170178 | 7254.25ms | 716365 | 640 | 1.49142e+08 | 283667 | 0.120555 | 1.02751 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10564.2 | 0.180795 | 6623.84ms | 716365 | 640 | 8.74883e+06 | 64669.4 | 0.419127 | 0.23424 | 1(Win) | true |
| Glaze | 4924.92 | 0.130771 | 7268.11ms | 716365 | 1280 | 4.21212e+07 | 138719 | 0.128243 | 0.502572 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1131.3 | 0.528932 | 238.952ms | 2632 | 160 | 22036.2 | 2218.75 | 0.225861 | 2.16208 | 1(Win) | true |
| Jsonifier (two-stage) | 1038.29 | 0.251679 | 246.656ms | 2632 | 40 | 1480.77 | 2417.5 | 0.172652 | 2.3523 | 2(Loss) | true |
| Glaze | 872.689 | 0.632881 | 313.506ms | 2632 | 160 | 53017.3 | 2876.25 | 0.0434405 | 2.80831 | 3(Loss) | true |
| simdjson (ondemand) | 653.664 | 0.204288 | 403.775ms | 2632 | 40 | 2461.54 | 3840 | 0.0867303 | 3.76022 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491.04 | 0.134357 | 202.792ms | 2632 | 320 | 1637.05 | 1683.44 | 0.167348 | 1.63165 | 1(Win) | true |
| Glaze | 1445.95 | 0.154756 | 217.79ms | 2632 | 320 | 2309.46 | 1735.94 | 0.305097 | 1.6848 | 2(Loss) | true |
| Jsonifier (two-stage) | 1336.45 | 0.383963 | 218.228ms | 2632 | 4890 | 254303 | 1878.16 | 0.0584435 | 1.8242 | 3(Loss) | true |
| simdjson (ondemand) | 866.288 | 0.1949 | 340.264ms | 2632 | 40 | 1275.64 | 2897.5 | 0.0862069 | 2.82448 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8410.71 | 0.479708 | 34.1648ms | 2632 | 320 | 655.858 | 298.438 | 0.104822 | 0.2679 | 1(Win) | true |
| Glaze | 3325.72 | 0.382124 | 79.4443ms | 2632 | 4890 | 40673.9 | 754.744 | 0.368916 | 0.716369 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8927.18 | 0.388776 | 31.6869ms | 2632 | 1280 | 1529.51 | 281.172 | 0.0832871 | 0.249396 | 1(Win) | true |
| Glaze | 3857.94 | 0.430239 | 69.4623ms | 2632 | 320 | 2507.45 | 650.625 | 0 | 0.612949 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1317.04 | 0.314235 | 248.576ms | 3370 | 2560 | 150526 | 2440.23 | 0.188535 | 1.85722 | 1(Win) | true |
| Jsonifier (two-stage) | 1257.66 | 0.245687 | 259.283ms | 3370 | 4890 | 192755 | 2555.44 | 0.141221 | 1.94532 | 2(Loss) | true |
| Glaze | 1076.68 | 0.14719 | 309.307ms | 3370 | 80 | 1544.3 | 2985 | 0.251889 | 2.28281 | 3(Loss) | true |
| simdjson (ondemand) | 828.187 | 0.265962 | 402.921ms | 3370 | 160 | 17043.6 | 3880.62 | 0.436752 | 2.96787 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1745.49 | 0.212034 | 217.462ms | 3370 | 160 | 2438.68 | 1841.25 | 0.135593 | 1.39637 | 1(Win) | true |
| Glaze | 1722.11 | 0.285067 | 219.635ms | 3370 | 80 | 2264.24 | 1866.25 | 0.333778 | 1.4163 | 2(Loss) | true |
| Jsonifier (two-stage) | 1624.15 | 0.260381 | 229.108ms | 3370 | 4890 | 129819 | 1978.81 | 0.111141 | 1.50132 | 3(Loss) | true |
| simdjson (ondemand) | 1080.89 | 0.499421 | 344.221ms | 3370 | 1280 | 282253 | 2973.36 | 0.118377 | 2.26849 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9270.42 | 0.229588 | 41.3271ms | 3643 | 2560 | 1895.22 | 374.766 | 0 | 0.246906 | 1(Win) | true |
| Glaze | 3326.4 | 0.373247 | 109.928ms | 3682 | 160 | 2483.88 | 1055.62 | 0.535714 | 0.723168 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9872.4 | 0.323503 | 38.7303ms | 3643 | 2560 | 3317.94 | 351.914 | 0.1 | 0.230761 | 1(Win) | true |
| Glaze | 3736.8 | 0.211276 | 98.5712ms | 3682 | 640 | 2522.59 | 939.688 | 0.529276 | 0.643278 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 555.672 | 0.107233 | 809.243ms | 4630 | 80 | 5808.54 | 7946.25 | 0.0785916 | 4.43817 | 1(Win) | true |
| Jsonifier (two-stage) | 516.864 | 0.417172 | 877.221ms | 4630 | 1280 | 1.62574e+06 | 8542.89 | 0.212626 | 4.77329 | 2(Loss) | true |
| simdjson (ondemand) | 172.443 | 0.177854 | 2633.26ms | 4630 | 1280 | 2.65467e+06 | 25605.7 | 0.5729 | 14.3401 | 3(Loss) | true |
| Glaze | 162.215 | 0.128506 | 2758.54ms | 4630 | 2560 | 3.13235e+06 | 27220.2 | 0.0837338 | 15.2454 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 659.289 | 0.234325 | 838.299ms | 4630 | 2560 | 630501 | 6697.38 | 0.146182 | 3.73971 | 1(Win) | true |
| Jsonifier (two-stage) | 642.958 | 0.150998 | 866.736ms | 4630 | 40 | 4301.28 | 6867.5 | 0.0607091 | 3.8371 | 2(Loss) | true |
| simdjson (ondemand) | 180.879 | 0.103952 | 2609.11ms | 4630 | 4890 | 3.14891e+06 | 24411.3 | 0.683686 | 13.6713 | 3(Loss) | true |
| Glaze | 171.745 | 0.203428 | 2796.19ms | 4630 | 1280 | 3.50127e+06 | 25709.7 | 0.194858 | 14.4003 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1676.51 | 0.201996 | 261.054ms | 4630 | 80 | 2264.24 | 2633.75 | 0.333333 | 1.45764 | 1(Win) | true |
| Glaze | 885.732 | 0.275221 | 510.935ms | 4630 | 1280 | 240952 | 4985.16 | 0.328022 | 2.7774 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1770.93 | 0.185778 | 257.906ms | 4630 | 30 | 643.678 | 2493.33 | 0 | 1.38084 | 1(Win) | true |
| Glaze | 936.979 | 0.0789576 | 488.967ms | 4630 | 80 | 1107.59 | 4712.5 | 0.105988 | 2.62232 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1236.57 | 0.331628 | 940.865ms | 11579 | 30 | 26310.3 | 8930 | 0.0373134 | 1.99493 | 1(Win) | true |
| Jsonifier | 1167.43 | 0.297002 | 966.666ms | 11579 | 2560 | 2.0204e+06 | 9458.87 | 0.021066 | 2.11377 | 2(Loss) | true |
| simdjson (ondemand) | 425.21 | 0.1729 | 2651.4ms | 11579 | 1280 | 2.5807e+06 | 25969.8 | 0.000902484 | 5.8163 | 3(Loss) | true |
| Glaze | 386.714 | 0.0832309 | 2878.87ms | 11579 | 4890 | 2.7621e+06 | 28554.9 | 0.152411 | 6.39536 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1494.01 | 0.0906749 | 914.34ms | 11579 | 80 | 3593.35 | 7391.25 | 0.118524 | 1.65028 | 1(Win) | true |
| Jsonifier | 1394.89 | 0.374583 | 956.305ms | 11579 | 1280 | 1.12557e+06 | 7916.48 | 0.341632 | 1.76879 | 2(Loss) | true |
| simdjson (ondemand) | 449.981 | 0.250148 | 2658.81ms | 11579 | 640 | 2.41173e+06 | 24540.2 | 0.0260984 | 5.49616 | 3(Loss) | true |
| Glaze | 413.735 | 0.0605208 | 2923.6ms | 11579 | 30 | 7827.59 | 26690 | 0.300639 | 5.977 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4384.1 | 0.346422 | 323.255ms | 14795 | 1280 | 159108 | 3218.36 | 0.37003 | 0.559715 | 1(Win) | true |
| Glaze | 2377.39 | 0.175885 | 602.286ms | 14795 | 4890 | 532840 | 5934.93 | 0.172852 | 1.03653 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4718.93 | 0.186316 | 310.604ms | 14795 | 30 | 931.034 | 2990 | 0 | 0.520635 | 1(Win) | true |
| Glaze | 2586.14 | 0.229752 | 555.47ms | 14795 | 2560 | 402240 | 5455.86 | 0.0358115 | 0.952144 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.333 | 0.355255 | 431.581ms | 3223 | 40 | 8820.51 | 4180 | 0 | 3.32683 | 1(Win) | true |
| Jsonifier (two-stage) | 638.579 | 0.258479 | 492.796ms | 3223 | 30 | 4643.68 | 4813.33 | 0 | 3.82645 | 2(Loss) | true |
| Glaze | 469.027 | 0.228257 | 672.911ms | 3223 | 30 | 6712.64 | 6553.33 | 0.0508388 | 5.23037 | 3(Loss) | true |
| simdjson (ondemand) | 446.616 | 0.220806 | 737.051ms | 3223 | 2560 | 591171 | 6882.19 | 0.114784 | 5.52003 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1046.36 | 0.130701 | 366.198ms | 3223 | 160 | 2358.49 | 2937.5 | 0.42735 | 2.34341 | 1(Win) | true |
| Jsonifier (two-stage) | 863.035 | 0.256832 | 428.213ms | 3223 | 4890 | 409139 | 3561.49 | 0.195851 | 2.84464 | 2(Loss) | true |
| Glaze | 575.239 | 0.172212 | 603.264ms | 3223 | 30 | 2540.23 | 5343.33 | 0.124611 | 4.28573 | 3(Loss) | true |
| simdjson (ondemand) | 516.587 | 0.175625 | 694.353ms | 3223 | 30 | 3275.86 | 5950 | 0.501672 | 4.78561 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7962.61 | 0.286309 | 42.1594ms | 3223 | 1280 | 1563.47 | 386.016 | 0.101297 | 0.288254 | 1(Win) | true |
| Glaze | 2315.4 | 0.378431 | 132.286ms | 3223 | 80 | 2018.99 | 1327.5 | 0.375235 | 1.04972 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9430.31 | 0.531959 | 35.906ms | 3223 | 640 | 1924 | 325.938 | 0.666667 | 0.239794 | 1(Win) | true |
| Glaze | 2916.91 | 0.532346 | 110.997ms | 3223 | 80 | 2517.41 | 1053.75 | 0.118765 | 0.822328 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1140.5 | 0.195444 | 542.985ms | 5839 | 80 | 7284.81 | 4882.5 | 0.0512295 | 2.14719 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1139.34 | 0.168276 | 512.494ms | 5839 | 80 | 5411.39 | 4887.5 | 0.205023 | 2.14708 | 1(Tie) | true |
| simdjson (ondemand) | 787.068 | 0.344658 | 729.476ms | 5839 | 1280 | 761095 | 7075 | 0.0882613 | 3.13389 | 3(Loss) | true |
| Glaze | 762.213 | 0.274777 | 756.711ms | 5839 | 1280 | 515816 | 7305.7 | 0.00748615 | 3.22621 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1503.65 | 0.157682 | 449.949ms | 5839 | 30 | 1022.99 | 3703.33 | 0.2693 | 1.63002 | 1(Win) | true |
| Jsonifier | 1482.3 | 0.244948 | 448.251ms | 5839 | 30 | 2540.23 | 3756.67 | 0.0886525 | 1.6557 | 2(Loss) | true |
| Glaze | 928.277 | 0.112898 | 676.823ms | 5839 | 80 | 3669.3 | 5998.75 | 0.52367 | 2.65254 | 3(Loss) | true |
| simdjson (ondemand) | 889.099 | 0.164121 | 709.299ms | 5839 | 4890 | 516672 | 6263.09 | 0.500769 | 2.77205 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7720.36 | 0.336849 | 90.9975ms | 6938 | 640 | 5333.9 | 857.031 | 0.272727 | 0.311351 | 1(Win) | true |
| Glaze | 3670.89 | 0.396639 | 185.093ms | 6960 | 2560 | 131676 | 1808.16 | 0.0712404 | 0.664236 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8402.02 | 0.672475 | 83.8901ms | 6938 | 40 | 1121.79 | 787.5 | 0.105932 | 0.285356 | 1(Win) | true |
| Glaze | 4290.85 | 0.274427 | 158.727ms | 6960 | 4890 | 88124 | 1546.91 | 0.408085 | 0.566368 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1153.19 | 0.317694 | 415.772ms | 4857 | 30 | 4885.06 | 4016.67 | 0.333056 | 2.12375 | 1(Win) | true |
| Jsonifier (two-stage) | 913.609 | 0.342934 | 527.902ms | 4857 | 30 | 9068.97 | 5070 | 0.13132 | 2.69957 | 2(Loss) | true |
| Glaze | 815.683 | 0.280774 | 579.332ms | 4857 | 1280 | 325401 | 5678.67 | 0.501908 | 3.01851 | 3(Loss) | true |
| simdjson (ondemand) | 607.102 | 0.361388 | 770.394ms | 4857 | 640 | 486566 | 7629.69 | 0.0286791 | 4.06171 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1684.36 | 0.379988 | 342.828ms | 4857 | 30 | 3275.86 | 2750 | 0.243013 | 1.45942 | 1(Win) | true |
| Glaze | 1264.63 | 0.473826 | 434.964ms | 4857 | 1280 | 385530 | 3662.73 | 1.61472 | 1.94378 | 2(Loss) | true |
| Jsonifier (two-stage) | 1214.89 | 0.315442 | 435.258ms | 4857 | 2560 | 370292 | 3812.7 | 0.18714 | 2.02191 | 3(Loss) | true |
| simdjson (ondemand) | 885.659 | 0.17047 | 592.957ms | 4857 | 40 | 3179.49 | 5230 | 0.127307 | 2.77931 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8934.53 | 0.418798 | 56.6864ms | 4857 | 320 | 1508.52 | 518.438 | 0.180505 | 0.262441 | 1(Win) | true |
| Glaze | 2881.26 | 0.349697 | 166.012ms | 4857 | 4890 | 154548 | 1607.63 | 0.339555 | 0.843482 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10124.6 | 0.856917 | 50.159ms | 4857 | 160 | 2459.12 | 457.5 | 0.813008 | 0.229427 | 1(Win) | true |
| Glaze | 3474.54 | 0.28778 | 150.343ms | 4857 | 160 | 2354.95 | 1333.12 | 0.0469043 | 0.697141 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1385.49 | 0.222122 | 489.703ms | 6701 | 40 | 4198.72 | 4612.5 | 0.234319 | 1.77899 | 1(Win) | true |
| Jsonifier (two-stage) | 1196.04 | 0.337609 | 546.086ms | 6701 | 1280 | 416513 | 5343.12 | 0.05261 | 2.05816 | 2(Loss) | true |
| Glaze | 1028.97 | 0.43058 | 648.687ms | 6701 | 1280 | 915352 | 6210.62 | 0.0301993 | 2.39373 | 3(Loss) | true |
| simdjson (ondemand) | 878.052 | 0.09721 | 754.925ms | 6701 | 160 | 8009.04 | 7278.12 | 0.0772267 | 2.80891 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1886.52 | 0.188712 | 389.799ms | 6701 | 40 | 1634.62 | 3387.5 | 0.0737463 | 1.30173 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1607.56 | 0.742447 | 445.104ms | 6701 | 640 | 557512 | 3975.31 | 0.260088 | 1.52917 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1601.65 | 0.0948024 | 454.507ms | 6701 | 160 | 2289.31 | 3990 | 0.25 | 1.53445 | 2(Tie) | true |
| simdjson (ondemand) | 1196.75 | 0.439139 | 571.589ms | 6701 | 1280 | 703855 | 5339.92 | 0.607907 | 2.0579 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7087.46 | 0.557435 | 93.1761ms | 7376 | 40 | 1224.36 | 992.5 | 0.0838926 | 0.338208 | 1(Win) | true |
| Glaze | 2976.99 | 0.3191 | 253.169ms | 7376 | 2560 | 145539 | 2362.89 | 0.122185 | 0.820371 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8728.1 | 0.181623 | 85.0519ms | 7376 | 320 | 685.639 | 805.938 | 0.116189 | 0.274118 | 1(Win) | true |
| Glaze | 3344.36 | 0.158479 | 227.507ms | 7376 | 30 | 333.333 | 2103.33 | 0 | 0.727431 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1165.96 | 0.241754 | 154.769ms | 1691 | 160 | 1788.92 | 1383.12 | 0.135379 | 2.07638 | 1(Win) | true |
| Glaze | 1054.34 | 0.45137 | 156.766ms | 1691 | 4890 | 233078 | 1529.55 | 0.116291 | 2.30326 | 2(Loss) | true |
| Jsonifier (two-stage) | 972.949 | 0.524161 | 172.607ms | 1691 | 40 | 3019.23 | 1657.5 | 0.150602 | 2.49694 | 3(Loss) | true |
| simdjson (ondemand) | 620.255 | 0.412351 | 266.465ms | 1691 | 30 | 3448.28 | 2600 | 0 | 3.9561 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1543.68 | 0.266454 | 129.742ms | 1691 | 320 | 2479.53 | 1044.69 | 0.0299043 | 1.55964 | 1(Win) | true |
| Glaze | 1353.9 | 0.413756 | 143.85ms | 1691 | 4890 | 118772 | 1191.12 | 0.632961 | 1.7871 | 2(Loss) | true |
| Jsonifier (two-stage) | 1274.99 | 0.14933 | 152.788ms | 1691 | 640 | 2283.23 | 1264.84 | 0.0370737 | 1.90215 | 3(Loss) | true |
| simdjson (ondemand) | 715.15 | 0.174961 | 260.647ms | 1691 | 160 | 2490.57 | 2255 | 0.221239 | 3.41775 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9874.06 | 0.354966 | 22.5861ms | 1996 | 4890 | 2289.87 | 192.781 | 1.54729 | 0.214258 | 1(Win) | true |
| Glaze | 3402.49 | 0.717485 | 64.7236ms | 1996 | 2560 | 41247.1 | 559.453 | 0.0698714 | 0.680393 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12273.6 | 0.458677 | 18.932ms | 1996 | 4890 | 2474.58 | 155.092 | 0.109829 | 0.165812 | 1(Win) | true |
| Glaze | 4301.77 | 0.885965 | 48.0604ms | 1996 | 160 | 2459.12 | 442.5 | 0 | 0.538868 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1246.13 | 0.305274 | 169.515ms | 2158 | 4890 | 124298 | 1651.53 | 0.327069 | 1.95365 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1237.91 | 0.466296 | 193.635ms | 2158 | 40 | 2403.85 | 1662.5 | 0.0501002 | 1.96023 | 1(Tie) | true |
| Jsonifier (two-stage) | 1217.77 | 0.190615 | 174.775ms | 2158 | 160 | 1660.38 | 1690 | 0.148148 | 1.99844 | 3(Loss) | true |
| simdjson (ondemand) | 781.036 | 0.143553 | 270.159ms | 2158 | 160 | 2289.31 | 2635 | 0.0947867 | 3.13927 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1633.36 | 0.622591 | 153.645ms | 2158 | 40 | 2461.54 | 1260 | 0 | 1.49695 | 1(Win) | true |
| Jsonifier | 1593.06 | 0.106748 | 166.014ms | 2158 | 640 | 1217.14 | 1291.88 | 0.433526 | 1.52331 | 2(Loss) | true |
| Jsonifier (two-stage) | 1562.44 | 0.119364 | 158.591ms | 2158 | 640 | 1582.06 | 1317.19 | 0.307474 | 1.55028 | 3(Loss) | true |
| simdjson (ondemand) | 896.135 | 0.0889749 | 254.749ms | 2158 | 320 | 1336.11 | 2296.56 | 0.177208 | 2.72877 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8317.96 | 0.543994 | 36.8515ms | 2866 | 640 | 2044.97 | 328.594 | 0.0475737 | 0.272546 | 1(Win) | true |
| Glaze | 3307.99 | 0.67206 | 89.1162ms | 2866 | 80 | 2466.77 | 826.25 | 0.451807 | 0.721554 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10987.9 | 0.824203 | 27.2858ms | 2866 | 640 | 2690.14 | 248.75 | 0.74813 | 0.199022 | 1(Win) | true |
| Glaze | 4043.85 | 0.587118 | 71.79ms | 2866 | 2560 | 40313.8 | 675.898 | 0.0636132 | 0.583136 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1096.69 | 0.227583 | 413.202ms | 4390 | 40 | 3019.23 | 3817.5 | 0.0218341 | 2.2396 | 1(Win) | true |
| Jsonifier (two-stage) | 956.398 | 0.152751 | 456.293ms | 4390 | 40 | 1788.46 | 4377.5 | 0.0570776 | 2.57126 | 2(Loss) | true |
| Glaze | 816.107 | 0.2121 | 532.077ms | 4390 | 30 | 3551.72 | 5130 | 0.0649351 | 3.01753 | 3(Loss) | true |
| simdjson (ondemand) | 543.954 | 0.191837 | 794.583ms | 4390 | 30 | 6540.23 | 7696.67 | 0.259179 | 4.53588 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1101.02 | 0.175849 | 435.42ms | 4390 | 40 | 1788.46 | 3802.5 | 0.0219106 | 2.2319 | 1(Win) | true |
| Glaze | 959.592 | 0.26638 | 490.067ms | 4390 | 2560 | 345780 | 4362.93 | 0.42703 | 2.5624 | 2(Loss) | true |
| Jsonifier | 741.872 | 0.163057 | 385.882ms | 4390 | 30 | 2540.23 | 5643.33 | 0.296209 | 3.31464 | 3(Loss) | true |
| simdjson (ondemand) | 574.43 | 0.165756 | 829.105ms | 4390 | 4890 | 713676 | 7288.32 | 1.06209 | 4.29341 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7191.21 | 0.784597 | 61.2708ms | 4390 | 2560 | 53414.5 | 582.188 | 0.458345 | 0.327282 | 1(Win) | true |
| Glaze | 2669.83 | 1.26996 | 172.36ms | 4390 | 640 | 253818 | 1568.12 | 1.8772 | 0.907054 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7668.7 | 0.361109 | 64.3801ms | 4390 | 640 | 2487.38 | 545.938 | 0.114613 | 0.305919 | 1(Win) | true |
| Glaze | 3006.56 | 0.332519 | 143.112ms | 4390 | 80 | 1715.19 | 1392.5 | 0.535714 | 0.801469 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1958.44 | 0.191688 | 477.558ms | 9378 | 30 | 2298.85 | 4566.67 | 0.0729395 | 1.25231 | 1(Win) | true |
| Jsonifier (two-stage) | 1885.83 | 0.166912 | 495.871ms | 9378 | 40 | 2506.41 | 4742.5 | 0.193662 | 1.3047 | 2(Loss) | true |
| Glaze | 1357.9 | 0.333085 | 665.229ms | 9378 | 1280 | 616037 | 6586.33 | 0.150871 | 1.81474 | 3(Loss) | true |
| simdjson (ondemand) | 1077.1 | 0.152442 | 845.783ms | 9378 | 4890 | 783472 | 8303.33 | 0.186262 | 2.28625 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2236.59 | 0.0799089 | 465.45ms | 9378 | 160 | 1633.65 | 3998.75 | 0.345044 | 1.09925 | 1(Win) | true |
| Jsonifier (two-stage) | 2099.43 | 0.202863 | 471.085ms | 9378 | 80 | 5974.68 | 4260 | 0.176367 | 1.17011 | 2(Loss) | true |
| Glaze | 1597.78 | 0.119458 | 620.298ms | 9378 | 40 | 1788.46 | 5597.5 | 0.0148898 | 1.54571 | 3(Loss) | true |
| simdjson (ondemand) | 1203.27 | 0.299584 | 868.235ms | 9378 | 2560 | 1.26933e+06 | 7432.73 | 0.318441 | 2.05033 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10495.3 | 0.37803 | 108.717ms | 11521 | 160 | 2505.9 | 1046.88 | 0.297619 | 0.230212 | 1(Win) | true |
| Glaze | 3558.63 | 0.331834 | 315.055ms | 11521 | 40 | 4198.72 | 3087.5 | 0.403226 | 0.688191 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12450.2 | 0.484415 | 91.875ms | 11521 | 80 | 1462.03 | 882.5 | 0 | 0.191019 | 1(Win) | true |
| Glaze | 4361.11 | 0.087835 | 261.409ms | 11521 | 320 | 1567.01 | 2519.38 | 0.123885 | 0.561442 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1389.97 | 0.225738 | 323.209ms | 4669 | 4890 | 255715 | 3203.46 | 0.290414 | 1.76509 | 1(Win) | true |
| Jsonifier (two-stage) | 1010.26 | 0.112542 | 453.417ms | 4669 | 80 | 1968.35 | 4407.5 | 0.284414 | 2.43433 | 2(Loss) | true |
| Glaze | 901.966 | 0.265686 | 502.925ms | 4669 | 30 | 5160.92 | 4936.67 | 0.0674764 | 2.73216 | 3(Loss) | true |
| simdjson (ondemand) | 756.78 | 0.0977081 | 604.884ms | 4669 | 80 | 2643.99 | 5883.75 | 0.148494 | 3.25527 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1531.45 | 0.118876 | 309.601ms | 4669 | 80 | 955.696 | 2907.5 | 0.25729 | 1.60334 | 1(Win) | true |
| Jsonifier (two-stage) | 1109.02 | 0.168028 | 453.624ms | 4669 | 40 | 1820.51 | 4015 | 0.124688 | 2.22131 | 2(Loss) | true |
| Glaze | 1010.54 | 0.129845 | 521.012ms | 4669 | 80 | 2618.67 | 4406.25 | 0.198188 | 2.43618 | 3(Loss) | true |
| simdjson (ondemand) | 850.565 | 0.145895 | 569.295ms | 4669 | 40 | 2333.33 | 5235 | 0.159439 | 2.89737 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12256.9 | 0.528432 | 40.8897ms | 4669 | 640 | 2358.54 | 363.281 | 0.47089 | 0.188996 | 1(Win) | true |
| Glaze | 2687.75 | 0.555445 | 179.431ms | 4669 | 30 | 2540.23 | 1656.67 | 0.400802 | 0.904719 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14842.4 | 0 | 32.6217ms | 4669 | 30 | 0 | 300 | 0 | 0.14774 | 1(Win) | true |
| Glaze | 3163.56 | 0.104775 | 150.975ms | 4669 | 320 | 695.925 | 1407.5 | 0 | 0.76546 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1861.66 | 0.220227 | 430.543ms | 7932 | 30 | 2402.3 | 4063.33 | 0.1638 | 1.32152 | 1(Win) | true |
| Jsonifier (two-stage) | 1693.71 | 0.119117 | 466.468ms | 7932 | 80 | 2264.24 | 4466.25 | 0.139743 | 1.45271 | 2(Loss) | true |
| Glaze | 1283.21 | 0.0597862 | 609.626ms | 7932 | 160 | 1987.42 | 5895 | 0.233794 | 1.9197 | 3(Loss) | true |
| simdjson (ondemand) | 1246.27 | 0.222983 | 619.792ms | 7932 | 4890 | 895762 | 6069.73 | 0.0464831 | 1.97716 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1957.11 | 0.255496 | 401.266ms | 7932 | 2560 | 249657 | 3865.16 | 0.0868389 | 1.25572 | 1(Win) | true |
| Jsonifier (two-stage) | 1816.22 | 0.0932808 | 441.953ms | 7932 | 160 | 2415.09 | 4165 | 0.448163 | 1.35389 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1419.78 | 0.446403 | 553.5ms | 7932 | 1280 | 724080 | 5327.97 | 0.0586872 | 1.73446 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1410.14 | 0.257806 | 569.577ms | 7932 | 2560 | 489625 | 5364.38 | 0.188225 | 1.74653 | 3(Tie) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10571.4 | 0.225188 | 97.3512ms | 9249 | 640 | 2259.39 | 834.375 | 0.558659 | 0.226185 | 1(Win) | true |
| Glaze | 3418.05 | 0.217599 | 262.264ms | 9249 | 4890 | 154190 | 2580.57 | 0.382022 | 0.715994 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11268.3 | 0.488761 | 85.2416ms | 9249 | 2560 | 37471.8 | 782.773 | 0.79703 | 0.2114 | 1(Win) | true |
| Glaze | 3830.85 | 0.108578 | 244.213ms | 9249 | 40 | 250 | 2302.5 | 0.253991 | 0.637982 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 447.198 | 0.222797 | 1005.69ms | 4604 | 2560 | 1.22498e+06 | 9818.28 | 0.0772434 | 5.52074 | 1(Win) | true |
| Jsonifier (two-stage) | 428.559 | 0.420512 | 1102.75ms | 4604 | 320 | 593959 | 10245.3 | 0.494719 | 5.75953 | 2(Loss) | true |
| Glaze | 155.744 | 0.332482 | 2844.22ms | 4604 | 320 | 2.81147e+06 | 28191.9 | 0.179251 | 15.8796 | 3(Loss) | true |
| simdjson (ondemand) | 100.547 | 0.371097 | 4542.34ms | 4604 | 160 | 4.20168e+06 | 43668.1 | 0.0472089 | 24.6033 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 544.709 | 0.267089 | 972.942ms | 4604 | 2560 | 1.18657e+06 | 8060.66 | 0.266307 | 4.52945 | 1(Win) | true |
| Jsonifier (two-stage) | 517.938 | 0.178677 | 997.006ms | 4604 | 4890 | 1.12192e+06 | 8477.3 | 0.144387 | 4.7642 | 2(Loss) | true |
| Glaze | 169.912 | 0.113572 | 2764.03ms | 4604 | 2560 | 2.20496e+06 | 25841.1 | 0.0799021 | 14.5552 | 3(Loss) | true |
| simdjson (ondemand) | 104.07 | 0.0787156 | 4507ms | 4604 | 4890 | 5.3932e+06 | 42189.9 | 0.25532 | 23.774 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1470.27 | 0.131965 | 331.539ms | 4918 | 80 | 1417.72 | 3190 | 0.156495 | 1.66767 | 1(Win) | true |
| Glaze | 721.194 | 0.0733583 | 615.403ms | 4604 | 160 | 3191.43 | 6088.12 | 0.0307882 | 3.41539 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1567.96 | 0.0805661 | 306.228ms | 4918 | 160 | 929.245 | 2991.25 | 0.0835073 | 1.56505 | 1(Win) | true |
| Glaze | 762.719 | 0.159847 | 600.334ms | 4604 | 30 | 2540.23 | 5756.67 | 0 | 3.23061 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1550.05 | 0.159185 | 1152.93ms | 18245 | 4890 | 1.56138e+06 | 11225.3 | 0.480118 | 1.59302 | 1(Win) | true |
| Jsonifier | 1366.67 | 0.540166 | 1311.31ms | 18245 | 320 | 1.51345e+06 | 12731.6 | 0.0909002 | 1.80719 | 2(Loss) | true |
| Glaze | 559.687 | 0.247233 | 3174.53ms | 18245 | 640 | 3.78087e+06 | 31088.4 | 0.233664 | 4.41947 | 3(Loss) | true |
| simdjson (ondemand) | 387.871 | 0.268799 | 4651.58ms | 18245 | 320 | 4.65282e+06 | 44859.7 | 0.346407 | 6.37906 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1881.57 | 0.10235 | 1109.86ms | 18245 | 40 | 3583.33 | 9247.5 | 0.0811688 | 1.31094 | 1(Win) | true |
| Jsonifier | 1586.49 | 0.201588 | 1263.59ms | 18245 | 2560 | 1.25137e+06 | 10967.5 | 0.0719973 | 1.55642 | 2(Loss) | true |
| Glaze | 598.119 | 0.20235 | 3113.77ms | 18245 | 1280 | 4.43537e+06 | 29090.9 | 0.788918 | 4.13545 | 3(Loss) | true |
| simdjson (ondemand) | 392.398 | 0.322854 | 4623.24ms | 18245 | 320 | 6.55837e+06 | 44342.2 | 0.00916086 | 6.30516 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5405.39 | 0.0604711 | 460.563ms | 24893 | 160 | 1128.54 | 4391.88 | 0.0142328 | 0.455378 | 1(Win) | true |
| Glaze | 2767.46 | 0.100468 | 837.939ms | 24579 | 30 | 2172.41 | 8470 | 0.157667 | 0.892297 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5513.52 | 0.195785 | 443.215ms | 24893 | 4890 | 347508 | 4305.75 | 0.143037 | 0.44619 | 1(Win) | true |
| Glaze | 3145.05 | 0.143609 | 764.452ms | 24579 | 4890 | 560200 | 7453.09 | 0.802542 | 0.784175 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 506.262 | 0.165665 | 895.87ms | 4604 | 4890 | 1.00947e+06 | 8672.82 | 0.0552583 | 4.87415 | 1(Win) | true |
| Jsonifier (two-stage) | 456.199 | 0.240813 | 996.406ms | 4604 | 2560 | 1.37519e+06 | 9624.57 | 0.0482743 | 5.41047 | 2(Loss) | true |
| simdjson (ondemand) | 184.175 | 0.0921952 | 2430.53ms | 4604 | 4890 | 2.36231e+06 | 23840 | 0.548703 | 13.4252 | 3(Loss) | true |
| Glaze | 156.265 | 0.136783 | 2844.91ms | 4604 | 2560 | 3.78138e+06 | 28097.9 | 0.540929 | 15.827 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 641.903 | 0.333517 | 843.484ms | 4604 | 1280 | 666158 | 6840.16 | 0.245019 | 3.84055 | 1(Win) | true |
| Jsonifier (two-stage) | 562.822 | 0.0897575 | 967.991ms | 4604 | 80 | 3922.47 | 7801.25 | 0.0480461 | 4.38395 | 2(Loss) | true |
| simdjson (ondemand) | 199.966 | 0.214154 | 2341.95ms | 4604 | 1280 | 2.83022e+06 | 21957.3 | 0.338643 | 12.3648 | 3(Loss) | true |
| Glaze | 168.146 | 0.122766 | 2790.77ms | 4604 | 2560 | 2.63084e+06 | 26112.5 | 0.239623 | 14.7081 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1436.02 | 0.221908 | 331.395ms | 4918 | 4890 | 256870 | 3266.09 | 0.0681158 | 1.70909 | 1(Win) | true |
| Glaze | 722.659 | 0.4595 | 641.718ms | 4604 | 640 | 498834 | 6075.78 | 0.15196 | 3.41055 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1522.78 | 0.241163 | 320.442ms | 4918 | 30 | 1655.17 | 3080 | 0.108108 | 1.60166 | 1(Win) | true |
| Glaze | 766.425 | 0.27184 | 577.514ms | 4604 | 2560 | 620865 | 5728.83 | 0.0218242 | 3.21543 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1667.71 | 0.244614 | 1084.38ms | 18245 | 30 | 19540.2 | 10433.3 | 0.16 | 1.47967 | 1(Win) | true |
| Jsonifier | 1441.57 | 0.362216 | 1218.91ms | 18245 | 640 | 1.22329e+06 | 12070 | 0.293423 | 1.71309 | 2(Loss) | true |
| simdjson (ondemand) | 706.373 | 0.125642 | 2513.7ms | 18245 | 2560 | 2.45206e+06 | 24632.6 | 0.0351925 | 3.50066 | 3(Loss) | true |
| Glaze | 557.186 | 0.161934 | 3185.88ms | 18245 | 1280 | 3.2732e+06 | 31228 | 0.607595 | 4.439 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2008.44 | 0.151397 | 1038.43ms | 18245 | 30 | 5160.92 | 8663.33 | 0.192012 | 1.22815 | 1(Win) | true |
| Jsonifier | 1848.09 | 0.129248 | 1117.21ms | 18245 | 40 | 5923.08 | 9415 | 0.444523 | 1.33562 | 2(Loss) | true |
| simdjson (ondemand) | 788.123 | 0.0834686 | 2395.86ms | 18245 | 40 | 13583.3 | 22077.5 | 0.0113225 | 3.13738 | 3(Loss) | true |
| Glaze | 603.023 | 0.127333 | 3066.76ms | 18245 | 2560 | 3.45576e+06 | 28854.3 | 0.213677 | 4.10184 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5159.22 | 0.211735 | 459.547ms | 24893 | 4890 | 464175 | 4601.43 | 0.238278 | 0.476675 | 1(Win) | true |
| Glaze | 2833.52 | 0.143442 | 839.895ms | 24579 | 4890 | 688551 | 8272.52 | 0.449365 | 0.870821 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5568.37 | 0.238126 | 445.749ms | 24893 | 30 | 3091.95 | 4263.33 | 0.078125 | 0.44132 | 1(Win) | true |
| Glaze | 3121.22 | 0.116852 | 752.418ms | 24579 | 30 | 2310.34 | 7510 | 0.0443656 | 0.788953 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 879.08 | 0.127726 | 580.192ms | 5094 | 80 | 3985.76 | 5526.25 | 0.340445 | 2.7936 | 1(Win) | true |
| Jsonifier (two-stage) | 777.283 | 0.136502 | 675.972ms | 5094 | 80 | 5822.78 | 6250 | 0.040016 | 3.1636 | 2(Loss) | true |
| Glaze | 611.36 | 0.276156 | 841.981ms | 5094 | 1280 | 616374 | 7946.25 | 0.159527 | 4.03382 | 3(Loss) | true |
| simdjson (ondemand) | 427.633 | 0.145069 | 1195.71ms | 5094 | 4890 | 1.3281e+06 | 11360.2 | 0.0552327 | 5.76526 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1092.51 | 0.208338 | 573.525ms | 5094 | 30 | 2574.71 | 4446.67 | 0.0749064 | 2.25376 | 1(Win) | true |
| Jsonifier (two-stage) | 914.536 | 0.202825 | 650.766ms | 5094 | 4890 | 567635 | 5312 | 0.361002 | 2.69311 | 2(Loss) | true |
| Glaze | 802.398 | 0.581105 | 720.083ms | 5094 | 320 | 396094 | 6054.38 | 0.560573 | 3.07097 | 3(Loss) | true |
| simdjson (ondemand) | 499.915 | 0.149966 | 1127.58ms | 5094 | 4890 | 1.03854e+06 | 9717.69 | 0.0349206 | 4.93817 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8817.35 | 0.507915 | 58.8268ms | 5094 | 4890 | 38294.2 | 550.961 | 0.0610479 | 0.266309 | 1(Win) | true |
| Glaze | 2761.22 | 0.243247 | 185.87ms | 5094 | 160 | 2930.42 | 1759.38 | 0.392297 | 0.883505 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10802.2 | 0.25328 | 49.5937ms | 5094 | 2560 | 3321.54 | 449.727 | 0.165304 | 0.215087 | 1(Win) | true |
| Glaze | 3079.57 | 0.496805 | 161.81ms | 5094 | 1280 | 78617.7 | 1577.5 | 0.0693825 | 0.790041 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1257.54 | 0.255456 | 626.426ms | 8051 | 2560 | 622771 | 6105.59 | 0.139916 | 1.95384 | 1(Win) | true |
| Jsonifier (two-stage) | 1112.36 | 0.132125 | 710.663ms | 8051 | 40 | 3326.92 | 6902.5 | 0.156702 | 2.20728 | 2(Loss) | true |
| Glaze | 891.111 | 0.0956067 | 884.773ms | 8051 | 80 | 5428.8 | 8616.25 | 0.274884 | 2.77059 | 3(Loss) | true |
| simdjson (ondemand) | 652.374 | 0.1536 | 1193.14ms | 8051 | 4890 | 1.59808e+06 | 11769.4 | 0.140848 | 3.77971 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1541.77 | 0.163955 | 622.198ms | 8051 | 40 | 2666.67 | 4980 | 0.0669792 | 1.59709 | 1(Win) | true |
| Jsonifier (two-stage) | 1298.39 | 0.169645 | 707.85ms | 8051 | 4890 | 492127 | 5913.5 | 0.484137 | 1.89681 | 2(Loss) | true |
| Glaze | 1115.99 | 0.09465 | 810.821ms | 8051 | 80 | 3392.41 | 6880 | 0.511322 | 2.20875 | 3(Loss) | true |
| simdjson (ondemand) | 765.689 | 0.216008 | 1139.13ms | 8051 | 2560 | 1.20109e+06 | 10027.6 | 0.0315435 | 3.22419 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10634 | 0.437858 | 87.6628ms | 9255 | 160 | 2113.21 | 830 | 0 | 0.22424 | 1(Win) | true |
| Glaze | 3057.33 | 0.302866 | 303.54ms | 9255 | 4890 | 373832 | 2886.91 | 0.404354 | 0.802016 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11699.4 | 0.474093 | 77.9722ms | 9255 | 4890 | 62554.6 | 754.417 | 0.077195 | 0.202918 | 1(Win) | true |
| Glaze | 3596.82 | 0.649577 | 258.365ms | 9255 | 640 | 162614 | 2453.91 | 0.428444 | 0.679184 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5462.53 | 0.366515 | 67.8296ms | 2889 | 160 | 546.777 | 504.375 | 0.124069 | 0.427404 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5442.3 | 0.537956 | 55.7721ms | 2889 | 80 | 593.354 | 506.25 | 0.246305 | 0.432974 | 1(Tie) | true |
| simdjson (ondemand) | 3002.9 | 0.465936 | 94.8746ms | 2889 | 80 | 1462.03 | 917.5 | 0.547945 | 0.793077 | 3(Loss) | true |
| Glaze | 2659.99 | 0.191596 | 107.112ms | 2889 | 640 | 2520.52 | 1035.78 | 0.0150875 | 0.902167 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5931.07 | 0.40742 | 53.3021ms | 2889 | 640 | 2292.42 | 464.531 | 0.0336247 | 0.392496 | 1(Win) | true |
| Jsonifier (two-stage) | 5821.27 | 0.296411 | 51.7485ms | 2889 | 4890 | 9624.05 | 473.292 | 1.41346 | 0.399919 | 2(Loss) | true |
| simdjson (ondemand) | 3275.08 | 0.464079 | 91.4507ms | 2889 | 160 | 2438.68 | 841.25 | 0.447761 | 0.729621 | 3(Loss) | true |
| Glaze | 2879.34 | 0.495736 | 115.144ms | 2889 | 160 | 3600.24 | 956.875 | 0.325521 | 0.830484 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 6748.6 | 0.715782 | 70.8171ms | 3808 | 160 | 2373.82 | 538.125 | 0.34965 | 0.347417 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6698.04 | 0.360332 | 59.1275ms | 3808 | 640 | 2442.78 | 542.188 | 0 | 0.350755 | 1(Tie) | true |
| simdjson (ondemand) | 3865.97 | 0.291207 | 98.6766ms | 3808 | 320 | 2394.59 | 939.375 | 0.0664894 | 0.620009 | 3(Loss) | true |
| Glaze | 3286.51 | 0.315829 | 115.596ms | 3808 | 40 | 487.179 | 1105 | 0.151057 | 0.735347 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7184.6 | 0.193408 | 63.9412ms | 3808 | 640 | 611.674 | 505.469 | 0.154799 | 0.326316 | 1(Win) | true |
| Jsonifier | 7093.6 | 0.178498 | 56.2631ms | 3808 | 1280 | 1068.9 | 511.953 | 0.0152625 | 0.329497 | 2(Loss) | true |
| simdjson (ondemand) | 4123.88 | 0.413388 | 93.9335ms | 3808 | 640 | 8481.61 | 880.625 | 1.84315 | 0.578626 | 3(Loss) | true |
| Glaze | 3393.52 | 0.364832 | 112.578ms | 3808 | 2560 | 39023 | 1070.16 | 0.204828 | 0.709831 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1469.42 | 0.373526 | 198.469ms | 2889 | 80 | 3924.05 | 1875 | 0 | 1.65951 | 1(Win) | true |
| Glaze | 1166.15 | 0.25497 | 241.664ms | 2889 | 4890 | 177449 | 2362.62 | 0.066195 | 2.09563 | 2(Loss) | true |
| Jsonifier (two-stage) | 1119.21 | 0.243836 | 260.091ms | 2889 | 4890 | 176187 | 2461.7 | 0.111821 | 2.1852 | 3(Loss) | true |
| simdjson (ondemand) | 1070.49 | 0.274248 | 274.591ms | 2889 | 80 | 3985.76 | 2573.75 | 0.0485437 | 2.28104 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2019.13 | 0.141511 | 167.727ms | 2889 | 640 | 2386.32 | 1364.53 | 0.0572213 | 1.20239 | 1(Win) | true |
| Glaze | 1519.04 | 0.235059 | 206.849ms | 2889 | 80 | 1454.11 | 1813.75 | 0.207182 | 1.60889 | 2(Loss) | true |
| Jsonifier (two-stage) | 1421.1 | 0.370624 | 223.841ms | 2889 | 2560 | 132175 | 1938.75 | 0.560987 | 1.71558 | 3(Loss) | true |
| simdjson (ondemand) | 1278.31 | 0.129151 | 243.353ms | 2889 | 320 | 2479.53 | 2155.31 | 0.363795 | 1.91538 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8579.09 | 0.54705 | 44.1767ms | 2963 | 640 | 2077.86 | 329.375 | 0.189394 | 0.264972 | 1(Win) | true |
| Glaze | 4110.16 | 0.77029 | 75.214ms | 2963 | 40 | 1121.79 | 687.5 | 0.362319 | 0.582847 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10378.4 | 0.290535 | 30.8029ms | 2963 | 4890 | 3059.89 | 272.27 | 0.448342 | 0.214869 | 1(Win) | true |
| Glaze | 4762.48 | 0.780684 | 64.3976ms | 2963 | 30 | 643.678 | 593.333 | 0.564972 | 0.502801 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1600.26 | 0.234413 | 234.45ms | 3808 | 160 | 4527.91 | 2269.38 | 0.0825537 | 1.52828 | 1(Win) | true |
| Jsonifier (two-stage) | 1433.93 | 0.251903 | 257.057ms | 3808 | 4890 | 199028 | 2532.62 | 0.564376 | 1.70609 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1366.58 | 0.409859 | 272.377ms | 3808 | 1280 | 151845 | 2657.42 | 0.825121 | 1.79038 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1354.23 | 0.225581 | 274.792ms | 3808 | 4890 | 178946 | 2681.66 | 0.199091 | 1.80762 | 3(Tie) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2027.8 | 0.31287 | 197.423ms | 3808 | 4890 | 153525 | 1790.9 | 0.122371 | 1.20164 | 1(Win) | true |
| Jsonifier (two-stage) | 1788.96 | 0.419194 | 229.212ms | 3808 | 30 | 2172.41 | 2030 | 0 | 1.35962 | 2(Loss) | true |
| Glaze | 1718.08 | 0.201698 | 237.406ms | 3808 | 80 | 1454.11 | 2113.75 | 0.535077 | 1.41888 | 3(Loss) | true |
| simdjson (ondemand) | 1664.2 | 0.104267 | 236.974ms | 3808 | 320 | 1656.64 | 2182.19 | 0.0429799 | 1.4687 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7189.48 | 0.366142 | 60.9194ms | 4300 | 4890 | 21327.9 | 570.389 | 0.389202 | 0.32833 | 1(Win) | true |
| Glaze | 3335.15 | 0.681738 | 126.29ms | 4300 | 2560 | 179879 | 1229.57 | 0.790906 | 0.7248 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7800.56 | 0.505599 | 56.0494ms | 4300 | 4890 | 34546.7 | 525.706 | 0.597819 | 0.300775 | 1(Win) | true |
| Glaze | 4339.47 | 0.417501 | 111.069ms | 4300 | 160 | 2490.57 | 945 | 0.526316 | 0.553785 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22081.6 | 0.381413 | 2034.77ms | 466906 | 320 | 1.89294e+06 | 20165 | 0.812398 | 0.111945 | 1(Win) | true |
| simdjson (ondemand) | 20311.1 | 0.376594 | 2191.78ms | 466906 | 640 | 4.36233e+06 | 21922.8 | 1.32738 | 0.121748 | 2(Loss) | true |
| Glaze | 1668.42 | 0.197924 | 6876.18ms | 466906 | 160 | 4.46441e+07 | 266884 | 0.129336 | 1.48376 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22878.4 | 0.172626 | 1949.36ms | 466906 | 2560 | 2.88975e+06 | 19462.8 | 0.193249 | 0.107992 | 1(Win) | true |
| simdjson (ondemand) | 21330.8 | 0.126573 | 2155.76ms | 466906 | 4890 | 3.41378e+06 | 20874.8 | 0.717768 | 0.115906 | 2(Loss) | true |
| Glaze | 1715.04 | 0.139664 | 6688ms | 466906 | 320 | 4.20753e+07 | 259630 | 0.421113 | 1.44344 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2925.99 | 0.64331 | 6111.42ms | 699405 | 160 | 3.44091e+08 | 227959 | 0.796384 | 0.845988 | 1(Win) | true |
| Jsonifier | 2428.58 | 0.458881 | 7047.78ms | 699405 | 40 | 6.35349e+07 | 274648 | 0.00455108 | 1.01908 | 2(Loss) | true |
| simdjson (ondemand) | 1373.27 | 0.278342 | 6701.4ms | 767297 | 320 | 7.03923e+08 | 532854 | 0.652567 | 1.80256 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4522.72 | 0.377917 | 7719.28ms | 699405 | 160 | 4.97018e+07 | 147479 | 0.1613 | 0.547304 | 1(Win) | true |
| Glaze | 2908.13 | 0.248859 | 6007.11ms | 699405 | 160 | 5.21263e+07 | 229359 | 0.500622 | 0.85124 | 2(Loss) | true |
| simdjson (ondemand) | 1376.09 | 0.172931 | 6755.68ms | 767297 | 640 | 5.41202e+08 | 531761 | 0.308104 | 1.79869 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2948.2 | 0.739305 | 5422.02ms | 631514 | 30 | 6.84258e+07 | 204280 | 0.0603382 | 0.83961 | 1(Win) | true |
| Glaze | 2432.79 | 0.182839 | 6497.88ms | 631514 | 1280 | 2.62243e+08 | 247559 | 0.767988 | 1.01756 | 2(Loss) | true |
