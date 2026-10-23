# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

Latest Results: (Oct 23, 2026)
#### Using the following commits:
----
| Jsonifier: [b975cd7](https://github.com/nihilai-collective/jsonifier/commit/b975cd7)  
| Glaze: [628bec1](https://github.com/stephenberry/glaze/commit/628bec1)  
| Simdjson: [70f83c9](https://github.com/simdjson/simdjson/commit/70f83c9)  

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
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2180.47 | 0.156226 | 763.751ms | 905 | 640 | 244.727 | 395.82 | 0.126875 | 2.55466 | 12.6785 | 1.84972 | 0.00113432 | 0.000189917 | 3.45304e-06 | 1(Win) | true |
| glaze | 774.203 | 0.114599 | 835.28ms | 905 | 1280 | 2089.1 | 1114.79 | 0.177967 | 6.82844 | 18.6398 | 3.27515 | 0.00275639 | 0.000149344 | 3.45304e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 274.361 | 0.053167 | 1042.6ms | 905 | 160 | 447.566 | 3145.76 | 0.0481037 | 18.6672 | 52.9127 | 7.91713 | 0.00619475 | 0.000110497 | 2.07182e-05 | 3(Loss) | true |
| simdjson (ondemand) | 193.574 | 0.0971976 | 1174.72ms | 905 | 160 | 3004.94 | 4458.64 | 0.00532646 | 26.3499 | 104.06 | 10.9039 | 0.0240815 | 0.000145028 | 2.07182e-05 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2393.35 | 0.0933519 | 761.445ms | 905 | 4890 | 554.164 | 360.613 | 0.0762118 | 2.35944 | 12.1473 | 1.73044 | 0.00112169 | 0.000188681 | 4.24816e-05 | 1(Win) | true |
| glaze | 725.21 | 0.0642521 | 838.078ms | 905 | 320 | 187.108 | 1190.1 | 0.219299 | 7.20923 | 18.2972 | 3.16243 | 0.00111533 | 0.000165746 | 1.38122e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 280.055 | 0.071932 | 1036.09ms | 905 | 1280 | 6290.22 | 3081.81 | 0.238251 | 18.4371 | 52.347 | 7.80442 | 0.00548688 | 0.000239123 | 4.3163e-05 | 3(Loss) | true |
| simdjson (ondemand) | 195.095 | 0.0324709 | 1175.75ms | 905 | 1280 | 2641.21 | 4423.86 | 0.0639233 | 26.1431 | 103.519 | 10.7934 | 0.0238916 | 0.000245166 | 4.05732e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2052.2 | 0.163409 | 769.203ms | 905 | 2560 | 1209.06 | 420.56 | 0.490958 | 2.69165 | 10.0729 | 0.743646 | 0.00336067 | 0.000107044 | 5.61119e-06 | 1(Win) | true |
| simdjson (reflection) | 247.415 | 0.0444167 | 1079.67ms | 905 | 2560 | 6145.81 | 3488.37 | 0.0199619 | 20.6457 | 94.8387 | 20.9083 | 0.0475717 | 0.000230922 | 7.8125e-05 | 2(Loss) | true |
| glaze | 205.343 | 0.0431566 | 1154.6ms | 905 | 2560 | 8423.09 | 4203.09 | 0.0604459 | 24.7933 | 109.057 | 23.0022 | 0.0891169 | 0.000563277 | 0.000279265 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3276.67 | 0.103478 | 758.567ms | 905 | 4890 | 363.274 | 263.4 | 0.123234 | 1.7802 | 7.77459 | 0.271823 | 0.00222215 | 5.33279e-05 | 1.15243e-05 | 1(Win) | true |
| simdjson (reflection) | 3147.33 | 0.24157 | 761.649ms | 905 | 160 | 70.2132 | 274.225 | 0.146079 | 1.84424 | 8.45304 | 1.05193 | 0.00110497 | 8.28729e-05 | 1.38122e-05 | 2(Loss) | true |
| glaze | 675.294 | 0.0282352 | 867.301ms | 905 | 4890 | 636.798 | 1278.07 | 0.109057 | 7.70669 | 21.8155 | 3.36685 | 0.00114316 | 0.000222802 | 6.21406e-05 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1174.52 | 0.0526685 | 879.053ms | 1811 | 4890 | 2933.09 | 1470.47 | 0.142935 | 4.40949 | 18.995 | 3.75207 | 0.000597011 | 0.00020145 | 7.71247e-05 | 1(Win) | true |
| glaze | 952.008 | 0.081448 | 914.084ms | 1811 | 1280 | 2794.65 | 1814.17 | 0.0278269 | 5.42778 | 26.6455 | 4.12148 | 0.00189942 | 0.000157889 | 4.09822e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 372.673 | 0.0655838 | 1199.01ms | 1811 | 1280 | 11824.5 | 4634.36 | 0.104157 | 13.7105 | 38.1883 | 6.25677 | 0.000638459 | 0.000355035 | 0.000168243 | 3(Loss) | true |
| simdjson (ondemand) | 232.009 | 0.0281674 | 1478.63ms | 1811 | 2560 | 11255.4 | 7444.13 | 0.00892507 | 21.8812 | 85.1971 | 11.3782 | 0.000600281 | 0.000240285 | 8.1533e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1285.87 | 0.423588 | 863.856ms | 1811 | 320 | 10358.1 | 1343.14 | 0.130354 | 4.0366 | 17.9387 | 3.51132 | 0.000974945 | 6.72971e-05 | 1.72557e-05 | 1(Win) | true |
| glaze | 1056.11 | 0.0427573 | 891.428ms | 1811 | 4890 | 2390.83 | 1635.35 | 0.121936 | 4.9179 | 25.7079 | 3.88515 | 0.00109781 | 0.000234649 | 9.60953e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 383.77 | 0.0427834 | 1178.11ms | 1811 | 160 | 593.151 | 4500.36 | 0.00916677 | 13.2998 | 37.1231 | 6.01601 | 0.00111126 | 0.000189812 | 5.86692e-05 | 3(Loss) | true |
| simdjson (ondemand) | 234.531 | 0.0446222 | 1468.9ms | 1811 | 4890 | 52801.7 | 7364.08 | 0.114696 | 21.6056 | 84.1414 | 11.1496 | 0.00092177 | 0.000258362 | 0.000106484 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 346.434 | 0.0592141 | 1280.38ms | 1997 | 2560 | 27127.2 | 5497.4 | 0.171504 | 14.7107 | 64.362 | 11.6965 | 0.00517632 | 0.000198736 | 6.70928e-05 | 1(Win) | true |
| jsonifier | 343.243 | 0.041371 | 1234.59ms | 1811 | 4890 | 21190.1 | 5031.72 | 0.0631845 | 14.8631 | 62.3811 | 10.8366 | 0.0174111 | 0.000189819 | 7.03495e-05 | 2(Loss) | true |
| glaze | 307.411 | 0.0787083 | 1288.74ms | 1798 | 320 | 6167.83 | 5577.9 | 0.10656 | 16.5615 | 70.0968 | 12.3654 | 0.0201387 | 0.000241588 | 7.12597e-05 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 863.509 | 0.112192 | 934.17ms | 1811 | 80 | 402.825 | 2000.1 | 0.100095 | 5.97419 | 19.6963 | 1.03424 | 0.000614301 | 0.000358918 | 0.000207068 | 1(Win) | true |
| glaze | 734.714 | 0.0684531 | 980.575ms | 1798 | 2560 | 6533.84 | 2333.84 | 0.0338378 | 6.98935 | 26.4755 | 2.36263 | 0.00106477 | 0.000354561 | 0.000197702 | 2(Loss) | true |
| simdjson (reflection) | 647.114 | 0.0430599 | 1034.88ms | 1997 | 80 | 128.478 | 2943.05 | 0.0314399 | 7.92238 | 25.2954 | 2.57787 | 0.00333625 | 4.38157e-05 | 2.50376e-05 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3338.15 | 0.0861037 | 839.441ms | 3862 | 2560 | 2310.45 | 1103.33 | 0.0141596 | 1.56482 | 7.28146 | 0.900829 | 0.00026126 | 8.48613e-05 | 2.19486e-05 | 1(Win) | true |
| glaze | 1738.97 | 0.0785021 | 939.158ms | 3862 | 2560 | 7076.94 | 2117.98 | 0.197493 | 2.95519 | 14.5215 | 1.82367 | 0.000266317 | 0.000100235 | 3.86377e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 820.663 | 0.0275041 | 1180.2ms | 3862 | 4890 | 7450.7 | 4487.94 | 0.0126623 | 6.21458 | 15.7848 | 1.93501 | 0.000267829 | 0.000113952 | 4.33673e-05 | 3(Loss) | true |
| simdjson (ondemand) | 537.333 | 0.0882468 | 1412.58ms | 3862 | 320 | 11708.1 | 6854.4 | 0.105432 | 9.46004 | 31.5552 | 3.40394 | 0.00595789 | 0.000104382 | 5.74508e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3706.41 | 0.0535487 | 823.672ms | 3862 | 320 | 90.6081 | 993.709 | 0.0568882 | 1.42161 | 6.78975 | 0.790005 | 0.000258933 | 4.61225e-05 | 1.13283e-05 | 1(Win) | true |
| glaze | 1858.21 | 0.0847987 | 922.577ms | 3862 | 2560 | 7231.92 | 1982.06 | 0.379412 | 2.78787 | 14.1336 | 1.71129 | 0.00033459 | 0.000104382 | 4.11663e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 841.879 | 0.0758545 | 1167.81ms | 3862 | 320 | 3524.02 | 4374.85 | 0.143281 | 6.05963 | 15.3045 | 1.82807 | 0.000264597 | 5.25958e-05 | 1.69925e-05 | 3(Loss) | true |
| simdjson (ondemand) | 537.939 | 0.0681165 | 1409.45ms | 3862 | 30 | 652.506 | 6846.67 | 0.150665 | 9.45817 | 31.0642 | 3.297 | 0.00802693 | 0.00015536 | 2.58933e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 961.617 | 0.0863774 | 1119.1ms | 3862 | 640 | 7004.87 | 3830.1 | 0.0651484 | 5.35171 | 25.4474 | 5.21854 | 0.00709598 | 0.000100741 | 4.89546e-05 | 1(Win) | true |
| simdjson (reflection) | 950.479 | 0.0473963 | 1116.79ms | 3862 | 1280 | 4317.56 | 3874.98 | 0.10107 | 5.39283 | 26.739 | 5.25479 | 0.00958842 | 8.27372e-05 | 2.32635e-05 | 2(Loss) | true |
| glaze | 830.495 | 0.0534885 | 1176.99ms | 3862 | 640 | 3601.24 | 4434.81 | 0.0227302 | 6.14304 | 29.0533 | 5.85811 | 0.00935275 | 0.000156574 | 6.71608e-05 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5476.41 | 0.0985428 | 815.082ms | 3862 | 160 | 70.2753 | 672.538 | 0.0408732 | 0.980569 | 5.19239 | 0.592439 | 0.000276735 | 3.72216e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 4224.89 | 0.0710657 | 819.786ms | 3862 | 2560 | 982.546 | 871.759 | 0.329711 | 1.26817 | 6.48887 | 0.533662 | 0.000292109 | 4.30881e-05 | 1.05192e-05 | 2(Loss) | true |
| glaze | 2479.2 | 0.0466966 | 908.897ms | 3862 | 4890 | 2353.32 | 1485.6 | 0.0689169 | 2.10628 | 8.6709 | 1.15122 | 0.00541488 | 0.000128196 | 5.87762e-05 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1759.06 | 0.0641951 | 1254.28ms | 9578 | 160 | 1777.93 | 5192.72 | 0.0345316 | 2.89777 | 14.3134 | 2.71267 | 0.0014147 | 3.65421e-05 | 1.89236e-05 | 1(Win) | true |
| glaze | 1439.88 | 0.0283634 | 1374.52ms | 9578 | 4890 | 15831.5 | 6343.79 | 0.193842 | 3.55182 | 17.7295 | 3.50992 | 0.00110909 | 4.947e-05 | 2.81832e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1034.79 | 0.0610947 | 1624.76ms | 9578 | 2560 | 74454.2 | 8827.16 | 0.0653184 | 4.88578 | 19.0914 | 2.95834 | 0.00435931 | 4.89811e-05 | 1.85565e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1015.41 | 0.0581045 | 1656.91ms | 9578 | 2560 | 69940 | 8995.67 | 0.429755 | 4.9934 | 18.8837 | 3.25924 | 0.00102383 | 8.49522e-05 | 4.81654e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2705.9 | 0.0640193 | 1213.33ms | 9578 | 160 | 747.255 | 3375.7 | 0.0414901 | 1.89424 | 10.297 | 1.82115 | 0.000120067 | 3.19743e-05 | 1.43558e-05 | 1(Win) | true |
| glaze | 1942.32 | 0.043466 | 1342.03ms | 9578 | 2560 | 10696.6 | 4702.76 | 0.0448824 | 2.63518 | 13.5506 | 2.55575 | 0.000670971 | 4.84101e-05 | 2.40215e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1287.1 | 0.157454 | 1582.64ms | 9578 | 640 | 79912.3 | 7096.81 | 0.0912869 | 3.9242 | 15.1231 | 2.07517 | 0.00315159 | 6.83533e-05 | 3.11586e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1267.8 | 0.0993019 | 1597.96ms | 9578 | 320 | 16380.1 | 7204.86 | 0.0248158 | 4.00877 | 14.913 | 2.38985 | 0.000277655 | 3.13218e-05 | 1.07669e-05 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3999.86 | 0.113148 | 985.955ms | 9578 | 320 | 2136.5 | 2283.65 | 0.000410528 | 1.28586 | 5.19942 | 1.00762 | 0.00194652 | 4.33937e-05 | 8.48298e-06 | 1(Win) | true |
| simdjson (reflection) | 3712.33 | 0.0800933 | 977.803ms | 9578 | 160 | 621.396 | 2460.53 | 0.247807 | 1.38425 | 6.03383 | 1.12174 | 0.000403268 | 2.61015e-05 | 1.30507e-06 | 2(Loss) | true |
| glaze | 2032.74 | 0.0740492 | 1182.7ms | 9578 | 4890 | 54141.9 | 4493.58 | 0.0522659 | 2.52 | 12.6679 | 2.59762 | 0.000917641 | 9.45418e-05 | 6.77251e-05 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11414.3 | 0.114811 | 834.844ms | 9578 | 1280 | 1080.5 | 800.247 | 0.0504005 | 0.46457 | 2.21476 | 0.253706 | 0.000602944 | 8.27906e-05 | 5.64445e-05 | 1(Win) | true |
| simdjson (reflection) | 8784.64 | 0.220896 | 860.966ms | 9578 | 320 | 1688.22 | 1039.8 | 0.0815121 | 0.599536 | 3.02422 | 0.331489 | 0.000116804 | 2.28388e-05 | 4.56776e-06 | 2(Loss) | true |
| glaze | 6167.45 | 0.0621817 | 905.566ms | 9578 | 2560 | 2171.22 | 1481.05 | 0.150611 | 0.844487 | 4.38046 | 0.677699 | 0.000159056 | 4.16808e-05 | 2.42254e-05 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3419.75 | 0.0790216 | 833.766ms | 3873 | 2560 | 1864.83 | 1080.07 | 0.0418622 | 1.53852 | 7.02685 | 0.830365 | 0.000276554 | 0.000146245 | 5.91031e-05 | 1(Win) | true |
| glaze | 1909.19 | 0.0466408 | 917.055ms | 3873 | 2560 | 2084.34 | 1934.63 | 0.139858 | 2.70122 | 12.8079 | 1.7906 | 0.000271108 | 7.53413e-05 | 2.86438e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 840.402 | 0.0527942 | 1164.92ms | 3873 | 1280 | 6891.34 | 4395.02 | 0.0178793 | 6.0862 | 15.5025 | 1.86316 | 0.000781653 | 0.00011861 | 4.80086e-05 | 3(Loss) | true |
| simdjson (ondemand) | 535.817 | 0.0418218 | 1420.88ms | 3873 | 1280 | 10638.4 | 6893.36 | 0.0304961 | 9.49207 | 31.1567 | 3.50865 | 0.010459 | 9.35967e-05 | 3.36867e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3787.74 | 0.0277494 | 819.36ms | 3873 | 1280 | 93.7243 | 975.141 | 0.102844 | 1.39231 | 6.58663 | 0.731474 | 0.000673533 | 4.76052e-05 | 6.05151e-06 | 1(Win) | true |
| glaze | 2013.94 | 0.0504653 | 906.446ms | 3873 | 1280 | 1096.47 | 1834 | 0.00264101 | 2.56637 | 12.4735 | 1.69171 | 0.000425825 | 0.000116391 | 4.47812e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 865.096 | 0.0321331 | 1152.39ms | 3873 | 80 | 150.578 | 4269.56 | 0.0792778 | 5.90298 | 15.0596 | 1.76427 | 0.000774593 | 9.68242e-05 | 3.87297e-05 | 3(Loss) | true |
| simdjson (ondemand) | 541.071 | 0.0248473 | 1420.28ms | 3873 | 2560 | 7365.2 | 6826.42 | 0.0356998 | 9.40588 | 30.7033 | 3.40976 | 0.0134186 | 9.67233e-05 | 3.71159e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 968.159 | 0.0669883 | 1132.9ms | 3873 | 640 | 4180.03 | 3815.05 | 0.210439 | 5.3736 | 24.4178 | 5.0661 | 0.00644324 | 0.00012103 | 3.83262e-05 | 1(Win) | true |
| simdjson (reflection) | 917.949 | 0.0681394 | 1148.88ms | 3873 | 640 | 4810.99 | 4023.73 | 0.00244636 | 5.55923 | 26.9713 | 5.2835 | 0.0102416 | 8.14937e-05 | 1.53305e-05 | 2(Loss) | true |
| glaze | 878.126 | 0.069603 | 1174.99ms | 3873 | 320 | 2742.76 | 4206.21 | 0.0158223 | 5.81312 | 28.3979 | 5.74929 | 0.00653725 | 4.35709e-05 | 1.61374e-06 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6316.32 | 0.111731 | 824.539ms | 3873 | 4890 | 2087.48 | 584.767 | 0.32811 | 0.855606 | 3.98483 | 0.476388 | 0.000262791 | 6.13022e-05 | 2.00116e-05 | 1(Win) | true |
| simdjson (reflection) | 4302.15 | 0.0453216 | 838.868ms | 3873 | 160 | 24.2245 | 858.544 | 0.111257 | 1.20843 | 6.42319 | 0.530338 | 0.000258198 | 5.80945e-05 | 3.22747e-06 | 2(Loss) | true |
| glaze | 2558.29 | 0.104174 | 920.919ms | 3873 | 320 | 723.882 | 1443.77 | 0.00844214 | 2.03417 | 7.7875 | 0.993029 | 0.00409163 | 5.40602e-05 | 1.12962e-05 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 910.637 | 0.122431 | 6864.74ms | 2090234 | 30 | 2.15478e+08 | 2.18902e+06 | 0.0731502 | 5.54221 | 24.6356 | 5.13415 | 0.033618 | 0.0682436 | 0.000300317 | 1(Win) | true |
| jsonifier (two-stage) | 904.594 | 0.162506 | 6844.94ms | 2090234 | 160 | 2.05183e+09 | 2.20364e+06 | 0.361338 | 5.49471 | 27.1811 | 5.44632 | 0.021299 | 0.107273 | 0.000791538 | 2(Loss) | true |
| simdjson (reflection) | 868.049 | 0.149641 | 7149.54ms | 2090234 | 160 | 1.88939e+09 | 2.29642e+06 | 0.451795 | 5.76774 | 28.0691 | 5.14317 | 0.0190793 | 0.108035 | 0.0010718 | 3(Loss) | true |
| simdjson (ondemand) | 771.583 | 0.202289 | 8045.16ms | 2090234 | 40 | 1.09252e+09 | 2.58352e+06 | 0.410446 | 6.48652 | 30.0676 | 5.6097 | 0.0256033 | 0.114322 | 0.00225677 | 4(Loss) | true |
| glaze | 730.713 | 0.113895 | 8545.57ms | 2090234 | 30 | 2.8962e+08 | 2.72802e+06 | 0.12905 | 6.92266 | 30.6084 | 6.01958 | 0.028731 | 0.066889 | 0.00254193 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1105.6 | 0.173917 | 6839.48ms | 2090234 | 80 | 7.86625e+08 | 1.80301e+06 | 0.0283571 | 4.54649 | 21.9374 | 4.19654 | 0.020638 | 0.0816931 | 0.000765859 | 1(Win) | true |
| jsonifier | 1087.04 | 0.106768 | 6876.24ms | 2090234 | 40 | 1.53333e+08 | 1.83379e+06 | 0.135265 | 4.61467 | 19.341 | 3.86914 | 0.0331217 | 0.0434943 | 0.00219052 | 2(Loss) | true |
| simdjson (reflection) | 1031.49 | 0.419751 | 7149.77ms | 2090234 | 80 | 5.26422e+09 | 1.93255e+06 | 0.236426 | 4.8501 | 22.8273 | 3.89151 | 0.0178297 | 0.0804937 | 0.000676001 | 3(Loss) | true |
| simdjson (ondemand) | 933.1 | 0.0922528 | 7876.73ms | 2090234 | 160 | 6.21459e+08 | 2.13632e+06 | 0.114688 | 5.40186 | 24.7797 | 4.35333 | 0.0220764 | 0.0802632 | 0.001631 | 4(Loss) | true |
| glaze | 838.144 | 0.091971 | 8664.12ms | 2090234 | 30 | 1.43541e+08 | 2.37835e+06 | 0.094002 | 6.01724 | 25.2686 | 4.74995 | 0.027815 | 0.041478 | 0.00135465 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2101.02 | 0.830143 | 6012.81ms | 2090234 | 30 | 1.86104e+09 | 948777 | 0.597155 | 2.39933 | 7.74538 | 0.373395 | 0.00035811 | 0.0511033 | 0.000273319 | 1(Win) | true |
| glaze | 1431.25 | 0.156378 | 8903.37ms | 2090234 | 160 | 7.5898e+08 | 1.39277e+06 | 0.312962 | 3.48538 | 9.69968 | 0.651381 | 0.0117122 | 0.0693796 | 0.000625065 | 2(Loss) | true |
| simdjson (reflection) | 1023.48 | 0.168274 | 6103.89ms | 2090326 | 80 | 8.59403e+08 | 1.94776e+06 | 0.128291 | 4.89895 | 15.3147 | 1.4617 | 0.0160174 | 0.0509677 | 0.000288478 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2122.43 | 0.0646371 | 6014.41ms | 2090234 | 80 | 2.94832e+07 | 939206 | 0.3001 | 2.37341 | 7.74512 | 0.373337 | 0.000344214 | 0.0509103 | 0.000228455 | 1(Win) | true |
| glaze | 1508.92 | 0.13699 | 8405.73ms | 2090234 | 320 | 1.04807e+09 | 1.32108e+06 | 0.147544 | 3.33654 | 9.69575 | 0.650458 | 0.0117218 | 0.0434536 | 0.000350693 | 2(Loss) | true |
| simdjson (reflection) | 1030.53 | 0.060497 | 6062.18ms | 2090326 | 40 | 5.47821e+07 | 1.93444e+06 | 0.28839 | 4.89639 | 15.3145 | 1.46167 | 0.0160266 | 0.0507529 | 0.00286033 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2635.78 | 0.156086 | 7532.38ms | 6661897 | 40 | 5.66194e+08 | 2.4104e+06 | 0.0736024 | 1.88228 | 9.38498 | 1.74108 | 0.00558161 | 0.0565022 | 0.00275149 | 1(Win) | true |
| simdjson (reflection) | 2502.13 | 0.227188 | 7881.25ms | 6661897 | 80 | 2.66217e+09 | 2.53915e+06 | 0.297671 | 1.99319 | 9.72606 | 1.65334 | 0.00523563 | 0.0565058 | 0.00447711 | 2(Loss) | true |
| jsonifier | 2389.28 | 0.0752836 | 8296.54ms | 6661897 | 40 | 1.60296e+08 | 2.65908e+06 | 0.0629759 | 2.07632 | 9.69575 | 2.1231 | 0.00996163 | 0.0341481 | 0.00456876 | 3(Loss) | true |
| simdjson (ondemand) | 2272.68 | 0.133033 | 8703.21ms | 6661897 | 40 | 5.53219e+08 | 2.7955e+06 | 0.0700699 | 2.19381 | 10.3508 | 1.79927 | 0.00727014 | 0.0581884 | 0.0010624 | 4(Loss) | true |
| glaze | 1844.9 | 0.150884 | 5165.03ms | 6661897 | 30 | 8.0995e+08 | 3.44369e+06 | 0.257504 | 2.70413 | 13.2515 | 2.49511 | 0.0088213 | 0.035623 | 0.00247388 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3116.95 | 0.106544 | 7460.46ms | 6661897 | 160 | 7.5459e+08 | 2.0383e+06 | 0.160133 | 1.58736 | 7.74463 | 1.35002 | 0.00532801 | 0.0483518 | 0.00185363 | 1(Win) | true |
| simdjson (reflection) | 2986.07 | 0.179468 | 7779.63ms | 6661897 | 80 | 1.16643e+09 | 2.12764e+06 | 0.253047 | 1.67863 | 8.08192 | 1.26093 | 0.00483193 | 0.0476297 | 0.00272536 | 2(Loss) | true |
| jsonifier | 2799.89 | 0.145333 | 8195.94ms | 6661897 | 30 | 3.26259e+08 | 2.26911e+06 | 0.054372 | 1.78381 | 8.05692 | 1.73231 | 0.00975433 | 0.025944 | 0.00182381 | 3(Loss) | true |
| simdjson (ondemand) | 2678.24 | 0.315076 | 8598.13ms | 6661897 | 40 | 2.23453e+09 | 2.37218e+06 | 0.000357264 | 1.86796 | 8.69433 | 1.4058 | 0.0061539 | 0.0471406 | 0.000579917 | 4(Loss) | true |
| glaze | 2073.09 | 0.0955382 | 5224.79ms | 6661897 | 40 | 3.42906e+08 | 3.06465e+06 | 0.0212078 | 2.39663 | 11.6032 | 2.10392 | 0.0084573 | 0.0268993 | 0.00231163 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6118.23 | 0.13121 | 6598.75ms | 6661897 | 160 | 2.97028e+08 | 1.03842e+06 | 0.0976386 | 0.815306 | 2.48889 | 0.117149 | 9.8144e-05 | 0.0278402 | 0.000879779 | 1(Win) | true |
| glaze | 3146.35 | 0.210554 | 6301.99ms | 6661897 | 160 | 2.89221e+09 | 2.01926e+06 | 0.263689 | 1.57741 | 4.40918 | 0.355587 | 0.00381386 | 0.0633491 | 0.00421638 | 2(Loss) | true |
| simdjson (reflection) | 375.257 | 0.356192 | 5097.46ms | 6661989 | 30 | 1.09104e+11 | 1.69307e+07 | 0.537172 | 13.2483 | 41.6556 | 5.70062 | 0.0238257 | 0.254585 | 0.112521 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6162.54 | 0.224445 | 6561.05ms | 6661897 | 40 | 2.14169e+08 | 1.03095e+06 | 0.144772 | 0.814716 | 2.48884 | 0.117138 | 9.99978e-05 | 0.0278177 | 7.46972e-05 | 1(Win) | true |
| glaze | 3756.72 | 0.194504 | 5238.87ms | 6661897 | 160 | 1.73123e+09 | 1.69118e+06 | 0.117242 | 1.3269 | 4.40771 | 0.355242 | 0.00382189 | 0.0246485 | 0.000132486 | 2(Loss) | true |
| simdjson (reflection) | 380.678 | 0.347481 | 5077.43ms | 6661989 | 30 | 1.00897e+11 | 1.66896e+07 | 1.57066 | 13.0557 | 41.6573 | 5.7019 | 0.0238509 | 0.255498 | 0.108697 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2441.93 | 0.0512105 | 5183.29ms | 500299 | 640 | 6.40754e+06 | 195387 | 0.102749 | 2.04493 | 8.91663 | 1.68061 | 0.0115795 | 0.00585977 | 8.93434e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1846.87 | 0.0700018 | 6778.94ms | 500299 | 1280 | 4.18614e+07 | 258341 | 0.517983 | 2.70025 | 11.847 | 2.04919 | 0.012882 | 0.0337704 | 0.00025109 | 2(Loss) | true |
| glaze | 1816.94 | 0.0924538 | 6950.99ms | 500299 | 160 | 9.43084e+06 | 262597 | 0.0118208 | 2.75956 | 11.5495 | 2.25867 | 0.0137076 | 0.00359561 | 0.000132308 | 3(Loss) | true |
| simdjson (reflection) | 1416.66 | 0.320035 | 8800.76ms | 500299 | 40 | 4.64715e+07 | 336795 | 0.155454 | 3.549 | 14.6226 | 2.32258 | 0.0180855 | 0.0281535 | 0.000140866 | 4(Loss) | true |
| simdjson (ondemand) | 1365.35 | 0.0428434 | 9110.86ms | 500299 | 1280 | 2.86912e+07 | 349450 | 0.192618 | 3.67135 | 14.1875 | 2.32528 | 0.0168656 | 0.0388593 | 0.000319721 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3052.45 | 0.0643484 | 5017.8ms | 500299 | 640 | 6.47469e+06 | 156308 | 0.0454778 | 1.64653 | 7.7971 | 1.40966 | 0.00865151 | 0.00341805 | 4.4183e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2226.66 | 0.110931 | 6565.67ms | 500299 | 320 | 1.80804e+07 | 214277 | 0.203685 | 2.25632 | 10.7308 | 1.77967 | 0.00912635 | 0.0234526 | 3.67343e-05 | 2(Loss) | true |
| glaze | 2158.78 | 0.096625 | 6742.87ms | 500299 | 160 | 7.29697e+06 | 221015 | 0.0459402 | 2.30893 | 10.4361 | 1.99034 | 0.0093291 | 0.00161822 | 2.6784e-05 | 3(Loss) | true |
| simdjson (reflection) | 1664.93 | 0.14143 | 8311.07ms | 500299 | 320 | 5.25658e+07 | 286572 | 0.0862809 | 3.00665 | 13.5169 | 2.05207 | 0.0115392 | 0.0166393 | 5.15504e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1659.35 | 0.0588672 | 8394.44ms | 500299 | 320 | 9.16812e+06 | 287536 | 0.103734 | 3.03412 | 13.0462 | 2.04525 | 0.00810963 | 0.0211397 | 6.96271e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12860.6 | 0.0355847 | 4496.17ms | 500299 | 640 | 111544 | 37099.7 | 0.00689396 | 0.39336 | 1.75419 | 0.30134 | 0.0014009 | 0.00152164 | 7.20819e-06 | 1(Win) | true |
| simdjson (reflection) | 11254.3 | 0.0865059 | 5035.97ms | 500299 | 160 | 215197 | 42394.8 | 0.0222413 | 0.448957 | 2.16987 | 0.197422 | 0.00120388 | 0.000384932 | 5.24686e-06 | 2(Loss) | true |
| glaze | 6146.24 | 0.176329 | 8576.76ms | 500299 | 640 | 1.19913e+07 | 77628.3 | 0.222853 | 0.814373 | 3.61223 | 0.52608 | 0.00135547 | 0.0183867 | 3.20402e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12673.6 | 0.184204 | 4504.23ms | 500299 | 1280 | 6.15559e+06 | 37647 | 0.0107069 | 0.394981 | 1.75311 | 0.301094 | 0.00138273 | 0.00131649 | 1.26815e-05 | 1(Win) | true |
| simdjson (reflection) | 11112.2 | 0.0353942 | 5048.27ms | 500299 | 2560 | 591236 | 42936.7 | 0.0749939 | 0.451912 | 2.16878 | 0.197174 | 0.00121686 | 7.03001e-05 | 1.52994e-05 | 2(Loss) | true |
| glaze | 7279.66 | 0.0424951 | 7338.95ms | 500299 | 1280 | 992942 | 65541.8 | 0.119702 | 0.692143 | 3.59893 | 0.523033 | 0.0013399 | 0.00248767 | 1.49707e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4331.59 | 0.189419 | 8354.89ms | 1439562 | 320 | 1.15336e+08 | 316945 | 0.154566 | 1.16354 | 5.0018 | 0.745126 | 0.00474105 | 0.0569534 | 8.11749e-05 | 1(Win) | true |
| jsonifier | 3879.78 | 0.156193 | 9274.75ms | 1439562 | 160 | 4.88754e+07 | 353853 | 0.0748451 | 1.30139 | 5.34963 | 1.17088 | 0.00435429 | 0.0212125 | 2.24026e-05 | 2(Loss) | true |
| simdjson (reflection) | 3520.48 | 0.0472627 | 5069.9ms | 1439562 | 640 | 2.17407e+07 | 389967 | 0.358647 | 1.43264 | 6.02432 | 0.848813 | 0.00609321 | 0.0470202 | 0.000125978 | 3(Loss) | true |
| simdjson (ondemand) | 3368.21 | 0.182449 | 5277.49ms | 1439562 | 160 | 8.8484e+07 | 407598 | 0.465676 | 1.49989 | 5.87601 | 0.850832 | 0.00599274 | 0.0513832 | 3.8497e-05 | 4(Loss) | true |
| glaze | 2946.89 | 0.0452388 | 6031.32ms | 1439562 | 320 | 1.42136e+07 | 465871 | 0.063798 | 1.71215 | 7.70569 | 1.43157 | 0.00639358 | 0.0173918 | 3.39057e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 5004.56 | 0.252186 | 8183.05ms | 1439562 | 160 | 7.65759e+07 | 274324 | 0.20738 | 1.00713 | 4.61305 | 0.651312 | 0.00354759 | 0.0497553 | 5.37881e-05 | 1(Win) | true |
| jsonifier | 4355.7 | 0.164447 | 9105.1ms | 1439562 | 320 | 8.59703e+07 | 315190 | 0.216037 | 1.15314 | 4.96176 | 1.07705 | 0.00331938 | 0.014886 | 6.21174e-05 | 2(Loss) | true |
| simdjson (reflection) | 4059.23 | 0.0678911 | 9720.12ms | 1439562 | 640 | 3.37426e+07 | 338210 | 0.0965856 | 1.24464 | 5.63638 | 0.754258 | 0.00408604 | 0.038328 | 2.7427e-05 | 3(Loss) | true |
| simdjson (ondemand) | 4001.79 | 0.0687037 | 9762.38ms | 1439562 | 320 | 1.77772e+07 | 343065 | 0.164679 | 1.25943 | 5.47336 | 0.751891 | 0.00307458 | 0.0390848 | 6.78158e-06 | 4(Loss) | true |
| glaze | 3268.49 | 0.121197 | 5968.72ms | 1439562 | 30 | 7.77454e+06 | 420033 | 0.20443 | 1.55153 | 7.32129 | 1.33895 | 0.00487269 | 0.0122351 | 1.29669e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20647 | 0.0889348 | 7556.82ms | 1439562 | 40 | 139879 | 66492.8 | 0.00845885 | 0.2448 | 0.688432 | 0.10486 | 0.000651083 | 0.0161194 | 5.93931e-06 | 1(Win) | true |
| glaze | 5837.08 | 0.14042 | 6221.12ms | 1439584 | 1280 | 1.39621e+08 | 235202 | 0.0577662 | 0.861642 | 2.99202 | 0.365951 | 0.00066096 | 0.060198 | 8.57507e-06 | 2(Loss) | true |
| simdjson (reflection) | 549.783 | 0.782855 | 7800.51ms | 1439562 | 80 | 3.05725e+10 | 2.49712e+06 | 0.731639 | 9.13504 | 35.3838 | 6.30335 | 0.0142491 | 0.307469 | 0.00500835 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20596.4 | 0.0201952 | 7503.44ms | 1439562 | 2560 | 463887 | 66655.9 | 0.0625863 | 0.244871 | 0.688196 | 0.10481 | 0.000620915 | 0.0159821 | 3.31562e-06 | 1(Win) | true |
| glaze | 7999.32 | 0.242749 | 9247.28ms | 1439584 | 640 | 1.11087e+08 | 171626 | 0.303704 | 0.630826 | 2.98646 | 0.364671 | 0.000651553 | 0.0163121 | 1.41621e-05 | 2(Loss) | true |
| simdjson (reflection) | 553.36 | 1.4396 | 7881.66ms | 1439562 | 30 | 3.82695e+10 | 2.48098e+06 | 0.297329 | 9.0874 | 35.384 | 6.30338 | 0.0142878 | 0.307278 | 0.00447923 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2355.81 | 0.0580981 | 3020.84ms | 56369 | 80 | 14061 | 22819.2 | 0.0325825 | 2.15057 | 9.28696 | 1.78935 | 0.00175229 | 4.76769e-05 | 3.52587e-05 | 1(Win) | true |
| glaze | 1902.79 | 0.0303559 | 3581.24ms | 56369 | 4890 | 359663 | 28252.1 | 0.0149781 | 2.65405 | 11.1678 | 2.23191 | 0.00720515 | 4.74887e-05 | 3.34852e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1852.73 | 0.0181033 | 3652.69ms | 56369 | 2560 | 70633.8 | 29015.4 | 0.0981205 | 2.73078 | 11.9622 | 2.074 | 0.00423174 | 6.70803e-05 | 4.01234e-05 | 3(Loss) | true |
| simdjson (reflection) | 1542.38 | 0.0581919 | 4224.6ms | 56369 | 30 | 12340.9 | 34853.8 | 0.0340586 | 3.28234 | 13.6759 | 2.33301 | 0.00578864 | 2.54277e-05 | 1.12355e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1446.8 | 0.0229773 | 4464.83ms | 56369 | 2560 | 186597 | 37156.3 | 0.0928079 | 3.49618 | 14.1772 | 2.61899 | 0.00850699 | 0.000107426 | 7.81472e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3204.99 | 0.0433042 | 2766.82ms | 56369 | 2560 | 135060 | 16773.1 | 0.278094 | 1.56738 | 7.31361 | 1.35848 | 0.00194922 | 8.73846e-06 | 3.31937e-06 | 1(Win) | true |
| glaze | 2943.41 | 0.0357526 | 2923.79ms | 56369 | 2560 | 109153 | 18263.7 | 0.161043 | 1.72056 | 8.93367 | 1.74674 | 0.00149454 | 1.67354e-05 | 9.7017e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2448.24 | 0.0367392 | 3298.88ms | 56369 | 1280 | 83299.1 | 21957.7 | 0.0263648 | 2.06834 | 9.99064 | 1.6434 | 0.002496 | 1.2432e-05 | 5.9319e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1814.59 | 0.0145304 | 4103.99ms | 56369 | 4890 | 90612 | 29625.3 | 0.0291374 | 2.78896 | 12.0106 | 2.15879 | 0.00825894 | 2.68208e-05 | 1.55889e-05 | 4(Loss) | true |
| simdjson (reflection) | 1795.05 | 0.0171532 | 4102.47ms | 56369 | 2560 | 67555 | 29947.7 | 0.00757384 | 2.82072 | 12.1349 | 1.98376 | 0.00422395 | 1.33953e-05 | 6.63873e-06 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15362.4 | 0.0330797 | 1098.14ms | 56369 | 2560 | 3430.24 | 3499.3 | 0.0836856 | 0.333172 | 1.3523 | 0.224113 | 0.000175372 | 6.59715e-06 | 2.70262e-06 | 1(Win) | true |
| simdjson (reflection) | 11365.4 | 0.0582474 | 1220.62ms | 56369 | 2560 | 19431.3 | 4729.93 | 0.0399143 | 0.447135 | 1.85554 | 0.281981 | 0.000132629 | 1.63404e-05 | 7.98311e-06 | 2(Loss) | true |
| glaze | 6254.76 | 0.09509 | 1615.46ms | 56369 | 1280 | 85494.7 | 8594.68 | 0.0333307 | 0.809831 | 3.29043 | 0.477195 | 7.88471e-05 | 1.03947e-05 | 4.47664e-06 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15652.9 | 0.0735823 | 1093.44ms | 56369 | 80 | 510.889 | 3434.35 | 0.270786 | 0.327089 | 1.34283 | 0.221966 | 0.000176959 | 1.90708e-05 | 1.17529e-05 | 1(Win) | true |
| simdjson (reflection) | 11542.8 | 0.0868954 | 1212.4ms | 56369 | 80 | 1310.22 | 4657.25 | 0.00805131 | 0.442363 | 1.84555 | 0.279675 | 0.000159219 | 4.65681e-06 | 1.55227e-06 | 2(Loss) | true |
| glaze | 6880.94 | 0.109807 | 1529.86ms | 56369 | 2560 | 188403 | 7812.54 | 0.227917 | 0.736148 | 3.21134 | 0.459384 | 6.16127e-05 | 1.26191e-05 | 5.86953e-06 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2845.34 | 0.0381228 | 3916.3ms | 94370 | 4890 | 711016 | 31630.1 | 0.11463 | 1.76768 | 7.72535 | 1.25401 | 0.00291454 | 2.12994e-05 | 1.21525e-05 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2462.23 | 0.0365548 | 4394.77ms | 94370 | 640 | 114256 | 36551.6 | 0.0192958 | 2.05424 | 8.76263 | 1.42088 | 0.00287177 | 3.06308e-05 | 2.00673e-05 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 2461.93 | 0.0210349 | 4455.12ms | 94370 | 1280 | 75684.9 | 36556 | 0.0426283 | 2.05398 | 7.74472 | 1.70323 | 0.00490456 | 1.19957e-05 | 6.60631e-06 | 2(Tie) | true |
| glaze | 2403.97 | 0.0514668 | 4492.38ms | 94370 | 640 | 237599 | 37437.4 | 0.00334297 | 2.10469 | 9.01254 | 1.864 | 0.00552745 | 9.27201e-06 | 5.14928e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2250.61 | 0.046634 | 4745.86ms | 94370 | 640 | 222563 | 39988.4 | 0.0452037 | 2.2499 | 9.05084 | 1.58866 | 0.00584564 | 8.35309e-05 | 6.00197e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3653.47 | 0.0423134 | 3571.14ms | 94370 | 4890 | 531280 | 24633.7 | 0.0790861 | 1.3711 | 6.54466 | 0.996274 | 0.00155665 | 5.7967e-06 | 2.09765e-06 | 1(Win) | true |
| glaze | 3199.95 | 0.043996 | 3895.27ms | 94370 | 640 | 97991.4 | 28124.9 | 0.117266 | 1.57486 | 7.68312 | 1.57568 | 0.0033159 | 4.07306e-06 | 1.17556e-06 | 2(Loss) | true |
| jsonifier | 3115.91 | 0.00988723 | 3999.19ms | 94370 | 4890 | 39880.1 | 28883.4 | 0.143215 | 1.62464 | 6.56382 | 1.44561 | 0.00296032 | 8.90417e-06 | 3.99377e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2925.25 | 0.0328485 | 4189.15ms | 94370 | 1280 | 130732 | 30766 | 0.00204928 | 1.72521 | 7.74516 | 1.31241 | 0.00325516 | 8.85809e-06 | 4.75191e-06 | 4(Loss) | true |
| simdjson (reflection) | 2815.36 | 0.0139295 | 4311.9ms | 94370 | 4890 | 96957.5 | 31966.8 | 0.107241 | 1.79823 | 7.8214 | 1.20623 | 0.00223776 | 3.4661e-05 | 2.63398e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20391.7 | 0.0858141 | 1181.06ms | 94370 | 30 | 430.326 | 4413.47 | 0.0520861 | 0.250542 | 0.847738 | 0.134004 | 0.000140935 | 1.30691e-05 | 6.00473e-06 | 1(Win) | true |
| glaze | 6190.64 | 0.0645863 | 2211.45ms | 94370 | 1280 | 112846 | 14537.8 | 0.0128528 | 0.8174 | 3.47845 | 0.472841 | 0.000269427 | 5.9937e-06 | 2.81472e-06 | 2(Loss) | true |
| simdjson (reflection) | 518.92 | 0.161765 | 9281.59ms | 94370 | 1280 | 1.0075e+08 | 173434 | 0.19687 | 9.6985 | 37.8093 | 7.33863 | 0.0254101 | 0.0262843 | 0.00020261 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20584 | 0.120843 | 1180.87ms | 94370 | 160 | 4466.53 | 4372.24 | 0.354818 | 0.247896 | 0.842047 | 0.132733 | 0.000106165 | 1.0133e-05 | 4.83469e-06 | 1(Win) | true |
| glaze | 7261.83 | 0.06107 | 1991.91ms | 94370 | 1280 | 73323.3 | 12393.3 | 0.0448779 | 0.700732 | 3.42499 | 0.460666 | 0.00023459 | 1.88917e-05 | 1.34775e-05 | 2(Loss) | true |
| simdjson (reflection) | 515.772 | 0.178864 | 9355.46ms | 94370 | 1280 | 1.24683e+08 | 174492 | 0.0379041 | 9.7792 | 37.8163 | 7.34045 | 0.025728 | 0.0263141 | 9.53113e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2679.38 | 0.0842914 | 1160.83ms | 11812 | 40 | 502.346 | 4204.25 | 0.184788 | 1.90538 | 9.37779 | 1.5938 | 0.000406366 | 6.77277e-05 | 1.69319e-05 | 1(Win) | true |
| glaze | 1990.45 | 0.0266047 | 1303.87ms | 11812 | 4890 | 11085.9 | 5659.42 | 0.107724 | 2.56187 | 12.841 | 2.45276 | 0.0012294 | 6.41786e-05 | 1.9373e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1944.34 | 0.0759166 | 1323.39ms | 11812 | 640 | 12381.1 | 5793.65 | 0.0200341 | 2.63516 | 12.7488 | 2.04876 | 0.00390519 | 3.92874e-05 | 1.6006e-05 | 3(Loss) | true |
| simdjson (reflection) | 1284.46 | 0.0780045 | 1616.28ms | 11812 | 160 | 7488.02 | 8770.09 | 0.146733 | 3.95556 | 14.6504 | 2.44243 | 0.0083485 | 2.48688e-05 | 1.2699e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1102.45 | 0.130082 | 1757.87ms | 11812 | 30 | 5300.06 | 10217.9 | 0.0769296 | 4.6047 | 15.7155 | 2.72898 | 0.00776047 | 1.41099e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3084.32 | 0.0535624 | 1152.94ms | 11812 | 2560 | 9796.88 | 3652.28 | 0.0712552 | 1.67476 | 8.55833 | 1.40196 | 0.000172031 | 3.46576e-05 | 1.20706e-05 | 1(Win) | true |
| glaze | 2244.62 | 0.0709804 | 1291.01ms | 11812 | 320 | 4060.59 | 5018.58 | 0.0124553 | 2.27001 | 11.8045 | 2.21588 | 0.000715639 | 2.61916e-05 | 6.61404e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2117.31 | 0.0921741 | 1328.9ms | 11812 | 320 | 7695.66 | 5320.34 | 0.10878 | 2.40609 | 11.9282 | 1.85718 | 0.00378191 | 2.96309e-05 | 7.67228e-06 | 3(Loss) | true |
| simdjson (reflection) | 1338.19 | 0.0461751 | 1640.41ms | 11812 | 1280 | 19339.2 | 8417.95 | 0.0748404 | 3.81096 | 14.218 | 2.33559 | 0.00828163 | 3.02261e-05 | 1.11116e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1187.59 | 0.0464201 | 1749.18ms | 11812 | 1280 | 24816.2 | 9485.41 | 0.0502411 | 4.32147 | 14.8521 | 2.5359 | 0.00681689 | 5.4169e-05 | 2.77128e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15901.1 | 0.0913357 | 813.712ms | 11812 | 640 | 267.951 | 708.431 | 0.137439 | 0.338892 | 1.59152 | 0.25237 | 0.000127519 | 2.94986e-05 | 1.34926e-05 | 1(Win) | true |
| simdjson (reflection) | 10069.5 | 0.120517 | 854.481ms | 11812 | 320 | 581.68 | 1118.71 | 0.125021 | 0.524113 | 2.44489 | 0.347782 | 0.000100533 | 2.38105e-05 | 2.64561e-06 | 2(Loss) | true |
| glaze | 4066.84 | 0.114222 | 1025.5ms | 11812 | 4890 | 48948.6 | 2769.91 | 0.0471506 | 1.26619 | 4.52641 | 0.716221 | 0.000108655 | 4.75583e-05 | 2.3909e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17096.8 | 0.0298516 | 802.771ms | 11812 | 2560 | 99.0364 | 658.885 | 0.0130412 | 0.315392 | 1.54749 | 0.242127 | 8.46597e-05 | 6.77939e-06 | 1.25667e-06 | 1(Win) | true |
| simdjson (reflection) | 10342 | 0.0619883 | 847.483ms | 11812 | 2560 | 1167.08 | 1089.23 | 0.0180421 | 0.512519 | 2.40222 | 0.337962 | 0.000100798 | 3.75677e-05 | 1.48154e-05 | 2(Loss) | true |
| glaze | 5261.13 | 0.333931 | 958.523ms | 11812 | 1280 | 65435.2 | 2141.14 | 0.0951408 | 0.991601 | 4.26414 | 0.658568 | 0.000102385 | 3.98826e-05 | 2.28184e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4258.38 | 0.0207376 | 1442.83ms | 31235 | 4890 | 10290.1 | 6995.15 | 0.0989501 | 1.19368 | 5.69371 | 0.808933 | 0.00147923 | 3.38682e-05 | 1.69701e-05 | 1(Win) | true |
| jsonifier | 4247.59 | 0.11657 | 1448.27ms | 31235 | 40 | 2673.2 | 7012.93 | 0.0153265 | 1.19723 | 5.66669 | 1.17775 | 0.00199696 | 3.84184e-05 | 3.20154e-05 | 2(Loss) | true |
| simdjson (reflection) | 3039.09 | 0.0185902 | 1727.88ms | 31235 | 4890 | 16235.9 | 9801.63 | 0.0749691 | 1.66911 | 6.40999 | 0.960589 | 0.003393 | 1.85349e-05 | 6.80899e-06 | 3(Loss) | true |
| glaze | 2937.91 | 0.0300301 | 1760.98ms | 31235 | 2560 | 23733.5 | 10139.2 | 0.124711 | 1.73587 | 8.45103 | 1.54052 | 0.00555388 | 2.48119e-05 | 9.76719e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2607.22 | 0.0728435 | 1886.13ms | 31235 | 80 | 5541.16 | 11425.2 | 0.00142231 | 1.94678 | 6.79596 | 1.06528 | 0.0029218 | 1.28061e-05 | 1.00048e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4580.8 | 0.173339 | 1441.49ms | 31235 | 30 | 3811.68 | 6502.8 | 0.0624981 | 1.11111 | 5.39033 | 0.738434 | 0.0014535 | 7.25682e-05 | 6.29636e-05 | 1(Win) | true |
| jsonifier | 4559.21 | 0.0210654 | 1445.1ms | 31235 | 4890 | 9263 | 6533.6 | 0.0940818 | 1.11618 | 5.36376 | 1.10725 | 0.00208311 | 7.83034e-06 | 1.46655e-06 | 2(Loss) | true |
| simdjson (reflection) | 3147.28 | 0.0438652 | 1744.51ms | 31235 | 640 | 11031.4 | 9464.67 | 0.0415848 | 1.61305 | 6.25148 | 0.921339 | 0.00334245 | 6.70322e-06 | 8.00384e-07 | 3(Loss) | true |
| glaze | 3120.83 | 0.0250835 | 1743.25ms | 31235 | 2560 | 14674.4 | 9544.89 | 0.0374365 | 1.62846 | 8.07303 | 1.45417 | 0.00558594 | 1.74084e-05 | 6.76575e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2746.82 | 0.0200295 | 1878.73ms | 31235 | 4890 | 23071.3 | 10844.6 | 0.0582093 | 1.84442 | 6.49342 | 0.997535 | 0.0028795 | 1.04099e-05 | 3.68602e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20803.3 | 0.0468527 | 883.441ms | 31235 | 1280 | 576.097 | 1431.89 | 0.0592336 | 0.250038 | 0.662142 | 0.0958861 | 3.21905e-05 | 5.90283e-06 | 1.12554e-06 | 1(Win) | true |
| glaze | 6605.64 | 0.0755758 | 1193.19ms | 31235 | 2560 | 29734.4 | 4509.48 | 0.12201 | 0.771075 | 3.60567 | 0.477541 | 0.000155787 | 9.09186e-06 | 3.01395e-06 | 2(Loss) | true |
| simdjson (reflection) | 521.885 | 0.106049 | 6453.84ms | 31235 | 4890 | 1.79167e+07 | 57077.7 | 0.308738 | 9.60186 | 37.8691 | 7.00077 | 0.0161752 | 9.17577e-05 | 5.31494e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21908.4 | 0.0571062 | 874.273ms | 31235 | 2560 | 1543.37 | 1359.66 | 0.00835959 | 0.237443 | 0.643413 | 0.091564 | 3.21654e-05 | 6.19047e-06 | 1.10053e-06 | 1(Win) | true |
| glaze | 7570.06 | 0.0771513 | 1132.28ms | 31235 | 4890 | 45069.2 | 3934.98 | 0.120528 | 0.674369 | 3.48362 | 0.450424 | 0.000173983 | 1.65118e-05 | 9.36891e-06 | 2(Loss) | true |
| simdjson (reflection) | 520.254 | 0.321286 | 6455.58ms | 31235 | 640 | 2.16579e+07 | 57256.7 | 0.0241488 | 9.60635 | 37.8229 | 6.99001 | 0.0164527 | 9.45954e-05 | 5.57267e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3382.44 | 0.0218684 | 3800.91ms | 108313 | 1280 | 57088.1 | 30538.7 | 0.0748386 | 1.49461 | 6.993 | 1.45726 | 0.00195448 | 9.86002e-06 | 4.87592e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2332.93 | 0.0283795 | 5176.29ms | 108313 | 640 | 101053 | 44277.1 | 0.00932604 | 2.16507 | 9.88468 | 1.77575 | 0.00269973 | 8.81415e-06 | 4.55855e-06 | 2(Loss) | true |
| glaze | 2115.11 | 0.061559 | 5637.72ms | 108313 | 4890 | 4.41965e+06 | 48836.9 | 0.0428064 | 2.38376 | 10.1286 | 1.90564 | 0.00325005 | 4.00188e-05 | 3.00462e-05 | 3(Loss) | true |
| simdjson (reflection) | 1867.34 | 0.00943771 | 6286.65ms | 108313 | 4890 | 133278 | 55316.9 | 0.010568 | 2.70659 | 12.8559 | 1.96025 | 0.00251936 | 5.77947e-05 | 4.3287e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1384.82 | 0.0156308 | 8210.47ms | 108313 | 2560 | 348000 | 74591.4 | 0.00695242 | 3.64787 | 14.468 | 2.44875 | 0.00306114 | 5.59252e-05 | 3.96781e-05 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4017.82 | 0.0436016 | 3496.61ms | 108313 | 160 | 20105.1 | 25709.3 | 0.0453666 | 1.26005 | 6.29751 | 1.30927 | 0.00201355 | 6.05883e-06 | 3.51989e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2652.88 | 0.0247162 | 4823.22ms | 108313 | 640 | 59274.8 | 38937 | 0.0254 | 1.90714 | 9.1895 | 1.62792 | 0.00248216 | 5.97227e-06 | 2.3514e-06 | 2(Loss) | true |
| glaze | 2356.68 | 0.024 | 5328.18ms | 108313 | 2560 | 283285 | 43830.9 | 0.0724802 | 2.14132 | 9.48787 | 1.76902 | 0.00281187 | 5.17886e-06 | 2.31173e-06 | 3(Loss) | true |
| simdjson (reflection) | 1928.13 | 0.0425587 | 6291.59ms | 108313 | 160 | 83173.2 | 53572.7 | 0.0549418 | 2.62203 | 12.5512 | 1.88963 | 0.00243432 | 2.1581e-05 | 1.56376e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1484.41 | 0.0256988 | 7882.08ms | 108313 | 1280 | 409344 | 69586.6 | 0.0642114 | 3.39917 | 13.8306 | 2.31692 | 0.00260158 | 1.20095e-05 | 7.12634e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20074.9 | 0.0353376 | 1256.98ms | 108313 | 1280 | 4231.91 | 5145.49 | 0.20844 | 0.253721 | 1.05666 | 0.286679 | 0.000110877 | 2.87073e-06 | 1.01702e-06 | 1(Win) | true |
| simdjson (reflection) | 15594.2 | 0.0299779 | 1405.56ms | 108313 | 2560 | 10094.3 | 6623.96 | 0.0881437 | 0.326117 | 1.49032 | 0.193753 | 0.000169171 | 6.14899e-06 | 3.71825e-06 | 2(Loss) | true |
| glaze | 5444.65 | 0.0910426 | 2647.3ms | 108313 | 1280 | 381875 | 18971.9 | 0.0989877 | 0.930151 | 2.95972 | 0.38277 | 0.00016744 | 8.84301e-06 | 5.12837e-06 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20280 | 0.0357518 | 1244.88ms | 108313 | 640 | 2122.27 | 5093.46 | 0.00444791 | 0.251316 | 1.05182 | 0.285589 | 0.000114267 | 3.73628e-06 | 1.44258e-06 | 1(Win) | true |
| simdjson (reflection) | 15977 | 0.0267848 | 1391ms | 108313 | 4890 | 14664.1 | 6465.25 | 0.0256383 | 0.317843 | 1.48547 | 0.192664 | 0.000181646 | 5.38279e-06 | 2.61304e-06 | 2(Loss) | true |
| glaze | 6303.09 | 0.0885248 | 2393.49ms | 108313 | 1280 | 269398 | 16388.1 | 0.0478921 | 0.806422 | 2.91371 | 0.372153 | 0.000164245 | 2.09102e-05 | 1.53995e-05 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3886.28 | 0.0346981 | 6018.74ms | 213963 | 4890 | 1.62304e+06 | 52505.5 | 0.0162814 | 1.29286 | 5.78128 | 0.944103 | 0.00133217 | 2.31353e-05 | 1.58485e-05 | 1(Win) | true |
| jsonifier | 3478.68 | 0.0394651 | 6607.93ms | 213963 | 320 | 171485 | 58657.6 | 0.0451658 | 1.45356 | 5.82822 | 1.36903 | 0.00213626 | 4.87818e-05 | 3.75503e-05 | 2(Loss) | true |
| simdjson (reflection) | 3345.49 | 0.132757 | 6905.19ms | 213963 | 30 | 196697 | 60992.9 | 0.0674487 | 1.51172 | 7.19453 | 1.01945 | 0.00129898 | 3.27159e-05 | 2.46148e-05 | 3(Loss) | true |
| glaze | 2840.57 | 0.0329835 | 7945.34ms | 213963 | 1280 | 718568 | 71834.4 | 0.0224634 | 1.77767 | 8.05087 | 1.54188 | 0.00213469 | 2.72681e-05 | 1.87094e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2535.47 | 0.050079 | 8819.78ms | 213963 | 320 | 519782 | 80478.6 | 0.0117564 | 1.98485 | 8.01458 | 1.26855 | 0.00164268 | 2.79254e-05 | 1.99363e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4349.47 | 0.0601321 | 5682.87ms | 213963 | 80 | 63666.2 | 46914 | 0.203071 | 1.16295 | 5.43084 | 0.869693 | 0.0012848 | 5.95897e-06 | 3.27159e-06 | 1(Win) | true |
| jsonifier | 3830.24 | 0.0141401 | 6278.13ms | 213963 | 4890 | 277485 | 53273.7 | 0.101402 | 1.31852 | 5.47556 | 1.29389 | 0.00200488 | 2.08682e-05 | 1.59871e-05 | 2(Loss) | true |
| simdjson (reflection) | 3441.57 | 0.036262 | 6911.91ms | 213963 | 320 | 147917 | 59290.2 | 0.0848773 | 1.46884 | 7.04124 | 0.983891 | 0.0012588 | 3.27744e-05 | 2.65233e-05 | 3(Loss) | true |
| glaze | 3045.97 | 0.027759 | 7639.76ms | 213963 | 2560 | 885267 | 66990.4 | 0.0855331 | 1.65561 | 7.72376 | 1.47242 | 0.00185313 | 1.22977e-05 | 8.66096e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2691.67 | 0.0430472 | 8499.95ms | 213963 | 640 | 681559 | 75808.4 | 0.0838217 | 1.86566 | 7.68773 | 1.2009 | 0.00141696 | 4.39036e-05 | 3.68054e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 25656.7 | 0.0223014 | 1542.99ms | 213963 | 4890 | 15383.3 | 7953.11 | 0.0372426 | 0.195714 | 0.612087 | 0.145114 | 5.2659e-05 | 3.44554e-06 | 2.16959e-06 | 1(Win) | true |
| glaze | 6106.1 | 0.0871234 | 4100.86ms | 213963 | 1280 | 1.085e+06 | 33417.6 | 0.189222 | 0.818374 | 3.21184 | 0.397321 | 0.000396549 | 2.55995e-05 | 2.06227e-05 | 2(Loss) | true |
| simdjson (reflection) | 472.169 | 0.228127 | 5615.8ms | 213963 | 640 | 6.22038e+08 | 432157 | 0.108552 | 10.4861 | 40.3027 | 7.89632 | 0.0261442 | 0.200887 | 0.00105589 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 25677.6 | 0.0425654 | 1542.43ms | 213963 | 1280 | 14645.1 | 7946.65 | 0.212134 | 0.194979 | 0.60969 | 0.144572 | 5.44888e-05 | 5.31999e-06 | 3.37383e-06 | 1(Win) | true |
| glaze | 7229.58 | 0.135486 | 3594.01ms | 213963 | 640 | 935879 | 28224.5 | 0.556165 | 0.693826 | 3.18456 | 0.391091 | 0.000394052 | 1.35099e-05 | 1.02018e-05 | 2(Loss) | true |
| simdjson (reflection) | 477.55 | 0.60846 | 5558.05ms | 213963 | 80 | 5.40747e+08 | 427287 | 0.144034 | 10.3775 | 40.3013 | 7.89489 | 0.0244144 | 0.206193 | 0.00122258 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 751.087 | 0.169153 | 7255.95ms | 1834197 | 40 | 6.20774e+08 | 2.32893e+06 | 0.136408 | 6.67428 | 25.8933 | 5.46655 | 0.0395517 | 0.0811726 | 0.00794938 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 719.699 | 0.22081 | 7543.23ms | 1834197 | 30 | 8.64073e+08 | 2.4305e+06 | 0.0240633 | 6.94254 | 30.8714 | 5.22852 | 0.033751 | 0.134901 | 0.0162459 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 716.227 | 0.158419 | 7634.62ms | 1834197 | 80 | 1.19755e+09 | 2.44228e+06 | 0.430238 | 6.93198 | 29.7107 | 6.05667 | 0.0322079 | 0.144049 | 0.00146163 | 2(Tie) | true |
| glaze | 631.199 | 0.0807767 | 8613.19ms | 1834197 | 80 | 4.00887e+08 | 2.77128e+06 | 0.26425 | 7.85481 | 31.9293 | 6.36396 | 0.0325199 | 0.0819765 | 0.01435 | 4(Loss) | true |
| simdjson (ondemand) | 589.039 | 0.15051 | 9213.93ms | 1834197 | 30 | 5.99319e+08 | 2.96963e+06 | 0.328809 | 8.48594 | 33.3321 | 6.10846 | 0.0421888 | 0.145725 | 0.0207199 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 827.234 | 0.194992 | 7180.99ms | 1834197 | 40 | 6.80029e+08 | 2.11455e+06 | 0.0636139 | 6.07949 | 22.8867 | 4.76591 | 0.0388108 | 0.0553262 | 0.000485321 | 1(Win) | true |
| simdjson (reflection) | 814.979 | 0.117617 | 7261.82ms | 1834197 | 160 | 1.01967e+09 | 2.14635e+06 | 0.205837 | 6.15313 | 27.8453 | 4.51133 | 0.0289886 | 0.111689 | 0.00243697 | 2(Loss) | true |
| jsonifier (two-stage) | 780.729 | 0.1021 | 7652.44ms | 1834197 | 160 | 8.3726e+08 | 2.24051e+06 | 0.009922 | 6.37985 | 26.705 | 5.35631 | 0.0314983 | 0.118028 | 0.0150667 | 3(Loss) | true |
| glaze | 693.254 | 0.138958 | 8560.81ms | 1834197 | 160 | 1.96696e+09 | 2.52321e+06 | 0.166549 | 7.22731 | 28.9172 | 5.66255 | 0.031353 | 0.0586354 | 0.0104204 | 4(Loss) | true |
| simdjson (ondemand) | 657.899 | 0.13259 | 9032.81ms | 1834197 | 40 | 4.97113e+08 | 2.65881e+06 | 0.313699 | 7.65827 | 30.3101 | 5.40673 | 0.0377373 | 0.117884 | 0.0144417 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1327.06 | 0.0898656 | 8411.08ms | 1834197 | 80 | 1.12251e+08 | 1.31812e+06 | 0.401317 | 3.78752 | 12.2571 | 0.758364 | 0.00145488 | 0.0597841 | 0.00053719 | 1(Win) | true |
| glaze | 991.332 | 0.246958 | 5522.87ms | 1833577 | 160 | 3.03618e+09 | 1.76393e+06 | 0.343081 | 5.06822 | 15.8266 | 1.02014 | 0.000946688 | 0.0492956 | 0.000223828 | 2(Loss) | true |
| simdjson (reflection) | 877.383 | 0.030233 | 6557.56ms | 1922245 | 40 | 1.5961e+07 | 2.08939e+06 | 0.0150332 | 5.75626 | 18.1209 | 2.02074 | 0.0272848 | 0.0498123 | 0.00302885 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1303.12 | 0.107864 | 8484.44ms | 1834197 | 80 | 1.67714e+08 | 1.34234e+06 | 0.0412119 | 3.82098 | 12.2569 | 0.758324 | 0.00145697 | 0.0596473 | 0.00400002 | 1(Win) | true |
| glaze | 992.812 | 0.296646 | 5480.65ms | 1833577 | 160 | 4.3678e+09 | 1.7613e+06 | 0.249245 | 5.06098 | 15.8258 | 1.01998 | 0.000940842 | 0.0492233 | 0.00053293 | 2(Loss) | true |
| simdjson (reflection) | 866.11 | 0.161376 | 6590.47ms | 1922245 | 30 | 3.5e+08 | 2.11658e+06 | 0.263845 | 5.82675 | 18.1207 | 2.02071 | 0.0272604 | 0.0499257 | 0.0114211 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3225.39 | 0.111359 | 9148.17ms | 9930848 | 160 | 1.7107e+09 | 2.93632e+06 | 0.390024 | 1.54931 | 6.73835 | 1.53949 | 0.00762027 | 0.029986 | 0.00699117 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 3201.3 | 0.254856 | 9192.49ms | 9930848 | 30 | 1.70542e+09 | 2.95842e+06 | 0.0277965 | 1.55694 | 6.83234 | 1.01052 | 0.00595883 | 0.0517947 | 0.00728891 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3198.43 | 0.116318 | 9209.56ms | 9930848 | 160 | 1.89809e+09 | 2.96108e+06 | 0.0729878 | 1.56085 | 6.43931 | 1.15598 | 0.00658755 | 0.0542274 | 0.0170696 | 2(Tie) | true |
| simdjson (ondemand) | 2728.72 | 0.140302 | 5238.21ms | 9930848 | 80 | 1.89702e+09 | 3.47078e+06 | 0.529798 | 1.82249 | 7.28504 | 1.17284 | 0.00732378 | 0.0534905 | 0.00574539 | 4(Loss) | true |
| glaze | 2528.06 | 0.287223 | 5605.18ms | 9930848 | 40 | 4.63125e+09 | 3.74628e+06 | 0.00879083 | 1.9842 | 9.14557 | 1.8014 | 0.00666771 | 0.0290247 | 0.00818976 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 3597.84 | 0.138362 | 8854.33ms | 9930848 | 80 | 1.06123e+09 | 2.63235e+06 | 0.0396618 | 1.38489 | 6.2725 | 0.878069 | 0.00510629 | 0.0467519 | 0.00317335 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 3517.48 | 0.106475 | 9156.21ms | 9930848 | 80 | 6.57496e+08 | 2.6925e+06 | 0.178072 | 1.41688 | 6.18301 | 1.41029 | 0.0074892 | 0.0251162 | 0.00481358 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3506.94 | 0.123804 | 9186.15ms | 9930848 | 80 | 8.94286e+08 | 2.70059e+06 | 0.186383 | 1.42683 | 5.88357 | 1.02663 | 0.00642694 | 0.0494068 | 0.0145806 | 2(Tie) | true |
| simdjson (ondemand) | 2977.1 | 0.438729 | 5131.13ms | 9930848 | 40 | 7.79183e+09 | 3.18122e+06 | 0.389657 | 1.67721 | 6.72747 | 1.04335 | 0.00655628 | 0.0478719 | 0.0045543 | 4(Loss) | true |
| glaze | 2745.35 | 0.311247 | 5545.09ms | 9930848 | 30 | 3.45867e+09 | 3.44976e+06 | 0.304764 | 1.83175 | 8.58897 | 1.67184 | 0.00650159 | 0.0246138 | 0.00457101 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6415.56 | 0.13354 | 9345ms | 9930848 | 80 | 3.10895e+08 | 1.47622e+06 | 0.0272831 | 0.77408 | 2.3539 | 0.141952 | 0.000273622 | 0.0251115 | 0.00133248 | 1(Win) | true |
| glaze | 3634.85 | 0.178421 | 8192.83ms | 9930228 | 160 | 3.45747e+09 | 2.60539e+06 | 0.170139 | 1.37357 | 4.43056 | 0.415403 | 0.000748511 | 0.041677 | 0.00364391 | 2(Loss) | true |
| simdjson (reflection) | 266.758 | 0.11743 | 10757.6ms | 10018896 | 30 | 5.30744e+10 | 3.58182e+07 | 0.575616 | 14.0389 | 38.9099 | 5.85304 | 0.0261067 | 0.271375 | 0.136447 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6439.75 | 0.106757 | 9364.33ms | 9930848 | 320 | 7.88821e+08 | 1.47068e+06 | 0.0405556 | 0.774467 | 2.35386 | 0.141945 | 0.00027142 | 0.0250545 | 0.000435324 | 1(Win) | true |
| glaze | 4006.37 | 0.269514 | 7390.2ms | 9930228 | 40 | 1.62346e+09 | 2.36379e+06 | 0.0235969 | 1.24358 | 4.43026 | 0.415337 | 0.000746181 | 0.0223747 | 0.00110327 | 2(Loss) | true |
| simdjson (reflection) | 266.001 | 0.157117 | 10734.1ms | 10018896 | 30 | 9.55527e+10 | 3.59201e+07 | 0.261129 | 14.0294 | 38.8926 | 5.85196 | 0.0258757 | 0.27098 | 0.136892 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 762.367 | 0.210773 | 7150.75ms | 1834197 | 30 | 7.01645e+08 | 2.29447e+06 | 0.0938871 | 6.52522 | 25.4472 | 5.3174 | 0.0412385 | 0.0839947 | 0.000746303 | 1(Win) | true |
| jsonifier (two-stage) | 724.71 | 0.155873 | 7531.78ms | 1834197 | 80 | 1.13239e+09 | 2.41369e+06 | 0.152845 | 6.89876 | 29.2965 | 5.93796 | 0.0329771 | 0.147726 | 0.00518371 | 2(Loss) | true |
| simdjson (reflection) | 716.201 | 0.178945 | 7629.14ms | 1834197 | 40 | 7.64053e+08 | 2.44237e+06 | 0.0262098 | 7.01662 | 30.7967 | 5.2334 | 0.035662 | 0.136493 | 0.000782945 | 3(Loss) | true |
| glaze | 644.178 | 0.105229 | 8467.63ms | 1834197 | 80 | 6.53192e+08 | 2.71544e+06 | 0.412037 | 7.77862 | 31.7418 | 6.35321 | 0.0327803 | 0.0830806 | 0.00211076 | 4(Loss) | true |
| simdjson (ondemand) | 596.103 | 0.194978 | 9172.24ms | 1834197 | 30 | 9.82072e+08 | 2.93444e+06 | 0.354514 | 8.47409 | 33.2953 | 6.09678 | 0.042318 | 0.147516 | 0.0084066 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 846.627 | 0.194355 | 7132.8ms | 1834197 | 160 | 2.58e+09 | 2.06611e+06 | 0.0780782 | 5.92897 | 22.472 | 4.62835 | 0.0402286 | 0.057349 | 0.000337079 | 1(Win) | true |
| simdjson (reflection) | 810.991 | 0.0986697 | 7352.29ms | 1834197 | 160 | 7.24683e+08 | 2.1569e+06 | 0.0477234 | 6.20189 | 27.7873 | 4.53124 | 0.030531 | 0.111873 | 0.00163877 | 2(Loss) | true |
| jsonifier (two-stage) | 800.96 | 0.329175 | 7534.38ms | 1834197 | 30 | 1.5504e+09 | 2.18391e+06 | 0.162961 | 6.27657 | 26.3226 | 5.2495 | 0.0320462 | 0.120995 | 0.0024183 | 3(Loss) | true |
| glaze | 695.141 | 0.122078 | 8471.1ms | 1834197 | 80 | 7.54943e+08 | 2.51636e+06 | 0.029943 | 7.16961 | 28.7626 | 5.66236 | 0.0318539 | 0.0593174 | 0.000489335 | 4(Loss) | true |
| simdjson (ondemand) | 656.023 | 0.0921903 | 9020.59ms | 1834197 | 160 | 9.66818e+08 | 2.66641e+06 | 0.79026 | 7.63641 | 30.3084 | 5.40585 | 0.0379389 | 0.118351 | 0.00146968 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1318.6 | 0.428342 | 8375.17ms | 1834197 | 40 | 1.29155e+09 | 1.32658e+06 | 0.0223406 | 3.81563 | 12.2518 | 0.758299 | 0.00156714 | 0.0616583 | 0.000127317 | 1(Win) | true |
| glaze | 951.981 | 0.357779 | 5745.7ms | 1833577 | 80 | 3.45511e+09 | 1.83684e+06 | 0.0927029 | 5.26088 | 15.8114 | 1.02019 | 0.000969546 | 0.0818652 | 0.000637722 | 2(Loss) | true |
| simdjson (reflection) | 885.904 | 0.0566107 | 6457.41ms | 1922245 | 80 | 1.09782e+08 | 2.06929e+06 | 0.0643501 | 5.69497 | 18.1187 | 2.02075 | 0.0255661 | 0.0520747 | 5.01497e-05 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1325.47 | 0.175267 | 8371.39ms | 1834197 | 320 | 1.71198e+09 | 1.3197e+06 | 0.255486 | 3.81271 | 12.2516 | 0.75826 | 0.0015793 | 0.061501 | 7.3082e-05 | 1(Win) | true |
| glaze | 1001.94 | 0.378299 | 5464.14ms | 1833577 | 80 | 3.48722e+09 | 1.74525e+06 | 0.134795 | 5.03478 | 15.8105 | 1.01998 | 0.000975539 | 0.0494648 | 0.000569447 | 2(Loss) | true |
| simdjson (reflection) | 887.111 | 0.104083 | 6440.66ms | 1922245 | 30 | 1.38784e+08 | 2.06648e+06 | 0.035009 | 5.69126 | 18.1185 | 2.02071 | 0.0254866 | 0.0520326 | 1.94217e-05 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3300.34 | 0.233113 | 8892.84ms | 9930848 | 80 | 3.57997e+09 | 2.86965e+06 | 0.206742 | 1.5067 | 6.3624 | 1.13411 | 0.00668071 | 0.0546036 | 0.000540841 | 1(Win) | true |
| jsonifier | 3278.58 | 0.154665 | 8982.88ms | 9930848 | 80 | 1.59688e+09 | 2.88868e+06 | 0.148085 | 1.52025 | 6.66862 | 1.5187 | 0.00775892 | 0.0303345 | 0.000591497 | 2(Loss) | true |
| simdjson (reflection) | 3250.8 | 0.147975 | 9132.59ms | 9930848 | 160 | 2.97364e+09 | 2.91338e+06 | 0.0129798 | 1.54933 | 6.81769 | 1.01147 | 0.00626762 | 0.0517526 | 0.00160861 | 3(Loss) | true |
| simdjson (ondemand) | 2789.58 | 0.110999 | 5153.94ms | 9930848 | 80 | 1.13611e+09 | 3.39506e+06 | 1.2397 | 1.80737 | 7.27936 | 1.17096 | 0.00745649 | 0.0536116 | 0.00366439 | 4(Loss) | true |
| glaze | 2569.42 | 0.272942 | 5537.02ms | 9930848 | 40 | 4.0486e+09 | 3.68597e+06 | 0.254636 | 1.96268 | 9.13975 | 1.79951 | 0.00670639 | 0.0293051 | 0.000215145 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 3603.53 | 0.182368 | 8853.44ms | 9930848 | 160 | 3.67566e+09 | 2.6282e+06 | 0.299836 | 1.39881 | 6.26164 | 0.881709 | 0.0053489 | 0.0467849 | 0.00124867 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3576.57 | 0.447001 | 8969.62ms | 9930848 | 160 | 2.2417e+10 | 2.64801e+06 | 0.0243142 | 1.40339 | 5.8131 | 1.00693 | 0.00650198 | 0.0495921 | 0.00104852 | 1(Tie) | true |
| jsonifier | 3527.88 | 0.396088 | 9033.26ms | 9930848 | 30 | 3.39195e+09 | 2.68456e+06 | 0.0442224 | 1.41384 | 6.11903 | 1.39146 | 0.00759158 | 0.025314 | 0.000200201 | 3(Loss) | true |
| simdjson (ondemand) | 2969.08 | 0.355364 | 5103.14ms | 9930848 | 80 | 1.02793e+10 | 3.1898e+06 | 0.747407 | 1.67329 | 6.72719 | 1.04321 | 0.00659509 | 0.0478426 | 0.00227051 | 4(Loss) | true |
| glaze | 2733.4 | 0.128371 | 5511.78ms | 9930848 | 80 | 1.58268e+09 | 3.46484e+06 | 0.703282 | 1.8438 | 8.58931 | 1.67188 | 0.00656812 | 0.0248346 | 0.00173607 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6532.03 | 0.0310098 | 9263.17ms | 9930848 | 160 | 3.23441e+07 | 1.4499e+06 | 0.115181 | 0.772989 | 2.34614 | 0.14195 | 0.000375321 | 0.025127 | 0.000804719 | 1(Win) | true |
| glaze | 2984.18 | 0.195109 | 9898.98ms | 9930228 | 160 | 6.134e+09 | 3.17346e+06 | 0.204974 | 1.67687 | 4.42787 | 0.414461 | 0.000699813 | 0.075669 | 0.0182124 | 2(Loss) | true |
| simdjson (reflection) | 270.905 | 0.240716 | 10622.6ms | 10018896 | 30 | 2.1624e+11 | 3.52698e+07 | 2.41277 | 13.7745 | 38.8632 | 5.84901 | 0.0232304 | 0.265803 | 0.124868 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6481.76 | 0.355762 | 9270.13ms | 9930848 | 40 | 1.08085e+09 | 1.46114e+06 | 0.144441 | 0.77946 | 2.3461 | 0.141943 | 0.000377767 | 0.0251044 | 0.000739803 | 1(Win) | true |
| glaze | 4078.23 | 0.114497 | 7253.95ms | 9930228 | 160 | 1.13106e+09 | 2.32214e+06 | 0.434569 | 1.23658 | 4.42747 | 0.414372 | 0.000736299 | 0.022389 | 0.00155715 | 2(Loss) | true |
| simdjson (reflection) | 286.242 | 1.51556 | 10109ms | 10018896 | 30 | 7.67788e+12 | 3.33801e+07 | 0.526536 | 13.6849 | 38.8759 | 5.85003 | 0.0232071 | 0.280323 | 0.143823 | 3(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1338.44 | 0.163435 | 5945.85ms | 642697 | 40 | 2.2406e+07 | 457938 | 0.0295506 | 3.72905 | 17.9515 | 3.35036 | 0.0135327 | 0.0250974 | 5.95926e-05 | 1(Win) | true |
| simdjson (ondemand) | 1209.29 | 0.212423 | 6568.76ms | 642697 | 320 | 3.7094e+08 | 506844 | 0.276795 | 4.15872 | 19.9982 | 3.18446 | 0.0119787 | 0.0667268 | 7.31245e-05 | 2(Loss) | true |
| simdjson (reflection) | 1188.38 | 0.174312 | 6691.56ms | 642697 | 40 | 3.23307e+07 | 515763 | 0.00861096 | 4.22427 | 20.6316 | 3.16711 | 0.0120132 | 0.0577119 | 6.23933e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1151.11 | 0.222177 | 6984.41ms | 642697 | 80 | 1.11962e+08 | 532464 | 0.550409 | 4.29291 | 20.2808 | 3.70273 | 0.0168496 | 0.0528104 | 6.96868e-05 | 4(Loss) | true |
| jsonifier | 1073.2 | 0.170696 | 7389.3ms | 642697 | 160 | 1.52062e+08 | 571120 | 0.0576525 | 4.69 | 17.8552 | 3.43983 | 0.0405687 | 0.0169267 | 4.11644e-05 | 5(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1481.25 | 0.0947832 | 5703.82ms | 642697 | 640 | 9.84465e+07 | 413789 | 0.201764 | 3.39025 | 16.7834 | 3.09 | 0.0130374 | 0.00317374 | 1.53163e-05 | 1(Win) | true |
| simdjson (ondemand) | 1330.68 | 0.230351 | 6253.96ms | 642697 | 30 | 3.37729e+07 | 460611 | 0.108419 | 3.72492 | 18.7915 | 2.91419 | 0.010979 | 0.0225223 | 3.62016e-05 | 2(Loss) | true |
| simdjson (reflection) | 1263.06 | 0.129774 | 6661.24ms | 642697 | 80 | 3.17273e+07 | 485270 | 0.957517 | 3.97606 | 19.4844 | 2.90776 | 0.0112277 | 0.0478366 | 7.0951e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1201.75 | 0.102761 | 6949.73ms | 642697 | 640 | 1.75801e+08 | 510026 | 0.36373 | 4.12437 | 19.1717 | 3.45343 | 0.0164038 | 0.0467854 | 4.19059e-05 | 4(Loss) | true |
| jsonifier | 1125.07 | 0.0890688 | 7383.99ms | 642697 | 160 | 3.76722e+07 | 544785 | 0.017544 | 4.43168 | 16.7457 | 3.1904 | 0.0400414 | 0.0146166 | 2.89405e-05 | 5(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2422.36 | 0.084049 | 6653.74ms | 642697 | 1280 | 5.78912e+07 | 253028 | 0.1038 | 2.0743 | 7.15744 | 0.610276 | 8.15752e-05 | 0.0041151 | 1.93022e-05 | 1(Win) | true |
| glaze | 1617.84 | 0.129403 | 9919.84ms | 642692 | 640 | 1.53816e+08 | 378850 | 0.133816 | 3.09086 | 9.63423 | 0.666379 | 0.000137345 | 0.0427378 | 5.10207e-05 | 2(Loss) | true |
| simdjson (reflection) | 1294.2 | 0.103264 | 6147.6ms | 643373 | 160 | 3.83477e+07 | 474091 | 0.204872 | 3.8812 | 14.0539 | 1.45437 | 0.00541869 | 0.00236444 | 1.88848e-05 | 3(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2437.24 | 0.0957166 | 6659.68ms | 642697 | 30 | 1.73825e+06 | 251483 | 0.17673 | 2.07057 | 7.15663 | 0.610093 | 8.59918e-05 | 0.00401537 | 1.04767e-05 | 1(Win) | true |
| glaze | 1741.03 | 0.0973164 | 9216.36ms | 642692 | 320 | 3.7559e+07 | 352043 | 0.210142 | 2.90114 | 9.63206 | 0.665886 | 0.000137867 | 0.00333653 | 0.000118389 | 2(Loss) | true |
| simdjson (reflection) | 1288.21 | 0.102383 | 6122.21ms | 643373 | 160 | 3.80478e+07 | 476296 | 0.0717309 | 3.87741 | 14.0531 | 1.45419 | 0.00515273 | 0.00410606 | 2.08763e-05 | 3(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2222.19 | 0.0900738 | 6823.54ms | 1225964 | 320 | 7.18685e+07 | 526133 | 0.179081 | 2.22806 | 11.1558 | 1.68591 | 0.004845 | 0.0630541 | 3.18092e-05 | 1(Win) | true |
| simdjson (reflection) | 2121.77 | 0.72602 | 7038.94ms | 1225964 | 640 | 1.02432e+10 | 551035 | 0.808592 | 2.352 | 11.4877 | 1.67675 | 0.00494911 | 0.0579361 | 3.95862e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2031.4 | 0.330948 | 7433.54ms | 1225964 | 40 | 1.45126e+08 | 575550 | 0.41088 | 2.42871 | 11.3399 | 1.97938 | 0.00745313 | 0.0578616 | 3.53395e-05 | 3(Loss) | true |
| glaze | 1844.91 | 0.179633 | 8148.19ms | 1225964 | 320 | 4.14695e+08 | 633729 | 0.206079 | 2.69056 | 12.2201 | 2.52536 | 0.01373 | 0.0297647 | 1.50545e-05 | 4(Loss) | true |
| jsonifier | 1775.21 | 0.0983715 | 8475.5ms | 1225964 | 640 | 2.68643e+08 | 658610 | 0.0504384 | 2.80985 | 12.4108 | 2.70407 | 0.0168787 | 0.0233612 | 2.01665e-05 | 5(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2408.01 | 0.975014 | 6587.73ms | 1225964 | 160 | 3.58576e+09 | 485534 | 0.00306097 | 2.05592 | 10.5229 | 1.54418 | 0.00433432 | 0.037537 | 2.1269e-05 | 1(Win) | true |
| simdjson (reflection) | 2316.53 | 0.101942 | 6942.24ms | 1225964 | 160 | 4.23548e+07 | 504707 | 0.152702 | 2.16075 | 10.8862 | 1.54081 | 0.00463747 | 0.0510653 | 2.32521e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2162.08 | 0.177823 | 7347.46ms | 1225964 | 160 | 1.47947e+08 | 540762 | 0.373937 | 2.27819 | 10.7586 | 1.84872 | 0.00714089 | 0.0528484 | 2.46388e-05 | 3(Loss) | true |
| glaze | 2011.12 | 0.13379 | 7857.63ms | 1225964 | 640 | 3.87173e+08 | 581353 | 0.191988 | 2.46904 | 11.6079 | 2.38894 | 0.013407 | 0.0118955 | 6.5293e-06 | 4(Loss) | true |
| jsonifier | 1850.14 | 0.155718 | 8444.59ms | 1225964 | 40 | 3.87332e+07 | 631937 | 0.143875 | 2.68301 | 11.829 | 2.57328 | 0.0167639 | 0.0211759 | 1.09506e-05 | 5(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4587.21 | 0.127326 | 6950.58ms | 1225964 | 40 | 4.21261e+06 | 254876 | 0.393598 | 1.09775 | 3.76988 | 0.319937 | 2.46337e-05 | 0.0126575 | 4.05803e-06 | 1(Win) | true |
| glaze | 2562.16 | 0.811835 | 5978.83ms | 1225970 | 640 | 8.78341e+09 | 456325 | 0.273916 | 1.96005 | 6.47955 | 0.654433 | 0.000117007 | 0.034868 | 2.17035e-05 | 2(Loss) | true |
| simdjson (reflection) | 261.016 | 0.766375 | 6692.89ms | 1226640 | 80 | 9.43782e+10 | 4.48177e+06 | 0.384358 | 18.964 | 60.4739 | 8.45871 | 0.0258504 | 0.595273 | 0.0814614 | 3(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4561.73 | 0.180634 | 6964.57ms | 1225964 | 30 | 6.43006e+06 | 256300 | 0.229347 | 1.09885 | 3.76943 | 0.319836 | 2.62379e-05 | 0.0124391 | 9.73384e-06 | 1(Win) | true |
| glaze | 2735.03 | 0.765412 | 5547.82ms | 1225970 | 640 | 6.85184e+09 | 427482 | 0.184412 | 1.83557 | 6.47793 | 0.654079 | 0.000114703 | 0.0153123 | 1.46045e-05 | 2(Loss) | true |
| simdjson (reflection) | 258.642 | 1.18399 | 6854.97ms | 1226640 | 30 | 8.60307e+10 | 4.52291e+06 | 0.0956565 | 19.2245 | 60.4743 | 8.4588 | 0.0260458 | 0.5964 | 0.117049 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1450.16 | 0.587994 | 7090.43ms | 409725 | 640 | 1.60649e+09 | 269449 | 0.147803 | 3.46321 | 13.5787 | 2.458 | 0.0219563 | 0.0187085 | 0.00049293 | 1(Win) | true |
| jsonifier (two-stage) | 1367.74 | 0.947092 | 7521.51ms | 409725 | 320 | 2.34267e+09 | 285686 | 0.0866638 | 3.65986 | 16.0494 | 2.7746 | 0.013088 | 0.0525263 | 0.000198365 | 2(Loss) | true |
| glaze | 1178.35 | 0.255202 | 8657.06ms | 409725 | 1280 | 9.16681e+08 | 331604 | 0.0539581 | 4.24742 | 17.2097 | 3.36869 | 0.025479 | 0.0102484 | 0.000407304 | 3(Loss) | true |
| simdjson (reflection) | 1150 | 0.0393234 | 8879.67ms | 409725 | 640 | 1.14253e+07 | 339776 | 0.143794 | 4.33317 | 16.9769 | 2.95527 | 0.0131518 | 0.0465231 | 0.000140899 | 4(Loss) | true |
| simdjson (ondemand) | 845.102 | 0.211537 | 5975.08ms | 409725 | 320 | 3.06117e+08 | 462363 | 0.0811472 | 5.94978 | 19.3646 | 3.51444 | 0.015048 | 0.0595105 | 0.000144274 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2123.71 | 0.143066 | 6147.1ms | 409725 | 160 | 1.10863e+07 | 183992 | 0.196893 | 2.36187 | 10.2622 | 1.79443 | 0.0160028 | 0.000173211 | 2.31863e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1941.19 | 0.351987 | 6634.18ms | 409725 | 1280 | 6.42562e+08 | 201291 | 0.549185 | 2.58829 | 12.7336 | 2.11109 | 0.00777756 | 0.00802783 | 6.15752e-05 | 2(Loss) | true |
| glaze | 1505.52 | 0.198692 | 8068.78ms | 409725 | 160 | 4.25495e+07 | 259541 | 0.253048 | 3.31076 | 14.331 | 2.75908 | 0.0204299 | 0.000588199 | 8.26316e-05 | 3(Loss) | true |
| simdjson (reflection) | 1411.72 | 0.105965 | 8457.78ms | 409725 | 640 | 5.50542e+07 | 276786 | 0.0891708 | 3.55521 | 14.4776 | 2.37367 | 0.00603809 | 0.0323086 | 6.32208e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1041.6 | 0.131812 | 5450.88ms | 409725 | 80 | 1.95605e+07 | 375138 | 0.105806 | 4.80999 | 16.3457 | 2.87018 | 0.00636686 | 0.0145708 | 0.000165507 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15466 | 0.0562585 | 3341.2ms | 409725 | 320 | 64648.2 | 25264.7 | 0.00132347 | 0.327234 | 1.59814 | 0.24103 | 1.75651e-05 | 0.00601233 | 1.45677e-06 | 1(Win) | true |
| simdjson (reflection) | 11159.6 | 0.132016 | 4217.04ms | 409725 | 30 | 64100.8 | 35014.1 | 0.0439629 | 0.453112 | 2.38968 | 0.298915 | 0.00141656 | 0.00164793 | 9.35587e-06 | 2(Loss) | true |
| glaze | 3681.35 | 0.0882419 | 5934.56ms | 409725 | 2560 | 2.24574e+07 | 106141 | 0.795805 | 1.36231 | 5.57969 | 0.872066 | 0.0102413 | 0.0274034 | 9.43087e-06 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15361.6 | 0.0757669 | 3310.53ms | 409725 | 1280 | 475426 | 25436.5 | 0.0867679 | 0.325861 | 1.59689 | 0.240747 | 2.12891e-05 | 0.00572413 | 5.17687e-06 | 1(Win) | true |
| simdjson (reflection) | 11571.1 | 0.0466957 | 4150.05ms | 409725 | 2560 | 636542 | 33768.9 | 0.168961 | 0.434064 | 2.38835 | 0.298615 | 0.000757101 | 5.26258e-05 | 1.80294e-05 | 2(Loss) | true |
| glaze | 4141.28 | 0.496489 | 5313.11ms | 409725 | 40 | 8.77801e+06 | 94353.6 | 0.133489 | 1.22016 | 5.56313 | 0.868285 | 0.010104 | 0.000727378 | 1.72677e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2425.73 | 0.871031 | 8151.01ms | 785750 | 40 | 2.89608e+08 | 308917 | 0.951229 | 2.05269 | 9.00296 | 1.46452 | 0.00778463 | 0.0545339 | 3.28985e-05 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2032.65 | 0.472394 | 9623.43ms | 785750 | 1280 | 3.88208e+09 | 368657 | 0.126931 | 2.48168 | 9.53385 | 1.57439 | 0.00772404 | 0.0500527 | 6.54252e-05 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 2009.84 | 0.467366 | 9705.55ms | 785750 | 1280 | 3.8866e+09 | 372840 | 0.0229683 | 2.50431 | 9.13875 | 1.84647 | 0.0122811 | 0.0277024 | 1.74336e-05 | 2(Tie) | true |
| glaze | 1833.26 | 0.10954 | 5299.47ms | 785750 | 160 | 3.20765e+07 | 408751 | 0.0533124 | 2.75125 | 11.6457 | 2.3008 | 0.0133233 | 0.0198588 | 3.85857e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1536.07 | 0.270483 | 6299.72ms | 785750 | 320 | 5.57154e+08 | 487835 | 0.0765503 | 3.29459 | 10.7581 | 1.86077 | 0.00868842 | 0.0573909 | 0.000418529 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3351.14 | 0.088131 | 7199.6ms | 785750 | 1280 | 4.97107e+07 | 223610 | 0.242867 | 1.49756 | 7.27462 | 1.11886 | 0.00499098 | 0.0219018 | 1.68122e-05 | 1(Win) | true |
| jsonifier | 2626.62 | 0.446226 | 8768.55ms | 785750 | 640 | 1.0372e+09 | 285290 | 0.43638 | 1.91672 | 7.40528 | 1.49971 | 0.00907315 | 0.00526492 | 7.22836e-06 | 2(Loss) | true |
| simdjson (reflection) | 2496.58 | 0.179686 | 9054.07ms | 785750 | 1280 | 3.72319e+08 | 300150 | 0.203624 | 2.00926 | 8.2304 | 1.27097 | 0.00391323 | 0.0340397 | 4.011e-05 | 3(Loss) | true |
| glaze | 2192.77 | 0.142046 | 5069.51ms | 785750 | 160 | 3.7702e+07 | 341737 | 0.0201558 | 2.293 | 10.1459 | 1.98345 | 0.0109222 | 0.00592712 | 1.4405e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1900.03 | 0.0356075 | 5679.53ms | 785750 | 640 | 1.26215e+07 | 394388 | 0.125401 | 2.65812 | 9.18551 | 1.52512 | 0.00392092 | 0.0234957 | 2.34609e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19618.9 | 0.255119 | 4608.72ms | 785750 | 4890 | 4.64318e+07 | 38195.4 | 0.112075 | 0.256949 | 0.892093 | 0.125707 | 1.3672e-05 | 0.00883999 | 5.9144e-06 | 1(Win) | true |
| glaze | 4778.2 | 0.314612 | 8451.23ms | 785750 | 640 | 1.55801e+08 | 156827 | 0.143499 | 1.04459 | 4.36993 | 0.633717 | 0.00552545 | 0.0561422 | 8.32187e-05 | 2(Loss) | true |
| simdjson (reflection) | 499.588 | 0.367135 | 9464.54ms | 785750 | 320 | 9.70389e+09 | 1.49993e+06 | 0.450534 | 9.97519 | 37.7704 | 7.16678 | 0.0319049 | 0.357359 | 0.00124795 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19952.2 | 0.109283 | 4581.49ms | 785750 | 320 | 539068 | 37557.3 | 0.0254176 | 0.252363 | 0.891438 | 0.125559 | 1.27545e-05 | 0.00827075 | 2.19138e-06 | 1(Win) | true |
| glaze | 5742.01 | 0.093522 | 7102.66ms | 785750 | 2560 | 3.81337e+07 | 130503 | 0.127108 | 0.878175 | 4.36041 | 0.631537 | 0.00548661 | 0.0134477 | 2.46386e-05 | 2(Loss) | true |
| simdjson (reflection) | 504.985 | 0.406029 | 9444.22ms | 785750 | 160 | 5.80825e+09 | 1.48391e+06 | 0.717863 | 9.93436 | 37.7711 | 7.16697 | 0.0319483 | 0.357207 | 0.000992141 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7336.71 | 0.0664636 | 4204.11ms | 264040 | 640 | 333031 | 34321.7 | 0.0850906 | 0.687191 | 3.0243 | 0.37197 | 0.000569611 | 1.8759e-06 | 3.96483e-07 | 1(Win) | true |
| jsonifier | 7321.53 | 0.0387789 | 4199.4ms | 264040 | 2560 | 455373 | 34392.9 | 0.0825889 | 0.686243 | 3.0243 | 0.37197 | 0.000564782 | 3.36567e-06 | 1.43651e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5410.87 | 0.0209025 | 5424.99ms | 264040 | 4890 | 462710 | 46537.5 | 0.0535367 | 0.933392 | 4.47366 | 0.7144 | 0.00110312 | 9.98873e-06 | 6.61036e-06 | 3(Loss) | true |
| simdjson (reflection) | 5232.62 | 0.0320146 | 5553.4ms | 264040 | 2560 | 607627 | 48122.7 | 0.00609806 | 0.960247 | 4.4569 | 0.715343 | 0.000913591 | 4.11278e-06 | 2.1348e-06 | 4(Loss) | true |
| glaze | 2605.52 | 0.0424629 | 5348.82ms | 264040 | 160 | 269458 | 96644.2 | 0.0860206 | 1.9386 | 8.89564 | 1.3643 | 0.00267116 | 1.70429e-06 | 2.84048e-07 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 7522.55 | 0.0246786 | 4181.26ms | 264040 | 4890 | 333704 | 33473.8 | 0.0644568 | 0.669208 | 2.97008 | 0.359798 | 0.000549191 | 6.8884e-06 | 4.58814e-06 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 7521.48 | 0.0494285 | 4186.28ms | 264040 | 1280 | 350508 | 33478.6 | 0.102603 | 0.668512 | 2.97008 | 0.359798 | 0.000550932 | 1.85519e-06 | 6.86449e-07 | 1(Tie) | true |
| simdjson (ondemand) | 5503 | 0.0541283 | 5401.5ms | 264040 | 320 | 196308 | 45758.3 | 0.0336528 | 0.915947 | 4.40259 | 0.701523 | 0.00116326 | 1.9765e-06 | 8.16638e-07 | 3(Loss) | true |
| simdjson (reflection) | 5299.59 | 0.059692 | 5598.06ms | 264040 | 640 | 514833 | 47514.6 | 0.0481889 | 0.953526 | 4.42106 | 0.707942 | 0.00100266 | 1.39657e-06 | 2.66295e-07 | 4(Loss) | true |
| glaze | 2629.57 | 0.0349096 | 5320.56ms | 264040 | 2560 | 2.86087e+06 | 95760.1 | 0.143225 | 1.91411 | 8.81808 | 1.34841 | 0.00260839 | 3.36123e-06 | 8.96526e-07 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 8867.26 | 0.074696 | 5070.69ms | 399947 | 80 | 82586.8 | 43014.3 | 0.0373573 | 0.570276 | 2.50548 | 0.258652 | 0.000329387 | 1.1564e-06 | 2.50033e-07 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 8855.65 | 0.109855 | 5083.13ms | 399947 | 320 | 716396 | 43070.7 | 0.12298 | 0.569784 | 2.50771 | 0.259207 | 0.000305962 | 1.23454e-06 | 2.18779e-07 | 1(Tie) | true |
| simdjson (ondemand) | 7071.35 | 0.0431165 | 6160.56ms | 399947 | 1280 | 692304 | 53938.7 | 0.0423113 | 0.711846 | 3.43076 | 0.4905 | 0.000661822 | 4.9909e-06 | 3.12151e-06 | 3(Loss) | true |
| simdjson (reflection) | 6902.11 | 0.0352645 | 6311.7ms | 399947 | 1280 | 486102 | 55261.3 | 0.0761354 | 0.731019 | 3.42134 | 0.49148 | 0.000583146 | 8.26281e-06 | 5.79569e-06 | 4(Loss) | true |
| glaze | 3403.15 | 0.0557729 | 6119.9ms | 399947 | 2560 | 1.0003e+07 | 112078 | 0.0351942 | 1.47556 | 7.26752 | 1.2044 | 0.002134 | 8.171e-06 | 5.63161e-06 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9075.16 | 0.0358997 | 5032.06ms | 399947 | 320 | 72849.7 | 42028.9 | 0.0126162 | 0.557275 | 2.47195 | 0.251181 | 0.000297532 | 4.04741e-06 | 1.86743e-06 | 1(Win) | true |
| jsonifier (two-stage) | 9039.89 | 0.0305342 | 5047.61ms | 399947 | 2560 | 424904 | 42192.9 | 0.0412027 | 0.557907 | 2.46988 | 0.250678 | 0.00030569 | 2.22002e-06 | 1.25114e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7170.46 | 0.119821 | 6162.38ms | 399947 | 30 | 121871 | 53193.1 | 0.0137217 | 0.705122 | 3.39296 | 0.484094 | 0.000816025 | 3.16709e-06 | 1.25017e-06 | 3(Loss) | true |
| simdjson (reflection) | 6906.79 | 0.0200862 | 6365.32ms | 399947 | 4890 | 601668 | 55223.8 | 0.158485 | 0.730487 | 3.40516 | 0.488332 | 0.000700175 | 2.72224e-06 | 1.604e-06 | 4(Loss) | true |
| glaze | 3432.09 | 0.127539 | 6163.39ms | 399947 | 320 | 6.42875e+06 | 111133 | 0.0921438 | 1.45987 | 7.2164 | 1.19401 | 0.00213868 | 1.73617e-05 | 1.32127e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2041.23 | 0.0533786 | 6719.45ms | 264040 | 1280 | 5.55007e+06 | 123361 | 0.0614899 | 2.47926 | 7.53144 | 1.27594 | 0.0137463 | 0.000674173 | 0.000119859 | 1(Win) | true |
| glaze | 1865.48 | 0.0669827 | 7278.3ms | 264040 | 1280 | 1.04639e+07 | 134983 | 0.278458 | 2.67335 | 10.3516 | 1.82083 | 0.00598031 | 0.000339677 | 6.02063e-05 | 2(Loss) | true |
| simdjson (reflection) | 1786.3 | 0.0553081 | 7624.78ms | 264040 | 2560 | 1.55614e+07 | 140967 | 0.133857 | 2.80643 | 9.95079 | 1.56458 | 0.0109995 | 0.00284255 | 0.000201319 | 3(Loss) | true |
| jsonifier (two-stage) | 1748.18 | 0.0864444 | 7626.44ms | 264040 | 1280 | 1.98451e+07 | 144040 | 0.535716 | 2.84282 | 8.82026 | 1.40546 | 0.0125163 | 0.00191959 | 3.81571e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1332.45 | 0.0801877 | 5025.74ms | 264040 | 1280 | 2.93945e+07 | 188982 | 0.19775 | 3.76378 | 11.1754 | 1.99086 | 0.0113598 | 0.00668453 | 0.000204541 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2627.98 | 0.0876347 | 6119.42ms | 264040 | 640 | 4.5126e+06 | 95818 | 0.0522715 | 1.9236 | 6.19711 | 0.988183 | 0.0101399 | 3.64587e-05 | 1.78595e-05 | 1(Win) | true |
| glaze | 2292.34 | 0.0584411 | 6670.67ms | 264040 | 1280 | 5.27507e+06 | 109848 | 0.00567017 | 2.1926 | 9.01748 | 1.53166 | 0.00465781 | 9.63396e-06 | 3.87015e-06 | 2(Loss) | true |
| simdjson (reflection) | 2210.94 | 0.0464445 | 6983.31ms | 264040 | 2560 | 7.16298e+06 | 113892 | 0.188337 | 2.27387 | 9.0135 | 1.34831 | 0.00340113 | 0.000309547 | 2.1379e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 2183.16 | 0.0465751 | 7146.36ms | 264040 | 2560 | 7.38777e+06 | 115341 | 0.148386 | 2.30145 | 7.49797 | 1.1205 | 0.00908046 | 8.19833e-05 | 2.61087e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1555.19 | 0.070598 | 9430.44ms | 264040 | 2560 | 3.34499e+07 | 161914 | 0.364309 | 3.22681 | 9.92134 | 1.72249 | 0.00861459 | 0.000131482 | 3.88983e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19238.8 | 0.0678853 | 2072.52ms | 264040 | 1280 | 101052 | 13088.5 | 0.00646994 | 0.262844 | 1.0436 | 0.153852 | 1.67884e-05 | 9.80853e-06 | 2.65703e-06 | 1(Win) | true |
| simdjson (reflection) | 12955 | 0.030088 | 2704.11ms | 264040 | 4890 | 167248 | 19437.2 | 0.011288 | 0.390285 | 1.41651 | 0.203848 | 0.00026675 | 1.96413e-05 | 8.8293e-06 | 2(Loss) | true |
| glaze | 6912.42 | 0.185779 | 4414.6ms | 263923 | 2560 | 1.17146e+07 | 36412.2 | 0.00801864 | 0.73046 | 2.34826 | 0.343096 | 0.000341454 | 0.000894302 | 7.8429e-06 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19345.2 | 0.0581768 | 2064.01ms | 264040 | 320 | 18350.3 | 13016.6 | 0.0771498 | 0.262191 | 1.04166 | 0.153412 | 2.21794e-05 | 7.37341e-06 | 3.01801e-06 | 1(Win) | true |
| simdjson (reflection) | 12872.1 | 0.0917141 | 2720.67ms | 264040 | 160 | 51502.9 | 19562.3 | 0.00897692 | 0.393296 | 1.41456 | 0.203405 | 0.000275692 | 6.88816e-06 | 3.43225e-06 | 2(Loss) | true |
| glaze | 7731.18 | 0.218178 | 4030.25ms | 263923 | 2560 | 1.29159e+07 | 32556 | 0.402445 | 0.65342 | 2.32645 | 0.338182 | 0.000329568 | 2.65288e-05 | 1.82064e-05 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2563.11 | 0.0813175 | 8015.54ms | 399947 | 640 | 9.37167e+06 | 148811 | 0.172013 | 1.96576 | 7.0556 | 1.05403 | 0.00752495 | 0.00273649 | 0.000147156 | 1(Win) | true |
| jsonifier (two-stage) | 2478.45 | 0.114172 | 8295.28ms | 399947 | 640 | 1.97579e+07 | 153894 | 0.0946599 | 2.03052 | 6.33704 | 0.941129 | 0.00874083 | 0.00331097 | 0.000107866 | 2(Loss) | true |
| glaze | 2112.96 | 0.0605629 | 9668.1ms | 399947 | 640 | 7.64922e+06 | 180514 | 0.073795 | 2.39681 | 8.68878 | 1.56719 | 0.00871619 | 0.00191702 | 0.000132682 | 3(Loss) | true |
| jsonifier | 2095.51 | 0.0477187 | 9743.43ms | 399947 | 1280 | 9.65639e+06 | 182018 | 0.0371263 | 2.41131 | 6.47293 | 1.23515 | 0.00780557 | 0.00309202 | 9.42859e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1924.89 | 0.0776836 | 5270.04ms | 399947 | 640 | 1.51646e+07 | 198151 | 0.29056 | 2.61658 | 7.87218 | 1.33785 | 0.0081291 | 0.00487045 | 0.000135815 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3032.53 | 0.109452 | 7726.81ms | 399947 | 320 | 6.06444e+06 | 125776 | 0.0857808 | 1.66329 | 5.46334 | 0.752742 | 0.00667585 | 0.000260824 | 4.39043e-05 | 1(Win) | true |
| simdjson (reflection) | 2910.03 | 0.0484188 | 7868.58ms | 399947 | 2560 | 1.03105e+07 | 131071 | 0.101357 | 1.7242 | 6.43864 | 0.911516 | 0.00554183 | 0.00101766 | 2.84852e-05 | 2(Loss) | true |
| glaze | 2591.07 | 0.0463245 | 8603.1ms | 399947 | 160 | 744024 | 147205 | 0.079795 | 1.95005 | 7.81663 | 1.37907 | 0.00412786 | 0.000105498 | 5.81796e-05 | 3(Loss) | true |
| jsonifier | 2520.57 | 0.0285793 | 8859.67ms | 399947 | 1280 | 2.39398e+06 | 151323 | 0.0334156 | 2.00102 | 5.59757 | 1.04628 | 0.00459438 | 0.000124288 | 1.89478e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2229.93 | 0.0708259 | 9883.72ms | 399947 | 1280 | 1.87852e+07 | 171045 | 0.0462774 | 2.24312 | 7.03462 | 1.15721 | 0.00583666 | 0.000156972 | 4.69769e-05 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24094.7 | 0.0349767 | 2339.65ms | 399947 | 1280 | 39240 | 15830 | 0.00455997 | 0.209489 | 0.736605 | 0.101561 | 9.4661e-06 | 9.96812e-06 | 3.25629e-06 | 1(Win) | true |
| glaze | 4143.27 | 0.10985 | 5093.23ms | 399830 | 2560 | 2.61641e+07 | 92030.7 | 0.284323 | 1.21491 | 2.77638 | 0.355471 | 0.000405624 | 0.00510507 | 4.23373e-05 | 2(Loss) | true |
| simdjson (reflection) | 522.367 | 0.177053 | 9466.03ms | 399947 | 640 | 1.06964e+09 | 730175 | 0.0788433 | 9.6141 | 31.0691 | 6.39914 | 0.0622907 | 0.250508 | 0.000292429 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24265.1 | 0.0408337 | 2330.9ms | 399947 | 640 | 26366.9 | 15718.9 | 0.00818153 | 0.208822 | 0.735325 | 0.101271 | 1.52012e-05 | 9.25123e-06 | 5.35227e-06 | 1(Win) | true |
| glaze | 4532.31 | 0.113212 | 9160.36ms | 399830 | 2560 | 2.32239e+07 | 84131 | 0.17808 | 1.11491 | 2.76023 | 0.351722 | 0.000393287 | 2.20709e-05 | 9.48255e-06 | 2(Loss) | true |
| simdjson (reflection) | 526.275 | 0.213828 | 9354.41ms | 399947 | 320 | 7.68523e+08 | 724752 | 0.255189 | 9.53579 | 31.0789 | 6.40138 | 0.0616933 | 0.242407 | 0.00022092 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1050.76 | 0.0669499 | 1155.35ms | 4630 | 80 | 633.207 | 4202.21 | 0.0639953 | 4.85904 | 22.4097 | 4.50389 | 0.00240281 | 9.44924e-05 | 4.58963e-05 | 1(Win) | true |
| jsonifier (two-stage) | 955.298 | 0.0312292 | 1198.62ms | 4630 | 4890 | 10188.6 | 4622.13 | 0.0231069 | 5.33596 | 25.1449 | 4.86048 | 0.00217529 | 0.000107417 | 3.8338e-05 | 2(Loss) | true |
| simdjson (reflection) | 937.446 | 0.0940355 | 1208.13ms | 4630 | 320 | 6277.74 | 4710.15 | 0.124687 | 5.43617 | 26.3203 | 4.67927 | 0.00479279 | 0.00018696 | 7.76188e-05 | 3(Loss) | true |
| simdjson (ondemand) | 788.688 | 0.02422 | 1301.29ms | 4630 | 4890 | 8991.06 | 5598.55 | 0.0215566 | 6.44747 | 30.1372 | 5.48639 | 0.00326147 | 0.000178572 | 8.71439e-05 | 4(Loss) | true |
| glaze | 725.778 | 0.0583228 | 1344.32ms | 4630 | 1280 | 16115.4 | 6083.84 | 0.37715 | 7.01018 | 30.1724 | 5.84428 | 0.00295964 | 9.58423e-05 | 3.25661e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1345.58 | 0.0801183 | 1155.64ms | 4630 | 80 | 552.962 | 3281.49 | 0.00190459 | 3.87802 | 18.1382 | 3.53477 | 0.000542657 | 4.85961e-05 | 1.07991e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1181.94 | 0.0331591 | 1197.79ms | 4630 | 4890 | 7503.88 | 3735.82 | 0.0677689 | 4.32506 | 20.8616 | 3.88855 | 0.00110151 | 5.79929e-05 | 1.76231e-05 | 2(Loss) | true |
| simdjson (reflection) | 1116.87 | 0.0328899 | 1227.98ms | 4630 | 4890 | 8267.83 | 3953.48 | 0.0342858 | 4.53953 | 23.5166 | 4.03672 | 0.00174283 | 8.88223e-05 | 3.00786e-05 | 3(Loss) | true |
| simdjson (ondemand) | 898.154 | 0.0440272 | 1328.15ms | 4630 | 2560 | 11993.4 | 4916.21 | 0.1088 | 5.67111 | 27.0119 | 4.78078 | 0.000913961 | 0.000144185 | 6.28543e-05 | 4(Loss) | true |
| glaze | 847.736 | 0.039914 | 1343.94ms | 4630 | 2560 | 11064.5 | 5208.59 | 0.294897 | 6.01016 | 25.8112 | 4.85421 | 0.00249806 | 5.61049e-05 | 1.09679e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2033.27 | 0.0975869 | 949.955ms | 4630 | 640 | 2874.33 | 2171.63 | 0.0582459 | 2.53117 | 7.74946 | 0.410583 | 0.000216658 | 3.7122e-05 | 1.34989e-06 | 1(Win) | true |
| glaze | 1566.41 | 0.0556073 | 1019.25ms | 4630 | 160 | 393.129 | 2818.88 | 0.00798254 | 3.2748 | 10.1244 | 0.779482 | 0.000215983 | 5.53456e-05 | 2.69978e-06 | 2(Loss) | true |
| simdjson (reflection) | 1059.84 | 0.0287554 | 1146.72ms | 4630 | 40 | 57.4096 | 4166.23 | 0.0110024 | 4.81586 | 15.5339 | 1.47365 | 0.000431965 | 1.07991e-05 | 0 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2053.23 | 0.0384089 | 945.4ms | 4630 | 4890 | 3336.27 | 2150.52 | 0.0337072 | 2.50727 | 7.64082 | 0.385314 | 0.000217308 | 6.48832e-05 | 2.51759e-05 | 1(Win) | true |
| glaze | 1664.2 | 0.043875 | 996.521ms | 4630 | 4890 | 6626.67 | 2653.24 | 0.19171 | 3.06893 | 9.58164 | 0.655941 | 0.000250566 | 5.76837e-05 | 1.61656e-05 | 2(Loss) | true |
| simdjson (reflection) | 1062.65 | 0.0245204 | 1142.61ms | 4630 | 80 | 83.0481 | 4155.2 | 0.0162473 | 4.80444 | 15.4646 | 1.45724 | 0.000429266 | 0.000102592 | 6.2095e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2743.08 | 0.0436934 | 1253.16ms | 14795 | 320 | 1616.35 | 5143.72 | 0.0282585 | 1.85795 | 9.09902 | 1.49348 | 0.000774544 | 3.61186e-05 | 1.98547e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2693.93 | 0.0343304 | 1259.71ms | 14795 | 2560 | 8276.65 | 5237.55 | 0.00458656 | 1.89032 | 8.72477 | 1.55519 | 0.000730056 | 3.34256e-05 | 1.40461e-05 | 2(Loss) | true |
| jsonifier | 2529.85 | 0.0502683 | 1297.44ms | 14795 | 640 | 5030.49 | 5577.26 | 0.00753562 | 2.01282 | 9.09179 | 1.95897 | 0.00191408 | 2.20725e-05 | 6.54782e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2262.91 | 0.0419802 | 1363.17ms | 14795 | 1280 | 8769.87 | 6235.15 | 0.0497935 | 2.2473 | 10.407 | 1.76945 | 0.00101797 | 6.00921e-05 | 3.03629e-05 | 4(Loss) | true |
| glaze | 1741.06 | 0.147447 | 1549.69ms | 14795 | 1280 | 182762 | 8104.03 | 0.124389 | 2.9118 | 13.3715 | 2.47773 | 0.00384748 | 6.87521e-05 | 4.19272e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3240.66 | 0.0771948 | 1264.59ms | 14795 | 30 | 338.892 | 4353.93 | 0.0896545 | 1.57727 | 7.38351 | 1.25076 | 0.000477639 | 3.15422e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 3157.19 | 0.025311 | 1277.37ms | 14795 | 4890 | 6256.85 | 4469.04 | 0.00989067 | 1.6153 | 8.27165 | 1.30301 | 0.000617809 | 1.51076e-05 | 3.49701e-06 | 2(Loss) | true |
| jsonifier | 3027.66 | 0.113413 | 1297.12ms | 14795 | 2560 | 71512.4 | 4660.23 | 0.00699954 | 1.68306 | 7.74931 | 1.65434 | 0.000787824 | 1.54983e-05 | 9.76893e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2562.35 | 0.0367633 | 1381.93ms | 14795 | 2560 | 10491.1 | 5506.51 | 0.111249 | 1.98217 | 9.42967 | 1.54823 | 0.000439417 | 1.56039e-05 | 4.33001e-06 | 4(Loss) | true |
| glaze | 1963.1 | 0.018674 | 1554.06ms | 14795 | 4890 | 8809.11 | 7187.43 | 0.0193981 | 2.58978 | 12.0103 | 2.16884 | 0.00355129 | 1.87014e-05 | 5.1142e-06 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4873.68 | 0.0473932 | 1023.83ms | 14795 | 4890 | 9205.7 | 2895.06 | 0.0054295 | 1.05003 | 2.48658 | 0.129706 | 0.000122838 | 1.8342e-05 | 3.46936e-06 | 1(Win) | true |
| glaze | 3474.99 | 0.0559644 | 1143.03ms | 14795 | 2560 | 13218.6 | 4060.33 | 0.102284 | 1.47009 | 4.6167 | 0.414803 | 0.000131933 | 1.8693e-05 | 6.20459e-06 | 2(Loss) | true |
| simdjson (reflection) | 405.704 | 0.106952 | 4224.4ms | 14795 | 1280 | 1.77093e+06 | 34778.1 | 0.0478385 | 12.4698 | 43.5184 | 6.09774 | 0.00918643 | 7.11811e-05 | 3.92869e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4995.96 | 0.0709108 | 1013.29ms | 14795 | 2560 | 10267.3 | 2824.2 | 0.069163 | 1.02627 | 2.44833 | 0.120649 | 6.796e-05 | 1.34917e-05 | 2.29702e-06 | 1(Win) | true |
| glaze | 3827.82 | 0.0398379 | 1102.15ms | 14795 | 2560 | 5520.28 | 3686.07 | 0.0527468 | 1.33411 | 4.40399 | 0.366543 | 0.000105795 | 1.80329e-05 | 3.69635e-06 | 2(Loss) | true |
| simdjson (reflection) | 406.516 | 0.0575667 | 4213.91ms | 14795 | 4890 | 1.95221e+06 | 34708.6 | 0.0190234 | 12.4399 | 43.533 | 6.10186 | 0.00862337 | 9.39078e-05 | 4.15494e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1870.26 | 0.0855283 | 993.751ms | 5092 | 80 | 394.531 | 2596.49 | 0.0139592 | 2.74564 | 10.8486 | 2.00452 | 0.00178957 | 5.15515e-05 | 9.81932e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1568.63 | 0.0631329 | 1045.65ms | 5092 | 640 | 2444.71 | 3095.76 | 0.046355 | 3.27431 | 13.3315 | 2.31108 | 0.00159288 | 3.7743e-05 | 2.14798e-06 | 2(Loss) | true |
| glaze | 1481.26 | 0.0702495 | 1064.14ms | 5092 | 160 | 848.635 | 3278.36 | 0.0788644 | 3.45668 | 13.9521 | 2.72604 | 0.00159196 | 3.80499e-05 | 4.90966e-06 | 3(Loss) | true |
| simdjson (reflection) | 1251.09 | 0.0332961 | 1128.06ms | 5092 | 2560 | 4275.89 | 3881.51 | 0.0297597 | 4.07774 | 15.1724 | 2.46445 | 0.00116927 | 0.000100034 | 4.23458e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1198.26 | 0.072269 | 1143.98ms | 5092 | 640 | 5489.82 | 4052.63 | 0.00929267 | 4.25818 | 15.5884 | 2.64709 | 0.00128572 | 6.10639e-05 | 1.16604e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2266.4 | 0.100774 | 994.356ms | 5092 | 1280 | 5967.71 | 2142.66 | 0.0194379 | 2.27388 | 9.24921 | 1.60683 | 0.00205807 | 5.10912e-05 | 1.35016e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1865.47 | 0.0516181 | 1036.33ms | 5092 | 320 | 577.769 | 2603.16 | 0.179985 | 2.75732 | 11.7557 | 1.91811 | 0.00108319 | 2.82306e-05 | 1.22742e-06 | 2(Loss) | true |
| glaze | 1757.51 | 0.0597045 | 1048.76ms | 5092 | 2560 | 6966.86 | 2763.07 | 0.0508828 | 2.91742 | 12.3221 | 2.32522 | 0.000794368 | 5.80721e-05 | 1.99455e-05 | 3(Loss) | true |
| simdjson (reflection) | 1394.43 | 0.0427693 | 1123.15ms | 5092 | 1280 | 2839.61 | 3482.51 | 0.0192292 | 3.67078 | 13.9902 | 2.15279 | 0.00146016 | 4.48007e-05 | 1.13536e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1348.92 | 0.0342822 | 1133.3ms | 5092 | 4890 | 7448.16 | 3599.99 | 0.0119569 | 3.78825 | 13.9998 | 2.25629 | 0.00190049 | 4.78717e-05 | 1.33334e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8008.34 | 0.0716527 | 795.356ms | 5092 | 1280 | 241.639 | 606.381 | 0.225216 | 0.67308 | 2.01767 | 0.346033 | 0.000197 | 7.02695e-05 | 3.20662e-05 | 1(Win) | true |
| simdjson (reflection) | 6847.38 | 0.0846754 | 806.608ms | 5092 | 4890 | 1763.4 | 709.192 | 0.094529 | 0.775961 | 2.58896 | 0.290849 | 0.000196828 | 5.00404e-05 | 1.36145e-05 | 2(Loss) | true |
| glaze | 3557.91 | 0.0890992 | 873.036ms | 5092 | 4890 | 7231.76 | 1364.88 | 0.134893 | 1.45712 | 4.71583 | 0.72231 | 0.000198997 | 7.96389e-05 | 2.7711e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9011.16 | 0.0646349 | 788.748ms | 5092 | 4890 | 593.28 | 538.9 | 0.145798 | 0.602918 | 1.90416 | 0.317753 | 0.000196949 | 3.37753e-05 | 4.49801e-06 | 1(Win) | true |
| simdjson (reflection) | 7301.01 | 0.0717999 | 801.219ms | 5092 | 640 | 145.962 | 665.128 | 0.0643259 | 0.735276 | 2.48507 | 0.2663 | 0.000196386 | 1.87181e-05 | 9.20562e-07 | 2(Loss) | true |
| glaze | 4068.78 | 0.0931399 | 854.523ms | 5092 | 4890 | 6042.66 | 1193.5 | 0.196758 | 1.28186 | 4.2176 | 0.614101 | 0.000197109 | 7.38558e-05 | 1.91969e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3192 | 0.048663 | 1092.04ms | 11724 | 4890 | 14208 | 3502.78 | 0.00692665 | 1.60049 | 6.56158 | 1.02499 | 0.000468565 | 4.60489e-05 | 1.85417e-05 | 1(Win) | true |
| jsonifier | 2708.7 | 0.025454 | 1153.14ms | 11724 | 4890 | 5398.25 | 4127.77 | 0.119169 | 1.8842 | 6.87863 | 1.45616 | 0.000933798 | 3.49379e-05 | 1.09192e-05 | 2(Loss) | true |
| simdjson (reflection) | 2671.79 | 0.0709814 | 1168.25ms | 11724 | 160 | 1411.75 | 4184.79 | 0.0216605 | 1.91087 | 7.38835 | 1.10525 | 0.000613059 | 3.99821e-05 | 1.65259e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2532.92 | 0.0362396 | 1186.69ms | 11724 | 2560 | 6551.13 | 4414.22 | 0.108974 | 2.01902 | 7.56943 | 1.18449 | 0.000686492 | 0.000117014 | 6.83694e-05 | 4(Loss) | true |
| glaze | 2244.31 | 0.0747543 | 1240.48ms | 11724 | 80 | 1109.55 | 4981.88 | 0.0962565 | 2.27537 | 9.40831 | 1.7703 | 0.00142123 | 1.38605e-05 | 2.13238e-06 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3678.36 | 0.0914967 | 1077.48ms | 11724 | 80 | 618.791 | 3039.64 | 0.00534632 | 1.39446 | 5.90788 | 0.860201 | 0.000554418 | 2.66547e-05 | 1.17281e-05 | 1(Win) | true |
| jsonifier | 3016.68 | 0.146277 | 1166.49ms | 11724 | 1280 | 37623.3 | 3706.35 | 0.0394959 | 1.69318 | 6.22484 | 1.29137 | 0.00145055 | 2.22567e-05 | 5.7974e-06 | 2(Loss) | true |
| simdjson (reflection) | 2853.19 | 0.0851159 | 1171.99ms | 11724 | 1280 | 14240.4 | 3918.73 | 0.00972985 | 1.77173 | 6.873 | 0.96891 | 0.000757527 | 6.0173e-05 | 2.65881e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2812.14 | 0.136476 | 1176.16ms | 11724 | 30 | 883.306 | 3975.93 | 0.0587209 | 1.8174 | 6.89068 | 1.01679 | 0.000747754 | 2.84317e-05 | 5.68634e-06 | 4(Loss) | true |
| glaze | 2465.31 | 0.0487578 | 1247.02ms | 11724 | 2560 | 12518.1 | 4535.29 | 0.00509055 | 2.06116 | 8.75051 | 1.60602 | 0.00140974 | 2.92202e-05 | 7.5966e-06 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18512.8 | 0.0542806 | 796.813ms | 11724 | 1280 | 137.565 | 603.955 | 0.00129354 | 0.291239 | 0.932787 | 0.145002 | 8.59615e-05 | 2.39226e-05 | 7.19678e-06 | 1(Win) | true |
| glaze | 4080.04 | 0.423771 | 1021ms | 11746 | 320 | 43317.4 | 2745.53 | 0.0812026 | 1.25859 | 3.75438 | 0.515324 | 0.000223214 | 1.46326e-05 | 3.19258e-06 | 2(Loss) | true |
| simdjson (reflection) | 540.956 | 0.129587 | 2813.75ms | 11724 | 2560 | 1.83649e+06 | 20668.7 | 0.256667 | 9.3534 | 37.2479 | 6.78847 | 0.00496598 | 0.000223467 | 0.000150099 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19306.6 | 0.075574 | 799.517ms | 11724 | 4890 | 936.681 | 579.121 | 0.162975 | 0.279273 | 0.904981 | 0.138349 | 8.5644e-05 | 2.57106e-05 | 5.40726e-06 | 1(Win) | true |
| glaze | 4798.9 | 0.233805 | 974.373ms | 11746 | 1280 | 38125.4 | 2334.26 | 0.0300306 | 1.07304 | 3.49268 | 0.456496 | 0.000248289 | 3.6116e-05 | 1.31029e-05 | 2(Loss) | true |
| simdjson (reflection) | 538.59 | 0.247762 | 2825.56ms | 11724 | 640 | 1.6931e+06 | 20759.5 | 0.0146566 | 9.37536 | 37.2857 | 6.79725 | 0.00549607 | 0.000143536 | 7.72987e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1907.83 | 0.0446755 | 980.592ms | 4857 | 4890 | 5753.13 | 2427.88 | 0.0511677 | 2.69265 | 9.77682 | 1.81954 | 0.000888099 | 5.07353e-05 | 1.58311e-05 | 1(Win) | true |
| glaze | 1658.94 | 0.0913106 | 1027.12ms | 4857 | 4890 | 31785.2 | 2792.14 | 0.13684 | 3.08113 | 11.6969 | 2.28546 | 0.00122754 | 7.22504e-05 | 2.46308e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1632.14 | 0.0542967 | 1025.34ms | 4857 | 2560 | 6078.67 | 2837.99 | 0.113587 | 3.13834 | 11.9367 | 2.00669 | 0.00114839 | 8.66983e-05 | 3.57088e-05 | 3(Loss) | true |
| simdjson (reflection) | 1342.39 | 0.143408 | 1088.86ms | 4857 | 320 | 7835.65 | 3450.56 | 0.0347648 | 3.80744 | 13.4609 | 2.25614 | 0.00244171 | 4.37513e-05 | 1.9302e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1283.06 | 0.0928269 | 1101.52ms | 4857 | 640 | 7187.31 | 3610.1 | 0.155535 | 3.99192 | 14.428 | 2.80008 | 0.000659165 | 0.000106483 | 4.98636e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2616.85 | 0.0771684 | 940.668ms | 4857 | 2560 | 4776.37 | 1770.07 | 0.0861028 | 1.97381 | 7.34836 | 1.2551 | 0.000212162 | 6.93265e-05 | 1.76935e-05 | 1(Win) | true |
| glaze | 2422.14 | 0.0415559 | 956.715ms | 4857 | 4890 | 3088.24 | 1912.35 | 0.0861952 | 2.13292 | 9.14659 | 1.71546 | 0.000997359 | 8.21448e-05 | 3.96198e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2038.46 | 0.0490948 | 996.716ms | 4857 | 4890 | 6085.71 | 2272.3 | 0.0530401 | 2.52426 | 9.81491 | 1.50587 | 0.000652359 | 7.61661e-05 | 2.1052e-05 | 3(Loss) | true |
| simdjson (reflection) | 1587.25 | 0.0761968 | 1059.93ms | 4857 | 4890 | 24178.5 | 2918.26 | 0.0468114 | 3.23106 | 11.8785 | 1.89026 | 0.000955129 | 0.000121933 | 6.61874e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1568.69 | 0.0854746 | 1057.81ms | 4857 | 1280 | 8153.58 | 2952.79 | 0.0436749 | 3.27131 | 12.1717 | 2.32963 | 0.00163247 | 9.00762e-05 | 2.99182e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10720.8 | 0.163481 | 778.388ms | 4857 | 2560 | 1277.19 | 432.056 | 0.0579197 | 0.514789 | 1.58987 | 0.274449 | 0.000206612 | 5.30002e-05 | 1.54416e-05 | 1(Win) | true |
| simdjson (reflection) | 6666.89 | 0.0840565 | 806.256ms | 4857 | 4890 | 1667.79 | 694.776 | 0.14345 | 0.797259 | 2.15998 | 0.335186 | 0.000206225 | 6.26928e-05 | 2.49677e-05 | 2(Loss) | true |
| glaze | 3987.55 | 0.140439 | 855.952ms | 4857 | 2560 | 6813.05 | 1161.62 | 0.208624 | 1.31107 | 3.93267 | 0.618695 | 0.00020621 | 0.00010029 | 5.08287e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12071.3 | 0.0783152 | 773.601ms | 4857 | 2560 | 231.187 | 383.721 | 0.111288 | 0.464561 | 1.46963 | 0.245007 | 0.000205888 | 4.76921e-05 | 1.9865e-05 | 1(Win) | true |
| simdjson (reflection) | 7268.83 | 0.142193 | 800.509ms | 4857 | 1280 | 1050.92 | 637.241 | 0.0257391 | 0.73821 | 2.04324 | 0.305744 | 0.00020621 | 4.45555e-05 | 1.83369e-05 | 2(Loss) | true |
| glaze | 4764.41 | 0.105453 | 833.804ms | 4857 | 2560 | 2690.75 | 972.207 | 0.19053 | 1.1039 | 3.44101 | 0.508133 | 0.000206612 | 4.9381e-05 | 2.53339e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2324.42 | 0.0947674 | 1042.9ms | 7376 | 640 | 5263.92 | 3026.26 | 0.0219902 | 2.20269 | 8.38253 | 1.33223 | 0.000674908 | 7.94384e-05 | 4.42737e-05 | 1(Win) | true |
| jsonifier | 2001.33 | 0.0476156 | 1088.97ms | 7376 | 1280 | 3585.21 | 3514.82 | 0.19606 | 2.55496 | 8.49776 | 1.77691 | 0.00131762 | 6.78933e-05 | 2.7115e-05 | 2(Loss) | true |
| glaze | 1993.63 | 0.0400818 | 1088.15ms | 7376 | 2560 | 5120.22 | 3528.39 | 0.0773457 | 2.56402 | 9.83921 | 1.97817 | 0.00130443 | 2.94981e-05 | 7.0965e-06 | 3(Loss) | true |
| simdjson (reflection) | 1953.7 | 0.072544 | 1102.34ms | 7376 | 1280 | 8732.5 | 3600.5 | 0.139867 | 2.61482 | 9.399 | 1.5139 | 0.00135458 | 3.66476e-05 | 1.36634e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1867.19 | 0.0570416 | 1139.74ms | 7376 | 1280 | 5910.95 | 3767.32 | 0.0238124 | 2.73644 | 10.0298 | 1.86971 | 0.000378974 | 5.71956e-05 | 2.43611e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2884.91 | 0.0461988 | 1005.66ms | 7376 | 4890 | 6205.1 | 2438.31 | 0.0100036 | 1.78182 | 6.98482 | 1.00163 | 0.000533926 | 5.17347e-05 | 1.48606e-05 | 1(Win) | true |
| glaze | 2681.38 | 0.105028 | 1023.28ms | 7376 | 80 | 607.329 | 2623.39 | 0.0347954 | 1.91564 | 7.98807 | 1.5667 | 0.00096936 | 1.86415e-05 | 6.77874e-06 | 2(Loss) | true |
| jsonifier | 2550.99 | 0.0512941 | 1042.78ms | 7376 | 320 | 640.194 | 2757.48 | 0.0547674 | 2.01349 | 6.89791 | 1.40523 | 0.000495695 | 8.34633e-05 | 4.74512e-05 | 3(Loss) | true |
| simdjson (reflection) | 2326.38 | 0.102965 | 1072.51ms | 7376 | 320 | 3101.79 | 3023.71 | 0.00351377 | 2.20403 | 8.19889 | 1.23902 | 0.000346563 | 2.9657e-05 | 4.66039e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2276.56 | 0.153974 | 1071.69ms | 7376 | 80 | 1810.81 | 3089.89 | 0.0441149 | 2.25397 | 8.50976 | 1.55315 | 0.00119136 | 4.57565e-05 | 8.47343e-06 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14756.1 | 0.152963 | 782.694ms | 7376 | 1280 | 680.582 | 476.704 | 0.281254 | 0.372349 | 1.09165 | 0.179094 | 0.000136104 | 4.68157e-05 | 1.84297e-05 | 1(Win) | true |
| glaze | 3600.9 | 0.242054 | 937.712ms | 7376 | 640 | 14309.4 | 1953.48 | 0.0594645 | 1.43174 | 4.04637 | 0.595445 | 0.0001396 | 2.24546e-05 | 2.33019e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.294 | 0.193322 | 2083.06ms | 7376 | 320 | 212034 | 13315.1 | 0.0484881 | 9.6645 | 38.1407 | 7.58853 | 0.00746975 | 4.57565e-05 | 2.20309e-05 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16463.8 | 0.0759137 | 776.668ms | 7376 | 1280 | 134.658 | 427.259 | 0.0851362 | 0.3375 | 1.01247 | 0.161334 | 0.000135575 | 1.72646e-05 | 9.53261e-07 | 1(Win) | true |
| glaze | 4025.07 | 0.0796578 | 913.245ms | 7376 | 4890 | 9476.77 | 1747.62 | 0.0928649 | 1.28617 | 3.70445 | 0.518032 | 0.000154955 | 2.10709e-05 | 5.68361e-06 | 2(Loss) | true |
| simdjson (reflection) | 524.428 | 0.159031 | 2088.21ms | 7376 | 640 | 291217 | 13413.3 | 0.01492 | 9.66068 | 38.1472 | 7.59016 | 0.00743501 | 0.000125195 | 6.46099e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2404.29 | 0.0268946 | 909.206ms | 4390 | 4890 | 1072.49 | 1741.31 | 0.0731557 | 2.15053 | 9.87472 | 1.71139 | 0.000230585 | 4.51854e-05 | 1.32761e-05 | 1(Win) | true |
| glaze | 1936.03 | 0.0622088 | 951.492ms | 4390 | 1280 | 2316.44 | 2162.49 | 0.405075 | 2.65797 | 12.6517 | 2.42756 | 0.000233663 | 6.26424e-05 | 1.70843e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1814.26 | 0.0610391 | 966.344ms | 4390 | 1280 | 2539.54 | 2307.62 | 0.0963944 | 2.83535 | 13.2756 | 2.17312 | 0.00207734 | 3.06093e-05 | 2.66942e-06 | 3(Loss) | true |
| simdjson (reflection) | 1269.06 | 0.136275 | 1065.82ms | 4390 | 40 | 808.462 | 3299 | 0.037399 | 4.03367 | 14.8153 | 2.47198 | 0.00534169 | 3.98633e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1124.06 | 0.0403606 | 1109.95ms | 4390 | 2560 | 5785.02 | 3724.56 | 0.0306653 | 4.54409 | 15.785 | 2.74396 | 0.00288982 | 6.32652e-05 | 2.37578e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2806.51 | 0.044866 | 932.797ms | 4390 | 4890 | 2190.48 | 1491.76 | 0.0141749 | 1.85782 | 8.8303 | 1.46242 | 0.000232449 | 3.88036e-05 | 1.16923e-05 | 1(Win) | true |
| glaze | 2238.14 | 0.0514982 | 939.814ms | 4390 | 2560 | 2375.62 | 1870.58 | 0.0400784 | 2.30599 | 11.4554 | 2.14806 | 0.00026276 | 3.85286e-05 | 1.18344e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2033.73 | 0.0579258 | 968.053ms | 4390 | 320 | 455.026 | 2058.59 | 0.0849373 | 2.53556 | 12.2282 | 1.92483 | 0.00183015 | 3.48804e-05 | 4.98292e-06 | 3(Loss) | true |
| simdjson (reflection) | 1344.5 | 0.0521358 | 1086.42ms | 4390 | 320 | 843.394 | 3113.9 | 0.0126433 | 3.81247 | 14.0128 | 2.27608 | 0.00626139 | 2.56264e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1245.22 | 0.0492276 | 1096.53ms | 4390 | 320 | 876.602 | 3362.16 | 0.0353321 | 4.11188 | 14.3697 | 2.43326 | 0.00337842 | 2.70501e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13175 | 0.0760944 | 765.165ms | 4390 | 4890 | 285.916 | 317.77 | 0.0498197 | 0.433339 | 1.76765 | 0.288155 | 0.000228303 | 4.89586e-05 | 2.24995e-05 | 1(Win) | true |
| simdjson (reflection) | 7989.49 | 0.069521 | 787.95ms | 4390 | 1280 | 169.876 | 524.017 | 0.0289316 | 0.682557 | 2.6 | 0.383144 | 0.000227968 | 2.91856e-05 | 4.44903e-06 | 2(Loss) | true |
| glaze | 3814.35 | 0.117747 | 845.229ms | 4390 | 4890 | 8167.61 | 1097.6 | 0.0428998 | 1.37312 | 4.70775 | 0.756037 | 0.000228769 | 6.01851e-05 | 1.53258e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14721.3 | 0.052239 | 758.548ms | 4390 | 4890 | 107.928 | 284.392 | 0.0134443 | 0.391948 | 1.64351 | 0.259681 | 0.000227837 | 3.49372e-05 | 1.09004e-05 | 1(Win) | true |
| simdjson (reflection) | 8575.13 | 0.111597 | 782.795ms | 4390 | 2560 | 759.961 | 488.229 | 0.0240884 | 0.639074 | 2.48633 | 0.356948 | 0.000228146 | 1.28132e-05 | 2.49146e-06 | 2(Loss) | true |
| glaze | 4248.64 | 0.139936 | 831.944ms | 4390 | 4890 | 9298.1 | 985.404 | 0.0357267 | 1.23716 | 4.28497 | 0.659454 | 0.000229048 | 3.97352e-05 | 7.22035e-06 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3892.9 | 0.0432173 | 1021.7ms | 11521 | 2560 | 3808.81 | 2822.39 | 0.00315547 | 1.31704 | 6.02335 | 0.882823 | 0.000662174 | 2.87179e-05 | 8.27294e-06 | 1(Win) | true |
| jsonifier | 3664.72 | 0.0856563 | 1035.28ms | 11521 | 80 | 527.604 | 2998.12 | 0.0141735 | 1.39827 | 6.01788 | 1.25727 | 0.00146255 | 2.92943e-05 | 1.08498e-05 | 2(Loss) | true |
| simdjson (reflection) | 2983.69 | 0.0249318 | 1104.48ms | 11521 | 4890 | 4121.83 | 3682.45 | 0.057048 | 1.71307 | 6.48702 | 0.974655 | 0.00215099 | 1.85844e-05 | 3.31927e-06 | 3(Loss) | true |
| glaze | 2830.96 | 0.0285568 | 1122.04ms | 11521 | 4890 | 6006.74 | 3881.11 | 0.222952 | 1.80717 | 8.56011 | 1.56445 | 0.00376208 | 2.25071e-05 | 4.93453e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2648.88 | 0.162834 | 1153.27ms | 11521 | 30 | 1368.58 | 4147.9 | 0.0482404 | 1.92778 | 6.88456 | 1.08367 | 0.00140902 | 1.73596e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4312.92 | 0.0898766 | 1020.05ms | 11521 | 80 | 419.392 | 2547.53 | 0.0657069 | 1.19197 | 5.58259 | 0.780227 | 0.000719339 | 1.95296e-05 | 0 | 1(Win) | true |
| jsonifier | 4026.34 | 0.0195739 | 1035.29ms | 11521 | 4890 | 1395.15 | 2728.85 | 0.067948 | 1.27464 | 5.57834 | 1.15467 | 0.00141392 | 1.88861e-05 | 3.26602e-06 | 2(Loss) | true |
| simdjson (reflection) | 3126.64 | 0.0704196 | 1107.31ms | 11521 | 1280 | 7838.31 | 3514.09 | 0.00731484 | 1.63589 | 6.20927 | 0.90539 | 0.002568 | 1.37656e-05 | 1.49184e-06 | 3(Loss) | true |
| glaze | 3047.76 | 0.199664 | 1116.26ms | 11521 | 30 | 1554.31 | 3605.03 | 0.0184961 | 1.67886 | 8.02995 | 1.44362 | 0.00431386 | 0.00015913 | 0.000101264 | 4(Loss) | true |
| simdjson (ondemand) | 2919.67 | 0.0407184 | 1131.35ms | 11521 | 4890 | 11481.7 | 3763.2 | 0.00518534 | 1.75172 | 6.33513 | 0.963198 | 0.00151068 | 1.24428e-05 | 1.70401e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24121.5 | 0.0443572 | 779.156ms | 11521 | 4890 | 199.622 | 455.497 | 0.332522 | 0.228438 | 0.734745 | 0.110407 | 8.6798e-05 | 1.35788e-05 | 1.65076e-06 | 1(Win) | true |
| glaze | 5952.56 | 0.174439 | 920.792ms | 11521 | 640 | 6635 | 1845.81 | 0.06218 | 0.868848 | 3.74316 | 0.506814 | 0.000125179 | 1.32909e-05 | 1.62746e-06 | 2(Loss) | true |
| simdjson (reflection) | 536.552 | 0.208716 | 2828.79ms | 11521 | 1280 | 2.33817e+06 | 20477.6 | 0.319074 | 9.4485 | 37.4458 | 6.87805 | 0.00927837 | 0.000204043 | 0.000115753 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 27992.2 | 0.202146 | 770.623ms | 11521 | 160 | 100.729 | 392.512 | 0.16907 | 0.199144 | 0.685878 | 0.0989497 | 8.6798e-05 | 9.76478e-06 | 5.42488e-07 | 1(Win) | true |
| glaze | 6870.62 | 0.143862 | 894.737ms | 11521 | 2560 | 13549.5 | 1599.17 | 0.0154401 | 0.754645 | 3.50464 | 0.455516 | 0.000154982 | 2.32931e-05 | 6.27251e-06 | 2(Loss) | true |
| simdjson (reflection) | 534.27 | 0.21489 | 2798.72ms | 11521 | 1280 | 2.49979e+06 | 20565.1 | 0.0373484 | 9.48469 | 37.4549 | 6.88078 | 0.0093375 | 7.41174e-05 | 3.51939e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3331.04 | 0.0551788 | 865.616ms | 4669 | 4890 | 2660.37 | 1336.73 | 0.127229 | 1.56955 | 6.5053 | 1.37482 | 0.000622344 | 6.6575e-05 | 3.26305e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2238.92 | 0.0342166 | 935.799ms | 4669 | 4890 | 2264.39 | 1988.77 | 0.079587 | 2.3039 | 9.27522 | 1.67081 | 0.00113436 | 7.92768e-05 | 2.80754e-05 | 2(Loss) | true |
| glaze | 2027.54 | 0.0873688 | 955.06ms | 4669 | 640 | 2356.15 | 2196.12 | 0.249533 | 2.54161 | 9.64768 | 1.82802 | 0.000804174 | 3.38001e-05 | 9.70497e-06 | 3(Loss) | true |
| simdjson (reflection) | 1759.2 | 0.0370845 | 990.564ms | 4669 | 4890 | 4308.38 | 2531.1 | 0.0250445 | 2.93629 | 12.5123 | 1.91497 | 0.00110422 | 0.00010779 | 5.05006e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1247.98 | 0.117614 | 1096.16ms | 4669 | 40 | 704.379 | 3567.93 | 0.0861103 | 4.09678 | 14.62 | 2.49711 | 0.00190619 | 9.63804e-05 | 1.60634e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3722.58 | 0.0367384 | 859.507ms | 4669 | 4890 | 944.299 | 1196.13 | 0.220429 | 1.40648 | 5.99657 | 1.24802 | 0.000584458 | 4.63397e-05 | 1.08622e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2406.15 | 0.0689014 | 926.442ms | 4669 | 1280 | 2080.99 | 1850.56 | 0.0787123 | 2.14794 | 8.82159 | 1.55729 | 0.00110536 | 3.51387e-05 | 4.68516e-06 | 2(Loss) | true |
| glaze | 2196.91 | 0.129967 | 940.756ms | 4669 | 30 | 208.166 | 2026.8 | 0.0131553 | 2.34701 | 8.93617 | 1.66588 | 0.00117798 | 2.85571e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1811.64 | 0.0465333 | 989.507ms | 4669 | 1280 | 1674.33 | 2457.83 | 0.0391453 | 2.83716 | 12.2407 | 1.84322 | 0.00110185 | 7.86437e-05 | 2.97842e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1355.64 | 0.0338683 | 1071.5ms | 4669 | 4890 | 6051.41 | 3284.59 | 0.118175 | 3.82922 | 13.8698 | 2.33498 | 0.00168483 | 7.80066e-05 | 3.77112e-05 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12068.6 | 0.0984665 | 763.683ms | 4669 | 160 | 21.117 | 368.95 | 0.0881655 | 0.471305 | 1.24866 | 0.324695 | 0.000214179 | 2.81109e-05 | 2.67723e-06 | 1(Win) | true |
| simdjson (reflection) | 7821.9 | 0.140951 | 788.311ms | 4669 | 2560 | 1648.17 | 569.261 | 0.0971911 | 0.696534 | 1.65988 | 0.224459 | 0.000214848 | 8.80977e-05 | 4.55966e-05 | 2(Loss) | true |
| glaze | 3958.03 | 0.155472 | 847.252ms | 4669 | 640 | 1957.82 | 1124.98 | 0.00861051 | 1.33938 | 3.40565 | 0.492825 | 0.000214179 | 6.32496e-05 | 3.07882e-05 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13618.6 | 0.12328 | 758.521ms | 4669 | 4890 | 794.47 | 326.958 | 0.313785 | 0.422174 | 1.12337 | 0.293425 | 0.000214266 | 4.68215e-05 | 2.3345e-05 | 1(Win) | true |
| simdjson (reflection) | 8488.47 | 0.185484 | 804.791ms | 4669 | 2560 | 2423.49 | 524.559 | 0.045073 | 0.649548 | 1.55472 | 0.200257 | 0.000215266 | 5.97358e-05 | 2.86129e-05 | 2(Loss) | true |
| glaze | 4596.17 | 0.203559 | 823.201ms | 4669 | 1280 | 4977.88 | 968.785 | 0.838127 | 1.14828 | 2.87471 | 0.373099 | 0.000214681 | 1.99119e-05 | 3.6812e-06 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3741.53 | 0.209578 | 968.484ms | 9249 | 30 | 732.326 | 2357.47 | 0.062175 | 1.37413 | 5.44145 | 0.885717 | 0.000583847 | 2.5228e-05 | 0 | 1(Win) | true |
| jsonifier | 3314.59 | 0.102049 | 1001.39ms | 9249 | 80 | 589.984 | 2661.12 | 0.0761536 | 1.57763 | 5.54979 | 1.31376 | 0.000698724 | 1.75695e-05 | 2.70299e-06 | 2(Loss) | true |
| simdjson (reflection) | 3139.22 | 0.154128 | 1017.19ms | 9249 | 640 | 12003 | 2809.79 | 0.00861869 | 1.63204 | 7.01049 | 0.996216 | 0.000577427 | 3.37874e-05 | 9.46048e-06 | 3(Loss) | true |
| glaze | 2635.28 | 0.131759 | 1066.8ms | 9249 | 30 | 583.472 | 3347.1 | 0.0318582 | 1.94255 | 7.80863 | 1.49032 | 0.00107759 | 7.20799e-05 | 2.88319e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2370.43 | 0.075646 | 1111.29ms | 9249 | 80 | 633.868 | 3721.07 | 0.262673 | 2.19675 | 8.06249 | 1.28695 | 0.000882528 | 2.4327e-05 | 8.10898e-06 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3951.96 | 0.0939195 | 960.215ms | 9249 | 160 | 703.065 | 2231.94 | 0.0100819 | 1.30349 | 5.21246 | 0.828414 | 0.000569656 | 2.36512e-05 | 6.75749e-07 | 1(Win) | true |
| jsonifier | 3443.18 | 0.0417078 | 994.124ms | 9249 | 4890 | 5582.3 | 2561.74 | 0.232676 | 1.49345 | 5.29452 | 1.25008 | 0.000777357 | 3.82731e-05 | 1.69808e-05 | 2(Loss) | true |
| simdjson (reflection) | 3224.77 | 0.0306366 | 1014.3ms | 9249 | 4890 | 3433.85 | 2735.25 | 0.0137027 | 1.59319 | 6.87339 | 0.959996 | 0.000685732 | 2.62671e-05 | 1.14311e-05 | 3(Loss) | true |
| glaze | 2807.55 | 0.0543887 | 1049.26ms | 9249 | 2560 | 7474.69 | 3141.72 | 0.00872905 | 1.83055 | 7.45086 | 1.41086 | 0.00102541 | 3.31962e-05 | 1.55e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2465.92 | 0.0293061 | 1099.24ms | 9249 | 4890 | 5373.49 | 3576.98 | 0.130165 | 2.07555 | 7.69305 | 1.20748 | 0.000778463 | 3.85826e-05 | 1.54994e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20913.5 | 0.0304527 | 772.821ms | 9249 | 320 | 5.27884 | 421.762 | 0.00889205 | 0.264557 | 0.702346 | 0.160774 | 0.000108796 | 1.18256e-05 | 6.75749e-07 | 1(Win) | true |
| glaze | 3497.03 | 0.173145 | 990.033ms | 9249 | 4890 | 93264.9 | 2522.29 | 0.201017 | 1.47023 | 3.47335 | 0.453995 | 0.000326659 | 3.03576e-05 | 1.12321e-05 | 2(Loss) | true |
| simdjson (reflection) | 520.88 | 0.226425 | 2428.87ms | 9249 | 640 | 940902 | 16933.9 | 0.0223068 | 9.71975 | 39.5411 | 7.74922 | 0.00685175 | 0.000133122 | 6.43651e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23442.5 | 0.0735094 | 783.024ms | 9249 | 80 | 6.12009 | 376.262 | 0.0232496 | 0.238328 | 0.647421 | 0.148124 | 0.00010812 | 1.0812e-05 | 0 | 1(Win) | true |
| glaze | 3997.49 | 0.346094 | 958.962ms | 9249 | 1280 | 74647.3 | 2206.52 | 0.3894 | 1.28727 | 3.20251 | 0.393772 | 0.000337621 | 1.88365e-05 | 4.22343e-06 | 2(Loss) | true |
| simdjson (reflection) | 526.085 | 0.0792531 | 2422.71ms | 9249 | 4890 | 863413 | 16766.4 | 0.345161 | 9.63052 | 39.4443 | 7.72824 | 0.00690616 | 0.000116411 | 5.05222e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 828.162 | 0.0583543 | 1274.24ms | 4604 | 640 | 6125.85 | 5301.76 | 0.132029 | 6.26715 | 23.51 | 5.04931 | 0.003069 | 0.000154757 | 9.33292e-05 | 1(Win) | true |
| simdjson (reflection) | 745.04 | 0.0207681 | 1341.17ms | 4604 | 4890 | 7325.09 | 5893.27 | 0.0557321 | 6.83098 | 28.1901 | 5.07016 | 0.0042044 | 0.000114731 | 4.14861e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 714.594 | 0.0607038 | 1357.13ms | 4604 | 640 | 8903.55 | 6144.35 | 0.153552 | 7.15768 | 26.853 | 5.38988 | 0.00584953 | 6.17669e-05 | 1.01814e-05 | 3(Loss) | true |
| glaze | 622.045 | 0.118068 | 1441.92ms | 4604 | 2560 | 177801 | 7058.52 | 0.0365217 | 8.18574 | 33.5098 | 6.96091 | 0.00700011 | 7.55118e-05 | 2.28232e-05 | 4(Loss) | true |
| simdjson (ondemand) | 566.624 | 0.0346816 | 1516.86ms | 4604 | 2560 | 18489.3 | 7748.91 | 0.062876 | 8.96399 | 34.7854 | 6.84058 | 0.00859494 | 8.2469e-05 | 3.16471e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1009.84 | 0.0453665 | 1265.48ms | 4604 | 2560 | 9960.43 | 4347.95 | 0.102547 | 5.06461 | 19.0552 | 4.0328 | 0.00227358 | 9.25656e-05 | 3.57196e-05 | 1(Win) | true |
| simdjson (reflection) | 855.561 | 0.0629483 | 1345.02ms | 4604 | 80 | 834.885 | 5131.98 | 0.0204558 | 5.96091 | 26.4457 | 4.63662 | 0.00177834 | 6.51607e-05 | 2.71503e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 853.65 | 0.0340652 | 1346.55ms | 4604 | 2560 | 7859.08 | 5143.46 | 0.0287082 | 5.99858 | 22.6277 | 4.42702 | 0.00520429 | 5.93064e-05 | 1.79871e-05 | 3(Loss) | true |
| glaze | 720.986 | 0.0292043 | 1436.71ms | 4604 | 4890 | 15467.5 | 6089.88 | 0.0129603 | 7.06471 | 28.9303 | 5.90986 | 0.00606781 | 6.08522e-05 | 1.43913e-05 | 4(Loss) | true |
| simdjson (ondemand) | 628.084 | 0.0400409 | 1540.69ms | 4604 | 2560 | 20057.7 | 6990.65 | 0.320626 | 8.10552 | 31.5988 | 6.11175 | 0.0075091 | 7.88207e-05 | 2.10415e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1477.17 | 0.0604629 | 1053.31ms | 4918 | 1280 | 4717.43 | 3175.11 | 0.0985707 | 3.47359 | 11.5382 | 1.38654 | 0.000488639 | 5.25811e-05 | 1.4297e-05 | 1(Win) | true |
| jsonifier | 1467.34 | 0.480478 | 1034.52ms | 4604 | 320 | 66146 | 2992.29 | 0.0671969 | 3.49276 | 8.92941 | 0.550174 | 0.000316301 | 4.00467e-05 | 1.01814e-05 | 2(Loss) | true |
| glaze | 1174.12 | 0.116523 | 1112.15ms | 4604 | 2560 | 48608.3 | 3739.58 | 0.109164 | 4.36258 | 12.7533 | 1.12511 | 0.000649486 | 8.69658e-05 | 3.4956e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1517.82 | 0.229012 | 1021.91ms | 4604 | 1280 | 56176.9 | 2892.78 | 0.0317972 | 3.37326 | 8.80778 | 0.520635 | 0.000300859 | 8.82385e-05 | 2.37565e-05 | 1(Win) | true |
| simdjson (reflection) | 1503.19 | 0.0776887 | 1044.48ms | 4918 | 640 | 3760.52 | 3120.15 | 0.0599571 | 3.44311 | 11.4296 | 1.36092 | 0.000488639 | 2.89117e-05 | 5.40108e-06 | 2(Loss) | true |
| glaze | 1259.93 | 0.0535646 | 1086.98ms | 4604 | 4890 | 17039 | 3484.9 | 0.0953526 | 4.07847 | 12.2129 | 1.00891 | 0.000566858 | 7.51991e-05 | 2.78499e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 3394.18 | 0.0258181 | 1433.05ms | 24579 | 2560 | 8138.55 | 6906.04 | 0.0011878 | 1.49751 | 6.39635 | 0.992921 | 0.000839338 | 2.80982e-05 | 1.32545e-05 | 1(Win) | true |
| jsonifier (two-stage) | 3316.86 | 0.0791565 | 1453.49ms | 24579 | 40 | 1251.72 | 7067.02 | 0.095776 | 1.53448 | 5.97437 | 1.04463 | 0.00117478 | 3.35652e-05 | 5.08564e-06 | 2(Loss) | true |
| jsonifier | 2982.95 | 0.174312 | 1522.7ms | 24579 | 80 | 15010.1 | 7858.12 | 0.000954435 | 1.70233 | 6.21148 | 1.42125 | 0.00119614 | 9.66272e-06 | 3.05139e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2682.94 | 0.0198586 | 1617ms | 24579 | 4890 | 14720.1 | 8736.81 | 0.103896 | 1.8908 | 7.62183 | 1.323 | 0.00158858 | 1.15815e-05 | 2.88706e-06 | 4(Loss) | true |
| glaze | 2205.71 | 0.0234273 | 1805.03ms | 24579 | 2560 | 15867.8 | 10627.1 | 0.192655 | 2.30142 | 10.1338 | 1.95484 | 0.00386644 | 2.05333e-05 | 9.01112e-06 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3906.94 | 0.100497 | 1446.32ms | 24579 | 30 | 1090.64 | 5999.67 | 0.0567019 | 1.32895 | 5.18382 | 0.864559 | 0.00113647 | 2.71234e-05 | 5.42469e-06 | 1(Win) | true |
| simdjson (reflection) | 3840.33 | 0.100587 | 1445.54ms | 24579 | 30 | 1130.82 | 6103.73 | 0.00163831 | 1.32649 | 6.04151 | 0.906044 | 0.000378372 | 8.81511e-05 | 3.11919e-05 | 2(Loss) | true |
| jsonifier | 3478.22 | 0.0266271 | 1515.83ms | 24579 | 320 | 1030.42 | 6739.18 | 0.0350903 | 1.46334 | 5.41686 | 1.24033 | 0.00102946 | 7.7556e-06 | 8.89987e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2935.84 | 0.0339199 | 1635.74ms | 24579 | 4890 | 35865.9 | 7984.21 | 0.0453627 | 1.73144 | 7.00073 | 1.18089 | 0.00160706 | 1.47681e-05 | 4.99204e-06 | 4(Loss) | true |
| glaze | 2423.49 | 0.0682224 | 1799.25ms | 24579 | 640 | 27866.4 | 9672.15 | 0.0119397 | 2.09404 | 9.32924 | 1.76999 | 0.00402643 | 1.27141e-05 | 3.55995e-06 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7092.56 | 0.211756 | 1061.55ms | 24579 | 640 | 31345.4 | 3304.92 | 0.0395873 | 0.721895 | 1.77041 | 0.104886 | 6.47784e-05 | 7.94632e-06 | 1.0807e-06 | 1(Win) | true |
| glaze | 3849.3 | 0.106656 | 1349.76ms | 24579 | 2560 | 107988 | 6089.51 | 0.0801456 | 1.33074 | 3.99097 | 0.453314 | 0.000305472 | 3.88893e-05 | 2.30125e-05 | 2(Loss) | true |
| simdjson (reflection) | 532.05 | 0.256492 | 5213.91ms | 24893 | 640 | 8.3826e+06 | 44619.5 | 0.00192604 | 9.54943 | 36.9013 | 6.05962 | 0.00625402 | 0.000318363 | 0.000227536 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7243.86 | 0.0724148 | 1060.72ms | 24579 | 4890 | 26850.5 | 3235.89 | 0.284774 | 0.706606 | 1.75064 | 0.100289 | 5.67845e-05 | 1.37947e-05 | 4.5178e-06 | 1(Win) | true |
| glaze | 4320.14 | 0.0791217 | 1281.44ms | 24579 | 4890 | 90122.4 | 5425.83 | 0.254254 | 1.18574 | 3.83807 | 0.419057 | 0.000248404 | 1.55752e-05 | 4.9754e-06 | 2(Loss) | true |
| simdjson (reflection) | 531.485 | 0.091119 | 5223.46ms | 24893 | 4890 | 8.10027e+06 | 44666.9 | 0.139331 | 9.5118 | 36.9166 | 6.06327 | 0.00638845 | 9.96576e-05 | 5.54274e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 914.235 | 0.0503711 | 1212.5ms | 4604 | 320 | 1872.7 | 4802.61 | 0.16124 | 5.57802 | 21.7389 | 4.57846 | 0.00415739 | 0.000107922 | 2.37565e-05 | 1(Win) | true |
| jsonifier (two-stage) | 760.908 | 0.0323204 | 1320.54ms | 4604 | 4890 | 17008.6 | 5770.36 | 0.0289151 | 6.69554 | 25.9713 | 5.14878 | 0.00534314 | 9.62087e-05 | 4.37514e-05 | 2(Loss) | true |
| simdjson (reflection) | 752.398 | 0.0368616 | 1328.32ms | 4604 | 2560 | 11845.8 | 5835.63 | 0.123488 | 6.7653 | 28.1138 | 5.07754 | 0.0044115 | 0.000112334 | 5.20946e-05 | 3(Loss) | true |
| glaze | 626.213 | 0.0628316 | 1437.44ms | 4604 | 2560 | 49684.7 | 7011.53 | 0.00818896 | 8.11289 | 32.5378 | 6.79181 | 0.00896469 | 0.000157641 | 7.46633e-05 | 4(Loss) | true |
| simdjson (ondemand) | 571.314 | 0.0448596 | 1510.43ms | 4604 | 1280 | 15213.9 | 7685.29 | 0.223932 | 8.88924 | 34.1173 | 6.69331 | 0.00907363 | 7.02514e-05 | 1.69689e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1150.94 | 0.0357827 | 1207.83ms | 4604 | 4890 | 9112.21 | 3814.91 | 0.0426608 | 4.44523 | 17.5672 | 3.62577 | 0.00298616 | 6.71151e-05 | 2.00324e-05 | 1(Win) | true |
| jsonifier (two-stage) | 913.046 | 0.0994736 | 1312.5ms | 4604 | 4890 | 111895 | 4808.87 | 0.278156 | 5.59695 | 21.7524 | 4.18745 | 0.0046639 | 7.03132e-05 | 2.08319e-05 | 2(Loss) | true |
| simdjson (reflection) | 852.196 | 0.0651789 | 1345.37ms | 4604 | 4890 | 55146 | 5152.24 | 0.0241133 | 5.97411 | 25.7619 | 4.51765 | 0.00350491 | 8.48378e-05 | 3.19807e-05 | 3(Loss) | true |
| glaze | 727.64 | 0.0714988 | 1427.72ms | 4604 | 1280 | 23825.7 | 6034.19 | 0.00871413 | 7.00633 | 28.2798 | 5.80973 | 0.00755118 | 8.84082e-05 | 3.39379e-05 | 4(Loss) | true |
| simdjson (ondemand) | 628.196 | 0.0226903 | 1537.88ms | 4604 | 4890 | 12299 | 6989.4 | 0.190732 | 8.1019 | 31.656 | 6.12033 | 0.00550091 | 7.02243e-05 | 1.42581e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1503.92 | 0.163499 | 1055.77ms | 4918 | 80 | 2079.91 | 3118.62 | 0.00881721 | 3.47072 | 11.536 | 1.38796 | 0.000556629 | 4.8292e-05 | 2.79585e-05 | 1(Win) | true |
| jsonifier | 1498.1 | 0.0994899 | 1031.73ms | 4604 | 2560 | 21766.3 | 2930.85 | 0.103186 | 3.43923 | 8.91855 | 0.548437 | 0.000289999 | 7.34755e-05 | 2.35868e-05 | 2(Loss) | true |
| glaze | 1180.53 | 0.083989 | 1114.72ms | 4604 | 2560 | 24980.4 | 3719.27 | 0.0834585 | 4.34037 | 12.7211 | 1.12402 | 0.000659668 | 6.76212e-05 | 2.83381e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1532.7 | 0.117523 | 1026.01ms | 4604 | 4890 | 55425.9 | 2864.7 | 0.0212531 | 3.33887 | 8.79692 | 0.518898 | 0.000300219 | 7.92411e-05 | 2.39411e-05 | 1(Win) | true |
| simdjson (reflection) | 1500.66 | 0.0721013 | 1043.24ms | 4918 | 160 | 812.495 | 3125.41 | 0.0868639 | 3.41485 | 11.4274 | 1.36234 | 0.000549004 | 3.55836e-05 | 6.35421e-06 | 2(Loss) | true |
| glaze | 1286.36 | 0.0926726 | 1081.8ms | 4604 | 1280 | 12807.4 | 3413.3 | 0.0253539 | 3.99028 | 12.2085 | 1.00804 | 0.000765808 | 6.9403e-05 | 2.27384e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3475.51 | 0.0830872 | 1411.37ms | 24579 | 640 | 20097.4 | 6744.44 | 0.086651 | 1.46728 | 5.82229 | 1.00208 | 0.00118654 | 4.62158e-05 | 2.90517e-05 | 1(Win) | true |
| simdjson (reflection) | 3463.41 | 0.0781018 | 1419.87ms | 24579 | 40 | 1117.64 | 6768 | 0.00197009 | 1.46997 | 6.3632 | 0.990846 | 0.000763863 | 2.03426e-05 | 1.01713e-06 | 2(Loss) | true |
| jsonifier | 3183.78 | 0.0422339 | 1478.21ms | 24579 | 4890 | 47279.7 | 7362.44 | 0.0291761 | 1.59756 | 6.06608 | 1.37646 | 0.00113673 | 3.84637e-05 | 2.32047e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2658.45 | 0.118285 | 1612.32ms | 24579 | 30 | 3263.25 | 8817.3 | 0.00529235 | 1.91112 | 7.47451 | 1.28988 | 0.00203697 | 1.89864e-05 | 1.22055e-05 | 4(Loss) | true |
| glaze | 2220.64 | 0.0774989 | 1799.43ms | 24579 | 160 | 10707.3 | 10555.7 | 0.280909 | 2.28439 | 10.0472 | 1.93556 | 0.00383356 | 6.35705e-06 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4056.94 | 0.0559056 | 1408.02ms | 24579 | 2560 | 26710.5 | 5777.84 | 0.0570391 | 1.25926 | 5.03385 | 0.822654 | 0.00104225 | 2.64136e-05 | 1.47643e-05 | 1(Win) | true |
| simdjson (reflection) | 3862.37 | 0.105172 | 1436.47ms | 24579 | 160 | 6518.44 | 6068.9 | 0.0140039 | 1.31782 | 5.97528 | 0.896466 | 0.000478813 | 3.00053e-05 | 1.39855e-05 | 2(Loss) | true |
| jsonifier | 3670.15 | 0.0364629 | 1476.79ms | 24579 | 4890 | 26519.9 | 6386.75 | 0.054559 | 1.38625 | 5.27707 | 1.19679 | 0.000938437 | 1.90363e-05 | 5.46629e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2951.32 | 0.0485122 | 1635.73ms | 24579 | 2560 | 38004.9 | 7942.34 | 0.0933695 | 1.72407 | 7.00736 | 1.18167 | 0.00118093 | 1.83401e-05 | 6.61133e-06 | 4(Loss) | true |
| glaze | 2428.99 | 0.0899525 | 1795.8ms | 24579 | 30 | 2260.62 | 9650.27 | 0.0642882 | 2.09163 | 9.26128 | 1.75516 | 0.00359385 | 2.03426e-05 | 9.4932e-06 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6553.8 | 0.164039 | 1105.3ms | 24579 | 640 | 22030.1 | 3576.6 | 0.0490361 | 0.795015 | 1.76293 | 0.104805 | 6.78298e-05 | 3.41374e-05 | 2.1169e-05 | 1(Win) | true |
| glaze | 3798.69 | 0.147024 | 1361.72ms | 24579 | 1280 | 105353 | 6170.64 | 0.358504 | 1.34187 | 3.99034 | 0.451976 | 0.000333427 | 1.81494e-05 | 7.43775e-06 | 2(Loss) | true |
| simdjson (reflection) | 497.262 | 0.0768467 | 5521.35ms | 24893 | 4890 | 6.58178e+06 | 47741.1 | 0.128937 | 10.1621 | 36.9401 | 6.07303 | 0.00728468 | 0.00021743 | 0.000137094 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6516.45 | 0.0838868 | 1099.04ms | 24579 | 2560 | 23309.6 | 3597.11 | 0.296295 | 0.785278 | 1.74315 | 0.100208 | 6.43811e-05 | 1.47484e-05 | 4.89493e-06 | 1(Win) | true |
| glaze | 4235.65 | 0.144849 | 1311.07ms | 24579 | 2560 | 164496 | 5534.06 | 0.232476 | 1.20593 | 3.84096 | 0.417918 | 0.000347715 | 2.03902e-05 | 8.77273e-06 | 2(Loss) | true |
| simdjson (reflection) | 497.432 | 0.0844428 | 5532.53ms | 24893 | 4890 | 7.94183e+06 | 47724.7 | 0.167028 | 10.1227 | 36.9273 | 6.0693 | 0.00708323 | 0.000183386 | 0.000120253 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1008.45 | 0.0945254 | 841.471ms | 1181 | 1280 | 1426.6 | 1116.86 | 0.0621549 | 5.21205 | 19.6495 | 4.00508 | 0.00321827 | 0.000273867 | 0.000107166 | 1(Win) | true |
| jsonifier (two-stage) | 888.197 | 0.0404249 | 858.913ms | 1181 | 640 | 168.174 | 1268.06 | 0.215415 | 5.87306 | 22.7528 | 4.29382 | 0.00254287 | 9.65813e-05 | 1.32303e-06 | 2(Loss) | true |
| simdjson (reflection) | 871.596 | 0.0907546 | 862.872ms | 1181 | 4890 | 6725.37 | 1292.22 | 0.138498 | 5.98784 | 24.5987 | 4.09145 | 0.0025655 | 0.000203633 | 6.09514e-05 | 3(Loss) | true |
| glaze | 819.381 | 0.0937428 | 868.863ms | 1181 | 2560 | 4250.54 | 1374.56 | 0.0683557 | 6.39948 | 24.696 | 4.91363 | 0.00378652 | 0.000371441 | 0.000175632 | 4(Loss) | true |
| simdjson (ondemand) | 736.511 | 0.0627697 | 884.44ms | 1181 | 4890 | 4505.57 | 1529.22 | 0.451208 | 7.03183 | 28.0567 | 4.97714 | 0.00394141 | 0.000198958 | 5.31593e-05 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1210.35 | 0.0829741 | 838.938ms | 1181 | 2560 | 1526.16 | 930.546 | 0.0564924 | 4.36417 | 16.486 | 3.28112 | 0.00169745 | 0.000111465 | 2.41453e-05 | 1(Win) | true |
| glaze | 1122.31 | 0.081356 | 842.854ms | 1181 | 320 | 213.308 | 1003.55 | 0.0392203 | 4.68821 | 18.2549 | 3.45216 | 0.00241056 | 0.000108489 | 5.29213e-06 | 2(Loss) | true |
| simdjson (reflection) | 1031.49 | 0.0862631 | 856.396ms | 1181 | 320 | 283.903 | 1091.91 | 0.0738933 | 5.09443 | 21.3446 | 3.34547 | 0.00171465 | 7.67358e-05 | 5.29213e-06 | 3(Loss) | true |
| jsonifier (two-stage) | 1026.06 | 0.0864827 | 859.808ms | 1181 | 640 | 576.762 | 1097.69 | 0.0459561 | 5.14773 | 19.602 | 3.57494 | 0.00187077 | 0.000171994 | 4.1014e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1001.61 | 0.063505 | 858.35ms | 1181 | 2560 | 1305.45 | 1124.48 | 0.0236512 | 5.24339 | 21.3878 | 3.47756 | 0.00191046 | 0.000163725 | 4.69676e-05 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2176.58 | 0.0925033 | 776.745ms | 1181 | 4890 | 1120.41 | 517.459 | 0.0240337 | 2.51943 | 7.70619 | 0.703643 | 0.000868558 | 0.000173504 | 6.96093e-05 | 1(Win) | true |
| glaze | 1392.02 | 0.126461 | 812.49ms | 1181 | 320 | 335.021 | 809.103 | 0.0528855 | 3.81326 | 10.2955 | 0.918713 | 0.00116956 | 4.49831e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 1370.18 | 0.0643993 | 809.089ms | 1187 | 320 | 90.5857 | 826.178 | 0.0866938 | 3.88779 | 13.3496 | 1.45072 | 0.00084246 | 2.36942e-05 | 0 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2311.6 | 0.303414 | 770.232ms | 1181 | 30 | 65.5644 | 487.233 | 0.143875 | 2.36317 | 7.29128 | 0.605419 | 0.00084674 | 0.000169348 | 0 | 1(Win) | true |
| glaze | 1466.02 | 0.0676135 | 801.899ms | 1181 | 4890 | 1319.47 | 768.265 | 0.106685 | 3.6579 | 9.73582 | 0.790857 | 0.00118215 | 9.83534e-05 | 1.93936e-05 | 2(Loss) | true |
| simdjson (reflection) | 1407.93 | 0.0372688 | 807.679ms | 1187 | 320 | 28.7329 | 804.025 | 0.0474402 | 3.84211 | 12.9183 | 1.34878 | 0.00084246 | 0.000102675 | 2.63269e-06 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1780.44 | 0.0578234 | 864.844ms | 2496 | 2560 | 1529.97 | 1336.96 | 0.0506958 | 2.92237 | 12.3293 | 1.94992 | 0.00120865 | 9.57782e-05 | 1.92495e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1710.86 | 0.0467907 | 874.7ms | 2496 | 4890 | 2072.46 | 1391.33 | 0.10683 | 3.03931 | 11.7007 | 2.11499 | 0.00120577 | 9.39745e-05 | 2.52346e-05 | 2(Loss) | true |
| jsonifier | 1518.35 | 0.0314925 | 890.476ms | 2496 | 4890 | 1191.99 | 1567.74 | 0.0110034 | 3.41966 | 12.6406 | 2.83814 | 0.00198682 | 7.82438e-05 | 2.0073e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1511.89 | 0.0470775 | 887.402ms | 2496 | 4890 | 2686.49 | 1574.43 | 0.2256 | 3.43317 | 13.9655 | 2.36899 | 0.00188047 | 9.37287e-05 | 2.84299e-05 | 4(Loss) | true |
| glaze | 1401.01 | 0.169387 | 902.813ms | 2496 | 4890 | 40502.3 | 1699.04 | 0.00857952 | 3.73608 | 15.1279 | 3.08576 | 0.00274951 | 0.000154767 | 7.84077e-05 | 5(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2090.02 | 0.0679964 | 860.757ms | 2496 | 2560 | 1535.32 | 1138.92 | 0.17352 | 2.50698 | 10.7898 | 1.59699 | 0.000808638 | 3.34911e-05 | 3.91251e-06 | 1(Win) | true |
| simdjson (ondemand) | 2020.04 | 0.0761983 | 862.434ms | 2496 | 4890 | 3942.48 | 1178.38 | 0.0406551 | 2.59783 | 10.8101 | 1.65946 | 0.000809475 | 9.07792e-05 | 3.15433e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1956.35 | 0.0429824 | 871.645ms | 2496 | 1280 | 350.095 | 1216.74 | 0.156232 | 2.67483 | 10.2099 | 1.77484 | 0.00103384 | 8.23192e-05 | 1.6589e-05 | 3(Loss) | true |
| glaze | 1802.61 | 0.0525847 | 878.5ms | 2496 | 4890 | 2357.84 | 1320.51 | 0.0126055 | 2.89329 | 12.0493 | 2.39423 | 0.00206826 | 8.64369e-05 | 3.17072e-05 | 4(Loss) | true |
| jsonifier | 1714.9 | 0.137591 | 889.374ms | 2496 | 160 | 583.595 | 1388.05 | 0.156941 | 3.0477 | 11.1406 | 2.498 | 0.00145232 | 7.76242e-05 | 1.7528e-05 | 5(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4387.98 | 0.157478 | 786.777ms | 2496 | 160 | 116.767 | 542.475 | 0.0161324 | 1.23968 | 3.71194 | 0.334936 | 0.000400641 | 3.00481e-05 | 0 | 1(Win) | true |
| glaze | 2061.83 | 0.143519 | 846.563ms | 2507 | 640 | 1772.55 | 1159.58 | 0.164662 | 2.53799 | 7.12884 | 0.83925 | 0.000561553 | 5.48464e-05 | 3.11627e-06 | 2(Loss) | true |
| simdjson (reflection) | 297.742 | 0.0633032 | 1551.08ms | 2502 | 1280 | 32942.4 | 8013.96 | 0.151595 | 17.0522 | 61.7897 | 9.33839 | 0.00939467 | 0.000176734 | 5.55805e-05 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4853.99 | 0.0767468 | 779.997ms | 2496 | 2560 | 362.62 | 490.395 | 0.00541685 | 1.12679 | 3.50441 | 0.28726 | 0.000400954 | 4.02206e-05 | 1.0955e-05 | 1(Win) | true |
| glaze | 2267.4 | 0.0698226 | 838.645ms | 2507 | 4890 | 2650.64 | 1054.45 | 0.0611025 | 2.31468 | 6.44436 | 0.687277 | 0.000693029 | 4.46194e-05 | 1.06043e-05 | 2(Loss) | true |
| simdjson (reflection) | 297.816 | 0.0289035 | 1550.19ms | 2502 | 4890 | 26223.3 | 8011.97 | 0.119718 | 17.0573 | 61.793 | 9.33973 | 0.00849848 | 0.000316638 | 0.000160608 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2212.71 | 0.0268474 | 949.89ms | 4926 | 640 | 207.935 | 2123.1 | 0.0609732 | 2.32786 | 10.446 | 1.85302 | 0.000525591 | 2.75959e-05 | 5.39231e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1711.8 | 0.0458998 | 1013.84ms | 4926 | 2560 | 4062.04 | 2744.36 | 0.00807117 | 2.99466 | 13.0187 | 2.189 | 0.00469519 | 5.93154e-05 | 1.90317e-05 | 2(Loss) | true |
| glaze | 1472.53 | 0.0793394 | 1059.55ms | 4926 | 640 | 4100.34 | 3190.3 | 0.186302 | 3.47504 | 15.3871 | 2.94154 | 0.00169414 | 2.91819e-05 | 3.17194e-07 | 3(Loss) | true |
| simdjson (reflection) | 1272.96 | 0.0966193 | 1111.35ms | 4926 | 2560 | 32548.3 | 3690.46 | 0.116846 | 4.0097 | 14.8886 | 2.47381 | 0.0047419 | 6.558e-05 | 2.06969e-05 | 4(Loss) | true |
| simdjson (ondemand) | 902.943 | 0.126701 | 1263.58ms | 4926 | 160 | 6952.57 | 5202.76 | 0.0290626 | 5.63944 | 17.746 | 3.11064 | 0.00392941 | 3.17194e-05 | 5.07511e-06 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2726.17 | 0.0422597 | 951.142ms | 4926 | 4890 | 2593.25 | 1723.22 | 0.00648234 | 1.90328 | 8.77994 | 1.46772 | 0.000219859 | 4.28842e-05 | 6.64227e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2035.32 | 0.0535017 | 1008.39ms | 4926 | 4890 | 7457.04 | 2308.13 | 0.00418919 | 2.5302 | 11.3528 | 1.8039 | 0.00427729 | 6.62152e-05 | 1.55263e-05 | 2(Loss) | true |
| glaze | 1866.78 | 0.0421388 | 1024.27ms | 4926 | 1280 | 1439.39 | 2516.53 | 0.139679 | 2.75359 | 12.8055 | 2.41413 | 0.00132508 | 3.01335e-05 | 3.80633e-06 | 3(Loss) | true |
| simdjson (reflection) | 1399.61 | 0.188203 | 1120.38ms | 4926 | 2560 | 102157 | 3356.51 | 0.0462971 | 3.65307 | 14.0656 | 2.25985 | 0.00369024 | 7.54923e-05 | 1.5146e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1052.12 | 0.0238524 | 1222.67ms | 4926 | 4890 | 5546.59 | 4465.06 | 0.0990597 | 4.8606 | 15.188 | 2.60171 | 0.00425608 | 5.28891e-05 | 1.33261e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12385.6 | 0.149198 | 764.807ms | 4926 | 2560 | 819.823 | 379.296 | 0.140155 | 0.453075 | 1.77629 | 0.279537 | 0.000203242 | 3.75875e-05 | 8.16776e-06 | 1(Win) | true |
| simdjson (reflection) | 7649.56 | 0.081977 | 799.262ms | 4926 | 640 | 162.211 | 614.127 | 0.0506052 | 0.705081 | 2.5881 | 0.342063 | 0.000203004 | 2.50584e-05 | 4.44072e-06 | 2(Loss) | true |
| glaze | 3736.64 | 0.100837 | 861.833ms | 4926 | 4890 | 7859.22 | 1257.23 | 0.0813762 | 1.39855 | 6.11652 | 0.987414 | 0.000204374 | 3.86082e-05 | 3.69476e-06 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14063.8 | 0.279779 | 761.558ms | 4926 | 320 | 279.488 | 334.034 | 0.107702 | 0.405846 | 1.66971 | 0.25335 | 0.000204273 | 2.15692e-05 | 2.53756e-06 | 1(Win) | true |
| simdjson (reflection) | 8401.93 | 0.0954709 | 792.362ms | 4926 | 1280 | 364.74 | 559.134 | 0.0409562 | 0.651823 | 2.47462 | 0.314454 | 0.000203639 | 2.17278e-05 | 3.01335e-06 | 2(Loss) | true |
| glaze | 4552.09 | 0.110468 | 834.304ms | 4926 | 4890 | 6355.43 | 1032.01 | 0.114747 | 1.1615 | 5.5745 | 0.871904 | 0.000209232 | 4.20124e-05 | 1.0088e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3031.66 | 0.0430855 | 1036.26ms | 9463 | 2560 | 4211.13 | 2976.79 | 0.0263296 | 1.70413 | 7.39522 | 1.15281 | 0.00231626 | 2.74507e-05 | 6.23316e-06 | 1(Win) | true |
| jsonifier | 2822.29 | 0.123162 | 1062.99ms | 9463 | 40 | 620.394 | 3197.62 | 0.00651483 | 1.84789 | 7.52647 | 1.5382 | 0.00107788 | 3.69862e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 2276.71 | 0.0907726 | 1164.17ms | 9463 | 320 | 4142.86 | 3963.88 | 0.039718 | 2.24317 | 8.40896 | 1.3166 | 0.00240872 | 2.24559e-05 | 6.9349e-06 | 3(Loss) | true |
| glaze | 2071.01 | 0.0860057 | 1173.49ms | 9463 | 320 | 4494.69 | 4357.6 | 0.0246756 | 2.46322 | 10.6948 | 2.07735 | 0.00239155 | 4.55722e-05 | 1.68419e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1640.72 | 0.172325 | 1290.59ms | 9463 | 30 | 2695.28 | 5500.4 | 0.0405866 | 3.10544 | 9.89644 | 1.6481 | 0.00211349 | 6.34048e-05 | 1.409e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3495.66 | 0.0327436 | 1039.16ms | 9463 | 4890 | 3494.29 | 2581.66 | 0.00727724 | 1.47249 | 6.52806 | 0.952341 | 0.00219548 | 2.84176e-05 | 2.22587e-06 | 1(Win) | true |
| jsonifier | 3154.3 | 0.0382757 | 1065.03ms | 9463 | 4890 | 5864.17 | 2861.05 | 0.0154093 | 1.63444 | 6.65952 | 1.33774 | 0.000971883 | 4.90988e-05 | 2.12214e-05 | 2(Loss) | true |
| simdjson (reflection) | 2495.03 | 0.032648 | 1143.51ms | 9463 | 2560 | 3569.93 | 3617.04 | 0.0493244 | 2.04914 | 8.00296 | 1.21008 | 0.00202082 | 4.08664e-05 | 6.76979e-06 | 3(Loss) | true |
| glaze | 2455.82 | 0.0573899 | 1140.35ms | 9463 | 1280 | 5693.05 | 3674.79 | 0.185025 | 2.08576 | 9.35359 | 1.80313 | 0.00285025 | 2.32815e-05 | 6.19188e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1901.22 | 0.0491629 | 1251.15ms | 9463 | 4890 | 26630.4 | 4746.75 | 0.0464578 | 2.68597 | 8.62247 | 1.39482 | 0.00229185 | 4.04114e-05 | 1.40467e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22983.1 | 0.446812 | 769.699ms | 9463 | 80 | 246.252 | 392.663 | 0.271323 | 0.246146 | 0.987319 | 0.145408 | 0.000105675 | 6.60467e-06 | 0 | 1(Win) | true |
| glaze | 4517.82 | 0.133865 | 940.77ms | 9463 | 1280 | 9152.63 | 1997.56 | 0.0569902 | 1.1433 | 4.70084 | 0.707915 | 0.000108069 | 2.84826e-05 | 8.42096e-06 | 2(Loss) | true |
| simdjson (reflection) | 537.856 | 0.0575945 | 2458.09ms | 9463 | 4890 | 456663 | 16778.9 | 0.074452 | 9.42633 | 39.1396 | 7.44716 | 0.00945121 | 0.0002276 | 0.000131197 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 25423.3 | 0.107428 | 762.881ms | 9463 | 640 | 93.0698 | 354.975 | 0.205577 | 0.221102 | 0.928458 | 0.131882 | 0.000105675 | 4.62327e-06 | 8.25584e-07 | 1(Win) | true |
| glaze | 5541.12 | 0.223594 | 900.111ms | 9463 | 640 | 8487.14 | 1628.66 | 0.152389 | 0.93479 | 4.3724 | 0.634577 | 0.000153228 | 1.61814e-05 | 2.14652e-06 | 2(Loss) | true |
| simdjson (reflection) | 543.716 | 0.0768242 | 2417.82ms | 9463 | 2560 | 416246 | 16598 | 0.0873512 | 9.32711 | 38.7257 | 7.36424 | 0.0101062 | 6.9349e-05 | 3.24042e-05 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 5599.28 | 0.0816445 | 779.841ms | 2821 | 4890 | 752.496 | 480.475 | 0.166627 | 0.987245 | 3.5771 | 0.479972 | 0.000378769 | 5.01642e-05 | 6.74172e-06 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 5588.67 | 0.093477 | 781.26ms | 2821 | 320 | 64.7961 | 481.387 | 0.00908749 | 0.980334 | 3.5771 | 0.479972 | 0.000354484 | 1.8832e-05 | 1.10776e-06 | 1(Tie) | true |
| simdjson (ondemand) | 4691.86 | 0.199897 | 802.789ms | 2821 | 80 | 105.104 | 573.4 | 0.10453 | 1.16149 | 4.53598 | 0.696562 | 0.000735555 | 0.000124069 | 8.86211e-06 | 3(Loss) | true |
| simdjson (reflection) | 4591.75 | 0.267691 | 783.898ms | 2821 | 2560 | 6297.34 | 585.902 | 0.034147 | 1.18416 | 4.56895 | 0.704715 | 0.000697752 | 4.50029e-05 | 6.92352e-06 | 4(Loss) | true |
| glaze | 2627.07 | 0.168746 | 834.939ms | 2821 | 640 | 1911.22 | 1024.07 | 0.0468192 | 2.02593 | 8.76604 | 1.35909 | 0.0003567 | 1.71703e-05 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 6225.42 | 0.217748 | 774.132ms | 2821 | 80 | 70.838 | 432.15 | 0.290091 | 0.898228 | 3.36299 | 0.429635 | 0.000354484 | 4.43105e-05 | 0 | 1(Win) | true |
| jsonifier | 6093.06 | 0.08739 | 779.475ms | 2821 | 640 | 95.2881 | 441.538 | 0.0793314 | 0.908548 | 3.36299 | 0.429635 | 0.000354484 | 1.10776e-05 | 2.21553e-06 | 2(Loss) | true |
| simdjson (ondemand) | 4907.83 | 0.09613 | 781.946ms | 2821 | 4890 | 1357.86 | 548.168 | 0.244478 | 1.11842 | 4.45977 | 0.678129 | 0.000797263 | 6.61124e-05 | 2.153e-05 | 3(Loss) | true |
| simdjson (reflection) | 4694.6 | 0.0550107 | 783.003ms | 2821 | 1280 | 127.208 | 573.066 | 0.245333 | 1.16083 | 4.49876 | 0.68699 | 0.000696783 | 3.01865e-05 | 8.30822e-07 | 4(Loss) | true |
| glaze | 2646.53 | 0.0813915 | 834.292ms | 2821 | 2560 | 1752.47 | 1016.54 | 0.0574041 | 2.00409 | 8.69267 | 1.34031 | 0.000360023 | 4.54183e-05 | 1.53702e-05 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7119.65 | 0.219197 | 781.087ms | 4147 | 1280 | 1897.71 | 555.489 | 0.105651 | 0.765783 | 2.89703 | 0.333254 | 0.000241892 | 3.33449e-05 | 1.50711e-06 | 1(Win) | true |
| jsonifier | 7075.17 | 0.0701373 | 782.699ms | 4147 | 640 | 98.3721 | 558.981 | 0.105549 | 0.767257 | 2.89703 | 0.333253 | 0.000241138 | 1.84621e-05 | 2.26067e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6237.51 | 0.0915128 | 792.261ms | 4147 | 2560 | 861.885 | 634.049 | 0.0795958 | 0.870634 | 3.52665 | 0.492404 | 0.000684983 | 3.1461e-05 | 1.6955e-06 | 3(Loss) | true |
| simdjson (reflection) | 5893.03 | 0.126136 | 795.062ms | 4147 | 160 | 114.654 | 671.112 | 0.174776 | 0.909005 | 3.55004 | 0.498191 | 0.000699301 | 1.95925e-05 | 1.05498e-05 | 4(Loss) | true |
| glaze | 3305.02 | 0.0510679 | 851.806ms | 4147 | 4890 | 1826.1 | 1196.63 | 0.0618991 | 1.59727 | 7.18736 | 1.20039 | 0.000311359 | 3.26942e-05 | 1.26733e-05 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7662.72 | 0.0522537 | 775.206ms | 4147 | 4890 | 355.668 | 516.121 | 0.252393 | 0.719044 | 2.75139 | 0.299011 | 0.000241533 | 1.29199e-05 | 2.41631e-06 | 1(Win) | true |
| jsonifier (two-stage) | 7626.45 | 0.127739 | 779.584ms | 4147 | 160 | 70.2082 | 518.575 | 0.0554711 | 0.715364 | 2.75139 | 0.299011 | 0.000241138 | 3.46636e-05 | 2.56209e-05 | 2(Loss) | true |
| simdjson (ondemand) | 6387.91 | 0.0711637 | 791.674ms | 4147 | 1280 | 248.472 | 619.12 | 0.0103463 | 0.843694 | 3.4748 | 0.479865 | 0.000455525 | 3.16494e-05 | 4.33295e-06 | 3(Loss) | true |
| simdjson (reflection) | 6226.15 | 0.170821 | 791.651ms | 4147 | 160 | 188.379 | 635.206 | 0.453674 | 0.869674 | 3.50229 | 0.486135 | 0.0003813 | 1.05498e-05 | 7.53557e-06 | 4(Loss) | true |
| glaze | 3377.88 | 0.0379917 | 851.194ms | 4147 | 1280 | 253.26 | 1170.82 | 0.00713925 | 1.56586 | 7.136 | 1.18761 | 0.000307074 | 1.46944e-05 | 7.53557e-07 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2972.51 | 0.0726486 | 822.589ms | 2821 | 2560 | 1106.76 | 905.066 | 0.107497 | 1.79026 | 5.88267 | 0.991493 | 0.000359608 | 7.11738e-05 | 1.99397e-05 | 1(Win) | true |
| glaze | 2303.3 | 0.0850504 | 845.512ms | 2821 | 2560 | 2526.37 | 1168.03 | 0.040617 | 2.30274 | 8.87735 | 1.51826 | 0.00101568 | 6.24502e-05 | 1.95243e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2150.78 | 0.0762697 | 861.501ms | 2821 | 320 | 291.252 | 1250.86 | 0.142104 | 2.42744 | 7.86211 | 1.20915 | 0.0003567 | 8.97288e-05 | 2.43708e-05 | 3(Loss) | true |
| simdjson (reflection) | 2121.59 | 0.0478012 | 865.06ms | 2821 | 4890 | 1796.68 | 1268.07 | 0.018614 | 2.45774 | 9.07551 | 1.37044 | 0.000434298 | 8.22055e-05 | 1.13087e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1628.37 | 0.0400643 | 905.723ms | 2821 | 640 | 280.41 | 1652.15 | 0.0365866 | 3.18469 | 9.83587 | 1.70755 | 0.000949353 | 4.2095e-05 | 5.53882e-07 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3348.2 | 0.103907 | 817.317ms | 2821 | 1280 | 892.245 | 803.51 | 0.0374474 | 1.59483 | 5.38568 | 0.860688 | 0.000357531 | 6.42503e-05 | 6.92352e-06 | 1(Win) | true |
| glaze | 2521.73 | 0.177032 | 845.532ms | 2821 | 2560 | 9131.72 | 1066.85 | 0.0226959 | 2.09617 | 8.4105 | 1.39135 | 0.000360438 | 5.98192e-05 | 1.78627e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2446.67 | 0.0968723 | 850.757ms | 2821 | 160 | 181.541 | 1099.58 | 0.118654 | 2.16528 | 7.18717 | 1.04254 | 0.00113435 | 6.86813e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 2297.48 | 0.0610444 | 860.625ms | 2821 | 320 | 163.511 | 1170.99 | 0.180729 | 2.28108 | 8.58384 | 1.24282 | 0.000358915 | 6.0927e-05 | 1.21854e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1713.74 | 0.0929412 | 908.188ms | 2821 | 160 | 340.606 | 1569.85 | 0.133152 | 3.03259 | 9.46154 | 1.60829 | 0.000726693 | 5.31726e-05 | 2.21553e-06 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8120.48 | 0.315795 | 766.758ms | 2821 | 30 | 32.8379 | 331.3 | 0.110798 | 0.702836 | 1.56079 | 0.244949 | 0.000354484 | 7.08968e-05 | 1.18161e-05 | 1(Win) | true |
| simdjson (reflection) | 6002.47 | 0.1341 | 779.443ms | 2821 | 640 | 231.197 | 448.202 | 0.00174311 | 0.918764 | 2.09429 | 0.323999 | 0.000354484 | 5.98192e-05 | 1.44009e-05 | 2(Loss) | true |
| glaze | 5404.31 | 0.151282 | 783.953ms | 2819 | 640 | 362.461 | 497.456 | 0.374255 | 1.01112 | 3.02944 | 0.4569 | 0.000354736 | 2.66052e-05 | 2.77137e-06 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9417.19 | 0.199321 | 761.757ms | 2821 | 160 | 51.8789 | 285.681 | 0.0590345 | 0.614611 | 1.38036 | 0.203119 | 0.000354484 | 4.43105e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6662.94 | 0.0988436 | 774.235ms | 2821 | 4890 | 778.898 | 403.773 | 0.309839 | 0.837116 | 1.91563 | 0.281815 | 0.000355137 | 3.85656e-05 | 4.3495e-06 | 2(Loss) | true |
| glaze | 6385.87 | 0.0936081 | 771.61ms | 2819 | 2560 | 397.572 | 420.993 | 0.224676 | 0.868496 | 2.58815 | 0.365378 | 0.00035529 | 5.27947e-05 | 5.95845e-06 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2994.71 | 0.139194 | 880.596ms | 4147 | 40 | 135.163 | 1320.62 | 0.0460428 | 1.73957 | 5.75717 | 0.818182 | 0.000247167 | 3.01423e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 2948.19 | 0.107176 | 883.563ms | 4147 | 160 | 330.728 | 1341.46 | 0.24848 | 1.76584 | 6.61466 | 0.950808 | 0.000242645 | 4.37063e-05 | 1.20569e-05 | 2(Loss) | true |
| glaze | 2633.19 | 0.0918419 | 900.586ms | 4147 | 1280 | 2435.53 | 1501.94 | 0.130053 | 1.96927 | 7.87895 | 1.39981 | 0.000331 | 3.10842e-05 | 1.88389e-06 | 3(Loss) | true |
| jsonifier | 2516.75 | 0.0667788 | 909.62ms | 4147 | 80 | 88.0956 | 1571.42 | 0.200858 | 2.0611 | 5.54473 | 1.08054 | 0.000244152 | 6.93272e-05 | 3.01423e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2280.45 | 0.0540209 | 931.167ms | 4147 | 2560 | 2246.93 | 1734.26 | 0.528245 | 2.26555 | 7.1319 | 1.18013 | 0.000420579 | 4.03153e-05 | 7.06459e-06 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3394.2 | 0.132881 | 876.64ms | 4147 | 1280 | 3068.51 | 1165.19 | 0.0930166 | 1.5374 | 5.35905 | 0.716904 | 0.000245094 | 4.33295e-05 | 7.53557e-06 | 1(Win) | true |
| simdjson (reflection) | 3165.73 | 0.0630776 | 869.103ms | 4147 | 320 | 198.711 | 1249.28 | 0.319659 | 1.65142 | 6.28213 | 0.86448 | 0.000248674 | 3.39101e-05 | 1.50711e-06 | 2(Loss) | true |
| glaze | 2804.54 | 0.179144 | 898.512ms | 4147 | 40 | 255.276 | 1410.17 | 0.0820737 | 1.85471 | 7.5293 | 1.30697 | 0.000355679 | 0 | 0 | 3(Loss) | true |
| jsonifier | 2750.63 | 0.0299144 | 900.377ms | 4147 | 1280 | 236.796 | 1437.81 | 0.0858159 | 1.89687 | 5.2069 | 0.991801 | 0.000273353 | 3.4852e-05 | 3.20262e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2390.18 | 0.107485 | 927.085ms | 4147 | 160 | 506.082 | 1654.64 | 0.185497 | 2.16814 | 6.87726 | 1.11261 | 0.000513926 | 3.61707e-05 | 7.53557e-06 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11133.2 | 0.111681 | 777.207ms | 4147 | 2560 | 402.926 | 355.232 | 0.0364111 | 0.499957 | 1.06294 | 0.15674 | 0.000244152 | 4.5496e-05 | 3.01423e-06 | 1(Win) | true |
| glaze | 3627.93 | 0.410888 | 850.908ms | 4145 | 1280 | 25655.9 | 1089.6 | 0.285271 | 1.44661 | 3.56864 | 0.511942 | 0.000457253 | 5.57901e-05 | 1.8848e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.08 | 0.151223 | 1491.27ms | 4147 | 1280 | 164800 | 7503.39 | 0.0563906 | 9.59811 | 35.0953 | 7.35737 | 0.00329191 | 0.000140727 | 5.84007e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12251.3 | 0.0703239 | 772.409ms | 4147 | 320 | 16.4914 | 322.812 | 0.0445107 | 0.464721 | 0.985532 | 0.138172 | 0.000241138 | 3.99385e-05 | 0 | 1(Win) | true |
| glaze | 4357.45 | 0.19306 | 829.814ms | 4145 | 4890 | 14999.6 | 907.178 | 0.0237864 | 1.2071 | 2.98239 | 0.379252 | 0.000242932 | 4.86949e-05 | 1.16927e-05 | 2(Loss) | true |
| simdjson (reflection) | 538.848 | 0.243674 | 1480.55ms | 4147 | 320 | 102354 | 7339.52 | 0.158223 | 9.42873 | 35.1083 | 7.36074 | 0.00321543 | 0.000116801 | 4.67205e-05 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3242.7 | 0.19483 | 7472.79ms | 466906 | 1280 | 9.16155e+07 | 137317 | 0.297115 | 1.5401 | 6.14234 | 1.26002 | 0.00202178 | 0.000601279 | 3.09049e-06 | 1(Win) | true |
| glaze | 2363.49 | 0.117325 | 5042.86ms | 466906 | 80 | 3.90866e+06 | 188398 | 0.0376804 | 2.11538 | 8.76985 | 1.98463 | 0.00259343 | 0.000419008 | 2.91815e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1400.49 | 0.43144 | 8385.48ms | 466906 | 40 | 7.52657e+07 | 317942 | 0.0283019 | 3.57937 | 14.0983 | 2.46268 | 0.0131085 | 0.0915539 | 1.526e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3203.45 | 0.113441 | 7479.29ms | 466906 | 2560 | 6.36507e+07 | 138999 | 0.217848 | 1.56247 | 6.14123 | 1.25977 | 0.00206396 | 0.000530129 | 3.97397e-06 | 1(Win) | true |
| glaze | 2338.95 | 0.303488 | 5034.91ms | 466906 | 160 | 5.34097e+07 | 190374 | 0.106746 | 2.14991 | 8.76877 | 1.98438 | 0.00261572 | 0.000314424 | 1.83388e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1398.02 | 0.177051 | 8338.76ms | 466906 | 320 | 1.01761e+08 | 318505 | 0.0494251 | 3.57957 | 14.0987 | 2.4628 | 0.0125321 | 0.0928257 | 8.90838e-06 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4295.29 | 0.0474112 | 8313.29ms | 699405 | 1280 | 6.93815e+06 | 155287 | 0.0894939 | 1.1745 | 4.52355 | 1.13912 | 0.00133861 | 0.000118915 | 1.26447e-06 | 1(Win) | true |
| glaze | 3590.47 | 0.456964 | 9977.77ms | 699405 | 640 | 4.6121e+08 | 185771 | 0.0266857 | 1.39953 | 6.02374 | 1.25783 | 0.00218456 | 0.00149348 | 3.86042e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1448.37 | 0.674215 | 6549.4ms | 767297 | 640 | 7.42579e+09 | 505223 | 0.520519 | 3.44645 | 13.5134 | 2.23507 | 0.0117339 | 0.0940205 | 2.77068e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4279.05 | 0.128686 | 8413.97ms | 699405 | 30 | 1.2071e+06 | 155877 | 0.121401 | 1.18072 | 4.52306 | 1.13902 | 0.00153063 | 0.000153654 | 6.65804e-05 | 1(Win) | true |
| glaze | 3646.57 | 0.199348 | 9829.95ms | 699405 | 1280 | 1.70185e+08 | 182913 | 0.183617 | 1.3829 | 6.02304 | 1.25768 | 0.00214351 | 0.00144457 | 2.91989e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1481.5 | 0.633968 | 6577ms | 767297 | 40 | 3.9221e+08 | 493926 | 0.340221 | 3.3708 | 13.5138 | 2.23519 | 0.011167 | 0.0931912 | 3.19954e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2999.39 | 0.0597434 | 5334.69ms | 631514 | 1280 | 1.842e+07 | 200794 | 0.0760941 | 1.68118 | 8.03357 | 1.32323 | 0.00559234 | 5.30966e-06 | 4.14554e-06 | 1(Win) | true |
| glaze | 2437.86 | 0.0837213 | 6483.13ms | 631514 | 640 | 2.73778e+07 | 247044 | 0.0886643 | 2.07337 | 8.43579 | 1.51693 | 0.008172 | 5.27255e-06 | 4.21111e-06 | 2(Loss) | true |
