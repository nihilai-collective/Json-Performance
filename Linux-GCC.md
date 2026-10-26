# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

Latest Results: (Oct 28, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| Glaze: [f67610b](https://github.com/stephenberry/glaze/commit/f67610b)  
| Simdjson: [41ad75c](https://github.com/simdjson/simdjson/commit/41ad75c)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
| **simdjson (reflection)** | `haswell` |
| **Glaze** | utf8: `AVX2`, escape: `AVX2`, float: `SSE4.1`, struct-skip: `AVX2` |

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
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
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2242.2 | 0.0746155 | 763.654ms | 905 | 4890 | 403.38 | 384.923 | 0.0357986 | 2.49311 | 12.6785 | 1.84972 | 0.00110768 | 0.000137613 | 1.3106e-05 | 1(Win) | true |
| glaze | 774.678 | 0.0434723 | 835.843ms | 905 | 2560 | 600.509 | 1114.11 | 0.0119224 | 6.75651 | 18.6398 | 3.27514 | 0.00222074 | 6.73343e-05 | 8.6326e-07 | 2(Loss) | true |
| jsonifier (two-stage) | 556.067 | 0.0470228 | 880.577ms | 905 | 2560 | 1363.64 | 1552.11 | 0.00274332 | 9.32098 | 42.7669 | 5.32707 | 0.00111922 | 0.000148481 | 5.61119e-06 | 3(Loss) | true |
| simdjson (ondemand) | 246.574 | 0.0492231 | 1080.44ms | 905 | 4890 | 14516.1 | 3500.27 | 0.162968 | 20.6414 | 103.864 | 10.4641 | 0.0212866 | 0.000171056 | 1.03944e-05 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2454.8 | 0.0945355 | 757.855ms | 905 | 640 | 70.7028 | 351.587 | 0.0186619 | 2.29612 | 12.147 | 1.73039 | 0.00110497 | 5.35221e-05 | 0 | 1(Win) | true |
| glaze | 728.888 | 0.0401076 | 841.533ms | 905 | 4890 | 1102.91 | 1184.1 | 0.0403432 | 7.17175 | 18.2972 | 3.16243 | 0.00115627 | 9.76172e-05 | 3.61545e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 582.46 | 0.0622511 | 873.801ms | 905 | 160 | 136.138 | 1481.78 | 0.0523295 | 9.08662 | 42.2011 | 5.21436 | 0.00167818 | 0.000131215 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 250.854 | 0.0748504 | 1075.01ms | 905 | 40 | 265.279 | 3440.55 | 0.0972734 | 20.4007 | 103.298 | 10.3514 | 0.021105 | 0.000138122 | 0 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2194.65 | 0.0931926 | 764.202ms | 905 | 640 | 85.963 | 393.264 | 0.308554 | 2.53174 | 10.0729 | 0.743646 | 0.00337707 | 6.04282e-05 | 1.72652e-06 | 1(Win) | true |
| simdjson (reflection) | 248.829 | 0.0762714 | 1076.51ms | 905 | 640 | 4479.19 | 3468.55 | 0.162493 | 20.5382 | 94.8696 | 20.9171 | 0.0456319 | 0.000108771 | 0 | 2(Loss) | true |
| glaze | 203.465 | 0.0518338 | 1151.02ms | 905 | 1280 | 6188.06 | 4241.89 | 0.0959736 | 25.073 | 109.057 | 23.0022 | 0.0876157 | 0.00011913 | 6.04282e-06 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3279.6 | 0.0541064 | 754.166ms | 905 | 2560 | 51.903 | 263.164 | 0.144514 | 1.7753 | 7.77459 | 0.271823 | 0.00221642 | 9.36637e-05 | 1.29489e-05 | 1(Win) | true |
| simdjson (reflection) | 2476.73 | 0.204836 | 772.298ms | 905 | 2560 | 1304.34 | 348.473 | 0.0972819 | 2.28152 | 8.45304 | 1.05193 | 0.00110497 | 7.4672e-05 | 1.29489e-05 | 2(Loss) | true |
| glaze | 677.653 | 0.0499077 | 864.101ms | 905 | 1280 | 517.164 | 1273.62 | 0.0416677 | 7.71695 | 21.8155 | 3.36685 | 0.00150121 | 4.40262e-05 | 0 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1221.35 | 0.0378778 | 872.629ms | 1811 | 1280 | 367.228 | 1414.09 | 0.0841021 | 4.26284 | 18.8586 | 3.75207 | 0.000566848 | 8.84353e-05 | 3.45113e-06 | 1(Win) | true |
| glaze | 964.398 | 0.0718776 | 908.779ms | 1811 | 160 | 265.113 | 1790.86 | 0.0230283 | 5.36309 | 26.6455 | 4.12148 | 0.000552181 | 5.86692e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 624.496 | 0.0405853 | 1010.08ms | 1811 | 2560 | 3225.19 | 2765.6 | 0.00810808 | 8.20748 | 33.3954 | 5.10933 | 0.00102024 | 0.00011475 | 1.42359e-05 | 3(Loss) | true |
| simdjson (ondemand) | 292.129 | 0.0772517 | 1326.09ms | 1811 | 1280 | 26700.2 | 5912.13 | 0.13685 | 17.3108 | 88.1938 | 12.2253 | 0.000633714 | 0.000146242 | 2.45893e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1336.57 | 0.0778168 | 857.302ms | 1811 | 1280 | 1294.22 | 1292.19 | 0.019585 | 3.9007 | 17.8023 | 3.51132 | 0.000905922 | 5.60809e-05 | 0 | 1(Win) | true |
| glaze | 1003.2 | 0.0304557 | 898.47ms | 1811 | 4890 | 1344.34 | 1721.6 | 0.0120673 | 5.15197 | 25.7079 | 3.88515 | 0.00111125 | 0.000154475 | 2.6988e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 660.948 | 0.0205857 | 991.715ms | 1811 | 4890 | 1414.96 | 2613.07 | 0.00375429 | 7.76533 | 32.3302 | 4.86858 | 0.00111023 | 0.000100273 | 1.51313e-05 | 3(Loss) | true |
| simdjson (ondemand) | 298.692 | 0.0371754 | 1313.99ms | 1811 | 4890 | 22594.8 | 5782.22 | 0.0743025 | 16.8805 | 87.159 | 11.9972 | 0.000636307 | 0.000116195 | 1.38892e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 342.08 | 0.0573015 | 1233.79ms | 1811 | 640 | 5356.66 | 5048.83 | 0.0531346 | 14.8916 | 62.54 | 10.8736 | 0.0170891 | 0.000207068 | 7.50621e-05 | 1(Win) | true |
| simdjson (reflection) | 339.198 | 0.0454549 | 1294.03ms | 1997 | 1280 | 8337.2 | 5614.68 | 0.0520963 | 14.9581 | 64.2529 | 11.6635 | 0.00371925 | 7.31566e-05 | 8.21545e-06 | 2(Loss) | true |
| glaze | 303.236 | 0.0245222 | 1299.79ms | 1798 | 4890 | 9402.6 | 5654.7 | 0.0587186 | 16.7216 | 70.1475 | 12.3677 | 0.0201207 | 0.000194831 | 2.26336e-05 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 824.048 | 0.0256161 | 943.905ms | 1811 | 4890 | 1409.51 | 2095.88 | 0.00943101 | 6.2559 | 19.6963 | 1.03424 | 0.000772037 | 6.40259e-05 | 5.08142e-06 | 1(Win) | true |
| simdjson (reflection) | 645.3 | 0.0416552 | 1037.16ms | 1997 | 1280 | 1934.56 | 2951.32 | 0.024227 | 7.94285 | 25.2954 | 2.57787 | 0.000788683 | 7.70687e-05 | 1.25188e-05 | 2(Loss) | true |
| glaze | 641.373 | 0.073907 | 1014.23ms | 1798 | 4890 | 19091.4 | 2673.49 | 0.0287496 | 8.00096 | 26.4755 | 2.36263 | 0.000753962 | 0.00012693 | 1.2966e-05 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3346.06 | 0.0566628 | 843.486ms | 3862 | 2560 | 995.849 | 1100.73 | 0.0256512 | 1.55687 | 7.23123 | 0.889177 | 0.000268137 | 7.73765e-05 | 1.40593e-05 | 1(Win) | true |
| glaze | 1750.78 | 0.025763 | 941.283ms | 3862 | 4890 | 1436.36 | 2103.68 | 0.0896392 | 2.94045 | 14.515 | 1.82108 | 0.000266823 | 3.43656e-05 | 5.77172e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1432.5 | 0.0634463 | 990.973ms | 3862 | 640 | 1703.04 | 2571.09 | 0.0364765 | 3.56623 | 14.1295 | 1.56939 | 0.000271475 | 2.75117e-05 | 4.04583e-07 | 3(Loss) | true |
| simdjson (ondemand) | 724.224 | 0.0193972 | 1242.45ms | 3862 | 4890 | 4758.42 | 5085.56 | 0.0342615 | 7.03107 | 32.9221 | 3.87157 | 0.00524104 | 3.03413e-05 | 3.283e-06 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3698.62 | 0.15076 | 831.809ms | 3862 | 30 | 67.6138 | 995.8 | 0.0434972 | 1.42703 | 6.78975 | 0.790005 | 0.000258933 | 1.72622e-05 | 0 | 1(Win) | true |
| glaze | 1847.33 | 0.0535036 | 927.087ms | 3862 | 80 | 91.0315 | 1993.74 | 0.0394831 | 2.79102 | 14.1336 | 1.71129 | 0.000313956 | 3.23666e-05 | 1.61833e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1509.41 | 0.0353045 | 974.513ms | 3862 | 2560 | 1899.8 | 2440.08 | 0.0196145 | 3.40395 | 13.696 | 1.47022 | 0.000263687 | 3.3277e-05 | 1.61833e-06 | 3(Loss) | true |
| simdjson (ondemand) | 739.307 | 0.0659312 | 1223.97ms | 3862 | 160 | 1726.14 | 4981.81 | 0.102729 | 6.87466 | 32.4803 | 3.7724 | 0.00673388 | 3.56033e-05 | 0 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 963.277 | 0.0514117 | 1118.49ms | 3862 | 1280 | 4946.04 | 3823.5 | 0.0367313 | 5.29721 | 25.2799 | 5.17245 | 0.00711803 | 6.3115e-05 | 2.06337e-05 | 1(Win) | true |
| simdjson (reflection) | 949.615 | 0.0308048 | 1120.31ms | 3862 | 4890 | 6980.3 | 3878.51 | 0.0459423 | 5.3581 | 26.6989 | 5.23693 | 0.00865303 | 5.7982e-05 | 7.36027e-06 | 2(Loss) | true |
| glaze | 829.976 | 0.0220894 | 1176.94ms | 3862 | 4890 | 4698.63 | 4437.59 | 0.117936 | 6.14316 | 28.9961 | 5.84853 | 0.00905774 | 0.000107704 | 2.77996e-05 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5521.43 | 0.079604 | 820.242ms | 3862 | 2560 | 721.824 | 667.054 | 0.0622878 | 0.974078 | 5.19239 | 0.592439 | 0.000292311 | 3.58056e-05 | 1.3149e-05 | 1(Win) | true |
| simdjson (reflection) | 4217.08 | 0.0414965 | 828.857ms | 3862 | 160 | 21.0157 | 873.375 | 0.0701795 | 1.25775 | 6.48887 | 0.533661 | 0.000258933 | 2.913e-05 | 3.23666e-06 | 2(Loss) | true |
| glaze | 2530.94 | 0.195505 | 907.868ms | 3862 | 40 | 323.769 | 1455.22 | 0.0166041 | 2.05912 | 8.6709 | 1.15122 | 0.00577421 | 5.17866e-05 | 1.29467e-05 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1821.37 | 0.0433825 | 1239.11ms | 9578 | 1280 | 6058.91 | 5015.08 | 0.0654549 | 2.79724 | 14.2344 | 2.70056 | 0.00112506 | 3.45845e-05 | 1.01959e-05 | 1(Win) | true |
| glaze | 1423.46 | 0.034211 | 1377.4ms | 9578 | 2560 | 12337.6 | 6416.97 | 0.0273978 | 3.55536 | 17.8247 | 3.53623 | 0.0014366 | 3.31978e-05 | 1.20719e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1285.29 | 0.0291908 | 1451.44ms | 9578 | 4890 | 21044.9 | 7106.78 | 0.0229475 | 3.93602 | 18.9485 | 2.91178 | 0.00375146 | 3.44177e-05 | 8.3055e-06 | 3(Loss) | true |
| jsonifier (two-stage) | 1226.61 | 0.125661 | 1480.45ms | 9578 | 80 | 7005.3 | 7446.76 | 0.0919028 | 4.14509 | 18.6259 | 3.03988 | 0.00154129 | 2.21863e-05 | 5.2203e-06 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2752.23 | 0.031053 | 1204.54ms | 9578 | 4890 | 5193.94 | 3318.87 | 0.0408527 | 1.84541 | 10.1503 | 1.77991 | 0.000116747 | 2.73292e-05 | 9.11684e-06 | 1(Win) | true |
| glaze | 1998.5 | 0.0369722 | 1342.36ms | 9578 | 2560 | 7310.23 | 4570.56 | 0.179428 | 2.55012 | 13.5896 | 2.56943 | 0.000408325 | 2.5245e-05 | 8.31985e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1722.18 | 0.0670572 | 1414.4ms | 9578 | 320 | 4047.93 | 5303.91 | 0.020449 | 2.95852 | 14.9485 | 2.02568 | 0.00249759 | 1.53346e-05 | 3.26269e-07 | 3(Loss) | true |
| jsonifier (two-stage) | 1571.72 | 0.0302741 | 1461.22ms | 9578 | 4890 | 15137.2 | 5811.64 | 0.0315264 | 3.22785 | 14.6997 | 2.17686 | 0.000214705 | 2.54076e-05 | 7.34471e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4016.16 | 0.0500868 | 963.53ms | 9578 | 4890 | 6345.76 | 2274.38 | 0.0962393 | 1.27075 | 5.17728 | 1.00063 | 0.0018036 | 2.87383e-05 | 9.11684e-06 | 1(Win) | true |
| simdjson (reflection) | 3771.98 | 0.121878 | 980.559ms | 9578 | 320 | 2787.5 | 2421.62 | 0.0615171 | 1.36265 | 6.07509 | 1.13405 | 0.000373904 | 1.85973e-05 | 0 | 2(Loss) | true |
| glaze | 2044.15 | 0.0227199 | 1181.92ms | 9578 | 4890 | 5040.16 | 4468.5 | 0.0836622 | 2.49471 | 12.6405 | 2.58916 | 0.000960535 | 6.93264e-05 | 4.2531e-05 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11417.6 | 0.18871 | 837.967ms | 9578 | 1280 | 2917.42 | 800.018 | 0.0857643 | 0.464337 | 2.21476 | 0.253706 | 0.000681249 | 1.70475e-05 | 2.12075e-06 | 1(Win) | true |
| simdjson (reflection) | 9312.79 | 0.0726854 | 862.649ms | 9578 | 4890 | 2485.39 | 980.833 | 0.134139 | 0.56149 | 3.02422 | 0.331489 | 0.000115338 | 2.49592e-05 | 9.99222e-06 | 2(Loss) | true |
| glaze | 6214.93 | 0.0448578 | 908.362ms | 9578 | 1280 | 556.369 | 1469.73 | 0.0324888 | 0.840417 | 4.38046 | 0.677699 | 0.000425699 | 1.37848e-05 | 6.52537e-07 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3452.36 | 0.0545847 | 836.903ms | 3873 | 4890 | 1667.68 | 1069.87 | 0.0640488 | 1.51893 | 7.06636 | 0.838369 | 0.000315223 | 9.20853e-05 | 3.49016e-05 | 1(Win) | true |
| glaze | 1903.47 | 0.0513621 | 927.044ms | 3873 | 80 | 79.4658 | 1940.45 | 0.100593 | 2.71177 | 12.8474 | 1.79861 | 0.000516396 | 4.19571e-05 | 3.22747e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1409.51 | 0.032026 | 990.328ms | 3873 | 320 | 225.378 | 2620.47 | 0.0127585 | 3.644 | 13.9889 | 1.51665 | 0.000774593 | 4.2764e-05 | 1.04893e-05 | 3(Loss) | true |
| simdjson (ondemand) | 715.687 | 0.0199248 | 1251.44ms | 3873 | 4890 | 5170.65 | 5160.89 | 0.0369753 | 7.10927 | 32.6403 | 3.98735 | 0.010577 | 7.23904e-05 | 1.80052e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3813.26 | 0.0378297 | 824.424ms | 3873 | 640 | 85.9306 | 968.614 | 0.204478 | 1.38196 | 6.58663 | 0.731474 | 0.00052164 | 4.51846e-05 | 7.26181e-06 | 1(Win) | true |
| glaze | 2013.42 | 0.0260472 | 912.05ms | 3873 | 4890 | 1116.49 | 1834.48 | 0.128301 | 2.56437 | 12.4735 | 1.69171 | 0.000287397 | 6.48927e-05 | 2.09621e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1500.21 | 0.0633936 | 994.097ms | 3873 | 80 | 194.884 | 2462.05 | 0.0121835 | 3.42549 | 13.5172 | 1.40976 | 0.000303382 | 3.55022e-05 | 6.45494e-06 | 3(Loss) | true |
| simdjson (ondemand) | 728.431 | 0.043758 | 1238.99ms | 3873 | 160 | 787.688 | 5070.6 | 0.0110921 | 6.99739 | 32.1603 | 3.88045 | 0.0116108 | 4.03434e-05 | 1.61374e-06 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 919.957 | 0.063118 | 1131.77ms | 3873 | 640 | 4110.04 | 4014.95 | 0.0273272 | 5.54719 | 26.8621 | 5.26207 | 0.00855966 | 3.22747e-05 | 3.63091e-06 | 1(Win) | true |
| jsonifier | 907.29 | 0.0414891 | 1144ms | 3873 | 2560 | 7303.17 | 4071 | 0.048643 | 5.6225 | 23.9127 | 4.95275 | 0.00512734 | 9.98499e-05 | 4.1352e-05 | 2(Loss) | true |
| glaze | 859.422 | 0.0864729 | 1164.79ms | 3873 | 80 | 1104.92 | 4297.75 | 0.00698088 | 5.94279 | 28.5533 | 5.79861 | 0.00658727 | 5.4867e-05 | 6.45494e-06 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6210.89 | 0.0869757 | 814.209ms | 3873 | 4890 | 1308.26 | 594.695 | 0.0417529 | 0.872503 | 3.98477 | 0.476375 | 0.000277734 | 3.84393e-05 | 8.7122e-06 | 1(Win) | true |
| simdjson (reflection) | 4357.4 | 0.122852 | 823.618ms | 3873 | 160 | 173.51 | 847.656 | 0.104071 | 1.21791 | 6.42319 | 0.530338 | 0.000413116 | 2.09786e-05 | 0 | 2(Loss) | true |
| glaze | 2752.96 | 0.0530466 | 891.882ms | 3873 | 640 | 324.184 | 1341.68 | 0.0223651 | 1.88061 | 7.7875 | 0.993029 | 0.00401578 | 2.86438e-05 | 3.22747e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1650.07 | 0.0203056 | 6232.33ms | 94653 | 4890 | 603399 | 54705.6 | 0.0241146 | 3.06411 | 13.3967 | 2.36834 | 0.0126675 | 1.7511e-05 | 1.0405e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1504.85 | 0.0707854 | 6698.96ms | 94653 | 80 | 144231 | 59984.7 | 0.0480725 | 3.35889 | 15.1125 | 2.61699 | 0.0087315 | 1.09611e-05 | 5.94276e-06 | 2(Loss) | true |
| glaze | 1481.67 | 0.0727099 | 6831.3ms | 94653 | 320 | 627922 | 60923.4 | 0.0203647 | 3.41267 | 15.3596 | 3.01356 | 0.014033 | 9.70651e-06 | 5.28245e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1385.4 | 0.0129273 | 7280.78ms | 94653 | 4890 | 346931 | 65156.6 | 0.0133562 | 3.63999 | 14.4804 | 2.76203 | 0.0111936 | 2.24542e-05 | 1.39893e-05 | 4(Loss) | true |
| simdjson (reflection) | 1353.73 | 0.0761533 | 7446.84ms | 94653 | 160 | 412577 | 66681.2 | 0.0321033 | 3.73335 | 14.434 | 2.70887 | 0.0120554 | 3.6713e-05 | 2.73367e-05 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2720.42 | 0.0104135 | 5304.81ms | 94653 | 4890 | 58385 | 33181.6 | 0.000137676 | 1.85966 | 9.51999 | 1.54649 | 0.00376652 | 9.97725e-06 | 4.09417e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2229.74 | 0.0285622 | 6039.17ms | 94653 | 2560 | 342281 | 40483.7 | 0.000438064 | 2.2433 | 11.2699 | 1.80172 | 0.00500289 | 1.09528e-05 | 5.37737e-06 | 2(Loss) | true |
| glaze | 2165.31 | 0.0465369 | 6156.11ms | 94653 | 640 | 240883 | 41688.4 | 0.0360879 | 2.32664 | 11.667 | 2.21864 | 0.0089687 | 5.67864e-06 | 1.7333e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1994.5 | 0.0299013 | 6519.9ms | 94653 | 1280 | 234417 | 45258.5 | 0.0177646 | 2.52733 | 10.7088 | 1.94701 | 0.00655603 | 1.65159e-05 | 1.00862e-05 | 4(Loss) | true |
| simdjson (reflection) | 1726.31 | 0.0263124 | 7207.08ms | 94653 | 2560 | 484606 | 52289.5 | 0.0372988 | 2.91903 | 11.3367 | 1.99199 | 0.00858603 | 3.7881e-05 | 2.89833e-05 | 5(Loss) | true |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20270 | 0.0841293 | 1188.6ms | 94653 | 640 | 8983.33 | 4453.29 | 0.00873728 | 0.24901 | 1.17609 | 0.174036 | 4.61224e-05 | 4.68818e-06 | 2.01394e-06 | 1(Win) | true |
| simdjson (reflection) | 13339.9 | 0.0548925 | 1428.31ms | 94653 | 640 | 8830.18 | 6766.77 | 0.0769514 | 0.38146 | 2.13616 | 0.290577 | 3.52604e-05 | 4.72119e-06 | 1.66727e-06 | 2(Loss) | true |
| glaze | 7971.64 | 0.0253519 | 1879.97ms | 94653 | 4890 | 40299.9 | 11323.7 | 0.036879 | 0.631068 | 3.33113 | 0.602126 | 4.36423e-05 | 7.80593e-06 | 4.68615e-06 | 3(Loss) | true |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20550.2 | 0.113627 | 1180.68ms | 94653 | 160 | 3985.85 | 4392.56 | 0.464003 | 0.248444 | 1.17049 | 0.172778 | 3.57226e-05 | 2.04695e-05 | 1.59134e-05 | 1(Win) | true |
| simdjson (reflection) | 13318.9 | 0.10432 | 1417.81ms | 94653 | 320 | 15996.4 | 6777.46 | 0.357974 | 0.378276 | 2.13061 | 0.289331 | 3.27512e-05 | 6.10784e-06 | 3.73073e-06 | 2(Loss) | true |
| glaze | 9526.85 | 0.109794 | 1701.99ms | 94653 | 30 | 3246.74 | 9475.13 | 0.0975431 | 0.533414 | 3.28357 | 0.591307 | 5.24724e-05 | 1.40865e-06 | 7.04327e-07 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1889.86 | 0.0475828 | 7046.99ms | 124597 | 2560 | 2.29138e+06 | 62875 | 0.027842 | 2.65619 | 11.9203 | 2.00323 | 0.00750959 | 5.43063e-05 | 4.14555e-05 | 1(Win) | true |
| simdjson (ondemand) | 1754.26 | 0.0643935 | 7547.13ms | 124597 | 80 | 152194 | 67734.9 | 0.0755317 | 2.88206 | 11.3265 | 2.10845 | 0.00901175 | 0.000112262 | 8.30678e-05 | 2(Loss) | true |
| jsonifier | 1719.74 | 0.0221042 | 7669.77ms | 124597 | 4890 | 1.14064e+06 | 69094.6 | 0.16342 | 2.92706 | 12.0599 | 2.29178 | 0.0173567 | 2.40448e-05 | 1.64752e-05 | 3(Loss) | true |
| simdjson (reflection) | 1704.83 | 0.0408955 | 7755.87ms | 124597 | 640 | 519977 | 69699 | 0.0345003 | 2.96544 | 11.3421 | 2.08327 | 0.010607 | 2.16699e-05 | 1.44967e-05 | 4(Loss) | true |
| glaze | 1669.76 | 0.0295521 | 7887.44ms | 124597 | 1280 | 566104 | 71163.1 | 0.226971 | 3.01968 | 13.6447 | 2.65272 | 0.0114156 | 1.67039e-05 | 1.11673e-05 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2735.77 | 0.246433 | 6463.86ms | 124597 | 160 | 1.83306e+06 | 43433.9 | 0.00827476 | 1.82045 | 9.01177 | 1.39184 | 0.00445607 | 1.22896e-05 | 7.0728e-06 | 1(Win) | true |
| jsonifier | 2529.81 | 0.0665339 | 6793.84ms | 124597 | 320 | 312519 | 46969.9 | 0.074354 | 1.99888 | 9.12178 | 1.67573 | 0.0109354 | 6.22005e-06 | 2.3576e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2507.52 | 0.0159164 | 6751.65ms | 124597 | 4890 | 278179 | 47387.4 | 0.107854 | 2.01103 | 8.47176 | 1.49455 | 0.00540769 | 1.35504e-05 | 8.81697e-06 | 3(Loss) | true |
| glaze | 2233.3 | 0.0373922 | 7450.35ms | 124597 | 1280 | 506632 | 53205.9 | 0.165273 | 2.26367 | 10.8407 | 2.05242 | 0.00903398 | 1.61897e-05 | 1.04587e-05 | 4(Loss) | true |
| simdjson (reflection) | 2202.2 | 0.0543818 | 7402.38ms | 124597 | 640 | 551048 | 53957.4 | 0.0139192 | 2.29264 | 8.99243 | 1.54028 | 0.00653631 | 1.06719e-05 | 6.74675e-06 | 5(Loss) | true |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23227.5 | 0.0381969 | 1301.47ms | 136037 | 1280 | 5826.06 | 5585.4 | 0.124765 | 0.218696 | 0.850945 | 0.121085 | 5.78887e-05 | 5.46726e-06 | 3.06098e-06 | 1(Win) | true |
| glaze | 7073.33 | 0.175565 | 2589.9ms | 136076 | 30 | 31125.3 | 18346.7 | 0.0019985 | 0.715821 | 3.8624 | 0.577185 | 0.000188865 | 3.94387e-05 | 2.67008e-05 | 2(Loss) | true |
| simdjson (reflection) | 595.496 | 0.375696 | 5790.62ms | 136037 | 80 | 5.35945e+07 | 217861 | 0.21399 | 8.46646 | 33.4838 | 6.57894 | 0.0432438 | 0.0301652 | 0.000133052 | 3(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23371.1 | 0.0342264 | 1297.91ms | 136037 | 4890 | 17651.7 | 5551.08 | 0.0367642 | 0.216844 | 0.847064 | 0.120217 | 3.68599e-05 | 6.53768e-06 | 4.03174e-06 | 1(Win) | true |
| glaze | 7954.94 | 0.0303267 | 2377.99ms | 136076 | 320 | 7832.3 | 16313.4 | 0.0205778 | 0.637085 | 3.82926 | 0.569608 | 1.63282e-05 | 2.4343e-06 | 4.82267e-07 | 2(Loss) | true |
| simdjson (reflection) | 591.318 | 0.114196 | 5804.94ms | 136037 | 1280 | 8.03502e+07 | 219400 | 0.254716 | 8.47406 | 33.4728 | 6.57597 | 0.0434046 | 0.0277428 | 0.000123726 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1013.48 | 0.0824167 | 6580.18ms | 2251027 | 160 | 4.87623e+08 | 2.1182e+06 | 0.0193179 | 4.92037 | 26.7769 | 5.14215 | 0.0105097 | 0.10296 | 0.00513717 | 1(Win) | true |
| jsonifier | 988.556 | 0.124521 | 6763.53ms | 2251027 | 40 | 2.92486e+08 | 2.1716e+06 | 0.1018 | 5.10496 | 24.428 | 4.89555 | 0.017165 | 0.0647116 | 0.000154052 | 2(Loss) | true |
| simdjson (reflection) | 925.642 | 0.186239 | 7239.87ms | 2251027 | 80 | 1.49247e+09 | 2.3192e+06 | 0.118019 | 5.43232 | 27.6529 | 4.87626 | 0.00986889 | 0.103708 | 0.000376417 | 3(Loss) | true |
| simdjson (ondemand) | 857.554 | 0.0723473 | 7799.11ms | 2251027 | 40 | 1.31203e+08 | 2.50334e+06 | 0.0178637 | 5.88948 | 29.9788 | 5.43456 | 0.0148455 | 0.108348 | 0.00398942 | 4(Loss) | true |
| glaze | 809.723 | 0.115633 | 8255.24ms | 2251027 | 40 | 3.75933e+08 | 2.65121e+06 | 0.0121793 | 6.23293 | 30.1846 | 5.68796 | 0.0180943 | 0.0635292 | 0.000733343 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1251.41 | 0.0605358 | 6610.68ms | 2251027 | 160 | 1.72546e+08 | 1.71546e+06 | 0.179514 | 4.02502 | 21.9074 | 3.98391 | 0.00989988 | 0.0789181 | 0.00103875 | 1(Win) | true |
| jsonifier | 1191.22 | 0.118974 | 6829.54ms | 2251027 | 30 | 1.37912e+08 | 1.80214e+06 | 0.167934 | 4.23774 | 19.5105 | 3.72204 | 0.016521 | 0.0417815 | 0.000150598 | 2(Loss) | true |
| simdjson (reflection) | 1117.68 | 0.356068 | 7108.38ms | 2251027 | 30 | 1.40319e+09 | 1.92072e+06 | 0.332695 | 4.51189 | 22.7747 | 3.71331 | 0.00860234 | 0.0774004 | 0.00265911 | 3(Loss) | true |
| simdjson (ondemand) | 1033.39 | 0.081835 | 7683.03ms | 2251027 | 40 | 1.15603e+08 | 2.07738e+06 | 0.0859722 | 4.88298 | 25.063 | 4.26713 | 0.0112348 | 0.0763294 | 0.000132062 | 4(Loss) | true |
| glaze | 945.528 | 0.0941324 | 8239.59ms | 2251027 | 40 | 1.82705e+08 | 2.27042e+06 | 0.276292 | 5.33648 | 25.24 | 4.51229 | 0.0172266 | 0.0400978 | 0.000782043 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2145.49 | 0.0194242 | 5917.62ms | 2090234 | 320 | 1.04225e+07 | 929111 | 0.00511536 | 2.35426 | 7.66555 | 0.373371 | 0.000307791 | 0.0513313 | 0.000189618 | 1(Win) | true |
| glaze | 1441.69 | 0.0647091 | 8782.24ms | 2090234 | 160 | 1.28084e+08 | 1.38268e+06 | 0.0164422 | 3.48811 | 9.69978 | 0.651392 | 0.0117862 | 0.0700118 | 0.00160438 | 2(Loss) | true |
| simdjson (reflection) | 1036.09 | 0.0868992 | 6006.5ms | 2090326 | 40 | 1.11821e+08 | 1.92405e+06 | 0.075745 | 4.88705 | 15.3147 | 1.4617 | 0.016069 | 0.0513235 | 0.000592467 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2146.03 | 0.0165942 | 5908.48ms | 2090234 | 160 | 3.80146e+06 | 928878 | 0.100983 | 2.35362 | 7.66539 | 0.373337 | 0.000323128 | 0.0512703 | 0.000170947 | 1(Win) | true |
| glaze | 1513.25 | 0.14987 | 8338.32ms | 2090234 | 30 | 1.16928e+08 | 1.3173e+06 | 0.170388 | 3.31568 | 9.69577 | 0.65046 | 0.0117784 | 0.0440803 | 0.000311943 | 2(Loss) | true |
| simdjson (reflection) | 1033.97 | 0.0145442 | 6025.57ms | 2090326 | 30 | 2.35896e+06 | 1.928e+06 | 0.0511619 | 4.88572 | 15.3145 | 1.46167 | 0.0160246 | 0.0511491 | 0.000299092 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2235.66 | 0.196392 | 7159.32ms | 5373214 | 30 | 6.0789e+08 | 2.29208e+06 | 0.123651 | 2.24158 | 12.0022 | 2.17531 | 0.00501905 | 0.0628752 | 0.00164834 | 1(Win) | true |
| jsonifier | 2092.96 | 0.125164 | 7631.81ms | 5373214 | 80 | 7.51269e+08 | 2.44835e+06 | 0.0634471 | 2.40261 | 12.1399 | 2.59343 | 0.0067514 | 0.0386388 | 0.00102361 | 2(Loss) | true |
| simdjson (reflection) | 2062.16 | 0.223334 | 7773.43ms | 5373214 | 40 | 1.23195e+09 | 2.48491e+06 | 0.290521 | 2.44059 | 12.3508 | 2.07612 | 0.00447411 | 0.062687 | 0.000962878 | 3(Loss) | true |
| simdjson (ondemand) | 1907.69 | 0.108417 | 8382.58ms | 5373214 | 30 | 2.54432e+08 | 2.68612e+06 | 0.121402 | 2.64429 | 13.3259 | 2.3103 | 0.00656794 | 0.0647331 | 0.00113769 | 4(Loss) | true |
| glaze | 1597.81 | 0.0963116 | 10010.3ms | 5373214 | 40 | 3.81624e+08 | 3.20708e+06 | 0.0235694 | 3.16043 | 16.0443 | 2.96014 | 0.00799326 | 0.0415821 | 0.00218136 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2665.21 | 0.18128 | 7151.62ms | 5373214 | 40 | 4.85922e+08 | 1.92266e+06 | 0.788522 | 1.88014 | 9.96926 | 1.69178 | 0.00476381 | 0.0525631 | 0.000826326 | 1(Win) | true |
| jsonifier | 2468.32 | 0.0871966 | 7578.9ms | 5373214 | 160 | 5.24307e+08 | 2.07603e+06 | 0.00195058 | 2.04464 | 10.1065 | 2.10955 | 0.00647816 | 0.0284636 | 0.00115372 | 2(Loss) | true |
| simdjson (reflection) | 2442.78 | 0.182285 | 7621.1ms | 5373214 | 80 | 1.16974e+09 | 2.09773e+06 | 0.174086 | 2.05974 | 10.306 | 1.58882 | 0.00386472 | 0.0512063 | 0.00136127 | 3(Loss) | true |
| simdjson (ondemand) | 2274.94 | 0.0997991 | 8188.86ms | 5373214 | 40 | 2.02136e+08 | 2.2525e+06 | 0.0719481 | 2.21749 | 11.2643 | 1.82073 | 0.00503152 | 0.0509507 | 0.00195208 | 4(Loss) | true |
| glaze | 1800.49 | 0.0873444 | 10080.8ms | 5373214 | 80 | 4.94366e+08 | 2.84606e+06 | 0.180091 | 2.80155 | 14.0002 | 2.47552 | 0.0075683 | 0.0305648 | 0.00463215 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6107.11 | 0.0106182 | 6616.88ms | 6661897 | 40 | 488078 | 1.04031e+06 | 0.0288234 | 0.827096 | 2.48897 | 0.117149 | 0.000100287 | 0.0280815 | 1.65944e-05 | 1(Win) | true |
| glaze | 3219.93 | 0.128357 | 6199.13ms | 6661897 | 30 | 1.92424e+08 | 1.97311e+06 | 0.345028 | 1.56188 | 4.40913 | 0.355571 | 0.00381816 | 0.063548 | 0.00301126 | 2(Loss) | true |
| simdjson (reflection) | 384.821 | 0.2912 | 11637.7ms | 6661989 | 30 | 6.93418e+10 | 1.65099e+07 | 0.60741 | 13.0712 | 41.3281 | 5.59124 | 0.0241769 | 0.254942 | 0.105674 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6103.08 | 0.020768 | 6619.21ms | 6661897 | 80 | 3.73917e+06 | 1.041e+06 | 0.00580127 | 0.827566 | 2.48892 | 0.117138 | 0.000100546 | 0.028066 | 2.93404e-05 | 1(Win) | true |
| glaze | 3842.2 | 0.0403603 | 5158.48ms | 6661897 | 80 | 3.56315e+07 | 1.65355e+06 | 0.0298424 | 1.31457 | 4.40771 | 0.355242 | 0.00380442 | 0.0248034 | 8.70773e-05 | 2(Loss) | true |
| simdjson (reflection) | 379.847 | 0.31211 | 5007.06ms | 6661989 | 30 | 8.17575e+10 | 1.67261e+07 | 0.641732 | 13.1125 | 41.3195 | 5.5877 | 0.0242287 | 0.255508 | 0.116997 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2414.22 | 0.0225894 | 5249.51ms | 500299 | 1280 | 2.55109e+06 | 197630 | 0.00443003 | 2.09278 | 8.93208 | 1.68478 | 0.0122221 | 0.0105803 | 0.000151014 | 1(Win) | true |
| jsonifier (two-stage) | 1861.99 | 0.154152 | 6828.05ms | 500299 | 40 | 6.24114e+06 | 256243 | 0.0508697 | 2.71364 | 11.8648 | 2.05224 | 0.0138492 | 0.0424387 | 0.000113482 | 2(Loss) | true |
| glaze | 1782.77 | 0.152828 | 6940.02ms | 500299 | 40 | 6.69165e+06 | 267630 | 0.016733 | 2.78844 | 11.5682 | 2.26287 | 0.0138648 | 0.00585965 | 0.000136269 | 3(Loss) | true |
| simdjson (reflection) | 1420.9 | 0.0361835 | 9078.15ms | 500299 | 320 | 4.72392e+06 | 335789 | 0.165821 | 3.55609 | 14.6782 | 2.36489 | 0.0185487 | 0.0232455 | 0.000181142 | 4(Loss) | true |
| simdjson (ondemand) | 1362.51 | 0.020169 | 9157.34ms | 500299 | 1280 | 6.38495e+06 | 350179 | 0.181255 | 3.70691 | 14.1991 | 2.33486 | 0.0177011 | 0.0355987 | 0.000215851 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3012.82 | 0.108044 | 5083.34ms | 500299 | 40 | 1.17103e+06 | 158364 | 0.0302191 | 1.6772 | 7.81515 | 1.41447 | 0.00904779 | 0.00548887 | 1.12932e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2238.39 | 0.0392099 | 6538.73ms | 500299 | 320 | 2.23528e+06 | 213155 | 0.195817 | 2.2572 | 10.7468 | 1.78237 | 0.00958331 | 0.0318692 | 8.01271e-05 | 2(Loss) | true |
| glaze | 2176.24 | 0.0389024 | 6705ms | 500299 | 640 | 4.65564e+06 | 219242 | 0.0108967 | 2.32252 | 10.4582 | 1.99555 | 0.00947295 | 0.0027519 | 2.37296e-05 | 3(Loss) | true |
| simdjson (reflection) | 1671.01 | 0.0163792 | 8380.65ms | 500299 | 1280 | 2.79962e+06 | 285529 | 0.0946625 | 3.02418 | 13.5644 | 2.09306 | 0.0119015 | 0.0164459 | 4.76512e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1627.19 | 0.106134 | 8530.78ms | 500299 | 30 | 2.90541e+06 | 293218 | 0.023731 | 3.1063 | 13.065 | 2.05709 | 0.0102065 | 0.0172738 | 3.41129e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12724.7 | 0.0393242 | 4506.86ms | 500299 | 1280 | 278289 | 37495.8 | 0.00895597 | 0.396844 | 1.74934 | 0.301332 | 0.00153552 | 0.0026881 | 2.10952e-05 | 1(Win) | true |
| simdjson (reflection) | 11089.6 | 0.040451 | 5057.4ms | 500299 | 320 | 96924.9 | 43024.3 | 0.085402 | 0.456078 | 2.16983 | 0.197412 | 0.00120039 | 0.000453604 | 1.21677e-05 | 2(Loss) | true |
| glaze | 4993.15 | 0.118416 | 5306.9ms | 500299 | 2560 | 3.2777e+07 | 95555.4 | 0.00473647 | 1.00788 | 3.62395 | 0.527978 | 0.00145077 | 0.0247773 | 1.2719e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12814.1 | 0.0161445 | 4487.39ms | 500299 | 4890 | 176704 | 37234.3 | 0.132187 | 0.394703 | 1.74824 | 0.301082 | 0.00151575 | 0.00220154 | 1.60624e-05 | 1(Win) | true |
| simdjson (reflection) | 11202.3 | 0.0141983 | 4998.36ms | 500299 | 2560 | 93617.5 | 42591.3 | 0.04838 | 0.451455 | 2.16878 | 0.197174 | 0.00118506 | 0.000135959 | 1.73802e-06 | 2(Loss) | true |
| glaze | 5183.24 | 0.518597 | 5175.87ms | 500299 | 320 | 7.29234e+07 | 92050.9 | 0.133453 | 0.97377 | 3.61072 | 0.524932 | 0.00155741 | 0.00284743 | 1.45725e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3678.47 | 0.127687 | 7860.61ms | 1151920 | 320 | 4.65322e+07 | 298645 | 0.0301647 | 1.36708 | 5.92579 | 0.925311 | 0.00579101 | 0.0555677 | 3.76871e-05 | 1(Win) | true |
| jsonifier | 3276.18 | 0.0628668 | 8742.41ms | 1151920 | 160 | 7.11001e+06 | 335316 | 0.018768 | 1.54218 | 6.29103 | 1.39185 | 0.0054682 | 0.0187831 | 2.48335e-05 | 2(Loss) | true |
| simdjson (reflection) | 2952.91 | 0.0401565 | 9714.02ms | 1151920 | 160 | 3.57088e+06 | 372025 | 0.084794 | 1.71099 | 7.13665 | 1.05974 | 0.00765563 | 0.0440279 | 6.31554e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2828.75 | 0.0321162 | 5049.11ms | 1151920 | 640 | 9.95593e+06 | 388354 | 0.0588224 | 1.78173 | 6.93455 | 1.04809 | 0.00730196 | 0.0506045 | 0.000142363 | 4(Loss) | true |
| glaze | 2616.37 | 0.0468119 | 5446.45ms | 1151920 | 160 | 6.18127e+06 | 419878 | 0.391007 | 1.93229 | 8.61645 | 1.63417 | 0.00752058 | 0.0145057 | 4.3205e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4313.5 | 0.0709826 | 7627.72ms | 1151920 | 1280 | 4.18311e+07 | 254679 | 0.274125 | 1.16761 | 5.44095 | 0.808313 | 0.0042479 | 0.047017 | 2.56996e-05 | 1(Win) | true |
| jsonifier | 3747.29 | 0.0247862 | 8540.51ms | 1151920 | 1280 | 6.75835e+06 | 293160 | 0.0756198 | 1.34947 | 5.80404 | 1.27416 | 0.00399792 | 0.0117012 | 2.24483e-05 | 2(Loss) | true |
| simdjson (reflection) | 3415.14 | 0.0378466 | 9258.08ms | 1151920 | 160 | 2.37138e+06 | 321672 | 0.00572432 | 1.47903 | 6.65438 | 0.9421 | 0.00496818 | 0.0349393 | 3.38674e-05 | 3(Loss) | true |
| simdjson (ondemand) | 3335.74 | 0.014544 | 9405.4ms | 1151920 | 1280 | 2.93656e+06 | 329329 | 0.0717724 | 1.51464 | 6.43362 | 0.925505 | 0.00423701 | 0.0354846 | 3.33587e-05 | 4(Loss) | true |
| glaze | 2961.15 | 0.163188 | 5317.19ms | 1151920 | 40 | 1.4661e+07 | 370990 | 0.0698282 | 1.72767 | 8.13695 | 1.51872 | 0.00559238 | 0.00919367 | 5.94876e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20318.3 | 0.0469841 | 7573.04ms | 1439562 | 160 | 161253 | 67568.3 | 0.0213904 | 0.248862 | 0.686887 | 0.104892 | 0.000413264 | 0.0178008 | 4.82786e-06 | 1(Win) | true |
| glaze | 5787.63 | 0.0881663 | 6278.39ms | 1439584 | 1280 | 5.59871e+07 | 237212 | 0.242171 | 0.866228 | 2.99201 | 0.365963 | 0.000651408 | 0.0620913 | 7.67366e-06 | 2(Loss) | true |
| simdjson (reflection) | 548.716 | 0.540035 | 7822.25ms | 1439562 | 160 | 2.92099e+10 | 2.50197e+06 | 0.9451 | 9.11904 | 34.9977 | 6.19663 | 0.0141908 | 0.308853 | 0.0306843 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20358.4 | 0.0327483 | 7568.67ms | 1439562 | 320 | 156064 | 67435.2 | 0.168482 | 0.248391 | 0.686505 | 0.104806 | 0.000416518 | 0.0176246 | 3.57965e-06 | 1(Win) | true |
| glaze | 8037.9 | 0.31476 | 9147.37ms | 1439584 | 80 | 2.31227e+07 | 170803 | 0.0482734 | 0.628644 | 2.98646 | 0.364671 | 0.000652393 | 0.0164886 | 3.11722e-05 | 2(Loss) | true |
| simdjson (reflection) | 549.572 | 1.07359 | 7811.9ms | 1439562 | 40 | 2.87704e+10 | 2.49808e+06 | 0.951226 | 9.13987 | 34.9992 | 6.19719 | 0.0144358 | 0.308127 | 0.0415736 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2385.72 | 0.0147584 | 2987.96ms | 56369 | 2560 | 28311.2 | 22533.1 | 0.0575041 | 2.12226 | 9.30206 | 1.79255 | 0.00100847 | 2.08864e-05 | 1.02214e-05 | 1(Win) | true |
| glaze | 1945.92 | 0.056328 | 3512ms | 56369 | 4890 | 1.1841e+06 | 27625.8 | 0.259411 | 2.6014 | 11.1871 | 2.23621 | 0.00429073 | 2.04974e-05 | 1.02342e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1821.03 | 0.0199597 | 3689.31ms | 56369 | 4890 | 169772 | 29520.5 | 0.0619326 | 2.77443 | 11.9915 | 2.07936 | 0.00513653 | 5.02459e-05 | 2.55982e-05 | 3(Loss) | true |
| simdjson (reflection) | 1575.01 | 0.0159358 | 4160.26ms | 56369 | 4890 | 144667 | 34131.7 | 0.0235034 | 3.22954 | 13.7352 | 2.32948 | 0.00569964 | 6.15104e-05 | 3.98956e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1439.56 | 0.0113635 | 4515.27ms | 56369 | 4890 | 88054 | 37343 | 0.0362281 | 3.51638 | 13.9787 | 2.61816 | 0.0091166 | 2.14443e-05 | 1.05353e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3359.2 | 0.0448561 | 2680.35ms | 56369 | 2560 | 131915 | 16003.1 | 0.0548094 | 1.50889 | 7.32329 | 1.36039 | 0.000581076 | 3.55567e-05 | 2.1018e-05 | 1(Win) | true |
| glaze | 2842.59 | 0.224084 | 2994.26ms | 56369 | 640 | 1.14936e+06 | 18911.5 | 0.221644 | 1.78191 | 8.95852 | 1.7523 | 0.00177192 | 6.65259e-06 | 2.43928e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2448.29 | 0.0288796 | 3287.49ms | 56369 | 2560 | 102938 | 21957.2 | 0.0105592 | 2.06481 | 10.0128 | 1.64772 | 0.00237631 | 9.36907e-06 | 3.13919e-06 | 3(Loss) | true |
| simdjson (reflection) | 1832.31 | 0.0336378 | 4025.63ms | 56369 | 640 | 62332.8 | 29338.7 | 0.0140313 | 2.76564 | 12.2333 | 1.9915 | 0.00386588 | 6.31996e-06 | 1.21964e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1805.57 | 0.126972 | 4078.37ms | 56369 | 30 | 42873.2 | 29773.2 | 0.0412953 | 2.80568 | 11.8281 | 2.16226 | 0.00845086 | 1.47835e-05 | 7.0961e-06 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15106.7 | 0.0252307 | 1094.3ms | 56369 | 4890 | 3941.94 | 3558.53 | 0.101337 | 0.339116 | 1.40519 | 0.223864 | 0.000182648 | 9.16761e-06 | 4.39334e-06 | 1(Win) | true |
| simdjson (reflection) | 11333.4 | 0.105701 | 1222.35ms | 56369 | 160 | 4021.98 | 4743.29 | 0.023987 | 0.450247 | 1.85533 | 0.281928 | 0.000145914 | 4.54594e-06 | 6.65259e-07 | 2(Loss) | true |
| glaze | 6167.33 | 0.0803599 | 1615.46ms | 56369 | 2560 | 125605 | 8716.52 | 0.0134515 | 0.822601 | 3.29202 | 0.477142 | 8.98585e-05 | 1.27092e-05 | 6.04277e-06 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15322.1 | 0.0204442 | 1089.76ms | 56369 | 4890 | 2515.91 | 3508.5 | 0.0101603 | 0.33392 | 1.39541 | 0.221647 | 0.000178828 | 9.34175e-06 | 4.13939e-06 | 1(Win) | true |
| simdjson (reflection) | 11489.3 | 0.0423685 | 1217.6ms | 56369 | 160 | 628.781 | 4678.93 | 0.079949 | 0.444961 | 1.84555 | 0.279675 | 0.000171304 | 3.54805e-06 | 0 | 2(Loss) | true |
| glaze | 6820.47 | 0.115242 | 1533.49ms | 56369 | 2560 | 211209 | 7881.81 | 0.00342474 | 0.744827 | 3.21389 | 0.459579 | 9.36699e-05 | 9.04337e-06 | 3.95691e-06 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2559.09 | 0.0211155 | 3871.47ms | 83958 | 4890 | 213435 | 31287.9 | 0.00659363 | 1.97866 | 8.54737 | 1.4069 | 0.00320489 | 6.99688e-05 | 4.77403e-05 | 1(Win) | true |
| glaze | 2313.73 | 0.061405 | 4222.73ms | 83958 | 640 | 288992 | 34605.8 | 0.124085 | 2.18692 | 10.0154 | 2.06987 | 0.00509727 | 1.68239e-05 | 9.10053e-06 | 2(Loss) | true |
| simdjson (reflection) | 2280.4 | 0.0142468 | 4261.14ms | 83958 | 2560 | 64058 | 35111.6 | 0.00359778 | 2.21927 | 9.69404 | 1.58432 | 0.00340237 | 3.4355e-05 | 2.2956e-05 | 3(Loss) | true |
| jsonifier | 2173.68 | 0.0210513 | 4421.75ms | 83958 | 640 | 38482.8 | 36835.4 | 0.0200807 | 2.32775 | 8.6283 | 1.8427 | 0.00615008 | 1.90013e-05 | 1.0366e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2048.29 | 0.0111516 | 4697.88ms | 83958 | 4890 | 92923.2 | 39090.5 | 0.0641289 | 2.46935 | 9.86499 | 1.77979 | 0.0067778 | 5.2753e-05 | 3.51135e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3328.7 | 0.0732597 | 3545.75ms | 83958 | 320 | 99370.1 | 24054 | 0.129355 | 1.5211 | 7.21511 | 1.11629 | 0.00202467 | 5.69481e-06 | 1.82383e-06 | 1(Win) | true |
| glaze | 3099.88 | 0.0376159 | 3667.81ms | 83958 | 2560 | 241667 | 25829.6 | 0.102011 | 1.63355 | 8.53266 | 1.74847 | 0.00248959 | 4.41999e-06 | 1.24225e-06 | 2(Loss) | true |
| jsonifier | 2762.47 | 0.0281525 | 3983.48ms | 83958 | 4890 | 325590 | 28984.4 | 0.131906 | 1.83925 | 7.29346 | 1.55157 | 0.00385234 | 3.07803e-05 | 2.00631e-05 | 3(Loss) | true |
| simdjson (reflection) | 2615.66 | 0.0195839 | 4205.65ms | 83958 | 1280 | 46001.3 | 30611.2 | 0.000319023 | 1.93567 | 8.6846 | 1.3579 | 0.00275846 | 1.64796e-05 | 1.00404e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2573.76 | 0.0175503 | 4238.22ms | 83958 | 2560 | 76312.9 | 31109.6 | 0.13489 | 1.9663 | 8.41995 | 1.47331 | 0.00570548 | 2.06065e-05 | 1.26319e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20026.9 | 0.0219332 | 1190.39ms | 94370 | 4890 | 4750.64 | 4493.86 | 0.00951594 | 0.255525 | 0.87886 | 0.133687 | 0.000115912 | 1.04102e-05 | 5.38497e-06 | 1(Win) | true |
| glaze | 6033.99 | 0.0371246 | 2238.55ms | 94370 | 4890 | 149931 | 14915.2 | 0.00219957 | 0.838245 | 3.47992 | 0.473212 | 0.00029379 | 8.21073e-06 | 4.28414e-06 | 2(Loss) | true |
| simdjson (reflection) | 541.914 | 0.118476 | 8924.42ms | 94370 | 2560 | 9.91078e+07 | 166075 | 0.137483 | 9.2824 | 37.32 | 7.24163 | 0.0229849 | 0.0216651 | 8.81173e-05 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20265 | 0.0804179 | 1183.73ms | 94370 | 320 | 4081.62 | 4441.08 | 0.0931807 | 0.253225 | 0.873318 | 0.132436 | 0.000117755 | 5.79501e-06 | 3.90749e-06 | 1(Win) | true |
| glaze | 7381.48 | 0.0296125 | 1960.03ms | 94370 | 4890 | 63744.2 | 12192.4 | 0.0360128 | 0.687022 | 3.42499 | 0.460666 | 0.000258962 | 9.24005e-06 | 4.29498e-06 | 2(Loss) | true |
| simdjson (reflection) | 535.947 | 0.114668 | 8993.65ms | 94370 | 2560 | 9.49184e+07 | 167924 | 0.0653059 | 9.39362 | 37.3626 | 7.25003 | 0.0234705 | 0.0255204 | 0.000232827 | 3(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1790.47 | 0.0151954 | 3592.69ms | 53331 | 4890 | 91109 | 28406.2 | 0.0218861 | 2.82648 | 10.3881 | 1.88969 | 0.00184712 | 7.45776e-05 | 4.66815e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1700.45 | 0.0166037 | 3760.97ms | 53331 | 4890 | 120601 | 29909.9 | 0.504976 | 2.97567 | 10.4241 | 1.77521 | 0.000849543 | 0.000145858 | 0.000106987 | 2(Loss) | true |
| jsonifier | 1613.01 | 0.0391267 | 3911.21ms | 53331 | 4890 | 744292 | 31531.4 | 0.0467965 | 3.13704 | 9.65307 | 1.69363 | 0.0140129 | 0.000134408 | 9.15339e-05 | 3(Loss) | true |
| glaze | 1418.6 | 0.0620481 | 4337.53ms | 53331 | 2560 | 1.26689e+06 | 35852.6 | 0.0194279 | 3.56693 | 11.662 | 2.26453 | 0.0207847 | 0.000104148 | 5.58862e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1350 | 0.0325497 | 4521.13ms | 53331 | 2560 | 384972 | 37674.5 | 0.026332 | 3.74693 | 10.5815 | 2.12821 | 0.0116873 | 0.000154145 | 0.000102822 | 5(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2195.64 | 0.0113312 | 3599.69ms | 53331 | 4890 | 33689.7 | 23164.3 | 0.104334 | 2.306 | 8.26645 | 1.29988 | 0.000771445 | 3.39125e-05 | 2.2129e-05 | 1(Win) | true |
| jsonifier | 2181.83 | 0.0575929 | 3669.29ms | 53331 | 2560 | 461420 | 23310.9 | 0.0448909 | 2.32056 | 7.44592 | 1.20663 | 0.0105754 | 4.55147e-05 | 2.84412e-05 | 2(Loss) | true |
| glaze | 1893.36 | 0.0478801 | 4048.53ms | 53331 | 4890 | 808935 | 26862.6 | 0.107075 | 2.6683 | 9.43852 | 1.77275 | 0.0172511 | 4.02817e-05 | 2.07639e-05 | 3(Loss) | true |
| simdjson (reflection) | 1885.65 | 0.0850537 | 4037.75ms | 53331 | 320 | 168412 | 26972.3 | 0.141874 | 2.68478 | 8.47632 | 1.45358 | 0.0109272 | 5.59009e-05 | 3.39859e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1665.6 | 0.0194848 | 4349.89ms | 53331 | 4890 | 173109 | 30535.8 | 0.0808978 | 3.03791 | 8.72698 | 1.7288 | 0.0105388 | 6.67744e-05 | 4.52589e-05 | 5(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14274.9 | 0.11686 | 1135.6ms | 58581 | 1280 | 26773.9 | 3913.67 | 0.123978 | 0.357035 | 1.05712 | 0.170328 | 2.91797e-05 | 6.77214e-05 | 4.72236e-05 | 1(Win) | true |
| simdjson (reflection) | 9512.01 | 0.0374441 | 1336.74ms | 58581 | 4890 | 23650.7 | 5873.33 | 0.274112 | 0.53371 | 1.50165 | 0.22369 | 5.90342e-05 | 2.75814e-05 | 1.44627e-05 | 2(Loss) | true |
| glaze | 7041.06 | 0.120412 | 1541.77ms | 58581 | 2560 | 233676 | 7934.48 | 0.207144 | 0.718503 | 2.52631 | 0.379167 | 4.79971e-05 | 5.74925e-05 | 3.71147e-05 | 3(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14601.2 | 0.121825 | 1130.11ms | 58581 | 160 | 3476.37 | 3826.19 | 0.125783 | 0.349979 | 1.0481 | 0.168297 | 3.43541e-05 | 6.18801e-06 | 1.92042e-06 | 1(Win) | true |
| simdjson (reflection) | 9720.17 | 0.0867942 | 1323.63ms | 58581 | 160 | 3981.69 | 5747.56 | 0.0533638 | 0.523758 | 1.4926 | 0.221625 | 6.45474e-05 | 1.97376e-05 | 9.70878e-06 | 2(Loss) | true |
| glaze | 8190.66 | 0.164226 | 1433.78ms | 58581 | 2560 | 321216 | 6820.84 | 0.0340007 | 0.619078 | 2.45216 | 0.362182 | 3.33072e-05 | 2.06378e-05 | 1.16292e-05 | 3(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2028.36 | 0.0285428 | 3859.75ms | 65103 | 2560 | 195409 | 30609.5 | 0.0531211 | 2.4954 | 8.93113 | 1.46854 | 0.00156123 | 0.000171717 | 2.90345e-05 | 1(Win) | true |
| simdjson (reflection) | 1907.93 | 0.0407431 | 4004.49ms | 65103 | 4890 | 859595 | 32541.6 | 0.0973672 | 2.66047 | 8.71441 | 1.54347 | 0.00883076 | 0.000186221 | 0.000128169 | 2(Loss) | true |
| jsonifier | 1771.56 | 0.0467703 | 4240.26ms | 65103 | 160 | 42988.1 | 35046.4 | 0.0481379 | 2.85721 | 9.00878 | 1.67445 | 0.00110959 | 2.19844e-05 | 1.10402e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1650.13 | 0.0522103 | 4519.9ms | 65103 | 1280 | 493954 | 37625.5 | 0.113982 | 3.066 | 8.90587 | 1.74745 | 0.00815503 | 7.08493e-05 | 4.15087e-05 | 4(Loss) | true |
| glaze | 1540.79 | 0.0433779 | 4769.21ms | 65103 | 4890 | 1.49404e+06 | 40295.7 | 0.165045 | 3.28333 | 10.8569 | 2.1126 | 0.0173104 | 0.000285038 | 0.000142357 | 5(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2629.52 | 0.0567542 | 3636.1ms | 65103 | 160 | 28732 | 23611.5 | 0.00381155 | 1.92564 | 7.16159 | 1.07881 | 0.000663756 | 2.64005e-05 | 1.58403e-05 | 1(Win) | true |
| simdjson (reflection) | 2243.75 | 0.0490699 | 4096.69ms | 65103 | 1280 | 235990 | 27671.1 | 0.06866 | 2.2561 | 7.21784 | 1.20553 | 0.00898449 | 7.38853e-05 | 4.13287e-05 | 2(Loss) | true |
| jsonifier | 2215.52 | 0.0188232 | 3991.95ms | 65103 | 1280 | 35615.9 | 28023.6 | 0.00116811 | 2.28586 | 7.21929 | 1.27988 | 0.000760922 | 3.68647e-05 | 2.33644e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2005.03 | 0.0382643 | 4398.25ms | 65103 | 1280 | 179705 | 30965.7 | 0.00546502 | 2.52409 | 7.43979 | 1.43392 | 0.0086516 | 2.30884e-05 | 1.12922e-05 | 4(Loss) | true |
| glaze | 1989.08 | 0.060915 | 4482.18ms | 65103 | 2560 | 925518 | 31213.9 | 0.0836753 | 2.54405 | 9.06094 | 1.71706 | 0.0137583 | 4.36688e-05 | 2.81945e-05 | 5(Loss) | true |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17780.5 | 0.0438059 | 1163.44ms | 78778 | 2560 | 8770.59 | 4225.34 | 0.0236353 | 0.28682 | 0.831442 | 0.126623 | 3.00141e-05 | 1.89764e-05 | 1.11716e-05 | 1(Win) | true |
| glaze | 5120.73 | 0.103509 | 2216.03ms | 78778 | 2560 | 590390 | 14671.5 | 0.0339582 | 0.9878 | 2.81888 | 0.386237 | 8.52376e-05 | 2.57597e-05 | 1.31352e-05 | 2(Loss) | true |
| simdjson (reflection) | 608.071 | 0.0869175 | 6738.02ms | 78778 | 2560 | 2.95228e+07 | 123552 | 0.162938 | 8.25632 | 29.0429 | 6.17574 | 0.0446946 | 0.00321057 | 0.000120602 | 3(Loss) | true |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18185.8 | 0.0352301 | 1155.49ms | 78778 | 4890 | 10358.1 | 4131.16 | 0.0183473 | 0.2803 | 0.824941 | 0.12515 | 3.04498e-05 | 1.15725e-05 | 5.29561e-06 | 1(Win) | true |
| glaze | 6117.03 | 0.112886 | 1981.26ms | 78778 | 2560 | 492092 | 12281.9 | 0.0935051 | 0.826701 | 2.75515 | 0.371665 | 5.55904e-05 | 9.7386e-06 | 4.20485e-06 | 2(Loss) | true |
| simdjson (reflection) | 606.609 | 0.102219 | 6729.21ms | 78778 | 2560 | 4.10298e+07 | 123850 | 0.11891 | 8.27057 | 29.0444 | 6.17613 | 0.0446213 | 0.00218653 | 0.000131972 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2638.36 | 0.0236864 | 1164.25ms | 11812 | 4890 | 5001.33 | 4269.62 | 0.0168131 | 1.92882 | 9.45936 | 1.61116 | 0.000827535 | 2.94145e-05 | 5.71323e-06 | 1(Win) | true |
| glaze | 1985.75 | 0.0225882 | 1305.13ms | 11812 | 2560 | 4203.41 | 5672.81 | 0.0343283 | 2.56399 | 12.9272 | 2.46991 | 0.00170077 | 3.94197e-05 | 9.95413e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1932.48 | 0.0181641 | 1323.01ms | 11812 | 4890 | 5482.16 | 5829.18 | 0.163063 | 2.63372 | 12.8281 | 2.06553 | 0.00383761 | 4.61906e-05 | 1.64299e-05 | 3(Loss) | true |
| simdjson (reflection) | 1280.87 | 0.120666 | 1775.01ms | 11812 | 40 | 4504.74 | 8794.67 | 0.0608899 | 3.96682 | 14.731 | 2.45039 | 0.00923849 | 5.50288e-05 | 1.2699e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1060.02 | 0.0560582 | 1807.7ms | 11812 | 1280 | 45426.6 | 10627 | 0.0399985 | 4.78496 | 15.9334 | 2.74104 | 0.00801211 | 5.29123e-05 | 2.10326e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3041.37 | 0.0299182 | 1154.45ms | 11812 | 4890 | 6004.66 | 3703.86 | 0.158912 | 1.6774 | 8.62504 | 1.41593 | 0.000333653 | 3.03147e-05 | 6.11142e-06 | 1(Win) | true |
| glaze | 2247.47 | 0.025852 | 1289.98ms | 11812 | 4890 | 8210.24 | 5012.21 | 0.0447404 | 2.26432 | 11.935 | 2.24323 | 0.000963926 | 2.38571e-05 | 7.25407e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2120.56 | 0.0230099 | 1320.43ms | 11812 | 4890 | 7306.1 | 5312.19 | 0.109026 | 2.40302 | 11.9926 | 1.87056 | 0.00382135 | 4.40957e-05 | 2.07581e-05 | 3(Loss) | true |
| simdjson (reflection) | 1355.39 | 0.016002 | 1625.56ms | 11812 | 4890 | 8649.19 | 8311.11 | 0.0113323 | 3.74842 | 14.2073 | 2.32729 | 0.00832528 | 4.26934e-05 | 2.09658e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1152.32 | 0.0493399 | 1775.77ms | 11812 | 640 | 14889.3 | 9775.72 | 0.0224198 | 4.40449 | 15.1271 | 2.5618 | 0.00685135 | 1.87839e-05 | 2.51333e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16275.3 | 0.0666053 | 803.846ms | 11812 | 2560 | 544.063 | 692.143 | 0.000903001 | 0.328932 | 1.59313 | 0.252878 | 8.50565e-05 | 2.23224e-05 | 8.56518e-06 | 1(Win) | true |
| simdjson (reflection) | 10097 | 0.0936687 | 845.692ms | 11812 | 1280 | 1397.86 | 1115.66 | 0.134758 | 0.518905 | 2.44489 | 0.347782 | 0.000115481 | 2.57286e-05 | 2.91018e-06 | 2(Loss) | true |
| glaze | 4003.97 | 0.161149 | 1022.19ms | 11812 | 2560 | 52621.1 | 2813.41 | 0.239873 | 1.28078 | 4.55427 | 0.719099 | 8.63132e-05 | 4.11724e-05 | 1.29635e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17762.7 | 0.0826175 | 795.421ms | 11812 | 160 | 43.9229 | 634.181 | 0.0404228 | 0.303164 | 1.54749 | 0.242127 | 8.46597e-05 | 4.76211e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 10312.5 | 0.0578833 | 841.499ms | 11812 | 1280 | 511.727 | 1092.35 | 0.138985 | 0.508578 | 2.40222 | 0.337961 | 9.9872e-05 | 1.63367e-05 | 2.97632e-06 | 2(Loss) | true |
| glaze | 4504.94 | 0.158289 | 985.342ms | 11812 | 4890 | 76608.9 | 2500.54 | 0.0218934 | 1.14081 | 4.28989 | 0.660771 | 8.93341e-05 | 2.23335e-05 | 6.30186e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3547.06 | 0.11068 | 1424.74ms | 25388 | 40 | 2283.07 | 6825.9 | 0.0151361 | 1.43425 | 6.75762 | 1.43068 | 0.00291575 | 2.06791e-05 | 1.28013e-05 | 1(Win) | true |
| jsonifier (two-stage) | 3506.48 | 0.0285 | 1433.2ms | 25388 | 2560 | 9913.93 | 6904.9 | 0.0219039 | 1.44718 | 6.78078 | 1.0115 | 0.00212936 | 1.33398e-05 | 4.04657e-06 | 2(Loss) | true |
| simdjson (reflection) | 2524.11 | 0.0599539 | 1698.97ms | 25388 | 320 | 10583.4 | 9592.24 | 0.0927949 | 2.0107 | 7.58386 | 1.17522 | 0.00432697 | 5.60058e-05 | 3.45882e-05 | 3(Loss) | true |
| glaze | 2483.49 | 0.0183817 | 1715.2ms | 25388 | 4890 | 15704.1 | 9749.12 | 0.147865 | 2.04209 | 9.47832 | 1.75985 | 0.00554959 | 2.11201e-05 | 5.69485e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2120.73 | 0.027644 | 1887.22ms | 25388 | 4890 | 48707.5 | 11416.8 | 0.0530093 | 2.39159 | 8.13543 | 1.30855 | 0.00373832 | 2.23041e-05 | 1.0415e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3813.74 | 0.0362894 | 1429.15ms | 25388 | 1280 | 6793.98 | 6348.59 | 0.123779 | 1.3344 | 6.37856 | 1.34225 | 0.00275647 | 1.1355e-05 | 3.78501e-06 | 1(Win) | true |
| jsonifier (two-stage) | 3792.41 | 0.0208789 | 1429.75ms | 25388 | 4890 | 8688.61 | 6384.3 | 0.00508539 | 1.34158 | 6.40133 | 0.923074 | 0.00194135 | 1.47325e-05 | 6.93531e-06 | 2(Loss) | true |
| simdjson (reflection) | 2678.26 | 0.0336794 | 1701.38ms | 25388 | 1280 | 11865.7 | 9040.17 | 0.0581425 | 1.89587 | 7.31996 | 1.1134 | 0.00383594 | 1.59093e-05 | 4.8005e-06 | 3(Loss) | true |
| glaze | 2665.87 | 0.0375853 | 1698.83ms | 25388 | 1280 | 14915 | 9082.16 | 0.0307944 | 1.90418 | 9.00457 | 1.65224 | 0.00512819 | 2.20023e-05 | 8.86245e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2294.28 | 0.0187483 | 1853.23ms | 25388 | 4890 | 19142.4 | 10553.1 | 0.0415371 | 2.21196 | 7.7413 | 1.22133 | 0.00320038 | 2.28922e-05 | 1.25013e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20848.3 | 0.0331777 | 879.366ms | 31235 | 4890 | 1098.86 | 1428.8 | 0.0134921 | 0.249369 | 0.66195 | 0.095854 | 3.21201e-05 | 5.88585e-06 | 1.44691e-06 | 1(Win) | true |
| glaze | 6756.6 | 0.056023 | 1184.35ms | 31235 | 4890 | 29831.1 | 4408.73 | 0.0266247 | 0.756362 | 3.60314 | 0.476869 | 0.000147447 | 1.40763e-05 | 5.97096e-06 | 2(Loss) | true |
| simdjson (reflection) | 530.001 | 0.147175 | 6377.72ms | 31235 | 2560 | 1.75161e+07 | 56203.7 | 0.113249 | 9.48878 | 37.266 | 6.86663 | 0.012006 | 8.86551e-05 | 4.91736e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22053 | 0.0503272 | 869.421ms | 31235 | 1280 | 591.512 | 1350.75 | 0.0736246 | 0.236261 | 0.643413 | 0.091564 | 3.21404e-05 | 1.10053e-06 | 2.5012e-08 | 1(Win) | true |
| glaze | 7541.16 | 0.233299 | 1155.36ms | 31235 | 640 | 54351.5 | 3950.06 | 0.0950032 | 0.677459 | 3.48362 | 0.450424 | 0.000180737 | 6.30303e-06 | 6.00288e-07 | 2(Loss) | true |
| simdjson (reflection) | 526.341 | 0.162434 | 6393.87ms | 31235 | 4890 | 4.13247e+07 | 56594.5 | 0.12131 | 9.49534 | 37.3244 | 6.88302 | 0.0115666 | 0.00021684 | 0.000127806 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3283.18 | 0.0485329 | 3903.14ms | 108313 | 320 | 74609.4 | 31461.9 | 0.0305919 | 1.5405 | 7.04549 | 1.4703 | 0.00223914 | 1.77149e-05 | 9.05939e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2240.21 | 0.017109 | 5360.17ms | 108313 | 2560 | 159321 | 46109.7 | 0.0238576 | 2.2545 | 9.93282 | 1.78504 | 0.00268919 | 1.81404e-05 | 1.08554e-05 | 2(Loss) | true |
| glaze | 2125.82 | 0.0314303 | 5617.45ms | 108313 | 2560 | 597093 | 48590.7 | 0.214022 | 2.37262 | 10.1465 | 1.90883 | 0.00301532 | 3.27357e-05 | 2.11338e-05 | 3(Loss) | true |
| simdjson (reflection) | 1842.45 | 0.0509956 | 6360.9ms | 108313 | 160 | 130784 | 56064 | 0.00647739 | 2.74435 | 12.8272 | 1.94517 | 0.00244788 | 9.98264e-06 | 5.5395e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1391.11 | 0.0169475 | 8159.62ms | 108313 | 640 | 101352 | 74253.8 | 0.0033943 | 3.63414 | 14.3935 | 2.45339 | 0.00322488 | 1.06462e-05 | 5.04902e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3898.3 | 0.0168788 | 3574.42ms | 108313 | 2560 | 51207.5 | 26497.5 | 0.0402543 | 1.29815 | 6.35334 | 1.32282 | 0.00199331 | 1.10682e-05 | 4.57658e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2517.58 | 0.0463065 | 5027.71ms | 108313 | 160 | 57756.4 | 41029.7 | 0.0488605 | 2.0094 | 9.24017 | 1.6376 | 0.00267489 | 3.51989e-06 | 1.26947e-06 | 2(Loss) | true |
| glaze | 2359.28 | 0.0831939 | 5317.59ms | 108313 | 320 | 424556 | 43782.5 | 0.0212654 | 2.14326 | 9.50251 | 1.7715 | 0.0028235 | 8.39581e-06 | 3.7507e-06 | 3(Loss) | true |
| simdjson (reflection) | 1901.13 | 0.0232278 | 6365.22ms | 108313 | 640 | 101937 | 54333.5 | 0.124781 | 2.66059 | 12.5476 | 1.87949 | 0.00254839 | 7.86205e-06 | 3.64972e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1477.25 | 0.00880691 | 7935.44ms | 108313 | 4890 | 185443 | 69924.2 | 0.0508628 | 3.4252 | 13.803 | 2.33059 | 0.00320595 | 1.28821e-05 | 7.42565e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20038.5 | 0.0366726 | 1255.67ms | 108313 | 1280 | 4574.29 | 5154.83 | 0.00766936 | 0.254267 | 1.057 | 0.286715 | 0.00011405 | 9.1171e-06 | 5.5395e-06 | 1(Win) | true |
| simdjson (reflection) | 15682.4 | 0.03439 | 1400.77ms | 108313 | 2560 | 13135.3 | 6586.71 | 0.0177053 | 0.324438 | 1.49029 | 0.193753 | 0.00017254 | 6.16342e-06 | 3.18089e-06 | 2(Loss) | true |
| glaze | 5664.15 | 0.266715 | 2602.71ms | 108313 | 160 | 378536 | 18236.7 | 0.238963 | 0.895567 | 2.9887 | 0.385079 | 0.000219157 | 3.28908e-06 | 1.44258e-06 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20253.1 | 0.0197621 | 1249.12ms | 108313 | 4890 | 4967.68 | 5100.22 | 0.0121382 | 0.251612 | 1.05227 | 0.285644 | 0.000111151 | 7.2765e-06 | 2.99632e-06 | 1(Win) | true |
| simdjson (reflection) | 15380.9 | 0.044667 | 1414.51ms | 108313 | 1280 | 11518.1 | 6715.82 | 0.0127281 | 0.330567 | 1.48547 | 0.192664 | 0.000191358 | 7.50862e-06 | 4.32774e-06 | 2(Loss) | true |
| glaze | 6666.14 | 0.0582439 | 2293.45ms | 108313 | 4890 | 398310 | 15495.5 | 0.181298 | 0.759764 | 2.94418 | 0.37484 | 0.000179022 | 1.06806e-05 | 5.62446e-06 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3386.13 | 0.0995209 | 5956.83ms | 183677 | 30 | 79515.7 | 51731.1 | 0.0891297 | 1.49363 | 6.58322 | 1.09992 | 0.00171624 | 5.93433e-05 | 4.15585e-05 | 1(Win) | true |
| jsonifier | 3001.56 | 0.0212002 | 6604.34ms | 183677 | 2560 | 391864 | 58359.1 | 0.0378333 | 1.68329 | 6.67899 | 1.54341 | 0.00270575 | 1.77877e-05 | 1.11822e-05 | 2(Loss) | true |
| simdjson (reflection) | 2954.44 | 0.0249188 | 6706.73ms | 183677 | 320 | 69849.5 | 59289.7 | 0.241531 | 1.71155 | 8.12684 | 1.16531 | 0.00125016 | 3.02841e-06 | 1.02081e-06 | 3(Loss) | true |
| glaze | 2606.94 | 0.0661601 | 7495.48ms | 183677 | 320 | 632395 | 67192.9 | 0.114297 | 1.94167 | 8.99291 | 1.73315 | 0.00238603 | 2.03652e-05 | 1.32536e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2256.06 | 0.0439492 | 8566.97ms | 183677 | 80 | 93153.7 | 77643.3 | 0.0269751 | 2.24126 | 9.06213 | 1.46726 | 0.00183678 | 4.83185e-06 | 1.15692e-06 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3785.27 | 0.0651018 | 5543.69ms | 183677 | 4890 | 4.43825e+06 | 46276.3 | 0.167786 | 1.33304 | 6.17524 | 1.01305 | 0.00159311 | 1.1992e-05 | 7.78129e-06 | 1(Win) | true |
| jsonifier | 3309.63 | 0.095329 | 6257.33ms | 183677 | 30 | 76370 | 52926.8 | 0.0531269 | 1.52747 | 6.27141 | 1.45656 | 0.00243906 | 9.0739e-06 | 5.62582e-06 | 2(Loss) | true |
| simdjson (reflection) | 3001.57 | 0.0209716 | 6765.35ms | 183677 | 2560 | 383457 | 58358.8 | 0.0941979 | 1.68434 | 7.99025 | 1.13281 | 0.0016308 | 1.16713e-05 | 6.71823e-06 | 3(Loss) | true |
| glaze | 2805.82 | 0.064909 | 7173.82ms | 183677 | 320 | 525470 | 62430.2 | 0.00385445 | 1.80259 | 8.6147 | 1.65319 | 0.00215165 | 1.16203e-05 | 7.38389e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2364.24 | 0.048758 | 8313.28ms | 183677 | 4890 | 6.38156e+06 | 74090.6 | 0.140695 | 2.13428 | 8.72251 | 1.39731 | 0.00176154 | 4.5139e-05 | 2.94351e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 25924.1 | 0.0758387 | 1547.68ms | 213963 | 30 | 1068.99 | 7871.1 | 0.0338677 | 0.196092 | 0.61169 | 0.145142 | 5.70192e-05 | 4.67371e-07 | 4.67371e-07 | 1(Win) | true |
| glaze | 6099.21 | 0.12991 | 4092.96ms | 213963 | 640 | 1.20891e+06 | 33455.3 | 0.0406021 | 0.829754 | 3.23303 | 0.398396 | 0.000399397 | 4.47653e-06 | 1.73803e-06 | 2(Loss) | true |
| simdjson (reflection) | 498.118 | 0.225506 | 5317.38ms | 213963 | 640 | 5.46146e+08 | 409644 | 0.191253 | 10.063 | 39.7918 | 7.78685 | 0.0226583 | 0.208899 | 0.000151917 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 25956.3 | 0.0806676 | 1526.04ms | 213963 | 160 | 6434.45 | 7861.34 | 0.0362665 | 0.195733 | 0.609292 | 0.1446 | 5.4361e-05 | 1.57738e-06 | 2.04475e-07 | 1(Win) | true |
| glaze | 7259.31 | 0.0573511 | 3553.95ms | 213963 | 4890 | 1.27081e+06 | 28108.9 | 0.0798177 | 0.696769 | 3.20589 | 0.392213 | 0.000386409 | 6.54414e-06 | 3.72272e-06 | 2(Loss) | true |
| simdjson (reflection) | 494.603 | 0.223465 | 5324.52ms | 213963 | 640 | 5.43958e+08 | 412556 | 0.0398465 | 10.1254 | 39.7917 | 7.78685 | 0.0220874 | 0.212813 | 0.000131214 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 738.956 | 0.0881152 | 7400.6ms | 1834197 | 80 | 3.48054e+08 | 2.36716e+06 | 0.471618 | 6.80097 | 29.668 | 6.01861 | 0.0353931 | 0.145493 | 8.9944e-05 | 1(Win) | true |
| jsonifier | 734.436 | 0.0774025 | 7420.02ms | 1834197 | 80 | 2.71885e+08 | 2.38173e+06 | 0.0501076 | 6.86584 | 25.7933 | 5.46181 | 0.0421961 | 0.0821666 | 3.26233e-05 | 2(Loss) | true |
| simdjson (reflection) | 712.967 | 0.0463296 | 7649.03ms | 1834197 | 160 | 2.06724e+08 | 2.45345e+06 | 0.0957746 | 7.08531 | 30.9074 | 5.23583 | 0.0370994 | 0.13628 | 0.000272841 | 3(Loss) | true |
| glaze | 644.142 | 0.106164 | 8459.26ms | 1834197 | 160 | 1.32985e+09 | 2.71559e+06 | 0.0174219 | 7.79734 | 31.9267 | 6.36332 | 0.0341733 | 0.0827852 | 0.00345513 | 4(Loss) | true |
| simdjson (ondemand) | 612.894 | 0.0496116 | 8880.34ms | 1834197 | 160 | 3.2078e+08 | 2.85404e+06 | 0.133106 | 8.22703 | 33.554 | 6.11037 | 0.0442842 | 0.147471 | 0.00277541 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 812.152 | 0.14881 | 7437.22ms | 1834197 | 30 | 3.08181e+08 | 2.15382e+06 | 0.132548 | 6.19066 | 26.6644 | 5.31921 | 0.0344082 | 0.118823 | 0.000740796 | 1(Win) | true |
| jsonifier | 802.863 | 0.156205 | 7437.19ms | 1834197 | 30 | 3.47474e+08 | 2.17874e+06 | 0.136974 | 6.29068 | 22.7906 | 4.763 | 0.0412863 | 0.0555385 | 8.3706e-05 | 2(Loss) | true |
| simdjson (reflection) | 797.428 | 0.055309 | 7469.53ms | 1834197 | 80 | 1.17758e+08 | 2.19358e+06 | 0.00919128 | 6.32755 | 27.8771 | 4.51905 | 0.0320704 | 0.111887 | 0.000385523 | 3(Loss) | true |
| glaze | 706.256 | 0.0614132 | 8423.16ms | 1834197 | 80 | 1.8509e+08 | 2.47676e+06 | 0.0813299 | 7.14882 | 28.9184 | 5.66275 | 0.0326723 | 0.0587962 | 0.00211227 | 4(Loss) | true |
| simdjson (ondemand) | 674.826 | 0.123816 | 8806.47ms | 1834197 | 30 | 3.09016e+08 | 2.59211e+06 | 0.0822567 | 7.48034 | 30.5355 | 5.40954 | 0.039446 | 0.118322 | 0.00153159 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1298.79 | 0.137845 | 8597.89ms | 1834197 | 30 | 1.03399e+08 | 1.34682e+06 | 0.0078141 | 3.92188 | 12.2502 | 0.788676 | 0.00269644 | 0.059993 | 0.000262567 | 1(Win) | true |
| glaze | 973.552 | 0.176988 | 5591.35ms | 1833577 | 160 | 1.61692e+09 | 1.79614e+06 | 0.264459 | 5.18636 | 15.8119 | 1.0202 | 0.000951358 | 0.0496957 | 0.000293109 | 2(Loss) | true |
| simdjson (reflection) | 880.392 | 0.0160175 | 6495.07ms | 1922245 | 160 | 1.77981e+07 | 2.08225e+06 | 0.00944141 | 5.73577 | 18.1209 | 2.02074 | 0.027312 | 0.0508684 | 6.13801e-05 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1280.41 | 0.0661932 | 8652.71ms | 1834197 | 80 | 6.54199e+07 | 1.36614e+06 | 0.0539421 | 3.94579 | 12.25 | 0.788637 | 0.00271948 | 0.0599551 | 0.000779674 | 1(Win) | true |
| glaze | 976.728 | 0.16189 | 5573.52ms | 1833577 | 80 | 6.72017e+08 | 1.7903e+06 | 0.0868206 | 5.16974 | 15.8112 | 1.02006 | 0.000945427 | 0.0495399 | 0.000468115 | 2(Loss) | true |
| simdjson (reflection) | 881.022 | 0.0156056 | 6483.24ms | 1922245 | 30 | 3.16321e+06 | 2.08076e+06 | 0.00474324 | 5.73338 | 18.1207 | 2.0207 | 0.0272798 | 0.0506739 | 5.6271e-05 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2579.38 | 0.141622 | 8426.06ms | 7351818 | 40 | 5.92757e+08 | 2.71819e+06 | 0.0037646 | 1.93218 | 8.29871 | 1.53771 | 0.0102988 | 0.0612893 | 9.96828e-05 | 1(Win) | true |
| simdjson (reflection) | 2542.73 | 0.0415768 | 8607.96ms | 7351818 | 160 | 2.10286e+08 | 2.75737e+06 | 0.0213204 | 1.98538 | 8.72668 | 1.34398 | 0.00909016 | 0.0586851 | 5.46821e-05 | 2(Loss) | true |
| jsonifier | 2411.44 | 0.078859 | 9049.89ms | 7351818 | 160 | 8.41122e+08 | 2.90749e+06 | 0.15686 | 2.0846 | 8.84542 | 2.03739 | 0.0105741 | 0.0342001 | 0.00145489 | 3(Loss) | true |
| simdjson (ondemand) | 2218.33 | 0.115034 | 9810.92ms | 7351818 | 80 | 1.0575e+09 | 3.1606e+06 | 0.0344053 | 2.27423 | 9.38724 | 1.56225 | 0.0109036 | 0.0615311 | 0.000191757 | 4(Loss) | true |
| glaze | 2032.81 | 0.0725215 | 5186.4ms | 7351818 | 30 | 1.87694e+08 | 3.44904e+06 | 0.392736 | 2.48392 | 11.3971 | 2.27935 | 0.00926506 | 0.033687 | 0.000248143 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2840.42 | 0.0809413 | 8371.04ms | 7351818 | 80 | 3.1934e+08 | 2.46838e+06 | 0.0308903 | 1.77624 | 7.5492 | 1.36321 | 0.0100241 | 0.0546218 | 0.000127943 | 1(Win) | true |
| simdjson (reflection) | 2809.34 | 0.0470177 | 8363.43ms | 7351818 | 160 | 2.20304e+08 | 2.49569e+06 | 0.0747921 | 1.79538 | 7.97105 | 1.16527 | 0.00793444 | 0.0520713 | 0.000127511 | 2(Loss) | true |
| jsonifier | 2592.19 | 0.0807419 | 9081.57ms | 7351818 | 160 | 7.63088e+08 | 2.70476e+06 | 0.126953 | 1.93954 | 8.09611 | 1.86295 | 0.0103971 | 0.0274039 | 0.00128261 | 3(Loss) | true |
| simdjson (ondemand) | 2430.7 | 0.0744568 | 9794.27ms | 7351818 | 40 | 1.845e+08 | 2.88445e+06 | 0.134914 | 2.07571 | 8.63364 | 1.3872 | 0.00969015 | 0.0538736 | 0.000195805 | 4(Loss) | true |
| glaze | 2191.08 | 0.0625783 | 5161.37ms | 7351818 | 80 | 3.20784e+08 | 3.19991e+06 | 0.00248881 | 2.29727 | 10.6467 | 2.10461 | 0.00895931 | 0.0276496 | 0.000131607 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6400.18 | 0.026514 | 9389.69ms | 9930848 | 320 | 4.92594e+07 | 1.47977e+06 | 0.0157683 | 0.787852 | 2.34768 | 0.147548 | 0.000401107 | 0.0249875 | 8.34732e-05 | 1(Win) | true |
| glaze | 3694.69 | 0.12131 | 8003.36ms | 9930228 | 80 | 7.73476e+08 | 2.56319e+06 | 0.0614299 | 1.36656 | 4.43038 | 0.41539 | 0.000764789 | 0.0417594 | 0.000732225 | 2(Loss) | true |
| simdjson (reflection) | 269.811 | 0.242448 | 10579ms | 10018896 | 30 | 2.21147e+11 | 3.54129e+07 | 0.845082 | 13.8958 | 38.5448 | 5.73337 | 0.0261148 | 0.270248 | 0.122818 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6402.99 | 0.0836126 | 9377.82ms | 9930848 | 30 | 4.58851e+07 | 1.47912e+06 | 0.00929295 | 0.787987 | 2.34764 | 0.147541 | 0.000391853 | 0.0249737 | 0.000131083 | 1(Win) | true |
| glaze | 4073.15 | 0.107495 | 7271.44ms | 9930228 | 40 | 2.49857e+08 | 2.32503e+06 | 0.136964 | 1.24007 | 4.43014 | 0.415337 | 0.000759227 | 0.0224909 | 7.88778e-05 | 2(Loss) | true |
| simdjson (reflection) | 304.66 | 1.68019 | 9417ms | 10018896 | 30 | 8.33008e+12 | 3.1362e+07 | 0.5374 | 13.4687 | 38.4969 | 5.72673 | 0.0255627 | 0.291854 | 0.126644 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 745.834 | 0.158913 | 7361.48ms | 1834197 | 30 | 4.16725e+08 | 2.34533e+06 | 0.254205 | 6.73781 | 29.2887 | 5.91362 | 0.0359014 | 0.147321 | 0.000145659 | 1(Win) | true |
| jsonifier | 738.756 | 0.292159 | 7365.58ms | 1834197 | 30 | 1.43566e+09 | 2.3678e+06 | 0.0985752 | 6.82984 | 25.3768 | 5.32233 | 0.0429184 | 0.0838349 | 0.000645968 | 2(Loss) | true |
| simdjson (reflection) | 687.97 | 0.106329 | 7874.03ms | 1834197 | 30 | 2.1927e+08 | 2.54259e+06 | 0.124589 | 7.20857 | 30.8321 | 5.24271 | 0.0389831 | 0.137366 | 0.000113274 | 3(Loss) | true |
| glaze | 646.454 | 0.121299 | 8432.1ms | 1834197 | 30 | 3.23187e+08 | 2.70588e+06 | 0.211587 | 7.79466 | 31.7432 | 6.35383 | 0.0343398 | 0.0834146 | 0.000978194 | 4(Loss) | true |
| simdjson (ondemand) | 610.284 | 0.0665136 | 8917.6ms | 1834197 | 160 | 5.81526e+08 | 2.86625e+06 | 0.084336 | 8.27156 | 33.5189 | 6.1 | 0.0446645 | 0.148794 | 0.00188667 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 828.311 | 0.0734207 | 7353.1ms | 1834197 | 160 | 3.84647e+08 | 2.1118e+06 | 0.201547 | 6.08635 | 26.3138 | 5.22442 | 0.035003 | 0.120956 | 0.000552084 | 1(Win) | true |
| jsonifier | 820.819 | 0.0652893 | 7347.97ms | 1834197 | 160 | 3.09742e+08 | 2.13107e+06 | 0.0513023 | 6.15524 | 22.4022 | 4.63336 | 0.0419839 | 0.056834 | 0.00102312 | 2(Loss) | true |
| simdjson (reflection) | 791.525 | 0.0348804 | 7571.02ms | 1834197 | 160 | 9.50705e+07 | 2.20994e+06 | 0.0768566 | 6.37618 | 27.8203 | 4.53916 | 0.0334302 | 0.112318 | 0.000817108 | 3(Loss) | true |
| glaze | 702.769 | 0.208434 | 8504.47ms | 1834197 | 80 | 2.15324e+09 | 2.48905e+06 | 0.0298592 | 7.16776 | 28.766 | 5.66322 | 0.0333379 | 0.0595856 | 0.000108999 | 4(Loss) | true |
| simdjson (ondemand) | 667.299 | 0.14459 | 8908.81ms | 1834197 | 40 | 5.74632e+08 | 2.62135e+06 | 0.173193 | 7.46587 | 30.5294 | 5.40841 | 0.0397498 | 0.119268 | 0.000221705 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1301.5 | 0.0462808 | 8537.84ms | 1834197 | 160 | 6.1905e+07 | 1.34401e+06 | 0.00322553 | 3.87676 | 12.2999 | 0.788835 | 0.00280498 | 0.0618842 | 5.03183e-05 | 1(Win) | true |
| glaze | 924.096 | 0.337365 | 5894.05ms | 1833577 | 160 | 6.52055e+09 | 1.89226e+06 | 0.113498 | 5.43398 | 15.8271 | 1.02027 | 0.000968926 | 0.0835224 | 0.000605875 | 2(Loss) | true |
| simdjson (reflection) | 880.176 | 0.15273 | 6503.05ms | 1922245 | 30 | 3.03563e+08 | 2.08276e+06 | 0.125322 | 5.69811 | 18.1187 | 2.02075 | 0.0256333 | 0.0524263 | 0.000128045 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1302.21 | 0.0580137 | 8563.46ms | 1834197 | 40 | 2.42914e+07 | 1.34328e+06 | 0.106091 | 3.87782 | 12.2997 | 0.788796 | 0.00280003 | 0.0616153 | 0.000247547 | 1(Win) | true |
| glaze | 975.747 | 0.418251 | 5619.63ms | 1833577 | 80 | 4.49456e+09 | 1.7921e+06 | 0.0235087 | 5.17081 | 15.8262 | 1.02006 | 0.000951099 | 0.0497445 | 6.88068e-05 | 2(Loss) | true |
| simdjson (reflection) | 880.002 | 0.135383 | 6513.68ms | 1922245 | 30 | 2.38615e+08 | 2.08317e+06 | 0.0876483 | 5.70233 | 18.1185 | 2.02071 | 0.0256347 | 0.0525472 | 0.000179738 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2592.9 | 0.0841774 | 8477.28ms | 7351818 | 160 | 8.28952e+08 | 2.70402e+06 | 0.379466 | 1.92748 | 8.20401 | 1.51156 | 0.0104237 | 0.0616772 | 0.00155937 | 1(Win) | true |
| simdjson (reflection) | 2494.56 | 0.0879511 | 8821.05ms | 7351818 | 30 | 1.83319e+08 | 2.81062e+06 | 0.0752073 | 2.01913 | 8.70801 | 1.34576 | 0.00954848 | 0.0587707 | 0.000595073 | 2(Loss) | true |
| jsonifier | 2421.04 | 0.191328 | 9064.61ms | 7351818 | 30 | 9.21004e+08 | 2.89596e+06 | 0.06127 | 2.05333 | 8.74485 | 2.00866 | 0.0108273 | 0.0346221 | 0.000657579 | 3(Loss) | true |
| simdjson (ondemand) | 2187.16 | 0.0774185 | 9957.26ms | 7351818 | 160 | 9.85457e+08 | 3.20563e+06 | 0.115357 | 2.29327 | 9.37869 | 1.5597 | 0.0109629 | 0.0614995 | 0.000988293 | 4(Loss) | true |
| glaze | 2005.51 | 0.157667 | 5247.83ms | 7351818 | 30 | 9.11465e+08 | 3.49598e+06 | 0.0687859 | 2.50143 | 11.3893 | 2.27669 | 0.00943364 | 0.0340042 | 0.000420295 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2843.34 | 0.0968934 | 8404.67ms | 7351818 | 80 | 4.5668e+08 | 2.46585e+06 | 0.336148 | 1.75934 | 7.46199 | 1.33972 | 0.0101737 | 0.0548731 | 0.000303699 | 1(Win) | true |
| simdjson (reflection) | 2774.83 | 0.070816 | 8552.73ms | 7351818 | 160 | 5.12271e+08 | 2.52673e+06 | 0.108412 | 1.81212 | 7.95654 | 1.1702 | 0.00812198 | 0.0521105 | 0.00215987 | 2(Loss) | true |
| jsonifier | 2655.77 | 0.262699 | 8994.61ms | 7351818 | 30 | 1.44294e+09 | 2.64001e+06 | 0.148385 | 1.89351 | 8.00259 | 1.83671 | 0.0106101 | 0.0279322 | 0.000579594 | 3(Loss) | true |
| simdjson (ondemand) | 2402.93 | 0.15669 | 9877.2ms | 7351818 | 40 | 8.36086e+08 | 2.91778e+06 | 0.590671 | 2.08482 | 8.63223 | 1.38696 | 0.00971298 | 0.0534763 | 0.00120461 | 4(Loss) | true |
| glaze | 2127.64 | 0.0851154 | 5264ms | 7351818 | 80 | 6.29359e+08 | 3.29531e+06 | 0.433033 | 2.3423 | 10.6468 | 2.10449 | 0.00905005 | 0.0279576 | 0.000243598 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6327.18 | 0.0984622 | 9531.77ms | 9930848 | 40 | 8.68864e+07 | 1.49684e+06 | 0.0149504 | 0.796772 | 2.35463 | 0.147543 | 0.000385843 | 0.0251305 | 0.00210778 | 1(Win) | true |
| glaze | 2981.39 | 0.266605 | 10054.2ms | 9930228 | 40 | 2.86865e+09 | 3.17644e+06 | 0.122458 | 1.6749 | 4.4372 | 0.414459 | 0.000696839 | 0.0760254 | 0.0175895 | 2(Loss) | true |
| simdjson (reflection) | 274.219 | 0.342604 | 10376.5ms | 10018896 | 30 | 4.27513e+11 | 3.48435e+07 | 0.912201 | 14.0164 | 38.4689 | 5.72467 | 0.0236271 | 0.264776 | 0.143338 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6313.47 | 0.114762 | 9516.01ms | 9930848 | 80 | 2.37094e+08 | 1.50009e+06 | 0.235532 | 0.793354 | 2.3546 | 0.147536 | 0.000377378 | 0.025098 | 0.00134742 | 1(Win) | true |
| glaze | 4030.78 | 0.106453 | 7336.58ms | 9930228 | 160 | 1.00087e+09 | 2.34947e+06 | 0.200324 | 1.24563 | 4.43681 | 0.414372 | 0.000649494 | 0.0224773 | 0.002326 | 2(Loss) | true |
| simdjson (reflection) | 310.438 | 2.00551 | 9141.06ms | 10018896 | 30 | 1.14304e+13 | 3.07784e+07 | 0.603031 | 13.8555 | 38.4684 | 5.72283 | 0.0233672 | 0.298318 | 0.168748 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1109.82 | 0.0939721 | 5175.51ms | 461466 | 160 | 2.22173e+07 | 396539 | 0.0155241 | 4.54746 | 17.2626 | 3.19678 | 0.031329 | 0.0503939 | 0.000239576 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1106.31 | 0.163008 | 5203.63ms | 461466 | 40 | 1.68192e+07 | 397798 | 0.0623357 | 4.56625 | 19.1781 | 3.76612 | 0.0236719 | 0.0356062 | 0.000603999 | 1(Tie) | true |
| jsonifier (two-stage) | 1104.15 | 0.0557244 | 5172.09ms | 461466 | 320 | 1.57858e+07 | 398577 | 0.127878 | 4.5708 | 18.4635 | 3.32703 | 0.0245089 | 0.0883833 | 0.000679316 | 3(Loss) | true |
| simdjson (reflection) | 1089.3 | 0.116032 | 5245.95ms | 461466 | 320 | 7.03225e+07 | 404012 | 0.0707523 | 4.59499 | 18.6952 | 3.26767 | 0.0152357 | 0.0892998 | 0.000331478 | 4(Loss) | true |
| simdjson (ondemand) | 1029.92 | 0.136292 | 5547.34ms | 461466 | 320 | 1.08534e+08 | 427304 | 0.0673736 | 4.87646 | 19.0763 | 3.5615 | 0.0131844 | 0.08474 | 0.000259607 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1501.42 | 0.0457786 | 9405.97ms | 461466 | 640 | 1.15233e+07 | 293114 | 0.0903807 | 3.35776 | 14.2489 | 2.44809 | 0.0210607 | 0.0286595 | 0.00012593 | 1(Win) | true |
| jsonifier | 1486.06 | 0.111519 | 9406.44ms | 461466 | 160 | 1.7451e+07 | 296143 | 0.00766579 | 3.38684 | 13.0462 | 2.3179 | 0.028211 | 0.00513181 | 1.85008e-05 | 2(Loss) | true |
| simdjson (reflection) | 1425.63 | 0.17366 | 9725.87ms | 461466 | 160 | 4.5982e+07 | 308698 | 0.0761293 | 3.53427 | 15.0707 | 2.43353 | 0.00754959 | 0.0484297 | 0.000126337 | 3(Loss) | true |
| glaze | 1404.45 | 0.211181 | 9941.15ms | 461466 | 40 | 1.7516e+07 | 313352 | 0.18318 | 3.59701 | 15.3286 | 2.93101 | 0.0214494 | 0.00735249 | 9.59442e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1396.96 | 0.158592 | 9852.38ms | 461466 | 320 | 7.9877e+07 | 315032 | 0.170929 | 3.60446 | 15.0712 | 2.68379 | 0.00401594 | 0.0297626 | 0.000170042 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15541.1 | 0.0279401 | 3621.31ms | 461466 | 4890 | 306114 | 28317.8 | 0.214953 | 0.326801 | 1.46848 | 0.228821 | 0.000208819 | 0.012126 | 3.02987e-05 | 1(Win) | true |
| simdjson (reflection) | 11197 | 0.0424249 | 4688.2ms | 461466 | 640 | 177949 | 39304 | 0.166669 | 0.451705 | 2.40031 | 0.304556 | 0.00134598 | 0.0100177 | 3.36936e-05 | 2(Loss) | true |
| glaze | 4158.29 | 0.100844 | 5854ms | 461466 | 2560 | 2.91601e+07 | 105834 | 0.109965 | 1.20875 | 5.02781 | 0.783349 | 0.00787398 | 0.0419976 | 0.000124575 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15551.1 | 0.0664717 | 3624.66ms | 461466 | 160 | 56617.7 | 28299.5 | 0.0636972 | 0.325451 | 1.4673 | 0.228554 | 0.000208019 | 0.012185 | 7.13758e-06 | 1(Win) | true |
| simdjson (reflection) | 11345.9 | 0.0623542 | 4675.14ms | 461466 | 2560 | 1.49751e+06 | 38788.2 | 0.0713485 | 0.445606 | 2.3992 | 0.304304 | 0.00118367 | 0.0112598 | 7.88841e-06 | 2(Loss) | true |
| glaze | 4698.05 | 0.0798442 | 5203.36ms | 461466 | 2560 | 1.43209e+07 | 93674.6 | 0.182974 | 1.07849 | 5.01325 | 0.779936 | 0.00786284 | 0.0101957 | 7.07189e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1689 | 0.0564926 | 5369.89ms | 728486 | 640 | 3.45579e+07 | 411331 | 0.161198 | 2.98782 | 12.2211 | 2.12029 | 0.0152527 | 0.0783436 | 0.000289646 | 1(Win) | true |
| simdjson (reflection) | 1648.64 | 0.160389 | 5481.07ms | 728486 | 160 | 7.30908e+07 | 421402 | 0.2267 | 3.04579 | 12.4049 | 2.09298 | 0.00991913 | 0.076866 | 0.000448971 | 2(Loss) | true |
| simdjson (ondemand) | 1558.66 | 0.0952891 | 5774.4ms | 728486 | 640 | 1.15454e+08 | 445729 | 0.301425 | 3.22008 | 12.6543 | 2.28097 | 0.00847962 | 0.0767903 | 0.000474361 | 3(Loss) | true |
| glaze | 1459.66 | 0.172968 | 6120.02ms | 728486 | 40 | 2.711e+07 | 475958 | 0.103568 | 3.45927 | 14.5779 | 2.89747 | 0.0145879 | 0.034075 | 0.000210093 | 4(Loss) | true |
| jsonifier | 1378.66 | 0.0321689 | 6529.49ms | 728486 | 640 | 1.68184e+07 | 503924 | 0.0801753 | 3.66508 | 13.1097 | 2.60244 | 0.0202569 | 0.0464168 | 0.00025568 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2236.19 | 0.249254 | 9947.36ms | 728486 | 80 | 4.79734e+07 | 310680 | 0.274807 | 2.24885 | 9.56694 | 1.56743 | 0.0132735 | 0.0354397 | 2.93588e-05 | 1(Win) | true |
| simdjson (reflection) | 2104.53 | 0.147383 | 5095.67ms | 728486 | 320 | 7.57497e+07 | 330116 | 0.038483 | 2.36663 | 10.1091 | 1.56457 | 0.00518129 | 0.0462912 | 5.32483e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2073.49 | 0.120684 | 5161.42ms | 728486 | 640 | 1.04645e+08 | 335057 | 0.0408322 | 2.41963 | 10.111 | 1.72349 | 0.00305145 | 0.0334093 | 1.49304e-05 | 3(Loss) | true |
| glaze | 1794.45 | 0.11237 | 5859.01ms | 728486 | 160 | 3.02832e+07 | 387159 | 0.00880529 | 2.80428 | 12.141 | 2.36909 | 0.0130438 | 0.0108407 | 3.53902e-05 | 4(Loss) | true |
| jsonifier | 1725.8 | 0.0547224 | 6073.15ms | 728486 | 640 | 3.10577e+07 | 402559 | 0.199543 | 2.93531 | 10.4391 | 2.04586 | 0.0185074 | 0.010117 | 5.21265e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19183.6 | 0.0471406 | 4937.37ms | 837491 | 1280 | 493059 | 41634.1 | 0.0481094 | 0.259919 | 0.866363 | 0.126068 | 0.000117266 | 0.0155589 | 7.84617e-06 | 1(Win) | true |
| glaze | 5127.79 | 0.174275 | 8464.27ms | 837491 | 320 | 2.35789e+07 | 155758 | 0.204902 | 0.978901 | 4.13953 | 0.597635 | 0.0052271 | 0.0608827 | 8.08927e-05 | 2(Loss) | true |
| simdjson (reflection) | 538.001 | 0.216531 | 9509.38ms | 837491 | 320 | 3.30663e+09 | 1.48456e+06 | 0.722503 | 9.34497 | 36.2816 | 6.87319 | 0.033733 | 0.350826 | 0.00105702 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19519 | 0.128877 | 4926.21ms | 837491 | 30 | 83429.4 | 40918.7 | 0.0345281 | 0.259082 | 0.865704 | 0.12592 | 0.000116419 | 0.0151772 | 0.000179027 | 1(Win) | true |
| glaze | 6173.23 | 0.191406 | 7048.96ms | 837491 | 80 | 4.90613e+06 | 129380 | 0.344804 | 0.81678 | 4.13032 | 0.595506 | 0.00524577 | 0.0195072 | 3.04779e-05 | 2(Loss) | true |
| simdjson (reflection) | 538.474 | 0.617131 | 9511.32ms | 837491 | 40 | 3.35155e+09 | 1.48325e+06 | 0.0458538 | 9.33869 | 36.2812 | 6.87307 | 0.0339549 | 0.351 | 0.0020611 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 8072.32 | 0.030567 | 6295.16ms | 466906 | 2560 | 727792 | 55160.9 | 0.489726 | 0.625668 | 2.79607 | 0.328972 | 0.00051425 | 8.30684e-06 | 5.36527e-06 | 1(Win) | true |
| jsonifier | 8001.93 | 0.0261305 | 6300.44ms | 466906 | 4890 | 1.03389e+06 | 55646.1 | 0.042044 | 0.626441 | 2.79983 | 0.329897 | 0.00051677 | 1.31501e-05 | 9.39001e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7276.53 | 0.0528339 | 6876.3ms | 466906 | 80 | 83623.2 | 61193.5 | 0.0727693 | 0.694775 | 3.41824 | 0.290978 | 0.000409986 | 5.97015e-06 | 3.29295e-06 | 3(Loss) | true |
| simdjson (reflection) | 7079.81 | 0.0840281 | 7003.04ms | 466906 | 160 | 446873 | 62893.8 | 0.213743 | 0.705698 | 3.47021 | 0.316022 | 0.000348852 | 5.15361e-06 | 3.64099e-06 | 4(Loss) | true |
| glaze | 2985.13 | 0.0433744 | 8049.58ms | 466906 | 1280 | 5.3581e+06 | 149165 | 0.23744 | 1.69943 | 7.03126 | 1.04484 | 0.00154157 | 7.82913e-06 | 4.78549e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 8170.99 | 0.06127 | 6266.26ms | 466906 | 1280 | 1.42697e+06 | 54494.7 | 0.0333128 | 0.616624 | 2.76513 | 0.322016 | 0.000520943 | 1.57821e-05 | 1.32019e-05 | 1(Win) | true |
| jsonifier | 8058.58 | 0.032824 | 6274.16ms | 466906 | 4890 | 1.60855e+06 | 55255 | 0.00558089 | 0.619515 | 2.7689 | 0.322909 | 0.000526954 | 3.44206e-05 | 2.94582e-05 | 2(Loss) | true |
| simdjson (ondemand) | 7351.89 | 0.021995 | 6898.3ms | 466906 | 2560 | 454307 | 60566.2 | 0.178446 | 0.687111 | 3.3887 | 0.286148 | 0.000406704 | 1.60875e-05 | 1.30062e-05 | 3(Loss) | true |
| simdjson (reflection) | 7107.65 | 0.0445208 | 7092.41ms | 466906 | 1280 | 995733 | 62647.5 | 0.0741063 | 0.706503 | 3.45847 | 0.313847 | 0.000441629 | 1.61184e-05 | 1.21244e-05 | 4(Loss) | true |
| glaze | 2984.42 | 0.176389 | 8050.97ms | 466906 | 160 | 1.10816e+07 | 149200 | 0.0672385 | 1.68696 | 6.98819 | 1.03609 | 0.00154635 | 9.34342e-06 | 6.82686e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8891.82 | 0.0307004 | 7546.04ms | 631514 | 2560 | 1.10691e+06 | 67731.7 | 0.00597738 | 0.567739 | 2.5015 | 0.253849 | 0.000396297 | 9.21521e-06 | 6.3977e-06 | 1(Win) | true |
| jsonifier (two-stage) | 8873.83 | 0.0289543 | 7546.35ms | 631514 | 2560 | 988577 | 67869.1 | 0.0452379 | 0.568424 | 2.50097 | 0.253711 | 0.000391319 | 1.34665e-05 | 1.0482e-05 | 2(Loss) | true |
| simdjson (ondemand) | 8221.46 | 0.0775882 | 8122.48ms | 631514 | 40 | 129217 | 73254.5 | 0.031817 | 0.614807 | 2.89904 | 0.23084 | 0.00029267 | 9.06552e-06 | 4.79008e-06 | 3(Loss) | true |
| simdjson (reflection) | 8097.33 | 0.0671095 | 8247.6ms | 631514 | 40 | 99657.5 | 74377.4 | 0.0565007 | 0.62453 | 2.93568 | 0.248964 | 0.000328259 | 2.03875e-05 | 1.631e-05 | 4(Loss) | true |
| glaze | 3556.02 | 0.086236 | 9069.2ms | 631514 | 160 | 3.41298e+06 | 169363 | 0.0827013 | 1.41765 | 6.38392 | 0.992727 | 0.00161164 | 1.45979e-05 | 1.1223e-05 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9037.52 | 0.051185 | 7533.83ms | 631514 | 80 | 93077.3 | 66639.8 | 0.0366469 | 0.559402 | 2.47866 | 0.248717 | 0.000377426 | 8.4717e-06 | 6.47254e-06 | 1(Win) | true |
| jsonifier (two-stage) | 9010.26 | 0.0672387 | 7528.64ms | 631514 | 640 | 1.29274e+06 | 66841.4 | 0.158445 | 0.560599 | 2.47836 | 0.248628 | 0.000388382 | 1.34102e-05 | 9.53562e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8225.12 | 0.0696289 | 8168.74ms | 631514 | 320 | 831785 | 73221.9 | 0.232291 | 0.612664 | 2.87924 | 0.227743 | 0.000328724 | 2.56279e-05 | 2.08972e-05 | 3(Loss) | true |
| simdjson (reflection) | 8075.68 | 0.124111 | 8311.3ms | 631514 | 40 | 342678 | 74576.9 | 0.164104 | 0.626012 | 2.9307 | 0.248178 | 0.000371567 | 4.30711e-05 | 3.65788e-05 | 4(Loss) | true |
| glaze | 3591.54 | 0.0746527 | 9032.6ms | 631514 | 640 | 1.00294e+07 | 167688 | 0.105017 | 1.40417 | 6.35259 | 0.98645 | 0.00147975 | 8.39748e-06 | 5.70801e-06 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1932.29 | 0.263148 | 6114.92ms | 466906 | 40 | 1.47086e+07 | 230439 | 0.00191659 | 2.60329 | 7.53859 | 1.27077 | 0.0163989 | 0.0145614 | 0.000128827 | 1(Win) | true |
| glaze | 1769.5 | 0.158929 | 6687.79ms | 466906 | 160 | 2.55908e+07 | 251640 | 0.0461036 | 2.84646 | 10.345 | 1.80058 | 0.0130797 | 0.0106773 | 0.000339107 | 2(Loss) | true |
| simdjson (reflection) | 1739.46 | 0.074302 | 6753.79ms | 466906 | 1280 | 4.63065e+07 | 255986 | 0.0734392 | 2.87526 | 9.70339 | 1.56607 | 0.0139472 | 0.0380414 | 0.000669713 | 3(Loss) | true |
| jsonifier (two-stage) | 1673.27 | 0.167659 | 7102.6ms | 466906 | 160 | 3.18494e+07 | 266112 | 0.304516 | 3.00653 | 8.69869 | 1.38738 | 0.0173464 | 0.0323247 | 0.000779413 | 4(Loss) | true |
| simdjson (ondemand) | 1325.51 | 0.0838835 | 8780.33ms | 466906 | 640 | 5.08193e+07 | 335929 | 0.298148 | 3.74297 | 10.8299 | 1.92588 | 0.0141952 | 0.0440881 | 0.000421307 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2504.8 | 0.0865468 | 5448.79ms | 466906 | 320 | 7.57472e+06 | 177769 | 0.166341 | 2.01697 | 6.14474 | 0.97074 | 0.0127246 | 0.000976341 | 0.000105984 | 1(Win) | true |
| glaze | 2331.96 | 0.174636 | 5806.7ms | 466906 | 80 | 8.89551e+06 | 190945 | 0.100974 | 2.16155 | 8.94429 | 1.49779 | 0.00705187 | 0.00021091 | 8.12262e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2099.88 | 0.0954997 | 6423.35ms | 466906 | 640 | 2.62455e+07 | 212049 | 0.310538 | 2.37234 | 7.30211 | 1.08705 | 0.0129137 | 0.00500627 | 5.9571e-05 | 3(Loss) | true |
| simdjson (reflection) | 2042.06 | 0.217032 | 6509.45ms | 466906 | 320 | 7.16673e+07 | 218053 | 0.183914 | 2.44165 | 8.66136 | 1.32229 | 0.00965836 | 0.0321215 | 0.000215253 | 4(Loss) | true |
| simdjson (ondemand) | 1588.61 | 0.107274 | 8066.48ms | 466906 | 640 | 5.7862e+07 | 280293 | 0.0715691 | 3.14136 | 9.51876 | 1.64186 | 0.0104249 | 0.00987136 | 0.000259103 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17445.6 | 0.234948 | 3397.37ms | 475954 | 30 | 112104 | 26018.3 | 0.00820004 | 0.289783 | 0.997449 | 0.149844 | 0.000264031 | 0.00165296 | 5.62379e-05 | 1(Win) | true |
| simdjson (reflection) | 9601.47 | 0.0373081 | 5503.93ms | 475954 | 2560 | 796342 | 47274.5 | 0.0643623 | 0.518061 | 1.29723 | 0.191414 | 0.000306848 | 0.0050462 | 0.000110067 | 2(Loss) | true |
| glaze | 7605.46 | 0.101227 | 6757.87ms | 475954 | 4890 | 1.78475e+07 | 59681.5 | 0.270867 | 0.656502 | 2.25793 | 0.340094 | 0.000211637 | 0.0130087 | 5.55883e-05 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17622.8 | 0.0496957 | 3388.93ms | 475954 | 40 | 6553.52 | 25756.6 | 0.29359 | 0.287455 | 0.996308 | 0.149586 | 0.000262105 | 0.00131352 | 3.79764e-05 | 1(Win) | true |
| simdjson (reflection) | 9636.51 | 0.0974135 | 5451.09ms | 475954 | 80 | 168430 | 47102.6 | 0.0982066 | 0.514744 | 1.29613 | 0.191164 | 0.000319254 | 0.00450093 | 7.00435e-05 | 2(Loss) | true |
| glaze | 9014.09 | 0.370673 | 5804.84ms | 475954 | 640 | 2.22971e+07 | 50355 | 0.244567 | 0.551036 | 2.2457 | 0.337314 | 0.000214004 | 0.000596585 | 2.0321e-05 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2253.27 | 0.25909 | 7080.96ms | 631514 | 30 | 1.43868e+07 | 267283 | 0.0102378 | 2.24018 | 7.56264 | 1.17739 | 0.0107698 | 0.037636 | 0.000211238 | 1(Win) | true |
| jsonifier (two-stage) | 2165.4 | 0.132271 | 7317.89ms | 631514 | 1280 | 1.73233e+08 | 278129 | 0.208649 | 2.31283 | 6.87553 | 1.03842 | 0.011957 | 0.0366651 | 0.000262588 | 2(Loss) | true |
| glaze | 1871.21 | 0.0468038 | 8401.42ms | 631514 | 640 | 1.45232e+07 | 321855 | 0.0569952 | 2.68243 | 9.33446 | 1.685 | 0.0113794 | 0.0173786 | 0.000269457 | 3(Loss) | true |
| jsonifier STATISTICAL TIE | 1752.62 | 0.0680084 | 9011.04ms | 631514 | 160 | 8.7385e+06 | 343634 | 0.0808692 | 2.882 | 7.00634 | 1.31472 | 0.0138417 | 0.0262965 | 0.000184923 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1750.11 | 0.0786669 | 9026.12ms | 631514 | 640 | 4.69026e+07 | 344125 | 0.0013263 | 2.87897 | 8.38169 | 1.43984 | 0.0107041 | 0.0397108 | 0.000178326 | 4(Tie) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2735.94 | 0.140141 | 6625.71ms | 631514 | 320 | 3.04534e+07 | 220129 | 0.061182 | 1.83653 | 5.84138 | 0.816245 | 0.00917724 | 0.00962864 | 4.8648e-05 | 1(Win) | true |
| simdjson (reflection) | 2639.25 | 0.103817 | 6814.33ms | 631514 | 640 | 3.59184e+07 | 228193 | 0.104822 | 1.90801 | 6.79206 | 0.997793 | 0.00745085 | 0.026759 | 0.000141077 | 2(Loss) | true |
| glaze | 2251.03 | 0.0517024 | 7678.75ms | 631514 | 640 | 1.22463e+07 | 267548 | 0.19539 | 2.23901 | 8.30374 | 1.46314 | 0.00912185 | 0.00138556 | 9.33026e-05 | 3(Loss) | true |
| jsonifier | 2145.54 | 0.0353489 | 8162.75ms | 631514 | 1280 | 1.26025e+07 | 280703 | 0.0438411 | 2.35356 | 5.9737 | 1.09277 | 0.00900921 | 0.00459384 | 0.00015235 | 4(Loss) | true |
| simdjson (ondemand) | 2085.47 | 0.134635 | 8301.38ms | 631514 | 80 | 1.20938e+07 | 288788 | 0.0459719 | 2.42194 | 7.41394 | 1.23064 | 0.00788904 | 0.0108345 | 0.000117773 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21129.9 | 0.135525 | 4010.27ms | 716365 | 80 | 153603 | 32332.3 | 0.0596121 | 0.238128 | 0.712898 | 0.0995889 | 0.00017854 | 0.00331526 | 1.60009e-05 | 1(Win) | true |
| glaze | 5020.26 | 0.193262 | 7385.52ms | 716365 | 640 | 4.42677e+07 | 136084 | 0.190259 | 0.9905 | 2.59192 | 0.346191 | 0.000252431 | 0.0476875 | 1.69301e-05 | 2(Loss) | true |
| simdjson (reflection) | 550.192 | 0.604036 | 7941.85ms | 716365 | 40 | 2.25023e+09 | 1.24171e+06 | 0.1424 | 9.06312 | 29.6648 | 6.19471 | 0.0563026 | 0.28204 | 0.00102901 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21117.9 | 0.02737 | 4087.93ms | 716365 | 2560 | 200705 | 32350.7 | 0.440228 | 0.239246 | 0.712123 | 0.0994131 | 0.000175501 | 0.00334373 | 4.26688e-05 | 1(Win) | true |
| glaze | 6645.75 | 0.337924 | 5670.75ms | 716365 | 320 | 3.8616e+07 | 102799 | 0.197097 | 0.758931 | 2.58211 | 0.343924 | 0.000247691 | 0.0040054 | 2.52708e-05 | 2(Loss) | true |
| simdjson (reflection) | 548.255 | 0.379645 | 7950.57ms | 716365 | 80 | 1.7904e+09 | 1.2461e+06 | 0.0998803 | 9.17269 | 29.6644 | 6.19466 | 0.0560849 | 0.283195 | 0.0130659 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2473.24 | 0.0433355 | 834.033ms | 2632 | 4890 | 945.878 | 1014.89 | 0.041049 | 2.13243 | 7.93921 | 1.33967 | 0.000381182 | 5.81952e-05 | 2.60286e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2148.56 | 0.0638914 | 847.887ms | 2632 | 640 | 356.566 | 1168.26 | 0.111401 | 2.43463 | 9.78571 | 1.57219 | 0.000759878 | 5.87718e-05 | 1.18731e-06 | 2(Loss) | true |
| glaze | 2017.74 | 0.1627 | 854.277ms | 2632 | 30 | 122.897 | 1244 | 0.0187532 | 2.58936 | 10.9552 | 2.06193 | 0.00051925 | 0 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1681.77 | 0.146931 | 883.492ms | 2632 | 1280 | 6155.65 | 1492.51 | 0.0416313 | 3.08226 | 10.0148 | 1.69529 | 0.00138084 | 0.000113982 | 4.24463e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1642.59 | 0.0488243 | 887.001ms | 2632 | 4890 | 2722.03 | 1528.11 | 0.0286548 | 3.15612 | 10.5008 | 1.84878 | 0.00144633 | 6.26239e-05 | 1.56171e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2865.41 | 0.17685 | 825.485ms | 2632 | 1280 | 3071.99 | 875.989 | 0.11822 | 1.85078 | 6.95327 | 1.08397 | 0.000384688 | 9.1126e-05 | 5.61004e-05 | 1(Win) | true |
| glaze | 2556.93 | 0.14916 | 836.551ms | 2632 | 40 | 85.7635 | 981.675 | 0.123241 | 2.06223 | 9.21657 | 1.67895 | 0.00107333 | 2.84954e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 2469.16 | 0.0547468 | 844.947ms | 2632 | 2560 | 792.922 | 1016.57 | 0.107593 | 2.12529 | 8.80205 | 1.31801 | 0.000761066 | 2.64176e-05 | 4.15559e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1943.94 | 0.0814494 | 872.329ms | 2632 | 1280 | 1415.76 | 1291.23 | 0.0651813 | 2.68592 | 8.91109 | 1.50304 | 0.00137817 | 4.57114e-05 | 8.90483e-06 | 4(Loss) | true |
| simdjson (reflection) | 1850.24 | 0.0659456 | 879.519ms | 2632 | 2560 | 2048.93 | 1356.62 | 0.111788 | 2.80747 | 9.17667 | 1.47302 | 0.00170394 | 0.000104186 | 3.27994e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10964 | 0.459064 | 753.145ms | 2632 | 80 | 88.3631 | 228.938 | 0.180505 | 0.540126 | 1.74848 | 0.294453 | 0.000379939 | 9.49848e-06 | 9.49848e-06 | 1(Win) | true |
| simdjson (reflection) | 6605.55 | 0.120573 | 770.953ms | 2632 | 4890 | 1026.51 | 379.994 | 0.546912 | 0.845191 | 2.78913 | 0.455927 | 0.000381882 | 5.14355e-05 | 1.32085e-05 | 2(Loss) | true |
| glaze | 4296.2 | 0.0875362 | 790.365ms | 2632 | 4890 | 1279.05 | 584.253 | 0.121127 | 1.25764 | 4.06269 | 0.716566 | 0.000381415 | 4.40543e-05 | 1.21208e-05 | 3(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13326.6 | 0.145462 | 744.665ms | 2632 | 40 | 3.00256 | 188.35 | 0.257275 | 0.459384 | 1.53951 | 0.245821 | 0.000379939 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 7419.05 | 0.0595018 | 764.103ms | 2632 | 4890 | 198.173 | 338.328 | 0.309076 | 0.763834 | 2.58131 | 0.407295 | 0.00038025 | 6.40225e-05 | 2.94472e-05 | 2(Loss) | true |
| glaze | 4927.75 | 0.355953 | 779.067ms | 2632 | 80 | 262.997 | 509.375 | 0.058861 | 1.10872 | 3.53723 | 0.606383 | 0.000379939 | 1.8997e-05 | 0 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2435.94 | 0.149093 | 865.771ms | 3370 | 80 | 309.55 | 1319.36 | 0.0653298 | 2.13657 | 8.57715 | 1.33472 | 0.000593472 | 2.22552e-05 | 3.7092e-06 | 1(Win) | true |
| jsonifier | 2312.88 | 0.0693045 | 871.687ms | 3370 | 160 | 148.387 | 1389.56 | 0.13879 | 2.25103 | 8.03947 | 1.54154 | 0.000615727 | 1.11276e-05 | 0 | 2(Loss) | true |
| glaze | 2104.01 | 0.0453219 | 884.783ms | 3370 | 2560 | 1226.93 | 1527.5 | 0.0104582 | 2.46611 | 10.4264 | 1.96261 | 0.000349244 | 2.97895e-05 | 3.82511e-06 | 3(Loss) | true |
| simdjson (reflection) | 2098.74 | 0.094538 | 894.122ms | 3370 | 160 | 335.332 | 1531.34 | 0.000816273 | 2.47407 | 8.13501 | 1.33769 | 0.00104043 | 4.45104e-05 | 9.273e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2019.07 | 0.185785 | 904.364ms | 3370 | 80 | 699.626 | 1591.76 | 0.203805 | 2.56683 | 8.62552 | 1.48131 | 0.00112018 | 4.45104e-05 | 0 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2912 | 0.0646403 | 868.775ms | 3370 | 4890 | 2488.81 | 1103.67 | 0.247769 | 1.79115 | 7.3816 | 1.0543 | 0.000614893 | 4.15673e-05 | 6.55368e-06 | 1(Win) | true |
| jsonifier | 2601.31 | 0.123394 | 876.357ms | 3370 | 640 | 1487.46 | 1235.48 | 0.144636 | 2.00989 | 7.26944 | 1.34273 | 0.000597181 | 2.96736e-05 | 2.7819e-06 | 2(Loss) | true |
| glaze | 2521.11 | 0.149115 | 871.177ms | 3370 | 1280 | 4625.16 | 1274.79 | 0.116945 | 2.06791 | 9.08991 | 1.66291 | 0.00109236 | 4.89151e-05 | 1.34458e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2398.23 | 0.0721457 | 880.031ms | 3370 | 2560 | 2392.99 | 1340.11 | 0.136106 | 2.17517 | 7.31187 | 1.19555 | 0.00111357 | 8.84412e-05 | 4.48581e-05 | 4(Loss) | true |
| simdjson (reflection) | 2306.33 | 0.0462479 | 896.755ms | 3370 | 640 | 265.815 | 1393.5 | 0.00952992 | 2.26025 | 7.48101 | 1.16439 | 0.00106408 | 4.40467e-05 | 1.02003e-05 | 5(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12888.4 | 0.149397 | 757.747ms | 3643 | 1280 | 207.594 | 269.562 | 0.171288 | 0.450064 | 1.29865 | 0.213286 | 0.000274499 | 1.28671e-05 | 2.78788e-06 | 1(Win) | true |
| glaze | 4057.04 | 0.106999 | 822.393ms | 3682 | 2560 | 2195.56 | 865.516 | 0.367502 | 1.3023 | 4.22352 | 0.658066 | 0.000275517 | 5.70767e-05 | 1.98389e-05 | 2(Loss) | true |
| simdjson (reflection) | 578.404 | 0.0650851 | 1354.63ms | 3643 | 2560 | 39125.5 | 6006.59 | 0.131927 | 8.77522 | 36.4529 | 7.57947 | 0.00610171 | 0.00016041 | 7.22705e-05 | 3(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15231 | 0.142991 | 751.824ms | 3643 | 640 | 68.0864 | 228.103 | 0.239176 | 0.392226 | 1.15262 | 0.177601 | 0.000274499 | 1.3725e-05 | 4.28905e-07 | 1(Win) | true |
| glaze | 4381.04 | 0.103902 | 815.613ms | 3682 | 4890 | 3391.3 | 801.505 | 0.291786 | 1.21269 | 3.93645 | 0.592341 | 0.000310914 | 4.55985e-05 | 1.2441e-05 | 2(Loss) | true |
| simdjson (reflection) | 576.806 | 0.0933327 | 1345.9ms | 3643 | 1280 | 40451.7 | 6023.23 | 0.01462 | 8.78007 | 36.4677 | 7.58331 | 0.00622255 | 8.06341e-05 | 2.14452e-05 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1070.09 | 0.0834607 | 1154.05ms | 4630 | 320 | 3795.22 | 4126.31 | 0.0466301 | 4.76995 | 22.4067 | 4.50151 | 0.00184058 | 3.44222e-05 | 2.69978e-06 | 1(Win) | true |
| jsonifier (two-stage) | 967.503 | 0.0368663 | 1196.56ms | 4630 | 2560 | 7246.96 | 4563.82 | 0.340187 | 5.26911 | 25.0487 | 4.85487 | 0.00199767 | 6.62291e-05 | 1.94891e-05 | 2(Loss) | true |
| simdjson (reflection) | 933.742 | 0.146871 | 1221.05ms | 4630 | 30 | 1447.11 | 4728.83 | 0.0211513 | 5.46302 | 26.2104 | 4.65205 | 0.00397408 | 7.19942e-05 | 3.59971e-05 | 3(Loss) | true |
| simdjson (ondemand) | 774.254 | 0.14718 | 1315.79ms | 4630 | 160 | 11272.3 | 5702.93 | 0.00306869 | 6.57248 | 30.1868 | 5.55162 | 0.00405373 | 4.04968e-05 | 1.61987e-05 | 4(Loss) | true |
| glaze | 709.296 | 0.177914 | 1365.09ms | 4630 | 40 | 4906.68 | 6225.2 | 0.0165964 | 7.1779 | 30.073 | 5.82527 | 0.00523218 | 0.000102592 | 4.31965e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1371.22 | 0.0413133 | 1148.26ms | 4630 | 1280 | 2265.37 | 3220.14 | 0.00468266 | 3.73647 | 18.1266 | 3.53002 | 0.000234206 | 4.20154e-05 | 9.28051e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1204.78 | 0.0793208 | 1203.09ms | 4630 | 40 | 338.051 | 3665 | 0.0254596 | 4.24978 | 20.7531 | 3.88035 | 0.000907127 | 2.69978e-05 | 5.39957e-06 | 2(Loss) | true |
| simdjson (reflection) | 1104.06 | 0.03854 | 1244.19ms | 4630 | 2560 | 6081.91 | 3999.34 | 0.0178123 | 4.62002 | 23.3741 | 4.0095 | 0.00143485 | 4.33653e-05 | 7.84625e-06 | 3(Loss) | true |
| simdjson (ondemand) | 898.541 | 0.0495398 | 1330.33ms | 4630 | 1280 | 7585.86 | 4914.09 | 0.0662673 | 5.64837 | 27.1646 | 4.87106 | 0.000944756 | 8.74055e-05 | 8.7743e-06 | 4(Loss) | true |
| glaze | 826.825 | 0.0285021 | 1369.6ms | 4630 | 4890 | 11329.2 | 5340.32 | 0.151906 | 6.15374 | 25.6793 | 4.82808 | 0.00208289 | 7.07134e-05 | 2.257e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1782.2 | 0.0966161 | 982.17ms | 4630 | 640 | 3667.15 | 2477.56 | 0.0312274 | 2.88131 | 7.68099 | 0.411447 | 0.000260192 | 2.86852e-05 | 4.38715e-06 | 1(Win) | true |
| glaze | 1507.12 | 0.15567 | 1022.45ms | 4630 | 40 | 832.025 | 2929.78 | 0.0122293 | 3.40197 | 10.0994 | 0.771058 | 0.000286177 | 2.15983e-05 | 1.07991e-05 | 2(Loss) | true |
| simdjson (reflection) | 1054.61 | 0.0451245 | 1151.2ms | 4630 | 40 | 142.779 | 4186.88 | 0.0141295 | 4.84117 | 15.5771 | 1.48359 | 0.000431965 | 1.07991e-05 | 0 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1856.82 | 0.0315588 | 968.653ms | 4630 | 4890 | 2754.05 | 2377.99 | 0.00982362 | 2.76702 | 7.56976 | 0.385314 | 0.00024721 | 5.33111e-05 | 1.73581e-05 | 1(Win) | true |
| glaze | 1688.54 | 0.0487122 | 999.675ms | 4630 | 320 | 519.238 | 2614.99 | 0.0613428 | 3.04093 | 9.59158 | 0.656803 | 0.000236231 | 4.65713e-05 | 2.29482e-05 | 2(Loss) | true |
| simdjson (reflection) | 1060.64 | 0.0283316 | 1146.13ms | 4630 | 4890 | 6802.69 | 4163.08 | 0.108772 | 4.80991 | 15.4646 | 1.45724 | 0.000437707 | 8.28155e-05 | 5.63587e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2258.54 | 0.058345 | 1226.75ms | 11579 | 1280 | 10416 | 4889.26 | 0.0849994 | 2.25676 | 10.7318 | 1.94939 | 0.00100775 | 3.67044e-05 | 1.15376e-05 | 1(Win) | true |
| simdjson (reflection) | 2207.7 | 0.0487622 | 1236.14ms | 11579 | 1280 | 7614.44 | 5001.85 | 0.0269671 | 2.30759 | 11.119 | 1.8588 | 0.00186221 | 2.74608e-05 | 1.13352e-05 | 2(Loss) | true |
| jsonifier | 2053.34 | 0.0403184 | 1277.2ms | 11579 | 2560 | 12035.6 | 5377.87 | 0.237773 | 2.45421 | 10.9924 | 2.39382 | 0.00157006 | 4.87817e-05 | 1.96341e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1853.31 | 0.0649255 | 1329.74ms | 11579 | 640 | 9577.66 | 5958.32 | 0.116123 | 2.74512 | 12.7072 | 2.21772 | 0.001381 | 1.80823e-05 | 3.77839e-06 | 4(Loss) | true |
| glaze | 1458.03 | 0.0190425 | 1492.26ms | 11579 | 4890 | 10171.1 | 7573.66 | 0.0227567 | 3.48531 | 15.6052 | 2.9234 | 0.00498417 | 3.95081e-05 | 1.45352e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2793.95 | 0.0311354 | 1224.62ms | 11579 | 4890 | 7404.93 | 3952.32 | 0.118532 | 1.8481 | 9.02885 | 1.56335 | 0.000485983 | 4.71377e-05 | 2.37896e-05 | 1(Win) | true |
| simdjson (reflection) | 2547.12 | 0.0867176 | 1253.39ms | 11579 | 640 | 9045.6 | 4335.32 | 0.00436079 | 2.00461 | 10.1366 | 1.6314 | 0.000940145 | 2.38848e-05 | 7.01701e-06 | 2(Loss) | true |
| jsonifier | 2456.04 | 0.059328 | 1282.7ms | 11579 | 640 | 4553.78 | 4496.1 | 0.0515459 | 2.07359 | 9.28811 | 2.00725 | 0.000970777 | 2.33451e-05 | 8.50138e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2111.61 | 0.0571812 | 1354.34ms | 11579 | 80 | 715.341 | 5229.48 | 0.0846882 | 2.41417 | 11.679 | 1.98109 | 0.000886303 | 2.15908e-05 | 0 | 4(Loss) | true |
| glaze | 1634.59 | 0.0684885 | 1511.32ms | 11579 | 320 | 6850.31 | 6755.58 | 0.0688309 | 3.11137 | 13.8731 | 2.53053 | 0.00438132 | 2.348e-05 | 1.02556e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5583.2 | 0.105772 | 985.569ms | 14795 | 2560 | 18291.2 | 2527.16 | 0.0362601 | 0.920396 | 2.49057 | 0.129977 | 6.81449e-05 | 1.86138e-05 | 6.75904e-06 | 1(Win) | true |
| glaze | 3401.82 | 0.08253 | 1147.8ms | 14795 | 1280 | 14998.3 | 4147.67 | 0.431544 | 1.50434 | 4.6071 | 0.413045 | 6.97554e-05 | 2.03299e-05 | 5.49172e-06 | 2(Loss) | true |
| simdjson (reflection) | 418.917 | 0.0703643 | 4103.29ms | 14795 | 2560 | 1.43786e+06 | 33681.1 | 0.164606 | 12.0798 | 43.0327 | 5.95242 | 0.00761166 | 9.00061e-05 | 4.29833e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5814.63 | 0.151846 | 974.092ms | 14795 | 1280 | 17378.2 | 2426.57 | 0.0310591 | 0.883007 | 2.44994 | 0.12066 | 6.88049e-05 | 1.0561e-05 | 7.3927e-07 | 1(Win) | true |
| glaze | 3937.14 | 0.179126 | 1093.07ms | 14795 | 80 | 3296.68 | 3583.72 | 0.156507 | 1.32311 | 4.40399 | 0.366543 | 0.000112369 | 2.7881e-05 | 1.85874e-05 | 2(Loss) | true |
| simdjson (reflection) | 418.905 | 0.0644839 | 4105.03ms | 14795 | 2560 | 1.20765e+06 | 33682.1 | 0.0071016 | 12.0768 | 43.0409 | 5.95418 | 0.00804239 | 0.000148171 | 8.11877e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1808.58 | 0.0621918 | 897.765ms | 3223 | 2560 | 2859.92 | 1699.51 | 0.0583229 | 2.88648 | 11.0379 | 2.04778 | 0.00064078 | 9.81713e-05 | 4.10865e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1483.89 | 0.0431581 | 933.24ms | 3223 | 2560 | 2045.87 | 2071.37 | 0.0945603 | 3.50368 | 13.5327 | 2.34688 | 0.00125453 | 7.00531e-05 | 1.85435e-05 | 2(Loss) | true |
| glaze | 1363.3 | 0.130852 | 960.5ms | 3223 | 40 | 348.144 | 2254.6 | 0.031038 | 3.77617 | 14.4198 | 2.83121 | 0.00168321 | 1.55135e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1218.78 | 0.0371962 | 977.663ms | 3223 | 2560 | 2252.73 | 2521.95 | 0.0960016 | 4.30713 | 15.4604 | 2.54483 | 0.00150129 | 7.06591e-05 | 1.64831e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1146.34 | 0.0437163 | 994.898ms | 3223 | 4890 | 6718.8 | 2681.32 | 0.0165139 | 4.55637 | 15.816 | 2.69097 | 0.00210438 | 0.000139463 | 5.15848e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2196.44 | 0.141 | 886.193ms | 3223 | 40 | 155.733 | 1399.4 | 0.0142898 | 2.3745 | 9.52684 | 1.65374 | 0.000651567 | 3.1027e-05 | 7.75675e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1784.37 | 0.0726943 | 921.476ms | 3223 | 2560 | 4014.14 | 1722.57 | 0.181222 | 2.93376 | 12.0217 | 1.95315 | 0.00109843 | 6.43568e-05 | 1.63619e-05 | 2(Loss) | true |
| glaze | 1609.12 | 0.0640484 | 944.674ms | 3223 | 1280 | 1915.89 | 1910.17 | 0.0539345 | 3.2093 | 12.8697 | 2.43283 | 0.00112715 | 8.84754e-05 | 2.44822e-05 | 3(Loss) | true |
| simdjson (reflection) | 1342.29 | 0.0465197 | 984.241ms | 3223 | 320 | 363.122 | 2289.89 | 0.235828 | 3.9096 | 14.1021 | 2.18461 | 0.00105589 | 3.97533e-05 | 4.84797e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1317.83 | 0.041641 | 977.704ms | 3223 | 2560 | 2414.8 | 2332.38 | 0.046002 | 3.97599 | 14.2799 | 2.30158 | 0.00117333 | 7.38103e-05 | 2.15735e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7665.79 | 0.263141 | 762.857ms | 3223 | 1280 | 1424.94 | 400.962 | 0.0132476 | 0.731348 | 2.03506 | 0.349054 | 0.00031124 | 3.99957e-05 | 1.06655e-05 | 1(Win) | true |
| simdjson (reflection) | 5940.87 | 0.149162 | 775.024ms | 3223 | 2560 | 1524.68 | 517.38 | 0.182378 | 0.92999 | 2.68725 | 0.322991 | 0.00031233 | 8.60514e-05 | 4.02381e-05 | 2(Loss) | true |
| glaze | 3399.49 | 0.0906518 | 822.462ms | 3223 | 640 | 429.958 | 904.163 | 0.0570605 | 1.58324 | 4.91747 | 0.763574 | 0.000312694 | 9.11418e-05 | 1.01807e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8582.59 | 0.0288601 | 759.936ms | 3223 | 320 | 3.41846 | 358.131 | 0.0593006 | 0.667401 | 1.90009 | 0.317096 | 0.00031027 | 1.26047e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6414.15 | 0.112822 | 772.957ms | 3223 | 4890 | 1429.36 | 479.205 | 0.0122748 | 0.863544 | 2.5287 | 0.286069 | 0.000310587 | 4.5557e-05 | 1.38955e-05 | 2(Loss) | true |
| glaze | 3802.97 | 0.361233 | 806.637ms | 3223 | 320 | 2727.72 | 808.234 | 0.0824233 | 1.39315 | 4.37108 | 0.640398 | 0.000318027 | 2.71486e-05 | 0 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2479.55 | 0.2777 | 959.241ms | 5839 | 160 | 6223.08 | 2245.78 | 0.145484 | 2.1099 | 8.15653 | 1.32728 | 0.000644374 | 6.74345e-05 | 2.46189e-05 | 1(Win) | true |
| jsonifier | 2075.13 | 0.133804 | 1003.27ms | 5839 | 640 | 8250.92 | 2683.45 | 0.0452222 | 2.47183 | 8.49289 | 1.79483 | 0.00100349 | 5.9139e-05 | 1.95346e-05 | 2(Loss) | true |
| simdjson (reflection) | 2061.94 | 0.0714685 | 1006.69ms | 5839 | 160 | 596.038 | 2700.61 | 0.0407481 | 2.49727 | 9.08221 | 1.42096 | 0.000626177 | 8.34903e-05 | 2.89005e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1936.45 | 0.0953061 | 1018.69ms | 5839 | 160 | 1201.78 | 2875.62 | 0.117662 | 2.65548 | 9.32026 | 1.50865 | 0.00152744 | 3.8534e-05 | 6.42233e-06 | 4(Loss) | true |
| glaze | 1793.47 | 0.107172 | 1039.61ms | 5839 | 80 | 885.807 | 3104.88 | 0.217065 | 2.91005 | 11.2192 | 2.15242 | 0.00180039 | 2.14078e-05 | 8.56311e-06 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2864.95 | 0.121614 | 949.564ms | 5839 | 320 | 1787.97 | 1943.67 | 0.0421062 | 1.80345 | 7.32146 | 1.10978 | 0.00068933 | 1.98022e-05 | 1.07039e-06 | 1(Win) | true |
| jsonifier | 2391.89 | 0.105059 | 991.904ms | 5839 | 80 | 478.577 | 2328.07 | 0.0838304 | 2.19397 | 7.65765 | 1.57732 | 0.000802792 | 2.99709e-05 | 8.56311e-06 | 2(Loss) | true |
| simdjson (reflection) | 2272.35 | 0.0863754 | 1004.4ms | 5839 | 1280 | 5734.77 | 2450.54 | 0.0502373 | 2.27603 | 8.37678 | 1.23172 | 0.000660564 | 6.78359e-05 | 3.05061e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2208.62 | 0.0332331 | 1009.07ms | 5839 | 1280 | 898.646 | 2521.26 | 0.166183 | 2.32853 | 8.47337 | 1.29474 | 0.000911971 | 4.50901e-05 | 1.23095e-05 | 4(Loss) | true |
| glaze | 1982.85 | 0.055752 | 1036.88ms | 5839 | 2560 | 6275.62 | 2808.33 | 0.397257 | 2.61424 | 10.3615 | 1.93252 | 0.0018889 | 3.49883e-05 | 7.42582e-06 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15523.5 | 0.0562205 | 778.638ms | 6938 | 2560 | 147.001 | 426.231 | 0.181679 | 0.363119 | 1.04238 | 0.166331 | 0.000149482 | 3.18671e-05 | 9.79659e-06 | 1(Win) | true |
| glaze | 3782.12 | 0.134664 | 909.357ms | 6960 | 4890 | 27312.3 | 1754.99 | 0.0245697 | 1.36944 | 4.03233 | 0.567816 | 0.000370919 | 8.32099e-05 | 3.49646e-05 | 2(Loss) | true |
| simdjson (reflection) | 539.462 | 0.0702828 | 1969.67ms | 6938 | 4890 | 363374 | 12265.2 | 0.0684026 | 9.3975 | 37.6128 | 6.87879 | 0.00664857 | 0.000228374 | 0.00011572 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16781.6 | 0.118237 | 770.571ms | 6938 | 2560 | 556.347 | 394.276 | 0.116079 | 0.333893 | 0.962525 | 0.147737 | 0.000144359 | 4.57174e-05 | 2.19579e-05 | 1(Win) | true |
| glaze | 4244.5 | 0.690846 | 887.315ms | 6960 | 160 | 18674.5 | 1563.81 | 0.0778742 | 1.22262 | 3.67529 | 0.490805 | 0.000524425 | 9.87787e-06 | 1.79598e-06 | 2(Loss) | true |
| simdjson (reflection) | 538.984 | 0.0756769 | 1972.36ms | 6938 | 4890 | 422039 | 12276.1 | 0.173213 | 9.48168 | 37.6485 | 6.887 | 0.00686787 | 0.000293455 | 0.00017691 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2035.5 | 0.0650917 | 961.099ms | 4857 | 2560 | 5616.76 | 2275.61 | 0.0138203 | 2.53394 | 9.45584 | 1.74614 | 0.000291461 | 7.33477e-05 | 2.57361e-05 | 1(Win) | true |
| glaze | 1769.77 | 0.0451876 | 1002.8ms | 4857 | 4890 | 6839.94 | 2617.29 | 0.113578 | 2.90251 | 11.5088 | 2.2411 | 0.00032218 | 0.00014168 | 6.86295e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1623.79 | 0.122859 | 1027ms | 4857 | 320 | 3930.43 | 2852.58 | 0.226073 | 3.15748 | 11.9088 | 1.9895 | 0.000428505 | 2.18756e-05 | 1.2868e-06 | 3(Loss) | true |
| simdjson (reflection) | 1523.22 | 0.0727843 | 1043.08ms | 4857 | 1280 | 6270.46 | 3040.93 | 0.0140807 | 3.36987 | 12.6216 | 2.12312 | 0.00159596 | 7.38303e-05 | 2.86314e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1243.25 | 0.0737933 | 1113.18ms | 4857 | 1280 | 9675.28 | 3725.72 | 0.269717 | 4.10856 | 14.5446 | 2.83035 | 0.000909126 | 0.000102301 | 4.13385e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2693.57 | 0.0885393 | 934.585ms | 4857 | 2560 | 5934.62 | 1719.65 | 0.113879 | 1.93217 | 7.27013 | 1.23986 | 0.000218435 | 4.87376e-05 | 1.7211e-05 | 1(Win) | true |
| glaze | 2518.77 | 0.0534833 | 946.045ms | 4857 | 4890 | 4730.48 | 1838.99 | 0.128779 | 2.05506 | 8.58596 | 1.59852 | 0.00147191 | 5.78087e-05 | 2.30309e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2051.43 | 0.126173 | 991.867ms | 4857 | 160 | 1298.61 | 2257.94 | 0.0653678 | 2.51158 | 9.72637 | 1.48301 | 0.00111308 | 4.63249e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1810.25 | 0.215281 | 1044.28ms | 4857 | 30 | 910.323 | 2558.77 | 0.0611899 | 2.84142 | 11.3152 | 1.81285 | 0.00120102 | 0.000102944 | 7.54924e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1525.58 | 0.0562747 | 1064.08ms | 4857 | 2560 | 7473.62 | 3036.21 | 0.00980257 | 3.36386 | 12.2831 | 2.36031 | 0.00198135 | 8.58136e-05 | 2.38058e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10654.2 | 0.138891 | 778.097ms | 4857 | 2560 | 933.441 | 434.759 | 0.140901 | 0.519242 | 1.55837 | 0.261067 | 0.000205888 | 7.53584e-05 | 4.37513e-05 | 1(Win) | true |
| simdjson (reflection) | 6765.56 | 0.178795 | 802.964ms | 4857 | 320 | 479.503 | 684.644 | 0.0684194 | 0.792525 | 2.15256 | 0.332716 | 0.000206532 | 4.37513e-05 | 6.43401e-06 | 2(Loss) | true |
| glaze | 4095.39 | 0.327488 | 859.969ms | 4857 | 320 | 4390.23 | 1131.03 | 0.0229274 | 1.30281 | 3.93473 | 0.615812 | 0.000208462 | 6.88439e-05 | 2.95965e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11632.3 | 0.187946 | 771.503ms | 4857 | 320 | 179.233 | 398.2 | 0.136366 | 0.480759 | 1.49125 | 0.245007 | 0.000205888 | 1.02944e-05 | 4.50381e-06 | 1(Win) | true |
| simdjson (reflection) | 7137.26 | 0.115935 | 801.044ms | 4857 | 2560 | 1449.24 | 648.988 | 0.0639023 | 0.755613 | 2.04324 | 0.305744 | 0.000206451 | 5.30806e-05 | 2.23582e-05 | 2(Loss) | true |
| glaze | 4912.07 | 0.137754 | 830.731ms | 4857 | 1280 | 2159.85 | 942.983 | 0.103668 | 1.07408 | 3.47066 | 0.510398 | 0.000206693 | 5.40457e-05 | 2.10714e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2098.29 | 0.0474997 | 1042.76ms | 6701 | 2560 | 5357.61 | 3045.62 | 0.0180235 | 2.44189 | 9.08596 | 1.45232 | 0.000522951 | 0.000124981 | 5.78272e-05 | 1(Win) | true |
| simdjson (reflection) | 2023.28 | 0.0779081 | 1054.66ms | 6701 | 640 | 3875.35 | 3158.52 | 0.00697567 | 2.53039 | 9.58872 | 1.56126 | 0.00101944 | 5.38632e-05 | 2.28511e-05 | 2(Loss) | true |
| glaze | 1942.26 | 0.0662226 | 1070.79ms | 6701 | 1280 | 6076.98 | 3290.28 | 0.144692 | 2.63141 | 10.6324 | 2.13043 | 0.000529888 | 8.47588e-05 | 3.91733e-05 | 3(Loss) | true |
| jsonifier | 1883.38 | 0.0340715 | 1083.03ms | 6701 | 320 | 427.694 | 3393.13 | 0.0624034 | 2.7181 | 9.00149 | 1.85107 | 0.000714912 | 4.66348e-05 | 2.23847e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1689.76 | 0.0692203 | 1121.76ms | 6701 | 1280 | 8772.15 | 3781.94 | 0.0705948 | 3.02252 | 10.9715 | 2.07044 | 0.000520212 | 5.15315e-05 | 2.2035e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2621.92 | 0.0470758 | 1011.19ms | 6701 | 640 | 842.592 | 2437.37 | 0.0917157 | 1.96494 | 7.5041 | 1.08521 | 0.000748955 | 4.91997e-05 | 1.53895e-05 | 1(Win) | true |
| glaze | 2527.52 | 0.0461287 | 1025.02ms | 6701 | 640 | 870.591 | 2528.4 | 0.0831109 | 2.03454 | 8.56469 | 1.67572 | 0.00134098 | 5.12983e-05 | 2.07525e-05 | 2(Loss) | true |
| simdjson (reflection) | 2380.97 | 0.0561193 | 1035.92ms | 6701 | 1280 | 2904.07 | 2684.02 | 0.00948812 | 2.15655 | 8.64662 | 1.33756 | 0.00092302 | 5.17647e-05 | 1.57393e-05 | 3(Loss) | true |
| jsonifier | 2296.04 | 0.157785 | 1047.75ms | 6701 | 320 | 6171.66 | 2783.3 | 0.0493139 | 2.23403 | 7.41889 | 1.4847 | 0.0008786 | 4.52358e-05 | 1.58558e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2024.64 | 0.0414237 | 1078.62ms | 6701 | 2560 | 4376.44 | 3156.4 | 0.0296237 | 2.53632 | 9.37204 | 1.7378 | 0.0017273 | 4.68097e-05 | 1.32326e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15391.1 | 0.0507538 | 779.323ms | 7376 | 2560 | 137.745 | 457.036 | 0.241039 | 0.357977 | 1.09572 | 0.177196 | 0.000135575 | 2.20309e-05 | 4.50151e-06 | 1(Win) | true |
| glaze | 3926.12 | 0.180514 | 909.806ms | 7376 | 640 | 6694.47 | 1791.67 | 0.388485 | 1.31838 | 4.02779 | 0.591242 | 0.000137058 | 5.27471e-05 | 1.65232e-05 | 2(Loss) | true |
| simdjson (reflection) | 531.859 | 0.179256 | 2067.86ms | 7376 | 640 | 359729 | 13225.9 | 0.017925 | 9.5413 | 37.6124 | 7.48712 | 0.00747102 | 0.00012689 | 6.77874e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16904 | 0.163077 | 774.472ms | 7376 | 2560 | 1178.92 | 416.132 | 0.0646246 | 0.33031 | 1.02698 | 0.161334 | 0.000135628 | 3.26227e-05 | 2.01244e-05 | 1(Win) | true |
| glaze | 4420.04 | 0.089349 | 893.573ms | 7376 | 4890 | 9887.32 | 1591.46 | 0.115253 | 1.17444 | 3.70445 | 0.518032 | 0.000145168 | 3.54047e-05 | 1.04523e-05 | 2(Loss) | true |
| simdjson (reflection) | 532.353 | 0.060872 | 2066.05ms | 7376 | 4890 | 316363 | 13213.6 | 0.00760722 | 9.52208 | 37.6238 | 7.48956 | 0.00739484 | 0.000122267 | 6.20761e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2071.59 | 0.062078 | 814.093ms | 1691 | 640 | 149.464 | 778.467 | 0.131296 | 2.57017 | 8.57067 | 1.42164 | 0.000591366 | 5.72886e-05 | 5.54406e-06 | 1(Win) | true |
| glaze | 1944.01 | 0.0722253 | 816.537ms | 1691 | 640 | 229.747 | 829.555 | 0.00659283 | 2.72833 | 10.071 | 1.96629 | 0.00115594 | 2.67963e-05 | 3.69604e-06 | 2(Loss) | true |
| simdjson (reflection) | 1799.24 | 0.0642876 | 822.218ms | 1691 | 4890 | 1623.58 | 896.304 | 0.235615 | 2.94747 | 9.68066 | 1.70491 | 0.000593301 | 0.000180191 | 7.123e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1772.65 | 0.133938 | 824.049ms | 1691 | 640 | 950.229 | 909.748 | 0.0324714 | 2.99149 | 10.0325 | 1.61857 | 0.00060153 | 6.37567e-05 | 3.69604e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1558.03 | 0.0905625 | 839.787ms | 1691 | 320 | 281.18 | 1035.07 | 0.0724065 | 3.37658 | 8.8356 | 1.5618 | 0.0017741 | 0.000144145 | 5.91366e-05 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2581.45 | 0.245055 | 802.3ms | 1691 | 1280 | 2999.84 | 624.712 | 0.0349033 | 2.08673 | 7.06328 | 1.05145 | 0.000601992 | 6.65287e-05 | 1.15501e-05 | 1(Win) | true |
| glaze | 2395.83 | 0.0835567 | 806.433ms | 1691 | 2560 | 809.799 | 673.112 | 0.0167743 | 2.23972 | 8.56949 | 1.59728 | 0.00102311 | 5.95986e-05 | 1.82492e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2361.08 | 0.144856 | 807.359ms | 1691 | 1280 | 1252.99 | 683.02 | 0.00228769 | 2.27037 | 7.4725 | 1.22768 | 0.000591828 | 0.000113653 | 3.78844e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 2130.16 | 0.174265 | 816.037ms | 1691 | 160 | 278.487 | 757.062 | 0.0446001 | 2.50877 | 8.53873 | 1.25074 | 0.000591366 | 9.24009e-05 | 1.47842e-05 | 4(Loss) | true |
| simdjson (reflection) | 2075.2 | 0.180625 | 818.574ms | 1691 | 80 | 157.62 | 777.112 | 0.0917697 | 2.63242 | 8.75399 | 1.4524 | 0.000591366 | 0.000340035 | 0.000199586 | 5(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8604.09 | 0.104852 | 751.946ms | 1996 | 4890 | 263.134 | 221.236 | 0.0627444 | 0.693573 | 1.46743 | 0.250501 | 0.000501309 | 6.37266e-05 | 1.78271e-05 | 1(Win) | true |
| simdjson (reflection) | 5922.63 | 0.117267 | 759.497ms | 1996 | 40 | 5.68205 | 321.4 | 0.280811 | 0.96126 | 1.93637 | 0.29509 | 0.000501002 | 0 | 0 | 2(Loss) | true |
| glaze | 5087.68 | 0.188246 | 765.032ms | 1996 | 1280 | 634.958 | 374.146 | 0.538901 | 1.12277 | 3.5496 | 0.576653 | 0.000501785 | 3.32697e-05 | 1.0568e-05 | 3(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10031.8 | 0.100579 | 744.359ms | 1996 | 2560 | 93.2435 | 189.75 | 0.142248 | 0.616787 | 1.30661 | 0.211924 | 0.000501393 | 5.20572e-05 | 2.54415e-05 | 1(Win) | true |
| simdjson (reflection) | 6809.89 | 0.0730908 | 757.145ms | 1996 | 160 | 6.67862 | 279.525 | 0.10721 | 0.85135 | 1.69639 | 0.238477 | 0.000504133 | 2.19188e-05 | 0 | 2(Loss) | true |
| glaze | 5943.61 | 0.38278 | 760.213ms | 1996 | 320 | 480.917 | 320.266 | 0.1319 | 0.956895 | 3.06012 | 0.46994 | 0.000501002 | 8.29785e-05 | 5.01002e-05 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2278.27 | 0.110028 | 822.27ms | 2158 | 160 | 158.059 | 903.331 | 0.0836479 | 2.37007 | 8.21316 | 1.26738 | 0.000469184 | 5.7924e-05 | 5.7924e-06 | 1(Win) | true |
| simdjson (reflection) | 2233.37 | 0.0618435 | 825.504ms | 2158 | 2560 | 831.396 | 921.489 | 0.125549 | 2.36387 | 7.85357 | 1.34708 | 0.000465383 | 7.11379e-05 | 2.29886e-05 | 2(Loss) | true |
| glaze | 2017.28 | 0.240373 | 832.279ms | 2158 | 320 | 1924.39 | 1020.2 | 0.0177693 | 2.60126 | 9.69277 | 1.87906 | 0.000722602 | 8.83341e-05 | 1.01367e-05 | 3(Loss) | true |
| jsonifier | 2005.27 | 0.0808643 | 836.071ms | 2158 | 1280 | 881.622 | 1026.31 | 0.261247 | 2.63788 | 8.27618 | 1.52549 | 0.00180361 | 0.000101729 | 2.9324e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1944.36 | 0.0481601 | 839.365ms | 2158 | 4890 | 1270.67 | 1058.46 | 0.151292 | 2.72252 | 7.19138 | 1.23494 | 0.00139482 | 9.40999e-05 | 4.05586e-05 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2851.55 | 0.13103 | 814.277ms | 2158 | 320 | 286.176 | 721.722 | 0.00476269 | 1.87544 | 6.18489 | 0.985635 | 0.000470633 | 4.19949e-05 | 2.8962e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2696.24 | 0.0710265 | 814.878ms | 2158 | 2560 | 752.431 | 763.296 | 0.050383 | 1.98551 | 7.04263 | 0.979147 | 0.000463392 | 6.73367e-05 | 1.90063e-05 | 2(Loss) | true |
| simdjson (reflection) | 2491.38 | 0.0677552 | 823.593ms | 2158 | 4890 | 1531.85 | 826.059 | 0.133234 | 2.16132 | 7.18906 | 1.16172 | 0.000464813 | 9.8838e-05 | 3.81896e-05 | 3(Loss) | true |
| jsonifier | 2427.71 | 0.0703338 | 825.54ms | 2158 | 160 | 56.8799 | 847.725 | 0.00589779 | 2.19208 | 7.10612 | 1.23726 | 0.000732739 | 5.7924e-05 | 0 | 4(Loss) | true |
| glaze | 2403.94 | 0.0511657 | 822.507ms | 2158 | 320 | 61.3993 | 856.106 | 0.0474307 | 2.20491 | 8.51761 | 1.5899 | 0.000738531 | 1.88253e-05 | 0 | 5(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10524.3 | 0.0997481 | 755.15ms | 2866 | 320 | 21.4746 | 259.706 | 0.0432994 | 0.559468 | 1.13643 | 0.18702 | 0.000356551 | 7.63259e-06 | 0 | 1(Win) | true |
| glaze | 4070.92 | 0.117392 | 799.748ms | 2866 | 4890 | 3037.78 | 671.403 | 0.279626 | 1.31659 | 3.92882 | 0.597 | 0.000349917 | 4.70219e-05 | 1.78384e-05 | 2(Loss) | true |
| simdjson (reflection) | 556.074 | 0.155031 | 1228.08ms | 2866 | 640 | 37162.3 | 4915.23 | 0.401286 | 9.16292 | 34.7893 | 7.03803 | 0.00483797 | 0.00022189 | 0.000112853 | 3(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12866 | 0.0974983 | 749.486ms | 2866 | 160 | 6.86399 | 212.438 | 0.0294291 | 0.468048 | 0.964759 | 0.147592 | 0.000348918 | 2.61689e-05 | 0 | 1(Win) | true |
| glaze | 4900.76 | 0.235465 | 786.452ms | 2866 | 2560 | 4414.87 | 557.716 | 0.228994 | 1.11392 | 3.3074 | 0.458828 | 0.000351099 | 5.54726e-05 | 3.47555e-05 | 2(Loss) | true |
| simdjson (reflection) | 552.43 | 0.075032 | 1236.81ms | 2866 | 2560 | 35280.2 | 4947.65 | 0.108654 | 9.24329 | 34.8212 | 7.04519 | 0.00496718 | 0.00028704 | 0.000120486 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2350.26 | 0.0441721 | 910.229ms | 4390 | 4890 | 3027.63 | 1781.35 | 0.0439628 | 2.20123 | 9.87631 | 1.70797 | 0.000408439 | 4.97971e-05 | 1.73754e-05 | 1(Win) | true |
| glaze | 1903.52 | 0.107906 | 952.556ms | 4390 | 80 | 450.6 | 2199.41 | 0.016479 | 2.70632 | 12.8806 | 2.47198 | 0.000281891 | 0.000111048 | 7.97267e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1781.14 | 0.19308 | 965.505ms | 4390 | 30 | 617.913 | 2350.53 | 0.0326061 | 2.88781 | 13.2747 | 2.16925 | 0.00233865 | 3.79651e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1265.89 | 0.0647784 | 1067.28ms | 4390 | 2560 | 11749.9 | 3307.25 | 0.0688238 | 4.04344 | 14.9228 | 2.48588 | 0.00562073 | 0.0001292 | 5.59688e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1092.69 | 0.0897511 | 1122.27ms | 4390 | 640 | 7568.3 | 3831.5 | 0.00256923 | 4.67167 | 16.0103 | 2.7615 | 0.00317091 | 4.44903e-05 | 1.17454e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2731.96 | 0.101734 | 908.658ms | 4390 | 160 | 388.892 | 1532.46 | 0.0195802 | 1.9044 | 8.71526 | 1.43918 | 0.000454157 | 6.26424e-05 | 3.84396e-05 | 1(Win) | true |
| glaze | 2229.63 | 0.155594 | 942.292ms | 4390 | 40 | 341.435 | 1877.72 | 0.00665744 | 2.3195 | 11.4929 | 2.15581 | 0.000256264 | 1.13895e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 1997.13 | 0.069057 | 967.956ms | 4390 | 2560 | 5365.03 | 2096.32 | 0.0878797 | 2.59662 | 12.1107 | 1.90114 | 0.0022739 | 7.91038e-05 | 3.02534e-05 | 3(Loss) | true |
| simdjson (reflection) | 1375.21 | 0.0514572 | 1070.58ms | 4390 | 640 | 1570.6 | 3044.36 | 0.0464701 | 3.72845 | 13.8911 | 2.24442 | 0.00560542 | 5.33884e-05 | 2.42027e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1195.25 | 0.126268 | 1113.63ms | 4390 | 640 | 12519.4 | 3502.73 | 0.0455655 | 4.27533 | 14.7109 | 2.47198 | 0.00328659 | 3.52363e-05 | 5.69476e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13396.7 | 0.0986656 | 762.18ms | 4390 | 640 | 60.848 | 312.512 | 0.197601 | 0.43139 | 1.76902 | 0.288838 | 0.000228858 | 3.55923e-05 | 1.42369e-05 | 1(Win) | true |
| simdjson (reflection) | 7967.14 | 0.193901 | 784.921ms | 4390 | 160 | 166.113 | 525.487 | 0.16679 | 0.684389 | 2.59749 | 0.382916 | 0.00022779 | 4.27107e-05 | 2.42027e-05 | 2(Loss) | true |
| glaze | 3897.28 | 0.358119 | 875.571ms | 4390 | 640 | 9472 | 1074.25 | 0.0624374 | 1.36745 | 4.73713 | 0.755126 | 0.000230994 | 0.000105353 | 5.5168e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14832.2 | 0.174828 | 757.264ms | 4390 | 30 | 7.30575 | 282.267 | 0.153284 | 0.388656 | 1.64351 | 0.259681 | 0.00022779 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 8476.51 | 0.283442 | 780.292ms | 4390 | 2560 | 5017.22 | 493.91 | 0.0456548 | 0.645189 | 2.48633 | 0.356948 | 0.000228502 | 4.33336e-05 | 2.10884e-05 | 2(Loss) | true |
| glaze | 4196.81 | 0.369233 | 848.316ms | 4390 | 640 | 8683.05 | 997.575 | 0.132371 | 1.25893 | 4.32711 | 0.66287 | 0.000228502 | 3.38126e-05 | 7.8303e-06 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3320.6 | 0.190186 | 1008.21ms | 9378 | 640 | 16792.9 | 2693.36 | 0.138029 | 1.55244 | 7.04948 | 1.07091 | 0.000973022 | 9.43032e-05 | 4.63185e-05 | 1(Win) | true |
| jsonifier | 3126.6 | 0.0577131 | 1019.01ms | 9378 | 2560 | 6976.93 | 2860.47 | 0.0188007 | 1.64176 | 7.0611 | 1.50085 | 0.0018048 | 4.34028e-05 | 1.64947e-05 | 2(Loss) | true |
| simdjson (reflection) | 2497.89 | 0.123756 | 1094.43ms | 9378 | 320 | 6282.85 | 3580.45 | 0.00296759 | 2.04792 | 7.68746 | 1.19407 | 0.00280544 | 7.03108e-05 | 4.06537e-05 | 3(Loss) | true |
| glaze | 2469.36 | 0.0974672 | 1090.92ms | 9378 | 320 | 3987.66 | 3621.81 | 0.0333162 | 2.06916 | 9.54937 | 1.7765 | 0.00256951 | 4.16533e-05 | 2.06601e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2172.73 | 0.304112 | 1144.29ms | 9378 | 40 | 6268.1 | 4116.27 | 0.206315 | 2.35332 | 8.19652 | 1.3231 | 0.00138356 | 4.53188e-05 | 2.66581e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3640.54 | 0.274288 | 1013.18ms | 9378 | 640 | 29059.2 | 2456.66 | 0.12673 | 1.41422 | 6.50459 | 0.945404 | 0.00104133 | 6.16469e-05 | 3.71548e-05 | 1(Win) | true |
| jsonifier | 3426.24 | 0.0431169 | 1017.6ms | 9378 | 4890 | 6194.26 | 2610.32 | 0.054662 | 1.50135 | 6.51727 | 1.37535 | 0.00180907 | 3.38651e-05 | 1.44793e-05 | 2(Loss) | true |
| glaze | 2699.12 | 0.0753684 | 1090.9ms | 9378 | 80 | 498.937 | 3313.51 | 0.0381161 | 1.89768 | 8.89945 | 1.62849 | 0.0028151 | 3.46556e-05 | 3.99872e-06 | 3(Loss) | true |
| simdjson (reflection) | 2693.24 | 0.0677881 | 1083.31ms | 9378 | 160 | 810.77 | 3320.74 | 0.0547994 | 1.9024 | 7.20452 | 1.08104 | 0.00265248 | 2.73246e-05 | 9.33035e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2340.22 | 0.0828156 | 1141.3ms | 9378 | 1280 | 12821.6 | 3821.68 | 0.0777627 | 2.18317 | 7.55086 | 1.18 | 0.0017317 | 3.14899e-05 | 1.28292e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23498.5 | 0.0871995 | 785.327ms | 11521 | 4890 | 812.902 | 467.574 | 0.778688 | 0.234058 | 0.737349 | 0.110754 | 8.6869e-05 | 1.84779e-05 | 1.04548e-05 | 1(Win) | true |
| glaze | 5575.95 | 0.152165 | 931.663ms | 11521 | 2560 | 23014.9 | 1970.48 | 0.00477733 | 0.940394 | 3.76521 | 0.512629 | 8.81542e-05 | 2.89214e-05 | 1.1494e-05 | 2(Loss) | true |
| simdjson (reflection) | 528.143 | 0.137802 | 2819.63ms | 11521 | 2560 | 2.10392e+06 | 20803.6 | 0.587639 | 9.59829 | 36.9528 | 6.78306 | 0.00805292 | 0.000115652 | 5.83174e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 26789.9 | 0.103932 | 771.226ms | 11521 | 4890 | 888.475 | 410.128 | 0.142545 | 0.207272 | 0.685878 | 0.0989498 | 8.69578e-05 | 1.53183e-05 | 8.20055e-06 | 1(Win) | true |
| glaze | 6911.38 | 0.120364 | 898.108ms | 11521 | 4890 | 17904.1 | 1589.74 | 0.202335 | 0.747713 | 3.50464 | 0.455516 | 0.00011447 | 3.22164e-05 | 1.32238e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.281 | 0.101341 | 2818.25ms | 11521 | 4890 | 2.18062e+06 | 20837.6 | 0.0932943 | 9.61215 | 37.0441 | 6.80551 | 0.00909894 | 0.000155793 | 8.45793e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3307.46 | 0.0434268 | 866.688ms | 4669 | 640 | 218.753 | 1346.26 | 0.0339017 | 1.57414 | 6.50889 | 1.37267 | 0.000642536 | 2.7107e-05 | 1.00396e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2204.17 | 0.150107 | 932.603ms | 4669 | 40 | 367.804 | 2020.12 | 0.0573726 | 2.34031 | 9.26066 | 1.66267 | 0.00123153 | 5.35447e-06 | 5.35447e-06 | 2(Loss) | true |
| glaze | 2045.12 | 0.178616 | 950.967ms | 4669 | 30 | 453.702 | 2177.23 | 0.00153102 | 2.51985 | 9.58642 | 1.81324 | 0.00101378 | 0 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1705.14 | 0.108154 | 996.396ms | 4669 | 160 | 1276.24 | 2611.34 | 0.0550787 | 3.01304 | 12.517 | 1.90726 | 0.00111239 | 0.000111105 | 5.08674e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1264.44 | 0.0391208 | 1088.78ms | 4669 | 4890 | 9280.67 | 3521.5 | 0.174783 | 4.06224 | 14.51 | 2.49347 | 0.00169516 | 0.000197447 | 0.000129734 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3670.78 | 0.110951 | 853.974ms | 4669 | 160 | 289.811 | 1213.01 | 0.00927357 | 1.4259 | 5.99593 | 1.24802 | 0.000642536 | 8.0317e-06 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 2390.18 | 0.0908913 | 924.217ms | 4669 | 160 | 458.722 | 1862.91 | 0.0604258 | 2.16467 | 8.82395 | 1.55494 | 0.00109767 | 2.67723e-05 | 8.0317e-06 | 2(Loss) | true |
| glaze | 2237.94 | 0.085569 | 937.426ms | 4669 | 640 | 1855.09 | 1989.65 | 0.103084 | 2.3094 | 8.93618 | 1.66588 | 0.000799823 | 5.88991e-05 | 2.44297e-05 | 3(Loss) | true |
| simdjson (reflection) | 1765.78 | 0.0730276 | 990.885ms | 4669 | 160 | 542.588 | 2521.67 | 0.176534 | 2.92102 | 12.2454 | 1.83551 | 0.00138279 | 4.01585e-05 | 1.20475e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1335.33 | 0.0323594 | 1075.61ms | 4669 | 4890 | 5693.46 | 3334.52 | 0.070527 | 3.83951 | 13.8218 | 2.34611 | 0.00174058 | 0.000100738 | 5.12452e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12235 | 0.0938864 | 766.187ms | 4669 | 1280 | 149.436 | 363.932 | 0.0225352 | 0.463582 | 1.23967 | 0.320197 | 0.000214179 | 5.63892e-05 | 2.81109e-05 | 1(Win) | true |
| simdjson (reflection) | 7916.27 | 0.0969576 | 787.494ms | 4669 | 40 | 11.8968 | 562.475 | 0.063666 | 0.684734 | 1.65988 | 0.224459 | 0.000214179 | 2.67723e-05 | 0 | 2(Loss) | true |
| glaze | 3872.25 | 0.127219 | 847.028ms | 4669 | 2560 | 5478.57 | 1149.9 | 0.0647214 | 1.35767 | 3.39602 | 0.486615 | 0.000216856 | 5.17877e-05 | 2.32585e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14057.2 | 0.0752585 | 758.731ms | 4669 | 320 | 18.1849 | 316.756 | 0.243285 | 0.410707 | 1.12337 | 0.293425 | 0.000214179 | 1.33862e-05 | 4.01585e-06 | 1(Win) | true |
| simdjson (reflection) | 8446.2 | 0.105645 | 779.907ms | 4669 | 320 | 99.2606 | 527.184 | 0.0148171 | 0.649461 | 1.55472 | 0.200257 | 0.000331308 | 7.36239e-06 | 2.00792e-06 | 2(Loss) | true |
| glaze | 4583.73 | 0.17409 | 822.625ms | 4669 | 640 | 1830.36 | 971.416 | 0.226988 | 1.14778 | 2.90535 | 0.3761 | 0.000215183 | 1.07089e-05 | 2.34258e-06 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3351.78 | 0.0741242 | 955.871ms | 7932 | 160 | 447.77 | 2256.88 | 0.0481629 | 1.53584 | 6.16818 | 1.0237 | 0.00069103 | 2.44264e-05 | 5.51563e-06 | 1(Win) | true |
| jsonifier | 2903.87 | 0.0857315 | 991.858ms | 7932 | 1280 | 6384.15 | 2604.99 | 0.216691 | 1.77683 | 6.26929 | 1.46596 | 0.000829118 | 3.41772e-05 | 1.5759e-05 | 2(Loss) | true |
| simdjson (reflection) | 2729.28 | 0.0356977 | 1014.56ms | 7932 | 1280 | 1253.03 | 2771.63 | 0.0932179 | 1.88055 | 7.94718 | 1.14624 | 0.000707577 | 6.25433e-05 | 3.06315e-05 | 3(Loss) | true |
| glaze | 2409.44 | 0.092963 | 1052.2ms | 7932 | 640 | 5451.71 | 3139.54 | 0.097043 | 2.15656 | 8.7142 | 1.67764 | 0.00113208 | 2.61993e-05 | 8.86441e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2044.39 | 0.0351244 | 1106.79ms | 7932 | 4890 | 8259.67 | 3700.14 | 0.0178057 | 2.50146 | 9.12027 | 1.4913 | 0.00101381 | 6.62327e-05 | 3.56301e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3576.34 | 0.0393543 | 949.827ms | 7932 | 4890 | 3388.3 | 2115.17 | 0.0437952 | 1.45063 | 5.91112 | 0.960288 | 0.000647374 | 4.0709e-05 | 1.79182e-05 | 1(Win) | true |
| jsonifier | 3049.6 | 0.0534514 | 984.91ms | 7932 | 80 | 140.633 | 2480.5 | 0.0161232 | 1.68637 | 6.01311 | 1.40255 | 0.000789523 | 3.93974e-05 | 2.9942e-05 | 2(Loss) | true |
| simdjson (reflection) | 2815.95 | 0.0884232 | 1014.7ms | 7932 | 1280 | 7222.03 | 2686.32 | 0.00305375 | 1.82819 | 7.78732 | 1.10401 | 0.000880137 | 5.86036e-05 | 2.86616e-05 | 3(Loss) | true |
| glaze | 2583.29 | 0.0897618 | 1033ms | 7932 | 640 | 4421.63 | 2928.26 | 0.0717664 | 2.02104 | 8.32224 | 1.5909 | 0.00114449 | 3.84124e-05 | 2.44264e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2158.21 | 0.0342543 | 1091.27ms | 7932 | 4890 | 7048.83 | 3505.01 | 0.0481562 | 2.37201 | 8.7152 | 1.40456 | 0.00120694 | 5.09185e-05 | 2.19401e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21443.5 | 0.138262 | 772.946ms | 9249 | 320 | 103.503 | 411.337 | 0.012154 | 0.263608 | 0.701049 | 0.160558 | 0.000108458 | 1.8921e-05 | 6.08174e-06 | 1(Win) | true |
| glaze | 3710.92 | 0.151288 | 977.325ms | 9249 | 4890 | 63233.1 | 2376.92 | 0.177652 | 1.39966 | 3.46275 | 0.450535 | 0.000422618 | 5.0478e-05 | 2.26631e-05 | 2(Loss) | true |
| simdjson (reflection) | 536.733 | 0.109404 | 2390.46ms | 9249 | 2560 | 827526 | 16433.7 | 0.150918 | 9.43899 | 38.9237 | 7.6151 | 0.00649449 | 0.000258854 | 0.000180636 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23912 | 0.0888418 | 773.764ms | 9249 | 80 | 8.59177 | 368.875 | 0.101557 | 0.238797 | 0.646773 | 0.148124 | 0.00010812 | 1.21635e-05 | 1.3515e-06 | 1(Win) | true |
| glaze | 4080.62 | 0.143607 | 952.732ms | 9249 | 4890 | 47118.9 | 2161.57 | 0.0641713 | 1.2641 | 3.20891 | 0.394101 | 0.000359073 | 4.7073e-05 | 2.8036e-05 | 2(Loss) | true |
| simdjson (reflection) | 536.308 | 0.309039 | 2380.14ms | 9249 | 320 | 826679 | 16446.8 | 0.21018 | 9.4466 | 38.9171 | 7.61347 | 0.00669836 | 0.000194278 | 0.000133122 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 814.653 | 0.113169 | 1275.29ms | 4604 | 40 | 1488.12 | 5389.68 | 0.0094325 | 6.25619 | 23.0089 | 4.93636 | 0.00486533 | 0.000130321 | 3.80104e-05 | 1(Win) | true |
| simdjson (reflection) | 728.474 | 0.0683976 | 1355.64ms | 4604 | 160 | 2719.22 | 6027.28 | 0.0933421 | 6.99124 | 28.0117 | 5.02997 | 0.00498208 | 0.000357026 | 0.000247068 | 2(Loss) | true |
| jsonifier (two-stage) | 723.245 | 0.0469607 | 1353.14ms | 4604 | 1280 | 10403.5 | 6070.86 | 0.068986 | 7.0209 | 26.593 | 5.30604 | 0.00585191 | 0.000341585 | 0.000222632 | 3(Loss) | true |
| glaze | 636.968 | 0.0662714 | 1426.19ms | 4604 | 1280 | 26711.4 | 6893.15 | 0.109888 | 7.96921 | 32.1429 | 6.66182 | 0.0068546 | 0.000261152 | 0.000155266 | 4(Loss) | true |
| simdjson (ondemand) | 580.508 | 0.0459012 | 1509.71ms | 4604 | 1280 | 15428.1 | 7563.58 | 0.0834565 | 8.74495 | 33.9542 | 6.60361 | 0.00706434 | 0.000301029 | 0.000176138 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1007.99 | 0.197336 | 1263.33ms | 4604 | 80 | 5911.01 | 4355.93 | 0.226641 | 5.06107 | 18.7941 | 3.97524 | 0.00252226 | 7.87359e-05 | 3.25804e-05 | 1(Win) | true |
| jsonifier (two-stage) | 863.705 | 0.112802 | 1346.13ms | 4604 | 640 | 21045.2 | 5083.58 | 0.0984835 | 5.86921 | 22.3821 | 4.34774 | 0.00534216 | 0.000122855 | 4.85312e-05 | 2(Loss) | true |
| simdjson (reflection) | 833.614 | 0.0435611 | 1365.78ms | 4604 | 2560 | 13476.5 | 5267.09 | 0.0349039 | 6.09094 | 25.7921 | 4.49196 | 0.0014662 | 0.000163665 | 8.72204e-05 | 3(Loss) | true |
| glaze | 741.257 | 0.0512766 | 1421.67ms | 4604 | 640 | 5904.07 | 5923.34 | 0.06672 | 6.86695 | 27.7698 | 5.66247 | 0.00626901 | 3.66529e-05 | 1.05207e-05 | 4(Loss) | true |
| simdjson (ondemand) | 634.861 | 0.225016 | 1541.16ms | 4604 | 40 | 9687.26 | 6916.02 | 0.00301224 | 8.01464 | 31.9311 | 6.11933 | 0.00553323 | 6.51607e-05 | 1.62902e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1478.81 | 0.0715146 | 1055.7ms | 4918 | 1280 | 6584.91 | 3171.57 | 0.110453 | 3.47479 | 11.548 | 1.38776 | 0.000562665 | 0.000135027 | 8.43521e-05 | 1(Win) | true |
| jsonifier | 1284.18 | 0.36315 | 1088.46ms | 4604 | 1280 | 197334 | 3419.09 | 0.430206 | 3.97757 | 8.85426 | 0.540835 | 0.000498038 | 8.85779e-05 | 5.02281e-05 | 2(Loss) | true |
| glaze | 1132.56 | 0.230202 | 1126.89ms | 4604 | 320 | 25486.7 | 3876.8 | 0.0782507 | 4.42256 | 12.7974 | 1.13163 | 0.000461555 | 8.62022e-05 | 4.34405e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1485.95 | 0.0766312 | 1058.29ms | 4918 | 1280 | 7488.44 | 3156.35 | 0.0150963 | 3.4534 | 11.4296 | 1.36092 | 0.000544238 | 0.000145511 | 0.000100079 | 1(Win) | true |
| jsonifier | 1295.16 | 0.191656 | 1070ms | 4604 | 4890 | 206433 | 3390.1 | 0.105255 | 3.9428 | 8.78345 | 0.523893 | 0.000555621 | 0.000119839 | 7.46217e-05 | 2(Loss) | true |
| glaze | 1269.11 | 0.0539588 | 1090.88ms | 4604 | 4890 | 17041.5 | 3459.69 | 0.28085 | 4.02892 | 12.2453 | 1.01261 | 0.000555443 | 6.33396e-05 | 2.82941e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2597.61 | 0.0544923 | 1415.78ms | 18245 | 320 | 4263.45 | 6698.39 | 0.0581425 | 1.95816 | 8.12847 | 1.31411 | 0.00128083 | 4.282e-05 | 2.22664e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2574.4 | 0.140144 | 1414.64ms | 18245 | 320 | 28709.9 | 6758.77 | 0.210025 | 1.98152 | 7.68605 | 1.38909 | 0.0014975 | 9.83146e-05 | 6.78268e-05 | 2(Loss) | true |
| jsonifier | 2245.66 | 0.19079 | 1506.75ms | 18245 | 160 | 34964.9 | 7748.2 | 0.00742163 | 2.27472 | 8.0273 | 1.83771 | 0.00138052 | 2.84324e-05 | 1.23321e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2112.06 | 0.0551867 | 1562.71ms | 18245 | 1280 | 26457.9 | 8238.31 | 0.293251 | 2.42208 | 9.66106 | 1.71927 | 0.00185076 | 6.42299e-05 | 3.53693e-05 | 4(Loss) | true |
| glaze | 1803.36 | 0.167623 | 1715.68ms | 18245 | 40 | 10462.9 | 9648.55 | 0.0437217 | 2.8234 | 12.1147 | 2.38043 | 0.00365854 | 6.44012e-05 | 3.97369e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3001.71 | 0.127994 | 1417.86ms | 18245 | 320 | 17614.8 | 5796.62 | 0.0931907 | 1.69817 | 6.62466 | 1.14766 | 0.00144012 | 6.50863e-05 | 4.02508e-05 | 1(Win) | true |
| simdjson (reflection) | 2958.29 | 0.0904944 | 1415.6ms | 18245 | 160 | 4532.85 | 5881.71 | 0.088968 | 1.72166 | 7.53554 | 1.17199 | 0.000340504 | 2.74048e-05 | 1.23321e-05 | 2(Loss) | true |
| jsonifier | 2618.91 | 0.0436874 | 1502.83ms | 18245 | 2560 | 21567.5 | 6643.91 | 0.025841 | 1.96989 | 6.9652 | 1.59594 | 0.00113248 | 8.16791e-05 | 5.8856e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2326.93 | 0.0712183 | 1584.28ms | 18245 | 80 | 2268.8 | 7477.59 | 0.0225623 | 2.18605 | 9.0462 | 1.57501 | 0.00125308 | 4.0422e-05 | 1.7128e-05 | 4(Loss) | true |
| glaze | 2020.76 | 0.102755 | 1708.25ms | 18245 | 30 | 2348.46 | 8610.53 | 0.0127767 | 2.51487 | 11.0265 | 2.13127 | 0.00329953 | 7.30794e-06 | 0 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6448.88 | 0.18894 | 1103.12ms | 24579 | 2560 | 120739 | 3634.79 | 0.264167 | 0.798041 | 1.76569 | 0.105782 | 9.72629e-05 | 1.98817e-05 | 1.01395e-05 | 1(Win) | true |
| glaze | 3842.05 | 0.26356 | 1353.29ms | 24579 | 320 | 82739.3 | 6101 | 0.129552 | 1.34922 | 3.98983 | 0.452297 | 0.000222751 | 1.47484e-05 | 8.13703e-06 | 2(Loss) | true |
| simdjson (reflection) | 537.915 | 0.103299 | 5159.88ms | 24893 | 4890 | 1.01631e+07 | 44133.1 | 0.208795 | 9.5164 | 36.5592 | 5.96489 | 0.00570787 | 0.000373985 | 0.000268782 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6460.61 | 0.195692 | 1110.25ms | 24579 | 2560 | 129052 | 3628.2 | 0.772174 | 0.78673 | 1.74442 | 0.100818 | 0.000101506 | 2.27741e-05 | 1.10613e-05 | 1(Win) | true |
| glaze | 4063.68 | 0.294569 | 1321.51ms | 24579 | 320 | 92387.9 | 5768.26 | 0.0191745 | 1.27574 | 3.84194 | 0.419057 | 0.000244111 | 1.79269e-05 | 6.61133e-06 | 2(Loss) | true |
| simdjson (reflection) | 536.518 | 0.140978 | 5186.11ms | 24893 | 2560 | 9.96167e+06 | 44248 | 0.118984 | 9.52568 | 36.5614 | 5.96574 | 0.00586708 | 0.000309465 | 0.000211232 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 928.187 | 0.102192 | 1203.83ms | 4604 | 320 | 7477.94 | 4730.42 | 0.208595 | 5.54434 | 21.6768 | 4.58319 | 0.00341754 | 5.70156e-05 | 4.07255e-06 | 1(Win) | true |
| jsonifier (two-stage) | 771.834 | 0.0546722 | 1313.74ms | 4604 | 1280 | 12381.3 | 5688.68 | 0.24228 | 6.57465 | 25.9818 | 5.1364 | 0.00580151 | 0.000173083 | 8.16206e-05 | 2(Loss) | true |
| simdjson (reflection) | 717.987 | 0.0916362 | 1353.79ms | 4604 | 320 | 10049 | 6115.31 | 0.0364996 | 7.04686 | 28.073 | 5.06408 | 0.00454971 | 0.000101135 | 4.2083e-05 | 3(Loss) | true |
| glaze | 640.256 | 0.120061 | 1418.62ms | 4604 | 320 | 21692.9 | 6857.75 | 0.0743587 | 7.93163 | 31.0355 | 6.45982 | 0.00846275 | 0.000123534 | 4.68343e-05 | 4(Loss) | true |
| simdjson (ondemand) | 594.505 | 0.124265 | 1488.41ms | 4604 | 160 | 13476.5 | 7385.5 | 0.057174 | 8.54598 | 33.4437 | 6.48567 | 0.00662603 | 0.000149327 | 6.10882e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1145.62 | 0.043924 | 1205.33ms | 4604 | 2560 | 7254.99 | 3832.63 | 0.0210409 | 4.49918 | 17.4739 | 3.62663 | 0.00239058 | 0.000135582 | 7.44088e-05 | 1(Win) | true |
| jsonifier (two-stage) | 920.033 | 0.0576789 | 1308.7ms | 4604 | 1280 | 9698.58 | 4772.35 | 0.0977938 | 5.54298 | 21.7819 | 4.18115 | 0.00556445 | 0.000156454 | 7.51724e-05 | 2(Loss) | true |
| simdjson (reflection) | 823.616 | 0.10407 | 1365.65ms | 4604 | 40 | 1231.2 | 5331.02 | 0.0638931 | 6.19074 | 25.8228 | 4.52085 | 0.00229149 | 0.000114031 | 3.80104e-05 | 3(Loss) | true |
| glaze | 742.728 | 0.0512136 | 1418.65ms | 4604 | 640 | 5866.28 | 5911.61 | 0.306057 | 6.85494 | 27.0394 | 5.54691 | 0.00660363 | 0.000133036 | 7.05908e-05 | 4(Loss) | true |
| simdjson (ondemand) | 643.101 | 0.0270416 | 1528.8ms | 4604 | 4890 | 16668.2 | 6827.42 | 0.114306 | 7.9274 | 32.1093 | 6.15226 | 0.00479551 | 0.000180691 | 0.00010869 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1463.26 | 0.039897 | 1054.5ms | 4918 | 4890 | 7996.93 | 3205.28 | 0.209889 | 3.51634 | 11.5458 | 1.38918 | 0.000502973 | 0.000151732 | 8.68227e-05 | 1(Win) | true |
| jsonifier | 1346.18 | 0.152826 | 1062.97ms | 4604 | 4890 | 121498 | 3261.61 | 0.132825 | 3.85085 | 8.84036 | 0.542138 | 0.000300219 | 0.000171541 | 0.000106203 | 2(Loss) | true |
| glaze | 1150.53 | 0.0821693 | 1117.53ms | 4604 | 2560 | 25172.7 | 3816.24 | 0.407413 | 4.40147 | 12.7263 | 1.12294 | 0.000659074 | 7.40694e-05 | 3.95376e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1490.95 | 0.115205 | 1044.32ms | 4918 | 320 | 4202.83 | 3145.77 | 0.0299102 | 3.43699 | 11.4274 | 1.36234 | 0.000667827 | 4.25732e-05 | 8.89589e-06 | 1(Win) | true |
| jsonifier | 1354.74 | 0.391761 | 1063.67ms | 4604 | 640 | 103176 | 3241 | 0.491743 | 3.77954 | 8.76955 | 0.525195 | 0.000308156 | 6.82151e-05 | 2.07021e-05 | 2(Loss) | true |
| glaze | 1215.35 | 0.170556 | 1098.27ms | 4604 | 640 | 24298.6 | 3612.72 | 0.103994 | 4.25766 | 12.2407 | 1.01195 | 0.000738149 | 0.000122176 | 6.58395e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2686.83 | 0.0375183 | 1399.72ms | 18245 | 2560 | 15112.4 | 6475.95 | 0.268711 | 1.88506 | 7.51302 | 1.34245 | 0.00154235 | 7.15307e-05 | 4.4704e-05 | 1(Win) | true |
| simdjson (reflection) | 2588.72 | 0.0764491 | 1411.21ms | 18245 | 320 | 8449.12 | 6721.38 | 0.143829 | 1.96409 | 8.08419 | 1.31083 | 0.00125343 | 4.05933e-05 | 2.53494e-05 | 2(Loss) | true |
| jsonifier | 2451.46 | 0.0983704 | 1446.41ms | 18245 | 30 | 1462.48 | 7097.73 | 0.104367 | 2.11605 | 7.88457 | 1.79271 | 0.00130995 | 1.64429e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2154.17 | 0.112617 | 1540.81ms | 18245 | 30 | 2482.34 | 8077.27 | 0.0259921 | 2.35963 | 9.45788 | 1.67312 | 0.00167717 | 2.74048e-05 | 7.30794e-06 | 4(Loss) | true |
| glaze | 1862.84 | 0.0611258 | 1679.25ms | 18245 | 640 | 20862.3 | 9340.44 | 0.244664 | 2.75051 | 11.8968 | 2.33176 | 0.00342988 | 2.25233e-05 | 1.11332e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3152.45 | 0.0669934 | 1386.88ms | 18245 | 80 | 1093.82 | 5519.45 | 0.0144963 | 1.61998 | 6.45322 | 1.1014 | 0.00142916 | 1.50726e-05 | 4.79583e-06 | 1(Win) | true |
| simdjson (reflection) | 2983.62 | 0.215787 | 1417.59ms | 18245 | 30 | 4750.87 | 5831.77 | 0.008573 | 1.7427 | 7.51346 | 1.17287 | 0.000533479 | 7.12524e-05 | 4.93286e-05 | 2(Loss) | true |
| jsonifier | 2844.06 | 0.0514892 | 1449.36ms | 18245 | 40 | 396.921 | 6117.95 | 0.0444246 | 1.82594 | 6.82521 | 1.55171 | 0.000927651 | 8.22143e-06 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2330.69 | 0.0649978 | 1585.11ms | 18245 | 80 | 1883.67 | 7465.5 | 0.0739524 | 2.18372 | 9.08501 | 1.58131 | 0.00137914 | 2.60345e-05 | 1.09619e-05 | 4(Loss) | true |
| glaze | 2030.28 | 0.0843436 | 1683.69ms | 18245 | 40 | 2089.98 | 8570.15 | 0.0184784 | 2.50307 | 10.8854 | 2.10129 | 0.00316525 | 8.22143e-06 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6302.55 | 0.235702 | 1103ms | 24579 | 640 | 49181.5 | 3719.19 | 0.56211 | 0.811185 | 1.76106 | 0.105578 | 8.85537e-05 | 4.49444e-05 | 2.92424e-05 | 1(Win) | true |
| glaze | 3653.74 | 0.102128 | 1386.2ms | 24579 | 2560 | 109895 | 6415.44 | 0.0588222 | 1.40147 | 3.99135 | 0.451079 | 0.00035938 | 4.7217e-05 | 2.90517e-05 | 2(Loss) | true |
| simdjson (reflection) | 501.213 | 0.0901676 | 5471.96ms | 24893 | 4890 | 8.9191e+06 | 47364.8 | 0.105077 | 10.0745 | 36.5138 | 5.952 | 0.00688876 | 0.000164968 | 0.000100742 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6563.93 | 0.174428 | 1094.94ms | 24579 | 1280 | 49663.8 | 3571.08 | 0.0449154 | 0.792927 | 1.73978 | 0.100615 | 6.45241e-05 | 2.64136e-05 | 1.41444e-05 | 1(Win) | true |
| glaze | 3880.43 | 0.0723817 | 1341.75ms | 24579 | 4890 | 93483.4 | 6040.65 | 0.354291 | 1.30897 | 3.84572 | 0.41804 | 0.000350824 | 3.7848e-05 | 1.93858e-05 | 2(Loss) | true |
| simdjson (reflection) | 499.711 | 0.125348 | 5512.87ms | 24893 | 4890 | 1.73405e+07 | 47507.1 | 0.100199 | 10.1097 | 36.5164 | 5.95292 | 0.00712487 | 0.000218498 | 0.000129207 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1666.89 | 0.0819732 | 1029.35ms | 5094 | 40 | 228.302 | 2914.43 | 0.0437288 | 3.07563 | 13.3545 | 2.3987 | 0.00052022 | 0.000127601 | 1.47232e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1564.84 | 0.0506563 | 1048.74ms | 5094 | 1280 | 3165.59 | 3104.48 | 0.0885535 | 3.27615 | 14.2729 | 2.45917 | 0.00177936 | 0.000131895 | 6.07332e-05 | 2(Loss) | true |
| glaze | 1334.67 | 0.0408507 | 1103.48ms | 5094 | 4890 | 10811.3 | 3639.86 | 0.0772867 | 3.83139 | 16.3289 | 3.10955 | 0.00314998 | 8.01697e-05 | 2.8222e-05 | 3(Loss) | true |
| simdjson (reflection) | 1200.94 | 0.0892829 | 1148.86ms | 5094 | 640 | 8348.17 | 4045.18 | 0.078202 | 4.24825 | 15.8288 | 2.60993 | 0.00432893 | 0.000138337 | 6.16534e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1147.97 | 0.062397 | 1166.71ms | 5094 | 40 | 278.9 | 4231.85 | 0.0547136 | 4.44793 | 16.1396 | 2.87947 | 0.00467216 | 2.94464e-05 | 0 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2040.09 | 0.188087 | 1029.23ms | 5094 | 40 | 802.41 | 2381.28 | 0.0863636 | 2.4771 | 10.8791 | 1.83922 | 0.000211033 | 8.34315e-05 | 1.96309e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1894.46 | 0.0571319 | 1051.6ms | 5094 | 2560 | 5494.73 | 2564.33 | 0.00143192 | 2.70287 | 12.0332 | 1.94503 | 0.00100785 | 7.92139e-05 | 2.53055e-05 | 2(Loss) | true |
| glaze | 1757.47 | 0.0417701 | 1068.49ms | 5094 | 4890 | 6519.06 | 2764.22 | 0.0800965 | 2.92223 | 13.0526 | 2.42737 | 0.00265588 | 8.71549e-05 | 3.08716e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1415.15 | 0.054881 | 1140.72ms | 5094 | 2560 | 9086.56 | 3432.87 | 0.121652 | 3.59422 | 13.3854 | 2.30429 | 0.0033766 | 9.98417e-05 | 4.20992e-05 | 4(Loss) | true |
| simdjson (reflection) | 1376.99 | 0.0992514 | 1157.72ms | 5094 | 640 | 7847.12 | 3528 | 0.047853 | 3.71228 | 15.0124 | 2.39556 | 0.00160452 | 5.9813e-05 | 1.47232e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12984.9 | 0.226705 | 771.162ms | 5094 | 640 | 460.409 | 374.128 | 0.0350693 | 0.431293 | 1.62996 | 0.26168 | 0.00019723 | 1.77905e-05 | 9.202e-07 | 1(Win) | true |
| simdjson (reflection) | 7559.23 | 0.14259 | 804.318ms | 5094 | 4890 | 4106.28 | 642.661 | 0.137311 | 0.703812 | 2.56792 | 0.342167 | 0.000196871 | 5.43163e-05 | 2.42476e-05 | 2(Loss) | true |
| glaze | 4191.6 | 0.182309 | 853.231ms | 5094 | 320 | 1428.65 | 1158.99 | 0.130332 | 1.24959 | 5.53043 | 0.895563 | 0.000197536 | 0.000138644 | 6.13467e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14395.6 | 0.251304 | 769.889ms | 5094 | 640 | 460.296 | 337.466 | 0.188336 | 0.390319 | 1.53141 | 0.239105 | 0.00019907 | 1.90175e-05 | 4.601e-06 | 1(Win) | true |
| simdjson (reflection) | 8107.76 | 0.118057 | 799.296ms | 5094 | 160 | 80.0613 | 599.181 | 0.319158 | 0.659846 | 2.4523 | 0.316058 | 0.000196309 | 1.71771e-05 | 1.10424e-05 | 2(Loss) | true |
| glaze | 4681.97 | 0.306004 | 836.934ms | 5094 | 640 | 6452.01 | 1037.6 | 0.187078 | 1.11726 | 5.07303 | 0.792501 | 0.000343235 | 9.44739e-05 | 5.79726e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2288.88 | 0.088737 | 1074.76ms | 8051 | 640 | 5670.81 | 3354.5 | 0.339709 | 2.19252 | 9.53695 | 1.5654 | 0.000957179 | 5.82226e-05 | 1.94075e-05 | 1(Win) | true |
| jsonifier | 1890.4 | 0.072413 | 1149.14ms | 8051 | 1280 | 11072.3 | 4061.6 | 0.248437 | 2.69842 | 10.6954 | 2.11253 | 0.000514008 | 6.62767e-05 | 2.50357e-05 | 2(Loss) | true |
| simdjson (reflection) | 1837.33 | 0.0439105 | 1166.44ms | 8051 | 4890 | 16465.4 | 4178.91 | 0.116675 | 2.74593 | 10.5275 | 1.66998 | 0.00250588 | 7.65061e-05 | 3.20554e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1761.21 | 0.105946 | 1184.53ms | 8051 | 320 | 6826.46 | 4359.52 | 0.0406989 | 2.89501 | 10.7393 | 1.84387 | 0.0028137 | 2.75587e-05 | 5.04596e-06 | 4(Loss) | true |
| glaze | 1671.07 | 0.129097 | 1201.66ms | 8051 | 40 | 1407.35 | 4594.68 | 0.054622 | 2.99596 | 12.7993 | 2.4859 | 0.00231338 | 3.1052e-05 | 6.21041e-06 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2820.18 | 0.0570945 | 1067.66ms | 8051 | 2560 | 6185.49 | 2722.53 | 0.0262778 | 1.80844 | 8.11991 | 1.2401 | 0.00055229 | 4.29392e-05 | 1.00919e-05 | 1(Win) | true |
| jsonifier | 2209.9 | 0.108897 | 1150ms | 8051 | 640 | 9161.51 | 3474.39 | 0.0456224 | 2.31405 | 9.12955 | 1.75866 | 0.000137017 | 0.000114116 | 6.11337e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2160.06 | 0.136921 | 1162.5ms | 8051 | 40 | 947.485 | 3554.55 | 0.0604493 | 2.37368 | 8.98696 | 1.4777 | 0.00208359 | 3.41572e-05 | 1.24208e-05 | 3(Loss) | true |
| glaze | 2106.93 | 0.145171 | 1160.93ms | 8051 | 40 | 1119.48 | 3644.18 | 0.074721 | 2.4281 | 10.7903 | 2.06695 | 0.00205254 | 3.1052e-05 | 0 | 4(Loss) | true |
| simdjson (reflection) | 2064.28 | 0.0874192 | 1181.42ms | 8051 | 1280 | 13532.7 | 3719.46 | 0.131387 | 2.44102 | 10.0002 | 1.53236 | 0.00102452 | 5.12359e-05 | 1.22267e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21503 | 0.333713 | 780.605ms | 9255 | 320 | 600.413 | 410.466 | 0.0737946 | 0.257641 | 0.961534 | 0.145327 | 0.00010805 | 1.89087e-05 | 3.71421e-06 | 1(Win) | true |
| glaze | 4817.48 | 0.0880375 | 927.146ms | 9255 | 2560 | 6660.23 | 1832.13 | 0.394154 | 1.07312 | 4.50902 | 0.680281 | 0.0001094 | 5.00574e-05 | 2.23697e-05 | 2(Loss) | true |
| simdjson (reflection) | 568.521 | 0.265163 | 2283.92ms | 9255 | 320 | 542296 | 15525 | 0.102733 | 8.70348 | 37.0609 | 7.03916 | 0.00874595 | 0.000397758 | 0.000276877 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24632.3 | 0.0723513 | 771.445ms | 9255 | 4890 | 328.658 | 358.321 | 0.196381 | 0.227019 | 0.900702 | 0.131605 | 0.000108337 | 1.61301e-05 | 6.6951e-06 | 1(Win) | true |
| glaze | 5697.89 | 0.121244 | 893.128ms | 9255 | 1280 | 4515 | 1549.04 | 0.147638 | 0.906035 | 4.1718 | 0.604322 | 0.000148737 | 4.18693e-05 | 1.90775e-05 | 2(Loss) | true |
| simdjson (reflection) | 570.824 | 0.119381 | 2299.77ms | 9255 | 2560 | 872288 | 15462.3 | 0.243072 | 8.69487 | 37.072 | 7.0403 | 0.00928582 | 0.00023332 | 0.000131854 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5836.09 | 0.143599 | 786.529ms | 2889 | 2560 | 1176.5 | 472.091 | 0.145426 | 0.938666 | 3.49152 | 0.436829 | 0.000346952 | 3.25859e-05 | 7.03098e-06 | 1(Win) | true |
| jsonifier (two-stage) | 5770.05 | 0.141035 | 789.766ms | 2889 | 2560 | 1160.99 | 477.495 | 0.246123 | 0.941368 | 3.49152 | 0.436829 | 0.000347222 | 5.51661e-05 | 2.90704e-05 | 2(Loss) | true |
| simdjson (ondemand) | 5651.54 | 0.168266 | 784.876ms | 2889 | 2560 | 1722.64 | 487.507 | 0.0820629 | 0.958741 | 3.74559 | 0.364487 | 0.000348033 | 4.15098e-05 | 1.37915e-05 | 3(Loss) | true |
| simdjson (reflection) | 5407.92 | 0.0964416 | 783.63ms | 2889 | 1280 | 309.011 | 509.469 | 0.0021468 | 1.00708 | 3.85324 | 0.398062 | 0.000558692 | 6.32788e-05 | 2.73127e-05 | 4(Loss) | true |
| glaze | 2683.49 | 0.140528 | 838.764ms | 2889 | 2560 | 5329.16 | 1026.71 | 0.0832765 | 1.95442 | 8.39426 | 1.3008 | 0.000352631 | 2.06873e-05 | 5.81408e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6088.29 | 0.0894909 | 783.08ms | 2889 | 4890 | 801.995 | 452.535 | 0.0941228 | 0.902721 | 3.34545 | 0.402562 | 0.000346848 | 3.24905e-05 | 9.55603e-06 | 1(Win) | true |
| jsonifier (two-stage) | 6069.76 | 0.0734505 | 788.151ms | 2889 | 2560 | 284.566 | 453.917 | 0.157646 | 0.899242 | 3.34545 | 0.402561 | 0.000346141 | 4.50253e-05 | 2.04169e-05 | 2(Loss) | true |
| simdjson (ondemand) | 5900.73 | 0.0753634 | 779.808ms | 2889 | 1280 | 158.495 | 466.92 | 0.0396391 | 0.929705 | 3.67082 | 0.346141 | 0.000346141 | 4.75943e-05 | 2.29859e-05 | 3(Loss) | true |
| simdjson (reflection) | 5592.82 | 0.0559325 | 785.138ms | 2889 | 2560 | 194.357 | 492.625 | 0.218849 | 0.973466 | 3.7847 | 0.380755 | 0.000346411 | 3.71831e-05 | 1.36563e-05 | 4(Loss) | true |
| glaze | 2734.76 | 0.14044 | 837.68ms | 2889 | 80 | 160.15 | 1007.46 | 0.016127 | 1.92089 | 8.3226 | 1.28245 | 0.000346141 | 2.59605e-05 | 2.16338e-05 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 6815.81 | 0.18915 | 788.636ms | 3808 | 160 | 162.514 | 532.819 | 0.03635 | 0.798616 | 3.19275 | 0.292017 | 0.000262605 | 5.41623e-05 | 2.46192e-05 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 6809.09 | 0.0482699 | 790.819ms | 3808 | 2560 | 169.671 | 533.345 | 0.251023 | 0.798025 | 3.04175 | 0.33771 | 0.000262605 | 2.90302e-05 | 9.74511e-06 | 1(Tie) | true |
| jsonifier (two-stage) | 6726.98 | 0.122767 | 792.973ms | 3808 | 640 | 281.123 | 539.855 | 0.0298202 | 0.802068 | 3.04175 | 0.33771 | 0.000262605 | 4.59559e-05 | 1.72335e-05 | 3(Loss) | true |
| simdjson (reflection) | 6525.64 | 0.082188 | 785.877ms | 3808 | 1280 | 267.778 | 556.511 | 0.178606 | 0.8422 | 3.27442 | 0.317489 | 0.000262605 | 4.30836e-05 | 2.40037e-05 | 4(Loss) | true |
| glaze | 3094.21 | 0.159937 | 855.711ms | 3808 | 80 | 281.893 | 1173.67 | 0.0532232 | 1.69343 | 7.65704 | 1.2802 | 0.00052521 | 2.29779e-05 | 6.56513e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7074.03 | 0.0618486 | 791.371ms | 3808 | 2560 | 258.084 | 513.37 | 0.153863 | 0.768114 | 2.93093 | 0.311712 | 0.000262708 | 3.48772e-05 | 1.15916e-05 | 1(Win) | true |
| simdjson (ondemand) | 6997.38 | 0.0575106 | 786.545ms | 3808 | 4890 | 435.64 | 518.993 | 0.107384 | 0.774021 | 3.13655 | 0.278099 | 0.000263411 | 2.0568e-05 | 4.94063e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 6962.87 | 0.197406 | 790.639ms | 3808 | 320 | 339.225 | 521.566 | 0.0856062 | 0.770615 | 2.93093 | 0.311712 | 0.000262605 | 3.85701e-05 | 1.31303e-05 | 3(Loss) | true |
| simdjson (reflection) | 6662.6 | 0.150094 | 784.388ms | 3808 | 2560 | 1713.46 | 545.071 | 0.0838465 | 0.813731 | 3.22295 | 0.304359 | 0.000263733 | 2.28754e-05 | 6.05223e-06 | 4(Loss) | true |
| glaze | 3122.58 | 0.0898426 | 856.252ms | 3808 | 640 | 698.734 | 1163.01 | 0.0162589 | 1.67508 | 7.6011 | 1.26628 | 0.000536289 | 1.35406e-05 | 8.20641e-07 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2906.64 | 0.100607 | 834.462ms | 2889 | 160 | 145.509 | 947.888 | 0.0751107 | 1.82518 | 5.93493 | 0.991695 | 0.00064685 | 6.49013e-05 | 1.29803e-05 | 1(Win) | true |
| glaze | 2345.97 | 0.240019 | 853.204ms | 2889 | 1280 | 10170.7 | 1174.42 | 0.156438 | 2.22803 | 8.90516 | 1.51298 | 0.000380755 | 0.000114118 | 6.40901e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2297.05 | 0.294375 | 858.725ms | 2889 | 160 | 1994.7 | 1199.44 | 0.0490053 | 2.27543 | 7.61509 | 1.15542 | 0.000378591 | 9.30253e-05 | 2.16338e-05 | 3(Loss) | true |
| simdjson (reflection) | 2105.02 | 0.0827546 | 871.66ms | 2889 | 4890 | 5736.88 | 1308.85 | 0.0413544 | 2.46512 | 8.82901 | 1.36379 | 0.000349892 | 0.000232955 | 0.000126918 | 4(Loss) | true |
| simdjson (ondemand) | 1699.36 | 0.112103 | 900.012ms | 2889 | 640 | 2114.15 | 1621.3 | 0.058147 | 3.04942 | 9.48979 | 1.65109 | 0.000707425 | 2.27155e-05 | 1.62253e-06 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3187.22 | 0.29567 | 829.94ms | 2889 | 1280 | 8361.73 | 864.441 | 0.0542867 | 1.66759 | 5.41468 | 0.85393 | 0.000607909 | 7.59887e-05 | 3.24507e-05 | 1(Win) | true |
| glaze | 2572.95 | 0.075639 | 848.235ms | 2889 | 4890 | 3208 | 1070.82 | 0.0572785 | 2.03986 | 8.36803 | 1.3697 | 0.000358457 | 0.000132793 | 8.47301e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2535.12 | 0.134038 | 853.639ms | 2889 | 40 | 84.8821 | 1086.8 | 0.128985 | 2.07055 | 7.0945 | 1.01661 | 0.000346141 | 3.46141e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 2289.87 | 0.0807948 | 867.417ms | 2889 | 2560 | 2419.25 | 1203.2 | 0.0753283 | 2.28117 | 8.31499 | 1.22949 | 0.000365205 | 9.68112e-05 | 4.0969e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1791.47 | 0.0684853 | 899.625ms | 2889 | 2560 | 2839.94 | 1537.93 | 0.149699 | 2.89952 | 9.108 | 1.54967 | 0.000599932 | 0.000121555 | 7.05802e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8542.45 | 0.122833 | 768.789ms | 2963 | 80 | 13.2074 | 330.788 | 0.0188907 | 0.663331 | 1.48296 | 0.238947 | 0.000337496 | 8.43739e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 6038.06 | 0.0996682 | 784.669ms | 2963 | 80 | 17.4049 | 467.988 | 0.284984 | 0.913057 | 1.91259 | 0.299359 | 0.000345933 | 6.32805e-05 | 1.68748e-05 | 2(Loss) | true |
| glaze | 5675.11 | 0.129231 | 785.465ms | 2963 | 4890 | 2024.69 | 497.917 | 0.400691 | 0.957996 | 2.97739 | 0.460345 | 0.000343776 | 0.000107115 | 5.34886e-05 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9850.92 | 0.112503 | 763.88ms | 2963 | 80 | 8.33165 | 286.85 | 0.244627 | 0.586125 | 1.31522 | 0.199798 | 0.000337496 | 1.68748e-05 | 0 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 6743.5 | 0.0603116 | 775.184ms | 2963 | 160 | 10.2191 | 419.031 | 0.00149156 | 0.825597 | 1.74587 | 0.260884 | 0.000337496 | 2.32028e-05 | 0 | 2(Tie) | true |
| glaze STATISTICAL TIE | 6733.19 | 0.168684 | 775.708ms | 2963 | 2560 | 1282.96 | 419.673 | 0.0189916 | 0.819038 | 2.58252 | 0.378333 | 0.000339737 | 4.44282e-05 | 1.59519e-05 | 2(Tie) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2789.3 | 0.0683366 | 865.23ms | 3808 | 4890 | 3870.97 | 1301.97 | 0.144359 | 1.86868 | 6.31014 | 0.910978 | 0.000268888 | 5.09099e-05 | 1.74533e-05 | 1(Win) | true |
| simdjson (reflection) | 2706.88 | 0.0568222 | 868.124ms | 3808 | 4890 | 2841.85 | 1341.61 | 0.257617 | 1.93066 | 7.04622 | 1.04937 | 0.000274151 | 0.000107459 | 3.82899e-05 | 2(Loss) | true |
| glaze | 2418.54 | 0.0387874 | 884.847ms | 3808 | 1280 | 434.191 | 1501.57 | 0.0536186 | 2.14783 | 8.53046 | 1.50998 | 0.000262605 | 8.08331e-05 | 4.45198e-05 | 3(Loss) | true |
| jsonifier | 2315.33 | 0.0503099 | 896.169ms | 3808 | 4890 | 3044.96 | 1568.5 | 0.138014 | 2.24376 | 6.03414 | 1.15205 | 0.000351429 | 0.000114816 | 6.06301e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2140.34 | 0.0476217 | 904.243ms | 3808 | 4890 | 3192.62 | 1696.74 | 0.28382 | 2.42067 | 7.55068 | 1.26812 | 0.000274044 | 0.000135814 | 7.66871e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3159.65 | 0.176663 | 856.166ms | 3808 | 30 | 123.689 | 1149.37 | 0.0116019 | 1.66373 | 5.7823 | 0.779412 | 0.000332633 | 7.0028e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 2902.26 | 0.223566 | 864.505ms | 3808 | 40 | 313.036 | 1251.3 | 0.0106544 | 1.80179 | 6.65572 | 0.947216 | 0.000492384 | 0.000190389 | 3.28256e-05 | 2(Loss) | true |
| glaze | 2579.25 | 0.0382024 | 881.078ms | 3808 | 4890 | 1414.8 | 1408 | 0.000673832 | 2.01715 | 8.1229 | 1.40126 | 0.000266149 | 3.72695e-05 | 1.03109e-05 | 3(Loss) | true |
| jsonifier | 2509.04 | 0.14244 | 888.027ms | 3808 | 640 | 2720.35 | 1447.4 | 0.183964 | 2.0732 | 5.63997 | 1.04779 | 0.000284352 | 4.88281e-05 | 1.84644e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2286.11 | 0.0924456 | 901.586ms | 3808 | 320 | 690.117 | 1588.55 | 0.0817058 | 2.27045 | 7.26155 | 1.19118 | 0.000517004 | 7.87815e-05 | 3.69288e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12446.8 | 0.168292 | 766.711ms | 4300 | 30 | 9.22299 | 329.467 | 0.0202388 | 0.456798 | 1.02674 | 0.155581 | 0.000232558 | 7.75194e-06 | 0 | 1(Win) | true |
| glaze | 3900.86 | 0.333831 | 841.182ms | 4300 | 1280 | 15764.4 | 1051.25 | 0.581691 | 1.34227 | 3.45698 | 0.513489 | 0.000234738 | 0.000132631 | 7.83067e-05 | 2(Loss) | true |
| simdjson (reflection) | 554.966 | 0.0669543 | 1484.62ms | 4300 | 2560 | 62661.6 | 7389.28 | 0.0323474 | 9.15639 | 33.9658 | 7.1907 | 0.00396566 | 0.000191951 | 8.34847e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13613.1 | 0.0451101 | 761.481ms | 4300 | 4890 | 90.2978 | 301.238 | 0.102731 | 0.422337 | 0.952093 | 0.137674 | 0.000232558 | 4.59409e-05 | 2.03548e-05 | 1(Win) | true |
| glaze | 4725.33 | 0.193909 | 823.539ms | 4300 | 4890 | 13847.6 | 867.833 | 0.660239 | 1.11601 | 2.91279 | 0.388837 | 0.000233557 | 5.28844e-05 | 3.31003e-05 | 2(Loss) | true |
| simdjson (reflection) | 554.033 | 0.0547643 | 1488.11ms | 4300 | 4890 | 80347.1 | 7401.73 | 0.0399923 | 9.123 | 33.9736 | 7.19291 | 0.00396305 | 0.000339516 | 0.000163219 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3254.87 | 0.0887525 | 7389.72ms | 466906 | 320 | 4.71741e+06 | 136803 | 0.0525639 | 1.54988 | 6.14059 | 1.26003 | 0.0019789 | 0.00121294 | 9.14933e-06 | 1(Win) | true |
| glaze | 2388.28 | 0.0283512 | 9898.91ms | 466906 | 1280 | 3.57635e+06 | 186442 | 0.0393621 | 2.10436 | 8.76986 | 1.98463 | 0.00256965 | 0.000217176 | 3.90185e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1381.98 | 0.154625 | 8455.69ms | 466906 | 320 | 7.94263e+07 | 322202 | 0.113001 | 3.63172 | 14.0984 | 2.46273 | 0.0137695 | 0.0932617 | 2.1605e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3248.93 | 0.0941413 | 7354.63ms | 466906 | 320 | 5.32708e+06 | 137053 | 0.0458609 | 1.55184 | 6.13946 | 1.25977 | 0.0019899 | 0.00138267 | 2.71602e-05 | 1(Win) | true |
| glaze | 2393.09 | 0.0186646 | 9867.25ms | 466906 | 1280 | 1.54378e+06 | 186067 | 0.143938 | 2.11207 | 8.76876 | 1.98438 | 0.00260902 | 0.000146093 | 2.1088e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1378.56 | 0.10846 | 8515.24ms | 466906 | 640 | 7.85469e+07 | 323002 | 0.0222095 | 3.6429 | 14.0984 | 2.46272 | 0.0139786 | 0.0964328 | 3.50044e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4223.25 | 0.0479781 | 8473.31ms | 699405 | 2560 | 1.46991e+07 | 157936 | 0.00260828 | 1.18102 | 4.52389 | 1.13909 | 0.00128932 | 0.00228585 | 1.72144e-05 | 1(Win) | true |
| glaze | 3667.78 | 0.0458799 | 9673.05ms | 699405 | 2560 | 1.78212e+07 | 181855 | 0.100207 | 1.37671 | 6.02374 | 1.25783 | 0.00211336 | 0.00177238 | 3.50638e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1449.44 | 0.724973 | 6531.32ms | 767297 | 160 | 2.14332e+09 | 504850 | 0.307077 | 3.45113 | 13.5134 | 2.23507 | 0.0123136 | 0.0768057 | 8.13244e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4277.04 | 0.0595163 | 8433.34ms | 699405 | 1280 | 1.10269e+07 | 155950 | 0.147744 | 1.1701 | 4.52339 | 1.13899 | 0.00130085 | 0.00221723 | 3.60999e-05 | 1(Win) | true |
| glaze | 3673.19 | 0.0213469 | 9676.82ms | 699405 | 2560 | 3.84663e+06 | 181587 | 0.11243 | 1.37539 | 6.02304 | 1.25768 | 0.00212584 | 0.00168672 | 3.03863e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1428.77 | 0.296593 | 6640.4ms | 767297 | 640 | 1.47673e+09 | 512154 | 0.163398 | 3.46483 | 13.5133 | 2.23504 | 0.0124439 | 0.0918214 | 0.000144281 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2939.75 | 0.0689026 | 5411.22ms | 631514 | 1280 | 2.55052e+07 | 204868 | 0.0604495 | 1.68814 | 8.03853 | 1.32344 | 0.0053879 | 2.30201e-05 | 1.97838e-05 | 1(Win) | true |
| glaze | 2443.99 | 0.0441827 | 6490.96ms | 631514 | 1280 | 1.51734e+07 | 246425 | 0.0319051 | 2.05269 | 8.43595 | 1.51701 | 0.00845038 | 4.84686e-05 | 4.10497e-05 | 2(Loss) | true |
