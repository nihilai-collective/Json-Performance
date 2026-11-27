# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-1020-azure using the GCC 16.2.0 compiler).  

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
| **simdjson (reflection)** | `icelake` |
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
* **simdjson (reflection):** The C++26 static reflection API (P2996). Minified serialization only, for now.
* **Jsonifier:** We test both the fused scalar structural iteration and the two-stage indexing. The Partial tests always use two-stage parsing.
* **Summary Rows:** `*(combined)` rows are the best rank across each library's variants, they don't sum with the per-test rows.

---
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2182.45 | 0.142246 | 43.6218ms | 905 | 80 | 25.315 | 395.462 | 0.0347815 | 1.0557 | 1(Win) | true |
| Glaze | 2158.05 | 0.200225 | 42.6294ms | 905 | 30 | 19.2368 | 399.933 | 0.091598 | 1.06582 | 2(Loss) | true |
| simdjson (reflection) | 1120.29 | 0.0981311 | 78.5933ms | 905 | 40 | 22.8615 | 770.4 | 0.357836 | 2.13298 | 3(Loss) | true |
| simdjson (ondemand) | 476.64 | 0.392367 | 186.034ms | 905 | 1280 | 64611.6 | 1810.75 | 0.169372 | 5.11271 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2358.95 | 0.0543844 | 39.6602ms | 905 | 640 | 25.3388 | 365.872 | 0.129139 | 0.97318 | 1(Win) | true |
| Jsonifier | 2142.39 | 0.0627503 | 43.389ms | 905 | 320 | 20.4495 | 402.856 | 0.046521 | 1.07691 | 2(Loss) | true |
| simdjson (reflection) | 1162.78 | 0.0837974 | 75.5171ms | 905 | 80 | 30.9494 | 742.25 | 0.0471317 | 2.04862 | 3(Loss) | true |
| simdjson (ondemand) | 500.299 | 0.0309723 | 178.395ms | 905 | 160 | 45.6776 | 1725.12 | 0.0228297 | 4.86773 | 4(Loss) | true |

----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1983.63 | 0.0909565 | 46.8381ms | 905 | 160 | 25.0591 | 435.1 | 0.0459876 | 1.1718 | 1(Win) | true |
| simdjson (reflection) | 253.587 | 0.031712 | 350.047ms | 905 | 30 | 34.9471 | 3403.47 | 0.0782901 | 9.68641 | 2(Loss) | true |
| Glaze | 193.691 | 0.227914 | 448.835ms | 905 | 1280 | 132017 | 4455.94 | 0.101062 | 12.7031 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3080.49 | 0.238365 | 35.9921ms | 905 | 40 | 17.8404 | 280.175 | 0.210733 | 0.727459 | 1(Win) | true |
| simdjson (reflection) | 2431.41 | 0.0795994 | 44.6736ms | 905 | 320 | 25.5476 | 354.969 | 0.119872 | 0.941105 | 2(Loss) | true |
| Glaze | 1063.47 | 0.21043 | 89.109ms | 905 | 30 | 87.4954 | 811.567 | 0.0369519 | 2.25227 | 3(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1392.49 | 0.0769328 | 131.066ms | 1811 | 320 | 291.359 | 1240.3 | 0.180473 | 1.73929 | 1(Win) | true |
| Glaze | 1000.77 | 0.49776 | 175.149ms | 1811 | 640 | 47227.2 | 1725.78 | 0.372891 | 2.43456 | 2(Loss) | true |
| simdjson (ondemand) | 381.944 | 0.134977 | 454.37ms | 1811 | 40 | 1490.11 | 4521.88 | 0.147834 | 6.44041 | 3(Loss) | true |
| simdjson (reflection) | 360.269 | 0.50509 | 476.705ms | 1811 | 640 | 375232 | 4793.93 | 0.276732 | 6.83224 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491.94 | 0.0533297 | 121.899ms | 1811 | 80 | 30.4905 | 1157.62 | 0.0733723 | 1.6212 | 1(Win) | true |
| Glaze | 1064.01 | 0.0556709 | 167.022ms | 1811 | 80 | 65.3266 | 1623.2 | 0.0446449 | 2.28928 | 2(Loss) | true |
| simdjson (ondemand) | 390.097 | 0.212176 | 444.721ms | 1811 | 2560 | 225904 | 4427.37 | 0.117934 | 6.30668 | 3(Loss) | true |
| simdjson (reflection) | 371.871 | 0.242541 | 459.198ms | 1811 | 30 | 3806.65 | 4644.37 | 0.188396 | 6.61888 | 4(Loss) | true |

----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 363.831 | 0.0294213 | 520.942ms | 1997 | 30 | 71.154 | 5234.53 | 0.0496948 | 6.76835 | 1(Win) | true |
| simdjson (reflection) | 305.076 | 0.0238415 | 629.824ms | 1997 | 80 | 177.214 | 6242.66 | 0.0194266 | 8.07988 | 2(Loss) | true |
| Glaze | 271.968 | 0.0486716 | 640.386ms | 1798 | 80 | 753.327 | 6304.8 | 0.312669 | 9.06219 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 876.332 | 0.0495299 | 224.747ms | 1997 | 40 | 46.3462 | 2173.25 | 0.135926 | 2.78938 | 1(Win) | true |
| simdjson (reflection) | 724.085 | 0.0522333 | 273.253ms | 1997 | 40 | 75.4974 | 2630.2 | 0.0671234 | 3.3831 | 2(Loss) | true |
| Glaze | 558.118 | 0.0975177 | 323.889ms | 1798 | 160 | 1436.2 | 3072.3 | 0.197344 | 4.3972 | 3(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1662.2 | 0.0741464 | 79.7819ms | 1313 | 160 | 49.9189 | 753.325 | 0.107739 | 1.43485 | 1(Win) | true |
| simdjson (reflection) | 952.785 | 0.0695402 | 132.818ms | 1313 | 40 | 33.4096 | 1314.22 | 0.00824245 | 2.54299 | 2(Loss) | true |
| Glaze | 898.139 | 0.0437846 | 143.205ms | 1313 | 320 | 119.244 | 1394.19 | 0.216994 | 2.70401 | 3(Loss) | true |
| simdjson (ondemand) | 338.798 | 0.0311327 | 381.217ms | 1313 | 30 | 39.7195 | 3695.93 | 0.134202 | 7.25732 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1903.4 | 0.103562 | 68.7946ms | 1313 | 80 | 37.1328 | 657.862 | 0.249533 | 1.24891 | 1(Win) | true |
| simdjson (reflection) | 1039.29 | 0.0817575 | 124.124ms | 1313 | 30 | 29.1092 | 1204.83 | 0.0165971 | 2.32734 | 2(Loss) | true |
| Glaze | 952.305 | 0.0859601 | 137.825ms | 1313 | 80 | 102.202 | 1314.89 | 0.260203 | 2.54666 | 3(Loss) | true |
| simdjson (ondemand) | 342.241 | 0.0267786 | 373.469ms | 1313 | 40 | 38.3974 | 3658.75 | 0.0068334 | 7.18355 | 4(Loss) | true |

----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 333.087 | 0.0696487 | 373.848ms | 1313 | 30 | 205.666 | 3759.3 | 0.338081 | 7.3788 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 332.931 | 3.05013 | 397.582ms | 1313 | 160 | 2.10561e+06 | 3761.06 | 1.64553 | 7.38467 | 1(Tie) | true |
| Glaze | 309.324 | 0.0735993 | 411.609ms | 1313 | 40 | 355.067 | 4048.1 | 0.057607 | 7.95089 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2433.3 | 0.0772514 | 65.1067ms | 1313 | 160 | 25.2855 | 514.6 | 0.0922196 | 0.963647 | 1(Win) | true |
| Jsonifier | 2175.8 | 0.0979928 | 66.4009ms | 1313 | 80 | 25.443 | 575.5 | 0.117152 | 1.08211 | 2(Loss) | true |
| Glaze | 1299.37 | 0.0700444 | 103.674ms | 1313 | 40 | 18.225 | 963.675 | 0.116604 | 1.84798 | 3(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1382.45 | 0.116483 | 306.251ms | 4215 | 30 | 344.148 | 2907.7 | 0.192964 | 1.77321 | 1(Win) | true |
| Glaze | 975.185 | 0.139848 | 433.34ms | 4215 | 40 | 1329.2 | 4122.02 | 0.0127381 | 2.52302 | 2(Loss) | true |
| simdjson (reflection) | 955.793 | 0.265462 | 420.807ms | 4215 | 1280 | 159544 | 4205.66 | 0.0180342 | 2.57315 | 3(Loss) | true |
| simdjson (ondemand) | 687.068 | 0.178336 | 592.56ms | 4215 | 30 | 3265.84 | 5850.57 | 0.380322 | 3.58794 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1787.94 | 0.206114 | 269.822ms | 4215 | 2560 | 54972.7 | 2248.25 | 0.156335 | 1.36806 | 1(Win) | true |
| Glaze | 1203.31 | 0.0969405 | 373.226ms | 4215 | 40 | 419.481 | 3340.57 | 0.0546015 | 2.04065 | 2(Loss) | true |
| simdjson (reflection) | 1159.46 | 0.35212 | 383.054ms | 4215 | 1280 | 190754 | 3466.9 | 0.017664 | 2.1184 | 3(Loss) | true |
| simdjson (ondemand) | 811.736 | 0.121916 | 534.803ms | 4215 | 40 | 1457.97 | 4952.02 | 0.0405394 | 3.03358 | 4(Loss) | true |

----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.33 | 0.0738823 | 242.812ms | 4215 | 160 | 521.305 | 2443.12 | 0.0399238 | 1.48712 | 1(Win) | true |
| simdjson (reflection) | 1529.77 | 0.0921114 | 270.155ms | 4215 | 30 | 175.747 | 2627.67 | 0.34134 | 1.60251 | 2(Loss) | true |
| Glaze | 961.208 | 0.48579 | 419.541ms | 4215 | 640 | 264142 | 4181.96 | 0.278604 | 2.55937 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4449.23 | 0.051744 | 97.632ms | 4215 | 160 | 34.9676 | 903.469 | 0.293144 | 0.539721 | 1(Win) | true |
| simdjson (reflection) | 3983.68 | 0.0865526 | 108.013ms | 4215 | 40 | 30.5103 | 1009.05 | 0.114099 | 0.60465 | 2(Loss) | true |
| Glaze | 2742.63 | 0.0245952 | 164.754ms | 4215 | 320 | 41.5824 | 1465.65 | 0.196544 | 0.885386 | 3(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1536.74 | 0.170275 | 78.5842ms | 1213 | 30 | 49.2885 | 752.767 | 0.00885544 | 1.55109 | 1(Win) | true |
| simdjson (reflection) | 971.182 | 0.122869 | 120.286ms | 1213 | 30 | 64.2575 | 1191.13 | 0.170415 | 2.49132 | 2(Loss) | true |
| Glaze | 938.871 | 0.0906093 | 125.633ms | 1213 | 40 | 49.8558 | 1232.12 | 0.0263842 | 2.58007 | 3(Loss) | true |
| simdjson (ondemand) | 304.968 | 0.462038 | 384.951ms | 1213 | 320 | 98291.9 | 3793.2 | 0.657929 | 8.05955 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1679.91 | 0.058977 | 71.1047ms | 1213 | 160 | 26.3898 | 688.612 | 0.0852438 | 1.41565 | 1(Win) | true |
| simdjson (reflection) | 1117.66 | 0.0446032 | 107.23ms | 1213 | 160 | 34.1 | 1035.03 | 0.221724 | 2.15809 | 2(Loss) | true |
| Glaze | 964.011 | 0.0953807 | 121.824ms | 1213 | 160 | 209.604 | 1199.99 | 0.0234321 | 2.49423 | 3(Loss) | true |
| simdjson (ondemand) | 315.636 | 0.0310484 | 368.7ms | 1213 | 40 | 51.7949 | 3665 | 0.00363815 | 7.78551 | 4(Loss) | true |

----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 317.613 | 0.24594 | 373.727ms | 1213 | 4890 | 392365 | 3642.19 | 0.0255762 | 7.73647 | 1(Win) | true |
| simdjson (reflection) | 312.739 | 0.0733926 | 380.72ms | 1213 | 80 | 589.592 | 3698.95 | 0.159251 | 7.85783 | 2(Loss) | true |
| Glaze | 284.963 | 0.0622598 | 425.808ms | 1213 | 30 | 191.638 | 4059.5 | 0.247769 | 8.62874 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2221.76 | 0.0228949 | 60.1233ms | 1213 | 640 | 9.09458 | 520.67 | 0.0590836 | 1.0562 | 1(Win) | true |
| Jsonifier | 2138.8 | 0.156515 | 64.4654ms | 1213 | 30 | 21.4989 | 540.867 | 0.0492793 | 1.09879 | 2(Loss) | true |
| Glaze | 1325.09 | 0.188261 | 97.8484ms | 1213 | 30 | 81.0345 | 873 | 0.0420184 | 1.8097 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1574.42 | 0.193855 | 5787.66ms | 94653 | 160 | 1.97651e+06 | 57334.1 | 0.0570449 | 1.57176 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1389.16 | 0.109416 | 6532.18ms | 94653 | 2560 | 1.29408e+07 | 64980.2 | 0.212416 | 1.78148 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1388.73 | 0.281372 | 6627.75ms | 94653 | 80 | 2.67598e+06 | 65000.4 | 0.164288 | 1.78206 | 2(Tie) | true |
| Glaze | 1345.64 | 0.374125 | 6737.43ms | 94653 | 80 | 5.03887e+06 | 67081.8 | 0.197205 | 1.8391 | 4(Loss) | true |
| simdjson (ondemand) | 1283.15 | 0.12078 | 6975.38ms | 94653 | 1280 | 9.24103e+06 | 70349.1 | 0.39295 | 1.92873 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2156.55 | 0.322157 | 5381.79ms | 94653 | 320 | 5.81882e+06 | 41857.7 | 0.316923 | 1.14728 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.4 | 0.0668455 | 6205.86ms | 94653 | 4890 | 5.37856e+06 | 49614.2 | 0.55482 | 1.36002 | 2(Loss) | true |
| Glaze | 1755.6 | 0.189531 | 6413.95ms | 94653 | 640 | 6.07796e+06 | 51417.3 | 0.144856 | 1.40949 | 3(Loss) | true |
| simdjson (reflection) | 1746.11 | 0.0866644 | 6321.39ms | 94653 | 4890 | 9.81558e+06 | 51696.7 | 0.978805 | 1.41715 | 4(Loss) | true |
| simdjson (ondemand) | 1722.71 | 0.252359 | 6497.18ms | 94653 | 160 | 2.79773e+06 | 52399.1 | 0.625275 | 1.43644 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20824.1 | 0.779921 | 434.663ms | 94653 | 160 | 182876 | 4334.79 | 0.302442 | 0.118146 | 1(Win) | true |
| simdjson (reflection) | 14579.7 | 0.0427903 | 645.801ms | 94653 | 40 | 280.753 | 6191.38 | 0.102532 | 0.169089 | 2(Loss) | true |
| Glaze | 5868.6 | 0.227758 | 1538.74ms | 94653 | 1280 | 1.57094e+06 | 15381.5 | 0.575961 | 0.421126 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21344.3 | 0.0682561 | 431.32ms | 94653 | 40 | 333.31 | 4229.15 | 0.0681312 | 0.115224 | 1(Win) | true |
| simdjson (reflection) | 14220.6 | 0.130256 | 633.948ms | 94653 | 4890 | 334302 | 6347.72 | 0.492637 | 0.173353 | 2(Loss) | true |
| Glaze | 6480.38 | 0.11661 | 1398.93ms | 94653 | 4890 | 1.29017e+06 | 13929.5 | 0.586138 | 0.381274 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1807.6 | 0.0604012 | 6647.88ms | 124597 | 4890 | 7.70923e+06 | 65736.4 | 0.712964 | 1.36911 | 1(Win) | true |
| simdjson (reflection) | 1769.54 | 0.161975 | 6863.95ms | 124597 | 160 | 1.89282e+06 | 67150.1 | 0.53062 | 1.39855 | 2(Loss) | true |
| Jsonifier (two-stage) | 1697.38 | 0.159889 | 7056.94ms | 124597 | 1280 | 1.60363e+07 | 70004.9 | 0.195236 | 1.45804 | 3(Loss) | true |
| simdjson (ondemand) | 1668.35 | 0.15224 | 7042.8ms | 124597 | 640 | 7.5245e+06 | 71223.1 | 0.395112 | 1.48342 | 4(Loss) | true |
| Glaze | 1543.3 | 0.119558 | 7770.25ms | 124597 | 1280 | 1.08464e+07 | 76994.3 | 0.283519 | 1.60367 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2361.13 | 0.141896 | 6257.31ms | 124597 | 40 | 203975 | 50325.4 | 0.0539283 | 1.04802 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 2180.43 | 0.359583 | 6615.91ms | 124597 | 320 | 1.2288e+07 | 54496.2 | 0.277646 | 1.1349 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2171.19 | 0.247443 | 6590.83ms | 124597 | 2560 | 4.69473e+07 | 54728 | 0.653828 | 1.13972 | 2(Tie) | true |
| Jsonifier (two-stage) | 2162.18 | 0.194167 | 6681.03ms | 124597 | 640 | 7.28723e+06 | 54956.2 | 0.245401 | 1.14448 | 4(Loss) | true |
| Glaze | 1953.66 | 0.152449 | 7266.49ms | 124597 | 640 | 5.50229e+06 | 60821.6 | 0.206992 | 1.2667 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26628.7 | 0.0719149 | 486.003ms | 136037 | 30 | 368.276 | 4872 | 0.0335361 | 0.0924778 | 1(Win) | true |
| Glaze | 6257.41 | 0.113918 | 2221.62ms | 136076 | 1280 | 714443 | 20739 | 0.00660699 | 0.395169 | 2(Loss) | true |
| simdjson (reflection) | 602.849 | 0.315685 | 5425.39ms | 136037 | 30 | 1.3846e+07 | 215203 | 0.704701 | 4.10612 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26608.6 | 0.300755 | 479.033ms | 136037 | 2560 | 550474 | 4875.68 | 0.447201 | 0.0925176 | 1(Win) | true |
| Glaze | 6292.42 | 0.186627 | 2055.29ms | 136076 | 2560 | 3.7924e+06 | 20623.6 | 0.174627 | 0.392939 | 2(Loss) | true |
| simdjson (reflection) | 605.457 | 0.417125 | 5507.55ms | 136037 | 40 | 3.1955e+07 | 214276 | 0.0598674 | 4.08845 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 824.23 | 0.20704 | 8192.86ms | 2251027 | 160 | 4.65257e+09 | 2.60455e+06 | 0.296718 | 3.00374 | 1(Win) | true |
| Jsonifier (two-stage) | 779.411 | 0.242676 | 8642.82ms | 2251027 | 80 | 3.57414e+09 | 2.75432e+06 | 1.36005 | 3.17646 | 2(Loss) | true |
| Glaze | 744.482 | 0.134366 | 8939.51ms | 2251027 | 40 | 6.00475e+08 | 2.88354e+06 | 0.148314 | 3.3255 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 707.972 | 0.343512 | 9451.18ms | 2251027 | 160 | 1.73594e+10 | 3.03225e+06 | 0.253625 | 3.49699 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 705.325 | 0.214685 | 9602.13ms | 2251027 | 30 | 1.28088e+09 | 3.04363e+06 | 0.606301 | 3.51013 | 4(Tie) | true |

----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 949.039 | 0.088371 | 8202.17ms | 2251027 | 40 | 1.59836e+08 | 2.26202e+06 | 1.06533 | 2.60871 | 1(Win) | true |
| Jsonifier (two-stage) | 882.42 | 0.111134 | 8725.21ms | 2251027 | 160 | 1.16956e+09 | 2.4328e+06 | 0.0251643 | 2.80566 | 2(Loss) | true |
| Glaze | 850.487 | 0.206277 | 9037.84ms | 2251027 | 160 | 4.33756e+09 | 2.52414e+06 | 0.163262 | 2.911 | 3(Loss) | true |
| simdjson (ondemand) | 802.829 | 0.0910973 | 9506.47ms | 2251027 | 30 | 1.78012e+08 | 2.67398e+06 | 0.111164 | 3.08381 | 4(Loss) | true |
| simdjson (reflection) | 795.603 | 0.15431 | 9431.28ms | 2251027 | 30 | 5.20091e+08 | 2.69826e+06 | 0.606058 | 3.11181 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1812.44 | 0.0725435 | 6935.33ms | 2090326 | 80 | 5.09317e+07 | 1.09989e+06 | 0.374073 | 1.36597 | 1(Win) | true |
| Glaze | 1295.85 | 0.124519 | 9616.18ms | 2090234 | 80 | 2.93523e+08 | 1.5383e+06 | 0.502263 | 1.91052 | 2(Loss) | true |
| simdjson (reflection) | 1160.7 | 0.138867 | 5239.76ms | 2090326 | 40 | 2.27534e+08 | 1.71749e+06 | 1.78684 | 2.13298 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1825.55 | 0.0860629 | 6915.04ms | 2090326 | 160 | 1.41316e+08 | 1.09199e+06 | 0.714163 | 1.35615 | 1(Win) | true |
| Glaze | 1373.9 | 0.263705 | 9278.38ms | 2090234 | 30 | 4.39176e+08 | 1.45091e+06 | 0.635275 | 1.80199 | 2(Loss) | true |
| simdjson (reflection) | 1185.21 | 0.0920759 | 5244.17ms | 2090326 | 160 | 3.83749e+08 | 1.68197e+06 | 0.524064 | 2.08886 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1684.18 | 0.138589 | 9511.76ms | 5373214 | 40 | 7.1122e+08 | 3.0426e+06 | 0.436252 | 1.47001 | 1(Win) | true |
| Jsonifier (two-stage) | 1665.06 | 0.10406 | 9507.68ms | 5373214 | 160 | 1.64095e+09 | 3.07754e+06 | 0.774801 | 1.48687 | 2(Loss) | true |
| simdjson (reflection) | 1625.42 | 0.25485 | 10156.2ms | 5373214 | 30 | 1.93654e+09 | 3.15259e+06 | 0.884621 | 1.52316 | 3(Loss) | true |
| simdjson (ondemand) | 1549.65 | 0.121705 | 10320.9ms | 5373214 | 40 | 6.47856e+08 | 3.30674e+06 | 0.00196791 | 1.59761 | 4(Loss) | true |
| Glaze | 1476.72 | 0.313292 | 5078.69ms | 5373214 | 40 | 4.7275e+09 | 3.47006e+06 | 0.616246 | 1.67651 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1906.68 | 0.104468 | 9565.04ms | 5373214 | 160 | 1.26124e+09 | 2.68755e+06 | 0.243061 | 1.29846 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1902.85 | 0.135039 | 9647.96ms | 5373214 | 30 | 3.9673e+08 | 2.69296e+06 | 0.0462828 | 1.30108 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1805.63 | 0.112079 | 10113.6ms | 5373214 | 160 | 1.61875e+09 | 2.83796e+06 | 0.810077 | 1.37114 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1770.57 | 1.19838 | 10100.4ms | 5373214 | 40 | 4.81165e+10 | 2.89416e+06 | 0.574201 | 1.39829 | 3(Tie) | true |
| Glaze | 1726.77 | 0.0876541 | 5110.8ms | 5373214 | 80 | 5.41292e+08 | 2.96755e+06 | 0.0913857 | 1.43375 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5617.99 | 0.133315 | 7179.88ms | 6661989 | 80 | 1.81842e+08 | 1.1309e+06 | 0.0157466 | 0.440677 | 1(Win) | true |
| Glaze | 3009.26 | 0.60845 | 6444.84ms | 6661897 | 30 | 4.95048e+09 | 2.11124e+06 | 0.550612 | 0.822637 | 2(Loss) | true |
| simdjson (reflection) | 435.272 | 0.269807 | 10293.7ms | 6661989 | 30 | 4.65279e+10 | 1.45963e+07 | 0.659403 | 5.68773 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5638.18 | 0.0565338 | 7147.46ms | 6661989 | 160 | 6.49332e+07 | 1.12685e+06 | 0.106079 | 0.439095 | 1(Win) | true |
| Glaze | 3404.12 | 0.0860068 | 5773.3ms | 6661897 | 30 | 7.72992e+07 | 1.86635e+06 | 0.00193965 | 0.727279 | 2(Loss) | true |
| simdjson (reflection) | 421.111 | 0.268745 | 10631.2ms | 6661989 | 30 | 4.93191e+10 | 1.50871e+07 | 0.0690249 | 5.87907 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2018.14 | 0.223765 | 5940.47ms | 500299 | 160 | 4.47775e+07 | 236417 | 0.149412 | 1.22659 | 1(Win) | true |
| Jsonifier (two-stage) | 1781.29 | 0.225304 | 6738.41ms | 500299 | 40 | 1.45675e+07 | 267851 | 1.32955 | 1.38969 | 2(Loss) | true |
| Glaze | 1580.83 | 0.299409 | 7766.96ms | 500299 | 30 | 2.44985e+07 | 301818 | 0.0451394 | 1.56599 | 3(Loss) | true |
| simdjson (ondemand) | 1534.24 | 0.219992 | 8028.06ms | 500299 | 40 | 1.87218e+07 | 310983 | 0.205774 | 1.61347 | 4(Loss) | true |
| simdjson (reflection) | 1518.36 | 0.207864 | 7993.51ms | 500299 | 40 | 1.7066e+07 | 314236 | 0.264576 | 1.63035 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2483.23 | 0.30701 | 5851.54ms | 500299 | 40 | 1.39184e+07 | 192138 | 0.129466 | 0.996852 | 1(Win) | true |
| Jsonifier (two-stage) | 2124.69 | 0.210708 | 6698.94ms | 500299 | 1280 | 2.86578e+08 | 224561 | 0.0657725 | 1.16506 | 2(Loss) | true |
| simdjson (ondemand) | 1878.05 | 0.0844868 | 7384.1ms | 500299 | 1280 | 5.89705e+07 | 254053 | 0.472928 | 1.31811 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1796.98 | 0.152965 | 7727.6ms | 500299 | 320 | 5.2784e+07 | 265513 | 0.381034 | 1.37757 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1793.15 | 0.275923 | 7685.23ms | 500299 | 30 | 1.61705e+07 | 266080 | 0.111983 | 1.38054 | 4(Tie) | true |

----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 9513.09 | 0.297753 | 5037.34ms | 500299 | 160 | 3.56819e+06 | 50154.3 | 0.33352 | 0.260094 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 9490.25 | 0.105922 | 5099.85ms | 500299 | 1280 | 3.62986e+06 | 50275 | 0.00832539 | 0.260724 | 1(Tie) | true |
| Glaze | 3715.75 | 0.288595 | 6842.08ms | 500299 | 30 | 4.11969e+06 | 128405 | 0.0168968 | 0.666108 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9651.83 | 0.0923263 | 4937.27ms | 500299 | 2560 | 5.3325e+06 | 49433.3 | 0.211548 | 0.256361 | 1(Win) | true |
| simdjson (reflection) | 9353.83 | 0.0787957 | 5147.07ms | 500299 | 4890 | 7.89941e+06 | 51008.2 | 0.18005 | 0.264522 | 2(Loss) | true |
| Glaze | 4069.85 | 0.220651 | 6168.26ms | 500299 | 80 | 5.35312e+06 | 117233 | 0.0151324 | 0.60816 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3630.54 | 0.0707548 | 7754.9ms | 1151920 | 1280 | 5.86711e+07 | 302588 | 0.652541 | 0.681853 | 1(Win) | true |
| Jsonifier | 3564.08 | 0.127963 | 7964.55ms | 1151920 | 320 | 4.97819e+07 | 308230 | 0.45601 | 0.694582 | 2(Loss) | true |
| simdjson (ondemand) | 3140.21 | 0.108121 | 8863.79ms | 1151920 | 160 | 2.28912e+07 | 349835 | 0.774784 | 0.788333 | 3(Loss) | true |
| simdjson (reflection) | 3051.26 | 0.168958 | 9221.15ms | 1151920 | 640 | 2.36825e+08 | 360034 | 0.319085 | 0.811307 | 4(Loss) | true |
| Glaze | 2467.25 | 0.202941 | 5485.99ms | 1151920 | 160 | 1.30641e+08 | 445256 | 0.131383 | 1.0034 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4243.86 | 0.179989 | 7653.98ms | 1151920 | 80 | 1.73663e+07 | 258858 | 0.342726 | 0.583315 | 1(Win) | true |
| Jsonifier | 4073.73 | 0.105293 | 7917.61ms | 1151920 | 160 | 1.28996e+07 | 269668 | 1.15111 | 0.607675 | 2(Loss) | true |
| simdjson (ondemand) | 3723.33 | 0.100613 | 8498.02ms | 1151920 | 320 | 2.81996e+07 | 295047 | 0.404484 | 0.664864 | 3(Loss) | true |
| simdjson (reflection) | 3515.08 | 0.129221 | 8872.14ms | 1151920 | 320 | 5.21906e+07 | 312526 | 0.118977 | 0.704255 | 4(Loss) | true |
| Glaze | 2793.7 | 0.0811332 | 5489.91ms | 1151920 | 320 | 3.25712e+07 | 393227 | 0.681857 | 0.886134 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24759 | 0.985082 | 5647.75ms | 1439562 | 30 | 8.95079e+06 | 55449.5 | 0.123146 | 0.0999413 | 1(Win) | true |
| Glaze | 5082.6 | 0.16805 | 6866.95ms | 1439584 | 160 | 3.29685e+07 | 270117 | 0.428132 | 0.487044 | 2(Loss) | true |
| simdjson (reflection) | 565.336 | 0.26181 | 7494.73ms | 1439562 | 80 | 3.23376e+09 | 2.42842e+06 | 0.427389 | 4.37907 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24059.7 | 0.405442 | 5609.25ms | 1439562 | 1280 | 6.85088e+07 | 57061.1 | 0.121539 | 0.10284 | 1(Win) | true |
| Glaze | 6043.28 | 0.315011 | 5811.32ms | 1439584 | 40 | 2.04852e+07 | 227177 | 0.333123 | 0.409627 | 2(Loss) | true |
| simdjson (reflection) | 562.493 | 0.224885 | 7782.59ms | 1439562 | 160 | 4.82025e+09 | 2.44069e+06 | 0.188485 | 4.40136 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2214.37 | 0.0617543 | 2456.41ms | 56369 | 4890 | 1.09907e+06 | 24276.8 | 0.242755 | 1.11679 | 1(Win) | true |
| Jsonifier (two-stage) | 1820.55 | 0.131931 | 2937.24ms | 56369 | 640 | 971284 | 29528.3 | 0.242426 | 1.35857 | 2(Loss) | true |
| simdjson (reflection) | 1601.34 | 0.364361 | 3327.85ms | 56369 | 320 | 4.7877e+06 | 33570.4 | 0.0518024 | 1.54477 | 3(Loss) | true |
| Glaze | 1510.94 | 0.10665 | 3527.76ms | 56369 | 2560 | 3.68595e+06 | 35579.1 | 0.312193 | 1.63734 | 4(Loss) | true |
| simdjson (ondemand) | 1421.71 | 0.0909589 | 3784.75ms | 56369 | 4890 | 5.78437e+06 | 37811.9 | 0.388685 | 1.74018 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2820.06 | 0.384746 | 2240.09ms | 56369 | 160 | 860661 | 19062.6 | 0.453895 | 0.876678 | 1(Win) | true |
| Jsonifier (two-stage) | 2263.13 | 0.277861 | 2750.39ms | 56369 | 320 | 1.39401e+06 | 23753.7 | 0.0794851 | 1.09273 | 2(Loss) | true |
| Glaze | 1914.61 | 0.175243 | 3172.61ms | 56369 | 1280 | 3.09892e+06 | 28077.6 | 0.0225598 | 1.2916 | 3(Loss) | true |
| simdjson (reflection) | 1884.04 | 0.239735 | 3238.79ms | 56369 | 4890 | 2.28807e+07 | 28533.1 | 0.445857 | 1.31284 | 4(Loss) | true |
| simdjson (ondemand) | 1720.48 | 0.0831912 | 3501.46ms | 56369 | 4890 | 3.30404e+06 | 31245.7 | 0.128957 | 1.43777 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15198.5 | 0.0967439 | 354.781ms | 56369 | 30 | 351.275 | 3537.03 | 0.074395 | 0.161575 | 1(Win) | true |
| simdjson (reflection) | 13216.5 | 0.0590534 | 410.809ms | 56369 | 30 | 173.085 | 4067.47 | 0.211804 | 0.186004 | 2(Loss) | true |
| Glaze | 5381.82 | 0.206448 | 1006.98ms | 56369 | 1280 | 544321 | 9988.75 | 0.229015 | 0.458787 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15544.9 | 0.0695054 | 348.889ms | 56369 | 40 | 231.102 | 3458.22 | 0.0672763 | 0.158022 | 1(Win) | true |
| simdjson (reflection) | 13809.4 | 0.0933307 | 393.627ms | 56369 | 30 | 396.006 | 3892.83 | 0.0676915 | 0.17801 | 2(Loss) | true |
| Glaze | 5961.66 | 0.110272 | 918.543ms | 56369 | 30 | 2966.19 | 9017.23 | 0.111882 | 0.414029 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2609.1 | 0.249202 | 3140.11ms | 83958 | 4890 | 2.85993e+07 | 30688.2 | 0.151941 | 0.94803 | 1(Win) | true |
| Jsonifier (two-stage) | 2422.85 | 0.085442 | 3262.51ms | 83958 | 4890 | 3.89874e+06 | 33047.3 | 0.644282 | 1.02092 | 2(Loss) | true |
| simdjson (reflection) | 2300.46 | 0.109038 | 3465.05ms | 83958 | 2560 | 3.68716e+06 | 34805.4 | 0.234744 | 1.07536 | 3(Loss) | true |
| simdjson (ondemand) | 2001.28 | 0.141084 | 3998.84ms | 83958 | 1280 | 4.07824e+06 | 40008.7 | 0.0749333 | 1.23627 | 4(Loss) | true |
| Glaze | 1848.98 | 0.110101 | 4361.77ms | 83958 | 4890 | 1.1116e+07 | 43304.3 | 0.309342 | 1.33816 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3242.79 | 0.303803 | 2853.59ms | 83958 | 160 | 900310 | 24691.3 | 0.152056 | 0.762636 | 1(Win) | true |
| Jsonifier (two-stage) | 3083.2 | 0.285023 | 2941.87ms | 83958 | 4890 | 2.6791e+07 | 25969.3 | 0.125913 | 0.802127 | 2(Loss) | true |
| simdjson (reflection) | 2653.82 | 0.144006 | 3366.67ms | 83958 | 640 | 1.20815e+06 | 30171.1 | 0.482741 | 0.932073 | 3(Loss) | true |
| simdjson (ondemand) | 2468.46 | 0.17096 | 3623ms | 83958 | 320 | 984033 | 32436.7 | 0.0526326 | 1.00212 | 4(Loss) | true |
| Glaze | 2168.52 | 0.154796 | 4040.89ms | 83958 | 320 | 1.04537e+06 | 36923.2 | 0.0382827 | 1.14085 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24646.7 | 0.0605674 | 371.821ms | 94370 | 30 | 146.74 | 3651.53 | 0.708796 | 0.09968 | 1(Win) | true |
| Glaze | 4974.41 | 0.0914874 | 1815.16ms | 94370 | 4890 | 1.33973e+06 | 18092.2 | 0.411227 | 0.496949 | 2(Loss) | true |
| simdjson (reflection) | 528.791 | 0.21113 | 8815.74ms | 94370 | 160 | 2.06594e+07 | 170196 | 0.0644759 | 4.68063 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24967.3 | 0.108657 | 369.812ms | 94370 | 40 | 613.618 | 3604.65 | 0.106921 | 0.0984317 | 1(Win) | true |
| Glaze | 5718.7 | 0.125375 | 1596.3ms | 94370 | 2560 | 996626 | 15737.5 | 0.496196 | 0.432192 | 2(Loss) | true |
| simdjson (reflection) | 515.427 | 0.67935 | 8687.55ms | 94370 | 40 | 5.62836e+07 | 174609 | 0.0168882 | 4.8025 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1847.53 | 0.110051 | 2748.74ms | 53331 | 4890 | 4.48826e+06 | 27528.9 | 0.511161 | 1.33861 | 1(Win) | true |
| simdjson (reflection) | 1652.55 | 0.0839929 | 3092.84ms | 53331 | 4890 | 3.2677e+06 | 30776.9 | 0.111101 | 1.49679 | 2(Loss) | true |
| Jsonifier (two-stage) | 1539.96 | 0.35476 | 3358.77ms | 53331 | 320 | 4.39301e+06 | 33027.1 | 0.531222 | 1.60634 | 3(Loss) | true |
| Glaze | 1363.19 | 0.106616 | 3725.61ms | 53331 | 2560 | 4.05069e+06 | 37309.7 | 0.199611 | 1.81473 | 4(Loss) | true |
| simdjson (ondemand) | 1176.36 | 0.654934 | 4109.42ms | 53331 | 80 | 6.41457e+06 | 43235.6 | 0.364138 | 2.10329 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2522.05 | 0.133524 | 2531.62ms | 53331 | 1280 | 928062 | 20166.3 | 0.0847623 | 0.980351 | 1(Win) | true |
| simdjson (reflection) | 1924.83 | 0.313883 | 3203.59ms | 53331 | 160 | 1.1006e+06 | 26423.3 | 1.0405 | 1.28486 | 2(Loss) | true |
| Jsonifier (two-stage) | 1897.62 | 0.278624 | 3062.96ms | 53331 | 2560 | 1.42764e+07 | 26802.2 | 0.131771 | 1.30335 | 3(Loss) | true |
| Glaze | 1642.84 | 0.18776 | 3535.87ms | 53331 | 2560 | 8.65e+06 | 30958.8 | 0.531811 | 1.50569 | 4(Loss) | true |
| simdjson (ondemand) | 1383.42 | 0.163528 | 4214.43ms | 53331 | 640 | 2.31321e+06 | 36764.3 | 0.383902 | 1.78832 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12716.5 | 0.140047 | 444.821ms | 58581 | 30 | 1135.65 | 4393.27 | 0.00834541 | 0.193421 | 1(Win) | true |
| simdjson (reflection) | 10335.7 | 0.0663478 | 534.292ms | 58581 | 80 | 1028.92 | 5405.29 | 0.104868 | 0.238291 | 2(Loss) | true |
| Glaze | 6636.69 | 0.151109 | 846.84ms | 58581 | 2560 | 414220 | 8417.93 | 0.379609 | 0.371823 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13248.5 | 0.0891052 | 432.439ms | 58581 | 80 | 1129.48 | 4216.88 | 0.0243012 | 0.185636 | 1(Win) | true |
| simdjson (reflection) | 10797.3 | 0.0265337 | 526.736ms | 58581 | 160 | 301.579 | 5174.19 | 0.132815 | 0.228061 | 2(Loss) | true |
| Glaze | 7579.79 | 0.205892 | 732.023ms | 58581 | 2560 | 589549 | 7370.55 | 0.812501 | 0.325396 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1988.59 | 0.262633 | 3138.88ms | 65103 | 320 | 2.15161e+06 | 31221.7 | 0.345229 | 1.24386 | 1(Win) | true |
| Jsonifier | 1967.28 | 0.182286 | 3200.23ms | 65103 | 640 | 2.11815e+06 | 31559.8 | 0.058326 | 1.25734 | 2(Loss) | true |
| Jsonifier (two-stage) | 1795.28 | 0.0754693 | 3513.55ms | 65103 | 4890 | 3.33109e+06 | 34583.4 | 1.05686 | 1.37787 | 3(Loss) | true |
| Glaze | 1500.83 | 0.0810176 | 4118.43ms | 65103 | 4890 | 5.49296e+06 | 41368.4 | 0.235411 | 1.64849 | 4(Loss) | true |
| simdjson (ondemand) | 1491.22 | 0.134616 | 4186.38ms | 65103 | 2560 | 8.04175e+06 | 41635 | 0.09636 | 1.65909 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2530.22 | 0.268589 | 3011.14ms | 65103 | 640 | 2.78e+06 | 24538.2 | 0.822534 | 0.977413 | 1(Win) | true |
| simdjson (reflection) | 2240.42 | 0.418454 | 3264.27ms | 65103 | 320 | 4.3032e+06 | 27712.3 | 0.374262 | 1.10388 | 2(Loss) | true |
| Jsonifier (two-stage) | 2168.21 | 0.176786 | 3214.99ms | 65103 | 4890 | 1.25315e+07 | 28635.1 | 0.00402439 | 1.14074 | 3(Loss) | true |
| Glaze | 1824.86 | 0.362903 | 3979.98ms | 65103 | 160 | 2.43918e+06 | 34022.9 | 0.0895604 | 1.35563 | 4(Loss) | true |
| simdjson (ondemand) | 1658.3 | 0.206323 | 4266.07ms | 65103 | 640 | 3.81904e+06 | 37440.3 | 0.141638 | 1.4919 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16670.3 | 0.393325 | 455.376ms | 78778 | 640 | 201096 | 4506.73 | 0.0102635 | 0.147622 | 1(Win) | true |
| Glaze | 5151.01 | 0.122463 | 1469.45ms | 78778 | 2560 | 816727 | 14585.2 | 0.810401 | 0.479735 | 2(Loss) | true |
| simdjson (reflection) | 679.815 | 0.124253 | 5657.5ms | 78778 | 640 | 1.20677e+07 | 110513 | 0.0209037 | 3.64037 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17144.5 | 0.12203 | 434.919ms | 78778 | 80 | 2287.63 | 4382.09 | 0.480667 | 0.143386 | 1(Win) | true |
| Glaze | 5916.34 | 0.0965013 | 1275.36ms | 78778 | 4890 | 734309 | 12698.5 | 0.0393541 | 0.417565 | 2(Loss) | true |
| simdjson (reflection) | 674.867 | 0.185505 | 5732.89ms | 78778 | 160 | 6.82344e+06 | 111323 | 0.686223 | 3.66748 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1906.66 | 0.256442 | 618.342ms | 11812 | 640 | 146912 | 5908.12 | 0.238034 | 1.2928 | 1(Win) | true |
| Jsonifier (two-stage) | 1539.43 | 0.180798 | 718.804ms | 11812 | 4890 | 855894 | 7317.5 | 0.0675247 | 1.60208 | 2(Loss) | true |
| Glaze | 1471.4 | 0.121227 | 770.785ms | 11812 | 40 | 3445.43 | 7655.82 | 0.020359 | 1.67672 | 3(Loss) | true |
| simdjson (reflection) | 1433.2 | 0.28271 | 779.755ms | 11812 | 1280 | 632018 | 7859.91 | 0.376681 | 1.72142 | 4(Loss) | true |
| simdjson (ondemand) | 1200.86 | 0.315996 | 948.788ms | 11812 | 320 | 281176 | 9380.63 | 0.00099941 | 2.05573 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2036.39 | 0.572034 | 595.109ms | 11812 | 4890 | 4.89643e+06 | 5531.76 | 0.101048 | 1.21016 | 1(Win) | true |
| Glaze | 1681.61 | 0.160302 | 714.227ms | 11812 | 30 | 3459.34 | 6698.8 | 0.040322 | 1.46655 | 2(Loss) | true |
| Jsonifier (two-stage) | 1644.57 | 0.347979 | 714.768ms | 11812 | 320 | 181803 | 6849.71 | 0.053851 | 1.49933 | 3(Loss) | true |
| simdjson (reflection) | 1569.47 | 0.126618 | 776.598ms | 11812 | 2560 | 211433 | 7177.45 | 0.0927699 | 1.57167 | 4(Loss) | true |
| simdjson (ondemand) | 1270.35 | 0.107853 | 997.539ms | 11812 | 30 | 2743.98 | 8867.47 | 0.264962 | 1.94339 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13497.2 | 0.195628 | 85.3974ms | 11812 | 30 | 79.9724 | 834.6 | 0.00399409 | 0.177986 | 1(Win) | true |
| simdjson (reflection) | 11663.1 | 0.275886 | 100.615ms | 11812 | 4890 | 34720.7 | 965.851 | 0.268839 | 0.206275 | 2(Loss) | true |
| Glaze | 3827.14 | 0.170149 | 304.684ms | 11812 | 30 | 752.455 | 2943.4 | 0.0135879 | 0.640829 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14838.9 | 0.141819 | 80.5345ms | 11812 | 320 | 370.905 | 759.141 | 0.319221 | 0.161134 | 1(Win) | true |
| simdjson (reflection) | 11745.2 | 0.110925 | 99.7208ms | 11812 | 30 | 33.9552 | 959.1 | 0.069558 | 0.204992 | 2(Loss) | true |
| Glaze | 4274.42 | 0.0802958 | 265.693ms | 11812 | 40 | 179.118 | 2635.4 | 0.0151803 | 0.573557 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3062.65 | 0.115641 | 793.853ms | 25388 | 30 | 2507.29 | 7905.53 | 0.00716849 | 0.80576 | 1(Win) | true |
| simdjson (reflection) | 2847.35 | 0.108302 | 860.339ms | 25388 | 40 | 3392.42 | 8503.3 | 0.00156799 | 0.866723 | 2(Loss) | true |
| Jsonifier (two-stage) | 2818.94 | 0.0931758 | 874.807ms | 25388 | 30 | 1921.38 | 8589 | 0.129013 | 0.87537 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2339.82 | 0.429449 | 1055.54ms | 25388 | 320 | 631926 | 10347.8 | 0.470433 | 1.0553 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 2336.29 | 0.132638 | 1047.37ms | 25388 | 2560 | 483702 | 10363.4 | 0.168545 | 1.05701 | 4(Tie) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3372.55 | 0.0528384 | 776.934ms | 25388 | 30 | 431.679 | 7179.1 | 0.15484 | 0.73144 | 1(Win) | true |
| Jsonifier (two-stage) | 2941.1 | 0.0413741 | 868.552ms | 25388 | 40 | 464.038 | 8232.25 | 0.457272 | 0.839046 | 2(Loss) | true |
| simdjson (reflection) | 2898.93 | 0.132097 | 876.357ms | 25388 | 4890 | 595221 | 8352.01 | 0.0961443 | 0.851246 | 3(Loss) | true |
| simdjson (ondemand) | 2500.69 | 0.0608334 | 1011.45ms | 25388 | 80 | 2775.31 | 9682.08 | 0.06941 | 0.987299 | 4(Loss) | true |
| Glaze | 2396.95 | 0.384649 | 1041.44ms | 25388 | 640 | 966160 | 10101.1 | 0.399347 | 1.03014 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30902 | 0.0935315 | 99.3969ms | 31235 | 160 | 130.06 | 963.95 | 0.125627 | 0.0779554 | 1(Win) | true |
| Glaze | 5546.84 | 0.177093 | 568.957ms | 31235 | 2560 | 231545 | 5370.26 | 0.47147 | 0.444098 | 2(Loss) | true |
| simdjson (reflection) | 583.161 | 0.379087 | 5220.23ms | 31235 | 40 | 1.49984e+06 | 51080.2 | 0.0716707 | 4.24316 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30925.3 | 0.0510452 | 98.6721ms | 31235 | 320 | 77.3599 | 963.225 | 0.122485 | 0.0777845 | 1(Win) | true |
| Glaze | 5945.8 | 0.561923 | 502.326ms | 31235 | 320 | 253611 | 5009.93 | 0.246835 | 0.414118 | 2(Loss) | true |
| simdjson (reflection) | 569.927 | 0.109719 | 5267.45ms | 31235 | 1280 | 4.2094e+06 | 52266.4 | 0.0472982 | 4.34184 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2932.33 | 0.0743481 | 3540.62ms | 108313 | 4890 | 3.35417e+06 | 35226.4 | 0.0144725 | 0.843665 | 1(Win) | true |
| Jsonifier (two-stage) | 2494.72 | 0.124222 | 4159.11ms | 108313 | 640 | 1.69316e+06 | 41405.6 | 0.0840137 | 0.991766 | 2(Loss) | true |
| simdjson (reflection) | 1611.96 | 0.0668684 | 6424.39ms | 108313 | 2560 | 4.70039e+06 | 64080.5 | 0.309093 | 1.53523 | 3(Loss) | true |
| Glaze | 1573.69 | 0.087994 | 6416.11ms | 108313 | 1280 | 4.27011e+06 | 65639 | 0.15842 | 1.57248 | 4(Loss) | true |
| simdjson (ondemand) | 1264.32 | 0.120741 | 8170.32ms | 108313 | 640 | 6.2278e+06 | 81700.4 | 0.156055 | 1.95755 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3366.46 | 0.459 | 3288.2ms | 108313 | 40 | 793415 | 30683.7 | 0.631074 | 0.734812 | 1(Win) | true |
| Jsonifier (two-stage) | 2739.45 | 0.17723 | 4020.08ms | 108313 | 1280 | 5.71635e+06 | 37706.6 | 0.362892 | 0.903105 | 2(Loss) | true |
| Glaze | 1741.69 | 0.0452424 | 6098.06ms | 108313 | 4890 | 3.52062e+06 | 59307.5 | 0.0375789 | 1.42085 | 3(Loss) | true |
| simdjson (reflection) | 1665.48 | 0.119629 | 6395.21ms | 108313 | 320 | 1.76158e+06 | 62021.3 | 0.200114 | 1.48589 | 4(Loss) | true |
| simdjson (ondemand) | 1331.01 | 0.129205 | 7922.17ms | 108313 | 640 | 6.43487e+06 | 77606.6 | 0.0946408 | 1.85944 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17282.8 | 0.0291124 | 602.271ms | 108313 | 40 | 121.102 | 5976.77 | 0.0439007 | 0.142604 | 1(Win) | true |
| simdjson (reflection) | 14118.5 | 0.0309104 | 743.736ms | 108313 | 40 | 204.574 | 7316.3 | 0.0355497 | 0.174692 | 2(Loss) | true |
| Glaze | 2322.73 | 0.284753 | 4536.04ms | 108313 | 80 | 1.28289e+06 | 44471.6 | 0.209498 | 1.06525 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17589.7 | 0.0352 | 591.537ms | 108313 | 30 | 128.19 | 5872.5 | 0.039749 | 0.140098 | 1(Win) | true |
| simdjson (reflection) | 14191.1 | 0.0281094 | 728.789ms | 108313 | 80 | 334.905 | 7278.86 | 0.0530928 | 0.17381 | 2(Loss) | true |
| Glaze | 2394.04 | 0.0859529 | 4310.25ms | 108313 | 1280 | 1.76047e+06 | 43146.8 | 0.0404543 | 1.0335 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3567.85 | 0.108393 | 4870.42ms | 183677 | 2560 | 7.25004e+06 | 49096.3 | 0.378671 | 0.693484 | 1(Win) | true |
| Jsonifier | 3515.89 | 0.111336 | 4969.36ms | 183677 | 1280 | 3.93842e+06 | 49821.8 | 0.87831 | 0.703773 | 2(Loss) | true |
| simdjson (reflection) | 2488.65 | 0.0510671 | 6958.18ms | 183677 | 4890 | 6.31794e+06 | 70386.9 | 0.336285 | 0.994436 | 3(Loss) | true |
| Glaze | 2181.09 | 0.0714007 | 8151.05ms | 183677 | 1280 | 4.20898e+06 | 80312.1 | 0.162589 | 1.13474 | 4(Loss) | true |
| simdjson (ondemand) | 2032.6 | 0.0962979 | 8524.66ms | 183677 | 1280 | 8.81554e+06 | 86179.2 | 0.364429 | 1.21764 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4003.79 | 0.186888 | 4538.59ms | 183677 | 640 | 4.27869e+06 | 43750.6 | 0.22253 | 0.617972 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 3993.93 | 0.15258 | 4633.21ms | 183677 | 640 | 2.86605e+06 | 43858.5 | 0.131379 | 0.619501 | 1(Tie) | true |
| simdjson (reflection) | 2618.96 | 0.202727 | 7012.56ms | 183677 | 160 | 2.9417e+06 | 66884.7 | 0.14519 | 0.944955 | 3(Loss) | true |
| Glaze | 2250.6 | 0.110075 | 8007.42ms | 183677 | 4890 | 3.58922e+07 | 77831.8 | 0.341962 | 1.09968 | 4(Loss) | true |
| simdjson (ondemand) | 2117.29 | 0.0538433 | 8514.47ms | 183677 | 4890 | 9.70333e+06 | 82732.2 | 0.0210681 | 1.16894 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 32291.4 | 0.0504937 | 652.411ms | 213963 | 40 | 407.228 | 6319.05 | 0.128809 | 0.0763303 | 1(Win) | true |
| Glaze | 3608.02 | 0.064501 | 5675.98ms | 213963 | 2560 | 3.40654e+06 | 56554.9 | 0.094158 | 0.685865 | 2(Loss) | true |
| simdjson (reflection) | 511.516 | 0.12257 | 5161.02ms | 213963 | 320 | 7.65031e+07 | 398914 | 0.731064 | 4.83898 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 32906 | 0.0453063 | 634.483ms | 213963 | 30 | 236.792 | 6201.03 | 0.210083 | 0.0749145 | 1(Win) | true |
| Glaze | 3877.4 | 0.0784219 | 5286.81ms | 213963 | 1280 | 2.18013e+06 | 52625.8 | 0.709015 | 0.638193 | 2(Loss) | true |
| simdjson (reflection) | 508.3 | 0.170292 | 5116.13ms | 213963 | 320 | 1.49546e+08 | 401438 | 0.245903 | 4.87025 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 853.585 | 0.192571 | 6490.34ms | 1834197 | 30 | 4.67198e+08 | 2.04927e+06 | 0.100169 | 2.90042 | 1(Win) | true |
| Jsonifier (two-stage) | 751.177 | 0.135805 | 7285.42ms | 1834197 | 40 | 4.00038e+08 | 2.32865e+06 | 0.555375 | 3.29585 | 2(Loss) | true |
| simdjson (reflection) | 652.604 | 0.138646 | 8298.25ms | 1834197 | 160 | 2.20967e+09 | 2.68038e+06 | 0.0242611 | 3.79368 | 3(Loss) | true |
| Glaze | 629.309 | 0.558268 | 8518.16ms | 1834197 | 30 | 7.2239e+09 | 2.7796e+06 | 1.42968 | 3.93409 | 4(Loss) | true |
| simdjson (ondemand) | 551.951 | 0.315133 | 9773.49ms | 1834197 | 40 | 3.9897e+09 | 3.16917e+06 | 0.0599834 | 4.4855 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 943.536 | 0.0633477 | 6479.01ms | 1834197 | 160 | 2.20676e+08 | 1.8539e+06 | 0.790409 | 2.62391 | 1(Win) | true |
| Jsonifier (two-stage) | 823.552 | 0.197436 | 7268.44ms | 1834197 | 160 | 2.81374e+09 | 2.124e+06 | 0.587102 | 3.0062 | 2(Loss) | true |
| simdjson (reflection) | 724.612 | 0.092482 | 7998.91ms | 1834197 | 30 | 1.49526e+08 | 2.41402e+06 | 1.41566 | 3.41667 | 3(Loss) | true |
| Glaze | 696.306 | 0.141212 | 8659.31ms | 1834197 | 30 | 3.77535e+08 | 2.51215e+06 | 0.145836 | 3.55558 | 4(Loss) | true |
| simdjson (ondemand) | 608.81 | 0.192442 | 9722.84ms | 1834197 | 30 | 9.17167e+08 | 2.87319e+06 | 0.825482 | 4.06658 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1221.4 | 0.112637 | 9453.37ms | 1922245 | 80 | 2.2864e+08 | 1.50089e+06 | 0.602878 | 2.02698 | 1(Win) | true |
| simdjson (reflection) | 1028.68 | 0.190797 | 5436.54ms | 1922245 | 30 | 3.46833e+08 | 1.78208e+06 | 0.0314402 | 2.40674 | 2(Loss) | true |
| Glaze | 915.077 | 0.310242 | 5945.53ms | 1833577 | 160 | 5.62347e+09 | 1.91092e+06 | 0.0877374 | 2.70553 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1229.9 | 0.0582352 | 9425.97ms | 1922245 | 160 | 1.2055e+08 | 1.49052e+06 | 0.171609 | 2.01293 | 1(Win) | true |
| simdjson (reflection) | 1038.04 | 0.0951736 | 5510.34ms | 1922245 | 40 | 1.13002e+08 | 1.76602e+06 | 1.05825 | 2.38503 | 2(Loss) | true |
| Glaze | 916.788 | 0.204563 | 6015.84ms | 1833577 | 30 | 4.56707e+08 | 1.90735e+06 | 0.563734 | 2.70047 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2592.82 | 0.168799 | 8487.09ms | 7351818 | 30 | 6.25041e+08 | 2.7041e+06 | 0.734596 | 0.954858 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2588.1 | 0.135928 | 8430.89ms | 7351818 | 160 | 2.16952e+09 | 2.70903e+06 | 0.679266 | 0.956596 | 1(Tie) | true |
| simdjson (reflection) | 2306.65 | 0.0777227 | 9350.14ms | 7351818 | 160 | 8.92982e+08 | 3.03958e+06 | 0.698654 | 1.07332 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1951.28 | 0.251992 | 5342.08ms | 7351818 | 40 | 3.27932e+09 | 3.59314e+06 | 0.522367 | 1.26879 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1939.78 | 0.17853 | 5488.13ms | 7351818 | 30 | 1.24919e+09 | 3.61445e+06 | 0.34649 | 1.27632 | 4(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2800.85 | 0.340237 | 8503.25ms | 7351818 | 40 | 2.90157e+09 | 2.50325e+06 | 0.0453487 | 0.883926 | 1(Win) | true |
| Jsonifier | 2780.14 | 0.141458 | 8482.13ms | 7351818 | 160 | 2.03625e+09 | 2.52191e+06 | 1.49439 | 0.89052 | 2(Loss) | true |
| simdjson (reflection) | 2539.09 | 0.165502 | 9122.84ms | 7351818 | 30 | 6.26557e+08 | 2.76132e+06 | 1.13039 | 0.975058 | 3(Loss) | true |
| simdjson (ondemand) | 2179.14 | 0.200384 | 5229.84ms | 7351818 | 80 | 3.32532e+09 | 3.21743e+06 | 1.784 | 1.13611 | 4(Loss) | true |
| Glaze | 2055.14 | 0.148364 | 5470.02ms | 7351818 | 30 | 7.68576e+08 | 3.41157e+06 | 0.93477 | 1.20467 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6182.22 | 0.0710589 | 9895.3ms | 10018896 | 80 | 9.6489e+07 | 1.54552e+06 | 0.108391 | 0.400459 | 1(Win) | true |
| Glaze | 3458.03 | 0.272366 | 8508.44ms | 9930228 | 40 | 2.2255e+09 | 2.73861e+06 | 0.374842 | 0.715945 | 2(Loss) | true |
| simdjson (reflection) | 222.371 | 0.587616 | 12821.1ms | 10018896 | 30 | 1.91246e+12 | 4.29677e+07 | 2.27263 | 11.1336 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5902.72 | 0.509758 | 9921.76ms | 10018896 | 80 | 5.44696e+09 | 1.61871e+06 | 0.738292 | 0.41942 | 1(Win) | true |
| Glaze | 3756.65 | 0.066396 | 7901.69ms | 9930228 | 30 | 8.40471e+07 | 2.52092e+06 | 0.617836 | 0.659035 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 259.172 | 2.24844 | 11153.8ms | 10018896 | 30 | 2.06134e+13 | 3.68666e+07 | 3.38259 | 9.55266 | -(Loss) | false |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 834.716 | 0.0900339 | 6484.04ms | 1834197 | 80 | 2.84785e+08 | 2.0956e+06 | 0.306313 | 2.96599 | 1(Win) | true |
| Jsonifier (two-stage) | 746.634 | 0.201304 | 7302.41ms | 1834197 | 30 | 6.6727e+08 | 2.34282e+06 | 0.089729 | 3.31589 | 2(Loss) | true |
| simdjson (reflection) | 669.369 | 0.0687539 | 8148.21ms | 1834197 | 30 | 9.68451e+07 | 2.61325e+06 | 0.652305 | 3.69866 | 3(Loss) | true |
| Glaze | 641.429 | 0.146126 | 8460.34ms | 1834197 | 80 | 1.27039e+09 | 2.72708e+06 | 0.382903 | 3.85976 | 4(Loss) | true |
| simdjson (ondemand) | 562.971 | 0.12616 | 9825.34ms | 1834197 | 30 | 4.60985e+08 | 3.10713e+06 | 0.936159 | 4.39771 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 943.692 | 0.122648 | 6533.11ms | 1834197 | 80 | 4.13465e+08 | 1.8536e+06 | 0.674086 | 2.62347 | 1(Win) | true |
| Jsonifier (two-stage) | 820.669 | 0.114646 | 7291.68ms | 1834197 | 80 | 4.77707e+08 | 2.13146e+06 | 0.27487 | 3.01676 | 2(Loss) | true |
| simdjson (reflection) | 754.086 | 0.133886 | 7946.65ms | 1834197 | 40 | 3.85816e+08 | 2.31966e+06 | 0.101044 | 3.28313 | 3(Loss) | true |
| Glaze | 704.28 | 0.0614164 | 8430.5ms | 1834197 | 160 | 3.72298e+08 | 2.48371e+06 | 1.1864 | 3.51532 | 4(Loss) | true |
| simdjson (ondemand) | 608.53 | 0.208115 | 9492.01ms | 1834197 | 40 | 1.43151e+09 | 2.87451e+06 | 1.18808 | 4.0684 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1235.52 | 0.170292 | 9284.91ms | 1922245 | 30 | 1.91525e+08 | 1.48374e+06 | 0.903142 | 2.00381 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 1079.22 | 0.518975 | 5415.68ms | 1922245 | 80 | 6.217e+09 | 1.69863e+06 | 2.68986 | 2.29402 | -(Loss) | false |
| Glaze | 895.823 | 0.23575 | 6115.49ms | 1833577 | 80 | 1.69413e+09 | 1.95199e+06 | 0.762813 | 2.76367 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1242.93 | 0.0836024 | 9372.92ms | 1922245 | 320 | 4.86529e+08 | 1.47489e+06 | 0.427787 | 1.99184 | 1(Win) | true |
| simdjson (reflection) | 1032.62 | 0.0754207 | 5410.36ms | 1922245 | 160 | 2.86836e+08 | 1.77528e+06 | 0.346409 | 2.39753 | 2(Loss) | true |
| Glaze | 885.929 | 0.129583 | 5897.45ms | 1833577 | 30 | 1.96254e+08 | 1.97379e+06 | 2.06286 | 2.79452 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2619.73 | 0.134537 | 8335.5ms | 7351818 | 160 | 2.07434e+09 | 2.67632e+06 | 1.0015 | 0.945043 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2615.17 | 0.234013 | 8237.73ms | 7351818 | 30 | 1.18084e+09 | 2.68099e+06 | 0.0728309 | 0.946686 | 1(Tie) | true |
| simdjson (reflection) | 2379.76 | 0.154277 | 9076.93ms | 7351818 | 30 | 6.19795e+08 | 2.94619e+06 | 1.54034 | 1.04028 | 3(Loss) | true |
| simdjson (ondemand) | 2015.95 | 0.197407 | 5252.93ms | 7351818 | 80 | 3.77089e+09 | 3.47788e+06 | 0.295274 | 1.22804 | 4(Loss) | true |
| Glaze | 1926.97 | 0.194285 | 5440.2ms | 7351818 | 40 | 1.99883e+09 | 3.63848e+06 | 0.266332 | 1.28479 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2837.34 | 0.110707 | 8370.1ms | 7351818 | 160 | 1.19739e+09 | 2.47106e+06 | 0.454027 | 0.872563 | 1(Win) | true |
| Jsonifier (two-stage) | 2755.19 | 0.198249 | 8417.23ms | 7351818 | 40 | 1.01805e+09 | 2.54474e+06 | 0.520413 | 0.898569 | 2(Loss) | true |
| simdjson (reflection) | 2588.47 | 0.168587 | 9208.88ms | 7351818 | 80 | 1.66818e+09 | 2.70864e+06 | 0.127426 | 0.956414 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2294.95 | 0.218028 | 5025.98ms | 7351818 | 80 | 3.5494e+09 | 3.05507e+06 | 3.97528 | 1.07878 | -(Loss) | false |
| Glaze | 2099.08 | 0.265216 | 5386ms | 7351818 | 30 | 2.35425e+09 | 3.34015e+06 | 0.00191013 | 1.17945 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5992.52 | 0.482743 | 5065.4ms | 10018896 | 30 | 1.77735e+09 | 1.59445e+06 | 1.65198 | 0.413107 | 1(Win) | true |
| Glaze | 2759.82 | 0.618654 | 5008.21ms | 9930228 | 30 | 1.35199e+10 | 3.43146e+06 | 0.838965 | 0.896943 | 2(Loss) | true |
| simdjson (reflection) | 368.577 | 0.344374 | 7870.32ms | 10018896 | 30 | 2.39092e+11 | 2.59234e+07 | 1.73064 | 6.71709 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6019.85 | 0.296139 | 5017.84ms | 10018896 | 160 | 3.53491e+09 | 1.58721e+06 | 1.43436 | 0.41123 | 1(Win) | true |
| Glaze | 3712.99 | 0.107961 | 8012.53ms | 9930228 | 160 | 1.21318e+09 | 2.55056e+06 | 0.696707 | 0.66676 | 2(Loss) | true |
| simdjson (reflection) | 276.3 | 2.75653 | 10222.5ms | 10018896 | 30 | 2.72601e+13 | 3.45812e+07 | 2.26206 | 8.96049 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1254.2 | 0.3178 | 8599.58ms | 461466 | 320 | 3.97927e+08 | 350891 | 0.678023 | 1.97375 | 1(Win) | true |
| Jsonifier (two-stage) | 1101.43 | 0.200926 | 5084.59ms | 461466 | 640 | 4.12498e+08 | 399562 | 0.093868 | 2.24759 | 2(Loss) | true |
| simdjson (reflection) | 1063.44 | 0.136885 | 5301.42ms | 461466 | 320 | 1.02688e+08 | 413836 | 0.342888 | 2.32789 | 3(Loss) | true |
| simdjson (ondemand) | 1057.75 | 0.166271 | 5242.36ms | 461466 | 320 | 1.53143e+08 | 416062 | 1.09325 | 2.3404 | 4(Loss) | true |
| Glaze | 960.908 | 0.460172 | 5811.29ms | 461466 | 30 | 1.33253e+08 | 457992 | 0.173326 | 2.57631 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1813.59 | 0.194559 | 7990.53ms | 461466 | 80 | 1.78317e+07 | 242661 | 1.14853 | 1.36497 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1408.09 | 0.326159 | 9593.49ms | 461466 | 40 | 4.15662e+07 | 312544 | 0.393856 | 1.7581 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1406.32 | 0.205309 | 9640.15ms | 461466 | 80 | 3.30228e+07 | 312935 | 0.104924 | 1.7603 | 2(Tie) | true |
| simdjson (reflection) | 1361.78 | 0.0865692 | 9815.83ms | 461466 | 1280 | 1.00186e+08 | 323173 | 0.754719 | 1.81787 | 4(Loss) | true |
| Glaze | 1164.53 | 0.0715662 | 5683.79ms | 461466 | 640 | 4.68139e+07 | 377911 | 0.606242 | 2.12577 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14657.5 | 0.130719 | 3055.76ms | 461466 | 1280 | 1.97174e+06 | 30024.8 | 0.047137 | 0.168733 | 1(Win) | true |
| simdjson (reflection) | 10413.4 | 0.608333 | 4293.96ms | 461466 | 40 | 2.64387e+06 | 42261.8 | 0.307878 | 0.237591 | 2(Loss) | true |
| Glaze | 3183.03 | 0.128833 | 6847.55ms | 461466 | 1280 | 4.06125e+07 | 138261 | 0.00182058 | 0.777613 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14082.1 | 0.454291 | 3135.55ms | 461466 | 160 | 3.22502e+06 | 31251.6 | 0.0580434 | 0.175417 | 1(Win) | true |
| simdjson (reflection) | 10724.8 | 0.253875 | 4249.02ms | 461466 | 640 | 6.94581e+06 | 41034.7 | 0.610031 | 0.230676 | 2(Loss) | true |
| Glaze | 3714.89 | 0.172407 | 6099.25ms | 461466 | 640 | 2.66979e+07 | 118466 | 0.321403 | 0.666281 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.12 | 0.0794265 | 9718.47ms | 728486 | 640 | 5.67476e+07 | 374903 | 0.0191351 | 1.33588 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1634.58 | 0.259067 | 5498.09ms | 728486 | 80 | 9.69942e+07 | 425027 | 0.129113 | 1.5145 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1630.66 | 0.127772 | 5431.21ms | 728486 | 160 | 4.74141e+07 | 426048 | 2.00091 | 1.51814 | 2(Tie) | true |
| simdjson (reflection) | 1622.95 | 0.210085 | 5424.63ms | 728486 | 40 | 3.23509e+07 | 428072 | 0.624876 | 1.52536 | 4(Loss) | true |
| Glaze | 1279.52 | 0.254559 | 6894.55ms | 728486 | 30 | 5.73121e+07 | 542969 | 0.219132 | 1.93481 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2358.95 | 0.487746 | 9114.13ms | 728486 | 80 | 1.65076e+08 | 294512 | 0.0149038 | 1.04942 | 1(Win) | true |
| simdjson (ondemand) | 2140.01 | 0.136963 | 9855.4ms | 728486 | 320 | 6.3266e+07 | 324643 | 0.0824591 | 1.1568 | 2(Loss) | true |
| Jsonifier (two-stage) | 2038.14 | 0.101991 | 5298.39ms | 728486 | 640 | 7.73531e+07 | 340868 | 1.23865 | 1.21461 | 3(Loss) | true |
| simdjson (reflection) | 2006.42 | 0.0941485 | 5109.66ms | 728486 | 640 | 6.80151e+07 | 346257 | 0.111805 | 1.23382 | 4(Loss) | true |
| Glaze | 1580.31 | 0.206836 | 6528.53ms | 728486 | 30 | 2.48048e+07 | 439623 | 0.103542 | 1.56655 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22540.5 | 0.224139 | 3564.43ms | 837491 | 1280 | 8.07379e+06 | 35433.7 | 0.111343 | 0.109741 | 1(Win) | true |
| Glaze | 3741.23 | 0.223827 | 5689.5ms | 837491 | 40 | 9.13307e+06 | 213484 | 0.256017 | 0.661644 | 2(Loss) | true |
| simdjson (reflection) | 568.576 | 0.297771 | 9123.17ms | 837491 | 160 | 2.79943e+09 | 1.40473e+06 | 0.527752 | 4.35426 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22110.3 | 0.143504 | 3646.61ms | 837491 | 2560 | 6.87921e+06 | 36123.1 | 0.0553795 | 0.111841 | 1(Win) | true |
| Glaze | 4021.39 | 0.182926 | 5043.48ms | 837491 | 320 | 4.22384e+07 | 198611 | 0.623342 | 0.61557 | 2(Loss) | true |
| simdjson (reflection) | 544.648 | 0.251157 | 9249.27ms | 837491 | 40 | 5.42601e+08 | 1.46644e+06 | 0.548052 | 4.54544 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 8734.89 | 0.31634 | 5117.74ms | 466906 | 640 | 1.6643e+07 | 50976.7 | 0.089596 | 0.283168 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 8718.73 | 0.10657 | 5089.8ms | 466906 | 2560 | 7.58337e+06 | 51071.2 | 2.1477 | 0.283733 | 1(Tie) | true |
| simdjson (ondemand) | 7569.72 | 0.151509 | 5942.46ms | 466906 | 640 | 5.0834e+06 | 58823.4 | 0.0332834 | 0.326846 | 3(Loss) | true |
| simdjson (reflection) | 7389.58 | 0.13321 | 5940.27ms | 466906 | 1280 | 8.24717e+06 | 60257.3 | 0.0236404 | 0.334802 | 4(Loss) | true |
| Glaze | 3083.34 | 0.323128 | 7390.4ms | 466906 | 40 | 8.71016e+06 | 144414 | 0.328009 | 0.802801 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 9006.01 | 0.127253 | 5077.02ms | 466906 | 1280 | 5.06687e+06 | 49442.1 | 0.593237 | 0.274714 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 8992.83 | 0.11435 | 5120.2ms | 466906 | 1280 | 4.10348e+06 | 49514.6 | 0.0140225 | 0.275115 | 1(Tie) | true |
| simdjson (ondemand) | 7756.62 | 0.0636922 | 5852.71ms | 466906 | 4890 | 6.53725e+06 | 57406 | 0.158872 | 0.319008 | 3(Loss) | true |
| simdjson (reflection) | 7534.75 | 0.175373 | 5890.56ms | 466906 | 640 | 6.87427e+06 | 59096.4 | 0.193013 | 0.328399 | 4(Loss) | true |
| Glaze | 3104.33 | 0.379096 | 7389.51ms | 466906 | 40 | 1.18272e+07 | 143437 | 0.102599 | 0.797378 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9451.29 | 0.0865442 | 6351.98ms | 631514 | 2560 | 7.78574e+06 | 63722.4 | 0.16764 | 0.261786 | 1(Win) | true |
| Jsonifier | 9430.62 | 0.0592342 | 6349.24ms | 631514 | 4890 | 6.99745e+06 | 63862 | 0.733219 | 0.262361 | 2(Loss) | true |
| simdjson (ondemand) | 8874.28 | 0.107867 | 6991.24ms | 631514 | 1280 | 6.85945e+06 | 67865.7 | 0.443323 | 0.278843 | 3(Loss) | true |
| simdjson (reflection) | 8848.84 | 0.0744354 | 6886.56ms | 631514 | 4890 | 1.25505e+07 | 68060.8 | 0.0265088 | 0.27963 | 4(Loss) | true |
| Glaze | 3708.21 | 0.128549 | 8428.6ms | 631514 | 320 | 1.39483e+07 | 162412 | 0.353456 | 0.667531 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9585.08 | 0.135322 | 6292.83ms | 631514 | 1280 | 9.25385e+06 | 62833 | 0.132424 | 0.258137 | 1(Win) | true |
| Jsonifier | 9428.9 | 0.0763797 | 6416.14ms | 631514 | 4890 | 1.16388e+07 | 63873.7 | 0.82625 | 0.262453 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 8816.26 | 0.0696686 | 6904.25ms | 631514 | 4890 | 1.10759e+07 | 68312.3 | 0.0715045 | 0.280695 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 8813.09 | 0.423691 | 6955.07ms | 631514 | 30 | 2.51495e+06 | 68336.8 | 0.361257 | 0.280781 | 3(Tie) | true |
| Glaze | 3656.29 | 0.128616 | 8348.61ms | 631514 | 320 | 1.43623e+07 | 164719 | 0.414067 | 0.677019 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2057.55 | 0.330386 | 5552.13ms | 466906 | 80 | 4.08971e+07 | 216411 | 0.0548621 | 1.20304 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1667.04 | 0.556913 | 6938.38ms | 466906 | 30 | 6.6384e+07 | 267106 | 0.52112 | 1.48491 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1665.22 | 0.248457 | 6761.43ms | 466906 | 80 | 3.53108e+07 | 267398 | 0.464608 | 1.48654 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1650.48 | 0.413574 | 7088.14ms | 466906 | 30 | 3.73481e+07 | 269786 | 0.466432 | 1.49983 | 2(Tie) | true |
| simdjson (ondemand) | 1028.23 | 0.133884 | 5537.69ms | 466906 | 320 | 1.07568e+08 | 433050 | 0.139735 | 2.40761 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2553.63 | 0.486434 | 5154.43ms | 466906 | 30 | 2.15829e+07 | 174370 | 0.179309 | 0.969351 | 1(Win) | true |
| Jsonifier (two-stage) | 2047.35 | 0.229538 | 6540.01ms | 466906 | 80 | 1.99377e+07 | 217489 | 0.440529 | 1.20909 | 2(Loss) | true |
| Glaze | 2037.2 | 0.100318 | 6477.21ms | 466906 | 1280 | 6.15408e+07 | 218573 | 0.05254 | 1.21513 | 3(Loss) | true |
| simdjson (reflection) | 1958.15 | 0.140269 | 6558.17ms | 466906 | 640 | 6.51138e+07 | 227397 | 0.134277 | 1.26415 | 4(Loss) | true |
| simdjson (ondemand) | 1071.98 | 0.178603 | 5399.62ms | 466906 | 80 | 4.40302e+07 | 415376 | 0.126038 | 2.30935 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13113.1 | 0.377509 | 3423.26ms | 475954 | 1280 | 2.18565e+07 | 34614.5 | 0.238147 | 0.188626 | 1(Win) | true |
| simdjson (reflection) | 10337.5 | 0.719869 | 4424.59ms | 475954 | 80 | 7.99277e+06 | 43908.7 | 0.461634 | 0.239334 | 2(Loss) | true |
| Glaze | 5640.96 | 0.222358 | 8260.05ms | 475954 | 320 | 1.02442e+07 | 80465.9 | 0.0545054 | 0.438701 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12996.8 | 0.203023 | 3517.24ms | 475954 | 640 | 3.21754e+06 | 34924.3 | 0.166155 | 0.190303 | 1(Win) | true |
| simdjson (reflection) | 10219.1 | 0.149132 | 4492.02ms | 475954 | 1280 | 5.61642e+06 | 44417.3 | 0.212769 | 0.242104 | 2(Loss) | true |
| Glaze | 6517.52 | 0.479622 | 7273.17ms | 475954 | 30 | 3.34722e+06 | 69643.8 | 0.37289 | 0.379711 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2237.08 | 0.22175 | 6871.36ms | 631514 | 320 | 1.14046e+08 | 269217 | 0.171545 | 1.10654 | 1(Win) | true |
| simdjson (reflection) | 2096.36 | 0.308204 | 7392.15ms | 631514 | 80 | 6.27193e+07 | 287287 | 0.147648 | 1.18083 | 2(Loss) | true |
| Jsonifier (two-stage) | 2034.04 | 0.175271 | 7582.21ms | 631514 | 160 | 4.3091e+07 | 296090 | 0.0561019 | 1.217 | 3(Loss) | true |
| Glaze | 1700.9 | 0.270507 | 8996.95ms | 631514 | 80 | 7.33926e+07 | 354081 | 0.133319 | 1.45541 | 4(Loss) | true |
| simdjson (ondemand) | 1291.66 | 0.0884031 | 6045.16ms | 631514 | 320 | 5.43695e+07 | 466268 | 1.39696 | 1.91658 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2710.98 | 0.0872038 | 6387.85ms | 631514 | 1280 | 4.8039e+07 | 222155 | 0.409948 | 0.913098 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2454.94 | 0.311306 | 6923.96ms | 631514 | 40 | 2.33302e+07 | 245325 | 0.327845 | 1.00835 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2439.83 | 0.0957309 | 7081.18ms | 631514 | 1280 | 7.14761e+07 | 246844 | 0.211007 | 1.0146 | 2(Tie) | true |
| Glaze | 2024.48 | 0.0871798 | 8284.37ms | 631514 | 320 | 2.15239e+07 | 297488 | 0.104693 | 1.22279 | 4(Loss) | true |
| simdjson (ondemand) | 1423.86 | 0.480077 | 5769.52ms | 631514 | 40 | 1.64935e+08 | 422977 | 0.721468 | 1.73865 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16618.1 | 0.460908 | 4147.67ms | 716365 | 160 | 5.74457e+06 | 41110.6 | 0.0394214 | 0.148869 | 1(Win) | true |
| Glaze | 4261.32 | 0.135515 | 8171.86ms | 716365 | 2560 | 1.20835e+08 | 160321 | 0.131732 | 0.580853 | 2(Loss) | true |
| simdjson (reflection) | 571.87 | 0.2624 | 7484.32ms | 716365 | 30 | 2.94797e+08 | 1.19464e+06 | 1.16535 | 4.32919 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16432.3 | 0.148416 | 4141.3ms | 716365 | 1280 | 4.87358e+06 | 41575.5 | 0.314925 | 0.150547 | 1(Win) | true |
| Glaze | 4984.53 | 0.503006 | 7070.94ms | 716365 | 80 | 3.80238e+07 | 137060 | 0.402773 | 0.496592 | 2(Loss) | true |
| simdjson (reflection) | 564.245 | 0.182887 | 7622.22ms | 716365 | 320 | 1.5691e+09 | 1.21078e+06 | 1.4867 | 4.38766 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2315.99 | 0.0979736 | 113.248ms | 2632 | 160 | 180.4 | 1083.8 | 0 | 1.04251 | 1(Win) | true |
| Jsonifier (two-stage) | 2002.25 | 0.240035 | 132.029ms | 2632 | 160 | 1448.79 | 1253.62 | 0.359655 | 1.21043 | 2(Loss) | true |
| simdjson (reflection) | 1838.21 | 0.327237 | 141.964ms | 2632 | 2560 | 51115.1 | 1365.5 | 0.114501 | 1.31794 | 3(Loss) | true |
| Glaze | 1748.05 | 0.17966 | 145.909ms | 2632 | 80 | 532.425 | 1435.92 | 0.431647 | 1.38913 | 4(Loss) | true |
| simdjson (ondemand) | 1724.09 | 0.253509 | 148.467ms | 2632 | 2560 | 34872.1 | 1455.88 | 0.500689 | 1.40883 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2565.33 | 0.408735 | 105.507ms | 2632 | 1280 | 20472.8 | 978.459 | 0.218373 | 0.937909 | 1(Win) | true |
| Jsonifier (two-stage) | 2259.1 | 0.0529445 | 123.39ms | 2632 | 160 | 55.3685 | 1111.09 | 0.311221 | 1.06881 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2008.19 | 0.125292 | 135.874ms | 2632 | 320 | 784.802 | 1249.92 | 0.950511 | 1.20587 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2008.16 | 0.282062 | 138.508ms | 2632 | 30 | 372.892 | 1249.93 | 0.19238 | 1.20483 | 3(Tie) | true |
| Glaze | 1969.27 | 0.114932 | 137.479ms | 2632 | 640 | 1373.49 | 1274.62 | 0.344668 | 1.23031 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10955.6 | 0.326012 | 25.7168ms | 2632 | 80 | 44.6328 | 229.113 | 0.554093 | 0.198741 | 1(Win) | true |
| simdjson (reflection) | 8874.73 | 0.376323 | 31.4023ms | 2632 | 4890 | 5539.77 | 282.833 | 0.183102 | 0.252464 | 2(Loss) | true |
| Glaze | 4250.28 | 0.15376 | 63.2961ms | 2632 | 30 | 24.7368 | 590.567 | 0.113014 | 0.556117 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12484.8 | 0.599716 | 24.4193ms | 2632 | 40 | 58.1513 | 201.05 | 0.0248756 | 0.172084 | 1(Win) | true |
| simdjson (reflection) | 10042.5 | 0.117132 | 27.181ms | 2632 | 160 | 13.7138 | 249.944 | 0.0725689 | 0.22097 | 2(Loss) | true |
| Glaze | 4686.9 | 0.149491 | 57.5411ms | 2632 | 40 | 25.6385 | 535.55 | 0.0528771 | 0.500085 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2510.96 | 0.21628 | 131.516ms | 3370 | 4890 | 37473.2 | 1279.94 | 0.230461 | 0.96498 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2374.51 | 0.338731 | 140.081ms | 3370 | 2560 | 53809.7 | 1353.49 | 0.553124 | 1.02053 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2362.46 | 0.320562 | 139.904ms | 3370 | 4890 | 92995.8 | 1360.4 | 0.465444 | 1.02724 | 2(Tie) | true |
| simdjson (ondemand) | 2079.4 | 0.105422 | 159.534ms | 3370 | 160 | 424.786 | 1545.58 | 0.00606531 | 1.16945 | 4(Loss) | true |
| Glaze | 1965.08 | 0.121361 | 161.032ms | 3370 | 30 | 118.19 | 1635.5 | 0.294656 | 1.24054 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2890.18 | 0.208796 | 123.871ms | 3370 | 30 | 161.724 | 1112 | 0.0329628 | 0.836528 | 1(Win) | true |
| Jsonifier (two-stage) | 2646.13 | 0.0296127 | 133.254ms | 3370 | 320 | 41.3946 | 1214.56 | 0.256379 | 0.914724 | 2(Loss) | true |
| simdjson (reflection) | 2513.4 | 0.154288 | 139.082ms | 3370 | 320 | 1245.51 | 1278.7 | 0.965031 | 0.964152 | 3(Loss) | true |
| simdjson (ondemand) | 2449.67 | 0.239936 | 142.959ms | 3370 | 30 | 297.275 | 1311.97 | 0.154744 | 0.989565 | 4(Loss) | true |
| Glaze | 2315.27 | 0.633854 | 150.047ms | 3370 | 640 | 49546.6 | 1388.12 | 0.273115 | 1.04874 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 13075.8 | 0.457456 | 29.5629ms | 3643 | 80 | 118.187 | 265.7 | 2.82527 | 0.170543 | -(Win) | false |
| Glaze | 4376.4 | 0.111885 | 84.5795ms | 3682 | 320 | 257.885 | 802.356 | 0.276541 | 0.546828 | 2(Loss) | true |
| simdjson (reflection) | 557.481 | 0.429239 | 631.456ms | 3643 | 640 | 457969 | 6232.02 | 0.00318406 | 4.42164 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16266.6 | 0.193406 | 24.7173ms | 3643 | 160 | 27.3015 | 213.581 | 0.131857 | 0.133288 | 1(Win) | true |
| Glaze | 4849.29 | 0.245632 | 77.2638ms | 3682 | 80 | 253.088 | 724.112 | 0.170607 | 0.491978 | 2(Loss) | true |
| simdjson (reflection) | 570.65 | 0.0501205 | 630.927ms | 3643 | 80 | 744.904 | 6088.21 | 0.0494564 | 4.31937 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 955.67 | 0.0599131 | 493.599ms | 4630 | 30 | 229.885 | 4620.33 | 0.115299 | 2.57693 | 1(Win) | true |
| Jsonifier (two-stage) | 833.399 | 0.261488 | 590.274ms | 4630 | 40 | 7677.5 | 5298.2 | 0.371311 | 2.956 | 2(Loss) | true |
| simdjson (reflection) | 714.421 | 0.0852775 | 630.933ms | 4630 | 40 | 1111.18 | 6180.55 | 0.0418153 | 3.4514 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 699.318 | 0.0877889 | 653.86ms | 4630 | 40 | 1229 | 6314.02 | 0.461511 | 3.52472 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 697.344 | 0.502748 | 640.881ms | 4630 | 640 | 648558 | 6331.9 | 0.396814 | 3.53528 | 4(Tie) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.92 | 0.827403 | 475.734ms | 4630 | 160 | 163774 | 3866.74 | 0.182657 | 2.15351 | 1(Win) | true |
| Jsonifier (two-stage) | 976.602 | 0.0798386 | 541.537ms | 4630 | 30 | 390.907 | 4521.3 | 0.528018 | 2.51949 | 2(Loss) | true |
| Glaze | 835.923 | 0.201063 | 616.82ms | 4630 | 40 | 4511.86 | 5282.2 | 0.460888 | 2.94646 | 3(Loss) | true |
| simdjson (reflection) | 822.278 | 0.0825949 | 649.505ms | 4630 | 40 | 786.849 | 5369.85 | 0.315275 | 2.99589 | 4(Loss) | true |
| simdjson (ondemand) | 793.692 | 0.164406 | 675.192ms | 4630 | 160 | 13384.9 | 5563.26 | 0.320192 | 3.1046 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1790.51 | 0.0700989 | 250.763ms | 4630 | 30 | 89.6506 | 2466.07 | 0.0391834 | 1.36772 | 1(Win) | true |
| Glaze | 1413.1 | 0.121671 | 317.668ms | 4630 | 40 | 578.164 | 3124.7 | 0.254309 | 1.73741 | 2(Loss) | true |
| simdjson (reflection) | 1303.54 | 0.040328 | 371.846ms | 4630 | 80 | 149.285 | 3387.32 | 0.0435637 | 1.88449 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1817.34 | 0.0378929 | 242.802ms | 4630 | 160 | 135.621 | 2429.66 | 0.040627 | 1.34687 | 1(Win) | true |
| Glaze | 1502.48 | 0.0657854 | 303.294ms | 4630 | 80 | 299.015 | 2938.81 | 0.0966459 | 1.63242 | 2(Loss) | true |
| simdjson (reflection) | 1314.62 | 0.0409486 | 336.34ms | 4630 | 40 | 75.666 | 3358.78 | 0.147406 | 1.86869 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1917.35 | 0.28149 | 581.814ms | 11579 | 2560 | 672832 | 5759.3 | 0.0609305 | 1.2853 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1904.36 | 0.308125 | 578.48ms | 11579 | 640 | 204304 | 5798.58 | 0.691291 | 1.29399 | 1(Tie) | true |
| simdjson (ondemand) | 1713.23 | 0.0778911 | 673.545ms | 11579 | 40 | 1008.21 | 6445.5 | 0.00930795 | 1.43899 | 3(Loss) | true |
| simdjson (reflection) | 1691.3 | 0.208135 | 658.015ms | 11579 | 2560 | 472753 | 6529.07 | 0.0427538 | 1.45792 | 4(Loss) | true |
| Glaze | 1514.76 | 0.0441761 | 756.745ms | 11579 | 40 | 414.846 | 7289.98 | 0.329961 | 1.629 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2363.52 | 0.171652 | 557.602ms | 11579 | 80 | 5145.27 | 4672.09 | 0.291671 | 1.04149 | 1(Win) | true |
| Jsonifier (two-stage) | 2301.85 | 0.0456141 | 555.377ms | 11579 | 30 | 143.651 | 4797.27 | 0.146827 | 1.06971 | 2(Loss) | true |
| simdjson (ondemand) | 1895.97 | 0.0687437 | 681.58ms | 11579 | 40 | 641.218 | 5824.25 | 0.036901 | 1.30043 | 3(Loss) | true |
| simdjson (reflection) | 1872.27 | 0.0814026 | 658.434ms | 11579 | 40 | 922.025 | 5897.98 | 0.146023 | 1.31632 | 4(Loss) | true |
| Glaze | 1582.47 | 0.170025 | 774.881ms | 11579 | 2560 | 360361 | 6978.1 | 1.44171 | 1.55839 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5692.19 | 0.057141 | 252.792ms | 14795 | 30 | 60.1851 | 2478.77 | 0.0671926 | 0.430132 | 1(Win) | true |
| Glaze | 3429.47 | 0.0773605 | 418.695ms | 14795 | 40 | 405.204 | 4114.23 | 0.0419453 | 0.717254 | 2(Loss) | true |
| simdjson (reflection) | 486.683 | 0.199983 | 2951.47ms | 14795 | 640 | 2.15131e+06 | 28991.4 | 0.981593 | 5.08245 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5793.01 | 0.0579647 | 257.574ms | 14795 | 40 | 79.7276 | 2435.62 | 0.0290737 | 0.423107 | 1(Win) | true |
| Glaze | 3629.47 | 0.315082 | 407.514ms | 14795 | 1280 | 192044 | 3887.51 | 0.0464443 | 0.677418 | 2(Loss) | true |
| simdjson (reflection) | 474.27 | 0.111014 | 3007.69ms | 14795 | 2560 | 2.79239e+06 | 29750.2 | 0.358804 | 5.21551 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1921.3 | 0.155568 | 168.901ms | 3223 | 30 | 185.821 | 1599.8 | 0.233908 | 1.26678 | 1(Win) | true |
| Jsonifier (two-stage) | 1596.37 | 0.147883 | 197.241ms | 3223 | 40 | 324.302 | 1925.42 | 0.148673 | 1.52827 | 2(Loss) | true |
| simdjson (ondemand) | 1412.59 | 0.0618005 | 225.949ms | 3223 | 320 | 578.663 | 2175.93 | 0.297404 | 1.73165 | 3(Loss) | true |
| Glaze | 1317.32 | 0.103357 | 237.636ms | 3223 | 80 | 465.271 | 2333.29 | 0.682643 | 1.8578 | 4(Loss) | true |
| simdjson (reflection) | 1304.4 | 0.155429 | 239.467ms | 3223 | 80 | 1073.13 | 2356.4 | 0.752523 | 1.87647 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2234.28 | 0.0555492 | 153.907ms | 3223 | 80 | 46.719 | 1375.7 | 0.134296 | 1.0858 | 1(Win) | true |
| Jsonifier (two-stage) | 1931.17 | 0.0760461 | 182.223ms | 3223 | 80 | 117.199 | 1591.62 | 0.128634 | 1.26025 | 2(Loss) | true |
| simdjson (ondemand) | 1602.91 | 0.106337 | 252.074ms | 3223 | 30 | 124.737 | 1917.57 | 0.0156424 | 1.52487 | 3(Loss) | true |
| Glaze | 1487.46 | 0.0818677 | 224.954ms | 3223 | 80 | 228.952 | 2066.4 | 0.30581 | 1.64231 | 4(Loss) | true |
| simdjson (reflection) | 1397.8 | 0.3223 | 246.003ms | 3223 | 1280 | 64293 | 2198.96 | 0.201748 | 1.74943 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7730.61 | 0.278298 | 43.9805ms | 3223 | 30 | 36.731 | 397.6 | 0.342552 | 0.298459 | 1(Win) | true |
| simdjson (reflection) | 7654.93 | 0.158466 | 43.8629ms | 3223 | 160 | 64.7789 | 401.531 | 0.295054 | 0.30282 | 2(Loss) | true |
| Glaze | 2396.65 | 0.115946 | 127.627ms | 3223 | 160 | 353.786 | 1282.49 | 0.37715 | 1.01122 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9043.1 | 0.113726 | 37.3235ms | 3223 | 160 | 23.9069 | 339.894 | 0.0716622 | 0.252019 | 1(Win) | true |
| simdjson (reflection) | 8840.05 | 0.0537593 | 41.6362ms | 3223 | 1280 | 44.7228 | 347.701 | 0.108856 | 0.258181 | 2(Loss) | true |
| Glaze | 2649.42 | 0.168257 | 115.535ms | 3223 | 80 | 304.829 | 1160.14 | 0.273342 | 0.911856 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2589.97 | 0.0826442 | 221.418ms | 5839 | 80 | 252.582 | 2150.03 | 0.220249 | 0.943267 | 1(Win) | true |
| Jsonifier | 2532.36 | 0.375238 | 227.329ms | 5839 | 80 | 5446.64 | 2198.94 | 0.25798 | 0.965576 | 2(Loss) | true |
| simdjson (reflection) | 2267.33 | 0.134076 | 252.723ms | 5839 | 40 | 433.717 | 2455.97 | 0.0701876 | 1.07989 | 3(Loss) | true |
| simdjson (ondemand) | 2238.66 | 0.163357 | 250.227ms | 5839 | 4890 | 80739.5 | 2487.42 | 0.325969 | 1.09362 | 4(Loss) | true |
| Glaze | 1863.4 | 0.284306 | 311.125ms | 5839 | 1280 | 92395 | 2988.36 | 0.0731495 | 1.31687 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2960.66 | 0.13614 | 226.395ms | 5839 | 30 | 196.695 | 1880.83 | 0.425299 | 0.823463 | 1(Win) | true |
| Jsonifier | 2781.84 | 0.098086 | 215.422ms | 5839 | 30 | 115.651 | 2001.73 | 0.42779 | 0.87749 | 2(Loss) | true |
| simdjson (ondemand) | 2535.86 | 0.0816198 | 236.914ms | 5839 | 30 | 96.369 | 2195.9 | 0.0621985 | 0.964029 | 3(Loss) | true |
| simdjson (reflection) | 2433.63 | 0.109162 | 258.99ms | 5839 | 80 | 499.116 | 2288.15 | 0.176216 | 1.00538 | 4(Loss) | true |
| Glaze | 2020.75 | 0.228436 | 297.67ms | 5839 | 4890 | 193771 | 2755.66 | 1.10769 | 1.21314 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14662.4 | 0.212718 | 48.1697ms | 6938 | 80 | 73.715 | 451.262 | 0.0193938 | 0.158785 | 1(Win) | true |
| Glaze | 3965.75 | 0.211454 | 175.59ms | 6960 | 40 | 501.025 | 1673.72 | 0.503805 | 0.614501 | 2(Loss) | true |
| simdjson (reflection) | 565.599 | 0.420993 | 1205.02ms | 6938 | 640 | 1.55233e+06 | 11698.4 | 0.169327 | 4.36747 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16799.2 | 0.208828 | 41.8486ms | 6938 | 80 | 54.1201 | 393.863 | 0.502084 | 0.137648 | 1(Win) | true |
| Glaze | 4583.41 | 0.0831481 | 171.589ms | 6960 | 80 | 115.994 | 1448.17 | 0.229073 | 0.530442 | 2(Loss) | true |
| simdjson (reflection) | 553.982 | 0.134768 | 1204.95ms | 6938 | 2560 | 663269 | 11943.7 | 0.662093 | 4.45905 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1936.72 | 0.119333 | 241.334ms | 4857 | 30 | 244.368 | 2391.67 | 0.12699 | 1.2642 | 1(Win) | true |
| Glaze | 1624.3 | 0.542671 | 291.869ms | 4857 | 640 | 153269 | 2851.68 | 0.0590311 | 1.50973 | 2(Loss) | true |
| simdjson (reflection) | 1594.82 | 0.168461 | 307.873ms | 4857 | 30 | 718.179 | 2904.4 | 0.989739 | 1.53792 | 3(Loss) | true |
| Jsonifier (two-stage) | 1565.26 | 0.0927713 | 293.225ms | 4857 | 40 | 301.474 | 2959.25 | 0.398643 | 1.56618 | 4(Loss) | true |
| simdjson (ondemand) | 1338.97 | 0.148662 | 362.127ms | 4857 | 40 | 1057.93 | 3459.38 | 0.227194 | 1.83436 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2562.29 | 0.0732102 | 206.19ms | 4857 | 160 | 280.248 | 1807.76 | 0.0252321 | 0.951292 | 1(Win) | true |
| Glaze | 2009.17 | 0.142522 | 254.269ms | 4857 | 40 | 431.84 | 2305.43 | 0.0126529 | 1.21768 | 2(Loss) | true |
| Jsonifier (two-stage) | 1915.37 | 0.124488 | 263.934ms | 4857 | 40 | 362.533 | 2418.32 | 0.288964 | 1.27765 | 3(Loss) | true |
| simdjson (reflection) | 1796.65 | 0.109552 | 280.829ms | 4857 | 40 | 319.087 | 2578.12 | 0.190098 | 1.36341 | 4(Loss) | true |
| simdjson (ondemand) | 1578.36 | 0.0571172 | 320.688ms | 4857 | 80 | 224.775 | 2934.69 | 0.677311 | 1.55419 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11206.4 | 0.429876 | 43.6314ms | 4857 | 30 | 94.7126 | 413.333 | 0.0241994 | 0.206609 | 1(Win) | true |
| simdjson (reflection) | 8258.89 | 0.212944 | 58.6093ms | 4857 | 40 | 57.0538 | 560.85 | 0.0623664 | 0.285964 | 2(Loss) | true |
| Glaze | 3790.81 | 0.308799 | 123.784ms | 4857 | 2560 | 36447 | 1221.9 | 0.125602 | 0.638276 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12724.4 | 0.236165 | 38.7175ms | 4857 | 40 | 29.5635 | 364.025 | 0.0571978 | 0.179957 | 1(Win) | true |
| simdjson (reflection) | 9428.52 | 0.229668 | 51.8535ms | 4857 | 40 | 50.9224 | 491.275 | 0.282476 | 0.248888 | 2(Loss) | true |
| Glaze | 4626.91 | 0.276639 | 106.052ms | 4857 | 30 | 230.093 | 1001.1 | 0.0266445 | 0.521007 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2221.62 | 0.543537 | 323.908ms | 6701 | 640 | 156451 | 2876.54 | 0.69771 | 1.10374 | 1(Win) | true |
| Jsonifier (two-stage) | 2122.27 | 0.284877 | 306.722ms | 6701 | 1280 | 94189.5 | 3011.2 | 0.170801 | 1.15613 | 2(Loss) | true |
| simdjson (reflection) | 2059.18 | 0.178878 | 322.36ms | 6701 | 40 | 1232.72 | 3103.45 | 0.0488465 | 1.19116 | 3(Loss) | true |
| Glaze | 1819.74 | 0.478929 | 353.399ms | 6701 | 320 | 90521.4 | 3511.8 | 0.744915 | 1.34991 | 4(Loss) | true |
| simdjson (ondemand) | 1785.02 | 0.220885 | 362.705ms | 6701 | 4890 | 305799 | 3580.12 | 0.260401 | 1.37672 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2854.03 | 0.0758653 | 246.228ms | 6701 | 80 | 230.854 | 2239.14 | 0.022883 | 0.857366 | 1(Win) | true |
| Jsonifier (two-stage) | 2511.12 | 0.0396582 | 277.814ms | 6701 | 160 | 162.979 | 2544.91 | 0.209434 | 0.975017 | 2(Loss) | true |
| simdjson (reflection) | 2390.78 | 0.0495395 | 295.119ms | 6701 | 320 | 561.116 | 2673.01 | 0.065044 | 1.02518 | 3(Loss) | true |
| Glaze | 2303.44 | 0.457943 | 300.92ms | 6701 | 1280 | 206613 | 2774.35 | 0.132413 | 1.06431 | 4(Loss) | true |
| simdjson (ondemand) | 2085.34 | 0.0427582 | 361.304ms | 6701 | 160 | 274.716 | 3064.53 | 0.123032 | 1.17678 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15901.3 | 0.0492648 | 47.3976ms | 7376 | 640 | 30.3971 | 442.373 | 0.158134 | 0.145994 | 1(Win) | true |
| Glaze | 3983.35 | 0.224555 | 177.373ms | 7376 | 80 | 1257.99 | 1765.92 | 0.183701 | 0.611909 | 2(Loss) | true |
| simdjson (reflection) | 538.689 | 0.117889 | 1298.82ms | 7376 | 2560 | 606671 | 13058.2 | 0.0179936 | 4.5862 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17044.7 | 0.0612566 | 43.9933ms | 7376 | 640 | 40.9027 | 412.698 | 0.217979 | 0.135388 | 1(Win) | true |
| Glaze | 4584.8 | 0.162289 | 160.842ms | 7376 | 30 | 185.995 | 1534.27 | 0.15185 | 0.530613 | 2(Loss) | true |
| simdjson (reflection) | 554.819 | 0.177192 | 1298.32ms | 7376 | 2560 | 1.29202e+06 | 12678.6 | 0.675233 | 4.45312 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2196.79 | 0.320575 | 76.9879ms | 1691 | 40 | 221.528 | 734.1 | 0.0499228 | 1.08659 | 1(Win) | true |
| Glaze | 2007.42 | 0.0972336 | 84.5307ms | 1691 | 80 | 48.8127 | 803.35 | 0.0497667 | 1.19212 | 2(Loss) | true |
| simdjson (reflection) | 1758.9 | 0.0845186 | 94.6171ms | 1691 | 320 | 192.159 | 916.859 | 0.0508106 | 1.36534 | 3(Loss) | true |
| Jsonifier (two-stage) | 1589.61 | 0.195649 | 103.238ms | 1691 | 30 | 118.19 | 1014.5 | 0.260245 | 1.51648 | 4(Loss) | true |
| simdjson (ondemand) | 1295.08 | 0.0931081 | 132.414ms | 1691 | 320 | 430.148 | 1245.22 | 0.17321 | 1.87075 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2728.7 | 0.11974 | 68.0096ms | 1691 | 160 | 80.1258 | 591 | 0.254453 | 0.86298 | 1(Win) | true |
| Glaze | 2334.15 | 0.101389 | 78.0077ms | 1691 | 80 | 39.2557 | 690.9 | 0.23212 | 1.02161 | 2(Loss) | true |
| Jsonifier (two-stage) | 2108.5 | 0.0528446 | 90.8319ms | 1691 | 320 | 52.2745 | 764.837 | 0.14157 | 1.13435 | 3(Loss) | true |
| simdjson (reflection) | 1992.45 | 0.214069 | 87.6573ms | 1691 | 80 | 240.164 | 809.388 | 0.196521 | 1.19925 | 4(Loss) | true |
| simdjson (ondemand) | 1444.85 | 0.270666 | 121.303ms | 1691 | 2560 | 23364 | 1116.14 | 0.120073 | 1.67129 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14138 | 0.107605 | 16.2873ms | 1996 | 1280 | 26.8671 | 134.64 | 0.242552 | 0.14103 | 1(Win) | true |
| simdjson (reflection) | 10982.4 | 0.0790766 | 19.9335ms | 1996 | 2560 | 48.0906 | 173.325 | 0.13976 | 0.192145 | 2(Loss) | true |
| Glaze | 5598.53 | 0.280132 | 36.8625ms | 1996 | 640 | 580.601 | 340.006 | 0.0854034 | 0.406752 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14519.5 | 0.0908154 | 15.8399ms | 1996 | 1280 | 18.1445 | 131.102 | 0.171329 | 0.134163 | 1(Win) | true |
| simdjson (reflection) | 12500.8 | 0.127921 | 17.9313ms | 1996 | 640 | 24.2835 | 152.273 | 0.0605041 | 0.163839 | 2(Loss) | true |
| Glaze | 6674.42 | 0.0743372 | 31.4225ms | 1996 | 640 | 28.7665 | 285.198 | 0.0279489 | 0.336168 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2384.88 | 0.184276 | 89.4285ms | 2158 | 80 | 202.301 | 862.95 | 0.0724785 | 1.00656 | 1(Win) | true |
| Glaze | 2172.81 | 0.123995 | 98.0137ms | 2158 | 40 | 55.1737 | 947.175 | 0.00791891 | 1.1078 | 2(Loss) | true |
| Jsonifier | 2143.57 | 0.0413112 | 98.0079ms | 2158 | 640 | 100.68 | 960.094 | 0.445947 | 1.12178 | 3(Loss) | true |
| Jsonifier (two-stage) | 1909.24 | 0.121645 | 110.706ms | 2158 | 30 | 51.5816 | 1077.93 | 0.345146 | 1.26345 | 4(Loss) | true |
| simdjson (ondemand) | 1635.25 | 0.177582 | 127.143ms | 2158 | 80 | 399.594 | 1258.54 | 0.11236 | 1.48174 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3045.92 | 0.243071 | 75.515ms | 2158 | 30 | 80.9195 | 675.667 | 0.15762 | 0.77941 | 1(Win) | true |
| Glaze | 2574.98 | 0.0483703 | 87.3038ms | 2158 | 320 | 47.8259 | 799.241 | 0.0504131 | 0.930539 | 2(Loss) | true |
| simdjson (reflection) | 2534.67 | 0.205782 | 87.3688ms | 2158 | 80 | 223.339 | 811.95 | 0.490226 | 0.944972 | 3(Loss) | true |
| Jsonifier (two-stage) | 2355.87 | 0.173116 | 94.034ms | 2158 | 40 | 91.4814 | 873.575 | 0.124809 | 1.02069 | 4(Loss) | true |
| simdjson (ondemand) | 1883.28 | 0.209476 | 121.443ms | 2158 | 80 | 419.207 | 1092.79 | 0.292539 | 1.28307 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15298.8 | 0.13284 | 20.2914ms | 2866 | 640 | 36.0475 | 178.656 | 0.0507002 | 0.138198 | 1(Win) | true |
| Glaze | 4432.75 | 0.266046 | 65.9378ms | 2866 | 30 | 80.731 | 616.6 | 0.325415 | 0.534275 | 2(Loss) | true |
| simdjson (reflection) | 610.532 | 0.113254 | 457.03ms | 2866 | 30 | 771.2 | 4476.8 | 0.306962 | 4.03088 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20143.9 | 0.0895984 | 16.246ms | 2866 | 2560 | 37.836 | 135.685 | 0.136274 | 0.0990487 | 1(Win) | true |
| Glaze | 5304.28 | 0.114665 | 54.4632ms | 2866 | 80 | 27.929 | 515.288 | 0.24441 | 0.441543 | 2(Loss) | true |
| simdjson (reflection) | 596.046 | 0.107759 | 455.08ms | 2866 | 30 | 732.524 | 4585.6 | 0.0283416 | 4.12918 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1761.98 | 0.0803894 | 234.821ms | 4390 | 80 | 291.889 | 2376.1 | 0.0946034 | 1.38926 | 1(Win) | true |
| Jsonifier (two-stage) | 1581.27 | 0.0460231 | 268.976ms | 4390 | 160 | 237.568 | 2647.63 | 0.475551 | 1.55031 | 2(Loss) | true |
| Glaze | 1562.19 | 0.381257 | 280.996ms | 4390 | 1280 | 133631 | 2679.97 | 0.368771 | 1.56949 | 3(Loss) | true |
| simdjson (reflection) | 1516.77 | 0.0634722 | 285.666ms | 4390 | 160 | 491.106 | 2760.22 | 0.15739 | 1.61738 | 4(Loss) | true |
| simdjson (ondemand) | 1306.69 | 0.243874 | 330.968ms | 4390 | 1280 | 78150 | 3204.01 | 0.118972 | 1.87716 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1999.65 | 0.26921 | 234.022ms | 4390 | 1280 | 40664.3 | 2093.68 | 0.746317 | 1.22274 | 1(Win) | true |
| Glaze | 1707.57 | 0.135723 | 271.303ms | 4390 | 40 | 442.933 | 2451.8 | 0.378018 | 1.43618 | 2(Loss) | true |
| Jsonifier (two-stage) | 1677.66 | 0.152446 | 268.419ms | 4390 | 4890 | 70772.6 | 2495.52 | 0.543117 | 1.45989 | 3(Loss) | true |
| simdjson (reflection) | 1552.98 | 0.0707501 | 285.659ms | 4390 | 80 | 291.031 | 2695.86 | 0.000463676 | 1.5787 | 4(Loss) | true |
| simdjson (ondemand) | 1317.36 | 0.216755 | 331.369ms | 4390 | 4890 | 232043 | 3178.05 | 0.0190904 | 1.86306 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13516.4 | 0.139775 | 34.9936ms | 4390 | 160 | 29.9905 | 309.744 | 0.0705731 | 0.167866 | 1(Win) | true |
| simdjson (reflection) | 11216.2 | 0.225771 | 39.9534ms | 4390 | 30 | 21.3057 | 373.267 | 0 | 0.204905 | 2(Loss) | true |
| Glaze | 3645.82 | 0.174612 | 115.838ms | 4390 | 80 | 321.644 | 1148.34 | 0.118509 | 0.662574 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13890.1 | 0.0407023 | 32.9672ms | 4390 | 1280 | 19.2648 | 301.41 | 0.138996 | 0.162659 | 1(Win) | true |
| simdjson (reflection) | 11191.2 | 0.142783 | 41.4986ms | 4390 | 80 | 22.8253 | 374.1 | 0.456498 | 0.205339 | 2(Loss) | true |
| Glaze | 3588.25 | 0.244698 | 106.871ms | 4390 | 160 | 1304.21 | 1166.76 | 0.195365 | 0.672462 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3131.72 | 0.240947 | 288.731ms | 9378 | 40 | 1893.91 | 2855.8 | 0.0175113 | 0.783205 | 1(Win) | true |
| simdjson (reflection) | 2936.91 | 0.0733697 | 310.105ms | 9378 | 160 | 798.716 | 3045.22 | 0.115066 | 0.835775 | 2(Loss) | true |
| Jsonifier (two-stage) | 2866.74 | 0.0974745 | 316.93ms | 9378 | 30 | 277.426 | 3119.77 | 0.140164 | 0.856586 | 3(Loss) | true |
| Glaze | 2498.43 | 0.0546158 | 360.033ms | 9378 | 40 | 152.892 | 3579.68 | 0.148536 | 0.983576 | 4(Loss) | true |
| simdjson (ondemand) | 2439.87 | 0.257546 | 372.767ms | 9378 | 1280 | 114079 | 3665.58 | 0.644717 | 1.00729 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3288.22 | 0.108415 | 305.912ms | 9378 | 40 | 347.804 | 2719.88 | 0.200472 | 0.745636 | 1(Win) | true |
| simdjson (reflection) | 3084.62 | 0.077539 | 310.318ms | 9378 | 30 | 151.628 | 2899.4 | 0.0103459 | 0.79641 | 2(Loss) | true |
| Jsonifier (two-stage) | 3035.35 | 0.104774 | 313.868ms | 9378 | 30 | 285.913 | 2946.47 | 0.159259 | 0.808069 | 3(Loss) | true |
| Glaze | 2671.5 | 0.0782699 | 354.519ms | 9378 | 30 | 205.978 | 3347.77 | 0.0089604 | 0.92005 | 4(Loss) | true |
| simdjson (ondemand) | 2615.28 | 0.0610502 | 353.824ms | 9378 | 160 | 697.393 | 3419.73 | 0.708632 | 0.939227 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 29055.5 | 0.0781444 | 40.3772ms | 11521 | 640 | 55.8856 | 378.148 | 0.0202426 | 0.0794457 | 1(Win) | true |
| Glaze | 5555.54 | 0.580778 | 199.165ms | 11521 | 640 | 84436.3 | 1977.72 | 0.0940255 | 0.439664 | 2(Loss) | true |
| simdjson (reflection) | 596.598 | 0.207347 | 1881.15ms | 11521 | 1280 | 1.86647e+06 | 18416.6 | 0.0145017 | 4.14405 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 29774.8 | 0.164078 | 39.4533ms | 11521 | 1280 | 469.242 | 369.013 | 0.0378823 | 0.0771059 | 1(Win) | true |
| Glaze | 6178.05 | 0.063577 | 179.671ms | 11521 | 80 | 102.275 | 1778.44 | 0.085119 | 0.39478 | 2(Loss) | true |
| simdjson (reflection) | 591.668 | 0.429743 | 1954.76ms | 11521 | 320 | 2.03795e+06 | 18570 | 0.00107702 | 4.17853 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3189.94 | 0.217669 | 141.435ms | 4669 | 2560 | 23632.8 | 1395.86 | 0.125809 | 0.760713 | 1(Win) | true |
| Jsonifier (two-stage) | 2449.16 | 0.0595414 | 187.693ms | 4669 | 160 | 187.487 | 1818.06 | 0.183581 | 0.99652 | 2(Loss) | true |
| Glaze | 1679.65 | 0.0847533 | 277.716ms | 4669 | 40 | 201.922 | 2650.97 | 0.113609 | 1.45908 | 3(Loss) | true |
| simdjson (reflection) | 1658.02 | 0.0760316 | 273.421ms | 4669 | 80 | 333.54 | 2685.56 | 0.158971 | 1.47908 | 4(Loss) | true |
| simdjson (ondemand) | 1143.15 | 0.121615 | 393.62ms | 4669 | 4890 | 109729 | 3895.12 | 0.088613 | 2.15138 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3812.29 | 0.0616134 | 127.405ms | 4669 | 80 | 41.4302 | 1167.99 | 0.0610396 | 0.635406 | 1(Win) | true |
| Jsonifier (two-stage) | 2692.41 | 0.12498 | 171.791ms | 4669 | 30 | 128.166 | 1653.8 | 0.0605034 | 0.905412 | 2(Loss) | true |
| Glaze | 1774.13 | 0.0823542 | 259.793ms | 4669 | 30 | 128.166 | 2509.8 | 0.119389 | 1.3808 | 3(Loss) | true |
| simdjson (reflection) | 1713.44 | 0.245992 | 269.856ms | 4669 | 2560 | 104614 | 2598.69 | 0.00652415 | 1.43051 | 4(Loss) | true |
| simdjson (ondemand) | 1241.33 | 0.341574 | 368.363ms | 4669 | 1280 | 192155 | 3587.03 | 0.0152218 | 1.98008 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12712 | 0.147512 | 37.9226ms | 4669 | 160 | 42.7164 | 350.275 | 0.0749973 | 0.180701 | 1(Win) | true |
| simdjson (reflection) | 8679.21 | 0.0917357 | 54.0454ms | 4669 | 160 | 35.4393 | 513.031 | 0.144762 | 0.270366 | 2(Loss) | true |
| Glaze | 2051.21 | 0.126856 | 221.231ms | 4669 | 80 | 606.658 | 2170.78 | 0.265328 | 1.19202 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15013.8 | 0.169584 | 32.7436ms | 4669 | 160 | 40.4723 | 296.575 | 0.126604 | 0.150605 | 1(Win) | true |
| simdjson (reflection) | 9876.52 | 0.1162 | 47.6834ms | 4669 | 160 | 43.9105 | 450.837 | 0.00277269 | 0.236013 | 2(Loss) | true |
| Glaze | 2163.06 | 0.147682 | 209.516ms | 4669 | 80 | 739.366 | 2058.53 | 0.0072873 | 1.13028 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3534.85 | 0.0624094 | 209.947ms | 7932 | 80 | 142.696 | 2139.99 | 0.26623 | 0.691566 | 1(Win) | true |
| Jsonifier (two-stage) | 3437.8 | 0.0775888 | 219.546ms | 7932 | 80 | 233.18 | 2200.4 | 0.0635843 | 0.711242 | 2(Loss) | true |
| simdjson (reflection) | 2552.36 | 0.0925516 | 296.04ms | 7932 | 40 | 300.962 | 2963.75 | 0.200034 | 0.961539 | 3(Loss) | true |
| Glaze | 2158.48 | 0.218848 | 358.663ms | 7932 | 40 | 2352.97 | 3504.57 | 0.0871908 | 1.13887 | 4(Loss) | true |
| simdjson (ondemand) | 1731.16 | 0.107853 | 438.965ms | 7932 | 30 | 666.309 | 4369.63 | 0.0602281 | 1.42094 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3857.1 | 0.0749696 | 197.77ms | 7932 | 40 | 86.4718 | 1961.2 | 0.0272016 | 0.632864 | 1(Win) | true |
| Jsonifier (two-stage) | 3818.34 | 0.326108 | 206.421ms | 7932 | 4890 | 204103 | 1981.11 | 0.44803 | 0.639502 | 2(Loss) | true |
| simdjson (reflection) | 2743.54 | 0.0693626 | 292.72ms | 7932 | 80 | 292.607 | 2757.22 | 0.0154117 | 0.893857 | 3(Loss) | true |
| Glaze | 2252.4 | 0.0858329 | 337.63ms | 7932 | 30 | 249.289 | 3358.43 | 0.199101 | 1.09064 | 4(Loss) | true |
| simdjson (ondemand) | 1941.98 | 0.166797 | 428.952ms | 7932 | 30 | 1266.41 | 3895.27 | 0.151237 | 1.26633 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20432.8 | 0.0905029 | 46.0195ms | 9249 | 320 | 48.8436 | 431.684 | 0.149625 | 0.113869 | 1(Win) | true |
| Glaze | 3236.77 | 0.213779 | 267.02ms | 9249 | 30 | 1018.16 | 2725.1 | 0.293201 | 0.757303 | 2(Loss) | true |
| simdjson (reflection) | 547.165 | 0.712432 | 1647.5ms | 9249 | 160 | 2.11038e+06 | 16120.4 | 0.172194 | 4.51723 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23565.8 | 0.133345 | 40.5439ms | 9249 | 160 | 39.8566 | 374.294 | 0.214943 | 0.0975187 | 1(Win) | true |
| Glaze | 3730.7 | 0.0951832 | 251.148ms | 9249 | 80 | 405.154 | 2364.31 | 0.159391 | 0.656306 | 2(Loss) | true |
| simdjson (reflection) | 555.589 | 0.0537196 | 1626.68ms | 9249 | 30 | 2182.07 | 15876 | 0.0798487 | 4.44913 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 877.353 | 0.29374 | 508.145ms | 4604 | 640 | 138302 | 5004.51 | 0.469052 | 2.80685 | 1(Win) | true |
| Jsonifier (two-stage) | 745.972 | 0.0694433 | 568.112ms | 4604 | 30 | 501.197 | 5885.9 | 0.0554691 | 3.3029 | 2(Loss) | true |
| simdjson (reflection) | 660.417 | 0.205073 | 668.419ms | 4604 | 4890 | 908991 | 6648.4 | 0.00847085 | 3.73421 | 3(Loss) | true |
| Glaze | 632.134 | 0.13405 | 665.898ms | 4604 | 30 | 2600.81 | 6945.87 | 0.172467 | 3.9011 | 4(Loss) | true |
| simdjson (ondemand) | 526.555 | 0.32151 | 863.395ms | 4604 | 640 | 459995 | 8338.58 | 0.183615 | 4.68732 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1086.98 | 0.0881923 | 532.114ms | 4604 | 30 | 380.723 | 4039.37 | 0.025575 | 2.26284 | 1(Win) | true |
| Jsonifier (two-stage) | 899.356 | 0.099579 | 563.935ms | 4604 | 30 | 709.03 | 4882.07 | 0.381573 | 2.7374 | 2(Loss) | true |
| Glaze | 757.815 | 0.138478 | 671.794ms | 4604 | 4890 | 314784 | 5793.91 | 0.0854511 | 3.25242 | 3(Loss) | true |
| simdjson (reflection) | 727.735 | 0.128753 | 678.227ms | 4604 | 160 | 9655.22 | 6033.4 | 0.0816956 | 3.38755 | 4(Loss) | true |
| simdjson (ondemand) | 572.031 | 0.431108 | 856.104ms | 4604 | 160 | 175196 | 7675.66 | 0.364353 | 4.31345 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1614.86 | 0.0461184 | 295.071ms | 4918 | 80 | 143.531 | 2904.39 | 0.0511894 | 1.5186 | 1(Win) | true |
| simdjson (reflection) | 1431.24 | 0.0471841 | 331.351ms | 4918 | 30 | 71.7241 | 3277 | 0.0223832 | 1.71551 | 2(Loss) | true |
| Glaze | 1064.97 | 0.126679 | 423.221ms | 4604 | 30 | 818.326 | 4122.87 | 0.0404086 | 2.30953 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.5 | 0.0478713 | 290.799ms | 4918 | 40 | 74.4718 | 2850.3 | 0.093645 | 1.48992 | 1(Win) | true |
| simdjson (reflection) | 1547.45 | 0.0599117 | 307.175ms | 4918 | 30 | 98.9207 | 3030.9 | 0.208292 | 1.58635 | 2(Loss) | true |
| Glaze | 1133.52 | 0.14108 | 393.555ms | 4604 | 30 | 895.913 | 3873.53 | 0.0146271 | 2.16817 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2699.01 | 0.0895383 | 648.55ms | 18245 | 30 | 999.582 | 6446.73 | 0.186825 | 0.913874 | 1(Win) | true |
| Jsonifier | 2555.69 | 0.0878715 | 699.645ms | 18245 | 30 | 1073.72 | 6808.27 | 0.230559 | 0.965127 | 2(Loss) | true |
| simdjson (reflection) | 2342.77 | 0.180183 | 760.466ms | 18245 | 40 | 7163.33 | 7427 | 0.0479999 | 1.05317 | 3(Loss) | true |
| simdjson (ondemand) | 1823.55 | 0.11657 | 939.065ms | 18245 | 30 | 3711.46 | 9541.7 | 0.695218 | 1.35393 | 4(Loss) | true |
| Glaze | 1791.94 | 0.0824252 | 972.465ms | 18245 | 30 | 1921.69 | 9710.03 | 0.0628611 | 1.37791 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3117.29 | 0.0780698 | 666.487ms | 18245 | 30 | 569.666 | 5581.7 | 0.0418208 | 0.790516 | 1(Win) | true |
| Jsonifier | 2896.99 | 0.209093 | 683.318ms | 18245 | 1280 | 201875 | 6006.17 | 0.010329 | 0.850952 | 2(Loss) | true |
| simdjson (reflection) | 2586.94 | 0.155291 | 754.517ms | 18245 | 80 | 8727.61 | 6726.01 | 0.314019 | 0.953262 | 3(Loss) | true |
| simdjson (ondemand) | 1977.27 | 0.177415 | 947.87ms | 18245 | 30 | 7312.37 | 8799.9 | 0.19698 | 1.24838 | 4(Loss) | true |
| Glaze | 1959.71 | 0.139914 | 977.757ms | 18245 | 4890 | 754628 | 8878.75 | 0.0626721 | 1.25967 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8133.1 | 0.0790196 | 307.134ms | 24893 | 80 | 425.6 | 2918.91 | 0.1031 | 0.301779 | 1(Win) | true |
| Glaze | 3772.94 | 0.0737289 | 631.543ms | 24579 | 80 | 1678.54 | 6212.75 | 0.042636 | 0.653183 | 2(Loss) | true |
| simdjson (reflection) | 567.603 | 0.273852 | 4286.81ms | 24893 | 160 | 2.09901e+06 | 41824.7 | 0.225719 | 4.35895 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7980.14 | 0.0318661 | 299.55ms | 24893 | 80 | 71.8922 | 2974.86 | 0.0718005 | 0.307488 | 1(Win) | true |
| Glaze | 3894.68 | 0.626632 | 587.569ms | 24579 | 320 | 455156 | 6018.56 | 0.399449 | 0.63279 | 2(Loss) | true |
| simdjson (reflection) | 541.151 | 0.15415 | 4461.71ms | 24893 | 640 | 2.92674e+06 | 43869.1 | 0.979583 | 4.57226 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 950.938 | 0.111703 | 478.61ms | 4604 | 40 | 1064.04 | 4617.25 | 0.128699 | 2.58799 | 1(Win) | true |
| Jsonifier (two-stage) | 769.702 | 0.142167 | 563.842ms | 4604 | 4890 | 321610 | 5704.43 | 0.173526 | 3.20067 | 2(Loss) | true |
| simdjson (reflection) | 654.994 | 0.151351 | 699.847ms | 4604 | 4890 | 503354 | 6703.44 | 0.466 | 3.76443 | 3(Loss) | true |
| Glaze | 639.769 | 0.190692 | 689.758ms | 4604 | 1280 | 219229 | 6862.97 | 0.00561241 | 3.85448 | 4(Loss) | true |
| simdjson (ondemand) | 505.279 | 0.23845 | 895.405ms | 4604 | 1280 | 549557 | 8689.69 | 0.0279144 | 4.88467 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1166.69 | 0.102101 | 461.621ms | 4604 | 30 | 442.938 | 3763.4 | 0.147247 | 2.10641 | 1(Win) | true |
| Jsonifier (two-stage) | 920.601 | 0.109178 | 594.902ms | 4604 | 30 | 813.421 | 4769.4 | 0.130524 | 2.6734 | 2(Loss) | true |
| simdjson (reflection) | 758.654 | 0.382902 | 668.32ms | 4604 | 640 | 314296 | 5787.51 | 0.0588745 | 3.24884 | 3(Loss) | true |
| Glaze | 738.946 | 0.0805985 | 709.302ms | 4604 | 80 | 1834.8 | 5941.86 | 0.00988649 | 3.33538 | 4(Loss) | true |
| simdjson (ondemand) | 522.744 | 0.400526 | 912.349ms | 4604 | 160 | 181082 | 8399.36 | 0.240288 | 4.72046 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1584.25 | 0.0561434 | 305.683ms | 4918 | 80 | 221.013 | 2960.5 | 0.103129 | 1.54826 | 1(Win) | true |
| simdjson (reflection) | 1456.86 | 0.027123 | 330.626ms | 4918 | 80 | 60.9968 | 3219.38 | 0.0240672 | 1.68518 | 2(Loss) | true |
| Glaze | 1015.92 | 0.181714 | 438.838ms | 4604 | 2560 | 157894 | 4321.9 | 0.665583 | 2.42166 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1640.74 | 0.0963627 | 302.127ms | 4918 | 30 | 227.633 | 2858.57 | 0.0548361 | 1.49401 | 1(Win) | true |
| simdjson (reflection) | 1477.2 | 0.0210758 | 355.427ms | 4918 | 160 | 71.6453 | 3175.05 | 0.759529 | 1.66142 | 2(Loss) | true |
| Glaze | 1093.07 | 0.0964474 | 419.536ms | 4604 | 40 | 600.369 | 4016.88 | 0.0802219 | 2.24902 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2671.42 | 0.20285 | 654.929ms | 18245 | 2560 | 446882 | 6513.3 | 0.0629924 | 0.922822 | 1(Win) | true |
| Jsonifier | 2615.18 | 0.413579 | 698.146ms | 18245 | 640 | 484598 | 6653.39 | 0.424105 | 0.94285 | 2(Loss) | true |
| simdjson (reflection) | 2311.76 | 0.155662 | 736.349ms | 18245 | 40 | 5490.75 | 7526.65 | 0.15057 | 1.06728 | 3(Loss) | true |
| simdjson (ondemand) | 1793.62 | 0.11721 | 949.124ms | 18245 | 40 | 5171.51 | 9700.92 | 0.560024 | 1.37631 | 4(Loss) | true |
| Glaze | 1755.65 | 0.0607649 | 998.43ms | 18245 | 40 | 1450.71 | 9910.75 | 0.0455526 | 1.40627 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3166.45 | 0.0762732 | 638.389ms | 18245 | 40 | 702.664 | 5495.05 | 0.324389 | 0.777895 | 1(Win) | true |
| Jsonifier | 2807.55 | 0.220767 | 684.897ms | 18245 | 2560 | 479227 | 6197.49 | 0.117833 | 0.877774 | 2(Loss) | true |
| simdjson (reflection) | 2502.27 | 0.12077 | 758.568ms | 18245 | 80 | 5641.96 | 6953.61 | 0.396867 | 0.985503 | 3(Loss) | true |
| Glaze | 1898.17 | 0.0868069 | 995.484ms | 18245 | 4890 | 309623 | 9166.59 | 0.139169 | 1.30043 | 4(Loss) | true |
| simdjson (ondemand) | 1807.08 | 0.741081 | 1008.99ms | 18245 | 80 | 407339 | 9628.69 | 0.15746 | 1.3661 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7389.75 | 0.057431 | 320.357ms | 24893 | 30 | 102.12 | 3212.53 | 0.351545 | 0.332103 | 1(Win) | true |
| Glaze | 3644.36 | 0.109069 | 657.461ms | 24579 | 80 | 3937.15 | 6431.96 | 0.00408101 | 0.676466 | 2(Loss) | true |
| simdjson (reflection) | 555.005 | 0.0627164 | 4247.25ms | 24893 | 2560 | 1.84231e+06 | 42774 | 0.220962 | 4.45794 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7815.96 | 0.101857 | 300.466ms | 24893 | 80 | 765.699 | 3037.35 | 0.0675386 | 0.314016 | 1(Win) | true |
| Glaze | 4037.97 | 0.197926 | 592.672ms | 24579 | 1280 | 168974 | 5804.99 | 0.67964 | 0.610342 | 2(Loss) | true |
| simdjson (reflection) | 572.931 | 0.31458 | 4340.77ms | 24893 | 80 | 1.35926e+06 | 41435.7 | 0.150489 | 4.31862 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1962.04 | 0.0613857 | 257.053ms | 5094 | 80 | 184.81 | 2476 | 0.502311 | 1.24843 | 1(Win) | true |
| Jsonifier (two-stage) | 1603.01 | 0.0535192 | 306.223ms | 5094 | 160 | 420.903 | 3030.55 | 0.317823 | 1.53071 | 2(Loss) | true |
| simdjson (reflection) | 1354.94 | 0.110823 | 366.951ms | 5094 | 40 | 631.528 | 3585.4 | 0.11886 | 1.81345 | 3(Loss) | true |
| simdjson (ondemand) | 1265.17 | 0.161149 | 390.866ms | 5094 | 40 | 1531.55 | 3839.8 | 0.234703 | 1.94361 | 4(Loss) | true |
| Glaze | 1107.06 | 0.429455 | 443.567ms | 5094 | 640 | 227296 | 4388.22 | 0.255004 | 2.22249 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2304.67 | 0.12403 | 253.948ms | 5094 | 30 | 205.059 | 2107.9 | 0.0126492 | 1.06144 | 1(Win) | true |
| Jsonifier (two-stage) | 1793.91 | 0.0978261 | 306.706ms | 5094 | 30 | 210.547 | 2708.07 | 0.370636 | 1.36668 | 2(Loss) | true |
| simdjson (ondemand) | 1551.14 | 0.47021 | 358.58ms | 5094 | 1280 | 277595 | 3131.91 | 0.00895441 | 1.58289 | 3(Loss) | true |
| simdjson (reflection) | 1486.39 | 0.0834169 | 373.78ms | 5094 | 30 | 222.989 | 3268.33 | 0.142581 | 1.65333 | 4(Loss) | true |
| Glaze | 1337.47 | 0.0466314 | 403.303ms | 5094 | 160 | 459.016 | 3632.24 | 0.469771 | 1.83756 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14775 | 0.142024 | 35.4701ms | 5094 | 160 | 34.8906 | 328.8 | 0.148047 | 0.154683 | 1(Win) | true |
| simdjson (reflection) | 10918.3 | 0.101293 | 46.7914ms | 5094 | 640 | 130.001 | 444.942 | 0.301154 | 0.213191 | 2(Loss) | true |
| Glaze | 3728.89 | 0.243222 | 132.274ms | 5094 | 160 | 1606.52 | 1302.81 | 0.139798 | 0.651251 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16461.2 | 0.0683028 | 31.9993ms | 5094 | 640 | 26.0047 | 295.119 | 0.0466131 | 0.136993 | 1(Win) | true |
| simdjson (reflection) | 12764.5 | 0.107576 | 40.5427ms | 5094 | 80 | 13.41 | 380.587 | 0.134842 | 0.180585 | 2(Loss) | true |
| Glaze | 4167.2 | 0.0686436 | 120.763ms | 5094 | 40 | 25.6147 | 1165.78 | 0.0579349 | 0.580438 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2505.76 | 0.12478 | 306.568ms | 8051 | 40 | 584.746 | 3064.15 | 0.123319 | 0.979552 | 1(Win) | true |
| Jsonifier (two-stage) | 2330.44 | 0.112238 | 332.546ms | 8051 | 30 | 410.23 | 3294.67 | 0.284091 | 1.05364 | 2(Loss) | true |
| simdjson (reflection) | 1940.45 | 0.0887085 | 404.742ms | 8051 | 40 | 492.815 | 3956.82 | 0.129776 | 1.26745 | 3(Loss) | true |
| simdjson (ondemand) | 1912.78 | 0.181679 | 400.356ms | 8051 | 30 | 1595.51 | 4014.07 | 0.222883 | 1.28573 | 4(Loss) | true |
| Glaze | 1529.28 | 0.472264 | 493.384ms | 8051 | 320 | 179906 | 5020.68 | 0.0430534 | 1.61018 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3002.63 | 0.0895186 | 303.829ms | 8051 | 30 | 157.197 | 2557.1 | 0.0599278 | 0.816586 | 1(Win) | true |
| Jsonifier (two-stage) | 2605.9 | 0.0785009 | 331.236ms | 8051 | 40 | 213.99 | 2946.4 | 0.0656599 | 0.941442 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2242.19 | 0.52285 | 393.256ms | 8051 | 640 | 205159 | 3424.35 | 0.752379 | 1.09575 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2224.57 | 0.146454 | 386.754ms | 8051 | 30 | 766.533 | 3451.47 | 0.103445 | 1.10413 | 3(Tie) | true |
| Glaze | 1852.92 | 0.10818 | 461.691ms | 8051 | 40 | 803.782 | 4143.75 | 0.139373 | 1.32759 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22958.1 | 0.239136 | 40.6875ms | 9255 | 80 | 67.6177 | 384.45 | 0.0325034 | 0.100108 | 1(Win) | true |
| Glaze | 4312.14 | 0.0661496 | 216.406ms | 9255 | 160 | 293.319 | 2046.84 | 0.0721144 | 0.566783 | 2(Loss) | true |
| simdjson (reflection) | 586.751 | 0.422092 | 1552.53ms | 9255 | 80 | 322514 | 15042.6 | 0.347053 | 4.21209 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26266.7 | 0.138069 | 35.8603ms | 9255 | 160 | 34.4396 | 336.025 | 0.0371858 | 0.0869152 | 1(Win) | true |
| Glaze | 4873.79 | 0.199039 | 187.733ms | 9255 | 80 | 1039.4 | 1810.96 | 0.0696657 | 0.500978 | 2(Loss) | true |
| simdjson (reflection) | 557.075 | 0.130503 | 1597.17ms | 9255 | 1280 | 547240 | 15843.9 | 0.205657 | 4.43551 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7086.44 | 0.115659 | 41.865ms | 2889 | 160 | 32.3534 | 388.794 | 0.15295 | 0.326125 | 1(Win) | true |
| Jsonifier | 6798.31 | 0.0943444 | 43.1266ms | 2889 | 320 | 46.7817 | 405.272 | 0.0362542 | 0.340532 | 2(Loss) | true |
| Jsonifier (two-stage) | 6729.02 | 0.0566185 | 43.3702ms | 2889 | 640 | 34.3945 | 409.445 | 0.0270872 | 0.343964 | 3(Loss) | true |
| simdjson (reflection) | 6357.97 | 0.0693451 | 45.5432ms | 2889 | 320 | 28.8962 | 433.341 | 0.0699997 | 0.364574 | 4(Loss) | true |
| Glaze | 2936.96 | 0.171835 | 98.7756ms | 2889 | 30 | 77.9552 | 938.1 | 0 | 0.818345 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7295.19 | 0.0901192 | 40.8967ms | 2889 | 320 | 37.0686 | 377.669 | 0.0264852 | 0.316258 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 7145.14 | 0.230241 | 41.5535ms | 2889 | 40 | 31.5282 | 385.6 | 0.00864528 | 0.323269 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 7125.73 | 0.128688 | 41.6404ms | 2889 | 160 | 39.6126 | 386.65 | 0.0161619 | 0.322659 | 2(Tie) | true |
| simdjson (reflection) | 6732.18 | 0.0747083 | 44.3812ms | 2889 | 320 | 29.9138 | 409.253 | 0.290239 | 0.343393 | 4(Loss) | true |
| Glaze | 3021.35 | 0.130924 | 95.2396ms | 2889 | 40 | 57.0154 | 911.9 | 0.021937 | 0.794843 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 8086.04 | 0.101483 | 47.7828ms | 3808 | 160 | 33.2374 | 449.119 | 0.0570236 | 0.289571 | 1(Win) | true |
| simdjson (reflection) | 7960.63 | 0.0996083 | 48.6406ms | 3808 | 160 | 33.0377 | 456.194 | 0.223815 | 0.293504 | 2(Loss) | true |
| Jsonifier | 7544.6 | 0.106862 | 51.753ms | 3808 | 80 | 21.1671 | 481.35 | 0.0207792 | 0.310051 | 3(Loss) | true |
| Jsonifier (two-stage) | 6959.95 | 0.0657431 | 54.9645ms | 3808 | 640 | 75.3118 | 521.784 | 0.144128 | 0.336768 | 4(Loss) | true |
| Glaze | 3883.43 | 0.0270991 | 97.3947ms | 3808 | 640 | 41.1011 | 935.15 | 0.0789266 | 0.620141 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 8145.95 | 0.0487111 | 47.7383ms | 3808 | 640 | 30.1819 | 445.816 | 0.014718 | 0.286088 | 1(Win) | true |
| simdjson (ondemand) | 7783.25 | 0.0686363 | 49.4478ms | 3808 | 320 | 32.8193 | 466.591 | 0.0662615 | 0.299266 | 2(Loss) | true |
| Jsonifier (two-stage) | 7610.01 | 0.11892 | 50.4929ms | 3808 | 80 | 25.7644 | 477.212 | 0.159527 | 0.307386 | 3(Loss) | true |
| Jsonifier | 7509.01 | 0.0833235 | 51.7368ms | 3808 | 160 | 25.9827 | 483.631 | 0.00646195 | 0.311487 | 4(Loss) | true |
| Glaze | 3861.89 | 0.138651 | 101.751ms | 3808 | 30 | 50.9989 | 940.367 | 0.067395 | 0.624256 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2747.68 | 0.204194 | 105.565ms | 2889 | 40 | 167.692 | 1002.73 | 0.146883 | 0.878133 | 1(Win) | true |
| Glaze | 2039.65 | 0.140317 | 141.732ms | 2889 | 40 | 143.703 | 1350.8 | 0.10375 | 1.19149 | 2(Loss) | true |
| Jsonifier (two-stage) | 1955.73 | 0.105621 | 145.642ms | 2889 | 80 | 177.12 | 1408.76 | 0.0115336 | 1.24059 | 3(Loss) | true |
| simdjson (reflection) | 1852.96 | 0.262429 | 149.602ms | 2889 | 30 | 456.783 | 1486.9 | 0.221447 | 1.31209 | 4(Loss) | true |
| simdjson (ondemand) | 1135.06 | 0.0709198 | 247.069ms | 2889 | 160 | 474.145 | 2427.32 | 0.0920948 | 2.15769 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2941.51 | 0.120853 | 102.309ms | 2889 | 80 | 102.509 | 936.65 | 0.130957 | 0.816455 | 1(Win) | true |
| Glaze | 2188.38 | 0.121328 | 132.783ms | 2889 | 30 | 70 | 1259 | 0.159109 | 1.10603 | 2(Loss) | true |
| Jsonifier (two-stage) | 2133.4 | 0.0840298 | 147.616ms | 2889 | 160 | 188.424 | 1291.44 | 0.0295125 | 1.13563 | 3(Loss) | true |
| simdjson (reflection) | 2115.03 | 0.0853855 | 141.595ms | 2889 | 160 | 197.948 | 1302.66 | 0.156166 | 1.14606 | 4(Loss) | true |
| simdjson (ondemand) | 1139.42 | 0.0703789 | 241.26ms | 2889 | 160 | 463.375 | 2418.04 | 0.490652 | 2.14813 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10910.1 | 0.0713488 | 28.5955ms | 2963 | 1280 | 43.7107 | 259.002 | 0.0633844 | 0.204166 | 1(Win) | true |
| simdjson (reflection) | 9964.36 | 0.122533 | 31.9933ms | 2963 | 320 | 38.6386 | 283.584 | 0.477068 | 0.225804 | 2(Loss) | true |
| Glaze | 5166.53 | 0.138142 | 57.572ms | 2963 | 160 | 91.3349 | 546.931 | 0.00571402 | 0.456946 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12471.5 | 0.377917 | 25.2563ms | 2963 | 40 | 29.3276 | 226.575 | 0.387683 | 0.176738 | 1(Win) | true |
| simdjson (reflection) | 11069.4 | 0.105456 | 28.1514ms | 2963 | 640 | 46.3812 | 255.275 | 0.00856846 | 0.200329 | 2(Loss) | true |
| Glaze | 5645.83 | 0.0669916 | 53.3335ms | 2963 | 160 | 17.9874 | 500.5 | 0.0524201 | 0.415824 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2733.98 | 0.0778333 | 142.508ms | 3808 | 160 | 171.024 | 1328.32 | 0.108572 | 0.887392 | 1(Win) | true |
| Jsonifier (two-stage) | 2493.88 | 0.142701 | 151.017ms | 3808 | 30 | 129.545 | 1456.2 | 0.0458022 | 0.975639 | 2(Loss) | true |
| simdjson (reflection) | 2464.6 | 0.151947 | 146.949ms | 3808 | 40 | 200.513 | 1473.5 | 0.32245 | 0.987743 | 3(Loss) | true |
| Glaze | 2054.92 | 0.0917199 | 181.999ms | 3808 | 30 | 78.823 | 1767.27 | 0.173225 | 1.18662 | 4(Loss) | true |
| simdjson (ondemand) | 1470.41 | 0.0754378 | 297.059ms | 3808 | 160 | 555.408 | 2469.78 | 0.222173 | 1.66593 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3107.11 | 0.144418 | 124.72ms | 3808 | 30 | 85.4759 | 1168.8 | 0.263068 | 0.779473 | 1(Win) | true |
| Jsonifier (two-stage) | 2720.79 | 0.0615773 | 141.937ms | 3808 | 160 | 108.085 | 1334.76 | 0.121424 | 0.892224 | 2(Loss) | true |
| simdjson (reflection) | 2699.27 | 0.197702 | 142.106ms | 3808 | 30 | 212.248 | 1345.4 | 0.217553 | 0.898748 | 3(Loss) | true |
| Glaze | 2304.66 | 0.0587611 | 168.736ms | 3808 | 80 | 68.5884 | 1575.76 | 0.194729 | 1.05655 | 4(Loss) | true |
| simdjson (ondemand) | 1496.41 | 0.299452 | 249.74ms | 3808 | 2560 | 135204 | 2426.87 | 0.429165 | 1.63626 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14365.6 | 0.142451 | 31.0922ms | 4300 | 320 | 52.9137 | 285.459 | 0.036139 | 0.156233 | 1(Win) | true |
| Glaze | 4076.86 | 0.0619469 | 107.804ms | 4300 | 320 | 124.244 | 1005.87 | 0.0952866 | 0.591932 | 2(Loss) | true |
| simdjson (reflection) | 580.859 | 0.347954 | 705.652ms | 4300 | 320 | 193103 | 7059.89 | 0.0719217 | 4.24533 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17277.1 | 0.102836 | 26.6421ms | 4300 | 1280 | 76.2603 | 237.355 | 0.065214 | 0.127474 | 1(Win) | true |
| Glaze | 4542.97 | 0.0412083 | 93.5416ms | 4300 | 640 | 88.5536 | 902.669 | 0.0623541 | 0.528755 | 2(Loss) | true |
| simdjson (reflection) | 596.763 | 0.057625 | 710.193ms | 4300 | 30 | 470.409 | 6871.73 | 0.183991 | 4.13236 | 3(Loss) | true |

----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21412.2 | 0.0579887 | 2100.04ms | 466906 | 30 | 4362.6 | 20795.5 | 0.132255 | 0.11547 | 1(Win) | true |
| simdjson (ondemand) | 17682 | 0.430865 | 2575.91ms | 466906 | 160 | 1.88366e+06 | 25182.5 | 0.11676 | 0.139852 | 2(Loss) | true |
| Glaze | 2561.87 | 0.144864 | 8851.99ms | 466906 | 320 | 2.02868e+07 | 173809 | 0.646516 | 0.96624 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21674.5 | 0.0651248 | 2084.11ms | 466906 | 40 | 7159.99 | 20543.8 | 0.395269 | 0.114069 | 1(Win) | true |
| simdjson (ondemand) | 17839.9 | 0.790358 | 2501.03ms | 466906 | 30 | 1.16747e+06 | 24959.6 | 0.322943 | 0.138624 | 2(Loss) | true |
| Glaze | 2603.93 | 0.425473 | 8858.81ms | 466906 | 30 | 1.58805e+07 | 171002 | 0.205384 | 0.950631 | 3(Loss) | true |

----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5365.99 | 0.46576 | 6382.84ms | 699405 | 30 | 1.00555e+07 | 124302 | 0.453257 | 0.461282 | 1(Win) | true |
| Glaze | 3287.14 | 0.228626 | 5394.27ms | 699405 | 40 | 8.60856e+06 | 202913 | 0.0738216 | 0.753062 | 2(Loss) | true |
| simdjson (ondemand) | 2700.06 | 0.0452383 | 7083.84ms | 767297 | 1280 | 1.92398e+07 | 271013 | 0.186344 | 0.916814 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5502.78 | 0.519402 | 6560.47ms | 699405 | 30 | 1.18911e+07 | 121212 | 0.671871 | 0.449801 | 1(Win) | true |
| Glaze | 3409.09 | 0.117319 | 5178.84ms | 699405 | 160 | 8.43015e+06 | 195655 | 0.077102 | 0.726133 | 2(Loss) | true |
| simdjson (ondemand) | 2703 | 0.173011 | 7028.16ms | 767297 | 80 | 1.75498e+07 | 270719 | 0.0634297 | 0.915841 | 3(Loss) | true |

----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3035.77 | 0.173131 | 5131.23ms | 631514 | 80 | 9.43771e+06 | 198387 | 0.0429206 | 0.815405 | 1(Win) | true |
| Glaze | 2450.79 | 0.096634 | 6424.97ms | 631514 | 320 | 1.80453e+07 | 245741 | 0.104565 | 1.0101 | 2(Loss) | true |
