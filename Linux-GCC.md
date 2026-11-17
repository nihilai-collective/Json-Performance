# Json-Performance: Jsonifier (Fused vs Two-Stage) vs Glaze vs simdjson (AVX512)
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1019-azure using the GCC 16.2.0 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier: [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| Glaze: [a53ddd59](https://github.com/stephenberry/glaze/commit/a53ddd59)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX512` |
| **simdjson (ondemand)** | `icelake` |
| **simdjson (reflection)** | `icelake` |
| **Glaze** | utf8: `AVX512BW`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX512BW` |

> **Adaptive Sampling & Convergence (AMD EPYC 9V45 96-Core Processor-AVX512):**  
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
* **simdjson (reflection):** C++26 static reflection API (P2996). Minified serialization only.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2415.65 | 0.09159 | 38.5331ms | 905 | 320 | 34.2668 | 357.284 | 0.243434 | 0.949624 | 1(Win) | true |
| Glaze | 610.713 | 0.024985 | 147.07ms | 905 | 80 | 9.97405 | 1413.22 | 0.0424741 | 3.90848 | 2(Loss) | true |
| Jsonifier (two-stage) | 452.082 | 0.0377466 | 195.429ms | 905 | 80 | 41.5441 | 1909.11 | 0.089621 | 5.40135 | 3(Loss) | true |
| simdjson (ondemand) | 210.78 | 0.0567945 | 416.134ms | 905 | 40 | 216.328 | 4094.68 | 0.168183 | 11.6683 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2430.19 | 0.0787767 | 38.7343ms | 905 | 320 | 25.0473 | 355.147 | 0.108113 | 0.945566 | 1(Win) | true |
| Jsonifier | 2361.19 | 0.21461 | 40.2017ms | 905 | 40 | 24.6147 | 365.525 | 0.2751 | 0.973204 | 2(Loss) | true |
| Jsonifier (two-stage) | 455.641 | 0.0487153 | 195.225ms | 905 | 30 | 25.5448 | 1894.2 | 0.0175945 | 5.35974 | 3(Loss) | true |
| simdjson (ondemand) | 210.775 | 0.0522167 | 410.793ms | 905 | 30 | 137.151 | 4094.77 | 0.0975903 | 11.6726 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2014.63 | 0.114918 | 46.3117ms | 905 | 640 | 155.118 | 428.405 | 0.0200559 | 1.15314 | 1(Win) | true |
| simdjson (reflection) | 258.575 | 0.13569 | 335.349ms | 905 | 4890 | 100306 | 3337.81 | 0.0730154 | 9.49848 | 2(Loss) | true |
| Glaze | 199.799 | 0.0507724 | 435.038ms | 905 | 40 | 192.41 | 4319.73 | 0.770406 | 12.3119 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3172.92 | 0.164603 | 35.4487ms | 905 | 80 | 16.0378 | 272.012 | 0.032178 | 0.702983 | 1(Win) | true |
| simdjson (reflection) | 2206.79 | 0.131974 | 42.1105ms | 905 | 40 | 10.6564 | 391.1 | 0.127681 | 1.04494 | 2(Loss) | true |
| Glaze | 479.833 | 0.0438936 | 187.52ms | 905 | 40 | 24.9333 | 1798.7 | 0.0555648 | 5.0218 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1414.04 | 0.108119 | 125.105ms | 1811 | 30 | 52.3172 | 1221.4 | 0.253165 | 1.71176 | 1(Win) | true |
| Glaze | 623.562 | 0.0248563 | 278.441ms | 1811 | 80 | 37.9176 | 2769.74 | 0.0573488 | 3.93366 | 2(Loss) | true |
| Jsonifier (two-stage) | 457.434 | 0.0718748 | 384.304ms | 1811 | 30 | 220.93 | 3775.63 | 0.15074 | 5.37322 | 3(Loss) | true |
| simdjson (ondemand) | 209.566 | 0.163889 | 830.248ms | 1811 | 1280 | 233509 | 8241.33 | 0.197452 | 11.7758 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1527.46 | 0.116835 | 115.86ms | 1811 | 30 | 52.3552 | 1130.7 | 0.293936 | 1.58531 | 1(Win) | true |
| Glaze | 696.56 | 0.0378226 | 268.576ms | 1811 | 40 | 35.1788 | 2479.47 | 0.138999 | 3.52013 | 2(Loss) | true |
| Jsonifier (two-stage) | 451.798 | 0.0788671 | 388.642ms | 1811 | 30 | 272.685 | 3822.73 | 0.235989 | 5.44116 | 3(Loss) | true |
| simdjson (ondemand) | 218.953 | 0.0589028 | 800.318ms | 1811 | 40 | 863.512 | 7888.02 | 0.0136264 | 11.2664 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 344.959 | 0.0233628 | 503.07ms | 1811 | 40 | 54.7282 | 5006.7 | 0.0253058 | 7.13704 | 1(Win) | true |
| simdjson (reflection) | 314.92 | 0.0372441 | 611.819ms | 1997 | 40 | 202.922 | 6047.52 | 0.332498 | 7.82695 | 2(Loss) | true |
| Glaze | 266.11 | 0.0306941 | 656.054ms | 1798 | 30 | 117.352 | 6443.6 | 0.016034 | 9.2672 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 813.645 | 0.0509238 | 222.318ms | 1811 | 40 | 46.7378 | 2122.68 | 0.0231572 | 3.0069 | 1(Win) | true |
| simdjson (reflection) | 568.165 | 0.0291391 | 345.773ms | 1997 | 30 | 28.6207 | 3352 | 0.109507 | 4.3198 | 2(Loss) | true |
| Glaze | 522.663 | 0.17075 | 337.45ms | 1798 | 4890 | 153450 | 3280.71 | 0.28568 | 4.69741 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3031.16 | 0.084094 | 125.821ms | 3862 | 40 | 41.7635 | 1215.08 | 0.308355 | 0.799236 | 1(Win) | true |
| Glaze | 1452.42 | 0.0663674 | 271.323ms | 3862 | 30 | 84.9713 | 2535.83 | 0.116853 | 1.6873 | 2(Loss) | true |
| Jsonifier (two-stage) | 821.307 | 0.115799 | 460.822ms | 3862 | 40 | 1078.66 | 4484.43 | 0.176041 | 2.9965 | 3(Loss) | true |
| simdjson (ondemand) | 421.294 | 0.0225683 | 898.614ms | 3862 | 30 | 116.782 | 8742.33 | 0.202814 | 5.85882 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3186.89 | 0.0511534 | 118.889ms | 3862 | 80 | 27.9595 | 1155.7 | 0.108277 | 0.75837 | 1(Win) | true |
| Glaze | 1598.17 | 0.0419955 | 239.445ms | 3862 | 80 | 74.9328 | 2304.56 | 0.244026 | 1.53339 | 2(Loss) | true |
| Jsonifier (two-stage) | 809.197 | 0.0382243 | 460.164ms | 3862 | 80 | 242.15 | 4551.54 | 0.060657 | 3.04137 | 3(Loss) | true |
| simdjson (ondemand) | 578.117 | 0.123083 | 641.835ms | 3862 | 4890 | 300678 | 6370.84 | 0.0482283 | 4.26477 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 952.655 | 0.051474 | 389.949ms | 3862 | 30 | 118.809 | 3866.13 | 0.103356 | 2.58091 | 1(Win) | true |
| simdjson (reflection) | 891.144 | 0.148433 | 416.883ms | 3862 | 4890 | 184034 | 4132.99 | 0.626712 | 2.76073 | 2(Loss) | true |
| Glaze | 775.906 | 0.140368 | 493.125ms | 3862 | 4890 | 217098 | 4746.83 | 0.153386 | 3.17316 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4712.68 | 0.0432444 | 87.6265ms | 3862 | 320 | 36.5509 | 781.528 | 0.311658 | 0.50771 | 1(Win) | true |
| simdjson (reflection) | 3172.16 | 0.0739785 | 126.431ms | 3862 | 30 | 22.1333 | 1161.07 | 0.0574515 | 0.762515 | 2(Loss) | true |
| Glaze | 1700.78 | 0.0473175 | 222.463ms | 3862 | 30 | 31.4989 | 2165.53 | 0.0277145 | 1.43351 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1606.95 | 0.284622 | 571.029ms | 9578 | 1280 | 335037 | 5684.25 | 0.0731172 | 1.53343 | 1(Win) | true |
| Glaze | 1437.23 | 0.240328 | 639.701ms | 9578 | 1280 | 298616 | 6355.48 | 0.207621 | 1.71546 | 2(Loss) | true |
| simdjson (ondemand) | 1130.67 | 0.154173 | 821.448ms | 9578 | 2560 | 397131 | 8078.65 | 0.43796 | 2.18263 | 3(Loss) | true |
| Jsonifier (two-stage) | 904.886 | 0.184458 | 1021.01ms | 9578 | 1280 | 443782 | 10094.4 | 0.0295249 | 2.7289 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2170.77 | 0.0649657 | 551.54ms | 9578 | 30 | 224.189 | 4207.87 | 0.333968 | 1.13385 | 1(Win) | true |
| Glaze | 1933.29 | 0.148326 | 614.029ms | 9578 | 30 | 1473.37 | 4724.73 | 0.331894 | 1.27285 | 2(Loss) | true |
| simdjson (ondemand) | 1366.39 | 0.0675675 | 795.829ms | 9578 | 30 | 612.069 | 6685 | 0.0299267 | 1.80472 | 3(Loss) | true |
| Jsonifier (two-stage) | 1086.64 | 0.0452524 | 1065.79ms | 9578 | 40 | 578.794 | 8406.02 | 0.152802 | 2.27179 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3930.44 | 0.0518624 | 235.857ms | 9578 | 80 | 116.215 | 2323.99 | 0.0209813 | 0.622437 | 1(Win) | true |
| simdjson (reflection) | 3808.26 | 0.11844 | 244.481ms | 9578 | 40 | 322.818 | 2398.55 | 0.0827573 | 0.643065 | 2(Loss) | true |
| Glaze | 1931.83 | 0.0409007 | 480.209ms | 9578 | 40 | 149.6 | 4728.3 | 0.185768 | 1.27434 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 8925.44 | 0.0804227 | 111.197ms | 9578 | 80 | 54.1924 | 1023.4 | 0.0415455 | 0.270156 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 8921.3 | 0.0878975 | 111.17ms | 9578 | 80 | 64.7943 | 1023.88 | 0.28001 | 0.270287 | 1(Tie) | true |
| Glaze | 3872.06 | 0.0363798 | 248.498ms | 9578 | 40 | 29.4609 | 2359.03 | 0.00883055 | 0.631601 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2804.27 | 0.0505239 | 135.047ms | 3873 | 80 | 35.4272 | 1317.12 | 0.0664767 | 0.864633 | 1(Win) | true |
| Glaze | 1837.87 | 0.0272131 | 207.869ms | 3873 | 160 | 47.8566 | 2009.71 | 0.294262 | 1.32972 | 2(Loss) | true |
| Jsonifier (two-stage) | 794.945 | 0.0431364 | 468.726ms | 3873 | 80 | 321.366 | 4646.34 | 0.00349726 | 3.09634 | 3(Loss) | true |
| simdjson (ondemand) | 415.057 | 0.0279467 | 918.421ms | 3873 | 30 | 185.551 | 8898.97 | 0.0561547 | 5.94758 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3001.29 | 0.0399124 | 127.244ms | 3873 | 160 | 38.6024 | 1230.66 | 0.0497947 | 0.807475 | 1(Win) | true |
| Glaze | 1985.15 | 0.0263528 | 189.84ms | 3873 | 160 | 38.4666 | 1860.61 | 0.0097405 | 1.2296 | 2(Loss) | true |
| Jsonifier (two-stage) | 823.657 | 0.0784997 | 459.558ms | 3873 | 30 | 371.757 | 4484.37 | 0.155855 | 2.98845 | 3(Loss) | true |
| simdjson (ondemand) | 554.508 | 0.0612259 | 703.782ms | 3873 | 30 | 498.966 | 6661 | 0.12495 | 4.44853 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 923.366 | 0.04926 | 397.325ms | 3873 | 80 | 310.617 | 4000.12 | 0.197257 | 2.66333 | 1(Win) | true |
| simdjson (reflection) | 882.443 | 0.0253579 | 425.428ms | 3873 | 160 | 180.247 | 4185.63 | 0.452327 | 2.78802 | 2(Loss) | true |
| Glaze | 785.576 | 0.0395617 | 485.332ms | 3873 | 40 | 138.397 | 4701.75 | 0.0869226 | 3.13349 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4732.78 | 0.117589 | 87.5ms | 3873 | 40 | 33.6865 | 780.425 | 0.00106778 | 0.505945 | 1(Win) | true |
| simdjson (reflection) | 3188.66 | 0.0531573 | 122.253ms | 3873 | 80 | 30.3316 | 1158.35 | 0.00863371 | 0.758737 | 2(Loss) | true |
| Glaze | 1846.79 | 0.0425481 | 212.28ms | 3873 | 30 | 21.7241 | 2000 | 0.0667111 | 1.32313 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1534.97 | 0.0514758 | 5916ms | 94653 | 4890 | 4.48112e+06 | 58807.9 | 0.0872752 | 1.61221 | 1(Win) | true |
| simdjson (reflection) | 1430.82 | 0.0561343 | 6396.04ms | 94653 | 4890 | 6.13288e+06 | 63088.4 | 0.229206 | 1.72961 | 2(Loss) | true |
| Jsonifier (two-stage) | 1335.6 | 0.0561748 | 6837.07ms | 94653 | 4890 | 7.04869e+06 | 67586.2 | 0.099719 | 1.853 | 3(Loss) | true |
| simdjson (ondemand) | 1317.45 | 0.178209 | 6854.19ms | 94653 | 320 | 4.77099e+06 | 68517.3 | 0.234108 | 1.87855 | 4(Loss) | true |
| Glaze | 1254.49 | 0.0673391 | 7252.11ms | 94653 | 4890 | 1.1481e+07 | 71956.1 | 0.0504298 | 1.97285 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2069.86 | 0.0684734 | 5565.93ms | 94653 | 2560 | 2.28281e+06 | 43610.6 | 0.103569 | 1.19541 | 1(Win) | true |
| simdjson (reflection) | 1805.75 | 0.0946286 | 6321.3ms | 94653 | 640 | 1.43212e+06 | 49989.3 | 0.100804 | 1.37036 | 2(Loss) | true |
| Jsonifier (two-stage) | 1735.39 | 0.127143 | 6310.36ms | 94653 | 2560 | 1.1197e+07 | 52016.2 | 0.0030203 | 1.42585 | 3(Loss) | true |
| simdjson (ondemand) | 1724.52 | 0.0599049 | 6390.52ms | 94653 | 4890 | 4.80805e+06 | 52344 | 0.0804931 | 1.43494 | 4(Loss) | true |
| Glaze | 1598.16 | 0.242075 | 6906.53ms | 94653 | 80 | 1.49561e+06 | 56482.5 | 0.00821118 | 1.54846 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26345.3 | 0.0469157 | 350.637ms | 94653 | 40 | 103.362 | 3426.35 | 0.171028 | 0.0932282 | 1(Win) | true |
| simdjson (reflection) | 14755.1 | 0.225541 | 614.268ms | 94653 | 2560 | 487387 | 6117.75 | 0.356187 | 0.167066 | 2(Loss) | true |
| Glaze | 6280.48 | 0.0324774 | 1486.42ms | 94653 | 30 | 653.683 | 14372.8 | 0.116057 | 0.39347 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26471.3 | 0.0522411 | 346.912ms | 94653 | 30 | 95.2057 | 3410.03 | 0.0293166 | 0.0928071 | 1(Win) | true |
| simdjson (reflection) | 15311.5 | 0.0265119 | 611.373ms | 94653 | 30 | 73.2885 | 5895.43 | 0.0163996 | 0.160966 | 2(Loss) | true |
| Glaze | 6775.67 | 0.177697 | 1349.23ms | 94653 | 640 | 358677 | 13322.4 | 0.126992 | 0.364642 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1821.83 | 0.0880742 | 6688.56ms | 124597 | 1280 | 4.22382e+06 | 65222.7 | 0.28194 | 1.35843 | 1(Win) | true |
| Jsonifier (two-stage) | 1708 | 0.0759789 | 7038.31ms | 124597 | 2560 | 7.15261e+06 | 69569.6 | 0.0972937 | 1.449 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1690.13 | 0.482485 | 7088.79ms | 124597 | 40 | 4.60259e+06 | 70305.1 | 0.083658 | 1.46433 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1677.77 | 0.10043 | 7167.56ms | 124597 | 1280 | 6.47577e+06 | 70823.1 | 0.404317 | 1.47512 | 3(Tie) | true |
| Glaze | 1655.89 | 0.17693 | 7289.01ms | 124597 | 160 | 2.57916e+06 | 71759.2 | 0.00249103 | 1.49462 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2312.26 | 0.147323 | 6329.78ms | 124597 | 640 | 3.6683e+06 | 51389.2 | 0.176058 | 1.07018 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2209.57 | 0.0578477 | 6706.33ms | 124597 | 2560 | 2.4775e+06 | 53777.5 | 0.161006 | 1.11995 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2209.44 | 0.164778 | 6618.52ms | 124597 | 320 | 2.51305e+06 | 53780.6 | 0.128216 | 1.12002 | 2(Tie) | true |
| Jsonifier | 2173.96 | 0.232508 | 6674.83ms | 124597 | 160 | 2.58409e+06 | 54658.4 | 0.128497 | 1.13832 | 4(Loss) | true |
| Glaze | 2038.98 | 0.13328 | 6986.75ms | 124597 | 320 | 1.93049e+06 | 58276.6 | 0.0977655 | 1.21368 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 34480.7 | 0.21714 | 381.6ms | 136037 | 1280 | 85438 | 3762.54 | 0.165091 | 0.0712973 | 1(Win) | true |
| Glaze | 5917.75 | 0.0948555 | 2196.27ms | 136076 | 4890 | 2.11585e+06 | 21929.3 | 0.144694 | 0.417872 | 2(Loss) | true |
| simdjson (reflection) | 602.182 | 0.116089 | 5605.49ms | 136037 | 320 | 2.00165e+07 | 215441 | 0.0866668 | 4.1106 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 34667.5 | 0.0585295 | 379.687ms | 136037 | 30 | 143.926 | 3742.27 | 0.123658 | 0.0709001 | 1(Win) | true |
| Glaze | 6416.57 | 0.161191 | 2039.08ms | 136076 | 1280 | 1.36034e+06 | 20224.6 | 0.683405 | 0.385345 | 2(Loss) | true |
| simdjson (reflection) | 598.848 | 0.055714 | 5555.23ms | 136037 | 1280 | 1.86475e+07 | 216641 | 0.303613 | 4.13365 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 852.198 | 0.0403775 | 7944.36ms | 2251027 | 30 | 3.1037e+07 | 2.51907e+06 | 0.174759 | 2.90521 | 1(Win) | true |
| Jsonifier (two-stage) | 774.406 | 0.15391 | 8875.8ms | 2251027 | 30 | 5.46108e+08 | 2.77212e+06 | 1.08207 | 3.19704 | 2(Loss) | true |
| Glaze | 733.716 | 0.0595172 | 9079.65ms | 2251027 | 160 | 4.85189e+08 | 2.92586e+06 | 0.128767 | 3.37435 | 3(Loss) | true |
| simdjson (ondemand) | 697.715 | 0.138403 | 9512.89ms | 2251027 | 80 | 1.45073e+09 | 3.07682e+06 | 0.404893 | 3.54846 | 4(Loss) | true |
| simdjson (reflection) | 688.224 | 0.0977197 | 9748.74ms | 2251027 | 40 | 3.71643e+08 | 3.11926e+06 | 0.0371215 | 3.5974 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 994.909 | 0.194189 | 8010.5ms | 2251027 | 30 | 5.26705e+08 | 2.15773e+06 | 0.0794211 | 2.48847 | 1(Win) | true |
| Glaze | 915.244 | 0.154725 | 8587.88ms | 2251027 | 30 | 3.95122e+08 | 2.34555e+06 | 0.162601 | 2.70507 | 2(Loss) | true |
| Jsonifier (two-stage) | 878.61 | 0.152255 | 8755.03ms | 2251027 | 40 | 5.53569e+08 | 2.44334e+06 | 0.00248675 | 2.81786 | 3(Loss) | true |
| simdjson (ondemand) | 812.135 | 0.304592 | 9418.7ms | 2251027 | 160 | 1.0372e+10 | 2.64334e+06 | 0.232464 | 3.04852 | 4(Loss) | true |
| simdjson (reflection) | 782.443 | 0.122899 | 9698.48ms | 2251027 | 80 | 9.09579e+08 | 2.74365e+06 | 0.229927 | 3.1642 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1770.81 | 0.0757918 | 7085.9ms | 2090234 | 40 | 2.91171e+07 | 1.1257e+06 | 0.0269523 | 1.3981 | 1(Win) | true |
| Glaze | 1289.01 | 0.0365151 | 9738.07ms | 2090234 | 320 | 1.0204e+08 | 1.54646e+06 | 0.181881 | 1.92068 | 2(Loss) | true |
| simdjson (reflection) | 876.108 | 0.0638452 | 7115.91ms | 2090326 | 80 | 1.68834e+08 | 2.27539e+06 | 0.316387 | 2.82592 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1769.54 | 0.0673916 | 7044.52ms | 2090234 | 80 | 4.61074e+07 | 1.12651e+06 | 0.111925 | 1.39909 | 1(Win) | true |
| Glaze | 1330.64 | 0.0847016 | 9473.06ms | 2090234 | 160 | 2.57617e+08 | 1.49808e+06 | 0.00657217 | 1.86059 | 2(Loss) | true |
| simdjson (reflection) | 862.531 | 0.103653 | 7209.34ms | 2090326 | 40 | 2.29565e+08 | 2.31121e+06 | 0.0413966 | 2.87039 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1709.73 | 0.371397 | 9451ms | 5373214 | 160 | 1.98248e+10 | 2.99713e+06 | 0.781443 | 1.44806 | 1(Win) | true |
| Jsonifier | 1681.14 | 0.0598383 | 9543ms | 5373214 | 80 | 2.66139e+08 | 3.04811e+06 | 0.267596 | 1.47269 | 2(Loss) | true |
| simdjson (ondemand) | 1572.79 | 0.0827591 | 10150.4ms | 5373214 | 40 | 2.90817e+08 | 3.2581e+06 | 0.162119 | 1.57416 | 3(Loss) | true |
| simdjson (reflection) | 1568.23 | 0.0585709 | 10153.4ms | 5373214 | 80 | 2.93025e+08 | 3.26758e+06 | 0.321757 | 1.57874 | 4(Loss) | true |
| Glaze | 1521.25 | 0.0894016 | 5030.53ms | 5373214 | 40 | 3.62759e+08 | 3.36848e+06 | 0.739956 | 1.62749 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1960.48 | 0.110934 | 9355.7ms | 5373214 | 160 | 1.34522e+09 | 2.61379e+06 | 0.10431 | 1.26286 | 1(Win) | true |
| Jsonifier | 1910.56 | 0.33913 | 9707.88ms | 5373214 | 80 | 6.61868e+09 | 2.6821e+06 | 0.0281846 | 1.29586 | 2(Loss) | true |
| simdjson (ondemand) | 1851.41 | 0.0778692 | 9986.23ms | 5373214 | 40 | 1.85803e+08 | 2.76778e+06 | 1.04275 | 1.33725 | 3(Loss) | true |
| simdjson (reflection) | 1785.43 | 0.0551476 | 10136.4ms | 5373214 | 40 | 1.00206e+08 | 2.87006e+06 | 0.511589 | 1.38667 | 4(Loss) | true |
| Glaze | 1753.66 | 0.10729 | 10361.1ms | 5373214 | 30 | 2.94859e+08 | 2.92206e+06 | 0.620344 | 1.4118 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5612.32 | 0.324949 | 7097.3ms | 6661897 | 160 | 2.16502e+09 | 1.13202e+06 | 0.256329 | 0.441132 | 1(Win) | true |
| Glaze | 3126.76 | 0.115765 | 6342.92ms | 6661897 | 160 | 8.85273e+08 | 2.0319e+06 | 0.0412362 | 0.791765 | 2(Loss) | true |
| simdjson (reflection) | 375.793 | 0.399086 | 5115.86ms | 6661989 | 30 | 1.36573e+11 | 1.69066e+07 | 0.636083 | 6.5881 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5671.94 | 0.0534337 | 7188.9ms | 6661897 | 160 | 5.7317e+07 | 1.12012e+06 | 1.18703 | 0.436491 | 1(Win) | true |
| Glaze | 3403.83 | 0.0609535 | 5873.44ms | 6661897 | 40 | 5.17745e+07 | 1.86651e+06 | 0.357229 | 0.727345 | 2(Loss) | true |
| simdjson (reflection) | 373.554 | 0.152346 | 5236.68ms | 6661989 | 30 | 2.01413e+10 | 1.70079e+07 | 1.17641 | 6.62764 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2072.01 | 0.0705081 | 5884.08ms | 500299 | 1280 | 3.37415e+07 | 230271 | 0.0457079 | 1.19468 | 1(Win) | true |
| Jsonifier (two-stage) | 1799.29 | 0.173967 | 6811.96ms | 500299 | 80 | 1.70246e+07 | 265172 | 0.44325 | 1.3758 | 2(Loss) | true |
| Glaze | 1574.09 | 0.120363 | 7786.1ms | 500299 | 160 | 2.12965e+07 | 303110 | 0.0460853 | 1.57266 | 3(Loss) | true |
| simdjson (ondemand) | 1542.7 | 0.152226 | 7946.63ms | 500299 | 1280 | 2.83714e+08 | 309277 | 0.0651458 | 1.60467 | 4(Loss) | true |
| simdjson (reflection) | 1512.68 | 0.100822 | 8177.28ms | 500299 | 320 | 3.23614e+07 | 315415 | 0.106031 | 1.63652 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2485.9 | 0.137791 | 5832.78ms | 500299 | 160 | 1.11906e+07 | 191931 | 0.129234 | 0.995792 | 1(Win) | true |
| Jsonifier (two-stage) | 2136.66 | 0.106776 | 6574.8ms | 500299 | 320 | 1.81921e+07 | 223302 | 0.139128 | 1.15857 | 2(Loss) | true |
| simdjson (ondemand) | 1864.04 | 0.376797 | 7355.58ms | 500299 | 30 | 2.79053e+07 | 255962 | 0.0218831 | 1.32804 | 3(Loss) | true |
| Glaze | 1820.18 | 0.123105 | 7557.26ms | 500299 | 1280 | 1.33287e+08 | 262129 | 0.373698 | 1.36006 | 4(Loss) | true |
| simdjson (reflection) | 1744.61 | 0.136154 | 7873.29ms | 500299 | 320 | 4.43684e+07 | 273483 | 0.768495 | 1.41897 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10439.1 | 0.110308 | 4534.82ms | 500299 | 1280 | 3.25355e+06 | 45705.5 | 0.176111 | 0.237007 | 1(Win) | true |
| simdjson (reflection) | 8504.27 | 0.194085 | 5608.26ms | 500299 | 640 | 7.58838e+06 | 56103.9 | 0.158001 | 0.290976 | 2(Loss) | true |
| Glaze | 3692.8 | 0.0542674 | 6692.97ms | 500299 | 2560 | 1.25854e+07 | 129204 | 0.112791 | 0.670261 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10533.3 | 0.223072 | 4523.7ms | 500299 | 640 | 6.53432e+06 | 45296.6 | 0.279675 | 0.234846 | 1(Win) | true |
| simdjson (reflection) | 8455.57 | 0.0534126 | 5683.2ms | 500299 | 4890 | 4.44191e+06 | 56427 | 0.015802 | 0.292639 | 2(Loss) | true |
| Glaze | 4071.26 | 0.156622 | 6009.57ms | 500299 | 1280 | 4.31239e+07 | 117193 | 0.146328 | 0.607946 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3619.07 | 0.219909 | 7789.78ms | 1151920 | 40 | 1.78236e+07 | 303546 | 0.970088 | 0.684014 | 1(Win) | true |
| Jsonifier | 3199.14 | 0.171913 | 8876.86ms | 1151920 | 1280 | 4.46071e+08 | 343391 | 0.280686 | 0.773826 | 2(Loss) | true |
| simdjson (ondemand) | 3110.67 | 0.0452135 | 9004.96ms | 1151920 | 1280 | 3.2635e+07 | 353157 | 0.0455684 | 0.795823 | 3(Loss) | true |
| simdjson (reflection) | 3055.85 | 0.0701568 | 9155.04ms | 1151920 | 1280 | 8.14199e+07 | 359493 | 0.185024 | 0.8101 | 4(Loss) | true |
| Glaze | 2476.58 | 0.0652131 | 5623.45ms | 1151920 | 640 | 5.35539e+07 | 443579 | 0.387477 | 0.999612 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4166.03 | 0.148079 | 7461.7ms | 1151920 | 160 | 2.43954e+07 | 263694 | 0.141709 | 0.594212 | 1(Win) | true |
| simdjson (ondemand) | 3706.1 | 0.0873312 | 8501.6ms | 1151920 | 640 | 4.28874e+07 | 296419 | 0.100099 | 0.66797 | 2(Loss) | true |
| Jsonifier | 3636.73 | 0.295281 | 8495.71ms | 1151920 | 40 | 3.18239e+07 | 302073 | 0.15553 | 0.680715 | 3(Loss) | true |
| simdjson (reflection) | 3494.4 | 0.152348 | 8802.52ms | 1151920 | 160 | 3.67025e+07 | 314377 | 0.0207119 | 0.708439 | 4(Loss) | true |
| Glaze | 2772.91 | 0.175231 | 5562.25ms | 1151920 | 80 | 3.85553e+07 | 396174 | 0.182883 | 0.892779 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27253.5 | 0.849846 | 5034.24ms | 1439562 | 40 | 7.33089e+06 | 50374.2 | 0.63674 | 0.0907956 | 1(Win) | true |
| Glaze | 5334.02 | 0.309624 | 6829.93ms | 1439584 | 30 | 1.90526e+07 | 257384 | 0.177641 | 0.464096 | 2(Loss) | true |
| simdjson (reflection) | 554.428 | 0.0912545 | 7724.54ms | 1439562 | 80 | 4.08478e+08 | 2.4762e+06 | 0.275755 | 4.46551 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27082.7 | 0.200592 | 5068.37ms | 1439562 | 320 | 3.30869e+06 | 50692 | 0.173101 | 0.0913554 | 1(Win) | true |
| Glaze | 6215.18 | 0.182633 | 5683.25ms | 1439584 | 160 | 2.60402e+07 | 220894 | 0.107755 | 0.398299 | 2(Loss) | true |
| simdjson (reflection) | 568.896 | 0.287638 | 7427.41ms | 1439562 | 30 | 1.44547e+09 | 2.41322e+06 | 0.182398 | 4.35192 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1973.95 | 0.101452 | 2777.55ms | 56369 | 2560 | 1.95419e+06 | 27233.5 | 0.240712 | 1.25295 | 1(Win) | true |
| Jsonifier (two-stage) | 1751.52 | 0.170028 | 3116.14ms | 56369 | 320 | 871444 | 30692 | 0.16374 | 1.41223 | 2(Loss) | true |
| simdjson (reflection) | 1652.03 | 0.0890171 | 3270.59ms | 56369 | 2560 | 2.14797e+06 | 32540.3 | 0.213129 | 1.49742 | 3(Loss) | true |
| Glaze | 1590.63 | 0.274997 | 3296.82ms | 56369 | 80 | 691019 | 33796.5 | 0.274114 | 1.55523 | 4(Loss) | true |
| simdjson (ondemand) | 1436.81 | 0.218169 | 3870.37ms | 56369 | 160 | 1.06609e+06 | 37414.7 | 0.0423475 | 1.72193 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2480.95 | 0.08621 | 2475.95ms | 56369 | 2560 | 893307 | 21668.2 | 0.366523 | 0.996692 | 1(Win) | true |
| Jsonifier (two-stage) | 2059.55 | 0.0621764 | 2939.47ms | 56369 | 4890 | 1.28795e+06 | 26101.7 | 0.0279693 | 1.20091 | 2(Loss) | true |
| Glaze | 1936.69 | 0.108959 | 3068.64ms | 56369 | 30 | 27441.2 | 27757.4 | 0.573831 | 1.2772 | 3(Loss) | true |
| simdjson (reflection) | 1896.65 | 0.097625 | 3200.88ms | 56369 | 2560 | 1.96007e+06 | 28343.5 | 0.186807 | 1.30412 | 4(Loss) | true |
| simdjson (ondemand) | 1675.69 | 0.0555602 | 3575.91ms | 56369 | 4890 | 1.55357e+06 | 32080.9 | 0.544453 | 1.47626 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15615.3 | 0.0615287 | 349.899ms | 56369 | 40 | 179.471 | 3442.62 | 0.0627337 | 0.157308 | 1(Win) | true |
| simdjson (reflection) | 13465.5 | 0.0535788 | 403.444ms | 56369 | 40 | 183.013 | 3992.25 | 0.00125244 | 0.182628 | 2(Loss) | true |
| Glaze | 5255.41 | 0.145842 | 1026.67ms | 56369 | 4890 | 1.08828e+06 | 10229 | 0.109257 | 0.469837 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15780.2 | 0.159104 | 343.871ms | 56369 | 4890 | 143657 | 3406.66 | 0.00987262 | 0.155641 | 1(Win) | true |
| simdjson (reflection) | 13756.4 | 0.0958426 | 391.862ms | 56369 | 30 | 420.833 | 3907.83 | 0.306983 | 0.17867 | 2(Loss) | true |
| Glaze | 5889.1 | 0.10159 | 916.458ms | 56369 | 4890 | 420529 | 9128.33 | 0.0671692 | 0.41915 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2370.55 | 0.326521 | 3428.1ms | 83958 | 160 | 1.94612e+06 | 33776.3 | 0.0817951 | 1.04351 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2364.15 | 0.130522 | 3445.44ms | 83958 | 1280 | 2.50121e+06 | 33867.9 | 0.207917 | 1.04642 | 1(Tie) | true |
| Jsonifier | 2068.03 | 0.089474 | 3913.52ms | 83958 | 2560 | 3.07215e+06 | 38717.3 | 0.18242 | 1.19631 | 3(Loss) | true |
| simdjson (ondemand) | 2018.17 | 0.489478 | 4027.08ms | 83958 | 40 | 1.50847e+06 | 39673.8 | 0.0853109 | 1.2259 | 4(Loss) | true |
| Glaze | 1909.94 | 0.0654349 | 4212.98ms | 83958 | 4890 | 3.67971e+06 | 41922.1 | 0.0409533 | 1.29545 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2835.81 | 0.0514612 | 3194.79ms | 83958 | 4890 | 1.03238e+06 | 28234.8 | 0.0934343 | 0.872168 | 1(Win) | true |
| simdjson (reflection) | 2696.17 | 0.0681333 | 3333.19ms | 83958 | 2560 | 1.04807e+06 | 29697.2 | 0.0345347 | 0.917436 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 2366.54 | 0.323497 | 3699.45ms | 83958 | 320 | 3.83344e+06 | 33833.7 | 0.236629 | 1.04536 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2365.8 | 0.138025 | 3736.88ms | 83958 | 1280 | 2.79314e+06 | 33844.2 | 0.134439 | 1.04568 | 3(Tie) | true |
| Glaze | 2254.97 | 0.0840308 | 3920.18ms | 83958 | 2560 | 2.27908e+06 | 35507.6 | 0.243621 | 1.09711 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24343.6 | 0.0774201 | 367.316ms | 94370 | 40 | 327.692 | 3697 | 0.0153254 | 0.100946 | 1(Win) | true |
| Glaze | 4924.34 | 0.269645 | 1826.88ms | 94370 | 4890 | 1.18759e+07 | 18276.2 | 0.0475049 | 0.502014 | 2(Loss) | true |
| simdjson (reflection) | 521.829 | 0.254648 | 8864.42ms | 94370 | 80 | 1.54306e+07 | 172467 | 0.961727 | 4.74299 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24986.3 | 0.0832645 | 362.219ms | 94370 | 40 | 359.785 | 3601.9 | 0.295158 | 0.0983353 | 1(Win) | true |
| Glaze | 5513.92 | 0.16476 | 1641.76ms | 94370 | 2560 | 1.85137e+06 | 16322 | 0.0194246 | 0.448282 | 2(Loss) | true |
| simdjson (reflection) | 532.02 | 0.170516 | 8742.12ms | 94370 | 160 | 1.33125e+07 | 169163 | 0.00791458 | 4.65255 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1952.1 | 0.191293 | 2714.12ms | 53331 | 320 | 794886 | 26054.2 | 0.0878027 | 1.26702 | 1(Win) | true |
| Jsonifier | 1665.91 | 0.441486 | 3020.22ms | 53331 | 320 | 5.81356e+06 | 30530.1 | 0.115583 | 1.48484 | 2(Loss) | true |
| Jsonifier (two-stage) | 1634.53 | 0.148051 | 3141.78ms | 53331 | 1280 | 2.71648e+06 | 31116.2 | 0.171262 | 1.51328 | 3(Loss) | true |
| Glaze | 1477.76 | 0.102184 | 3457.49ms | 53331 | 2560 | 3.16635e+06 | 34417.2 | 0.355905 | 1.67403 | 4(Loss) | true |
| simdjson (ondemand) | 1301.74 | 0.287899 | 3937.79ms | 53331 | 160 | 2.02446e+06 | 39071 | 0.400494 | 1.90045 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2070.59 | 0.127716 | 2903.87ms | 53331 | 2560 | 2.51944e+06 | 24563.3 | 0.093064 | 1.19441 | 1(Win) | true |
| Jsonifier (two-stage) | 2051.51 | 0.174883 | 3024.83ms | 53331 | 1280 | 2.40613e+06 | 24791.7 | 0.18133 | 1.20539 | 2(Loss) | true |
| simdjson (reflection) | 2019.33 | 0.130873 | 3056.58ms | 53331 | 2560 | 2.78151e+06 | 25186.7 | 0.599057 | 1.22475 | 3(Loss) | true |
| Glaze | 1839.18 | 0.137729 | 3264.59ms | 53331 | 1280 | 1.85684e+06 | 27653.9 | 0.0476822 | 1.3448 | 4(Loss) | true |
| simdjson (ondemand) | 1441.24 | 0.549979 | 3988.64ms | 53331 | 30 | 1.13006e+06 | 35289.4 | 0.379499 | 1.7165 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14486.6 | 0.122887 | 396.919ms | 58581 | 30 | 673.775 | 3856.47 | 0.00605008 | 0.169733 | 1(Win) | true |
| simdjson (reflection) | 10988.2 | 0.0514725 | 514.83ms | 58581 | 40 | 273.948 | 5084.27 | 0.138691 | 0.22413 | 2(Loss) | true |
| Glaze | 6550.8 | 0.121263 | 851.918ms | 58581 | 4890 | 522986 | 8528.3 | 0.246642 | 0.376756 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14270.4 | 0.214843 | 393.459ms | 58581 | 30 | 2122.3 | 3914.9 | 0.00170292 | 0.172277 | 1(Win) | true |
| simdjson (reflection) | 10997.5 | 0.245243 | 507.513ms | 58581 | 2560 | 397336 | 5079.98 | 0.0283739 | 0.223936 | 2(Loss) | true |
| Glaze | 7744.28 | 0.105174 | 733.798ms | 58581 | 4890 | 281500 | 7213.99 | 0.354264 | 0.318518 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2224.66 | 0.0792971 | 2791.64ms | 65103 | 4890 | 2.39496e+06 | 27908.5 | 0.0197917 | 1.11177 | 1(Win) | true |
| Jsonifier (two-stage) | 2037.48 | 0.156722 | 3122.71ms | 65103 | 1280 | 2.91932e+06 | 30472.4 | 0.00593739 | 1.21396 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1773.29 | 0.205701 | 3545.2ms | 65103 | 320 | 1.65984e+06 | 35012.3 | 0.018604 | 1.39501 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 1755.45 | 0.514037 | 3650.57ms | 65103 | 160 | 5.28853e+06 | 35368.2 | 0.174401 | 1.40888 | 3(Tie) | true |
| simdjson (ondemand) | 1556.86 | 0.13418 | 4049.51ms | 65103 | 1280 | 3.66513e+06 | 39879.6 | 0.654085 | 1.58913 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2541.95 | 0.426767 | 2937.11ms | 65103 | 80 | 869243 | 24425 | 0.169977 | 0.972877 | 1(Win) | true |
| simdjson (reflection) | 2347.18 | 0.35902 | 3129.86ms | 65103 | 320 | 2.886e+06 | 26451.8 | 0.289112 | 1.05369 | 2(Loss) | true |
| Jsonifier | 2009.11 | 0.408815 | 3564.39ms | 65103 | 160 | 2.55369e+06 | 30902.7 | 0.0260967 | 1.23119 | 3(Loss) | true |
| Glaze | 1989.85 | 0.158472 | 3583.59ms | 65103 | 640 | 1.56476e+06 | 31201.9 | 0.0729102 | 1.24317 | 4(Loss) | true |
| simdjson (ondemand) | 1730.78 | 0.355908 | 4149.86ms | 65103 | 160 | 2.60803e+06 | 35872.3 | 0.0440954 | 1.4294 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18593.7 | 0.0451008 | 409.452ms | 78778 | 160 | 531.332 | 4040.53 | 0.00262954 | 0.132245 | 1(Win) | true |
| Glaze | 5238.43 | 0.205778 | 1438.78ms | 78778 | 1280 | 1.11485e+06 | 14341.8 | 0.360143 | 0.47173 | 2(Loss) | true |
| simdjson (reflection) | 657.608 | 0.368156 | 5955.75ms | 78778 | 80 | 1.41524e+07 | 114245 | 0.230859 | 3.76342 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18789.5 | 0.112582 | 404.307ms | 78778 | 30 | 607.909 | 3998.43 | 0.0208458 | 0.130882 | 1(Win) | true |
| Glaze | 6095.17 | 0.268452 | 1234.35ms | 78778 | 320 | 350364 | 12325.9 | 0.337776 | 0.405308 | 2(Loss) | true |
| simdjson (reflection) | 657.079 | 0.725059 | 5863.39ms | 78778 | 30 | 2.06178e+07 | 114337 | 0.00239065 | 3.76674 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1997.28 | 0.0779685 | 570.285ms | 11812 | 30 | 580.133 | 5640.07 | 0.243496 | 1.23367 | 1(Win) | true |
| Glaze | 1746.29 | 0.133742 | 653.799ms | 11812 | 30 | 2232.91 | 6450.7 | 0.0625646 | 1.41187 | 2(Loss) | true |
| Jsonifier (two-stage) | 1606.86 | 0.0440694 | 712.81ms | 11812 | 40 | 381.789 | 7010.43 | 0.170871 | 1.53458 | 3(Loss) | true |
| simdjson (reflection) | 1441.13 | 0.0448651 | 809.122ms | 11812 | 80 | 983.897 | 7816.66 | 0.553898 | 1.712 | 4(Loss) | true |
| simdjson (ondemand) | 1145.68 | 0.102364 | 989.362ms | 11812 | 40 | 4052.1 | 9832.45 | 0.0894099 | 2.15498 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2140.97 | 0.0520675 | 564.699ms | 11812 | 30 | 225.154 | 5261.53 | 0.0843304 | 1.15046 | 1(Win) | true |
| Glaze | 1786.25 | 0.150387 | 664.174ms | 11812 | 4890 | 439840 | 6306.4 | 0.321858 | 1.37973 | 2(Loss) | true |
| Jsonifier (two-stage) | 1689.06 | 0.0642733 | 701.069ms | 11812 | 30 | 551.237 | 6669.27 | 0.0599407 | 1.45987 | 3(Loss) | true |
| simdjson (reflection) | 1482.59 | 0.0856601 | 815.92ms | 11812 | 30 | 1270.82 | 7598.07 | 0.0882582 | 1.66406 | 4(Loss) | true |
| simdjson (ondemand) | 1246.51 | 0.116551 | 974.417ms | 11812 | 30 | 3328.23 | 9037.1 | 0.0236008 | 1.98065 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15509.8 | 0.230664 | 75.3987ms | 11812 | 40 | 112.267 | 726.3 | 0.110026 | 0.154125 | 1(Win) | true |
| simdjson (reflection) | 12054.4 | 0.0320888 | 98.3599ms | 11812 | 640 | 57.5493 | 934.494 | 0.0872038 | 0.199636 | 2(Loss) | true |
| Glaze | 3729.5 | 0.2882 | 303.965ms | 11812 | 1280 | 96993.6 | 3020.46 | 0.412383 | 0.65789 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16205.9 | 0.0844637 | 75.6263ms | 11812 | 160 | 55.1522 | 695.106 | 0.024271 | 0.146942 | 1(Win) | true |
| simdjson (reflection) | 12324.1 | 0.0756242 | 93.8276ms | 11812 | 80 | 38.2253 | 914.05 | 0.0437804 | 0.194986 | 2(Loss) | true |
| Glaze | 4277.45 | 0.143225 | 269.72ms | 11812 | 30 | 426.809 | 2633.53 | 0.135616 | 0.572878 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3058.39 | 0.0524287 | 792.261ms | 25388 | 30 | 516.809 | 7916.53 | 0.237197 | 0.806751 | 1(Win) | true |
| Jsonifier | 3047.85 | 0.0930966 | 798.632ms | 25388 | 4890 | 267453 | 7943.92 | 0.0228154 | 0.809617 | 2(Loss) | true |
| simdjson (reflection) | 2834.12 | 0.0503168 | 858.631ms | 25388 | 80 | 1478.22 | 8543.01 | 0.178045 | 0.87087 | 3(Loss) | true |
| Glaze | 2562.54 | 0.191294 | 957.111ms | 25388 | 1280 | 418145 | 9448.39 | 0.0296269 | 0.963503 | 4(Loss) | true |
| simdjson (ondemand) | 2338.24 | 0.0768937 | 1063.77ms | 25388 | 40 | 2535.83 | 10354.8 | 0.00917538 | 1.05613 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3142.64 | 0.129965 | 811.274ms | 25388 | 4890 | 490265 | 7704.3 | 0.00579567 | 0.785102 | 1(Win) | true |
| Jsonifier (two-stage) | 3075.35 | 0.0322645 | 793.53ms | 25388 | 80 | 516.187 | 7872.88 | 1.09761 | 0.802257 | 2(Loss) | true |
| simdjson (reflection) | 2963.91 | 0.283936 | 889.983ms | 25388 | 640 | 344307 | 8168.89 | 0.225405 | 0.832618 | 3(Loss) | true |
| Glaze | 2666.95 | 0.0585576 | 939.077ms | 25388 | 30 | 847.845 | 9078.5 | 0.0741129 | 0.925754 | 4(Loss) | true |
| simdjson (ondemand) | 2438.17 | 0.276889 | 1043.54ms | 25388 | 640 | 483862 | 9930.35 | 0.0471343 | 1.01276 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 32352.5 | 0.0660317 | 96.1742ms | 31235 | 320 | 118.283 | 920.734 | 0.110862 | 0.0744038 | 1(Win) | true |
| Glaze | 5645.73 | 0.079343 | 523.081ms | 31235 | 30 | 525.752 | 5276.2 | 0.151855 | 0.436339 | 2(Loss) | true |
| simdjson (reflection) | 585.217 | 0.205316 | 5315.38ms | 31235 | 320 | 3.49497e+06 | 50900.8 | 0.288222 | 4.22855 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 33895.3 | 0.0774446 | 90.991ms | 31235 | 80 | 37.0576 | 878.825 | 0.116769 | 0.070844 | 1(Win) | true |
| Glaze | 6455.68 | 0.0997569 | 472.572ms | 31235 | 30 | 635.633 | 4614.23 | 0.130202 | 0.381482 | 2(Loss) | true |
| simdjson (reflection) | 559.189 | 0.143808 | 5178.75ms | 31235 | 320 | 1.87793e+06 | 53270 | 0.544072 | 4.42531 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3002.74 | 0.0700616 | 3435.67ms | 108313 | 4890 | 2.84051e+06 | 34400.4 | 0.462701 | 0.823868 | 1(Win) | true |
| Jsonifier (two-stage) | 2392.29 | 0.101757 | 4281.72ms | 108313 | 2560 | 4.94196e+06 | 43178.4 | 0.545565 | 1.03427 | 2(Loss) | true |
| Glaze | 1700.64 | 0.193198 | 6197.12ms | 108313 | 160 | 2.20324e+06 | 60739.2 | 0.277068 | 1.45518 | 3(Loss) | true |
| simdjson (reflection) | 1575.61 | 0.0876753 | 6558.62ms | 108313 | 2560 | 8.45781e+06 | 65558.9 | 0.34158 | 1.57071 | 4(Loss) | true |
| simdjson (ondemand) | 1064.57 | 0.279582 | 5035.27ms | 108313 | 640 | 4.7099e+07 | 97030 | 0.557991 | 2.32501 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3502.46 | 0.200303 | 3116.66ms | 108313 | 640 | 2.23342e+06 | 29492.2 | 0.204128 | 0.706252 | 1(Win) | true |
| Jsonifier (two-stage) | 2681.82 | 0.501409 | 3923.1ms | 108313 | 40 | 1.49192e+06 | 38516.8 | 0.131869 | 0.922523 | 2(Loss) | true |
| Glaze | 1874.21 | 0.260832 | 5908.48ms | 108313 | 80 | 1.65323e+06 | 55114 | 0.0597947 | 1.32038 | 3(Loss) | true |
| simdjson (reflection) | 1581.66 | 0.0971502 | 6524.47ms | 108313 | 640 | 2.57634e+06 | 65308.2 | 0.13225 | 1.56469 | 4(Loss) | true |
| simdjson (ondemand) | 1169.04 | 0.341813 | 9413.85ms | 108313 | 80 | 7.29744e+06 | 88359.3 | 0.277973 | 2.11725 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23912.1 | 0.134893 | 429.56ms | 108313 | 30 | 1018.65 | 4319.8 | 0.353699 | 0.102906 | 1(Win) | true |
| simdjson (reflection) | 14630.4 | 0.0293063 | 701.521ms | 108313 | 40 | 171.251 | 7060.32 | 0.630814 | 0.168594 | 2(Loss) | true |
| Glaze | 2536.23 | 0.117581 | 4092.74ms | 108313 | 1280 | 2.93539e+06 | 40727.8 | 0.123616 | 0.975582 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25550.9 | 0.175654 | 413.529ms | 108313 | 2560 | 129094 | 4042.73 | 0.171812 | 0.0962908 | 1(Win) | true |
| simdjson (reflection) | 15101.4 | 0.0952834 | 689.581ms | 108313 | 4890 | 207716 | 6840.11 | 0.0508796 | 0.163333 | 2(Loss) | true |
| Glaze | 2650.8 | 0.174253 | 4048.47ms | 108313 | 640 | 2.95085e+06 | 38967.7 | 0.0912224 | 0.93338 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3649.42 | 0.0486428 | 4836ms | 183677 | 4890 | 2.66568e+06 | 47998.9 | 0.0666023 | 0.677995 | 1(Win) | true |
| Jsonifier | 2814.52 | 0.151222 | 6278.71ms | 183677 | 640 | 5.66906e+06 | 62237.3 | 0.628424 | 0.879254 | 2(Loss) | true |
| simdjson (reflection) | 2536.96 | 0.128692 | 6868.7ms | 183677 | 640 | 5.05322e+06 | 69046.5 | 0.154743 | 0.975531 | 3(Loss) | true |
| Glaze | 2317.03 | 0.216262 | 7765.46ms | 183677 | 320 | 8.55376e+06 | 75600.4 | 0.342266 | 1.06817 | 4(Loss) | true |
| simdjson (ondemand) | 1748.68 | 0.309541 | 5170.13ms | 183677 | 80 | 7.69156e+06 | 100172 | 0.400136 | 1.41546 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4014.2 | 0.158672 | 4564.87ms | 183677 | 640 | 3.06826e+06 | 43637.1 | 0.225923 | 0.616381 | 1(Win) | true |
| Jsonifier | 2866.74 | 0.181577 | 6075.01ms | 183677 | 640 | 7.87837e+06 | 61103.5 | 0.041627 | 0.863258 | 2(Loss) | true |
| simdjson (reflection) | 2489.44 | 0.0854345 | 7130.14ms | 183677 | 1280 | 4.62576e+06 | 70364.5 | 0.166511 | 0.994142 | 3(Loss) | true |
| Glaze | 2387.53 | 0.147286 | 7490.7ms | 183677 | 2560 | 2.98933e+07 | 73367.8 | 1.28557 | 1.03661 | 4(Loss) | true |
| simdjson (ondemand) | 1900.01 | 0.0468599 | 9360.29ms | 183677 | 4890 | 9.12657e+06 | 92193 | 0.684951 | 1.30269 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 39634.4 | 0.0521305 | 520.524ms | 213963 | 30 | 216.092 | 5148.33 | 0.123512 | 0.062147 | 1(Win) | true |
| Glaze | 4010.05 | 0.21561 | 5263.48ms | 213963 | 320 | 3.85184e+06 | 50884.9 | 0.250152 | 0.617099 | 2(Loss) | true |
| simdjson (reflection) | 496.954 | 0.168412 | 5173.29ms | 213963 | 160 | 7.6509e+07 | 410604 | 0.344195 | 4.98147 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 40684.7 | 0.0559813 | 499.516ms | 213963 | 40 | 315.328 | 5015.43 | 0.0330756 | 0.0605144 | 1(Win) | true |
| Glaze | 4165.79 | 0.0637756 | 4901.28ms | 213963 | 4890 | 4.772e+06 | 48982.5 | 0.236447 | 0.594001 | 2(Loss) | true |
| simdjson (reflection) | 507.978 | 0.195098 | 5138.59ms | 213963 | 80 | 4.9134e+07 | 401692 | 0.661681 | 4.87343 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 869.392 | 0.143482 | 6424.59ms | 1834197 | 80 | 6.66728e+08 | 2.01201e+06 | 2.71491 | 2.84774 | -(Win) | false |
| Jsonifier (two-stage) | 746.528 | 0.0747534 | 7339ms | 1834197 | 80 | 2.45444e+08 | 2.34315e+06 | 0.903896 | 3.31643 | 2(Loss) | true |
| Glaze | 657.36 | 0.0877353 | 8335.18ms | 1834197 | 160 | 8.72076e+08 | 2.66099e+06 | 0.433706 | 3.76629 | 3(Loss) | true |
| simdjson (reflection) | 621.466 | 0.0499164 | 8851.33ms | 1834197 | 160 | 3.15838e+08 | 2.81468e+06 | 0.0579789 | 3.98382 | 4(Loss) | true |
| simdjson (ondemand) | 565.21 | 0.256811 | 9850.81ms | 1834197 | 30 | 1.89506e+09 | 3.09483e+06 | 0.681529 | 4.38034 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 931.274 | 0.168792 | 6531.58ms | 1834197 | 30 | 3.01552e+08 | 1.87831e+06 | 0.214985 | 2.6585 | 1(Win) | true |
| Jsonifier (two-stage) | 841.829 | 0.101648 | 7219.7ms | 1834197 | 40 | 1.78446e+08 | 2.07789e+06 | 0.39677 | 2.94098 | 2(Loss) | true |
| Glaze | 710.204 | 0.147559 | 8513.26ms | 1834197 | 30 | 3.9626e+08 | 2.46299e+06 | 0.889776 | 3.48605 | 3(Loss) | true |
| simdjson (reflection) | 689.654 | 0.0560234 | 8547ms | 1834197 | 80 | 1.61532e+08 | 2.53638e+06 | 0.22718 | 3.58992 | 4(Loss) | true |
| simdjson (ondemand) | 624.538 | 0.171532 | 9771.22ms | 1834197 | 30 | 6.92447e+08 | 2.80083e+06 | 0.244268 | 3.96423 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1118.55 | 0.126676 | 9836.75ms | 1834197 | 40 | 1.56974e+08 | 1.56383e+06 | 0.0693672 | 2.21337 | 1(Win) | true |
| Glaze | 907.427 | 0.101478 | 5936.28ms | 1833577 | 80 | 3.05918e+08 | 1.92702e+06 | 0.775613 | 2.72838 | 2(Loss) | true |
| simdjson (reflection) | 715.247 | 0.293689 | 7652.02ms | 1922245 | 30 | 1.69982e+09 | 2.56303e+06 | 0.0225659 | 3.46147 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1126.72 | 0.188544 | 9836.21ms | 1834197 | 30 | 2.57045e+08 | 1.5525e+06 | 0.127301 | 2.19731 | 1(Win) | true |
| Glaze | 905.841 | 0.131661 | 5956.97ms | 1833577 | 30 | 1.93789e+08 | 1.9304e+06 | 0.575695 | 2.73314 | 2(Loss) | true |
| simdjson (reflection) | 727.742 | 0.0615915 | 7849.54ms | 1922245 | 40 | 9.62865e+07 | 2.51902e+06 | 0.120411 | 3.40204 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2668.4 | 0.167774 | 8179.83ms | 7351818 | 160 | 3.10925e+09 | 2.62751e+06 | 1.86157 | 0.927819 | 1(Win) | true |
| Jsonifier | 2500.27 | 0.202951 | 8715.82ms | 7351818 | 40 | 1.29556e+09 | 2.80419e+06 | 0.0114337 | 0.990209 | 2(Loss) | true |
| simdjson (reflection) | 2194.13 | 0.366473 | 9708.72ms | 7351818 | 30 | 4.11404e+09 | 3.19545e+06 | 0.177527 | 1.12837 | 3(Loss) | true |
| simdjson (ondemand) | 2036.75 | 0.222822 | 5278.98ms | 7351818 | 80 | 4.70675e+09 | 3.44237e+06 | 1.17788 | 1.21532 | 4(Loss) | true |
| Glaze | 2017.57 | 0.104811 | 5201.33ms | 7351818 | 30 | 3.97984e+08 | 3.47508e+06 | 0.624453 | 1.22712 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2847.24 | 0.563322 | 8316.31ms | 7351818 | 160 | 3.07877e+10 | 2.46247e+06 | 2.17173 | 0.869546 | 1(Win) | true |
| Jsonifier | 2730.24 | 0.104841 | 8853.12ms | 7351818 | 40 | 2.89941e+08 | 2.56799e+06 | 0.435343 | 0.9068 | 2(Loss) | true |
| simdjson (reflection) | 2427.12 | 0.322365 | 9564.47ms | 7351818 | 40 | 3.46865e+09 | 2.8887e+06 | 0.0172118 | 1.02004 | 3(Loss) | true |
| Glaze | 2184.4 | 0.166683 | 5158.3ms | 7351818 | 80 | 2.28981e+09 | 3.20968e+06 | 0.0297478 | 1.1334 | 4(Loss) | true |
| simdjson (ondemand) | 2173.6 | 0.129504 | 5171.9ms | 7351818 | 80 | 1.39601e+09 | 3.22564e+06 | 0.348294 | 1.13903 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6133 | 0.118615 | 5000.68ms | 9930848 | 80 | 2.6841e+08 | 1.54423e+06 | 2.17439 | 0.403683 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3750.67 | 0.16846 | 8164.36ms | 9930228 | 30 | 5.42767e+08 | 2.52493e+06 | 2.9951 | 0.660086 | -(Loss) | false |
| simdjson (reflection) | 191.745 | 0.999288 | 14865ms | 10018896 | 30 | 7.43866e+12 | 4.98306e+07 | 1.77372 | 12.912 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5728.21 | 0.606804 | 5063.96ms | 9930848 | 80 | 8.05233e+09 | 1.65336e+06 | 0.553765 | 0.432199 | 1(Win) | true |
| Glaze | 3792.68 | 0.250272 | 7762.76ms | 9930228 | 40 | 1.5621e+09 | 2.49697e+06 | 0.211408 | 0.652775 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 245.286 | 3.2235 | 11261.5ms | 10018896 | 30 | 4.73011e+13 | 3.89536e+07 | 4.39679 | 10.0936 | -(Loss) | false |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 839.829 | 0.0618372 | 6443.87ms | 1834197 | 160 | 2.65418e+08 | 2.08284e+06 | 0.2349 | 2.94797 | 1(Win) | true |
| Jsonifier (two-stage) | 740.725 | 0.12464 | 7347.74ms | 1834197 | 80 | 6.93084e+08 | 2.36151e+06 | 0.155465 | 3.3424 | 2(Loss) | true |
| Glaze | 651.952 | 0.105104 | 8355.25ms | 1834197 | 30 | 2.38573e+08 | 2.68306e+06 | 1.203 | 3.79753 | 3(Loss) | true |
| simdjson (reflection) | 615.008 | 0.0629491 | 8895.27ms | 1834197 | 160 | 5.12896e+08 | 2.84423e+06 | 0.673821 | 4.02564 | 4(Loss) | true |
| simdjson (ondemand) | 553.055 | 0.113764 | 10018.5ms | 1834197 | 30 | 3.88406e+08 | 3.16284e+06 | 0.120516 | 4.47656 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 939.938 | 0.134541 | 6585.58ms | 1834197 | 40 | 2.50764e+08 | 1.861e+06 | 0.455178 | 2.63399 | 1(Win) | true |
| Jsonifier (two-stage) | 811.688 | 0.0917692 | 7398.46ms | 1834197 | 80 | 3.12895e+08 | 2.15505e+06 | 1.10669 | 3.05017 | 2(Loss) | true |
| Glaze | 717.811 | 0.122035 | 8180.55ms | 1834197 | 160 | 1.41501e+09 | 2.43689e+06 | 0.425407 | 3.44908 | 3(Loss) | true |
| simdjson (reflection) | 680.137 | 0.0797522 | 8605.22ms | 1834197 | 160 | 6.73138e+08 | 2.57187e+06 | 0.0705947 | 3.64015 | 4(Loss) | true |
| simdjson (ondemand) | 605.768 | 0.0837196 | 9723.81ms | 1834197 | 160 | 9.35092e+08 | 2.88762e+06 | 0.39514 | 4.08706 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1139.05 | 0.0448267 | 9698.6ms | 1834197 | 320 | 1.51646e+08 | 1.53569e+06 | 0.211466 | 2.17354 | 1(Win) | true |
| Glaze | 898.328 | 0.046694 | 6062.79ms | 1833577 | 40 | 3.30454e+07 | 1.94654e+06 | 0.0832719 | 2.75601 | 2(Loss) | true |
| simdjson (reflection) | 733.283 | 0.060298 | 7853.89ms | 1922245 | 80 | 1.81791e+08 | 2.49999e+06 | 0.274253 | 3.37634 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.65 | 0.0341381 | 9718.42ms | 1834197 | 160 | 4.37748e+07 | 1.53219e+06 | 0.725925 | 2.16859 | 1(Win) | true |
| Glaze | 927.718 | 0.139974 | 5853.91ms | 1833577 | 40 | 2.78432e+08 | 1.88488e+06 | 0.00814398 | 2.66869 | 2(Loss) | true |
| simdjson (reflection) | 733.509 | 0.202472 | 7830.36ms | 1922245 | 30 | 7.68173e+08 | 2.49921e+06 | 0.461519 | 3.37529 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2592.76 | 0.0833168 | 8484.63ms | 7351818 | 30 | 1.52283e+08 | 2.70416e+06 | 0.0868327 | 0.95489 | 1(Win) | true |
| Jsonifier | 2535.84 | 0.183855 | 8746.8ms | 7351818 | 30 | 7.75213e+08 | 2.76486e+06 | 0.149625 | 0.976305 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 2190.37 | 0.0480381 | 10153.7ms | 7351818 | 80 | 1.89154e+08 | 3.20094e+06 | 2.64022 | 1.13031 | -(Loss) | false |
| Glaze | 1998.01 | 0.443652 | 5245.26ms | 7351818 | 30 | 7.27114e+09 | 3.50912e+06 | 1.11323 | 1.23914 | 4(Loss) | true |
| simdjson (ondemand) | 1969.52 | 0.0854226 | 5315.97ms | 7351818 | 30 | 2.77418e+08 | 3.55987e+06 | 0.559998 | 1.25706 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2802.09 | 0.181359 | 8586.51ms | 7351818 | 80 | 1.64737e+09 | 2.50214e+06 | 0.0885435 | 0.883553 | 1(Win) | true |
| Jsonifier | 2771.22 | 0.0962166 | 8677.92ms | 7351818 | 40 | 2.37032e+08 | 2.53002e+06 | 0.00501438 | 0.89339 | 2(Loss) | true |
| simdjson (reflection) | 2399.57 | 0.0671262 | 9798.42ms | 7351818 | 30 | 1.15406e+08 | 2.92188e+06 | 0.383967 | 1.03177 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 2148.15 | 0.0551744 | 5283.71ms | 7351818 | 30 | 9.7287e+07 | 3.26384e+06 | 0.00735792 | 1.15252 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2145.5 | 0.187248 | 5335.31ms | 7351818 | 80 | 2.99542e+09 | 3.26788e+06 | 0.314734 | 1.15396 | 4(Tie) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5926.68 | 0.0661127 | 5033.45ms | 9930848 | 80 | 8.92912e+07 | 1.59799e+06 | 0.150878 | 0.417733 | 1(Win) | true |
| Glaze | 3159.42 | 0.310914 | 9221.39ms | 9930228 | 30 | 2.60559e+09 | 2.99745e+06 | 0.270497 | 0.783565 | 2(Loss) | true |
| simdjson (reflection) | 370.511 | 1.0179 | 7771.01ms | 10018896 | 30 | 2.06712e+12 | 2.57881e+07 | 0.647536 | 6.68212 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5934.45 | 0.0699161 | 5006.88ms | 9930848 | 30 | 3.73497e+07 | 1.5959e+06 | 0.0446174 | 0.417186 | 1(Win) | true |
| Glaze | 3784.89 | 0.105471 | 7887.51ms | 9930228 | 40 | 2.78574e+08 | 2.50211e+06 | 0.103587 | 0.654119 | 2(Loss) | true |
| simdjson (reflection) | 286.803 | 2.74907 | 10100.6ms | 10018896 | 30 | 2.51632e+13 | 3.33147e+07 | 1.05878 | 8.63248 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1136.06 | 0.144297 | 9889.88ms | 461466 | 640 | 1.99971e+08 | 387380 | 0.0691148 | 2.17902 | 1(Win) | true |
| Jsonifier | 1104.56 | 0.23298 | 5109.04ms | 461466 | 40 | 3.44666e+07 | 398428 | 0.0735434 | 2.24126 | 2(Loss) | true |
| simdjson (ondemand) | 1064.4 | 0.10761 | 5243.9ms | 461466 | 320 | 6.33472e+07 | 413462 | 0.444256 | 2.32581 | 3(Loss) | true |
| Jsonifier (two-stage) | 1027.62 | 0.0583342 | 5477.29ms | 461466 | 640 | 3.99429e+07 | 428259 | 0.129449 | 2.40907 | 4(Loss) | true |
| Glaze | 1008.46 | 0.0921614 | 5568.34ms | 461466 | 640 | 1.03523e+08 | 436395 | 0.157328 | 2.45482 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1466.32 | 0.135226 | 9205.34ms | 461466 | 160 | 2.63552e+07 | 300131 | 0.313728 | 1.68823 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1411.66 | 0.20931 | 5020.45ms | 461466 | 30 | 1.27737e+07 | 311751 | 0.389804 | 1.75369 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1405.23 | 0.105746 | 9469.98ms | 461466 | 320 | 3.50966e+07 | 313179 | 0.12259 | 1.76168 | 2(Tie) | true |
| Jsonifier (two-stage) | 1305.12 | 0.146536 | 5344.63ms | 461466 | 80 | 1.95326e+07 | 337201 | 0.168919 | 1.89676 | 4(Loss) | true |
| Glaze | 1232.79 | 0.136222 | 5403.96ms | 461466 | 320 | 7.56733e+07 | 356985 | 0.153095 | 2.00815 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14516.2 | 0.185797 | 3136.28ms | 461466 | 640 | 2.03064e+06 | 30317.1 | 0.322763 | 0.170382 | 1(Win) | true |
| simdjson (reflection) | 10088.8 | 0.272053 | 4338.35ms | 461466 | 160 | 2.25337e+06 | 43621.7 | 0.208035 | 0.245234 | 2(Loss) | true |
| Glaze | 3365.72 | 0.161958 | 6699.4ms | 461466 | 160 | 7.17548e+06 | 130756 | 0.252157 | 0.735044 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14455.2 | 0.241519 | 3030.04ms | 461466 | 640 | 3.46031e+06 | 30444.9 | 0.0422868 | 0.171095 | 1(Win) | true |
| simdjson (reflection) | 10646.4 | 0.12608 | 4215.6ms | 461466 | 1280 | 3.47673e+06 | 41336.6 | 0.224732 | 0.232365 | 2(Loss) | true |
| Glaze | 3571.3 | 0.0857526 | 6391.67ms | 461466 | 640 | 7.14664e+06 | 123229 | 0.330659 | 0.693081 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1713.63 | 0.203988 | 5304.94ms | 728486 | 40 | 2.73575e+07 | 405419 | 0.122981 | 1.44464 | 1(Win) | true |
| simdjson (reflection) | 1704.03 | 0.195837 | 5035.94ms | 728486 | 160 | 1.01999e+08 | 407703 | 0.237306 | 1.45278 | 2(Loss) | true |
| Jsonifier (two-stage) | 1678.48 | 0.0580554 | 5336.55ms | 728486 | 320 | 1.84775e+07 | 413908 | 0.0867248 | 1.47491 | 3(Loss) | true |
| Jsonifier | 1534.95 | 0.0740074 | 5750.25ms | 728486 | 640 | 7.18095e+07 | 452612 | 0.178591 | 1.61283 | 4(Loss) | true |
| Glaze | 1423 | 0.229092 | 6336.15ms | 728486 | 30 | 3.75297e+07 | 488222 | 0.0124549 | 1.73976 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2263.44 | 0.193569 | 9275.51ms | 728486 | 320 | 1.1296e+08 | 306939 | 0.00472282 | 1.09372 | 1(Win) | true |
| simdjson (ondemand) | 2135.34 | 0.26516 | 9725.61ms | 728486 | 40 | 2.97705e+07 | 325353 | 0.305497 | 1.15933 | 2(Loss) | true |
| Jsonifier (two-stage) | 2100.78 | 0.16852 | 5135.5ms | 728486 | 40 | 1.24235e+07 | 330705 | 1.15035 | 1.17841 | 3(Loss) | true |
| Jsonifier | 1885.27 | 0.194062 | 5605.46ms | 728486 | 30 | 1.53425e+07 | 368508 | 0.032517 | 1.31315 | 4(Loss) | true |
| Glaze | 1674.77 | 0.0954135 | 6305.12ms | 728486 | 80 | 1.25327e+07 | 414827 | 0.138949 | 1.47819 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24798.7 | 0.0903258 | 3224.11ms | 837491 | 2560 | 2.16653e+06 | 32207 | 0.19512 | 0.0997239 | 1(Win) | true |
| Glaze | 3945.44 | 0.395616 | 5285.55ms | 837491 | 30 | 1.92415e+07 | 202434 | 0.244809 | 0.627417 | 2(Loss) | true |
| simdjson (reflection) | 578.894 | 0.103999 | 8839.14ms | 837491 | 30 | 6.17651e+07 | 1.37969e+06 | 0.437775 | 4.27671 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24902.9 | 0.0922162 | 3200.54ms | 837491 | 4890 | 4.27744e+06 | 32072.3 | 0.0341087 | 0.0993193 | 1(Win) | true |
| Glaze | 4164.08 | 0.325486 | 9638.81ms | 837491 | 40 | 1.559e+07 | 191805 | 0.819821 | 0.594487 | 2(Loss) | true |
| simdjson (reflection) | 581.273 | 0.127131 | 9013.11ms | 837491 | 30 | 9.1542e+07 | 1.37404e+06 | 0.111168 | 4.25923 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8455.89 | 0.152175 | 5284.97ms | 466906 | 640 | 4.10969e+06 | 52658.7 | 0.332487 | 0.292634 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 8112.7 | 0.7015 | 5270.07ms | 466906 | 40 | 5.92985e+06 | 54886.3 | 0.116908 | 0.305009 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 8088.91 | 0.0840601 | 5579.2ms | 466906 | 2560 | 5.4815e+06 | 55047.8 | 0.00465881 | 0.305934 | 2(Tie) | true |
| simdjson (reflection) | 7741.58 | 0.220876 | 5731.44ms | 466906 | 160 | 2.58236e+06 | 57517.5 | 0.193467 | 0.319664 | 4(Loss) | true |
| Glaze | 3266.96 | 0.0586083 | 7086.35ms | 466906 | 1280 | 8.16771e+06 | 136297 | 0.057037 | 0.75769 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8734.78 | 0.0679777 | 5228.52ms | 466906 | 4890 | 5.87215e+06 | 50977.4 | 0.0639553 | 0.283295 | 1(Win) | true |
| Jsonifier | 8682.38 | 0.194436 | 5347.78ms | 466906 | 2560 | 2.54552e+07 | 51285 | 0.540843 | 0.284988 | 2(Loss) | true |
| simdjson (ondemand) | 8255.15 | 0.355697 | 5744.67ms | 466906 | 30 | 1.10431e+06 | 53939.2 | 0.00908513 | 0.299771 | 3(Loss) | true |
| simdjson (reflection) | 7777.38 | 0.187874 | 5825.39ms | 466906 | 160 | 1.85117e+06 | 57252.7 | 0.179603 | 0.318189 | 4(Loss) | true |
| Glaze | 3298.27 | 0.046332 | 7023.27ms | 466906 | 1280 | 5.00794e+06 | 135003 | 0.0604939 | 0.750506 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9969.39 | 0.337775 | 6134.92ms | 631514 | 40 | 1.6655e+06 | 60410.8 | 0.342744 | 0.248194 | 1(Win) | true |
| Jsonifier | 9688.42 | 0.637504 | 6052.83ms | 631514 | 40 | 6.28184e+06 | 62162.8 | 0.0222217 | 0.255386 | 2(Loss) | true |
| simdjson (reflection) | 9216.42 | 0.102401 | 6715.3ms | 631514 | 1280 | 5.7314e+06 | 65346.3 | 0.0984668 | 0.26849 | 3(Loss) | true |
| simdjson (ondemand) | 8779.49 | 0.0869838 | 6771.72ms | 631514 | 2560 | 9.11473e+06 | 68598.4 | 0.703516 | 0.281832 | 4(Loss) | true |
| Glaze | 3690.18 | 0.169091 | 8107.54ms | 631514 | 80 | 6.09258e+06 | 163206 | 0.0259172 | 0.670785 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10125 | 0.212135 | 5953.91ms | 631514 | 2560 | 4.07606e+07 | 59482.3 | 0.104468 | 0.244399 | 1(Win) | true |
| Jsonifier (two-stage) | 10039.1 | 0.110322 | 6128.95ms | 631514 | 640 | 2.80342e+06 | 59991.6 | 0.0419923 | 0.246492 | 2(Loss) | true |
| simdjson (reflection) | 9100.38 | 0.0915773 | 6861.85ms | 631514 | 1280 | 4.70146e+06 | 66179.5 | 0.369964 | 0.271923 | 3(Loss) | true |
| simdjson (ondemand) | 8865.07 | 0.112598 | 6652.52ms | 631514 | 640 | 3.74495e+06 | 67936.1 | 0.0965717 | 0.279157 | 4(Loss) | true |
| Glaze | 3717.61 | 0.161437 | 7968.59ms | 631514 | 80 | 5.47187e+06 | 162002 | 1.04948 | 0.665857 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1955.62 | 0.173689 | 6056.86ms | 466906 | 80 | 1.2512e+07 | 227691 | 0.0309699 | 1.2658 | 1(Win) | true |
| Jsonifier (two-stage) | 1768.03 | 0.192253 | 6627.08ms | 466906 | 160 | 3.75099e+07 | 251849 | 0.0291136 | 1.40013 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1656.06 | 0.24251 | 6903.14ms | 466906 | 40 | 1.70069e+07 | 268877 | 0.180274 | 1.4948 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1642.68 | 0.356469 | 6952.03ms | 466906 | 40 | 3.73472e+07 | 271068 | 0.1833 | 1.50696 | 3(Tie) | true |
| simdjson (ondemand) | 986.881 | 0.200628 | 5789.53ms | 466906 | 80 | 6.55545e+07 | 451195 | 0.0565483 | 2.50852 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2271.24 | 0.199776 | 5592.22ms | 466906 | 640 | 9.81746e+07 | 196050 | 0.000184903 | 1.0899 | 1(Win) | true |
| Jsonifier (two-stage) | 2142.78 | 0.783328 | 6052.1ms | 466906 | 160 | 4.23947e+08 | 207803 | 0.0105068 | 1.15523 | 2(Loss) | true |
| Glaze | 2014.22 | 0.25403 | 6126.78ms | 466906 | 80 | 2.52292e+07 | 221066 | 0.32545 | 1.22901 | 3(Loss) | true |
| simdjson (reflection) | 1966.5 | 0.224062 | 6509.67ms | 466906 | 160 | 4.11838e+07 | 226430 | 0.0151366 | 1.25877 | 4(Loss) | true |
| simdjson (ondemand) | 1099.09 | 0.172845 | 5410.42ms | 466906 | 80 | 3.92282e+07 | 405132 | 0.28804 | 2.25242 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12538.1 | 0.241207 | 3657.4ms | 475954 | 640 | 4.88006e+06 | 36202 | 0.012924 | 0.19726 | 1(Win) | true |
| simdjson (reflection) | 9390.69 | 0.357098 | 4837.85ms | 475954 | 80 | 2.38342e+06 | 48335.7 | 0.156444 | 0.263484 | 2(Loss) | true |
| Glaze | 5548.83 | 0.229838 | 8261.94ms | 475954 | 320 | 1.13116e+07 | 81802 | 0.162845 | 0.445982 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12671.1 | 0.267793 | 3610.44ms | 475954 | 320 | 2.94475e+06 | 35822 | 0.460075 | 0.195179 | 1(Win) | true |
| simdjson (reflection) | 9474.98 | 0.192044 | 4798.07ms | 475954 | 320 | 2.70847e+06 | 47905.7 | 0.293819 | 0.261104 | 2(Loss) | true |
| Glaze | 6021.9 | 0.455316 | 7684.53ms | 475954 | 80 | 9.42279e+06 | 75375.8 | 0.0420073 | 0.410975 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2123.88 | 0.107719 | 7232.93ms | 631514 | 320 | 2.98563e+07 | 283565 | 0.0349599 | 1.16554 | 1(Win) | true |
| simdjson (reflection) | 2066.03 | 0.15001 | 7383.64ms | 631514 | 320 | 6.11904e+07 | 291505 | 0.394373 | 1.19819 | 2(Loss) | true |
| Jsonifier | 1732.92 | 0.0829653 | 8768.78ms | 631514 | 640 | 5.32086e+07 | 347540 | 0.0269421 | 1.42854 | 3(Loss) | true |
| Glaze | 1719.12 | 0.302151 | 8860.02ms | 631514 | 80 | 8.96382e+07 | 350331 | 0.404708 | 1.43999 | 4(Loss) | true |
| simdjson (ondemand) | 1261.33 | 0.0552799 | 6067.03ms | 631514 | 640 | 4.45885e+07 | 477479 | 0.313606 | 1.96269 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2676.85 | 0.556778 | 6427.1ms | 631514 | 160 | 2.51075e+08 | 224988 | 0.0113576 | 0.924744 | 1(Win) | true |
| simdjson (reflection) | 2424.11 | 0.108346 | 7017.79ms | 631514 | 640 | 4.6373e+07 | 248445 | 0.118984 | 1.02115 | 2(Loss) | true |
| Glaze | 1983.47 | 0.17943 | 8172.63ms | 631514 | 40 | 1.18731e+07 | 303638 | 0.226226 | 1.24811 | 3(Loss) | true |
| Jsonifier | 1970.33 | 0.082514 | 8471.43ms | 631514 | 1280 | 8.14245e+07 | 305665 | 0.386166 | 1.25641 | 4(Loss) | true |
| simdjson (ondemand) | 1411.62 | 0.112861 | 5776.78ms | 631514 | 320 | 7.41942e+07 | 426643 | 0.212672 | 1.75373 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17676 | 0.195193 | 3952.98ms | 716365 | 1280 | 7.28517e+06 | 38650.1 | 0.0979913 | 0.139947 | 1(Win) | true |
| Glaze | 4175.44 | 0.0732204 | 8448.35ms | 716365 | 1280 | 1.83713e+07 | 163619 | 0.106946 | 0.592815 | 2(Loss) | true |
| simdjson (reflection) | 567.054 | 0.147519 | 7760.17ms | 716365 | 320 | 1.01081e+09 | 1.20479e+06 | 0.907252 | 4.36598 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17726.5 | 0.377511 | 3940.12ms | 716365 | 80 | 1.69345e+06 | 38540 | 0.274285 | 0.139535 | 1(Win) | true |
| Glaze | 4839.05 | 0.0628528 | 7281.26ms | 716365 | 2560 | 2.01575e+07 | 141180 | 0.0335034 | 0.511523 | 2(Loss) | true |
| simdjson (reflection) | 564.448 | 0.218812 | 7595.68ms | 716365 | 320 | 2.24446e+09 | 1.21035e+06 | 0.479294 | 4.38613 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2075.81 | 0.124514 | 125.708ms | 2632 | 80 | 181.352 | 1209.2 | 0.0103363 | 1.16613 | 1(Win) | true |
| simdjson (reflection) | 2069.92 | 0.0296196 | 125.468ms | 2632 | 640 | 82.5659 | 1212.64 | 0.0766077 | 1.17122 | 2(Loss) | true |
| Jsonifier | 2048.02 | 0.0343709 | 126.975ms | 2632 | 320 | 56.7849 | 1225.61 | 0.0270347 | 1.18258 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1700.17 | 0.192028 | 152.15ms | 2632 | 80 | 642.994 | 1476.36 | 0.141195 | 1.42948 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1696.42 | 0.0988823 | 155.004ms | 2632 | 40 | 85.625 | 1479.62 | 0.173728 | 1.43284 | 4(Tie) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2265.13 | 0.162112 | 120.175ms | 2632 | 80 | 258.171 | 1108.14 | 0.156549 | 1.06793 | 1(Win) | true |
| Jsonifier (two-stage) | 2246.29 | 0.188018 | 121.578ms | 2632 | 4890 | 21584.9 | 1117.43 | 0.0415318 | 1.07405 | 2(Loss) | true |
| Jsonifier | 2231.17 | 0.0774212 | 122.44ms | 2632 | 30 | 22.7586 | 1125 | 0.0652277 | 1.08294 | 3(Loss) | true |
| simdjson (ondemand) | 1977.31 | 0.147606 | 134.873ms | 2632 | 160 | 561.757 | 1269.44 | 0.193608 | 1.22703 | 4(Loss) | true |
| Glaze | 1751.12 | 0.0457116 | 144.493ms | 2632 | 80 | 34.3467 | 1433.41 | 0.384299 | 1.38665 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14501 | 0.147696 | 19.8184ms | 2632 | 320 | 20.9154 | 173.097 | 0.091988 | 0.145717 | 1(Win) | true |
| simdjson (reflection) | 9093.22 | 0.114669 | 29.731ms | 2632 | 320 | 32.0613 | 276.038 | 0.205617 | 0.246985 | 2(Loss) | true |
| Glaze | 4575.83 | 0.209887 | 58.1377ms | 2632 | 40 | 53.0231 | 548.55 | 0.0516247 | 0.51609 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16299.3 | 0.124764 | 17.7913ms | 2632 | 640 | 23.626 | 153.998 | 0.135127 | 0.126412 | 1(Win) | true |
| simdjson (reflection) | 10596.3 | 0.470098 | 26.2125ms | 2632 | 4890 | 6063.91 | 236.883 | 0.124078 | 0.208638 | 2(Loss) | true |
| Glaze | 4914 | 0.138998 | 54.5331ms | 2632 | 40 | 20.1641 | 510.8 | 0.287958 | 0.476871 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2608.21 | 0.0818174 | 127.826ms | 3370 | 160 | 162.625 | 1232.22 | 0.0929066 | 0.927973 | 1(Win) | true |
| simdjson (reflection) | 2458.44 | 0.0580102 | 136.333ms | 3370 | 160 | 92.0175 | 1307.29 | 0.0573378 | 0.986638 | 2(Loss) | true |
| simdjson (ondemand) | 2202.01 | 0.196912 | 150.531ms | 3370 | 80 | 660.784 | 1459.53 | 0.0925815 | 1.1043 | 3(Loss) | true |
| Jsonifier | 2190.11 | 0.121999 | 153.624ms | 3370 | 40 | 128.203 | 1467.45 | 0.0420407 | 1.11133 | 4(Loss) | true |
| Glaze | 2124.32 | 0.0992789 | 152.595ms | 3370 | 30 | 67.6793 | 1512.9 | 0.152257 | 1.14463 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2782.81 | 0.087153 | 127.12ms | 3370 | 160 | 162.098 | 1154.91 | 0.156154 | 0.869266 | 1(Win) | true |
| simdjson (reflection) | 2720.98 | 0.0469094 | 129.02ms | 3370 | 80 | 24.5595 | 1181.15 | 0.116548 | 0.889703 | 2(Loss) | true |
| Glaze | 2504.15 | 0.10206 | 129.831ms | 3370 | 80 | 137.26 | 1283.42 | 0.115059 | 0.968884 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2422.37 | 0.350825 | 144.162ms | 3370 | 40 | 866.603 | 1326.75 | 0.134595 | 1.00139 | 4(Tie) | true |
| Jsonifier STATISTICAL TIE | 2418.65 | 0.0620919 | 142.525ms | 3370 | 160 | 108.919 | 1328.79 | 0.0897565 | 1.00398 | 4(Tie) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17493.6 | 0.0730522 | 22.4028ms | 3643 | 1280 | 26.9423 | 198.6 | 0.0779497 | 0.122287 | 1(Win) | true |
| Glaze | 4265.45 | 0.0907657 | 84.696ms | 3682 | 40 | 22.3327 | 823.225 | 0.00101227 | 0.562371 | 2(Loss) | true |
| simdjson (reflection) | 570.101 | 0.069155 | 621.38ms | 3643 | 30 | 532.823 | 6094.07 | 0.0870455 | 4.32357 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20799.9 | 0.0789628 | 19.3718ms | 3643 | 1280 | 22.2664 | 167.031 | 0.367105 | 0.0998482 | 1(Win) | true |
| Glaze | 4740.48 | 0.0457392 | 77.7083ms | 3682 | 30 | 3.44368 | 740.733 | 0.166779 | 0.502761 | 2(Loss) | true |
| simdjson (reflection) | 558.213 | 0.102248 | 624.944ms | 3643 | 4890 | 198032 | 6223.86 | 0.152586 | 4.41601 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 906.086 | 0.153752 | 492.028ms | 4630 | 2560 | 143717 | 4873.17 | 0.125067 | 2.71665 | 1(Win) | true |
| Jsonifier (two-stage) | 830.885 | 0.060247 | 534.84ms | 4630 | 40 | 410.025 | 5314.23 | 0.0368644 | 2.96457 | 2(Loss) | true |
| simdjson (ondemand) | 739.043 | 0.110862 | 628.209ms | 4630 | 30 | 1316.17 | 5974.63 | 0.111458 | 3.33578 | 3(Loss) | true |
| Glaze | 699.52 | 0.0648182 | 638.795ms | 4630 | 80 | 1339.2 | 6312.2 | 0.206316 | 3.52464 | 4(Loss) | true |
| simdjson (reflection) | 687.714 | 0.126359 | 639.309ms | 4630 | 30 | 1974.6 | 6420.57 | 0.317697 | 3.58439 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1097.57 | 0.0497141 | 484.985ms | 4630 | 40 | 160 | 4023 | 0.0910596 | 2.24016 | 1(Win) | true |
| Jsonifier (two-stage) | 1035.93 | 0.0618936 | 506.859ms | 4630 | 30 | 208.792 | 4262.37 | 0.0390866 | 2.37553 | 2(Loss) | true |
| Glaze | 876.694 | 0.0865364 | 592.397ms | 4630 | 40 | 759.844 | 5036.55 | 0.101031 | 2.80875 | 3(Loss) | true |
| simdjson (reflection) | 763.45 | 0.14909 | 673.893ms | 4630 | 30 | 2230.59 | 5783.63 | 0.150199 | 3.22706 | 4(Loss) | true |
| simdjson (ondemand) | 758.778 | 0.171152 | 674.162ms | 4630 | 4890 | 485068 | 5819.24 | 0.219257 | 3.24759 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1844.55 | 0.0284068 | 262.859ms | 4630 | 160 | 73.9858 | 2393.82 | 0.0524514 | 1.32727 | 1(Win) | true |
| Glaze | 1412.26 | 0.260732 | 316.475ms | 4630 | 2560 | 170123 | 3126.56 | 0.166178 | 1.73716 | 2(Loss) | true |
| simdjson (reflection) | 929.211 | 0.233933 | 480.412ms | 4630 | 1280 | 158171 | 4751.9 | 0.461247 | 2.64963 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1928.04 | 0.0439483 | 239.802ms | 4630 | 80 | 81.0405 | 2290.15 | 0.207841 | 1.26992 | 1(Win) | true |
| Glaze | 1509.26 | 0.0629868 | 299.2ms | 4630 | 80 | 271.658 | 2925.61 | 0.333088 | 1.62514 | 2(Loss) | true |
| simdjson (reflection) | 967.238 | 0.0175276 | 471.907ms | 4630 | 40 | 25.6096 | 4565.07 | 0.015149 | 2.54407 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1873.04 | 0.0691294 | 582.747ms | 11579 | 40 | 664.408 | 5895.55 | 0.0132886 | 1.31543 | 1(Win) | true |
| Jsonifier | 1789.18 | 0.409658 | 606.923ms | 11579 | 640 | 409124 | 6171.86 | 0.0939372 | 1.37765 | 2(Loss) | true |
| simdjson (reflection) | 1648.71 | 0.114541 | 681.302ms | 11579 | 30 | 1765.6 | 6697.7 | 0.095148 | 1.49531 | 3(Loss) | true |
| simdjson (ondemand) | 1618.15 | 0.0860828 | 686.296ms | 11579 | 40 | 1380.38 | 6824.23 | 0.025284 | 1.5238 | 4(Loss) | true |
| Glaze | 1553.08 | 0.115472 | 724.874ms | 11579 | 4890 | 329620 | 7110.11 | 0.0215429 | 1.58826 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2189.89 | 0.0405427 | 586.398ms | 11579 | 40 | 167.179 | 5042.52 | 0.344097 | 1.12429 | 1(Win) | true |
| Jsonifier | 2005.24 | 0.127308 | 622.73ms | 11579 | 4890 | 240342 | 5506.88 | 0.0716188 | 1.22834 | 2(Loss) | true |
| Glaze | 1784.66 | 0.0513993 | 712.858ms | 11579 | 80 | 809.164 | 6187.51 | 0.36069 | 1.38167 | 3(Loss) | true |
| simdjson (reflection) | 1772.8 | 0.118557 | 715.006ms | 11579 | 40 | 2181.43 | 6228.9 | 0.0422939 | 1.39054 | 4(Loss) | true |
| simdjson (ondemand) | 1736.63 | 0.144747 | 727.879ms | 11579 | 2560 | 216865 | 6358.64 | 0.0567402 | 1.41948 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5669.37 | 0.468523 | 251.352ms | 14795 | 640 | 87016.6 | 2488.74 | 0.0555945 | 0.431915 | 1(Win) | true |
| Glaze | 3294.19 | 0.0844649 | 458.084ms | 14795 | 40 | 523.533 | 4283.18 | 0.0251045 | 0.746953 | 2(Loss) | true |
| simdjson (reflection) | 403.043 | 0.0898402 | 3529.66ms | 14795 | 2560 | 2.53226e+06 | 35007.7 | 0.598992 | 6.13809 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5846.21 | 0.196504 | 244.414ms | 14795 | 4890 | 109985 | 2413.46 | 0.025564 | 0.418793 | 1(Win) | true |
| Glaze | 3609.15 | 0.0442631 | 398.47ms | 14795 | 160 | 479.097 | 3909.4 | 0.00863229 | 0.681229 | 2(Loss) | true |
| simdjson (reflection) | 427.221 | 0.103927 | 3412.61ms | 14795 | 1280 | 1.50798e+06 | 33026.5 | 0.115843 | 5.79073 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.32 | 0.0710921 | 190.027ms | 3223 | 80 | 141.107 | 1868.14 | 0.244825 | 1.48231 | 1(Win) | true |
| Jsonifier (two-stage) | 1542.17 | 0.0744112 | 205.51ms | 3223 | 80 | 175.965 | 1993.1 | 0.182797 | 1.58402 | 2(Loss) | true |
| Glaze | 1438.04 | 0.228743 | 217.998ms | 3223 | 4890 | 116892 | 2137.42 | 0.114588 | 1.70088 | 3(Loss) | true |
| simdjson (ondemand) | 1250.11 | 0.0826858 | 242.362ms | 3223 | 30 | 123.995 | 2458.73 | 0.252877 | 1.95731 | 4(Loss) | true |
| simdjson (reflection) | 1198.57 | 0.299084 | 259.276ms | 3223 | 1280 | 75299.1 | 2564.47 | 0.293071 | 2.04208 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1873.12 | 0.0841406 | 181.283ms | 3223 | 40 | 76.2538 | 1640.95 | 0.153132 | 1.29936 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.53 | 0.109768 | 196.922ms | 3223 | 80 | 301.646 | 1769 | 0.0792034 | 1.40343 | 2(Loss) | true |
| Glaze | 1519.07 | 0.216661 | 220.18ms | 3223 | 4890 | 93980.1 | 2023.41 | 0.104473 | 1.60676 | 3(Loss) | true |
| simdjson (ondemand) | 1508.17 | 0.072342 | 232.78ms | 3223 | 40 | 86.9481 | 2038.03 | 0.0657884 | 1.61965 | 4(Loss) | true |
| simdjson (reflection) | 1355.44 | 0.104728 | 252.092ms | 3223 | 80 | 451.209 | 2267.68 | 0.252922 | 1.80327 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7578.55 | 0.109131 | 43.4888ms | 3223 | 320 | 62.6898 | 405.578 | 0.451777 | 0.303474 | 1(Win) | true |
| simdjson (reflection) | 6462.77 | 0.0933167 | 51.1516ms | 3223 | 320 | 63.0307 | 475.6 | 0.181022 | 0.361462 | 2(Loss) | true |
| Glaze | 2594.27 | 0.241638 | 118.56ms | 3223 | 30 | 245.89 | 1184.8 | 0.0225023 | 0.931451 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9094.18 | 0.123706 | 35.4881ms | 3223 | 320 | 55.9402 | 337.984 | 0.0434373 | 0.249927 | 1(Win) | true |
| simdjson (reflection) | 7097.69 | 0.0474209 | 46.0004ms | 3223 | 1280 | 53.9805 | 433.055 | 0.0276095 | 0.326588 | 2(Loss) | true |
| Glaze | 2892.52 | 0.0609908 | 107.575ms | 3223 | 320 | 134.414 | 1062.63 | 0.0626784 | 0.83366 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2521.31 | 0.0423148 | 252.953ms | 5839 | 160 | 139.743 | 2208.57 | 0.0175422 | 0.969596 | 1(Win) | true |
| simdjson (ondemand) | 2301.27 | 0.261213 | 253.131ms | 5839 | 2560 | 102276 | 2419.76 | 0.110913 | 1.06408 | 2(Loss) | true |
| simdjson (reflection) | 2235.09 | 0.144048 | 252.467ms | 5839 | 30 | 386.386 | 2491.4 | 0.135314 | 1.09595 | 3(Loss) | true |
| Jsonifier | 1908.86 | 0.217625 | 297.894ms | 5839 | 4890 | 197086 | 2917.2 | 0.524651 | 1.28406 | 4(Loss) | true |
| Glaze | 1845.79 | 0.377236 | 309.379ms | 5839 | 1280 | 165786 | 3016.86 | 0.0780934 | 1.32938 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2873.94 | 0.241908 | 213.979ms | 5839 | 2560 | 56242.3 | 1937.59 | 0.0227358 | 0.849175 | 1(Win) | true |
| simdjson (ondemand) | 2576.4 | 0.289691 | 235.153ms | 5839 | 2560 | 100360 | 2161.35 | 0.30781 | 0.948878 | 2(Loss) | true |
| simdjson (reflection) | 2468.08 | 0.0796116 | 248.923ms | 5839 | 160 | 516.215 | 2256.21 | 0.0124641 | 0.991234 | 3(Loss) | true |
| Jsonifier | 2117.22 | 0.141929 | 280.676ms | 5839 | 40 | 557.374 | 2630.1 | 0.838371 | 1.15683 | 4(Loss) | true |
| Glaze | 1921.94 | 0.0919642 | 298.044ms | 5839 | 30 | 212.989 | 2897.33 | 0.310812 | 1.27543 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14253.2 | 0.124277 | 49.8088ms | 6938 | 160 | 53.2537 | 464.219 | 0.0471 | 0.163372 | 1(Win) | true |
| Glaze | 3714.99 | 0.198456 | 194.607ms | 6960 | 30 | 377.183 | 1786.7 | 0.0765497 | 0.655599 | 2(Loss) | true |
| simdjson (reflection) | 535.158 | 0.103224 | 1318.25ms | 6938 | 30 | 4886.37 | 12363.8 | 0.148332 | 4.61612 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16298 | 0.151502 | 42.9066ms | 6938 | 160 | 60.5277 | 405.975 | 0.339842 | 0.141552 | 1(Win) | true |
| Glaze | 4316.35 | 0.10435 | 158.167ms | 6960 | 40 | 102.999 | 1537.78 | 0.0113814 | 0.562859 | 2(Loss) | true |
| simdjson (reflection) | 538.394 | 0.168022 | 1245.75ms | 6938 | 2560 | 1.09154e+06 | 12289.5 | 0.13979 | 4.58857 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1730.79 | 0.0932856 | 290.531ms | 4857 | 40 | 249.307 | 2676.22 | 0.0333292 | 1.41719 | 1(Win) | true |
| simdjson (reflection) | 1677.19 | 0.0967647 | 281.661ms | 4857 | 30 | 214.254 | 2761.77 | 0.109713 | 1.46245 | 2(Loss) | true |
| Glaze | 1588.82 | 0.0436604 | 294.088ms | 4857 | 160 | 259.23 | 2915.38 | 0.116059 | 1.54319 | 3(Loss) | true |
| Jsonifier (two-stage) | 1508.66 | 0.191706 | 337.788ms | 4857 | 30 | 1039.31 | 3070.27 | 0.327862 | 1.62768 | 4(Loss) | true |
| simdjson (ondemand) | 1282.34 | 0.189439 | 361.427ms | 4857 | 4890 | 228969 | 3612.14 | 0.0247856 | 1.91624 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2009.43 | 0.125641 | 265.538ms | 4857 | 30 | 251.637 | 2305.13 | 0.192695 | 1.21762 | 1(Win) | true |
| Glaze | 1984.74 | 0.134206 | 253.45ms | 4857 | 30 | 294.303 | 2333.8 | 0.0142849 | 1.23228 | 2(Loss) | true |
| Jsonifier (two-stage) | 1803.33 | 0.0414027 | 288.753ms | 4857 | 320 | 361.905 | 2568.58 | 0.293921 | 1.35904 | 3(Loss) | true |
| simdjson (reflection) | 1721.46 | 0.171002 | 293.018ms | 4857 | 4890 | 103527 | 2690.73 | 0.191175 | 1.42245 | 4(Loss) | true |
| simdjson (ondemand) | 1634.44 | 0.0773124 | 312.802ms | 4857 | 80 | 384.051 | 2834 | 0.212146 | 1.50099 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10447.6 | 0.0505487 | 47.0453ms | 4857 | 1280 | 64.2883 | 443.354 | 0.0903159 | 0.222042 | 1(Win) | true |
| simdjson (reflection) | 7623.12 | 0.215282 | 63.3926ms | 4857 | 40 | 68.4455 | 607.625 | 0.26945 | 0.310058 | 2(Loss) | true |
| Glaze | 3406.21 | 0.316513 | 138.39ms | 4857 | 4890 | 90591.2 | 1359.87 | 0.297065 | 0.710629 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12081.9 | 0.0789227 | 40.5151ms | 4857 | 640 | 58.5934 | 383.383 | 0.25002 | 0.189973 | 1(Win) | true |
| simdjson (reflection) | 9307.71 | 0.0545037 | 63.2594ms | 4857 | 640 | 47.085 | 497.652 | 0.0505244 | 0.250746 | 2(Loss) | true |
| Glaze | 3895.26 | 0.211836 | 121.863ms | 4857 | 80 | 507.639 | 1189.14 | 0.220181 | 0.620218 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2019.46 | 0.0606162 | 314.978ms | 6701 | 40 | 147.179 | 3164.5 | 0.00631971 | 1.21454 | 1(Win) | true |
| Jsonifier (two-stage) | 1999.55 | 0.0945667 | 350.353ms | 6701 | 40 | 365.385 | 3196 | 0.0573305 | 1.22782 | 2(Loss) | true |
| Glaze | 1937.52 | 0.0421506 | 340.613ms | 6701 | 160 | 309.254 | 3298.33 | 0.0992015 | 1.26737 | 3(Loss) | true |
| Jsonifier | 1758.09 | 0.0592305 | 371.873ms | 6701 | 80 | 370.833 | 3634.95 | 0.0618608 | 1.39776 | 4(Loss) | true |
| simdjson (ondemand) | 1722.62 | 0.0833045 | 372.25ms | 6701 | 80 | 764.061 | 3709.8 | 0.39669 | 1.42677 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2494.27 | 0.0826876 | 288.058ms | 6701 | 40 | 179.528 | 2562.1 | 0.0247254 | 0.981921 | 1(Win) | true |
| Glaze | 2442.94 | 0.116713 | 288.652ms | 6701 | 30 | 279.651 | 2615.93 | 0.0624769 | 1.00297 | 2(Loss) | true |
| Jsonifier (two-stage) | 2338.22 | 0.071834 | 301.632ms | 6701 | 80 | 308.359 | 2733.09 | 0.155716 | 1.04866 | 3(Loss) | true |
| Jsonifier | 2020.11 | 0.0604289 | 349.951ms | 6701 | 80 | 292.354 | 3163.47 | 0.184473 | 1.21521 | 4(Loss) | true |
| simdjson (ondemand) | 1958.11 | 0.0953004 | 342.789ms | 6701 | 40 | 386.951 | 3263.65 | 0.128016 | 1.25353 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14357.7 | 0.0833104 | 51.3574ms | 7376 | 160 | 26.6556 | 489.931 | 0.0932121 | 0.162314 | 1(Win) | true |
| Glaze | 3907.8 | 0.225304 | 186.865ms | 7376 | 30 | 493.444 | 1800.07 | 0 | 0.624259 | 2(Loss) | true |
| simdjson (reflection) | 523.9 | 0.137594 | 1393.63ms | 7376 | 1280 | 436874 | 13426.8 | 0.695829 | 4.71612 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17395.6 | 0.0583751 | 42.8753ms | 7376 | 640 | 35.6616 | 404.373 | 0.0405556 | 0.132803 | 1(Win) | true |
| Glaze | 4360.43 | 0.0553031 | 167.313ms | 7376 | 160 | 127.351 | 1613.21 | 0.191023 | 0.558011 | 2(Loss) | true |
| simdjson (reflection) | 521.566 | 0.172369 | 1376.64ms | 7376 | 1280 | 691753 | 13486.9 | 0.0574418 | 4.73757 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1839.73 | 0.0759461 | 92.7837ms | 1691 | 640 | 283.641 | 876.575 | 0.232609 | 1.30116 | 1(Win) | true |
| simdjson (reflection) | 1769.63 | 0.165806 | 94.1714ms | 1691 | 30 | 68.4931 | 911.3 | 0.222628 | 1.35407 | 2(Loss) | true |
| Jsonifier (two-stage) | 1589.04 | 0.191541 | 104.885ms | 1691 | 30 | 113.361 | 1014.87 | 0.131208 | 1.51549 | 3(Loss) | true |
| Glaze | 1521.68 | 0.0258851 | 118.97ms | 1691 | 640 | 48.1636 | 1059.79 | 0.113543 | 1.58473 | 4(Loss) | true |
| simdjson (ondemand) | 1409.39 | 0.102144 | 127.465ms | 1691 | 320 | 437.125 | 1144.23 | 0.364632 | 1.71732 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2292.97 | 0.0505243 | 79.1628ms | 1691 | 640 | 80.8112 | 703.308 | 0.152837 | 1.03937 | 1(Win) | true |
| Jsonifier | 2240.35 | 0.217613 | 81.1909ms | 1691 | 40 | 98.1481 | 719.825 | 0.059077 | 1.05934 | 2(Loss) | true |
| simdjson (reflection) | 2037.3 | 0.0664731 | 88.8859ms | 1691 | 640 | 177.194 | 791.569 | 0.441734 | 1.17023 | 3(Loss) | true |
| Glaze | 1679.99 | 0.121177 | 102.658ms | 1691 | 40 | 54.1224 | 959.925 | 0.0182273 | 1.43028 | 4(Loss) | true |
| simdjson (ondemand) | 1457.42 | 0.176169 | 119.003ms | 1691 | 160 | 607.987 | 1106.52 | 0.236092 | 1.65496 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13095.1 | 0.0985191 | 17.2224ms | 1996 | 1280 | 26.2516 | 145.363 | 0.393883 | 0.151564 | 1(Win) | true |
| simdjson (reflection) | 9412.22 | 0.0546007 | 23.1632ms | 1996 | 4890 | 59.6269 | 202.241 | 0.205774 | 0.225617 | 2(Loss) | true |
| Glaze | 5458.65 | 0.179631 | 38.5181ms | 1996 | 160 | 62.782 | 348.719 | 0.0663582 | 0.416082 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14414.4 | 0.0734141 | 15.994ms | 1996 | 2560 | 24.0619 | 132.058 | 0.173332 | 0.133194 | 1(Win) | true |
| simdjson (reflection) | 11953.1 | 0.312964 | 18.464ms | 1996 | 40 | 9.9359 | 159.25 | 0.031407 | 0.168687 | 2(Loss) | true |
| Glaze | 6038.5 | 0.0719778 | 34.4898ms | 1996 | 640 | 32.9488 | 315.233 | 0.0133848 | 0.372008 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2310.43 | 0.272197 | 92.0741ms | 2158 | 4890 | 28747 | 890.755 | 0.00897377 | 1.03787 | 1(Win) | true |
| Jsonifier (two-stage) | 2097.49 | 0.108723 | 101.823ms | 2158 | 80 | 91.0403 | 981.188 | 0.0827393 | 1.14651 | 2(Loss) | true |
| Glaze | 1966.2 | 0.0588812 | 108.779ms | 2158 | 160 | 60.7748 | 1046.71 | 0.307756 | 1.22482 | 3(Loss) | true |
| simdjson (ondemand) | 1630.86 | 0.302836 | 129.039ms | 2158 | 40 | 584.174 | 1261.92 | 0.0508224 | 1.48372 | 4(Loss) | true |
| Jsonifier | 1590.59 | 0.0560954 | 134.709ms | 2158 | 320 | 168.574 | 1293.88 | 0.499536 | 1.52259 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2757.41 | 0.104437 | 83.1562ms | 2158 | 160 | 97.2137 | 746.362 | 0.0502185 | 0.863169 | 1(Win) | true |
| simdjson (reflection) | 2446.54 | 0.269313 | 95.8191ms | 2158 | 40 | 205.292 | 841.2 | 0.284495 | 0.976193 | 2(Loss) | true |
| Glaze | 2395.93 | 0.0591393 | 95.52ms | 2158 | 160 | 41.2883 | 858.969 | 0.491623 | 0.999838 | 3(Loss) | true |
| Jsonifier | 1947.85 | 0.213509 | 123.563ms | 2158 | 30 | 152.668 | 1056.57 | 1.09832 | 1.2377 | 4(Loss) | true |
| simdjson (ondemand) | 1873.2 | 0.188366 | 119.523ms | 2158 | 160 | 685.267 | 1098.67 | 0.269485 | 1.2886 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16285.6 | 0.0865507 | 19.593ms | 2866 | 1280 | 27.0082 | 167.831 | 0.205239 | 0.127506 | 1(Win) | true |
| Glaze | 2857.42 | 0.0985788 | 70.5639ms | 2866 | 160 | 142.263 | 956.538 | 0.0117626 | 0.840658 | 2(Loss) | true |
| simdjson (reflection) | 569.702 | 0.16452 | 488.276ms | 2866 | 4890 | 304653 | 4797.65 | 0.0104228 | 4.32016 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19836.5 | 0.115589 | 16.2903ms | 2866 | 1280 | 32.4688 | 137.788 | 0.0130425 | 0.100621 | 1(Win) | true |
| Glaze | 5268.37 | 0.193945 | 54.8351ms | 2866 | 30 | 30.3724 | 518.8 | 0.320225 | 0.444208 | 2(Loss) | true |
| simdjson (reflection) | 555.608 | 0.096798 | 484.416ms | 2866 | 40 | 907.003 | 4919.35 | 0.181604 | 4.43112 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2060.96 | 0.107853 | 213.375ms | 4390 | 80 | 384.015 | 2031.4 | 0.178767 | 1.1859 | 1(Win) | true |
| Glaze | 1745.47 | 0.16339 | 247.579ms | 4390 | 40 | 614.353 | 2398.57 | 0.0977228 | 1.40318 | 2(Loss) | true |
| Jsonifier (two-stage) | 1563.2 | 0.095369 | 267.592ms | 4390 | 40 | 260.962 | 2678.25 | 0.246413 | 1.56782 | 3(Loss) | true |
| simdjson (reflection) | 1406.36 | 0.205106 | 299.711ms | 4390 | 2560 | 95440 | 2976.92 | 0.048653 | 1.74426 | 4(Loss) | true |
| simdjson (ondemand) | 1201.26 | 0.0799531 | 385.78ms | 4390 | 80 | 621.182 | 3485.21 | 0.136116 | 2.04526 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2089.87 | 0.105936 | 220.372ms | 4390 | 30 | 135.114 | 2003.3 | 0.084788 | 1.1687 | 1(Win) | true |
| Glaze | 1817.3 | 0.255894 | 243.509ms | 4390 | 30 | 1042.6 | 2303.77 | 0.12749 | 1.34657 | 2(Loss) | true |
| Jsonifier (two-stage) | 1710.03 | 0.0665663 | 264.071ms | 4390 | 80 | 212.48 | 2448.28 | 0.395715 | 1.43198 | 3(Loss) | true |
| simdjson (reflection) | 1518.46 | 0.143995 | 294.19ms | 4390 | 40 | 630.49 | 2757.15 | 0.00302254 | 1.61478 | 4(Loss) | true |
| simdjson (ondemand) | 1272.94 | 0.152052 | 347.044ms | 4390 | 30 | 750.271 | 3288.93 | 0.0415362 | 1.92836 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13694.4 | 0.0464117 | 33.1437ms | 4390 | 1280 | 25.7695 | 305.718 | 0.059066 | 0.164722 | 1(Win) | true |
| simdjson (reflection) | 10900.4 | 0.0495952 | 41.3754ms | 4390 | 640 | 23.2221 | 384.08 | 0.197696 | 0.211318 | 2(Loss) | true |
| Glaze | 3639.12 | 0.0902412 | 118.919ms | 4390 | 80 | 86.2253 | 1150.45 | 0.132733 | 0.664243 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15150.9 | 0.110402 | 30.8605ms | 4390 | 320 | 29.7823 | 276.328 | 0.0531242 | 0.148124 | 1(Win) | true |
| simdjson (reflection) | 11056.7 | 0.18471 | 40.3443ms | 4390 | 40 | 19.5667 | 378.65 | 0.0132066 | 0.207728 | 2(Loss) | true |
| Glaze | 3828.59 | 0.0707051 | 111.057ms | 4390 | 160 | 95.6474 | 1093.52 | 0.000571546 | 0.630256 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3004.5 | 0.0836049 | 311.714ms | 9378 | 40 | 247.743 | 2976.72 | 0.000279949 | 0.816277 | 1(Win) | true |
| Jsonifier | 2912.17 | 0.0894309 | 312.772ms | 9378 | 40 | 301.733 | 3071.1 | 0.321218 | 0.842602 | 2(Loss) | true |
| simdjson (reflection) | 2787.21 | 0.0586453 | 319.039ms | 9378 | 160 | 566.587 | 3208.78 | 0.303514 | 0.881038 | 3(Loss) | true |
| Glaze | 2591.96 | 0.101053 | 367.159ms | 9378 | 30 | 364.741 | 3450.5 | 0.671688 | 0.947978 | 4(Loss) | true |
| simdjson (ondemand) | 2385.49 | 0.149055 | 379.088ms | 9378 | 40 | 1249.16 | 3749.15 | 0.0111124 | 1.03052 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3228.28 | 0.10011 | 293.663ms | 9378 | 40 | 307.676 | 2770.38 | 0.0393895 | 0.75909 | 1(Win) | true |
| Jsonifier | 3139.47 | 0.0667541 | 308.711ms | 9378 | 80 | 289.304 | 2848.75 | 0.0894329 | 0.781191 | 2(Loss) | true |
| simdjson (reflection) | 3043.42 | 0.140441 | 331.462ms | 9378 | 40 | 681.31 | 2938.65 | 0.372871 | 0.806142 | 3(Loss) | true |
| Glaze | 2789.2 | 0.0792466 | 342.949ms | 9378 | 30 | 193.707 | 3206.5 | 0.0841331 | 0.8806 | 4(Loss) | true |
| simdjson (ondemand) | 2488.27 | 0.0592797 | 372.354ms | 9378 | 160 | 726.367 | 3594.28 | 0.277422 | 0.987569 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 31984.2 | 0.082293 | 37.5281ms | 11521 | 320 | 25.5732 | 343.522 | 0.0974322 | 0.0717236 | 1(Win) | true |
| Glaze | 5747.31 | 0.0889667 | 195.622ms | 11521 | 80 | 231.417 | 1911.72 | 0.0731787 | 0.42499 | 2(Loss) | true |
| simdjson (reflection) | 584.153 | 0.437565 | 2015.97ms | 11521 | 160 | 1.08376e+06 | 18808.9 | 0.00714371 | 4.23234 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 34071.7 | 0.137798 | 34.9495ms | 11521 | 80 | 15.7968 | 322.475 | 0.0698216 | 0.0668453 | 1(Win) | true |
| Glaze | 6335.19 | 0.0520672 | 177.334ms | 11521 | 80 | 65.2348 | 1734.33 | 0.0302803 | 0.384877 | 2(Loss) | true |
| simdjson (reflection) | 569.116 | 0.0591809 | 2010.67ms | 11521 | 30 | 3916.19 | 19305.9 | 0.556626 | 4.3446 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3258.01 | 0.0512565 | 139.419ms | 4669 | 320 | 157.033 | 1366.7 | 0.0185175 | 0.744756 | 1(Win) | true |
| Jsonifier (two-stage) | 2422.39 | 0.0407869 | 188.71ms | 4669 | 320 | 179.866 | 1838.14 | 0.0424841 | 1.00756 | 2(Loss) | true |
| Glaze | 1658.21 | 0.0501803 | 271.214ms | 4669 | 80 | 145.253 | 2685.25 | 0.0558919 | 1.47763 | 3(Loss) | true |
| simdjson (reflection) | 1487.55 | 0.0669967 | 303.824ms | 4669 | 80 | 321.737 | 2993.31 | 0.0897029 | 1.64969 | 4(Loss) | true |
| simdjson (ondemand) | 993.351 | 0.159545 | 459.104ms | 4669 | 2560 | 130933 | 4482.51 | 0.245958 | 2.4779 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3778.28 | 0.0944321 | 124.938ms | 4669 | 30 | 37.1552 | 1178.5 | 0.0480606 | 0.640366 | 1(Win) | true |
| Jsonifier (two-stage) | 2638.68 | 0.0688054 | 175.829ms | 4669 | 80 | 107.847 | 1687.47 | 0.255645 | 0.923809 | 2(Loss) | true |
| Glaze | 1757.47 | 0.0368118 | 257.038ms | 4669 | 160 | 139.176 | 2533.58 | 0.0510902 | 1.39364 | 3(Loss) | true |
| simdjson (reflection) | 1536.65 | 0.100149 | 300.398ms | 4669 | 30 | 252.644 | 2897.67 | 0.077133 | 1.59577 | 4(Loss) | true |
| simdjson (ondemand) | 1027.13 | 0.162085 | 439.882ms | 4669 | 4890 | 241428 | 4335.09 | 0.277132 | 2.39529 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15438 | 0.164561 | 31.033ms | 4669 | 160 | 36.0447 | 288.425 | 0.173656 | 0.145524 | 1(Win) | true |
| simdjson (reflection) | 9049.93 | 0.0683808 | 51.9902ms | 4669 | 320 | 36.2223 | 492.016 | 0.185751 | 0.259133 | 2(Loss) | true |
| Glaze | 1980.16 | 0.111591 | 228.942ms | 4669 | 160 | 1007.46 | 2248.66 | 0.0962609 | 1.23565 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19684 | 0.120484 | 25.0843ms | 4669 | 640 | 47.5398 | 226.209 | 0.166878 | 0.111371 | 1(Win) | true |
| simdjson (reflection) | 9576.74 | 0.114512 | 49.3831ms | 4669 | 160 | 45.356 | 464.95 | 0.0215031 | 0.243848 | 2(Loss) | true |
| Glaze | 2196.95 | 0.141756 | 210.506ms | 4669 | 80 | 660.361 | 2026.76 | 0.120411 | 1.11244 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3689.89 | 0.0833692 | 205.513ms | 7932 | 80 | 233.691 | 2050.07 | 0.0609362 | 0.662075 | 1(Win) | true |
| Jsonifier | 2695.2 | 0.0710916 | 291.047ms | 7932 | 80 | 318.501 | 2806.68 | 0.160963 | 0.910562 | 2(Loss) | true |
| simdjson (reflection) | 2333.78 | 0.0865128 | 324.299ms | 7932 | 40 | 314.533 | 3241.32 | 0.0882619 | 1.0521 | 3(Loss) | true |
| Glaze | 2002.08 | 0.0806207 | 375.311ms | 7932 | 40 | 371.156 | 3778.35 | 0.214397 | 1.22715 | 4(Loss) | true |
| simdjson (ondemand) | 1607.02 | 0.201823 | 479.204ms | 7932 | 1280 | 115525 | 4707.2 | 0.109917 | 1.53236 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4101.65 | 0.393988 | 196.861ms | 7932 | 1280 | 67580.9 | 1844.27 | 0.131062 | 0.595147 | 1(Win) | true |
| Jsonifier | 2708.49 | 0.111724 | 285.01ms | 7932 | 30 | 292.093 | 2792.9 | 0.0489576 | 0.905539 | 2(Loss) | true |
| simdjson (reflection) | 2284.46 | 0.0829984 | 324.535ms | 7932 | 80 | 604.268 | 3311.31 | 0.0252985 | 1.0746 | 3(Loss) | true |
| Glaze | 2171.1 | 0.104107 | 352.132ms | 7932 | 30 | 394.717 | 3484.2 | 0.389765 | 1.13118 | 4(Loss) | true |
| simdjson (ondemand) | 1696.59 | 0.0883903 | 442.838ms | 7932 | 160 | 2485.08 | 4458.67 | 0.496859 | 1.4504 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22463.7 | 0.0614763 | 41.7436ms | 9249 | 640 | 37.2927 | 392.658 | 0.0394105 | 0.102624 | 1(Win) | true |
| Glaze | 3345.7 | 0.266841 | 267.229ms | 9249 | 2560 | 126695 | 2636.38 | 0.0857893 | 0.732497 | 2(Loss) | true |
| simdjson (reflection) | 516.925 | 0.0858658 | 1741.87ms | 9249 | 4890 | 1.04974e+06 | 17063.5 | 0.211298 | 4.78179 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27698.6 | 0.115882 | 34.5746ms | 9249 | 320 | 43.5771 | 318.447 | 0.09118 | 0.0818001 | 1(Win) | true |
| Glaze | 3563.24 | 0.104664 | 249.403ms | 9249 | 40 | 268.507 | 2475.43 | 0.0380261 | 0.687374 | 2(Loss) | true |
| simdjson (reflection) | 521.63 | 0.176775 | 1706.17ms | 9249 | 40 | 35741.1 | 16909.5 | 0.32027 | 4.73917 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 873.856 | 0.129076 | 522.883ms | 4604 | 30 | 1261.84 | 5024.53 | 0.0663852 | 2.81777 | 1(Win) | true |
| Jsonifier (two-stage) | 770.361 | 0.115025 | 576.639ms | 4604 | 4890 | 210172 | 5699.56 | 0.0841601 | 3.19881 | 2(Loss) | true |
| Glaze | 704.93 | 0.364949 | 656.306ms | 4604 | 320 | 165345 | 6228.58 | 0.324509 | 3.49748 | 3(Loss) | true |
| simdjson (reflection) | 664.67 | 0.096381 | 660.79ms | 4604 | 4890 | 198221 | 6605.85 | 0.148344 | 3.71017 | 4(Loss) | true |
| simdjson (ondemand) | 565.905 | 0.117208 | 781.317ms | 4604 | 2560 | 211707 | 7758.75 | 0.0622669 | 4.36048 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1012.17 | 0.783595 | 518.411ms | 4604 | 160 | 184872 | 4337.94 | 0.287829 | 2.4307 | 1(Win) | true |
| Jsonifier (two-stage) | 900.229 | 0.0982716 | 559.629ms | 4604 | 30 | 689.195 | 4877.33 | 0.35752 | 2.73401 | 2(Loss) | true |
| Glaze | 782.973 | 0.0766035 | 642.386ms | 4604 | 80 | 1476.27 | 5607.75 | 0.0374622 | 3.14685 | 3(Loss) | true |
| simdjson (reflection) | 701.555 | 0.130684 | 710.087ms | 4604 | 4890 | 327116 | 6258.55 | 0.0348185 | 3.51393 | 4(Loss) | true |
| simdjson (ondemand) | 585.792 | 0.149237 | 840.947ms | 4604 | 4890 | 611850 | 7495.35 | 0.27499 | 4.21184 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1499.37 | 0.0795314 | 302.763ms | 4604 | 30 | 162.723 | 2928.37 | 0.169318 | 1.63542 | 1(Win) | true |
| simdjson (reflection) | 1292.93 | 0.0260639 | 358.611ms | 4918 | 80 | 71.515 | 3627.56 | 0.162036 | 1.90081 | 2(Loss) | true |
| Glaze | 1032.2 | 0.112879 | 444.662ms | 4604 | 30 | 691.651 | 4253.73 | 0.379929 | 2.38331 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1525.81 | 0.0842445 | 287.314ms | 4604 | 30 | 176.309 | 2877.63 | 0.149652 | 1.60829 | 1(Win) | true |
| simdjson (reflection) | 1324.41 | 0.0321345 | 396.929ms | 4918 | 30 | 38.8506 | 3541.33 | 0.139113 | 1.85474 | 2(Loss) | true |
| Glaze | 1076.98 | 0.0599359 | 417.079ms | 4604 | 40 | 238.83 | 4076.88 | 0.124638 | 2.28234 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2629.25 | 0.143392 | 652.144ms | 18245 | 2560 | 230522 | 6617.78 | 0.415689 | 0.937803 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 2317.53 | 0.0976302 | 763.529ms | 18245 | 4890 | 262732 | 7507.89 | 0.0890018 | 1.06462 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2314.03 | 0.244713 | 767.886ms | 18245 | 640 | 216693 | 7519.25 | 0.208838 | 1.06624 | 2(Tie) | true |
| simdjson (ondemand) | 1990.06 | 0.123743 | 876.213ms | 18245 | 30 | 3511.68 | 8743.33 | 0.210384 | 1.24012 | 4(Loss) | true |
| Glaze | 1919.13 | 0.0451924 | 916.723ms | 18245 | 40 | 671.538 | 9066.5 | 0.00845532 | 1.28628 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3133.63 | 0.0799681 | 640.496ms | 18245 | 30 | 591.49 | 5552.6 | 0.0743842 | 0.786477 | 1(Win) | true |
| Jsonifier | 2687.27 | 0.0940643 | 736.324ms | 18245 | 30 | 1112.85 | 6474.9 | 0.0406864 | 0.917488 | 2(Loss) | true |
| simdjson (reflection) | 2562.69 | 0.208413 | 767.041ms | 18245 | 2560 | 512606 | 6789.65 | 0.0304324 | 0.962384 | 3(Loss) | true |
| simdjson (ondemand) | 2089.8 | 0.246367 | 922.274ms | 18245 | 1280 | 538583 | 8326.04 | 0.220964 | 1.18103 | 4(Loss) | true |
| Glaze | 2049.09 | 0.0521726 | 904.299ms | 18245 | 40 | 785.076 | 8491.48 | 0.081094 | 1.2043 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7656.33 | 0.0608492 | 313.272ms | 24579 | 30 | 104.116 | 3061.57 | 0.0881124 | 0.320686 | 1(Win) | true |
| Glaze | 3794.45 | 0.135462 | 621.46ms | 24579 | 2560 | 179270 | 6177.54 | 0.0910044 | 0.649685 | 2(Loss) | true |
| simdjson (reflection) | 534.354 | 0.454647 | 4365.59ms | 24893 | 80 | 3.26389e+06 | 44427.2 | 0.765543 | 4.63046 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7703.55 | 0.0544506 | 308.809ms | 24579 | 80 | 219.605 | 3042.8 | 0.230582 | 0.318593 | 1(Win) | true |
| Glaze | 4160.28 | 0.235578 | 572.445ms | 24579 | 1280 | 225508 | 5634.33 | 0.126228 | 0.592394 | 2(Loss) | true |
| simdjson (reflection) | 551.982 | 0.0723688 | 4279.79ms | 24893 | 4890 | 4.73714e+06 | 43008.3 | 0.0877048 | 4.48266 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 970.159 | 0.0436835 | 457.792ms | 4604 | 160 | 625.374 | 4525.77 | 0.0354786 | 2.53686 | 1(Win) | true |
| Jsonifier (two-stage) | 828.592 | 0.299651 | 533.75ms | 4604 | 1280 | 322724 | 5299.01 | 0.25664 | 2.97326 | 2(Loss) | true |
| Glaze | 698.146 | 0.107713 | 630.739ms | 4604 | 4890 | 224399 | 6289.11 | 0.145201 | 3.53167 | 3(Loss) | true |
| simdjson (reflection) | 667.699 | 0.12639 | 662.083ms | 4604 | 4890 | 337788 | 6575.89 | 0.0415723 | 3.69327 | 4(Loss) | true |
| simdjson (ondemand) | 544.799 | 0.175621 | 819.119ms | 4604 | 30 | 6009.95 | 8059.33 | 0.0458884 | 4.53094 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1174.74 | 0.293452 | 452.509ms | 4604 | 1280 | 153982 | 3737.59 | 0.0991883 | 2.09305 | 1(Win) | true |
| Jsonifier (two-stage) | 983.657 | 0.10638 | 548.543ms | 4604 | 30 | 676.437 | 4463.67 | 0.0141866 | 2.50096 | 2(Loss) | true |
| Glaze | 789.3 | 0.1106 | 630.243ms | 4604 | 40 | 1514.11 | 5562.8 | 0.135006 | 3.12359 | 3(Loss) | true |
| simdjson (reflection) | 745.816 | 0.192626 | 675.302ms | 4604 | 30 | 3857.98 | 5887.13 | 0.288497 | 3.30457 | 4(Loss) | true |
| simdjson (ondemand) | 571.487 | 0.124198 | 857.512ms | 4604 | 2560 | 233092 | 7682.96 | 0.00745303 | 4.31667 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1569.35 | 0.023069 | 284.569ms | 4604 | 160 | 66.6516 | 2797.8 | 0.161918 | 1.56323 | 1(Win) | true |
| simdjson (reflection) | 1284.99 | 0.0388456 | 359.837ms | 4918 | 30 | 60.3092 | 3649.97 | 0.0602382 | 1.91288 | 2(Loss) | true |
| Glaze | 1095.04 | 0.506978 | 404.397ms | 4604 | 1280 | 528926 | 4009.62 | 0.372344 | 2.24652 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1586.5 | 0.0365475 | 281.24ms | 4604 | 80 | 81.8456 | 2767.55 | 0.0848406 | 1.54723 | 1(Win) | true |
| simdjson (reflection) | 1373.92 | 0.176327 | 346.539ms | 4918 | 2560 | 92753.7 | 3413.72 | 0.134198 | 1.78847 | 2(Loss) | true |
| Glaze | 1147.14 | 0.064324 | 397.316ms | 4604 | 40 | 242.461 | 3827.53 | 0.0198166 | 2.14368 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2902.55 | 0.0593537 | 606.159ms | 18245 | 40 | 506.387 | 5994.65 | 0.161236 | 0.849533 | 1(Win) | true |
| Jsonifier | 2478.16 | 0.18781 | 710.152ms | 18245 | 2560 | 445150 | 7021.24 | 0.449695 | 0.995312 | 2(Loss) | true |
| simdjson (reflection) | 2367.44 | 0.129829 | 742.258ms | 18245 | 4890 | 445232 | 7349.64 | 0.0157949 | 1.04208 | 3(Loss) | true |
| simdjson (ondemand) | 1964.02 | 0.156094 | 893.762ms | 18245 | 1280 | 244781 | 8859.29 | 0.0149626 | 1.25697 | 4(Loss) | true |
| Glaze | 1927.65 | 0.0561635 | 908.993ms | 18245 | 30 | 771.013 | 9026.43 | 0.457412 | 1.2805 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3372.61 | 0.111312 | 598.725ms | 18245 | 4890 | 161268 | 5159.15 | 0.165885 | 0.730169 | 1(Win) | true |
| Jsonifier | 2850.79 | 0.116815 | 698.284ms | 18245 | 4890 | 248578 | 6103.5 | 0.273014 | 0.864844 | 2(Loss) | true |
| simdjson (reflection) | 2614.51 | 0.1 | 744.093ms | 18245 | 4890 | 216580 | 6655.09 | 0.285784 | 0.943262 | 3(Loss) | true |
| simdjson (ondemand) | 2073.87 | 0.12965 | 942.41ms | 18245 | 40 | 4732.95 | 8390.02 | 0.0261291 | 1.19012 | 4(Loss) | true |
| Glaze | 1981.19 | 0.0787139 | 938.627ms | 18245 | 30 | 1433.71 | 8782.5 | 0.252893 | 1.24568 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7188.38 | 0.0699885 | 329.106ms | 24579 | 30 | 156.257 | 3260.87 | 0.051085 | 0.341565 | 1(Win) | true |
| Glaze | 3714.13 | 0.256094 | 697.304ms | 24579 | 640 | 167184 | 6311.13 | 0.0522365 | 0.663886 | 2(Loss) | true |
| simdjson (reflection) | 556.017 | 0.160357 | 4381.95ms | 24893 | 4890 | 2.29225e+07 | 42696.2 | 0.776531 | 4.44974 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7384.54 | 0.0639466 | 321.493ms | 24579 | 40 | 164.808 | 3174.25 | 0.0781725 | 0.332518 | 1(Win) | true |
| Glaze | 4117.02 | 0.083715 | 646.299ms | 24579 | 40 | 908.717 | 5693.52 | 0.339145 | 0.59856 | 2(Loss) | true |
| simdjson (reflection) | 524.101 | 0.123456 | 4528.83ms | 24893 | 4890 | 1.52918e+07 | 45296.2 | 0.0878778 | 4.72123 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1496.24 | 0.0566291 | 326.649ms | 5094 | 40 | 135.225 | 3246.82 | 0.0720698 | 1.6418 | 1(Win) | true |
| simdjson (reflection) | 1473.67 | 0.10756 | 338.683ms | 5094 | 80 | 1005.8 | 3296.54 | 0.0793127 | 1.66671 | 2(Loss) | true |
| Jsonifier (two-stage) | 1377.1 | 0.135682 | 356.141ms | 5094 | 4890 | 112031 | 3527.71 | 0.0754977 | 1.78426 | 3(Loss) | true |
| Glaze | 1234.18 | 0.115369 | 413.378ms | 5094 | 30 | 618.668 | 3936.23 | 0.196002 | 1.99226 | 4(Loss) | true |
| simdjson (ondemand) | 1220.53 | 0.2506 | 402.949ms | 5094 | 30 | 2984.75 | 3980.27 | 0.0829778 | 2.0159 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1682.56 | 0.0544947 | 328.841ms | 5094 | 40 | 99.025 | 2887.28 | 0.263394 | 1.45745 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1590.67 | 0.13098 | 350.858ms | 5094 | 40 | 640.071 | 3054.07 | 0.127263 | 1.54319 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1590.38 | 0.0848685 | 354.217ms | 5094 | 30 | 201.62 | 3054.63 | 0.421615 | 1.54412 | 2(Tie) | true |
| Jsonifier (two-stage) | 1556.22 | 0.0824838 | 357.153ms | 5094 | 80 | 530.399 | 3121.68 | 0.0320443 | 1.57744 | 4(Loss) | true |
| Glaze | 1460.9 | 0.0683932 | 378.894ms | 5094 | 80 | 413.804 | 3325.36 | 0.0944397 | 1.68138 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17440.8 | 0.0926282 | 30.3237ms | 5094 | 320 | 21.3022 | 278.544 | 0.176948 | 0.129193 | 1(Win) | true |
| simdjson (reflection) | 11466.6 | 0.283678 | 44.5803ms | 5094 | 30 | 43.3333 | 423.667 | 0.0786164 | 0.202277 | 2(Loss) | true |
| Glaze | 3757.06 | 0.0454382 | 133.065ms | 5094 | 160 | 55.2313 | 1293.04 | 0.0415515 | 0.645485 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17983.3 | 0.066725 | 29.4327ms | 5094 | 640 | 20.794 | 270.141 | 0.0300679 | 0.1248 | 1(Win) | true |
| simdjson (reflection) | 12462.4 | 0.158157 | 41.5176ms | 5094 | 80 | 30.4074 | 389.812 | 0.125217 | 0.184882 | 2(Loss) | true |
| Glaze | 4225.33 | 0.058217 | 118.589ms | 5094 | 80 | 35.8416 | 1149.74 | 0.00108719 | 0.57259 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 2207.21 | 0.317459 | 387.64ms | 8051 | 1280 | 156098 | 3478.61 | 0.0991913 | 1.11335 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2206.18 | 0.088458 | 357.802ms | 8051 | 30 | 284.323 | 3480.23 | 0.0382969 | 1.1136 | 1(Tie) | true |
| Jsonifier | 1929.58 | 0.051525 | 409.202ms | 8051 | 80 | 336.278 | 3979.11 | 0.0348817 | 1.27499 | 3(Loss) | true |
| simdjson (ondemand) | 1912.8 | 0.150543 | 415.731ms | 8051 | 40 | 1460.64 | 4014.03 | 0.0500079 | 1.28617 | 4(Loss) | true |
| Glaze | 1693.47 | 0.0557194 | 461.136ms | 8051 | 80 | 510.562 | 4533.91 | 0.229633 | 1.45354 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2495.72 | 0.164052 | 350.642ms | 8051 | 4890 | 124560 | 3076.47 | 0.44215 | 0.983649 | 1(Win) | true |
| simdjson (ondemand) | 2455.07 | 0.106966 | 365.642ms | 8051 | 40 | 447.635 | 3127.43 | 0.115244 | 0.999736 | 2(Loss) | true |
| simdjson (reflection) | 2392.91 | 0.0507277 | 368.992ms | 8051 | 80 | 211.948 | 3208.66 | 0.145521 | 1.02629 | 3(Loss) | true |
| Jsonifier | 2172.29 | 0.0797893 | 406.761ms | 8051 | 30 | 238.602 | 3534.53 | 0.149228 | 1.13198 | 4(Loss) | true |
| Glaze | 1994.46 | 0.0409856 | 436.384ms | 8051 | 160 | 398.319 | 3849.68 | 0.0047084 | 1.23305 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27101.3 | 0.0682585 | 35.1866ms | 9255 | 640 | 31.6276 | 325.677 | 0.164833 | 0.0840748 | 1(Win) | true |
| Glaze | 4447.97 | 0.144437 | 210.421ms | 9255 | 30 | 246.437 | 1984.33 | 0.117726 | 0.549289 | 2(Loss) | true |
| simdjson (reflection) | 574.825 | 0.0855468 | 1546.41ms | 9255 | 4890 | 843720 | 15354.7 | 0.687712 | 4.2998 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30422.9 | 0.0837989 | 31.5931ms | 9255 | 320 | 18.9138 | 290.119 | 0.195657 | 0.073984 | 1(Win) | true |
| Glaze | 4919.33 | 0.0787506 | 183.914ms | 9255 | 40 | 79.8564 | 1794.2 | 0.026003 | 0.496524 | 2(Loss) | true |
| simdjson (reflection) | 588.451 | 0.0794945 | 1590.7ms | 9255 | 30 | 4265.09 | 14999.1 | 0.715119 | 4.19997 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7024.65 | 0.0480082 | 42.15ms | 2889 | 640 | 22.6912 | 392.214 | 0.0465887 | 0.329512 | 1(Win) | true |
| simdjson (reflection) | 6431.2 | 0.0776966 | 45.2586ms | 2889 | 160 | 17.727 | 428.406 | 0.173308 | 0.361113 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 6019.75 | 0.166166 | 48.5034ms | 2889 | 160 | 92.5432 | 457.688 | 0.00546254 | 0.387418 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6011.91 | 0.0747856 | 48.5384ms | 2889 | 640 | 75.1772 | 458.284 | 0.0878866 | 0.387742 | 3(Tie) | true |
| Glaze | 3158.93 | 0.0604864 | 90.8652ms | 2889 | 320 | 89.0599 | 872.184 | 0.043335 | 0.760508 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7120.47 | 0.0393332 | 63.9229ms | 2889 | 1280 | 29.6487 | 386.936 | 0.0327196 | 0.324405 | 1(Win) | true |
| simdjson (reflection) | 6471.13 | 0.131944 | 45.2252ms | 2889 | 80 | 25.2467 | 425.762 | 0.0850689 | 0.358056 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 6141.93 | 0.0846565 | 47.4429ms | 2889 | 640 | 92.2967 | 448.583 | 0.17351 | 0.378543 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6131.64 | 0.0792684 | 48.098ms | 2889 | 640 | 81.1937 | 449.336 | 0.283986 | 0.379779 | 3(Tie) | true |
| Glaze | 3036.44 | 0.143499 | 92.7546ms | 2889 | 30 | 50.8609 | 907.367 | 0.554098 | 0.792223 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7626.89 | 0.064249 | 52.0359ms | 3808 | 1280 | 119.796 | 476.156 | 0.129787 | 0.306567 | 1(Win) | true |
| Jsonifier (two-stage) | 7178.74 | 0.106084 | 54.2067ms | 3808 | 160 | 46.0801 | 505.881 | 0.0506285 | 0.326106 | 2(Loss) | true |
| Jsonifier | 7124.17 | 0.0901418 | 53.2525ms | 3808 | 160 | 33.783 | 509.756 | 0.0771832 | 0.328921 | 3(Loss) | true |
| simdjson (reflection) | 7036.11 | 0.0699068 | 54.7226ms | 3808 | 640 | 83.3195 | 516.136 | 0.0778623 | 0.333641 | 4(Loss) | true |
| Glaze | 3894.74 | 0.0242268 | 98.6777ms | 3808 | 640 | 32.6594 | 932.436 | 0.031996 | 0.618587 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7616.07 | 0.0883935 | 50.5882ms | 3808 | 640 | 113.698 | 476.833 | 0.016059 | 0.306469 | 1(Win) | true |
| Jsonifier (two-stage) | 7582.2 | 0.115403 | 51.1303ms | 3808 | 80 | 24.4416 | 478.962 | 0.101886 | 0.307888 | 2(Loss) | true |
| Jsonifier | 7271.91 | 0.207164 | 52.4596ms | 3808 | 30 | 32.1103 | 499.4 | 0.133672 | 0.321551 | 3(Loss) | true |
| simdjson (reflection) | 7205.05 | 0.0676963 | 53.1374ms | 3808 | 2560 | 298.05 | 504.034 | 0.303726 | 0.325142 | 4(Loss) | true |
| Glaze | 3873.03 | 0.0581958 | 96.9742ms | 3808 | 80 | 23.8214 | 937.663 | 0.238057 | 0.62071 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2296.38 | 0.0981573 | 124.703ms | 2889 | 80 | 110.954 | 1199.79 | 0.126223 | 1.05272 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1975.94 | 0.0301549 | 143.857ms | 2889 | 640 | 113.147 | 1394.36 | 0.299982 | 1.22873 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1973 | 0.144724 | 145.037ms | 2889 | 30 | 122.53 | 1396.43 | 0.0716623 | 1.23111 | 2(Tie) | true |
| Glaze | 1960.9 | 0.138527 | 147.681ms | 2889 | 40 | 151.536 | 1405.05 | 0.376971 | 1.23831 | 4(Loss) | true |
| simdjson (ondemand) | 1177.34 | 0.0923848 | 245.438ms | 2889 | 160 | 747.848 | 2340.16 | 0.18075 | 2.07939 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2531.58 | 0.0770117 | 118.088ms | 2889 | 160 | 112.395 | 1088.32 | 0.280037 | 0.953647 | 1(Win) | true |
| Jsonifier (two-stage) | 2253.44 | 0.246464 | 130.779ms | 2889 | 4890 | 44403.6 | 1222.65 | 0.0066497 | 1.0757 | 2(Loss) | true |
| Glaze | 2126.56 | 0.0445258 | 136.631ms | 2889 | 320 | 106.492 | 1295.6 | 0.146435 | 1.13994 | 3(Loss) | true |
| simdjson (reflection) | 2079 | 0.133637 | 144.729ms | 2889 | 80 | 250.918 | 1325.24 | 0.326476 | 1.16657 | 4(Loss) | true |
| simdjson (ondemand) | 1194.94 | 0.07499 | 242.722ms | 2889 | 160 | 478.329 | 2305.69 | 0.0260294 | 2.04793 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12471.3 | 0.0893299 | 25.2355ms | 2963 | 640 | 26.219 | 226.58 | 0.124974 | 0.175389 | 1(Win) | true |
| simdjson (reflection) | 8978.97 | 0.0942072 | 34.5691ms | 2963 | 640 | 56.2547 | 314.706 | 0.208094 | 0.253657 | 2(Loss) | true |
| Glaze | 5107.8 | 0.0845351 | 57.6975ms | 2963 | 640 | 139.975 | 553.22 | 0.0296471 | 0.461544 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14018.9 | 0.0724509 | 22.7845ms | 2963 | 1280 | 27.2982 | 201.566 | 0.101059 | 0.152754 | 1(Win) | true |
| simdjson (reflection) | 11102.5 | 0.133178 | 28.0828ms | 2963 | 320 | 36.7647 | 254.512 | 0.242522 | 0.201126 | 2(Loss) | true |
| Glaze | 5595.24 | 0.15702 | 53.7084ms | 2963 | 40 | 25.1532 | 505.025 | 0.19012 | 0.41895 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2493.6 | 0.0594696 | 149.346ms | 3808 | 160 | 120.019 | 1456.36 | 0.0557586 | 0.971837 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2488.37 | 0.114681 | 149.48ms | 3808 | 80 | 224.096 | 1459.42 | 0.140269 | 0.976513 | 1(Tie) | true |
| Glaze | 2233.93 | 0.0960461 | 167.135ms | 3808 | 40 | 97.5154 | 1625.65 | 0.150482 | 1.09019 | 3(Loss) | true |
| Jsonifier | 2055.35 | 0.111783 | 180.872ms | 3808 | 40 | 156.041 | 1766.9 | 0.137528 | 1.18612 | 4(Loss) | true |
| simdjson (ondemand) | 1436.36 | 0.159278 | 258.015ms | 3808 | 40 | 648.687 | 2528.32 | 0.00560287 | 1.70554 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2699.06 | 0.179603 | 141.028ms | 3808 | 40 | 233.59 | 1345.5 | 0.0643708 | 0.89851 | 1(Win) | true |
| simdjson (reflection) | 2675.69 | 0.0518901 | 150.805ms | 3808 | 320 | 158.724 | 1357.26 | 0.0423469 | 0.906744 | 2(Loss) | true |
| Glaze | 2390.17 | 0.0529784 | 164.285ms | 3808 | 80 | 51.8353 | 1519.39 | 0.155732 | 1.01823 | 3(Loss) | true |
| Jsonifier | 2220.85 | 0.11916 | 171.487ms | 3808 | 40 | 151.871 | 1635.22 | 0.116566 | 1.09634 | 4(Loss) | true |
| simdjson (ondemand) | 1514.3 | 0.115515 | 257.455ms | 3808 | 80 | 613.959 | 2398.2 | 0.21636 | 1.61696 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16749.1 | 0.319811 | 27.3839ms | 4300 | 80 | 49.0492 | 244.838 | 0.107329 | 0.131645 | 1(Win) | true |
| Glaze | 3797.52 | 0.0949959 | 112.118ms | 4300 | 160 | 168.371 | 1079.86 | 0.127169 | 0.635465 | 2(Loss) | true |
| simdjson (reflection) | 552.936 | 0.385972 | 760.605ms | 4300 | 640 | 524420 | 7416.41 | 0.192638 | 4.46013 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19549.9 | 0.0375081 | 23.7438ms | 4300 | 2560 | 15.8467 | 209.761 | 0.124986 | 0.110359 | 1(Win) | true |
| Glaze | 4621.17 | 0.0744104 | 92.7877ms | 4300 | 160 | 69.7622 | 887.394 | 0.0359069 | 0.519557 | 2(Loss) | true |
| simdjson (reflection) | 540.589 | 0.325902 | 724.544ms | 4300 | 320 | 195582 | 7585.8 | 0.184442 | 4.56295 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4449.57 | 0.144133 | 5453.7ms | 466906 | 640 | 1.33146e+07 | 100072 | 1.6822 | 0.556279 | 1(Win) | true |
| Glaze | 2482.25 | 0.359678 | 8916.27ms | 466906 | 30 | 1.24887e+07 | 179384 | 0.0802102 | 0.99725 | 2(Loss) | true |
| simdjson (ondemand) | 1888.28 | 0.0796746 | 5961.66ms | 466906 | 1280 | 4.51832e+07 | 235811 | 0.206086 | 1.31096 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4191.74 | 0.630699 | 5555.81ms | 466906 | 30 | 1.34659e+07 | 106227 | 0.0625626 | 0.590456 | 1(Win) | true |
| Glaze | 2637.77 | 0.274095 | 9076.27ms | 466906 | 30 | 6.42255e+06 | 168808 | 0.0721603 | 0.93848 | 2(Loss) | true |
| simdjson (ondemand) | 1913.13 | 0.160403 | 5886.79ms | 466906 | 80 | 1.11503e+07 | 232748 | 0.904782 | 1.29396 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5279.51 | 0.198494 | 6575.82ms | 699405 | 80 | 5.03103e+06 | 126338 | 0.337422 | 0.468844 | 1(Win) | true |
| Glaze | 3311.86 | 0.109368 | 5430.96ms | 699405 | 160 | 7.76273e+06 | 201399 | 0.702259 | 0.747467 | 2(Loss) | true |
| simdjson (ondemand) | 2652.7 | 0.11125 | 6987.34ms | 767297 | 320 | 3.01372e+07 | 275852 | 0.354678 | 0.933192 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5203.36 | 0.0928811 | 6588.79ms | 699405 | 640 | 9.07243e+06 | 128187 | 0.0984795 | 0.475704 | 1(Win) | true |
| Glaze | 3453.07 | 0.0844686 | 5140.36ms | 699405 | 640 | 1.70379e+07 | 193163 | 0.137642 | 0.716892 | 2(Loss) | true |
| simdjson (ondemand) | 2678.43 | 0.114942 | 6976.82ms | 767297 | 1280 | 1.26221e+08 | 273201 | 0.239829 | 0.924244 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3133.27 | 0.177579 | 9708.53ms | 631514 | 1280 | 1.49129e+08 | 192214 | 0.901406 | 0.790028 | 1(Win) | true |
| Glaze | 2419.77 | 0.207945 | 6449.58ms | 631514 | 40 | 1.07145e+07 | 248891 | 0.0353243 | 1.02307 | 2(Loss) | true |
