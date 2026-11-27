# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson
Just a bit of performance profiling of some JSON libraries (compiled and run on macOS 25.6.0 using the Clang 23.1.6 compiler).  

Latest results: (Nov 28, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
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
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1271.45 | 0.0882768 | 71.431ms | 905 | 1280 | 459.624 | 678.812 | 0.032215 | 1(Win) | true |
| Glaze | 1121.92 | 0.304127 | 77.0467ms | 905 | 80 | 437.904 | 769.288 | 0.196225 | 2(Loss) | true |
| simdjson (ondemand) | 312.202 | 0.0473388 | 282.608ms | 905 | 320 | 548.037 | 2764.47 | 0.0700366 | 3(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1369.51 | 0.0947684 | 66.5744ms | 905 | 640 | 228.285 | 630.209 | 0.0595395 | 1(Win) | true |
| Glaze | 1322.91 | 0.138448 | 67.536ms | 905 | 640 | 522.145 | 652.406 | 0.0944513 | 2(Loss) | true |
| simdjson (ondemand) | 308.078 | 0.106457 | 283.525ms | 905 | 4890 | 43494.6 | 2801.48 | 0.217092 | 3(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1023.75 | 0.228471 | 87.2548ms | 905 | 2560 | 9497.44 | 843.049 | 0.0182129 | 1(Win) | true |
| Glaze | 131.48 | 0.100674 | 663.245ms | 905 | 2560 | 111804 | 6564.32 | 0.00524882 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1266.59 | 0.0599692 | 78.7407ms | 905 | 2560 | 427.486 | 681.416 | 0.0281547 | 1(Win) | true |
| Glaze | 753.58 | 0.224115 | 128.678ms | 905 | 80 | 527.073 | 1145.3 | 0.135519 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 868.033 | 0.194566 | 196.827ms | 1811 | 40 | 599.456 | 1989.67 | 0.101672 | 1(Win) | true |
| Glaze | 784.232 | 0.0545152 | 214.898ms | 1811 | 640 | 922.493 | 2202.29 | 0.127404 | 2(Loss) | true |
| simdjson (ondemand) | 303.604 | 0.0988002 | 626.006ms | 1811 | 2560 | 80868.1 | 5688.67 | 0.0680166 | 3(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1074.96 | 0.0772841 | 173.611ms | 1811 | 320 | 493.378 | 1606.66 | 0.086673 | 1(Win) | true |
| Glaze | 978.459 | 0.0498238 | 181.926ms | 1811 | 640 | 495 | 1765.13 | 0.082658 | 2(Loss) | true |
| simdjson (ondemand) | 303.612 | 0.0584937 | 574.521ms | 1811 | 40 | 442.871 | 5688.52 | 0.0300222 | 3(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 325.297 | 0.0711543 | 591.973ms | 1997 | 4890 | 84860.7 | 5854.61 | 0.0106913 | 1(Win) | true |
| Glaze | 214.171 | 0.102296 | 805.879ms | 1798 | 2560 | 171717 | 8006.25 | 0.0534014 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 952.552 | 0.106165 | 221.666ms | 1997 | 320 | 1441.75 | 1999.35 | 0.511443 | 1(Win) | true |
| Glaze | 701.559 | 0.177401 | 258.019ms | 1798 | 1280 | 24064.3 | 2444.14 | 0.0558742 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1059.35 | 0.138378 | 122.014ms | 1313 | 160 | 428.056 | 1182.02 | 0.017452 | 1(Win) | true |
| Glaze | 717.665 | 0.0888579 | 179.811ms | 1313 | 320 | 769.182 | 1744.79 | 0.0141513 | 2(Loss) | true |
| simdjson (ondemand) | 295.228 | 0.180451 | 424.297ms | 1313 | 1280 | 74979.3 | 4241.38 | 0.0621868 | 3(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1386.06 | 0.236407 | 94.3889ms | 1313 | 160 | 729.802 | 903.406 | 0.257328 | 1(Win) | true |
| Glaze | 859.872 | 0.0561017 | 149.5ms | 1313 | 1280 | 854.327 | 1456.23 | 0.101391 | 2(Loss) | true |
| simdjson (ondemand) | 323.145 | 0.0730603 | 394.348ms | 1313 | 30 | 240.447 | 3874.97 | 0.357431 | 3(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 953.08 | 0.729914 | 115.953ms | 1313 | 160 | 14714.1 | 1313.82 | 2.48778 | 1(Win) | true |
| Glaze | 182.854 | 0.132209 | 683.661ms | 1313 | 1280 | 104918 | 6847.93 | 0.580948 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1546.09 | 0.107191 | 91.4154ms | 1313 | 640 | 482.346 | 809.897 | 0.0807081 | 1(Win) | true |
| Glaze | 797.485 | 1.00354 | 173.232ms | 1313 | 1280 | 317809 | 1570.15 | 0.196548 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1023.34 | 0.626864 | 363.638ms | 4215 | 640 | 388045 | 3928.05 | 0.0880306 | 1(Win) | true |
| Glaze | 840.146 | 0.212852 | 478.446ms | 4215 | 640 | 66377.7 | 4784.57 | 0.383745 | 2(Loss) | true |
| simdjson (ondemand) | 714.491 | 0.0494617 | 569.161ms | 4215 | 320 | 2477.94 | 5626.02 | 0.0655008 | 3(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1635.16 | 0.0450476 | 303.505ms | 4215 | 160 | 196.219 | 2458.32 | 0.0404403 | 1(Win) | true |
| Glaze | 1018.36 | 0.188685 | 458.243ms | 4215 | 640 | 35501.4 | 3947.25 | 0.828081 | 2(Loss) | true |
| simdjson (ondemand) | 852.272 | 0.20438 | 588.854ms | 4215 | 640 | 59469.8 | 4716.5 | 0.108841 | 3(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 601.454 | 0.125402 | 521.43ms | 4215 | 30 | 2107.27 | 6683.37 | 0.205561 | 1(Win) | true |
| Glaze | 530.149 | 0.0652875 | 764.249ms | 4215 | 4890 | 119831 | 7582.28 | 0.0241977 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3523.71 | 0.110505 | 133.549ms | 4215 | 320 | 508.523 | 1140.77 | 0.120388 | 1(Win) | true |
| Glaze | 2049.77 | 0.141487 | 213.892ms | 4215 | 30 | 230.961 | 1961.07 | 0.00169973 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1072.96 | 0.135981 | 111.26ms | 1213 | 160 | 343.902 | 1078.15 | 0.0440375 | 1(Win) | true |
| Glaze | 632.38 | 0.08731 | 178.166ms | 1213 | 320 | 816.288 | 1829.29 | 0.0916523 | 2(Loss) | true |
| simdjson (ondemand) | 274.49 | 0.0825265 | 425.299ms | 1213 | 4890 | 59151.4 | 4214.39 | 0.00754595 | 3(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1461.93 | 0.0545943 | 82.3627ms | 1213 | 640 | 119.438 | 791.286 | 0.0321969 | 1(Win) | true |
| Glaze | 793.101 | 0.0583865 | 148.589ms | 1213 | 1280 | 928.324 | 1458.59 | 0.103643 | 2(Loss) | true |
| simdjson (ondemand) | 288.505 | 0.0414441 | 405.688ms | 1213 | 160 | 441.835 | 4009.66 | 0.0205795 | 3(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1158.85 | 0.0799355 | 103.134ms | 1213 | 640 | 407.499 | 998.237 | 0.0203525 | 1(Win) | true |
| Glaze | 174.76 | 0.0888054 | 670.647ms | 1213 | 30 | 1036.66 | 6619.4 | 0.0226555 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1418.79 | 0.220342 | 92.0458ms | 1213 | 160 | 516.418 | 815.35 | 0.0291371 | 1(Win) | true |
| Glaze | 828.938 | 0.241103 | 156.102ms | 1213 | 4890 | 55359.5 | 1395.53 | 0.168771 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1331.58 | 0.167359 | 6866.49ms | 94653 | 320 | 4.11887e+06 | 67790 | 0.0681651 | 1(Win) | true |
| Jsonifier (two-stage) | 1218.37 | 0.0984264 | 7569.9ms | 94653 | 640 | 3.40341e+06 | 74089.4 | 0.0940524 | 2(Loss) | true |
| Glaze | 1118.63 | 0.0550446 | 8218.48ms | 94653 | 2560 | 5.05089e+06 | 80695.5 | 0.165356 | 3(Loss) | true |
| simdjson (ondemand) | 833.87 | 0.391322 | 5322.94ms | 94653 | 40 | 7.17795e+06 | 108252 | 0.515114 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1859.65 | 0.0531146 | 6514.09ms | 94653 | 30 | 19941.3 | 48540.3 | 0.0599828 | 1(Win) | true |
| Jsonifier (two-stage) | 1623.78 | 0.0793829 | 7251.85ms | 94653 | 1280 | 2.49275e+06 | 55591.4 | 0.0414819 | 2(Loss) | true |
| Glaze | 1468.28 | 0.166218 | 7776.03ms | 94653 | 320 | 3.34164e+06 | 61478.9 | 0.357443 | 3(Loss) | true |
| simdjson (ondemand) | 1052.51 | 0.132377 | 5325.35ms | 94653 | 320 | 4.12472e+06 | 85765 | 0.0135126 | 4(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11325.7 | 0.0362894 | 792.49ms | 94653 | 80 | 669.251 | 7970.2 | 0.0990211 | 1(Win) | true |
| Glaze | 3556.35 | 0.0293532 | 2629.55ms | 94653 | 40 | 2220.41 | 25382.3 | 0.167912 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11819.5 | 0.0249586 | 811.073ms | 94653 | 160 | 581.346 | 7637.25 | 0.0240655 | 1(Win) | true |
| Glaze | 4056.64 | 0.0552937 | 2157.29ms | 94653 | 40 | 6055.46 | 22251.9 | 0.0846027 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1500.55 | 0.13144 | 8126.53ms | 124597 | 320 | 3.46672e+06 | 79187.8 | 0.143857 | 1(Win) | true |
| Jsonifier (two-stage) | 1398.71 | 0.0618618 | 8562.51ms | 124597 | 4890 | 1.35057e+07 | 84953.5 | 0.0430676 | 2(Loss) | true |
| Glaze | 1373.05 | 0.0408003 | 8756.77ms | 124597 | 4890 | 6.09651e+06 | 86541.2 | 0.0821869 | 3(Loss) | true |
| simdjson (ondemand) | 1115.81 | 0.0785494 | 5570.28ms | 124597 | 640 | 4.47815e+06 | 106492 | 0.166425 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1972.13 | 0.0792827 | 7680.51ms | 124597 | 1280 | 2.92087e+06 | 60252.2 | 0.0533551 | 1(Win) | true |
| Jsonifier (two-stage) | 1774.12 | 0.0179322 | 8362.15ms | 124597 | 40 | 5770.02 | 66977 | 0.0114578 | 2(Loss) | true |
| Glaze | 1725.06 | 0.161692 | 8411.27ms | 124597 | 320 | 3.96948e+06 | 68881.5 | 0.173442 | 3(Loss) | true |
| simdjson (ondemand) | 1343.52 | 0.127603 | 5399.05ms | 124597 | 320 | 4.07565e+06 | 88443 | 0.079416 | 4(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12075.5 | 0.0293845 | 1098.91ms | 136037 | 80 | 797.315 | 10743.7 | 0.00965779 | 1(Win) | true |
| Glaze | 3593.46 | 0.102454 | 3770.35ms | 136076 | 1280 | 1.75227e+06 | 36113.4 | 0.0594733 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12246.8 | 0.17991 | 1115.54ms | 136037 | 320 | 116232 | 10593.3 | 0.314595 | 1(Win) | true |
| Glaze | 3974.69 | 0.107539 | 3276.72ms | 136076 | 1280 | 1.57798e+06 | 32649.7 | 0.399396 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 735.221 | 0.0851113 | 9208.78ms | 2251027 | 40 | 2.47036e+08 | 2.91987e+06 | 1.32914 | 1(Win) | true |
| Jsonifier (two-stage) | 644.044 | 0.753164 | 5032.5ms | 2251027 | 40 | 2.52098e+10 | 3.33323e+06 | 0.314097 | 2(Loss) | true |
| Glaze | 581.296 | 0.882066 | 5429.81ms | 2251027 | 40 | 4.24453e+10 | 3.69304e+06 | 1.61111 | 3(Loss) | true |
| simdjson (ondemand) | 539.512 | 0.0631554 | 6058.28ms | 2251027 | 30 | 1.89454e+08 | 3.97906e+06 | 0.109692 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 890.75 | 0.061465 | 9228.71ms | 2251027 | 80 | 1.75548e+08 | 2.41004e+06 | 0.0146767 | 1(Win) | true |
| Jsonifier (two-stage) | 774.104 | 0.0568437 | 10428.5ms | 2251027 | 80 | 1.988e+08 | 2.7732e+06 | 0.0530052 | 2(Loss) | true |
| Glaze | 703.076 | 0.0723455 | 5435.83ms | 2251027 | 30 | 1.46387e+08 | 3.05336e+06 | 4.64909 | 3(Loss) | true |
| simdjson (ondemand) | 619.402 | 0.0772719 | 6027.74ms | 2251027 | 30 | 2.15169e+08 | 3.46583e+06 | 0.00825803 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2952.08 | 0.0936584 | 8786.4ms | 2090326 | 80 | 3.20004e+07 | 675283 | 0.399771 | 1(Win) | true |
| Glaze | 1879.06 | 0.178533 | 6915.39ms | 2090234 | 160 | 5.73936e+08 | 1.06085e+06 | 0.352769 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2956.53 | 0.133801 | 8790.55ms | 2090326 | 30 | 2.44175e+07 | 674267 | 0.214996 | 1(Win) | true |
| Glaze | 1981.45 | 0.0863997 | 6389.31ms | 2090234 | 80 | 6.04421e+07 | 1.00603e+06 | 0.0214311 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1529.32 | 0.0637488 | 5140.92ms | 5373214 | 80 | 3.6501e+08 | 3.3507e+06 | 0.104735 | 1(Win) | true |
| Jsonifier (two-stage) | 1415.13 | 0.0414305 | 5552.29ms | 5373214 | 40 | 9.00275e+07 | 3.62107e+06 | 0.0310884 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1205.06 | 0.935094 | 6490.36ms | 5373214 | 30 | 4.74332e+10 | 4.25231e+06 | 1.47859 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1195.01 | 0.0710854 | 6539.01ms | 5373214 | 30 | 2.78747e+08 | 4.28809e+06 | 0.0265836 | 3(Tie) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1788.27 | 0.580317 | 5041.68ms | 5373214 | 40 | 1.1061e+10 | 2.86551e+06 | 0.334152 | 1(Win) | true |
| Jsonifier (two-stage) | 1646.8 | 0.0700782 | 5509.58ms | 5373214 | 30 | 1.4265e+08 | 3.11166e+06 | 0.0335977 | 2(Loss) | true |
| Glaze | 1398.87 | 0.066341 | 6301.14ms | 5373214 | 40 | 2.36231e+08 | 3.66316e+06 | 0.396607 | 3(Loss) | true |
| simdjson (ondemand) | 1345.24 | 0.388209 | 6653.92ms | 5373214 | 30 | 6.56029e+09 | 3.80921e+06 | 0.704579 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7410.83 | 0.110486 | 5433.11ms | 6661989 | 40 | 3.58879e+07 | 857308 | 0.00552924 | 1(Win) | true |
| Glaze | 3567.72 | 0.0864065 | 5568.07ms | 6661897 | 80 | 1.89408e+08 | 1.78077e+06 | 0.114376 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7390.35 | 0.0770089 | 5517.74ms | 6661989 | 160 | 7.01262e+07 | 859684 | 0.0370848 | 1(Win) | true |
| Glaze | 4035.6 | 0.0606137 | 5020.51ms | 6661897 | 160 | 1.45694e+08 | 1.57431e+06 | 0.187327 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2131.82 | 0.15864 | 5730.23ms | 500299 | 80 | 1.00849e+07 | 223810 | 0.0865935 | 1(Win) | true |
| Jsonifier (two-stage) | 1482.19 | 0.109952 | 8357.15ms | 500299 | 160 | 2.00437e+07 | 321904 | 0.0377273 | 2(Loss) | true |
| Glaze | 1274.52 | 0.191491 | 9771.05ms | 500299 | 80 | 4.11104e+07 | 374354 | 0.200875 | 3(Loss) | true |
| simdjson (ondemand) | 852.541 | 0.127878 | 7149.26ms | 500299 | 640 | 3.27792e+08 | 559647 | 0.0497771 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2608.75 | 0.173473 | 5626.44ms | 500299 | 160 | 1.61057e+07 | 182893 | 0.232221 | 1(Win) | true |
| Jsonifier (two-stage) | 1706.06 | 0.0509652 | 8179.99ms | 500299 | 1280 | 2.60032e+07 | 279663 | 0.0440006 | 2(Loss) | true |
| Glaze | 1426.36 | 0.158477 | 9539.87ms | 500299 | 80 | 2.24813e+07 | 334503 | 0.0227002 | 3(Loss) | true |
| simdjson (ondemand) | 916.5 | 0.050291 | 7145.55ms | 500299 | 640 | 4.38688e+07 | 520592 | 0.0599422 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9582.57 | 0.0190643 | 5088.92ms | 500299 | 40 | 3604.09 | 49790.6 | 0.0806228 | 1(Win) | true |
| Glaze | 2221.79 | 0.0840626 | 5569.06ms | 500299 | 640 | 2.08565e+07 | 214747 | 0.00460986 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9525.84 | 0.23031 | 5066.63ms | 500299 | 320 | 4.25821e+06 | 50087.2 | 0.155489 | 1(Win) | true |
| Glaze | 2353.08 | 0.200819 | 5315.21ms | 500299 | 160 | 2.65286e+07 | 202765 | 0.181912 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3203.92 | 0.11459 | 8888.21ms | 1151920 | 160 | 2.46998e+07 | 342879 | 0.121762 | 1(Win) | true |
| Jsonifier (two-stage) | 2761.81 | 0.0593908 | 5236.1ms | 1151920 | 640 | 3.57169e+07 | 397766 | 0.238573 | 2(Loss) | true |
| Glaze | 2011.9 | 0.208669 | 7062.77ms | 1151920 | 160 | 2.07714e+08 | 546029 | 0.144085 | 3(Loss) | true |
| simdjson (ondemand) | 1785.57 | 0.142475 | 7900.77ms | 1151920 | 40 | 3.07345e+07 | 615241 | 0.0189104 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3652.48 | 0.0698998 | 8963.88ms | 1151920 | 320 | 1.41439e+07 | 300770 | 0.126419 | 1(Win) | true |
| Jsonifier (two-stage) | 3096.9 | 0.17213 | 10104.1ms | 1151920 | 30 | 1.11847e+07 | 354728 | 0.379168 | 2(Loss) | true |
| Glaze | 2176.4 | 0.0936789 | 6900.45ms | 1151920 | 160 | 3.57742e+07 | 504758 | 0.0846778 | 3(Loss) | true |
| simdjson (ondemand) | 1892.86 | 0.134333 | 7933.14ms | 1151920 | 80 | 4.86252e+07 | 580369 | 0.105621 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14542.3 | 0.0598302 | 9556.45ms | 1439562 | 4890 | 1.56008e+07 | 94405.7 | 0.452948 | 1(Win) | true |
| Glaze | 4216.51 | 0.126326 | 8480.35ms | 1439584 | 80 | 1.35345e+07 | 325600 | 0.115526 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14694.8 | 0.063837 | 9497.9ms | 1439562 | 1280 | 4.55291e+06 | 93426 | 0.065193 | 1(Win) | true |
| Glaze | 4935.1 | 0.0703287 | 7255.97ms | 1439584 | 640 | 2.44978e+07 | 278190 | 0.0233694 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2376.9 | 0.0680954 | 2330.04ms | 56369 | 30 | 7115.67 | 22616.7 | 0.0797982 | 1(Win) | true |
| Jsonifier (two-stage) | 1683.6 | 0.0374838 | 3251.27ms | 56369 | 80 | 11459.9 | 31930.2 | 0.0328734 | 2(Loss) | true |
| Glaze | 1567.63 | 0.0557705 | 3535.64ms | 56369 | 4890 | 1.78859e+06 | 34292.3 | 0.222957 | 3(Loss) | true |
| simdjson (ondemand) | 765.406 | 0.0446724 | 7277.59ms | 56369 | 4890 | 4.81377e+06 | 70234.2 | 0.189336 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2913.38 | 0.107518 | 2057.68ms | 56369 | 320 | 125950 | 18452 | 0.315684 | 1(Win) | true |
| Jsonifier (two-stage) | 1930.36 | 0.112148 | 3119.38ms | 56369 | 1280 | 1.24853e+06 | 27848.5 | 0.272837 | 2(Loss) | true |
| Glaze | 1878.31 | 0.0789339 | 3017.47ms | 56369 | 2560 | 1.30651e+06 | 28620.2 | 0.0383153 | 3(Loss) | true |
| simdjson (ondemand) | 831.751 | 0.107074 | 6808.49ms | 56369 | 640 | 3.06505e+06 | 64631.9 | 0.282032 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11777.1 | 0.103258 | 464.621ms | 56369 | 40 | 888.61 | 4564.57 | 0.0440176 | 1(Win) | true |
| Glaze | 3394.62 | 0.100141 | 1607.07ms | 56369 | 30 | 7544.74 | 15836.1 | 0.0440116 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12361.6 | 0.101735 | 444.46ms | 56369 | 40 | 782.948 | 4348.77 | 0.125357 | 1(Win) | true |
| Glaze | 3921.54 | 0.0245622 | 1397.54ms | 56369 | 160 | 1813.93 | 13708.3 | 0.061558 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2412.01 | 0.0299851 | 3407.9ms | 83958 | 80 | 7926.25 | 33195.8 | 0.0222117 | 1(Win) | true |
| Jsonifier (two-stage) | 1975.61 | 0.0944808 | 4082.42ms | 83958 | 1280 | 1.8768e+06 | 40528.6 | 0.0479216 | 2(Loss) | true |
| Glaze | 1856.85 | 0.053175 | 4463.82ms | 83958 | 4890 | 2.57095e+06 | 43120.6 | 0.311147 | 3(Loss) | true |
| simdjson (ondemand) | 1113.32 | 0.0634467 | 7305.28ms | 83958 | 2560 | 5.33023e+06 | 71919.1 | 0.282657 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2742.26 | 0.0357116 | 3143.13ms | 83958 | 40 | 4348.97 | 29198 | 0.0553425 | 1(Win) | true |
| Jsonifier (two-stage) | 2496.39 | 0.051289 | 3405.71ms | 83958 | 4890 | 1.3233e+06 | 32073.8 | 0.0483041 | 2(Loss) | true |
| Glaze | 2164.48 | 0.116613 | 3841.89ms | 83958 | 1280 | 2.38188e+06 | 36992 | 0.0619393 | 3(Loss) | true |
| simdjson (ondemand) | 1204.58 | 0.048016 | 6992.16ms | 83958 | 4890 | 4.98123e+06 | 66470.3 | 0.912135 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12671 | 0.0388391 | 720.543ms | 94370 | 160 | 1217.59 | 7102.67 | 0.037588 | 1(Win) | true |
| Glaze | 3008.59 | 0.0881285 | 3014.63ms | 94370 | 2560 | 1.77916e+06 | 29913.8 | 0.0610015 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12967.3 | 0.0678438 | 749.833ms | 94370 | 4890 | 108417 | 6940.39 | 0.117138 | 1(Win) | true |
| Glaze | 3449.95 | 0.0588683 | 2655.82ms | 94370 | 4890 | 1.15323e+06 | 26086.9 | 0.0740933 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1745.15 | 0.142439 | 3013.3ms | 53331 | 640 | 1.10289e+06 | 29143.8 | 0.0623083 | 1(Win) | true |
| Jsonifier (two-stage) | 1578.3 | 0.101792 | 3402.04ms | 53331 | 1280 | 1.37726e+06 | 32224.8 | 0.122491 | 2(Loss) | true |
| Glaze | 1527.03 | 0.0602309 | 3323.14ms | 53331 | 4890 | 1.96794e+06 | 33306.7 | 0.326761 | 3(Loss) | true |
| simdjson (ondemand) | 887.954 | 0.0658087 | 5817.06ms | 53331 | 4890 | 6.94792e+06 | 57278.2 | 0.176344 | 4(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2365.14 | 0.0247965 | 2700.58ms | 53331 | 80 | 2274.68 | 21504.2 | 0.0147043 | 1(Win) | true |
| Jsonifier (two-stage) | 2060.93 | 0.0568377 | 3009.95ms | 53331 | 4890 | 962090 | 24678.4 | 0.0583114 | 2(Loss) | true |
| Glaze | 1871.99 | 0.14303 | 3149.6ms | 53331 | 640 | 966474 | 27169.2 | 0.185162 | 3(Loss) | true |
| simdjson (ondemand) | 1021.42 | 0.058173 | 5590.98ms | 53331 | 4890 | 4.10304e+06 | 49794 | 0.18383 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14192.9 | 0.0814146 | 399.289ms | 58581 | 4890 | 50220.7 | 3936.27 | 0.160376 | 1(Win) | true |
| Glaze | 4775.97 | 0.0867541 | 1180.28ms | 58581 | 2560 | 263640 | 11697.6 | 0.0409807 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15144.7 | 0.129645 | 375.376ms | 58581 | 30 | 686.162 | 3688.9 | 0.0370618 | 1(Win) | true |
| Glaze | 6016.17 | 0.149354 | 931.594ms | 58581 | 1280 | 246217 | 9286.17 | 0.320247 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1842.8 | 0.256099 | 3383.42ms | 65103 | 160 | 1.19119e+06 | 33691.6 | 0.037106 | 1(Win) | true |
| Jsonifier (two-stage) | 1770.86 | 0.019504 | 3603.51ms | 65103 | 80 | 3740.86 | 35060.4 | 0.0564345 | 2(Loss) | true |
| Glaze | 1702.63 | 0.054399 | 3730.39ms | 65103 | 4890 | 1.92422e+06 | 36465.5 | 0.0168253 | 3(Loss) | true |
| simdjson (ondemand) | 1066.48 | 0.0509475 | 6028.06ms | 65103 | 4890 | 4.30179e+06 | 58216.6 | 0.0578731 | 4(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2362.61 | 0.135654 | 3193.52ms | 65103 | 4890 | 6.21429e+06 | 26279 | 0.283251 | 1(Win) | true |
| Jsonifier (two-stage) | 2248.96 | 0.0797912 | 3293.83ms | 65103 | 2560 | 1.24219e+06 | 27607 | 0.198128 | 2(Loss) | true |
| Glaze | 2110.53 | 0.146739 | 3531.78ms | 65103 | 640 | 1.19259e+06 | 29417.8 | 0.0401119 | 3(Loss) | true |
| simdjson (ondemand) | 1214.77 | 0.285147 | 5644.07ms | 65103 | 320 | 6.79676e+06 | 51110.2 | 0.209816 | 4(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13553.3 | 0.0421063 | 560.726ms | 78778 | 160 | 871.64 | 5543.21 | 0.0570192 | 1(Win) | true |
| Glaze | 4022.9 | 0.0876258 | 1899.71ms | 78778 | 2560 | 685546 | 18675.2 | 0.0892518 | 2(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14779.4 | 0.0492918 | 527.041ms | 78778 | 160 | 1004.54 | 5083.34 | 0.0528968 | 1(Win) | true |
| Glaze | 5243.6 | 0.035744 | 1509.84ms | 78778 | 80 | 2098.2 | 14327.7 | 0.032357 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1869.03 | 0.05831 | 609.292ms | 11812 | 40 | 494.041 | 6027.1 | 0.0586585 | 1(Win) | true |
| Jsonifier (two-stage) | 1416.75 | 0.0527656 | 804.782ms | 11812 | 40 | 704.079 | 7951.15 | 0.0325006 | 2(Loss) | true |
| Glaze | 1060.85 | 0.226391 | 1066.76ms | 11812 | 640 | 369860 | 10618.7 | 0.00417914 | 3(Loss) | true |
| simdjson (ondemand) | 825.287 | 0.0623485 | 1378.92ms | 11812 | 4890 | 354159 | 13649.6 | 0.201109 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1963.71 | 0.0604001 | 636.574ms | 11812 | 40 | 480.204 | 5736.48 | 0.00653754 | 1(Win) | true |
| Jsonifier (two-stage) | 1470.68 | 0.0514824 | 805.746ms | 11812 | 40 | 621.994 | 7659.57 | 0.00250225 | 2(Loss) | true |
| Glaze | 1120.13 | 0.10607 | 1019.82ms | 11812 | 4890 | 556424 | 10056.7 | 0.468901 | 3(Loss) | true |
| simdjson (ondemand) | 874.831 | 0.0791248 | 1339.11ms | 11812 | 2560 | 265744 | 12876.5 | 0.0385182 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9047.2 | 0.0743999 | 128.25ms | 11812 | 640 | 549.215 | 1245.11 | 0.0355264 | 1(Win) | true |
| Glaze | 2366.36 | 0.0752865 | 495.648ms | 11812 | 40 | 513.785 | 4760.4 | 0.0741684 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9353.79 | 0.0764957 | 124.268ms | 11812 | 320 | 271.579 | 1204.3 | 0.00908119 | 1(Win) | true |
| Glaze | 2630.82 | 0.089305 | 439.831ms | 11812 | 30 | 438.671 | 4281.87 | 0.162186 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2730.43 | 0.0253204 | 897.809ms | 25388 | 160 | 806.597 | 8867.42 | 0.01431 | 1(Win) | true |
| Jsonifier (two-stage) | 2327.57 | 0.0616084 | 1046.31ms | 25388 | 4890 | 200836 | 10402.2 | 0.00711752 | 2(Loss) | true |
| Glaze | 1774.17 | 0.168255 | 1455.1ms | 25388 | 40 | 21089.2 | 13646.9 | 0.0580446 | 3(Loss) | true |
| simdjson (ondemand) | 1647.31 | 0.13431 | 1476.05ms | 25388 | 1280 | 498810 | 14697.8 | 0.0197004 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2830.75 | 0.0491878 | 896.095ms | 25388 | 40 | 707.994 | 8553.17 | 0.0207568 | 1(Win) | true |
| Jsonifier (two-stage) | 2391.63 | 0.0666305 | 1072.37ms | 25388 | 4890 | 222497 | 10123.6 | 0.102423 | 2(Loss) | true |
| Glaze | 1849.64 | 0.15564 | 1381.78ms | 25388 | 640 | 265648 | 13090.1 | 0.0870572 | 3(Loss) | true |
| simdjson (ondemand) | 1737.34 | 0.064739 | 1415.47ms | 25388 | 4890 | 398041 | 13936.2 | 0.104689 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12358.3 | 0.16039 | 246.93ms | 31235 | 80 | 1195.68 | 2410.38 | 0.173944 | 1(Win) | true |
| Glaze | 3830.58 | 0.0655112 | 784.238ms | 31235 | 30 | 778.585 | 7776.37 | 0.126719 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13476 | 0.0684977 | 222.871ms | 31235 | 160 | 366.802 | 2210.44 | 0.0240279 | 1(Win) | true |
| Glaze | 4394.12 | 0.0521366 | 688.243ms | 31235 | 30 | 374.754 | 6779.07 | 0.0191804 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2680.97 | 0.0520774 | 3870.27ms | 108313 | 4890 | 1.96873e+06 | 38529.1 | 0.0981648 | 1(Win) | true |
| Jsonifier (two-stage) | 1767.16 | 0.0336196 | 5924.88ms | 108313 | 30 | 11585.5 | 58452.6 | 0.0402197 | 2(Loss) | true |
| Glaze | 1506.03 | 0.0474494 | 6953.49ms | 108313 | 4890 | 5.17922e+06 | 68587.9 | 0.0490333 | 3(Loss) | true |
| simdjson (ondemand) | 687.418 | 0.0879442 | 7821.63ms | 108313 | 640 | 1.11767e+07 | 150266 | 0.0477686 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3155.42 | 0.103931 | 3547.15ms | 108313 | 1280 | 1.48167e+06 | 32735.9 | 0.012063 | 1(Win) | true |
| Jsonifier (two-stage) | 1966.12 | 0.277374 | 5610.69ms | 108313 | 160 | 3.39777e+06 | 52537.7 | 0.0945211 | 2(Loss) | true |
| Glaze | 1630 | 0.120653 | 6672.34ms | 108313 | 1280 | 7.48291e+06 | 63371.4 | 0.021178 | 3(Loss) | true |
| simdjson (ondemand) | 714.848 | 0.0495621 | 7584.95ms | 108313 | 2560 | 1.31303e+07 | 144500 | 0.0621998 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11841.2 | 0.044336 | 889.711ms | 108313 | 160 | 2393.33 | 8723.39 | 0.0168397 | 1(Win) | true |
| Glaze | 2342.37 | 0.105677 | 4504.63ms | 108313 | 1280 | 2.77986e+06 | 44098.7 | 0.0334472 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12126.6 | 0.0693146 | 863.154ms | 108313 | 30 | 1045.82 | 8518.1 | 0.0172212 | 1(Win) | true |
| Glaze | 2547.4 | 0.0535808 | 4205.17ms | 108313 | 4890 | 2.30831e+06 | 40549.3 | 0.0647629 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2928.37 | 0.0715875 | 6065.17ms | 183677 | 1280 | 2.34716e+06 | 59817.6 | 0.0759311 | 1(Win) | true |
| Jsonifier (two-stage) | 2526.42 | 0.344693 | 7027.4ms | 183677 | 80 | 4.56933e+06 | 69334.4 | 0.0660642 | 2(Loss) | true |
| Glaze | 1939.12 | 0.198147 | 9153.05ms | 183677 | 160 | 5.12621e+06 | 90333.9 | 0.206479 | 3(Loss) | true |
| simdjson (ondemand) | 1125.67 | 0.537525 | 8067.51ms | 183677 | 40 | 2.79864e+07 | 155613 | 0.109591 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3237.89 | 0.0573271 | 5703.26ms | 183677 | 4890 | 4.70342e+06 | 54099.4 | 0.000238611 | 1(Win) | true |
| Jsonifier (two-stage) | 2792.18 | 0.0949536 | 6664.2ms | 183677 | 640 | 2.27104e+06 | 62735.2 | 0.656232 | 2(Loss) | true |
| Glaze | 2078.74 | 0.109936 | 8780.09ms | 183677 | 640 | 5.49246e+06 | 84266.3 | 0.10722 | 3(Loss) | true |
| simdjson (ondemand) | 1179.7 | 0.216281 | 7840.36ms | 183677 | 40 | 4.12538e+06 | 148485 | 0.0426205 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15166.1 | 0.0851187 | 1358.36ms | 213963 | 2560 | 335752 | 13454.4 | 0.00196849 | 1(Win) | true |
| Glaze | 3234.14 | 0.139389 | 6552.13ms | 213963 | 320 | 2.47495e+06 | 63092.8 | 0.129339 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15325.4 | 0.161232 | 1345.63ms | 213963 | 40 | 18433.8 | 13314.5 | 0.0579903 | 1(Win) | true |
| Glaze | 3672.12 | 0.0743508 | 5608.33ms | 213963 | 1280 | 2.18487e+06 | 55567.7 | 0.069821 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 693.612 | 0.456874 | 8048.74ms | 1834197 | 80 | 1.06204e+10 | 2.52191e+06 | 0.975101 | 1(Win) | true |
| Jsonifier (two-stage) | 508.103 | 0.579225 | 9793.25ms | 1834197 | 160 | 6.36216e+10 | 3.44266e+06 | 0.462098 | 2(Loss) | true |
| Glaze | 492.221 | 0.0442682 | 5424.42ms | 1834197 | 80 | 1.97991e+08 | 3.55374e+06 | 0.123996 | 3(Loss) | true |
| simdjson (ondemand) | 400.159 | 0.205449 | 6611.41ms | 1834197 | 80 | 6.45242e+09 | 4.37132e+06 | 2.92193 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 783.376 | 0.437623 | 8640.21ms | 1834197 | 160 | 1.52781e+10 | 2.23293e+06 | 1.76228 | 1(Win) | true |
| Jsonifier (two-stage) | 600.378 | 0.430801 | 10056.7ms | 1834197 | 80 | 1.26034e+10 | 2.91354e+06 | 3.76157 | 2(Loss) | true |
| Glaze | 544.171 | 0.0569266 | 5383.22ms | 1834197 | 40 | 1.3394e+08 | 3.21448e+06 | 0.00120106 | 3(Loss) | true |
| simdjson (ondemand) | 432.16 | 0.577806 | 6818.53ms | 1834197 | 40 | 2.1879e+10 | 4.04763e+06 | 1.96006 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1334.9 | 0.575597 | 8375ms | 1922245 | 80 | 4.99854e+09 | 1.37328e+06 | 3.14171 | 1(Win) | true |
| Glaze | 823.17 | 0.32823 | 6567.47ms | 1833577 | 160 | 7.77849e+09 | 2.12427e+06 | 2.18669 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1422.27 | 1.24877 | 8218.56ms | 1922245 | 30 | 7.77209e+09 | 1.28892e+06 | 0.87353 | 1(Win) | true |
| Glaze | 840.472 | 0.363999 | 7035.62ms | 1833577 | 30 | 1.72057e+09 | 2.08054e+06 | 0.362393 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2002.47 | 0.275003 | 5242.5ms | 7351818 | 80 | 7.41686e+09 | 3.50129e+06 | 1.02911 | 1(Win) | true |
| Jsonifier (two-stage) | 1854.11 | 0.729861 | 5645.5ms | 7351818 | 40 | 3.0469e+10 | 3.78146e+06 | 1.41007 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 1272.56 | 0.68973 | 7722.83ms | 7351818 | 40 | 5.77636e+10 | 5.50958e+06 | 5.04919 | -(Loss) | false |
| simdjson (ondemand) | 1241.78 | 0.916254 | 8547.5ms | 7351818 | 30 | 8.0289e+10 | 5.64614e+06 | 0.73342 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2235.11 | 0.10096 | 5328.44ms | 7351818 | 30 | 3.00896e+08 | 3.13687e+06 | 0.110719 | 1(Win) | true |
| Jsonifier (two-stage) | 2187.54 | 0.0544466 | 6058.86ms | 7351818 | 30 | 9.13563e+07 | 3.20507e+06 | 0.42696 | 2(Loss) | true |
| Glaze | 1538.57 | 0.763362 | 7228ms | 7351818 | 30 | 3.63027e+10 | 4.55699e+06 | 2.03121 | 3(Loss) | true |
| simdjson (ondemand) | 1436.93 | 1.61193 | 8507.89ms | 7351818 | 40 | 2.47441e+11 | 4.87933e+06 | 2.80295 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5725.39 | 0.341831 | 5277.42ms | 10018896 | 40 | 1.3017e+09 | 1.66884e+06 | 0.651805 | 1(Win) | true |
| Glaze | 3135.43 | 0.189066 | 9766.15ms | 9930228 | 160 | 5.21758e+09 | 3.02038e+06 | 1.91956 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5734.88 | 0.262326 | 5450.37ms | 10018896 | 80 | 1.52814e+09 | 1.66608e+06 | 0.346448 | 1(Win) | true |
| Glaze | 3279.11 | 0.876763 | 8786.8ms | 9930228 | 80 | 5.12935e+10 | 2.88804e+06 | 1.39632 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 618.08 | 1.52756 | 8730.14ms | 1834197 | 40 | 7.47585e+10 | 2.8301e+06 | 7.66985 | -(Win) | false |
| Jsonifier (two-stage) | 495.519 | 0.806752 | 5209.28ms | 1834197 | 80 | 6.48845e+10 | 3.53009e+06 | 1.33329 | 2(Loss) | true |
| Glaze | 404.758 | 0.483974 | 6201.22ms | 1834197 | 80 | 3.49972e+10 | 4.32166e+06 | 1.4776 | 3(Loss) | true |
| simdjson (ondemand) | 372.639 | 0.634936 | 6968.88ms | 1834197 | 40 | 3.55332e+10 | 4.69415e+06 | 0.928915 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 675.364 | 0.822509 | 9199.83ms | 1834197 | 30 | 1.3615e+10 | 2.59005e+06 | 0.559352 | 1(Win) | true |
| Jsonifier (two-stage) | 608.411 | 0.460649 | 10233.5ms | 1834197 | 40 | 7.01614e+09 | 2.87508e+06 | 1.06531 | 2(Loss) | true |
| Glaze | 492.462 | 0.61065 | 6031.03ms | 1834197 | 80 | 3.76376e+10 | 3.55201e+06 | 1.29946 | 3(Loss) | true |
| simdjson (ondemand) | 416.156 | 0.579332 | 6982.43ms | 1834197 | 40 | 2.37189e+10 | 4.2033e+06 | 0.193641 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1484.82 | 0.209782 | 7876.31ms | 1922245 | 320 | 2.14661e+09 | 1.23462e+06 | 0.370398 | 1(Win) | true |
| Glaze | 819.796 | 0.578043 | 7049.81ms | 1833577 | 30 | 4.56067e+09 | 2.13301e+06 | 3.0392 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1482.17 | 0.266066 | 7790.54ms | 1922245 | 320 | 3.46535e+09 | 1.23683e+06 | 0.423826 | 1(Win) | true |
| Glaze | 824.481 | 0.685801 | 6596.38ms | 1833577 | 40 | 8.46241e+09 | 2.12089e+06 | 0.833633 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1875.01 | 0.352817 | 5686.61ms | 7351818 | 80 | 1.39242e+10 | 3.7393e+06 | 0.861564 | 1(Win) | true |
| Jsonifier (two-stage) | 1818.42 | 0.170151 | 5916.17ms | 7351818 | 80 | 3.44318e+09 | 3.85568e+06 | 0.0477411 | 2(Loss) | true |
| Glaze | 1395.8 | 0.624595 | 7621.45ms | 7351818 | 40 | 3.93734e+10 | 5.02311e+06 | 2.69724 | 3(Loss) | true |
| simdjson (ondemand) | 1352.21 | 0.332244 | 7771.97ms | 7351818 | 80 | 2.37413e+10 | 5.18502e+06 | 1.79167 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2080.8 | 0.569882 | 5706.38ms | 7351818 | 40 | 1.47489e+10 | 3.3695e+06 | 1.28103 | 1(Win) | true |
| Jsonifier | 2051.38 | 0.433925 | 5719.53ms | 7351818 | 80 | 1.75961e+10 | 3.41781e+06 | 0.256177 | 2(Loss) | true |
| Glaze | 1501.86 | 0.414181 | 7550.82ms | 7351818 | 40 | 1.49545e+10 | 4.66838e+06 | 0.777244 | 3(Loss) | true |
| simdjson (ondemand) | 1476.28 | 0.193123 | 7763.92ms | 7351818 | 80 | 6.72995e+09 | 4.74926e+06 | 0.677549 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5114.55 | 0.32035 | 5964.53ms | 10018896 | 30 | 1.07447e+09 | 1.86815e+06 | 4.72403 | 1(Win) | true |
| Glaze | 2793.17 | 0.240223 | 5158.88ms | 9930228 | 30 | 1.99009e+09 | 3.39048e+06 | 0.253171 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 5287.24 | 1.11135 | 5462.03ms | 10018896 | 40 | 1.61341e+10 | 1.80714e+06 | 6.79589 | -(Win) | false |
| Glaze | 3203.35 | 0.188291 | 9415.11ms | 9930228 | 30 | 9.29585e+08 | 2.95634e+06 | 0.541739 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1107.6 | 0.717941 | 5074.59ms | 461466 | 320 | 2.604e+09 | 397335 | 1.56654 | 1(Win) | true |
| Jsonifier (two-stage) | 916.202 | 1.002 | 6258.76ms | 461466 | 40 | 9.26606e+08 | 480340 | 2.00398 | 2(Loss) | true |
| Glaze | 860.35 | 0.154696 | 7223.42ms | 461466 | 30 | 1.87848e+07 | 511522 | 0.660553 | 3(Loss) | true |
| simdjson (ondemand) | 630.86 | 0.563661 | 8856.31ms | 461466 | 30 | 4.63842e+08 | 697600 | 0.00440577 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1714.32 | 0.248733 | 9094.16ms | 461466 | 1280 | 5.21886e+08 | 256714 | 1.4001 | 1(Win) | true |
| Jsonifier (two-stage) | 1115.51 | 1.14064 | 5832.87ms | 461466 | 40 | 8.10013e+08 | 394519 | 2.0184 | 2(Loss) | true |
| Glaze | 938.687 | 0.43721 | 7171.33ms | 461466 | 80 | 3.36131e+08 | 468834 | 0.434821 | 3(Loss) | true |
| simdjson (ondemand) | 751.739 | 0.495454 | 8451.51ms | 461466 | 80 | 6.73041e+08 | 585427 | 0.70582 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8757.09 | 0.328103 | 4923.51ms | 461466 | 2560 | 6.96019e+07 | 50255.1 | 1.80044 | 1(Win) | true |
| Glaze | 2747.08 | 0.118515 | 8474.56ms | 461466 | 320 | 1.15355e+07 | 160202 | 0.0770205 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8374.14 | 0.220982 | 5219.33ms | 461466 | 2560 | 3.45265e+07 | 52553.2 | 0.0235361 | 1(Win) | true |
| Glaze | 2970.06 | 0.307283 | 8615.87ms | 461466 | 40 | 8.29253e+06 | 148175 | 0.275268 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1630.49 | 0.260153 | 5638.99ms | 728486 | 320 | 3.93199e+08 | 426091 | 0.645786 | 1(Win) | true |
| Jsonifier (two-stage) | 1362.12 | 0.255699 | 6557.13ms | 728486 | 160 | 2.72138e+08 | 510042 | 0.0861565 | 2(Loss) | true |
| Glaze | 1037.81 | 0.532082 | 8676.12ms | 728486 | 80 | 1.01498e+09 | 669429 | 0.868995 | 3(Loss) | true |
| simdjson (ondemand) | 916.637 | 0.55564 | 9963.66ms | 728486 | 30 | 5.32054e+08 | 757921 | 0.301263 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2053.52 | 0.22455 | 5422.21ms | 728486 | 320 | 1.84681e+08 | 338316 | 0.701107 | 1(Win) | true |
| Jsonifier (two-stage) | 1689.02 | 0.0985939 | 6319.81ms | 728486 | 640 | 1.05257e+08 | 411325 | 0.0454835 | 2(Loss) | true |
| Glaze | 1329.91 | 0.164165 | 7901.91ms | 728486 | 320 | 2.35349e+08 | 522396 | 0.961892 | 3(Loss) | true |
| simdjson (ondemand) | 899.491 | 0.889088 | 5213.04ms | 728486 | 320 | 1.509e+10 | 772368 | 0.938784 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9333.34 | 0.278317 | 8117.74ms | 837491 | 1280 | 7.26067e+07 | 85574.2 | 0.515572 | 1(Win) | true |
| Glaze | 2736.45 | 0.300655 | 7727.14ms | 837491 | 1280 | 9.85671e+08 | 291872 | 2.94693 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10235.5 | 0.506908 | 7009.05ms | 837491 | 640 | 1.00133e+08 | 78031.4 | 1.6011 | 1(Win) | true |
| Glaze | 2803.07 | 0.335197 | 7099.31ms | 837491 | 640 | 5.8381e+08 | 284935 | 0.710323 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4880.52 | 0.330639 | 9668.7ms | 466906 | 1280 | 1.16478e+08 | 91235.4 | 0.167802 | 1(Win) | true |
| Jsonifier | 4751.19 | 0.466096 | 9844.51ms | 466906 | 640 | 1.22119e+08 | 93718.9 | 0.268301 | 2(Loss) | true |
| simdjson (ondemand) | 4098.26 | 0.0568142 | 5983.39ms | 466906 | 2560 | 9.7547e+06 | 108650 | 0.0833355 | 3(Loss) | true |
| Glaze | 2131.25 | 0.31888 | 5503.54ms | 466906 | 640 | 2.8407e+08 | 208927 | 1.61029 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4718.65 | 1.77662 | 5104.03ms | 466906 | 30 | 8.43209e+07 | 94365.3 | 0.176202 | 1(Win) | true |
| Jsonifier (two-stage) | 4388.54 | 0.49688 | 5076.71ms | 466906 | 640 | 1.62668e+08 | 101463 | 0.0145825 | 2(Loss) | true |
| simdjson (ondemand) | 4161.75 | 0.15635 | 5624.74ms | 466906 | 640 | 1.79094e+07 | 106992 | 0.152442 | 3(Loss) | true |
| Glaze | 2012.58 | 0.321583 | 5595.5ms | 466906 | 640 | 3.23978e+08 | 221246 | 1.75491 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5737.52 | 0.142569 | 5735.06ms | 631514 | 160 | 3.58334e+06 | 104968 | 0.0568121 | 1(Win) | true |
| Jsonifier (two-stage) | 5095.49 | 0.322864 | 6332.45ms | 631514 | 2560 | 3.72796e+08 | 118194 | 0.706808 | 2(Loss) | true |
| simdjson (ondemand) | 3970.02 | 0.43247 | 7428.43ms | 631514 | 640 | 2.75469e+08 | 151702 | 2.51429 | 3(Loss) | true |
| Glaze | 2750.86 | 0.124455 | 5728.22ms | 631514 | 160 | 1.18789e+07 | 218934 | 0.0219006 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5162.19 | 0.243494 | 6230.86ms | 631514 | 2560 | 2.06593e+08 | 116667 | 0.136351 | 1(Win) | true |
| Jsonifier | 4320.45 | 0.682605 | 5946.8ms | 631514 | 160 | 1.44866e+08 | 139397 | 0.149869 | 2(Loss) | true |
| simdjson (ondemand) | 3961.36 | 0.449513 | 7146.41ms | 631514 | 320 | 1.49456e+08 | 152033 | 2.65005 | 3(Loss) | true |
| Glaze | 2794.97 | 0.126973 | 5568.17ms | 631514 | 160 | 1.19773e+07 | 215479 | 0.00257282 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2046.16 | 0.210073 | 5454.12ms | 466906 | 80 | 1.6719e+07 | 217616 | 0.100931 | 1(Win) | true |
| Jsonifier (two-stage) | 1712.25 | 0.674396 | 6371.93ms | 466906 | 160 | 4.92125e+08 | 260054 | 1.28198 | 2(Loss) | true |
| Glaze | 1633.42 | 0.725888 | 6857.91ms | 466906 | 80 | 3.13252e+08 | 272604 | 0.239398 | 3(Loss) | true |
| simdjson (ondemand) | 849.321 | 0.0866582 | 6908.45ms | 466906 | 160 | 3.30259e+07 | 524273 | 0.120868 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2432.93 | 1.2148 | 10050ms | 466906 | 40 | 1.97729e+08 | 183021 | 0.404553 | 1(Win) | true |
| Jsonifier (two-stage) | 2171.62 | 0.344733 | 6033.33ms | 466906 | 30 | 1.49892e+07 | 205043 | 0.776331 | 2(Loss) | true |
| Glaze | 2108.51 | 0.293389 | 6661.8ms | 466906 | 320 | 1.22842e+08 | 211180 | 1.08891 | 3(Loss) | true |
| simdjson (ondemand) | 917.59 | 0.0966784 | 6893.68ms | 466906 | 160 | 3.5216e+07 | 485267 | 0.0196387 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14090.2 | 0.0764128 | 3261.94ms | 475954 | 4890 | 2.96303e+06 | 32214.2 | 0.275383 | 1(Win) | true |
| Glaze | 4516.29 | 0.0560368 | 5325.21ms | 475954 | 2560 | 8.11992e+06 | 100504 | 0.0759852 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14192.1 | 0.0768827 | 3205.98ms | 475954 | 4890 | 2.95668e+06 | 31983 | 0.0455219 | 1(Win) | true |
| Glaze | 5029.01 | 0.120168 | 9234.37ms | 475954 | 320 | 3.76441e+06 | 90257.4 | 0.163484 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2414.63 | 0.155485 | 6734.25ms | 631514 | 160 | 2.40637e+07 | 249421 | 0.0732533 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1985.84 | 0.677918 | 8797.06ms | 631514 | 80 | 3.3816e+08 | 303277 | 0.0303715 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1963.94 | 0.285069 | 7972.67ms | 631514 | 30 | 2.29261e+07 | 306658 | 1.10449 | 2(Tie) | true |
| simdjson (ondemand) | 919.204 | 0.818542 | 8189.94ms | 631514 | 320 | 9.20395e+09 | 655196 | 1.10231 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2708.55 | 0.695246 | 6507.73ms | 631514 | 160 | 3.82375e+08 | 222355 | 2.09245 | 1(Win) | true |
| Glaze | 2298.18 | 0.12554 | 7757.71ms | 631514 | 160 | 1.73173e+07 | 262059 | 0.430733 | 2(Loss) | true |
| Jsonifier (two-stage) | 2134.91 | 1.22546 | 7910.04ms | 631514 | 80 | 9.56088e+08 | 282101 | 2.06364 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1118.96 | 0.221175 | 7519.48ms | 631514 | 640 | 9.06964e+08 | 538231 | 5.29213 | -(Loss) | false |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14897.5 | 0.0770022 | 4640.51ms | 716365 | 1280 | 1.5961e+06 | 45858.7 | 0.0161441 | 1(Win) | true |
| Glaze | 4145.1 | 0.0446619 | 8717.99ms | 716365 | 2560 | 1.38712e+07 | 164816 | 0.0181431 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15122 | 0.0723268 | 5020.66ms | 716365 | 30 | 32030.9 | 45177.8 | 0.196024 | 1(Win) | true |
| Glaze | 4803.05 | 0.186617 | 7426.86ms | 716365 | 80 | 5.63671e+06 | 142238 | 0.0725101 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1601.1 | 0.0766511 | 171.55ms | 2632 | 320 | 462.085 | 1567.72 | 0.0672209 | 1(Win) | true |
| Jsonifier (two-stage) | 1397.71 | 0.140426 | 214.753ms | 2632 | 40 | 254.387 | 1795.85 | 0.00278427 | 2(Loss) | true |
| Glaze | 918.482 | 0.198828 | 275.065ms | 2632 | 4890 | 144377 | 2732.85 | 0.371504 | 3(Loss) | true |
| simdjson (ondemand) | 678.714 | 0.51841 | 329.291ms | 2632 | 640 | 235247 | 3698.28 | 0.560574 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2092.43 | 0.0877476 | 149.207ms | 2632 | 320 | 354.561 | 1199.6 | 0.0122422 | 1(Win) | true |
| Jsonifier (two-stage) | 1765.33 | 0.147649 | 169.108ms | 2632 | 2560 | 11282.9 | 1421.87 | 0.0548601 | 2(Loss) | true |
| Glaze | 1422.62 | 0.233939 | 204.498ms | 2632 | 4890 | 83312.3 | 1764.4 | 2.43151 | 3(Loss) | true |
| simdjson (ondemand) | 1078.3 | 0.675199 | 274.634ms | 2632 | 30 | 7410.99 | 2327.8 | 0.0601788 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7009.66 | 0.717031 | 43.8143ms | 2632 | 160 | 1054.81 | 358.087 | 1.49916 | 1(Win) | true |
| Glaze | 2540.51 | 1.01144 | 102.441ms | 2632 | 160 | 15978.3 | 988.019 | 0.476057 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 7484.48 | 0.542868 | 41.137ms | 2632 | 4890 | 16208.6 | 335.37 | 7.84018 | -(Win) | false |
| Glaze | 3523.24 | 0.94662 | 83.396ms | 2632 | 30 | 1364.46 | 712.433 | 0.768505 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1441.94 | 0.396262 | 249.074ms | 3370 | 640 | 49923.9 | 2228.85 | 0.761369 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1435.73 | 0.548757 | 238.404ms | 3370 | 40 | 6035.79 | 2238.5 | 0.0788597 | 1(Tie) | true |
| Glaze | 1124.89 | 0.359764 | 297.695ms | 3370 | 4890 | 516640 | 2857.08 | 0.675129 | 3(Loss) | true |
| simdjson (ondemand) | 935.763 | 0.557091 | 356.373ms | 3370 | 640 | 234294 | 3434.5 | 1.34707 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2084.15 | 0.0378272 | 181.766ms | 3370 | 640 | 217.765 | 1542.06 | 0.0170256 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.17 | 0.444983 | 237.128ms | 3370 | 40 | 2472.07 | 1766.67 | 0.0749434 | 2(Loss) | true |
| Glaze | 1676.3 | 0.392887 | 235.686ms | 3370 | 640 | 36313.9 | 1917.25 | 3.55293 | 3(Loss) | true |
| simdjson (ondemand) | 1313.94 | 0.374404 | 268.756ms | 3370 | 640 | 53674.6 | 2445.99 | 0.34954 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8212.78 | 0.379384 | 50.9311ms | 3643 | 320 | 824.228 | 423.028 | 1.06486 | 1(Win) | true |
| Glaze | 2804.18 | 0.32855 | 130.13ms | 3682 | 2560 | 43331 | 1252.21 | 0.389008 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8918.01 | 1.51266 | 47.8225ms | 3643 | 40 | 1389.07 | 389.575 | 1.64594 | 1(Win) | true |
| Glaze | 3638.03 | 0.299512 | 105.038ms | 3682 | 30 | 250.717 | 965.2 | 0.311785 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 575.979 | 1.25467 | 763.216ms | 4630 | 80 | 740112 | 7666.1 | 0.0622484 | 1(Win) | true |
| Jsonifier (two-stage) | 546.61 | 0.390819 | 827.687ms | 4630 | 640 | 637880 | 8077.99 | 0.729163 | 2(Loss) | true |
| simdjson (ondemand) | 411.294 | 0.37449 | 1179.69ms | 4630 | 640 | 1.03447e+06 | 10735.7 | 0.350645 | 3(Loss) | true |
| Glaze | 391.746 | 0.278897 | 1104.42ms | 4630 | 2560 | 2.52977e+06 | 11271.4 | 0.386517 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 717.469 | 0.311989 | 782.751ms | 4630 | 2560 | 943788 | 6154.29 | 1.17477 | 1(Win) | true |
| Jsonifier (two-stage) | 642.475 | 0.751492 | 853.934ms | 4630 | 160 | 426793 | 6872.66 | 0.22394 | 2(Loss) | true |
| Glaze | 528.279 | 0.187824 | 1062.76ms | 4630 | 30 | 7393.67 | 8358.3 | 0.233045 | 3(Loss) | true |
| simdjson (ondemand) | 436.966 | 0.944728 | 1159.3ms | 4630 | 160 | 1.45814e+06 | 10104.9 | 3.18148 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2552.17 | 0.152959 | 186.208ms | 4630 | 1280 | 8964.08 | 1730.1 | 0.157212 | 1(Win) | true |
| Glaze | 1294.38 | 0.286595 | 338.649ms | 4630 | 2560 | 244692 | 3411.31 | 0.803536 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2294.71 | 0.296864 | 203.148ms | 4630 | 2560 | 83534.2 | 1924.22 | 0.290102 | 1(Win) | true |
| Glaze | 1451.17 | 0.942278 | 275.012ms | 4630 | 160 | 131523 | 3042.72 | 1.7787 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1488.74 | 0.0387149 | 853.929ms | 11579 | 160 | 1319.41 | 7417.41 | 0.0520162 | 1(Win) | true |
| Jsonifier (two-stage) | 1266.86 | 0.12036 | 877.297ms | 11579 | 4890 | 538219 | 8716.5 | 0.121944 | 2(Loss) | true |
| simdjson (ondemand) | 968.367 | 0.400645 | 1128.45ms | 11579 | 640 | 1.33586e+06 | 11403.3 | 0.190342 | 3(Loss) | true |
| Glaze | 949.52 | 0.643064 | 1226.66ms | 11579 | 160 | 894874 | 11629.7 | 0.0989483 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1432.4 | 0.304479 | 912.566ms | 11579 | 2560 | 1.41048e+06 | 7709.15 | 0.175241 | 1(Win) | true |
| Jsonifier | 1373.99 | 0.266083 | 893.296ms | 11579 | 2560 | 1.17071e+06 | 8036.9 | 1.47932 | 2(Loss) | true |
| simdjson (ondemand) | 1097.77 | 0.474334 | 1117.08ms | 11579 | 320 | 728514 | 10059.1 | 0.155511 | 3(Loss) | true |
| Glaze | 1010.3 | 0.621884 | 1166.35ms | 11579 | 640 | 2.95694e+06 | 10930 | 1.20554 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7059.88 | 0.0579368 | 204.691ms | 14795 | 320 | 429.037 | 1998.56 | 0.0849888 | 1(Win) | true |
| Glaze | 3367.16 | 0.100765 | 438.352ms | 14795 | 4890 | 87182.2 | 4190.36 | 0.202873 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7193.47 | 0.0316025 | 203.646ms | 14795 | 640 | 245.91 | 1961.45 | 0.0329106 | 1(Win) | true |
| Glaze | 3906.06 | 0.0353482 | 369.038ms | 14795 | 320 | 521.719 | 3612.24 | 0.0797863 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1244.57 | 0.249336 | 266.49ms | 3223 | 40 | 1516.74 | 2469.68 | 0.234385 | 1(Win) | true |
| Jsonifier (two-stage) | 1010.75 | 0.0807705 | 308.885ms | 3223 | 4890 | 29501.5 | 3040.99 | 0.0213102 | 2(Loss) | true |
| Glaze | 828.463 | 0.122559 | 368.476ms | 3223 | 4890 | 101106 | 3710.12 | 0.402251 | 3(Loss) | true |
| simdjson (ondemand) | 683.96 | 0.272604 | 454.777ms | 3223 | 1280 | 192102 | 4493.96 | 0.341882 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1921.96 | 0.0556164 | 216.802ms | 3223 | 640 | 506.314 | 1599.25 | 0.0698081 | 1(Win) | true |
| Jsonifier (two-stage) | 1422.04 | 0.0569639 | 273.933ms | 3223 | 320 | 485.115 | 2161.46 | 0.0248736 | 2(Loss) | true |
| Glaze | 1169.04 | 0.264407 | 315.174ms | 3223 | 40 | 1933.17 | 2629.25 | 0.117408 | 3(Loss) | true |
| simdjson (ondemand) | 872.223 | 0.112651 | 405.341ms | 3223 | 160 | 2521.47 | 3523.97 | 0.174215 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8139.49 | 0.103193 | 40.7351ms | 3223 | 1280 | 194.375 | 377.627 | 0.0242113 | 1(Win) | true |
| Glaze | 1959.33 | 0.224095 | 160.977ms | 3223 | 40 | 494.346 | 1568.75 | 0.130507 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9307.87 | 0.49128 | 37.9061ms | 3223 | 80 | 210.556 | 330.225 | 0.937453 | 1(Win) | true |
| Glaze | 2182.32 | 0.235695 | 147.059ms | 3223 | 2560 | 28211.5 | 1408.45 | 0.0958306 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1789.64 | 0.108235 | 318.513ms | 5839 | 80 | 907.341 | 3111.53 | 0.0353649 | 1(Win) | true |
| Jsonifier (two-stage) | 1641.82 | 0.12623 | 347.107ms | 5839 | 30 | 549.885 | 3391.67 | 0.0442065 | 2(Loss) | true |
| Glaze | 1288.3 | 0.0743404 | 460.528ms | 5839 | 4890 | 50489.7 | 4322.37 | 0.949655 | 3(Loss) | true |
| simdjson (ondemand) | 1195.65 | 0.113587 | 471.578ms | 5839 | 80 | 2238.79 | 4657.29 | 0.0889183 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2491.08 | 0.170638 | 279.18ms | 5839 | 40 | 581.984 | 2235.38 | 0.0964604 | 1(Win) | true |
| Jsonifier (two-stage) | 2233.2 | 0.0998997 | 303.723ms | 5839 | 4890 | 30343 | 2493.51 | 0.128349 | 2(Loss) | true |
| Glaze | 1628.72 | 0.0838445 | 397.172ms | 5839 | 160 | 1314.78 | 3418.94 | 0.0955155 | 3(Loss) | true |
| simdjson (ondemand) | 1473.44 | 0.170745 | 427.294ms | 5839 | 2560 | 106598 | 3779.25 | 0.0682127 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10283.2 | 0.273951 | 72.5191ms | 6938 | 640 | 1988.54 | 643.436 | 0.687306 | 1(Win) | true |
| Glaze | 2897.72 | 0.0425227 | 233.638ms | 6960 | 640 | 607.194 | 2290.62 | 0.0343229 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12969.7 | 0.202923 | 54.2807ms | 6938 | 320 | 342.941 | 510.156 | 0.0979132 | 1(Win) | true |
| Glaze | 3253.56 | 0.140658 | 213.948ms | 6960 | 2560 | 21080.1 | 2040.1 | 0.128219 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2153.37 | 0.135153 | 223.954ms | 4857 | 80 | 676.149 | 2151.05 | 0.147821 | 1(Win) | true |
| Jsonifier (two-stage) | 1672.49 | 0.063093 | 289.989ms | 4857 | 320 | 977.059 | 2769.52 | 0.122463 | 2(Loss) | true |
| Glaze | 1390.41 | 0.135851 | 367.584ms | 4857 | 320 | 6554.31 | 3331.39 | 0.0904396 | 3(Loss) | true |
| simdjson (ondemand) | 651.467 | 0.0738996 | 724.395ms | 4857 | 160 | 4417.29 | 7110.11 | 0.0410339 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2614.94 | 0.0713872 | 192.358ms | 4857 | 320 | 511.685 | 1771.36 | 0.00105852 | 1(Win) | true |
| Jsonifier (two-stage) | 1868.18 | 0.0715246 | 257.197ms | 4857 | 160 | 503.188 | 2479.42 | 0.033011 | 2(Loss) | true |
| Glaze | 1836.16 | 0.150152 | 270.784ms | 4857 | 320 | 4591.25 | 2522.66 | 0.0516301 | 3(Loss) | true |
| simdjson (ondemand) | 608.263 | 0.308449 | 758.666ms | 4857 | 2560 | 1.41241e+06 | 7615.12 | 0.140281 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10933.9 | 0.162295 | 47.9639ms | 4857 | 640 | 302.535 | 423.636 | 0.141462 | 1(Win) | true |
| Glaze | 3151.65 | 0.0837264 | 151.351ms | 4857 | 320 | 484.547 | 1469.71 | 0.0437821 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11923.4 | 0.198524 | 42.0268ms | 4857 | 640 | 380.66 | 388.478 | 0.187079 | 1(Win) | true |
| Glaze | 4009.83 | 0.0757374 | 122.412ms | 4857 | 640 | 489.874 | 1155.16 | 0.0327443 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2206.06 | 0.0884161 | 299.222ms | 6701 | 80 | 524.804 | 2896.82 | 0.0733024 | 1(Win) | true |
| Jsonifier (two-stage) | 1895.49 | 0.0954415 | 345.646ms | 6701 | 2560 | 26506.4 | 3371.46 | 0.217428 | 2(Loss) | true |
| Glaze | 1615.06 | 0.101672 | 404.578ms | 6701 | 320 | 5179.17 | 3956.87 | 0.0552351 | 3(Loss) | true |
| simdjson (ondemand) | 875.252 | 0.125941 | 766.019ms | 6701 | 1280 | 108233 | 7301.41 | 0.253525 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2576.65 | 0.0944981 | 265.289ms | 6701 | 80 | 439.445 | 2480.19 | 0.00352783 | 1(Win) | true |
| Jsonifier (two-stage) | 2409.69 | 0.0698989 | 282.656ms | 6701 | 160 | 549.817 | 2652.03 | 0.0619424 | 2(Loss) | true |
| Glaze | 2099.08 | 0.408267 | 339.935ms | 6701 | 30 | 4634.81 | 3044.47 | 1.48222 | 3(Loss) | true |
| simdjson (ondemand) | 940.008 | 0.111397 | 679.277ms | 6701 | 80 | 4588.35 | 6798.43 | 0.486289 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11301.7 | 0.262823 | 65.3587ms | 7376 | 160 | 428.156 | 622.413 | 0.168983 | 1(Win) | true |
| Glaze | 3031.62 | 0.0398616 | 239.941ms | 7376 | 640 | 547.498 | 2320.31 | 0.0666223 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12471.5 | 0.0747367 | 62.5185ms | 7376 | 2560 | 454.899 | 564.031 | 0.201957 | 1(Win) | true |
| Glaze | 3595.84 | 0.0749852 | 199.857ms | 7376 | 160 | 344.28 | 1956.23 | 0.0533267 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1549.93 | 0.0821786 | 106.454ms | 1691 | 320 | 233.956 | 1040.48 | 0.538601 | 1(Win) | true |
| Glaze | 1375.27 | 0.0865463 | 120.311ms | 1691 | 4890 | 5036.35 | 1172.61 | 0.298168 | 2(Loss) | true |
| Jsonifier (two-stage) | 1363.17 | 0.196909 | 120.046ms | 1691 | 2560 | 13891.8 | 1183.03 | 0.507457 | 3(Loss) | true |
| simdjson (ondemand) | 1000.72 | 0.283741 | 197.978ms | 1691 | 40 | 836.308 | 1611.5 | 0.405834 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2073.9 | 0.28508 | 95.1999ms | 1691 | 80 | 393.129 | 777.6 | 0.336441 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1801.22 | 0.135984 | 107.435ms | 1691 | 1280 | 1897.32 | 895.32 | 0.0381469 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1794.21 | 0.193612 | 108.937ms | 1691 | 320 | 969.072 | 898.816 | 0.157747 | 2(Tie) | true |
| simdjson (ondemand) | 1263.97 | 0.0450881 | 143.801ms | 1691 | 2560 | 847.181 | 1275.87 | 0.186686 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9114.3 | 0.145397 | 23.9735ms | 1996 | 4890 | 450.917 | 208.851 | 0.239115 | 1(Win) | true |
| Glaze | 3567.61 | 0.191845 | 59.4672ms | 1996 | 4890 | 5123.61 | 533.559 | 0.101673 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12366.8 | 0.249787 | 18.4851ms | 1996 | 2560 | 378.433 | 153.923 | 0.26374 | 1(Win) | true |
| Glaze | 4873.92 | 0.206855 | 42.1501ms | 1996 | 640 | 417.709 | 390.555 | 0.0140006 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1718.14 | 0.0337228 | 123.355ms | 2158 | 2560 | 417.707 | 1197.82 | 0.0575594 | 1(Win) | true |
| Jsonifier (two-stage) | 1636.41 | 0.0409219 | 129.909ms | 2158 | 1280 | 339.033 | 1257.65 | 0.0384669 | 2(Loss) | true |
| Glaze | 1552.55 | 0.110213 | 139.296ms | 2158 | 4890 | 10437.3 | 1325.58 | 0.0446536 | 3(Loss) | true |
| simdjson (ondemand) | 1275.52 | 0.21542 | 167.097ms | 2158 | 80 | 966.481 | 1613.49 | 0.059689 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2238.77 | 0.0838339 | 113.173ms | 2158 | 320 | 190.053 | 919.269 | 0.172308 | 1(Win) | true |
| Jsonifier (two-stage) | 2077.52 | 0.153198 | 115.744ms | 2158 | 4890 | 11262.3 | 990.617 | 0.447326 | 2(Loss) | true |
| Glaze | 1974.5 | 0.10641 | 121.798ms | 2158 | 640 | 787.291 | 1042.3 | 0.1354 | 3(Loss) | true |
| simdjson (ondemand) | 1575.52 | 0.283369 | 147.395ms | 2158 | 1280 | 17537.6 | 1306.26 | 0.628734 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10332.1 | 1.04857 | 32.9409ms | 2866 | 80 | 615.543 | 264.538 | 1.18091 | 1(Win) | true |
| Glaze | 3175.97 | 0.0666258 | 89.7125ms | 2866 | 1280 | 420.818 | 860.597 | 0.021792 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14128.2 | 0.288634 | 22.3014ms | 2866 | 1280 | 399.101 | 193.459 | 0.0828544 | 1(Win) | true |
| Glaze | 4401.41 | 0.0744928 | 68.3604ms | 2866 | 1280 | 273.91 | 620.99 | 0.320195 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1769.49 | 0.0487446 | 243.146ms | 4390 | 320 | 425.633 | 2366.01 | 0.0601321 | 1(Win) | true |
| Jsonifier (two-stage) | 1361.07 | 0.107127 | 315.8ms | 4390 | 40 | 434.333 | 3075.97 | 0.101491 | 2(Loss) | true |
| Glaze | 1010.33 | 0.109307 | 426.412ms | 4390 | 2560 | 52522.2 | 4143.83 | 0.086338 | 3(Loss) | true |
| simdjson (ondemand) | 804.344 | 0.0839988 | 551.622ms | 4390 | 4890 | 93476 | 5205.03 | 0.892057 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1931.17 | 0.0964766 | 231.268ms | 4390 | 4890 | 21391.5 | 2167.93 | 0.0710755 | 1(Win) | true |
| Jsonifier (two-stage) | 1461.09 | 0.0297846 | 318.714ms | 4390 | 640 | 466.167 | 2865.43 | 0.0393858 | 2(Loss) | true |
| Glaze | 1123.63 | 0.222541 | 393.145ms | 4390 | 40 | 2750.21 | 3726 | 0.376995 | 3(Loss) | true |
| simdjson (ondemand) | 797.454 | 0.215477 | 531.718ms | 4390 | 4890 | 625790 | 5250 | 2.01436 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8358.01 | 0.0933785 | 54.4046ms | 4390 | 320 | 70.0111 | 500.913 | 0.0249482 | 1(Win) | true |
| Glaze | 2128.84 | 0.80418 | 233.176ms | 4390 | 80 | 20009.7 | 1966.62 | 0.529067 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9134.88 | 0.0113785 | 49.2772ms | 4390 | 80 | 0.217563 | 458.312 | 0.00272747 | 1(Win) | true |
| Glaze | 2516.76 | 0.225934 | 173.681ms | 4390 | 40 | 565.026 | 1663.5 | 0.064163 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2211.93 | 0.119564 | 431.512ms | 9378 | 1280 | 29914.7 | 4043.32 | 0.0782893 | 1(Win) | true |
| Jsonifier | 1905.06 | 0.306513 | 402.068ms | 9378 | 320 | 66259.7 | 4694.62 | 0.499662 | 2(Loss) | true |
| simdjson (ondemand) | 1621.53 | 0.111331 | 558.604ms | 9378 | 2560 | 96524.7 | 5515.5 | 0.135292 | 3(Loss) | true |
| Glaze | 1542.61 | 0.179811 | 598.984ms | 9378 | 4890 | 531436 | 5797.68 | 0.39079 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2797.59 | 0.0935953 | 398.764ms | 9378 | 40 | 358.112 | 3196.88 | 0.66058 | 1(Win) | true |
| Jsonifier (two-stage) | 2319.66 | 0.280163 | 421.664ms | 9378 | 1280 | 149350 | 3855.55 | 1.12433 | 2(Loss) | true |
| simdjson (ondemand) | 1796.18 | 0.159421 | 516.673ms | 9378 | 30 | 1890.3 | 4979.2 | 0.0020084 | 3(Loss) | true |
| Glaze | 1701.81 | 1.21362 | 544.949ms | 9378 | 40 | 162713 | 5255.32 | 0.127494 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13649.1 | 0.0494996 | 83.8361ms | 11521 | 2560 | 406.46 | 804.984 | 0.0151863 | 1(Win) | true |
| Glaze | 3196.54 | 0.185544 | 351.245ms | 11521 | 4890 | 198895 | 3437.25 | 1.11493 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14449.1 | 0.188107 | 82.7222ms | 11521 | 160 | 327.363 | 760.413 | 0.136626 | 1(Win) | true |
| Glaze | 4332.57 | 0.0627665 | 260.926ms | 11521 | 160 | 405.383 | 2535.97 | 0.000492909 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2782.89 | 0.147597 | 163.705ms | 4669 | 4890 | 27272.3 | 1600.03 | 0.0982064 | 1(Win) | true |
| Jsonifier (two-stage) | 1443 | 0.806927 | 291.409ms | 4669 | 1280 | 793587 | 3085.73 | 0.625898 | 2(Loss) | true |
| Glaze | 1357.3 | 0.11561 | 332.968ms | 4669 | 4890 | 70339.4 | 3280.56 | 0.115545 | 3(Loss) | true |
| simdjson (ondemand) | 624.805 | 0.111666 | 717.716ms | 4669 | 1280 | 81060.9 | 7126.55 | 0.128305 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3191.19 | 0.184052 | 170.146ms | 4669 | 80 | 527.61 | 1395.31 | 0.110069 | 1(Win) | true |
| Jsonifier (two-stage) | 1985.88 | 0.0535554 | 237.082ms | 4669 | 320 | 461.42 | 2242.18 | 0.0218864 | 2(Loss) | true |
| Glaze | 1534.29 | 0.196136 | 304.44ms | 4669 | 40 | 1296.01 | 2902.12 | 0.0249879 | 3(Loss) | true |
| simdjson (ondemand) | 669.577 | 0.119969 | 681.112ms | 4669 | 2560 | 162940 | 6650.03 | 0.269987 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10591.5 | 0.0969382 | 45.1925ms | 4669 | 1280 | 212.587 | 420.405 | 0.025824 | 1(Win) | true |
| Glaze | 2058.08 | 0.127199 | 222.373ms | 4669 | 80 | 605.873 | 2163.53 | 0.0971581 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12051.7 | 0.107725 | 39.9991ms | 4669 | 1280 | 202.767 | 369.468 | 0.00105725 | 1(Win) | true |
| Glaze | 2349.29 | 0.0975571 | 193.463ms | 4669 | 160 | 547.03 | 1895.34 | 0.305626 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3025.2 | 0.0697339 | 254.605ms | 7932 | 80 | 243.24 | 2500.51 | 0.0624482 | 1(Win) | true |
| Jsonifier (two-stage) | 2684.64 | 0.0887833 | 297.513ms | 7932 | 80 | 500.663 | 2817.71 | 0.0731441 | 2(Loss) | true |
| Glaze | 1706.31 | 0.29285 | 446.819ms | 7932 | 40 | 6742.15 | 4433.27 | 0.0295204 | 3(Loss) | true |
| simdjson (ondemand) | 1032.7 | 0.110334 | 743ms | 7932 | 30 | 1959.55 | 7325.03 | 0.0181991 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3291.71 | 0.108009 | 249.073ms | 7932 | 4890 | 30126.4 | 2298.06 | 0.111138 | 1(Win) | true |
| Jsonifier (two-stage) | 2873.19 | 0.0895402 | 282.422ms | 7932 | 80 | 444.592 | 2632.8 | 0.0199447 | 2(Loss) | true |
| Glaze | 2010.16 | 0.0385285 | 396.394ms | 7932 | 640 | 1345.39 | 3763.15 | 0.0969822 | 3(Loss) | true |
| simdjson (ondemand) | 1105.13 | 0.176895 | 697.763ms | 7932 | 1280 | 187663 | 6844.92 | 0.040707 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14581.1 | 0.273187 | 75.6248ms | 9249 | 160 | 436.97 | 604.931 | 0.220552 | 1(Win) | true |
| Glaze | 3179.91 | 0.141302 | 281.197ms | 9249 | 2560 | 39327.3 | 2773.83 | 0.117403 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12600.5 | 0.625375 | 74.7665ms | 9249 | 1280 | 24530.6 | 700.016 | 1.75004 | 1(Win) | true |
| Glaze | 3729.86 | 0.0484506 | 241.039ms | 9249 | 320 | 420.101 | 2364.84 | 0.000264289 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 643.854 | 0.102943 | 695.665ms | 4604 | 30 | 1478.46 | 6819.43 | 0.142933 | 1(Win) | true |
| Jsonifier (two-stage) | 556.376 | 0.0861995 | 804.566ms | 4604 | 30 | 1388.24 | 7891.63 | 0.105907 | 2(Loss) | true |
| Glaze | 388.99 | 0.0524191 | 1148.64ms | 4604 | 80 | 2800.68 | 11287.5 | 0.0368635 | 3(Loss) | true |
| simdjson (ondemand) | 317.506 | 0.0615604 | 1391ms | 4604 | 4890 | 354388 | 13828.8 | 0.00878718 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 824.381 | 0.104233 | 675.523ms | 4604 | 40 | 1232.79 | 5326.07 | 0.0464911 | 1(Win) | true |
| Jsonifier (two-stage) | 689.36 | 0.0804585 | 793.079ms | 4604 | 80 | 2100.93 | 6369.26 | 0.0241452 | 2(Loss) | true |
| Glaze | 446.7 | 0.0768591 | 1122.29ms | 4604 | 30 | 1712.19 | 9829.23 | 0.0135631 | 3(Loss) | true |
| simdjson (ondemand) | 361.275 | 0.0366333 | 1374.07ms | 4604 | 160 | 3171.51 | 12153.4 | 0.0656793 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2206.61 | 0.102865 | 219.388ms | 4918 | 160 | 764.855 | 2125.51 | 0.0467317 | 1(Win) | true |
| Glaze | 1077.28 | 0.0503195 | 458.975ms | 4604 | 160 | 672.981 | 4075.72 | 0.124363 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2280.25 | 0.227736 | 216.646ms | 4918 | 30 | 658.257 | 2056.87 | 0.470554 | 1(Win) | true |
| Glaze | 1169.28 | 0.0444787 | 381.849ms | 4604 | 320 | 892.664 | 3755.06 | 0.0173962 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1926.41 | 0.0582828 | 916.958ms | 18245 | 40 | 1108.49 | 9032.23 | 0.0417773 | 1(Win) | true |
| Jsonifier | 1857.63 | 0.0731957 | 957.167ms | 18245 | 40 | 1880.18 | 9366.65 | 0.0154829 | 2(Loss) | true |
| Glaze | 1219.24 | 0.0577286 | 1451.55ms | 18245 | 4890 | 331894 | 14271 | 0.733081 | 3(Loss) | true |
| simdjson (ondemand) | 1174.77 | 0.0784125 | 1565.61ms | 18245 | 30 | 4046.42 | 14811.2 | 0.000225055 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2282.06 | 0.0739343 | 913.384ms | 18245 | 4890 | 155394 | 7624.6 | 0.31273 | 1(Win) | true |
| Jsonifier | 2208.89 | 0.0694096 | 930.722ms | 18245 | 4890 | 146180 | 7877.16 | 0.0629678 | 2(Loss) | true |
| Glaze | 1370.37 | 0.157237 | 1435.86ms | 18245 | 30 | 11957.6 | 12697.1 | 0.0228346 | 3(Loss) | true |
| simdjson (ondemand) | 1309.47 | 0.0769286 | 1469.97ms | 18245 | 2560 | 267493 | 13287.6 | 0.0388346 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5706.96 | 0.143263 | 421.556ms | 24893 | 1280 | 45459.6 | 4159.8 | 0.0709979 | 1(Win) | true |
| Glaze | 3248.41 | 0.116028 | 753.523ms | 24579 | 2560 | 179453 | 7215.95 | 0.0444201 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6040.16 | 0.286071 | 394.343ms | 24893 | 640 | 80906.8 | 3930.33 | 0.0351557 | 1(Win) | true |
| Glaze | 3940.14 | 0.0774987 | 605.327ms | 24579 | 40 | 850.266 | 5949.12 | 0.0570437 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 676.914 | 0.0667827 | 656.363ms | 4604 | 4890 | 91757 | 6486.37 | 0.00659392 | 1(Win) | true |
| Jsonifier (two-stage) | 512.906 | 0.512782 | 811.27ms | 4604 | 640 | 1.23322e+06 | 8560.47 | 2.65851 | 2(Loss) | true |
| Glaze | 390.935 | 0.0763633 | 1157.31ms | 4604 | 40 | 2942.33 | 11231.3 | 0.0435728 | 3(Loss) | true |
| simdjson (ondemand) | 332.209 | 0.0741771 | 1355.93ms | 4604 | 40 | 3844.56 | 13216.7 | 0.0204875 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 888.087 | 0.037297 | 643.709ms | 4604 | 320 | 1088.07 | 4944.02 | 0.100728 | 1(Win) | true |
| Jsonifier (two-stage) | 725.989 | 0.0637975 | 748.933ms | 4604 | 80 | 1190.99 | 6047.91 | 0.000620045 | 2(Loss) | true |
| Glaze | 450.786 | 0.0539901 | 1180.44ms | 4604 | 80 | 2212.32 | 9740.14 | 0.0815592 | 3(Loss) | true |
| simdjson (ondemand) | 375.631 | 0.0568439 | 1310.35ms | 4604 | 4890 | 215886 | 11688.9 | 0.195263 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2129.5 | 0.0633979 | 222.289ms | 4918 | 640 | 1247.82 | 2202.47 | 0.0457792 | 1(Win) | true |
| Glaze | 1047.08 | 0.316363 | 422.479ms | 4604 | 640 | 112633 | 4193.31 | 0.0877861 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2245.14 | 0.0497327 | 218.713ms | 4918 | 1280 | 1381.61 | 2089.04 | 0.0693458 | 1(Win) | true |
| Glaze | 1166.47 | 0.0856396 | 385.028ms | 4604 | 80 | 831.306 | 3764.1 | 0.0126176 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1964.45 | 0.0927151 | 923.832ms | 18245 | 2560 | 172643 | 8857.35 | 0.0419012 | 1(Win) | true |
| Jsonifier | 1718 | 0.55212 | 918.927ms | 18245 | 640 | 2.00119e+06 | 10127.9 | 0.863205 | 2(Loss) | true |
| Glaze | 1223.3 | 0.0751094 | 1438.42ms | 18245 | 30 | 3424.01 | 14223.7 | 0.137283 | 3(Loss) | true |
| simdjson (ondemand) | 1209.63 | 0.186571 | 1450.32ms | 18245 | 320 | 230474 | 14384.4 | 0.0034107 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2386.42 | 0.0324016 | 875.725ms | 18245 | 160 | 892.988 | 7291.16 | 0.0427927 | 1(Win) | true |
| Jsonifier | 2370.68 | 0.0506826 | 897.724ms | 18245 | 80 | 1107.01 | 7339.57 | 0.127569 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1374.77 | 0.191094 | 1415.02ms | 18245 | 320 | 187185 | 12656.5 | 0.260052 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1369.73 | 0.0522947 | 1422.61ms | 18245 | 80 | 3530.39 | 12703.1 | 0.0239173 | 3(Tie) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5545.19 | 0.090829 | 427.631ms | 24893 | 4890 | 73940.1 | 4281.16 | 0.016334 | 1(Win) | true |
| Glaze | 3324.41 | 0.0747477 | 712.367ms | 24579 | 40 | 1111.1 | 7050.98 | 0.0272937 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6100.15 | 0.166178 | 443.719ms | 24893 | 40 | 1672.94 | 3891.68 | 0.032773 | 1(Win) | true |
| Glaze | 3940.92 | 0.060491 | 601.238ms | 24579 | 80 | 1035.63 | 5947.94 | 0.0523017 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1196.05 | 0.0354619 | 414.846ms | 5094 | 320 | 663.888 | 4061.72 | 0.0514979 | 1(Win) | true |
| Jsonifier | 1140.02 | 0.614485 | 375.4ms | 5094 | 40 | 27426.6 | 4261.32 | 1.02601 | 2(Loss) | true |
| Glaze | 916.142 | 0.0666491 | 537.345ms | 5094 | 320 | 3996.97 | 5302.69 | 0.00300546 | 3(Loss) | true |
| simdjson (ondemand) | 657.071 | 0.0678899 | 777.245ms | 5094 | 4890 | 123201 | 7393.44 | 0.229861 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1932.73 | 0.105516 | 330.893ms | 5094 | 80 | 562.732 | 2513.55 | 0.000994599 | 1(Win) | true |
| Jsonifier (two-stage) | 1453.31 | 0.0441156 | 411.515ms | 5094 | 160 | 347.939 | 3342.72 | 0.0334795 | 2(Loss) | true |
| Glaze | 1111.23 | 0.109098 | 514.208ms | 5094 | 2560 | 58234.4 | 4371.75 | 0.0210469 | 3(Loss) | true |
| simdjson (ondemand) | 790.194 | 0.147302 | 690.762ms | 5094 | 40 | 3280.42 | 6147.88 | 0.00718457 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10164.7 | 0.122448 | 50.9774ms | 5094 | 1280 | 438.371 | 477.929 | 0.0279448 | 1(Win) | true |
| Glaze | 2785.98 | 0.147798 | 184.463ms | 5094 | 80 | 531.361 | 1743.74 | 0.175321 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11105.7 | 0.137705 | 46.8354ms | 5094 | 1280 | 464.448 | 437.434 | 0.000357198 | 1(Win) | true |
| Glaze | 3404.18 | 0.112217 | 146.081ms | 5094 | 4890 | 12540.7 | 1427.08 | 0.00814947 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1886.82 | 0.0574612 | 417.868ms | 8051 | 80 | 437.397 | 4069.29 | 0.0113643 | 1(Win) | true |
| Jsonifier (two-stage) | 1687.52 | 0.0689163 | 476.3ms | 8051 | 4890 | 48079.1 | 4549.9 | 0.00580121 | 2(Loss) | true |
| Glaze | 1268.5 | 0.0764183 | 633.873ms | 8051 | 160 | 3423.2 | 6052.83 | 0.05548 | 3(Loss) | true |
| simdjson (ondemand) | 1008.13 | 0.075687 | 774.61ms | 8051 | 160 | 5316.59 | 7616.14 | 0.0679118 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2288.04 | 0.0538556 | 427.284ms | 8051 | 160 | 522.581 | 3355.72 | 0.0787214 | 1(Win) | true |
| Jsonifier (two-stage) | 2015.28 | 0.0698511 | 456.106ms | 8051 | 80 | 566.587 | 3809.91 | 0.0154227 | 2(Loss) | true |
| Glaze | 1506.5 | 0.104369 | 596.759ms | 8051 | 160 | 4527.2 | 5096.61 | 0.17727 | 3(Loss) | true |
| simdjson (ondemand) | 1179.95 | 0.0689633 | 754.536ms | 8051 | 4890 | 98473.4 | 6507.09 | 0.039121 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11164.8 | 0.0228962 | 82.3152ms | 9255 | 2560 | 83.8717 | 790.541 | 0.129777 | 1(Win) | true |
| Glaze | 3125.19 | 0.0712509 | 288.377ms | 9255 | 160 | 647.89 | 2824.23 | 0.00818874 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13481.6 | 0.0826847 | 68.7269ms | 9255 | 1280 | 375.085 | 654.689 | 0.029603 | 1(Win) | true |
| Glaze | 3906.46 | 0.123649 | 233.726ms | 9255 | 40 | 312.195 | 2259.4 | 0.0162259 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4033.47 | 0.2426 | 71.5144ms | 2889 | 160 | 439.378 | 683.075 | 0.191777 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4020.45 | 0.173695 | 71.5188ms | 2889 | 320 | 453.39 | 685.288 | 0.364309 | 1(Tie) | true |
| simdjson (ondemand) | 3544.27 | 0.106854 | 81.1655ms | 2889 | 640 | 441.576 | 777.358 | 0.0190988 | 3(Loss) | true |
| Glaze | 2228.33 | 0.125492 | 130.514ms | 2889 | 160 | 385.202 | 1236.42 | 0.168105 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4386.38 | 0.0750581 | 69.7873ms | 2889 | 640 | 142.252 | 628.119 | 0.062151 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4382.23 | 0.0600106 | 69.7843ms | 2889 | 1280 | 182.209 | 628.713 | 0.0515952 | 1(Tie) | true |
| simdjson (ondemand) | 3803.57 | 0.160664 | 80.7271ms | 2889 | 320 | 433.411 | 724.362 | 0.0120781 | 3(Loss) | true |
| Glaze | 2307.86 | 0.13933 | 125.228ms | 2889 | 160 | 442.678 | 1193.82 | 0.12528 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4535.82 | 0.0950812 | 90.6253ms | 3808 | 640 | 370.895 | 800.647 | 0.227034 | 1(Win) | true |
| Jsonifier | 4358.57 | 0.0781417 | 89.818ms | 3808 | 320 | 135.65 | 833.206 | 0.0450271 | 2(Loss) | true |
| simdjson (ondemand) | 4091.78 | 0.400592 | 97.3718ms | 3808 | 30 | 379.223 | 887.533 | 0 | 3(Loss) | true |
| Glaze | 2596.66 | 0.123636 | 142.752ms | 3808 | 4890 | 14620.5 | 1398.56 | 0.00395714 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4805.21 | 0.093169 | 81.866ms | 3808 | 2560 | 1269.26 | 755.761 | 0.00449691 | 1(Win) | true |
| Jsonifier (two-stage) | 4673.34 | 0.303104 | 86.9377ms | 3808 | 80 | 443.828 | 777.087 | 0.00160854 | 2(Loss) | true |
| simdjson (ondemand) | 4243.88 | 0.276514 | 91.8496ms | 3808 | 160 | 895.823 | 855.725 | 1.13797 | 3(Loss) | true |
| Glaze | 2688.43 | 0.112555 | 142.474ms | 3808 | 4890 | 11304.1 | 1350.82 | 0.273625 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2329.2 | 0.0543848 | 121.844ms | 2889 | 1280 | 529.72 | 1182.88 | 0.112405 | 1(Win) | true |
| Jsonifier (two-stage) | 1881.2 | 0.0881845 | 149.826ms | 2889 | 160 | 266.887 | 1464.58 | 0.147436 | 2(Loss) | true |
| Glaze | 1812.91 | 0.461197 | 167.627ms | 2889 | 40 | 1965.06 | 1519.75 | 0.16751 | 3(Loss) | true |
| simdjson (ondemand) | 847.202 | 0.205076 | 328.991ms | 2889 | 40 | 1779.15 | 3252.07 | 0.0632529 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2228.48 | 0.0638483 | 142.795ms | 2889 | 640 | 398.801 | 1236.34 | 0.0539938 | 1(Win) | true |
| Jsonifier | 2189.51 | 0.80613 | 115.826ms | 2889 | 40 | 4115.98 | 1258.35 | 0.107168 | 2(Loss) | true |
| Glaze | 1915.34 | 0.229511 | 161.705ms | 2889 | 4890 | 53299.1 | 1438.48 | 0.380656 | 3(Loss) | true |
| simdjson (ondemand) | 908.306 | 0.166467 | 351.011ms | 2889 | 30 | 764.907 | 3033.3 | 0.0010989 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9429.14 | 0.351475 | 33.2209ms | 2963 | 640 | 710.048 | 299.681 | 0.190464 | 1(Win) | true |
| Glaze | 3634.44 | 0.0971827 | 81.1627ms | 2963 | 1280 | 730.761 | 777.488 | 0.219435 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12274.5 | 1.0168 | 27.7931ms | 2963 | 80 | 438.347 | 230.213 | 0.448649 | 1(Win) | true |
| Glaze | 4480.2 | 0.319911 | 65.2805ms | 2963 | 2560 | 10422.4 | 630.717 | 0.290489 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2481.76 | 0.11905 | 149.462ms | 3808 | 4890 | 14840.2 | 1463.32 | 0.0245453 | 1(Win) | true |
| Jsonifier (two-stage) | 2289.91 | 0.0321023 | 162.523ms | 3808 | 1280 | 331.772 | 1585.91 | 0.0015764 | 2(Loss) | true |
| Glaze | 2044.21 | 0.154185 | 183.819ms | 3808 | 2560 | 19207.4 | 1776.52 | 0.681519 | 3(Loss) | true |
| simdjson (ondemand) | 1095.14 | 0.146018 | 337.091ms | 3808 | 80 | 1875.65 | 3316.09 | 0.111829 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2954.53 | 0.0498784 | 141.643ms | 3808 | 1280 | 481.119 | 1229.16 | 0.00489433 | 1(Win) | true |
| Jsonifier (two-stage) | 2669.42 | 0.0430243 | 156.576ms | 3808 | 1280 | 438.528 | 1360.44 | 0.00195245 | 2(Loss) | true |
| Glaze | 2362.82 | 0.148254 | 169.758ms | 3808 | 160 | 830.742 | 1536.97 | 0.166186 | 3(Loss) | true |
| simdjson (ondemand) | 1159.98 | 0.0451354 | 327.196ms | 3808 | 640 | 1277.93 | 3130.73 | 0.0538223 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10438.4 | 0.322598 | 42.7747ms | 4300 | 320 | 513.973 | 392.856 | 0.0429731 | 1(Win) | true |
| Glaze | 3276.23 | 0.102455 | 128.967ms | 4300 | 320 | 526.268 | 1251.68 | 0.0558935 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12466.6 | 0.218974 | 36.1565ms | 4300 | 1280 | 664.103 | 328.942 | 0.0707261 | 1(Win) | true |
| Glaze | 4422.75 | 0.247787 | 97.824ms | 4300 | 4890 | 25811.9 | 927.207 | 0.0664514 | 2(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7598.87 | 0.0812469 | 5914.5ms | 466906 | 2560 | 5.80249e+06 | 58597.7 | 0.0989739 | 1(Win) | true |
| Jsonifier | 7335.92 | 0.0477272 | 6272.17ms | 466906 | 4890 | 4.10384e+06 | 60698.1 | 0.213188 | 2(Loss) | true |
| Glaze | 1745.29 | 0.124148 | 6624.74ms | 466906 | 160 | 1.60517e+07 | 255131 | 0.0188174 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7597.15 | 0.0678677 | 5978.3ms | 466906 | 2560 | 4.05065e+06 | 58610.9 | 0.28513 | 1(Win) | true |
| Jsonifier | 7372.73 | 0.245084 | 6231.16ms | 466906 | 160 | 3.50552e+06 | 60395 | 0.149677 | 2(Loss) | true |
| Glaze | 1745.09 | 0.168283 | 6790.35ms | 466906 | 80 | 1.47501e+07 | 255160 | 0.255923 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3392.29 | 0.103613 | 5114.32ms | 699405 | 320 | 1.32815e+07 | 196624 | 0.0943871 | 1(Win) | true |
| Glaze | 2533.42 | 0.208535 | 6857.01ms | 699405 | 30 | 9.04317e+06 | 263282 | 0.0442802 | 2(Loss) | true |
| simdjson (ondemand) | 1629.49 | 0.0973309 | 6005.51ms | 767297 | 320 | 6.11325e+07 | 449066 | 0.410841 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3410.82 | 0.0709939 | 5146.64ms | 699405 | 1280 | 2.46713e+07 | 195555 | 0.374046 | 1(Win) | true |
| Glaze | 2516.6 | 0.121747 | 7179.43ms | 699405 | 160 | 1.66597e+07 | 265042 | 0.146716 | 2(Loss) | true |
| simdjson (ondemand) | 1642.34 | 0.139397 | 5762.41ms | 767297 | 80 | 3.08599e+07 | 445553 | 0.26299 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2598.54 | 0.127683 | 6117.2ms | 631514 | 160 | 1.40118e+07 | 231768 | 1.03522 | 1(Win) | true |
| Glaze | 1991.1 | 0.084078 | 8007.36ms | 631514 | 640 | 4.13929e+07 | 302476 | 0.0192222 | 2(Loss) | true |
