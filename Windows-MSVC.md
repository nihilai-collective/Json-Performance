# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.51.36260.0 compiler).  

Latest Results: (Oct 29, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| Glaze: [f67610b](https://github.com/stephenberry/glaze/commit/f67610b)  
| Simdjson: [9262482](https://github.com/simdjson/simdjson/commit/9262482)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation / Backends |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |
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
* **simdjson (reflection):** Absent from this run; current toolchain lacks P2996 static reflection support.
* **Jsonifier:** Evaluates both fused scalar structural iteration and two-stage indexing. Partial tests default strictly to two-stage parsing.
* **Summary Rows:** `*(combined)` metrics display best-of-variant ranks and are not additive with isolated test results.

---
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 522.285 | 0.483897 | 345.813ms | 905 | 40 | 2557.69 | 1652.5 | 1.24502 | 5.79304 | 1(Win) | true |
| glaze | 336.228 | 0.359089 | 359.001ms | 905 | 4890 | 415472 | 2566.93 | 0.00832835 | 8.97389 | 2(Loss) | true |
| jsonifier (two-stage) | 270.848 | 0.215832 | 620.64ms | 905 | 640 | 30273 | 3186.56 | 0.76087 | 11.1436 | 3(Loss) | true |
| simdjson (ondemand) | 92.8787 | 0.104729 | 1492.52ms | 905 | 40 | 3788.46 | 9292.5 | 0.423271 | 32.6328 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 595.738 | 0.273616 | 298.33ms | 905 | 160 | 2514.15 | 1448.75 | 1.66667 | 5.04059 | 1(Win) | true |
| glaze | 360.889 | 0.263246 | 340.938ms | 905 | 2560 | 101464 | 2391.52 | 0.249283 | 8.29326 | 2(Loss) | true |
| jsonifier (two-stage) | 278.784 | 0.457489 | 597.696ms | 905 | 2560 | 513527 | 3095.86 | 0.0201842 | 10.8395 | 3(Loss) | true |
| simdjson (ondemand) | 92.2335 | 0.50747 | 1447.01ms | 905 | 40 | 90198.7 | 9357.5 | 0.402361 | 32.9076 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1194.37 | 0.326384 | 108.008ms | 905 | 2560 | 14240.1 | 722.617 | 0.0594981 | 2.48489 | 1(Win) | true |
| glaze DID NOT CONVERGE | 23.8155 | 1.08217 | 1568.6ms | 905 | 40 | 6.15221e+06 | 36240 | 9.48297 | 127.262 | -(Loss) | false |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1802.77 | 0.961352 | 126.62ms | 905 | 80 | 1694.62 | 478.75 | 0.26178 | 1.61634 | 1(Win) | true |
| glaze | 294.565 | 0.290431 | 494.897ms | 905 | 30 | 2172.41 | 2930 | 0.227015 | 10.2575 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 695.055 | 0.467638 | 383.967ms | 1811 | 4890 | 660280 | 2484.85 | 0.518415 | 4.33882 | 1(Win) | true |
| jsonifier (two-stage) | 532.509 | 0.283716 | 513.012ms | 1811 | 30 | 2540.23 | 3243.33 | 0.409417 | 5.67639 | 2(Loss) | true |
| glaze | 352.611 | 0.415918 | 769.117ms | 1811 | 1280 | 531216 | 4898.05 | 0.190169 | 8.58365 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 145.318 | 0.611916 | 2423.2ms | 1811 | 40 | 211564 | 11885 | 2.5748 | 20.8777 | -(Loss) | false |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 849.874 | 0.216636 | 261.41ms | 1811 | 320 | 6202.1 | 2032.19 | 0.200308 | 3.5142 | 1(Win) | true |
| jsonifier (two-stage) | 581.562 | 0.268214 | 517.727ms | 1811 | 2560 | 162423 | 2969.77 | 0.788203 | 5.16764 | 2(Loss) | true |
| glaze | 406.587 | 0.220537 | 645.606ms | 1811 | 320 | 28083 | 4247.81 | 0.0662544 | 7.38352 | 3(Loss) | true |
| simdjson (ondemand) | 152.544 | 0.357998 | 2263.44ms | 1811 | 640 | 1.05145e+06 | 11322 | 0.353156 | 19.8822 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 470.601 | 0.479948 | 770.661ms | 1811 | 40 | 12410.3 | 3670 | 0.542005 | 6.42634 | 1(Win) | true |
| glaze | 150.586 | 0.987807 | 2326.49ms | 1798 | 160 | 2.02429e+06 | 11386.9 | 0.280713 | 20.1412 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 779.291 | 0.137938 | 465.803ms | 1811 | 160 | 1495.28 | 2216.25 | 0.168919 | 3.84706 | 1(Win) | true |
| glaze | 384.176 | 0.20049 | 870.193ms | 1798 | 30 | 2402.3 | 4463.33 | 0.0746269 | 7.87772 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1705.38 | 0.325903 | 453.921ms | 3862 | 640 | 31705.7 | 2159.69 | 0.028931 | 1.7681 | 1(Win) | true |
| glaze | 910.037 | 0.126828 | 786.003ms | 3862 | 640 | 16862.2 | 4047.19 | 0.903779 | 3.32472 | 2(Loss) | true |
| jsonifier (two-stage) | 889.635 | 0.219739 | 843.431ms | 3862 | 30 | 2482.76 | 4140 | 0.404204 | 3.40025 | 3(Loss) | true |
| simdjson (ondemand) | 321.527 | 0.0695441 | 2326.5ms | 3862 | 40 | 2538.46 | 11455 | 0.101952 | 9.44147 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2132.03 | 0.290806 | 361.084ms | 3862 | 80 | 2018.99 | 1727.5 | 0.860832 | 1.40318 | 1(Win) | true |
| glaze | 1005.39 | 0.244274 | 563.121ms | 3862 | 30 | 2402.3 | 3663.33 | 0.272232 | 2.98928 | 2(Loss) | true |
| jsonifier (two-stage) | 937.024 | 0.218701 | 792.961ms | 3862 | 160 | 11823.5 | 3930.62 | 1.30477 | 3.2118 | 3(Loss) | true |
| simdjson (ondemand) | 327.75 | 0.0689848 | 2275.3ms | 3862 | 40 | 2403.85 | 11237.5 | 0.0964964 | 9.23884 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 502.983 | 0.586573 | 1477.94ms | 3862 | 80 | 147589 | 7322.5 | 0.475705 | 6.02048 | 1(Win) | true |
| glaze | 372.735 | 1.34319 | 2014.94ms | 3862 | 160 | 2.81851e+06 | 9881.25 | 0.228224 | 8.12915 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4169.54 | 0.783448 | 197.518ms | 3862 | 30 | 1436.78 | 883.333 | 0 | 0.711592 | 1(Win) | true |
| glaze | 1062.17 | 0.239679 | 756.761ms | 3862 | 40 | 2762.82 | 3467.5 | 1.11692 | 2.8294 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 988.292 | 0.168364 | 1902.54ms | 9578 | 40 | 9685.9 | 9242.5 | 0.0450613 | 3.06475 | 1(Win) | true |
| jsonifier (two-stage) | 773.601 | 0.141953 | 2384.87ms | 9578 | 80 | 22474.7 | 11807.5 | 0.233447 | 3.92259 | 2(Loss) | true |
| simdjson (ondemand) | 560.816 | 0.088448 | 3345.78ms | 9578 | 40 | 8301.28 | 16287.5 | 0.605167 | 5.41403 | 3(Loss) | true |
| glaze DID NOT CONVERGE | 412.304 | 9.81262 | 2323.98ms | 9578 | 4890 | 2.31096e+10 | 22154.3 | 3.26874 | 7.36228 | -(Loss) | false |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1743.19 | 0.149707 | 1505.88ms | 9578 | 40 | 2461.54 | 5240 | 0.820189 | 1.73318 | 1(Win) | true |
| glaze | 1209.84 | 0.138406 | 1959.28ms | 9578 | 30 | 3275.86 | 7550 | 0.666667 | 2.50334 | 2(Loss) | true |
| jsonifier (two-stage) | 1192.99 | 0.263328 | 1969ms | 9578 | 30 | 12195.4 | 7656.67 | 0.349498 | 2.54099 | 3(Loss) | true |
| simdjson (ondemand) | 724.8 | 0.0601864 | 3006.94ms | 9578 | 40 | 2301.28 | 12602.5 | 2.25569 | 4.18561 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1452.77 | 0.441802 | 1313.12ms | 9578 | 40 | 30865.4 | 6287.5 | 1.41129 | 2.08274 | 1(Win) | true |
| glaze DID NOT CONVERGE | 901.262 | 0.903168 | 2071.89ms | 9578 | 40 | 335154 | 10135 | 6.33087 | 3.36208 | -(Loss) | false |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7981.91 | 0.3443 | 280.055ms | 9578 | 160 | 2483.88 | 1144.38 | 0.0545852 | 0.373309 | 1(Win) | true |
| glaze | 2285.54 | 0.202807 | 861.32ms | 9578 | 320 | 21022.6 | 3996.56 | 1.62905 | 1.31548 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1558.47 | 0.30962 | 488.445ms | 3873 | 40 | 2153.85 | 2370 | 0.280505 | 1.92615 | 1(Win) | true |
| glaze | 987.423 | 0.104125 | 787.699ms | 3873 | 160 | 2427.28 | 3740.62 | 0.183456 | 3.06408 | 2(Loss) | true |
| jsonifier (two-stage) | 896.5 | 0.178107 | 839.849ms | 3873 | 40 | 2153.85 | 4120 | 0.651466 | 3.37139 | 3(Loss) | true |
| simdjson (ondemand) | 316.367 | 0.066841 | 2356.24ms | 3873 | 40 | 2435.9 | 11675 | 0.213675 | 9.59147 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1843.72 | 0.291489 | 419.233ms | 3873 | 30 | 1022.99 | 2003.33 | 0 | 1.62959 | 1(Win) | true |
| glaze | 1130.69 | 0.267972 | 682.133ms | 3873 | 30 | 2298.85 | 3266.67 | 0.102145 | 2.64689 | 2(Loss) | true |
| jsonifier (two-stage) | 934.492 | 0.221668 | 805.85ms | 3873 | 40 | 3070.51 | 3952.5 | 0.147804 | 3.2245 | 3(Loss) | true |
| simdjson (ondemand) | 328.976 | 0.137193 | 2298.47ms | 3873 | 80 | 18981 | 11227.5 | 0.0222618 | 9.21701 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 527.403 | 0.199404 | 1479.29ms | 3873 | 30 | 5850.57 | 7003.33 | 0.0475737 | 5.7452 | 1(Win) | true |
| glaze | 380.291 | 0.14367 | 2081.25ms | 3873 | 40 | 7788.46 | 9712.5 | 0.232198 | 7.96955 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4511.24 | 0.277645 | 202.835ms | 3873 | 320 | 1653.61 | 818.75 | 0.531511 | 0.656758 | 1(Win) | true |
| glaze | 1094.39 | 0.23122 | 758.881ms | 3873 | 40 | 2435.9 | 3375 | 0.344488 | 2.75324 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 446.587 | 6.32526 | 5268.51ms | 94653 | 1280 | 2.0923e+11 | 202129 | 2.2814 | 6.80426 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 442.868 | 6.61218 | 5058.97ms | 94653 | 1280 | 2.32498e+11 | 203826 | 0.196205 | 6.86141 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 389.041 | 6.09952 | 5904.82ms | 94653 | 1280 | 2.56377e+11 | 232028 | 0.333235 | 7.81106 | -(Tie) | false |
| simdjson (ondemand) DID NOT CONVERGE | 273.918 | 7.29203 | 8223.06ms | 94653 | 640 | 3.69576e+11 | 329544 | 0.100748 | 11.0946 | -(Loss) | false |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 766.323 | 6.02333 | 7836.43ms | 94653 | 2560 | 1.28872e+11 | 117794 | 2.56297 | 3.96491 | -(Tie) | false |
| glaze STATISTICAL TIE DID NOT CONVERGE | 746.488 | 5.96158 | 8114.61ms | 94653 | 2560 | 1.33041e+11 | 120924 | 0.0282575 | 4.07027 | -(Tie) | false |
| jsonifier (two-stage) DID NOT CONVERGE | 598.135 | 7.42648 | 9663.05ms | 94653 | 1280 | 1.60786e+11 | 150916 | 0.576245 | 5.08031 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 395.478 | 11.4376 | 6875.19ms | 94653 | 320 | 2.18095e+11 | 228251 | 4.0427 | 7.68403 | -(Loss) | false |

----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12363.4 | 0.233905 | 1486.53ms | 94653 | 160 | 46665.1 | 7301.25 | 0.654834 | 0.245062 | 1(Win) | true |
| glaze DID NOT CONVERGE | 4028.03 | 0.982159 | 4637.49ms | 94653 | 30 | 1.45334e+06 | 22410 | 2.80468 | 0.754126 | -(Loss) | false |

----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12707.9 | 0.125977 | 1432.69ms | 94653 | 30 | 2402.3 | 7103.33 | 1.28327 | 0.237943 | 1(Win) | true |
| glaze | 4327.85 | 3.05511 | 4058.17ms | 94653 | 40 | 1.6242e+07 | 20857.5 | 0.858317 | 0.700307 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 544.259 | 8.56024 | 5778.82ms | 124597 | 640 | 2.2354e+11 | 218324 | 3.56936 | 5.58326 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 528.104 | 6.15835 | 5770.58ms | 124597 | 1280 | 2.45762e+11 | 225003 | 0.601892 | 5.75414 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 494.842 | 5.91082 | 6063.23ms | 124597 | 1280 | 2.57862e+11 | 240127 | 5.1043 | 6.14076 | -(Tie) | false |
| simdjson (ondemand) DID NOT CONVERGE | 351.284 | 5.03786 | 8375.74ms | 124597 | 1280 | 3.71707e+11 | 338259 | 3.06387 | 8.65112 | -(Loss) | false |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 821.441 | 5.34839 | 9131.94ms | 124597 | 2560 | 1.53232e+11 | 144654 | 6.1618 | 3.69915 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 794.472 | 5.45068 | 9242.84ms | 124597 | 2560 | 1.70137e+11 | 149565 | 6.53882 | 3.82487 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 767.787 | 5.15822 | 9817.46ms | 124597 | 2560 | 1.63145e+11 | 154763 | 0.744152 | 3.95779 | -(Tie) | false |
| simdjson (ondemand) DID NOT CONVERGE | 481.982 | 5.83099 | 7138.16ms | 124597 | 1280 | 2.64514e+11 | 246534 | 5.62392 | 6.30496 | -(Loss) | false |

----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14280.1 | 0.100867 | 1827.79ms | 136037 | 40 | 3358.97 | 9085 | 0.0183486 | 0.212357 | 1(Win) | true |
| glaze | 4633.07 | 0.471697 | 5937ms | 136076 | 30 | 523690 | 28010 | 1.41952 | 0.655182 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14447.1 | 0.0827151 | 1834.11ms | 136037 | 30 | 1655.17 | 8980 | 0.335196 | 0.209045 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2507.64 | 9.39881 | 5408.5ms | 136076 | 2560 | 6.05644e+10 | 51750.7 | 5.05119 | 1.21101 | -(Loss) | false |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 338.241 | 2.20229 | 9435.28ms | 2251027 | 80 | 1.56295e+12 | 6.34679e+06 | 0.337219 | 8.98531 | 1(Win) | true |
| jsonifier (two-stage) DID NOT CONVERGE | 316.953 | 2.13409 | 9938.1ms | 2251027 | 80 | 1.67143e+12 | 6.77307e+06 | 3.37844 | 9.58902 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE | 212.871 | 2.15191 | 7051.69ms | 2251027 | 30 | 1.41286e+12 | 1.00847e+07 | 0.850535 | 14.2777 | 3(Tie) | true |
| glaze STATISTICAL TIE | 203.025 | 2.261 | 7405.77ms | 2251027 | 40 | 2.28625e+12 | 1.05738e+07 | 2.43475 | 14.9702 | 3(Tie) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 422.169 | 2.49192 | 9422.46ms | 2251027 | 80 | 1.28454e+12 | 5.08504e+06 | 3.69012 | 7.19898 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE | 397.256 | 3.43533 | 9985.74ms | 2251027 | 30 | 1.0339e+12 | 5.40393e+06 | 1.60946 | 7.65061 | 1(Tie) | true |
| glaze STATISTICAL TIE | 236.03 | 3.15942 | 7264.05ms | 2251027 | 30 | 2.47722e+12 | 9.09525e+06 | 1.16482 | 12.8767 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 231.035 | 2.24572 | 7070.66ms | 2251027 | 30 | 1.30629e+12 | 9.29188e+06 | 0.115201 | 13.1546 | 3(Tie) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 653.576 | 3.67031 | 9660.74ms | 2090234 | 80 | 1.00252e+12 | 3.04999e+06 | 1.89543 | 4.65007 | 1(Win) | true |
| glaze | 446.261 | 2.07952 | 6725.92ms | 2090234 | 80 | 6.90283e+11 | 4.4669e+06 | 0.737251 | 6.81053 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 786.646 | 3.54225 | 7853.79ms | 2090234 | 160 | 1.28916e+12 | 2.53405e+06 | 1.78139 | 3.8633 | 1(Win) | true |
| glaze | 614.779 | 2.57996 | 10002.4ms | 2090234 | 160 | 1.11969e+12 | 3.24247e+06 | 1.47901 | 4.94347 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 729.657 | 2.01409 | 10514.8ms | 5373214 | 80 | 1.60059e+12 | 7.02289e+06 | 0.0782719 | 4.16528 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 670.337 | 3.62542 | 5174.06ms | 5373214 | 30 | 2.3042e+12 | 7.64435e+06 | 1.14018 | 4.53407 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 464.84 | 1.77113 | 7635.94ms | 5373214 | 40 | 1.52483e+12 | 1.10238e+07 | 0.72478 | 6.53847 | 3(Tie) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 460.089 | 2.02182 | 7954.66ms | 5373214 | 30 | 1.52121e+12 | 1.11376e+07 | 2.86945 | 6.60596 | -(Tie) | false |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 876.663 | 2.17154 | 10476.3ms | 5373214 | 80 | 1.28893e+12 | 5.84523e+06 | 1.7199 | 3.46684 | 1(Win) | true |
| jsonifier | 808.618 | 3.10888 | 5192.27ms | 5373214 | 40 | 1.55256e+12 | 6.3371e+06 | 1.42716 | 3.75864 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 523.048 | 1.98898 | 7641.47ms | 5373214 | 30 | 1.13912e+12 | 9.79699e+06 | 3.88659 | 5.81078 | -(Tie) | false |
| glaze STATISTICAL TIE | 501.882 | 2.0127 | 7979.16ms | 5373214 | 40 | 1.6892e+12 | 1.02102e+07 | 1.18657 | 6.05579 | 3(Tie) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 1358.57 | 2.57126 | 6703.3ms | 6661897 | 40 | 5.78342e+11 | 4.67645e+06 | 5.35147 | 2.23683 | -(Win) | false |
| glaze | 764.403 | 2.74217 | 5925.71ms | 6661897 | 30 | 1.55833e+12 | 8.31143e+06 | 0.555922 | 3.97593 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 2371.15 | 3.21589 | 8356.34ms | 6661897 | 160 | 1.18796e+12 | 2.67941e+06 | 4.86861 | 1.2816 | -(Win) | false |
| glaze DID NOT CONVERGE | 1686.04 | 4.14571 | 5875.97ms | 6661897 | 30 | 7.32113e+11 | 3.76817e+06 | 3.40016 | 1.80248 | -(Loss) | false |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 886.181 | 5.33401 | 6860.05ms | 500299 | 640 | 5.27839e+11 | 538403 | 2.36704 | 3.42928 | -(Win) | false |
| jsonifier (two-stage) DID NOT CONVERGE | 643.889 | 6.21113 | 9540.3ms | 500299 | 320 | 6.77842e+11 | 741001 | 0.534513 | 4.7197 | -(Loss) | false |
| glaze DID NOT CONVERGE | 419.143 | 7.11106 | 6998.21ms | 500299 | 160 | 1.04839e+12 | 1.13833e+06 | 0.983205 | 7.2502 | -(Loss) | false |
| simdjson (ondemand) | 238.806 | 4.38684 | 6277.86ms | 500299 | 160 | 1.22912e+12 | 1.99795e+06 | 1.40734 | 12.7254 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 1050.47 | 8.5466 | 6544.06ms | 500299 | 320 | 4.82202e+11 | 454199 | 1.38602 | 2.89299 | -(Win) | false |
| jsonifier (two-stage) | 739.173 | 4.90428 | 9199.29ms | 500299 | 640 | 6.41353e+11 | 645481 | 0.6453 | 4.11121 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 478.365 | 5.24907 | 6757.82ms | 500299 | 320 | 8.77113e+11 | 997402 | 1.40423 | 6.35337 | -(Loss) | false |
| simdjson (ondemand) | 247.209 | 4.72336 | 6199.5ms | 500299 | 160 | 1.3297e+12 | 1.93004e+06 | 0.302187 | 12.2929 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 4320.52 | 5.87533 | 5821.62ms | 500299 | 2560 | 1.07769e+11 | 110432 | 5.8896 | 0.703232 | -(Win) | false |
| glaze DID NOT CONVERGE | 2118.57 | 6.16571 | 5595.37ms | 500299 | 1280 | 2.46802e+11 | 225209 | 4.10891 | 1.43421 | -(Loss) | false |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8365.8 | 0.571771 | 5831.07ms | 500299 | 40 | 4.25353e+06 | 57032.5 | 1.134 | 0.363098 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2413.21 | 4.58338 | 10017.1ms | 500299 | 2560 | 2.10224e+11 | 197713 | 4.38181 | 1.25896 | -(Loss) | false |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1322.97 | 8.46069 | 5772.04ms | 1151920 | 160 | 7.89721e+11 | 830369 | 2.97489 | 2.29703 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 1198.11 | 7.88004 | 5825.82ms | 1151920 | 160 | 8.35267e+11 | 916905 | 1.50643 | 2.5365 | -(Tie) | false |
| glaze DID NOT CONVERGE | 782.774 | 5.81657 | 8707.83ms | 1151920 | 160 | 1.06617e+12 | 1.40342e+06 | 1.13965 | 3.88231 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 508.715 | 4.0706 | 6676.19ms | 1151920 | 160 | 1.23633e+12 | 2.15947e+06 | 2.7688 | 5.97378 | -(Loss) | false |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3055.9 | 0.374925 | 9534.17ms | 1151920 | 40 | 7.26637e+07 | 359488 | 0.462172 | 0.994397 | 1(Win) | true |
| jsonifier DID NOT CONVERGE | 1300.29 | 5.92969 | 5713.16ms | 1151920 | 320 | 8.03112e+11 | 844853 | 1.61141 | 2.33713 | -(Loss) | false |
| glaze DID NOT CONVERGE | 846.792 | 6.36828 | 8602.68ms | 1151920 | 160 | 1.09208e+12 | 1.29732e+06 | 0.635021 | 3.58905 | -(Loss) | false |
| simdjson (ondemand) | 517.708 | 4.65897 | 6648.39ms | 1151920 | 160 | 1.56377e+12 | 2.12196e+06 | 1.6544 | 5.87038 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2200.46 | 4.99016 | 8041.43ms | 1439562 | 640 | 6.20359e+11 | 623903 | 0.77238 | 1.38072 | 1(Win) | true |
| glaze | 904.013 | 4.08732 | 9321.62ms | 1439584 | 320 | 1.23297e+12 | 1.51867e+06 | 0.81793 | 3.36153 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7168.48 | 4.64987 | 9820.45ms | 1439562 | 2560 | 2.03015e+11 | 191515 | 1.79573 | 0.422044 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3383.99 | 4.51434 | 9965.58ms | 1439584 | 1280 | 4.29354e+11 | 405703 | 4.34462 | 0.897782 | -(Loss) | false |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 615.889 | 4.91165 | 9362.9ms | 56369 | 4890 | 8.98751e+10 | 87284.7 | 8.76232 | 4.93342 | -(Tie) | false |
| glaze STATISTICAL TIE DID NOT CONVERGE | 605.987 | 5.01245 | 8813.77ms | 56369 | 4890 | 9.66857e+10 | 88710.9 | 0.70355 | 5.01394 | -(Tie) | false |
| jsonifier (two-stage) DID NOT CONVERGE | 500.578 | 6.56163 | 5350.74ms | 56369 | 2560 | 1.27116e+11 | 107391 | 1.09033 | 6.06948 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 254.578 | 6.47167 | 5198.65ms | 56369 | 1280 | 2.39046e+11 | 211164 | 2.41252 | 11.9365 | -(Loss) | false |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1958.38 | 0.756889 | 6265.87ms | 56369 | 30 | 1.295e+06 | 27450 | 1.60395 | 1.55053 | 1(Win) | true |
| jsonifier DID NOT CONVERGE | 867.068 | 5.90287 | 7525.91ms | 56369 | 4890 | 6.54954e+10 | 61999.4 | 9.81019 | 3.50396 | -(Loss) | false |
| jsonifier (two-stage) DID NOT CONVERGE | 694.584 | 5.40699 | 8510.32ms | 56369 | 4890 | 8.5635e+10 | 77395.5 | 2.73608 | 4.37408 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 312.11 | 4.97933 | 9195.11ms | 56369 | 2560 | 1.88299e+11 | 172240 | 2.83879 | 9.73538 | -(Loss) | false |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10610.9 | 0.241299 | 1020.85ms | 56369 | 320 | 47822.9 | 5066.25 | 0.368732 | 0.285003 | 1(Win) | true |
| glaze | 3988.7 | 0.477089 | 2742.73ms | 56369 | 40 | 165378 | 13477.5 | 0.98027 | 0.761686 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11326.3 | 0.32877 | 979.001ms | 56369 | 80 | 19479.4 | 4746.25 | 0.0789474 | 0.266753 | 1(Win) | true |
| glaze | 4692.43 | 0.486156 | 2335.53ms | 56369 | 160 | 496313 | 11456.2 | 0.811688 | 0.644898 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 781.307 | 6.4415 | 5231.25ms | 83958 | 2560 | 1.11557e+11 | 102480 | 4.05328 | 3.88909 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 735.483 | 6.30445 | 5529.14ms | 83958 | 2560 | 1.20591e+11 | 108865 | 1.63326 | 4.13155 | -(Tie) | false |
| jsonifier DID NOT CONVERGE | 622.789 | 5.93397 | 6429.55ms | 83958 | 2560 | 1.48996e+11 | 128565 | 3.93843 | 4.87926 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 374.249 | 6.24539 | 5417.09ms | 83958 | 1280 | 2.28525e+11 | 213945 | 1.09327 | 8.12011 | -(Loss) | false |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) DID NOT CONVERGE | 1941.84 | 3.18592 | 9066.37ms | 83958 | 30 | 5.17713e+07 | 41233.3 | 2.82033 | 1.56395 | -(Win) | false |
| glaze DID NOT CONVERGE | 1214.96 | 5.79306 | 7559.73ms | 83958 | 4890 | 7.12729e+10 | 65902.2 | 5.83118 | 2.50041 | -(Loss) | false |
| jsonifier DID NOT CONVERGE | 852.99 | 6.48968 | 5507.44ms | 83958 | 2560 | 9.5e+10 | 93868.2 | 6.82374 | 3.56211 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 453.999 | 6.93339 | 9577.43ms | 83958 | 1280 | 1.91388e+11 | 176363 | 0.620497 | 6.69322 | -(Loss) | false |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 7126.93 | 12.7021 | 1393.21ms | 94370 | 4890 | 1.25812e+10 | 12627.9 | 8.67872 | 0.408221 | -(Win) | false |
| glaze | 3874.64 | 0.921953 | 4608.08ms | 94370 | 40 | 1.83435e+06 | 23227.5 | 1.22962 | 0.783382 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13753.3 | 0.279681 | 1327.85ms | 94370 | 80 | 26795.9 | 6543.75 | 0.133894 | 0.220079 | 1(Win) | true |
| glaze DID NOT CONVERGE | 4497.1 | 1.04236 | 4013.06ms | 94370 | 40 | 1.74061e+06 | 20012.5 | 3.13949 | 0.674229 | -(Loss) | false |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 879.976 | 0.64003 | 5524.01ms | 53331 | 80 | 1.09473e+07 | 57797.5 | 0.833043 | 3.45246 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 514.59 | 0.872525 | 9932.6ms | 53331 | 30 | 2.23107e+07 | 98836.7 | 0.826306 | 5.90453 | 2(Tie) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 503.766 | 6.60278 | 5140.49ms | 53331 | 2560 | 1.13761e+11 | 100960 | 3.34202 | 6.03173 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 492.625 | 6.47205 | 5232.08ms | 53331 | 2560 | 1.14301e+11 | 103244 | 7.04094 | 6.16801 | -(Tie) | false |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1259.86 | 0.400084 | 8753.61ms | 53331 | 80 | 2.08694e+06 | 40370 | 0.466621 | 2.41051 | 1(Win) | true |
| glaze STATISTICAL TIE DID NOT CONVERGE | 788.142 | 8.54719 | 7694.15ms | 53331 | 2560 | 7.78821e+10 | 64532 | 2.8796 | 3.85464 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 765.543 | 7.99967 | 7804.83ms | 53331 | 2560 | 7.23111e+10 | 66437 | 5.97391 | 3.96859 | -(Tie) | false |
| simdjson (ondemand) | 634.565 | 0.376431 | 9072.11ms | 53331 | 30 | 2.73086e+06 | 80150 | 0.112164 | 4.78762 | 4(Loss) | true |

----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11487.4 | 0.251027 | 1008.77ms | 58581 | 30 | 4471.26 | 4863.33 | 0.62069 | 0.263127 | 1(Win) | true |
| glaze | 4525.03 | 0.742207 | 2268.3ms | 58581 | 160 | 1.34351e+06 | 12346.2 | 1.7618 | 0.670543 | 2(Loss) | true |

----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12115.4 | 0.159031 | 933.708ms | 58581 | 80 | 4302.22 | 4611.25 | 1.06849 | 0.248601 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2777.8 | 10.7765 | 2030.31ms | 58581 | 4890 | 2.29706e+10 | 20112 | 1.33298 | 1.09134 | -(Loss) | false |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 572.102 | 6.38648 | 5420.77ms | 65103 | 2560 | 1.22975e+11 | 108524 | 0.841105 | 5.31135 | -(Tie) | false |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 515.873 | 8.54052 | 6367.24ms | 65103 | 1280 | 1.35237e+11 | 120353 | 0.0183738 | 5.88932 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 514.988 | 8.5275 | 6298.98ms | 65103 | 1280 | 1.35289e+11 | 120560 | 3.10276 | 5.90022 | -(Tie) | false |
| simdjson (ondemand) DID NOT CONVERGE | 303.996 | 6.45994 | 5321.22ms | 65103 | 1280 | 2.2281e+11 | 204237 | 7.15358 | 9.9965 | -(Loss) | false |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE DID NOT CONVERGE | 860.805 | 7.77563 | 8406.95ms | 65103 | 2560 | 8.052e+10 | 72126.8 | 1.09238 | 3.52934 | -(Tie) | false |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 704.46 | 7.1544 | 5051.08ms | 65103 | 2560 | 1.01783e+11 | 88134.2 | 3.0814 | 4.31309 | -(Tie) | false |
| jsonifier DID NOT CONVERGE | 652.612 | 6.86025 | 5316.22ms | 65103 | 2560 | 1.09047e+11 | 95136.3 | 4.56818 | 4.65506 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 375.185 | 5.01944 | 9242.81ms | 65103 | 2560 | 1.76628e+11 | 165484 | 0.691442 | 8.09968 | -(Loss) | false |

----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13692.9 | 0.11505 | 1161.23ms | 78778 | 30 | 1195.4 | 5486.67 | 0.181928 | 0.220994 | 1(Win) | true |
| glaze DID NOT CONVERGE | 1508.45 | 6.86018 | 5052.59ms | 78778 | 4890 | 5.7086e+10 | 49805.2 | 5.07429 | 2.01364 | -(Loss) | false |

----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14438.5 | 0.112226 | 1054.9ms | 78778 | 30 | 1022.99 | 5203.33 | 1.5142 | 0.208897 | 1(Win) | true |
| glaze DID NOT CONVERGE | 1836.04 | 7.76499 | 3984.57ms | 78778 | 4890 | 4.9367e+10 | 40918.8 | 3.40567 | 1.65303 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1659.64 | 0.164459 | 1371.94ms | 11812 | 80 | 9968.35 | 6787.5 | 1.30862 | 1.8257 | 1(Win) | true |
| jsonifier (two-stage) | 1170.98 | 0.365841 | 1857.87ms | 11812 | 80 | 99088.6 | 9620 | 0.0520021 | 2.58773 | 2(Loss) | true |
| glaze | 1010.3 | 0.75729 | 2267.3ms | 11812 | 80 | 570380 | 11150 | 2.49235 | 3.00357 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 214.872 | 6.64398 | 5191.55ms | 11812 | 4890 | 5.93273e+10 | 52425.7 | 3.05143 | 13.9973 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1935.53 | 0.189408 | 1337.69ms | 11812 | 80 | 9721.52 | 5820 | 0.605013 | 1.56616 | 1(Win) | true |
| jsonifier (two-stage) | 1379.36 | 1.21365 | 1844.47ms | 11812 | 30 | 294713 | 8166.67 | 1.74419 | 2.19639 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 619.936 | 10.7609 | 2110.88ms | 11812 | 4890 | 1.86963e+10 | 18170.9 | 3.03428 | 4.89467 | -(Loss) | false |
| simdjson (ondemand) | 473.908 | 0.595186 | 5037.52ms | 11812 | 40 | 800615 | 23770 | 2.08705 | 6.40508 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9486.15 | 0.313337 | 254.051ms | 11812 | 80 | 1107.59 | 1187.5 | 0.635593 | 0.315624 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3386.21 | 0.285842 | 684.974ms | 11812 | 30 | 2712.64 | 3326.67 | 7.59259 | 0.89082 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10358.4 | 0.379242 | 222.252ms | 11812 | 80 | 1360.76 | 1087.5 | 0 | 0.286551 | 1(Win) | true |
| glaze | 4183.77 | 0.158773 | 556.975ms | 11812 | 80 | 1462.03 | 2692.5 | 0.370028 | 0.716837 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2416.05 | 0.712428 | 2072.61ms | 25388 | 80 | 407771 | 10021.2 | 0.0872383 | 1.25482 | 1(Win) | true |
| jsonifier | 2220.59 | 1.10065 | 2155.75ms | 25388 | 30 | 432057 | 10903.3 | 0.708128 | 1.36605 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 814.397 | 8.7808 | 2953.21ms | 25388 | 4890 | 3.33244e+10 | 29729.8 | 5.77066 | 3.72909 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 427.961 | 8.64232 | 6398.89ms | 25388 | 2560 | 6.11997e+10 | 56575 | 0.705535 | 7.09882 | -(Loss) | false |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2704.86 | 0.141916 | 2069.61ms | 25388 | 80 | 12909.8 | 8951.25 | 1.63462 | 1.11994 | 1(Win) | true |
| jsonifier | 2542.6 | 0.18223 | 2176.72ms | 25388 | 40 | 12044.9 | 9522.5 | 0.767196 | 1.19413 | 2(Loss) | true |
| glaze | 1899.53 | 0.752605 | 2766.24ms | 25388 | 80 | 736188 | 12746.2 | 2.15388 | 1.59613 | 3(Loss) | true |
| simdjson (ondemand) | 928.503 | 0.182901 | 4192.49ms | 25388 | 320 | 727898 | 26076.2 | 0.853296 | 3.27017 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13838.8 | 0.320602 | 353.292ms | 31235 | 640 | 30478.9 | 2152.5 | 0.706357 | 0.2172 | 1(Win) | true |
| glaze | 4812.28 | 0.447314 | 991.805ms | 31235 | 30 | 23000 | 6190 | 1.86506 | 0.628763 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15233.8 | 0.411592 | 317.276ms | 31235 | 1280 | 82910.7 | 1955.39 | 0.0119875 | 0.196902 | 1(Win) | true |
| glaze | 6006.69 | 0.64362 | 732.834ms | 31235 | 1280 | 1.30401e+06 | 4959.14 | 0.278066 | 0.501549 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE | 1472.17 | 0.388077 | 5315.9ms | 108313 | 320 | 2.37263e+07 | 70165.3 | 0.664071 | 2.06378 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1420.6 | 2.69036 | 7203.86ms | 108313 | 40 | 1.53073e+08 | 72712.5 | 5.79441 | 2.13804 | -(Tie) | false |
| jsonifier DID NOT CONVERGE | 704.807 | 23.0406 | 7185.21ms | 108313 | 2560 | 2.91911e+12 | 146558 | 18.0324 | 4.31155 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 325.619 | 12.801 | 8691.6ms | 108313 | 1280 | 2.11076e+12 | 317228 | 4.81009 | 9.33323 | -(Loss) | false |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2476.07 | 1.87913 | 5586.98ms | 108313 | 40 | 2.45815e+07 | 41717.5 | 0.994593 | 1.22676 | 1(Win) | true |
| glaze | 1838 | 0.499433 | 10398ms | 108313 | 40 | 3.15128e+06 | 56200 | 1.14916 | 1.65238 | 2(Loss) | true |
| jsonifier (two-stage) | 1802.32 | 0.243816 | 6272.06ms | 108313 | 80 | 1.56212e+06 | 57312.5 | 0.205438 | 1.68555 | 3(Loss) | true |
| simdjson (ondemand) | 636.653 | 0.341529 | 8067.41ms | 108313 | 40 | 1.2282e+07 | 162248 | 0.719501 | 4.77354 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13485.9 | 0.200614 | 1540.68ms | 108313 | 640 | 151114 | 7659.53 | 0.477099 | 0.224631 | 1(Win) | true |
| glaze | 4356 | 1.42996 | 5532.46ms | 108313 | 30 | 3.44947e+06 | 23713.3 | 1.8614 | 0.696655 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14426.7 | 0.158466 | 1411.55ms | 108313 | 30 | 3862.07 | 7160 | 0.233318 | 0.210131 | 1(Win) | true |
| glaze DID NOT CONVERGE | 4709.16 | 1.47089 | 4346.28ms | 108313 | 40 | 4.16387e+06 | 21935 | 13.1058 | 0.643935 | -(Loss) | false |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1842.61 | 1.06926 | 9663.54ms | 183677 | 40 | 4.13305e+07 | 95065 | 1.80082 | 1.64886 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1093.52 | 5.21735 | 8057.54ms | 183677 | 2560 | 1.78812e+11 | 160187 | 0.239136 | 2.77878 | -(Tie) | false |
| jsonifier STATISTICAL TIE | 968.879 | 4.82102 | 9308.27ms | 183677 | 2560 | 1.94486e+11 | 180795 | 1.79322 | 3.13629 | 2(Tie) | true |
| simdjson (ondemand) | 454.906 | 4.60153 | 9743.21ms | 183677 | 1280 | 4.01865e+11 | 385064 | 2.40523 | 6.68036 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1325.78 | 7.797 | 7192.05ms | 183677 | 1280 | 1.35841e+11 | 132124 | 1.89943 | 2.29177 | -(Tie) | false |
| glaze STATISTICAL TIE DID NOT CONVERGE | 1120.34 | 5.18753 | 8447.11ms | 183677 | 2560 | 1.68412e+11 | 156353 | 4.35958 | 2.71212 | -(Tie) | false |
| jsonifier DID NOT CONVERGE | 1046.55 | 5.1241 | 8440.7ms | 183677 | 2560 | 1.88305e+11 | 167376 | 3.42808 | 2.90338 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 514.778 | 6.84648 | 9083.91ms | 183677 | 640 | 3.47364e+11 | 340279 | 0.40697 | 5.90309 | -(Loss) | false |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 18449.5 | 0.0844213 | 2299.6ms | 213963 | 40 | 3487.18 | 11060 | 0.896057 | 0.164632 | 1(Win) | true |
| glaze DID NOT CONVERGE | 1893.16 | 6.37335 | 5681.86ms | 213963 | 2560 | 1.20803e+11 | 107783 | 2.18405 | 1.60484 | -(Loss) | false |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 18571.2 | 0.478474 | 2237.35ms | 213963 | 80 | 221108 | 10987.5 | 2.13804 | 0.163092 | 1(Win) | true |
| glaze | 2180.37 | 4.96445 | 9360.8ms | 213963 | 4890 | 1.05553e+11 | 93585.6 | 2.0415 | 1.393 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 280.928 | 2.17285 | 9185.14ms | 1834197 | 80 | 1.46437e+12 | 6.2266e+06 | 0.741452 | 10.818 | 1(Win) | true |
| jsonifier (two-stage) | 250.177 | 2.2504 | 10372.3ms | 1834197 | 80 | 1.98065e+12 | 6.99197e+06 | 0.102419 | 12.1485 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 162.075 | 1.84045 | 7675.29ms | 1834197 | 40 | 1.57824e+12 | 1.07927e+07 | 5.33568 | 18.7523 | -(Loss) | false |
| simdjson (ondemand) | 89.9614 | 1.67733 | 5882.92ms | 1834197 | 30 | 3.19109e+12 | 1.94442e+07 | 0.999825 | 33.7851 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 334.033 | 1.93707 | 9146.92ms | 1834197 | 80 | 8.23184e+11 | 5.23669e+06 | 4.41785 | 9.09851 | -(Win) | false |
| jsonifier (two-stage) | 283.365 | 2.0896 | 10404.9ms | 1834197 | 80 | 1.33113e+12 | 6.17306e+06 | 1.6355 | 10.725 | 2(Loss) | true |
| glaze | 171.975 | 2.67813 | 7692.51ms | 1834197 | 30 | 2.22611e+12 | 1.01714e+07 | 0.110431 | 17.6727 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 90.8818 | 1.41388 | 5880.32ms | 1834197 | 30 | 2.22169e+12 | 1.92473e+07 | 2.8681 | 33.4428 | -(Loss) | false |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 422.043 | 3.75037 | 6112.48ms | 1834197 | 40 | 9.66465e+11 | 4.14466e+06 | 0.773511 | 7.20103 | 1(Win) | true |
| glaze | 348.645 | 2.19821 | 7566.28ms | 1833577 | 80 | 9.72436e+11 | 5.01552e+06 | 1.93768 | 8.71734 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 472.541 | 4.64707 | 5335.94ms | 1834197 | 40 | 1.18367e+12 | 3.70174e+06 | 0.166844 | 6.43046 | 1(Win) | true |
| glaze | 393 | 2.05234 | 6807.77ms | 1833577 | 80 | 6.67116e+11 | 4.44945e+06 | 0.568255 | 7.73333 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 901.326 | 2.36587 | 5471.05ms | 7351818 | 30 | 1.01609e+12 | 7.77881e+06 | 1.48546 | 3.37183 | 1(Tie) | true |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 868.129 | 2.11737 | 5545.25ms | 7351818 | 30 | 8.77279e+11 | 8.07626e+06 | 4.06675 | 3.50077 | -(Tie) | false |
| glaze | 575.027 | 1.70741 | 8643.59ms | 7351818 | 40 | 1.7336e+12 | 1.21929e+07 | 1.61038 | 5.28546 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 280.576 | 1.2668 | 7350.97ms | 7351818 | 30 | 3.00624e+12 | 2.49888e+07 | 3.19832 | 10.8327 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 983.077 | 3.03577 | 5430.7ms | 7351818 | 30 | 1.40628e+12 | 7.13194e+06 | 0.404041 | 3.09139 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 959.031 | 2.77024 | 5531.27ms | 7351818 | 40 | 1.64066e+12 | 7.31076e+06 | 1.07603 | 3.169 | 1(Tie) | true |
| glaze DID NOT CONVERGE | 635.334 | 2.06703 | 8671.43ms | 7351818 | 30 | 1.56099e+12 | 1.10355e+07 | 3.63282 | 4.78369 | -(Loss) | false |
| simdjson (ondemand) | 300.081 | 1.27373 | 7421.86ms | 7351818 | 30 | 2.65696e+12 | 2.33645e+07 | 0.806094 | 10.1286 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1505.76 | 2.57086 | 9393.03ms | 9930848 | 80 | 2.09174e+12 | 6.28972e+06 | 0.867838 | 2.01838 | 1(Win) | true |
| glaze DID NOT CONVERGE | 942.847 | 1.79217 | 7059.57ms | 9930228 | 40 | 1.29615e+12 | 1.00443e+07 | 2.64775 | 3.22346 | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2338.96 | 2.91016 | 5904.95ms | 9930848 | 30 | 4.16565e+11 | 4.04915e+06 | 0.488152 | 1.29923 | 1(Win) | true |
| glaze | 1730.89 | 2.28806 | 8370.8ms | 9930228 | 80 | 1.25373e+12 | 5.4713e+06 | 0.216981 | 1.75577 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 297.043 | 2.28775 | 8963.6ms | 1834197 | 80 | 1.45198e+12 | 5.8888e+06 | 1.61606 | 10.2316 | 1(Win) | true |
| jsonifier (two-stage) | 260.854 | 3.15776 | 10091.5ms | 1834197 | 40 | 1.79356e+12 | 6.70577e+06 | 1.4212 | 11.651 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 158.737 | 1.89374 | 7526.49ms | 1834197 | 40 | 1.74196e+12 | 1.10197e+07 | 0.19942 | 19.1467 | 3(Tie) | true |
| glaze STATISTICAL TIE | 158.119 | 2.76676 | 7818.4ms | 1834197 | 40 | 3.74736e+12 | 1.10627e+07 | 0.760675 | 19.2213 | 3(Tie) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 319.262 | 2.75366 | 9049.9ms | 1834197 | 80 | 1.82099e+12 | 5.47897e+06 | 3.0195 | 9.51931 | -(Win) | false |
| jsonifier (two-stage) DID NOT CONVERGE | 289.974 | 2.07466 | 10048.3ms | 1834197 | 80 | 1.25302e+12 | 6.03236e+06 | 2.90319 | 10.4811 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 176.14 | 1.90415 | 7528.7ms | 1834197 | 40 | 1.43034e+12 | 9.9309e+06 | 3.15201 | 17.2549 | -(Tie) | false |
| glaze STATISTICAL TIE | 170.736 | 2.01347 | 7669.47ms | 1834197 | 40 | 1.70212e+12 | 1.02452e+07 | 2.22981 | 17.801 | 3(Tie) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 431.413 | 2.38601 | 6083.2ms | 1834197 | 30 | 2.80783e+11 | 4.05465e+06 | 0.523717 | 7.0446 | 1(Win) | true |
| glaze | 300.501 | 3.09966 | 8591.44ms | 1833577 | 40 | 1.30135e+12 | 5.81907e+06 | 1.99925 | 10.1138 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 500.938 | 3.11838 | 5281.1ms | 1834197 | 80 | 9.48577e+11 | 3.4919e+06 | 1.71281 | 6.06645 | 1(Win) | true |
| glaze | 387.781 | 4.02992 | 6724.63ms | 1833577 | 40 | 1.32093e+12 | 4.50934e+06 | 0.274386 | 7.83725 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1924.22 | 0.233629 | 5535.55ms | 7351818 | 40 | 2.89864e+09 | 3.64369e+06 | 1.52347 | 1.57931 | 1(Win) | true |
| jsonifier | 1871 | 0.632344 | 5704.38ms | 7351818 | 30 | 1.68449e+10 | 3.74731e+06 | 0.321417 | 1.62436 | 2(Loss) | true |
| simdjson (ondemand) | 1165 | 0.458863 | 9005.95ms | 7351818 | 80 | 6.10094e+10 | 6.01825e+06 | 0.221692 | 2.60868 | 3(Loss) | true |
| glaze | 552.165 | 1.78205 | 8813.92ms | 7351818 | 40 | 2.04811e+12 | 1.26977e+07 | 1.62324 | 5.50429 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 2063.82 | 0.576826 | 5523.86ms | 7351818 | 40 | 1.53601e+10 | 3.39721e+06 | 0.696762 | 1.47255 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 2039.8 | 0.276802 | 5678.51ms | 7351818 | 80 | 7.24173e+09 | 3.43722e+06 | 0.109525 | 1.48991 | 1(Tie) | true |
| simdjson (ondemand) | 1231.23 | 0.337488 | 9012.07ms | 7351818 | 30 | 1.10803e+10 | 5.69452e+06 | 0.497677 | 2.46824 | 3(Loss) | true |
| glaze | 578.101 | 1.66788 | 6835.8ms | 7351818 | 30 | 1.22752e+12 | 1.2128e+07 | 1.38168 | 5.25744 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3124.87 | 0.613754 | 9449.02ms | 9930848 | 30 | 1.03805e+10 | 3.03078e+06 | 0.000219965 | 0.972565 | 1(Win) | true |
| glaze | 1353.96 | 0.587633 | 10689.1ms | 9930228 | 40 | 6.75742e+10 | 6.99446e+06 | 1.6539 | 2.24469 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4927.08 | 0.207631 | 5982.1ms | 9930848 | 80 | 1.27429e+09 | 1.92219e+06 | 0.885348 | 0.616665 | 1(Win) | true |
| glaze | 3484.53 | 0.278203 | 8435.44ms | 9930228 | 160 | 9.14691e+09 | 2.71778e+06 | 0.142944 | 0.872109 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 791.393 | 0.324856 | 7120.11ms | 461466 | 160 | 5.22151e+08 | 556093 | 0.768757 | 3.83996 | 1(Win) | true |
| glaze | 766.529 | 0.631269 | 7262.72ms | 461466 | 640 | 8.40681e+09 | 574131 | 0.918374 | 3.96438 | 2(Loss) | true |
| jsonifier (two-stage) | 712.148 | 0.579863 | 7802.4ms | 461466 | 640 | 8.21807e+09 | 617973 | 0.015704 | 4.26692 | 3(Loss) | true |
| simdjson (ondemand) | 439.712 | 0.230114 | 6321.58ms | 461466 | 320 | 1.69738e+09 | 1.00086e+06 | 0.0223921 | 6.91102 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1061.75 | 0.304707 | 6372.87ms | 461466 | 160 | 2.55222e+08 | 414493 | 0.339362 | 2.86237 | 1(Win) | true |
| glaze | 1027.4 | 0.263902 | 6521.16ms | 461466 | 640 | 8.17826e+08 | 428350 | 0.127144 | 2.95803 | 2(Loss) | true |
| jsonifier (two-stage) | 985.944 | 0.206099 | 6972.37ms | 461466 | 40 | 3.38521e+07 | 446362 | 0.380338 | 3.08243 | 3(Loss) | true |
| simdjson (ondemand) | 515.306 | 0.557539 | 5945.02ms | 461466 | 30 | 6.80176e+08 | 854033 | 0.849058 | 5.89728 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3712.9 | 0.624646 | 6033.93ms | 461466 | 160 | 8.77083e+07 | 118529 | 0.181587 | 0.817753 | 1(Win) | true |
| glaze | 2987 | 0.466585 | 7580.71ms | 461466 | 2560 | 1.20979e+09 | 147334 | 0.4162 | 1.0172 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11102.4 | 0.23853 | 4007.3ms | 461466 | 1280 | 1.1443e+07 | 39638.9 | 0.937948 | 0.273543 | 1(Win) | true |
| glaze | 3351.86 | 0.363354 | 6889.57ms | 461466 | 30 | 6.82792e+06 | 131297 | 0.0329932 | 0.906497 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1126.16 | 0.41063 | 7829.29ms | 728486 | 320 | 2.0535e+09 | 616910 | 0.219771 | 2.69839 | 1(Win) | true |
| glaze | 1087.48 | 0.283417 | 8246.48ms | 728486 | 30 | 9.83502e+07 | 638853 | 0.76498 | 2.79454 | 2(Loss) | true |
| jsonifier | 1026.84 | 0.228766 | 8655.66ms | 728486 | 640 | 1.53319e+09 | 676576 | 0.58792 | 2.95948 | 3(Loss) | true |
| simdjson (ondemand) | 679.34 | 0.365027 | 6527.49ms | 728486 | 30 | 4.18062e+08 | 1.02267e+06 | 0.20882 | 4.47338 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1464.25 | 0.353288 | 7093.37ms | 728486 | 640 | 1.79826e+09 | 474469 | 0.0613797 | 2.07533 | 1(Win) | true |
| glaze | 1393.93 | 0.138452 | 7466.25ms | 728486 | 320 | 1.52373e+08 | 498402 | 0.463642 | 2.18023 | 2(Loss) | true |
| jsonifier | 1304.71 | 0.227275 | 7875.29ms | 728486 | 160 | 2.34335e+08 | 532486 | 0.282139 | 2.32937 | 3(Loss) | true |
| simdjson (ondemand) | 769.775 | 0.888173 | 6163.35ms | 728486 | 80 | 5.14043e+09 | 902521 | 0.436094 | 3.94768 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4152.64 | 0.401262 | 9866.16ms | 837491 | 160 | 9.52986e+07 | 192334 | 0.257351 | 0.731276 | 1(Win) | true |
| glaze | 2153.91 | 0.459816 | 9565.63ms | 837491 | 80 | 2.32576e+08 | 370811 | 0.422137 | 1.41023 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13965.2 | 0.194934 | 5759.26ms | 837491 | 4890 | 6.07787e+07 | 57191.7 | 0.769155 | 0.217413 | 1(Win) | true |
| glaze | 4237.63 | 0.19132 | 9681.66ms | 837491 | 2560 | 3.32872e+08 | 188476 | 0.282804 | 0.716982 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6760.95 | 0.230054 | 6690.37ms | 466906 | 30 | 688690 | 65860 | 0.335161 | 0.449404 | 1(Win) | true |
| jsonifier (two-stage) | 6651.87 | 0.597449 | 6714.93ms | 466906 | 40 | 6.39785e+06 | 66940 | 0.119653 | 0.456744 | 2(Loss) | true |
| simdjson (ondemand) | 3521.39 | 0.216194 | 6455.15ms | 466906 | 2560 | 1.91319e+08 | 126449 | 0.635256 | 0.862921 | 3(Loss) | true |
| glaze | 2797.74 | 0.299238 | 8230.94ms | 466906 | 320 | 7.25816e+07 | 159156 | 0.0761253 | 1.0862 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 6956.85 | 0.209625 | 6599.48ms | 466906 | 640 | 1.15213e+07 | 64005.5 | 0.0378243 | 0.436691 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 6933.62 | 0.268408 | 6582.76ms | 466906 | 1280 | 3.80311e+07 | 64219.8 | 0.012407 | 0.438163 | 1(Tie) | true |
| simdjson (ondemand) | 3692.09 | 0.124772 | 6281.93ms | 466906 | 1280 | 2.89839e+07 | 120603 | 0.324457 | 0.82302 | 3(Loss) | true |
| glaze | 2873.58 | 0.16609 | 8046.51ms | 466906 | 2560 | 1.69566e+08 | 154955 | 0.158665 | 1.05749 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 7611.62 | 0.223393 | 8028.96ms | 631514 | 640 | 1.99955e+07 | 79123.6 | 0.375174 | 0.399175 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 7579.51 | 0.131179 | 7966.32ms | 631514 | 4890 | 5.31278e+07 | 79458.8 | 0.372081 | 0.400861 | 1(Tie) | true |
| simdjson (ondemand) | 4131.55 | 0.174717 | 7480.85ms | 631514 | 1280 | 8.30274e+07 | 145771 | 0.0445032 | 0.735521 | 3(Loss) | true |
| glaze | 3402.01 | 0.266113 | 9132.38ms | 631514 | 30 | 6.65803e+06 | 177030 | 0.0470952 | 0.893289 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 7845.6 | 0.213133 | 7865.2ms | 631514 | 640 | 1.71315e+07 | 76763.9 | 0.21955 | 0.387269 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 7816.58 | 0.21823 | 7928.01ms | 631514 | 640 | 1.80943e+07 | 77048.9 | 0.0115579 | 0.388693 | 1(Tie) | true |
| simdjson (ondemand) | 4273.6 | 0.132362 | 7267.17ms | 631514 | 2560 | 8.90724e+07 | 140925 | 0.142955 | 0.711052 | 3(Loss) | true |
| glaze | 3439.71 | 0.13947 | 9014.46ms | 631514 | 1280 | 7.63304e+07 | 175090 | 0.480114 | 0.883453 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1224.96 | 0.297387 | 9291.44ms | 466906 | 1280 | 1.49579e+09 | 363504 | 0.682774 | 2.48052 | 1(Win) | true |
| glaze | 1203.75 | 0.378418 | 9452.77ms | 466906 | 640 | 1.25403e+09 | 369906 | 0.000844816 | 2.52434 | 2(Loss) | true |
| jsonifier (two-stage) | 1074.67 | 0.340441 | 5295.11ms | 466906 | 640 | 1.27342e+09 | 414337 | 0.499835 | 2.82748 | 3(Loss) | true |
| simdjson (ondemand) | 735.282 | 0.313762 | 7692.14ms | 466906 | 640 | 2.31063e+09 | 605586 | 0.0600297 | 4.13267 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1781.02 | 0.471842 | 7301.32ms | 466906 | 80 | 1.11327e+08 | 250011 | 0.0765551 | 1.70636 | 1(Win) | true |
| glaze | 1719.31 | 0.167513 | 7497.13ms | 466906 | 1280 | 2.40912e+08 | 258985 | 0.259161 | 1.76743 | 2(Loss) | true |
| jsonifier (two-stage) | 1495.19 | 0.147961 | 8574.98ms | 466906 | 1280 | 2.48526e+08 | 297806 | 0.211623 | 2.03248 | 3(Loss) | true |
| simdjson (ondemand) | 915.219 | 0.207401 | 6563.02ms | 466906 | 640 | 6.51647e+08 | 486524 | 0.0875346 | 3.3205 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 4975.27 | 0.319736 | 9079.34ms | 475954 | 2560 | 2.17831e+08 | 91232.3 | 0.185353 | 0.610605 | 1(Win) | true |
| jsonifier | 3904.24 | 0.301012 | 5968.68ms | 475954 | 1280 | 1.56759e+08 | 116259 | 1.00839 | 0.777644 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15063.6 | 0.249657 | 3046.83ms | 475954 | 160 | 905478 | 30132.5 | 1.31125 | 0.201509 | 1(Win) | true |
| glaze | 5696.24 | 0.256065 | 7930.78ms | 475954 | 4890 | 2.03593e+08 | 79685 | 0.0336994 | 0.533302 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE | 1409.67 | 0.511094 | 5405.31ms | 631514 | 640 | 3.05148e+09 | 427233 | 0.929404 | 2.15552 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1399.75 | 0.67274 | 5479.02ms | 631514 | 160 | 1.34053e+09 | 430261 | 0.082005 | 2.1709 | 1(Tie) | true |
| jsonifier | 1249.07 | 0.375586 | 6172.97ms | 631514 | 640 | 2.0989e+09 | 482167 | 0.237907 | 2.43282 | 3(Loss) | true |
| simdjson (ondemand) | 949.682 | 0.344818 | 8100.33ms | 631514 | 320 | 1.53017e+09 | 634169 | 0.0200105 | 3.19989 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1940.41 | 0.251731 | 8859.35ms | 631514 | 1280 | 7.81385e+08 | 310378 | 0.0915133 | 1.56602 | 1(Win) | true |
| jsonifier (two-stage) | 1925.41 | 0.154794 | 8927.12ms | 631514 | 1280 | 3.0008e+08 | 312795 | 0.00629366 | 1.5782 | 2(Loss) | true |
| jsonifier | 1671.1 | 0.427932 | 5084.64ms | 631514 | 30 | 7.13562e+07 | 360397 | 0.252784 | 1.8185 | 3(Loss) | true |
| simdjson (ondemand) | 1164.9 | 0.348133 | 6990.77ms | 631514 | 80 | 2.59161e+08 | 517005 | 0.0798502 | 2.60883 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4165.92 | 0.356785 | 8334.24ms | 716365 | 320 | 1.09549e+08 | 163992 | 0.0192426 | 0.728905 | 1(Win) | true |
| glaze | 1686.4 | 0.425161 | 5168.12ms | 716365 | 320 | 9.49301e+08 | 405111 | 0.241178 | 1.80127 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15066.3 | 0.203263 | 4556.7ms | 716365 | 1280 | 1.08738e+07 | 45344.8 | 0.126449 | 0.201573 | 1(Win) | true |
| glaze | 3085.17 | 0.538711 | 5640.73ms | 716365 | 640 | 9.10753e+08 | 221439 | 0.689951 | 0.985016 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1322.83 | 0.297613 | 195.096ms | 2632 | 40 | 1275.64 | 1897.5 | 0.65445 | 2.26714 | 1(Win) | true |
| jsonifier (two-stage) | 997.049 | 0.337222 | 264.97ms | 2632 | 80 | 5765.82 | 2517.5 | 0.0992063 | 3.03056 | 2(Loss) | true |
| glaze | 982.025 | 0.297516 | 268.382ms | 2632 | 1280 | 74021.6 | 2556.02 | 0.259131 | 3.06823 | 3(Loss) | true |
| simdjson (ondemand) | 649.156 | 0.22639 | 390.353ms | 2632 | 30 | 2298.85 | 3866.67 | 0 | 4.6555 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1766.1 | 0.323833 | 179.591ms | 2632 | 80 | 1694.62 | 1421.25 | 0.441696 | 1.69395 | 1(Win) | true |
| jsonifier | 1640.69 | 0.234788 | 182.851ms | 2632 | 2560 | 33030.1 | 1529.88 | 0.191131 | 1.83084 | 2(Loss) | true |
| jsonifier (two-stage) | 1261.34 | 0.440986 | 241.958ms | 2632 | 30 | 2310.34 | 1990 | 0.167785 | 2.38089 | 3(Loss) | true |
| simdjson (ondemand) | 785.74 | 0.508529 | 360.596ms | 2632 | 1280 | 337796 | 3194.53 | 0.368189 | 3.83802 | 4(Loss) | true |

----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9526 | 0.490247 | 29.0557ms | 2632 | 4890 | 8159.99 | 263.497 | 0.77197 | 0.298061 | 1(Win) | true |
| glaze | 3393.42 | 0.370328 | 77.4088ms | 2632 | 320 | 2401.16 | 739.688 | 0.126904 | 0.866488 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11249.6 | 1.07645 | 25.2517ms | 2632 | 320 | 1846 | 223.125 | 0.280899 | 0.247549 | 1(Win) | true |
| glaze | 4137.48 | 0.763526 | 64.8577ms | 2632 | 30 | 643.678 | 606.667 | 0.546448 | 0.702457 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1361.81 | 0.23355 | 241.246ms | 3370 | 80 | 2430.38 | 2360 | 0.211416 | 2.21199 | 1(Win) | true |
| jsonifier (two-stage) | 1195.12 | 0.331167 | 273.028ms | 3370 | 4890 | 387827 | 2689.16 | 0.223523 | 2.52168 | 2(Loss) | true |
| glaze | 1132.98 | 0.520508 | 287.338ms | 3370 | 30 | 6540.23 | 2836.67 | 0 | 2.64885 | 3(Loss) | true |
| simdjson (ondemand) | 828.32 | 0.279908 | 400.623ms | 3370 | 40 | 4717.95 | 3880 | 0.431406 | 3.65631 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1881.1 | 0.194437 | 204.933ms | 3370 | 2560 | 28251 | 1708.52 | 0.0274286 | 1.59026 | 1(Win) | true |
| jsonifier | 1679.36 | 0.11325 | 224.911ms | 3370 | 320 | 1503.13 | 1913.75 | 0.492287 | 1.7923 | 2(Loss) | true |
| jsonifier (two-stage) | 1508.86 | 0.344507 | 250.903ms | 3370 | 40 | 2153.85 | 2130 | 0.622084 | 1.99283 | 3(Loss) | true |
| simdjson (ondemand) | 1012.25 | 0.218386 | 367.702ms | 3370 | 40 | 1923.08 | 3175 | 0.366109 | 2.97473 | 4(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11758.4 | 0.340926 | 33.0314ms | 3643 | 2560 | 2597.67 | 295.469 | 0.526039 | 0.243666 | 1(Win) | true |
| glaze | 3862.36 | 0.288507 | 94.771ms | 3682 | 1280 | 8806.14 | 909.141 | 1.06274 | 0.769606 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14566.6 | 0.305818 | 26.8649ms | 3643 | 4890 | 2601.58 | 238.507 | 1.08888 | 0.190965 | 1(Win) | true |
| glaze | 4348.52 | 0.573414 | 85.4039ms | 3682 | 80 | 1715.19 | 807.5 | 0.308642 | 0.685029 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 653.348 | 0.379656 | 683.266ms | 4630 | 640 | 421340 | 6758.28 | 0.18298 | 4.63719 | 1(Win) | true |
| jsonifier (two-stage) | 611.969 | 0.179787 | 726.142ms | 4630 | 4890 | 822868 | 7215.26 | 0.225496 | 4.95114 | 2(Loss) | true |
| glaze | 355.409 | 0.435544 | 1249.38ms | 4630 | 80 | 234239 | 12423.8 | 0.0704793 | 8.5347 | 3(Loss) | true |
| simdjson (ondemand) | 350.132 | 0.214535 | 1272.17ms | 4630 | 2560 | 1.87384e+06 | 12611 | 0.268654 | 8.66536 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 799.423 | 0.25753 | 677.898ms | 4630 | 4890 | 989400 | 5523.37 | 0.286807 | 3.78871 | 1(Win) | true |
| jsonifier (two-stage) | 755.838 | 0.293314 | 718.152ms | 4630 | 160 | 46977.6 | 5841.88 | 0.311226 | 4.00805 | 2(Loss) | true |
| glaze | 396.62 | 0.199834 | 1242.02ms | 4630 | 4890 | 2.42025e+06 | 11132.8 | 0.310352 | 7.64677 | 3(Loss) | true |
| simdjson (ondemand) | 384.731 | 0.155568 | 1290.32ms | 4630 | 2560 | 816073 | 11476.9 | 0.115588 | 7.88269 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1800.41 | 0.326051 | 240.171ms | 4630 | 40 | 2557.69 | 2452.5 | 0.169607 | 1.67894 | 1(Win) | true |
| glaze | 1188.03 | 0.31818 | 378.518ms | 4630 | 30 | 4195.4 | 3716.67 | 0.179051 | 2.54333 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1910.44 | 0.153815 | 240.412ms | 4630 | 80 | 1011.08 | 2311.25 | 0.0540541 | 1.57819 | 1(Win) | true |
| glaze | 1280.78 | 0.267367 | 345.76ms | 4630 | 4890 | 415466 | 3447.51 | 0.0847597 | 2.3553 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1434.35 | 0.224433 | 772.46ms | 11579 | 2560 | 764266 | 7698.67 | 0.0619403 | 2.11235 | 1(Win) | true |
| jsonifier | 1328.88 | 0.15711 | 845.186ms | 11579 | 4890 | 833467 | 8309.69 | 0.0238993 | 2.28182 | 2(Loss) | true |
| simdjson (ondemand) | 815.071 | 0.219983 | 1357.41ms | 11579 | 2560 | 2.27388e+06 | 13548 | 0.12558 | 3.72263 | 3(Loss) | true |
| glaze | 793.072 | 0.28142 | 1396.23ms | 11579 | 1280 | 1.96533e+06 | 13923.8 | 0.0790509 | 3.82722 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1784.9 | 0.229028 | 765.992ms | 11579 | 30 | 6022.99 | 6186.67 | 0.107643 | 1.69513 | 1(Win) | true |
| jsonifier | 1653.08 | 0.166792 | 821.658ms | 11579 | 30 | 3724.14 | 6680 | 1.72589 | 1.83387 | 2(Loss) | true |
| simdjson (ondemand) | 897.769 | 0.18753 | 1379.76ms | 11579 | 2560 | 1.36205e+06 | 12300 | 0.232053 | 3.37767 | 3(Loss) | true |
| glaze | 887.312 | 0.114905 | 1389.18ms | 11579 | 40 | 8179.49 | 12445 | 0.173797 | 3.42138 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4916.24 | 0.334763 | 291.154ms | 14795 | 40 | 3692.31 | 2870 | 0 | 0.615495 | 1(Win) | true |
| glaze | 2991.44 | 0.205413 | 481.046ms | 14795 | 30 | 2816.09 | 4716.67 | 0.352113 | 1.01084 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5324.38 | 0.302129 | 273.729ms | 14795 | 40 | 2564.1 | 2650 | 0.250941 | 0.565108 | 1(Win) | true |
| glaze | 3301.46 | 0.154312 | 443.202ms | 14795 | 80 | 3479.43 | 4273.75 | 0.205158 | 0.914394 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 881.03 | 0.225885 | 356.49ms | 3223 | 320 | 19873 | 3488.75 | 0.0717103 | 3.42702 | 1(Win) | true |
| jsonifier (two-stage) | 754.512 | 0.455314 | 416.658ms | 3223 | 640 | 220186 | 4073.75 | 0.10728 | 4.00247 | 2(Loss) | true |
| glaze | 683.803 | 0.297516 | 468.038ms | 3223 | 40 | 7153.85 | 4495 | 0.111359 | 4.42076 | 3(Loss) | true |
| simdjson (ondemand) | 459.71 | 0.205861 | 680.39ms | 3223 | 4890 | 926421 | 6686.16 | 0.198786 | 6.59009 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1262.3 | 0.5609 | 321.784ms | 3223 | 40 | 7461.54 | 2435 | 0.205761 | 2.39294 | 1(Win) | true |
| jsonifier (two-stage) | 1012.75 | 0.383195 | 378.825ms | 3223 | 40 | 5410.26 | 3035 | 0.0549451 | 2.97941 | 2(Loss) | true |
| glaze | 862.792 | 0.251139 | 417.067ms | 3223 | 4890 | 391422 | 3562.49 | 0.0645913 | 3.49707 | 3(Loss) | true |
| simdjson (ondemand) | 519.397 | 0.185855 | 660.813ms | 3223 | 320 | 38709.9 | 5917.81 | 0.163969 | 5.82364 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6732.25 | 0.607857 | 48.7609ms | 3223 | 320 | 2464.64 | 456.562 | 0.0684932 | 0.432353 | 1(Win) | true |
| glaze | 3139.96 | 0.275043 | 100.918ms | 3223 | 4890 | 35447.3 | 978.896 | 0.158793 | 0.945828 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7542.8 | 0.727211 | 44.0853ms | 3223 | 80 | 702.532 | 407.5 | 0 | 0.384808 | 1(Win) | true |
| glaze | 3686.59 | 0.761562 | 86.3729ms | 3223 | 320 | 12901.3 | 833.75 | 0.679245 | 0.803915 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1322.69 | 0.221988 | 429.837ms | 5839 | 80 | 6987.34 | 4210 | 0.178465 | 2.28412 | 1(Win) | true |
| jsonifier | 1172.08 | 0.162959 | 478.483ms | 5839 | 4890 | 293107 | 4750.94 | 0.0955343 | 2.58014 | 2(Loss) | true |
| glaze | 1042.65 | 0.240771 | 552.47ms | 5839 | 2560 | 423298 | 5340.7 | 0.0453681 | 2.9038 | 3(Loss) | true |
| simdjson (ondemand) | 797.871 | 0.202737 | 707.929ms | 5839 | 4890 | 979005 | 6979.2 | 0.180876 | 3.79802 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1705.68 | 0.244705 | 399.042ms | 5839 | 1280 | 81691.8 | 3264.69 | 0.00478583 | 1.76946 | 1(Win) | true |
| jsonifier | 1504.49 | 0.195195 | 447.804ms | 5839 | 80 | 4175.63 | 3701.25 | 0.782845 | 2.00486 | 2(Loss) | true |
| glaze | 1300.18 | 0.217978 | 492.743ms | 5839 | 4890 | 426190 | 4282.86 | 0.287119 | 2.32356 | 3(Loss) | true |
| simdjson (ondemand) | 873.924 | 0.232264 | 700.762ms | 5839 | 4890 | 1.07103e+06 | 6371.84 | 0.135841 | 3.46224 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12389.2 | 0.496841 | 57.9331ms | 6938 | 320 | 2253.04 | 534.062 | 0.291715 | 0.238509 | 1(Win) | true |
| glaze | 3725.7 | 0.958738 | 178.747ms | 6960 | 320 | 93358.1 | 1781.56 | 0.297307 | 0.8044 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13686.6 | 0.440163 | 51.8934ms | 6938 | 320 | 1448.96 | 483.438 | 0.0645995 | 0.21423 | 1(Win) | true |
| glaze | 4604.43 | 0.624328 | 154.92ms | 6960 | 1280 | 103682 | 1441.56 | 0.581897 | 0.646751 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1069.66 | 0.386667 | 437.761ms | 4857 | 4890 | 1.37096e+06 | 4330.33 | 0.0780795 | 2.82775 | 1(Win) | true |
| glaze | 1014.26 | 0.216634 | 460.588ms | 4857 | 4890 | 478628 | 4566.87 | 0.14784 | 2.98116 | 2(Loss) | true |
| jsonifier (two-stage) | 869.483 | 0.251497 | 538.399ms | 4857 | 4890 | 877788 | 5327.3 | 0.0960717 | 3.48165 | 3(Loss) | true |
| simdjson (ondemand) | 546.659 | 0.334918 | 851.849ms | 4857 | 640 | 515420 | 8473.28 | 0.255665 | 5.54456 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1890.91 | 0.276455 | 293.784ms | 4857 | 1280 | 58702 | 2449.61 | 0.0861849 | 1.5909 | 1(Win) | true |
| jsonifier | 1475.07 | 0.525895 | 367.665ms | 4857 | 2560 | 698153 | 3140.2 | 0.115554 | 2.04765 | 2(Loss) | true |
| jsonifier (two-stage) | 1206.62 | 0.329146 | 434.385ms | 4857 | 4890 | 780694 | 3838.81 | 0.112706 | 2.50507 | 3(Loss) | true |
| simdjson (ondemand) | 702.291 | 0.308142 | 706.372ms | 4857 | 2560 | 1.05741e+06 | 6595.55 | 0.0272363 | 4.30764 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9501.53 | 0.275931 | 51.5592ms | 4857 | 640 | 1158.06 | 487.5 | 0.191939 | 0.307931 | 1(Win) | true |
| glaze | 3600.73 | 0.168072 | 135.906ms | 4857 | 640 | 2991.76 | 1286.41 | 0.783321 | 0.83045 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10402.6 | 0.859368 | 46.6841ms | 4857 | 2560 | 37484.5 | 445.273 | 0.0613712 | 0.279909 | 1(Win) | true |
| glaze | 4419.32 | 0.307283 | 114.716ms | 4857 | 320 | 3319.36 | 1048.12 | 0.945068 | 0.666725 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1216.15 | 0.266279 | 528.595ms | 6701 | 2560 | 501212 | 5254.77 | 0.334879 | 2.48883 | 1(Win) | true |
| jsonifier (two-stage) | 1182.28 | 0.303767 | 545.395ms | 6701 | 320 | 86272.6 | 5405.31 | 0.727929 | 2.55731 | 2(Loss) | true |
| jsonifier | 1071.15 | 0.382395 | 591.845ms | 6701 | 1280 | 666215 | 5966.09 | 0.262584 | 2.82552 | 3(Loss) | true |
| simdjson (ondemand) | 737.142 | 0.124582 | 878.585ms | 6701 | 4890 | 570425 | 8669.39 | 0.367536 | 4.11322 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2157.61 | 0.143166 | 349.375ms | 6701 | 160 | 2876.97 | 2961.88 | 0.105396 | 1.39474 | 1(Win) | true |
| jsonifier (two-stage) | 1626.36 | 0.298078 | 448.36ms | 6701 | 320 | 43899.3 | 3929.38 | 0.26967 | 1.85489 | 2(Loss) | true |
| jsonifier | 1344.8 | 0.414506 | 526.752ms | 6701 | 4890 | 1.89729e+06 | 4752.07 | 0.519629 | 2.24942 | 3(Loss) | true |
| simdjson (ondemand) | 936.433 | 0.392859 | 730.102ms | 6701 | 1280 | 920047 | 6824.38 | 0.531707 | 3.23004 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11353.5 | 0.262459 | 64.8361ms | 7376 | 4890 | 12930.5 | 619.571 | 0.386115 | 0.25864 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2779.24 | 0.766225 | 253.384ms | 7376 | 2560 | 962813 | 2531.02 | 4.24155 | 1.08277 | -(Loss) | false |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12470.8 | 0.47627 | 59.1844ms | 7376 | 320 | 2309.46 | 564.062 | 0.055371 | 0.235791 | 1(Win) | true |
| glaze | 3095.13 | 0.358899 | 228.955ms | 7376 | 4890 | 325340 | 2272.7 | 1.38963 | 0.964797 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1331.4 | 0.440446 | 127.577ms | 1691 | 80 | 2276.9 | 1211.25 | 0.513347 | 2.2505 | 1(Win) | true |
| jsonifier | 1211.25 | 0.351145 | 136.029ms | 1691 | 640 | 13988.6 | 1331.41 | 0.152332 | 2.46584 | 2(Loss) | true |
| jsonifier (two-stage) | 844.05 | 0.280739 | 195.722ms | 1691 | 160 | 4603.38 | 1910.62 | 0.0327011 | 3.56518 | 3(Loss) | true |
| simdjson (ondemand) | 524.81 | 0.17335 | 312.966ms | 1691 | 2560 | 72639 | 3072.85 | 0.35081 | 5.75631 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1888.92 | 0.326978 | 109.438ms | 1691 | 320 | 2493.73 | 853.75 | 0.364697 | 1.57181 | 1(Win) | true |
| jsonifier | 1728.65 | 0.256223 | 118.939ms | 1691 | 4890 | 27939.4 | 932.904 | 0.257502 | 1.72542 | 2(Loss) | true |
| jsonifier (two-stage) | 1151.7 | 0.191489 | 173.942ms | 1691 | 4890 | 35156.4 | 1400.25 | 0.0566131 | 2.59496 | 3(Loss) | true |
| simdjson (ondemand) | 610.749 | 0.269193 | 292.671ms | 1691 | 640 | 32334.7 | 2640.47 | 0.0532292 | 4.94229 | 4(Loss) | true |

----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9763.25 | 0.3916 | 22.1141ms | 1996 | 4890 | 2850.53 | 194.969 | 0.0845142 | 0.283298 | 1(Win) | true |
| glaze | 3955.4 | 0.481228 | 54.3842ms | 1996 | 320 | 1716.3 | 481.25 | 0.645161 | 0.74292 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 13314.3 | 1.36975 | 17.0215ms | 1996 | 640 | 2454.4 | 142.969 | 1.40086 | 0.200658 | 1(Win) | true |
| glaze | 5438.67 | 1.60727 | 41.6011ms | 1996 | 80 | 2531.65 | 350 | 2.0979 | 0.511536 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1426.71 | 0.291886 | 149.726ms | 2158 | 160 | 2836.48 | 1442.5 | 0.0865801 | 2.10414 | 1(Win) | true |
| jsonifier | 1156.81 | 0.346855 | 181.24ms | 2158 | 1280 | 48740.3 | 1779.06 | 0.0175623 | 2.59678 | 2(Loss) | true |
| jsonifier (two-stage) | 1071.5 | 0.196612 | 200.93ms | 2158 | 2560 | 36507.5 | 1920.7 | 0.248736 | 2.80351 | 3(Loss) | true |
| simdjson (ondemand) | 666.029 | 0.284001 | 314.632ms | 2158 | 30 | 2310.34 | 3090 | 0.542299 | 4.51812 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1932.56 | 0.188473 | 131.511ms | 2158 | 1280 | 5156.37 | 1064.92 | 0.836607 | 1.53984 | 1(Win) | true |
| jsonifier | 1534.6 | 0.344204 | 160.504ms | 2158 | 4890 | 104196 | 1341.08 | 0.666204 | 1.95451 | 2(Loss) | true |
| jsonifier (two-stage) | 1449.32 | 0.708261 | 180.231ms | 2158 | 30 | 3034.48 | 1420 | 0.46729 | 2.06432 | 3(Loss) | true |
| simdjson (ondemand) | 764.911 | 0.308261 | 293.42ms | 2158 | 1280 | 88049.7 | 2690.55 | 0.355882 | 3.94476 | 4(Loss) | true |

----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12675.9 | 0.666143 | 24.2747ms | 2866 | 640 | 1320.42 | 215.625 | 0.719424 | 0.220199 | 1(Win) | true |
| glaze | 3714.34 | 0.685725 | 79.0557ms | 2866 | 1280 | 32591.1 | 735.859 | 0.789973 | 0.796623 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15888 | 0.729549 | 21.4015ms | 2866 | 1280 | 2016.2 | 172.031 | 0.0909091 | 0.175212 | 1(Win) | true |
| glaze | 3709.22 | 1.11855 | 62.4105ms | 2866 | 1280 | 86958.2 | 736.875 | 0.338123 | 0.78657 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1580.28 | 0.654073 | 268.454ms | 4390 | 1280 | 384347 | 2649.3 | 1.08797 | 1.9107 | 1(Win) | true |
| jsonifier (two-stage) | 1105.5 | 0.492228 | 379.3ms | 4390 | 4890 | 1.69924e+06 | 3787.1 | 0.130817 | 2.73574 | 2(Loss) | true |
| glaze | 1086.38 | 0.400651 | 395.294ms | 4390 | 320 | 76286.8 | 3853.75 | 0.636527 | 2.78024 | 3(Loss) | true |
| simdjson (ondemand) | 451.206 | 0.229089 | 936.28ms | 4390 | 2560 | 1.15672e+06 | 9278.75 | 0.233523 | 6.71973 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2052.27 | 0.384541 | 259.13ms | 4390 | 40 | 2461.54 | 2040 | 0.327869 | 1.47381 | 1(Win) | true |
| glaze | 1356.68 | 0.333252 | 348.565ms | 4390 | 2560 | 270744 | 3085.94 | 0.460337 | 2.22214 | 2(Loss) | true |
| jsonifier (two-stage) | 1304.09 | 0.173124 | 371.934ms | 4390 | 1280 | 39540.1 | 3210.39 | 1.89323 | 2.31787 | 3(Loss) | true |
| simdjson (ondemand) | 480.372 | 0.234145 | 934.558ms | 4390 | 1280 | 533031 | 8715.39 | 0.537625 | 6.30374 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8928.7 | 0.316816 | 49.6483ms | 4390 | 4890 | 10791.4 | 468.896 | 0.276397 | 0.32793 | 1(Win) | true |
| glaze | 3511.72 | 0.164051 | 124.66ms | 4390 | 320 | 1224.04 | 1192.19 | 1.01194 | 0.848312 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9731.93 | 0.43133 | 45.8306ms | 4390 | 2560 | 8814.34 | 430.195 | 0.154602 | 0.299657 | 1(Win) | true |
| glaze | 4015.18 | 0.208139 | 107.519ms | 4390 | 4890 | 23032.2 | 1042.7 | 0.0969187 | 0.737403 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2245.85 | 0.136713 | 405.707ms | 9378 | 2560 | 75879.2 | 3982.27 | 0.402509 | 1.34701 | 1(Win) | true |
| jsonifier | 2048.63 | 0.392801 | 446.625ms | 9378 | 160 | 47049.9 | 4365.62 | 0.0716332 | 1.47725 | 2(Loss) | true |
| glaze | 1732.88 | 0.219716 | 521.857ms | 9378 | 4890 | 628804 | 5161.08 | 0.0667516 | 1.7473 | 3(Loss) | true |
| simdjson (ondemand) | 904.028 | 0.20185 | 997.442ms | 9378 | 2560 | 1.02083e+06 | 9893.01 | 0.0359184 | 3.355 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2721.16 | 0.349304 | 395.864ms | 9378 | 30 | 3954.02 | 3286.67 | 0.202429 | 1.11071 | 1(Win) | true |
| jsonifier | 2303.56 | 0.556988 | 438.133ms | 9378 | 80 | 37411.4 | 3882.5 | 0 | 1.30952 | 2(Loss) | true |
| glaze | 2072.67 | 0.195487 | 476.342ms | 9378 | 40 | 2846.15 | 4315 | 0.269646 | 1.45637 | 3(Loss) | true |
| simdjson (ondemand) | 950.21 | 0.200579 | 1000.78ms | 9378 | 320 | 114052 | 9412.19 | 0.156292 | 3.18582 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 15956.1 | 0.35374 | 68.9915ms | 11521 | 1280 | 7594.58 | 688.594 | 1.84886 | 0.184713 | 1(Win) | true |
| glaze | 4886.63 | 0.132002 | 234.701ms | 11521 | 320 | 2818.87 | 2248.44 | 0.883343 | 0.615533 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 19841.6 | 1.01302 | 58.8841ms | 11521 | 80 | 2517.41 | 553.75 | 0.226244 | 0.147296 | 1(Win) | true |
| glaze | 6024.38 | 0.312864 | 186.166ms | 11521 | 4890 | 159212 | 1823.8 | 0.690487 | 0.493915 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2095.72 | 0.539688 | 217.231ms | 4669 | 4890 | 642947 | 2124.66 | 0.425328 | 1.43792 | 1(Win) | true |
| jsonifier (two-stage) | 1492.59 | 0.313124 | 303.867ms | 4669 | 4890 | 426687 | 2983.21 | 0.0939376 | 2.02227 | 2(Loss) | true |
| glaze | 1411.93 | 0.215461 | 320.523ms | 4669 | 4890 | 225768 | 3153.62 | 0.308959 | 2.13934 | 3(Loss) | true |
| simdjson (ondemand) | 595.002 | 0.251694 | 754.019ms | 4669 | 2560 | 908231 | 7483.52 | 0.315323 | 5.0946 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2369.34 | 0.253141 | 208.137ms | 4669 | 4890 | 110670 | 1879.3 | 0.407389 | 1.2691 | 1(Win) | true |
| glaze | 1662.4 | 0.220155 | 281.779ms | 4669 | 4890 | 170038 | 2678.49 | 0.0244077 | 1.80932 | 2(Loss) | true |
| jsonifier (two-stage) | 1649.15 | 0.174318 | 294.747ms | 4669 | 80 | 1772.15 | 2700 | 0.558659 | 1.83047 | 3(Loss) | true |
| simdjson (ondemand) | 641.98 | 0.233561 | 712.126ms | 4669 | 4890 | 1.28325e+06 | 6935.89 | 0.168801 | 4.71795 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10427 | 0.3781 | 44.7731ms | 4669 | 4890 | 12748.2 | 427.035 | 0.372824 | 0.279434 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3294.68 | 0.494889 | 142.56ms | 4669 | 2560 | 114519 | 1351.48 | 2.86917 | 0.908444 | -(Loss) | false |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11829.5 | 0.385525 | 40.0057ms | 4669 | 1280 | 2695.44 | 376.406 | 1.27049 | 0.245095 | 1(Win) | true |
| glaze DID NOT CONVERGE | 3903.74 | 1.46524 | 125.834ms | 4669 | 160 | 44691.4 | 1140.62 | 3.57548 | 0.755227 | -(Loss) | false |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2253.66 | 0.358304 | 337.459ms | 7932 | 640 | 92570.3 | 3356.56 | 0.638298 | 1.34044 | 1(Win) | true |
| jsonifier | 1850.09 | 0.0972253 | 414.221ms | 7932 | 80 | 1264.24 | 4088.75 | 0.399018 | 1.62821 | 2(Loss) | true |
| glaze | 1825.46 | 0.274086 | 417.285ms | 7932 | 640 | 82560.6 | 4143.91 | 0.229479 | 1.65566 | 3(Loss) | true |
| simdjson (ondemand) | 968.534 | 0.144083 | 788.306ms | 7932 | 4890 | 619256 | 7810.31 | 0.495744 | 3.13028 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2485.27 | 0.192459 | 323.917ms | 7932 | 80 | 2745.25 | 3043.75 | 0.531046 | 1.21429 | 1(Win) | true |
| glaze | 2081.21 | 0.252224 | 385.232ms | 7932 | 4890 | 410975 | 3634.68 | 0.0591974 | 1.44983 | 2(Loss) | true |
| jsonifier | 1992.8 | 0.0608551 | 406.227ms | 7932 | 320 | 1707.58 | 3795.94 | 0.336396 | 1.516 | 3(Loss) | true |
| simdjson (ondemand) | 1042.05 | 0.272197 | 744.344ms | 7932 | 4890 | 1.90928e+06 | 7259.33 | 0.416454 | 2.90724 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 16348.5 | 0.358483 | 57.2377ms | 9249 | 640 | 2394.15 | 539.531 | 0.261324 | 0.180234 | 1(Win) | true |
| glaze | 3190.5 | 0.562145 | 288.846ms | 9249 | 4890 | 1.18107e+06 | 2764.62 | 1.57521 | 0.943824 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 17847.4 | 0.211921 | 52.8076ms | 9249 | 640 | 702.049 | 494.219 | 0.471995 | 0.164213 | 1(Win) | true |
| glaze | 3075.53 | 0.450668 | 287.995ms | 9249 | 2560 | 427664 | 2867.97 | 0.724359 | 0.974287 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 485.38 | 0.339545 | 907.723ms | 4604 | 1280 | 1.20757e+06 | 9045.94 | 0.207706 | 6.24462 | 1(Win) | true |
| jsonifier (two-stage) | 433.164 | 0.214626 | 1026.34ms | 4604 | 4890 | 2.3144e+06 | 10136.4 | 0.307219 | 6.99972 | 2(Loss) | true |
| glaze | 300.728 | 0.278312 | 1465.57ms | 4604 | 320 | 528370 | 14600.3 | 0.00214041 | 10.0878 | 3(Loss) | true |
| simdjson (ondemand) | 138.368 | 0.369243 | 3159.53ms | 4604 | 1280 | 1.75727e+07 | 31732.3 | 0.114844 | 21.9474 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 599.31 | 0.172218 | 870.904ms | 4604 | 2560 | 407534 | 7326.29 | 0.0815104 | 5.05684 | 1(Win) | true |
| jsonifier (two-stage) | 540.749 | 0.225012 | 941.785ms | 4604 | 640 | 213634 | 8119.69 | 0.00384852 | 5.60325 | 2(Loss) | true |
| glaze | 335.911 | 0.202339 | 1428.7ms | 4604 | 4890 | 3.42051e+06 | 13071.1 | 0.174596 | 9.03019 | 3(Loss) | true |
| simdjson (ondemand) | 143.915 | 0.123864 | 3196.8ms | 4604 | 4890 | 6.98318e+06 | 30509.1 | 0.0769982 | 21.1029 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1454.07 | 0.305128 | 304.149ms | 4604 | 1280 | 108661 | 3019.61 | 0.220401 | 2.07616 | 1(Win) | true |
| glaze | 919.87 | 0.469598 | 480.208ms | 4604 | 4890 | 2.45685e+06 | 4773.19 | 0.0939299 | 3.28757 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1494.87 | 0.537974 | 296.692ms | 4604 | 320 | 79898 | 2937.19 | 0.0106383 | 2.01155 | 1(Win) | true |
| glaze | 987.64 | 0.303866 | 450.866ms | 4604 | 2560 | 467172 | 4445.66 | 0.0395556 | 3.05669 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1602.84 | 0.230731 | 1106.05ms | 18245 | 2560 | 1.60606e+06 | 10855.6 | 0.0805385 | 1.89192 | 1(Win) | true |
| jsonifier | 1442.68 | 0.206991 | 1218.81ms | 18245 | 2560 | 1.59546e+06 | 12060.7 | 0.0356144 | 2.10253 | 2(Loss) | true |
| glaze | 1024.07 | 0.145597 | 1712.22ms | 18245 | 4890 | 2.99255e+06 | 16990.8 | 0.282455 | 2.96381 | 3(Loss) | true |
| simdjson (ondemand) | 521.948 | 0.349789 | 3376.66ms | 18245 | 160 | 2.17553e+06 | 33336.2 | 0.146451 | 5.81921 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1927.21 | 0.236666 | 1036.52ms | 18245 | 4890 | 2.23259e+06 | 9028.47 | 0.0210906 | 1.5728 | 1(Win) | true |
| jsonifier | 1680.09 | 0.372215 | 1193.61ms | 18245 | 1280 | 1.90205e+06 | 10356.5 | 0.0898493 | 1.80505 | 2(Loss) | true |
| glaze | 1145.1 | 0.0704958 | 1656.23ms | 18245 | 40 | 4589.74 | 15195 | 0.164258 | 2.64758 | 3(Loss) | true |
| simdjson (ondemand) | 536.823 | 0.299804 | 3404.91ms | 18245 | 640 | 6.04338e+06 | 32412.5 | 0.299778 | 5.65763 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6613.4 | 0.34282 | 364.074ms | 24579 | 640 | 94491 | 3544.38 | 0.336164 | 0.45638 | 1(Win) | true |
| glaze | 2691.87 | 0.190592 | 879.843ms | 24579 | 2560 | 705132 | 8707.85 | 0.321773 | 1.12568 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6867.38 | 0.235266 | 349.87ms | 24579 | 4890 | 315336 | 3413.29 | 0.306579 | 0.43771 | 1(Win) | true |
| glaze | 3137.24 | 0.297068 | 755.504ms | 24579 | 2560 | 1.2612e+06 | 7471.64 | 0.0805776 | 0.965746 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 516.678 | 0.183188 | 853.358ms | 4604 | 640 | 155098 | 8497.97 | 0.252535 | 5.86791 | 1(Win) | true |
| jsonifier (two-stage) | 454.997 | 0.265225 | 986.407ms | 4604 | 80 | 52405.1 | 9650 | 0.25974 | 6.66279 | 2(Loss) | true |
| glaze | 294.031 | 0.209056 | 1517.76ms | 4604 | 2560 | 2.49489e+06 | 14932.9 | 0.127556 | 10.3193 | 3(Loss) | true |
| simdjson (ondemand) | 278.776 | 0.187039 | 1613.64ms | 4604 | 30 | 26034.5 | 15750 | 0.19084 | 10.8897 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 649.394 | 0.227889 | 819.083ms | 4604 | 160 | 37985.8 | 6761.25 | 0.166667 | 4.66623 | 1(Win) | true |
| jsonifier (two-stage) | 586.406 | 0.144949 | 904.031ms | 4604 | 40 | 4711.54 | 7487.5 | 0.0111309 | 5.16367 | 2(Loss) | true |
| glaze | 340.919 | 0.261385 | 1421.02ms | 4604 | 1280 | 1.45057e+06 | 12879.1 | 0.399523 | 8.89607 | 3(Loss) | true |
| simdjson (ondemand) | 310.113 | 0.383921 | 1553.76ms | 4604 | 320 | 945509 | 14158.4 | 0.720922 | 9.78658 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1537.01 | 0.322119 | 295.99ms | 4604 | 30 | 2540.23 | 2856.67 | 0.233918 | 1.96358 | 1(Win) | true |
| glaze | 913.771 | 0.205677 | 490.764ms | 4604 | 4890 | 477612 | 4805.05 | 0.464149 | 3.31014 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1577.42 | 0.153178 | 281.227ms | 4604 | 2560 | 46538.1 | 2783.48 | 0.0631916 | 1.90456 | 1(Win) | true |
| glaze | 998.546 | 0.337037 | 448.982ms | 4604 | 2560 | 562250 | 4397.11 | 0.5548 | 3.02808 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1672.45 | 0.234671 | 1046.25ms | 18245 | 4890 | 2.91479e+06 | 10403.8 | 0.22214 | 1.81305 | 1(Win) | true |
| jsonifier | 1519.59 | 0.245325 | 1163.07ms | 18245 | 640 | 505008 | 11450.3 | 0.839388 | 1.99598 | 2(Loss) | true |
| glaze | 1011.37 | 0.24042 | 1724.99ms | 18245 | 1280 | 2.18986e+06 | 17204.1 | 0.0186218 | 3.00078 | 3(Loss) | true |
| simdjson (ondemand) | 994.271 | 0.270905 | 1759.07ms | 18245 | 4890 | 1.09906e+07 | 17500 | 0.259386 | 3.05266 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2073.05 | 0.160897 | 983.335ms | 18245 | 30 | 5471.26 | 8393.33 | 0.0793651 | 1.46116 | 1(Win) | true |
| jsonifier | 1814.37 | 0.115641 | 1119.74ms | 18245 | 30 | 3689.66 | 9590 | 0.0347705 | 1.66943 | 2(Loss) | true |
| glaze | 1123.48 | 0.298088 | 1671.55ms | 18245 | 4890 | 1.04222e+07 | 15487.4 | 0.0982602 | 2.7007 | 3(Loss) | true |
| simdjson (ondemand) | 1093.85 | 0.136983 | 1704.62ms | 18245 | 4890 | 2.32173e+06 | 15906.9 | 0.237396 | 2.77467 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6779.64 | 0.402547 | 348.217ms | 24579 | 4890 | 947235 | 3457.46 | 0.311759 | 0.445416 | 1(Win) | true |
| glaze | 2730.25 | 0.253355 | 860.641ms | 24579 | 2560 | 1.21122e+06 | 8585.43 | 0.124057 | 1.10991 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7128.98 | 0.225477 | 333.629ms | 24579 | 4890 | 268773 | 3288.04 | 0.123707 | 0.42166 | 1(Win) | true |
| glaze | 3174.18 | 0.2986 | 754.934ms | 24579 | 640 | 311189 | 7384.69 | 0.849266 | 0.954612 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 926.589 | 0.164725 | 530.988ms | 5094 | 4890 | 364729 | 5242.9 | 0.631268 | 3.26839 | 1(Win) | true |
| jsonifier (two-stage) | 817.418 | 0.102954 | 612.986ms | 5094 | 160 | 5990.17 | 5943.12 | 0.0105175 | 3.70434 | 2(Loss) | true |
| glaze | 773.046 | 0.143123 | 632.594ms | 5094 | 4890 | 395583 | 6284.25 | 0.0298949 | 3.91801 | 3(Loss) | true |
| simdjson (ondemand) | 430.282 | 0.294349 | 1134.47ms | 5094 | 320 | 353417 | 11290.3 | 0.130259 | 7.05014 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1128.9 | 0.207945 | 525.462ms | 5094 | 30 | 2402.3 | 4303.33 | 0 | 2.68526 | 1(Win) | true |
| glaze | 1099.51 | 0.309448 | 530.508ms | 5094 | 4890 | 914128 | 4418.36 | 0.595979 | 2.74877 | 2(Loss) | true |
| jsonifier (two-stage) | 973.611 | 0.158639 | 607.16ms | 5094 | 320 | 20050.1 | 4989.69 | 0.430282 | 3.11039 | 3(Loss) | true |
| simdjson (ondemand) | 508.186 | 0.157121 | 1060.09ms | 5094 | 2560 | 577541 | 9559.53 | 0.020427 | 5.96741 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9271.6 | 0.213903 | 55.0571ms | 5094 | 4890 | 6142.57 | 523.967 | 1.75666 | 0.31589 | 1(Win) | true |
| glaze | 3482.45 | 0.510126 | 153.044ms | 5094 | 40 | 2025.64 | 1395 | 0.829384 | 0.858677 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 11727.7 | 0.42521 | 43.8307ms | 5094 | 4890 | 15170.7 | 414.233 | 0.164051 | 0.247899 | 1(Win) | true |
| glaze | 3879.26 | 0.303006 | 128.876ms | 5094 | 2560 | 36860.6 | 1252.3 | 1.92344 | 0.765288 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1237.31 | 0.267704 | 623.667ms | 8051 | 4890 | 1.34945e+06 | 6205.4 | 0.213986 | 2.44782 | 1(Win) | true |
| jsonifier | 1160.8 | 0.211823 | 668.031ms | 8051 | 4890 | 959936 | 6614.46 | 0.0801773 | 2.6098 | 2(Loss) | true |
| glaze | 1095.09 | 0.455848 | 711.361ms | 8051 | 1280 | 1.30753e+06 | 7011.33 | 0.0523432 | 2.76594 | 3(Loss) | true |
| simdjson (ondemand) | 668.693 | 0.239462 | 1154.88ms | 8051 | 2560 | 1.93536e+06 | 11482.1 | 0.131832 | 4.53583 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 1489.7 | 0.242431 | 621.12ms | 8051 | 640 | 99920.9 | 5154.06 | 0.10318 | 2.03092 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1482.6 | 0.268567 | 612.495ms | 8051 | 640 | 123804 | 5178.75 | 0.144613 | 2.04227 | 1(Tie) | true |
| jsonifier | 1386.08 | 0.316334 | 665.236ms | 8051 | 320 | 98256.7 | 5539.38 | 0.583287 | 2.18367 | 3(Loss) | true |
| simdjson (ondemand) | 770.327 | 0.186851 | 1098.9ms | 8051 | 4890 | 1.69608e+06 | 9967.24 | 0.511428 | 3.93674 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 14710.4 | 0.296487 | 64.4984ms | 9255 | 80 | 253.165 | 600 | 0.414938 | 0.200213 | 1(Win) | true |
| glaze | 3807.5 | 0.266369 | 237.874ms | 9255 | 1280 | 48803.4 | 2318.12 | 0.460455 | 0.790624 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 18012.8 | 0.688829 | 52.0884ms | 9255 | 80 | 911.392 | 490 | 0 | 0.162346 | 1(Win) | true |
| glaze | 5072.56 | 0.316769 | 181.871ms | 9255 | 80 | 2430.38 | 1740 | 0.143885 | 0.587387 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3974.99 | 0.514992 | 72.4673ms | 2889 | 1280 | 16309.2 | 693.125 | 0.359389 | 0.74569 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3960.7 | 0.345488 | 73.0528ms | 2889 | 160 | 924.135 | 695.625 | 0.27027 | 0.749187 | 1(Tie) | true |
| simdjson (ondemand) | 3122 | 0.255796 | 92.0383ms | 2889 | 640 | 3261.35 | 882.5 | 0.423131 | 0.954128 | 3(Loss) | true |
| glaze | 2962.54 | 0.877953 | 100.319ms | 2889 | 40 | 2666.67 | 930 | 0.711744 | 1.00412 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4355.99 | 0.587265 | 68.2741ms | 2889 | 160 | 2207.55 | 632.5 | 0 | 0.679063 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4271.57 | 0.867789 | 68.5465ms | 2889 | 80 | 2506.33 | 645 | 0 | 0.692744 | 1(Tie) | true |
| simdjson (ondemand) | 3380.57 | 0.701561 | 86.9916ms | 2889 | 40 | 1307.69 | 815 | 0.617284 | 0.880192 | 3(Loss) | true |
| glaze | 3175.98 | 0.641129 | 97.7397ms | 2889 | 80 | 2474.68 | 867.5 | 0.57971 | 0.936418 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 4810.06 | 0.368931 | 78.0389ms | 3808 | 320 | 2482.76 | 755 | 0.165837 | 0.615733 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 4770.81 | 0.30906 | 77.8978ms | 3808 | 2560 | 14168.9 | 761.211 | 0.376017 | 0.620509 | 1(Tie) | true |
| simdjson (ondemand) | 3705.71 | 0.653584 | 100.91ms | 3808 | 40 | 1641.03 | 980 | 0.338983 | 0.803118 | 3(Loss) | true |
| glaze | 3325.06 | 0.159677 | 112.884ms | 3808 | 320 | 973.256 | 1092.19 | 0.76661 | 0.895913 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5211.54 | 0.208618 | 74.3382ms | 3808 | 2560 | 5410.07 | 696.836 | 0.0280206 | 0.568593 | 1(Win) | true |
| jsonifier (two-stage) | 5116.04 | 0.130087 | 74.8593ms | 3808 | 1280 | 1091.45 | 709.844 | 0.175786 | 0.578109 | 2(Loss) | true |
| simdjson (ondemand) | 4003.13 | 0.379789 | 96.6031ms | 3808 | 1280 | 15194.6 | 907.188 | 0.257688 | 0.745933 | 3(Loss) | true |
| glaze | 3391.29 | 0.366689 | 109.552ms | 3808 | 1280 | 19736.6 | 1070.86 | 0.0218914 | 0.869775 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1659.74 | 0.548023 | 169.63ms | 2889 | 30 | 2482.76 | 1660 | 0.201207 | 1.81501 | 1(Win) | true |
| jsonifier | 1500.19 | 0.276454 | 188.938ms | 2889 | 4890 | 126054 | 1836.54 | 0.0947937 | 2.00023 | 2(Loss) | true |
| jsonifier (two-stage) | 1258.01 | 0.254912 | 225.451ms | 2889 | 4890 | 152412 | 2190.1 | 0.290561 | 2.39119 | 3(Loss) | true |
| simdjson (ondemand) | 1022.8 | 0.178961 | 277.425ms | 2889 | 80 | 1859.18 | 2693.75 | 0.231481 | 2.95497 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2014.75 | 0.548446 | 158.136ms | 2889 | 40 | 2250 | 1367.5 | 0.0609756 | 1.47563 | 1(Win) | true |
| jsonifier | 1776.31 | 0.409363 | 176.749ms | 2889 | 4890 | 197145 | 1551.06 | 0.199916 | 1.68668 | 2(Loss) | true |
| jsonifier (two-stage) | 1486.27 | 0.302608 | 211.673ms | 2889 | 80 | 2517.41 | 1853.75 | 0.202703 | 2.0223 | 3(Loss) | true |
| simdjson (ondemand) | 1106.49 | 0.192925 | 268.935ms | 2889 | 40 | 923.077 | 2490 | 0.267023 | 2.70765 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9683.92 | 0.375349 | 32.0205ms | 2963 | 1280 | 1535.47 | 291.797 | 0.0803859 | 0.293733 | 1(Win) | true |
| glaze | 4196.96 | 0.454714 | 77.0853ms | 2963 | 640 | 5998.61 | 673.281 | 1.2453 | 0.702404 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12204.4 | 0.28891 | 25.5531ms | 2963 | 4890 | 2188.07 | 231.534 | 0.515881 | 0.226577 | 1(Win) | true |
| glaze | 5298.26 | 1.64133 | 60.6473ms | 2963 | 30 | 2298.85 | 533.333 | 0.628931 | 0.530723 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 1877.13 | 0.182512 | 197.051ms | 3808 | 2560 | 31917.4 | 1934.65 | 0.675838 | 1.60009 | 1(Win) | true |
| jsonifier (two-stage) | 1643.25 | 0.252075 | 228.752ms | 3808 | 30 | 931.034 | 2210 | 0.300752 | 1.83356 | 2(Loss) | true |
| jsonifier | 1482.28 | 0.37897 | 258.02ms | 3808 | 30 | 2586.21 | 2450 | 0.27137 | 2.03409 | 3(Loss) | true |
| simdjson (ondemand) | 1296.2 | 0.202994 | 285.295ms | 3808 | 640 | 20701.3 | 2801.72 | 0.769922 | 2.32975 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| glaze | 2288.82 | 0.657436 | 183.818ms | 3808 | 30 | 3264.37 | 1586.67 | 0 | 1.30522 | 1(Win) | true |
| jsonifier (two-stage) | 1952.47 | 0.489096 | 213.982ms | 3808 | 30 | 2482.76 | 1860 | 0 | 1.5368 | 2(Loss) | true |
| jsonifier | 1638.77 | 0.303334 | 243.985ms | 3808 | 4890 | 220959 | 2216.05 | 0.458566 | 1.83553 | 3(Loss) | true |
| simdjson (ondemand) | 1391.41 | 0.184055 | 278.218ms | 3808 | 40 | 923.077 | 2610 | 0 | 2.15396 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 10047.9 | 0.390195 | 43.3251ms | 4300 | 320 | 811.52 | 408.125 | 0.616333 | 0.288644 | 1(Win) | true |
| glaze | 3298.16 | 0.585507 | 138.72ms | 4300 | 1280 | 67837 | 1243.36 | 1.34515 | 0.904399 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 12339 | 0.556815 | 35.985ms | 4300 | 640 | 2191.68 | 332.344 | 0.977654 | 0.232871 | 1(Win) | true |
| glaze | 4372 | 1.30416 | 104.507ms | 4300 | 2560 | 383067 | 937.969 | 1.77164 | 0.670234 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2958.72 | 0.268582 | 7700.68ms | 466906 | 160 | 2.61411e+07 | 150496 | 0.608345 | 1.02706 | 1(Win) | true |
| glaze | 1978.1 | 0.281241 | 5833.12ms | 466906 | 30 | 1.20238e+07 | 225103 | 1.00852 | 1.53637 | 2(Loss) | true |
| simdjson (ondemand) | 1100.03 | 0.151611 | 5187.53ms | 466906 | 640 | 2.41041e+08 | 404786 | 0.410754 | 2.76241 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2971.39 | 0.215365 | 7700.32ms | 466906 | 160 | 1.66651e+07 | 149854 | 0.0571062 | 1.02271 | 1(Win) | true |
| glaze | 1956.57 | 0.170807 | 5820.22ms | 466906 | 40 | 6.04421e+06 | 227580 | 0.0424579 | 1.55335 | 2(Loss) | true |
| simdjson (ondemand) | 1092.18 | 0.27506 | 5214.65ms | 466906 | 320 | 4.02416e+08 | 407695 | 0.172319 | 2.78211 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2449.3 | 0.256893 | 7101.01ms | 699405 | 1280 | 6.2645e+08 | 272324 | 1.29585 | 1.24029 | 1(Win) | true |
| glaze | 2149.21 | 0.24259 | 7992.14ms | 699405 | 80 | 4.53458e+07 | 310349 | 0.193359 | 1.41405 | 2(Loss) | true |
| simdjson (ondemand) | 848.351 | 0.523485 | 5385.77ms | 767297 | 80 | 1.63108e+09 | 862558 | 0.530591 | 3.58148 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3866.91 | 0.119919 | 8908.46ms | 699405 | 640 | 2.7383e+07 | 172490 | 0.0693455 | 0.785886 | 1(Win) | true |
| glaze | 2131.68 | 0.567002 | 8043.1ms | 699405 | 1280 | 4.02895e+09 | 312901 | 0.416471 | 1.42566 | 2(Loss) | true |
| simdjson (ondemand) | 842.531 | 0.664214 | 5429.59ms | 767297 | 320 | 1.06493e+10 | 868516 | 0.0720179 | 3.60628 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 2785.14 | 0.268097 | 5602.06ms | 631514 | 160 | 5.37745e+07 | 216240 | 0.0381375 | 1.09119 | 1(Win) | true |
| glaze | 2610.76 | 0.162895 | 5891.37ms | 631514 | 1280 | 1.8074e+08 | 230683 | 0.0369284 | 1.16403 | 2(Loss) | true |
